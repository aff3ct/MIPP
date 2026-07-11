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

all_categories = [cfloat, cint, cuint]

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
all_defs = []

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


# First definition of gather will use this 4 simplicity's sake
all_datatypes_idx_pair = []
for type in [cfloat, cint, cuint]:
    for n_bits in [64, 32, 16, 8]:
        if type == cfloat and n_bits in [16, 8]:
            continue
        dt = type + str(n_bits)
        idx = cuint + str(n_bits)
        all_datatypes_idx_pair.append(dt + "," + dt)

avx_datatypes_idx_pair = [
"float64,float64",
"float32,float32",
"int64,int64",
"int32,int32",
]


same_dt = [
    "float64,float64",
    "float32,float32",
    "int64,int64",
    "int32,int32",
    "uint64,uint64",
    "uint32,uint32",
    "int16,int16",
    "int8,int8",
    "uint16,uint16",
    "uint8,uint8",
]

f2i_dt = [ "float64,int64", "float32,int32" ]
f2u_dt = [ "float64,uint64", "float32,uint32" ]

i2f_dt = [ "int64,float64", "int32,float32"]
i2u_dt = [ "int64,uint64", "int32,uint32", "int16,uint16", "int8,uint8" ]

u2f_dt = [ "uint64,float64", "uint32,float32"]
u2i_dt = [ "uint64,int64", "uint32,int32", "uint16,int16", "uint8,int8" ]

all_datatypes_same_size = same_dt + f2i_dt + f2u_dt + i2f_dt + i2u_dt + u2f_dt + u2i_dt

int_dt_widenning = [ "int32,int64", "int16,int32", "int8,int16" ]
float_dt_widenning = [ "float32,float64" ]
uint_dt_widenning = [ "uint32,uint64", "uint16,uint32", "uint8,uint16" ]

all_datatypes_widenning = int_dt_widenning + float_dt_widenning + uint_dt_widenning
            
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

def _lmul_to_str(lmul):
    if lmul == 0 :
        return ""
    elif lmul >= 1 :
        return "_m" + str(int(lmul))
    elif lmul < 1 and lmul > 0 :
        return "_d" + str(int(1/lmul))
    elif lmul < 0 :
        return "_d" + str(int(-1*lmul))
    else:
        return ""

def build_reg(datatype, isa, lmul=0, isa_name=True, cpp=False):
    if cpp:
        str_reg = "rvd"

        str_reg += "<" + datatype["cstd"]
        if lmul:
            str_reg += "," + str(int(lmul))
        if isa_name:
            str_reg += "," + isa["name"].upper()
        else:
            str_reg += ",DEFAULT_ISA"
        str_reg += ">"
        return str_reg
    else:
        str_reg = "rvd_"
        if isa_name:
            str_reg += isa["name"] + "_"
        #print("Debug", datatype["category"], datatype["n_bits"])
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

        str_msk += "<" + datatype["cstd"]
        if lmul:
            str_msk += "," + str(int(lmul))
        if isa_name:
            str_msk += "," + isa["name"].upper()
        else:
            str_msk += ",DEFAULT_ISA"
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
        str_N += _lmul_to_str(lmul).upper()
    return str_N

def build_type(type, datatype, isa,lmul=0, isa_name=True, cpp=False):
    if type:

        # print("Debug build type " ,type)

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
        else : 
            print("error: type should be reg, msk, val, ptr, Nele or vindex")
            exit(-1)
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
def build_proto_set0(dt_ret, isa, func_name, lmul=0, isa_name=True, cpp=False, masked_version=False):
    isa_type = "DEFAULT_ISA"
    if isa_name:
        isa_type = isa["name"].upper()
    template = f"<{dt_ret}_t, {lmul}, {isa_type}>"
    if func_name == "set0":
        reg_type = "rvd"
    elif func_name == "set0_k":
        reg_type = "rvm"
    else:
        reg_type = "rvd"

    # masked template form (no template<>)
    if masked_version:
        if masked_version == "mask":
            template = f"<M, {dt_ret}_t, {lmul}, {isa_type}>"
        elif masked_version == "maskz":
            template = f"<Z, {dt_ret}_t, {lmul}, {isa_type}>"
        elif masked_version == "masks":
            template = f"<S, {dt_ret}_t, {lmul}, {isa_type}>"
        else:
            print("error: masked_version should be mask, maskz or masks")
            exit(-1)

        # set0 has no other args, but masked forms still take m0 (and maybe rsrc)
        if masked_version in ("mask", "maskz"):
            return f"inline {reg_type}<{dt_ret}_t, {lmul}, {isa_type}> {func_name}{template}(const rvm<{dt_ret}_t,{lmul}, {isa_type}> m0"
        elif masked_version == "masks":
            return f"inline {reg_type}<{dt_ret}_t, {lmul}, {isa_type}> {func_name}{template}(const rvm<{dt_ret}_t,{lmul}, {isa_type}> m0, const {reg_type}<{dt_ret}_t,{lmul}, {isa_type}> rsrc"

    # unmasked (unchanged)
    return f"template <>\ninline {reg_type}<{dt_ret}_t, {lmul}, {isa_type}> {func_name}{template}("


# Build prototype of set
def build_proto_set(dt_ret, isa, func_name, lmul=0, isa_name=True, cpp=False, masked_version=False):
    isa_type = "DEFAULT_ISA"
    if isa_name:
        isa_type = isa["name"].upper()
    lmul_str = _lmul_to_str(lmul)
    dt_par = None
    template = f"<{dt_ret}_t, {lmul}, {isa_type}>"
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
            template = f"<M, {dt_ret}_t, {lmul}, {isa_type}>"
        elif masked_version == "maskz":
            template = f"<Z, {dt_ret}_t, {lmul}, {isa_type}>"
        elif masked_version == "masks":
            template = f"<S, {dt_ret}_t, {lmul}, {isa_type}>"
        else:
            print("error: masked_version should be mask, maskz or masks")
            exit(-1)


        if masked_version in ("mask", "maskz"):
            return (
                f"inline {reg_type}<{dt_ret}_t, {lmul}, {isa_type}> {func_name}{template}("
                f"const rvm<{dt_par},{lmul}, {isa_type}> m0, "
                f"const {dt_par} vals[N<{dt_ret}_t, {lmul}, {isa_type}>()]"
            )
        elif masked_version == "masks":
            return (
                f"inline {reg_type}<{dt_ret}_t, {lmul}, {isa_type}> {func_name}{template}("
                f"const rvm<{dt_par},{lmul}, {isa_type}> m0, "
                f"const rvd<{dt_par},{lmul}, {isa_type}> rsrc, "
                f"const {dt_par} vals[N<{dt_ret}_t, {lmul}, {isa_type}>()]"
            )

    # unmasked (unchanged)
    return f"template <>\ninline {reg_type}<{dt_ret}_t, {lmul}, {isa_type}> {func_name}{template}(const {dt_par} vals[N<{dt_ret}_t, {lmul}, {isa_type}>()]"


def build_proto_set1(dt_ret, isa, func_name, lmul=0, isa_name=True, cpp=False, masked_version=False):
    isa_type = "DEFAULT_ISA"
    if isa_name:
        isa_type = isa["name"].upper()
    lmul_str = _lmul_to_str(lmul)
    template = f"<{dt_ret}_t, {lmul}, {isa_type}>"
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
            template = f"<M, {dt_ret}_t, {lmul}, {isa_type}>"
        elif masked_version == "maskz":
            template = f"<Z, {dt_ret}_t, {lmul}, {isa_type}>"
        elif masked_version == "masks":
            template = f"<S, {dt_ret}_t, {lmul}, {isa_type}>"
        else:
            print("error: masked_version should be mask, maskz or masks")
            exit(-1)

        if masked_version in ("mask", "maskz"):
            return (
                f"inline {reg_type}<{dt_ret}_t, {lmul}, {isa_type}> {func_name}{template}("
                f"const rvm<{dt_par},{lmul}, {isa_type}> m0, "
                f"const {dt_par} v0"
            )
        elif masked_version == "masks":
            return (
                f"inline {reg_type}<{dt_ret}_t, {lmul}, {isa_type}> {func_name}{template}("
                f"const rvm<{dt_par},{lmul}, {isa_type}> m0, "
                f"const rvd<{dt_par},{lmul}, {isa_type}> rsrc, "
                f"const {dt_par} v0"
            )

    # unmasked (unchanged)
    return f"template <>\ninline {reg_type}<{dt_ret}_t, {lmul}, {isa_type}> {func_name}{template}(const {dt_par} v0"

def build_proto_load(dt_ret, isa, func_name, lmul=0, isa_name=True, cpp=False, masked_version=False):
    isa_type = "DEFAULT_ISA"
    if isa_name:
        isa_type = isa["name"].upper()
    if func_name == "load" or func_name == "loadu":
        dt_par = f"{dt_ret}_t"
        template = f"<{dt_ret}_t, {lmul}, {isa_type}>"
        if masked_version:
            if masked_version == "mask" :
                template = f"<M, {dt_ret}_t, {lmul}, {isa_type}>"
            elif masked_version == "maskz" :
                template = f"<Z, {dt_ret}_t, {lmul}, {isa_type}>"
            elif masked_version == "masks" :
                template = f"<S, {dt_ret}_t, {lmul}, {isa_type}>"
            else :
                print("error: masked_version should be mask, maskz or masks")
                exit(-1)
        reg_type = "rvd"
  
    if masked_version:
        if masked_version == "mask" :
            ret = f"inline {reg_type}<{dt_ret}_t, {lmul}, {isa_type}> {func_name}{template}(const rvm<{dt_par},{lmul}, {isa_type}> m0, const {dt_par}* p0"
        elif masked_version == "maskz" :
            ret = f"inline {reg_type}<{dt_ret}_t, {lmul}, {isa_type}> {func_name}{template}(const rvm<{dt_par},{lmul}, {isa_type}> m0, const {dt_par}* p0"
        elif masked_version == "masks" :
            ret = f"inline {reg_type}<{dt_ret}_t, {lmul}, {isa_type}> {func_name}{template}(const rvm<{dt_par},{lmul}, {isa_type}> m0, const rvd<{dt_par},{lmul}, {isa_type}> rsrc, const {dt_par}* p0"
        else : 
            print("error: masked_version should be mask, maskz or masks")
            exit(-1)
    else :
        ret = f"template <>\ninline {reg_type}<{dt_ret}_t, {lmul}, {isa_type}> {func_name}{template}(const {dt_par}* p0"
    return  ret

def build_proto_gather(dt_par, dt_ret, isa, func_name, lmul=1, isa_name=False, cpp=False, masked_version=False):
    isa_type = "DEFAULT_ISA"
    msk_dt = datatypes["uint" + str(_get_dt_par_size(dt_par))]["name"]+ "_t"
    if isa_name:
        isa_type = isa["name"].upper()
    template = f"<{dt_ret}_t, {dt_par}_t, {lmul}, {isa_type}>"
    if masked_version:
        if masked_version == "mask" :
            template = f"<M, {dt_ret}_t, {msk_dt}, {lmul}, {isa_type}>"
        elif masked_version == "maskz" :
            template = f"<Z, {dt_ret}_t, {msk_dt}, {lmul}, {isa_type}>"
        elif masked_version == "masks" :
            template = f"<S, {dt_ret}_t, {msk_dt}, {lmul}, {isa_type}>"
        else :
            print("error: masked_version should be mask, maskz or masks")
            exit(-1)
    reg_type = "rvd"
    if masked_version:
        if masked_version == "mask" :
            return f"inline {reg_type}<{dt_ret}_t, {lmul}, {isa_type}> {func_name}{template}(const rvm<{msk_dt},{lmul}, {isa_type}> m0, const {dt_par}_t* p0, const rvd<{msk_dt},{lmul}, {isa_type}> r0"
        elif masked_version == "maskz" :
            return f"inline {reg_type}<{dt_ret}_t, {lmul}, {isa_type}> {func_name}{template}(const rvm<{msk_dt},{lmul}, {isa_type}> m0, const {dt_par}_t* p0, const rvd<{msk_dt},{lmul}, {isa_type}> r0"
        elif masked_version == "masks" :
            return f"inline {reg_type}<{dt_ret}_t, {lmul}, {isa_type}> {func_name}{template}(const rvm<{msk_dt},{lmul}, {isa_type}> m0, const rvd<{dt_par}_t,{lmul}, {isa_type}> rsrc, const {dt_par}_t* p0, const rvd<{msk_dt},{lmul}, {isa_type}> r0"
        else : 
            print("error: masked_version should be mask, maskz or masks")
            exit(-1)
    else :
        print("error: Unmasked gather proto should be built by build_proto.")
        exit(-1)

def build_proto_scatter(dt_par, dt_ret, isa, func_name, lmul=1, isa_name=False, cpp=False, masked_version=False):
    isa_type = "DEFAULT_ISA"

    msk_dt = datatypes["uint" + str(_get_dt_par_size(dt_par))]["name"]+ "_t"
    if isa_name:
        isa_type = isa["name"].upper()
    template = f"<{dt_ret}_t, {msk_dt}, {lmul}, {isa_type}>"
    if masked_version:
        if masked_version == "mask" :
            template = f"<M, {dt_ret}_t, {msk_dt}, {lmul}, {isa_type}>"
        elif masked_version == "maskz" :
            template = f"<Z, {dt_ret}_t, {msk_dt}, {lmul}, {isa_type}>"
        elif masked_version == "masks" :
            template = f"<S, {dt_ret}_t, {msk_dt}, {lmul}, {isa_type}>"
        else :
            print("error: masked_version should be mask, maskz or masks")
            exit(-1)
    reg_type = "rvd"
    if masked_version:
        if masked_version == "mask" :
            return f"inline void {func_name}{template}(const rvm<{msk_dt},{lmul}, {isa_type}> m0, {dt_par}_t* p0, const rvd<{msk_dt},{lmul}, {isa_type}> r0, const rvd<{dt_ret}_t,{lmul}, {isa_type}> r1"
        elif masked_version == "maskz" :
            return f"inline void {func_name}{template}(const rvm<{msk_dt},{lmul}, {isa_type}> m0, {dt_par}_t* p0, const rvd<{msk_dt},{lmul}, {isa_type}> r0, const rvd<{dt_ret}_t,{lmul}, {isa_type}> r1"
        elif masked_version == "masks" :
            return f"inline void {func_name}{template}(const rvm<{msk_dt},{lmul}, {isa_type}> m0, const rvd<{msk_dt},{lmul}, {isa_type}> rsrc, const {dt_par}_t* p0, const rvd<{msk_dt},{lmul}, {isa_type}> r0, const rvd<{dt_ret}_t,{lmul}, {isa_type}> r1"
        else : 
            print("error: masked_version should be mask, maskz or masks")
            exit(-1)
    else :
        print("error: Unmasked scatter proto should be built by build_proto.")
        exit(-1)
#function message error set functions
def gen_set_func_error(func_name,file):
    if func_name == "set":
        print(f"template <typename T, int LMUL=1, ISA ISA_TYPE=DEFAULT_ISA> inline rvd<T, LMUL, ISA_TYPE> {func_name}(const T[N<T, LMUL, ISA_TYPE>()]);", file=file) #{{ std::cerr << \"{func_name} checkout tools.gen_set_func_error\" << std::endl; exit(-1);}}\n",file=file)
    if func_name == "set1":
        print(f"template <typename T, int LMUL=1, ISA ISA_TYPE=DEFAULT_ISA> inline rvd<T, LMUL, ISA_TYPE> {func_name}(const T);", file=file) #{{ std::cerr << \"{func_name} checkout tools.gen_set_func_error\" << std::endl; exit(-1);}}\n",file=file)
    if func_name == "set0":
        print(f"template <typename T, int LMUL=1, ISA ISA_TYPE=DEFAULT_ISA> inline rvd<T, LMUL, ISA_TYPE> {func_name}();", file=file) #{{ std::cerr << \"{func_name} checkout tools.gen_set_func_error\" << std::endl; exit(-1);}}\n",file=file)
    if func_name == "set_k":
        print(f"template <typename T, int LMUL=1, ISA ISA_TYPE=DEFAULT_ISA> inline rvm<T, LMUL, ISA_TYPE> {func_name}(const int32_t[N<T, LMUL, ISA_TYPE>()]);", file=file) #{{ std::cerr << \"{func_name} checkout tools.gen_set_func_error\" << std::endl; exit(-1);}}\n",file=file)
    if func_name == "set0_k":
        print(f"template <typename T, int LMUL=1, ISA ISA_TYPE=DEFAULT_ISA> inline rvm<T, LMUL, ISA_TYPE> {func_name}();", file=file) #{{ std::cerr << \"{func_name} checkout tools.gen_set_func_error\" << std::endl; exit(-1);}}\n",file=file)
    if func_name == "set1_k":
        print(f"template <typename T, int LMUL=1, ISA ISA_TYPE=DEFAULT_ISA> inline rvm<T, LMUL, ISA_TYPE> {func_name}(const int32_t v0);", file=file) #{{ std::cerr << \"{func_name} checkout tools.gen_set_func_error\" << std::endl; exit(-1);}}\n",file=file)
    if func_name == "load" or func_name == "loadu":
        print(f"template <typename T, int LMUL=1, ISA ISA_TYPE=DEFAULT_ISA> inline rvd<T, LMUL, ISA_TYPE> {func_name}(const T* p0);", file=file) #{{ std::cerr << \"{func_name} checkout tools.gen_set_func_error\" << std::endl; exit(-1);}}\n",file=file)


def _get_dt_par_size(dt_par):
    if dt_par in datatypes:
        return datatypes[dt_par]["n_bits"]
    else:
        print(f"error: data type {dt_par} not found in datatypes")
        exit(-1)

def build_proto(proto, dt_par, dt_ret, isa, func_name, lmul=0, isa_name=True, cpp=False, masked_version=False):
    """if lmul and (not cpp or (cpp and not lmul_specialized(proto))):
        func_name += "_m" + str(int(lmul))"""

    #build proto for set functions
    if func_name == "set0" or func_name =="set0_k":
        return  build_proto_set0(dt_ret, isa, func_name, lmul=lmul, isa_name=isa_name, cpp=cpp, masked_version=masked_version) +')'
    if func_name == "set" or func_name =="set_k":
        return  build_proto_set(dt_ret, isa, func_name, lmul=lmul, isa_name=isa_name, cpp=cpp, masked_version=masked_version) +')'
    if func_name =="set1_k" or func_name =="set1":
        return  build_proto_set1(dt_ret, isa, func_name, lmul=lmul, isa_name=isa_name, cpp=cpp, masked_version=masked_version) +')'
    if func_name =="load" or func_name =="loadu":
        return  build_proto_load(dt_ret, isa, func_name, lmul=lmul, isa_name=isa_name, cpp=cpp, masked_version=masked_version) +')'
    if "gather" in func_name and masked_version and cpp:
        return  build_proto_gather(dt_par, dt_ret, isa, func_name, lmul=lmul, isa_name=isa_name, cpp=cpp, masked_version=masked_version) +')'
    if "scatter" in func_name and masked_version and cpp:
        return  build_proto_scatter(dt_par, dt_ret, isa, func_name, lmul=lmul, isa_name=isa_name, cpp=cpp, masked_version=masked_version) +')'

    realdatatype = datatypes[dt_ret]
    if (proto["ret"]["fixeddatatype"]):
        realdatatype = datatypes[proto["ret"]["fixeddatatype"]]
    
    # if  "gather" in func_name or  "scatter" in func_name:
    #     dt_str = "uint" + str(_get_dt_par_size(dt_par))
    #     realdatatype = datatypes[dt_str]
    if not masked_version:
        lmul_str = ""
        if lmul > 0 and (not cpp ):
            lmul_str = "_m" + str(int(lmul))
        if lmul < 0 and (not cpp): # ldiv
            lmul_str = "_d" + str(int(-lmul))
        # if "gather" in func_name or "scatter" in func_name:
        #     print("Debug " + func_name + " proto: ", proto, build_type(proto["ret"]["type"], realdatatype, isa, lmul, isa_name, cpp), "cpp=", cpp, "realdatatype=", realdatatype)
        p = "inline " + build_type(proto["ret"]["type"], realdatatype, isa, lmul, isa_name, cpp) + " " + func_name + lmul_str + "("

    else : #we assume "mask" or "maskz" is passed in masked_version if it's not false.
        lmul_str = ""
        if lmul > 0 and (not cpp or (cpp and not lmul_specialized(proto))):
            lmul_str = "_m" + str(int(lmul))
        if lmul < 0 and (not cpp or (cpp and not lmul_specialized(proto))): # ldiv
            lmul_str = "_d" + str(int(-lmul))
        p = "inline " + build_type(proto["ret"]["type"], realdatatype, isa, lmul, isa_name, cpp) + " " + func_name + "_" + masked_version + lmul_str + "("
    cnt_reg = 0
    cnt_msk = 0
    cnt_val = 0
    cnt_ptr = 0
    is_first = True
    
    #add m0 as first argument for masked version of function
    if masked_version:
        # hack to account 4 gather / scatter 
        # The issue I'm noticing is that the generator doesn't 
        # acknowledge that different parameters can be of different types. 
        # Which is fine 4 most functions but not 4 gather/scatter ...
        msk_dt = datatypes[dt_par]
        if "gather" in func_name or "scatter" in func_name:
            msk_dt = datatypes["uint" + str(_get_dt_par_size(dt_par))]

        if masked_version == "mask" or masked_version == "maskz":
            p += build_msk(msk_dt, isa, lmul, isa_name, cpp) + " m0"
            
        elif masked_version == "masks" :
            p += "const " + build_msk(msk_dt, isa, lmul, isa_name, cpp) + " m0"
            p += ", " + build_reg(datatypes[dt_par], isa, lmul, isa_name, cpp) + " rsrc"
        cnt_msk = cnt_msk +1		
        is_first = False
        #print(p, "cpp=", cpp)

    for arg in proto["args"]:
        if not is_first:
            p += ", "
        realdatatype = datatypes[dt_par]
        if (arg["fixeddatatype"]):
            if arg["fixeddatatype"] not in datatypes and arg["fixeddatatype"] in all_categories:
                dt_str =  arg["fixeddatatype"] + str(_get_dt_par_size(dt_par))
                realdatatype = datatypes[dt_str]
            elif arg["fixeddatatype"] in datatypes:
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
            p += " vals["+build_N(datatypes[dt_par],isa,lmul,isa_name)+"]"
        elif arg["type"] == "vindex":
            p += " vi"
        is_first = False

    # if "gather" in func_name : 
    #     print("Debug gather proto: ", proto, build_type(proto["ret"]["type"], realdatatype, isa, lmul, isa_name, cpp), "cpp=", cpp, "realdatatype=", realdatatype)
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
            if "offset_lmul" not in arg or arg["offset_lmul"] == True:
                p += "p" + str(cnt_ptr) + " + " + str(int(part-1)) + "*MIPP_LMUL_STRIDE(sizeof(*p" + str(cnt_ptr) + "), " + str(int(lmul)) +")"
            elif "offset_lmul" in arg and arg["offset_lmul"] == False:
                p += "p" + str(cnt_ptr)
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
    if lmul > 0:
        lmul_str = "_m" + str(int(lmul))
    if lmul < 0 :
        lmul_str = "_d" + str(int(-lmul))

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
    if lmul > 0:
        lmul_str = "_m" + str(int(lmul))
    if lmul < 0 : 
        lmul_str = "_d" + str(int(-lmul))
    mask_str = ""
    if masked_version:
        mask_str = "_" + masked_version

  
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

def _parse_lmul_expression(expr, dt_par, dt_ret, isa, base_lmul):
    # print("debug: parsing lmul expression '" + expr + "' with base_lmul=" + str(base_lmul))
    # expression can be a simple 
    # tp or tr or a more complex one like tp*2 or tr/4
    # can also be a literal in 1,2,4,8 or 1/2, 1/4, 1/8
    if base_lmul == 0:
        base_lmul = 1 # default base_lmul is 1 if not specified, to allow expressions like tp*2 to work as expected
    if expr == "tp" or expr == "tr":
        return base_lmul
    elif expr in ["1", "2", "4", "8"]:
        return int(expr)
    elif expr in ["-2", "-4", "-8"]: # convert to number
        return str(-int(expr)) # we return the string of the positive number, as we want to have ldiv in the function name if it's a division by a power of 2
    else:
        #print("else case for lmul expression: " + expr)
        match = re.match(r'^(tp|tr)([*/])(\d+)$', expr)
        if match:				
            base = match.group(1)
            op = match.group(2)
            factor = int(match.group(3))
            start_lmul = None
            if base == "tp":
                # we don't have base_lmul in dt_par / dt_ret, so we assume it's the same as the one passed to build_dt
                start_lmul = base_lmul
            elif base == "tr":
                start_lmul = base_lmul
            else:
                print("Panic: unknown base '" + base + "' in base_lmul expression.")
                exit(-1)
            lmul_value = None
            if op == "*":
                lmul_value = int(base_lmul * factor)
            elif op == "/":
                lmul_value = int(base_lmul / factor)
            else:
                print("Panic: unknown operator '" + op + "' in base_lmul expression.")
                exit(-1)
            
            return lmul_value
        else:
            print("Panic: invalid base_lmul expression '" + expr + "'.")
            exit(-1)

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
    
def _parse_lmul(input_str, isa, dt_par, dt_ret, base_lmul):
    # input str is the same than in build dt. Just return 
    # the lmul suffix.

    dt_info_carac = input_str.split("|")
    if len(dt_info_carac) == 1 and dt_info_carac[0] == "tp":
        return base_lmul
    elif len(dt_info_carac) == 1 and dt_info_carac[0] == "tr":
        return base_lmul
    elif len(dt_info_carac) >= 1:
        dt_info_carac_dic = {}
        for dtic in dt_info_carac:
            dt_info_carac_dic[dtic.split(':')[0]] = dtic.split(':')[1]

        if "m" in dt_info_carac_dic:
            return _parse_lmul_expression(dt_info_carac_dic["m"], dt_par, dt_ret, isa, base_lmul)
        else :
            return base_lmul

def parse_placeholders(ir, isa, funcs, func_name, dt_par, dt_ret,lmul=0, isa_name=True):
    #print("debug: parsing placeholders in ir '" + ir + "' with dt_par='" + dt_par + "' and dt_ret='" + dt_ret + "' and lmul=" + str(lmul))
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
            converted_ir = converted_ir.replace("%" + s + "%", build_reg(datatypes[dt], isa,lmul=_parse_lmul(dt_info, isa, dt_par, dt_ret, lmul), isa_name=isa_name))
        elif item_type == "m":
            dt_info = re.findall(r'\<(.*)\>', s)[0]
            dt_info_params = dt_info.split(",")
            dt = ""
            if len(dt_info_params) == 1:
                dt = build_dt(dt_info_params[0], isa, dt_par, dt_ret)
            if dt not in isa["datatypes"]:
                print("Panic: '" + dt + "' is not available.")
                exit(-1)
            converted_ir = converted_ir.replace("%" + s + "%", build_msk(datatypes[dt], isa,lmul=_parse_lmul(dt_info, isa, dt_par, dt_ret, lmul), isa_name=isa_name))
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
            converted_ir = converted_ir.replace("%" + s + "%", build_N(datatypes[dt], isa,lmul=_parse_lmul(dt_info, isa, dt_par, dt_ret, lmul), isa_name=isa_name))
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
                f_full_name = build_func_name_short(isa, dt, f_name,lmul=_parse_lmul(dt_info, isa, dt_par, dt_ret, lmul), isa_name=isa_name)
            elif len(dt_info_params) == 2:
                dt_1 = build_dt(dt_info_params[0], isa, dt_par, dt_ret)
                dt_2 = build_dt(dt_info_params[1], isa, dt_par, dt_ret)
                fdt_key = dt_1 + "," + dt_2
                f_full_name = build_func_name(isa, dt_1, dt_2, f_name,lmul=_parse_lmul(dt_info, isa, dt_par, dt_ret, lmul), isa_name=isa_name)
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

def get_requirements(ir, isa, funcs, func_name, dt_par, dt_ret,lmul=0, isa_name=True):
    """
    get requirements for a given ir + func_name + dt_par + dt_ret.
    Same logic as parse_placeholders but we just build the requirements. We also 
    don't raise an exception if a required function is missing, we just add it to the requirements and let the caller handle it.
    """
    dt_key = dt_par + "," + dt_ret
    ar_substitute = re.findall(r'\%([^%]*)\%', ir)
    requirements = {}

    for s in ar_substitute:
        item_type = s.split('<')[0]

        if item_type not in ["r", "m", "v", "N"]:
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
            elif len(dt_info_params) == 2:
                dt_1 = build_dt(dt_info_params[0], isa, dt_par, dt_ret)
                dt_2 = build_dt(dt_info_params[1], isa, dt_par, dt_ret)
                fdt_key = dt_1 + "," + dt_2
            else:
                print("Panic: '" + f_name + "' has incompatible format.")
                exit(-1)

            if f_name not in funcs:
                print("Panic: '" + f_name + "' is not in the available MIPP functions.")
                exit(-1)

            if f_name not in requirements:
                requirements[f_name] = []
            if fdt_key not in requirements[f_name]:
                requirements[f_name].append(fdt_key)

    return requirements
    


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
    # if func_name == "store":
    #     print("debug: bucket for func '" + func_name + "' dt_key '" + dt_key + "' mask_kind '" + mask_kind + "' is: " + str(bucket))

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

# ---------------------------------------------------------------------------
# Preprocessor condition AST and simplification engine
# ---------------------------------------------------------------------------

class Expr:
    pass

class Term(Expr):
    def __init__(self, value):
        self.value = value.strip()
    def __repr__(self):
        return f"Term({self.value!r})"
    def to_str(self):
        return self.value
    def __eq__(self, other):
        return isinstance(other, Term) and self.value == other.value
    def __hash__(self):
        return hash(self.value)

class Not(Expr):
    def __init__(self, child):
        self.child = child
    def __repr__(self):
        return f"Not({self.child!r})"
    def to_str(self):
        if isinstance(self.child, Term):
            return f"!{self.child.to_str()}"
        return f"!( {self.child.to_str()} )"
    def __eq__(self, other):
        return isinstance(other, Not) and self.child == other.child
    def __hash__(self):
        return hash(("Not", self.child))

class And(Expr):
    def __init__(self, children):
        self.children = children
    def __repr__(self):
        return f"And({self.children!r})"
    def to_str(self):
        parts = []
        for c in self.children:
            s = c.to_str()
            if isinstance(c, (Or, And)):
                parts.append(f"({s})")
            else:
                parts.append(s)
        return " && ".join(parts)
    def __eq__(self, other):
        return isinstance(other, And) and set(self.children) == set(other.children)
    def __hash__(self):
        return hash(("And", tuple(sorted(self.children, key=lambda x: str(x)))))

class Or(Expr):
    def __init__(self, children):
        self.children = children
    def __repr__(self):
        return f"Or({self.children!r})"
    def to_str(self):
        parts = []
        for c in self.children:
            s = c.to_str()
            if isinstance(c, (Or, And)):
                parts.append(f"({s})")
            else:
                parts.append(s)
        return " || ".join(parts)
    def __eq__(self, other):
        return isinstance(other, Or) and set(self.children) == set(other.children)
    def __hash__(self):
        return hash(("Or", tuple(sorted(self.children, key=lambda x: str(x)))))

def tokenize(s):
    # Capture comparison sub-expressions (e.g. "__ARM_ARCH >= 8") as single atomic tokens,
    # then defined(...), boolean operators, parentheses, and identifiers.
    pattern = r"([a-zA-Z_][a-zA-Z0-9_]*\s*(?:>=|<=|==|!=|>|<)\s*[a-zA-Z0-9_]+|defined\s*\(\s*[a-zA-Z0-9_]+\s*\)|&&|\|\||!|\(|\)|[a-zA-Z0-9_]+)"
    tokens = []
    for m in re.finditer(pattern, s):
        tokens.append(m.group(1))
    return tokens

def parse(tokens):
    pos = 0

    def parse_or():
        nonlocal pos
        left = parse_and()
        while pos < len(tokens) and tokens[pos] == "||":
            pos += 1
            right = parse_and()
            if isinstance(left, Or):
                if isinstance(right, Or):
                    left = Or(left.children + right.children)
                else:
                    left = Or(left.children + [right])
            elif isinstance(right, Or):
                left = Or([left] + right.children)
            else:
                left = Or([left, right])
        return left

    def parse_and():
        nonlocal pos
        left = parse_not()
        while pos < len(tokens) and tokens[pos] == "&&":
            pos += 1
            right = parse_not()
            if isinstance(left, And):
                if isinstance(right, And):
                    left = And(left.children + right.children)
                else:
                    left = And(left.children + [right])
            elif isinstance(right, And):
                left = And([left] + right.children)
            else:
                left = And([left, right])
        return left

    def parse_not():
        nonlocal pos
        if pos < len(tokens) and tokens[pos] == "!":
            pos += 1
            child = parse_primary()
            return Not(child)
        return parse_primary()

    def parse_primary():
        nonlocal pos
        if pos >= len(tokens):
            return Term("")
        
        tok = tokens[pos]
        if tok == "(":
            pos += 1
            expr = parse_or()
            if pos < len(tokens) and tokens[pos] == ")":
                pos += 1
            return expr
        else:
            pos += 1
            return Term(tok)

    return parse_or()

def substitute_known_true(expr, known_true_exprs):
    """Replace any sub-expression that matches a known-true expression with Term("1").
    This handles both direct matches and matching of individual terms within Or/And."""
    if not known_true_exprs:
        return expr
    # Check if the whole expression matches any known-true expression
    for kt in known_true_exprs:
        if expr == kt:
            return Term("1")
    # For Or: if all children of a known-true Or appear in the current Or, the whole Or is true
    if isinstance(expr, Or):
        new_children = [substitute_known_true(c, known_true_exprs) for c in expr.children]
        result = Or(new_children)
        for kt in known_true_exprs:
            if result == kt:
                return Term("1")
        return result
    if isinstance(expr, And):
        new_children = [substitute_known_true(c, known_true_exprs) for c in expr.children]
        return And(new_children)
    if isinstance(expr, Not):
        new_child = substitute_known_true(expr.child, known_true_exprs)
        return Not(new_child)
    return expr

def simplify(expr):
    if isinstance(expr, Term):
        return expr
        
    if isinstance(expr, Not):
        child = simplify(expr.child)
        if isinstance(child, Not):
            return simplify(child.child)
        if child == Term("0"):
            return Term("1")
        if child == Term("1"):
            return Term("0")
        return Not(child)
        
    if isinstance(expr, And):
        new_children = []
        for c in expr.children:
            sc = simplify(c)
            if isinstance(sc, And):
                new_children.extend(sc.children)
            else:
                new_children.append(sc)
                
        unique_children = []
        seen = set()
        for c in new_children:
            if c not in seen:
                seen.add(c)
                unique_children.append(c)
                
        # Subsumption: !X && !(X && ...) -> !X
        # (because !X implies !(X && ...))
        to_remove = set()
        for i, c in enumerate(unique_children):
            if isinstance(c, Not) and not isinstance(c.child, (And, Or)):
                for j, c2 in enumerate(unique_children):
                    if i != j and j not in to_remove and isinstance(c2, Not) and isinstance(c2.child, And):
                        if c.child in c2.child.children:
                            to_remove.add(j)
        # Absorption (dual): X && (X || ...) -> X
        # (because X is more restrictive than X || ...)
        for i, c in enumerate(unique_children):
            if i not in to_remove:
                for j, c2 in enumerate(unique_children):
                    if i != j and j not in to_remove and isinstance(c2, Or):
                        if c in c2.children:
                            to_remove.add(j)
        if to_remove:
            unique_children = [c for i, c in enumerate(unique_children) if i not in to_remove]
            seen = set(unique_children)

        has_contradiction = False
        for c in unique_children:
            if isinstance(c, Not):
                if c.child in seen:
                    has_contradiction = True
                    break
                if isinstance(c.child, And) and all(child in seen for child in c.child.children):
                    has_contradiction = True
                    break
            else:
                if Not(c) in seen:
                    has_contradiction = True
                    break
                    
        if has_contradiction or any(c == Term("0") for c in unique_children):
            return Term("0")
            
        unique_children = [c for c in unique_children if c != Term("1")]
        if not unique_children:
            return Term("1")
            
        if len(unique_children) == 1:
            return unique_children[0]
            
        return And(unique_children)

    if isinstance(expr, Or):
        new_children = []
        for c in expr.children:
            sc = simplify(c)
            if isinstance(sc, Or):
                new_children.extend(sc.children)
            else:
                new_children.append(sc)
                
        unique_children = []
        seen = set()
        for c in new_children:
            if c not in seen:
                seen.add(c)
                unique_children.append(c)

        # Absorption: X || (X && ...) -> X
        # (because X is less restrictive than X && ...)
        to_remove = set()
        for i, c in enumerate(unique_children):
            for j, c2 in enumerate(unique_children):
                if i != j and j not in to_remove and isinstance(c2, And):
                    if c in c2.children:
                        to_remove.add(j)
        if to_remove:
            unique_children = [c for i, c in enumerate(unique_children) if i not in to_remove]

        # Complement resolution: !X || (X && Y && ...) -> !X || Y && ...
        # (because if X is false we're done, if X is true we need Y && ...)
        changed_compl = True
        while changed_compl:
            changed_compl = False
            for i, c in enumerate(unique_children):
                if isinstance(c, Not) and not isinstance(c.child, (And, Or)):
                    neg_term = c.child
                    for j, c2 in enumerate(unique_children):
                        if i != j and isinstance(c2, And) and neg_term in c2.children:
                            remaining = [ch for ch in c2.children if ch != neg_term]
                            if not remaining:
                                unique_children[j] = Term("1")
                            elif len(remaining) == 1:
                                unique_children[j] = remaining[0]
                            else:
                                unique_children[j] = And(remaining)
                            changed_compl = True
                            break
                if changed_compl:
                    break
            # Re-deduplicate after complement resolution
            if changed_compl:
                new_unique = []
                new_seen = set()
                for c in unique_children:
                    if c not in new_seen:
                        new_seen.add(c)
                        new_unique.append(c)
                unique_children = new_unique

        # Re-flatten any Or children introduced by complement resolution
        flat_children = []
        for c in unique_children:
            sc = simplify(c)
            if isinstance(sc, Or):
                flat_children.extend(sc.children)
            else:
                flat_children.append(sc)
        unique_children = []
        seen = set()
        for c in flat_children:
            if c not in seen:
                seen.add(c)
                unique_children.append(c)

        has_tautology = False
        for c in unique_children:
            if isinstance(c, Not):
                if c.child in seen:
                    has_tautology = True
                    break
                if isinstance(c.child, Or) and all(child in seen for child in c.child.children):
                    has_tautology = True
                    break
            else:
                if Not(c) in seen:
                    has_tautology = True
                    break
                    
        if has_tautology or any(c == Term("1") for c in unique_children):
            return Term("1")
            
        unique_children = [c for c in unique_children if c != Term("0")]
        if not unique_children:
            return Term("0")
            
        if len(unique_children) == 1:
            return unique_children[0]
            
        return Or(unique_children)

    return expr

def simplify_cond_str(s, known_true_conds=None):
    if not s or s.strip() == "":
        return ""
    tokens = tokenize(s)
    if not tokens:
        return s
    expr = parse(tokens)
    # Substitute known-true conditions before simplifying
    if known_true_conds:
        known_true_exprs = []
        for kt_str in known_true_conds:
            if kt_str and kt_str.strip():
                kt_tokens = tokenize(kt_str)
                if kt_tokens:
                    known_true_exprs.append(parse(kt_tokens))
        if known_true_exprs:
            expr = substitute_known_true(expr, known_true_exprs)
    simplified = simplify(expr)
    res = simplified.to_str()
    if res == "0":
        return "0"
    if res == "1":
        return ""
    return res