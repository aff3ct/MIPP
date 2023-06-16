from tools import *

isa_sve = {
    "name": "sve",
    "prefix": "sv",
    "size": {"128 , 256 , 512 , 1024 , 2048",},
    "define": "__ARM_FEATURE_SVE",
    "hw_lmul": True,
    "datatypes": {
        float64 : {"data_ext": "f64" , "data_ext_logi": "b" , "data_ext_msk": "p" ,"reg" : "svfloat64_t" , "msk": "svbool_t" , "to_ptr": "float64_t",  } ,
        float32 : {"data_ext": "f32" , "data_ext_logi": "b" , "data_ext_msk": "p" ,"reg" : "svfloat32_t" , "msk": "svbool_t" , "to_ptr": "float32_t",  } ,
        int64   : {"data_ext": "s64" , "data_ext_logi": "b" , "data_ext_msk": "p" ,"reg" : "svint64_t"   , "msk": "svbool_t" , "to_ptr": "svint64_t",  } ,
        int32   : {"data_ext": "s32" , "data_ext_logi": "b" , "data_ext_msk": "p" ,"reg" : "svint32_t"   , "msk": "svbool_t" , "to_ptr": "svint32_t",  } ,
        int16   : {"data_ext": "s16" , "data_ext_logi": "b" , "data_ext_msk": "p" ,"reg" : "svint16_t"   , "msk": "svbool_t" , "to_ptr": "svint16_t",  } ,
        int8    : {"data_ext": "s8"  , "data_ext_logi": "b" , "data_ext_msk": "p" ,"reg" : "svint8_t"    , "msk": "svbool_t" , "to_ptr": "svint8_t",   } ,
        uint64  : {"data_ext": "u64" , "data_ext_logi": "b" , "data_ext_msk": "p" ,"reg" : "svuint64_t"  , "msk": "svbool_t" , "to_ptr": "svuint64_t", } ,
        uint32  : {"data_ext": "u32" , "data_ext_logi": "b" , "data_ext_msk": "p" ,"reg" : "svuint32_t"  , "msk": "svbool_t" , "to_ptr": "svuint32_t", } ,
        uint16  : {"data_ext": "u16" , "data_ext_logi": "b" , "data_ext_msk": "p" ,"reg" : "svuint16_t"  , "msk": "svbool_t" , "to_ptr": "svuint16_t", } ,
        uint8   : {"data_ext": "u8"  , "data_ext_logi": "b" , "data_ext_msk": "p" ,"reg" : "svuint8_t"   , "msk": "svbool_t" , "to_ptr": "svuint8_t",  } ,
    },
}

tpl_implem_sve = {
        "reinterpret" : { "format": "short", "code": "{% if isa_dt_par.data_ext_logi != isa_dt_ret.data_ext_logi -%}{{ isa.prefix }}{{ instr_name }}_{{isa_dt_par.data_ext_logi}}_{{isa_dt_ret.data_ext_logi}}(r0.m);{% else -%} r0.m;{% endif %}" },
        "load"        : { "format": "short", "code": "{{ isa.prefix }}{{ instr_name }}_{{ isa_dt_par.data_ext_logi }}(({{isa_dt_par.data_ext_msk}} m,{{ isa_dt_par.to_ptr }}*) p0);" },
        "toreg"       : { "format": "short", "code": "{% if isa_dt_par.data_ext_msk != isa_dt_ret.data_ext_logi -%}{{ isa.prefix }}_{{ instr_name }}{{isa_dt_par.data_ext_msk}}_{{isa_dt_ret.data_ext_logi}}(m0.m);{% else -%} m0.m;{% endif %}" },

}

implems_sve = {
    "reinterpret" : [
        { "instr_name": "reinterpret", "datatypes": [float32, float64, int64, int32], "template": tpl_implem_sve["reinterpret"], } ],
    "load"        : [
        { "instr_name": "ld1", "datatypes": all_datatypes, "template": tpl_implem_sve["load"]},
        { "instr_name": "loadu", "datatypes": all_datatypes, "template": tpl_implem_sve["load"], "if": "defined(_ARM_FEATURE_UNALIGNED)" } ],
    "toreg"       : [
        { "instr_name": "cast", "datatypes": all_datatypes, "template": tpl_implem_avx["toreg"], } ],
}
