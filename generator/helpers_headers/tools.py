"""
Tools Module
Provides core SIMD datatypes definitions, category registries, and dynamic
configuration loader functions (`load_isa_config`, `load_implem_tables`).
"""
from jinja2 import Template, StrictUndefined
import json
import re

from datatypes import *

# ---------------------------------------------------------------------------
# Compiled regex patterns (module-level, avoid recompiling on each call)
# ---------------------------------------------------------------------------
_RE_PLACEHOLDER    = re.compile(r'\%([^%]*)\%')
_RE_ANGLE          = re.compile(r'<(.*)>')
_RE_LMUL_EXPR      = re.compile(r'^(tp|tr)([*/])(\d+)$')

# Keys of the type expressions of the templating DSL (`%r<c:int|b:32|m:2|v:Z>%`):
# category, bit width, LMUL and masking variant. `tp` and `tr` may also appear
# alone as a part (`%add<tp|m:2>%`).
_DT_MODIFIER_KEYS  = ("c", "b", "m", "v")
_DT_BARE_PARTS     = ("tp", "tr")

def _split_dt_modifier(part, input_str):
    """Split one part of a type expression into (key, value); panic on an unknown key."""
    part = part.strip()
    if ":" in part:
        key, val = part.split(':', 1)
        key, val = key.strip(), val.strip()
        if key in _DT_MODIFIER_KEYS:
            return key, val
    elif part in _DT_BARE_PARTS:
        return part, part
    print("Panic: invalid modifier '" + part + "' in '" + input_str + "' (expected tp, tr, c:, b:, m: or v:).")
    exit(-1)

            
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
    float64 : { "name" : float64, "category": cfloat, "n_bits" : 64, "cstd": "float64_t", "literal_suffix": "", },
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
    "all_datatypes_same_size_except_f64": all_datatypes_same_size_except_f64,
    "all_datatypes_same_size_inc_f64": all_datatypes_same_size_inc_f64,
    "all_datatypes_widenning": all_datatypes_widenning,
    "all_datatypes_narrowing": all_datatypes_narrowing,
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

_ldiv_mask_functions_cache = {}

def ldiv_mask_functions(isa):
    """
    Names of the functions given by `simd_ext/<isa>/<isa>_ldiv_mask.json` (the half-vector
    specific implementations of an ISA whose d2 is a full register of its own).
    """
    import json
    import os
    name = isa["name"]
    if name not in _ldiv_mask_functions_cache:
        path = os.path.join(os.path.dirname(os.path.dirname(os.path.abspath(__file__))), "simd_ext", name, name + "_ldiv_mask.json")
        names = set()
        if os.path.exists(path):
            with open(path, "r", encoding="utf-8") as fd:
                for key in json.load(fd):
                    names.update(key.split("|"))
        _ldiv_mask_functions_cache[name] = names
    return _ldiv_mask_functions_cache[name]

def isa_provides_lmul(isa, proto, lmul):
    """
    Whether `isa` provides a function with this prototype for the arguments' LMUL `lmul`.
    Always true for the functions that keep the LMUL. For the functions that change it (low, high,
    combine), only the representations that implement them: the scalar ISA, the software
    LMUL >= 2 registers (a struct of two halves) and, between m1 and d2, the ISAs with mask-based
    half-vectors that give them in their `<isa>_ldiv_mask.json` (low and high for m1 -> d2, combine
    for d2 -> m1).
    """
    if not changes_lmul(proto):
        return True
    if not is_defined_for_lmul(proto, lmul):
        return False
    if isa.get("is_scalar", False):
        return True
    hw = [int(x) for x in isa.get("hw_lmul", [1])]
    sw = [int(x) for x in isa.get("sw_lmul", [])]
    ret = resolve_ret_lmul(proto["ret"], lmul)
    if uses_hw_ldiv_templates(isa):
        # hardware register groups: one template per function (masks: `<f>_k`), whatever the LMUL
        if lmul not in hw or ret not in hw:
            return False
        if is_narrowing(proto):
            need = {"ncvt"}
        elif is_widening(proto):
            need = {"wcvt"}
        else:
            msk = "_k" if proto["ret"].get("type") == "msk" else ""
            need = {"low" + msk, "high" + msk} if proto["ret"].get("lmul") == "down" else {"combine" + msk}
        return need <= ldiv_mask_functions(isa)
    if is_narrowing(proto):
        # ncvt: m1 -> d2 is a template (generic_ldiv_mask.json, then the ISA), m2 -> m1 joins the
        # conversions of the two halves (combine), m4 -> m2... converts each half
        if lmul == 1:
            return uses_ldiv_templates(isa)
        if lmul not in sw or lmul in hw or lmul < 2:
            return False
        if lmul == 2:
            return uses_ldiv_templates(isa) and "combine" in ldiv_mask_functions(isa)
        return isa_provides_lmul(isa, proto, lmul // 2)
    if is_widening(proto):
        # wcvt: d2 -> m1 is a template (generic_ldiv_mask.json, then the ISA), m1 -> m2 is made of
        # low / high on the argument and of two d2 -> m1, m2 -> m4... of two m1 -> m2, etc.
        if lmul == -2:
            return uses_ldiv_templates(isa)
        if ret not in sw or ret in hw:
            return False
        if lmul == 1:
            return {"low", "high"} <= ldiv_mask_functions(isa) and uses_ldiv_templates(isa)
        return isa_provides_lmul(isa, proto, lmul // 2)
    if {lmul, ret} == {1, -2}:
        if not uses_ldiv_templates(isa):
            return False
        return ("low" if lmul == 1 else "combine") in ldiv_mask_functions(isa)
    big, small = max(lmul, ret), min(lmul, ret)
    # the larger register must be a software LMUL (a struct of two halves), the smaller one
    # a register (not a half-vector 'd2', provided by the representation of the ISA)
    return big >= 2 and big in sw and big not in hw and small >= 1

def lmul_to_str(lmul):
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
        match = _RE_LMUL_EXPR.match(expr)
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
            # a negative LMUL is a division (-2 is 'd2', half of m1): work on the ratio
            ratio = base_lmul if base_lmul > 0 else 1 / (-base_lmul)
            if op == "*":
                ratio = ratio * factor
            elif op == "/":
                ratio = ratio / factor
            else:
                print("Panic: unknown operator '" + op + "' in base_lmul expression.")
                exit(-1)
            if ratio >= 1:
                lmul_value = int(ratio)
            else:
                lmul_value = -int(round(1 / ratio))

            return lmul_value
        else:
            print("Panic: invalid base_lmul expression '" + expr + "'.")
            exit(-1)

def _extract_mask_from_dt_info(input_str):
    masked_ver = False
    # `input_str` may hold two type expressions (`tp, c:int|b:tp`)
    parts = [p for dt_expr in input_str.split(",") for p in dt_expr.split("|")]
    for part in parts:
        key, val = _split_dt_modifier(part, input_str)
        if key == "v":
            if val == "Z":
                masked_ver = "maskz"
            elif val == "M":
                masked_ver = "mask"
            elif val == "S":
                masked_ver = "masks"
            elif val == "U":
                masked_ver = False
            else:
                print("Panic: invalid variant 'v:" + val + "' in '" + input_str + "' (expected M, Z, S or U).")
                exit(-1)
    return masked_ver

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
            key, val = _split_dt_modifier(dtic, input_str)
            if key != "v":
                dt_info_carac_dic[key] = val

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
def _dump_dict_json(di, filename):
    # debug
    fj = open(filename, "w")
    json_object = json.dumps(di, indent = 4)
    print(json_object, file=fj)
    fj.close()
    
def _parse_lmul(input_str, isa, dt_par, dt_ret, base_lmul, ret_lmul=None):
    # `ret_lmul`: LMUL of the returned value, when it differs from `base_lmul` (low, high, combine):
    # a plain `tr` is the type of the result, with its own LMUL.
    if base_lmul == 0:
        return 0

    dt_info_carac = input_str.split("|")
    if len(dt_info_carac) == 1 and dt_info_carac[0] == "tp":
        return base_lmul
    elif len(dt_info_carac) == 1 and dt_info_carac[0] == "tr":
        return base_lmul if ret_lmul is None else ret_lmul
    elif len(dt_info_carac) >= 1:
        dt_info_carac_dic = {}
        for dtic in dt_info_carac:
            key, val = _split_dt_modifier(dtic, input_str)
            if key != "v":
                dt_info_carac_dic[key] = val

        if "m" in dt_info_carac_dic:
            return _parse_lmul_expression(dt_info_carac_dic["m"], dt_par, dt_ret, isa, base_lmul)
        else :
            return base_lmul

def parse_placeholders(ir, isa, funcs, func_name, dt_par, dt_ret,lmul=0, isa_name=True):
    #print("debug: parsing placeholders in ir '" + ir + "' with dt_par='" + dt_par + "' and dt_ret='" + dt_ret + "' and lmul=" + str(lmul))
    dt_key = dt_par + "," + dt_ret
    converted_ir = ir
    ar_substitute = _RE_PLACEHOLDER.findall(ir)
    requirements = {}
    ret_lmul = None
    if lmul and func_name in funcs and changes_lmul(funcs[func_name]["proto"]):
        ret_lmul = resolve_ret_lmul(funcs[func_name]["proto"]["ret"], lmul)

    for s in ar_substitute:
        item_type = s.split('<')[0]

        if item_type == "r":
            dt_info = _RE_ANGLE.findall(s)[0]
            # print("dt_info: " + dt_info)
            dt_info_params = dt_info.split(",")
            dt = ""
            if len(dt_info_params) == 1:
                dt = build_dt(dt_info_params[0], isa, dt_par, dt_ret)
            if dt not in isa["datatypes"]:
                print("Panic: '" + dt + "' is not available.")
                exit(-1)
            converted_ir = converted_ir.replace("%" + s + "%", build_reg(datatypes[dt], isa,lmul=_parse_lmul(dt_info, isa, dt_par, dt_ret, lmul, ret_lmul), isa_name=isa_name))
        elif item_type == "m":
            dt_info = _RE_ANGLE.findall(s)[0]
            dt_info_params = dt_info.split(",")
            dt = ""
            if len(dt_info_params) == 1:
                dt = build_dt(dt_info_params[0], isa, dt_par, dt_ret)
            if dt not in isa["datatypes"]:
                print("Panic: '" + dt + "' is not available.")
                exit(-1)

            converted_ir = converted_ir.replace("%" + s + "%", build_msk(datatypes[dt], isa,lmul=_parse_lmul(dt_info, isa, dt_par, dt_ret, lmul, ret_lmul), isa_name=isa_name))
        elif item_type == "s":
            dt_info = _RE_ANGLE.findall(s)[0]
            dt_info_params = dt_info.split(",")
            dt = ""
            if len(dt_info_params) == 1:
                dt = build_dt(dt_info_params[0], isa, dt_par, dt_ret)
            if dt not in isa["datatypes"]:
                print("Panic: '" + dt + "' is not available.")
                exit(-1)
            converted_ir = converted_ir.replace("%" + s + "%", build_val(datatypes[dt], isa,lmul=lmul))
        elif item_type == "N":
            dt_info = _RE_ANGLE.findall(s)[0]
            dt = ""
            dt_info_params = dt_info.split(",")
            if len(dt_info_params) == 1:
                dt = build_dt(dt_info_params[0], isa, dt_par, dt_ret)
            if dt not in isa["datatypes"]:
                print("Panic: '" + dt + "' is not available.")
                exit(-1)
            converted_ir = converted_ir.replace("%" + s + "%", build_N(datatypes[dt], isa,lmul=_parse_lmul(dt_info, isa, dt_par, dt_ret, lmul, ret_lmul), isa_name=isa_name))
        else:
            f_name = item_type
            if f_name not in funcs:
                print("Panic: '" + f_name + "' is not in the available MIPP functions.")
                exit(-1)

            fdt_key = ""
            dt_info = _RE_ANGLE.findall(s)[0]
            masked_ver = _extract_mask_from_dt_info(dt_info)
            dt_info_params = dt_info.split(",")
            if len(dt_info_params) == 1:
                dt = build_dt(dt_info_params[0], isa, dt_par, dt_ret)
                fdt_key = dt + "," + dt
                f_full_name = build_func_name_short(isa, dt, f_name, lmul=_parse_lmul(dt_info_params[0], isa, dt_par, dt_ret, lmul), isa_name=isa_name, masked_version=masked_ver)
            elif len(dt_info_params) == 2:
                dt_1 = build_dt(dt_info_params[0], isa, dt_par, dt_ret)
                dt_2 = build_dt(dt_info_params[1], isa, dt_par, dt_ret)
                fdt_key = dt_1 + "," + dt_2
                f_full_name = build_func_name(isa, dt_1, dt_2, f_name, lmul=_parse_lmul(dt_info_params[0], isa, dt_par, dt_ret, lmul), isa_name=isa_name, masked_version=masked_ver)
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
    ar_substitute = _RE_PLACEHOLDER.findall(ir)
    requirements = {}

    for s in ar_substitute:
        item_type = s.split('<')[0]

        if item_type not in ["r", "m", "s", "N"]:
            f_name = item_type
            if f_name not in funcs:
                print("Panic: '" + f_name + "' is not in the available MIPP functions.")
                exit(-1)

            fdt_key = ""
            dt_info = _RE_ANGLE.findall(s)[0]
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


# Masks in interfaces and in implems are not defined the same way.
# This might be bad idk.

# Short variant names used in the JSON data files -> internal mask kinds.
_VARIANT_TO_MASK_KIND = {"u": None, "m": "mask", "z": "maskz", "s": "masks"}

def ff_mask_kind(ff):
    """
    Mask kind of an entry of implems: None (unmasked), "mask", "maskz", "masks",
    or "horiz_lmul" for the entries with `"mode": "horiz_lmul"`.
    The JSON files use the short names (`"variant": "m" | "z" | "s"`).
    """
    if ff.get("mode"):
        return ff["mode"]
    return _VARIANT_TO_MASK_KIND[ff.get("variant", "u")]

# ff is an entry in implems
def is_masked_implem(ff):
    return ff_mask_kind(ff) is not None

def mask_kind_from_ff(ff):
    # Expected: "mask", "maskz", "masks"
    return ff_mask_kind(ff)

def is_supported_mask_kind(variant_set, mask_kind):
    """
    variant_set is an entry in interfaces[f]["variants"] 
    and mask_kind is "mask", "maskz" or "masks".
     """
    if variant_set is None:
        return False
    if mask_kind == "mask":
        return variant_set.is_maskable()
    if mask_kind == "maskz":
        return variant_set.is_maskzable()
    if mask_kind == "masks":
        return variant_set.is_masksable()
    return False


#initialize the bucket for masked status if it does not exist yet
def _ensure_masked_status_bucket(funcs, f, dt_key, mask_kind):
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
    _ensure_masked_status_bucket(funcs, func_name, dt_key, mask_kind)
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

def _build_ifdef_rec_masked(funcs, func_name, dt_key, mask_kind, memo=None):
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


def _is_ifdef_masked(funcs, func_name, dt_key, mask_kind):
    ifdef = _build_ifdef_rec_masked(funcs, func_name, dt_key, mask_kind)
    if ifdef:
        return True
    else:
        return False


def _is_fully_missing_masked_func(funcs, func_name, dt_key, mask_kind):
    bucket = get_masked_bucket(funcs, func_name, dt_key, mask_kind)
    # if func_name == "store":
    #     print("debug: bucket for func '" + func_name + "' dt_key '" + dt_key + "' mask_kind '" + mask_kind + "' is: " + str(bucket))

    if bucket is None:
        return True
    return len(bucket) == 0


def is_missing_masked_func(funcs, func_name, dt_key, mask_kind):
    return _is_fully_missing_masked_func(funcs, func_name, dt_key, mask_kind) or _is_ifdef_masked(funcs, func_name, dt_key, mask_kind)


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
            ret = _build_ifdef_rec_masked(funcs, f, fdt, mask_kind)
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
from cond_utils import is_guard_dead_under_cond
from cond_utils import clear_cond_caches as _clear_cond_caches

_isa_config_cache = {}
# Cache for the no-validation fast path of compute_dt_par_dt_ret
_dt_split_cache = {}
_dt_validated_cache = {}

def clear_memo_caches():
    GLOBAL_MEMO_IFDEF.clear()
    GLOBAL_MEMO_IFDEF_MASKED.clear()
    _isa_config_cache.clear()
    _dt_split_cache.clear()
    _dt_validated_cache.clear()
    _clear_cond_caches()



def compute_dt_par_dt_ret(funcs, f, dt, check_support=True):
    # Fast path: no validation needed (most common call-site)
    if not check_support or funcs is None or f is None:
        cached = _dt_split_cache.get(dt)
        if cached is not None:
            return cached
        parts = dt.split(',')
        result = (parts[0], parts[0]) if len(parts) <= 1 else (parts[0], parts[1])
        _dt_split_cache[dt] = result
        return result
    # Slow path: with validation and cache
    key = (f, dt)
    cached = _dt_validated_cache.get(key)
    if cached is not None:
        return cached

    parts = dt.split(',')
    if len(parts) <= 1:
        dt_par = parts[0]
        dt_ret = parts[0]
        if check_support and funcs and f and dt_par not in funcs[f]["datatypes"]:
            print("Panic: unsupported type for '" + f + "<" + dt_par + "," + dt_par + ">" + "' function.")
            exit(-1)
    else:
        dt_par = parts[0]
        dt_ret = parts[1]
        dtk = dt_par + "," + dt_ret
        if check_support and funcs and f and dtk not in funcs[f]["datatypes"]:
            print("Panic: unsupported type for '" + f + "<" + dt_par + "," + dt_ret + ">" + "' function.")
            exit(-1)
    
    result = (dt_par, dt_ret)
    _dt_validated_cache[key] = result
    return result



def load_implem_tables(current_file, templates_filename, implems_filename):
    import json
    import os
    from input_validation import validate_templates_config, validate_implems_config
    current_dir = os.path.dirname(os.path.abspath(current_file))
    
    # Load templates
    templates_path = os.path.join(current_dir, templates_filename)
    with open(templates_path, "r") as f:
        tpl_dict = json.load(f)
    validate_templates_config(tpl_dict, templates_path)

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
    implems_path = os.path.join(current_dir, implems_filename)
    with open(implems_path, "r") as f:
        raw_implems = json.load(f)
    validate_implems_config(raw_implems, implems_path)
    from input_validation import validate_template_references
    validate_template_references(raw_implems, tpl_dict, implems_path)
        
    resolved_implems = {}
    for func, choices in raw_implems.items():
        resolved_choices = []
        for choice in choices:
            resolved_choice = {}
            for k, v in choice.items():
                if k in ("datatypes", "variants"):
                    resolved_choice[k] = resolve_datatypes(v)
                elif k == "template":
                    # Retrieve the template dict from tpl_dict
                    resolved_choice[k] = tpl_dict[v]
                else:
                    resolved_choice[k] = v
            resolved_choices.append(resolved_choice)
        resolved_implems[func] = resolved_choices
        
    return tpl_dict, resolved_implems


def list_simd_ext_names():
    """
    Returns the names of all SIMD extensions found in generator/simd_ext/,
    sorted alphabetically so that the generated output does not depend on
    the filesystem enumeration order.
    """
    import os
    base_dir = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
    simd_ext_dir = os.path.join(base_dir, "simd_ext")
    return sorted(
        d for d in os.listdir(simd_ext_dir)
        if os.path.isdir(os.path.join(simd_ext_dir, d)) and d != "__pycache__"
    )


def uses_mask_ldiv(isa):
    """
    True if the ISA implements software half-vectors (d2) on its own registers,
    only the lower half of the lanes being meaningful ("sw_ldiv_type" is "mask"
    and -2 is listed in "sw_lmul").
    """
    if not isa:
        return False
    return (
        isa.get("sw_ldiv_type") == "mask"
        and any(int(x) == -2 for x in isa.get("sw_lmul", []))
    )


def has_sw_ldiv(isa):
    """True if the ISA builds its half-vectors (d2) in software, whatever the strategy."""
    return uses_sub_isa_ldiv(isa) or uses_mask_ldiv(isa)


def uses_ldiv_templates(isa):
    """
    True if the functions that change the LMUL (low, high, combine, wcvt, ncvt) of the ISA come from
    templates: the ISAs with half-vectors by mask, and the ISAs with half-vectors on a sub_isa that
    provide a `<isa>_ldiv_mask.json` (their d2 is the register of the sub_isa, the generic file
    does not apply to them).
    """
    return (uses_mask_ldiv(isa) or (uses_sub_isa_ldiv(isa) and bool(ldiv_mask_functions(isa)))
            or uses_hw_ldiv_templates(isa))


def uses_hw_ldiv_templates(isa):
    """
    True if the ISA has hardware half-vectors and register groups (-2 and several LMULs in
    "hw_lmul", as RVV) and a `<isa>_ldiv_mask.json` that gives the functions changing the LMUL
    (low, high, combine, wcvt, ncvt) between every pair of consecutive hardware LMULs.
    """
    if not isa or isa.get("is_scalar", False) or uses_mask_ldiv(isa) or uses_sub_isa_ldiv(isa):
        return False
    hw = [int(x) for x in isa.get("hw_lmul", [1])]
    return -2 in hw and len(hw) > 2 and bool(ldiv_mask_functions(isa))


def uses_sub_isa_ldiv(isa):
    """
    True if the ISA implements software half-vectors (d2) on the registers of
    its sub_isa, i.e. "sw_ldiv_type" is "sub_isa" and -2 is listed in "sw_lmul".
    Declaring a sub_isa alone only sets the ISA detection precedence.
    """
    if not isa:
        return False
    return (
        isa.get("sw_ldiv_type") == "sub_isa"
        and bool(isa.get("sub_isa"))
        and any(int(x) == -2 for x in isa.get("sw_lmul", []))
    )


def load_isa_config(isa_name):
    import copy
    if isa_name not in _isa_config_cache:
        import json
        import os
        base_dir = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
        ext_dir = os.path.join(base_dir, "simd_ext", isa_name)
        
        # Load capability JSON
        with open(os.path.join(ext_dir, f"{isa_name}_isa.json"), "r") as f:
            isa = json.load(f)
        from input_validation import validate_isa_config
        validate_isa_config(isa, isa_name)
        
        # Merge "variables" into datatype configurations for backward-compatibility
        if "datatypes" in isa:
            for dt, dt_conf in isa["datatypes"].items():
                if "variables" in dt_conf:
                    variables = dt_conf.pop("variables")
                    for k, v in variables.items():
                        dt_conf[k] = v

        if "size" in isa and isinstance(isa["size"], list):
            isa["size"] = set(isa["size"]) # SVE backwards compatibility
            
        # Load native and emulation tables
        _, implems = load_implem_tables(os.path.join(ext_dir, "__init__.py"), f"{isa_name}_native_templates.json", f"{isa_name}_native_implems.json")
        
        emu_tpl_path = os.path.join(ext_dir, f"{isa_name}_emu_templates.json")
        emu_impl_path = os.path.join(ext_dir, f"{isa_name}_emu_implems.json")
        if os.path.exists(emu_tpl_path) and os.path.exists(emu_impl_path):
            _, implems_emu = load_implem_tables(os.path.join(ext_dir, "__init__.py"), f"{isa_name}_emu_templates.json", f"{isa_name}_emu_implems.json")
        else:
            implems_emu = {}
        
        from input_validation import validate_logical_integrity
        validate_logical_integrity(isa, implems, implems_emu)

        _isa_config_cache[isa_name] = (isa, implems, implems_emu)
        
    isa, implems, implems_emu = _isa_config_cache[isa_name]
    return copy.deepcopy(isa), copy.deepcopy(implems), copy.deepcopy(implems_emu)