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
        MAGENTA = ""
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
                
            if choice.get("skip_audit_level") == True:
                continue
                
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
                
            if choice.get("skip_audit_level") == True:
                continue
                
            expected = 1
            if expected != detected:
                discrepancies.append((func, choice, "emu_implems", expected, detected, deps))

    if "levels" in ACTIVE_AUDITS and discrepancies:
        print(Fore.BLUE + f"Warning: Level audit found {len(discrepancies)} implementation placement/level discrepancies for ISA '{isa['name']}':", file=sys.stderr)
        for func, choice, table, declared, detected, deps in discrepancies:
            dts = ", ".join(list(choice.get("datatypes", []))[:2])
            deps_str = f" (MIPP dependencies: {list(deps)})" if deps else ""
            snippet = get_code(choice).strip().replace('\n', ' ')[:50]
            print(Fore.BLUE + f"  - Function '{func}' [{dts}] in '{table}' has declared/expected level {declared} but detected level {detected}{deps_str} (template code: '{snippet}...')", file=sys.stderr)

    # Datatype implementation duplicates check
    from tools import resolve_datatypes
    from cond_utils import are_conds_mutually_exclusive
    func_impls = {}
    
    isa_known_true = [isa["define"]] if "define" in isa and isa["define"] else []
    
    def collect_impls(table, table_name, default_level):
        for func, choices in table.items():
            if func not in func_impls:
                func_impls[func] = {}
            for choice in choices:
                lvl = choice.get("level", default_level)
                dts = resolve_datatypes(choice.get("datatypes", []))
                mv = choice.get("version", "no_mask")
                if mv is None:
                    mv = "no_mask"
                cond = choice.get("if", "")
                for dt in dts:
                    key = (dt, mv)
                    if key not in func_impls[func]:
                        func_impls[func][key] = []
                    func_impls[func][key].append((lvl, table_name, cond))

    collect_impls(implems, "native_implems", 0)
    collect_impls(implems_emu, "emu_implems", 1)
    
    dup_warnings = []
    for func, impls_map in func_impls.items():
        for (dt, mv), locations in impls_map.items():
            if len(locations) > 1:
                lvl_map = {}
                for lvl, tbl, cond in locations:
                    lvl_map.setdefault(lvl, []).append((tbl, cond))
                
                # 1. Duplicates at the same level (only if conditions are not mutually exclusive)
                for lvl, items in lvl_map.items():
                    for i in range(len(items)):
                        for j in range(i + 1, len(items)):
                            tbl1, cond1 = items[i]
                            tbl2, cond2 = items[j]
                            if not are_conds_mutually_exclusive(cond1, cond2, known_true_conds=isa_known_true):
                                dup_warnings.append((func, dt, mv, f"Duplicate definitions at the same level (level {lvl} in {tbl1} and {tbl2}) with overlapping conditions: '{cond1}' and '{cond2}'"))
                
                # 2. Overlap across different levels (only if conditions are not mutually exclusive)
                if len(lvl_map) > 1:
                    levels = list(lvl_map.keys())
                    for i in range(len(levels)):
                        for j in range(i + 1, len(levels)):
                            lvl1, lvl2 = levels[i], levels[j]
                            for tbl1, cond1 in lvl_map[lvl1]:
                                for tbl2, cond2 in lvl_map[lvl2]:
                                    if not are_conds_mutually_exclusive(cond1, cond2, known_true_conds=isa_known_true):
                                        dup_warnings.append((func, dt, mv, f"Overlap across different levels: level {lvl1} ({tbl1}) cond '{cond1}' overlaps with level {lvl2} ({tbl2}) cond '{cond2}'"))

    if "duplicates" in ACTIVE_AUDITS and dup_warnings:
        print(Fore.MAGENTA + f"Warning: Duplicate audit found {len(dup_warnings)} datatype implementation overlaps for ISA '{isa['name']}':", file=sys.stderr)
        for func, dt, mv, reason in dup_warnings:
            print(Fore.MAGENTA + f"  - Function '{func}' for ({dt}, mask: {mv}): {reason}", file=sys.stderr)

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

def validate_categories_logical_integrity(categories_dict, interfaces_dict):
    # 1. Check uniqueness (a function should not be in multiple categories)
    seen_funcs = {}
    for cat, funcs in categories_dict.items():
        for f in funcs:
            if f in seen_funcs:
                print(f"Error: Logical integrity check failed for registry_categories.json:", file=sys.stderr)
                print(f"  - Function '{f}' is declared in multiple categories: '{seen_funcs[f]}' and '{cat}'.", file=sys.stderr)
                sys.exit(1)
            seen_funcs[f] = cat

    # 2. Check for missing categorizations (audit warning)
    if "dead-code" in ACTIVE_AUDITS:
        uncategorized = []
        for f in interfaces_dict:
            if f not in seen_funcs:
                uncategorized.append(f)
        if uncategorized:
            uncategorized.sort()
            print(Fore.YELLOW + "Warning: Found uncategorized functions (declared in registry_interfaces.json but missing from registry_categories.json):", file=sys.stderr)
            for f in uncategorized:
                print(Fore.YELLOW + f"  - Function '{f}' is not assigned to any category.", file=sys.stderr)


def validate_protos_config(protos_dict):
    validate_json_data(protos_dict, "protos_schema.json", label="registry_protos.json")

def validate_interfaces_config(interfaces_dict, protos_dict):
    validate_json_data(interfaces_dict, "interfaces_schema.json", label="registry_interfaces.json")
    for func, val in interfaces_dict.items():
        proto_ref = val.get("proto_ref")
        if proto_ref not in protos_dict:
            print(f"Error: Logical integrity check failed for registry_interfaces.json:", file=sys.stderr)
            print(f"  - Interface '{func}' references prototype '{proto_ref}', which does not exist in registry_protos.json.", file=sys.stderr)
            sys.exit(1)


def validate_scalar_implems_config(scalar_implems_dict):
    validate_json_data(scalar_implems_dict, "scalar_implems_schema.json", label="registry_scalar_implems.json")

def validate_scalar_implems_logical_integrity(scalar_implems_dict, interfaces_dict):
    from tools import resolve_datatypes
    inter_funcs = set(interfaces_dict.keys())
    scal_funcs = set(scalar_implems_dict.keys())

    # 1. Function Coverage Check
    missing_in_scal = inter_funcs - scal_funcs
    if missing_in_scal:
        print("Error: Logical integrity check failed for registry_scalar_implems.json:", file=sys.stderr)
        for f in sorted(missing_in_scal):
            print(f"  - Function '{f}' declared in registry_interfaces.json is missing from registry_scalar_implems.json.", file=sys.stderr)
        sys.exit(1)

    extra_in_scal = scal_funcs - inter_funcs
    if extra_in_scal:
        print("Error: Logical integrity check failed for registry_scalar_implems.json:", file=sys.stderr)
        for f in sorted(extra_in_scal):
            print(f"  - Function '{f}' in registry_scalar_implems.json is not declared in registry_interfaces.json.", file=sys.stderr)
        sys.exit(1)

    # 2. Datatypes Coverage Check
    for func in sorted(inter_funcs):
        inter_dts = set(resolve_datatypes(interfaces_dict[func]["datatypes"]))
        choices = scalar_implems_dict[func]
        scal_dts = set()
        for choice in choices:
            dt_spec = choice.get("datatypes")
            if isinstance(dt_spec, str) and dt_spec == "all_defs":
                scal_dts.update(inter_dts)
            elif isinstance(dt_spec, list):
                for item in dt_spec:
                    if item == "all_defs":
                        scal_dts.update(inter_dts)
                    else:
                        scal_dts.update(resolve_datatypes(item))
            elif dt_spec:
                scal_dts.update(resolve_datatypes(dt_spec))

        if scal_dts != inter_dts:
            diff_missing = inter_dts - scal_dts
            diff_extra = scal_dts - inter_dts
            print(f"Error: Logical integrity check failed for function '{func}':", file=sys.stderr)
            if diff_missing:
                print(f"  - Datatypes declared in registry_interfaces.json but missing from registry_scalar_implems.json: {sorted(diff_missing)}", file=sys.stderr)
            if diff_extra:
                print(f"  - Datatypes in registry_scalar_implems.json not declared in registry_interfaces.json: {sorted(diff_extra)}", file=sys.stderr)
            sys.exit(1)

def audit_generic_templates_dead_code(flat_implems, data_templates):
    if "dead-code" not in ACTIVE_AUDITS:
        return

    reachable = set()
    for choices in flat_implems.values():
        for choice in choices:
            tpl_key = choice.get("template_ref")
            if tpl_key and isinstance(tpl_key, str):
                reachable.add(tpl_key)

    for section in ["tpl_generic_emu", "tpl_mask_generic_emu", "tpl_horiz_lmul_generic_emu"]:
        if section in data_templates:
            dead = []
            for name in data_templates[section]:
                full_name = f"{section}.{name}"
                if full_name not in reachable:
                    dead.append(name)
            if dead:
                dead.sort()
                print(Fore.YELLOW + f"Warning: Found dead (unreferenced) generic templates in '{section}':", file=sys.stderr)
                for name in dead:
                    print(Fore.YELLOW + f"  - Template '{name}' in generic templates is never referenced.", file=sys.stderr)

def audit_scalar_implems_dead_code(scalar_implems, interfaces):
    if "dead-code" not in ACTIVE_AUDITS:
        return
    dead = []
    for func in scalar_implems:
        if func not in interfaces:
            dead.append(func)
    if dead:
        dead.sort()
        print(Fore.YELLOW + "Warning: Found dead (unreferenced) function implementations in 'registry_scalar_implems.json':", file=sys.stderr)
        for func in dead:
            print(Fore.YELLOW + f"  - Function '{func}' is implemented but does not exist in registry_interfaces.json.", file=sys.stderr)


def audit_json_files_structure(gen_dir):
    if "json-structure" not in ACTIVE_AUDITS:
        return

    unsorted_files = []
    empty_implem_files = []

    for root, dirs, files in os.walk(gen_dir):
        if ".venv" in root or ".git" in root or "build" in root or "schemas" in root:
            continue
        for f in files:
            if f.endswith(".json"):
                path = os.path.join(root, f)
                rel_path = os.path.relpath(path, gen_dir)
                try:
                    with open(path, "r", encoding="utf-8") as fp:
                        data = json.load(fp)
                except Exception as e:
                    print(Fore.YELLOW + f"Warning: Failed to parse JSON file '{rel_path}': {e}", file=sys.stderr)
                    continue

                if isinstance(data, dict):
                    keys = list(data.keys())
                    if keys != sorted(keys):
                        unsorted_files.append(rel_path)

                if "implems" in f and isinstance(data, dict):
                    empty_keys = [k for k, v in data.items() if isinstance(v, list) and len(v) == 0]
                    if empty_keys:
                        empty_implem_files.append((rel_path, empty_keys))

    if unsorted_files:
        print(Fore.YELLOW + f"Warning: JSON audit found {len(unsorted_files)} file(s) with unsorted top-level keys:", file=sys.stderr)
        for rel_path in sorted(unsorted_files):
            print(Fore.YELLOW + f"  - '{rel_path}': top-level keys are not sorted lexicographically.", file=sys.stderr)

    if empty_implem_files:
        print(Fore.YELLOW + f"Warning: JSON audit found {len(empty_implem_files)} implementation file(s) containing empty list entries:", file=sys.stderr)
        for rel_path, empty_keys in sorted(empty_implem_files, key=lambda x: x[0]):
            print(Fore.YELLOW + f"  - '{rel_path}': empty function lists for {', '.join(empty_keys)}.", file=sys.stderr)


def audit_generic_emu_dead_code(data_implems, isas_dict, implems_dict):
    if "dead-code" not in ACTIVE_AUDITS:
        return

    from tools import resolve_datatypes

    dead_choices = []
    for sect in ["implems_generic_emu", "implems_mask_generic_emu", "implems_horiz_lmul_generic_emu"]:
        if sect not in data_implems:
            continue
        for func_name, choices in data_implems[sect].items():
            for choice_idx, choice in enumerate(choices):
                pref_isas = choice.get("preferred_simd_ext", [])
                target_isas = [isa_name for isa_name in pref_isas if isa_name in isas_dict] if pref_isas else list(isas_dict.keys())
                
                dts = choice.get("datatypes", [])
                if isinstance(dts, str):
                    dts = resolve_datatypes(dts)
                
                unreachable_dts = []
                for dt in dts:
                    is_reachable_for_any_isa = False
                    for isa_name in target_isas:
                        native_implems, _ = implems_dict.get(isa_name, (None, None))
                        has_native = False
                        if native_implems and func_name in native_implems:
                            for n_choice in native_implems[func_name]:
                                n_dts = n_choice.get("datatypes", [])
                                if isinstance(n_dts, str):
                                    n_dts = resolve_datatypes(n_dts)
                                if dt in n_dts:
                                    has_native = True
                                    break
                        if not has_native:
                            is_reachable_for_any_isa = True
                            break
                    if not is_reachable_for_any_isa:
                        unreachable_dts.append(dt)
                
                if unreachable_dts and len(unreachable_dts) == len(dts):
                    template_ref = choice.get("template_ref", choice.get("template", f"choice #{choice_idx}"))
                    if isinstance(template_ref, dict):
                        template_ref = f"choice #{choice_idx}"
                    dead_choices.append((func_name, template_ref, pref_isas, len(unreachable_dts)))

    if dead_choices:
        print(Fore.YELLOW + "Warning: Found dead (unreachable) emulation choices in generic emulation files:", file=sys.stderr)
        for func_name, template_ref, pref_isas, dt_count in dead_choices:
            isa_str = f" for preferred ISA(s) {pref_isas}" if pref_isas else ""
            print(Fore.YELLOW + f"  - Function '{func_name}' template '{template_ref}'{isa_str} is dead code (all {dt_count} datatypes are already natively implemented).", file=sys.stderr)



