from jinja2 import Template, StrictUndefined
import json
import re

from tools import *

def gen_ci_defines(isa_list, file):
	i = 0
	for isa in isa_list:
		if i == 0:
			print("#if defined(" + isa["define"] + ")", file=file)
		else:
			print("#elif defined(" + isa_list["define"] + ")", file=file)
		print("#define MIPP_RVD_SIZE_BIT MIPP_" + isa["name"].upper() + "_RVD_SIZE_BIT", file=file)
		print("#define MIPP_RVD_SIZE_BYTE MIPP_" + isa["name"].upper() + "_RVD_SIZE_BYTE", file=file)

		template = """#define MIPP_N_{{type_category_upper}}{{n_bits}} MIPP_{{isa_name_upper}}_N_{{type_category_upper}}{{n_bits}}"""
		j2_template = Template(template, undefined=StrictUndefined)

		for dt in isa["datatypes"]:
			print(j2_template.render(isa_name_upper=isa["name"].upper(), type_category_upper=isa["datatypes"][dt]["category"].upper(), n_bits=isa["datatypes"][dt]["n_bits"]), file=file)
		i = i + 1
		if i == len(isa_list):
			print("#endif", file=file)

	print("#define MIPP_LMUL_STRIDE(elmt_byte, m) ((MIPP_RVD_SIZE_BYTE) / (elmt_byte) * (m))", file=file)

	for lmul in [1, 2, 4, 8]:
		template = """#define MIPP_N_{{type_category_upper}}{{n_bits}}_M{{lmul}} (MIPP_N_{{type_category_upper}}{{n_bits}} * {{lmul}})"""
		j2_template = Template(template, undefined=StrictUndefined)

		for dt in isa["datatypes"]:
			print(j2_template.render(type_category_upper=isa["datatypes"][dt]["category"].upper(), n_bits=isa["datatypes"][dt]["n_bits"], lmul=str(lmul)), file=file)

def gen_ci_structures(isa_list, file):
	i = 0
	for isa in isa_list:

		if i == 0:
			print("#if defined(" + isa["define"] + ")", file=file)
		else:
			print("#elif defined(" + isa_list["define"] + ")", file=file)

		template = """typedef rvd_{{ isa.name }}_{{ datatype.category }}{{ datatype.n_bits }}_t rvd_{{ datatype.category }}{{ datatype.n_bits }}_t;"""
		j2_template = Template(template, undefined=StrictUndefined)

		for dt in isa["datatypes"]:
			print(j2_template.render(isa=isa, datatype=isa["datatypes"][dt]), file=file)

		template = """typedef rvm_{{ isa.name }}_{{ datatype.category }}{{ datatype.n_bits }}_t rvm_{{ datatype.category }}{{ datatype.n_bits }}_t;"""
		j2_template = Template(template, undefined=StrictUndefined)

		for dt in isa["datatypes"]:
			print(j2_template.render(isa=isa, datatype=isa["datatypes"][dt]), file=file)

		i = i + 1
		if i == len(isa_list):
			print("#endif", file=file)

	template = """typedef rvd_{{ datatype.category }}{{ datatype.n_bits }}_t rvd_{{ datatype.category }}{{ datatype.n_bits }}_m1_t;"""
	j2_template = Template(template, undefined=StrictUndefined)

	for dt in isa["datatypes"]:
		print(j2_template.render(isa=isa, datatype=isa["datatypes"][dt]), file=file)

	template = """typedef rvm_{{ datatype.category }}{{ datatype.n_bits }}_t rvm_{{ datatype.category }}{{ datatype.n_bits }}_m1_t;"""
	j2_template = Template(template, undefined=StrictUndefined)

	for dt in isa["datatypes"]:
		print(j2_template.render(isa=isa, datatype=isa["datatypes"][dt]), file=file)

	for lmul in [2, 4, 8]:
		lmul_2 = int(lmul / 2)
		template = """typedef struct { rvd_{{ datatype.category }}{{ datatype.n_bits }}_m{{ lmul_2 }}_t m1, m2; } rvd_{{ datatype.category }}{{ datatype.n_bits }}_m{{ lmul }}_t;"""
		j2_template = Template(template, undefined=StrictUndefined)
		for dt in isa["datatypes"]:
			print(j2_template.render(isa=isa, datatype=isa["datatypes"][dt], lmul=str(lmul), lmul_2=str(lmul_2)), file=file)
	for lmul in [2, 4, 8]:
		lmul_2 = int(lmul / 2)
		template = """typedef struct { rvm_{{ datatype.category }}{{ datatype.n_bits }}_m{{ lmul_2 }}_t m1, m2; } rvm_{{ datatype.category }}{{ datatype.n_bits }}_m{{ lmul }}_t;"""
		j2_template = Template(template, undefined=StrictUndefined)
		for dt in isa["datatypes"]:
			print(j2_template.render(isa=isa, datatype=isa["datatypes"][dt], lmul=str(lmul), lmul_2=str(lmul_2)), file=file)

def gen_ci_functions(isa_list, file, funcs):
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
				func_name = build_func_name_short(isa_list[0], dt_par, f, False);
			else:
				func_name = build_func_name(isa_list[0], dt_par, dt_ret, f, False);
			print(build_proto(funcs[f]["proto"], dt_par, dt_ret, isa_list[0], func_name, 0, False) + " {", file=file)

			i = 0
			for isa in isa_list:
				if i == 0:
					print("#if defined(" + isa["define"] + ")", file=file)
				else:
					print("#elif defined(" + isa_list["define"] + ")", file=file)

				if len(dt.split(',')) <= 1:
					func_name_impl = build_func_name_short(isa, dt_par, f);
				else:
					func_name_impl = build_func_name(isa, dt_par, dt_ret, f);
				print("\t" + build_call(funcs[f]["proto"], dt_par, dt_ret, isa, func_name_impl) + ";", file=file)

				i = i + 1
				if i == len(isa_list):
					print("#endif", file=file)

			print("}", file=file)

			print(build_proto(funcs[f]["proto"], dt_par, dt_ret, isa_list[0], func_name, 1, False) + " {", file=file)
			print("\t" + build_call(funcs[f]["proto"], dt_par, dt_ret, isa_list[0], func_name) + ";", file=file)
			print("}", file=file)

			for lmul in [2, 4, 8]:
				print(build_proto(funcs[f]["proto"], dt_par, dt_ret, isa_list[0], func_name, lmul, False) + " {", file=file)
				if not funcs[f]["horizontal"]:
					lmul_2 = int(lmul / 2)
					print(build_call_lmul(funcs[f]["proto"], dt_par, dt_ret, isa_list[0], func_name, lmul, False), file=file)
				else:
					print("\tprintf(\"MIPP panic: '%s' is unimplemented.\\n\", \""+func_name+"_m"+str(lmul)+"\");", file=file);
					print("\texit(-1);", file=file);
				print("}", file=file)
