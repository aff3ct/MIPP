#!/usr/bin/env python3
from jinja2 import Template, StrictUndefined
import json

from tools import *
from headers_def import *
from implem_SVE import *
from implem_emu_SVE import *
from c_generator import *

def gen_c_defines_sve_ls(file):
    template = """#if __ARM_FEATURE_SVE_BITS
#define MIPP_REGISTER_SIZE __ARM_FEATURE_SVE_BITS
#define MIPP_SVE_RVD_SIZE_BIT __ARM_FEATURE_SVE_BITS
#define MIPP_SVE_RVD_SIZE_BYTE MIPP_SVE_RVD_SIZE_BIT/8"""
    j2_template = Template(template, undefined=StrictUndefined)
    print(j2_template.render(), file=file)
    
    template = """#define MIPP_N_{{type_category_upper}}{{n_bits}} MIPP_SVE_RVD_SIZE_BIT/{{n_bits}}"""
    j2_template = Template(template, undefined=StrictUndefined)
    for dt in isa_sve["datatypes"]:
        print(j2_template.render(isa_name_upper=isa_sve["name"].upper(), type_category_upper=datatypes[dt]["category"].upper(), n_bits=datatypes[dt]["n_bits"]), file=file)
    
    template = """#else
// autre possibilite genere un fichier SVE par taille supportee
#error Only -msve-vector-bits = 128-256-512-1024-2048 is supported
#endif"""
    j2_template = Template(template, undefined=StrictUndefined)
    print(j2_template.render(), file=file)
    

def gen_c_structures_sve_ls(file):
    template = """typedef {{ isa_datatype.reg }} fixed_{{isa_datatype.to_ptr}} __attribute__((arm_sve_vector_bits(MIPP_REGISTER_SIZE)));"""
    j2_template = Template(template, undefined=StrictUndefined)
    for dt in isa_sve["datatypes"]:
        print(j2_template.render(isa_datatype=isa_sve["datatypes"][dt]), file=file)
    print("typedef svbool_t fixed_bool_t __attribute__((arm_sve_vector_bits(MIPP_REGISTER_SIZE)));", file=file)
    
    template = """typedef struct { fixed_{{isa_datatype.to_ptr }} r; } rvd_{{ isa.name }}_{{ datatype.category }}{{ datatype.n_bits }}_t;"""
    j2_template = Template(template, undefined=StrictUndefined)
    for dt in isa_sve["datatypes"]:
        print(j2_template.render(isa=isa_sve, isa_datatype=isa_sve["datatypes"][dt], datatype=datatypes[dt]), file=file)

    template = """typedef struct { fixed_bool_t m; } rvm_{{ isa.name }}_{{ datatype.category }}{{ datatype.n_bits }}_t;"""
    j2_template = Template(template, undefined=StrictUndefined)
    for dt in isa_sve["datatypes"]:
        print(j2_template.render(isa=isa_sve, isa_datatype=isa_sve["datatypes"][dt], datatype=datatypes[dt]), file=file)

def gen_mipp_sve():
	for iemu in implems_emu_sve:
		for sub_iemu in implems_emu_sve[iemu]:
			if "type" not in sub_iemu:
				sub_iemu["type"] = "emulated"

	file = open("../include/sve/mipp_v2_impl_SVE_gen.h", "w")

	tpl_header_sve = """#ifndef MY_INTRINSICS_PLUS_PLUS_IMPL_GEN_SVE_H_
#define MY_INTRINSICS_PLUS_PLUS_IMPL_GEN_SVE_H_
#include <arm_sve.h>"""
	j2_template = Template(tpl_header_sve, undefined=StrictUndefined)
	print(j2_template.render(), file=file)

	gen_c_defines_sve_ls(file)
	gen_c_structures_sve_ls(file)
	print("Generate SVE")
	copy_mipp_funcs = copy.deepcopy(mipp_funcs)
	gen_c_functions(isa_sve, file, copy_mipp_funcs, implems_sve)
	gen_c_functions(isa_sve, file, copy_mipp_funcs, implems_emu_sve)
	gen_c_missing_functions(isa_sve, file, copy_mipp_funcs)

	tpl_footer_sve = """#endif /* MY_INTRINSICS_PLUS_PLUS_IMPL_GEN_SVE_H_ */"""
	j2_template = Template(tpl_footer_sve, undefined=StrictUndefined)
	print(j2_template.render(), file=file)

	file.close()
