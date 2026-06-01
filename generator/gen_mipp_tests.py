#!/usr/bin/env python3
import os
from pathlib import Path
import sys
import argparse
import shutil
from jinja2 import Template, StrictUndefined

path = os.getcwd()

sys.path.insert(1, path + "/simd_ext/avx512/")
sys.path.insert(1, path + "/simd_ext/avx/")
sys.path.insert(1, path + "/simd_ext/sse/")
sys.path.insert(1, path + "/simd_ext/sve/")
sys.path.insert(1, path + "/simd_ext/rvv/")
sys.path.insert(1, path + "/simd_ext/neon/")
# sys.path.insert(1, path + "/simd_ext/scalar/")
sys.path.insert(1, path + "/helpers_headers/")

from implem_sse import implems_sse
from implem_avx import implems_avx
from implem_avx512 import implems_avx512
from implem_sve import implems_sve
from implem_rvv import implems_rvv
from implem_neon import implems_neon
from headers_def import implems_scalar
from headers_def import mipp_funcs,mipp_funcs_concepts
from tools import *
from helpers_tests import get_gen_test_dict, test_function_name, get_gen_test_dict_lmul, get_gen_test_dict_mask

from implem_emu_sse import implems_emu_sse
from implem_emu_avx import implems_emu_avx
from implem_emu_avx512 import implems_emu_avx512
from implem_emu_sve import implems_emu_sve
from implem_emu_rvv import implems_emu_rvv
from implem_emu_neon import implems_emu_neon

from generic_emu import implems_generic_emu

avx512_guard = "#if defined(MIPP_AVX512)"
avx2_guard = "#elif defined(MIPP_AVX2)"
avx_guard = "#elif defined(MIPP_AVX)"
sse_guard = "#elif defined(MIPP_SSE)"
sve_guard = "#elif defined(MIPP_SVE)"
rvv_guard = "#elif defined(MIPP_RVV)"
neon_guard = "#elif defined(MIPP_NEON)"
scalar_guard = "#elif defined(MIPP_SCALAR)"

# .update can lead to bugs if there 
# are less types in the emu implem than in non emu implem. 
# this was the case for fmadd in RVV.
implems_avx512.update(implems_emu_avx512)
implems_avx.update(implems_emu_avx)
implems_sse.update(implems_emu_sse)
implems_sve.update(implems_emu_sve)
implems_rvv.update(implems_emu_rvv)
implems_neon.update(implems_emu_neon)

#implems_avx512.update(implems_generic_emu)
implems_avx.update(implems_generic_emu)
implems_sse.update(implems_generic_emu)
#implems_sve.update(implems_generic_emu)
implems_rvv.update(implems_generic_emu)

implem_dict = {
    # avx512 has to be first bc it's the one w the #if
    "avx512": {"implem": implems_avx512, "guard": avx512_guard},
    "avx": {"implem": implems_avx, "guard": avx_guard},
    "sse": {"implem": implems_sse, "guard": sse_guard},
    "sve": {"implem": implems_sve, "guard": sve_guard},
    "rvv": {"implem": implems_rvv, "guard": rvv_guard},
    "neon": {"implem": implems_neon, "guard": neon_guard},
    "scalar": {"implem": implems_scalar, "guard": scalar_guard},
}

set_skip_testing = {                    
    "maskzld", #prototype is broken.
    "maskst", #prototype also broken. 
    "cast_k", #either testing or cast_k is wrong.  
    # THESE FUNCTIONS ARE NOT IMPLEMENTED YET (they are only in scalar)
    "adds",
    "subs" ,
    "hadds_to_scal",
    "hadds", 
}

#every func that has the key "horizontal" set to false
#in headers_def.mipp_funcs will be generated with lmuls
#except for RVV which where lmul variants will be generated for 
#every function.
mipp_funcs_lmul = {
    func : meta for func, meta in mipp_funcs.items() if meta["horizontal"] == False
}
###### HELPERS ######

# helper to get the datatypes for 1 func in 1 implem
def get_defined_dttypes(func, implem, mkind=""):
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
    if not datatypes:
        datatypes = mipp_funcs[func]["datatypes"]
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

def gen_func_defines(func, dt, implem):
    func_defines = ""
    for sub_implem in implem[func]:
        if dt in sub_implem["datatypes"]:
            if "if" in sub_implem:
                if func_defines:
                    func_defines += " || "
                func_defines += "(" + sub_implem["if"] + ")"
    return func_defines

def lmul_to_str(lmul, mkind=""):
    #1-> m1 
    #2-> m2
    #4-> m4
    #8-> m8
    #1/2 -> d2
    #1/4 -> d4
    #1/8 -> d8
    
    #temporary fix. Every generator will be handled by 
    #layer_X_mask at some point. But we'll keep it that way for now.
    if mkind == "":
        match lmul:
            case 0 : return ""
            case 1 : return "m1"
            case 2 : return "m2"
            case 4 : return "m4"
            case 8 : return "m8"
            case 0.5 : return "d2"
            case 0.25 : return "d4"
            case 0.125 : return "d8"
    else:
        match lmul:
            case 0 : return ""
            case 1 : return "_m1"
            case 2 : return "_m2"
            case 4 : return "_m4"
            case 8 : return "_m8"
            case 0.5 : return "_d2"
            case 0.25 : return "_d4"
            case 0.125 : return "_d8"
def mask_to_str(mkind, kind):
    if kind == "c" : 
        if mkind == "" :
            return ""
        else :
            return f"_{mkind}"
    elif kind == "cpp" :
        if mkind == "" :
            return ""
        else :
            if mkind == "mask" :
                return "<M>"
            elif mask == "maskz" :
                return "<Z>"
            elif mask == "masks" :
                return "<S>"
            else : 
                raise ValueError(f"Unknown mask: {mask!r}")

def get_mask_args(mkind): 
    if mkind == "" :
        return ""
    else :
        if mkind== "mask" or mkind == "maskz" : 
            return "mpred,"
        elif mkind == "masks" :
            return "mpred, rsrc,"
def get_scalar_mask_args(mkind):
    if mkind == "" :
        return ""
    else :
        if mkind== "mask" or mkind == "maskz" : 
            return "smpred,"
        elif mkind == "masks" :
            return "smpred, srsrc,"

###### GENERATION FUNC ######

# add the type guard for 1 func in 1 implem
def add_type_guards(func, implem, function, kind="c", lmul=0, mkind=""):
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
    datatypes = get_defined_dttypes(func, implem, mkind)

    section = ""
    res = ""
    lmul_str = lmul_to_str(lmul, "")
    lmul_str = "_" + lmul_str if lmul_str else ""
    mask_str = mask_to_str(mkind, kind)
    if kind == "c":
        section = 'SECTION ("datatype = {dt}") {{ {function}_{dt_suffix}{mask_str}{lmul_str}(); }}\n'
    elif kind == "cpp" or kind == "obj":
        section = 'SECTION ("datatype = {dt}") {{ {function}{lmul_str}{dt_suffix}(); }}\n'

    #lists to store the dttypes that need to be 
    #wrapped in #if defined(MIPP_64BIT) or #if defined(MIPP_BW)
    list_64 = []
    list_bw = []
    datatypes.sort()
    for dt in datatypes:
        func_defines = gen_func_defines(func, dt, implem)
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
                
            if func_defines:
                res += f"#if {func_defines}\n"
            res += section.format(dt=dt, dt_suffix=dt_suffix, function=function, lmul_str=lmul_str, mask_str=mask_str)
            if func_defines:
                res += f"#endif // {func_defines}\n"

    #same logic for these
    if list_64 != []:
        list_64.sort()
        res += f"#if defined(MIPP_64BIT)\n"
        for dt in list_64:
            func_defines = gen_func_defines(func, dt, implem)
            dt_suffix = dt_to_suffix(dt)
            if kind == "cpp" or kind == "obj":
                dt_suffix = product_type_format_cpp(dt)
            
            if func_defines:
                res += f"#if {func_defines}\n"
            res += section.format(dt=dt, dt_suffix=dt_suffix, function=function, lmul_str=lmul_str, mask_str=mask_str)
            if func_defines:
                res += f"#endif // {func_defines}\n"
        res += "#endif // defined(MIPP_64BIT)\n"

    if list_bw != []:
        list_bw.sort()
        res += f"#if defined(MIPP_BW)\n"
        for dt in list_bw:
            func_defines = gen_func_defines(func, dt, implem)
            dt_suffix = dt_to_suffix(dt)
            if kind == "cpp" or kind == "obj":
                dt_suffix = product_type_format_cpp(dt)
               
            if func_defines:
                res += f"#if {func_defines}\n"
            res += section.format(dt=dt, dt_suffix=dt_suffix, function=function, lmul_str=lmul_str, mask_str=mask_str)
            if func_defines:
                res += f"#endif // {func_defines}\n"
        res += "#endif // defined(MIPP_BW)\n"

    return res

def gen_test_type_guards(func, long_name, short_name, kind="c", lmul=0, mkind=""):
    """
    Adds type guards to the test 
    case for the different implementations of a func.
    Only generates tests for the dttypes for which the func is defined in the implem.
    """
    layer_dict = get_gen_test_dict(kind)
    if lmul != 0 : 
        layer_dict = get_gen_test_dict_lmul(kind)
    if mkind != "" :
        layer_dict = get_gen_test_dict_mask(kind)
    lmul_str = "" if lmul == 0 else lmul_to_str(lmul, "")
    res = f'\nTEST_CASE("{long_name} - {kind} {lmul_str} {mkind}", "[{short_name}]") {{\n'
    for implems in implem_dict.values():

        res += implems["guard"] + "\n"
        if func in implems["implem"]:
            if kind == "c":
                res += add_type_guards(func, implems["implem"], function=f"test_cmipp_{func}", kind=kind, lmul=lmul, mkind=mkind)
            elif kind == "cpp":
                res += add_type_guards(
                    func,
                    implems["implem"],
                    function=f"test_cppmipp_{test_function_name(kind, func)}",
                    kind=kind,
                    lmul=lmul,
                     mkind=mkind,	
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
def gen_cast_test_type_guards(func, long_name, short_name, kind="c", lmul=0, mkind=""):
    """
    Cast is a "product type". 
    The logic is mostly the same as gen_test_type_guards 
    but we need to handle the dttype pairs properly.
    """
    layer_dict = get_gen_test_dict(kind)
    if lmul != 0 :
        layer_dict = get_gen_test_dict_lmul(kind)
    if mkind != "" :
        layer_dict = get_gen_test_dict_mask(kind)
    lmul_str = "" if lmul == 0 else lmul_to_str(lmul, "")
    res = f'\nTEST_CASE("{long_name} - {kind} {lmul_str}", "[{short_name}]") {{\n'

    for implems in implem_dict.values():
        res += implems["guard"] + "\n"
        if func in implems["implem"]:
            if kind == "c":
                res += add_type_guards(func, implems["implem"], function=f"test_cmipp_{func}", kind=kind, lmul=lmul, mkind=mkind)
            elif kind == "cpp":
                res += add_type_guards(
                    func,
                    implems["implem"],
                    function=f"test_cppmipp_{test_function_name(kind, func)}",
                    kind=kind,
                    lmul=lmul,
                    mkind=mkind,	
                )
            elif kind == "obj":
                res += add_type_guards(
                    func,
                    implems["implem"],
                    function=f"test_objmipp_{test_function_name(kind, func)}",
                    kind=kind,
                    lmul=lmul, 
                    mkind=mkind,
                )
    res += "#else\n"
    res += f'#error "No implementation for {func} in any of the supported architectures"\n'
    res += "#endif\n"
    res += "}\n"
    return res

# TODO : for C compatibiliy, use
# math.h stdio.h etc instead of cmath, cstdio, etc.


def match_func_headers(func, kind="c", mkind=""):
    """
    helper to match a func to the relevant headers to include in the test file.
    This is used to avoid including all headers in all test files, which can cause 
    issues with conflicting types etc...
    """
    headers = ""
    hsufix = ".h" if kind == "c" else ".hpp"
    
    cpp_func_scalprefix = "#include <simd_ext_cpp/scalar_cpp/functions/scalar_cpp_"
    c_func_scalprefix = "#include <simd_ext/scalar/functions/scalar_"
    func_scalprefix = cpp_func_scalprefix if kind == "cpp" else c_func_scalprefix

    cpp_common_scalpath = "#include <simd_ext_cpp/scalar_cpp/scalar_cpp_common.hpp>\n"
    c_common_scalpath = "#include <simd_ext/scalar/scalar_common.h>\n"

    common_scalpath = cpp_common_scalpath if kind == "cpp" else c_common_scalpath

    if kind == "c" or kind == "cpp":
            
        headers += f"\n#include <{kind}/common{hsufix}>\n"
        headers += common_scalpath
        
        headers += f'#include <{kind}/functions/{func}{hsufix}>\n'
        
        headers += f'{func_scalprefix}{func}{hsufix}>\n'
        #also include load, get 
        headers += f'#include <{kind}/functions/load{hsufix}>\n'
        headers += f'#include <{kind}/functions/get{hsufix}>\n'
        
        headers += f'{func_scalprefix}load{hsufix}>\n'
        headers += f'{func_scalprefix}get{hsufix}>\n'
        
        if mkind != "" :
            headers += f"\n#include <{kind}/functions/set1_k{hsufix}>\n"
            headers += f'#include <simd_ext/scalar/functions/scalar_set1_k.h>\n'
            
            headers += f"\n#include <{kind}/functions/get_k{hsufix}>\n"
            headers += f'#include <simd_ext/scalar/functions/scalar_get_k.h>\n'
            
            headers += f"\n#include <{kind}/functions/set_k{hsufix}>\n"
            headers += f'#include <simd_ext/scalar/functions/scalar_set_k.h>\n'

        if func.endswith("_k"):
            headers += f'#include <{kind}/functions/get_k{hsufix}>\n'
            headers += f'#include <{kind}/functions/set_k{hsufix}>\n'
            headers += f'#include <{kind}/functions/toreg{hsufix}>\n'
            
            # include get_k, set_k, toreg
            headers += f'{func_scalprefix}get_k{hsufix}>\n'
            headers += f'{func_scalprefix}set_k{hsufix}>\n'
            headers += f'{func_scalprefix}toreg{hsufix}>\n'

        if func == "tomsk" : 
            headers += f'#include <{kind}/functions/toreg{hsufix}>\n'
            headers += f'{func_scalprefix}toreg{hsufix}>\n'        
            
        if func == "storeu" : 
            headers += f'#include <{kind}/functions/store{hsufix}>\n'
            headers += f'{func_scalprefix}store{hsufix}>\n'
            
        # if func in {"fmadd", "fmsub", "fnmadd", "fnmsub"} :
        #     headers += f'#include <{kind}/functions/mul{hsufix}>\n'
        #     headers += f'#include <{kind}/functions/add{hsufix}>\n'
        #     headers += f'#include <{kind}/functions/sub{hsufix}>\n'
        
        #     headers += f'#include <simd_ext/scalar/functions/scalar_mul.h>\n'
        #     headers += f'#include <simd_ext/scalar/functions/scalar_add.h>\n'
        #     headers += f'#include <simd_ext/scalar/functions/scalar_sub.h>\n'

        if func == "toreg" : 
            headers += f'#include <{kind}/functions/get_k{hsufix}>\n'
            headers += f'#include <{kind}/functions/set_k{hsufix}>\n'
            
            headers += f'{func_scalprefix}get_k{hsufix}>\n'
            headers += f'{func_scalprefix}set_k{hsufix}>\n'

        
        if func in {"cmpeq", "cmpneq", "cmpgt", "cmpge", "cmplt", "cmple"} :
            headers += f'#include <{kind}/functions/toreg{hsufix}>\n'
            headers += f'{func_scalprefix}toreg{hsufix}>\n'
            
        if func == "blend" :
            headers += f'#include <{kind}/functions/get_k{hsufix}>\n'
            headers += f'#include <{kind}/functions/set_k{hsufix}>\n'
            headers += f'#include <{kind}/functions/set1{hsufix}>\n'
            
            headers += f'{func_scalprefix}get_k{hsufix}>\n'
            headers += f'{func_scalprefix}set_k{hsufix}>\n'
            headers += f'{func_scalprefix}set1{hsufix}>\n'
            
        if func == "maskz_add" : 
            headers += f'#include <{kind}/functions/set1{hsufix}>\n'
            headers += f'#include <{kind}/functions/set_k{hsufix}>\n'
            headers += f'#include <{kind}/functions/get_k{hsufix}>\n'
            
            headers += f'{func_scalprefix}set1{hsufix}>\n'
            headers += f'{func_scalprefix}set_k{hsufix}>\n'
            headers += f'{func_scalprefix}get_k{hsufix}>\n'
            
        if func == "testz" :
            headers += f'#include <{kind}/functions/set1_k{hsufix}>\n'
            headers += f'{func_scalprefix}set1_k{hsufix}>\n'
        
        if func == "testz_2" :
            headers += f'#include <{kind}/functions/set1_k{hsufix}>\n'
            headers += f'{func_scalprefix}set1_k{hsufix}>\n'
    
    elif kind == "obj":
        headers += "#include <mipp_obj{hsufix}pp>\n"

    return headers

def gen_headers(kind="c", func="", N=10, lmul=0, mkind=""):
    """
    simple helper to return headers for the test files
    """
    path_ext_hack = ""
    if lmul != 0 : 
        path_ext_hack += "../"
    if mkind != "" :
        path_ext_hack += "../"
    res = (
        "#include <exception>"
        "\n#include <algorithm>"
        "\n#include <numeric>"
        "\n#include <random>"
        "\n#include <cstdio>"
        "\n#include <cmath>"
        "\n#include <bit>"
        f'\n#include "{path_ext_hack}../../uniform.hpp"'
        f'\n#include "{path_ext_hack}../../overflow_helpers.hpp"'
        f'\n#include "{path_ext_hack}../../abs_diff.hpp"'
        f"\n#define N_ITER {N}\n"

    )
    if kind == "c":
        
        res += match_func_headers(func, kind, mkind)
    elif kind == "cpp":
        res += match_func_headers(func, kind, mkind)
    elif kind == "obj":
        res += "\n#include <mipp_obj.hpp>"
    res += "\n#include <catch2/catch_test_macros.hpp>"
    res += "\n#include <catch2/catch_get_random_seed.hpp>\n\n" # getSeed()
    return res

def gen_func(func, scalar_type, reg_type, kind="c", msk_type="", float=False, lmul=0, mkind=""):
    """
    generates the test function(s) for 1 func, 1 datatype, 1 layer.
    """
    # Pick per-layer dictionary
    layer_dict = get_gen_test_dict(kind)
    if lmul != 0:
        layer_dict = get_gen_test_dict_lmul(kind)
    if mkind != "":
        layer_dict = get_gen_test_dict_mask(kind)

    # we need to render twice because we have 2 levels of templates :)
    # if func not in layer_dict:
    #     return f"// No template for {func} in {kind} tests\n"
    func_dict = layer_dict[func]["proto"]
    func_template = layer_dict[func]["template"]


    size = "MIPP_N_" + scalar_type.upper()
    if kind != "c": 
        size = "mipp::N<T>()"

    func_template = Template(func_template, undefined=StrictUndefined)
    res = func_template.render(
        func_decl=func_dict["func_decl"],
        decl=func_dict["decl"],
        init=func_dict["init"],
        load=func_dict["load"],
        operation=func_dict["operation"],
        loop_body=func_dict["loop_body"],
        loop_assert=func_dict["loop_assert"],
        size=size,
    )

    func_template = Template(res, undefined=StrictUndefined)

    func_old = func
    func = test_function_name(kind, func)
    type_size=""
    if kind=="c": 
        type_size = scalar_type.split("t")[1]
    
    
    #hacky workaround to handle float versions of andb etc... in cpp tests.
    #nb: float is set to != False only for CPP
    lmul_suffix = lmul_to_str(lmul, mkind)
    lmul_coeff = 1
    if lmul != 0 :
        lmul_coeff = lmul
    if kind=="c":
        # append scalar after the first "_" in reg type 
        # nb : there can be a different amount of "_" in reg type like : rvd_int64_t
        # rvd_int64_m1_t etc
        split = reg_type.split("_", 1)
        reg_type_scalar = split[0] + "_scalar_" + split[1]
        scalar_ext = "scalar_" + scalar_type
        
        split = msk_type.split("_", 1)
        msk_type_scalar = split[0] + "_scalar_" + split[1]

        res = func_template.render(
            func=func,
            dt_ext=scalar_type,
            op=layer_dict[func_old]["op"],
            reg_type=reg_type,
            msk_type=msk_type,
            size=size,
            
            is_float=is_float_dt(scalar_type),
            is_int=is_int_dt(scalar_type),
            is_signed=is_signed_int_dt(scalar_type),
            type_size=type_size,
            lmul_suffix=lmul_suffix,
            lmul_coeff=lmul_coeff,
            mask_args=get_mask_args(mkind),
            mask_args_scalar=get_scalar_mask_args(mkind),
            mask_kind=mask_to_str(mkind, kind),
            
            reg_type_scalar=reg_type_scalar,
            scalar_ext=scalar_ext,
            msk_type_scalar=msk_type_scalar,
            mkind=mkind, # used to know wether to define mpred or not
        )
    if kind=="cpp" :
        
        lmul_coeff = lmul
        if lmul == 0:
            lmul_coeff = 1
        reg_type_scalar = f"mipp::rvd<T,{lmul_coeff},mipp::ISA::SCALAR>"
        msk_type_scalar = f"mipp::rvm<T,{lmul_coeff},mipp::ISA::SCALAR>"

        res = func_template.render(
            func=func,
            dt_ext=scalar_type,
            op=layer_dict[func_old]["op"],
            reg_type=reg_type,
            msk_type=msk_type,
            size=size,
            
            is_float=False,
            is_int=True,
            
            lmul_suffix=lmul_suffix,
            lmul_coeff=lmul_coeff,
            
            mask_args=get_mask_args(mkind),
            mask_kind=mask_to_str(mkind, kind),
            reg_type_scalar=reg_type_scalar,
            msk_type_scalar=msk_type_scalar,
        )
    # if float and kind=="cpp" :
    #     reg_type_scalar = "mipp::rvd<T,1,mipp::ISA::SCALAR>"
    #     msk_type_scalar = "mipp::rvm<T,1,mipp::ISA::SCALAR>"
     
    #     res = func_template.render(
    #         func=func,
    #         dt_ext=scalar_type,
    #         op=layer_dict[func_old]["op"],
    #         reg_type=reg_type,
    #         msk_type=msk_type,
    #         size=size,
            
    #         is_float=True,
    #         is_int=False,
    #         is_signed=False,
    #         type_size=float.split("t")[1],
    #         lmul_suffix=lmul_suffix,
    #         lmul_coeff=lmul_coeff,
            
    #         mask_args=get_mask_args(mkind),
    #         mask_kind=mask_to_str(mkind, kind),

    #         reg_type_scalar=reg_type_scalar,
    #         msk_type_scalar=msk_type_scalar,
    #     )
    if kind == "obj" : #obsolete :(
        res = func_template.render(
            func=func,
            dt_ext=scalar_type,
            op=layer_dict[func_old]["op"],
            reg_type=reg_type,
            msk_type=msk_type,
            size=size,
            
            is_float=is_float_dt(scalar_type),
            is_int=is_int_dt(scalar_type),
            is_signed=is_signed_int_dt(scalar_type),
            type_size=type_size,
        )
    return res + "\n"

def gen_cast_func(func, scalar1_type, scalar2_type, reg1_type, reg2_type, kind="c", msk1_type="", msk2_type="", lmul=0, mkind=""):
    res = ""
    layer_dict = get_gen_test_dict(kind)
    if lmul != 0:
        layer_dict = get_gen_test_dict_lmul(kind)
    if mkind != "":
        layer_dict = get_gen_test_dict_mask(kind)
    #from func, get "cast" or "cast_k" to get the right template and proto
    if kind == "c":
        is_cast_k = func.startswith("cast_k")
        fname = "cast_k" if is_cast_k else "cast"
        
        
        # if fname not in layer_dict:
        #     return f"// No template for {fname} in {kind} tests\n"
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
        
        
        
        lmul_suffix = lmul_to_str(lmul, mkind)
        lmul_coeff = 1 
        if lmul != 0 :
            lmul_coeff = lmul
        
        # split = reg_type.split("_", 1)
        # reg_type_scalar = split[0] + "_scalar_" + split[1]
        # scalar_ext = "scalar_" + scalar_type
        
        # split = msk_type.split("_", 1)
        # msk_type_scalar = split[0] + "_scalar_" + split[1]
        
        split = reg1_type.split("_", 1)
        reg1_type_scalar = split[0] + "_scalar_" + split[1]
        scalar1_ext = "scalar_" + scalar1_type
        
        split = reg2_type.split("_", 1)
        reg2_type_scalar = split[0] + "_scalar_" + split[1]
        scalar2_ext = "scalar_" + scalar2_type
        
        split = msk1_type.split("_", 1)
        msk1_type_scalar = split[0] + "_scalar_" + split[1]
        msk1_ext = "scalar_" + scalar1_type
        
        split = msk2_type.split("_", 1)
        msk2_type_scalar = split[0] + "_scalar_" + split[1]
        msk2_ext = "scalar_" + scalar2_type
        
        size = "MIPP_N_" + scalar1_type.upper()
        
        res = func_template.render(
            func=func,
            dt_ext=scalar1_type,
            dt1_ext=scalar1_type,
            dt2_ext=scalar2_type,
            op=layer_dict[func_old]["op"],
            reg1_type=reg1_type,
            msk1_type=msk1_type,
            reg2_type=reg2_type,
            msk2_type=msk2_type,
            size=size,
            lmul_suffix=lmul_suffix,
            lmul_coeff=lmul_coeff,
            #size2="MIPP_N_" + scalar2_type.upper(),
            
            mask_args=get_mask_args(mkind),
            mask_kind=mask_to_str(mkind, kind),
            
            reg1_scalar_type=reg1_type_scalar,
            reg2_scalar_type=reg2_type_scalar,
            msk1_scalar_type=msk1_type_scalar,
            msk2_scalar_type=msk2_type_scalar,
        )
    elif kind == "cpp": 
        
        size = "mipp::N<T>()"
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
            mask_args=get_mask_args(mkind),
            mask_kind=mask_to_str(mkind, kind),
        )
        func_template = Template(res, undefined=StrictUndefined)
        func_old = "cast"
        lst = list(layer_dict.keys())
        lst.sort()
        print("Debug", f"keys={lst}, lmul={lmul}, mkind={mkind}")
        
        lmul_suffix = lmul_to_str(lmul, mkind)
        lmul_coeff = lmul

       
        # add the 1, ISA::SCALAR 
        split = reg1_type.split(">", 1)
        reg1_type_scalar = split[0] + ",1,mipp::ISA::SCALAR>"

        split = msk1_type.split(">", 1)
        msk1_type_scalar = split[0] + ",1,mipp::ISA::SCALAR>"


        split = reg2_type.split(">", 1)
        reg2_type_scalar = split[0] + ",1,mipp::ISA::SCALAR>"
        
        split = msk2_type.split(">", 1)
        msk2_type_scalar = split[0] + ",1,mipp::ISA::SCALAR>"

        
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
            size=size,
            lmul_suffix=lmul_suffix,
            lmul_coeff=lmul_coeff,
            mask_args=get_mask_args(mkind),
            mask_kind=mask_to_str(mkind, kind),
            reg1_type_scalar=reg1_type_scalar,
            reg2_type_scalar=reg2_type_scalar,
            msk1_type_scalar=msk1_type_scalar,
            msk2_type_scalar=msk2_type_scalar,
        )
    else :#obj
        res = ""
    
    return res+ "\n"

def gen_cast_funcs_all_datatypes(func, kind="c", register="rvd", mask="rvm",lmul=0, mkind=""):

    datatypes = mipp_funcs[func]["datatypes"]
    
    res = ""
    if kind == "c":
        for dt in datatypes:
            dt1, dt2 = dt.split(",")
            func_name = f"{func}_{dt1}_{dt2}"
            
            
            
            if lmul > 0:
                reg1_type = f"{register}_" + dt1 + f"_m{lmul}_t"
                reg2_type = f"{register}_" + dt2 + f"_m{lmul}_t"
                msk1_type = f"{mask}_" + dt1 + f"_m{lmul}_t"
                msk2_type = f"{mask}_" + dt2 + f"_m{lmul}_t"
                
                res+= gen_cast_func(func_name, 
                                    scalar1_type=dt1,
                                    scalar2_type=dt2,
                                    reg1_type=reg1_type,
                                    reg2_type=reg2_type,
                                    kind=kind, 
                                    msk1_type=msk1_type,
                                    msk2_type=msk2_type,
                                    lmul=lmul,
                                    mkind=mkind,
                )
            
            else : 
                
                reg1_type = f"{register}_" + dt1 + "_t"
                reg2_type = f"{register}_" + dt2 + "_t"
            
                msk1_type = f"{mask}_" + dt1 + "_t"
                msk2_type = f"{mask}_" + dt2 + "_t"
            
                res+= gen_cast_func(func_name, 
                                    scalar1_type=dt1,
                                    scalar2_type=dt2,
                                    reg1_type=reg1_type,
                                    reg2_type=reg2_type,
                                    kind=kind, 
                                    msk1_type=msk1_type,
                                    msk2_type=msk2_type,
                                    lmul=lmul,
                                    mkind=mkind,
                )
    elif kind == "cpp" :
        
        for dt in all_datatypes:
            dt1 = dt
            func_name = f"{func}_{dt1}"
            
            
            reg1_type = f"mipp::{register}<T>"
            reg2_type = f"mipp::{register}<{dt1}_t>"
            
            msk1_type = f"mipp::{mask}<T>"
            msk2_type = f"mipp::{mask}<{dt1}_t>"
            
            if lmul > 0:
                reg1_type = f"mipp::{register}<T, {lmul}>"
                reg2_type = f"mipp::{register}<{dt1}_t, {lmul}>"
                msk1_type = f"mipp::{mask}<T, {lmul}>"
                msk2_type = f"mipp::{mask}<{dt1}_t, {lmul}>"
            
            res += gen_cast_func(func, 
                            scalar1_type="T",
                            scalar2_type=dt1,
                            reg1_type=reg1_type,
                            reg2_type=reg2_type,
                            kind=kind,
                            msk1_type=msk1_type,
                            msk2_type=msk2_type,
                            lmul=lmul,
                            mkind=mkind,
            )
    elif kind == "obj" :
        res += ""
    return res

def gen_funcs_all_datatypes(func, kind="c", register="rvd", mask="rvm",lmul=0, mkind=""):
    """
    generate the test function(s) for 1 func, all datatypes, 1 layer.
    """

    res = ""
    datatypes = mipp_funcs[func]["datatypes"]

    if kind == "c":
        for dt in datatypes:
            reg_type =f"{register}_" + dt + "_t"
            msk_type = f"{mask}_" + dt + "_t"
            if lmul > 0:
                reg_type = f"{register}_" + dt + f"_m{lmul}_t"
                msk_type = f"{mask}_" + dt + f"_m{lmul}_t"
            res += gen_func(
                    func,
                    dt,
                    reg_type=reg_type,
                    kind=kind,
                    msk_type=msk_type,
                    lmul=lmul,
                    mkind=mkind,
                    
            )
    elif kind == "cpp":  # template so no need to loop over datatypes
        
        reg_type = f"mipp::{register}<T>"
        msk_type = f"mipp::{mask}<T>"
        
        if lmul > 0:
            reg_type = f"mipp::{register}<T, {lmul}>"
            msk_type = f"mipp::{mask}<T, {lmul}>"
      
        res += gen_func(
            func,
            "T",
            reg_type=reg_type,
            kind=kind,
            msk_type=msk_type,
            lmul=lmul,
            mkind=mkind,
        )
        
        # if func in set_float_workaround:
        #     res += gen_func(
        #         func,
        #         "T",
        #         reg_type=reg_type,
        #         kind=kind,
        #         msk_type=msk_type,
        #         float="float32",
        #         lmul=lmul,
        #         mkind=mkind,
        #     )
        #     res += gen_func(
        #         func,
        #         "T",
        #         reg_type=reg_type,
        #         kind=kind,
        #         msk_type=msk_type,
        #         float="float64",
        #         lmul=lmul,
        #         mkind=mkind,
        #     )
    elif kind == "obj":  # template so no need to loop over datatypes
        res += gen_func(
            func,
            "T",
            reg_type=f"mipp::{register}<T>",
            kind=kind,
            msk_type=f"mipp::{mask}<T>",
        )
    return res

def gen_file(func, kind="c", lmul=0, mkind=""):
    """
    generates the test file for 1 func, all datatypes, 1 layer.
    Calls gen_headers -> gen_funcs_all_datatypes -> gen_test_type_guards
    """
    layer_dict = get_gen_test_dict(kind)
    if lmul != 0 :
        layer_dict = get_gen_test_dict_lmul(kind)
    if mkind != "" :
        layer_dict = get_gen_test_dict_mask(kind)

    register = "rvd"
    mask = "rvm"

    if kind == "obj":
        register = register.capitalize()  # obj types are Rvd, Rvm instead of rvd, rvm
        mask = mask.capitalize()

    res = gen_funcs_all_datatypes(func, kind=kind, register=register, mask=mask, lmul=lmul, mkind=mkind)
    res += gen_test_type_guards(
        func,
        layer_dict[func]["long_name"],
        layer_dict[func]["short_name"],
        kind=kind,
        lmul=lmul,
        mkind=mkind,
    )
    return res

def gen_cast_file(func,kind="c", lmul=0, mkind=""):
    layer_dict = get_gen_test_dict(kind)
    if lmul != 0 :
        layer_dict = get_gen_test_dict_lmul(kind)
    if mkind != "" :
        layer_dict = get_gen_test_dict_mask(kind)

    register = "rvd"
    mask = "rvm"

    if kind == "obj":
        register = register.capitalize()  # obj types are Rvd, Rvm instead of rvd, rvm
        mask = mask.capitalize()

    res = gen_cast_funcs_all_datatypes(func, kind=kind, register=register, mask=mask, lmul=lmul, mkind=mkind)
    res += gen_cast_test_type_guards(
        func,
        layer_dict[func]["long_name"],
        layer_dict[func]["short_name"],
        kind=kind,
          lmul=lmul,
        mkind=mkind,
    )
    return res


tmp_path = "../tests/src/"
cpath = tmp_path + "c_tests/"
cpppath = tmp_path + "cpp_tests/"
objpath = tmp_path + "obj_tests/"

def write_file_if_different(path, content, encoding="utf-8"):
    """
    Write only if the on-disk bytes would differ from what we'd write.
    Returns True if wrote, False if unchanged.
    """
    p = Path(path)
    new_bytes = content.encode(encoding)

    try:
        old_bytes = p.read_bytes()
        #print(f"Comparing existing file: {p}")
        if old_bytes == new_bytes:
            return False
    except FileNotFoundError:
        #print(f"File not found (will create): {p}")
        pass

    p.parent.mkdir(parents=True, exist_ok=True)
    #print(f"Writing file: {p}")
    p.write_bytes(new_bytes)
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


def get_str_path(tmp_path, lmul=0, mkind=""):
    a = tmp_path + "c_tests/"
    b = tmp_path + "cpp_tests/"
    c = tmp_path + "obj_tests/"
    if mkind != "" :
        a += mkind + "/"
        b += mkind + "/"
        c += mkind + "/"
    if lmul != 0 :
        lmul_str = lmul_to_str(lmul, mkind)
        a += lmul_str + "/"
        b += lmul_str + "/"
        c += lmul_str + "/"
    return a, b, c


def clean_folder(folder_path):
    try:
        shutil.rmtree(folder_path)
        print(f"Successfully deleted folder: {folder_path}")
    except Exception as e:
        print(f"Failed to delete folder: {folder_path}. Reason: {e}")

#big and somewhat ugly "main" func to generate all test files for all funcs for the requested layer(s)
def gen_test_files_all_funcs(kind="c", lmul=0, mkind="", N=10):
    """
    kind: "c", "cpp", "obj", or "all"
    Regenerates only the requested layer(s) for all functions.

    Important: functions available can differ per layer, so we iterate over the
    union of keys from the enabled layer dictionaries.
    """
    if kind not in {"c", "cpp", "obj", "all"}:
        raise ValueError(f"Invalid kind: {kind}")
    
    # if lmul != 0 or mkind != "" :
    # if mkind != "" :
    # if lmul != 0 and mkind != "" :
    # if lmul != 0 :
    #    print("wip zone :)")
    #    return

    regen_c = kind in {"c", "all"}
    # regen_cpp = kind in {"cpp", "all"}
    # regen_obj = kind in {"obj", "all"}

    # disabled during rewrite of C layer stuff
    regen_cpp = kind in {"cpp", "all"}
    regen_obj = kind in {"obj", "all"}
    
    # WIP
    if lmul != 0 : 
        # regen_cpp = False
        regen_obj = False
    if mkind != "" :
        # regen_cpp = False
        regen_obj = False

    c_dict = get_gen_test_dict("c") if regen_c else {}
    cpp_dict = get_gen_test_dict("cpp") if regen_cpp else {}
    obj_dict = get_gen_test_dict("obj") if regen_obj else {}
    
    if lmul != 0:
        c_dict = get_gen_test_dict_lmul("c") if regen_c else {}
        cpp_dict = get_gen_test_dict_lmul("cpp") if regen_cpp else {}
        obj_dict = get_gen_test_dict_lmul("obj") if regen_obj else {}
        
    if mkind != "" :
        c_dict = get_gen_test_dict_mask("c") if regen_c else {}
        cpp_dict = get_gen_test_dict_mask("cpp") if regen_cpp else {}
        obj_dict = get_gen_test_dict_mask("obj") if regen_obj else {}

    funcs = set()
    if regen_c:
        funcs |= set(c_dict.keys())
    if regen_cpp:
        funcs |= set(cpp_dict.keys())
    if regen_obj:
        funcs |= set(obj_dict.keys())
        
        
        
    #if lmul != "" add it to the path to generate lmul specific tests in a separate folder
    cpath, cpppath, objpath = get_str_path(tmp_path, lmul=lmul, mkind=mkind)

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

    dict_mask = get_gen_test_dict_mask("c")
    print(dict_mask.keys())
    for func in sorted(funcs):
        
        
        mask_support = mipp_funcs[func]["mask_support"]
        if mkind != "" and not mask_support.is_supported(mkind) :
            print(f"Skipping {func} for {mkind} because it doesn't support it")
            continue
        
        disable = func in set_skip_testing
        reason = (
            f"{func} is in set_skip_testing. "
            "If it's blend it's because it's broken on AVX2; otherwise it's likely "
            "because get_k/set_k is used and doesn't work well on AVX2."
        )

        if regen_c and func in c_dict:
            if func == "cast" or func == "cast_k":
                c_file = gen_headers(kind="c",func=func, N=N, lmul=lmul, mkind=mkind) + gen_cast_file(func, kind="c",lmul=lmul, mkind=mkind)
            else:
                c_file = gen_headers(kind="c",func=func, N=N, lmul=lmul, mkind=mkind) + gen_file(func, kind="c",lmul=lmul, mkind=mkind)
            if disable:
                c_file = comment_out_cpp_file(c_file, reason)
            file_path = cpath + match_concept(func) + f"/test_c{func}.cpp"
            write_file_if_different(file_path, c_file)

        if regen_cpp and func in cpp_dict:
            if func == "cast" or func == "cast_k":
                cpp_file = gen_headers(kind="cpp", func=func,  lmul=lmul, mkind=mkind) + gen_cast_file(func, kind="cpp",lmul=lmul, mkind=mkind)
            else:
                cpp_file = gen_headers(kind="cpp", func=func,  lmul=lmul, mkind=mkind) + gen_file(func, kind="cpp",lmul=lmul, mkind=mkind)
                
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
    # add arg for number of iteration of random tests 
    parser.add_argument(
        "-N" "--num-iterations",
        type=int,
        default=10,
        help="Number of iterations for random tests (default: 10).",
    )
    # clean dir option default : false
    parser.add_argument(
        "--clean",
        action="store_true",
        help="Clean the test folders before generating new files (default: false).",
    )
    args = parser.parse_args()

    if args.clean:
        clean_folder(cpath)
        clean_folder(cpppath)
        clean_folder(objpath)

    for lmul in [0, 1, 2, 4, 8]:
        for mkind in ["", "mask", "maskz", "masks"]:
            gen_test_files_all_funcs(kind=args.kind, lmul=lmul, mkind=mkind, N=args.N__num_iterations)


if __name__ == "__main__":
    main()