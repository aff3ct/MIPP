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
            if tpl_key:
                if "." in tpl_key:
                    section, name = tpl_key.split(".", 1)
                    if section not in tpl_dict or name not in tpl_dict[section]:
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
    supported_datatypes = set(isa["datatypes"].keys())
    
    def check_implem_datatypes(table, name):
        for func, choices in table.items():
            for choice in choices:
                for dt in choice["datatypes"]:
                    parts = dt.split(",")
                    for part in parts:
                        if part not in supported_datatypes:
                            print(f"Error: Validation failed for {isa['name']}:", file=sys.stderr)
                            print(f"  - Function '{func}' in {name} table claims support for datatype '{dt}' (involving unsupported '{part}'), but this datatype is not defined as supported by the ISA configuration.", file=sys.stderr)
                            sys.exit(1)
                        
    check_implem_datatypes(implems, "native implems")
    check_implem_datatypes(implems_emu, "emulated implems")
    
    # Check cycles in emulations
    check_dependency_cycles(implems_emu, isa["name"])
