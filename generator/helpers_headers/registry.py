"""
Registry Module
Loads the central registry of MIPP functions, prototypes, default scalar
fallback implementations, and generic emulation templates from JSON databases.
"""
import os
import json
import copy

from tools import resolve_datatypes
from datatypes import (
    all_float, all_uint, all_int, all_int_uint, all_datatypes, all_64bit, all_32bit, all_16bit, all_8bit,
    all_datatypes_cart_prod, all_datatypes_widenning,
    float64, float32, int64, int32, int16, int8, uint64, uint32, uint16, uint8
)

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
        categories = json.load(f)

    with open(os.path.join(current_dir, "registry_interfaces.json"), "r", encoding="utf-8") as f:
        raw_interfaces = json.load(f)

    with open(os.path.join(current_dir, "registry_scalar_implems.json"), "r", encoding="utf-8") as f:
        raw_scalar_implems = json.load(f)

    from input_validation import (
        validate_protos_config, validate_categories_config,
        validate_interfaces_config, validate_scalar_implems_config,
        validate_categories_logical_integrity, validate_scalar_implems_logical_integrity
    )
    validate_protos_config(raw_protos)
    validate_categories_config(categories)
    validate_categories_logical_integrity(categories, raw_interfaces)
    validate_interfaces_config(raw_interfaces, raw_protos)
    validate_scalar_implems_config(raw_scalar_implems)
    validate_scalar_implems_logical_integrity(raw_scalar_implems, raw_interfaces)

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

    # Resolve interfaces
    interfaces = {}
    for k, v in raw_interfaces.items():
        interfaces[k] = {
            "proto": protos[v["proto_ref"]],
            "datatypes": resolve_datatypes(v["datatypes"]),
            "horizontal": v["horizontal"],
            "mask_support": MASK_SUPPORT_MAP[v["mask_support"]]
        }

    # Resolve scalar_implems
    scalar_implems = {}
    for k, v in raw_scalar_implems.items():
        scalar_implems[k] = []
        for item in v:
            implem_val = item["implem"]
            if isinstance(implem_val, list):
                implem_val = "\n".join(implem_val)
                # Keep leading and trailing newlines like original code
                implem_val = "\n" + implem_val + "\n"
            scalar_implems[k].append({
                "type": item["type"],
                "datatypes": resolve_datatypes(item["datatypes"]),
                "mask_variants": item["mask_variants"],
                "implem": implem_val
            })

    return protos, categories, interfaces, scalar_implems

generic_flat_implems = None
generic_data_templates = None

def _load_generic_emu():
    global generic_flat_implems, generic_data_templates
    current_dir = os.path.dirname(os.path.abspath(__file__))

    # Load templates
    templates_path = os.path.join(current_dir, "generic_emu_templates.json")
    templates_lmulh_path = os.path.join(current_dir, "generic_emu_templates_lmulh.json")
    templates_mask_path = os.path.join(current_dir, "generic_emu_templates_mask.json")
    
    with open(templates_path, "r") as f:
        tpl_std = json.load(f)
    with open(templates_lmulh_path, "r") as f:
        tpl_lmulh = json.load(f)
    with open(templates_mask_path, "r") as f:
        tpl_mask = json.load(f)
        
    data_templates = {
        "tpl_generic_emu": tpl_std,
        "tpl_horiz_lmul_generic_emu": tpl_lmulh,
        "tpl_mask_generic_emu": tpl_mask
    }

    # Load implementations
    implems_path = os.path.join(current_dir, "generic_emu_implems.json")
    implems_lmulh_path = os.path.join(current_dir, "generic_emu_implems_lmulh.json")
    implems_mask_path = os.path.join(current_dir, "generic_emu_implems_mask.json")
    
    with open(implems_path, "r") as f:
        impl_std = json.load(f)
    with open(implems_lmulh_path, "r") as f:
        impl_lmulh = json.load(f)
    with open(implems_mask_path, "r") as f:
        impl_mask = json.load(f)
        
    data_implems = {
        "implems_generic_emu": impl_std,
        "implems_mask_generic_emu": impl_mask,
        "implems_horiz_lmul_generic_emu": impl_lmulh
    }

    from input_validation import (
        validate_templates_config, validate_implems_config, validate_template_references,
        audit_generic_templates_dead_code
    )
    # Validate each loaded split file
    validate_templates_config(tpl_std, templates_path)
    validate_templates_config(tpl_lmulh, templates_lmulh_path)
    validate_templates_config(tpl_mask, templates_mask_path)
    validate_implems_config(impl_std, implems_path)
    validate_implems_config(impl_lmulh, implems_lmulh_path)
    validate_implems_config(impl_mask, implems_mask_path)
    
    # Verify template references across section tables
    flat_implems = {}
    for sect in ["implems_generic_emu", "implems_mask_generic_emu", "implems_horiz_lmul_generic_emu"]:
        for name, items in data_implems[sect].items():
            if name not in flat_implems:
                flat_implems[name] = []
            flat_implems[name].extend(items)
            
    validate_template_references(flat_implems, data_templates, implems_path)
    generic_flat_implems = flat_implems
    generic_data_templates = data_templates
    audit_generic_templates_dead_code(flat_implems, data_templates)

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
        for name, tpl in data_templates[section].items():
            templates_pool[f"{section}.{name}"] = tpl

    def process_table(raw_table, default_type=None, default_level=None):
        processed = {}
        for func_name, items in raw_table.items():
            processed[func_name] = []
            for item in items:
                processed_item = {
                    "instr_name": item.get("instr_name", func_name),
                    "datatypes": resolve_datatypes(item["datatypes"])
                }
                for k, v in item.items():
                    if k not in ["instr_name", "datatypes", "template", "template_ref"]:
                        processed_item[k] = v
                
                # Resolve template
                template_code = ""
                if "template_ref" in item:
                    ref = item["template_ref"]
                    if ref in templates_pool:
                        processed_item["template"] = clean_template_code(templates_pool[ref])
                    else:
                        raise ValueError(f"Template reference not found: {ref}")
                elif "template" in item:
                    processed_item["template"] = clean_template_code(item["template"])

                # Auto-resolve dependencies from template placeholders
                auto_deps = set()
                if "template" in processed_item:
                    tpl = processed_item["template"]
                    if isinstance(tpl, dict):
                        code_val = tpl.get("code", "")
                        if isinstance(code_val, list):
                            template_code = "\n".join(code_val)
                        else:
                            template_code = str(code_val)
                    elif isinstance(tpl, str):
                        template_code = tpl

                if template_code:
                    import re
                    placeholder_regex = re.compile(r'\%([^%\n]*)\%')
                    matches = placeholder_regex.findall(template_code)
                    for m in matches:
                        m_clean = m.strip()
                        if m_clean and not m_clean.startswith("{") and not m_clean.endswith("}"):
                            dep_name = m_clean.split('<')[0].strip()
                            if dep_name:
                                first_word = dep_name.split()[0]
                                if first_word not in ["if", "else", "endif", "for", "endfor"]:
                                    if dep_name not in ["r", "m", "v", "N"] and not dep_name.startswith("{"):
                                        if dep_name != func_name:
                                            auto_deps.add(dep_name)
                                            
                processed_item["dependencies"] = auto_deps
                
                # Set default type/level
                if "type" not in processed_item:
                    if default_type is not None:
                        processed_item["type"] = default_type
                if default_level is not None:
                    processed_item["level"] = default_level
                    
                processed[func_name].append(processed_item)
        return processed

    implems_generic_emu = process_table(data_implems["implems_generic_emu"], default_type="emulated", default_level=2)
    implems_mask_generic_emu = process_table(data_implems["implems_mask_generic_emu"], default_type="emulated", default_level=2)
    implems_horiz_lmul_generic_emu = process_table(data_implems["implems_horiz_lmul_generic_emu"], default_level=2)
    
    return implems_generic_emu, implems_mask_generic_emu, implems_horiz_lmul_generic_emu

# Initialize globals dynamically
protos, categories, interfaces, scalar_implems = _load_funcs_registry()
copy_interfaces = copy.deepcopy(interfaces)

_current_dir = os.path.dirname(os.path.abspath(__file__))
with open(os.path.join(_current_dir, "registry_scalar_isa.json"), "r") as f:
    scalar_isa = json.load(f)
from input_validation import validate_isa_config
validate_isa_config(scalar_isa, "scalar")

implems_generic_emu, implems_mask_generic_emu, implems_horiz_lmul_generic_emu = _load_generic_emu()
