from tools import *

"""
"isa_sse" dictionary:
    - Purpose: This dictionary defines architectural characteristics specific to the "AVX" architecture.
    - Content: It includes detailed information about data types, their properties, and other specific details relevant to the AVX architecture.
    - These details are essential for generating optimized SIMD instructions
"""
isa_sse = {
    "name": "sse",
    "prefix": "_mm",
    "size": 128,
    "define": "defined(__SSE__)",
    "architecture": "x86",
    "hw_lmul": False,
    "datatypes": {
        float64: { "data_ext": "pd",    "data_ext_logi": "pd",    "data_ext_msk": "pd",    "reg": "__m128d", "msk": "__m128d", "to_ptr": "float64_t" },
        float32: { "data_ext": "ps",    "data_ext_logi": "ps",    "data_ext_msk": "ps",    "reg": "__m128",  "msk": "__m128",  "to_ptr": "float32_t" },
        int64:   { "data_ext": "epi64", "data_ext_logi": "si128", "data_ext_msk": "si128", "reg": "__m128i", "msk": "__m128i", "to_ptr": "__m128i"   },
        int32:   { "data_ext": "epi32", "data_ext_logi": "si128", "data_ext_msk": "si128", "reg": "__m128i", "msk": "__m128i", "to_ptr": "__m128i"   },
        int16:   { "data_ext": "epi16", "data_ext_logi": "si128", "data_ext_msk": "si128", "reg": "__m128i", "msk": "__m128i", "to_ptr": "__m128i"   },
        int8:    { "data_ext": "epi8",  "data_ext_logi": "si128", "data_ext_msk": "si128", "reg": "__m128i", "msk": "__m128i", "to_ptr": "__m128i"   },
        uint64:  { "data_ext": "epu64", "data_ext_logi": "si128", "data_ext_msk": "si128", "reg": "__m128i", "msk": "__m128i", "to_ptr": "__m128i"   },
        uint32:  { "data_ext": "epu32", "data_ext_logi": "si128", "data_ext_msk": "si128", "reg": "__m128i", "msk": "__m128i", "to_ptr": "__m128i"   },
        uint16:  { "data_ext": "epu16", "data_ext_logi": "si128", "data_ext_msk": "si128", "reg": "__m128i", "msk": "__m128i", "to_ptr": "__m128i"   },
        uint8:   { "data_ext": "epu8",  "data_ext_logi": "si128", "data_ext_msk": "si128", "reg": "__m128i", "msk": "__m128i", "to_ptr": "__m128i"   },
    },
}

"""
"tpl_implem_avx" dictionary:
    - Purpose: This dictionary contains implementation models for various functions.
    - Use: During the generation phase, this dictionary is used to select the appropriate implementation model for a specific function.
    - Content: The implementation models in this dictionary are adapted to the AVX architecture and define the structure and behavior of the generated SIMD code.
    - The notation convention involves using the letter "m" to designate masks, "r" for registers, "v" for values, and "p" for pointers.
"""
tpl_implem_sse = {
    "cast":               { "format": "short", "code": "{% if isa_dt_par.data_ext_logi != isa_dt_ret.data_ext_logi -%}{{ isa.prefix }}_{{ instr_name }}{{ isa_dt_par.data_ext_logi }}_{{ isa_dt_ret.data_ext_logi }}(r0.r);{% else -%} r0.r;{% endif %}" },
    "cast_k":             { "format": "short", "code": "{% if isa_dt_par.data_ext_logi != isa_dt_ret.data_ext_logi -%}{{ isa.prefix }}_{{ instr_name }}{{ isa_dt_par.data_ext_logi }}_{{ isa_dt_ret.data_ext_logi }}(m0.m);{% else -%} m0.m;{% endif %}" },
    "toreg":              { "format": "short", "code": "{% if isa_dt_par.data_ext_logi != isa_dt_ret.data_ext_logi -%}{{ isa.prefix }}_{{ instr_name }}{{ isa_dt_par.data_ext_logi }}_{{ isa_dt_ret.data_ext_logi }}(m0.m);{% else -%} m0.m;{% endif %}" },
    "tomsk":              { "format": "short", "code": "{% if isa_dt_par.data_ext_logi != isa_dt_ret.data_ext_logi -%}{{ isa.prefix }}_{{ instr_name }}{{ isa_dt_par.data_ext_logi }}_{{ isa_dt_ret.data_ext_logi }}(r0.r);{% else -%} r0.r;{% endif %}" },
    "load":               { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext_logi }}(({{ isa_dt_par.to_ptr }}*) p0);" },
    "store":              { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext_logi }}(({{ isa_dt_par.to_ptr }}*) p0, r0.r);" },
    "set0":               { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext_logi }}();"},
    "set0_si128":         { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_si128();"},
    "set0_k":             { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext_msk }}();" },
    "set1":               { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(v0);"},
    "set1x":              { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}x(v0);" },
    "maskzld":            { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(p0,m0.m);"},
    "maskst":             { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(p0,m0.m, r0.r);"},
    "gather":             { "format": "short", "code": "{{ isa.prefix }}_i{{ dt_par.n_bits }}{{ instr_name }}_{{ isa_dt_par.data_ext }}(p0,vi,{{dt_par.n_bits//8}});" },
    "mask_gather_64":     { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(%set0<tp>%(),p0,vi,m0.m,8);" },
    "mask_gather_32":     { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(%set0<tp>%(),p0,vi,m0.m,4);" },
    "arith_1arg":         { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(r0.r);" },
    "arith_2args":        { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(r0.r, r1.r);" },
    "arithmsk_2args":     { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(m0.m, r0.r, r1.r);" },
    "logi_2args":         { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext_logi }}(r0.r, r1.r);" },
    "logi_2args_si128":   { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_si128(r0.r, r1.r);" },
    "logi_m_2args":       { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext_msk }}(m0.m, m1.m);" },
    "logi_m_2args_si128": { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_si128(m0.m, m1.m);" },
    "compare":            { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(r0.r, r1.r);" },
    "arith_3args":        { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(r0.r, r1.r, r2.r);" },
    "cmp_int":            { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(r0.r, r1.r);" },
    "blend_float":        { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(r0.r, r1.r, m0.m);"},
    "blend_int":          { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_epi8(r0.r, r1.r, m0.m);" },
    "getfirst":           { "format": "long",  "code": "\treturn ({{ cstdint_ret }}) {{ isa.prefix }}_{{ instr_name }}_epi{{ dt_par.n_bits }}(%cast<tp,c:int|b:tp>%(r0).r, 0);" },
    "testz_2args":        { "format": "long",  "code": "\treturn {{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext_msk }}(m0.m, m1.m);" },
    "set-64f":            { "format": "short", "code": "_mm_set_pd(vals[1], vals[0]);" },
    "set-32f":            { "format": "short", "code": "_mm_set_ps(vals[3], vals[2], vals[1], vals[0]);" },
    "set-64":             { "format": "short", "code": "_mm_set_epi64x(vals[1], vals[0]);" },
    "set-32":             { "format": "short", "code": "_mm_set_epi32(vals[3], vals[2], vals[1], vals[0]);" },
    "set-16":             { "format": "short", "code": """_mm_set_epi16(
		vals[ 7], vals[ 6], vals[ 5], vals[ 4],
		vals[ 3], vals[ 2], vals[ 1], vals[ 0]);""" },
    "set-8": { "format": "short", "code": """_mm_set_epi8(
		(int8_t)vals[15], (int8_t)vals[14], (int8_t)vals[13], (int8_t)vals[12],
		(int8_t)vals[11], (int8_t)vals[10], (int8_t)vals[ 9], (int8_t)vals[ 8],
		(int8_t)vals[ 7], (int8_t)vals[ 6], (int8_t)vals[ 5], (int8_t)vals[ 4],
		(int8_t)vals[ 3], (int8_t)vals[ 2], (int8_t)vals[ 1], (int8_t)vals[ 0]);""" },
    "cmpeq_float": { "format": "long", "code":
"""// long format
	%r<tp>% tmp;
	tmp.r = {{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(r0.r, r1.r, _CMP_EQ_OQ);
	return %tomsk<tp>%(tmp);""" },
    "cmpneq_float": { "format": "long", "code":
"""// long format
	%r<tp>% tmp;
	tmp.r = {{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(r0.r, r1.r, _CMP_NEQ_OQ);
	return %tomsk<tp>%(tmp);""" },
    "cmpgt_float": { "format": "long", "code":
"""// long format
	%r<tp>% tmp;
	tmp.r = {{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(r0.r, r1.r, _CMP_GT_OS);
	return %tomsk<tp>%(tmp);""" },
    "cmpge_float": { "format": "long", "code":
"""// long format
	%r<tp>% tmp;
	tmp.r = {{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(r0.r, r1.r, _CMP_GE_OS);
	return %tomsk<tp>%(tmp);""" },
    "cmple_float": { "format": "long", "code":
"""// long format
	%r<tp>% tmp;
	tmp.r = {{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(r0.r, r1.r, _CMP_LE_OS);
	return %tomsk<tp>%(tmp);""" },
    "cmplt_float": { "format": "long", "code":
"""// long format
	%r<tp>% tmp;
	tmp.r = {{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(r0.r, r1.r, _CMP_LT_OS);
	return %tomsk<tp>%(tmp);""" },
    "logi_2args_e": { "format": "long", "code":
"""// long format
	%r<c:float|b:32>% r0f = %cast<tp,c:float|b:32>%(r0);
	%r<c:float|b:32>% r1f = %cast<tp,c:float|b:32>%(r1);
	%r<c:float|b:32>% resf = %{{ instr_name }}<c:float|b:32>%(r0f, r1f);
	return %cast<c:float|b:32,tp>%(resf);"""
	},
    "logi_m_2args_e": { "format": "long", "code":
"""// long format
	%r<c:float|b:32>% r0f = %toreg<c:float|b:32>%(%cast_k<tp,c:float|b:32>%(m0));
	%r<c:float|b:32>% r1f = %toreg<c:float|b:32>%(%cast_k<tp,c:float|b:32>%(m1));
	%r<c:float|b:32>% resf = %{{ instr_name }}<c:float|b:32>%(r0f, r1f);
	return %tomsk<tp>%(%cast<c:float|b:32,tp>%(resf));"""
	},
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
    "arith_2args_u":  { "format": "long", "code":
"""// long format
	%r<c:int|b:tp>% r0u = %cast<tp,c:int|b:tp>%(r0);
	%r<c:int|b:tp>% r1u = %cast<tp,c:int|b:tp>%(r1);
	%r<c:int|b:tp>% res = %{{ instr_name }}<c:int|b:tp>%(r0u, r1u);
	return %cast<c:int|b:tp,tp>%(res);"""},
    "set1_u": { "format": "long", "code":
"""// long format
	%r<c:int|b:tp>% r0u;
	r0u = %set1<c:int|b:tp>%((int{{ dt_par.n_bits }}_t)v0);
	return %cast<c:int|b:tp,tp>%(r0u);"""},
}

"""
"implems_avx" dictionary:
    - Purpose: This dictionary associates each function with its SIMD instruction name (as it appears in the official Intel Intrinsics guide), the data types for which the SIMD instruction should be generated, and the implementation template to be used for code generation.
    - Usage: It serves as a mapping between functions and the specific SIMD instructions and implementation templates required for each function.
    - Macros: Conditional preprocessor macros are used for certain functions to automatically adjust the generated code based on the hardware architecture capabilities and the compiler's supported instruction sets.
"""
implems_sse = {
    "cast": [
        { "instr_name": "cast",    "datatypes": all_datatypes_cart_prod,    "template": tpl_implem_sse["cast"]                                                                         } ], # cast
    "cast_k": [
        { "instr_name": "cast",    "datatypes": all_datatypes_cart_prod,    "template": tpl_implem_sse["cast_k"]                                                                       } ], # cast_k
    "toreg": [
        { "instr_name": "cast",    "datatypes": all_datatypes,              "template": tpl_implem_sse["toreg"]                                                                        } ], # toreg
    "tomsk": [
        { "instr_name": "cast",    "datatypes": all_datatypes,              "template": tpl_implem_sse["tomsk"]                                                                        } ], # tomsk
    "load": [
        { "instr_name": "load",    "datatypes": all_int + [float32],        "template": tpl_implem_sse["load"],               "if": "defined(MIPP_ALIGNED_LOADS)"                      },
        { "instr_name": "load",    "datatypes": [float64],                  "template": tpl_implem_sse["load"],               "if": "defined(MIPP_ALIGNED_LOADS) && defined(__SSE2__)" },
        { "instr_name": "loadu",   "datatypes": all_datatypes,              "template": tpl_implem_sse["load"],               "if": "!defined(MIPP_ALIGNED_LOADS)"                     } ], # load
    "loadu": [
        { "instr_name": "loadu",   "datatypes": all_datatypes,              "template": tpl_implem_sse["load"]                                                                         } ], # loadu
    "store": [
        { "instr_name": "store",   "datatypes": all_datatypes,              "template": tpl_implem_sse["store"],              "if": "defined(MIPP_ALIGNED_LOADS)"                      },
        { "instr_name": "storeu",  "datatypes": all_datatypes,              "template": tpl_implem_sse["store"],              "if": "!defined(MIPP_ALIGNED_LOADS)"                     } ], # store
    "storeu": [
        { "instr_name": "storeu",  "datatypes": all_datatypes,              "template": tpl_implem_sse["store"]                                                                        } ], # storeu
    "set1": [
        { "instr_name": "set1",    "datatypes": [float32],                  "template": tpl_implem_sse["set1"]                                                                         },
        { "instr_name": "set1",    "datatypes": [float64],                  "template": tpl_implem_sse["set1"],               "if": "defined(__SSE2__)"                                },
        { "instr_name": "set1",    "datatypes": [int8,int16,int32],         "template": tpl_implem_sse["set1"],               "if": "defined(__SSE2__)"                                },
        { "instr_name": "set1",    "datatypes": [int64],                    "template": tpl_implem_sse["set1x"],              "if": "defined(__SSE2__)"                                },
        { "instr_name": "set1",    "datatypes": all_uint,                   "template": tpl_implem_sse["set1_u"],             "if": "defined(__SSE2__)"                                } ], # set1
    "set0": [
        { "instr_name": "setzero", "datatypes": [float32],                  "template": tpl_implem_sse["set0"],               "if": "defined(__SSE2__)"                                },
        { "instr_name": "setzero", "datatypes": all_int,                    "template": tpl_implem_sse["set0_si128"]                                                                   } ], # set0
    "set0_k": [
        { "instr_name": "setzero", "datatypes": all_datatypes,              "template": tpl_implem_sse["set0_k"]                                                                       } ], # set0_k
    "set": [
        {                          "datatypes": [float64],                  "template": tpl_implem_sse["set-64f"],            "if": "defined(__SSE2__)"                                },
        {                          "datatypes": [float32],                  "template": tpl_implem_sse["set-32f"],                                                                     },
        {                          "datatypes": [int32, uint32],            "template": tpl_implem_sse["set-32"],             "if": "defined(__SSE2__)"                                },
        {                          "datatypes": [int64, uint64],            "template": tpl_implem_sse["set-64"],             "if": "defined(__SSE2__)"                                },
        {                          "datatypes": [int16, uint16],            "template": tpl_implem_sse["set-16"],             "if": "defined(__SSE2__)"                                },
        {                          "datatypes": [int8, uint8],              "template": tpl_implem_sse["set-8"],              "if": "defined(__SSE2__)"                                } ], # set
    "add": [
        { "instr_name": "add",     "datatypes": [float32],                  "template": tpl_implem_sse["arith_2args"]                                                                  },
        { "instr_name": "add",     "datatypes": all_int + [float64],        "template": tpl_implem_sse["arith_2args"],        "if": "defined(__SSE2__)"                                },
        { "instr_name": "add",     "datatypes": all_uint,                   "template": tpl_implem_sse["arith_2args_u"],      "if": "defined(__SSE2__)"                                } ], # add
    "sub": [
        { "instr_name": "sub",     "datatypes": [float32],                  "template": tpl_implem_sse["arith_2args"]                                                                  },
        { "instr_name": "sub",     "datatypes": all_int + [float64],        "template": tpl_implem_sse["arith_2args"],        "if": "defined(__SSE2__)"                                },
        { "instr_name": "sub",     "datatypes": all_uint,                   "template": tpl_implem_sse["arith_2args_u"],      "if": "defined(__SSE2__)"                                } ], # sub
    "mul": [
        { "instr_name": "mul",     "datatypes": [float32],                  "template": tpl_implem_sse["arith_2args"]                                                                  },
        { "instr_name": "mul",     "datatypes": [float64],                  "template": tpl_implem_sse["arith_2args"],        "if": "defined(__SSE2__)"                                },
        { "instr_name": "mullo",   "datatypes": [int16],                    "template": tpl_implem_sse["arith_2args"],        "if": "defined(__SSE2__)"                                },
        { "instr_name": "mullo",   "datatypes": [int32],                    "template": tpl_implem_sse["arith_2args"],        "if": "defined(__SSE4_1__)"                              } ], # mul
    "div": [
        { "instr_name": "div",     "datatypes": [float32],                  "template": tpl_implem_sse["arith_2args"]                                                                  },
        { "instr_name": "div",     "datatypes": [float64],                  "template": tpl_implem_sse["arith_2args"],        "if": "defined(__SSE2__)"                                } ], # div
    "andb": [
        { "instr_name": "and",     "datatypes": [float32],                  "template": tpl_implem_sse["logi_2args"]                                                                   },
        { "instr_name": "and",     "datatypes": [float64],                  "template": tpl_implem_sse["logi_2args"],         "if": "defined(__SSE2__)"                                },
        { "instr_name": "and",     "datatypes": all_int_uint,               "template": tpl_implem_sse["logi_2args_si128"],   "if": "defined(__SSE2__)"                                } ], # andb
    "andb_k": [
        { "instr_name": "and",     "datatypes": [float32],                  "template": tpl_implem_sse["logi_m_2args"]                                                                 },
        { "instr_name": "and",     "datatypes": [float64],                  "template": tpl_implem_sse["logi_m_2args"],       "if": "defined(__SSE2__)"                                },
        { "instr_name": "and",     "datatypes": all_int_uint,               "template": tpl_implem_sse["logi_m_2args_si128"], "if": "defined(__SSE2__)"                                } ], # andb_k
    "andnb": [
        { "instr_name": "andnot",  "datatypes": [float32],                  "template": tpl_implem_sse["logi_2args"]                                                                   },
        { "instr_name": "andnot",  "datatypes": [float64],                  "template": tpl_implem_sse["logi_2args"],         "if": "defined(__SSE2__)"                                },
        { "instr_name": "andnot",  "datatypes": all_int_uint,               "template": tpl_implem_sse["logi_2args_si128"],   "if": "defined(__SSE2__)"                                } ], # andnb
    "andnb_k": [
        { "instr_name": "andnot",  "datatypes": [float32],                  "template": tpl_implem_sse["logi_m_2args"]                                                                 },
        { "instr_name": "andnot",  "datatypes": [float64],                  "template": tpl_implem_sse["logi_m_2args"],       "if": "defined(__SSE2__)"                                },
        { "instr_name": "andnot",  "datatypes": all_int_uint,               "template": tpl_implem_sse["logi_m_2args_si128"], "if": "defined(__SSE2__)"                                } ], # andnb_k
    "orb": [
        { "instr_name": "or",      "datatypes": [float32],                  "template": tpl_implem_sse["logi_2args"]                                                                   },
        { "instr_name": "or",      "datatypes": [float64],                  "template": tpl_implem_sse["logi_2args"],         "if": "defined(__SSE2__)"                                },
        { "instr_name": "or",      "datatypes": all_int_uint,               "template": tpl_implem_sse["logi_2args_si128"],   "if": "defined(__SSE2__)"                                } ], # orb
    "orb_k": [
        { "instr_name": "or",      "datatypes": [float32],                  "template": tpl_implem_sse["logi_m_2args"]                                                                 },
        { "instr_name": "or",      "datatypes": [float64],                  "template": tpl_implem_sse["logi_m_2args"],       "if": "defined(__SSE2__)"                                },
        { "instr_name": "or",      "datatypes": all_int_uint,               "template": tpl_implem_sse["logi_m_2args_si128"], "if": "defined(__SSE2__)"                                } ], # orb_k
    "xorb": [
        { "instr_name": "xor",     "datatypes": [float32],                  "template": tpl_implem_sse["logi_2args"]                                                                   },
        { "instr_name": "xor",     "datatypes": [float64],                  "template": tpl_implem_sse["logi_2args"],         "if": "defined(__SSE2__)"                                },
        { "instr_name": "xor",     "datatypes": all_int_uint,               "template": tpl_implem_sse["logi_2args_si128"],   "if": "defined(__SSE2__)"                                } ], # xorb
    "xorb_k": [
        { "instr_name": "xor",     "datatypes": [float32],                  "template": tpl_implem_sse["logi_m_2args"]                                                                 },
        { "instr_name": "xor",     "datatypes": [float64],                  "template": tpl_implem_sse["logi_m_2args"],       "if": "defined(__SSE2__)"                                },
        { "instr_name": "xor",     "datatypes": all_int_uint,               "template": tpl_implem_sse["logi_m_2args_si128"], "if": "defined(__SSE2__)"                                } ], # xorb_k
    "cmpeq": [
        { "instr_name": "cmpeq",   "datatypes": [float32],                  "template": tpl_implem_sse["compare"]                                                                      },
        { "instr_name": "cmpeq",   "datatypes": [float64,int16,int32,int8], "template": tpl_implem_sse["compare"],            "if": "defined(__SSE2__)"                                },
        { "instr_name": "cmpeq",   "datatypes": [int64],                    "template": tpl_implem_sse["compare"],            "if": "defined(__SSE4_1__)"                              } ], # cmpeq
    "cmpneq": [
        { "instr_name": "cmpneq",  "datatypes": [float32],                  "template": tpl_implem_sse["compare"]                                                                      } ], # cmpneq
#       { "instr_name": "cmpneq",  "datatypes": [float64],                  "template": tpl_implem_sse["compare"],            "if": "defined(__SSE2__)"                                } ],
#       COMMENT: add all int combinate not and equals for __SSE2__
#       { "instr_name": "cmpneq",  "datatypes": all_int,                    "template": tpl_implem_sse["not_cmpneq"],         "if": "defined(__SSE2__)"                                },
#       { "instr_name": "cmpneq",  "datatypes": [int64],                    "template": tpl_implem_sse["compare"],            "if": "defined(__SSE4_1__)"                              } ],
    "cmplt": [
        { "instr_name": "cmplt",   "datatypes": [float32],                  "template": tpl_implem_sse["compare"]                                                                      },
        { "instr_name": "cmplt",   "datatypes": [int16,int32,float64],      "template": tpl_implem_sse["compare"],            "if": "defined(__SSE2__)"                                } ], # cmplt
    "cmpgt": [
        { "instr_name": "cmpgt",   "datatypes": [float32],                  "template": tpl_implem_sse["compare"]                                                                      },
        { "instr_name": "cmpgt",   "datatypes": [float64],                  "template": tpl_implem_sse["compare"],            "if": "defined(__SSE2__)"                                },
        { "instr_name": "cmpgt",   "datatypes": [int64],                    "template": tpl_implem_sse["compare"],            "if": "defined(__SSE4_2__)"                              },
        { "instr_name": "cmpgt",   "datatypes": [int32,int16,int8],         "template": tpl_implem_sse["compare"],            "if": "defined(__SSE2__)"                                } ], # cmpgt
    "cmple": [
        { "instr_name": "cmple",   "datatypes": [float32],                  "template": tpl_implem_sse["compare"]                                                                      },
        { "instr_name": "cmple",   "datatypes": [float64],                  "template": tpl_implem_sse["compare"],            "if": "defined(__SSE2__)"                                } ], # cmple
#       { "instr_name": "cmple",   "datatypes": all_int,                    "template": tpl_implem_sse["cmple_int"]                                                                    },
    "cmpge": [
        { "instr_name": "cmpge",   "datatypes": [float32],                  "template": tpl_implem_sse["compare"]                                                                      },
        { "instr_name": "cmpge",   "datatypes": [float64],                  "template": tpl_implem_sse["compare"],            "if": "defined(__SSE2__)"                                } ], # cmpge
#       { "instr_name": "cmpge",   "datatypes": all_int,                    "template": tpl_implem_sse["cmpge_int"]                                                                    },
}
