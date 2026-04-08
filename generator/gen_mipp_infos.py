#!/usr/bin/env python3
import sys
import os
import shutil
import struct

path = os.getcwd()

sys.path.insert(1, path + "/helpers_headers/")
sys.path.insert(1, path + "/simd_ext/avx512/")
sys.path.insert(1, path + "/simd_ext/avx/")
sys.path.insert(1, path + "/simd_ext/sse/")
sys.path.insert(1, path + "/simd_ext/sve/")
sys.path.insert(1, path + "/simd_ext/rvv/")

from implem_sse import isa_sse, implems_sse
from implem_emu_sse import implems_emu_sse

from implem_avx import isa_avx, implems_avx
from implem_emu_avx import implems_emu_avx

from implem_avx512 import isa_avx512, implems_avx512
from implem_emu_avx512 import implems_emu_avx512

#from implem_sve import isa_sve
#from implem_emu_sve import implem_emu_sve

from implem_rvv import isa_rvv, implems_rvv
from implem_emu_rvv import implems_emu_rvv

from headers_def import mipp_funcs
from headers_def import all_datatypes, all_datatypes_cart_prod

from gen_mipp_sse import gen_mipp_sse
from gen_mipp_avx import gen_mipp_avx
from gen_mipp_avx512 import gen_mipp_avx512
from gen_mipp_sve import gen_mipp_sve
from gen_mipp_rvv import gen_mipp_rvv

include_gen_path = "../include/"

# avx and avx512 folder path
sse_path = os.path.join(include_gen_path, "sse")
avx_path = os.path.join(include_gen_path, "avx")
avx512_path = os.path.join(include_gen_path, "avx512")
sve_path = os.path.join(include_gen_path, "sve")
rvv_path = os.path.join(include_gen_path, "rvv")


implems_dict = {
    "sse" : { "implems" : [implems_sse, implems_emu_sse], "defines" : {}},
    "sse2" : { "implems" : [implems_sse, implems_emu_sse], "defines" : {"SSE2"}},
    "sse3" : { "implems" : [implems_sse, implems_emu_sse], "defines" : {"SSE2", "SSE3"}},
    "ssse3" : { "implems" : [implems_sse, implems_emu_sse], "defines" : {"SSE2", "SSE3", "SSSE3"}},
    "sse4_1" : { "implems" : [implems_sse, implems_emu_sse], "defines" : {"SSE2", "SSE3", "SSSE3", "SSE4_1"}},
    "sse4_2" : { "implems" : [implems_sse, implems_emu_sse], "defines" : {"SSE2", "SSE3", "SSSE3", "SSE4_1", "SSE4_2"}},
    "avx" : { "implems" : [implems_avx, implems_emu_avx], "defines": {"!defined(__AVX2__)"}},
    "avx2" : { "implems" : [implems_avx, implems_emu_avx], "defines": {"AVX2"}},
    "avx2_fma" : { "implems" : [implems_avx, implems_emu_avx], "defines": {"AVX2", "FMA"}},
    "avx512f" : { "implems" : [implems_avx512, implems_emu_avx512], "defines": {"AVX512F", "AVX512"}},
    "avx512_bw_bq" : { "implems" : [implems_avx512, implems_emu_avx512], "defines": {"AVX512BW", "AVX512F", "AVX512", "AVX512DQ"}},
    "avx512_kncni" : { "implems" : [implems_avx512, implems_emu_avx512], "defines" :{"KCNI", "MIC"}},
    "rvv1_0" : { "implems": [implems_rvv, implems_emu_rvv], "defines": {}},

    #"sve" { "implems" :[implems_sve, implem_emu_sve],"defines": {}},
    #"sve2" { "implems" :[implems_sve, implem_emu_sve], "defines": {}},
    #"neonv1" : { "implems" :[implems_neonv, implems_emu_neonv], "defines": {}},
    #"neonv2" : { "implems" :[implems_neonv, implems_emu_neonv], "defines": {}},
}

if_ignored_set = {
    "MIPP_ALIGNED_LOADS",
}


def element_in_str(set, str):
    for element in set:
        if element in str:
            return True
    for element in if_ignored_set:
        if element in str:
            return True
    return False

class FuncInfo:

    def __init__(self):
        self.func_name = None
        self.datatypes = []
        self.emulated = False
        
    def gen_infos(self, func, implems_isa, implems_emu_isa, dict_entry):
        ret = FuncInfo()
        if func in implems_isa:
            for implem in implems_isa[func]:
                
                if "if" in implem :
                    if element_in_str(implems_dict[dict_entry]["defines"], implem["if"]):
                        #print(dict_entry, func, implems_dict[dict_entry]["defines"], implem["if"])
                        ret.datatypes += implem["datatypes"]       
                else :

                    ret.datatypes += implem["datatypes"]
                
        if func in implems_emu_isa and ret.datatypes == []:
            for implem in implems_emu_isa[func]:
                if "if" in implems_emu_isa[func] :
                    if element_in_str(implems_dict[dict_entry]["defines"], implem["if"]):
                        ret.datatypes += implem["datatypes"]
                else :
                    ret.datatypes += implem["datatypes"]
                ret.emulated = True
        
        if func == "hadd" : 
            print(dict_entry, ret.datatypes, ret.emulated)
        if dict_entry == "rvv1_0" : 
            print(func, ret.datatypes, ret.emulated)
        self.func_name = func
        self.datatypes = ret.datatypes
        self.emulated = ret.emulated
        
class IsaInfo:
    
    def __init__(self): 
        self.isa_name = None
        self.func_infos = []
        
    def sort_func_infos(self):
        self.func_infos.sort(key=lambda x: x.func_name)
        
    
    def gen_isa_infos(self, isa, implems_isa, implems_emu_isa):
        for func in mipp_funcs:
            dict_entry = mipp_funcs[func]
            func_info = FuncInfo()
            func_info.gen_infos(func, implems_isa, implems_emu_isa, isa)
            if len(func_info.datatypes) > 0:
                self.func_infos.append(func_info)
        self.isa_name = isa
        self.sort_func_infos()
    
    def is_missing(self, func):
        for func_info in self.func_infos:
            if func_info.func_name == func:
                return False
        return True
    def get_func_info(self, func):
        for func_info in self.func_infos:
            if func_info.func_name == func:
                return func_info
        return None


class MippInfo:

    def __init__(self): 
        self.isa_infos = []

    def gen_mipp_infos(self, mipp_funcs ,implem_dict):
        isa_infos = IsaInfo()
        for isa in implem_dict:
            #print("Generating infos for " + isa)
            isa_info = IsaInfo()
            isa_info.gen_isa_infos(isa, implem_dict[isa]["implems"][0], implem_dict[isa]["implems"][1])
            self.isa_infos.append(isa_info)
        
    
    def write_mipp_infos(self, base_dir):
        write_mipp_infos(self, base_dir)


def write_mipp_infos(mipp_infos, base_dir):
    #for each isa write a md file with the list of functions and their supported types
    #we put functions in a table where x is dttype
    # y is function name,
    # we write ::material-check: if the function is emulated for the given ddtype

    
    # we write :material-check-all:  if the function is not emulated for the given dtype
    # we write :material-close: if the function is not supported for the given dtype
    
    #nb : we don't generate table entries for cast, cast_k
    
    # we also want the square to be green code : 28A745
    # if the function is native, orange code : FD7E14 if emulated 
    #and red : DC3545 if not supported.
    
    
    color_green ='<span style="color: #28A745; font-weight: 600;">'
    color_orange = '<span style="color: #FD7E14; font-weight: 600;">'
    color_red = '<span style="color: #DC3545; font-weight: 600;">'
    color_end = '</span>'
    
    for isa_info in mipp_infos.isa_infos:
        file_path = os.path.join(base_dir, isa_info.isa_name + ".md")
        with open(file_path, "w") as f:
            dttypes = all_datatypes
            print("| Function | " + " | ".join(dttypes) + " |", file=f)
            print("| --- | " + " | ".join(["---"]*len(dttypes)) + " |", file=f)
            for func in mipp_funcs:
                func_info = isa_info.get_func_info(func)
                if func_info is None:
                    #generate missing for all dttypes
                    if func in ["cast", "cast_k"]:
                        continue
                    print("| " + func + " | " + " | ".join([color_red+":material-close:" + color_end]*len(dttypes)) + " |", file=f)
                else : 
                    if func_info.func_name in ["cast", "cast_k"]:
                        continue
                    print("| " + func_info.func_name + " | ", end="", file=f)
                    for dtype in dttypes:
                        if dtype in func_info.datatypes:
                            if func_info.emulated:
                                print(color_orange+":material-check:" + color_end + " | ", end="", file=f)
                            else:
                                print(color_green+":material-check-all:" + color_end + " | ", end="", file=f)
                        else:
                            print(color_red+":material-close:" + color_end + " | ", end="", file=f)
                    print("", file=f)
            #special table for cast and cast_k because they operate on product of datatypes
            dttypes = all_datatypes_cart_prod
            print("\n\n| Function | " + " | ".join(dttypes) + " |", file=f)
            print("| --- | " + " | ".join(["---"]*len(dttypes)) + " |", file=f)
            for func in ["cast", "cast_k"]:
                func_info = isa_info.get_func_info(func)
                if func_info is None:
                    #generate missing for all dttypes
                    print("| " + func + " | " + " | ".join([color_red+":material-close:" + color_end]*len(dttypes)) + " |", file=f)
                else : 
                    print("| " + func_info.func_name + " | ", end="", file=f)
                    for dtype in dttypes:
                        if dtype in func_info.datatypes:
                            if func_info.emulated:
                                print(color_orange+":material-check:" + color_end + " | ", end="", file=f)
                            else:
                                print(color_green+":material-check-all:" + color_end + " | ", end="", file=f)
                        else:
                            print(color_red+":material-close:" + color_end + " | ", end="", file=f)
                    print("", file=f)
def main():
    print("Generate MIPP infos")
    mipp_infos = MippInfo()
    mipp_infos.gen_mipp_infos(mipp_funcs, implems_dict)
    
    if not os.path.exists("../docs/isas_support/"):
        os.makedirs("../docs/isas_support/")
    write_mipp_infos(mipp_infos, "../docs/isas_support/")
    
            

if __name__ == "__main__":
    main()
    
