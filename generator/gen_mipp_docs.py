#!/usr/bin/env python3
"""
MIPP Documentation Generator (gen_mipp_docs.py)
Generates Markdown reference pages for MIPP functions and ISA capability matrices.
"""
import sys
import os
import shutil
import json
import copy

path = os.getcwd()
sys.path.insert(1, os.path.join(path, "helpers_headers"))
sys.path.insert(1, os.path.join(path, "simd_ext", "scalar"))

from tools import (
    load_isa_config,
    all_datatypes,
    all_datatypes_cart_prod,
    all_datatypes_same_size,
    all_datatypes_widenning,
    build_func_name,
    build_func_name_short,
    build_proto,
)
from registry import (
    interfaces,
    categories,
    scalar_isa,
    scalar_implems,
)
from gen_mipp_headers import discover_and_sort_isas
from c_generator import resolve_lmul_in_isa, register_all_candidates
from codegen.candidate_resolver import resolve_candidates
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

def pair_to_short(pair_str):
    src, dst = pair_str.split(",")
    return f"{dict_datatypes_short.get(src, src)}&rarr;{dict_datatypes_short.get(dst, dst)}"

all_datatypes_short_cart_prod = [pair_to_short(p) for p in all_datatypes_cart_prod]
all_datatypes_same_size_short = [pair_to_short(p) for p in all_datatypes_same_size]
all_datatypes_widenning_short = [pair_to_short(p) for p in all_datatypes_widenning]


# ---------------------------------------------------------------------------
# ISA Capability Tracking via Header Solver
# ---------------------------------------------------------------------------

class FuncInfo:
    def __init__(self, func_name=""):
        self.func_name = func_name
        self.levels = {}  # (dt_key, mask_kind) -> int (0, 1, 2, 3, 4)

    def get_level(self, dt, mask_kind=None):
        dt_par, dt_ret = dt.split(",") if "," in dt else (dt, dt)
        dt_key = f"{dt_par},{dt_ret}"
        return self.levels.get((dt_key, mask_kind), 3)

    def is_generic(self, dt):
        return self.get_level(dt, None) == 2

    def is_emulated(self, dt):
        return self.get_level(dt, None) == 1

    def is_native(self, dt):
        return self.get_level(dt, None) == 0

    def is_generic_mkind(self, dt, mkind):
        return self.get_level(dt, mkind) == 2

    def is_emulated_mkind(self, dt, mkind):
        return self.get_level(dt, mkind) == 1

    def is_native_mkind(self, dt, mkind):
        return self.get_level(dt, mkind) == 0

    def is_supported_dt(self, dt):
        return self.get_level(dt, None) <= 2

    def is_def_mkind(self, dt, mkind):
        return self.get_level(dt, mkind) <= 2


class IsaInfo:
    def __init__(self, isa_name):
        self.isa_name = isa_name
        self.func_infos = {}

    def get_func_info(self, func_name):
        return self.func_infos.get(func_name, None)


class MippInfo:
    def __init__(self):
        self.isa_infos = []

    def gen_mipp_infos(self, interfaces, isas_map):
        for isa_name, conf in isas_map.items():
            isa_info = IsaInfo(isa_name)
            isa_conf = conf["isa_conf"]
            native_impl, emu_impl = conf["implems"]

            resolved_isa = resolve_lmul_in_isa(isa_conf, "0")
            resolved_isa["candidates"] = []
            copy_interfaces = copy.deepcopy(interfaces)
            register_all_candidates(resolved_isa, copy_interfaces, native_impl, emu_impl, lmul=0)
            resolved_map = resolve_candidates(resolved_isa, copy_interfaces, lmul=0)

            for func in interfaces:
                f_info = FuncInfo(func)
                for dt in interfaces[func]["datatypes"]:
                    dt_par, dt_ret = dt.split(",") if "," in dt else (dt, dt)
                    dt_key = f"{dt_par},{dt_ret}"
                    mask_kinds = [None]
                    if "mask_support" in interfaces[func]:
                        support = interfaces[func]["mask_support"]
                        if support.is_maskable():
                            mask_kinds.append("mask")
                        if support.is_maskzable():
                            mask_kinds.append("maskz")
                        if support.is_masksable():
                            mask_kinds.append("masks")

                    for mkind in mask_kinds:
                        cands = resolved_map.get((func, dt_key, mkind), [])
                        active_levels = [cand["level"] for cand, cond in cands if cond != "0"]
                        lvl = min(active_levels, default=3)
                        f_info.levels[(dt_key, mkind)] = lvl
                isa_info.func_infos[func] = f_info
            self.isa_infos.append(isa_info)

    def get_intersection(self):
        intersection = IsaInfo("intersection")
        for func in interfaces:
            f_info = FuncInfo(func)
            for dt in interfaces[func]["datatypes"]:
                dt_par, dt_ret = dt.split(",") if "," in dt else (dt, dt)
                dt_key = f"{dt_par},{dt_ret}"
                mask_kinds = [None]
                if "mask_support" in interfaces[func]:
                    support = interfaces[func]["mask_support"]
                    if support.is_maskable():
                        mask_kinds.append("mask")
                    if support.is_maskzable():
                        mask_kinds.append("maskz")
                    if support.is_masksable():
                        mask_kinds.append("masks")

                for mkind in mask_kinds:
                    isa_levels = [
                        isa_info.get_func_info(func).get_level(dt, mkind)
                        for isa_info in self.isa_infos
                        if isa_info.get_func_info(func) is not None
                    ]
                    if isa_levels and all(lvl <= 2 for lvl in isa_levels):
                        if any(lvl == 2 for lvl in isa_levels):
                            f_info.levels[(dt_key, mkind)] = 2
                        elif any(lvl == 1 for lvl in isa_levels):
                            f_info.levels[(dt_key, mkind)] = 1
                        else:
                            f_info.levels[(dt_key, mkind)] = 0
                    else:
                        f_info.levels[(dt_key, mkind)] = 3
            intersection.func_infos[func] = f_info
        return intersection


# ---------------------------------------------------------------------------
# ISA Support Matrix Writers
# ---------------------------------------------------------------------------

badge_l0 = '<span style="color: #28A745; font-weight: 600;">:fontawesome-solid-0:</span>'
badge_l1 = '<span style="color: #3B42F5; font-weight: 600;">:fontawesome-solid-1:</span>'
badge_l2 = '<span style="color: #FFD20D; font-weight: 600;">:fontawesome-solid-2:</span>'
badge_l3 = '<span style="color: #6C757D; font-weight: 600;">:fontawesome-solid-3:</span>'
badge_na = '<span style="color: #6C757D; font-weight: 600;">:material-minus:</span>'

def level_to_badge(level):
    if level == 0:
        return badge_l0
    elif level == 1:
        return badge_l1
    elif level == 2:
        return badge_l2
    elif level == 3:
        return badge_l3
    else:
        return badge_na


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
                    if func in ("cast", "cast_k", "cvt", "wcvt"):
                        continue
                    func_info = isa_info.get_func_info(func)
                    line = f"| [{func}](../funcs_support/{category}/{func}.md) | "
                    for dtype in dttypes:
                        dtype_check = f"{dtype},{dtype}" if func in ("gather", "scatter") else dtype
                        if dtype_check in interfaces[func]["datatypes"]:
                            lvl = func_info.get_level(dtype_check, None) if func_info else 3
                            line += f"{level_to_badge(lvl)} | "
                        else:
                            line += f"{badge_na} | "
                    print(line, file=f)

            # Type Conversions (cvt)
            print("\n## Type Conversions (`cvt`)\n", file=f)
            print("| Function | " + " | ".join(all_datatypes_same_size_short) + " |", file=f)
            print("| :--- | " + " | ".join([":---:"] * len(all_datatypes_same_size)) + " |", file=f)
            func = "cvt"
            func_info = isa_info.get_func_info(func)
            line = f"| [{func}](../funcs_support/converts/{func}.md) | "
            for dtype in all_datatypes_same_size:
                if dtype in interfaces[func]["datatypes"]:
                    lvl = func_info.get_level(dtype, None) if func_info else 3
                    line += f"{level_to_badge(lvl)} | "
                else:
                    line += f"{badge_na} | "
            print(line, file=f)

            # Widening Conversions (wcvt)
            print("\n## Widening Conversions (`wcvt`)\n", file=f)
            print("| Function | " + " | ".join(all_datatypes_widenning_short) + " |", file=f)
            print("| :--- | " + " | ".join([":---:"] * len(all_datatypes_widenning)) + " |", file=f)
            func = "wcvt"
            func_info = isa_info.get_func_info(func)
            line = f"| [{func}](../funcs_support/converts/{func}.md) | "
            for dtype in all_datatypes_widenning:
                if dtype in interfaces[func]["datatypes"]:
                    lvl = func_info.get_level(dtype, None) if func_info else 3
                    line += f"{level_to_badge(lvl)} | "
                else:
                    line += f"{badge_na} | "
            print(line, file=f)

            # Cartesian product table for cast and cast_k
            print("\n## Type Reinterpretations (`cast` & `cast_k`)\n", file=f)
            print("| Function | " + " | ".join(all_datatypes_short_cart_prod) + " |", file=f)
            print("| :--- | " + " | ".join([":---:"] * len(all_datatypes_cart_prod)) + " |", file=f)
            for func in ["cast", "cast_k"]:
                func_info = isa_info.get_func_info(func)
                line = f"| [{func}](../funcs_support/reinterpret/{func}.md) | "
                for dtype in all_datatypes_cart_prod:
                    if dtype in interfaces[func]["datatypes"]:
                        lvl = func_info.get_level(dtype, None) if func_info else 3
                        line += f"{level_to_badge(lvl)} | "
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
                        if not exists_msk_in_func(func, mkind) or func in ("cast", "cast_k", "cvt", "wcvt"):
                            continue
                        func_info = isa_info.get_func_info(func)
                        line = f"| [{func}](../funcs_support/{category}/{func}.md) | "
                        for dtype in dttypes:
                            dtype_check = f"{dtype},{dtype}" if func in ("gather", "scatter") else dtype
                            if dtype_check in interfaces[func]["datatypes"] and interfaces[func]["mask_support"].is_supported(mkind):
                                lvl = func_info.get_level(dtype_check, mkind) if func_info else 3
                                line += f"{level_to_badge(lvl)} | "
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
        is_pair_func = self.func_name in ("cast", "cast_k", "cvt", "wcvt")
        if is_pair_func:
            lmul_tmpl = f"<typename T2, typename T1, int LMUL={lmul}> " if lmul != 1 else "<typename T2, typename T1> "
            lmul_arg = f",{lmul}" if lmul != 1 else ""
            type_name = "rvm" if self.func_name.endswith("_k") else "rvd"
            return f"template {lmul_tmpl}inline {type_name}<T2{lmul_arg}> {cpp_name}({type_name}<T1{lmul_arg}>);"

        fixed_dtypes = [arg.get("fixeddatatype", False) for arg in self.args]
        args_str = ", ".join(
            [match_args_type_cpp(arg["type"], False, False, fixed, lmul=lmul) for arg, fixed in zip(self.args, fixed_dtypes)]
        )
        ret_fixed = self.ret.get("fixeddatatype", False)
        ret_str = match_args_type_cpp(self.ret["type"], False, True, ret_fixed, lmul=lmul)
        lmul_tmpl = f"<typename T, int LMUL={lmul}> " if lmul != 1 else "<typename T> "
        return f"template {lmul_tmpl}inline {ret_str} {cpp_name}({args_str});"

    def func_to_str_c(self, lmul=1):
        is_pair_func = self.func_name in ("cast", "cast_k", "cvt", "wcvt")
        lines = []
        if is_pair_func:
            for dt in self.dttypes:
                dt_par, dt_ret = dt.split(",")
                full_func_name = build_func_name({}, dt_par, dt_ret, self.func_name, isa_name=False, lmul=lmul)
                proto = build_proto(interfaces[self.func_name]["proto"], dt_par, dt_ret, {}, full_func_name, lmul=lmul, isa_name=False)
                lines.append(proto + ";")
        else:
            for dt in self.dttypes:
                dt_single = dt.split(",")[0]
                full_func_name = build_func_name_short({}, dt_single, self.func_name, isa_name=False, lmul=lmul)
                proto = build_proto(interfaces[self.func_name]["proto"], dt_single, dt_single, {}, full_func_name, lmul=lmul, isa_name=False)
                lines.append(proto + ";")
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
        with open(file_path, "w", encoding="utf-8") as f:
            print(f"# `{self.func_name}`\n", file=f)
            
            doc_entry = funcs_docs.get(self.func_name, {})
            desc = doc_entry.get("description", "Vector function reference.")
            print(f"{desc}\n", file=f)

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
            elif self.func_name in ("cvt", "wcvt"):
                for dt in self.dttypes:
                    src, dst = dt.split(",")
                    print(f"- `{src}` &rarr; `{dst}`", file=f)
                print("", file=f)
            else:
                for dtype in self.dttypes:
                    dt_single = dtype.split(",")[0]
                    print(f"- `{dt_single}`", file=f)
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
        
        if self.func_name in ("cast", "cast_k"):
            dts = all_datatypes_cart_prod
            dts_headers = all_datatypes_short_cart_prod
        elif self.func_name == "cvt":
            dts = all_datatypes_same_size
            dts_headers = all_datatypes_same_size_short
        elif self.func_name == "wcvt":
            dts = all_datatypes_widenning
            dts_headers = all_datatypes_widenning_short
        else:
            dts = all_datatypes
            dts_headers = all_datatypes_short
        
        variants = [("Unmasked (`U`)", None)]
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
                    if dtype_check in interfaces[self.func_name]["datatypes"]:
                        if var_kind is None or (self.mask_support and self.mask_support.is_supported(var_kind)):
                            lvl = func_info.get_level(dtype_check, var_kind) if func_info else 3
                            row += f"{level_to_badge(lvl)} | "
                        else:
                            row += f"{badge_na} | "
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
        print("### Input Range\n", file=file)
        if "min" in domain and "max" in domain:
            print(f"- **Range**: $[{domain['min']}, {domain['max']}]$", file=file)
        elif "by_datatype" in domain:
            print("- **Ranges by Datatype**:", file=file)
            for dt, d_val in domain["by_datatype"].items():
                if "min" in d_val and "max" in d_val:
                    print(f"  - `{dt}`: $[{d_val['min']}, {d_val['max']}]$", file=file)
                elif "values" in d_val:
                    vals_str = ", ".join(map(str, d_val["values"]))
                    print(f"  - `{dt}`: Discrete set $\\{{{vals_str}\\}}$", file=file)
        elif "by_variable" in domain:
            print("- **Ranges by Operand**:", file=file)
            for var, d_val in domain["by_variable"].items():
                if "min" in d_val and "max" in d_val:
                    print(f"  - `{var}`: $[{d_val['min']}, {d_val['max']}]$", file=file)
        else:
            print("- **Range**: Full representable range of the target datatype.", file=file)
        print("", file=file)

        # 2. Precision & Verification Tolerances
        print("### Verification Tolerance\n", file=file)
        if self.func_name in ("cast", "cast_k", "cvt", "wcvt"):
            print("| Datatype Pairs | Comparison Mode | Allowed Tolerance |", file=file)
            print("| :--- | :--- | :--- |", file=file)
            print(f"| All supported conversion pairs | `{comp}` | Bit-exact ($0$ error) |\n", file=file)
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

## Implementation Levels & Acceleration Legend

MIPP functions are classified into 4 distinct implementation tiers:

| Badge | Implementation Level | Description |
| :---: | :--- | :--- |
| <span style="color: #28A745; font-weight: 600;">:fontawesome-solid-0:</span> | **Level 0 (Native Hardware)** | Direct 1:1 hardware intrinsic mapping with optimal throughput and latency. |
| <span style="color: #3B42F5; font-weight: 600;">:fontawesome-solid-1:</span> | **Level 1 (Dedicated Emulation)** | Architecture-specific vector sequence emulating missing hardware operations. |
| <span style="color: #FFD20D; font-weight: 600;">:fontawesome-solid-2:</span> | **Level 2 (Generic Emulation)** | Portable cross-ISA vector AST algorithm built from other MIPP operations. |
| <span style="color: #6C757D; font-weight: 600;">:fontawesome-solid-3:</span> | **Level 3 (Scalar Fallback)** | Element-by-element sequential loop fallback with maximum portability. |
| <span style="color: #6C757D; font-weight: 600;">:material-minus:</span> | **N/A (Not Applicable)** | Operation is not defined for this element datatype or masking variant. |

---

## Supported Target Architectures

### x86 / x86-64 Architectures
- [**SSE (Streaming SIMD Extensions)**](sse.md): 128-bit vector extensions (SSE2 through SSE4.2). ([Masked Variant Matrix](sse_masked.md))
- [**AVX (Advanced Vector Extensions)**](avx.md): 256-bit vector extensions (AVX, AVX2, FMA3). ([Masked Variant Matrix](avx_masked.md))
- [**AVX-512**](avx512.md): 512-bit vector extensions with native opmask registers ($k_0-k_7$). ([Masked Variant Matrix](avx512_masked.md))

### ARM Architectures
- [**ARM NEON**](neon.md): 128-bit fixed-length vector processing for ARMv7 and ARMv8/AArch64. ([Masked Variant Matrix](neon_masked.md))
- [**ARM SVE (Scalable Vector Extension)**](sve.md): Variable-length vector architecture with native predicate registers ($p_0-p_{15}$). ([Masked Variant Matrix](sve_masked.md))

### RISC-V Architectures
- [**RISC-V Vector (RVV 1.0)**](rvv.md): Variable-length vector extension with dynamic register grouping (LMUL) and active masking ($v_0$). ([Masked Variant Matrix](rvv_masked.md))

---

## Portability & Intersection Capabilities
- [**Universal Architecture Intersection Matrix**](intersection.md): Capabilities guaranteed to vectorize across **all** supported target ISAs.
""", file=f)


def write_funcs_support_index(base_dir, categories):
    file_path = os.path.join(base_dir, "index.md")
    with open(file_path, "w", encoding="utf-8") as f:
        print("""# Function Reference & Implementation Directory

This section contains complete API reference documentation, mathematical semantics, test specifications, and architecture acceleration matrices for all MIPP functions.

## Documentation Structure for Each Function

Each function reference page provides:
1. **Description & Semantics**: Mathematical operation and vector execution behavior.
2. **C++ & C99 Prototypes**: Complete templated C++ signatures and C99 function prototypes across all LMUL ratios.
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

    print("[MIPP DocGen] Discovering and sorting target ISAs...")
    isas_dict, implems_dict_raw, sorted_names = discover_and_sort_isas(base_generator_dir)

    isas_map = {}
    for isa_name in sorted_names:
        if isa_name == "scalar":
            continue
        native_impl, emu_impl = implems_dict_raw[isa_name]
        isas_map[isa_name] = {
            "isa_conf": isas_dict[isa_name],
            "implems": [native_impl, emu_impl],
        }

    print(f"[MIPP DocGen] Loaded {len(isas_map)} target ISAs: {', '.join(isas_map.keys())}")

    # Generate ISA Support Documentation
    isas_support_dir = os.path.join(project_root, "docs", "isas_support")
    if os.path.exists(isas_support_dir):
        shutil.rmtree(isas_support_dir)
    os.makedirs(isas_support_dir, exist_ok=True)

    print("[MIPP DocGen] Solving candidate dependencies across all target ISAs...")
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
