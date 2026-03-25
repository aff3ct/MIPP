import os
import sys
from jinja2 import Template, StrictUndefined

path = os.getcwd()

sys.path.insert(1,path +'/../simd_ext/avx512/')
sys.path.insert(1,path + '/../simd_ext/avx/')
sys.path.insert(1,path + '/../simd_ext/sse/')
sys.path.insert(1,path + '/../simd_ext/sve/')
sys.path.insert(1,path + '/../simd_ext/rvv/')
sys.path.insert(1,path + '/../')

from implem_sse import implems_sse
from implem_avx import implems_avx
from implem_avx512 import implems_avx512
from implem_sve import implems_sve
from implem_rvv import implems_rvv
from headers_def import mipp_funcs
from tools import *
from test_tools import *

from implem_emu_sse import implems_emu_sse
from implem_emu_avx import implems_emu_avx
from implem_emu_avx512 import implems_emu_avx512
from implem_emu_sve import implems_emu_sve
from implem_emu_rvv import implems_emu_rvv


avx512_guard = "#if defined(MIPP_AVX512)"
avx2_guard = "#elif defined(MIPP_AVX2)"
avx_guard = "#elif defined(MIPP_AVX)"
sse_guard = "#elif defined(MIPP_SSE)"
#for some reason MIPP_SVE isnt defined idk
sve_guard = "#elif defined(__ARM_FEATURE_SVE)"
rvv_guard = "#elif defined(MIPP_RVV)"

implems_avx512.update(implems_emu_avx512)
implems_avx.update(implems_emu_avx)
implems_sse.update(implems_emu_sse)
implems_sve.update(implems_emu_sve)
implems_rvv.update(implems_emu_rvv)

implem_dict = {
    #avx512 has to be first bc it's the one w the #if
    "avx512": {"implem": implems_avx512 ,"guard": avx512_guard},
    "avx": {"implem": implems_avx, "guard": avx_guard},
    "sse": {"implem": implems_sse, "guard": sse_guard},
    "sve": {"implem": implems_sve, "guard": sve_guard},
    "rvv": {"implem": implems_rvv, "guard": rvv_guard}
}

def get_defined_dttypes(func, implem):
    func_dt = implem[func]
    datatypes = []
    for dt in func_dt:
            datatypes.append(dt["datatypes"])
    datatypes = list(set([item for sublist in datatypes for item in sublist]))
    return datatypes

#add the type guard for 1 func in 1 implem
#TODO : more generic to support c and cpp tests
def add_type_guards(func, implem, function):
    datatypes = get_defined_dttypes(func, implem)
    print(f"{func} is implemented for datatypes : {datatypes}")
    ret = ""  
    for dt in datatypes:
        #function is a placeholder atm. I expect the jinja template to be more complex
        #but this is just to test things
        ret += f'SECTION ("datatype = {dt}") {{ {function}_{dt}(); }}\n' 
    return ret
        

#generate type guards for 1 func in all implems
#this isn't very elegant, we could "factorise" common guards ig
def gen_test_type_guards(func, long_name, short_name, kind="c"):
    res = f'\nTEST_CASE("{long_name} - placeholer", "[{short_name}]") {{\n'
    for implems in implem_dict.values():
        if func in implems["implem"]:
            res += implems["guard"] + "\n"
            res += add_type_guards(func, implems["implem"], function=f'test_cmipp_{func}')

    res += "#else\n"
    res += f'#error "No implementation for {func} in any of the supported architectures"\n'
    res += "#endif\n"
    res += "}\n"
    return res

def gen_c_headers():
    return f'#include <exception>\
            \n#include <algorithm>\
            \n#include <numeric>\
            \n//#include <random.h>\
            \n#include <stdio.h>\
            \n#include <math.h>\
            \n#include <mipp.h>\
            \n#include <catch2/catch_test_macros.hpp>\n'

def gen_cpp_headers():
    return f'#include <exception>\
            \n#include <algorithm>\
            \n#include <numeric>\
            \n#include <random>\
            \n#include <cstdio>\
            \n#include <cmath>\
            \n#include <mipp.hpp>\
            \n#include <catch2/catch_test_macros.hpp>\n'

def gen_obj_headers():
    return f'#include <exception>\
            \n#include <algorithm>\
            \n#include <numeric>\
            \n#include <random>\
            \n#include <cstdio>\
            \n#include <cmath>\
            \n#include <mipp_obj.hpp>\
            \n#include <catch2/catch_test_macros.hpp>\n'


def gen_c_func(func, scalar_type, reg_type_prefix="rvd", reg_type_suffix=""):
    #we need to render twice because we have 2 levels of templates
    func_dict = gen_test_dict[func]
    func_template = func_dict["template"]
    func_template = Template(func_template, undefined=StrictUndefined)
    res = func_template.render( func_declaration=func_dict["tpl_func_declaration"],
                                declaration=func_dict["tpl_body_declaration"],
                                init=func_dict["tpl_body_initialization"],
                                load=func_dict["tpl_body_load"],
                                operation=func_dict["tpl_body_operation"],
                                loop_body=func_dict["tpl_body_loop_body"],
                                loop_assert=func_dict["tpl_body_loop_assert"])
    
    func_template = Template(res, undefined=StrictUndefined)
    #print(res)
    res = func_template.render(func=func, dt_ext=scalar_type, op=func_dict["op"], 
                               reg_type=reg_type_prefix + "_" + scalar_type + "_t" + reg_type_suffix,
                               size="MIPP_N_" + scalar_type.upper())
    return res+"\n"

def gen_funcs_all_datatypes(func, kind="c"):
    res = ""
    datatypes = mipp_funcs[func]["datatypes"]
    for type in datatypes:
        if kind == "c":
            res += gen_c_func(func, scalar_type=type)
        elif kind == "cpp":
            res += gen_cpp_func(func, scalar_type=type)
        elif kind == "obj":
            res += gen_obj_func(func, scalar_type=type)
    return res


def gen_c_file(func):
    res = gen_c_headers()
    res += gen_funcs_all_datatypes(func)
    res += gen_test_type_guards(func, gen_test_dict[func]["long_name"], gen_test_dict[func]["short_name"])
    
    #template = Template(res, undefined=StrictUndefined)
    
    return res
#gen_c_file("add")

def gen_cpp_file(func):
    res = gen_cpp_headers()
    res += gen_cpp_funcs_all_datatypes(func)
    res += gen_cpp_test_type_guards(func, gen_test_dict[func]["long_name"], gen_test_dict[func]["short_name"])
    
    #template = Template(res, undefined=StrictUndefined)
    
    return res

tmp_path = "test_files/"
def gen_c_files_all_funcs():
    #mkdir
    if not os.path.exists(tmp_path):
        os.makedirs(tmp_path)
    for func in gen_test_dict.keys():
        file_name = tmp_path + func + "_test.cpp"
        with open(file_name, "w") as f:
            f.write(gen_c_file(func))
            
gen_c_files_all_funcs()