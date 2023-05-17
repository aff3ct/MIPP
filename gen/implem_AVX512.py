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
}

tpl_implem_avx512 = {
    "cast"                : { "format": "short", "code": "{% if isa_dt_par.data_ext_logi != isa_dt_ret.data_ext_logi -%}{{ isa.prefix }}_{{ instr_name }}{{isa_dt_par.data_ext_logi}}_{{isa_dt_ret.data_ext_logi}}(r0.m);{% else -%} r0.m;{% endif %}" },
    "cast_k"              : { "format": "short", "code": "m0.m;" },
    "toreg"               : { "format": "short", "code": "{% if isa_dt_par.data_ext_msk != isa_dt_ret.data_ext_logi -%}{{ isa.prefix }}_{{ instr_name }}{{isa_dt_par.data_ext_msk}}_{{isa_dt_ret.data_ext_logi}}(m0.m);{% else -%} m0.m;{% endif %}" },
    "tomsk"               : { "format": "short", "code": "{% if isa_dt_par.data_ext_logi != isa_dt_ret.data_ext_msk -%}{{ isa.prefix }}_{{ instr_name }}{{isa_dt_par.data_ext_logi}}_{{isa_dt_ret.data_ext_msk}}(r0.m);{% else -%} r0.m;{% endif %}" },
    "load"                : { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext_logi }}(({{ isa_dt_par.to_ptr }}*) p0);" },
    "store"               : { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext_logi }}(({{ isa_dt_par.to_ptr }}*) p0, r0.m);" },
    "set0"                : { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext_logi }}();" },
    "set1"                : { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(v0);" },
    "low"                 : { "format": "long",  "code":
""" return %cast<tp,c : float|b:32>%({{ isa.prefix }}_{{ instr_name }}_pd(%cast<c:float|b:32,tp>%(r0).m, 0));""" },
    "high"                : { "format": "long",  "code":
""" return %cast<tp,c : float|b:32>%({{ isa.prefix }}_{{ instr_name }}_pd(%cast<c:float|b:32,tp>%(r0).m, 1));""" },
    "arith_1arg"          : { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(r0.m);" },
    "arith_2args"         : { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(r0.m, r1.m);" },
    "logi_2args"          : { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext_logi }}(r0.m, r1.m);" },
    "logi_m_2args"        : { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}(m0.m, m1.m);" },
    "arith_3args"         : { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(r0.m, r1.m, r2.m);" },
    "lshift"              : { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(r0.m, r1.m, r2.m);" },
    "andb_k"              : { "format": "long",  "code":
""""{{ isa.prefix }}_{{ instr_name }}(m0.m, m1.m);""" }, 
    
    "cmpeq_float"         : { "format": "long", "code":
""" %r<tp>% tmp;
    tmp.m = {{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}_mask(r0.m, r1.m, _CMP_EQ_OQ);
    return %tomsk<tp>%(tmp);""" },
    "cmp_int"             : { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(r0.m, r1.m);" },
    "cmpneq_float": { "format": "long", "code":
""" %r<tp>% tmp;
    tmp.m = {{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}_mask(r0.m, r1.m, _CMP_NEQ_OQ);
    return %tomsk<tp>%(tmp);""" },
    "blend"                : { "format": "short", "code": "{{ isa.prefix }}_mask_{{ instr_name }}_{{ isa_dt_par.data_ext }}(r0.m, r1.m, %toreg<tp>%(m0).m);" },
    "reduce_64": { "format": "long", "code":
""" %r<c:float|b:32>% rsf; 
    rsf.m = _mm512_permutexvar_ps(%cast<tp,c:float|b:32>%(_mm512_set_epi32( 7, 6, 5, 4, 3, 2, 1, 0,15,14,13,12,11,10,9,8), %cast<tp,c:float|b:32>%(r0).m));
    %r<tp>% rs1 = %cast<c:float|b:32,tp>%(rsf);
    rs1.m = {{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(r0.m, rs1.m);
    rsf = %cast<tp,c:float|b:32>%(rs1);
    rsf.m = _mm512_permutexvar_ps(%cast<tp,c:float|b:32>%(_mm512_set_epi32(11,10, 9, 8,15,14,13,12, 3, 2, 1, 0, 7, 6,5,4), %cast<tp,c:float|b:32>%(r0).m));
    %r<tp>% rs2 = %cast<c:float|b:32,tp>%(rsf);
    rs2.m = {{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(rs1.m, rs2.m);
    rsf = %cast<tp,c:float|b:32>%(rs1);
    rsf.m = _mm512_shuffle_epi32(rsf.m, _MM_PERM_ENUM(_MM_SHUFFLE(1,0,3,2))))); 
    %r<tp>% rs3 = %cast<c:float|b:32,tp>%(rsf);
    rs3.m = {{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(rs2.m, rs3.m);
    return rs3;""" 
    "reduce_32": { "format": "long", "code":
""" %r<c:float|b:32>% rsf;
    rsf.m = _mm512_permutexvar_ps(_mm512_set_epi32( 7, 6, 5, 4, 3, 2, 1, 0,15,14,13,12,11,10,9,8),%cast<tp,c:float|b:32>%(r0).m));
    %r<tp>% rs1 = %cast<c:float|b:32,tp>%(rsf);
    rs1.m = {{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(r0.m, rs1.m);   
    rsf = %cast<tp,c:float|b:32>%(rs1);
    rsf.m = _mm512_permutexvar_ps(_mm512_set_epi32(11,10, 9, 8,15,14,13,12, 3, 2, 1, 0, 7, 6,5,4),%cast<tp,c:float|b:32>%(r0).m));
    %r<tp>% rs2 = %cast<c:float|b:32,tp>%(rsf);
    rs2.m = {{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(rs1.m, rs2.m);
    rsf = %cast<tp,c:float|b:32>%(rs2);
    rsf.m = _mm512_shuffle_epi32(%cast<tp,c:float|b:32>%(r0).m,_MM_PERM_ENUM(_MM_SHUFFLE(1,0,3,2)));
    %r<tp>% rs3 = %cast<c:float|b:32,tp>%(rsf);
    rs3.m = {{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(rs2.m, rs3.m);
    rsf = %cast<tp,c:float|b:32>%(rs3);
    rsf.m = _mm512_shuffle_epi32(%cast<tp,c:float|b:32>%(r0).m,_MM_PERM_ENUM(_MM_SHUFFLE(2,3,0,1)));
    %r<tp>% rs4 = %cast<c:float|b:32,tp>%(rsf);
    rs4.m = {{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(rs3.m, rs4.m);
    return rs4;""" },
    "reduce_16": { "format": "long", "code":
""" %r<c:float|b:32>% rsf;
    rsf.m = _mm512_permutexvar_ps(_mm512_set_epi32( 7, 6, 5, 4, 3, 2, 1, 0,15,14,13,12,11,10,9,8),%cast<tp,c:float|b:32>%(r0).m));
    %r<tp>% rs1 = %cast<c:float|b:32,tp>%(rsf);
    rs1.m = {{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(r0.m, rs1.m);   
    rsf = %cast<tp,c:float|b:32>%(rs1);

    rsf.m = _mm512_permutexvar_ps(_mm512_set_epi32(11,10, 9, 8,15,14,13,12, 3, 2, 1, 0, 7, 6,5,4),%cast<tp,c:float|b:32>%(r0).m));
    %r<tp>% rs2 = %cast<c:float|b:32,tp>%(rsf);
    rs2.m = {{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(rs1.m, rs2.m);
    rsf = %cast<tp,c:float|b:32>%(rs2);

    rsf.m = _mm512_shuffle_epi32(%cast<tp,c:float|b:32>%(r0).m,_MM_PERM_ENUM(_MM_SHUFFLE(1,0,3,2)));
    %r<tp>% rs3 = %cast<c:float|b:32,tp>%(rsf);
    rs3.m = {{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(rs2.m, rs3.m);
    rsf = %cast<tp,c:float|b:32>%(rs3);

    rsf.m = _mm512_shuffle_epi32(%cast<tp,c:float|b:32>%(r0).m,_MM_PERM_ENUM(_MM_SHUFFLE(2,3,0,1)));
    %r<tp>% rs4 = %cast<c:float|b:32,tp>%(rsf);
    rs4.m = {{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(rs3.m, rs4.m);
    rsf = %cast<tp,c:float|b:32>%(rs4);

    ___m512i mask_16 = _mm512_set_epi8(61,60,63,62,57,56,59,58,53,52,55,54,49,48,51,50,
                                              45,44,47,46,41,40,43,42,37,36,39,38,33,32,35,34,
                                              29,28,31,30,25,24,27,26,21,20,23,22,17,16,19,18,
                                              13,12,15,14, 9, 8,11,10, 5, 4, 7, 6, 1, 0, 3, 2);

    rsi.m = _mm512_shuffle_epi8((rsi.m, mask_16));
    %r<tp>% rs5 = %cast<c:int|b:8,tp>%(rsi);
    rs5.m = {{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(rs4.m, rs5.m);
    return rs5;"""
    "reduce_8": { "format": "long", "code":
""" %r<c:float|b:32>% rsf;
    rsf.m = _mm512_permutexvar_ps(_mm512_set_epi32( 7, 6, 5, 4, 3, 2, 1, 0,15,14,13,12,11,10,9,8),%cast<tp,c:float|b:32>%(r0).m));
    %r<tp>% rs1 = %cast<c:float|b:32,tp>%(rsf);
    rs1.m = {{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(r0.m, rs1.m);   
    rsf = %cast<tp,c:float|b:32>%(rs1);

    rsf.m = _mm512_permutexvar_ps(_mm512_set_epi32(11,10, 9, 8,15,14,13,12, 3, 2, 1, 0, 7, 6,5,4),%cast<tp,c:float|b:32>%(r0).m));
    %r<tp>% rs2 = %cast<c:float|b:32,tp>%(rsf);
    rs2.m = {{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(rs1.m, rs2.m);
    rsf = %cast<tp,c:float|b:32>%(rs2);

    rsf.m = _mm512_shuffle_epi32(%cast<tp,c:float|b:32>%(r0).m,_MM_PERM_ENUM(_MM_SHUFFLE(1,0,3,2)));
    %r<tp>% rs3 = %cast<c:float|b:32,tp>%(rsf);
    rs3.m = {{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(rs2.m, rs3.m);
    rsf = %cast<tp,c:float|b:32>%(rs3);

    rsf.m = _mm512_shuffle_epi32(%cast<tp,c:float|b:32>%(r0).m,_MM_PERM_ENUM(_MM_SHUFFLE(2,3,0,1)));
    %r<tp>% rs4 = %cast<c:float|b:32,tp>%(rsf);
    rs4.m = {{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(rs3.m, rs4.m);
    rsf = %cast<tp,c:float|b:32>%(rs4);

    __m512i mask_16 = _mm512_set_epi8(61,60,63,62,57,56,59,58,53,52,55,54,49,48,51,50,
                                              45,44,47,46,41,40,43,42,37,36,39,38,33,32,35,34,
                                              29,28,31,30,25,24,27,26,21,20,23,22,17,16,19,18,
                                              13,12,15,14, 9, 8,11,10, 5, 4, 7, 6, 1, 0, 3, 2);
    rsi.m = _mm512_shuffle_epi8((rsi.m, mask_16);
    %r<tp>% rs5 = %cast<c:int|b:8,tp>%(rsi);
    rs5.m = {{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(rs4.m, rs5.m);

    __m512i mask_8  = _mm512_set_epi8(62,63,60,61,58,59,56,57,54,55,52,53,50,51,48,49,
                                              46,47,44,45,42,43,40,41,38,39,36,37,34,35,32,33,
                                              30,31,28,29,26,27,24,25,22,23,20,21,18,19,16,17,
                                              14,15,12,13,10,11, 8, 9, 6, 7, 4, 5, 2, 3, 0, 1);
    rsi.m = _mm512_shuffle_epi8((rsi.m, mask_8);
    %r<tp>% rs6 = %cast<c:int|b:8,tp>%(rsi);
    rs6.m = {{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(rs5.m, rs6.m);
    return rs6;""" 
}
implems_avx512 = {
    "cast"   : [
        { "instr_name" : "cast"    , "datatypes": all_datatypes_cart_prod , "template": tpl_implem_avx512["cast"]   , "if": "defined(__AVX512F__)" } ]         ,
    "cast_k" : [
        { "instr_name" : "cast"    , "datatypes": all_datatypes_cart_prod , "template": tpl_implem_avx512["cast_k"] , "if": "defined(__AVX512F__)" } ]         ,
    "toreg"  : [
        { "instr_name" : "cast"    , "datatypes": all_datatypes           , "template": tpl_implem_avx512["toreg"]  , "if": "defined(__AVX512F__)"} ]          ,
    "tomsk": [
        { "instr_name": "cast"     , "datatypes": all_datatypes           ,"template": tpl_implem_avx512["tomsk"], } ],
    "load"   : [
        { "instr_name" : "load"    , "datatypes": all_datatypes           , "template": tpl_implem_avx512["load"]   , "if": "defined(MIPP_ALIGNED_LOADS)" }    ,
        { "instr_name" : "loadu"   , "datatypes": all_datatypes           , "template": tpl_implem_avx512["load"]   , "if": "!defined(MIPP_ALIGNED_LOADS)" } ] ,
    "loadu"  : [
        { "instr_name" : "loadu"   , "datatypes": all_datatypes           , "template": tpl_implem_avx512["load"]   , "if": "defined(__AVX512F__)"} ]          ,
    "store"  : [
        { "instr_name" : "store"   , "datatypes": all_datatypes           , "template": tpl_implem_avx512["store"]  , "if": "defined(MIPP_ALIGNED_LOADS)" }    ,
        { "instr_name" : "storeu"  , "datatypes": all_datatypes           , "template": tpl_implem_avx512["store"]  , "if": "!defined(MIPP_ALIGNED_LOADS)" } ] ,
    "storeu" : [
        { "instr_name" : "storeu"  , "datatypes": all_datatypes           , "template": tpl_implem_avx512["store"]  , "if": "defined(__AVX512F__)"} ]          ,
    "set0"   : [
        { "instr_name" : "setzero" , "datatypes": [all_float, all_int]    , "template": tpl_implem_avx512["set0"]       , "if": "defined(__AVX512F__)"} ]  ,
    "set1"   : [
        { "instr_name" : "set1"    , "datatypes": [all_float, all_int]    , "template": tpl_implem_avx512["set1"]       , "if": "defined(__AVX512F__)" } ] ,
    "low": [
        { "instr_name": "extractf64x4" , "datatypes": all_float+[int64 , int32 , int16 , int8_t] , "template": tpl_implem_avx512["low"] , "if": "defined(__AVX512F__)"  } ,
    "high": [
        { "instr_name": "extractf64x4" , "datatypes": all_float+[int64 , int32 , int16 , int8_t] , "template": tpl_implem_avx512["high"] , "if": "defined(__AVX512F__)"  } ,
    "sqrt": [
        { "instr_name": "sqrt", "datatypes": all_float, "template": tpl_implem_avx512["arith_1arg"], "if": "defined(__AVX512F__)"} ],
    "rsqrt": [
        { "instr_name": "rsqrt", "datatypes": [float32], "template": tpl_implem_avx512["arith_1arg"] } ],
    "sub": [
        { "instr_name": "sub", "datatypes": all_float, "template": tpl_implem_avx512["arith_2args"] },
        { "instr_name": "sub", "datatypes": [int64, int32], "template": tpl_implem_avx512["arith_2args"], "if": "defined(__AVX512F__)" },
        { "instr_name": "subs", "datatypes": [int16, int8], "template": tpl_implem_avx512["arith_2args"], "if": "defined(__AVX512BW__)" } ],
    "mul": [
        { "instr_name": "mul", "datatypes": all_float, "template": tpl_implem_avx512["arith_2args"] },
        { "instr_name": "mullo", "datatypes": [int32], "template": tpl_implem_avx512["arith_2args"] },
        { "instr_name": "mullo", "datatypes": [int16_t], "template": tpl_implem_avx512["arith_2args"], "if": "defined(__AVX512BW__)" }],
    "div": [
        { "instr_name": "div", "datatypes": all_float, "template": tpl_implem_avx512["arith_2args"], "if": "defined(__AVX512BW__)"} ],
    "min": [
        { "instr_name": "min", "datatypes": all_float+[int64 , int32], "template": tpl_implem_avx512["arith_2args"], "if": "defined(__AVX512F__)"},
        { "instr_name": "min", "datatypes": [int16, int8], "template": tpl_implem_avx512["arith_2args"], "if": "defined(__AVX512BW__)"  } ,
        { "instr_name": "gmin", "datatypes": all_float, "template": tpl_implem_avx512["arith_2args"], "if": "defined(__MIC__) || defined(__KNCNI__)" } ],
    "max": [
        { "instr_name": "max", "datatypes": all_float+[int64 , int32], "template": tpl_implem_avx512["arith_2args"], "if": "defined(__AVX512F__)"},
        { "instr_name": "max", "datatypes": [int16, int8], "template": tpl_implem_avx512["arith_2args"], "if": "defined(__AVX512BW__)"  } ,
        { "instr_name": "gmax", "datatypes": all_float, "template": tpl_implem_avx512["arith_2args"], "if": "defined(__MIC__) || defined(__KNCNI__)" } ],
    "fmadd": [
        { "instr_name": "fmadd", "datatypes": all_float, "template": tpl_implem_avx512["arith_3args"] },
        { "instr_name": "fmadd", "datatypes": int32_t, "template": tpl_implem_avx512["arith_3args"], "if": "defined(__MIC__) || defined(__KNCNI__)" } ],
    "fmsub": [
        { "instr_name": "fmsub", "datatypes": all_float, "template": tpl_implem_avx512["arith_3args"] } ],
    "andb": [
        { "instr_name": "and", "datatypes": [all_float, all_int] , "template": tpl_implem_avx512["logi_2args"] }],    
    "andb_k": [
        { "instr_name": "kand", "datatypes": [int8_t,int16_t] , "template": tpl_implem_avx512["andb_k"],  }],
    "andnb": [
        { "instr_name": "andnot", "datatypes":[all_float, all_int], "template": tpl_implem_avx512["logi_2args"] }],
    "andnb_k": [
        { "instr_name": "kand", "datatypes": [int8_t,int16_t] , "template": tpl_implem_avx512["andb_k"],  }],
    "xorb": [
        { "instr_name": "xor", "datatypes":[all_float, all_int], "template": tpl_implem_avx512["logi_2args"] }],
    "xorb_k": [
        { "instr_name": "kxor", "datatypes": [int8_t,int16_t] , "template": tpl_implem_avx512["xor_k"],  }],
    "orb": [
        { "instr_name": "or", "datatypes":[all_float, all_int], "template": tpl_implem_avx512["logi_2args"] }],
    "orb_k": [
        { "instr_name": "kor", "datatypes": [int8_t,int16_t] , "template": tpl_implem_avx512["orb_k"],  }],
    "cmpeq": [
        { "instr_name": "cmp", "datatypes": all_float, "template": tpl_implem_avx512["cmpeq_float"], },
        { "instr_name": "cmpeq", "datatypes": [int32_t,int64_t], "template": tpl_implem_avx512["cmp_int"], "if": "defined(__AVX512F__)" } ,
        { "instr_name": "cmpeq", "datatypes": [int16_t,int8_t], "template": tpl_implem_avx512["cmp_int"], "if": "defined(__AVX512BW__)" } ],
    "cmpneq": [
        { "instr_name": "cmp", "datatypes": all_float, "template": tpl_implem_avx512["cmpneq_float"], } ,
        { "instr_name": "cmpneq", "datatypes": [int32_t,int64_t], "template": tpl_implem_avx512["cmp_int"], "if": "defined(__AVX512F__)" } ,
        { "instr_name": "cmpneq", "datatypes": [int16_t,int8_t], "template": tpl_implem_avx512["cmp_int"], "if": "defined(__AVX512BW__)" } ],
    "blend": [
        { "instr_name": "blend", "datatypes": all_float+[int64 , int32], "template": tpl_implem_avx512["blend"],"if":"defined(__MIC__) || defined(__KNCNI__) || defined(__AVX512__) || defined(__AVX512F__)" },
        { "instr_name": "blend", "datatypes": [int8_t,int16_t] , "template": tpl_implem_avx512["blend"],  "if": "defined(__AVX512BW__)" } ],
    "hmul": [
        { "instr_name": "mul", "datatypes": [float64], "template": tpl_implem_avx512["reduce_64"],"if": "defined(__AVX512F__)", },
        { "instr_name": "mul", "datatypes": [float32], "template": tpl_implem_avx512["reduce_32"],"if": "defined(__AVX512F__)", },
        { "instr_name": "mullo", "datatypes": [int32], "template": tpl_implem_avx512["reduce_32"],"if": "defined(__AVX512F__)", },
        { "instr_name": "mullo", "datatypes": [int64], "template": tpl_implem_avx512["reduce_16"],"if": "defined(__AVX512F__)", }, ],
    "hmin": [
        { "instr_name": "min", "datatypes": [float64], "template": tpl_implem_avx512["reduce_64"],"if": "defined(__AVX512F__)", },
        { "instr_name": "min", "datatypes": [float32], "template": tpl_implem_avx512["reduce_32"],"if": "defined(__AVX512F__)", },
        { "instr_name": "gmin", "datatypes":[float64], "template": tpl_implem_avx512["reduce_64"],"if": "defined(__MIC__) || defined(__KNCNI__)" , },
        { "instr_name": "gmin", "datatypes":[float32], "template": tpl_implem_avx512["reduce_32"],"if": "defined(__MIC__) || defined(__KNCNI__)", },
        { "instr_name": "min", "datatypes": [int32], "template": tpl_implem_avx512["reduce_32"],"if": "defined(__AVX512F__)", },
        { "instr_name": "min", "datatypes": [int64], "template": tpl_implem_avx512["reduce_16"],"if": "defined(__AVX512F__)", }, 
        { "instr_name": "min", "datatypes": [int16], "template": tpl_implem_avx512["reduce_16"],"if": "defined(__AVX512BW__)" , }, 
        { "instr_name": "min", "datatypes": [int8], "template": tpl_implem_avx512["reduce_16"],"if": "defined(__AVX512BW__)", },],
    "hmax": [
        { "instr_name": "max", "datatypes": [float64], "template": tpl_implem_avx512["reduce_64"],"if": "defined(__AVX512F__)", },
        { "instr_name": "max", "datatypes": [float32], "template": tpl_implem_avx512["reduce_32"],"if": "defined(__AVX512F__)", },
        { "instr_name": "gmax","datatypes": [float64], "template": tpl_implem_avx512["reduce_64"],"if": "defined(__MIC__) || defined(__KNCNI__)" , },
        { "instr_name": "gmax","datatypes": [float32], "template": tpl_implem_avx512["reduce_32"],"if": "defined(__MIC__) || defined(__KNCNI__)", },
        { "instr_name": "max", "datatypes": [int32], "template": tpl_implem_avx512["reduce_32"],"if": "defined(__AVX512F__)", },
        { "instr_name": "max", "datatypes": [int64], "template": tpl_implem_avx512["reduce_16"],"if": "defined(__AVX512F__)", }, 
        { "instr_name": "max", "datatypes": [int16], "template": tpl_implem_avx512["reduce_16"],"if": "defined(__AVX512BW__)" , }, 
        { "instr_name": "max", "datatypes": [int8], "template": tpl_implem_avx512["reduce_16"],"if": "defined(__AVX512BW__)", },],
