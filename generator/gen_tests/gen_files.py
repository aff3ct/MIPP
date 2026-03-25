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

#helper to get the datatypes for 1 func in 1 implem
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

#add the type guard for 1 func in 1 implem
def add_type_guards(func, implem, function,kind="c"):
    """
    func: implem key, e.g. "add", "mul", ...
    implem: dict of the implem, e.g. implems_avx512
    function: part of the name of the fn to call. Should prolly be changed 
    kind: "c" for c test, "cpp" for cpp test, "obj" for obj test
    
    returns a string with the type guards for the func in the implem
    """
    datatypes = get_defined_dttypes(func, implem)
    section = ''
    res = ""
    if kind == "c":
        section = 'SECTION ("datatype = {dt}") {{ {function}_{dt}(); }}\n'
    elif kind == "cpp" or kind == "obj":
        section = 'SECTION ("datatype = {dt}") {{ {function}<{dt}_t>(); }}\n'

    list_64 = []
    list_bw = []
    for dt in datatypes:
        print(dt)
        if dt in ["int64", "uint64", "float64"]:
            list_64.append(dt)
        elif dt in ["int8", "uint8", "int16", "uint16"]:
            list_bw.append(dt)
        else:
            res += section.format(dt=dt, function=function)
    
    if list_64 != []:
        res += f'#if defined(MIPP_64BIT)\n'
        for dt in list_64:
            res += section.format(dt=dt, function=function)
        res += "#endif\n"
    
    if list_bw != []:
        res += f'#if defined(MIPP_BW)\n'
        for dt in list_bw:
            res += section.format(dt=dt, function=function)
        res += "#endif\n"
    
    return res

def gen_test_type_guards(func, long_name, short_name, kind="c"):
    res = f'\nTEST_CASE("{long_name} - {kind}", "[{short_name}]") {{\n'
    for implems in implem_dict.values():
        if func in implems["implem"]:
            res += implems["guard"] + "\n"
            if kind == "c":
                res += add_type_guards(func, implems["implem"], function=f'test_cmipp_{func}', kind=kind)
            elif kind == "cpp":
                res += add_type_guards(func, implems["implem"], function=f'test_cppmipp_{func}', kind=kind)
            elif kind == "obj":
                res += add_type_guards(func, implems["implem"], function=f'test_objmipp_{func}', kind=kind)
    res += "#else\n"
    res += f'#error "No implementation for {func} in any of the supported architectures"\n'
    res += "#endif\n"
    res += "}\n"
    return res


#TODO : for C compatibiliy, use 
#math.h stdio.h etc instead of cmath, cstdio, etc.
def gen_headers(kind="c"):
    """
    simple helper to return headers for the test files
    """
    res = f'#include <exception>\
            \n#include <algorithm>\
            \n#include <numeric>\
            \n#include <random>\
            \n#include <cstdio>\
            \n#include <cmath>'
    if kind == "c":
        res += '\n#include <mipp.h>'
    elif kind == "cpp":
        res += '\n#include <mipp.hpp>'
    elif kind == "obj":
        res += '\n#include <mipp_obj.hpp>'
    res += '\n#include <catch2/catch_test_macros.hpp>\n\n'
    return res

def gen_func(func, scalar_type, reg_type,kind="c"):
    #we need to render twice because we have 2 levels of templates :)
    func_dict = gen_test_dict[func]["protos"][kind]
    func_template = gen_test_dict[func]["template"]
    func_template = Template(func_template, undefined=StrictUndefined)
    res = func_template.render( func_declaration=func_dict["tpl_func_declaration"],
                                declaration=func_dict["tpl_body_declaration"],
                                init=func_dict["tpl_body_initialization"],
                                load=func_dict["tpl_body_load"],
                                operation=func_dict["tpl_body_operation"],
                                loop_body=func_dict["tpl_body_loop_body"],
                                loop_assert=func_dict["tpl_body_loop_assert"])
    
    func_template = Template(res, undefined=StrictUndefined)
    res = func_template.render(func=func, dt_ext=scalar_type, op=gen_test_dict[func]["op"], 
                               reg_type=reg_type,
                                size="MIPP_N_" + scalar_type.upper())
#Warning : this doesn't pose "portability" issues bc cpp/obj don't use the size argument. 
#but it's unelegant
    return res+"\n"

def gen_funcs_all_datatypes(func, kind="c"):
    res = ""
    datatypes = mipp_funcs[func]["datatypes"]
    if kind == "c":
        for dt in datatypes:
            res += gen_func(func, dt, reg_type="rvd_"+dt+"_t", kind=kind)
    elif kind == "cpp":#template so no need to loop over datatypes
        res += gen_func(func, "T", reg_type="mipp::rvd<T>", kind=kind)
    elif kind == "obj":#template so no need to loop over datatypes
        res += gen_func(func, "T", reg_type="mipp::Rvd<T>", kind=kind)
    return res

def gen_file(func,kind="c"):
    res = gen_funcs_all_datatypes(func,kind=kind)
    res += gen_test_type_guards(func, gen_test_dict[func]["long_name"], gen_test_dict[func]["short_name"],kind=kind)
    
    #template = Template(res, undefined=StrictUndefined)
    
    return res

tmp_path = "test_files/"
cpath = tmp_path + "c_tests/"
cpppath = tmp_path + "cpp_tests/"
objpath = tmp_path + "obj_tests/"
#we want to generate 3 files for each func : c test, cpp test and obj test.
def gen_test_files_all_funcs():
    for func in gen_test_dict.keys():
        c_file = gen_file(func, kind="c")
        cpp_file = gen_file(func, kind="cpp")
        obj_file = gen_file(func, kind="obj")
        
        #mkdir if not exists
        os.makedirs(cpath, exist_ok=True)
        os.makedirs(cpppath, exist_ok=True)
        os.makedirs(objpath, exist_ok=True)
        
        with open(cpath + f'test_{func}.c', 'w') as f:
            f.write(gen_headers(kind="c"))
            f.write(c_file)
        
        with open(cpppath + f'test_{func}.cpp', 'w') as f:
            f.write(gen_headers(kind="cpp"))
            f.write(cpp_file)
        
        with open(objpath + f'test_{func}.cpp', 'w') as f:
            f.write(gen_headers(kind="obj"))
            f.write(obj_file)
            
gen_test_files_all_funcs()