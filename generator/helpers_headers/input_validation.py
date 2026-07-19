import json
import os
import sys
from jsonschema import Draft7Validator, validators

ACTIVE_AUDITS = set()

try:
    import colorama
    colorama.init(autoreset=True)
    from colorama import Fore
    HAS_COLOR = True
except ImportError:
    HAS_COLOR = False
    class DummyFore:
        BLUE = ""
        YELLOW = ""
    Fore = DummyFore()

def extend_with_default(validator_class):
    validate_properties = validator_class.VALIDATORS["properties"]

    def set_defaults(validator, properties, instance, schema):
        for property, subschema in properties.items():
            if "default" in subschema:
                instance.setdefault(property, subschema["default"])

        for error in validate_properties(validator, properties, instance, schema):
            yield error

    return validators.extend(
        validator_class,
        {"properties": set_defaults},
    )

DefaultValidatingDraft7Validator = extend_with_default(Draft7Validator)

def load_schema(schema_name):
    current_dir = os.path.dirname(os.path.abspath(__file__))
    schema_path = os.path.join(current_dir, "schemas", schema_name)
    with open(schema_path, "r") as f:
        return json.load(f)

def validate_json_data(data, schema_name, label="JSON"):
    schema = load_schema(schema_name)
    validator = DefaultValidatingDraft7Validator(schema)
    errors = sorted(validator.iter_errors(data), key=lambda e: e.path)
    
    if errors:
        print(f"Error: Validation failed for {label}:", file=sys.stderr)
        for error in errors:
            path = " -> ".join([str(p) for p in error.path])
            location = f" at '{path}'" if path else ""
            print(f"  - {error.message}{location}", file=sys.stderr)
        sys.exit(1)

def validate_isa_config(isa_dict, isa_name):
    file_label = f"{isa_name}_isa.json"
    validate_json_data(isa_dict, "isa_schema.json", label=file_label)
    
    # Semantic/cross-field validation
    sw_ldiv_type = isa_dict.get("sw_ldiv_type", "native")
    if sw_ldiv_type == "sub_isa":
        sub_isa_name = isa_dict.get("sub_isa")
        if not sub_isa_name:
            print(f"Error: Validation failed for {file_label}:", file=sys.stderr)
            print(f"  - Field 'sub_isa' must be defined and non-empty when 'sw_ldiv_type' is set to 'sub_isa'.", file=sys.stderr)
            sys.exit(1)
        
        hw_lmuls = isa_dict.get("hw_lmul", [1])
        sw_lmuls = isa_dict.get("sw_lmul", [])
        all_ldivs = [int(x) for x in (hw_lmuls + sw_lmuls) if int(x) < 0]
        for ldiv in all_ldivs:
            if ldiv != -2:
                print(f"Error: Validation failed for {file_label}:", file=sys.stderr)
                print(f"  - Unsupported ldiv factor '{ldiv}'. Only ldiv = -2 is supported with sub_isa.", file=sys.stderr)
                sys.exit(1)
        
        # Verify sub_isa directory exists under simd_ext/
        base_dir = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
        sub_isa_dir = os.path.join(base_dir, "simd_ext", sub_isa_name)
        if not os.path.isdir(sub_isa_dir):
            print(f"Error: Validation failed for {file_label}:", file=sys.stderr)
            print(f"  - Referenced sub_isa '{sub_isa_name}' directory does not exist under 'simd_ext/'.", file=sys.stderr)
            sys.exit(1)

def validate_templates_config(templates_dict, file_name):
    validate_json_data(templates_dict, "templates_schema.json", label=os.path.basename(file_name))

def validate_implems_config(implems_dict, file_name):
    validate_json_data(implems_dict, "implems_schema.json", label=os.path.basename(file_name))

def validate_template_references(raw_implems, tpl_dict, implems_filename):
    file_label = os.path.basename(implems_filename)
    for func, choices in raw_implems.items():
        for choice in choices:
            tpl_key = choice.get("template") or choice.get("template_ref")
            if tpl_key and isinstance(tpl_key, str):
                if "." in tpl_key:
                    section, name = tpl_key.split(".", 1)
                    if section in tpl_dict and isinstance(tpl_dict[section], dict):
                        if name not in tpl_dict[section]:
                            print(f"Error: Validation failed for {file_label}:", file=sys.stderr)
                            print(f"  - Function '{func}' references template '{tpl_key}', which does not exist in templates file.", file=sys.stderr)
                            sys.exit(1)
                    elif tpl_key not in tpl_dict:
                        print(f"Error: Validation failed for {file_label}:", file=sys.stderr)
                        print(f"  - Function '{func}' references template '{tpl_key}', which does not exist in templates file.", file=sys.stderr)
                        sys.exit(1)
                else:
                    if tpl_key not in tpl_dict:
                        print(f"Error: Validation failed for {file_label}:", file=sys.stderr)
                        print(f"  - Function '{func}' references template '{tpl_key}', which does not exist in templates file.", file=sys.stderr)
                        sys.exit(1)

def check_dependency_cycles(implems_emu, isa_name):
    # Build dependency graph
    graph = {}
    for func, choices in implems_emu.items():
        deps = set()
        for choice in choices:
            if "dependencies" in choice:
                deps.update(choice["dependencies"])
        graph[func] = list(deps)
        
    # Cycle detection using DFS (three-color coloring)
    visited = {} # None: unvisited, 1: visiting, 2: visited
    
    def dfs(node):
        visited[node] = 1 # Visiting
        for neighbor in graph.get(node, []):
            if visited.get(neighbor, 0) == 1:
                print(f"Error: Dependency cycle detected in emulated functions for {isa_name}:", file=sys.stderr)
                print(f"  - Function '{node}' has a circular dependency involving '{neighbor}'.", file=sys.stderr)
                sys.exit(1)
            elif visited.get(neighbor, 0) == 0:
                dfs(neighbor)
        visited[node] = 2 # Visited
        
    for node in graph:
        if visited.get(node, 0) == 0:
            dfs(node)

def validate_logical_integrity(isa, implems, implems_emu):
    # Load raw registries to perform cross-registry validation
    current_dir = os.path.dirname(os.path.abspath(__file__))
    with open(os.path.join(current_dir, "registry_categories.json"), "r", encoding="utf-8") as f:
        categories = json.load(f)
    with open(os.path.join(current_dir, "registry_interfaces.json"), "r", encoding="utf-8") as f:
        interfaces = json.load(f)
    with open(os.path.join(current_dir, "registry_protos.json"), "r", encoding="utf-8") as f:
        protos = json.load(f)

    # 1. Verify that in categories, the function names exist in the interfaces
    for cat_name, func_list in categories.items():
        for func_name in func_list:
            if func_name not in interfaces:
                print(f"Error: Logical integrity check failed:", file=sys.stderr)
                print(f"  - Function '{func_name}' listed in category '{cat_name}' does not exist in registry_interfaces.json.", file=sys.stderr)
                sys.exit(1)

    # 2. Verify that all proto refs in interfaces exist in protos
    for func_name, interface in interfaces.items():
        proto_ref = interface.get("proto_ref")
        if proto_ref not in protos:
            print(f"Error: Logical integrity check failed:", file=sys.stderr)
            print(f"  - Interface '{func_name}' references prototype '{proto_ref}', which does not exist in registry_protos.json.", file=sys.stderr)
            sys.exit(1)

    # 3. Verify that all native/emulated implementations and dependencies exist in interfaces
    for func_name in implems:
        if func_name not in interfaces:
            print(f"Error: Logical integrity check failed for {isa['name']}:", file=sys.stderr)
            print(f"  - Function '{func_name}' has native implementations but does not exist in registry_interfaces.json.", file=sys.stderr)
            sys.exit(1)
            
    for func_name, choices in implems_emu.items():
        if func_name not in interfaces:
            print(f"Error: Logical integrity check failed for {isa['name']}:", file=sys.stderr)
            print(f"  - Function '{func_name}' has emulated implementations but does not exist in registry_interfaces.json.", file=sys.stderr)
            sys.exit(1)
        for choice in choices:
            if "dependencies" in choice:
                for dep in choice["dependencies"]:
                    if dep not in interfaces:
                        print(f"Error: Logical integrity check failed for {isa['name']}:", file=sys.stderr)
                        print(f"  - Emulation for '{func_name}' has dependency '{dep}', which does not exist in registry_interfaces.json.", file=sys.stderr)
                        sys.exit(1)

    # 4. Verify that implementation datatypes are supported by the ISA and are a subset of the interface datatypes
    from tools import resolve_datatypes
    supported_datatypes = set(isa["datatypes"].keys())
    
    def check_implem_datatypes(table, name):
        for func, choices in table.items():
            interface_dts = set(resolve_datatypes(interfaces[func]["datatypes"]))
            for choice in choices:
                for dt in choice["datatypes"]:
                    parts = dt.split(",")
                    for part in parts:
                        if part not in supported_datatypes:
                            print(f"Error: Validation failed for {isa['name']}:", file=sys.stderr)
                            print(f"  - Function '{func}' in {name} table claims support for datatype '{dt}' (involving unsupported '{part}'), but this datatype is not defined as supported by the ISA configuration.", file=sys.stderr)
                            sys.exit(1)
                    if dt not in interface_dts:
                        print(f"Error: Validation failed for {isa['name']}:", file=sys.stderr)
                        print(f"  - Function '{func}' in {name} table claims support for datatype '{dt}', but this datatype is not supported by its interface in registry_interfaces.json.", file=sys.stderr)
                        sys.exit(1)
                        
    check_implem_datatypes(implems, "native implems")
    check_implem_datatypes(implems_emu, "emulated implems")
    
    # Check cycles in emulations
    check_dependency_cycles(implems_emu, isa["name"])

    # Audit implementation levels
    audit_and_validate_implementation_levels(isa, implems, implems_emu)

def audit_and_validate_implementation_levels(isa, implems, implems_emu):
    if not ACTIVE_AUDITS:
        return
    import re
    import sys
    prefix = isa.get("prefix", "")

    # Build dynamic hardware intrinsic matching set/regex from datatypes
    hw_types = set()
    hw_suffixes = set()

    def expand_val(val_str, dt_info):
        if not isinstance(val_str, str):
            return {str(val_str)}
        placeholders = re.findall(r'\{([A-Za-z0-9_]+)\}', val_str)
        if not placeholders:
            return {val_str}
            
        import itertools
        possible_values = {}
        for p in placeholders:
            if p in dt_info and isinstance(dt_info[p], dict):
                possible_values[p] = list(dt_info[p].values())
            else:
                val = dt_info.get(p, "")
                possible_values[p] = [str(val)]
                
        keys = list(possible_values.keys())
        value_combinations = itertools.product(*(possible_values[k] for k in keys))
        
        expanded = set()
        for combo in value_combinations:
            sub_dict = dict(zip(keys, combo))
            try:
                expanded.add(val_str.format(**sub_dict))
            except Exception:
                expanded.add(val_str)
        return expanded

    # Collect prefixes dynamically by traversing the sub_isa hierarchy
    prefixes = []
    curr_isa = isa
    while curr_isa:
        if "prefix" in curr_isa and curr_isa["prefix"]:
            prefixes.append(curr_isa["prefix"])
            
        # Collect register types and suffixes for the current ISA node in the hierarchy
        for dt_name, dt_info in curr_isa.get("datatypes", {}).items():
            for key in ["reg", "msk", "data_ext", "data_ext_logi", "data_ext_msk", "uint_data_ext", "int_data_ext", "reg_dt_ext"]:
                if key in dt_info:
                    val = dt_info[key]
                    val_list = val if isinstance(val, list) else [val]
                    for v in val_list:
                        expanded_vals = expand_val(v, dt_info)
                        for ev in expanded_vals:
                            ev_clean = ev.strip()
                            if key in ["reg", "msk"]:
                                hw_types.add(ev_clean)
                            else:
                                hw_suffixes.add(ev_clean)

        sub_isa_name = curr_isa.get("sub_isa")
        if sub_isa_name:
            from tools import load_isa_config
            try:
                curr_isa, _, _ = load_isa_config(sub_isa_name)
            except Exception:
                curr_isa = None
        else:
            curr_isa = None

    hw_patterns = []
    
    # 1. Any Jinja2 reference to register, mask, prefix, or data extension variables
    hw_patterns.append(r'\{\{[^}]*\b(prefix|reg|msk|data_ext|uint_data_ext|int_data_ext|reg_dt_ext|msk_short)\b[^}]*\}\}')
    
    # MIPP architecture-specific wrapper calls
    helpers_dir = os.path.dirname(os.path.abspath(__file__))
    generator_dir = os.path.dirname(helpers_dir)
    simd_ext_dir = os.path.join(generator_dir, "simd_ext")
    exts = []
    if os.path.exists(simd_ext_dir):
        exts = [d for d in os.listdir(simd_ext_dir) if os.path.isdir(os.path.join(simd_ext_dir, d)) and d != "__pycache__"]
    if "scalar" not in exts:
        exts.append("scalar")
    escaped_exts = [re.escape(e) for e in exts]
    hw_patterns.append(r'\bmipp_(' + '|'.join(escaped_exts) + r')\b')
    
    # 2. Known register/mask types
    if hw_types:
        escaped_types = [re.escape(t) for t in hw_types]
        hw_patterns.append(r'\b(' + '|'.join(escaped_types) + r')\b')
        
    # 3. Dynamic architecture prefixes matching
    for p in prefixes:
        if p:
            if len(p) <= 2:
                if hw_suffixes:
                    escaped_sfx = [re.escape(s) for s in hw_suffixes]
                    hw_patterns.append(r'\b' + re.escape(p) + r'[a-z0-9_]*_(' + '|'.join(escaped_sfx) + r')(_[a-z0-9_]+)?\b')
            else:
                hw_patterns.append(r'\b' + re.escape(p))

    # 4. Suffix matching
    if hw_suffixes:
        escaped_sfx = [re.escape(s) for s in hw_suffixes]
        hw_patterns.append(r'\b[a-zA-Z0-9_]+_(' + '|'.join(escaped_sfx) + r')(_[a-zA-Z0-9_]+)?\b')

    combined_pattern = re.compile('|'.join(hw_patterns))

    def has_hw(code):
        if not code:
            return False
        return bool(combined_pattern.search(code))

    def get_mipp_dependencies(code, func_name):
        if not code:
            return set()
        deps = set()
        placeholder_regex = re.compile(r'\%([^%\n]*)\%')
        matches = placeholder_regex.findall(code)
        for m in matches:
            m_clean = m.strip()
            if m_clean and not m_clean.startswith("{") and not m_clean.endswith("}"):
                if any(k in m_clean for k in ["isa", "dt_par", "dt_ret", "elif", "else", "endif"]):
                    continue
                dep_name = m_clean.split('<')[0].strip()
                if dep_name:
                    first_word = dep_name.split()[0]
                    if first_word not in ["if", "else", "endif", "for", "endfor"]:
                        if dep_name not in ["r", "m", "v", "N", "cast", "cast_k", "toreg", "tomsk"] and not dep_name.startswith("{"):
                            deps.add(dep_name)
        return deps

    def count_useful_intrinsics(code):
        if not code:
            return 0
        clean_code = re.sub(r"%[^%\n]+%", "", code)
        clean_code = re.sub(r"\{\{[^}]*\}\}", "JINJA", clean_code)
        calls = re.findall(r"\b([a-zA-Z0-9_]+)\s*\(", clean_code)
        ignore = {"if", "for", "while", "switch", "return", "defined", "sizeof", "cast", "toreg", "tomsk", "cast_k"}
        useful_calls = [c for c in calls if c.lower() not in ignore and "cast" not in c.lower()]
        return len(useful_calls)

    def get_code(choice):
        tpl = choice.get("template", {})
        if isinstance(tpl, dict):
            code_val = tpl.get("code", "")
            if isinstance(code_val, list):
                return "\n".join(code_val)
            return str(code_val)
        return str(tpl)

    discrepancies = []

    # Check native implems (expected level 0)
    for func, choices in implems.items():
        for choice in choices:
            code = get_code(choice)
            has_hardware = has_hw(code)
            deps = get_mipp_dependencies(code, func)
            has_deps = len(deps) > 0
            
            # Detected level
            if has_hardware:
                if has_deps or count_useful_intrinsics(code) > 1:
                    detected = 1
                else:
                    detected = 0
            else:
                detected = 2
                
            expected = 0
            if expected != detected:
                discrepancies.append((func, choice, "native_implems", expected, detected, deps))

    # Check emu implems (expected level 1)
    for func, choices in implems_emu.items():
        for choice in choices:
            code = get_code(choice)
            has_hardware = has_hw(code)
            deps = get_mipp_dependencies(code, func)
            has_deps = len(deps) > 0
            
            # Detected level
            if has_hardware:
                if has_deps or count_useful_intrinsics(code) > 1:
                    detected = 1
                else:
                    detected = 0
            else:
                detected = 2
                
            expected = 1
            if expected != detected:
                discrepancies.append((func, choice, "emu_implems", expected, detected, deps))

    if "levels" in ACTIVE_AUDITS and discrepancies:
        print(Fore.BLUE + f"Warning: Level audit found {len(discrepancies)} implementation placement/level discrepancies for ISA '{isa['name']}':", file=sys.stderr)
        for func, choice, table, declared, detected, deps in discrepancies:
            dts = ", ".join(list(choice.get("datatypes", []))[:2])
            deps_str = f" (MIPP dependencies: {list(deps)})" if deps else ""
            print(Fore.BLUE + f"  - Function '{func}' [{dts}] in '{table}' has declared/expected level {declared} but detected level {detected}{deps_str} (template code: '{get_code(choice).strip().replace('\n', ' ')[:50]}...')", file=sys.stderr)

    # Dead templates detection
    import json
    helpers_dir = os.path.dirname(os.path.abspath(__file__))
    generator_dir = os.path.dirname(helpers_dir)
    simd_ext_dir = os.path.join(generator_dir, "simd_ext")
    isa_dir = os.path.join(simd_ext_dir, isa["name"])
    native_tpl_path = os.path.join(isa_dir, f"{isa['name']}_native_templates.json")
    emu_tpl_path = os.path.join(isa_dir, f"{isa['name']}_emu_templates.json")

    native_templates = {}
    if os.path.exists(native_tpl_path):
        with open(native_tpl_path, "r") as f:
            try:
                native_templates = json.load(f)
            except Exception:
                pass
    emu_templates = {}
    if os.path.exists(emu_tpl_path):
        with open(emu_tpl_path, "r") as f:
            try:
                emu_templates = json.load(f)
            except Exception:
                pass

    native_impl_path = os.path.join(isa_dir, f"{isa['name']}_native_implems.json")
    emu_impl_path = os.path.join(isa_dir, f"{isa['name']}_emu_implems.json")

    native_implems = {}
    if os.path.exists(native_impl_path):
        with open(native_impl_path, "r") as f:
            try:
                native_implems = json.load(f)
            except Exception:
                pass
    emu_implems_raw = {}
    if os.path.exists(emu_impl_path):
        with open(emu_impl_path, "r") as f:
            try:
                emu_implems_raw = json.load(f)
            except Exception:
                pass

    all_raw_choices = []
    for choices in native_implems.values():
        all_raw_choices.extend(choices)
    for choices in emu_implems_raw.values():
        all_raw_choices.extend(choices)

    reachable = set()
    for choice in all_raw_choices:
        tpl_key = choice.get("template") or choice.get("template_ref")
        if tpl_key and isinstance(tpl_key, str):
            if "." in tpl_key:
                tpl_key = tpl_key.split(".", 1)[1]
            reachable.add(tpl_key)

    all_templates = {}
    for name, info in native_templates.items():
        if isinstance(info, dict):
            code_val = info.get("code", "")
            if isinstance(code_val, list):
                all_templates[name] = "\n".join(code_val)
            else:
                all_templates[name] = str(code_val)
    for name, info in emu_templates.items():
        if isinstance(info, dict):
            code_val = info.get("code", "")
            if isinstance(code_val, list):
                all_templates[name] = "\n".join(code_val)
            else:
                all_templates[name] = str(code_val)

    placeholder_regex = re.compile(r'\%([^%\n]*)\%')
    queue = list(reachable)
    visited = set(reachable)
    while queue:
        curr = queue.pop(0)
        code = all_templates.get(curr, "")
        if code:
            matches = placeholder_regex.findall(code)
            for m in matches:
                m_clean = m.strip()
                if m_clean and not m_clean.startswith("{") and not m_clean.endswith("}"):
                    if any(k in m_clean for k in ["isa", "dt_par", "dt_ret", "elif", "else", "endif"]):
                        continue
                    dep_name = m_clean.split('<')[0].strip()
                    if dep_name and dep_name in all_templates:
                        if dep_name not in visited:
                            visited.add(dep_name)
                            queue.append(dep_name)

    dead_native = sorted([name for name in native_templates if name not in visited])
    dead_emu = sorted([name for name in emu_templates if name not in visited])

    if "dead-code" in ACTIVE_AUDITS and (dead_native or dead_emu):
        print(Fore.YELLOW + f"Warning: Found dead (unreferenced) templates for ISA '{isa['name']}':", file=sys.stderr)
        for name in dead_native:
            print(Fore.YELLOW + f"  - Template '{name}' in native_templates is never referenced.", file=sys.stderr)
        for name in dead_emu:
            print(Fore.YELLOW + f"  - Template '{name}' in emu_templates is never referenced.", file=sys.stderr)

def validate_categories_config(categories_dict):
    validate_json_data(categories_dict, "categories_schema.json", label="registry_categories.json")

def validate_protos_config(protos_dict):
    validate_json_data(protos_dict, "protos_schema.json", label="registry_protos.json")

def validate_interfaces_config(interfaces_dict):
    validate_json_data(interfaces_dict, "interfaces_schema.json", label="registry_interfaces.json")

def validate_scalar_implems_config(scalar_implems_dict):
    validate_json_data(scalar_implems_dict, "scalar_implems_schema.json", label="registry_scalar_implems.json")
