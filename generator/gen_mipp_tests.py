#!/usr/bin/env python3
import os
import sys
import argparse
from jinja2 import Template, StrictUndefined

path = os.getcwd()

sys.path.insert(1, path + "/simd_ext/avx512/")
sys.path.insert(1, path + "/simd_ext/avx/")
sys.path.insert(1, path + "/simd_ext/sse/")
sys.path.insert(1, path + "/simd_ext/sve/")
sys.path.insert(1, path + "/simd_ext/rvv/")
sys.path.insert(1, path + "/")

from implem_sse import implems_sse
from implem_avx import implems_avx
from implem_avx512 import implems_avx512
from implem_sve import implems_sve
from implem_rvv import implems_rvv
from headers_def import mipp_funcs,mipp_funcs_concepts
from tools import *
from tests_utils import get_gen_test_dict, set_float_workaround, test_function_name

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
    "maskzld", #prototype is broken.
    "maskst", #prototype also broken. 
    "cast_k", #either testing or cast_k is wrong.    
}

###### HELPERS ######

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
    return datatypes

def dt_to_suffix(dt):
    """Used to convert cast format t1,t2 to t1_t2. 
    for other dttypes this is a no-op.
    """
    return dt.replace(",", "_")

def product_type_format_cpp(dt):
    """convert factor type "uint32,float32" to "uint32<float32_t>"
    converts single type "uint32" to "uint32_t" for cpp tests
    """
    if "," in dt:
        dt1, dt2 = dt.split(",")
        return f"_{dt1}<{dt2}_t>"
    else:
        return f"<{dt}_t>"

def split_dt_pair(dt) :
    """ 
    "uint32,float32" -> ["uint32","float32"]
    """
    return dt.split(",") if "," in dt else [dt]

def is_64bit_dt(dt):
    return dt in {"int64", "uint64", "float64"}

def is_bw_dt(dt):
    return dt in {"int8", "uint8", "int16", "uint16"}

def is_float_dt(dt):
    return dt in all_float

def is_int_dt(dt):
    return dt in all_int_uint

def is_signed_int_dt(dt):
    return dt in all_int

def match_concept(func):
    """
    helper to match a func to an 
    entry in mipp_funcs_concepts. 
    This is used to write files in the relevant 
    subdir for their concept.
    """
    for concept in mipp_funcs_concepts:
        if func in mipp_funcs_concepts[concept]:
            if concept == "a_trier":
                return "miscellaneous"
            return concept
    return "miscellaneous"

###### GENERATION FUNC ######

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
        section = 'SECTION ("datatype = {dt}") {{ {function}_{dt_suffix}(); }}\n'
    elif kind == "cpp" or kind == "obj":
        section = 'SECTION ("datatype = {dt}") {{ {function}{dt_suffix}(); }}\n'

    #lists to store the dttypes that need to be 
    #wrapped in #if defined(MIPP_64BIT) or #if defined(MIPP_BW)
    list_64 = []
    list_bw = []
    datatypes.sort()
    for dt in datatypes:
        dt_suffix = dt_to_suffix(dt)
        parts = split_dt_pair(dt)
        if any(is_64bit_dt(part) for part in parts):
            list_64.append(dt)
        elif any(is_bw_dt(part) for part in parts):
            list_bw.append(dt)
        else:
            
            #this is the ugly part
            if kind == "cpp" or kind == "obj":
                dt_suffix = product_type_format_cpp(dt)#used to handle cast
                if func in set_float_workaround and is_float_dt(dt):
                    #this is hacky. It's to generate proper name to call float 
                    #versions of andb etc...
                    dt_suffix = f"_float{dt_suffix.split('t')[1].split("_")[0]}{dt_suffix}"
            res += section.format(dt=dt, dt_suffix=dt_suffix, function=function)

    #same logic for these
    if list_64 != []:
        list_64.sort()
        res += f"#if defined(MIPP_64BIT)\n"
        for dt in list_64:
            dt_suffix = dt_to_suffix(dt)
            if kind == "cpp" or kind == "obj":
                dt_suffix = product_type_format_cpp(dt)
                if func in set_float_workaround and is_float_dt(dt):
                    dt_suffix = f"_float{dt_suffix.split('t')[1].split("_")[0]}{dt_suffix}"
            res += section.format(dt=dt, dt_suffix=dt_suffix, function=function)
        res += "#endif\n"

    if list_bw != []:
        list_bw.sort()
        res += f"#if defined(MIPP_BW)\n"
        for dt in list_bw:
            dt_suffix = dt_to_suffix(dt)
            if kind == "cpp" or kind == "obj":
                dt_suffix = product_type_format_cpp(dt)
                if func in set_float_workaround and is_float_dt(dt):
                    dt_suffix = f"_float{dt_suffix.split('t')[1].split("_")[0]}{dt_suffix}"

            res += section.format(dt=dt, dt_suffix=dt_suffix, function=function)
        res += "#endif\n"

    return res

def gen_test_type_guards(func, long_name, short_name, kind="c"):
    """
    Adds type guards to the test 
    case for the different implementations of a func.
    Only generates tests for the dttypes for which the func is defined in the implem.
    """
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

#cast specific to handle the dttype pair
def gen_cast_test_type_guards(func, long_name, short_name, kind="c"):
    """
    Cast is a "product type". 
    The logic is mostly the same as gen_test_type_guards 
    but we need to handle the dttype pairs properly.
    """
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
        "\n#include <bit>"
    )
    if kind == "c":
        res += "\n#include <mipp.h>"
    elif kind == "cpp":
        res += "\n#include <mipp.hpp>"
    elif kind == "obj":
        res += "\n#include <mipp_obj.hpp>"
    res += "\n#include <catch2/catch_test_macros.hpp>\n\n"
    return res

def gen_func(func, scalar_type, reg_type, kind="c", msk_type="", float=False):
    """
    generates the test function(s) for 1 func, 1 datatype, 1 layer.
    """
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
    type_size=""
    if kind=="c": 
        type_size = scalar_type.split("t")[1]
    
    
    #hacky workaround to handle float versions of andb etc... in cpp tests.
    #nb: float is set to != False only for CPP
    if kind=="c":
        res = func_template.render(
            func=func,
            dt_ext=scalar_type,
            op=layer_dict[func_old]["op"],
            reg_type=reg_type,
            msk_type=msk_type,
            size="MIPP_N_" + scalar_type.upper(),
            
            is_float=is_float_dt(scalar_type),
            is_int=is_int_dt(scalar_type),
            is_signed=is_signed_int_dt(scalar_type),
            type_size=type_size,
        )
    if not float and kind=="cpp" :
        res = func_template.render(
            func=func,
            dt_ext=scalar_type,
            op=layer_dict[func_old]["op"],
            reg_type=reg_type,
            msk_type=msk_type,
            size="MIPP_N_" + scalar_type.upper(),
            
            is_float=False,
            is_int=True,
        )
    if float and kind=="cpp" :
        res = func_template.render(
            func=func,
            dt_ext=scalar_type,
            op=layer_dict[func_old]["op"],
            reg_type=reg_type,
            msk_type=msk_type,
            size="MIPP_N_" + scalar_type.upper(),
            
            is_float=True,
            is_int=False,
            is_signed=False,
            type_size=float.split("t")[1],
        )
    if kind == "obj" :
        res = func_template.render(
            func=func,
            dt_ext=scalar_type,
            op=layer_dict[func_old]["op"],
            reg_type=reg_type,
            msk_type=msk_type,
            size="MIPP_N_" + scalar_type.upper(),
            
            is_float=is_float_dt(scalar_type),
            is_int=is_int_dt(scalar_type),
            is_signed=is_signed_int_dt(scalar_type),
            type_size=type_size,
        )
    return res + "\n"

def gen_cast_func(func, scalar1_type, scalar2_type, reg1_type, reg2_type, kind="c", msk1_type="", msk2_type=""):
    res = ""
    layer_dict = get_gen_test_dict(kind)
    #from func, get "cast" or "cast_k" to get the right template and proto
    if kind == "c":
        is_cast_k = func.startswith("cast_k")
        fname = "cast_k" if is_cast_k else "cast"
        
        func_dict = layer_dict[fname]["proto"]
        func_template = layer_dict[fname]["template"]
        
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
        func_old = "cast"
        func = test_function_name(kind, func)
        res = func_template.render(
            func=func,
            dt1_ext=scalar1_type,
            dt2_ext=scalar2_type,
            op=layer_dict[func_old]["op"],
            reg1_type=reg1_type,
            msk1_type=msk1_type,
            reg2_type=reg2_type,
            msk2_type=msk2_type,
            size="MIPP_N_" + scalar1_type.upper(),
            #size2="MIPP_N_" + scalar2_type.upper(),
        )
    elif kind == "cpp": 
        is_cast_k = func.startswith("cast_k")
        fname = "cast_k" if is_cast_k else "cast"
        func_dict = layer_dict[fname]["proto"]
        func_template = layer_dict[fname]["template"]   
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
        func_old = "cast"
        func = test_function_name(kind, func)
        res = func_template.render(
            func=func + "_" + scalar2_type,
            dt1_ext=scalar2_type,
            dt2_ext=scalar1_type,
            op=layer_dict[func_old]["op"],
            reg1_type=reg1_type,
            msk1_type=msk1_type,
            reg2_type=reg2_type,
            msk2_type=msk2_type,
            size="MIPP_N_" + scalar1_type.upper(),
            #size2="MIPP_N_" + scalar2_type.upper(),
        )
    else :#obj
        res = ""
    
    return res+ "\n"

def gen_cast_funcs_all_datatypes(func, kind="c", register="rvd", mask="rvm"):
    layer_dict = get_gen_test_dict(kind)
    datatypes = mipp_funcs[func]["datatypes"]
    res = ""
    if kind == "c":
        for dt in datatypes:
            dt1, dt2 = dt.split(",")
            func_name = f"{func}_{dt1}_{dt2}"
            res+= gen_cast_func(func_name, 
                                scalar1_type=dt1,
                                scalar2_type=dt2,
                                reg1_type=f"{register}_" + dt1 + "_t",
                                reg2_type=f"{register}_" + dt2 + "_t",
                                kind=kind, 
                                msk1_type=f"{mask}_" + dt1 + "_t",
                                msk2_type=f"{mask}_" + dt2 + "_t")
            
    elif kind == "cpp" :  # template so no need
        
        for dt in all_datatypes:
            dt1 = dt
            func_name = f"{func}_{dt1}"
            res += gen_cast_func(func, 
                            scalar1_type="T",
                            scalar2_type=dt1,
                            reg1_type=f"mipp::{register}<T>",
                            reg2_type=f"mipp::{register}<{dt1}_t>",
                            kind=kind,
                            msk1_type=f"mipp::{mask}<T>",
                            msk2_type=f"mipp::{mask}<{dt1}_t>")
    elif kind == "obj" :  # template so no need
        res += ""
    return res

def gen_funcs_all_datatypes(func, kind="c", register="rvd", mask="rvm"):
    """
    generate the test function(s) for 1 func, all datatypes, 1 layer.
    """
    layer_dict = get_gen_test_dict(kind)

    res = ""
    datatypes = mipp_funcs[func]["datatypes"]

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
        if func in set_float_workaround:
            res += gen_func(
                func,
                "T",
                reg_type=f"mipp::{register}<T>",
                kind=kind,
                msk_type=f"mipp::{mask}<T>",
                float="float32",
            )
            res += gen_func(
                func,
                "T",
                reg_type=f"mipp::{register}<T>",
                kind=kind,
                msk_type=f"mipp::{mask}<T>",
                float="float64",
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
    """
    generates the test file for 1 func, all datatypes, 1 layer.
    Calls gen_headers -> gen_funcs_all_datatypes -> gen_test_type_guards
    """
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

def gen_cast_file(func,kind="c"):
    layer_dict = get_gen_test_dict(kind)

    register = "rvd"
    mask = "rvm"

    if kind == "obj":
        register = register.capitalize()  # obj types are Rvd, Rvm instead of rvd, rvm
        mask = mask.capitalize()

    res = gen_cast_funcs_all_datatypes(func, kind=kind, register=register, mask=mask)
    res += gen_cast_test_type_guards(
        func,
        layer_dict[func]["long_name"],
        layer_dict[func]["short_name"],
        kind=kind,
    )
    return res


tmp_path = "../tests/src/"
cpath = tmp_path + "c_tests/"
cpppath = tmp_path + "cpp_tests/"
objpath = tmp_path + "obj_tests/"

def write_file_if_different(path, content):
    """
    helper to avoid rewriting files if the content is the same 
    to avoid unnecessary recompilation.
    """
    if os.path.exists(path):
        with open(path, "r") as f:
            existing_content = f.read()
        if existing_content == content:
            return False
    with open(path, "w") as f:
        f.write(content)
    return True

def comment_out_cpp_file(content: str, reason: str):
    """
    simple way to skip testing for a func 
    without removing the generated file
    """
    header = (
        "// THIS FILE IS AUTO-GENERATED.\n"
        f"// Tests are currently disabled: {reason}\n"
        "// To re-enable, remove the function from set_skip_testing in gen_files.py\n\n"
    )
    return header + "/*\n" + content + "\n*/\n"

#big and somewhat ugly "main" func to generate all test files for all funcs for the requested layer(s)
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
        for concept in mipp_funcs_concepts:
            if concept != "a_trier":
                os.makedirs(cpath + concept + "/", exist_ok=True)
        os.makedirs(cpath + "miscellaneous/", exist_ok=True)
    if regen_cpp:
        os.makedirs(cpppath, exist_ok=True)
        for concept in mipp_funcs_concepts:
            if concept != "a_trier":
                os.makedirs(cpppath + concept + "/", exist_ok=True)
        os.makedirs(cpppath + "miscellaneous/", exist_ok=True)
    if regen_obj:
        os.makedirs(objpath, exist_ok=True)
        for concept in mipp_funcs_concepts:
            if concept != "a_trier":
                os.makedirs(objpath + concept + "/", exist_ok=True)
        os.makedirs(objpath + "miscellaneous/", exist_ok=True)

    for func in sorted(funcs):
        
        disable = func in set_skip_testing
        reason = (
            f"{func} is in set_skip_testing. "
            "If it's blend it's because it's broken on AVX2; otherwise it's likely "
            "because get_k/set_k is used and doesn't work well on AVX2."
        )

        if regen_c and func in c_dict:
            if func == "cast" or func == "cast_k":
                c_file = gen_headers(kind="c") + gen_cast_file(func, kind="c")
            else:
                c_file = gen_headers(kind="c") + gen_file(func, kind="c")
            if disable:
                c_file = comment_out_cpp_file(c_file, reason)
            file_path = cpath + match_concept(func) + f"/test_c{func}.cpp"
            write_file_if_different(file_path, c_file)

        if regen_cpp and func in cpp_dict:
            if func == "cast" or func == "cast_k":
                cpp_file = gen_headers(kind="cpp") + gen_cast_file(func, kind="cpp")
            else:
                cpp_file = gen_headers(kind="cpp") + gen_file(func, kind="cpp")
                
            if disable:
                cpp_file = comment_out_cpp_file(cpp_file, reason)
            file_path = cpppath + match_concept(func) + f"/test_{func}.cpp"
            write_file_if_different(file_path, cpp_file)

        if regen_obj and func in obj_dict:
            if func == "cast" or func == "cast_k":
                obj_file = gen_headers(kind="obj") + gen_cast_file(func, kind="obj")
            else:
                obj_file = gen_headers(kind="obj") + gen_file(func, kind="obj")
            if disable:
                obj_file = comment_out_cpp_file(obj_file, reason)

            file_path = objpath + match_concept(func) + f"/test_obj_{func}.cpp"
            write_file_if_different(file_path, obj_file)

def main():#just parse the args and call gen_test_files_all_funcs with the right kind
    parser = argparse.ArgumentParser(description="Generate MIPP test files.")
    parser.add_argument(
        "kind",
        nargs="?",
        default="all",
        choices=["c", "cpp", "obj", "all"],
        help="Which layer to regenerate (default: all).",
    )
    args = parser.parse_args()
    gen_test_files_all_funcs(kind=args.kind)


if __name__ == "__main__":
    main()