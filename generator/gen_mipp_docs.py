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
sys.path.insert(1, path + "/simd_ext/neon/")

from implem_sse import isa_sse, implems_sse
from implem_emu_sse import implems_emu_sse

from implem_avx import isa_avx, implems_avx
from implem_emu_avx import implems_emu_avx

from implem_avx512 import isa_avx512, implems_avx512
from implem_emu_avx512 import implems_emu_avx512

from implem_rvv import isa_rvv, implems_rvv
from implem_emu_rvv import implems_emu_rvv

from implem_neon import isa_neon, implems_neon
from implem_emu_neon import implems_emu_neon

#from implem_sve import isa_sve
#from implem_emu_sve import implem_emu_sve

from headers_def import mipp_funcs, mipp_funcs_concepts
from headers_def import all_datatypes, all_datatypes_cart_prod
from tools import *
from generic_emu import *

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
neon_path = os.path.join(include_gen_path, "neon")


implems_dict = {
    "SSE" : { "implems" : [implems_sse, implems_emu_sse], "defines" : {}},
    "SSE2" : { "implems" : [implems_sse, implems_emu_sse], "defines" : {"SSE2"}},
    "SSE3" : { "implems" : [implems_sse, implems_emu_sse], "defines" : {"SSE2", "SSE3"}},
    "SSSE3" : { "implems" : [implems_sse, implems_emu_sse], "defines" : {"SSE2", "SSE3", "SSSE3"}},
    "SSE4.1" : { "implems" : [implems_sse, implems_emu_sse], "defines" : {"SSE2", "SSE3", "SSSE3", "SSE4_1"}},
    "SSE4.2" : { "implems" : [implems_sse, implems_emu_sse], "defines" : {"SSE2", "SSE3", "SSSE3", "SSE4_1", "SSE4_2"}},
    "AVX" : { "implems" : [implems_avx, implems_emu_avx], "defines": {"!defined(__AVX2__)"}},
    "AVX2" : { "implems" : [implems_avx, implems_emu_avx], "defines": {"AVX2"}},
    "AVX2_FMA" : { "implems" : [implems_avx, implems_emu_avx], "defines": {"AVX2", "FMA"}},
    "AVX512F" : { "implems" : [implems_avx512, implems_emu_avx512], "defines": {"AVX512F", "AVX512"}},
    "AVX512_BW_BQ" : { "implems" : [implems_avx512, implems_emu_avx512], "defines": {"AVX512BW", "AVX512F", "AVX512", "AVX512DQ"}},
    "AVX512_KCNI" : { "implems" : [implems_avx512, implems_emu_avx512], "defines" :{"KCNI", "MIC"}},
    "RVV1.0" : { "implems": [implems_rvv, implems_emu_rvv], "defines": {}},
    "NEONv1" : { "implems" :[implems_neon, implems_emu_neon], "defines": {}},
    "NEONv2" : { "implems" :[implems_neon, implems_emu_neon], "defines": {"__aarch64__"}},
    #"sve" { "implems" :[implems_sve, implem_emu_sve],"defines": {}},
    #"sve2" { "implems" :[implems_sve, implem_emu_sve], "defines": {}},
}

#used to generate intersection
implems_dict_small = implems_dict.copy()
implems_dict_small.pop("SSE")
implems_dict_small.pop("SSE2")
implems_dict_small.pop("SSE3")
implems_dict_small.pop("SSSE3")
implems_dict_small.pop("SSE4.1")
implems_dict_small.pop("AVX")
implems_dict_small.pop("AVX2")
implems_dict_small.pop("AVX512F")
implems_dict_small.pop("AVX512_KCNI")
implems_dict_small.pop("NEONv1")


mipp_funcs_description = {
    "cast":   "Casts the elements of a register to another type. N.B : NOT A CONVERSION BUT A BITWISE CAST.",
	"cast_k":  "Casts the elements of a mask register to another type. N.B : NOT A CONVERSION BUT A BITWISE CAST.",
	"toreg":  "Converts a mask register to a vector register. Values in the register are 0 if the bit is not set and 0xFF..FF if the bit is set.",
	"tomsk":  "Converts a vector register to a mask register. The bit is set if the value in the register is not zero and not set if the value in the register is zero.",
	"load":   "Loads aligned data from a pointer to a register.",
	"loadu":  "Loads unaligned data from a pointer to a register.",
	"store":  "Stores the register in aligned data.",
	"storeu": "Stores the register in unaligned data.",
	"set" :   "Sets a registers to the values in an array.",
	"set_k" : "Sets a mask register to the values in an array.",
	"set1":   "Broadcasts a value to all elements of a register.",
	"set1_k": "Broadcasts a value to all elements of a mask register.",
	"maskzld":"Load elements from memory when the corresponding bit in the mask register is set, zeroing the other elements.",
	"maskst": "Store elements to memory when the corresponding bit in the mask register is set, not modifying the other elements in memory.",
	"set0":   "Broadcasts zero to all elements of a register.",
	#"low_k":  "",
	"get":     "Gets the value of a register at a given index.",
	"get_k":   "Gets the value of a mask register at a given index.",
	"getfirst":"Gets the value of the first lane of a register.",
	#"gather"  :"",
	#"mask_gather": "",
	"sqrt":   "Computes the square root of each element of a register.",
	"rsqrt":  "Computes the reciprocal of the square root of each element of a register.",
	"add":    "Adds two vector registers.",
	"sub":    "Subtracts two vector registers.",
	"mul":    "Multiplies two vector registers.",
	"div":    "Divides two vector registers.",
	"min":    "Computes the minimum of two vector registers.",
	"max":    "Computes the maximum of two vector registers.",
	"fmadd":  "Computes the fused multiply-add of three vector registers.",
	"fmsub":  "Computes the fused multiply-subtract of three vector registers.",
	"andb":   "Computes the bitwise AND of two registers.",
	"andb_k": "Computes the bitwise AND of two mask registers.",
	"andnb":  "Computes the bitwise AND NOT of two registers.",
	"andnb_k":"Computes the bitwise AND NOT of two mask registers.",
	"orb":    "Computes the bitwise OR of two registers.",
	"orb_k":  "Computes the bitwise OR of two mask registers.",
	"xorb":   "Computes the bitwise XOR of two registers.",
	"xorb_k": "Computes the bitwise XOR of two mask registers.",
	"msb":    "returns a register where every bit but the msb is masked out, the msb is the same as the msb of the input register.",
	"notb":   "Computes the bitwise NOT of a register.",
	"notb_k": "Computes the bitwise NOT of a mask register.",
	"cmpeq":  "Computes the lanes of two registers for equality returns a mask register with the bit set if the comparison is true and not set if the comparison is false.",
	"cmpneq": "Computes the lanes of two registers for inequality returns a mask register with the bit set if the comparison is true and not set if the comparison is false.",
    "cmplt":  "Computes the lanes of two registers for less than returns a mask register with the bit set if the comparison is true and not set if the comparison is false.",
	"cmple":  "Computes the lanes of two registers for less than or equal returns a mask register with the bit set if the comparison is true and not set if the comparison is false.",
	"cmpge":  "Computes the lanes of two registers for greater than or equal returns a mask register with the bit set if the comparison is true and not set if the comparison is false.",
	"cmpgt":  "Computes the lanes of two registers for greater than returns a mask register with the bit set if the comparison is true and not set if the comparison is false.",
	"round":  "Rounds the elements of a register to the nearest integer.",
	"blend":  "Blends two registers according to a mask register. Follows the pattern of the ternary operator ret[i] = (msk[i] ? rvd1[i] : rvd2[i]).",
	"set0_k": "Broadcasts zero to all elements of a mask register.",
	"testz":   "Tests if the bitwise AND of two registers is zero.",
	"testz_2": "Test if every element of a register is zero.",
	"hadd":    "Computes the reduction sum of the elements of a register.",
	"hmul":    "Computes the reduction product of the elements of a register.",
	"hmin":    "Computes the reduction minimum of the elements of a register.",
	"hmax":    "Computes the reduction maximum of the elements of a register.",
	"hadd_to_scal":    "Computes the reduction sum of the elements of a register and returns it as a scalar.",
	#"hmul_to_scal":    "",
	#"hmin_to_scal":    "",
	#"hmax_to_scal":    "",
	"maskz_add": "Adds two vector registers according to a mask register. Follows the pattern of the ternary operator ret[i] = (msk[i] ? rvd1[i] + rvd2[i] : 0).",
    "fnmadd" : "Computes the fused negative multiply-add of three vector registers. Computes -(a*b)+c for each element of the registers.",
    "fnmsub" : "Computes the fused negative multiply-subtract of three vector registers. Computes -(a*b)-c for each element of the registers.",
}


dict_datatypes_short = {
    "int8" : "i8",
    "int16" : "i16",
    "int32" : "i32",
    "int64" : "i64",
    "uint8" : "u8",
    "uint16" : "u16",
    "uint32" : "u32",
    "uint64" : "u64",
    "float32" : "f32",
    "float64" : "f64",
}

all_datatypes_short = [dict_datatypes_short[dt] for dt in all_datatypes]
all_datatypes_short_cart_prod = []
for dt1 in all_datatypes:
    for dt2 in all_datatypes:
        all_datatypes_short_cart_prod.append(dict_datatypes_short[dt1] + "," + dict_datatypes_short[dt2])

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
        self.emulated = {}
        self.generic = {}
        
    #this method is wrong.
    #each datatype can have different emulations/generic values...
    def gen_infos(self, func, implems_isa, implems_emu_isa, dict_entry):
        ret = FuncInfo()
        if func in implems_isa:
            for implem in implems_isa[func]:
                
                if "if" in implem :
                    if element_in_str(implems_dict[dict_entry]["defines"], implem["if"]):
                        ret.add_datatypes(implem["datatypes"],False,False)
                            
                else :
                    ret.add_datatypes(implem["datatypes"],False,False)
        #ret.datatypes == [] allows to check if the function has already been implemented natively before checking emulated implementations  
        if func in implems_emu_isa :
            for implem in implems_emu_isa[func]:
                if "if" in implems_emu_isa[func] :
                    if element_in_str(implems_dict[dict_entry]["defines"], implem["if"]):
                        ret.add_datatypes(implem["datatypes"],True,False)

                else :
                    ret.add_datatypes(implem["datatypes"],True,False)

        if func in implems_generic_emu :
            for implem in implems_generic_emu[func]: 
                ret.add_datatypes(implem["datatypes"],False,True)

                
        
        self.func_name = func
        self.datatypes = ret.datatypes
        self.emulated = ret.emulated
        self.generic = ret.generic
    
    def is_generic(self,dttype):
        if dttype in self.generic and self.generic[dttype]:
            return True
        return False
    def is_emulated(self,dttype):
        if dttype in self.emulated and self.emulated[dttype] :
            return True
        return False
    def is_native(self,dttype):
        if not is_emulated(dttype) and not is_generic(dttype):
            return True
        return False
    
    def add_datatypes(self, datatypes, emulated = False, generic = False):
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

            for dt in func_info.datatypes:
                func_info.emulated[dt] = False
                func_info.generic[dt] = False
            #check if func is mising in any isa, if it is we skip it
            missing = False
            for isa_info in self.isa_infos:
                if isa_info.is_missing(func):
                    missing = True
            if missing:
                continue
            #remove datatypes in func_info that are not supported by isa_info
            for isa_info in self.isa_infos:
                isa_func_info = isa_info.get_func_info(func)
                if isa_func_info is not None:
                    func_info.datatypes = list(set(func_info.datatypes) & set(isa_func_info.datatypes))
                    for dt in func_info.datatypes:
                        if isa_func_info.is_emulated(dt):
                            func_info.emulated[dt] = True
                        if isa_func_info.is_generic(dt):
                            func_info.generic[dt] = True
            #add func_info to intersection
            intersection.func_infos.append(func_info)
        return intersection


def write_mipp_infos(mipp_infos, base_dir, mipp_funcs = mipp_funcs, mipp_funcs_concepts = mipp_funcs_concepts):
    #for each isa write a md file with the list of functions and their supported types
    #we put functions in a table where x is dttype
    # y is function name,
    # we write ::material-check: if the function is emulated for the given ddtype

    
    # we write :material-check-all:  if the function is not emulated for the given dtype
    # we write :material-close: if the function is not supported for the given dtype
    #the function is very very boilerplatey but that's ok ig
    
    color_green ='<span style="color: #28A745; font-weight: 600;">'
    color_blue = '<span style="color: #3B42F5; font-weight: 600;">'
    color_red = '<span style="color: #DC3545; font-weight: 600;">'
    color_black = '<span style="color: #000000; font-weight: 600;">'
    color_yellow = '<span style="color: #FFD20D; font-weight: 600;">'
    color_end = '</span>'
    
    for isa_info in mipp_infos.isa_infos:
        file_path = os.path.join(base_dir, isa_info.isa_name + ".md")
        with open(file_path, "w") as f:
            dttypes = all_datatypes
            for concept in mipp_funcs_concepts:

                #we write one table per concept
                print("\n## " + concept + "\n", file=f)
                #we want the list of dtypes in the same order but shortened using all_datatypes_short
                print("| Function | " + " | ".join(all_datatypes_short) + " |", file=f)
                print("| --- | " + " | ".join(["---"]*len(dttypes)) + " |", file=f)
                for func in mipp_funcs:
                    if func == "cast" or func == "cast_k":
                        continue
                    if func in mipp_funcs_concepts[concept]:
                        func_info = isa_info.get_func_info(func)
                        if func_info is not None:
                            line = "| " + func + " | "
                            for dtype in dttypes:
                                if dtype in func_info.datatypes:
                                    if func_info.is_generic(dtype):
                                        line += color_yellow + ":material-check:" + color_end + " | "
                                    elif func_info.is_emulated(dtype):
                                        line += color_blue + ":material-check:" + color_end + " | "
                                    else :
                                        line += color_green + ":material-check-all:" + color_end + " | "
                                elif dtype in mipp_funcs[func]["datatypes"]:
                                    line += color_red + ":material-close:" + color_end + " | "
                                else :
                                    line += color_black + ":material-minus:" + color_end + " | "
                            print(line, file=f)
                        else :
                            line = "| " + func + " | "
                            for dtype in dttypes:
                                line += color_red + ":material-close:" + color_end + " | "
                            print(line, file=f)
            
            print("\n## miscellaneous\n", file=f)
            print("| Function | " + " | ".join(all_datatypes_short) + " |", file=f)
            print("| --- | " + " | ".join(["---"]*len(dttypes)) + " |", file=f)
            for func in mipp_funcs:
                if func == "cast" or func == "cast_k":
                    continue                
                if all(func not in mipp_funcs_concepts[concept] for concept in mipp_funcs_concepts):
                    func_info = isa_info.get_func_info(func)
                    if func_info is not None:
                        line = "| " + func + " | "
                        for dtype in dttypes:
                            if dtype in func_info.datatypes:
                                if func_info.is_generic(dtype):
                                    line += color_yellow + ":material-check:" + color_end + " | "
                                elif func_info.is_emulated(dtype):
                                    line += color_blue + ":material-check:" + color_end + " | "
                                else :
                                    line += color_green + ":material-check-all:" + color_end + " | "
                            elif dtype in mipp_funcs[func]["datatypes"]:
                                line += color_red + ":material-close:" + color_end + " | "
                            else :
                                line += color_black + ":material-minus:" + color_end + " | "
                        print(line, file=f)
                    else :
                        line = "| " + func + " | "
                        for dtype in dttypes:
                            line += color_red + ":material-close:" + color_end + " | "
                        print(line, file=f)
            dttypes = all_datatypes_cart_prod
            
            #cast and cast_k get their own tables bc they are defined on cartesian product of dt types
            print("\n## cast and cast_k\n", file=f)
            print("| Function | " + " | ".join(all_datatypes_short_cart_prod) + " |", file=f)
            print("| --- | " + " | ".join(["---"]*len(dttypes)) + " |", file=f)
            for func in ["cast", "cast_k"]:
                func_info = isa_info.get_func_info(func)
                if func_info is not None:
                    line = "| " + func + " | "
                    for dtype in dttypes:
                        if dtype in func_info.datatypes:
                            if func_info.is_generic(dtype):
                                line += color_yellow + ":material-check:" + color_end + " | "
                            elif func_info.is_emulated(dtype):
                                line += color_blue + ":material-check:" + color_end + " | "
                            else :
                                line += color_green + ":material-check-all:" + color_end + " | "
                        elif dtype in mipp_funcs[func]["datatypes"]:
                            line += color_red + ":material-close:" + color_end + " | "
                        else :
                            line += color_black + ":material-minus:" + color_end + " | "
                    print(line, file=f)
                else :
                    line = "| " + func + " | "
                    for dtype in dttypes:
                        line += color_red + ":material-close:" + color_end + " | "
                    print(line, file=f)
    


def match_args_type_cpp(arg_type, cast=False, ret=False, fixed_dtype=False, lmul=0):
    
    lmul_str = ""
    if lmul >= 1:
        lmul_str = "," + str(lmul)
    if arg_type == "msk":
        if cast:
            if ret:
                return "rvm<T2" + lmul_str + ">"
            else : 
                return "rvm<T1" + lmul_str + ">"
        else :
            return "rvm<T" + lmul_str + ">"
    elif arg_type == "reg":
        if cast:
            if ret :
                return "rvd<T2" + lmul_str + ">"
            else :
                return "rvd<T1" + lmul_str + ">"
        else : 
            return "rvd<T" + lmul_str + ">"
    elif arg_type == "val" :
        if fixed_dtype != False:
                return fixed_dtype + "_t"
        return "T"
    elif arg_type == "ptr":
        return "T*"
    elif arg_type == "Nele": 
        if fixed_dtype != False:
                return fixed_dtype + "_t []"
        return "T []"
    else:
        return "int32_t"

def match_args_type_c(arg_type, cast=False, ret=False, fixed_dtype=False):
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
        if fixed_dtype != False:
                return fixed_dtype + "_t"
        return "{type}_t"
    elif arg_type == "ptr":
        return "{type}_t*"
    elif arg_type == "Nele": 
        if fixed_dtype != False:
                return fixed_dtype + "_t []"
        return "{type}_t[]" 
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
        self.mask_support = mipp_funcs[func]["mask_support"]
        
        self.concept = "miscellaneous"
        for concept in mipp_funcs_concepts:
            if func in mipp_funcs_concepts[concept]:
                self.concept = concept
                break
            
    def func_to_str_cpp(self, mipp_funcs, lmul=0):
        #lambda to match reg -> rvd 
        #mask -> rvm 
        # val -> T
        
        cast = False
        ret = False
        fixed_dtype = []
        for arg in self.args:
            fixed_dtype.append(arg["fixeddatatype"])
            

        if self.func_name in ["cast", "cast_k"]:
            cast = True
        
        zipped_args = zip(self.args, fixed_dtype)
        args_str = ", ".join([match_args_type_cpp(arg["type"], cast, False, fixed, lmul=lmul) for arg, fixed in zipped_args])
        
        fixed_dtype = self.ret["fixeddatatype"]
        ret_str = match_args_type_cpp(self.ret["type"], cast, True, fixed_dtype, lmul=lmul)
        ret_str = "inline " + ret_str
        print("ret_str : " + ret_str)
        func_proto_str = " " + ret_str + " " + self.func_name + "(" + args_str + ")"
        return func_proto_str
    
    def func_to_str_c(self, mipp_funcs, lmul=0):
        
        lmul_str = ""
        if lmul >= 1:
            lmul_str = "_m" + str(lmul)
        elif lmul < 1 and lmul > 0:
            lmul_str = "_d" + str(int(1/lmul))

        cast = False
        ret = False
        fixed_dtype = []
        for arg in self.args:
            fixed_dtype.append(arg["fixeddatatype"])
        if self.func_name in ["cast", "cast_k"]:
            cast = True
        ret = ""
        args_str = ", ".join([match_args_type_c(arg["type"], cast, False, fixed) for arg, fixed in zip(self.args, fixed_dtype)])
        
        fixed_dtype = self.ret["fixeddatatype"]
        ret_str = match_args_type_c(self.ret["type"], cast, True, fixed_dtype)
        ret_str = "inline " + ret_str
        if cast :
            func_proto_str = " " + ret_str + " " + self.func_name + "_{type 1}_{type 2}" + lmul_str + "(" + args_str + ")"
        else :
            func_proto_str = " " + ret_str + " " + self.func_name + "_{type}" + lmul_str + "(" + args_str + ")"
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
            
            #add description of the function if it exists in mipp_funcs_description
            print("## Description\n", file=f)
            if self.func_name in mipp_funcs_description:
                description = mipp_funcs_description[self.func_name]
            else :
                description = "Uh-oh this function is not documented yet..."
            print(description + "\n\n", file=f)
            
            print("## Prototype", file=f)
            print("### CPP : \n", file=f)
            print("```cpp\n", file=f)
            for lmul in [0, 1, 2, 4, 8]:
                print(self.func_to_str_cpp(mipp_funcs,lmul), file=f)
            print("```", file=f)
            
            #print("\n\n```c", file=f)
            #print(self.func_to_str_c(mipp_funcs), file=f)
            #print("```", file=f)
            print("\n\n### C\n", file=f)
            cstr = "```c\n"
            for lmul in [0, 1, 2, 4, 8]:
                cstr += "// LMUL = " + str(lmul) + "\n"
                cstr += self.func_to_str_c(mipp_funcs,lmul)
            #cstr = cstr.replace("\n", "```\n\n```")
            #remove last ```
            #cstr = cstr[:-4]
            cstr += "\n```"
            print("\n\n" + cstr, file=f)
            
            print("\n\n## Supported datatypes", file=f)
            for dtype in self.dttypes:
                print("- " + dtype, file=f)
            
            if self.mask_support.is_any_mask():
                print("\n\n## Mask support", file=f)
            if self.mask_support.is_maskable():
                print("This function supports masked variants.", file=f)
            if self.mask_support.is_maskzable():
                print("This function supports zero-masking variants.", file=f)
            if self.mask_support.is_masksable():
                print("This function supports source masking variants.", file=f)
       
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
    if os.path.exists("../docs/isas_support/"):
        shutil.rmtree("../docs/isas_support/")
    os.makedirs("../docs/isas_support/")
    write_mipp_infos(mipp_infos, "../docs/isas_support/")
    
        
    #print sse info for debugging
    for isa_info in mipp_infos.isa_infos:
        if isa_info.isa_name == "SSE":
            print("SSE info : ")
            for func_info in isa_info.func_infos:
                print(func_info.func_name, func_info.datatypes)
    
    
    #we want the intersection to be done on 
    #sse4.2, avx2fma, avx512bwbq, rvv1.0
    mipp_infos = MippInfo()
    mipp_infos.gen_mipp_infos(mipp_funcs, implems_dict_small)

    
    intersection = mipp_infos.get_intersection()
    int_mipp_infos = MippInfo()
    int_mipp_infos.isa_infos.append(intersection)
    
    write_mipp_infos(int_mipp_infos, "../docs/isas_support/")
    #write intersection info in a md file in ../docs/isas_support/intersection.md
    
    #write each func prototype in a md file in ../docs/funcs_support/
    if os.path.exists("../docs/funcs_support/"):
        shutil.rmtree("../docs/funcs_support/")
    os.makedirs("../docs/funcs_support/")
    
    spec_func_infos = SpecFuncInfos()
    spec_func_infos.gen_spec_func_infos(mipp_funcs, mipp_funcs_concepts)
    spec_func_infos.write_spec_func_infos("../docs/funcs_support/")
    
if __name__ == "__main__":
    main()
    
