#!/usr/bin/env python3

from jinja2 import Template, StrictUndefined
import json
import re

cfloat = "float"
cint = "int"
cuint = "uint"

float64 = cfloat + "64"
float32 = cfloat + "32"
int64 = cint + "64"
int32 = cint + "32"
int16 = cint + "16"
int8 = cint + "8"
uint64 = cuint + "64"
uint32 = cuint + "32"
uint16 = cuint + "16"
uint8 = cuint + "8"

all_float = [float64, float32]
all_int = [int64, int32, int16, int8]
all_uint = [uint64, uint32, uint16, uint8]
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

def build_ifdef_rec(funcs, func_name, dt_key):
	str_ifdef = ""
	if "implem_status" in funcs[func_name]:
		if dt_key in funcs[func_name]["implem_status"]:
			is_first_or = True
			str_ifdef_sub = ""
			for implem in funcs[func_name]["implem_status"][dt_key]:
				if not is_first_or:
					str_ifdef_sub = str_ifdef_sub + " || "

				is_first_and = True
				str_ifdef_sub_sub = ""
				for f_name in implem["requirements"]:
					for fdt_key in implem["requirements"][f_name]:
						ret = build_ifdef_rec(funcs, f_name, fdt_key)
						if ret:
							if not is_first_and:
								str_ifdef_sub_sub = str_ifdef_sub_sub + " && "
							str_ifdef_sub_sub = str_ifdef_sub_sub + "( " + ret + " )"
							is_first_and = False

				if implem["if"] and str_ifdef_sub_sub:
					str_ifdef_sub = str_ifdef_sub + "( " + implem["if"] + " && (" + str_ifdef_sub_sub + ") )"
				if implem["if"] and not str_ifdef_sub_sub:
					str_ifdef_sub = str_ifdef_sub + "( " + implem["if"] + " )"
				if str_ifdef_sub_sub and not implem["if"]:
					str_ifdef_sub = str_ifdef_sub + "( " + str_ifdef_sub_sub + " )"

				if implem["if"] or str_ifdef_sub_sub:
					is_first_or = False

			if str_ifdef_sub:
				str_ifdef = "( " + str_ifdef_sub + " )"
	return str_ifdef

def is_ifdef(funcs, func_name, dt_key):
	ifdef = build_ifdef_rec(funcs, func_name, dt_key)
	if ifdef:
		return True
	else:
		return False

def is_fully_missing_func(funcs, func_name, dt_key):
	is_missing = False
	if "implem_status" in funcs[func_name]:
		if dt_key not in funcs[func_name]["implem_status"]:
			is_missing = True
	else:
		is_missing = True
	return is_missing

def is_missing_func(funcs, func_name, dt_key):
	return is_fully_missing_func(funcs, func_name, dt_key) or is_ifdef(funcs, func_name, dt_key)

def build_ifdef(funcs, func_name, dt_key, implem_id):
	str_ifdef = ""
	if "if" in funcs[func_name]["implem_status"][dt_key][implem_id]:
		str_ifdef = str_ifdef + funcs[func_name]["implem_status"][dt_key][implem_id]["if"]

	is_first_and = True
	str_ifdef_and = ""
	for f in funcs[func_name]["implem_status"][dt_key][implem_id]["requirements"]:
		for fdt in funcs[func_name]["implem_status"][dt_key][implem_id]["requirements"][f]:
			ret = build_ifdef_rec(funcs, f, fdt)
			if ret:
				if not is_first_and:
					str_ifdef_and = str_ifdef_and + " && "
				str_ifdef_and = str_ifdef_and + "( " + ret + " )"
				is_first_and = False

	if str_ifdef and str_ifdef_and:
		str_ifdef = str_ifdef + " && (" + str_ifdef_and + ")"
	if str_ifdef_and and not str_ifdef:
		str_ifdef = str_ifdef_and

	return str_ifdef

def build_dt(input_str, isa, dt_par, dt_ret):
	dt = ""
	dt_info_carac = input_str.split("|")
	if len(dt_info_carac) == 1:
		if dt_info_carac[0] == "tp":
			dt = dt_par
		elif dt_info_carac[0] == "tr":
			dt = dt_ret
	elif len(dt_info_carac) > 1:
		dt_info_carac_dic = {}
		for dtic in dt_info_carac:
			dt_info_carac_dic[dtic.split(':')[0]] = dtic.split(':')[1]

		if "c" in dt_info_carac_dic:
			if dt_info_carac_dic["c"] == "tp":
				dt += isa["datatypes"][dt_par]["category"]
			elif dt_info_carac_dic["c"] == "tr":
				dt += isa["datatypes"][dt_ret]["category"]
			elif dt_info_carac_dic["c"] == "int":
				dt += cint
			elif dt_info_carac_dic["c"] == "uint":
				dt += cuint
			elif dt_info_carac_dic["c"] == "float":
				dt += cfloat
			else:
				print("Panic: unknown datatype '" + dt_info_carac_dic["c"] + "'.")
				exit(-1)
		else:
			dt += isa["datatypes"][dt_par]["category"]

		if "b" in dt_info_carac_dic:
			if dt_info_carac_dic["b"] == "tp":
				dt += str(isa["datatypes"][dt_par]["n_bits"])
			elif dt_info_carac_dic["b"] == "tr":
				dt += str(isa["datatypes"][dt_ret]["n_bits"])
			elif dt_info_carac_dic["b"] == "64":
				dt += "64"
			elif dt_info_carac_dic["b"] == "32":
				dt += "32"
			elif dt_info_carac_dic["b"] == "16":
				dt += "16"
			elif dt_info_carac_dic["b"] == "8":
				dt += "8"
			else:
				print("Panic: unknown n_bits '" + dt_info_carac_dic["b"] + "'.")
				exit(-1)
		else:
			dt += str(isa["datatypes"][dt_par]["n_bits"])
	return dt

# for debug
def dump_dict_json(di, filename):
	# debug
	fj = open(filename, "w")
	json_object = json.dumps(di, indent = 4)
	print(json_object, file=fj)
	fj.close()

def parse_placeholders(ir, isa, funcs, func_name, dt_par, dt_ret):
	dt_key = dt_par + "," + dt_ret
	converted_ir = ir
	ar_substitute = re.findall(r'\%([^%]*)\%', ir)
	requirements = {}

	for s in ar_substitute:
		item_type = s.split('<')[0]

		if item_type == "r":
			dt_info = re.findall(r'\<(.*)\>', s)[0]
			# print("dt_info: " + dt_info)
			dt_info_params = dt_info.split(",")
			dt = ""
			if len(dt_info_params) == 1:
				dt = build_dt(dt_info_params[0], isa, dt_par, dt_ret)
			if dt not in isa["datatypes"]:
				print("Panic: '" + dt + "' is not available.")
				exit(-1)
			converted_ir = converted_ir.replace("%" + s + "%", build_reg(isa["datatypes"][dt], isa))

		elif item_type == "m":
			dt_info = re.findall(r'\<(.*)\>', s)[0]
			dt_info_params = dt_info.split(",")
			dt = ""
			if len(dt_info_params) == 1:
				dt = build_dt(dt_info_params[0], isa, dt_par, dt_ret)
			if dt not in isa["datatypes"]:
				print("Panic: '" + dt + "' is not available.")
				exit(-1)
			converted_ir = converted_ir.replace("%" + s + "%", build_msk(isa["datatypes"][dt], isa))

		else:
			f_name = item_type
			if f_name not in funcs:
				print("Panic: '" + f_name + "' is not in the available MIPP functions.")
				exit(-1)

			fdt_key = ""
			dt_info = re.findall(r'\<(.*)\>', s)[0]
			dt_info_params = dt_info.split(",")
			if len(dt_info_params) == 1:
				dt = build_dt(dt_info_params[0], isa, dt_par, dt_ret)
				fdt_key = dt + "," + dt
				f_full_name = build_func_name_short(isa, dt, f_name);

			elif len(dt_info_params) == 2:
				dt_1 = build_dt(dt_info_params[0], isa, dt_par, dt_ret)
				dt_2 = build_dt(dt_info_params[1], isa, dt_par, dt_ret)
				fdt_key = dt_1 + "," + dt_2
				f_full_name = build_func_name(isa, dt_1, dt_2, f_name);
			else:
				print("Panic: '" + f_name + "' has incompatible format.")
				exit(-1)

			if f_name not in funcs:
				print("Panic: '" + f_name + "' is not in the available MIPP functions.")
				exit(-1)

			if is_fully_missing_func(funcs, f_name, fdt_key):
				raise Exception("Warning: '" + f_name + "<" + fdt_key + ">' is not implemented.")

			if f_name not in requirements:
				requirements[f_name] = []
			if fdt_key not in requirements[f_name]:
				requirements[f_name].append(fdt_key)

			converted_ir = converted_ir.replace("%" + s + "%", f_full_name)

	ret_pack = { "converted_ir": converted_ir, "requirements": requirements }

	return ret_pack

# =============================================================================
# =============================================================================
# =============================================================================

def gen_defines(isa, file):
	template = """#define MIPP_MACRO_{{ type_category_upper }}{{ datatype.n_bits }}(MACRO, ...) MACRO(__VA_ARGS__, {{ datatype.n_bits }}, {{ datatype.category }}, {{ datatype.data_ext }}, {{ datatype.data_ext_logi }}, {{ datatype.to_ptr }})"""
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
		"load":         { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_{{ dt_par.data_ext_logi }}(({{ dt_par.to_ptr }}*) p0);" },
		"store":        { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_{{ dt_par.data_ext_logi }}(({{ dt_par.to_ptr }}*) p0, r0.m);" },
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
		"logi_2args_e": { "format": "long", "code":
"""	%r<c:float|b:32>% r0f = %cast<tp,c:float|b:32>%(r0);
	%r<c:float|b:32>% r1f = %cast<tp,c:float|b:32>%(r1);
	%r<c:float|b:32>% resf = %{{ instr_name }}<c:float|b:32>%(r0f, r1f);
	return %cast<c:float|b:32,tp>%(resf);"""
		},
		"logi_m_2args_e": { "format": "long", "code":
"""	%r<c:float|b:32>% r0f = %toreg<c:float|b:32>%(%cast_m<tp,c:float|b:32>%(m0));
	%r<c:float|b:32>% r1f = %toreg<c:float|b:32>%(%cast_m<tp,c:float|b:32>%(m1));
	%r<c:float|b:32>% resf = %{{ instr_name }}<c:float|b:32>%(r0f, r1f);
	return %tomsk<tp>%(%cast<c:float|b:32,tp>%(resf));"""
		},
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
				{ "instr_name": "set1", "datatypes": [int64], "template": tpl_implem_avx["set1x"] },
				{ "instr_name": "set1", "datatypes": [int32, int16, int8], "template": tpl_implem_avx["set1"] }], },
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
				{ "instr_name": "rsqrt", "datatypes": [float32], "template": tpl_implem_avx["arith_1arg"] }], },
		"add": {
			"implem": [
				{ "instr_name": "add", "datatypes": all_float, "template": tpl_implem_avx["arith_2args"] },
				{ "instr_name": "add", "datatypes": [int64, int32], "template": tpl_implem_avx["arith_2args"], "if": "defined(__AVX2__)" },
				{ "instr_name": "adds", "datatypes": [int16, int8, uint16, uint8], "template": tpl_implem_avx["arith_2args"], "if": "defined(__AVX2__)" }], },
		"sub": {
			"implem": [
				{ "instr_name": "sub", "datatypes": all_float, "template": tpl_implem_avx["arith_2args"] },
				{ "instr_name": "sub", "datatypes": [int64, int32], "template": tpl_implem_avx["arith_2args"], "if": "defined(__AVX2__)" },
				{ "instr_name": "subs", "datatypes": [int16, int8, uint16, uint8], "template": tpl_implem_avx["arith_2args"], "if": "defined(__AVX2__)" }], },
		"mul": {
			"implem": [
				{ "instr_name": "mul", "datatypes": all_float, "template": tpl_implem_avx["arith_2args"] },
				{ "instr_name": "mullo", "datatypes": [int32, int16], "template": tpl_implem_avx["arith_2args"], "if": "defined(__AVX2__)" }], },
		"div": {
			"implem" : [
				{ "instr_name": "div", "datatypes": all_float, "template": tpl_implem_avx["arith_2args"] }], },
		"min": {
			"implem": [
				{ "instr_name": "min", "datatypes": all_float, "template": tpl_implem_avx["arith_2args"] },
				{ "instr_name": "min", "datatypes": [int32, int16, int8, uint32, uint16, uint8], "template": tpl_implem_avx["arith_2args"], "if": "defined(__AVX2__)" }], },
		"max": {
			"implem": [
				{ "instr_name": "max", "datatypes": all_float, "template": tpl_implem_avx["arith_2args"] },
				{ "instr_name": "max", "datatypes": [int32, int16, int8, uint32, uint16, uint8], "template": tpl_implem_avx["arith_2args"], "if": "defined(__AVX2__)" }], },
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
				{ "instr_name": "andb", "datatypes": all_int_uint, "template": tpl_implem_avx["logi_2args_e"], "if": "!defined(__AVX2__)" },
				{ "instr_name": "and", "datatypes": all_int_uint, "template": tpl_implem_avx["logi_2args"], "if": "defined(__AVX2__)" }] },
		"andb_m": {
			"implem": [
				{ "instr_name": "andb", "datatypes": all_int_uint, "template": tpl_implem_avx["logi_m_2args_e"], "if": "!defined(__AVX2__)" },
				{ "instr_name": "and", "datatypes": all_datatypes, "template": tpl_implem_avx["logi_m_2args"], "if": "defined(__AVX2__)" }], },
		"andnb": {
			"implem" : [
				{ "instr_name": "andnot", "datatypes": all_float, "template": tpl_implem_avx["logi_2args"] },
				{ "instr_name": "andnb", "datatypes": all_int_uint, "template": tpl_implem_avx["logi_2args_e"], "if": "!defined(__AVX2__)" },
				{ "instr_name": "andnot", "datatypes": all_int_uint, "template": tpl_implem_avx["logi_2args"], "if": "defined(__AVX2__)" }], },
		"andnb_m": {
			"implem": [
				{ "instr_name": "andnb", "datatypes": all_int_uint, "template": tpl_implem_avx["logi_m_2args_e"], "if": "!defined(__AVX2__)" },
				{ "instr_name": "andnot", "datatypes": all_datatypes, "template": tpl_implem_avx["logi_m_2args"], "if": "defined(__AVX2__)" }], },
		"orb": {
			"implem": [
				{ "instr_name": "or", "datatypes": all_float, "template": tpl_implem_avx["logi_2args"] },
				{ "instr_name": "orb", "datatypes": all_int_uint, "template": tpl_implem_avx["logi_2args_e"], "if": "!defined(__AVX2__)" },
				{ "instr_name": "or", "datatypes": all_int_uint, "template": tpl_implem_avx["logi_2args"], "if": "defined(__AVX2__)" }], },
		"orb_m": {
			"implem": [
				{ "instr_name": "orb", "datatypes": all_int_uint, "template": tpl_implem_avx["logi_m_2args_e"], "if": "!defined(__AVX2__)" },
				{ "instr_name": "or", "datatypes": all_datatypes, "template": tpl_implem_avx["logi_m_2args"], "if": "defined(__AVX2__)" }], },
		"xorb": {
			"implem": [
				{ "instr_name": "xor", "datatypes": all_float, "template": tpl_implem_avx["logi_2args"] },
				{ "instr_name": "xorb", "datatypes": all_int_uint, "template": tpl_implem_avx["logi_2args_e"], "if": "!defined(__AVX2__)" },
				{ "instr_name": "xor", "datatypes": all_int_uint, "template": tpl_implem_avx["logi_2args"], "if": "defined(__AVX2__)" }], },
		"xorb_m": {
			"implem": [
				{ "instr_name": "xorb", "datatypes": all_int_uint, "template": tpl_implem_avx["logi_m_2args_e"], "if": "!defined(__AVX2__)" },
				{ "instr_name": "xor", "datatypes": all_datatypes, "template": tpl_implem_avx["logi_m_2args"], "if": "defined(__AVX2__)" }], },
		"lshiftr": {
			"implem": [
				{ "instr_name": "sllv", "datatypes": [int64, int32], "template": tpl_implem_avx["arith_2args"], "if": "defined(__AVX2__)" }], },
		"rshiftr": {
			"implem": [
				{ "instr_name": "srlv", "datatypes": [int64, int32], "template": tpl_implem_avx["arith_2args"], "if": "defined(__AVX2__)" }], },
		"lshift": {
			"implem": [
				{ "instr_name": "slli", "datatypes": [int64, int32, int16], "template": tpl_implem_avx["shift_2args"], "if": "defined(__AVX2__)" }], },
		"rshift": {
			"implem": [
				{ "instr_name": "srli", "datatypes": [int64, int32, int16], "template": tpl_implem_avx["shift_2args"], "if": "defined(__AVX2__)" }], },
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

				j2_template = Template(ff["template"]["code"], undefined=StrictUndefined)
				pre_rendering = j2_template.render(isa=isa, instr_name=ff["instr_name"], dt_par=isa["datatypes"][dt_par], dt_ret=isa["datatypes"][dt_ret])

				ph_ret = parse_placeholders(pre_rendering, isa, funcs, f, dt_par, dt_ret)

				cur_implem_status = { "if": "", "requirements": {} }
				if "if" in ff:
					cur_implem_status["if"] = ff["if"]
				cur_implem_status["requirements"] = ph_ret["requirements"]

				if "implem_status" not in funcs[f]:
				 	funcs[f]["implem_status"] = {}
				if dt_key not in funcs[f]["implem_status"]:
				 	funcs[f]["implem_status"][dt_key] = []
				funcs[f]["implem_status"][dt_key].append(cur_implem_status)

				post_rendering = ph_ret["converted_ir"]

				ifd = build_ifdef(funcs, f, dt_key, len(funcs[f]["implem_status"][dt_key])-1)
				if ifd:
					print("#if " + ifd, file=file)

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
				if ifd:
					print("#endif", file=file)

def gen_emulated_functions(isa, file, funcs):
	print("Generation of the emulated implementations...")

	funcs_emu = {
		"blend": [
			{ "datatypes": [int64, int32, uint64, uint32], "template":
"""	%r<c:float|b:tp>% r0f = %cast<tp,c:float|b:tp>%(r0);
	%r<c:float|b:tp>% r1f = %cast<tp,c:float|b:tp>%(r1);
	%m<c:float|b:tp>% m0f = %cast_m<tp,c:float|b:tp>%(m0);
	%r<c:float|b:tp>% resf = %blend<c:float|b:tp>%(r0f, r1f, m0f);
	return %cast<c:float|b:tp,tp>%(resf); """
			},
			{ "datatypes": all_datatypes, "template":
"""	%r<c:int|b:tp>% rmi = %cast<tp,c:int|b:tp>%(%toreg<tp>%(m0));
	%r<c:int|b:tp>% r0i = %cast<tp,c:int|b:tp>%(r0);
	%r<c:int|b:tp>% r1i = %cast<tp,c:int|b:tp>%(r1);
	%r<c:int|b:tp>% r_0i = %andb<c:int|b:tp>%(rmi, r0i);
	%r<c:int|b:tp>% r_1i = %andnb<c:int|b:tp>%(rmi, r1i);
	%r<c:int|b:tp>% resi = %xorb<c:int|b:tp>%(r_0i, r_1i);
	%r<tr>% res = %cast<c:int|b:tr,tr>%(resi);
	return res;"""
			}, ],
		"sat": [
			{ "datatypes": all_datatypes, "template":
"""	%r<tp>% rmin = %set1<tp>%(v0);
	%r<tp>% rmax = %set1<tp>%(v1);
	%r<tp>% res = %max<tp>%(%min<tp>%(r0, rmax), rmin);
	return res;"""
			}, ],
		"fmadd": [
			{ "datatypes": all_float, "template":
"""	%r<tp>% rmul = %mul<tp>%(r0, r1);
	%r<tp>% res = %add<tp>%(rmul, r2);
	return res;"""
			}, ],
		"fmsub": [
			{ "datatypes": all_float, "template":
"""	%r<tp>% rmul = %mul<tp>%(r0, r1);
	%r<tp>% res = %sub<tp>%(rmul, r3);
	return res;"""
			}, ],
		"fnmadd": [
			{ "datatypes": all_float, "template":
"""	%r<tp>% rmul = %mul<tp>%(r0, r1);
	%r<tp>% res = %sub<tp>%(r3, rmul);
	return res;"""
			}, ],
		"fnmsub": [
			{ "datatypes": all_float, "template":
"""	%r<tp>% rmul = %mul<tp>%(r0, r1);
	%r<tp>% rmulz = %sub<tp>%(%set0<tp>%(), rmul);
	%r<tp>% res = %sub<tp>%(rmulz, r3);
	return res;"""
			}, ],
	}

	for f in funcs_emu:
		if f in funcs:
			for tpl in funcs_emu[f]:
				for dt_par in tpl["datatypes"]:
					if dt_par in funcs[f]["datatypes"]:
						dt_ret = dt_par
						dt_key = dt_par + "," + dt_ret
						if is_missing_func(funcs, f, dt_key):
							try:
								ph_ret = parse_placeholders(tpl["template"], isa, funcs, f, dt_par, dt_ret)
							except Exception as err:
								print(" -> '" + f + "<" + dt_key + ">' has been skipped (reason: \"{0}\").".format(err))
								continue

							post_rendering = ph_ret["converted_ir"]

							ifd = ""
							if "implem_status" in funcs[f] and dt_key in funcs[f]["implem_status"]:
								is_first = True
								i = 0
								for implem in funcs[f]["implem_status"][dt_key]:
									ifd_sub = build_ifdef(funcs, f, dt_key, i)
									if ifd_sub:
										if not is_first:
											ifd = ifd + " && "
										ifd = ifd + "!( "
										ifd = ifd + ifd_sub
										ifd = ifd + " )"
										is_first = False
									i = i +1

							if "implem_status" not in funcs[f]:
								funcs[f]["implem_status"] = {}
							if dt_key not in funcs[f]["implem_status"]:
								funcs[f]["implem_status"][dt_key] = []
							funcs[f]["implem_status"][dt_key].append({ "if": "", "requirements": ph_ret["requirements"] })

							ifd_cur = build_ifdef(funcs, f, dt_key, len(funcs[f]["implem_status"][dt_key])-1)
							if ifd and ifd_cur:
								ifd = ifd + " && ( " + ifd_cur + " )"
							elif ifd_cur:
								ifd = ifd_cur
							if ifd:
								print("#if " + ifd, file=file)

							funcs[f]["implem_status"][dt_key][len(funcs[f]["implem_status"][dt_key])-1]["if"] = ifd

							func_name = build_func_name_short(isa, dt_par, f)
							print(build_proto(funcs[f]["proto"], dt_par, dt_ret, isa, func_name) + " {", file=file)
							print(post_rendering, file=file)
							print("}", file=file);

							if ifd:
								print("#endif", file=file)

							print(" -> '" + f + "<" + dt_key + ">' has been implemented.")
					else:
						print("Panic: unsupported type for '" + f + "<" + dt_par + "," + dt_par + ">' function.")
		else:
			print("Panic: '" + f + "' function does not exist.")
			exit(-1)

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

			if is_missing_func(funcs, f, dt_key):
				ifd = ""
				if "implem_status" in funcs[f] and dt_key in funcs[f]["implem_status"]:
					is_first = True
					i = 0
					for implem in funcs[f]["implem_status"][dt_key]:
						ifd_sub = build_ifdef(funcs, f, dt_key, i)
						if ifd_sub:
							if not is_first:
								ifd = ifd + " && "
							ifd = ifd + "!( "
							ifd = ifd + ifd_sub
							ifd = ifd + " )"
							is_first = False
						i = i +1
				if ifd:
					print("#if " + ifd, file=file)

				if len(dt.split(',')) <= 1:
					func_name = build_func_name_short(isa, dt_par, f)
				else:
					func_name = build_func_name(isa, dt_par, dt_ret, f)
				print(build_proto(funcs[f]["proto"], dt_par, dt_ret, isa, func_name) + " {", file=file)
				print("\tprintf(\"MIPP panic: '%s' is unimplemented.\\n\", \""+func_name+"\");", file=file);
				print("\texit(-1);", file=file);
				print("}", file=file);

				if ifd:
					print("#endif", file=file)

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
			{"type": "val", "charac": "RO", "fixeddatatype": int32},
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
	"ret_reg_3args_1reg_2val": {
		"ret" :
			{"type": "reg", "charac": "WO", "fixeddatatype": False},
		"args" : [
			{"type": "reg", "charac": "RO", "fixeddatatype": False},
			{"type": "val", "charac": "RO", "fixeddatatype": False},
			{"type": "val", "charac": "RO", "fixeddatatype": False},
		]
	},
}

mipp_funcs = {
	"cast":    { "name": "cast",    "proto": protos["ret_reg_1arg_reg"       ], "datatypes": all_datatypes_cart_prod },
	"cast_m":  { "name": "cast_m",  "proto": protos["ret_msk_1arg_msk"       ], "datatypes": all_datatypes_cart_prod },
	"toreg":   { "name": "toreg",   "proto": protos["ret_reg_1arg_msk"       ], "datatypes": all_datatypes           },
	"tomsk":   { "name": "tomsk",   "proto": protos["ret_msk_1arg_reg"       ], "datatypes": all_datatypes           },
	"load":    { "name": "load",    "proto": protos["ret_reg_1arg_ptr"       ], "datatypes": all_datatypes           },
	"loadu":   { "name": "loadu",   "proto": protos["ret_reg_1arg_ptr"       ], "datatypes": all_datatypes           },
	"store":   { "name": "store",   "proto": protos["ret_void_2args_ptr_reg" ], "datatypes": all_datatypes           },
	"storeu":  { "name": "storeu",  "proto": protos["ret_void_2args_ptr_reg" ], "datatypes": all_datatypes           },
	"set1":    { "name": "set1",    "proto": protos["ret_reg_1arg_val"       ], "datatypes": all_datatypes           },
	"set0":    { "name": "set0",    "proto": protos["ret_reg_0arg"           ], "datatypes": all_datatypes           },
	"set0_m":  { "name": "set0_m",  "proto": protos["ret_msk_0arg"           ], "datatypes": all_datatypes           },
	"sqrt":    { "name": "sqrt",    "proto": protos["ret_reg_1arg_reg"       ], "datatypes": all_float               },
	"rsqrt":   { "name": "rsqrt",   "proto": protos["ret_reg_1arg_reg"       ], "datatypes": all_float               },
	"add":     { "name": "add",     "proto": protos["ret_reg_2args_reg"      ], "datatypes": all_datatypes           },
	"sub":     { "name": "sub",     "proto": protos["ret_reg_2args_reg"      ], "datatypes": all_datatypes           },
	"mul":     { "name": "mul",     "proto": protos["ret_reg_2args_reg"      ], "datatypes": all_datatypes           },
	"div":     { "name": "div",     "proto": protos["ret_reg_2args_reg"      ], "datatypes": all_float               },
	"min":     { "name": "min",     "proto": protos["ret_reg_2args_reg"      ], "datatypes": all_datatypes           },
	"max":     { "name": "max",     "proto": protos["ret_reg_2args_reg"      ], "datatypes": all_datatypes           },
	"fmadd":   { "name": "fmadd",   "proto": protos["ret_reg_3args_reg"      ], "datatypes": all_float               },
	"fnmadd":  { "name": "fnmadd",  "proto": protos["ret_reg_3args_reg"      ], "datatypes": all_float               },
	"fmsub":   { "name": "fmsub",   "proto": protos["ret_reg_3args_reg"      ], "datatypes": all_float               },
	"fnmsub":  { "name": "fnmsub",  "proto": protos["ret_reg_3args_reg"      ], "datatypes": all_float               },
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
	"sat":     { "name": "sat",     "proto": protos["ret_reg_3args_1reg_2val"], "datatypes": all_datatypes           },
}

isa_avx = {
	"name": "avx",
	"prefix": "_mm256",
	"size": 256,
	"datatypes": {
		float64 : { "name" : float64, "category": cfloat, "n_bits" : 64, "data_ext" :    "pd", "data_ext_logi":    "pd", "data_ext_msk": "si256", "reg" : "__m256d", "msk" : "__m256i", "to_ptr": "float64_t", },
		float32 : { "name" : float32, "category": cfloat, "n_bits" : 32, "data_ext" :    "ps", "data_ext_logi":    "ps", "data_ext_msk": "si256", "reg" : " __m256", "msk" : "__m256i", "to_ptr": "float32_t", },
		  int64 : { "name" :   int64, "category":   cint, "n_bits" : 64, "data_ext" : "epi64", "data_ext_logi": "si256", "data_ext_msk": "si256", "reg" : "__m256i", "msk" : "__m256i", "to_ptr":   "__m256i", },
		  int32 : { "name" :   int32, "category":   cint, "n_bits" : 32, "data_ext" : "epi32", "data_ext_logi": "si256", "data_ext_msk": "si256", "reg" : "__m256i", "msk" : "__m256i", "to_ptr":   "__m256i", },
		  int16 : { "name" :   int16, "category":   cint, "n_bits" : 16, "data_ext" : "epi16", "data_ext_logi": "si256", "data_ext_msk": "si256", "reg" : "__m256i", "msk" : "__m256i", "to_ptr":   "__m256i", },
		   int8 : { "name" :    int8, "category":   cint, "n_bits" :  8, "data_ext" :  "epi8", "data_ext_logi": "si256", "data_ext_msk": "si256", "reg" : "__m256i", "msk" : "__m256i", "to_ptr":   "__m256i", },
		 uint64 : { "name" :  uint64, "category":  cuint, "n_bits" : 64, "data_ext" : "epu64", "data_ext_logi": "si256", "data_ext_msk": "si256", "reg" : "__m256i", "msk" : "__m256i", "to_ptr":   "__m256i", },
		 uint32 : { "name" :  uint32, "category":  cuint, "n_bits" : 32, "data_ext" : "epu32", "data_ext_logi": "si256", "data_ext_msk": "si256", "reg" : "__m256i", "msk" : "__m256i", "to_ptr":   "__m256i", },
		 uint16 : { "name" :  uint16, "category":  cuint, "n_bits" : 16, "data_ext" : "epu16", "data_ext_logi": "si256", "data_ext_msk": "si256", "reg" : "__m256i", "msk" : "__m256i", "to_ptr":   "__m256i", },
		  uint8 : { "name" :   uint8, "category":  cuint, "n_bits" :  8, "data_ext" :  "epu8", "data_ext_logi": "si256", "data_ext_msk": "si256", "reg" : "__m256i", "msk" : "__m256i", "to_ptr":   "__m256i", },
	},
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

gen_native_functions(isa_avx, file, mipp_funcs)
gen_emulated_functions(isa_avx, file, mipp_funcs)
gen_missing_functions(isa_avx, file, mipp_funcs)

dump_dict_json(mipp_funcs, "test.json")

tpl_footer_avx = """#endif /* MY_INTRINSICS_PLUS_PLUS_IMPL_GEN_AVX_H_ */"""
j2_template = Template(tpl_footer_avx, undefined=StrictUndefined)
print(j2_template.render(), file=file)

file.close()