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

from headers_def import mipp_funcs, mipp_funcs_concepts
from headers_def import all_datatypes, all_datatypes_cart_prod
from tools import *

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
        
    def get_intersection(self):
        #creates an IsaInfo with the intersection of all isa_infos
        #i.e only the functions AND dttypes that are supported by all isa_infos
        #If a function is emulated in one isa and native in another, we consider it as emulated in the intersection
        intersection = IsaInfo()
        intersection.isa_name = "intersection"
        for func in mipp_funcs:
            func_info = FuncInfo()
            func_info.func_name = func
            if func == "cast" or func == "cast_k":
                func_info.datatypes = all_datatypes_cart_prod
            else :
                func_info.datatypes = all_datatypes
            func_info.emulated = False
            #check if func is mising in any isa, if it is we skip it
            missing = False
            for isa_info in self.isa_infos:
                if isa_info.is_missing(func):
                    missing = True
                    break
            if missing:
                continue
            #remove datatypes in func_info that are not supported by isa_info
            for isa_info in self.isa_infos:
                isa_func_info = isa_info.get_func_info(func)
                if isa_func_info is not None:
                    func_info.datatypes = list(set(func_info.datatypes) & set(isa_func_info.datatypes))
                    if isa_func_info.emulated:
                        func_info.emulated = True
            #add func_info to intersection
            intersection.func_infos.append(func_info)
        return intersection


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


def match_args_type_cpp(arg_type, cast=False, ret=False):
    if arg_type == "msk":
        if cast:
            if ret:
                return "rvm<T2>"
            else : 
                return "rvm<T1>"
        else :
            return "rvm<T>"
    elif arg_type == "reg":
        if cast:
            if ret :
                return "rvd<T2>"
            else :
                return "rvd<T1>"
        else : 
            return "rvd<T>"
    elif arg_type == "val" :
        return "T"
    elif arg_type == "ptr":
        return "T*"
    else:
        return "int32_t"

def match_args_type_c(arg_type, cast=False, ret=False):
    if arg_type == "msk":
        if cast:
            if ret:
                return "rvm_{type 2}_t"
            else : 
                return "rvm_{type 1}_t"
        else :
            return "rvm_{type}_t"
    elif arg_type == "reg":
        if cast:
            if ret :
                return "rvd_{type 2}_t"
            else :
                return "rvd_{type 1}_t"
        else : 
            return "rvd_{type}_t"
    elif arg_type == "val" :
        return "{type}_t"
    elif arg_type == "ptr":
        return "{type}_t*"
    else:
        return "int32_t"

class SpecFuncInfo:
    
    def __init__(self):
        self.args = []
        self.ret = None
        self.dttypes = []
        self.concept = None
    
    def gen_spec_func_info(self, func, mipp_funcs, mipp_funcs_concepts):
        self.func_name = func
        self.args = mipp_funcs[func]["proto"]["args"]
        self.ret = mipp_funcs[func]["proto"]["ret"]
        self.dttypes = mipp_funcs[func]["datatypes"]
        
        self.concept = "miscellaneous"
        for concept in mipp_funcs_concepts:
            if concept == "a_trier": 
                continue
            if func in mipp_funcs_concepts[concept]:
                self.concept = concept
                break
            
    def func_to_str_cpp(self, mipp_funcs):
        #lambda to match reg -> rvd 
        #mask -> rvm 
        # val -> T
        cast = False
        ret = False
        if self.func_name in ["cast", "cast_k"]:
            cast = True
        args_str = ", ".join([match_args_type_cpp(arg["type"], cast, ret) for arg in self.args])
        ret_str = match_args_type_cpp(self.ret["type"], cast, True)
        ret_str = "inline " + ret_str
        func_proto_str = " " + ret_str + " " + self.func_name + "(" + args_str + ")"
        return func_proto_str
    
    def func_to_str_c(self, mipp_funcs):
        cast = False
        ret = False
        if self.func_name in ["cast", "cast_k"]:
            cast = True
        ret = ""
        args_str = ", ".join([match_args_type_c(arg["type"],cast,ret) for arg in self.args])
        ret_str = match_args_type_c(self.ret["type"], cast, True)
        ret_str = "inline " + ret_str
        if cast :
            func_proto_str = " " + ret_str + " " + self.func_name + "_{type 1}_{type 2}" + "(" + args_str + ")"
        else :
            func_proto_str = " " + ret_str + " " + self.func_name + "_{type}" + "(" + args_str + ")"
        for dt in self.dttypes:
            if cast:
                dt_par = dt.split(',')[0]
                dt_ret = dt.split(',')[1]
                func_proto_str_dt = func_proto_str.replace("{type 1}", dt_par).replace("{type 2}", dt_ret)
                ret += func_proto_str_dt + ";\n"
            else :
                ret += func_proto_str.format(type=dt) + ";\n"
        return ret
        
    
        
        
    def write_spec_func_info(self, base_dir):
        #path is base_dire + concept + "/" + func_name + ".md
        file_path = os.path.join(base_dir, self.concept, self.func_name + ".md")
        os.makedirs(os.path.dirname(file_path), exist_ok=True)
        with open(file_path, "w") as f:
            print("## Prototype", file=f)
            print("### CPP : \n", file=f)
            print("```", file=f)
            print(self.func_to_str_cpp(mipp_funcs), file=f)
            print("```", file=f)
            
            #print("\n\n```c", file=f)
            #print(self.func_to_str_c(mipp_funcs), file=f)
            #print("```", file=f)
            print("\n\n### C", file=f)
            cstr = self.func_to_str_c(mipp_funcs)
            cstr = cstr.replace("\n", "```\n\n```")
            #remove last ```
            cstr = cstr[:-4]
            cstr = "```" + cstr
            print("\n\n" + cstr, file=f)
            
            print("\n\n## Supported datatypes", file=f)
            for dtype in self.dttypes:
                print("- " + dtype, file=f)
       
class SpecFuncInfos:
    
    def __init__(self):
        self.spec_func_infos = []
    
    def gen_spec_func_infos(self, mipp_funcs, mipp_funcs_concepts):
        for func in mipp_funcs:
            spec_func_info = SpecFuncInfo()
            spec_func_info.gen_spec_func_info(func, mipp_funcs, mipp_funcs_concepts)
            self.spec_func_infos.append(spec_func_info)
    
    def write_spec_func_infos(self, base_dir):
        for spec_func_info in self.spec_func_infos:
            spec_func_info.write_spec_func_info(base_dir)
  
def main():
    print("Generate MIPP infos")
    mipp_infos = MippInfo()
    mipp_infos.gen_mipp_infos(mipp_funcs, implems_dict)
    
    #write each isa info in a md file in ../docs/isas_support/
    if not os.path.exists("../docs/isas_support/"):
        os.makedirs("../docs/isas_support/")
    write_mipp_infos(mipp_infos, "../docs/isas_support/")
    
    intersection = mipp_infos.get_intersection()
    int_mipp_infos = MippInfo()
    int_mipp_infos.isa_infos.append(intersection)
    write_mipp_infos(int_mipp_infos, "../docs/isas_support/")
    #write intersection info in a md file in ../docs/isas_support/intersection.md
    
    #write each func prototype in a md file in ../docs/funcs_support/
    if not os.path.exists("../docs/funcs_support/"):
        os.makedirs("../docs/funcs_support/")
    
    spec_func_infos = SpecFuncInfos()
    spec_func_infos.gen_spec_func_infos(mipp_funcs, mipp_funcs_concepts)
    spec_func_infos.write_spec_func_infos("../docs/funcs_support/")
    
if __name__ == "__main__":
    main()
    
