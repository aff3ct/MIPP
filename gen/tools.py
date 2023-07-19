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

datatypes = {
	float64 : { "name" : float64, "category": cfloat, "n_bits" : 64, "cstd": "float64_t", },
	float32 : { "name" : float32, "category": cfloat, "n_bits" : 32, "cstd": "float32_t", },
	  int64 : { "name" :   int64, "category":   cint, "n_bits" : 64, "cstd":   "int64_t", },
	  int32 : { "name" :   int32, "category":   cint, "n_bits" : 32, "cstd":   "int32_t", },
	  int16 : { "name" :   int16, "category":   cint, "n_bits" : 16, "cstd":   "int16_t", },
	   int8 : { "name" :    int8, "category":   cint, "n_bits" :  8, "cstd":    "int8_t", },
	 uint64 : { "name" :  uint64, "category":  cuint, "n_bits" : 64, "cstd":  "uint64_t", },
	 uint32 : { "name" :  uint32, "category":  cuint, "n_bits" : 32, "cstd":  "uint32_t", },
	 uint16 : { "name" :  uint16, "category":  cuint, "n_bits" : 16, "cstd":  "uint16_t", },
	  uint8 : { "name" :   uint8, "category":  cuint, "n_bits" :  8, "cstd":   "uint8_t", },
}

operators = {
    "add"    : {"operation" : "+", "option"  : "+="},
    "sub"    : {"operation" : "-", "option"  : "-="},
    "mul"    : {"operation" : "*", "option"  : "*="},
    "div"    : {"operation" : "/", "option"  : "/="},
    "notb"   : {"operation" : "~", "option"  : "~"},
    "xorb"   : {"operation" : "^", "option"  : "^="},
    "orb"    : {"operation" : "|", "option"  : "|="},
    "andb"   : {"operation" : "&", "option"  : "&="},
    "cmpeq"  : {"operation" : "==", "option" : "=="},
    "cmpneq" : {"operation" : "!=", "option" : "!="},
    "cmplt"  : {"operation" : "<", "option"  : "<"},
    "cmple"  : {"operation" : "<=", "option" : "<="},
    "cmpgt"  : {"operation" : ">", "option"  : ">"},
    "cmpge"  : {"operation" : ">=", "option" : ">="},
}
operators_msk = {
    "==" : "cmpeq",
    "!=" : "cmpneq",
    "<"  : "cmplt",
    "<=" : "cmple",
    ">"  : "cmpgt",
    ">=" : "cmpge",
}


def build_reg(datatype, isa, lmul=0, isa_name=True, cpp=False):
	if cpp:
		str_reg = "rvd"
		if isa_name:
			str_reg += "_"+isa["name"]
		str_reg += "<" + datatype["cstd"]
		if lmul:
			str_reg += "," + str(int(lmul))
		str_reg += ">"
		return str_reg
	else:
		str_reg = "rvd_"
		if isa_name:
			str_reg += isa["name"] + "_"
		str_reg += datatype["category"] + str(datatype["n_bits"])
		if lmul:
			str_reg += "_m" + str(int(lmul))
		str_reg += "_t"
		return str_reg

def build_msk(datatype, isa, lmul=0, isa_name=True, cpp=False):
	if cpp:
		str_msk = "rvm"
		if isa_name:
			str_msk += "_"+isa["name"]
		str_msk += "<" + datatype["cstd"]
		if lmul:
			str_msk += "," + str(int(lmul))
		str_msk += ">"
		return str_msk
	else:
		str_msk = "rvm_"
		if isa_name:
			str_msk += isa["name"] + "_"
		str_msk += datatype["category"] + str(datatype["n_bits"])
		if lmul:
			str_msk += "_m" + str(int(lmul))
		str_msk += "_t"
		return str_msk



# build class Rvd and Rvm
def build_Reg(datatype, isa, lmul=0, isa_name=True, cpp=True):
	if cpp:
		str_reg = "Rvd <T "
		if lmul:
			str_reg += "," + str(int(lmul))
		str_reg += ">"
		return str_reg
	else:
		str_reg = "Rvd_"
		if isa_name:
			str_reg += isa["name"] + "_"
		str_reg += datatype["category"] + str(datatype["n_bits"])
		if lmul:
			str_reg += "_m" + str(int(lmul))
		str_reg += "_t"
		return str_reg
def build_Msk(datatype, isa, lmul=0, isa_name=True, cpp=False):
	if cpp:
		str_msk = "Rvm"
		if isa_name:
			str_msk += "_"+isa["name"]
		str_msk += "<T " 
		if lmul:
			str_msk += "," + str(int(lmul))
		str_msk += ">"
		return str_msk
	else:
		str_msk = "Rvm_"
		if isa_name:
			str_msk += isa["name"] + "_"
		str_msk += datatype["category"] + str(datatype["n_bits"])
		if lmul:
			str_msk += "_m" + str(int(lmul))
		str_msk += "_t"
		return str_msk
		
def build_val(datatype, isa, lmul=0):
	return datatype["category"] + str(datatype["n_bits"]) + "_t"

def build_ptr(datatype, isa, lmul=0):
	return datatype["category"] + str(datatype["n_bits"]) + "_t*"

def build_N(datatype, isa, lmul=0, isa_name=True):
	str_N = "MIPP_"
	if isa_name:
		str_N += isa["name"].upper() + "_"
	str_N += "N_" + datatype["category"].upper() + str(datatype["n_bits"]).upper()
	if lmul:
		str_N += "_M" + str(int(lmul))
	return str_N

def build_type(type, datatype, isa, lmul=0, isa_name=True, cpp=False):
	if type:
		if type == "reg":
			return build_reg(datatype, isa, lmul, isa_name, cpp)
		elif type == "msk":
			return build_msk(datatype, isa, lmul, isa_name, cpp)
		elif type == "val":
			return build_val(datatype, isa)
		elif type == "ptr":
			return build_ptr(datatype, isa)
	else:
		return "void"
# for object layer
def build_class_type(type, datatype, isa, lmul=0, isa_name=True, cpp=False):
	if type:
		if type == "reg":
			return build_Reg(datatype, isa, lmul, isa_name, cpp)
		elif type == "msk":
			return build_Msk(datatype, isa, lmul, isa_name, cpp)
		elif type == "val":
			return build_val(datatype, isa)
		elif type == "ptr":
			return build_ptr(datatype, isa)
	else:
		return "void"
def lmul_specialized(proto):
	n_lmul_spe = 0
	for arg in proto["args"]:
		if (arg["type"] == "reg" or arg["type"] == "msk") and not arg["fixeddatatype"]:
			n_lmul_spe = n_lmul_spe +1
	return n_lmul_spe

def type_specialized(proto):
	n_type_spe = 0
	for arg in proto["args"]:
		if not arg["fixeddatatype"]:
			n_type_spe = n_type_spe +1
	return n_type_spe

def build_proto(proto, dt_par, dt_ret, isa, func_name, lmul=0, isa_name=True, cpp=False):
	"""if lmul and (not cpp or (cpp and not lmul_specialized(proto))):
		func_name += "_m" + str(int(lmul))"""
	realdatatype = datatypes[dt_ret]
	if (proto["ret"]["fixeddatatype"]):
		realdatatype = datatypes[proto["ret"]["fixeddatatype"]]
	p = build_type(proto["ret"]["type"], realdatatype, isa, lmul, isa_name, cpp) + " " + func_name + "("
	cnt_reg = 0
	cnt_msk = 0
	cnt_val = 0
	cnt_ptr = 0
	is_first = True
	for arg in proto["args"]:
		if not is_first:
			p += ", "
		realdatatype = datatypes[dt_par]
		if (arg["fixeddatatype"]):
			realdatatype = datatypes[arg["fixeddatatype"]]
		if arg["charac"] == "RO":
			p += "const "
		p += build_type(arg["type"], realdatatype, isa, lmul, isa_name, cpp)
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


# For layer object
def build_proto_object(proto, dt_par, dt_ret, isa, func_name, lmul=0, isa_name=False, cpp=False):
	"""if lmul and (not cpp or (cpp and not lmul_specialized(proto))):
		func_name += "_m" + str(int(lmul))"""
	realdatatype = datatypes[dt_ret]

	if (proto["ret"]["fixeddatatype"]):
		realdatatype = datatypes[proto["ret"]["fixeddatatype"]]
	p = build_class_type(proto["ret"]["type"], realdatatype, isa, lmul, isa_name, cpp) + " " + func_name + "(" 
	
	cnt_reg = 0
	cnt_msk = 0
	cnt_val = 0
	cnt_ptr = 0
	is_first = True
	for arg in proto["args"]:
		if not is_first:
			p += ","

		realdatatype = datatypes[dt_par]
		if (arg["fixeddatatype"]):
			realdatatype = datatypes[arg["fixeddatatype"]]
		if arg["charac"] == "RO":
			p += " const "

		p += build_class_type(arg["type"], realdatatype, isa, lmul, isa_name, cpp)
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

# print "return func" 
def build_call(proto, dt_par, dt_ret, isa, func_name, lmul=0, isa_name=True):
	"""if lmul:
		func_name += "_m" + str(int(lmul))"""
	p = ""
	realdatatype = datatypes[dt_ret]
	if (proto["ret"]["type"]):
		p += "return "
	p += func_name + "("
	cnt_reg = 0
	cnt_msk = 0
	cnt_val = 0
	cnt_ptr = 0
	is_first = True
	for arg in proto["args"]:
		if not is_first:
			p += ", "
		if arg["type"] == "reg":
			p += "r" + str(cnt_reg)
			cnt_reg = cnt_reg +1
		elif arg["type"] == "msk":
			p += "m" + str(cnt_msk)
			cnt_msk = cnt_msk +1
		elif arg["type"] == "val":
			p += "v" + str(cnt_val)
			cnt_val = cnt_val +1
		elif arg["type"] == "ptr":
			p += "p" + str(cnt_ptr)
			cnt_ptr = cnt_ptr +1
		is_first = False
	return p + ")";

# build call function  
def _build_call_lmul(proto, dt_par, dt_ret, isa, func_name, lmul, part):
	"""if lmul:
		func_name += "_m" + str(int(lmul))"""
	p = ""
	realdatatype = datatypes[dt_ret]
	for arg in proto["args"]:
		if (proto["ret"]["type"] == "reg" and arg["type"] == "reg"):
			p += "r" + str(cnt_reg) + ".r" + str(int(part))
			cnt_reg = cnt_reg +1							
		elif (proto["ret"]["type"] == "reg" and arg["type"] == "msk"):
			
			p += "res.r"  + str(int(part)) + " = "
			p += "m" + str(cnt_msk) + ".m" + str(int(part))

	p += func_name + "("
	cnt_reg = 0
	cnt_msk = 0
	cnt_val = 0
	cnt_ptr = 0
	is_first = True
	for arg in proto["args"]:
		if not is_first:
			p += ", "
		if arg["type"] == "reg":
			p += "r" + str(cnt_reg) + ".r" + str(int(part))
			cnt_reg = cnt_reg +1
		elif arg["type"] == "msk":
			p += "m" + str(cnt_msk) + ".m" + str(int(part))
			cnt_msk = cnt_msk +1
		elif arg["type"] == "val":
			p += "v" + str(cnt_val)
			cnt_val = cnt_val +1
		elif arg["type"] == "ptr":
			p += "p" + str(cnt_ptr) + " + " + str(int(part-1)) + "*MIPP_LMUL_STRIDE(sizeof(*p" + str(cnt_ptr) + "), " + str(int(lmul)) +")"
			cnt_ptr = cnt_ptr +1
		is_first = False
	return p + ")";

def build_call_lmul(proto, dt_par, dt_ret, isa, func_name, lmul=2, isa_name=True):
	lmul_2 = int(lmul / 2)
	str_code = ""
	realdatatype = datatypes[dt_ret]
	if proto["ret"]["fixeddatatype"]:
		realdatatype = datatypes[proto["ret"]["fixeddatatype"]]
	if proto["ret"]["type"]:
		str_code += "\t" + build_type(proto["ret"]["type"], realdatatype, isa, lmul, isa_name) + " res;\n"
		print(str_code)
	str_code += "\t" + _build_call_lmul(proto, dt_par, dt_ret, isa, func_name, lmul_2, 1) + ";\n"
	str_code += "\t" + _build_call_lmul(proto, dt_par, dt_ret, isa, func_name, lmul_2, 2) + ";"
	"""if (proto["ret"]["type"]):
					str_code += "\n\t" + "return res;"""
	return str_code;


# Build other functions build_func_name_short & build_cpp_func_name_short
def build_func_name_short(isa, dt, mipp_name, isa_name=True):
	param_type = datatypes[dt]["category"] + str(datatypes[dt]["n_bits"])
	if isa_name:
		return "mipp_" + isa["name"] + "_" + mipp_name + "_" +  param_type
	else:
		return  mipp_name + "_" +  param_type

def build_func_name_short_object(isa, dt, mipp_name, isa_name=True):
	param_type = datatypes[dt]["category"]+ str(datatypes[dt]["n_bits"])
	if isa_name:
		return "mipp_" + isa["name"] + "_" + mipp_name + "_" +  param_type
	else:
		return  mipp_name 

def build_cpp_func_name_short(proto, dt_ret, mipp_name):
	return_type = datatypes[dt_ret]["category"] + str(datatypes[dt_ret]["n_bits"])
	if type_specialized(proto):
		mipp_name = mipp_name.replace("_mz", "")
		mipp_name = mipp_name.replace("_m", "")
		mipp_name = mipp_name.replace("_k", "")
		return mipp_name + "_" +return_type
	else:
		return_type = datatypes[dt_ret]["category"] + str(datatypes[dt_ret]["n_bits"])
		return mipp_name + "_" +return_type


# Build cast's functions build_func_name & build_cpp_func_name
def build_func_name(isa, dt_par, dt_ret, mipp_name, isa_name=True):
	param_type = datatypes[dt_par]["category"] + str(datatypes[dt_par]["n_bits"])
	return_type = datatypes[dt_ret]["category"] + str(datatypes[dt_ret]["n_bits"])
	if isa_name:
		return "mipp_" + isa["name"] + "_" + mipp_name + "_" + param_type + "_" + return_type
	else:
		return "mipp_" + mipp_name + "_" + param_type + "_" + return_type

def build_func_name_object(isa, dt_par, dt_ret, mipp_name):
	param_type = datatypes[dt_par]["category"] + str(datatypes[dt_par]["n_bits"])
	return_type = datatypes[dt_ret]["category"] + str(datatypes[dt_ret]["n_bits"])
	return  mipp_name 

def build_cpp_func_name(isa, dt_par, dt_ret, mipp_name):

	param_type = datatypes[dt_par]["category"] + str(datatypes[dt_par]["n_bits"])
	return_type = datatypes[dt_ret]["category"] + str(datatypes[dt_ret]["n_bits"])
	
	return mipp_name + "_" + param_type + "_" + return_type
def build_cpp_func_name_object(isa, dt_par, dt_ret, mipp_name):

	param_type = datatypes[dt_par]["category"] + str(datatypes[dt_par]["n_bits"])
	return_type = datatypes[dt_ret]["category"] + str(datatypes[dt_ret]["n_bits"])
	
	return mipp_name 
	

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
				dt += datatypes[dt_par]["category"]
			elif dt_info_carac_dic["c"] == "tr":
				dt += datatypes[dt_ret]["category"]
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
			dt += datatypes[dt_par]["category"]

		if "b" in dt_info_carac_dic:
			if dt_info_carac_dic["b"] == "tp":
				dt += str(datatypes[dt_par]["n_bits"])
			elif dt_info_carac_dic["b"] == "tr":
				dt += str(datatypes[dt_ret]["n_bits"])
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
			dt += str(datatypes[dt_par]["n_bits"])
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
			converted_ir = converted_ir.replace("%" + s + "%", build_reg(datatypes[dt], isa))
		elif item_type == "m":
			dt_info = re.findall(r'\<(.*)\>', s)[0]
			dt_info_params = dt_info.split(",")
			dt = ""
			if len(dt_info_params) == 1:
				dt = build_dt(dt_info_params[0], isa, dt_par, dt_ret)
			if dt not in isa["datatypes"]:
				print("Panic: '" + dt + "' is not available.")
				exit(-1)
			converted_ir = converted_ir.replace("%" + s + "%", build_msk(datatypes[dt], isa))
		elif item_type == "v":
			dt_info = re.findall(r'\<(.*)\>', s)[0]
			dt_info_params = dt_info.split(",")
			dt = ""
			if len(dt_info_params) == 1:
				dt = build_dt(dt_info_params[0], isa, dt_par, dt_ret)
			if dt not in isa["datatypes"]:
				print("Panic: '" + dt + "' is not available.")
				exit(-1)
			converted_ir = converted_ir.replace("%" + s + "%", build_val(datatypes[dt], isa))
		elif item_type == "N":
			dt_info = re.findall(r'\<(.*)\>', s)[0]
			dt_info_params = dt_info.split(",")
			dt = ""
			if len(dt_info_params) == 1:
				dt = build_dt(dt_info_params[0], isa, dt_par, dt_ret)
			if dt not in isa["datatypes"]:
				print("Panic: '" + dt + "' is not available.")
				exit(-1)
			converted_ir = converted_ir.replace("%" + s + "%", build_N(datatypes[dt], isa))
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
