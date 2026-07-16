"""
Registry Module
Loads the central registry of MIPP functions, prototypes, default scalar
fallback implementations, and generic emulation templates from JSON databases.
"""
import os
import json
import copy

# Import resolve_datatypes from tools
from tools import resolve_datatypes

class MaskSupport:
    def __init__(self, maskable=False, maskzable=False, masksable=False):
        self.maskable = maskable
        self.maskzable = maskzable
        self.masksable = masksable

    def is_maskable(self):
        return self.maskable
    def is_maskzable(self):
        return self.maskzable
    def is_masksable(self):
        return self.masksable
    def is_any_mask(self):
        return self.maskable or self.maskzable or self.masksable
    def is_none(self):
        return not self.is_any_mask()
    def is_supported(self, mask_str):
        if mask_str == "mask":
            return self.maskable
        elif mask_str == "maskz":
            return self.maskzable
        elif mask_str == "masks":
            return self.masksable
        else:
            raise ValueError(f"Invalid mask type: {mask_str}")

only_maskz = MaskSupport(maskable=False, maskzable=True, masksable=False)
only_mask = MaskSupport(maskable=True, maskzable=False, masksable=False)
only_masks = MaskSupport(maskable=False, maskzable=False, masksable=True)
mask_and_maskz = MaskSupport(maskable=True, maskzable=True, masksable=False)
mask_and_masks = MaskSupport(maskable=True, maskzable=False, masksable=True)
maskz_and_masks = MaskSupport(maskable=False, maskzable=True, masksable=True)
all_mask = MaskSupport(maskable=True, maskzable=True, masksable=True)
no_mask = MaskSupport(maskable=False, maskzable=False, masksable=False)

def _load_funcs_registry():
    current_dir = os.path.dirname(os.path.abspath(__file__))

    with open(os.path.join(current_dir, "registry_protos.json"), "r", encoding="utf-8") as f:
        raw_protos = json.load(f)

    with open(os.path.join(current_dir, "registry_categories.json"), "r", encoding="utf-8") as f:
        mipp_funcs_categories = json.load(f)

    with open(os.path.join(current_dir, "registry_mipp_funcs.json"), "r", encoding="utf-8") as f:
        raw_mipp_funcs = json.load(f)

    with open(os.path.join(current_dir, "registry_implems_scalar.json"), "r", encoding="utf-8") as f:
        raw_implems_scalar = json.load(f)

    def resolve_fixed_datatype(fd):
        if fd is False:
            return False
        return fd

    # Resolve protos
    protos = {}
    for k, v in raw_protos.items():
        cleaned_proto = {
            "ret": {
                "type": v["ret"]["type"],
                "fixeddatatype": resolve_fixed_datatype(v["ret"]["fixeddatatype"])
            }
        }
        if "charac" in v["ret"]:
            cleaned_proto["ret"]["charac"] = v["ret"]["charac"]
            
        cleaned_proto["args"] = []
        for arg in v["args"]:
            c_arg = {
                "type": arg["type"],
                "fixeddatatype": resolve_fixed_datatype(arg["fixeddatatype"])
            }
            if "charac" in arg:
                c_arg["charac"] = arg["charac"]
            if "offset_lmul" in arg:
                c_arg["offset_lmul"] = arg["offset_lmul"]
            cleaned_proto["args"].append(c_arg)
        protos[k] = cleaned_proto

    # Resolve mask support specs
    MASK_SUPPORT_MAP = {
        "only_maskz": only_maskz,
        "only_mask": only_mask,
        "only_masks": only_masks,
        "mask_and_maskz": mask_and_maskz,
        "mask_and_masks": mask_and_masks,
        "maskz_and_masks": maskz_and_masks,
        "all_mask": all_mask,
        "no_mask": no_mask
    }

    # Resolve mipp_funcs
    mipp_funcs = {}
    for k, v in raw_mipp_funcs.items():
        mipp_funcs[k] = {
            "proto": protos[v["proto_ref"]],
            "datatypes": resolve_datatypes(v["datatypes"]),
            "horizontal": v["horizontal"],
            "mask_support": MASK_SUPPORT_MAP[v["mask_support"]]
        }

    # Resolve implems_scalar
    implems_scalar = {}
    for k, v in raw_implems_scalar.items():
        implems_scalar[k] = []
        for item in v:
            implem_val = item["implem"]
            if isinstance(implem_val, list):
                implem_val = "\n".join(implem_val)
                # Keep leading and trailing newlines like original code
                implem_val = "\n" + implem_val + "\n"
            implems_scalar[k].append({
                "type": item["type"],
                "datatypes": resolve_datatypes(item["datatypes"]),
                "mask_variants": item["mask_variants"],
                "implem": implem_val
            })

    return protos, mipp_funcs_categories, mipp_funcs, implems_scalar

def _load_generic_emu():
    current_dir = os.path.dirname(os.path.abspath(__file__))
    json_path = os.path.join(current_dir, "registry_emu.json")
    with open(json_path, "r") as f:
        data = json.load(f)

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
protos, mipp_funcs_categories, mipp_funcs, implems_scalar = _load_funcs_registry()
copy_mipp_funcs = copy.deepcopy(mipp_funcs)

_current_dir = os.path.dirname(os.path.abspath(__file__))
with open(os.path.join(_current_dir, "registry_isa_scalar.json"), "r") as f:
    isa_scalar = json.load(f)

implems_generic_emu, implems_mask_generic_emu, implems_horiz_lmul_generic_emu = _load_generic_emu()
