from jinja2 import Template, StrictUndefined
import json
import re

from tools import *

def gen_cpp_structures(isa,file):
	print("// should throw an exception", file=file)
	print("template<typename T, int LMUL=1> struct rvd_type{};", file=file)

	template = """template<> struct rvd_type<{{ datatype.cstd }}, {{ lmul }}>{ using type = rvd_{{ isa.name }}_{{ datatype.category }}{{ datatype.n_bits }}_t; };"""
	j2_template = Template(template, undefined=StrictUndefined)


	for lmul in [1]:
		for dt in datatypes:
			print(j2_template.render(isa =isa, datatype=datatypes[dt], lmul=str(lmul)), file=file)

	print("template <typename T, int LMUL=1> using rvd = typename rvd_type<T,LMUL>::type;", file=file)

	print("// should throw an exception", file=file)
	print("template<typename T, int LMUL=1> struct rvm_type{};", file=file)

	template = """template<> struct rvm_type<{{ datatype.cstd }}, {{ lmul }}>{ using type = rvd_{{ isa.name }}_{{ datatype.category }}{{ datatype.n_bits }}_t; };"""
	j2_template = Template(template, undefined=StrictUndefined)

	for lmul in [1]:
		for dt in datatypes:
			print(j2_template.render(isa =isa, datatype=datatypes[dt], lmul=str(lmul)), file=file)

	print("template <typename T, int LMUL=1> using rvm = typename rvm_type<T,LMUL>::type;", file=file)

def gen_cpp_constexpr_functions(isa,file):
	print("// should throw an exception", file=file)
	print("template<typename T, int LMUL=1> constexpr uint32_t N(){ return 0; }", file=file)


	template = """template<> constexpr uint32_t N<{{ datatype.cstd }}, {{ lmul }}>(){ return MIPP_{{isa_name_upper}}_N_{{type_category_upper}}{{ datatype.n_bits }}; }"""
	j2_template = Template(template, undefined=StrictUndefined)

	for lmul in [1]:
		for dt in datatypes:
			print(j2_template.render(isa_name_upper=isa["name"].upper(),datatype=datatypes[dt], lmul=str(lmul), type_category_upper=datatypes[dt]["category"].upper()), file=file)

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

				c_func_name = build_func_name_short(isa, dt_par, f, True);
				#print("c_func_name pour dt <1: ", c_func_name)

				cpp_func_name = build_cpp_func_name_short(funcs[f]["proto"],dt_ret, f);
				#print("cpp_func_name pour dt <1: ", cpp_func_name)
			else:
				# Build cast's functions
				c_func_name = build_func_name(isa, dt_par, dt_ret, f);
				cpp_func_name = build_cpp_func_name(isa, dt_par, dt_ret, f);
				
			for lmul in [1]:
				print(build_proto(funcs[f]["proto"], dt_par, dt_ret, {}, cpp_func_name, lmul, False, True) + " {", file=file)
				print("\t"+build_call(funcs[f]["proto"], dt_par, dt_ret, {}, c_func_name, lmul, False)+";", file=file)
				print("}", file=file)
