from jinja2 import Template, StrictUndefined
import json
import re

from avx_gen.implem_AVX import *
from avx_gen.implem_emu_AVX import *
from avx512_gen.implem_AVX512 import *
from avx512_gen.implem_emu_AVX512 import *
from avx_gen.headers_def_AVX import *
from avx512_gen.headers_def_AVX512 import *
from c_generator import *
from cpp_generator import *
from tools import *

def gen_cpp_functions(isa,file, funcs):
	for f in funcs:
		for dt in funcs[f]["datatypes"]:
			if len(dt.split(',')) <= 1:
				dt_par = dt.split(',')[0]
				dt_ret = dt.split(',')[0]
			else:
				dt_par = dt.split(',')[0]
				dt_ret = dt.split(',')[1]
				dtk = dt_par + "," + dt_ret
			dt_key = dt_par + "," + dt_ret
			
			if len(dt.split(',')) <= 1:
				# build other functions 

				c_func_name = build_func_name_short(isa, dt_par, f, False);
				#print("c_func_name pour dt <1: ", c_func_name)

				cpp_func_name = build_cpp_func_name_short(funcs[f]["proto"],dt_ret, f);
				#print("cpp_func_name pour dt <1: ", cpp_func_name)
			else:
				# Build cast's functions
				c_func_name = build_func_name(isa, dt_par, dt_ret, f);
				cpp_func_name = build_cpp_func_name(isa, dt_par, dt_ret, f);

			for lmul in [1]:
				print("inline "+ build_proto(funcs[f]["proto"], dt_par, dt_ret, {}, cpp_func_name, lmul, False, True ) +";", file=file)
				#print("\t"+build_call(funcs[f]["proto"], dt_par, dt_ret, {}, c_func_name, lmul, False)+";", file=file)


file = open("../include/mipp_v2_func_gen.h", "w")

tpl_header_cpp = """#ifndef MY_INTRINSICS_PLUS_PLUS_H_
#define MY_INTRINSICS_PLUS_PLUS_H_

#include "mipp_v2.h"

namespace mipp

{"""
j2_template = Template(tpl_header_cpp, undefined=StrictUndefined)
print(j2_template.render(), file=file)

gen_cpp_functions(isa_avx,file, mipp_funcs)

tpl_footer_cpp = """}
#endif /* MY_INTRINSICS_PLUS_PLUS_H_ */"""
j2_template = Template(tpl_footer_cpp, undefined=StrictUndefined)
print(j2_template.render(), file=file)

file.close()

