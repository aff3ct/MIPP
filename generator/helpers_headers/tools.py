from jinja2 import Template, StrictUndefined
import json
import re

# houps test code generation option to do displace
# warning order
all_ldiv = [2]#,4]

all_lmul = [1,2,4,8]
# end houps test code generation option to do displace

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
all_64bit = [float64, int64, uint64]
all_32bit = [float32, int32, uint32]
all_16bit = [int16, uint16]
all_8bit = [int8, uint8]

all_datatypes_cart_prod = [];
for dt_ret in all_datatypes:
	for dt_par in all_datatypes:
		new_entry = [dt_par, dt_ret]
		if new_entry not in all_datatypes_cart_prod:
			all_datatypes_cart_prod.append(dt_par + "," + dt_ret);


all_datatypes_cart_prod_except_f64 = []
for dt_ret in all_datatypes:
	if (dt_ret != "float64"):
		for dt_par in all_datatypes:
			if (dt_par != "float64"):
				new_entry = [dt_par, dt_ret]
				if new_entry not in all_datatypes_cart_prod_except_f64:
					all_datatypes_cart_prod_except_f64.append(dt_par + "," + dt_ret);

all_datatypes_cart_prod_inc_f64 = [];
for dt_ret in all_datatypes:
	for dt_par in all_datatypes:
		new_entry = [dt_par, dt_ret]
		if new_entry not in all_datatypes_cart_prod_inc_f64:
			if (dt_par == "float64" or dt_ret == "float64"):
				all_datatypes_cart_prod_inc_f64.append(dt_par + "," + dt_ret);
			
def find_data_types_from(criteria):
	all_types = dict(datatypes);
	for datatype in datatypes:
		current_type = datatypes[datatype]
		for key in criteria:
			if current_type[key]!=criteria[key]:
				del all_types[datatype]
				break;
	return all_types;
			
def find_one_data_types_from(criteria):
	all_types = find_data_types_from(criteria);
	if len(all_types) != 1:
		print("warning or error waiting for reduction size 1")
	return next(iter(all_types.values()));

datatypes = {
	float64 : { "name" : float64, "category": cfloat, "n_bits" : 64, "cstd": "float64_t", "literal_suffix": "d", },
	float32 : { "name" : float32, "category": cfloat, "n_bits" : 32, "cstd": "float32_t", "literal_suffix": "f", },
	  int64 : { "name" :   int64, "category":   cint, "n_bits" : 64, "cstd":   "int64_t", "literal_suffix": "LL", },
	  int32 : { "name" :   int32, "category":   cint, "n_bits" : 32, "cstd":   "int32_t", "literal_suffix": "", },
	  int16 : { "name" :   int16, "category":   cint, "n_bits" : 16, "cstd":   "int16_t", "literal_suffix": "", },
	   int8 : { "name" :    int8, "category":   cint, "n_bits" :  8, "cstd":    "int8_t", "literal_suffix": "", },
	 uint64 : { "name" :  uint64, "category":  cuint, "n_bits" : 64, "cstd":  "uint64_t", "literal_suffix": "UL", },
	 uint32 : { "name" :  uint32, "category":  cuint, "n_bits" : 32, "cstd":  "uint32_t", "literal_suffix": "U", },
	 uint16 : { "name" :  uint16, "category":  cuint, "n_bits" : 16, "cstd":  "uint16_t", "literal_suffix": "", },
	  uint8 : { "name" :   uint8, "category":  cuint, "n_bits" :  8, "cstd":   "uint8_t", "literal_suffix": "", },
}


#  Operator overloading in the object layer
operators_arithm = {
	"add"    : {"operation" : "+", "option"  : "+="},
	"sub"    : {"operation" : "-", "option"  : "-="},
	"mul"    : {"operation" : "*", "option"  : "*="},
	"div"    : {"operation" : "/", "option"  : "/="},
}
operators_binary = {
	"xorb"   : {"operation" : "^", "option"  : "^="},
	"orb"    : {"operation" : "|", "option"  : "|="},
	"andb"   : {"operation" : "&", "option"  : "&="},
}
operators_order = {
	"cmpeq"  : {"operation" : "==", "option" : "=="},
	"cmpneq" : {"operation" : "!=", "option" : "!="},
	"cmplt"  : {"operation" : "<", "option"  : "<"},
	"cmple"  : {"operation" : "<=", "option" : "<="},
	"cmpgt"  : {"operation" : ">", "option"  : ">"},
	"cmpge"  : {"operation" : ">=", "option" : ">="},
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
			if int(lmul) > 0:
				str_reg += "_m" + str(int(lmul))
			if int(lmul) < 0:
				ldiv = -int(lmul)
				str_reg += "_d" + str(ldiv)
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
			if int(lmul) > 0:
				str_msk += "_m" + str(int(lmul))
			if int(lmul) < 0:
				ldiv = -int(lmul)
				str_msk += "_d" + str(ldiv)
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
	"""	str_N = "MIPP_"
	if isa_name:
		str_N += isa["name"].upper() + "_"""
	if isa_name:
		isa_name_upper = isa["name"].upper()+"_"
	else:
		isa_name_upper=""
	
	str_N = "MIPP_"+isa_name_upper+"N_" + datatype["category"].upper() + str(datatype["n_bits"]).upper()
	if lmul:
		str_N += "_M" + str(int(lmul))
	return str_N

def build_type(type, datatype, isa,lmul=0, isa_name=True, cpp=False):
	if type:
		if type == "reg":
			return build_reg(datatype, isa, lmul, isa_name, cpp)
		elif type == "msk":
			return build_msk(datatype, isa, lmul, isa_name, cpp)
		elif type == "val":
			return build_val(datatype, isa)
		elif type == "ptr":
			return build_ptr(datatype, isa)
		elif type == "Nele":
			return datatype["cstd"]
		elif type == "vindex":
			same_size_integer_datatype = find_one_data_types_from({"n_bits": datatype["n_bits"], "category": cint});
			return build_reg(same_size_integer_datatype, isa, lmul, isa_name, cpp)
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
			return build_ptr(datatype, isa,{},isa_name)
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

# Build prototype of set0
def build_proto_set0(dt_ret, lmul, func_name, masked_version=False):
	template = f"<{dt_ret}_t, {lmul}>"
	if func_name == "set0":
		reg_type = "rvd"
	elif func_name == "set0_k":
		reg_type = "rvm"
	else:
		reg_type = "rvd"

	# masked template form (no template<>)
	if masked_version:
		if masked_version == "mask":
			template = f"<M, {dt_ret}_t, {lmul}>"
		elif masked_version == "maskz":
			template = f"<Z, {dt_ret}_t, {lmul}>"
		elif masked_version == "masks":
			template = f"<S, {dt_ret}_t, {lmul}>"
		else:
			print("error: masked_version should be mask, maskz or masks")
			exit(-1)

		# set0 has no other args, but masked forms still take m0 (and maybe rsrc)
		if masked_version in ("mask", "maskz"):
			return f"inline {reg_type}<{dt_ret}_t, {lmul}> {func_name}{template}(const rvm<{dt_ret}_t,{lmul}> m0"
		elif masked_version == "masks":
			return f"inline {reg_type}<{dt_ret}_t, {lmul}> {func_name}{template}(const rvm<{dt_ret}_t,{lmul}> m0, const {reg_type}<{dt_ret}_t,{lmul}> rsrc"

	# unmasked (unchanged)
	return f"template <>\ninline {reg_type}<{dt_ret}_t, {lmul}> {func_name}{template}("


# Build prototype of set
def build_proto_set(dt_ret, lmul, func_name, masked_version=False):
	dt_par = None
	template = f"<{dt_ret}_t, {lmul}>"
	if func_name == "set":
		dt_par = f"{dt_ret}_t"
		reg_type = "rvd"
	elif func_name == "set_k":
		dt_par = "int32_t"
		reg_type = "rvm"
	else:
		# keep fallback sane
		dt_par = f"{dt_ret}_t"
		reg_type = "rvd"

	if masked_version:
		if masked_version == "mask":
			template = f"<M, {dt_ret}_t, {lmul}>"
		elif masked_version == "maskz":
			template = f"<Z, {dt_ret}_t, {lmul}>"
		elif masked_version == "masks":
			template = f"<S, {dt_ret}_t, {lmul}>"
		else:
			print("error: masked_version should be mask, maskz or masks")
			exit(-1)

		if masked_version in ("mask", "maskz"):
			return (
				f"inline {reg_type}<{dt_ret}_t, {lmul}> {func_name}{template}("
				f"const rvm<{dt_par},{lmul}> m0, "
				f"const {dt_par} vals[MIPP_N_{dt_ret.upper()}]"
			)
		elif masked_version == "masks":
			return (
				f"inline {reg_type}<{dt_ret}_t, {lmul}> {func_name}{template}("
				f"const rvm<{dt_par},{lmul}> m0, "
				f"const rvd<{dt_par},{lmul}> rsrc, "
				f"const {dt_par} vals[MIPP_N_{dt_ret.upper()}]"
			)

	# unmasked (unchanged)
	return f"template <>\ninline {reg_type}<{dt_ret}_t, {lmul}> {func_name}{template}(const {dt_par} vals[MIPP_N_{dt_ret.upper()}]"


def build_proto_set1(dt_ret, lmul, func_name, masked_version=False):
	template = f"<{dt_ret}_t, {lmul}>"
	if func_name == "set1":
		dt_par = f"{dt_ret}_t"
		reg_type = "rvd"
	elif func_name == "set1_k":
		dt_par = "int32_t"
		reg_type = "rvm"
	else:
		dt_par = f"{dt_ret}_t"
		reg_type = "rvd"

	if masked_version:
		if masked_version == "mask":
			template = f"<M, {dt_ret}_t, {lmul}>"
		elif masked_version == "maskz":
			template = f"<Z, {dt_ret}_t, {lmul}>"
		elif masked_version == "masks":
			template = f"<S, {dt_ret}_t, {lmul}>"
		else:
			print("error: masked_version should be mask, maskz or masks")
			exit(-1)

		if masked_version in ("mask", "maskz"):
			return (
				f"inline {reg_type}<{dt_ret}_t, {lmul}> {func_name}{template}("
				f"const rvm<{dt_par},{lmul}> m0, "
				f"const {dt_par} v0"
			)
		elif masked_version == "masks":
			return (
				f"inline {reg_type}<{dt_ret}_t, {lmul}> {func_name}{template}("
				f"const rvm<{dt_par},{lmul}> m0, "
				f"const rvd<{dt_par},{lmul}> rsrc, "
				f"const {dt_par} v0"
			)

	# unmasked (unchanged)
	return f"template <>\ninline {reg_type}<{dt_ret}_t, {lmul}> {func_name}{template}(const {dt_par} v0"

def build_proto_load(dt_ret, lmul, func_name, masked_version=False):
	

	if func_name == "load" or func_name == "loadu":
		dt_par = f"{dt_ret}_t"
		template = f"<{dt_ret}_t, {lmul}>"
		if masked_version:
			if masked_version == "mask" :
				template = f"<M, {dt_ret}_t, {lmul}>"
			elif masked_version == "maskz" :
				template = f"<Z, {dt_ret}_t, {lmul}>"
			elif masked_version == "masks" :
				template = f"<S, {dt_ret}_t, {lmul}>"
			else :
				print("error: masked_version should be mask, maskz or masks")
				exit(-1)
		reg_type = "rvd"
  
	if masked_version:
		if masked_version == "mask" :
			ret = f"inline {reg_type}<{dt_ret}_t, {lmul}> {func_name}{template}(const rvm<{dt_par},{lmul}> m0, const {dt_par}* p0"
		elif masked_version == "maskz" :
			ret = f"inline {reg_type}<{dt_ret}_t, {lmul}> {func_name}{template}(const rvm<{dt_par},{lmul}> m0, const {dt_par}* p0"
		elif masked_version == "masks" :
			ret = f"inline {reg_type}<{dt_ret}_t, {lmul}> {func_name}{template}(const rvm<{dt_par},{lmul}> m0, const rvd<{dt_par},{lmul}> rsrc, const {dt_par}* p0"
		else : 
			print("error: masked_version should be mask, maskz or masks")
			exit(-1)
	else :
		ret = f"template <>\ninline {reg_type}<{dt_ret}_t, {lmul}> {func_name}{template}(const {dt_par}* p0"
	return  ret
	

#function message error set functions
def gen_set_func_error(func_name,file):
	if func_name == "set":
		print(f"template <typename T, int LMULT=1> inline rvd<T, LMULT> {func_name}(const T[N<T>()]) {{ std::cerr << \"{func_name}\" << std::endl; exit(-1);}}\n",file=file)
	if func_name == "set1":
		print(f"template <typename T, int LMULT=1> inline rvd<T, LMULT> {func_name}(const T) {{ std::cerr << \"{func_name}\" << std::endl; exit(-1);}}\n",file=file)
	if func_name == "set0":
		print(f"template <typename T, int LMULT=1> inline rvd<T, LMULT> {func_name}() {{ std::cerr << \"{func_name}\" << std::endl; exit(-1);}}\n",file=file)
	if func_name == "set_k":
		print(f"template <typename T, int LMULT=1> inline rvm<T, LMULT> {func_name}(const int32_t[N<T>()]) {{ std::cerr << \"{func_name}\" << std::endl; exit(-1);}}\n",file=file)
	if func_name == "set0_k":
		print(f"template <typename T, int LMULT=1> inline rvm<T, LMULT> {func_name}() {{ std::cerr << \"{func_name}\" << std::endl; exit(-1);}}\n",file=file)
	if func_name == "set1_k":
		print(f"template <typename T, int LMULT=1> inline rvm<T, LMULT> {func_name}(const int32_t v0) {{ std::cerr << \"{func_name}\" << std::endl; exit(-1);}}\n",file=file)
	if func_name == "load" or func_name == "loadu":
		print(f"template <typename T, int LMULT=1> inline rvd<T, LMULT> {func_name}(const T* p0) {{ std::cerr << \"{func_name}\" << std::endl; exit(-1);}}\n",file=file)


def build_proto(proto, dt_par, dt_ret, isa, func_name, lmul=0, isa_name=True, cpp=False, masked_version=False):
	"""if lmul and (not cpp or (cpp and not lmul_specialized(proto))):
		func_name += "_m" + str(int(lmul))"""

	#build proto for set functions
	if func_name == "set0" or func_name =="set0_k":
		return  build_proto_set0(dt_ret, lmul, func_name, masked_version) +')'
	if func_name == "set" or func_name =="set_k":
		return  build_proto_set(dt_ret, lmul, func_name, masked_version) +')'
	if func_name =="set1_k" or func_name =="set1":
		return  build_proto_set1(dt_ret, lmul, func_name, masked_version) +')'
	if func_name =="load" or func_name =="loadu":
		return  build_proto_load(dt_ret, lmul, func_name, masked_version) +')'

	realdatatype = datatypes[dt_ret]
	if (proto["ret"]["fixeddatatype"]):
		realdatatype = datatypes[proto["ret"]["fixeddatatype"]]
	if not masked_version:
		lmul_str = ""
		if lmul > 0 and (not cpp ):
			lmul_str = "_m" + str(int(lmul))
		p = "inline " + build_type(proto["ret"]["type"], realdatatype, isa, lmul, isa_name, cpp) + " " + func_name + lmul_str + "("

	else : #we assume "mask" or "maskz" is passed in masked_version if it's not false.
		lmul_str = ""
		if lmul > 0 and (not cpp or (cpp and not lmul_specialized(proto))):
			lmul_str = "_m" + str(int(lmul))
		p = "inline " + build_type(proto["ret"]["type"], realdatatype, isa, lmul, isa_name, cpp) + " " + func_name + "_" + masked_version + lmul_str + "("
	cnt_reg = 0
	cnt_msk = 0
	cnt_val = 0
	cnt_ptr = 0
	is_first = True
	
	#add m0 as first argument for masked version of function
	if masked_version:
		if masked_version == "mask" or masked_version == "maskz":
			p += build_msk(datatypes[dt_par], isa, lmul, isa_name, cpp) + " m0"
			
		elif masked_version == "masks" :
			p += "const " + build_msk(datatypes[dt_par], isa, lmul, isa_name, cpp) + " m0"
			p += ", " + build_reg(datatypes[dt_par], isa, lmul, isa_name, cpp) + " rsrc"
		cnt_msk = cnt_msk +1		
		is_first = False
		#print(p, "cpp=", cpp)

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
		elif arg["type"] == "Nele":
			p += " vals["+build_N(datatypes[dt_par],isa,{},isa_name)+"]"
		elif arg["type"] == "vindex":
			p += " vi"
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
		elif arg["type"] == "vindex":
			p += " vi"
		is_first = False

	return p + ")";


def build_call(proto, dt_par, dt_ret, isa, func_name, lmul=0, isa_name=True, masked_version=False):
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
 
	if masked_version:
		if masked_version == "mask" or masked_version == "maskz":
				p += "m0"
		elif masked_version == "masks" :
			p += "m0, rsrc"
		cnt_msk = cnt_msk +1		
		is_first = False
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
		elif arg["type"] == "Nele":
			p += "vals"
		elif arg["type"] == "vindex":
			p += " vi"
		is_first = False
	return p + ")";

# build call function  
def _build_call_lmul(proto, dt_par, dt_ret, isa, func_name, lmul, part, masked_version=False):
	"""if lmul:
		func_name += "_m" + str(int(lmul))"""
	p = ""
	if proto["ret"]["type"] == "reg":
		p += "res.r" + str(int(part)) + " = "
	elif proto["ret"]["type"] == "msk":
		p += "msk.m"  + str(int(part))+ " = "
  
	p += func_name + "("
	cnt_reg = 0
	cnt_msk = 0
	cnt_val = 0
	cnt_ptr = 0
	is_first = True
 
	if masked_version:
		if masked_version == "mask" or masked_version == "maskz":
			p += "m0.m" + str(int(part))
		elif masked_version == "masks" :
			p += "m0.m" + str(int(part)) + ", rsrc.r" + str(int(part))
		cnt_msk = cnt_msk +1		
		is_first = False

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
		elif arg["type"] == "Nele":
			p += "vals"
		is_first = False
	return p + ")";

def build_call_lmul(proto, dt_par, dt_ret, isa, func_name, lmul=2, isa_name=True, masked_version=False):
	lmul_2 = int(lmul / 2)
	str_code = ""
	realdatatype = datatypes[dt_ret]
	if proto["ret"]["fixeddatatype"]:
		realdatatype = datatypes[proto["ret"]["fixeddatatype"]]
	if proto["ret"]["type"] == "reg":
		str_code += "\t" + build_type(proto["ret"]["type"], realdatatype, isa, lmul, isa_name) + " res;\n"
	elif proto["ret"]["type"] == "msk":
		str_code += "\t" + build_type(proto["ret"]["type"], realdatatype, isa, lmul, isa_name) + " msk;\n"
	
	str_code += "\t" + _build_call_lmul(proto, dt_par, dt_ret, isa, func_name, lmul_2, 1, masked_version=masked_version) + ";\n"
	str_code += "\t" + _build_call_lmul(proto, dt_par, dt_ret, isa, func_name, lmul_2, 2, masked_version=masked_version) + ";"
	if proto["ret"]["type"] == "reg":
		str_code += "\n\t" + "return res;";
	elif proto["ret"]["type"] == "msk":
		str_code += "\n\t" + "return msk;";
	return str_code;

# Build other functions build_func_name_short & build_cpp_func_name_short
def build_func_name_short(isa, dt, mipp_name, isa_name=True, lmul=0, masked_version=False):
	param_type = datatypes[dt]["category"] + str(datatypes[dt]["n_bits"])
	lmul_str = ""
	if lmul :
		lmul_str = "_m" + str(int(lmul))

	mask_str = ""
	if masked_version:
		mask_str = "_" + masked_version

	if isa_name:
		return "mipp_" + isa["name"] + "_" + mipp_name + "_" +  param_type + mask_str + lmul_str
	else:
		return "mipp_" + mipp_name + "_" +  param_type + mask_str + lmul_str

def build_cpp_func_name_short(proto, dt_ret, mipp_name, masked_version=False):
	if type_specialized(proto):
		mipp_name = mipp_name.replace("_mz", "")
		mipp_name = mipp_name.replace("_m", "")
		mipp_name = mipp_name.replace("_k", "")
		return mipp_name
	else:
		return_type = datatypes[dt_ret]["category"] + str(datatypes[dt_ret]["n_bits"])
		return mipp_name 

# Build cast's functions build_func_name & build_cpp_func_name
def build_func_name(isa, dt_par, dt_ret, mipp_name, isa_name=True, lmul=0, masked_version=False):
	param_type = datatypes[dt_par]["category"] + str(datatypes[dt_par]["n_bits"])
	return_type = datatypes[dt_ret]["category"] + str(datatypes[dt_ret]["n_bits"])
	lmul_str = ""
	if lmul :
		lmul_str = "_m" + str(int(lmul))

	mask_str = ""

  
	if isa_name:
		return "mipp_" + isa["name"] + "_" + mipp_name + "_" + param_type + "_" + return_type + mask_str + lmul_str
	else:
		return "mipp_" + mipp_name + "_" + param_type + "_" + return_type + mask_str + lmul_str

def build_cpp_func_name(dt_ret, mipp_name, masked_version=False):
	mipp_name = mipp_name.replace("_mz", "")
	mipp_name = mipp_name.replace("_m", "")
	mipp_name = mipp_name.replace("_k", "")
	return_type = datatypes[dt_ret]["category"] + str(datatypes[dt_ret]["n_bits"])
	return mipp_name + "_" + return_type

def build_ifdef_rec(funcs, func_name, dt_key):
	str_ifdef = ""
	if "implem_status" in funcs[func_name]:
		if dt_key in funcs[func_name]["implem_status"]:
			is_first_or = True
			str_ifdef_sub = ""
			str_end_sub_token = ""
			for implem in funcs[func_name]["implem_status"][dt_key]:
				if not is_first_or:
					str_ifdef_sub = "( " + str_ifdef_sub + " || "
					str_end_sub_token = " )"
				is_first_and = True
				str_ifdef_sub_sub = ""
				for f_name in implem["requirements"]:
					for fdt_key in implem["requirements"][f_name]:
						ret = build_ifdef_rec(funcs, f_name, fdt_key)
						if ret:
							if not is_first_and:
								str_ifdef_sub_sub = str_ifdef_sub_sub + " && "
							str_ifdef_sub_sub = str_ifdef_sub_sub + ret
							is_first_and = False

				if implem["if"] and str_ifdef_sub_sub:
					str_ifdef_sub = str_ifdef_sub + implem["if"] + str_end_sub_token + " && " + str_ifdef_sub_sub
				if implem["if"] and not str_ifdef_sub_sub:
					str_ifdef_sub =  str_ifdef_sub + implem["if"] + str_end_sub_token
				if str_ifdef_sub_sub and not implem["if"]:
					str_ifdef_sub = str_ifdef_sub + str_ifdef_sub_sub + str_end_sub_token

				if implem["if"] or str_ifdef_sub_sub:
					is_first_or = False

			if str_ifdef_sub:
				str_ifdef = str_ifdef_sub
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
				str_ifdef_and = str_ifdef_and + ret
				is_first_and = False

	if str_ifdef and str_ifdef_and:
		str_ifdef = str_ifdef + " && " + str_ifdef_and
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

def parse_placeholders(ir, isa, funcs, func_name, dt_par, dt_ret,lmul=0):
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
			converted_ir = converted_ir.replace("%" + s + "%", build_reg(datatypes[dt], isa,lmul=lmul))
		elif item_type == "m":
			dt_info = re.findall(r'\<(.*)\>', s)[0]
			dt_info_params = dt_info.split(",")
			dt = ""
			if len(dt_info_params) == 1:
				dt = build_dt(dt_info_params[0], isa, dt_par, dt_ret)
			if dt not in isa["datatypes"]:
				print("Panic: '" + dt + "' is not available.")
				exit(-1)
			converted_ir = converted_ir.replace("%" + s + "%", build_msk(datatypes[dt], isa,lmul=lmul))
		elif item_type == "v":
			dt_info = re.findall(r'\<(.*)\>', s)[0]
			dt_info_params = dt_info.split(",")
			dt = ""
			if len(dt_info_params) == 1:
				dt = build_dt(dt_info_params[0], isa, dt_par, dt_ret)
			if dt not in isa["datatypes"]:
				print("Panic: '" + dt + "' is not available.")
				exit(-1)
			converted_ir = converted_ir.replace("%" + s + "%", build_val(datatypes[dt], isa,lmul=lmul))
		elif item_type == "N":
			dt_info = re.findall(r'\<(.*)\>', s)[0]
			dt_info_params = dt_info.split(",")
			dt = ""
			if len(dt_info_params) == 1:
				dt = build_dt(dt_info_params[0], isa, dt_par, dt_ret)
			if dt not in isa["datatypes"]:
				print("Panic: '" + dt + "' is not available.")
				exit(-1)
			converted_ir = converted_ir.replace("%" + s + "%", build_N(datatypes[dt], isa,lmul=lmul))
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
				f_full_name = build_func_name_short(isa, dt, f_name,lmul=lmul);
			elif len(dt_info_params) == 2:
				dt_1 = build_dt(dt_info_params[0], isa, dt_par, dt_ret)
				dt_2 = build_dt(dt_info_params[1], isa, dt_par, dt_ret)
				fdt_key = dt_1 + "," + dt_2
				f_full_name = build_func_name(isa, dt_1, dt_2, f_name,lmul=lmul);
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


# ----------------------------------------------------------------------------------------------------------------------
# Masked stuff
# ----------------------------------------------------------------------------------------------------------------------

"""
Parallel to 
	funcs[f]["implem_status"][dt_key] = [
		{
			"if" : "some condition",
			"requirements" : {"some_requirements" : "some values"},
		},
	]
we have
	funcs[f]["implem_status_masked"][dt_key][mask_kind] = [
		{
			"if" : "some condition",
			"requirements" : {"some_requirements" : "some values"},
		},
	]
Where mask_kind is "mask", "maskz" or "masks". 

What's cool about it is that it doesn't break anything for non masked algos 
but still looks same-ish.
"""

#TODO


# Masks in mipp_funcs and in implems are not defined the same way.
# This might be bad idk.

# ff is an entry in implems
def is_masked_implem(ff):
		return "version" in ff and ff["version"]

def mask_kind_from_ff(ff):
	# Expected: "mask", "maskz", "masks"
	return ff["version"]

def is_supported_mask_kind(mask_support, mask_kind):
	"""
	mask_support is an entry in mipp_funcs[f]["mask_support"] 
	and mask_kind is "mask", "maskz" or "masks".
 	"""
	if mask_support is None:
		return False
	if mask_kind == "mask":
		return mask_support.is_maskable()
	if mask_kind == "maskz":
		return mask_support.is_maskzable()
	if mask_kind == "masks":
		return mask_support.is_masksable()
	return False


#initialize the bucket for masked status if it does not exist yet
def ensure_masked_status_bucket(funcs, f, dt_key, mask_kind):
	"""
	implem_status_masked is similar to implem 
	status. But has one more level of dict. 
	which corresponds to the kind of mask (mask, maskz or masks).
	The entries in funcs[f][implem_status_masked][dt_key][mask_kind] are 
	"if" and "requirements" just like in implem_status.
	
	This functions initializes implem_status_masked for a 
	given function + dt_key + mask_kind if it does not exist yet.
	"""
	if "implem_status_masked" not in funcs[f]:
		funcs[f]["implem_status_masked"] = {}
	if dt_key not in funcs[f]["implem_status_masked"]:
		funcs[f]["implem_status_masked"][dt_key] = {}
	if mask_kind not in funcs[f]["implem_status_masked"][dt_key]:
		funcs[f]["implem_status_masked"][dt_key][mask_kind] = []


def _get_masked_bucket_create(funcs, func_name, dt_key, mask_kind):
	"""
	getter for funcs[f][implem_status_masked][dt_key][mask_kind] 
	that initializes the bucket if it does not exist yet.
	"""
	ensure_masked_status_bucket(funcs, func_name, dt_key, mask_kind)
	return funcs[func_name]["implem_status_masked"][dt_key][mask_kind]


def _get_masked_bucket_nocreate(funcs, func_name, dt_key, mask_kind):
	"""
	getter for funcs[f][implem_status_masked][dt_key][mask_kind]
 	that returns None if the bucket does not exist.
 	"""
	if "implem_status_masked" in funcs[func_name]:
		if dt_key in funcs[func_name]["implem_status_masked"]:
			if mask_kind in funcs[func_name]["implem_status_masked"][dt_key]:
				return funcs[func_name]["implem_status_masked"][dt_key][mask_kind]
	return None

def get_masked_bucket(funcs, func_name, dt_key, mask_kind, create_missing_bucket=False):
	"""
	getter for the bucket of masked implem status for a given func_name + dt_key + mask_kind.
	If create_missing_bucket is False, returns None if the bucket does not exist.
	If create_missing_bucket is True, creates the bucket if it does not exist and returns it.
 	"""
	if create_missing_bucket:
		return _get_masked_bucket_create(funcs, func_name, dt_key, mask_kind)
	else:
		return _get_masked_bucket_nocreate(funcs, func_name, dt_key, mask_kind)


def build_ifdef_rec_masked(funcs, func_name, dt_key, mask_kind):
	# Same algorithm as build_ifdef_rec, but reading from implem_status_masked and
	# recursing on the same mask_kind.
	str_ifdef = ""
	bucket = get_masked_bucket(funcs, func_name, dt_key, mask_kind)
	if bucket is not None:
		is_first_or = True
		str_ifdef_sub = ""
		str_end_sub_token = ""
		for implem in bucket:
			if not is_first_or:
				str_ifdef_sub = "( " + str_ifdef_sub + " || "
				str_end_sub_token = " )"
			is_first_and = True
			str_ifdef_sub_sub = ""
			for f_name in implem["requirements"]:
				for fdt_key in implem["requirements"][f_name]:
					ret = build_ifdef_rec(funcs, f_name, fdt_key)
					if ret:
						if not is_first_and:
							str_ifdef_sub_sub = str_ifdef_sub_sub + " && "
						str_ifdef_sub_sub = str_ifdef_sub_sub + ret
						is_first_and = False

			if implem["if"] and str_ifdef_sub_sub:
				str_ifdef_sub = str_ifdef_sub + implem["if"] + str_end_sub_token + " && " + str_ifdef_sub_sub
			if implem["if"] and not str_ifdef_sub_sub:
				str_ifdef_sub = str_ifdef_sub + implem["if"] + str_end_sub_token
			if str_ifdef_sub_sub and not implem["if"]:
				str_ifdef_sub = str_ifdef_sub + str_ifdef_sub_sub + str_end_sub_token

			if implem["if"] or str_ifdef_sub_sub:
				is_first_or = False

		if str_ifdef_sub:
			str_ifdef = str_ifdef_sub
	return str_ifdef


def is_ifdef_masked(funcs, func_name, dt_key, mask_kind):
	ifdef = build_ifdef_rec_masked(funcs, func_name, dt_key, mask_kind)
	if ifdef:
		return True
	else:
		return False


def is_fully_missing_masked_func(funcs, func_name, dt_key, mask_kind):
	bucket = get_masked_bucket(funcs, func_name, dt_key, mask_kind)
	if bucket is None:
		return True
	return len(bucket) == 0


def is_missing_masked_func(funcs, func_name, dt_key, mask_kind):
	return is_fully_missing_masked_func(funcs, func_name, dt_key, mask_kind) or is_ifdef_masked(funcs, func_name, dt_key, mask_kind)


def build_ifdef_masked(funcs, func_name, dt_key, mask_kind, implem_id):
	# Masked counterpart of build_ifdef() that uses same-mask-kind requirements recursion.
	str_ifdef = ""
	bucket = get_masked_bucket(funcs, func_name, dt_key, mask_kind, create_missing_bucket=True)

	if "if" in bucket[implem_id]:
		str_ifdef = str_ifdef + bucket[implem_id]["if"]

	is_first_and = True
	str_ifdef_and = ""
	for f in bucket[implem_id]["requirements"]:
		for fdt in bucket[implem_id]["requirements"][f]:
			ret = build_ifdef_rec_masked(funcs, f, fdt, mask_kind)
			if ret:
				if not is_first_and:
					str_ifdef_and = str_ifdef_and + " && "
				str_ifdef_and = str_ifdef_and + ret
				is_first_and = False

	if str_ifdef and str_ifdef_and:
		str_ifdef = str_ifdef + " && " + str_ifdef_and
	if str_ifdef_and and not str_ifdef:
		str_ifdef = str_ifdef_and

	return str_ifdef