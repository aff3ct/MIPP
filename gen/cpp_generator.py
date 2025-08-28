from jinja2 import Template, StrictUndefined
import json
import re

from tools import *
from headers_def import *

# cpp wrapper
def generate_cpp():

	
	file = open("../include/mipp_v2.hpp", "w")

	tpl_header_cpp = """#ifndef MY_INTRINSICS_PLUS_PLUS_HPP_
#define MY_INTRINSICS_PLUS_PLUS_HPP_

#include "mipp_v2_interface_gen.h"

namespace mipp
{"""

	j2_template = Template(tpl_header_cpp, undefined=StrictUndefined)
	print(j2_template.render(), file=file)

	gen_cpp_structures(file)
	gen_cpp_constexpr_functions(file)
	gen_cpp_functions(file, copy_mipp_funcs)

	tpl_footer_cpp = """}

#endif /* MY_INTRINSICS_PLUS_PLUS_HPP_ */"""
	j2_template = Template(tpl_footer_cpp, undefined=StrictUndefined)
	print(j2_template.render(), file=file)

	file.close()
	
def gen_cpp_structures(file):
	print("// should throw an exception", file=file)
	print("template<typename T, int LMUL=1> struct rvd_type{};", file=file)

	template = """template<> struct rvd_type<{{ datatype.cstd }}, {{ lmul }}>{ using type = rvd_{{ datatype.category }}{{ datatype.n_bits }}_m{{ lmul }}_t; };"""
	j2_template = Template(template, undefined=StrictUndefined)


	for lmul in [1,2,4,8]:
		for dt in datatypes:
			print(j2_template.render(datatype=datatypes[dt], lmul=str(lmul)), file=file)

	print("template <typename T, int LMUL=1> using rvd = typename rvd_type<T,LMUL>::type;", file=file)

	print("// should throw an exception", file=file)
	print("template<typename T, int LMUL=1> struct rvm_type{};", file=file)

	template = """template<> struct rvm_type<{{ datatype.cstd }}, {{ lmul }}>{ using type = rvm_{{ datatype.category }}{{ datatype.n_bits }}_m{{ lmul }}_t; };"""
	j2_template = Template(template, undefined=StrictUndefined)

	for lmul in [1,2,4,8]:
		for dt in datatypes:
			print(j2_template.render(datatype=datatypes[dt], lmul=str(lmul)), file=file)

	print("template <typename T, int LMUL=1> using rvm = typename rvm_type<T,LMUL>::type;", file=file)

def gen_cpp_constexpr_functions(file):
	print("// should throw an exception", file=file)
	print("template<typename T, int LMUL=1> constexpr uint32_t N(){ return 0; }", file=file)


	template = """template<> constexpr uint32_t N<{{ datatype.cstd }}, {{ lmul }}>(){ return MIPP_N_{{type_category_upper}}{{ datatype.n_bits }}; }"""
	j2_template = Template(template, undefined=StrictUndefined)

	for lmul in [1,2,4,8]:
		for dt in datatypes:
			print(j2_template.render(datatype=datatypes[dt], lmul=str(lmul), type_category_upper=datatypes[dt]["category"].upper()), file=file)

def gen_cpp_functions(file, funcs):
	set_functions = ["set0","set0_k","set","set_k","set1", "set1_k","load","loadu"]
	for f in funcs:
		if f in set_functions:
			gen_set_func_error(f,file)
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
				c_func_name = build_func_name_short("", dt_par, f, False);

				cpp_func_name = build_cpp_func_name_short(funcs[f]["proto"],dt_ret, f);

			else:
				# Build cast's functions
				c_func_name = build_func_name("", dt_par, dt_ret, f, False);
				cpp_func_name = build_cpp_func_name(dt_ret, f);
				
			for lmul in [1,2,4,8]:
				print(build_proto(funcs[f]["proto"], dt_par, dt_ret, {}, cpp_func_name, lmul, False, True) + " {", file=file)
				print("\t"+build_call(funcs[f]["proto"], dt_par, dt_ret,"", c_func_name+"_m"+str(lmul), lmul, False)+";", file=file)
				print("}", file=file)