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

avx512_guard = "#if defined(MIPP_AVX512)"
avx2_guard = "#elif defined(MIPP_AVX2)"
avx_guard = "#elif defined(MIPP_AVX)"
sse_guard = "#elif defined(MIPP_SSE)"
#for some reason MIPP_SVE isnt defined idk
sve_guard = "#elif defined(__ARM_FEATURE_SVE)"
rvv_guard = "#elif defined(MIPP_RVV)"


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


#oops I forgot to do that at first
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

#add the type guard for 1 func in 1 implem
def add_type_guards(func, implem, function):
    func_dt = implem[func]
    datatypes = []
    for dt in func_dt:
            datatypes.append(dt["datatypes"])
    datatypes = list(set([item for sublist in datatypes for item in sublist]))

    ret = ""  
    for dt in datatypes:
        #function is a placeholder atm. I expect the jinja template to be more complex
        #but this is just to test things
        ret += f'SECTION ("datatype = {dt}") {{ {function}_{dt}(); }}\n' 
    return ret
        

#generate type guards for 1 func in all implems
#this isn't very elegant, we could "factorise" common guards ig
def gen_c_test_type_guards(func):
    res = ""
    for implems in implem_dict.values():
        if func in implems["implem"]:
            res += implems["guard"] + "\n"
            res += add_type_guards(func, implems["implem"], function=f'test_{func}')

    res += "#else\n"
    res += f'#error "No implementation for {func} in any of the supported architectures"\n'
    res += "#endif\n"
    return res

def gen_c_headers():
    return f'#include <exception>\
            \n#include <algorithm>\
            \n#include <numeric>\
            \n#include <random.h>\
            \n#include <math.h>\
            \n#include <mipp.h>\
            \n#include <catch2/catch_test_macros.hpp>\n'


def gen_c_func(func, scalar_type, reg_type_prefix="rvd", reg_type_suffix=""):
    res = f'void test_{func}_{scalar_type}() {{\n' + bodies_dict[func] + '}\n'
    template = Template(res, undefined=StrictUndefined)
    
    reg_type = reg_type_prefix + "_" + type + reg_type_suffix + "_t"
    size = "MIPP_N_" + type.upper()
    res = template.render(func=func, dt_ext=type, reg_type=reg_type, size=size, type=scalar_type)
    
    return res+"\n"

def gen_c_funcs_all_datatypes(func):
    res = ""
    for type in all_datatypes:
        res += gen_c_func(func, scalar_type=type)
    return res


def gen_c_file(func):
    res = gen_c_headers()
    res += gen_c_funcs_all_datatypes(func)
    res += gen_c_test_type_guards(func)
    
    #template = Template(res, undefined=StrictUndefined)
    
    return res
#gen_c_file("add")

tmp_path = "test_files/"
def gen_c_files_all_funcs():
    #mkdir
    if not os.path.exists(tmp_path):
        os.makedirs(tmp_path)
    for func in bodies_dict.keys():
        with open(f"{tmp_path}test_{func}.cpp", "w") as f:
            f.write(gen_c_file(func))
            
gen_c_files_all_funcs()