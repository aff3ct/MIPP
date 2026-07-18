import json
import os
import sys
from jsonschema import Draft7Validator, validators

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

def validate_categories_config(categories_dict):
    validate_json_data(categories_dict, "categories_schema.json", label="registry_categories.json")

def validate_protos_config(protos_dict):
    validate_json_data(protos_dict, "protos_schema.json", label="registry_protos.json")

def validate_interfaces_config(interfaces_dict):
    validate_json_data(interfaces_dict, "interfaces_schema.json", label="registry_interfaces.json")

def validate_scalar_implems_config(scalar_implems_dict):
    validate_json_data(scalar_implems_dict, "scalar_implems_schema.json", label="registry_scalar_implems.json")
