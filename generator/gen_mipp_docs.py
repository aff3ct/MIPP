#!/usr/bin/env python3
"""
MIPP Documentation Generator (gen_mipp_docs.py)
Generates Markdown reference pages for MIPP functions and ISA capability matrices.
"""
import sys
import os
import shutil
import json

path = os.getcwd()
sys.path.insert(1, os.path.join(path, "helpers_headers"))
sys.path.insert(1, os.path.join(path, "simd_ext", "scalar"))

from tools import (
    load_isa_config,
    all_datatypes,
    all_datatypes_cart_prod,
)
from registry import (
    interfaces,
    categories,
    scalar_isa,
    scalar_implems,
    implems_generic_emu,
    implems_mask_generic_emu,
)
from scalar_gen import gen_c_functions_scalar_one

# Load Centralized Function Documentation Metadata
funcs_docs_path = os.path.join(path, "helpers_headers", "funcs_docs.json")
if os.path.exists(funcs_docs_path):
    with open(funcs_docs_path, "r", encoding="utf-8") as f:
        funcs_docs = json.load(f)
else:
    funcs_docs = {}

# Load Centralized Test Specifications
tests_specs_path = os.path.join(path, "helpers_tests", "tests_specs.json")
if os.path.exists(tests_specs_path):
    with open(tests_specs_path, "r", encoding="utf-8") as f:
        tests_specs_data = json.load(f)
else:
    tests_specs_data = {}

dict_datatypes_short = {
    "int8": "i8",
    "int16": "i16",
    "int32": "i32",
    "int64": "i64",
    "uint8": "u8",
    "uint16": "u16",
    "uint32": "u32",
    "uint64": "u64",
    "float32": "f32",
    "float64": "f64",
}

all_datatypes_short = [dict_datatypes_short[dt] for dt in all_datatypes]
all_datatypes_short_cart_prod = []
for dt1 in all_datatypes:
    for dt2 in all_datatypes:
        all_datatypes_short_cart_prod.append(f"{dict_datatypes_short[dt1]},{dict_datatypes_short[dt2]}")

if_ignored_set = {"MIPP_ALIGNED_LOADS"}


def element_in_str(s_set, s_str):
    for element in s_set:
        if element in s_str:
            return True
    for element in if_ignored_set:
        if element in s_str:
            return True
    return False


# ---------------------------------------------------------------------------
# ISA Capability Tracking
# ---------------------------------------------------------------------------

class FuncInfo:
    def __init__(self):
        self.func_name = None
        self.datatypes = []
        self.emulated = {}
        self.generic = {}
        self.mask_kind = {}
        self.mask_emulated = {"mask": {}, "maskz": {}, "masks": {}}
        self.mask_generic = {"mask": {}, "maskz": {}, "masks": {}}

    def gen_infos(self, func, implems_isa, implems_emu_isa, defines):
        self.func_name = func
        if func in implems_isa:
            for implem in implems_isa[func]:
                mask_kind = implem.get("version", "unmasked")
                if mask_kind != "unmasked":
                    for dt in implem["datatypes"]:
                        if dt not in self.mask_kind:
                            self.mask_kind[dt] = []
                        self.mask_kind[dt].append(mask_kind)
                        self.mask_emulated[mask_kind][dt] = False
                        self.mask_generic[mask_kind][dt] = False
                    continue

                if "if" in implem:
                    if element_in_str(defines, implem["if"]):
                        self.add_datatypes(implem["datatypes"], False, False)
                else:
                    self.add_datatypes(implem["datatypes"], False, False)

        if func in implems_emu_isa:
            for implem in implems_emu_isa[func]:
                mask_kind = implem.get("version", "unmasked")
                if mask_kind != "unmasked":
                    for dt in implem["datatypes"]:
                        if dt not in self.mask_kind:
                            self.mask_kind[dt] = []
                        self.mask_kind[dt].append(mask_kind)
                        self.mask_emulated[mask_kind][dt] = True
                        self.mask_generic[mask_kind][dt] = False
                    continue

                if "if" in implem:
                    if element_in_str(defines, implem["if"]):
                        self.add_datatypes(implem["datatypes"], True, False)
                else:
                    self.add_datatypes(implem["datatypes"], True, False)

        if func in implems_generic_emu:
            for implem in implems_generic_emu[func]:
                self.add_datatypes(implem["datatypes"], False, True)

        if func in implems_mask_generic_emu:
            for implem in implems_mask_generic_emu[func]:
                mask_kind = implem.get("version", "unmasked")
                if mask_kind == "unmasked":
                    continue
                for dt in implem["datatypes"]:
                    if dt not in self.mask_kind:
                        self.mask_kind[dt] = []
                    if mask_kind not in self.mask_kind[dt]:
                        self.mask_kind[dt].append(mask_kind)
                        self.mask_emulated[mask_kind][dt] = False
                        self.mask_generic[mask_kind][dt] = True

    def is_generic(self, dttype):
        return self.generic.get(dttype, False)

    def is_emulated(self, dttype):
        return self.emulated.get(dttype, False)

    def is_native(self, dttype):
        return not self.is_emulated(dttype) and not self.is_generic(dttype)

    def is_generic_mkind(self, dttype, mkind):
        if self.mask_generic.get(mkind, {}).get(dttype, False):
            if dttype in self.mask_kind and mkind in self.mask_kind[dttype]:
                return True
        return False

    def is_emulated_mkind(self, dttype, mkind):
        if self.mask_emulated.get(mkind, {}).get(dttype, False):
            if dttype in self.mask_kind and mkind in self.mask_kind[dttype]:
                return True
        return False

    def is_def_mkind(self, dttype, mkind):
        return dttype in self.mask_kind and mkind in self.mask_kind[dttype]

    def add_datatypes(self, datatypes, emulated=False, generic=False):
        for dt in datatypes:
            if dt in self.datatypes:
                continue
            self.datatypes.append(dt)
            if emulated:
                self.emulated[dt] = True
            if generic:
                self.generic[dt] = True

    def is_supported_dt(self, dttype):
        return dttype in self.datatypes

    def get_mask_kinds(self, dttype):
        return self.mask_kind.get(dttype, [])


class IsaInfo:
    def __init__(self, isa_name):
        self.isa_name = isa_name
        self.func_infos = []

    def gen_isa_info(self, interfaces, implems, implems_emu, defines):
        for func in interfaces:
            func_info = FuncInfo()
            func_info.gen_infos(func, implems, implems_emu, defines)
            self.func_infos.append(func_info)

    def get_func_info(self, func_name):
        for func_info in self.func_infos:
            if func_info.func_name == func_name:
                return func_info
        return None


class MippInfo:
    def __init__(self):
        self.isa_infos = []

    def gen_mipp_infos(self, interfaces, isas_map):
        for isa_name, conf in isas_map.items():
            isa_info = IsaInfo(isa_name)
            native_implems = conf["implems"][0] if conf["implems"][0] is not None else {}
            emu_implems = conf["implems"][1] if conf["implems"][1] is not None else {}
            defines = conf.get("defines", set())
            isa_info.gen_isa_info(interfaces, native_implems, emu_implems, defines)
            self.isa_infos.append(isa_info)

    def get_intersection(self):
        intersection = IsaInfo("intersection")
        for func in interfaces:
            func_info = FuncInfo()
            func_info.func_name = func
            for dtype in interfaces[func]["datatypes"]:
                if all(
                    isa_info.get_func_info(func) is not None
                    and isa_info.get_func_info(func).is_supported_dt(dtype)
                    for isa_info in self.isa_infos
                ):
                    func_info.datatypes.append(dtype)
                    if any(
                        isa_info.get_func_info(func).is_generic(dtype)
                        for isa_info in self.isa_infos
                    ):
                        func_info.generic[dtype] = True
                    elif any(
                        isa_info.get_func_info(func).is_emulated(dtype)
                        for isa_info in self.isa_infos
                    ):
                        func_info.emulated[dtype] = True
            intersection.func_infos.append(func_info)
        return intersection


# ---------------------------------------------------------------------------
# ISA Support Matrix Writers
# ---------------------------------------------------------------------------

badge_l0 = '<span style="color: #28A745; font-weight: 600;">:fontawesome-solid-0:</span>'
badge_l1 = '<span style="color: #3B42F5; font-weight: 600;">:fontawesome-solid-1:</span>'
badge_l2 = '<span style="color: #FFD20D; font-weight: 600;">:fontawesome-solid-2:</span>'
badge_l3 = '<span style="color: #6C757D; font-weight: 600;">:fontawesome-solid-3:</span>'
badge_na = '<span style="color: #6C757D; font-weight: 600;">:material-minus:</span>'

def write_mipp_infos(mipp_infos, base_dir):
    for isa_info in mipp_infos.isa_infos:
        file_path = os.path.join(base_dir, f"{isa_info.isa_name}.md")
        with open(file_path, "w", encoding="utf-8") as f:
            for category, funcs in categories.items():
                dttypes = all_datatypes
                print(f"\n## {category}\n", file=f)
                print("| Function | " + " | ".join(all_datatypes_short) + " |", file=f)
                print("| :--- | " + " | ".join([":---:"] * len(dttypes)) + " |", file=f)
                for func in funcs:
                    if func in ("cast", "cast_k"):
                        continue
                    func_info = isa_info.get_func_info(func)
                    if func_info is not None:
                        line = f"| [{func}](../funcs_support/{category}/{func}.md) | "
                        for dtype in dttypes:
                            dtype_check = f"{dtype},{dtype}" if func in ("gather", "scatter") else dtype
                            if dtype_check in func_info.datatypes:
                                if func_info.is_generic(dtype_check):
                                    line += f"{badge_l2} | "
                                elif func_info.is_emulated(dtype_check):
                                    line += f"{badge_l1} | "
                                else:
                                    line += f"{badge_l0} | "
                            elif dtype_check in interfaces[func]["datatypes"]:
                                line += f"{badge_l3} | "
                            else:
                                line += f"{badge_na} | "
                        print(line, file=f)
                    else:
                        line = f"| [{func}](../funcs_support/{category}/{func}.md) | "
                        for dtype in dttypes:
                            dtype_check = f"{dtype},{dtype}" if func in ("gather", "scatter") else dtype
                            if dtype_check in interfaces[func]["datatypes"]:
                                line += f"{badge_l3} | "
                            else:
                                line += f"{badge_na} | "
                        print(line, file=f)

            # Cartesian product table for cast and cast_k
            dttypes_cart = all_datatypes_cart_prod
            print("\n## Type Reinterpretations (`cast` & `cast_k`)\n", file=f)
            print("| Function | " + " | ".join(all_datatypes_short_cart_prod) + " |", file=f)
            print("| :--- | " + " | ".join([":---:"] * len(dttypes_cart)) + " |", file=f)
            for func in ["cast", "cast_k"]:
                func_info = isa_info.get_func_info(func)
                if func_info is not None:
                    line = f"| [{func}](../funcs_support/reinterpret/{func}.md) | "
                    for dtype in dttypes_cart:
                        if dtype in func_info.datatypes:
                            if func_info.is_generic(dtype):
                                line += f"{badge_l2} | "
                            elif func_info.is_emulated(dtype):
                                line += f"{badge_l1} | "
                            else:
                                line += f"{badge_l0} | "
                        elif dtype in interfaces[func]["datatypes"]:
                            line += f"{badge_l3} | "
                        else:
                            line += f"{badge_na} | "
                    print(line, file=f)


def exists_msk_in_category(category, mkind):
    for func in categories[category]:
        if func in interfaces and "mask_support" in interfaces[func]:
            if interfaces[func]["mask_support"].is_supported(mkind):
                return True
    return False


def exists_msk_in_func(func, mkind):
    if func in interfaces and "mask_support" in interfaces[func]:
        return interfaces[func]["mask_support"].is_supported(mkind)
    return False


def write_mipp_infos_masked(mipp_infos, base_dir):
    for isa_info in mipp_infos.isa_infos:
        file_path = os.path.join(base_dir, f"{isa_info.isa_name}_masked.md")
        with open(file_path, "w", encoding="utf-8") as f:
            dttypes = all_datatypes
            for mkind in ["mask", "maskz", "masks"]:
                print(f"\n## Variant: `{mkind}`\n", file=f)
                for category, funcs in categories.items():
                    if not exists_msk_in_category(category, mkind):
                        continue
                    print(f"\n### {category}\n", file=f)
                    print("| Function | " + " | ".join(all_datatypes_short) + " |", file=f)
                    print("| :--- | " + " | ".join([":---:"] * len(dttypes)) + " |", file=f)
                    for func in funcs:
                        if not exists_msk_in_func(func, mkind) or func in ("cast", "cast_k"):
                            continue
                        func_info = isa_info.get_func_info(func)
                        if func_info is not None:
                            line = f"| [{func}](../funcs_support/{category}/{func}.md) | "
                            for dtype in dttypes:
                                dtype_check = f"{dtype},{dtype}" if func in ("gather", "scatter") else dtype
                                if dtype_check in func_info.datatypes and func_info.is_def_mkind(dtype_check, mkind):
                                    if func_info.is_generic_mkind(dtype_check, mkind):
                                        line += f"{badge_l2} | "
                                    elif func_info.is_emulated_mkind(dtype_check, mkind):
                                        line += f"{badge_l1} | "
                                    else:
                                        line += f"{badge_l0} | "
                                elif dtype_check in interfaces[func]["datatypes"] and interfaces[func]["mask_support"].is_supported(mkind):
                                    line += f"{badge_l3} | "
                                else:
                                    line += f"{badge_na} | "
                            print(line, file=f)


# ---------------------------------------------------------------------------
# Function Prototype Formatter & Spec Writer
# ---------------------------------------------------------------------------

def match_args_type_cpp(arg_type, cast=False, ret=False, fixed_dtype=False, lmul=1):
    lmul_str = "" if lmul == 1 else (f",{lmul}" if lmul > 0 else f",-2")
    if arg_type == "msk":
        t_param = "T2" if (cast and ret) else ("T1" if cast else "T")
        return f"rvm<{t_param}{lmul_str}>"
    elif arg_type == "reg":
        t_param = "T2" if (cast and ret) else ("T1" if cast else "T")
        return f"rvd<{t_param}{lmul_str}>"
    elif arg_type == "val":
        return f"{fixed_dtype}_t" if fixed_dtype else "T"
    elif arg_type == "ptr":
        return f"const {fixed_dtype}_t*" if fixed_dtype else "const T*"
    elif arg_type == "Nele":
        return f"const {fixed_dtype}_t[]" if fixed_dtype else "const T[]"
    return "int32_t"


def match_args_type_c(arg_type, cast=False, ret=False, fixed_dtype=False):
    if arg_type == "msk":
        return "rvm_{type 2}_t" if (cast and ret) else ("rvm_{type 1}_t" if cast else "rvm_{type}_t")
    elif arg_type == "reg":
        return "rvd_{type 2}_t" if (cast and ret) else ("rvd_{type 1}_t" if cast else "rvd_{type}_t")
    elif arg_type == "val":
        return f"{fixed_dtype}_t" if fixed_dtype else "{type}_t"
    elif arg_type == "ptr":
        return f"const {fixed_dtype}_t*" if fixed_dtype else "const {type}_t*"
    elif arg_type == "Nele":
        return f"const {fixed_dtype}_t[]" if fixed_dtype else "const {type}_t[]"
    return "int32_t"


class SpecFuncInfo:
    def __init__(self):
        self.func_name = None
        self.args = []
        self.ret = None
        self.dttypes = []
        self.mask_support = None
        self.category = "miscellaneous"

    def gen_spec_func_info(self, func, interfaces, categories):
        self.func_name = func
        self.args = interfaces[func]["proto"]["args"]
        self.ret = interfaces[func]["proto"]["ret"]
        self.dttypes = interfaces[func]["datatypes"]
        self.mask_support = interfaces[func].get("mask_support", None)

        for category, funcs in categories.items():
            if func in funcs:
                self.category = category
                break

    def get_cpp_func_name(self):
        has_reg_or_msk_arg = any(arg["type"] in ("reg", "msk") for arg in self.args)
        if has_reg_or_msk_arg and self.func_name.endswith("_k"):
            return self.func_name[:-2]
        return self.func_name

    def func_to_str_cpp(self, lmul=1):
        cpp_name = self.get_cpp_func_name()
        cast = self.func_name in ("cast", "cast_k")
        fixed_dtypes = [arg.get("fixeddatatype", False) for arg in self.args]
        args_str = ", ".join(
            [match_args_type_cpp(arg["type"], cast, False, fixed, lmul=lmul) for arg, fixed in zip(self.args, fixed_dtypes)]
        )

        ret_fixed = self.ret.get("fixeddatatype", False)
        ret_str = match_args_type_cpp(self.ret["type"], cast, True, ret_fixed, lmul=lmul)
        if cast:
            lmul_tmpl = f"<typename T2, typename T1, int LMUL={lmul}> " if lmul != 1 else "<typename T2, typename T1> "
        else:
            lmul_tmpl = f"<typename T, int LMUL={lmul}> " if lmul != 1 else "<typename T> "
        return f"template {lmul_tmpl}inline {ret_str} {cpp_name}({args_str});"

    def func_to_str_c(self, lmul=1):
        lmul_str = "" if lmul == 1 else (f"_m{lmul}" if lmul > 0 else "_d2")
        cast = self.func_name in ("cast", "cast_k")
        fixed_dtypes = [arg.get("fixeddatatype", False) for arg in self.args]
        args_str = ", ".join(
            [match_args_type_c(arg["type"], cast, False, fixed) for arg, fixed in zip(self.args, fixed_dtypes)]
        )

        ret_fixed = self.ret.get("fixeddatatype", False)
        ret_str = match_args_type_c(self.ret["type"], cast, True, ret_fixed)

        if cast:
            func_proto_str = f"inline {ret_str} mipp_{self.func_name}_{{type 1}}_{{type 2}}{lmul_str}({args_str});"
        else:
            func_proto_str = f"inline {ret_str} mipp_{self.func_name}_{{type}}{lmul_str}({args_str});"

        lines = []
        for dt in self.dttypes:
            if cast:
                parts = dt.split(",")
                lines.append(func_proto_str.replace("{type 1}", parts[0]).replace("{type 2}", parts[1]))
            else:
                lines.append(func_proto_str.format(type=dt))
        return "\n".join(lines)

    def write_func_algo(self, file):
        if self.func_name not in scalar_implems:
            return
        isa = scalar_isa
        funcs = interfaces
        f = self.func_name
        ff = scalar_implems[self.func_name][0]
        datatypes = ff["datatypes"] if ff.get("datatypes") else funcs[f]["datatypes"]
        dt = datatypes[0]

        print("```c", file=file)
        gen_c_functions_scalar_one(isa, file, funcs, f, ff, dt, lmul=0)
        print("```\n", file=file)

    def write_spec_func_info(self, base_dir, mipp_infos=None):
        file_path = os.path.join(base_dir, self.category, f"{self.func_name}.md")
        os.makedirs(os.path.dirname(file_path), exist_ok=True)

        doc_entry = funcs_docs.get(self.func_name, {})
        description = doc_entry.get("description", "Function reference documentation.")
        latex = doc_entry.get("latex", None)

        with open(file_path, "w", encoding="utf-8") as f:
            print(f"# `{self.func_name}`\n", file=f)
            print("## Description\n", file=f)
            print(f"{description}\n", file=f)

            if latex:
                print(f"$$\n{latex}\n$$\n", file=f)

            print("## Prototypes\n", file=f)
            print('=== "C++ API"', file=f)
            print("    ```cpp", file=f)
            for lmul in [1, 2, 4, 8, -2]:
                lmul_label = f"LMUL = {lmul}" if lmul > 0 else "LMUL = 1/2"
                print(f"    // {lmul_label}", file=f)
                print(f"    {self.func_to_str_cpp(lmul)}", file=f)
            print("    ```\n", file=f)

            print('=== "C99 API"', file=f)
            print("    ```c", file=f)
            for lmul in [1, 2, 4, 8, -2]:
                lmul_label = f"LMUL = {lmul}" if lmul > 0 else "LMUL = 1/2"
                print(f"    // {lmul_label}", file=f)
                c_block = self.func_to_str_c(lmul)
                for line in c_block.splitlines():
                    print(f"    {line}", file=f)
            print("    ```\n", file=f)

            print("## Supported Datatypes\n", file=f)
            if self.func_name in ("cast", "cast_k"):
                print("Supported between all pairwise datatype permutations of matching bitwidth.\n", file=f)
            else:
                for dtype in self.dttypes:
                    print(f"- `{dtype}`", file=f)
                print("", file=f)

            if self.mask_support and self.mask_support.is_any_mask():
                print("## Mask Execution Variants\n", file=f)
                variants = []
                if self.mask_support.is_maskable():
                    variants.append("- **Masked (`_mask` / `<mipp::M>`)**: Active elements evaluated; inactive elements preserve existing destination values.")
                if self.mask_support.is_maskzable():
                    variants.append("- **Zero-Masked (`_maskz` / `<mipp::Z>`)**: Active elements evaluated; inactive elements zeroed.")
                if self.mask_support.is_masksable():
                    variants.append("- **Source-Masked (`_masks` / `<mipp::S>`)**: Active elements evaluated; inactive elements take values from source operand `src`.")
                print("\n".join(variants) + "\n", file=f)

            if mipp_infos is not None:
                self.write_isa_matrix(f, mipp_infos)

            print("## Reference Algorithm\n", file=f)
            print("> [!NOTE]\n> The scalar reference implementation below demonstrates exact mathematical semantics across datatypes and masking modes.\n", file=f)
            self.write_func_algo(f)

            self.write_test_specs(f)

    def write_isa_matrix(self, file, mipp_infos):
        print("## Architecture & Implementation Matrix\n", file=file)
        
        is_cast = self.func_name in ("cast", "cast_k")
        dts = all_datatypes_cart_prod if is_cast else all_datatypes
        dts_headers = all_datatypes_short_cart_prod if is_cast else all_datatypes_short
        
        variants = [("Unmasked (`U`)", "unmasked")]
        if self.mask_support and self.mask_support.is_any_mask():
            if self.mask_support.is_maskable():
                variants.append(("Masked (`M`)", "mask"))
            if self.mask_support.is_maskzable():
                variants.append(("Zero-Masked (`Z`)", "maskz"))
            if self.mask_support.is_masksable():
                variants.append(("Source-Masked (`S`)", "masks"))
                
        for var_title, var_kind in variants:
            print(f'=== "{var_title}"', file=file)
            print("    | Architecture | " + " | ".join(dts_headers) + " |", file=file)
            print("    | :--- | " + " | ".join([":---:"] * len(dts)) + " |", file=file)
            
            for isa_info in mipp_infos.isa_infos:
                func_info = isa_info.get_func_info(self.func_name)
                row = f"    | **{isa_info.isa_name.upper()}** | "
                for dt in dts:
                    dtype_check = f"{dt},{dt}" if self.func_name in ("gather", "scatter") else dt
                    if var_kind == "unmasked":
                        if func_info and dtype_check in func_info.datatypes:
                            if func_info.is_generic(dtype_check):
                                row += f"{badge_l2} | "
                            elif func_info.is_emulated(dtype_check):
                                row += f"{badge_l1} | "
                            else:
                                row += f"{badge_l0} | "
                        elif dtype_check in interfaces[self.func_name]["datatypes"]:
                            row += f"{badge_l3} | "
                        else:
                            row += f"{badge_na} | "
                    else:
                        if func_info and dtype_check in func_info.datatypes and func_info.is_def_mkind(dtype_check, var_kind):
                            if func_info.is_generic_mkind(dtype_check, var_kind):
                                row += f"{badge_l2} | "
                            elif func_info.is_emulated_mkind(dtype_check, var_kind):
                                row += f"{badge_l1} | "
                            else:
                                row += f"{badge_l0} | "
                        elif dtype_check in interfaces[self.func_name]["datatypes"] and interfaces[self.func_name]["mask_support"].is_supported(var_kind):
                            row += f"{badge_l3} | "
                        else:
                            row += f"{badge_na} | "
                print(row, file=file)
            print("", file=file)

    def write_test_specs(self, file):
        spec = tests_specs_data.get("functions", {}).get(self.func_name, {})
        default_spec = tests_specs_data.get("default", {})
        
        comp = spec.get("comparison", default_spec.get("comparison", "exact"))
        domain = spec.get("domain", default_spec.get("domain", {}))
        tolerance = spec.get("tolerance", default_spec.get("tolerance", {"type": "exact"}))
        overflow_check = spec.get("overflow_check", default_spec.get("overflow_check", None))
        nan_inf_skip = spec.get("nan_inf_skip", default_spec.get("nan_inf_skip", False))
        mask_pattern = spec.get("mask_pattern", default_spec.get("mask_pattern", "uniform_bool"))
        
        print("## Test & Verification Specifications\n", file=file)
        
        # 1. Input Domain
        print("### Test Domain & Input Range\n", file=file)
        if "min" in domain and "max" in domain:
            print(f"- **Input Range**: $[{domain['min']}, {domain['max']}]$", file=file)
        elif "by_datatype" in domain:
            print("- **Input Ranges by Datatype**:", file=file)
            for dt, d_val in domain["by_datatype"].items():
                if "min" in d_val and "max" in d_val:
                    print(f"  - `{dt}`: $[{d_val['min']}, {d_val['max']}]$", file=file)
                elif "values" in d_val:
                    vals_str = ", ".join(map(str, d_val["values"]))
                    print(f"  - `{dt}`: Discrete set $\\{{{vals_str}\\}}$", file=file)
        elif "by_variable" in domain:
            print("- **Input Ranges by Operand**:", file=file)
            for var, d_val in domain["by_variable"].items():
                if "min" in d_val and "max" in d_val:
                    print(f"  - `{var}`: $[{d_val['min']}, {d_val['max']}]$", file=file)
        else:
            print("- **Input Range**: Full representable range of the target datatype.", file=file)
            
        print(f"- **Mask Test Pattern**: `{mask_pattern}`", file=file)
        if overflow_check:
            print(f"- **Integer Overflow Handling**: Monitored (`{overflow_check}` overflow check enabled).", file=file)
        if nan_inf_skip:
            print("- **Special Values**: Skips NaN and Inf inputs during verification.", file=file)
        print("", file=file)

        # 2. Precision & Verification Tolerances
        print("### Verification Tolerance\n", file=file)
        if self.func_name in ("cast", "cast_k"):
            print("| Datatype Pairs | Comparison Mode | Allowed Tolerance |", file=file)
            print("| :--- | :--- | :--- |", file=file)
            print(f"| All bitwidth-matching pairs | `{comp}` | Bit-exact ($0$ error) |\n", file=file)
            return

        print("| Datatype | Comparison Mode | Allowed Tolerance |", file=file)
        print("| :--- | :--- | :--- |", file=file)
        
        if "by_datatype" in tolerance:
            for dt in self.dttypes:
                if dt in tolerance["by_datatype"]:
                    t_info = tolerance["by_datatype"][dt]
                    t_type = t_info.get("type", "max_abs_diff")
                    t_val = t_info.get("value", 0)
                    t_type_str = "Max Absolute Difference" if t_type == "max_abs_diff" else t_type.upper()
                    print(f"| `{dt}` | `{comp}` | $\\le {t_val}$ ({t_type_str}) |", file=file)
                else:
                    print(f"| `{dt}` | `exact` | Bit-exact ($0$ error) |", file=file)
        elif tolerance.get("type") == "ulp":
            ulp_val = tolerance.get("value", 1)
            for dt in self.dttypes:
                if dt.startswith("float"):
                    print(f"| `{dt}` | `{comp}` | $\\le {ulp_val}$ ULP |", file=file)
                else:
                    print(f"| `{dt}` | `exact` | Bit-exact ($0$ error) |", file=file)
        else:
            comp_desc = "Bit-exact ($0$ error)" if comp in ("exact", "bitwise") else ("Logical truthiness match" if comp == "logical" else "Exact")
            for dt in self.dttypes:
                print(f"| `{dt}` | `{comp}` | {comp_desc} |", file=file)
        print("", file=file)


class SpecFuncInfos:
    def __init__(self):
        self.spec_func_infos = []

    def gen_spec_func_infos(self, interfaces, categories):
        for func in interfaces:
            spec_func_info = SpecFuncInfo()
            spec_func_info.gen_spec_func_info(func, interfaces, categories)
            self.spec_func_infos.append(spec_func_info)

    def write_spec_func_infos(self, base_dir, mipp_infos=None):
        for spec_func_info in self.spec_func_infos:
            spec_func_info.write_spec_func_info(base_dir, mipp_infos=mipp_infos)


# ---------------------------------------------------------------------------
# Guide Pages Generator
# ---------------------------------------------------------------------------

def write_isas_support_index(base_dir):
    file_path = os.path.join(base_dir, "index.md")
    with open(file_path, "w", encoding="utf-8") as f:
        print("""# Target ISA Capability & Architecture Support Guide

MIPP provides high-performance SIMD/vector abstractions across a broad spectrum of hardware instruction set architectures (ISAs).

## Capability Matrix Legend

| Symbol | Support Level | Technical Meaning |
| :---: | :--- | :--- |
| <span style="color: #28A745; font-weight: 600;">:fontawesome-solid-0:</span> | **Level 0 (Native Hardware)** | Optimal 1:1 mapping to target hardware vector instruction(s). Zero runtime translation overhead. |
| <span style="color: #3B42F5; font-weight: 600;">:fontawesome-solid-1:</span> | **Level 1 (Dedicated Emulation)** | Hand-crafted sequence tailored specifically for this ISA to emulate missing hardware instructions efficiently. |
| <span style="color: #FFD20D; font-weight: 600;">:fontawesome-solid-2:</span> | **Level 2 (Generic Emulation)** | Synthesized cross-ISA AST emulation constructed from portable primitive operations (e.g. `cmpneq` + `blend`). |
| <span style="color: #6C757D; font-weight: 600;">:fontawesome-solid-3:</span> | **Level 3 (Scalar Fallback)** | Portable element-by-element scalar loop execution when vector hardware/emulation paths are absent. |
| <span style="color: #6C757D; font-weight: 600;">:material-minus:</span> | **Not Applicable** | Variant or datatype permutation is not part of the functional interface definition. |

## Masking Execution Modes

- **Unmasked (`U`)**: Evaluates the operation on all vector elements unconditionally.
- **Masked (`M`)**: Active elements ($m_i = 1$) are computed; inactive elements ($m_i = 0$) preserve their previous values in the destination register.
- **Zero-Masked (`Z`)**: Active elements ($m_i = 1$) are computed; inactive elements ($m_i = 0$) are zeroed.
- **Source-Masked (`S`)**: Active elements ($m_i = 1$) are computed; inactive elements ($m_i = 0$) take values from a fallback source operand `src`.

## Architecture Capability Matrices

### Unmasked Matrices
- [x86 SSE Family Support Matrix](sse.md)
- [ARM NEON Support Matrix](neon.md)
- [x86 AVX / AVX2 Support Matrix](avx.md)
- [x86 AVX-512 Support Matrix](avx512.md)
- [ARM SVE Support Matrix](sve.md)
- [RISC-V Vector (RVV 1.0) Support Matrix](rvv.md)
- [Common Portable Baseline (Intersection Matrix)](intersection.md)

### Masked Matrices
- [x86 SSE Masked Matrix](sse_masked.md)
- [ARM NEON Masked Matrix](neon_masked.md)
- [x86 AVX / AVX2 Masked Matrix](avx_masked.md)
- [x86 AVX-512 Masked Matrix](avx512_masked.md)
- [RISC-V Vector (RVV 1.0) Masked Matrix](rvv_masked.md)
""", file=f)


def write_funcs_support_index(base_dir, categories):
    file_path = os.path.join(base_dir, "index.md")
    with open(file_path, "w", encoding="utf-8") as f:
        print("""# MIPP Function Reference Guide

This reference directory catalogs all 85 vector functions provided by MIPP, categorized by operational domain.

## Function Reference Page Structure

Each function reference page provides:
1. **Description & Mathematical Formulation**: Behavior summary and formal LaTeX equation.
2. **Prototypes**: C++ template signatures (supporting LMUL vector length scaling) and C99 type-explicit prototypes.
3. **Supported Datatypes & Mask Execution Variants**: Supported element types and masking execution modes.
4. **ISA & Variant Support Matrix**: Per-architecture hardware capability breakdown across masking variants.
5. **Reference Algorithm**: Scalar C reference implementation demonstrating exact arithmetic and masking semantics.
6. **Test & Verification Specifications**: Input value domains, validity bounds, and precision tolerances.

## Function Directory by Category
""", file=f)
        for cat, funcs in categories.items():
            cat_title = cat.capitalize()
            print(f"### {cat_title}\n", file=f)
            for func in funcs:
                doc_entry = funcs_docs.get(func, {})
                desc = doc_entry.get("description", "Vector function reference.")
                print(f"- [`{func}`]({cat}/{func}.md): {desc}", file=f)
            print("", file=f)


# ---------------------------------------------------------------------------
# Main Execution Entrypoint
# ---------------------------------------------------------------------------

def main():
    base_generator_dir = os.path.dirname(os.path.abspath(__file__))
    project_root = os.path.dirname(base_generator_dir)

    print("[MIPP DocGen] Loading ISA configurations...")
    try:
        from gen_mipp_headers import discover_and_sort_isas
        isas_dict, implems_dict_raw, sorted_names = discover_and_sort_isas(base_generator_dir)
    except Exception:
        from tools import discover_and_sort_isas
        isas_dict, implems_dict_raw, sorted_names = discover_and_sort_isas(base_generator_dir)

    isas_map = {}
    for isa_name in sorted_names:
        if isa_name == "scalar":
            continue
        native_impl, emu_impl = implems_dict_raw[isa_name]
        isas_map[isa_name] = {
            "implems": [native_impl, emu_impl],
            "defines": set(),
        }

    if "sse" in isas_map:
        isas_map["sse"]["defines"] = {"SSE2", "SSE3", "SSSE3", "SSE4_1", "SSE4_2"}
    if "avx" in isas_map:
        isas_map["avx"]["defines"] = {"AVX2", "FMA"}
    if "avx512" in isas_map:
        isas_map["avx512"]["defines"] = {"AVX512BW", "AVX512F", "AVX512", "AVX512DQ"}
    if "neon" in isas_map:
        isas_map["neon"]["defines"] = {"__aarch64__"}

    print(f"[MIPP DocGen] Loaded {len(isas_map)} target ISAs: {', '.join(isas_map.keys())}")

    # Generate ISA Support Documentation
    isas_support_dir = os.path.join(project_root, "docs", "isas_support")
    if os.path.exists(isas_support_dir):
        shutil.rmtree(isas_support_dir)
    os.makedirs(isas_support_dir, exist_ok=True)

    mipp_infos = MippInfo()
    mipp_infos.gen_mipp_infos(interfaces, isas_map)

    print("[MIPP DocGen] Writing ISA capability matrices...")
    write_mipp_infos(mipp_infos, isas_support_dir)
    write_mipp_infos_masked(mipp_infos, isas_support_dir)

    # Generate Intersection Matrix
    intersection = mipp_infos.get_intersection()
    int_mipp_infos = MippInfo()
    int_mipp_infos.isa_infos.append(intersection)
    write_mipp_infos(int_mipp_infos, isas_support_dir)

    # Generate ISA Support Guide Landing Page
    write_isas_support_index(isas_support_dir)

    # Generate Function Support Documentation
    funcs_support_dir = os.path.join(project_root, "docs", "funcs_support")
    if os.path.exists(funcs_support_dir):
        shutil.rmtree(funcs_support_dir)
    os.makedirs(funcs_support_dir, exist_ok=True)

    print("[MIPP DocGen] Generating Function Reference Documentation pages...")
    spec_func_infos = SpecFuncInfos()
    spec_func_infos.gen_spec_func_infos(interfaces, categories)
    spec_func_infos.write_spec_func_infos(funcs_support_dir, mipp_infos=mipp_infos)

    # Generate Function Reference Guide Landing Page
    write_funcs_support_index(funcs_support_dir, categories)

    print("[MIPP DocGen] Complete! Documentation generated in docs/isas_support/ and docs/funcs_support/.")


if __name__ == "__main__":
    main()

