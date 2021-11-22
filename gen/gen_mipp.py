#!/usr/bin/env python3

from jinja2 import Template, StrictUndefined
import json
import re

all_float = ["float64", "float32"]
all_int = ["int64", "int32", "int16", "int8"]
all_uint = ["uint64", "uint32", "uint16", "uint8"]
all_int_uint = all_int + all_uint
all_datatypes = all_float + all_int_uint

all_datatypes_cart_prod = [];
for dt_ret in all_datatypes:
	for dt_par in all_datatypes:
		new_entry = [dt_par, dt_ret]
		if new_entry not in all_datatypes_cart_prod:
			all_datatypes_cart_prod.append(dt_par + "," + dt_ret);

def build_reg(datatype, isa):
	return "rvd_" + isa["name"] + "_" + datatype["category"] + str(datatype["n_bits"]) + "_t"

def build_msk(datatype, isa):
	return "rvm_" + isa["name"] + "_" + datatype["category"] + str(datatype["n_bits"]) + "_t"

def build_val(datatype, isa):
	return datatype["category"] + str(datatype["n_bits"]) + "_t"

def build_ptr(datatype, isa):
	return datatype["category"] + str(datatype["n_bits"]) + "_t*"

def build_type(type, datatype, isa):
	if type:
		if type == "reg":
			return build_reg(datatype, isa)
		elif type == "msk":
			return build_msk(datatype, isa)
		elif type == "val":
			return build_val(datatype, isa)
		elif type == "ptr":
			return build_ptr(datatype, isa)
	else:
		return "void"

def build_proto(proto, dt_par, dt_ret, isa, func_name):
	realdatatype = isa["datatypes"][dt_ret]
	if (proto["ret"]["fixeddatatype"]):
		realdatatype = isa["datatypes"][proto["ret"]["fixeddatatype"]]
	p = build_type(proto["ret"]["type"], realdatatype, isa) + " " + func_name + "("
	cnt_reg = 0
	cnt_msk = 0
	cnt_val = 0
	cnt_ptr = 0
	is_first = True
	for arg in proto["args"]:
		if not is_first:
			p += ", "
		realdatatype = isa["datatypes"][dt_par]
		if (arg["fixeddatatype"]):
			realdatatype = isa["datatypes"][arg["fixeddatatype"]]
		p += build_type(arg["type"], realdatatype, isa)
		if arg["type"] == "reg":
			p += " r" + str(cnt_reg)
			cnt_reg = cnt_reg +1
		elif arg["type"] == "msk":
			p += " m" + str(cnt_msk)
			cnt_msk = cnt_msk +1
		elif arg["type"] == "val":
			p += " v" + str(cnt_val)
			cnt_val = cnt_val +1
		elif arg["type"] == "ptr":
			p += " p" + str(cnt_ptr)
			cnt_ptr = cnt_ptr +1
		is_first = False
	return p + ")";

def build_func_name_short(isa, dt, mipp_name):
	param_type = isa["datatypes"][dt]["category"] + str(isa["datatypes"][dt]["n_bits"])
	return "mipp_" + isa["name"] + "_" + mipp_name + "_" +  param_type

def build_func_name(isa, dt_par, dt_ret, mipp_name):
	param_type = isa["datatypes"][dt_par]["category"] + str(isa["datatypes"][dt_par]["n_bits"])
	return_type = isa["datatypes"][dt_ret]["category"] + str(isa["datatypes"][dt_ret]["n_bits"])
	return "mipp_" + isa["name"] + "_" + mipp_name + "_" + param_type + "_" + return_type

def build_ifdef_contents(funcs, func_name, dt_key, logi="&&"):
	str_ifdef = ""
	defines = []
	if "implem_status" in funcs[func_name]:
		if dt_key in funcs[func_name]["implem_status"]:
			if funcs[func_name]["implem_status"][dt_key]:
				defines = funcs[func_name]["implem_status"][dt_key]
	if defines:
		is_first = True
		for define in defines:
			if not is_first:
				str_ifdef = str_ifdef + " " + logi + " "
			str_ifdef = str_ifdef + "(" + define + ")"
			is_first = False
	return str_ifdef

def convert_ir(ir, isa, funcs, func_name, dt_par, dt_ret):
	dt_key = dt_par + "," + dt_ret
	converted_ir = ir

	ar_substitute = re.findall(r'\%(.*)\%', ir)

	for s in ar_substitute:
		item_type = s.split('<')[0]

		if item_type == "r":
			dt_info = re.findall(r'\<([^]]*)\>', s)[0]
			# print("dt_info: " + dt_info)
			dt_info_params = dt_info.split(",")
			dt = ""
			if len(dt_info_params) == 1:
				dt_info_carac = dt_info_params[0].split("|")
				if len(dt_info_carac) == 1 and dt_info_carac[0] == "tp":
					dt = dt_par
					# print("dt: " + dt)

			if dt not in isa["datatypes"]:
				print("Panic: '" + dt + "' is not available.")
				exit(-1)

			converted_ir = converted_ir.replace("%" + s + "%", build_reg(isa["datatypes"][dt], isa))

		else:
			f_name = item_type
			# print("f_name: " + f_name)

			if f_name not in funcs:
				print("Panic: '" + f_name + "' is not in the available MIPP functions.")
				exit(-1)

			fdt_key = ""

			dt_info = re.findall(r'\<([^]]*)\>', s)[0]
			# print("dt_info: " + dt_info)
			dt_info_params = dt_info.split(",")
			if len(dt_info_params) == 1:
				dt_info_carac = dt_info_params[0].split("|")
				if len(dt_info_carac) == 1 and dt_info_carac[0] == "tp":
					fdt_key = dt_par + "," + dt_par
					# print("fdt_key: " + fdt_key)

				f_full_name = build_func_name_short(isa, dt_par, f_name);

			if "implem_status" not in funcs[f_name] or fdt_key not in funcs[f_name]["implem_status"]:
				print("Panic: '" + f_name + "<" + fdt_key + ">' is not in the available MIPP functions.")
				exit(-1)

			if len(funcs[f_name]["implem_status"]) > 0:
				if "implem_status" not in funcs[func_name]:
					funcs[func_name]["implem_status"] = {}
				if fdt_key not in funcs[func_name]["implem_status"]:
					funcs[func_name]["implem_status"][fdt_key] = []
				for ifdef in funcs[f_name]["implem_status"][fdt_key]:
					funcs[func_name]["implem_status"][fdt_key].append(ifdef)

			converted_ir = converted_ir.replace("%" + s + "%", f_full_name)


	# if len(ar_substitute) :
	# 	print("func_name: " + func_name + "<par=" + dt_par + ",ret=" + dt_ret + ">")
	# 	print(ar_substitute)
	# 	# print("requirements: ", end='')
	# 	# print(requirements)
	# 	print("")

	return converted_ir

# =============================================================================
# =============================================================================
# =============================================================================

def gen_defines(isa, file):
	template = """#define MIPP_MACRO_{{ type_category_upper }}{{ datatype.n_bits }}(MACRO, ...) MACRO(__VA_ARGS__, {{ datatype.n_bits }}, {{ datatype.category }}, {{ datatype.data_ext }}, {{ datatype.data_ext_logi }}, {{ isa.casts.to_ptr[datatype.name] }})"""
	j2_template = Template(template, undefined=StrictUndefined)

	for dt in isa["datatypes"]:
		print(j2_template.render(isa=isa, type_category_upper=isa["datatypes"][dt]["category"].upper(), datatype=isa["datatypes"][dt]), file=file)

	print("#define MIPP_" + isa["name"].upper() + "_RVD_SIZE_BIT " + str(isa["size"]), file=file)
	print("#define MIPP_" + isa["name"].upper() + "_RVD_SIZE_BYTE " + str(int(isa["size"] / 8)), file=file)

	template = """#define MIPP_{{isa_name_upper}}_N_{{type_category_upper}}{{n_bits}} {{n_elmts}}"""
	j2_template = Template(template, undefined=StrictUndefined)

	for dt in isa["datatypes"]:
		n_elmts = int(isa["size"] / isa["datatypes"][dt]["n_bits"])
		print(j2_template.render(isa_name_upper=isa["name"].upper(), type_category_upper=isa["datatypes"][dt]["category"].upper(), n_bits=isa["datatypes"][dt]["n_bits"], n_elmts=n_elmts), file=file)

def gen_structures(isa, file):
	template = """typedef struct { {{ datatype.reg }} m; } rvd_{{ isa.name }}_{{ datatype.category }}{{ datatype.n_bits }}_t;"""
	j2_template = Template(template, undefined=StrictUndefined)

	for dt in isa["datatypes"]:
		print(j2_template.render(isa=isa, datatype=isa["datatypes"][dt]), file=file)

	template = """typedef struct { {{ datatype.msk }} m; } rvm_{{ isa.name }}_{{ datatype.category }}{{ datatype.n_bits }}_t;"""
	j2_template = Template(template, undefined=StrictUndefined)

	for dt in isa["datatypes"]:
		print(j2_template.render(isa=isa, datatype=isa["datatypes"][dt]), file=file)

def gen_native_functions(isa, file, funcs):
	tpl_implem_avx = {
		"cast":         { "format": "short", "code": "{% if dt_par.data_ext_logi != dt_ret.data_ext_logi -%}{{ isa.prefix }}_{{ instr_name }}{{dt_par.data_ext_logi}}_{{dt_ret.data_ext_logi}}(r0.m);{% else -%} r0.m;{% endif %}" },
		"cast_m":       { "format": "short", "code": "m0.m;" },
		"toreg":        { "format": "short", "code": "{% if dt_par.data_ext_msk != dt_ret.data_ext_logi -%}{{ isa.prefix }}_{{ instr_name }}{{dt_par.data_ext_msk}}_{{dt_ret.data_ext_logi}}(m0.m);{% else -%} m0.m;{% endif %}" },
		"tomsk":        { "format": "short", "code": "{% if dt_par.data_ext_logi != dt_ret.data_ext_msk -%}{{ isa.prefix }}_{{ instr_name }}{{dt_par.data_ext_logi}}_{{dt_ret.data_ext_msk}}(r0.m);{% else -%} r0.m;{% endif %}" },
		"load":         { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_{{ dt_par.data_ext_logi }}(({{ isa.casts.to_ptr[dt_par.name] }}*) p0);" },
		"store":        { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_{{ dt_par.data_ext_logi }}(({{ isa.casts.to_ptr[dt_par.name]}}*) p0, r0.m);" },
		"set0":         { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_{{ dt_par.data_ext_logi }}();" },
		"set0_m":       { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_{{ dt_par.data_ext_msk }}();" },
		"set1":         { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_{{ dt_par.data_ext }}(v0);" },
		"set1x":        { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_{{ dt_par.data_ext }}x(v0);" },
		"arith_1arg":   { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_{{ dt_par.data_ext }}(r0.m);" },
		"arith_2args":  { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_{{ dt_par.data_ext }}(r0.m, r1.m);" },
		"logi_2args":   { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_{{ dt_par.data_ext_logi }}(r0.m, r1.m);" },
		"logi_m_2args": { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_{{ dt_par.data_ext_msk }}(m0.m, m1.m);" },
		"arith_3args":  { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_{{ dt_par.data_ext }}(r0.m, r1.m, r2.m);" },
		"shift_2args":  { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_{{ dt_par.data_ext }}(r0.m, v0);" },
		"cmpeq_float":  { "format": "long", "code":
"""	%r<tp>% tmp;
	tmp.m = {{ isa.prefix }}_{{ instr_name }}_{{ dt_par.data_ext }}(r0.m, r1.m, _CMP_EQ_OQ);
	return %tomsk<tp>%(tmp);""" },
		"cmpneq_float": { "format": "long", "code":
"""	%r<tp>% tmp;
	tmp.m = {{ isa.prefix }}_{{ instr_name }}_{{ dt_par.data_ext }}(r0.m, r1.m, _CMP_NEQ_OQ);
	return %tomsk<tp>%(tmp);""" },
		"cmpgt_float":  { "format": "long", "code":
"""	%r<tp>% tmp;
	tmp.m = {{ isa.prefix }}_{{ instr_name }}_{{ dt_par.data_ext }}(r0.m, r1.m, _CMP_GT_OS);
	return %tomsk<tp>%(tmp);""" },
		"cmpge_float":  { "format": "long", "code":
"""	%r<tp>% tmp;
	tmp.m = {{ isa.prefix }}_{{ instr_name }}_{{ dt_par.data_ext }}(r0.m, r1.m, _CMP_GE_OS);
	return %tomsk<tp>%(tmp);""" },
		"cmple_float":  { "format": "long", "code":
"""	%r<tp>% tmp;
	tmp.m = {{ isa.prefix }}_{{ instr_name }}_{{ dt_par.data_ext }}(r0.m, r1.m, _CMP_LE_OS);
	return %tomsk<tp>%(tmp);""" },
		"cmplt_float":  { "format": "long", "code":
"""	%r<tp>% tmp;
	tmp.m = {{ isa.prefix }}_{{ instr_name }}_{{ dt_par.data_ext }}(r0.m, r1.m, _CMP_LT_OS);
	return %tomsk<tp>%(tmp);""" },
		"cmp_int":      { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_{{ dt_par.data_ext }}(r0.m, r1.m);" },
		"blend_float":  { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_{{ dt_par.data_ext }}(r0.m, r1.m, %toreg<tp>%(m0).m);" },
		"blend_int":    { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_epi8(r0.m, r1.m, m0.m);" },
	}

	implems = {
		"cast": {
			"implem": [
				{ "instr_name": "cast", "datatypes": all_datatypes_cart_prod, "template": tpl_implem_avx["cast"], }], },
		"cast_m": {
			"implem": [
				{ "instr_name": "cast", "datatypes": all_datatypes_cart_prod, "template": tpl_implem_avx["cast_m"], }], },
		"toreg": {
			"implem": [
				{ "instr_name": "cast", "datatypes": all_datatypes, "template": tpl_implem_avx["toreg"], }], },
		"tomsk": {
			"implem": [
				{ "instr_name": "cast", "datatypes": all_datatypes, "template": tpl_implem_avx["tomsk"], }], },
		"load": {
			"implem": [
				{ "instr_name": "load", "datatypes": all_datatypes, "template": tpl_implem_avx["load"], "if": "defined(MIPP_ALIGNED_LOADS)" },
				{ "instr_name": "loadu", "datatypes": all_datatypes, "template": tpl_implem_avx["load"], "if": "!defined(MIPP_ALIGNED_LOADS)" }], },
		"loadu": {
			"implem": [
				{ "instr_name": "loadu", "datatypes": all_datatypes, "template": tpl_implem_avx["load"] }], },
		"store": {
			"implem": [
				{ "instr_name": "store", "datatypes": all_datatypes, "template": tpl_implem_avx["store"], "if": "defined(MIPP_ALIGNED_LOADS)" },
				{ "instr_name": "storeu", "datatypes": all_datatypes, "template": tpl_implem_avx["store"], "if": "!defined(MIPP_ALIGNED_LOADS)" }] },
		"storeu": {
			"implem": [
				{ "instr_name": "storeu", "datatypes": all_datatypes, "template": tpl_implem_avx["store"] }] },
		"set1": {
			"implem": [
				{ "instr_name": "set1", "datatypes": all_float, "template": tpl_implem_avx["set1"] },
				{ "instr_name": "set1", "datatypes": ["int64"], "template": tpl_implem_avx["set1x"] },
				{ "instr_name": "set1", "datatypes": ["int32", "int16", "int8"], "template": tpl_implem_avx["set1"] }], },
		"set0": {
			"implem": [
				{ "instr_name": "setzero", "datatypes": all_datatypes, "template": tpl_implem_avx["set0"] }], },
		"set0_m": {
			"implem": [
				{ "instr_name": "setzero", "datatypes": all_datatypes, "template": tpl_implem_avx["set0_m"] }], },
		"sqrt": {
			"implem": [
				{ "instr_name": "sqrt", "datatypes": all_float, "template": tpl_implem_avx["arith_1arg"] }], },
		"rsqrt": {
			"implem": [
				{ "instr_name": "rsqrt", "datatypes": ["float32"], "template": tpl_implem_avx["arith_1arg"] }], },
		"add": {
			"implem": [
				{ "instr_name": "add", "datatypes": all_float, "template": tpl_implem_avx["arith_2args"] },
				{ "instr_name": "add", "datatypes": ["int64", "int32"], "template": tpl_implem_avx["arith_2args"], "if": "defined(__AVX2__)" },
				{ "instr_name": "adds", "datatypes": ["int16", "int8", "uint16", "uint8"], "template": tpl_implem_avx["arith_2args"], "if": "defined(__AVX2__)" }], },
		"sub": {
			"implem": [
				{ "instr_name": "sub", "datatypes": all_float, "template": tpl_implem_avx["arith_2args"] },
				{ "instr_name": "sub", "datatypes": ["int64", "int32"], "template": tpl_implem_avx["arith_2args"], "if": "defined(__AVX2__)" },
				{ "instr_name": "subs", "datatypes": ["int16", "int8", "uint16", "uint8"], "template": tpl_implem_avx["arith_2args"], "if": "defined(__AVX2__)" }], },
		"mul": {
			"implem": [
				{ "instr_name": "mul", "datatypes": all_float, "template": tpl_implem_avx["arith_2args"] },
				{ "instr_name": "mullo", "datatypes": ["int32", "int16"], "template": tpl_implem_avx["arith_2args"], "if": "defined(__AVX2__)" }], },
		"div": {
			"implem" : [
				{ "instr_name": "div", "datatypes": all_float, "template": tpl_implem_avx["arith_2args"] }], },
		"min": {
			"implem": [
				{ "instr_name": "min", "datatypes": all_float, "template": tpl_implem_avx["arith_2args"] },
				{ "instr_name": "min", "datatypes": ["int32", "int16", "int8", "uint32", "uint16", "uint8"], "template": tpl_implem_avx["arith_2args"], "if": "defined(__AVX2__)" }], },
		"max": {
			"implem": [
				{ "instr_name": "max", "datatypes": all_float, "template": tpl_implem_avx["arith_2args"] },
				{ "instr_name": "max", "datatypes": ["int32", "int16", "int8", "uint32", "uint16", "uint8"], "template": tpl_implem_avx["arith_2args"], "if": "defined(__AVX2__)" }], },
		"fmadd": {
			"implem": [
				{ "instr_name": "fmadd", "datatypes": all_float, "template": tpl_implem_avx["arith_3args"], "if": "defined(__FMA__)" }], },
		"fnmadd": {
			"implem": [
				{ "instr_name": "fnmadd", "datatypes": all_float, "template": tpl_implem_avx["arith_3args"], "if": "defined(__FMA__)" }], },
		"fmsub": {
			"implem": [
				{ "instr_name": "fmsub", "datatypes": all_float, "template": tpl_implem_avx["arith_3args"], "if": "defined(__FMA__)" }], },
		"fnmsub": {
			"implem": [
				{ "instr_name": "fnmsub", "datatypes": all_float, "template": tpl_implem_avx["arith_3args"], "if": "defined(__FMA__)" }], },
		"andb": {
			"implem": [
				{ "instr_name": "and", "datatypes": all_float, "template": tpl_implem_avx["logi_2args"] },
				{ "instr_name": "and", "datatypes": all_int_uint, "template": tpl_implem_avx["logi_2args"], "if": "defined(__AVX2__)" }] },
		"andb_m": {
			"implem": [
				{ "instr_name": "and", "datatypes": all_datatypes, "template": tpl_implem_avx["logi_m_2args"], "if": "defined(__AVX2__)" }], },
		"andnb": {
			"implem" : [
				{ "instr_name": "andnot", "datatypes": all_float, "template": tpl_implem_avx["logi_2args"] },
				{ "instr_name": "andnot", "datatypes": all_int_uint, "template": tpl_implem_avx["logi_2args"], "if": "defined(__AVX2__)" }], },
		"andnb_m": {
			"implem": [
				{ "instr_name": "andnot", "datatypes": all_datatypes, "template": tpl_implem_avx["logi_m_2args"], "if": "defined(__AVX2__)" }], },
		"orb": {
			"implem": [
				{ "instr_name": "or", "datatypes": all_float, "template": tpl_implem_avx["logi_2args"] },
				{ "instr_name": "or", "datatypes": all_int_uint, "template": tpl_implem_avx["logi_2args"], "if": "defined(__AVX2__)" }], },
		"orb_m": {
			"implem": [
				{ "instr_name": "or", "datatypes": all_datatypes, "template": tpl_implem_avx["logi_m_2args"], "if": "defined(__AVX2__)" }], },
		"xorb": {
			"implem": [
				{ "instr_name": "xor", "datatypes": all_float, "template": tpl_implem_avx["logi_2args"] },
				{ "instr_name": "xor", "datatypes": all_int_uint, "template": tpl_implem_avx["logi_2args"], "if": "defined(__AVX2__)" }], },
		"xorb_m": {
			"implem": [
				{ "instr_name": "xor", "datatypes": all_datatypes, "template": tpl_implem_avx["logi_m_2args"], "if": "defined(__AVX2__)" }], },
		"lshiftr": {
			"implem": [
				{ "instr_name": "sllv", "datatypes": ["int64", "int32"], "template": tpl_implem_avx["arith_2args"], "if": "defined(__AVX2__)" }], },
		"rshiftr": {
			"implem": [
				{ "instr_name": "srlv", "datatypes": ["int64", "int32"], "template": tpl_implem_avx["arith_2args"], "if": "defined(__AVX2__)" }], },
		"lshift": {
			"implem": [
				{ "instr_name": "slli", "datatypes": ["int64", "int32", "int16"], "template": tpl_implem_avx["shift_2args"], "if": "defined(__AVX2__)" }], },
		"rshift": {
			"implem": [
				{ "instr_name": "srli", "datatypes": ["int64", "int32", "int16"], "template": tpl_implem_avx["shift_2args"], "if": "defined(__AVX2__)" }], },
		"cmpeq": {
			"implem": [
				{ "instr_name": "cmp", "datatypes": all_float, "template": tpl_implem_avx["cmpeq_float"], },
				{ "instr_name": "cmpeq", "datatypes": all_int, "template": tpl_implem_avx["cmp_int"], "if": "defined(__AVX2__)" }], },
		"cmpneq": {
			"implem": [
				{ "instr_name": "cmp", "datatypes": all_float, "template": tpl_implem_avx["cmpneq_float"], }], },
		"cmplt": {
			"implem": [
				{ "instr_name": "cmp", "datatypes": all_float, "template": tpl_implem_avx["cmplt_float"], }], },
		"cmple": {
			"implem": [
				{ "instr_name": "cmp", "datatypes": all_float, "template": tpl_implem_avx["cmple_float"], }], },
		"cmpge": {
			"implem": [
				{ "instr_name": "cmp", "datatypes": all_float, "template": tpl_implem_avx["cmpge_float"], }], },
		"cmpgt": {
			"implem": [
				{ "instr_name": "cmp", "datatypes": all_float, "template": tpl_implem_avx["cmpgt_float"], },
				{ "instr_name": "cmpgt", "datatypes": all_int, "template": tpl_implem_avx["cmp_int"], "if": "defined(__AVX2__)" }], },
		"blend": {
			"implem": [
				{ "instr_name": "blendv", "datatypes": all_float, "template": tpl_implem_avx["blend_float"], },
				{ "instr_name": "blendv", "datatypes": all_int_uint, "template": tpl_implem_avx["blend_int"], "if": "defined(__AVX2__)", }], },
	}

	for f in implems:
		for ff in implems[f]["implem"]:
			for dt in ff["datatypes"]:
				if len(dt.split(',')) <= 1:
					dt_par = dt.split(',')[0]
					dt_ret = dt.split(',')[0]
				else:
					dt_par = dt.split(',')[0]
					dt_ret = dt.split(',')[1]
				dt_key = dt_par + "," + dt_ret

				if "implem_status" not in funcs[f]:
					funcs[f]["implem_status"] = {}
				if dt_key not in funcs[f]["implem_status"]:
					funcs[f]["implem_status"][dt_key] = []
				if "if" in ff:
					if ff["if"] not in funcs[f]["implem_status"][dt_key]:
						funcs[f]["implem_status"][dt_key].append(ff["if"])

				j2_template = Template(ff["template"]["code"], undefined=StrictUndefined)
				pre_rendering = j2_template.render(isa=isa, instr_name=ff["instr_name"], dt_par=isa["datatypes"][dt_par], dt_ret=isa["datatypes"][dt_ret])
				post_rendering = convert_ir(pre_rendering, isa, funcs, f, dt_par, dt_ret)

				if "if" in ff:
					print("#if " + ff["if"], file=file)
				if len(dt.split(',')) <= 1:
					func_name = build_func_name_short(isa, dt_par, f);
				else:
					func_name = build_func_name(isa, dt_par, dt_ret, f);
				print(build_proto(funcs[f]["proto"], dt_par, dt_ret, isa, func_name) + " {", file=file)

				if ff["template"]["format"] == "short":
					if funcs[f]["proto"]["ret"]["type"]:
						print("\t" + build_type(funcs[f]["proto"]["ret"]["type"], isa["datatypes"][dt_ret], isa) + " res;", file=file);
						print("\tres.m = ", end='', file=file)
					else:
						print("\t", end='', file=file)
				print(post_rendering, file=file)
				if ff["template"]["format"] == "short":
					if funcs[f]["proto"]["ret"]["type"]:
						print("\treturn res;", file=file);
				print("}", file=file)
				if "if" in ff:
					print("#endif // " + ff["if"], file=file)

	# # debug
	# fj = open("dbg.json", "w")
	# json_object = json.dumps(funcs, indent = 4)
	# print(json_object, file=fj)
	# fj.close()

	return funcs

def gen_emulated_functions(isa, file, funcs):
	print("TODO gen_emulated_functions")

	return funcs

def gen_missing_functions(isa, file, funcs):
	for f in funcs:
		for dt in funcs[f]["datatypes"]:
			if len(dt.split(',')) <= 1:
				dt_par = dt.split(',')[0]
				dt_ret = dt.split(',')[0]
			else:
				dt_par = dt.split(',')[0]
				dt_ret = dt.split(',')[1]
			dt_key = dt_par + "," + dt_ret
			defines = []

			is_missing = False
			if "implem_status" in funcs[f]:
				if dt_key in funcs[f]["implem_status"]:
					if len(funcs[f]["implem_status"][dt_key]) > 0:
						is_missing = True
				else:
					is_missing = True
			else:
				is_missing = True

			if is_missing:
				ifdef = build_ifdef_contents(funcs, f, dt_key, "||")
				if ifdef != "":
					print("#if !( " + ifdef + " )", file=file)

				if len(dt.split(',')) <= 1:
					func_name = build_func_name_short(isa, dt_par, f)
				else:
					func_name = build_func_name(isa, dt_par, dt_ret, f)
				print(build_proto(funcs[f]["proto"], dt_par, dt_ret, isa, func_name) + " {", file=file)
				print("\tprintf(\"MIPP panic: '%s' is unimplemented.\\n\", \""+func_name+"\");", file=file);
				print("\texit(-1);", file=file);
				print("}", file=file);

				if ifdef != "":
					print("#endif // !( " + ifdef + ")", file=file)

# =============================================================================
# ======================================================================== MAIN
# =============================================================================
protos = {
	"ret_reg_1arg_ptr": {
		"ret" :
			{"type": "reg", "charac": "WO", "fixeddatatype": False},
		"args" : [
			{"type": "ptr", "charac": "RO", "fixeddatatype": False}
		]
	},
	"ret_void_2args_ptr_reg": {
		"ret" :
			{"type": False, "fixeddatatype": False},
		"args" : [
			{"type": "ptr", "charac": "WO", "fixeddatatype": False},
			{"type": "reg", "charac": "RO", "fixeddatatype": False}
		]
	},
	"ret_reg_1arg_val": {
		"ret" :
			{"type": "reg", "charac": "WO", "fixeddatatype": False},
		"args" : [
			{"type": "val", "charac": "RO", "fixeddatatype": False}
		]
	},
	"ret_msk_1arg_val": {
		"ret" :
			{"type": "msk", "charac": "WO", "fixeddatatype": False},
		"args" : [
			{"type": "val", "charac": "RO", "fixeddatatype": False}
		]
	},
	"ret_reg_0arg": {
		"ret" :
			{"type": "reg", "charac": "WO", "fixeddatatype": False},
		"args" : []
	},
	"ret_msk_0arg": {
		"ret" :
			{"type": "msk", "charac": "WO", "fixeddatatype": False},
		"args" : []
	},
	"ret_reg_1arg_reg": {
		"ret" :
			{"type": "reg", "charac": "WO", "fixeddatatype": False},
		"args" : [
			{"type": "reg", "charac": "RO", "fixeddatatype": False},
		]
	},
	"ret_msk_1arg_msk": {
		"ret" :
			{"type": "msk", "charac": "WO", "fixeddatatype": False},
		"args" : [
			{"type": "msk", "charac": "RO", "fixeddatatype": False},
		]
	},
	"ret_msk_1arg_reg": {
		"ret" :
			{"type": "msk", "charac": "WO", "fixeddatatype": False},
		"args" : [
			{"type": "reg", "charac": "RO", "fixeddatatype": False},
		]
	},
	"ret_reg_1arg_msk": {
		"ret" :
			{"type": "reg", "charac": "WO", "fixeddatatype": False},
		"args" : [
			{"type": "msk", "charac": "RO", "fixeddatatype": False},
		]
	},
	"ret_reg_2args_reg": {
		"ret" :
			{"type": "reg", "charac": "WO", "fixeddatatype": False},
		"args" : [
			{"type": "reg", "charac": "RO", "fixeddatatype": False},
			{"type": "reg", "charac": "RO", "fixeddatatype": False},
		]
	},
	"ret_msk_2args_reg": {
		"ret" :
			{"type": "msk", "charac": "WO", "fixeddatatype": False},
		"args" : [
			{"type": "reg", "charac": "RO", "fixeddatatype": False},
			{"type": "reg", "charac": "RO", "fixeddatatype": False},
		]
	},
	"ret_msk_2args_msk": {
		"ret" :
			{"type": "msk", "charac": "WO", "fixeddatatype": False},
		"args" : [
			{"type": "msk", "charac": "RO", "fixeddatatype": False},
			{"type": "msk", "charac": "RO", "fixeddatatype": False},
		]
	},
	"ret_reg_2args_reg_val": {
		"ret" :
			{"type": "reg", "charac": "WO", "fixeddatatype": False},
		"args" : [
			{"type": "reg", "charac": "RO", "fixeddatatype": False},
			{"type": "val", "charac": "RO", "fixeddatatype": "int32"},
		]
	},
	"ret_reg_3args_reg": {
		"ret" :
			{"type": "reg", "charac": "WO", "fixeddatatype": False},
		"args" : [
			{"type": "reg", "charac": "RO", "fixeddatatype": False},
			{"type": "reg", "charac": "RO", "fixeddatatype": False},
			{"type": "reg", "charac": "RO", "fixeddatatype": False},
		]
	},
	"ret_reg_3args_2reg_1msk": {
		"ret" :
			{"type": "reg", "charac": "WO", "fixeddatatype": False},
		"args" : [
			{"type": "reg", "charac": "RO", "fixeddatatype": False},
			{"type": "reg", "charac": "RO", "fixeddatatype": False},
			{"type": "msk", "charac": "RO", "fixeddatatype": False},
		]
	},
}

mipp_funcs = {
	"cast":    { "name": "cast",    "proto": protos["ret_reg_1arg_reg"       ], "datatypes": all_datatypes_cart_prod },
	"cast_m":  { "name": "cast",    "proto": protos["ret_msk_1arg_msk"       ], "datatypes": all_datatypes_cart_prod },
	"toreg":   { "name": "toreg",   "proto": protos["ret_reg_1arg_msk"       ], "datatypes": all_datatypes           },
	"tomsk":   { "name": "tomsk",   "proto": protos["ret_msk_1arg_reg"       ], "datatypes": all_datatypes           },
	"load":    { "name": "load",    "proto": protos["ret_reg_1arg_ptr"       ], "datatypes": all_datatypes           },
	"loadu":   { "name": "loadu",   "proto": protos["ret_reg_1arg_ptr"       ], "datatypes": all_datatypes           },
	"store":   { "name": "store",   "proto": protos["ret_void_2args_ptr_reg" ], "datatypes": all_datatypes           },
	"storeu":  { "name": "storeu",  "proto": protos["ret_void_2args_ptr_reg" ], "datatypes": all_datatypes           },
	"set1":    { "name": "set1",    "proto": protos["ret_reg_1arg_val"       ], "datatypes": all_datatypes           },
	"set0":    { "name": "set0",    "proto": protos["ret_reg_0arg"           ], "datatypes": all_datatypes           },
	"set0_m":  { "name": "set0_m",  "proto": protos["ret_msk_0arg"           ], "datatypes": all_datatypes           },
	"sqrt":    { "name": "sqrt",    "proto": protos["ret_reg_1arg_reg"       ], "datatypes": all_datatypes           },
	"rsqrt":   { "name": "rsqrt",   "proto": protos["ret_reg_1arg_reg"       ], "datatypes": all_datatypes           },
	"add":     { "name": "add",     "proto": protos["ret_reg_2args_reg"      ], "datatypes": all_datatypes           },
	"sub":     { "name": "sub",     "proto": protos["ret_reg_2args_reg"      ], "datatypes": all_datatypes           },
	"mul":     { "name": "mul",     "proto": protos["ret_reg_2args_reg"      ], "datatypes": all_datatypes           },
	"div":     { "name": "div",     "proto": protos["ret_reg_2args_reg"      ], "datatypes": all_datatypes           },
	"min":     { "name": "min",     "proto": protos["ret_reg_2args_reg"      ], "datatypes": all_datatypes           },
	"max":     { "name": "max",     "proto": protos["ret_reg_2args_reg"      ], "datatypes": all_datatypes           },
	"fmadd":   { "name": "fmadd",   "proto": protos["ret_reg_3args_reg"      ], "datatypes": all_datatypes           },
	"fnmadd":  { "name": "fnmadd",  "proto": protos["ret_reg_3args_reg"      ], "datatypes": all_datatypes           },
	"fmsub":   { "name": "fmsub",   "proto": protos["ret_reg_3args_reg"      ], "datatypes": all_datatypes           },
	"fnmsub":  { "name": "fnmsub",  "proto": protos["ret_reg_3args_reg"      ], "datatypes": all_datatypes           },
	"andb":    { "name": "andb",    "proto": protos["ret_reg_2args_reg"      ], "datatypes": all_datatypes           },
	"andb_m":  { "name": "andb_m",  "proto": protos["ret_msk_2args_msk"      ], "datatypes": all_datatypes           },
	"andnb":   { "name": "andnb",   "proto": protos["ret_reg_2args_reg"      ], "datatypes": all_datatypes           },
	"andnb_m": { "name": "andnb_m", "proto": protos["ret_msk_2args_msk"      ], "datatypes": all_datatypes           },
	"orb":     { "name": "orb",     "proto": protos["ret_reg_2args_reg"      ], "datatypes": all_datatypes           },
	"orb_m":   { "name": "orb_m",   "proto": protos["ret_msk_2args_msk"      ], "datatypes": all_datatypes           },
	"xorb":    { "name": "xorb",    "proto": protos["ret_reg_2args_reg"      ], "datatypes": all_datatypes           },
	"xorb_m":  { "name": "xorb_m",  "proto": protos["ret_msk_2args_msk"      ], "datatypes": all_datatypes           },
	"lshiftr": { "name": "lshiftr", "proto": protos["ret_reg_2args_reg"      ], "datatypes": all_datatypes           },
	"rshiftr": { "name": "rshiftr", "proto": protos["ret_reg_2args_reg"      ], "datatypes": all_datatypes           },
	"lshift":  { "name": "lshift",  "proto": protos["ret_reg_2args_reg_val"  ], "datatypes": all_datatypes           },
	"rshift":  { "name": "rshift",  "proto": protos["ret_reg_2args_reg_val"  ], "datatypes": all_datatypes           },
	"cmpeq":   { "name": "cmpeq",   "proto": protos["ret_msk_2args_reg"      ], "datatypes": all_datatypes           },
	"cmpneq":  { "name": "cmpneq",  "proto": protos["ret_msk_2args_reg"      ], "datatypes": all_datatypes           },
	"cmplt":   { "name": "cmplt",   "proto": protos["ret_msk_2args_reg"      ], "datatypes": all_datatypes           },
	"cmple":   { "name": "cmple",   "proto": protos["ret_msk_2args_reg"      ], "datatypes": all_datatypes           },
	"cmpge":   { "name": "cmpge",   "proto": protos["ret_msk_2args_reg"      ], "datatypes": all_datatypes           },
	"cmpgt":   { "name": "cmpgt",   "proto": protos["ret_msk_2args_reg"      ], "datatypes": all_datatypes           },
	"blend":   { "name": "blend",   "proto": protos["ret_reg_3args_2reg_1msk"], "datatypes": all_datatypes           },
}

isa_avx = {
	"name": "avx",
	"prefix": "_mm256",
	"size": 256,
	"datatypes": {
		"float64" : { "name" : "float64", "category": "float", "n_bits" : 64, "data_ext" :    "pd", "data_ext_logi":    "pd", "data_ext_msk": "si256", "reg" : "__m256d", "msk" : "__m256i" },
		"float32" : { "name" : "float32", "category": "float", "n_bits" : 32, "data_ext" :    "ps", "data_ext_logi":    "ps", "data_ext_msk": "si256", "reg" : " __m256", "msk" : "__m256i" },
		  "int64" : { "name" :   "int64", "category":   "int", "n_bits" : 64, "data_ext" : "epi64", "data_ext_logi": "si256", "data_ext_msk": "si256", "reg" : "__m256i", "msk" : "__m256i" },
		  "int32" : { "name" :   "int32", "category":   "int", "n_bits" : 32, "data_ext" : "epi32", "data_ext_logi": "si256", "data_ext_msk": "si256", "reg" : "__m256i", "msk" : "__m256i" },
		  "int16" : { "name" :   "int16", "category":   "int", "n_bits" : 16, "data_ext" : "epi16", "data_ext_logi": "si256", "data_ext_msk": "si256", "reg" : "__m256i", "msk" : "__m256i" },
		   "int8" : { "name" :    "int8", "category":   "int", "n_bits" :  8, "data_ext" :  "epi8", "data_ext_logi": "si256", "data_ext_msk": "si256", "reg" : "__m256i", "msk" : "__m256i" },
		 "uint64" : { "name" :  "uint64", "category":  "uint", "n_bits" : 64, "data_ext" : "epu64", "data_ext_logi": "si256", "data_ext_msk": "si256", "reg" : "__m256i", "msk" : "__m256i" },
		 "uint32" : { "name" :  "uint32", "category":  "uint", "n_bits" : 32, "data_ext" : "epu32", "data_ext_logi": "si256", "data_ext_msk": "si256", "reg" : "__m256i", "msk" : "__m256i" },
		 "uint16" : { "name" :  "uint16", "category":  "uint", "n_bits" : 16, "data_ext" : "epu16", "data_ext_logi": "si256", "data_ext_msk": "si256", "reg" : "__m256i", "msk" : "__m256i" },
		  "uint8" : { "name" :   "uint8", "category":  "uint", "n_bits" :  8, "data_ext" :  "epu8", "data_ext_logi": "si256", "data_ext_msk": "si256", "reg" : "__m256i", "msk" : "__m256i" },
	},
	"casts": {
		"to_ptr": {
			"float64": "float64_t",
			"float32": "float32_t",
			  "int64":   "__m256i",
			  "int32":   "__m256i",
			  "int16":   "__m256i",
			   "int8":   "__m256i",
			 "uint64":   "__m256i",
			 "uint32":   "__m256i",
			 "uint16":   "__m256i",
			  "uint8":   "__m256i",
		},
	}
}

file = open("../include/mipp_v2_impl_AVX_gen.h", "w")

tpl_header_avx = """#ifndef MY_INTRINSICS_PLUS_PLUS_IMPL_GEN_AVX_H_
#define MY_INTRINSICS_PLUS_PLUS_IMPL_AVX_H_
#include "mipp_v2.h"
#include <immintrin.h>"""
j2_template = Template(tpl_header_avx, undefined=StrictUndefined)
print(j2_template.render(), file=file)

gen_defines(isa_avx, file)
gen_structures(isa_avx, file)
mipp_funcs = gen_native_functions(isa_avx, file, mipp_funcs)
mipp_funcs = gen_emulated_functions(isa_avx, file, mipp_funcs)
gen_missing_functions(isa_avx, file, mipp_funcs)

tpl_footer_avx = """#endif /* MY_INTRINSICS_PLUS_PLUS_IMPL_GEN_AVX_H_ */"""
j2_template = Template(tpl_footer_avx, undefined=StrictUndefined)
print(j2_template.render(), file=file)

file.close()