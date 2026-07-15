import os
import json
from tools import (
    all_float, all_uint, all_datatypes, all_datatypes_widenning,
    float64, float32, int64, int32, int16, int8, uint64, uint32, uint16, uint8
)

def _load_generic_emu():
    current_dir = os.path.dirname(os.path.abspath(__file__))
    json_path = os.path.join(current_dir, "generic_emu.json")
    with open(json_path, "r") as f:
        data = json.load(f)
        
    DATATYPES_MAP = {
        "all_float": all_float,
        "all_uint": all_uint,
        "all_datatypes": all_datatypes,
        "all_datatypes_widenning": all_datatypes_widenning,
        "float64": [float64],
        "float32": [float32],
        "int64": [int64],
        "int32": [int32],
        "int16": [int16],
        "int8": [int8],
        "uint64": [uint64],
        "uint32": [uint32],
        "uint16": [uint16],
        "uint8": [uint8]
    }
    
    def resolve_datatypes(spec):
        if isinstance(spec, str):
            spec = [spec]
        resolved = []
        for s in spec:
            if s in DATATYPES_MAP:
                resolved.extend(DATATYPES_MAP[s])
            else:
                raise ValueError(f"Unknown datatype spec: {s}")
        return resolved

    def clean_template_code(tpl):
        if not isinstance(tpl, dict) or "code" not in tpl:
            return tpl
        res = dict(tpl)
        code_val = res["code"]
        if isinstance(code_val, list):
            res["code"] = "\n\t".join(code_val)
        return res

    templates_pool = {}
    for section in ["tpl_generic_emu", "tpl_mask_generic_emu", "tpl_horiz_lmul_generic_emu"]:
        for name, tpl in data["templates"][section].items():
            templates_pool[f"{section}.{name}"] = tpl

    # Pre-add snippet ends if needed
    snippet_ends = {
        "SNIPPET_END_MSK": data["templates"]["SNIPPET_END_MSK"],
        "SNIPPET_END_MSKZ": data["templates"]["SNIPPET_END_MSKZ"],
        "SNIPPET_END_MSKS": data["templates"]["SNIPPET_END_MSKS"]
    }

    def process_table(raw_table, default_type=None, default_level=None):
        processed = {}
        for func_name, items in raw_table.items():
            processed[func_name] = []
            for item in items:
                processed_item = {
                    "instr_name": item["instr_name"],
                    "datatypes": resolve_datatypes(item["datatypes"])
                }
                if "version" in item:
                    processed_item["version"] = item["version"]
                if "dependencies" in item:
                    processed_item["dependencies"] = set(item["dependencies"])
                
                # Resolve template
                if "template_ref" in item:
                    ref = item["template_ref"]
                    if ref in templates_pool:
                        processed_item["template"] = clean_template_code(templates_pool[ref])
                    else:
                        raise ValueError(f"Template reference not found: {ref}")
                elif "template" in item:
                    processed_item["template"] = clean_template_code(item["template"])
                
                # Set default type/level
                if "type" not in processed_item:
                    if default_type is not None:
                        processed_item["type"] = default_type
                if default_level is not None:
                    processed_item["level"] = default_level
                    
                processed[func_name].append(processed_item)
        return processed

    implems_generic_emu = process_table(data["implems_generic_emu"], default_type="emulated", default_level=2)
    implems_mask_generic_emu = process_table(data["implems_mask_generic_emu"], default_type="emulated", default_level=2)
    implems_horiz_lmul_generic_emu = process_table(data["implems_horiz_lmul_generic_emu"], default_level=2)
    
    return implems_generic_emu, implems_mask_generic_emu, implems_horiz_lmul_generic_emu

# Initialize globals dynamically
implems_generic_emu, implems_mask_generic_emu, implems_horiz_lmul_generic_emu = _load_generic_emu()
