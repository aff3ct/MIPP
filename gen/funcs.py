from jinja2 import Template, StrictUndefined
import json
import re
from avx_gen.headers_def_AVX import *

from tools import *

def gen_cpp_functions(file, funcs):
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
				c_func_name = build_func_name_short({}, dt_par, f, False);
				cpp_func_name = build_cpp_func_name_short(funcs[f]["proto"], dt_ret, f);
			else:
				c_func_name = build_func_name({}, dt_par, dt_ret, f, False);
				cpp_func_name = build_cpp_func_name(dt_ret, f);

			for lmul in [1]:
				print("inline "+ build_proto(funcs[f]["proto"], dt_par, dt_ret, {}, cpp_func_name, lmul, False, True) , file=file)
				#print("\t"+build_call(funcs[f]["proto"], dt_par, dt_ret, {}, c_func_name, lmul, False)+";", file=file)

file = open("func.hpp", "w")

gen_cpp_functions(file, mipp_funcs)
file.close()
