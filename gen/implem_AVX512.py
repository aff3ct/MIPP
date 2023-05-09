from tools import *

isa_avx512 = {
    "name": "avx512",
    "prefix": "_mm512",
    "size": 512,
    "define": {"__AVX512F__","__AVX512__","__KNCNI__","__MIC__"},
    "hw_lmul": False,
    "datatypes": {
        float64 : { "data_ext" : "pd"    , "data_ext_logi": "pd"    , "data_ext_msk": "si512" , "reg" : "__m512d" , "msk" : "__mmask8"  , "to_ptr": "float64_t" , } ,
        float32 : { "data_ext" : "ps"    , "data_ext_logi": "ps"    , "data_ext_msk": "si512" , "reg" : "__m512"  , "msk" : "__mmask16" , "to_ptr": "float32_t" , } ,
        int64   : { "data_ext" : "epi64" , "data_ext_logi": "si512" , "data_ext_msk": "si512" , "reg" : "__m512i" , "msk" : "__mmask8"  , "to_ptr": "int64_t"   , } ,
        int32   : { "data_ext" : "epi32" , "data_ext_logi": "si512" , "data_ext_msk": "si512" , "reg" : "__m512i" , "msk" : "__mmask16" , "to_ptr": "int32_t"   , } ,
        int16   : { "data_ext" : "epi16" , "data_ext_logi": "si512" , "data_ext_msk": "si512" , "reg" : "__m512i" , "msk" : "__mmask32" , "to_ptr": "int16_t"   , } ,
        int8    : { "data_ext" : "epi8"  , "data_ext_logi": "si512" , "data_ext_msk": "si512" , "reg" : "__m512i" , "msk" : "__mmask64" , "to_ptr": "int8_t"    , } ,
        uint64  : { "data_ext" : "epu64" , "data_ext_logi": "si512" , "data_ext_msk": "si512" , "reg" : "__m512i" , "msk" : "__mmask8"  , "to_ptr": "uint64_t"  , } ,
        uint32  : { "data_ext" : "epu32" , "data_ext_logi": "si512" , "data_ext_msk": "si512" , "reg" : "__m512i" , "msk" : "__mmask16" , "to_ptr": "uint32_t"  , } ,
        uint16  : { "data_ext" : "epu16" , "data_ext_logi": "si512" , "data_ext_msk": "si512" , "reg" : "__m512i" , "msk" : "__mmask32" , "to_ptr": "uint16_t"  , } ,
        uint8   : { "data_ext" : "epu8"  , "data_ext_logi": "si512" , "data_ext_msk": "si512" , "reg" : "__m512i" , "msk" : "__mmask64" , "to_ptr": "uint8_t"   , } ,
    },

tpl_implem_avx512 = {
    "cast"   : { "format": "short", "code": "{% if isa_dt_par.data_ext_logi != isa_dt_ret.data_ext_logi -%}{{ isa.prefix }}_{{ instr_name }}{{isa_dt_par.data_ext_logi}}_{{isa_dt_ret.data_ext_logi}}(r0.m);{% else -%} r0.m;{% endif %}" },
    "cast_k" : { "format": "short", "code": "m0.m;" },
    "toreg"  : { "format": "short", "code": "{% if isa_dt_par.data_ext_msk != isa_dt_ret.data_ext_logi -%}{{ isa.prefix }}_{{ instr_name }}{{isa_dt_par.data_ext_msk}}_{{isa_dt_ret.data_ext_logi}}(m0.m);{% else -%} m0.m;{% endif %}" },
    "load"   : { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext_logi }}(({{ isa_dt_par.to_ptr }}*) p0);" },
    "store"  : { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext_logi }}(({{ isa_dt_par.to_ptr }}*) p0, r0.m);" },

implems_avx = {
    "cast"   : [
        { "instr_name" : "cast", "datatypes": all_datatypes_cart_prod, "template": tpl_implem_avx["cast"],"if": "defined(__AVX512F__)" } ],
    "cast_k" : [
        { "instr_name" : "cast", "datatypes": all_datatypes_cart_prod, "template": tpl_implem_avx["cast_k"],"if": "defined(__AVX512F__)" } ],
    "toreg"  : [
        { "instr_name" : "cast", "datatypes": all_datatypes, "template": tpl_implem_avx["toreg"], "if": "defined(__AVX512F__)"} ],
    "load"   : [
        { "instr_name" : "load"  , "datatypes": all_datatypes , "template": tpl_implem_avx["load"] , "if": "defined(MIPP_ALIGNED_LOADS)" }    ,
        { "instr_name" : "loadu" , "datatypes": all_datatypes , "template": tpl_implem_avx["load"] , "if": "!defined(MIPP_ALIGNED_LOADS)" } ] ,
    "loadu"  : [
        { "instr_name" : "loadu", "datatypes": all_datatypes, "template": tpl_implem_avx["load"], "if": "defined(__AVX512F__)"} ],
    "store"  : [
        { "instr_name": "store", "datatypes": all_datatypes, "template": tpl_implem_avx["store"], "if": "defined(MIPP_ALIGNED_LOADS)" },
        { "instr_name": "storeu", "datatypes": all_datatypes, "template": tpl_implem_avx["store"], "if": "!defined(MIPP_ALIGNED_LOADS)" } ],
    "storeu" : [
        { "instr_name": "storeu", "datatypes": all_datatypes, "template": tpl_implem_avx["store"], "if": "defined(__AVX512F__)"} ],
