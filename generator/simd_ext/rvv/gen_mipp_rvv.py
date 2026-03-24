#!/usr/bin/env python3

from jinja2 import Template, StrictUndefined
import json
import copy
import sys
sys.path.insert(1, '.')

from tools import *
from headers_def import *
from implem_rvv import *
from implem_emu_rvv import *
from c_generator import *

#taken from gen_mipp_sve.py
def gen_c_defines_rvv_ls(file, isa_name, rvv_size):
    print("#define MIPP_" + isa_name.upper() + str(rvv_size) + "_RVD_SIZE_BIT " + str(rvv_size), file=file)
    print("#define MIPP_" + isa_name.upper() + str(rvv_size) + "_RVD_SIZE_BYTE " + str(int(rvv_size / 8)), file=file)
    template = """#define MIPP_RVV{{rvv_size}}_N_{{type_category_upper}}{{n_bits}} {{type_size}}"""
    j2_template = Template(template, undefined=StrictUndefined)
    for dt in isa_rvv["datatypes"]:
        n_bits=datatypes[dt]["n_bits"]
        print(j2_template.render(rvv_size=rvv_size, n_bits=n_bits, type_size = int(rvv_size/n_bits), type_category_upper=datatypes[dt]["category"].upper()), file=file)
    
#taken from gen_mipp_rvv.py
def gen_c_structures_rvv_ls(file, rvv_size):
    template = """typedef {{ isa_datatype.reg }} fixed_{{ rvv_size }}_{{isa_datatype.to_ptr}} __attribute__((riscv_rvv_vector_bits({{ rvv_size }})));"""
    j2_template = Template(template, undefined=StrictUndefined)
    for dt in isa_rvv["datatypes"]:
        print(j2_template.render(isa_datatype=isa_rvv["datatypes"][dt],rvv_size=rvv_size), file=file)
     
    template = """typedef {{isa_datatype.msk}} fixed_{{rvv_size}}_bool{{isa_datatype.data_ext_logi}}_t __attribute__((riscv_rvv_vector_bits({{nb_elem}})));"""
    j2_template = Template(template, undefined=StrictUndefined)
    
    #hacky solution bc we need 1 bool type per size and they're the same 
    #for types of the same size...
    #also, mask type technically does not depend on dt type but on EEW/LMUL. 
    #i.e both uint8m2 and uint16m1 should use vbool16. This might make lmul support 
    #trickier to generate...
    dt_list = {uint64 : "4", uint32 : "8", uint16 : "16", uint8 : "32"}
    for dt in dt_list:
        print(j2_template.render(rvv_size=rvv_size, isa_datatype=isa_rvv["datatypes"][dt], nb_elem=dt_list[dt]), file=file)
    
    template = """typedef struct { fixed_{{ rvv_size }}_{{isa_datatype.to_ptr }} r; } rvd_{{ isa.name }}_{{ datatype.category }}{{ datatype.n_bits }}_t;"""
    j2_template = Template(template, undefined=StrictUndefined)
    for dt in isa_rvv["datatypes"]:
        print(j2_template.render(isa=isa_rvv,rvv_size=rvv_size,isa_datatype=isa_rvv["datatypes"][dt], datatype=datatypes[dt]), file=file)

    template = """typedef struct { fixed_{{ rvv_size }}_bool{{isa_datatype.data_ext_logi}}_t m; } rvm_{{ isa.name }}_{{ datatype.category }}{{ datatype.n_bits }}_t;"""
    j2_template = Template(template, undefined=StrictUndefined)
    
    for dt in isa_rvv["datatypes"]:
        print(j2_template.render(isa=isa_rvv,rvv_size=rvv_size,isa_datatype=isa_rvv["datatypes"][dt], datatype=datatypes[dt]), file=file)


#taken from gen_mipp_avx.py (changed)
def gen_mipp_rvv(vl=32*8):
    #for iemu in implems_emu_rvv:
    #	for sub_iemu in implems_emu_rvv[iemu]:
    #		if "type" not in sub_iemu:
    #			sub_iemu["type"] = "emulated"
    # implementation C
    file = open("../include/rvv/mipp_v2_impl_RVV_gen.h", "w")

    tpl_header_rvv = """#ifndef MY_INTRINSICS_PLUS_PLUS_IMPL_GEN_RVV_H_
#define MY_INTRINSICS_PLUS_PLUS_IMPL_GEN_RVV_H_
#include <riscv_vector.h>
#include <string.h>
#include <float.h>
#include <stdint.h>
#define MIPP_RVV_VL {{vl}}"""#vl is unnecessary actually
#typedef double float64_t;
#typedef float float32_t;"""#the typedefs are here only for debugging and should be removed when 
#we integrate w mipp
    j2_template = Template(tpl_header_rvv, undefined=StrictUndefined)
    print(j2_template.render(vl=vl), file=file)

    ref_isa_name = isa_rvv["name"]
    #for function prototypes that use arrays declared w macros like MIPP_RVV256_N_FLOAT64 
    #we want the name to contain size. This is optional atm 
    #but if we want smtg similar to sve it will become useful
    isa_rvv["name"] = ref_isa_name+str(vl) 
    gen_c_defines_rvv_ls(file,ref_isa_name,vl)
    gen_c_structures_rvv_ls(file,vl)
    print("Generate RVV")
    copy_mipp_funcs = copy.deepcopy(mipp_funcs)
    gen_c_functions(isa_rvv, file, copy_mipp_funcs, implems_rvv)
    
    #will do these later
    gen_c_functions(isa_rvv, file, copy_mipp_funcs, implems_emu_rvv)
    gen_c_missing_functions(isa_rvv, file, copy_mipp_funcs)

    tpl_footer_rvv = """#endif /* MY_INTRINSICS_PLUS_PLUS_IMPL_GEN_RVV_H_ */"""
    j2_template = Template(tpl_footer_rvv, undefined=StrictUndefined)
    print(j2_template.render(), file=file)

    file.close()