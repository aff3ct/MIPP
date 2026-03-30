#!/bin/python3
import os
import sys
import argparse
from jinja2 import Template, StrictUndefined

path = os.getcwd()

sys.path.insert(1, path + "/../simd_ext/avx512/")
sys.path.insert(1, path + "/../simd_ext/avx/")
sys.path.insert(1, path + "/../simd_ext/sse/")
sys.path.insert(1, path + "/../simd_ext/sve/")
sys.path.insert(1, path + "/../simd_ext/rvv/")
sys.path.insert(1, path + "/../")

from implem_sse import implems_sse
from implem_avx import implems_avx
from implem_avx512 import implems_avx512
from implem_sve import implems_sve
from implem_rvv import implems_rvv
from headers_def import mipp_funcs
from tools import *
from test_tools import get_gen_test_dict, set_skip_float, test_function_name

from implem_emu_sse import implems_emu_sse
from implem_emu_avx import implems_emu_avx
from implem_emu_avx512 import implems_emu_avx512
from implem_emu_sve import implems_emu_sve
from implem_emu_rvv import implems_emu_rvv

avx512_guard = "#if defined(MIPP_AVX512)"
avx2_guard = "#elif defined(MIPP_AVX2)"
avx_guard = "#elif defined(MIPP_AVX)"
sse_guard = "#elif defined(MIPP_SSE)"
# for some reason MIPP_SVE isnt defined idk
sve_guard = "#elif defined(__ARM_FEATURE_SVE)"
rvv_guard = "#elif defined(MIPP_RVV)"

implems_avx512.update(implems_emu_avx512)
implems_avx.update(implems_emu_avx)
implems_sse.update(implems_emu_sse)
implems_sve.update(implems_emu_sve)
implems_rvv.update(implems_emu_rvv)

implem_dict = {
    # avx512 has to be first bc it's the one w the #if
    "avx512": {"implem": implems_avx512, "guard": avx512_guard},
    "avx": {"implem": implems_avx, "guard": avx_guard},
    "sse": {"implem": implems_sse, "guard": sse_guard},
    "sve": {"implem": implems_sve, "guard": sve_guard},
    "rvv": {"implem": implems_rvv, "guard": rvv_guard},
}

set_skip_testing = {
    "get_k", #missing uint
    "getfirst", #getfirst broken on avx2
    "blend", #blend broken on avx2 + uses get_k :(
    "andb_k", #uses get_k n.b : get_k not defined for uint on avx2
    "orb_k", #uses get_k
    "xorb_k", #uses get_k
    "andnb_k", #uses get_k
    "notb_k", #uses get_k
    "toreg", #uses get_k.
    
    "hadd", #overflow for i8 u8. Test is good though
    "testz", #no set1_k for float & get_k on uint
    "testz_2", #no set1_k for float & get_k on uint
    "hadd_to_scal", #overflow for i8 & getfirst used so wrong for floats.
                    #also not implemented for uint on avx2.
}

# helper to get the datatypes for 1 func in 1 implem
def get_defined_dttypes(func, implem):
    """
    func: implem key, e.g. "add", "mul", ...
    implem: dict of the implem, e.g. implems_avx512
    returns a list of datatypes for which the func is defined in the implem
    """
    func_dt = implem[func]
    datatypes = []
    for dt in func_dt:
        datatypes.append(dt["datatypes"])
    datatypes = list(set([item for sublist in datatypes for item in sublist]))
    if func in set_skip_float:
        datatypes = [dt for dt in datatypes if dt not in ["float32", "float64"]]
    return datatypes

# add the type guard for 1 func in 1 implem
def add_type_guards(func, implem, function, kind="c"):
    """
    func: implem key, e.g. "add", "mul", ...
    implem: dict of the implem, e.g. implems_avx512
    function: part of the name of the fn to call. Should prolly be changed
    kind: "c" for c test, "cpp" for cpp test, "obj" for obj test

    returns a string with the type guards for the func in the implem
    
    N.B : WILL NOT GENERATE TESTS FOR DTTYPES IF THE FUNC IS NOT DEFINED
    FOR THOSE DTTYPES IN IMPLEM. EVEN IF THE FUNC IS DEFINED FOR THOSE 
    DTTYPES IN headers_def.mipp_funcs[func]["datatypes"].
    THIS IS FORE EASE OF TESTS.
    """
    datatypes = get_defined_dttypes(func, implem)
    section = ""
    res = ""
    if kind == "c":
        section = 'SECTION ("datatype = {dt}") {{ {function}_{dt}(); }}\n'
    elif kind == "cpp" or kind == "obj":
        section = 'SECTION ("datatype = {dt}") {{ {function}<{dt}_t>(); }}\n'

    list_64 = []
    list_bw = []
    datatypes.sort()
    for dt in datatypes:
        if dt in ["int64", "uint64", "float64"]:
            list_64.append(dt)
        elif dt in ["int8", "uint8", "int16", "uint16"]:
            list_bw.append(dt)
        else:
            res += section.format(dt=dt, function=function)

    if list_64 != []:
        list_64.sort()
        res += f"#if defined(MIPP_64BIT)\n"
        for dt in list_64:
            res += section.format(dt=dt, function=function)
        res += "#endif\n"

    if list_bw != []:
        list_bw.sort()
        res += f"#if defined(MIPP_BW)\n"
        for dt in list_bw:
            res += section.format(dt=dt, function=function)
        res += "#endif\n"

    return res

def gen_test_type_guards(func, long_name, short_name, kind="c"):
    layer_dict = get_gen_test_dict(kind)
    res = f'\nTEST_CASE("{long_name} - {kind}", "[{short_name}]") {{\n'
    for implems in implem_dict.values():
        res += implems["guard"] + "\n"
        if func in implems["implem"]:
            if kind == "c":
                res += add_type_guards(func, implems["implem"], function=f"test_cmipp_{func}", kind=kind)
            elif kind == "cpp":
                res += add_type_guards(
                    func,
                    implems["implem"],
                    function=f"test_cppmipp_{test_function_name(kind, func)}",
                    kind=kind,
                )
            elif kind == "obj":
                res += add_type_guards(
                    func,
                    implems["implem"],
                    function=f"test_objmipp_{test_function_name(kind, func)}",
                    kind=kind,
                )
    res += "#else\n"
    res += f'#error "No implementation for {func} in any of the supported architectures"\n'
    res += "#endif\n"
    res += "}\n"
    return res

# TODO : for C compatibiliy, use
# math.h stdio.h etc instead of cmath, cstdio, etc.
def gen_headers(kind="c"):
    """
    simple helper to return headers for the test files
    """
    res = (
        "#include <exception>"
        "\n#include <algorithm>"
        "\n#include <numeric>"
        "\n#include <random>"
        "\n#include <cstdio>"
        "\n#include <cmath>"
    )
    if kind == "c":
        res += "\n#include <mipp.h>"
    elif kind == "cpp":
        res += "\n#include <mipp.hpp>"
    elif kind == "obj":
        res += "\n#include <mipp_obj.hpp>"
    res += "\n#include <catch2/catch_test_macros.hpp>\n\n"
    return res

def gen_func(func, scalar_type, reg_type, kind="c", msk_type=""):
    # Pick per-layer dictionary
    layer_dict = get_gen_test_dict(kind)

    # we need to render twice because we have 2 levels of templates :)
    func_dict = layer_dict[func]["proto"]
    func_template = layer_dict[func]["template"]

    func_template = Template(func_template, undefined=StrictUndefined)
    res = func_template.render(
        func_decl=func_dict["func_decl"],
        decl=func_dict["decl"],
        init=func_dict["init"],
        load=func_dict["load"],
        operation=func_dict["operation"],
        loop_body=func_dict["loop_body"],
        loop_assert=func_dict["loop_assert"],
    )

    func_template = Template(res, undefined=StrictUndefined)

    func_old = func
    func = test_function_name(kind, func)

    res = func_template.render(
        func=func,
        dt_ext=scalar_type,
        op=layer_dict[func_old]["op"],
        reg_type=reg_type,
        msk_type=msk_type,
        size="MIPP_N_" + scalar_type.upper(),
    )
    # Warning: this doesn't pose "portability" issues bc cpp/obj don't use the size argument.
    # but it's unelegant
    return res + "\n"

def gen_funcs_all_datatypes(func, kind="c", register="rvd", mask="rvm"):
    layer_dict = get_gen_test_dict(kind)

    res = ""
    datatypes = mipp_funcs[func]["datatypes"]
    if func in set_skip_float:
        datatypes = [dt for dt in datatypes if dt not in ["float32", "float64"]]
    if kind == "c":
        for dt in datatypes:
            res += gen_func(
                func,
                dt,
                reg_type=f"{register}_" + dt + "_t",
                kind=kind,
                msk_type=f"{mask}_" + dt + "_t",
            )
    elif kind == "cpp":  # template so no need to loop over datatypes
        res += gen_func(
            func,
            "T",
            reg_type=f"mipp::{register}<T>",
            kind=kind,
            msk_type=f"mipp::{mask}<T>",
        )
    elif kind == "obj":  # template so no need to loop over datatypes
        res += gen_func(
            func,
            "T",
            reg_type=f"mipp::{register}<T>",
            kind=kind,
            msk_type=f"mipp::{mask}<T>",
        )
    return res

def gen_file(func, kind="c"):
    layer_dict = get_gen_test_dict(kind)

    register = "rvd"
    mask = "rvm"

    if kind == "obj":
        register = register.capitalize()  # obj types are Rvd, Rvm instead of rvd, rvm
        mask = mask.capitalize()

    res = gen_funcs_all_datatypes(func, kind=kind, register=register, mask=mask)
    res += gen_test_type_guards(
        func,
        layer_dict[func]["long_name"],
        layer_dict[func]["short_name"],
        kind=kind,
    )
    return res

tmp_path = "../../tests/src/"
cpath = tmp_path + "c_tests/"
cpppath = tmp_path + "cpp_tests/"
objpath = tmp_path + "obj_tests/"
# we want to generate 3 files for each func : c test, cpp test and obj test.

# func to change file only if content is different to avoid recompilation of unchanged files
# returns bool indicating if the file was written or not
def write_file_if_different(path, content):
    if os.path.exists(path):
        with open(path, "r") as f:
            existing_content = f.read()
        if existing_content == content:
            # print(f"No changes for {path}, skipping write.")
            return False
    with open(path, "w") as f:
        f.write(content)
    return True

def comment_out_cpp_file(content: str, reason: str):
    # Wrap whole file as a comment so it becomes an inert translation unit.
    # Keep a short header outside the comment so it's obvious in diffs.
    header = (
        "// THIS FILE IS AUTO-GENERATED.\n"
        f"// Tests are currently disabled: {reason}\n"
        "// To re-enable, remove the function from set_skip_testing in gen_files.py\n\n"
    )
    return header + "/*\n" + content + "\n*/\n"

def gen_test_files_all_funcs(kind="c"):
    """
    kind: "c", "cpp", "obj", or "all"
    Regenerates only the requested layer(s) for all functions.

    Important: functions available can differ per layer, so we iterate over the
    union of keys from the enabled layer dictionaries.
    """
    if kind not in {"c", "cpp", "obj", "all"}:
        raise ValueError(f"Invalid kind: {kind!r}")

    regen_c = kind in {"c", "all"}
    regen_cpp = kind in {"cpp", "all"}
    regen_obj = kind in {"obj", "all"}

    c_dict = get_gen_test_dict("c") if regen_c else {}
    cpp_dict = get_gen_test_dict("cpp") if regen_cpp else {}
    obj_dict = get_gen_test_dict("obj") if regen_obj else {}

    funcs = set()
    if regen_c:
        funcs |= set(c_dict.keys())
    if regen_cpp:
        funcs |= set(cpp_dict.keys())
    if regen_obj:
        funcs |= set(obj_dict.keys())

    # Create dirs only if needed
    if not os.path.exists(tmp_path):
        os.makedirs(tmp_path, exist_ok=True)
    if regen_c:
        os.makedirs(cpath, exist_ok=True)
    if regen_cpp:
        os.makedirs(cpppath, exist_ok=True)
    if regen_obj:
        os.makedirs(objpath, exist_ok=True)

    for func in sorted(funcs):
        
        disable = func in set_skip_testing
        reason = (
            f"{func} is in set_skip_testing. "
            "If it's blend it's because it's broken on AVX2; otherwise it's likely "
            "because get_k/set_k is used and doesn't work well on AVX2."
        )

        if regen_c and func in c_dict:
            c_file = gen_headers(kind="c") + gen_file(func, kind="c")
            if disable:
                c_file = comment_out_cpp_file(c_file, reason)
            write_file_if_different(cpath + f"test_c{func}.cpp", c_file)

        if regen_cpp and func in cpp_dict:
            cpp_file = gen_headers(kind="cpp") + gen_file(func, kind="cpp")
            if disable:
                cpp_file = comment_out_cpp_file(cpp_file, reason)
            write_file_if_different(cpppath + f"test_{func}.cpp", cpp_file)

        if regen_obj and func in obj_dict:
            obj_file = gen_headers(kind="obj") + gen_file(func, kind="obj")
            if disable:
                obj_file = comment_out_cpp_file(obj_file, reason)
            write_file_if_different(objpath + f"test_obj_{func}.cpp", obj_file)

def main():
    parser = argparse.ArgumentParser(description="Generate MIPP test files.")
    parser.add_argument(
        "kind",
        nargs="?",
        default="c",
        choices=["c", "cpp", "obj", "all"],
        help="Which layer to regenerate (default: all).",
    )
    args = parser.parse_args()
    gen_test_files_all_funcs(kind=args.kind)


if __name__ == "__main__":
    main()