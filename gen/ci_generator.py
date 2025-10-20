from jinja2 import Template, StrictUndefined
import json
import re

from tools import *
from headers_def import *


def get_sub_isa(isa, ldiv, isa_list):
	for sub_isa in isa_list:
		if isa["architecture"] == "AArch64":
				return 
		elif isa["architecture"] == sub_isa["architecture"] :
			# pas genial sve list int x86 int (mettre un tableau de taille 1 pour x86)
			if isinstance(isa["size"], int) and isa["size"]/ldiv == sub_isa["size"] :
				return sub_isa
			
def duplicate_isa_sve_along_size(isa_list):			
	isa_list_copy = copy.deepcopy(isa_list)
	isa_sve = []
	current_index = -1
	isa_sve_size = []
	for index, isa in enumerate(isa_list_copy):
		if isa["name"]=="sve":
			isa_sve = isa
			current_index = index
			all_sve_sizes = list(isa["size"])
			break
	del isa_list_copy[current_index]
	all_sve_sizes = sorted(isa_sve["size"], reverse=True)
	for reg_size in all_sve_sizes:
		isa_sve_copy = copy.deepcopy(isa_sve)
		isa_sve_copy["name"]="sve"+str(reg_size)
		isa_sve_copy["size"]=reg_size
		isa_sve_copy["define"]="MIPP_USE_ARM_SVE_"+str(reg_size)
		isa_list_copy.append(isa_sve_copy)
	return isa_list_copy

def generate_c_interface(isa_list):
	
	file = open("../include/mipp_v2_interface_gen.h", "w")

	tpl_header_interface = """#ifndef MY_INTRINSICS_PLUS_PLUS_INTERFACE_H_
#define MY_INTRINSICS_PLUS_PLUS_INTERFACE_H_ """
	j2_template = Template(tpl_header_interface, undefined=StrictUndefined)
	print(j2_template.render(), file=file)
	# use try ldiv sve
	isa_list = duplicate_isa_sve_along_size(isa_list)
	gen_ci_defines(isa_list, file)
	gen_ci_structures(isa_list, file)
	gen_ci_functions(isa_list, file, copy_mipp_funcs)

	tpl_footer_interface = """#endif /* MY_INTRINSICS_PLUS_PLUS_INTERFACE_H_ */"""
	j2_template = Template(tpl_footer_interface, undefined=StrictUndefined)
	print(j2_template.render(), file=file)

	file.close()

def gen_ci_defines(isa_list, file):
	for i, isa in enumerate(isa_list):
		if i == 0:
			print("#if defined(" + isa["define"] + ")", file=file)
		else:
			print("#elif defined(" + isa["define"] + ")", file=file)
			
		print("#define MIPP_RVD_SIZE_BYTE MIPP_"+isa["name"].upper()+"_RVD_SIZE_BYTE", file=file)

		template = """#define MIPP_N_{{type_category_upper}}{{n_bits}} MIPP_{{isa_name_upper}}_N_{{type_category_upper}}{{n_bits}}"""
		for dt in isa["datatypes"]:
			j2_template = Template(template, undefined=StrictUndefined)
			print(j2_template.render(isa_name_upper=isa["name"].upper(), n_bits=datatypes[dt]["n_bits"], type_category_upper=datatypes[dt]["category"].upper()), file=file)

		if i == len(isa_list)-1:
			print("#endif", file=file)
		   
	print("#define MIPP_LMUL_STRIDE(elmt_byte, m) ((MIPP_RVD_SIZE_BYTE) / (elmt_byte) * (m))", file=file)


def gen_ci_structures(isa_list, file):
	
	for index, isa in enumerate(isa_list):
		
		if index == 0:
			print("#if defined(" + isa["define"] + ")", file=file)
		else:
			print("#elif defined(" + isa["define"] + ")", file=file)

		template = """typedef rvd_{{ isa.name }}_{{ datatype.category }}{{ datatype.n_bits }}_t rvd_{{ datatype.category }}{{ datatype.n_bits }}_t;"""
		j2_template = Template(template, undefined=StrictUndefined)

		for dt in isa["datatypes"]:
			print(j2_template.render(isa=isa, datatype=datatypes[dt]), file=file)

		template = """typedef rvm_{{ isa.name }}_{{ datatype.category }}{{ datatype.n_bits }}_t rvm_{{ datatype.category }}{{ datatype.n_bits }}_t;"""
		j2_template = Template(template, undefined=StrictUndefined)

		for dt in isa["datatypes"]:
			print(j2_template.render(isa=isa, datatype=datatypes[dt]), file=file)
		
		#sub_isa_list = isa_list[index+1:]
		
		for ldiv in all_ldiv:
			sub_isa = get_sub_isa(isa, ldiv, isa_list)
			if sub_isa :
				print("#if defined(" + sub_isa["define"] + ")", file=file)
				used_sub_isa = sub_isa
				print("#define MIPP_ENABLE_LDIV"+str(ldiv), file=file)
			else :
				break
				
			template = """typedef rvd_{{ used_sub_isa.name }}_{{ datatype.category }}{{ datatype.n_bits }}_t rvd_{{ datatype.category }}{{ datatype.n_bits }}_d{{ ldiv }}_t;"""
			j2_template = Template(template, undefined=StrictUndefined)
			for dt in isa["datatypes"]:
				print(j2_template.render(used_sub_isa=used_sub_isa, datatype=datatypes[dt], ldiv=str(ldiv)), file=file)
			template = """typedef rvm_{{ used_sub_isa.name }}_{{ datatype.category }}{{ datatype.n_bits }}_t rvm_{{ datatype.category }}{{ datatype.n_bits }}_d{{ ldiv }}_t;"""
			j2_template = Template(template, undefined=StrictUndefined)
			for dt in isa["datatypes"]:
				print(j2_template.render(used_sub_isa=used_sub_isa, datatype=datatypes[dt], ldiv=str(ldiv)), file=file)
			
			if sub_isa :	
				print("#endif /** "+sub_isa["define"]+" under "+isa["define"]+" **/", file=file)
			
		if index == len(isa_list)-1:
			print("#endif", file=file)

	template = """typedef rvd_{{ datatype.category }}{{ datatype.n_bits }}_t rvd_{{ datatype.category }}{{ datatype.n_bits }}_m1_t;"""
	j2_template = Template(template, undefined=StrictUndefined)

	for dt in isa["datatypes"]:
		print(j2_template.render(isa=isa, datatype=datatypes[dt]), file=file)

	template = """typedef rvm_{{ datatype.category }}{{ datatype.n_bits }}_t rvm_{{ datatype.category }}{{ datatype.n_bits }}_m1_t;"""
	j2_template = Template(template, undefined=StrictUndefined)

	for dt in isa["datatypes"]:
		print(j2_template.render(isa=isa, datatype=datatypes[dt]), file=file)

	for lmul in all_lmul[1:]:
		lmul_2 = int(lmul / 2)
		template = """typedef struct { rvd_{{ datatype.category }}{{ datatype.n_bits }}_m{{ lmul_2 }}_t r1, r2; } rvd_{{ datatype.category }}{{ datatype.n_bits }}_m{{ lmul }}_t;"""
		j2_template = Template(template, undefined=StrictUndefined)
		for dt in isa["datatypes"]:
			print(j2_template.render(isa=isa, datatype=datatypes[dt], lmul=str(lmul), lmul_2=str(lmul_2)), file=file)
	for lmul in all_lmul[1:]:
		lmul_2 = int(lmul / 2)
		template = """typedef struct { rvm_{{ datatype.category }}{{ datatype.n_bits }}_m{{ lmul_2 }}_t m1, m2; } rvm_{{ datatype.category }}{{ datatype.n_bits }}_m{{ lmul }}_t;"""
		j2_template = Template(template, undefined=StrictUndefined)
		for dt in isa["datatypes"]:
			print(j2_template.render(isa=isa, datatype=datatypes[dt], lmul=str(lmul), lmul_2=str(lmul_2)), file=file)

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
			for i, isa in  enumerate(isa_list):
				if i == 0:
					print("#if defined(" + isa["define"] + ")", file=file)
				else:
					print("#elif defined(" + isa["define"] + ")", file=file)
   
				if len(dt.split(',')) <= 1:
					func_name_impl = build_func_name_short(isa, dt_par, f);
				else:
					func_name_impl = build_func_name(isa, dt_par, dt_ret, f);
				print("\t" + build_call(funcs[f]["proto"], dt_par, dt_ret, isa, func_name_impl) + ";", file=file)
				if i == len(isa_list)-1:
					print("#endif", file=file)
		  		
			print("}", file=file)

			print(build_proto(funcs[f]["proto"], dt_par, dt_ret, isa_list[0], func_name+"_m1", 1, False) + " {", file=file)
			print("\t" + build_call(funcs[f]["proto"], dt_par, dt_ret, isa_list[0], func_name) + ";", file=file)
			print("}", file=file)
			
			for lmul in all_lmul[1:]:
				print(build_proto(funcs[f]["proto"], dt_par, dt_ret, isa_list[0], func_name+"_m"+str(lmul), lmul, False) + " {", file=file)
				if not funcs[f]["horizontal"]:
					lmul_2 = int(lmul / 2)
					print(build_call_lmul(funcs[f]["proto"], dt_par, dt_ret, isa_list[0], func_name+"_m"+str(lmul_2), lmul, False), file=file)
				else:
					print("\tprintf(\"MIPP panic: '%s' is unimplemented.\\n\", \""+func_name+"_m"+str(lmul)+"\");", file=file);
					print("\texit(-1);", file=file);
				print("}", file=file)
			
			if not funcs[f]["horizontal"]: #and funcs[f]["half_regiser"]:
				for ldiv in all_ldiv:
					print("#if defined(MIPP_ENABLE_LDIV"+str(ldiv)+")", file=file)
					print(build_proto(funcs[f]["proto"], dt_par, dt_ret, isa_list[0], func_name+"_d"+str(ldiv), -ldiv, False) + " {", file=file)
					for i, isa in  enumerate(isa_list):
						sub_isa = sub_isa = get_sub_isa(isa, ldiv, isa_list)
						if sub_isa :
							if i == 0:
								print("#if defined(" + isa["define"] + ") and defined(" + sub_isa["define"] + ")", file=file)
							else:
								print("#elif defined(" + isa["define"] + ") and defined(" + sub_isa["define"] + ")", file=file)
						   
							if len(dt.split(',')) <= 1:
								func_name_impl = build_func_name_short(sub_isa, dt_par, f);
							else:
								func_name_impl = build_func_name(sub_isa, dt_par, dt_ret, f);
							print("\t" + build_call(funcs[f]["proto"], dt_par, dt_ret, sub_isa, func_name_impl) + ";", file=file)	
					
					print("#else", file=file)
					print("\tprintf(\"MIPP panic: '%s' is unimplemented.\\n\", \""+func_name+"_d"+str(ldiv)+"\");", file=file);
					print("\texit(-1);", file=file);
					print("#endif", file=file)
					print("}", file=file)
					print("#endif // defined(MIPP_ENABLE_LDIV"+str(ldiv)+")", file=file)
			else :
				for ldiv in all_ldiv:
					print("#if defined(MIPP_ENABLE_LDIV"+str(ldiv)+")", file=file)
					print(build_proto(funcs[f]["proto"], dt_par, dt_ret, isa_list[0], func_name+"_d"+str(ldiv), -ldiv, False) + " {", file=file)
					print("\tprintf(\"MIPP panic: '%s' is unimplemented.\\n\", \""+func_name+"_d"+str(ldiv)+"\");", file=file);
					print("\texit(-1);", file=file);
					print("}", file=file)
					print("#endif // defined(MIPP_ENABLE_LDIV"+str(ldiv)+")"+")", file=file)
