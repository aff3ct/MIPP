from tools import *

"""isa_avx" dictionary:
	- Purpose: This dictionary defines architectural characteristics specific to the "AVX" architecture.
    - Content: It includes detailed information about data types, their properties, and other specific details relevant to the AVX architecture.
    - These details are essential for generating optimized SIMD instructions
"""

isa_avx = {
    "name": "avx",
    "prefix": "_mm256",
    "size": 256,
    "define": "defined(__AVX__)",
    "hw_lmul": False,
    "architecture": "x86",
    "datatypes": {
        float64: { "data_ext": "pd",    "data_ext_logi": "pd",    "data_ext_msk": "pd",    "reg": "__m256d", "msk": "__m256d", "to_ptr": "float64_t" },
        float32: { "data_ext": "ps",    "data_ext_logi": "ps",    "data_ext_msk": "ps",    "reg": " __m256", "msk": "__m256",  "to_ptr": "float32_t" },
        int64:   { "data_ext": "epi64", "data_ext_logi": "si256", "data_ext_msk": "si256", "reg": "__m256i", "msk": "__m256i", "to_ptr": "__m256i"   },
        int32:   { "data_ext": "epi32", "data_ext_logi": "si256", "data_ext_msk": "si256", "reg": "__m256i", "msk": "__m256i", "to_ptr": "__m256i"   },
        int16:   { "data_ext": "epi16", "data_ext_logi": "si256", "data_ext_msk": "si256", "reg": "__m256i", "msk": "__m256i", "to_ptr": "__m256i"   },
        int8:    { "data_ext": "epi8",  "data_ext_logi": "si256", "data_ext_msk": "si256", "reg": "__m256i", "msk": "__m256i", "to_ptr": "__m256i"   },
        uint64:  { "data_ext": "epu64", "data_ext_logi": "si256", "data_ext_msk": "si256", "reg": "__m256i", "msk": "__m256i", "to_ptr": "__m256i"   },
        uint32:  { "data_ext": "epu32", "data_ext_logi": "si256", "data_ext_msk": "si256", "reg": "__m256i", "msk": "__m256i", "to_ptr": "__m256i"   },
        uint16:  { "data_ext": "epu16", "data_ext_logi": "si256", "data_ext_msk": "si256", "reg": "__m256i", "msk": "__m256i", "to_ptr": "__m256i"   },
        uint8:   { "data_ext": "epu8",  "data_ext_logi": "si256", "data_ext_msk": "si256", "reg": "__m256i", "msk": "__m256i", "to_ptr": "__m256i"   },
    },
}

"""tpl_implem_avx dictionary:
    - Purpose: This dictionary contains implementation models for various functions.
    - Use: During the generation phase, this dictionary is used to select the appropriate implementation model for a specific function.
    - Content: The implementation models in this dictionary are adapted to the AVX architecture and define the structure and behavior of the generated SIMD code.
    - The notation convention involves using the letter "m" to designate masks, "r" for registers, "v" for values, and "p" for pointers.
"""
tpl_implem_avx = {
    "cast":           { "format": "short", "code": "{% if isa_dt_par.data_ext_logi != isa_dt_ret.data_ext_logi -%} {{ isa.prefix }}_{{ instr_name }}{{isa_dt_par.data_ext_logi}}_{{isa_dt_ret.data_ext_logi}}(r0.r);{% else -%} r0.r;{% endif %}"},
    "cast_k":         { "format": "short", "code": "{% if isa_dt_par.data_ext_logi != isa_dt_ret.data_ext_logi -%} {{ isa.prefix }}_{{ instr_name }}{{isa_dt_par.data_ext_logi}}_{{ isa_dt_ret.data_ext_logi}}(m0.m);{% else -%} m0.m;{% endif %}"},
    "toreg":          { "format": "short", "code": "{% if isa_dt_par.data_ext_logi != isa_dt_ret.data_ext_logi -%}{{ isa.prefix }}_{{ instr_name }}{{isa_dt_par.data_ext_logi}}_{{isa_dt_ret.data_ext_logi}}(m0.m);{% else -%} m0.m;{% endif %}" },
    "tomsk":          { "format": "short", "code": "{% if isa_dt_par.data_ext_logi != isa_dt_ret.data_ext_logi -%}{{ isa.prefix }}_{{ instr_name }}{{isa_dt_par.data_ext_logi}}_{{isa_dt_ret.data_ext_logi}}(r0.r);{% else -%} r0.r;{% endif %}" },
    "load":           { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext_logi }}(({{ isa_dt_par.to_ptr }}*) p0);" },
    "store":          { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext_logi }}(({{ isa_dt_par.to_ptr }}*) p0, r0.r);" },
    "set0":           { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext_logi }}();"},
    "set0_k":         { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext_msk }}();" },
    "set1":           { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(v0);"},
    "set1x":          { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}x(v0);" },
    "maskzld":		  { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(p0,m0.m);"},
    "maskst":		  { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(p0,m0.m, r0.r);"},
    "getfirst":       { "format": "long",  "code": "return ({{ cstdint_ret }}) {{ isa.prefix }}_{{ instr_name }}_epi{{ dt_par.n_bits }}(%cast<tp,c:int|b:tp>%(r0).r, 0);" },
#   "gather":         { "format": "short", "code": "{{ isa.prefix }}_i{{ dt_par.n_bits }}{{ instr_name }}_{{ isa_dt_par.data_ext }}(p0,vi,{{dt_par.n_bits//8}});" },
#   "mask_gather_64": { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(%set0<tp>%(),p0,vi,m0.m,8);" },
#   "mask_gather_32": { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(%set0<tp>%(),p0,vi,m0.m,4);" },
    "arith_1arg":     { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(r0.r);" },
    "arith_2args":    { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(r0.r, r1.r);" },
    "arithmsk_2args": { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(m0.m, r0.r, r1.r);" },
    "logi_2args":     { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext_logi }}(r0.r, r1.r);" },
    "logi_m_2args":   { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext_msk }}(m0.m, m1.m);" },
    "arith_3args":    { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(r0.r, r1.r, r2.r);" },
    "cmp_int":        { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(r0.r, r1.r);" },
    "blend_float":    { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(r1.r, r0.r, m0.m);"},
    "blend_int":      { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_epi8(r1.r, r0.r, m0.m);" },
    
    "round_float":    { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(r0.r,(_MM_FROUND_TO_NEAREST_INT |_MM_FROUND_NO_EXC));" },
    "round_int":      { "format": "short", "code": "r0.r;" },
    
    "testz_2args":    { "format": "long",  "code": "return {{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext_msk }}(m0.m, m1.m);" },
    "cmpeq_float":    { "format": "long", "code":
"""// long format
	%r<tp>% tmp;
	tmp.r = {{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(r0.r, r1.r, _CMP_EQ_OQ);
	return %tomsk<tp>%(tmp);""" },
    "cmpneq_float": { "format": "long", "code":
"""// long format
	%r<tp>% tmp;
	tmp.r = {{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(r0.r, r1.r, _CMP_NEQ_OQ);
	return %tomsk<tp>%(tmp);""" },
    "cmpgt_float":  { "format": "long", "code":
"""// long format
	%r<tp>% tmp;
	tmp.r = {{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(r0.r, r1.r, _CMP_GT_OS);
	return %tomsk<tp>%(tmp);""" },
    "cmpge_float":  { "format": "long", "code":
"""// long format
	%r<tp>% tmp;
	tmp.r = {{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(r0.r, r1.r, _CMP_GE_OS);
	return %tomsk<tp>%(tmp);""" },
    "cmple_float":  { "format": "long", "code":
"""// long format
	%r<tp>% tmp;
	tmp.r = {{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(r0.r, r1.r, _CMP_LE_OS);
	return %tomsk<tp>%(tmp);""" },
    "cmplt_float":  { "format": "long", "code":
"""// long format
	%r<tp>% tmp;
	tmp.r = {{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(r0.r, r1.r, _CMP_LT_OS);
	return %tomsk<tp>%(tmp);""" },
    "logi_2args_e": { "format": "long", "code":
"""// long format
	%r<c:float|b:32>% r0f = %cast<tp,c:float|b:32>%(r0);
	%r<c:float|b:32>% r1f = %cast<tp,c:float|b:32>%(r1);
	%r<c:float|b:32>% resf = %{{ instr_name }}<c:float|b:32>%(r0f, r1f);
	return %cast<c:float|b:32,tp>%(resf);""" },
    "logi_m_2args_e": { "format": "long", "code":
"""// long format
	%r<c:float|b:32>% r0f = %toreg<c:float|b:32>%(%cast_k<tp,c:float|b:32>%(m0));
	%r<c:float|b:32>% r1f = %toreg<c:float|b:32>%(%cast_k<tp,c:float|b:32>%(m1));
	%r<c:float|b:32>% resf = %{{ instr_name }}<c:float|b:32>%(r0f, r1f);
	return %tomsk<tp>%(%cast<c:float|b:32,tp>%(resf));""" },
    "reduce_64": { "format": "long", "code":
"""// long format
	%r<c:float|b:32>% rsf;
	rsf.r = _mm256_permute2f128_ps(%cast<tp,c:float|b:32>%(r0).r, %cast<tp,c:float|b:32>%(r0).r, _MM_SHUFFLE(0,0,0,1));
	%r<tp>% rs1 = %cast<c:float|b:32,tp>%(rsf);
	rs1.r = {{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(r0.r, rs1.r);
	rsf = %cast<tp,c:float|b:32>%(rs1);
	rsf.r = _mm256_shuffle_ps(rsf.r, rsf.r, _MM_SHUFFLE(1,0,3,2));
	%r<tp>% rs2 = %cast<c:float|b:32,tp>%(rsf);
	rs2.r = {{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(rs1.r, rs2.r);
	return rs2;""" },
    "reduce_32": { "format": "long", "code":
"""// long format
	%r<c:float|b:32>% rsf;
	rsf.r = _mm256_permute2f128_ps(%cast<tp,c:float|b:32>%(r0).r, %cast<tp,c:float|b:32>%(r0).r, _MM_SHUFFLE(0,0,0,1));
	%r<tp>% rs1 = %cast<c:float|b:32,tp>%(rsf);
	rs1.r = {{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(r0.r, rs1.r);
	rsf = %cast<tp,c:float|b:32>%(rs1);
	rsf.r = _mm256_shuffle_ps(rsf.r, rsf.r, _MM_SHUFFLE(1,0,3,2));
	%r<tp>% rs2 = %cast<c:float|b:32,tp>%(rsf);
	rs2.r = {{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(rs1.r, rs2.r);
	rsf = %cast<tp,c:float|b:32>%(rs2);
	rsf.r = _mm256_shuffle_ps(rsf.r, rsf.r, _MM_SHUFFLE(2,3,0,1));
	%r<tp>% rs3 = %cast<c:float|b:32,tp>%(rsf);
	rs3.r = {{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(rs2.r, rs3.r);
	return rs3;""" },
    "reduce_16": { "format": "long", "code":
"""// long format
	%r<c:float|b:32>% rsf;
	rsf.r = _mm256_permute2f128_ps(%cast<tp,c:float|b:32>%(r0).r, %cast<tp,c:float|b:32>%(r0).r, _MM_SHUFFLE(0,0,0,1));
	%r<tp>% rs1 = %cast<c:float|b:32,tp>%(rsf);
	rs1.r = {{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(r0.r, rs1.r);
	rsf = %cast<tp,c:float|b:32>%(rs1);
	rsf.r = _mm256_shuffle_ps(rsf.r, rsf.r, _MM_SHUFFLE(1,0,3,2));
	%r<tp>% rs2 = %cast<c:float|b:32,tp>%(rsf);
	rs2.r = {{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(rs1.r, rs2.r);
	rsf = %cast<tp,c:float|b:32>%(rs2);
	rsf.r = _mm256_shuffle_ps(rsf.r, rsf.r, _MM_SHUFFLE(2,3,0,1));
	%r<tp>% rs3 = %cast<c:float|b:32,tp>%(rsf);
	rs3.r = {{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(rs2.r, rs3.r);
	%r<c:int|b:8>% rsi = %cast<tp,c:int|b:8>%(rs3);
	__m256i mask_16 = _mm256_set_epi8(29,28,31,30,25,24,27,26,21,20,23,22,17,16,19,18,13,12,15,14,9,8,11,10,5,4,7,6,1,0,3,2);
	rsi.r = _mm256_shuffle_epi8(rsi.r, mask_16);
	%r<tp>% rs4 = %cast<c:int|b:8,tp>%(rsi);
	rs4.r = {{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(rs3.r, rs4.r);
	return rs4;""" },

    "reduce_8": { "format": "long", "code":
"""// long format
	%r<c:float|b:32>% rsf;
	rsf.r = _mm256_permute2f128_ps(%cast<tp,c:float|b:32>%(r0).r, %cast<tp,c:float|b:32>%(r0).r, _MM_SHUFFLE(0,0,0,1));
	%r<tp>% rs1 = %cast<c:float|b:32,tp>%(rsf);
	rs1.r = {{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(r0.r, rs1.r);
	rsf = %cast<tp,c:float|b:32>%(rs1);
	rsf.r = _mm256_shuffle_ps(rsf.r, rsf.r, _MM_SHUFFLE(1,0,3,2));
	%r<tp>% rs2 = %cast<c:float|b:32,tp>%(rsf);
	rs2.r = {{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(rs1.r, rs2.r);
	rsf = %cast<tp,c:float|b:32>%(rs2);
	rsf.r = _mm256_shuffle_ps(rsf.r, rsf.r, _MM_SHUFFLE(2,3,0,1));
	%r<tp>% rs3 = %cast<c:float|b:32,tp>%(rsf);
	rs3.r = {{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(rs2.r, rs3.r);
	%r<c:int|b:8>% rsi = %cast<tp,c:int|b:8>%(rs3);
	__m256i mask_16 = _mm256_set_epi8(29,28,31,30,25,24,27,26,21,20,23,22,17,16,19,18,13,12,15,14,9,8,11,10,5,4,7,6,1,0,3,2);
	rsi.r = _mm256_shuffle_epi8(rsi.r, mask_16);
	%r<tp>% rs4 = %cast<c:int|b:8,tp>%(rsi);
	rs4.r = {{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(rs3.r, rs4.r);
	rsi = %cast<tp,c:int|b:8>%(rs4);
	__m256i mask_8 = _mm256_set_epi8(30,31,28,29,26,27,24,25,22,23,20,21,18,19,16,17,14,15,12,13,10,11,8,9,6,7,4,5,2,3,0,1);
	rsi.r = _mm256_shuffle_epi8(rsi.r, mask_8);
	%r<tp>% rs5 = %cast<c:int|b:8,tp>%(rsi);
	rs5.r = {{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(rs4.r, rs5.r);
	return rs5;""" },
    "set1_u": { "format": "long", "code":
"""// long format
	%r<c:int|b:tp>% r0u;
	r0u = %set1<c:int|b:tp>%(v0);
	return %cast<c:int|b:tp,tp>%(r0u);"""},
    "arith_2args_u":  { "format": "long", "code":
"""// long format
	%r<c:int|b:tp>% r0u = %cast<tp,c:int|b:tp>%(r0);
	%r<c:int|b:tp>% r1u = %cast<tp,c:int|b:tp>%(r1);
	%r<c:int|b:tp>% res = %{{ instr_name }}<c:int|b:tp>%(r0u, r1u);
	return %cast<c:int|b:tp,tp>%(res);"""},
    "getfirst_float64": { "format": "long",  "code":
"""// long format
	__m128d low = _mm256_castpd256_pd128(r0.r);
	return _mm_cvtsd_f64(low);"""},
    "getfirst_float32": { "format": "long",  "code":
"""// long format
	__m128 low = _mm256_castps256_ps128(r0.r);
	return _mm_cvtss_f32(low);"""},
    "reduce_64_u": { "format": "long", "code":
"""// long format
	%r<c:float|b:32>% rsf;
	rsf.r = _mm256_permute2f128_ps(%cast<tp,c:float|b:32>%(r0).r, %cast<tp,c:float|b:32>%(r0).r, _MM_SHUFFLE(0,0,0,1));
	%r<tp>% rs1 = %cast<c:float|b:32,tp>%(rsf);
	rs1.r = {{ isa.prefix }}_{{ instr_name }}_epi64(r0.r, rs1.r);
	rsf = %cast<tp,c:float|b:32>%(rs1);
	rsf.r = _mm256_shuffle_ps(rsf.r, rsf.r, _MM_SHUFFLE(1,0,3,2));
	%r<tp>% rs2 = %cast<c:float|b:32,tp>%(rsf);
	rs2.r = {{ isa.prefix }}_{{ instr_name }}_epi64(rs1.r, rs2.r);
	return rs2;""" },
    "reduce_32_u": { "format": "long", "code":
"""// long format
	%r<c:float|b:32>% rsf;
	rsf.r = _mm256_permute2f128_ps(%cast<tp,c:float|b:32>%(r0).r, %cast<tp,c:float|b:32>%(r0).r, _MM_SHUFFLE(0,0,0,1));
	%r<tp>% rs1 = %cast<c:float|b:32,tp>%(rsf);
	rs1.r = {{ isa.prefix }}_{{ instr_name }}_epi32(r0.r, rs1.r);
	rsf = %cast<tp,c:float|b:32>%(rs1);
	rsf.r = _mm256_shuffle_ps(rsf.r, rsf.r, _MM_SHUFFLE(1,0,3,2));
	%r<tp>% rs2 = %cast<c:float|b:32,tp>%(rsf);
	rs2.r = {{ isa.prefix }}_{{ instr_name }}_epi32(rs1.r, rs2.r);
	rsf = %cast<tp,c:float|b:32>%(rs2);
	rsf.r = _mm256_shuffle_ps(rsf.r, rsf.r, _MM_SHUFFLE(2,3,0,1));
	%r<tp>% rs3 = %cast<c:float|b:32,tp>%(rsf);
	rs3.r = {{ isa.prefix }}_{{ instr_name }}_epi32(rs2.r, rs3.r);
	return rs3;""" },
	#_mm256_testz_ps / _mm256_testz_pd 
	#don't have the same behavior as _mm256_testz_si256.
	#I propose we do hacky casting to have a unified behavior.
    "testz_2argsf": { "format": "long", "code":
"""// long format
	%m<c:int|b:tp>% m0i = %cast_k<tp,c:int|b:tp>%(m0);
	%m<c:int|b:tp>% m1i = %cast_k<tp,c:int|b:tp>%(m1);	
	return _mm256_testz_si256(m0i.m, m1i.m);""" },

}

"""
"implems_avx" dictionary:
    - Purpose: This dictionary associates each function with its SIMD instruction name (as it appears in the official Intel Intrinsics guide), the data types for which the SIMD instruction should be generated, and the implementation template to be used for code generation.
    - Usage: It serves as a mapping between functions and the specific SIMD instructions and implementation templates required for each function.
    - Macros: Conditional preprocessor macros are used for certain functions to automatically adjust the generated code based on the hardware architecture capabilities and the compiler's supported instruction sets.
"""
implems_avx = {
    "cast": [
        { "instr_name": "cast",           "datatypes": all_datatypes_cart_prod,                     "template": tpl_implem_avx["cast"],                                                  } ], # cast
    "cast_k": [
        { "instr_name": "cast",           "datatypes": all_datatypes_cart_prod,                     "template": tpl_implem_avx["cast_k"],                                                } ], # cast_k
    "toreg": [
        { "instr_name": "cast",           "datatypes": all_datatypes,                               "template": tpl_implem_avx["toreg"],                                                 } ], # toreg
    "tomsk": [
        { "instr_name": "cast",           "datatypes": all_datatypes,                               "template": tpl_implem_avx["tomsk"],                                                 } ], # tomsk
    "load": [
        { "instr_name": "load",           "datatypes": all_datatypes,                               "template": tpl_implem_avx["load"],             "if": "defined(MIPP_ALIGNED_LOADS)"  },
        { "instr_name": "loadu",          "datatypes": all_datatypes,                               "template": tpl_implem_avx["load"],             "if": "!defined(MIPP_ALIGNED_LOADS)" } ], # load
    "loadu": [
        { "instr_name": "loadu",          "datatypes": all_datatypes,                               "template": tpl_implem_avx["load"],                                                  } ], # loadu
    "store": [
        { "instr_name": "store",          "datatypes": all_datatypes,                               "template": tpl_implem_avx["store"],            "if": "defined(MIPP_ALIGNED_LOADS)"  },
        { "instr_name": "storeu",         "datatypes": all_datatypes,                               "template": tpl_implem_avx["store"],            "if": "!defined(MIPP_ALIGNED_LOADS)" } ], # store
    "storeu": [
        { "instr_name": "storeu",         "datatypes": all_datatypes,                               "template": tpl_implem_avx["store"],                                                 } ], # storeu
    "set1": [
        { "instr_name": "set1",           "datatypes": all_float,                                   "template": tpl_implem_avx["set1"],                                                  },
        { "instr_name": "set1",           "datatypes": [int64],                                     "template": tpl_implem_avx["set1x"],                                                 },
        { "instr_name": "set1",           "datatypes": [int32, int16, int8],                        "template": tpl_implem_avx["set1"],                                                  },
        { "instr_name": "set1",           "datatypes": all_uint,                                    "template": tpl_implem_avx["set1_u"],                                                } ], # set1
    "maskzld":[
        { "instr_name": "maskload",       "datatypes": all_float,                                   "template": tpl_implem_avx["maskzld"],                                               },
        { "instr_name": "maskload",       "datatypes": [int32],                                     "template": tpl_implem_avx["maskzld"],          "if": "defined(__AVX2__)"            } ], # maskzld
    "maskst":[
        { "instr_name": "maskstore",      "datatypes": all_float,                                   "template": tpl_implem_avx["maskst"],                                                },
        { "instr_name": "maskstore",      "datatypes": [int32],                                     "template": tpl_implem_avx["maskst"],           "if": "defined(__AVX2__)"            } ], # maskst
    "set0": [
        { "instr_name": "setzero",        "datatypes": all_datatypes,                               "template": tpl_implem_avx["set0"],                                                  } ], # set0
    "set0_k": [
        { "instr_name": "setzero",        "datatypes": all_datatypes,                               "template": tpl_implem_avx["set0_k"],                                                } ], # set0_k
    "getfirst": [
        { "instr_name": "extract",        "datatypes": [int64, int32, uint64, uint32],              "template": tpl_implem_avx["getfirst"],                                              },
        { "instr_name": "extract",        "datatypes": [int16, int8, uint16, uint8],                "template": tpl_implem_avx["getfirst"],         "if": "defined(__AVX2__)"            },
        { "instr_name": "extract",        "datatypes": [float64],                                   "template": tpl_implem_avx["getfirst_float64"],                                      },
        { "instr_name": "extract",        "datatypes": [float32],                                   "template": tpl_implem_avx["getfirst_float32"],                                      } ], # getfirst
    "sqrt": [
        { "instr_name": "sqrt",           "datatypes": all_float,                                   "template": tpl_implem_avx["arith_1arg"],                                            } ], # sqrt
    "rsqrt": [
        { "instr_name": "rsqrt",          "datatypes": [float32],                                   "template": tpl_implem_avx["arith_1arg"],                                            } ], # rsqrt
    "add": [
        { "instr_name": "add",            "datatypes": all_float,                                   "template": tpl_implem_avx["arith_2args"],                                           },
        { "instr_name": "add",            "datatypes": [int64, int32],                              "template": tpl_implem_avx["arith_2args"],      "if": "defined(__AVX2__)"            },
        { "instr_name": "adds",           "datatypes": [int16, int8, uint16, uint8],                "template": tpl_implem_avx["arith_2args"],      "if": "defined(__AVX2__)"            },
        { "instr_name": "add",            "datatypes": [uint64, uint32],                            "template": tpl_implem_avx["arith_2args_u"],    "if": "defined(__AVX2__)"            } ], # add
    "sub": [
        { "instr_name": "sub",            "datatypes": all_float,                                   "template": tpl_implem_avx["arith_2args"],                                           },
        { "instr_name": "sub",            "datatypes": [int64, int32],                              "template": tpl_implem_avx["arith_2args"],      "if": "defined(__AVX2__)"            },
        { "instr_name": "subs",           "datatypes": [int16, int8, uint16, uint8],                "template": tpl_implem_avx["arith_2args"],      "if": "defined(__AVX2__)"            } ], # sub
    "mul": [
        { "instr_name": "mul",            "datatypes": all_float,                                   "template": tpl_implem_avx["arith_2args"],                                           },
        { "instr_name": "mullo",          "datatypes": [int32, int16],                              "template": tpl_implem_avx["arith_2args"],      "if": "defined(__AVX2__)"            } ], # mul
    "div": [
        { "instr_name": "div",            "datatypes": all_float,                                   "template": tpl_implem_avx["arith_2args"],                                           } ], # div
    "min": [
        { "instr_name": "min",            "datatypes": all_float,                                   "template": tpl_implem_avx["arith_2args"],                                           },
        { "instr_name": "min",            "datatypes": [int32, int16, int8, uint32, uint16, uint8], "template": tpl_implem_avx["arith_2args"],      "if": "defined(__AVX2__)"            } ], # min
    "max": [
        { "instr_name": "max",            "datatypes": all_float,                                   "template": tpl_implem_avx["arith_2args"],                                           },
        { "instr_name": "max",            "datatypes": [int32, int16, int8, uint32, uint16, uint8], "template": tpl_implem_avx["arith_2args"],      "if": "defined(__AVX2__)"            } ], # max
    "fmadd": [
        { "instr_name": "fmadd",          "datatypes": all_float,                                   "template": tpl_implem_avx["arith_3args"],      "if": "defined(__FMA__)"             } ], # fmadd
    
    "fnmadd": [
        { "instr_name": "fnmadd",         "datatypes": all_float,                                   "template": tpl_implem_avx["arith_3args"],      "if": "defined(__FMA__)"             } ], # fnmadd
    "fmsub": [
        { "instr_name": "fmsub",          "datatypes": all_float,                                   "template": tpl_implem_avx["arith_3args"],      "if": "defined(__FMA__)"             } ], # fmsub
    "fnmsub": [
        { "instr_name": "fnmsub",         "datatypes": all_float,                                   "template": tpl_implem_avx["arith_3args"],      "if": "defined(__FMA__)"             } ], # fnmsub
    "andb": [
        { "instr_name": "and",            "datatypes": all_float,                                   "template": tpl_implem_avx["logi_2args"],                                            },
        { "instr_name": "andb",           "datatypes": all_int_uint,                                "template": tpl_implem_avx["logi_2args_e"],     "if": "!defined(__AVX2__)"           },
        { "instr_name": "and",            "datatypes": all_int_uint,                                "template": tpl_implem_avx["logi_2args"],       "if": "defined(__AVX2__)"            } ], # andb
    "andb_k": [
        { "instr_name": "andb",           "datatypes": all_datatypes,                               "template": tpl_implem_avx["logi_m_2args_e"],   "if": "!defined(__AVX2__)"           },
        { "instr_name": "and",            "datatypes": all_datatypes,                               "template": tpl_implem_avx["logi_m_2args"],     "if": "defined(__AVX2__)"            } ], # andb_k
    "andnb": [
        { "instr_name": "andnot",         "datatypes": all_float,                                   "template": tpl_implem_avx["logi_2args"],                                            },
        { "instr_name": "andnb",          "datatypes": all_int_uint,                                "template": tpl_implem_avx["logi_2args_e"],     "if": "!defined(__AVX2__)"           },
        { "instr_name": "andnot",         "datatypes": all_int_uint,                                "template": tpl_implem_avx["logi_2args"],       "if": "defined(__AVX2__)"            } ], # andnb
    "andnb_k": [
        { "instr_name": "andnb",          "datatypes": all_datatypes,                               "template": tpl_implem_avx["logi_m_2args_e"],   "if": "!defined(__AVX2__)"           },
        { "instr_name": "andnot",         "datatypes": all_datatypes,                               "template": tpl_implem_avx["logi_m_2args"],     "if": "defined(__AVX2__)"            } ], # andnb_k
    "orb": [
        { "instr_name": "or",             "datatypes": all_float,                                   "template": tpl_implem_avx["logi_2args"],                                            },
        { "instr_name": "orb",            "datatypes": all_int_uint,                                "template": tpl_implem_avx["logi_2args_e"],     "if": "!defined(__AVX2__)"           },
        { "instr_name": "or",             "datatypes": all_int_uint,                                "template": tpl_implem_avx["logi_2args"],       "if": "defined(__AVX2__)"            } ], # orb
    "orb_k": [
        { "instr_name": "orb",            "datatypes": all_datatypes,                               "template": tpl_implem_avx["logi_m_2args_e"],   "if": "!defined(__AVX2__)"           },
        { "instr_name": "or",             "datatypes": all_datatypes,                               "template": tpl_implem_avx["logi_m_2args"],     "if": "defined(__AVX2__)"            } ], # orb_k
    "xorb": [
        { "instr_name": "xor",            "datatypes": all_float,                                   "template": tpl_implem_avx["logi_2args"],                                            },
        { "instr_name": "xorb",           "datatypes": all_int_uint,                                "template": tpl_implem_avx["logi_2args_e"],     "if": "!defined(__AVX2__)"           },
        { "instr_name": "xor",            "datatypes": all_int_uint,                                "template": tpl_implem_avx["logi_2args"],       "if": "defined(__AVX2__)"            } ], # xorb
    "xorb_k": [
        { "instr_name": "xorb",           "datatypes": all_datatypes,                               "template": tpl_implem_avx["logi_m_2args_e"],   "if": "!defined(__AVX2__)"           },
        { "instr_name": "xor",            "datatypes": all_datatypes,                               "template": tpl_implem_avx["logi_m_2args"],     "if": "defined(__AVX2__)"            } ], # xorb_k
    "cmpeq": [
        { "instr_name": "cmp",            "datatypes": all_float,                                   "template": tpl_implem_avx["cmpeq_float"],                                           },
        { "instr_name": "cmpeq",          "datatypes": all_int,                                     "template": tpl_implem_avx["cmp_int"],          "if": "defined(__AVX2__)"            } ], # cmpeq
    "cmpneq": [
        { "instr_name": "cmp",            "datatypes": all_float,                                   "template": tpl_implem_avx["cmpneq_float"],                                          } ], # cmpneq
    "cmplt": [
        { "instr_name": "cmp",            "datatypes": all_float,                                   "template": tpl_implem_avx["cmplt_float"],                                           } ], # cmplt
    "cmple": [
        { "instr_name": "cmp",            "datatypes": all_float,                                   "template": tpl_implem_avx["cmple_float"],                                           } ], # cmple
    "cmpge": [
        { "instr_name": "cmp",            "datatypes": all_float,                                   "template": tpl_implem_avx["cmpge_float"],                                           } ], # cmpge
    "cmpgt": [
        { "instr_name": "cmp",            "datatypes": all_float,                                   "template": tpl_implem_avx["cmpgt_float"],                                           },
        { "instr_name": "cmpgt",          "datatypes": all_int,                                     "template": tpl_implem_avx["cmp_int"],          "if": "defined(__AVX2__)"            } ], # cmpgt
    "blend": [
        { "instr_name": "blendv",         "datatypes": all_float,                                   "template": tpl_implem_avx["blend_float"],                                           },
        { "instr_name": "blendv",         "datatypes": all_int_uint,                                "template": tpl_implem_avx["blend_int"],        "if": "defined(__AVX2__)"            } ], # blend
    "testz": [
        { "instr_name": "testz",          "datatypes": all_int_uint,                                "template": tpl_implem_avx["testz_2args"],                                           },
        { "instr_name": "testz",          "datatypes": all_float,                                   "template": tpl_implem_avx["testz_2argsf"],                                          } ], # testz
    "hadd": [
        { "instr_name": "add",            "datatypes": [float64],                                   "template": tpl_implem_avx["reduce_64"],                                             },
        { "instr_name": "add",            "datatypes": [int64],                                     "template": tpl_implem_avx["reduce_64"],        "if": "defined(__AVX2__)"            },
        { "instr_name": "add",            "datatypes": [float32],                                   "template": tpl_implem_avx["reduce_32"],                                             },
        { "instr_name": "add",            "datatypes": [int32],                                     "template": tpl_implem_avx["reduce_32"],        "if": "defined(__AVX2__)"            },
        { "instr_name": "add",            "datatypes": [int16],                                     "template": tpl_implem_avx["reduce_16"],        "if": "defined(__AVX2__)"            },
        { "instr_name": "adds",           "datatypes": [uint16],                                    "template": tpl_implem_avx["reduce_16"],        "if": "defined(__AVX2__)"            },
        { "instr_name": "add",            "datatypes": [int8],                                      "template": tpl_implem_avx["reduce_8"],         "if": "defined(__AVX2__)"            },

        { "instr_name": "adds",           "datatypes": [uint8],                                     "template": tpl_implem_avx["reduce_8"],         "if": "defined(__AVX2__)"            },
        { "instr_name": "add",            "datatypes": [uint64],                                    "template": tpl_implem_avx["reduce_64_u"],      "if": "defined(__AVX2__)"            },
        { "instr_name": "add",            "datatypes": [uint32],                                    "template": tpl_implem_avx["reduce_32_u"],      "if": "defined(__AVX2__)"            } ], # hadd
    "hmul": [
        { "instr_name": "mul",            "datatypes": [float64],                                   "template": tpl_implem_avx["reduce_64"],                                             },
        { "instr_name": "mul",            "datatypes": [float32],                                   "template": tpl_implem_avx["reduce_32"],                                             },
        { "instr_name": "mullo",          "datatypes": [int32],                                     "template": tpl_implem_avx["reduce_32"],        "if": "defined(__AVX2__)"            },
        { "instr_name": "mullo",          "datatypes": [int16],                                     "template": tpl_implem_avx["reduce_16"],        "if": "defined(__AVX2__)"            } ], # hmul
    "hmin": [
        { "instr_name": "min",            "datatypes": [float64],                                   "template": tpl_implem_avx["reduce_64"],                                             },
        { "instr_name": "min",            "datatypes": [float32],                                   "template": tpl_implem_avx["reduce_32"],                                             },
        { "instr_name": "min",            "datatypes": [int32, uint32],                             "template": tpl_implem_avx["reduce_32"],        "if": "defined(__AVX2__)"            },
        { "instr_name": "min",            "datatypes": [int16, uint16],                             "template": tpl_implem_avx["reduce_16"],        "if": "defined(__AVX2__)"            },
        { "instr_name": "min",            "datatypes": [int8, uint8],                               "template": tpl_implem_avx["reduce_8"],         "if": "defined(__AVX2__)"            } ], # hmin
    "hmax": [
        { "instr_name": "max",            "datatypes": [float64],                                   "template": tpl_implem_avx["reduce_64"],                                             },
        { "instr_name": "max",            "datatypes": [float32],                                   "template": tpl_implem_avx["reduce_32"],                                             },
        { "instr_name": "max",            "datatypes": [int32, uint32],                             "template": tpl_implem_avx["reduce_32"],        "if": "defined(__AVX2__)"            },
        { "instr_name": "max",            "datatypes": [int16, uint16],                             "template": tpl_implem_avx["reduce_16"],        "if": "defined(__AVX2__)"            },
        { "instr_name": "max",            "datatypes": [int8, uint8],                               "template": tpl_implem_avx["reduce_8"],         "if": "defined(__AVX2__)"            } ], # hmax
    "round" : [
        { "instr_name": "round",          "datatypes": all_float,                                   "template": tpl_implem_avx["round_float"],                                                 },
        { "instr_name" : "",              "datatypes": all_int_uint,                                "template": tpl_implem_avx["round_int"]                                         }], # round
#   "gather": [
#       { "instr_name": "gather",         "datatypes": [float64, float32, int64, int32],            "template": tpl_implem_avx["gather"],           "if": "defined(__AVX2__)"            } ], # gather
#   "mask_gather": [
#       { "instr_name": "mask_i64gather", "datatypes": [float64, int64],                            "template": tpl_implem_avx["mask_gather_64"],   "if": "defined(__AVX2__)"            },
#       { "instr_name": "mask_i32gather", "datatypes": [float32, int32],                            "template": tpl_implem_avx["mask_gather_32"],   "if": "defined(__AVX2__)"            } ], # mask_gather
}
