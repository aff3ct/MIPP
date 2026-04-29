from tools import *

isa_sve = {
    "name": "sve",
    "prefix": "sv",
    "size": {128 , 256 , 512 , 1024 , 2048},
    "define": "defined(__ARM_FEATURE_SVE)",
    "architecture": "AArch64",
    "hw_lmul": True,
    "datatypes": {
        float64 : {"data_ext": "f64" , "data_ext_logi": "b64" , "data_ext_msk": "p" ,"reg" : "svfloat64_t" , "msk": "svbool_t" , "to_ptr": "float64_t",  } ,
        float32 : {"data_ext": "f32" , "data_ext_logi": "b32" , "data_ext_msk": "p" ,"reg" : "svfloat32_t" , "msk": "svbool_t" , "to_ptr": "float32_t",  } ,
        int64   : {"data_ext": "s64" , "data_ext_logi": "b64" , "data_ext_msk": "p" ,"reg" : "svint64_t"   , "msk": "svbool_t" , "to_ptr": "int64_t",  } ,
        int32   : {"data_ext": "s32" , "data_ext_logi": "b32" , "data_ext_msk": "p" ,"reg" : "svint32_t"   , "msk": "svbool_t" , "to_ptr": "int32_t",  } ,
        int16   : {"data_ext": "s16" , "data_ext_logi": "b16" , "data_ext_msk": "p" ,"reg" : "svint16_t"   , "msk": "svbool_t" , "to_ptr": "int16_t",  } ,
        int8    : {"data_ext": "s8"  , "data_ext_logi": "b8"  , "data_ext_msk": "p" ,"reg" : "svint8_t"    , "msk": "svbool_t" , "to_ptr": "int8_t",   } ,
        uint64  : {"data_ext": "u64" , "data_ext_logi": "b64" , "data_ext_msk": "p" ,"reg" : "svuint64_t"  , "msk": "svbool_t" , "to_ptr": "uint64_t", } ,
        uint32  : {"data_ext": "u32" , "data_ext_logi": "b32" , "data_ext_msk": "p" ,"reg" : "svuint32_t"  , "msk": "svbool_t" , "to_ptr": "uint32_t", } ,
        uint16  : {"data_ext": "u16" , "data_ext_logi": "b16" , "data_ext_msk": "p" ,"reg" : "svuint16_t"  , "msk": "svbool_t" , "to_ptr": "uint16_t", } ,
        uint8   : {"data_ext": "u8"  , "data_ext_logi": "b8"  , "data_ext_msk": "p" ,"reg" : "svuint8_t"   , "msk": "svbool_t" , "to_ptr": "uint8_t",  } ,
    },
}

tpl_implem_sve = {
    "cast"               : { "format": "short", "code":"{% if isa_dt_par.data_ext != isa_dt_ret.data_ext -%}{{ isa.prefix }}{{ instr_name }}_{{isa_dt_ret.data_ext}}_{{isa_dt_par.data_ext}}(r0.r);{% else -%} r0.r;{% endif %}" },
    "cast_k"             : { "format": "short", "code":" m0.m;"},
    # with mask or from mask
    "blend"                : { "format": "short", "code": "{{ isa.prefix }}{{ instr_name }}_{{ isa_dt_par.data_ext }}(m0.m, r0.r, r1.r);" },
    "load"                 : { "format": "short", "code": "{{ isa.prefix }}{{ instr_name }}_{{ isa_dt_par.data_ext }}(svptrue_{{ isa_dt_par.data_ext_logi }}(), ({{ isa_dt_par.to_ptr }}*) p0);" },
    "mask_load"            : { "format": "short", "code": "{{ isa.prefix }}{{ instr_name }}_{{ isa_dt_par.data_ext }}(m0.m, ({{ isa_dt_par.to_ptr }}*) p0);" },
    "store"                : { "format": "short", "code": "{{ isa.prefix }}{{ instr_name }}_{{ isa_dt_par.data_ext }}(svptrue_{{ isa_dt_par.data_ext_logi }}(), ({{ isa_dt_par.to_ptr }}*) p0, r0.r);" },
    "mask_store"           : { "format": "short", "code": "{{ isa.prefix }}{{ instr_name }}_{{ isa_dt_par.data_ext }}(m0.m, ({{ isa_dt_par.to_ptr }}*) p0, r0.r);" },
#    "set_k"                : { "format": "long", "code":
# """%m<tp>% res;
#    res.m = vals;
#    return res;""" },
    #"low_k"               : { "format": "short", "code": "{{ isa.prefix }}{{ instr_name }}(svptrue_{{ isa_dt_par.data_ext_logi }}());" },
    "set1"                 : { "format": "short", "code": "{{ isa.prefix }}{{ instr_name }}_{{ isa_dt_par.data_ext }}(v0);"},
    "set1_k"               : { "format": "short", "code": "{{ isa.prefix }}{{ instr_name }}_{{ isa_dt_par.data_ext_logi }}((const bool) v0);"},
    "set0"                 : { "format": "short", "code": "{{ isa.prefix }}{{ instr_name }}_{{ isa_dt_par.data_ext }}({% if 'float' in isa_dt_par.to_ptr -%}0.0{% else -%}0{% endif %}{{dt_par.literal_suffix}});"},
    "set0_k"               : { "format": "short", "code": "{{ isa.prefix }}{{ instr_name }}_b();"},
    "andb"                 : { "format": "short", "code": "{{ isa.prefix }}{{ instr_name }}_{{ isa_dt_par.data_ext}}_z(svptrue_{{ isa_dt_par.data_ext_logi }}(), r0.r, r1.r);" },
    "andb_k"               : { "format": "short", "code": "{{ isa.prefix }}{{ instr_name }}_z(svptrue_{{ isa_dt_par.data_ext_logi }}(), m0.m, m1.m);" },
    "notb_k"               : { "format": "short", "code": "{{ isa.prefix }}{{ instr_name }}_z(svptrue_{{ isa_dt_par.data_ext_logi }}(), m0.m);" },
    "testz"                : { "format": "long", "code": 
 """return !{{ isa.prefix }}{{ instr_name }}(svptrue_{{ isa_dt_par.data_ext_logi }}(), m0.m);""" },
    "std_2_reg_in_no_msk_z" : { "format": "short", "code": "{{ isa.prefix }}{{ instr_name }}_{{ isa_dt_par.data_ext }}_z(svptrue_{{ isa_dt_par.data_ext_logi }}(), r0.r, r1.r);" },
    "std_2_reg_in_msk_z"    : { "format": "short", "code": "{{ isa.prefix }}{{ instr_name }}_{{ isa_dt_par.data_ext }}_z(m0.m, r0.r, r1.r);" },
    "std_3_reg_in_no_msk_z" : { "format": "short", "code": "{{ isa.prefix }}{{ instr_name }}_{{ isa_dt_par.data_ext }}_z(svptrue_{{ isa_dt_par.data_ext_logi }}(), r0.r, r1.r, r2.r);" },
    "std_2_reg_in_no_msk" : { "format": "short", "code": "{{ isa.prefix }}{{ instr_name }}_{{ isa_dt_par.data_ext }}(svptrue_{{ isa_dt_par.data_ext_logi }}(), r0.r, r1.r);" },
    "reduce"              : { "format": "long", "code": 
"""return {{ isa.prefix }}{{ instr_name }}_{{ isa_dt_par.data_ext }}(svptrue_{{ isa_dt_par.data_ext_logi }}(), r0.r);""" },
    # idem store
    # getfirst unused from reduce
    #
    # require literal zero from c type instead of 0 (add it in tools or in this file)
    #"set0"                : { "format": "short", "code": "{{ isa.prefix }}{{ instr_name }}_{{ isa_dt_par.data_ext }}(0);"},
}

implems_sve = {
    "cast" : [
        { "instr_name": "reinterpret", "datatypes": all_datatypes_cart_prod, "template": tpl_implem_sve["cast"] } ],
    "cast_k" : [
        { "instr_name" : ""    , "datatypes": all_datatypes_cart_prod , "template": tpl_implem_sve["cast_k"]  } ],
    "blend": [
        { "instr_name": "sel", "datatypes": all_datatypes, "template": tpl_implem_sve["blend"] }],
    "load" : [
        { "instr_name": "ld1", "datatypes": all_datatypes, "template": tpl_implem_sve["load"]},],
    "maskzld" : [
        { "instr_name": "ld1", "datatypes": all_defs, "template": tpl_implem_sve["mask_load"]},],
    "loadu"  : [
        { "instr_name": "ld1", "datatypes": all_datatypes, "template": tpl_implem_sve["load"]},],
    "store" : [
        { "instr_name": "st1", "datatypes": all_datatypes, "template": tpl_implem_sve["store"]},],
    "maskst" : [
        { "instr_name": "st1", "datatypes": all_defs, "template": tpl_implem_sve["mask_store"]},],
    "storeu" : [
        { "instr_name": "st1", "datatypes": all_datatypes, "template": tpl_implem_sve["store"]},],
    # ok with bool array
    #"set_k" : [
    #    { "instr_name": "", "datatypes": [int32, int64], "template": tpl_implem_sve["set_k"], "if": "defined(__ARM_FEATURE_SVE_PREDICATE_OPERATORS)"},],
    "set1" : [
        { "instr_name": "dup", "datatypes": all_datatypes, "template": tpl_implem_sve["set1"]},],
    "set1_k" : [
        { "instr_name": "dup", "datatypes": all_int_uint , "template": tpl_implem_sve["set1_k"]},],
    "set0"   : [
        { "instr_name": "dup", "datatypes": all_datatypes, "template": tpl_implem_sve["set0"]   } ],
    "set0_k": [
        { "instr_name": "pfalse", "datatypes": all_datatypes, "template": tpl_implem_sve["set0_k"] } ],
    #"low_k": [
    #    { "instr_name": "unpklo_b", "datatypes": all_datatypes, "template": tpl_implem_sve["low_k"] } ],
    # manage z, m , x here only z
    "andb": [
        { "instr_name": "and"  , "datatypes": all_int_uint, "template": tpl_implem_sve["andb"] } ],
    "andb_k": [
        { "instr_name": "and"  , "datatypes": all_datatypes, "template": tpl_implem_sve["andb_k"] } ],
    "notb_k": [
        { "instr_name": "not"  , "datatypes": all_datatypes, "template": tpl_implem_sve["notb_k"] } ],
    "testz": [
        { "instr_name": "ptest_any"  , "datatypes": all_datatypes, "template": tpl_implem_sve["testz"] } ],
    "add": [
        { "instr_name": "add"  , "datatypes": all_datatypes, "template": tpl_implem_sve["std_2_reg_in_no_msk_z"] } ],
    "maskz_add": [
        { "instr_name": "add"  , "datatypes": all_datatypes, "template": tpl_implem_sve["std_2_reg_in_msk_z"] } ],
    "sub": [
        { "instr_name": "sub"  , "datatypes": all_datatypes, "template": tpl_implem_sve["std_2_reg_in_no_msk_z"] } ],
    #"maskz_sub": [
    #    { "instr_name": "sub"  , "datatypes": all_datatypes, "template": tpl_implem_sve["std_2_reg_in_msk_z"] } ],
    "mul": [
        { "instr_name": "mul"  , "datatypes": all_datatypes, "template": tpl_implem_sve["std_2_reg_in_no_msk_z"] } ],
    #"maskz_mul": [
    #    { "instr_name": "mul"  , "datatypes": all_datatypes, "template": tpl_implem_sve["std_2_reg_in_msk_z"] } ],
    "div": [
        { "instr_name": "div"  , "datatypes": all_float, "template": tpl_implem_sve["std_2_reg_in_no_msk_z"] } ],
    "fmadd": [
        { "instr_name": "mla"  , "datatypes": all_float, "template": tpl_implem_sve["std_3_reg_in_no_msk_z"] } ],
    "cmpeq": [
        { "instr_name": "cmpeq"  , "datatypes": all_datatypes, "template": tpl_implem_sve["std_2_reg_in_no_msk"] } ],
    "cmpneq": [
        { "instr_name": "cmpne"  , "datatypes": all_datatypes, "template": tpl_implem_sve["std_2_reg_in_no_msk"] } ],
    "hadd_to_scal": [
        { "instr_name": "addv", "datatypes": all_datatypes, "template": tpl_implem_sve["reduce"] } ],
}
