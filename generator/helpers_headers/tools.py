"""
Tools Module
Provides core SIMD datatypes definitions, category registries, and dynamic
configuration loader functions (`load_isa_config`, `load_implem_tables`).
"""
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

DATATYPES_MAP = {
    "all_float": all_float,
    "all_int": all_int,
    "all_uint": all_uint,
    "all_int_uint": all_int_uint,
    "all_defs": all_defs,
    "all_datatypes": all_datatypes,
    "all_64bit": all_64bit,
    "all_32bit": all_32bit,
    "all_16bit": all_16bit,
    "all_8bit": all_8bit,
    "all_datatypes_cart_prod": all_datatypes_cart_prod,
    "all_datatypes_cart_prod_except_f64": all_datatypes_cart_prod_except_f64,
    "all_datatypes_cart_prod_inc_f64": all_datatypes_cart_prod_inc_f64,
    "all_datatypes_idx_pair": all_datatypes_idx_pair,
    "all_datatypes_same_size": all_datatypes_same_size,
    "all_datatypes_widenning": all_datatypes_widenning,
    "float64": [float64],
    "float32": [float32],
    "int64": [int64],
    "int32": [int32],
    "int16": [int16],
    "int8": [int8],
    "uint64": [uint64],
    "uint32": [uint32],
    "uint16": [uint16],
    "uint8": [uint8],
}

def resolve_datatypes(spec):
    if isinstance(spec, str):
        spec = [spec]
    resolved = []
    for s in spec:
        if s in DATATYPES_MAP:
            resolved.extend(DATATYPES_MAP[s])
        else:
            import tools
            if hasattr(tools, s):
                val = getattr(tools, s)
                if isinstance(val, list):
                    resolved.extend(val)
                else:
                    resolved.append(val)
            else:
                resolved.append(s)
    return resolved

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

from name_builder import *
from name_builder import _build_func_name, _get_dt_par_size, _build_call_lmul

GLOBAL_MEMO_IFDEF = {}

def build_ifdef_rec(funcs, func_name, dt_key, memo=None):
    if memo is None:
        memo = GLOBAL_MEMO_IFDEF
    memo_key = (func_name, dt_key)
    if memo_key in memo:
        return memo[memo_key]
        
    str_ifdef = ""
    if "implem_status" in funcs[func_name]:
        if dt_key in funcs[func_name]["implem_status"]:
            is_first_or = True
            str_ifdef_sub = ""
            str_end_sub_token = ""
            for implem in funcs[func_name]["implem_status"][dt_key]:
                is_first_and = True
                str_ifdef_sub_sub = ""
                for f_name in implem["requirements"]:
                    for fdt_key in implem["requirements"][f_name]:
                        ret = build_ifdef_rec(funcs, f_name, fdt_key, memo)
                        if ret:
                            if not is_first_and:
                                str_ifdef_sub_sub = str_ifdef_sub_sub + " && "
                            str_ifdef_sub_sub = str_ifdef_sub_sub + ret
                            is_first_and = False

                if not implem["if"] and not str_ifdef_sub_sub:
                    str_ifdef_sub = ""
                    break

                if not is_first_or:
                    str_ifdef_sub = "( " + str_ifdef_sub + " || "
                    str_end_sub_token = " )"

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
                
    # Basic deduplication to avoid exponential growth string
    if " && " in str_ifdef and "||" not in str_ifdef and "(" not in str_ifdef:
        parts = [p.strip() for p in str_ifdef.split(" && ")]
        dedup_parts = list(dict.fromkeys(parts))
        str_ifdef = " && ".join(dedup_parts)
                
    memo[memo_key] = str_ifdef
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


GLOBAL_MEMO_IFDEF_MASKED = {}

def build_ifdef_rec_masked(funcs, func_name, dt_key, mask_kind, memo=None):
    if memo is None:
        memo = GLOBAL_MEMO_IFDEF_MASKED
    memo_key = (func_name, dt_key, mask_kind)
    if memo_key in memo:
        return memo[memo_key]
        
    # Same algorithm as build_ifdef_rec, but reading from implem_status_masked and
    # recursing on the same mask_kind.
    str_ifdef = ""
    bucket = get_masked_bucket(funcs, func_name, dt_key, mask_kind)
    if bucket is not None:
        is_first_or = True
        str_ifdef_sub = ""
        str_end_sub_token = ""
        for implem in bucket:
            is_first_and = True
            str_ifdef_sub_sub = ""
            for f_name in implem["requirements"]:
                for fdt_key in implem["requirements"][f_name]:
                    ret = build_ifdef_rec(funcs, f_name, fdt_key, memo)
                    if ret:
                        if not is_first_and:
                            str_ifdef_sub_sub = str_ifdef_sub_sub + " && "
                        str_ifdef_sub_sub = str_ifdef_sub_sub + ret
                        is_first_and = False

            if not implem["if"] and not str_ifdef_sub_sub:
                str_ifdef_sub = ""
                break

            if not is_first_or:
                str_ifdef_sub = "( " + str_ifdef_sub + " || "
                str_end_sub_token = " )"

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
            
    # Basic deduplication to avoid exponential growth string
    if " && " in str_ifdef and "||" not in str_ifdef and "(" not in str_ifdef:
        parts = [p.strip() for p in str_ifdef.split(" && ")]
        dedup_parts = list(dict.fromkeys(parts))
        str_ifdef = " && ".join(dedup_parts)
                
    memo[memo_key] = str_ifdef
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

from cond_utils import *
from cond_utils import _is_guard_dead_under_cond

GLOBAL_ISA_REGISTRY = {}
_isa_config_cache = {}

def clear_memo_caches():
    GLOBAL_MEMO_IFDEF.clear()
    GLOBAL_MEMO_IFDEF_MASKED.clear()
    _isa_config_cache.clear()



def compute_dt_par_dt_ret(funcs, f, dt, check_support=True):
    if len(dt.split(',')) <= 1:
        dt_par = dt.split(',')[0]
        dt_ret = dt.split(',')[0]
        if check_support and funcs and f and dt_par not in funcs[f]["datatypes"]:
            print("Panic: unsupported type for '" + f + "<" + dt_par + "," + dt_par + ">' function.")
            exit(-1)
    else:
        dt_par = dt.split(',')[0]
        dt_ret = dt.split(',')[1]
        dtk = dt_par + "," + dt_ret
        if check_support and funcs and f and dtk not in funcs[f]["datatypes"]:
            print("Panic: unsupported type for '" + f + "<" + dt_par + "," + dt_ret + ">' function.")
            exit(-1)
    return dt_par, dt_ret



def load_implem_tables(current_file, templates_filename, implems_filename):
    import json
    import os
    current_dir = os.path.dirname(os.path.abspath(current_file))
    
    # Load templates
    with open(os.path.join(current_dir, templates_filename), "r") as f:
        tpl_dict = json.load(f)
    for name, tpl in tpl_dict.items():
        if "code" in tpl:
            code = tpl["code"]
            fmt = tpl.get("format", "short")
            if isinstance(code, str):
                lines = code.split("\n")
            else:
                lines = code
                
            processed_lines = []
            for i, line in enumerate(lines):
                if line == "":
                    processed_lines.append("")
                else:
                    if fmt == "long":
                        processed_lines.append("\t" + line)
                    else:
                        if i > 0:
                            processed_lines.append("\t" + line)
                        else:
                            processed_lines.append(line)
            tpl["code"] = "\n".join(processed_lines)
        
    # Load implems
    with open(os.path.join(current_dir, implems_filename), "r") as f:
        raw_implems = json.load(f)
        
    resolved_implems = {}
    for func, choices in raw_implems.items():
        resolved_choices = []
        for choice in choices:
            resolved_choice = {}
            for k, v in choice.items():
                if k in ("datatypes", "mask_variants"):
                    resolved_choice[k] = resolve_datatypes(v)
                elif k == "template":
                    # Retrieve the template dict from tpl_dict
                    resolved_choice[k] = tpl_dict[v]
                else:
                    resolved_choice[k] = v
            resolved_choices.append(resolved_choice)
        resolved_implems[func] = resolved_choices
        
    return tpl_dict, resolved_implems


def load_isa_config(isa_name):
    import copy
    if isa_name not in _isa_config_cache:
        import json
        import os
        base_dir = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
        ext_dir = os.path.join(base_dir, "simd_ext", isa_name)
        
        # Load capability JSON
        with open(os.path.join(ext_dir, f"isa_{isa_name}.json"), "r") as f:
            isa = json.load(f)
        if "size" in isa and isinstance(isa["size"], list):
            isa["size"] = set(isa["size"]) # SVE backwards compatibility
            
        # Load native and emulation tables
        _, implems = load_implem_tables(os.path.join(ext_dir, "__init__.py"), f"templates_{isa_name}.json", f"implems_{isa_name}.json")
        _, implems_emu = load_implem_tables(os.path.join(ext_dir, "__init__.py"), f"templates_emu_{isa_name}.json", f"implems_emu_{isa_name}.json")
        
        _isa_config_cache[isa_name] = (isa, implems, implems_emu)
        
    isa, implems, implems_emu = _isa_config_cache[isa_name]
    return copy.deepcopy(isa), copy.deepcopy(implems), copy.deepcopy(implems_emu)