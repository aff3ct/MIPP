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
	if len(dt_info_carac) == 1 and dt_info_carac[0] == "tp":
		dt = dt_par
	elif len(dt_info_carac) == 1 and dt_info_carac[0] == "tr":
		dt = dt_ret
	elif len(dt_info_carac) >= 1:
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

def gen_functions(isa, file, funcs, implems):
	for f in implems:
		if f in funcs:
			for ff in implems[f]:
				for dt in ff["datatypes"]:
					if len(dt.split(',')) <= 1:
						dt_par = dt.split(',')[0]
						dt_ret = dt.split(',')[0]
						if dt_par not in funcs[f]["datatypes"]:
							print("Panic: unsupported type for '" + f + "<" + dt_par + "," + dt_par + ">' function.")
							exit(-1)
					else:
						dt_par = dt.split(',')[0]
						dt_ret = dt.split(',')[1]

						dtk = dt_par + "," + dt_ret
						if dtk not in funcs[f]["datatypes"]:
							print("Panic: unsupported type for '" + f + "<" + dt_par + "," + dt_ret + ">' function.")
							exit(-1)
					dt_key = dt_par + "," + dt_ret

					if is_missing_func(funcs, f, dt_key):
						j2_template = Template(ff["template"]["code"], undefined=StrictUndefined)
						instr_name = ""
						if "instr_name" in ff:
							instr_name = ff["instr_name"]
						pre_rendering = j2_template.render(isa=isa, instr_name=instr_name, dt_par=isa["datatypes"][dt_par], dt_ret=isa["datatypes"][dt_ret])

						try:
							ph_ret = parse_placeholders(pre_rendering, isa, funcs, f, dt_par, dt_ret)
						except Exception as err:
							print(" -> '" + f + "<" + dt_key + ">' has been skipped (reason: \"{0}\").".format(err))
							continue

						ifd = ""
						if "type" in ff and ff["type"] == "emulated":
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

						ifd_cur = build_ifdef(funcs, f, dt_key, len(funcs[f]["implem_status"][dt_key])-1)
						if ifd and ifd_cur:
							ifd = ifd + " && ( " + ifd_cur + " )"
						elif ifd_cur:
							ifd = ifd_cur
						if ifd:
							print("#if " + ifd, file=file)
							if "type" in ff and ff["type"] == "emulated":
								funcs[f]["implem_status"][dt_key][len(funcs[f]["implem_status"][dt_key])-1]["if"] = ifd

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

						if "type" in ff and ff["type"] == "emulated":
							print(" -> '" + f + "<" + dt_key + ">' has been implemented.")
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
	"ret_reg_3args_2reg_1msk": {
		"ret" :
			{"type": "reg", "charac": "WO", "fixeddatatype": False},
		"args" : [
			{"type": "reg", "charac": "RO", "fixeddatatype": False},
			{"type": "reg", "charac": "RO", "fixeddatatype": False},
			{"type": "msk", "charac": "RO", "fixeddatatype": False},
		]
	},
	"ret_reg_3args_2reg_1msk_1reg": {
		"ret" :
			{"type": "reg", "charac": "WO", "fixeddatatype": False},
		"args" : [
			{"type": "reg", "charac": "RO", "fixeddatatype": False},
			{"type": "reg", "charac": "RO", "fixeddatatype": False},
			{"type": "msk", "charac": "RO", "fixeddatatype": False},
			{"type": "reg", "charac": "RO", "fixeddatatype": False},
		]
	},
}

mipp_funcs = {
	"cast":    { "proto": protos["ret_reg_1arg_reg"            ], "datatypes": all_datatypes_cart_prod },
	"cast_m":  { "proto": protos["ret_msk_1arg_msk"            ], "datatypes": all_datatypes_cart_prod },
	"toreg":   { "proto": protos["ret_reg_1arg_msk"            ], "datatypes": all_datatypes           },
	"tomsk":   { "proto": protos["ret_msk_1arg_reg"            ], "datatypes": all_datatypes           },
	"load":    { "proto": protos["ret_reg_1arg_ptr"            ], "datatypes": all_datatypes           },
	"loadu":   { "proto": protos["ret_reg_1arg_ptr"            ], "datatypes": all_datatypes           },
	"store":   { "proto": protos["ret_void_2args_ptr_reg"      ], "datatypes": all_datatypes           },
	"storeu":  { "proto": protos["ret_void_2args_ptr_reg"      ], "datatypes": all_datatypes           },
	"set1":    { "proto": protos["ret_reg_1arg_val"            ], "datatypes": all_datatypes           },
	"set0":    { "proto": protos["ret_reg_0arg"                ], "datatypes": all_datatypes           },
	"set0_m":  { "proto": protos["ret_msk_0arg"                ], "datatypes": all_datatypes           },
	"sqrt":    { "proto": protos["ret_reg_1arg_reg"            ], "datatypes": all_float               },
	"rsqrt":   { "proto": protos["ret_reg_1arg_reg"            ], "datatypes": all_float               },
	"add":     { "proto": protos["ret_reg_2args_reg"           ], "datatypes": all_datatypes           },
	"add_m":   { "proto": protos["ret_reg_3args_2reg_1msk_1reg"], "datatypes": all_datatypes           },
	"add_mz":  { "proto": protos["ret_reg_3args_2reg_1msk"     ], "datatypes": all_datatypes           },
	"sub":     { "proto": protos["ret_reg_2args_reg"           ], "datatypes": all_datatypes           },
	"sub_m":   { "proto": protos["ret_reg_3args_2reg_1msk_1reg"], "datatypes": all_datatypes           },
	"sub_mz":  { "proto": protos["ret_reg_3args_2reg_1msk"     ], "datatypes": all_datatypes           },
	"mul":     { "proto": protos["ret_reg_2args_reg"           ], "datatypes": all_datatypes           },
	"mul_m":   { "proto": protos["ret_reg_3args_2reg_1msk_1reg"], "datatypes": all_datatypes           },
	"mul_mz":  { "proto": protos["ret_reg_3args_2reg_1msk"     ], "datatypes": all_datatypes           },
	"div":     { "proto": protos["ret_reg_2args_reg"           ], "datatypes": all_float               },
	"div_m":   { "proto": protos["ret_reg_3args_2reg_1msk_1reg"], "datatypes": all_float               },
	"div_mz":  { "proto": protos["ret_reg_3args_2reg_1msk"     ], "datatypes": all_float               },
	"min":     { "proto": protos["ret_reg_2args_reg"           ], "datatypes": all_datatypes           },
	"min_m":   { "proto": protos["ret_reg_3args_2reg_1msk_1reg"], "datatypes": all_datatypes           },
	"min_mz":  { "proto": protos["ret_reg_3args_2reg_1msk"     ], "datatypes": all_datatypes           },
	"max":     { "proto": protos["ret_reg_2args_reg"           ], "datatypes": all_datatypes           },
	"max_m":   { "proto": protos["ret_reg_3args_2reg_1msk_1reg"], "datatypes": all_datatypes           },
	"max_mz":  { "proto": protos["ret_reg_3args_2reg_1msk"     ], "datatypes": all_datatypes           },
	"fmadd":   { "proto": protos["ret_reg_3args_reg"           ], "datatypes": all_float               },
	"fnmadd":  { "proto": protos["ret_reg_3args_reg"           ], "datatypes": all_float               },
	"fmsub":   { "proto": protos["ret_reg_3args_reg"           ], "datatypes": all_float               },
	"fnmsub":  { "proto": protos["ret_reg_3args_reg"           ], "datatypes": all_float               },
	"andb":    { "proto": protos["ret_reg_2args_reg"           ], "datatypes": all_datatypes           },
	"andb_m":  { "proto": protos["ret_msk_2args_msk"           ], "datatypes": all_datatypes           },
	"andnb":   { "proto": protos["ret_reg_2args_reg"           ], "datatypes": all_datatypes           },
	"andnb_m": { "proto": protos["ret_msk_2args_msk"           ], "datatypes": all_datatypes           },
	"orb":     { "proto": protos["ret_reg_2args_reg"           ], "datatypes": all_datatypes           },
	"orb_m":   { "proto": protos["ret_msk_2args_msk"           ], "datatypes": all_datatypes           },
	"xorb":    { "proto": protos["ret_reg_2args_reg"           ], "datatypes": all_datatypes           },
	"xorb_m":  { "proto": protos["ret_msk_2args_msk"           ], "datatypes": all_datatypes           },
	"msb":     { "proto": protos["ret_reg_1arg_reg"            ], "datatypes": all_datatypes           },
	"notb":    { "proto": protos["ret_reg_1arg_reg"            ], "datatypes": all_datatypes           },
	"notb_m":  { "proto": protos["ret_msk_1arg_msk"            ], "datatypes": all_datatypes           },
	"lshiftr": { "proto": protos["ret_reg_2args_reg"           ], "datatypes": all_datatypes           },
	"rshiftr": { "proto": protos["ret_reg_2args_reg"           ], "datatypes": all_datatypes           },
	"lshift":  { "proto": protos["ret_reg_2args_reg_val"       ], "datatypes": all_datatypes           },
	"rshift":  { "proto": protos["ret_reg_2args_reg_val"       ], "datatypes": all_datatypes           },
	"cmpeq":   { "proto": protos["ret_msk_2args_reg"           ], "datatypes": all_datatypes           },
	"cmpneq":  { "proto": protos["ret_msk_2args_reg"           ], "datatypes": all_datatypes           },
	"cmplt":   { "proto": protos["ret_msk_2args_reg"           ], "datatypes": all_datatypes           },
	"cmple":   { "proto": protos["ret_msk_2args_reg"           ], "datatypes": all_datatypes           },
	"cmpge":   { "proto": protos["ret_msk_2args_reg"           ], "datatypes": all_datatypes           },
	"cmpgt":   { "proto": protos["ret_msk_2args_reg"           ], "datatypes": all_datatypes           },
	"blend":   { "proto": protos["ret_reg_3args_2reg_1msk"     ], "datatypes": all_datatypes           },
	"sat":     { "proto": protos["ret_reg_3args_1reg_2val"     ], "datatypes": all_datatypes           },
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

implems_avx = {
	"cast": [
		{ "instr_name": "cast", "datatypes": all_datatypes_cart_prod, "template": tpl_implem_avx["cast"], } ],
	"cast_m": [
		{ "instr_name": "cast", "datatypes": all_datatypes_cart_prod, "template": tpl_implem_avx["cast_m"], } ],
	"toreg": [
		{ "instr_name": "cast", "datatypes": all_datatypes, "template": tpl_implem_avx["toreg"], } ],
	"tomsk": [
		{ "instr_name": "cast", "datatypes": all_datatypes, "template": tpl_implem_avx["tomsk"], } ],
	"load": [
		{ "instr_name": "load", "datatypes": all_datatypes, "template": tpl_implem_avx["load"], "if": "defined(MIPP_ALIGNED_LOADS)" },
		{ "instr_name": "loadu", "datatypes": all_datatypes, "template": tpl_implem_avx["load"], "if": "!defined(MIPP_ALIGNED_LOADS)" } ],
	"loadu": [
		{ "instr_name": "loadu", "datatypes": all_datatypes, "template": tpl_implem_avx["load"] } ],
	"store": [
		{ "instr_name": "store", "datatypes": all_datatypes, "template": tpl_implem_avx["store"], "if": "defined(MIPP_ALIGNED_LOADS)" },
		{ "instr_name": "storeu", "datatypes": all_datatypes, "template": tpl_implem_avx["store"], "if": "!defined(MIPP_ALIGNED_LOADS)" } ],
	"storeu": [
		{ "instr_name": "storeu", "datatypes": all_datatypes, "template": tpl_implem_avx["store"] } ],
	"set1": [
		{ "instr_name": "set1", "datatypes": all_float, "template": tpl_implem_avx["set1"] },
		{ "instr_name": "set1", "datatypes": [int64], "template": tpl_implem_avx["set1x"] },
		{ "instr_name": "set1", "datatypes": [int32, int16, int8], "template": tpl_implem_avx["set1"] } ],
	"set0": [
			{ "instr_name": "setzero", "datatypes": all_datatypes, "template": tpl_implem_avx["set0"] } ],
	"set0_m": [
		{ "instr_name": "setzero", "datatypes": all_datatypes, "template": tpl_implem_avx["set0_m"] } ],
	"sqrt": [
		{ "instr_name": "sqrt", "datatypes": all_float, "template": tpl_implem_avx["arith_1arg"] } ],
	"rsqrt": [
		{ "instr_name": "rsqrt", "datatypes": [float32], "template": tpl_implem_avx["arith_1arg"] } ],
	"add": [
		{ "instr_name": "add", "datatypes": all_float, "template": tpl_implem_avx["arith_2args"] },
		{ "instr_name": "add", "datatypes": [int64, int32], "template": tpl_implem_avx["arith_2args"], "if": "defined(__AVX2__)" },
		{ "instr_name": "adds", "datatypes": [int16, int8, uint16, uint8], "template": tpl_implem_avx["arith_2args"], "if": "defined(__AVX2__)" } ],
	"sub": [
		{ "instr_name": "sub", "datatypes": all_float, "template": tpl_implem_avx["arith_2args"] },
		{ "instr_name": "sub", "datatypes": [int64, int32], "template": tpl_implem_avx["arith_2args"], "if": "defined(__AVX2__)" },
		{ "instr_name": "subs", "datatypes": [int16, int8, uint16, uint8], "template": tpl_implem_avx["arith_2args"], "if": "defined(__AVX2__)" } ],
	"mul": [
		{ "instr_name": "mul", "datatypes": all_float, "template": tpl_implem_avx["arith_2args"] },
		{ "instr_name": "mullo", "datatypes": [int32, int16], "template": tpl_implem_avx["arith_2args"], "if": "defined(__AVX2__)" }],
	"div": [
		{ "instr_name": "div", "datatypes": all_float, "template": tpl_implem_avx["arith_2args"] } ],
	"min": [
		{ "instr_name": "min", "datatypes": all_float, "template": tpl_implem_avx["arith_2args"] },
		{ "instr_name": "min", "datatypes": [int32, int16, int8, uint32, uint16, uint8], "template": tpl_implem_avx["arith_2args"], "if": "defined(__AVX2__)" } ],
	"max": [
		{ "instr_name": "max", "datatypes": all_float, "template": tpl_implem_avx["arith_2args"] },
		{ "instr_name": "max", "datatypes": [int32, int16, int8, uint32, uint16, uint8], "template": tpl_implem_avx["arith_2args"], "if": "defined(__AVX2__)" } ],
	"fmadd": [
		{ "instr_name": "fmadd", "datatypes": all_float, "template": tpl_implem_avx["arith_3args"], "if": "defined(__FMA__)" } ],
	"fnmadd": [
		{ "instr_name": "fnmadd", "datatypes": all_float, "template": tpl_implem_avx["arith_3args"], "if": "defined(__FMA__)" } ],
	"fmsub": [
		{ "instr_name": "fmsub", "datatypes": all_float, "template": tpl_implem_avx["arith_3args"], "if": "defined(__FMA__)" } ],
	"fnmsub": [
		{ "instr_name": "fnmsub", "datatypes": all_float, "template": tpl_implem_avx["arith_3args"], "if": "defined(__FMA__)" } ],
	"andb": [
		{ "instr_name": "and", "datatypes": all_float, "template": tpl_implem_avx["logi_2args"] },
		{ "instr_name": "andb", "datatypes": all_int_uint, "template": tpl_implem_avx["logi_2args_e"], "if": "!defined(__AVX2__)" },
		{ "instr_name": "and", "datatypes": all_int_uint, "template": tpl_implem_avx["logi_2args"], "if": "defined(__AVX2__)" } ],
	"andb_m": [
		{ "instr_name": "andb", "datatypes": all_int_uint, "template": tpl_implem_avx["logi_m_2args_e"], "if": "!defined(__AVX2__)" },
		{ "instr_name": "and", "datatypes": all_datatypes, "template": tpl_implem_avx["logi_m_2args"], "if": "defined(__AVX2__)" } ],
	"andnb": [
		{ "instr_name": "andnot", "datatypes": all_float, "template": tpl_implem_avx["logi_2args"] },
		{ "instr_name": "andnb", "datatypes": all_int_uint, "template": tpl_implem_avx["logi_2args_e"], "if": "!defined(__AVX2__)" },
		{ "instr_name": "andnot", "datatypes": all_int_uint, "template": tpl_implem_avx["logi_2args"], "if": "defined(__AVX2__)" } ],
	"andnb_m": [
		{ "instr_name": "andnb", "datatypes": all_int_uint, "template": tpl_implem_avx["logi_m_2args_e"], "if": "!defined(__AVX2__)" },
		{ "instr_name": "andnot", "datatypes": all_datatypes, "template": tpl_implem_avx["logi_m_2args"], "if": "defined(__AVX2__)" } ],
	"orb": [
		{ "instr_name": "or", "datatypes": all_float, "template": tpl_implem_avx["logi_2args"] },
		{ "instr_name": "orb", "datatypes": all_int_uint, "template": tpl_implem_avx["logi_2args_e"], "if": "!defined(__AVX2__)" },
		{ "instr_name": "or", "datatypes": all_int_uint, "template": tpl_implem_avx["logi_2args"], "if": "defined(__AVX2__)" } ],
	"orb_m": [
		{ "instr_name": "orb", "datatypes": all_int_uint, "template": tpl_implem_avx["logi_m_2args_e"], "if": "!defined(__AVX2__)" },
		{ "instr_name": "or", "datatypes": all_datatypes, "template": tpl_implem_avx["logi_m_2args"], "if": "defined(__AVX2__)" } ],
	"xorb": [
		{ "instr_name": "xor", "datatypes": all_float, "template": tpl_implem_avx["logi_2args"] },
		{ "instr_name": "xorb", "datatypes": all_int_uint, "template": tpl_implem_avx["logi_2args_e"], "if": "!defined(__AVX2__)" },
		{ "instr_name": "xor", "datatypes": all_int_uint, "template": tpl_implem_avx["logi_2args"], "if": "defined(__AVX2__)" } ],
	"xorb_m": [
		{ "instr_name": "xorb", "datatypes": all_int_uint, "template": tpl_implem_avx["logi_m_2args_e"], "if": "!defined(__AVX2__)" },
		{ "instr_name": "xor", "datatypes": all_datatypes, "template": tpl_implem_avx["logi_m_2args"], "if": "defined(__AVX2__)" } ],
	"lshiftr": [
		{ "instr_name": "sllv", "datatypes": [int64, int32], "template": tpl_implem_avx["arith_2args"], "if": "defined(__AVX2__)" } ],
	"rshiftr": [
		{ "instr_name": "srlv", "datatypes": [int64, int32], "template": tpl_implem_avx["arith_2args"], "if": "defined(__AVX2__)" } ],
	"lshift": [
		{ "instr_name": "slli", "datatypes": [int64, int32, int16], "template": tpl_implem_avx["shift_2args"], "if": "defined(__AVX2__)" } ],
	"rshift": [
		{ "instr_name": "srli", "datatypes": [int64, int32, int16], "template": tpl_implem_avx["shift_2args"], "if": "defined(__AVX2__)" } ],
	"cmpeq": [
		{ "instr_name": "cmp", "datatypes": all_float, "template": tpl_implem_avx["cmpeq_float"], },
		{ "instr_name": "cmpeq", "datatypes": all_int, "template": tpl_implem_avx["cmp_int"], "if": "defined(__AVX2__)" } ],
	"cmpneq": [
		{ "instr_name": "cmp", "datatypes": all_float, "template": tpl_implem_avx["cmpneq_float"], } ],
	"cmplt": [
		{ "instr_name": "cmp", "datatypes": all_float, "template": tpl_implem_avx["cmplt_float"], } ],
	"cmple": [
		{ "instr_name": "cmp", "datatypes": all_float, "template": tpl_implem_avx["cmple_float"], } ],
	"cmpge": [
		{ "instr_name": "cmp", "datatypes": all_float, "template": tpl_implem_avx["cmpge_float"], } ],
	"cmpgt": [
		{ "instr_name": "cmp", "datatypes": all_float, "template": tpl_implem_avx["cmpgt_float"], },
		{ "instr_name": "cmpgt", "datatypes": all_int, "template": tpl_implem_avx["cmp_int"], "if": "defined(__AVX2__)" } ],
	"blend": [
		{ "instr_name": "blendv", "datatypes": all_float, "template": tpl_implem_avx["blend_float"], },
		{ "instr_name": "blendv", "datatypes": all_int_uint, "template": tpl_implem_avx["blend_int"], "if": "defined(__AVX2__)", } ],
}

tpl_implem_emu = {
	"blend-1": { "format": "long", "code":
"""	%r<c:float|b:tp>% r0f = %cast<tp,c:float|b:tp>%(r0);
	%r<c:float|b:tp>% r1f = %cast<tp,c:float|b:tp>%(r1);
	%m<c:float|b:tp>% m0f = %cast_m<tp,c:float|b:tp>%(m0);
	%r<c:float|b:tp>% resf = %blend<c:float|b:tp>%(r0f, r1f, m0f);
	return %cast<c:float|b:tp,tp>%(resf); """
	},
	"blend-2": { "format": "long", "code":
"""	%r<c:int|b:tp>% rmi = %cast<tp,c:int|b:tp>%(%toreg<tp>%(m0));
	%r<c:int|b:tp>% r0i = %cast<tp,c:int|b:tp>%(r0);
	%r<c:int|b:tp>% r1i = %cast<tp,c:int|b:tp>%(r1);
	%r<c:int|b:tp>% r_0i = %andb<c:int|b:tp>%(rmi, r0i);
	%r<c:int|b:tp>% r_1i = %andnb<c:int|b:tp>%(rmi, r1i);
	%r<c:int|b:tp>% resi = %xorb<c:int|b:tp>%(r_0i, r_1i);
	%r<tr>% res = %cast<c:int|b:tr,tr>%(resi);
	return res;"""
	},
	"sat": { "format": "long", "code":
"""	%r<tp>% rmin = %set1<tp>%(v0);
	%r<tp>% rmax = %set1<tp>%(v1);
	%r<tp>% res = %max<tp>%(%min<tp>%(r0, rmax), rmin);
	return res;"""
	},
	"fmadd": { "format": "long", "code":
"""	%r<tp>% rmul = %mul<tp>%(r0, r1);
	%r<tp>% res = %add<tp>%(rmul, r2);
	return res;"""
	},
	"fmsub": { "format": "long", "code":
"""	%r<tp>% rmul = %mul<tp>%(r0, r1);
	%r<tp>% res = %sub<tp>%(rmul, r2);
	return res;"""
	},
	"fnmadd": { "format": "long", "code":
"""	%r<tp>% rmul = %mul<tp>%(r0, r1);
	%r<tp>% res = %sub<tp>%(r2, rmul);
	return res;"""
	},
	"fnmsub": { "format": "long", "code":
"""	%r<tp>% rmul = %mul<tp>%(r0, r1);
	%r<tp>% rmulz = %sub<tp>%(%set0<tp>%(), rmul);
	%r<tp>% res = %sub<tp>%(rmulz, r2);
	return res;"""
	},
	"arith_2args_1msk": { "format": "long", "code":
"""	%r<tp>% res = %{{ instr_name }}<tp>%(r0, r1);
	return %blend<tp>%(res, r2, m0);"""
	},
	"arith_2args_1msk_1reg": { "format": "long", "code":
"""	%r<tp>% rz = %set0<tp>%();
	return %{{ instr_name }}<tp>%(r0, r1, m0, rz);"""
	},
	"msb-64": { "format": "long", "code":
"""	%r<tp>% rm = %cast<c:int|b:tp,tp>%(%set1<c:int|b:tp>%(0x8000000000000000));
	return %andb<tp>%(r0, rm);"""
	},
	"msb-32": { "format": "long", "code":
"""	%r<tp>% rm = %cast<c:int|b:tp,tp>%(%set1<c:int|b:tp>%(0x80000000));
	return %andb<tp>%(r0, rm);"""
	},
	"msb-16": { "format": "long", "code":
"""	%r<tp>% rm = %cast<c:int|b:tp,tp>%(%set1<c:int|b:tp>%(0x8000));
	return %andb<tp>%(r0, rm);"""
	},
	"msb-8": { "format": "long", "code":
"""	%r<tp>% rm = %cast<c:int|b:tp,tp>%(%set1<c:int|b:tp>%(0x80));
	return %andb<tp>%(r0, rm);"""
	},
	"notb-64": { "format": "long", "code":
"""	%r<tp>% rm = %cast<c:int|b:tp,tp>%(%set1<c:int|b:tp>%(0xFFFFFFFFFFFFFFFF));
	return %andnb<tp>%(r0, rm);"""
	},
	"notb-32": { "format": "long", "code":
"""	%r<tp>% rm = %cast<c:int|b:tp,tp>%(%set1<c:int|b:tp>%(0xFFFFFFFF));
	return %andnb<tp>%(r0, rm);"""
	},
	"notb-16": { "format": "long", "code":
"""	%r<tp>% rm = %cast<c:int|b:tp,tp>%(%set1<c:int|b:tp>%(0xFFFF));
	return %andnb<tp>%(r0, rm);"""
	},
	"notb-8": { "format": "long", "code":
"""	%r<tp>% rm = %cast<c:int|b:tp,tp>%(%set1<c:int|b:tp>%(0xFF));
	return %andnb<tp>%(r0, rm);"""
	},
	"notb_m-64": { "format": "long", "code":
"""	%m<tp>% mm = %cast_m<c:int|b:tp,tp>%(%tomsk<c:int|b:tp>%(%set1<c:int|b:tp>%(0xFFFFFFFFFFFFFFFF)));
	return %andnb_m<tp>%(m0, mm);"""
	},
	"notb_m-32": { "format": "long", "code":
"""	%m<tp>% mm = %cast_m<c:int|b:tp,tp>%(%tomsk<c:int|b:tp>%(%set1<c:int|b:tp>%(0xFFFFFFFF)));
	return %andnb_m<tp>%(m0, mm);"""
	},
	"notb_m-16": { "format": "long", "code":
"""	%m<tp>% mm = %cast_m<c:int|b:tp,tp>%(%tomsk<c:int|b:tp>%(%set1<c:int|b:tp>%(0xFFFF)));
	return %andnb_m<tp>%(m0, mm);"""
	},
	"notb_m-8": { "format": "long", "code":
"""	%m<tp>% mm = %cast_m<c:int|b:tp,tp>%(%tomsk<c:int|b:tp>%(%set1<c:int|b:tp>%(0xFF)));
	return %andnb_m<tp>%(m0, mm);"""
	},
	"cmpeq-1": { "format": "long", "code":
"""	return %cast_m<c:float,tp>%(%cmpeq<c:float>%(%cast<tp,c:float>%(r0), %cast<tp,c:float>%(r1)));"""
	},
	"cmpeq-2": { "format": "long", "code":
"""	return %cast_m<c:int,tp>%(%cmpeq<c:int>%(%cast<tp,c:int>%(r0), %cast<tp,c:int>%(r1)));"""
	},
	"cmpneq": { "format": "long", "code":
"""	return %notb_m<tp>%(%cmpeq<tp>%(r0, r1));"""
	},
	"cmpge": { "format": "long", "code":
"""	return %orb_m<tp>%(%cmpeq<tp>%(r0, r1), %cmpgt<tp>%(r0, r1));"""
	},
}

implems_emu = {
	"blend": [
		{ "datatypes": [int64, int32, uint64, uint32], "template": tpl_implem_emu["blend-1"]},
		{ "datatypes": all_datatypes, "template": tpl_implem_emu["blend-2"]}, ],
	"sat": [
		{ "datatypes": all_datatypes, "template": tpl_implem_emu["sat"] }, ],
	"fmadd": [
		{ "datatypes": all_float, "template": tpl_implem_emu["fmadd"] }, ],
	"fmsub": [
		{ "datatypes": all_float, "template": tpl_implem_emu["fmsub"] }, ],
	"fnmadd": [
		{ "datatypes": all_float, "template": tpl_implem_emu["fnmadd"] }, ],
	"fnmsub": [
		{ "datatypes": all_float, "template": tpl_implem_emu["fnmsub"] }, ],
	"add_m": [
		{ "instr_name": "add", "datatypes": all_datatypes, "template": tpl_implem_emu["arith_2args_1msk"] }, ],
	"add_mz": [
		{ "instr_name": "add_m", "datatypes": all_datatypes, "template": tpl_implem_emu["arith_2args_1msk_1reg"] }, ],
	"sub_m": [
		{ "instr_name": "sub", "datatypes": all_datatypes, "template": tpl_implem_emu["arith_2args_1msk"] }, ],
	"sub_mz": [
		{ "instr_name": "sub_m", "datatypes": all_datatypes, "template": tpl_implem_emu["arith_2args_1msk_1reg"] }, ],
	"mul_m": [
		{ "instr_name": "mul", "datatypes": all_datatypes, "template": tpl_implem_emu["arith_2args_1msk"] }, ],
	"mul_mz": [
		{ "instr_name": "mul_m", "datatypes": all_datatypes, "template": tpl_implem_emu["arith_2args_1msk_1reg"] }, ],
	"div_m": [
		{ "instr_name": "div", "datatypes": all_float, "template": tpl_implem_emu["arith_2args_1msk"] }, ],
	"div_mz": [
		{ "instr_name": "div_m", "datatypes": all_float, "template": tpl_implem_emu["arith_2args_1msk_1reg"] }, ],
	"min_m": [
		{ "instr_name": "min", "datatypes": all_datatypes, "template": tpl_implem_emu["arith_2args_1msk"] }, ],
	"min_mz": [
		{ "instr_name": "min_m", "datatypes": all_datatypes, "template": tpl_implem_emu["arith_2args_1msk_1reg"] }, ],
	"max_m": [
		{ "instr_name": "max", "datatypes": all_datatypes, "template": tpl_implem_emu["arith_2args_1msk"] }, ],
	"max_mz": [
		{ "instr_name": "max_m", "datatypes": all_datatypes, "template": tpl_implem_emu["arith_2args_1msk_1reg"] }, ],
	"msb": [
		{ "datatypes": [float64, int64, uint64], "template": tpl_implem_emu["msb-64"] },
		{ "datatypes": [float32, int32, uint32], "template": tpl_implem_emu["msb-32"] },
		{ "datatypes": [int16, uint16], "template": tpl_implem_emu["msb-16"] },
		{ "datatypes": [int8, uint8], "template": tpl_implem_emu["msb-8"] }, ],
	"notb": [
		{ "datatypes": [float64, int64, uint64], "template": tpl_implem_emu["notb-64"] },
		{ "datatypes": [float32, int32, uint32], "template": tpl_implem_emu["notb-32"] },
		{ "datatypes": [int16, uint16], "template": tpl_implem_emu["notb-16"] },
		{ "datatypes": [int8, uint8], "template": tpl_implem_emu["notb-8"] }, ],
	"notb_m": [
		{ "datatypes": [float64, int64, uint64], "template": tpl_implem_emu["notb_m-64"] },
		{ "datatypes": [float32, int32, uint32], "template": tpl_implem_emu["notb_m-32"] },
		{ "datatypes": [int16, uint16], "template": tpl_implem_emu["notb_m-16"] },
		{ "datatypes": [int8, uint8], "template": tpl_implem_emu["notb_m-8"] }, ],
	"cmpeq": [
		{ "datatypes": [int64, int32, uint64, uint32], "template": tpl_implem_emu["cmpeq-1"] },
		{ "datatypes": [uint16, uint8], "template": tpl_implem_emu["cmpeq-2"] } ],
	"cmpneq": [
		{ "datatypes": all_datatypes, "template": tpl_implem_emu["cmpneq"] } ],
	"cmpge": [
		{ "datatypes": all_datatypes, "template": tpl_implem_emu["cmpge"] } ],
}

for iemu in implems_emu:
	for sub_iemu in implems_emu[iemu]:
		if "type" not in sub_iemu:
			sub_iemu["type"] = "emulated"

file = open("../include/mipp_v2_impl_AVX_gen.h", "w")

tpl_header_avx = """#ifndef MY_INTRINSICS_PLUS_PLUS_IMPL_GEN_AVX_H_
#define MY_INTRINSICS_PLUS_PLUS_IMPL_AVX_H_
#include "mipp_v2.h"
#include <immintrin.h>"""
j2_template = Template(tpl_header_avx, undefined=StrictUndefined)
print(j2_template.render(), file=file)

gen_defines(isa_avx, file)
gen_structures(isa_avx, file)

gen_functions(isa_avx, file, mipp_funcs, implems_avx)
gen_functions(isa_avx, file, mipp_funcs, implems_emu)
gen_missing_functions(isa_avx, file, mipp_funcs)

dump_dict_json(mipp_funcs, "test.json")

tpl_footer_avx = """#endif /* MY_INTRINSICS_PLUS_PLUS_IMPL_GEN_AVX_H_ */"""
j2_template = Template(tpl_footer_avx, undefined=StrictUndefined)
print(j2_template.render(), file=file)

file.close()