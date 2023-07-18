from tools import *

isa_avx = {
	"name": "avx",
	"prefix": "_mm256",
	"size": 256,
	"define": "__AVX__",
	"hw_lmul": False,
	"datatypes": {
		float64 : { "data_ext" :    "pd", "data_ext_logi":    "pd", "data_ext_msk": "pd", "reg" : "__m256d", "msk" : "__m256d", "to_ptr": "float64_t" },
		float32 : { "data_ext" :    "ps", "data_ext_logi":    "ps", "data_ext_msk": "ps", "reg" : " __m256", "msk" : "__m256", "to_ptr": "float32_t" },
		  int64 : { "data_ext" : "epi64", "data_ext_logi": "si256", "data_ext_msk": "si256", "reg" : "__m256i", "msk" : "__m256i", "to_ptr":   "__m256i" },
		  int32 : { "data_ext" : "epi32", "data_ext_logi": "si256", "data_ext_msk": "si256", "reg" : "__m256i", "msk" : "__m256i", "to_ptr":   "__m256i" },
		  int16 : { "data_ext" : "epi16", "data_ext_logi": "si256", "data_ext_msk": "si256", "reg" : "__m256i", "msk" : "__m256i", "to_ptr":   "__m256i" },
		   int8 : { "data_ext" :  "epi8", "data_ext_logi": "si256", "data_ext_msk": "si256", "reg" : "__m256i", "msk" : "__m256i", "to_ptr":   "__m256i" },
		 uint64 : { "data_ext" : "epu64", "data_ext_logi": "si256", "data_ext_msk": "si256", "reg" : "__m256i", "msk" : "__m256i", "to_ptr":   "__m256i" },
		 uint32 : { "data_ext" : "epu32", "data_ext_logi": "si256", "data_ext_msk": "si256", "reg" : "__m256i", "msk" : "__m256i", "to_ptr":   "__m256i" },
		 uint16 : { "data_ext" : "epu16", "data_ext_logi": "si256", "data_ext_msk": "si256", "reg" : "__m256i", "msk" : "__m256i", "to_ptr":   "__m256i" },
		  uint8 : { "data_ext" :  "epu8", "data_ext_logi": "si256", "data_ext_msk": "si256", "reg" : "__m256i", "msk" : "__m256i", "to_ptr":   "__m256i" },
	},                                                                                           
}

tpl_implem_avx = {
	"cast":         { "format": "short", "code":"{% if isa_dt_par.data_ext_logi != isa_dt_ret.data_ext_logi -%} {{ isa.prefix }}_{{ instr_name }}{{isa_dt_par.data_ext_logi}}_{{isa_dt_ret.data_ext_logi}}(r0.r);{% else -%} r0.r;{% endif %}"},
	"cast_k":       { "format": "short", "code": "{% if isa_dt_par.data_ext_logi != isa_dt_ret.data_ext_logi -%} {{ isa.prefix }}_{{ instr_name }}{{isa_dt_par.data_ext_logi}}_{{ isa_dt_ret.data_ext_logi}}(m0.m);{% else -%} m0.m;{% endif %}"},
	"toreg":        { "format": "short", "code": "{% if isa_dt_par.data_ext_logi != isa_dt_ret.data_ext_logi -%}{{ isa.prefix }}_{{ instr_name }}{{isa_dt_par.data_ext_logi}}_{{isa_dt_ret.data_ext_logi}}(m0.m);{% else -%} m0.m;{% endif %}" },
	"tomsk":        { "format": "short", "code": "{% if isa_dt_par.data_ext_logi != isa_dt_ret.data_ext_logi -%}{{ isa.prefix }}_{{ instr_name }}{{isa_dt_par.data_ext_logi}}_{{isa_dt_ret.data_ext_logi}}(r0.r);{% else -%} r0.r;{% endif %}" },
	"load":         { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext_logi }}(({{ isa_dt_par.to_ptr }}*) p0);" },
	"store":        { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext_logi }}(({{ isa_dt_par.to_ptr }}*) p0, r0.r);" },
	"set0":         { "format": "short",  "code": " {{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext_logi }}();"},
	"set0_k":       { "format": "short",  "code": "	 {{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext_msk }}();" },
	"set1":         { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(v0);"},
	"set1x":        { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}x(v0);" },
	"getfirst":     { "format": "long",  "code":
"""	return ({{ cstdint_ret }}){{ isa.prefix }}_{{ instr_name }}_epi{{ dt_par.n_bits }}(%cast<tp,c:int|b:tp>%(r0).r, 0);""" },
	"arith_1arg":   { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(r0.r);" },
	"arith_2args":  { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(r0.r, r1.r);" },
	"logi_2args":   { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext_logi }}(r0.r, r1.r);" },
	"logi_m_2args": { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext_msk }}(m0.m, m1.m);" },
	"arith_3args":  { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(r0.r, r1.r, r2.r);" },
	"cmpeq_float":  { "format": "long", "code":
"""	%r<tp>% tmp;
	tmp.r = {{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(r0.r, r1.r, _CMP_EQ_OQ);
	return %tomsk<tp>%(tmp);""" },
	"cmpneq_float": { "format": "long", "code":
"""	%r<tp>% tmp;
	tmp.r = {{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(r0.r, r1.r, _CMP_NEQ_OQ);
	return %tomsk<tp>%(tmp);""" },
	"cmpgt_float":  { "format": "long", "code":
"""	%r<tp>% tmp;
	tmp.r = {{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(r0.r, r1.r, _CMP_GT_OS);
	return %tomsk<tp>%(tmp);""" },
	"cmpge_float":  { "format": "long", "code":
"""	%r<tp>% tmp;
	tmp.r = {{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(r0.r, r1.r, _CMP_GE_OS);
	return %tomsk<tp>%(tmp);""" },
	"cmple_float":  { "format": "long", "code":
"""	%r<tp>% tmp;
	tmp.r = {{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(r0.r, r1.r, _CMP_LE_OS);
	return %tomsk<tp>%(tmp);""" },
	"cmplt_float":  { "format": "long", "code":
"""	%r<tp>% tmp;
	tmp.r = {{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(r0.r, r1.r, _CMP_LT_OS);
	return %tomsk<tp>%(tmp);""" },
	"cmp_int":      { "format": "long", "code": " return {{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(r0.r, r1.r);" },
	"blend_float":  { "format": "long", "code": "return {{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(r0.r, r1.r, %toreg<tp>%(m0).m);" },
	"blend_int":    { "format": "long", "code": "return {{ isa.prefix }}_{{ instr_name }}_epi8(r0.r, r1.r, m0.m);" },
	"logi_2args_e": { "format": "long", "code":
"""	%r<c:float|b:32>% r0f = %cast<tp,c:float|b:32>%(r0);
	%r<c:float|b:32>% r1f = %cast<tp,c:float|b:32>%(r1);
	%r<c:float|b:32>% resf = %{{ instr_name }}<c:float|b:32>%(r0f, r1f);
	return %cast<c:float|b:32,tp>%(resf);"""
	},
	"logi_m_2args_e": { "format": "long", "code":
"""	%r<c:float|b:32>% r0f = %toreg<c:float|b:32>%(%cast_k<tp,c:float|b:32>%(m0));
	%r<c:float|b:32>% r1f = %toreg<c:float|b:32>%(%cast_k<tp,c:float|b:32>%(m1));
	%r<c:float|b:32>% resf = %{{ instr_name }}<c:float|b:32>%(r0f, r1f);
	return %tomsk<tp>%(%cast<c:float|b:32,tp>%(resf));"""
	},
	"testz_2args": { "format": "long", "code":
"""	return {{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext_msk }}(m0.m, m1.m);""" },
	"reduce_64": { "format": "long", "code":
"""	%r<c:float|b:32>% rsf;
	rsf.r = _mm256_permute2f128_ps(%cast<tp,c:float|b:32>%(r0).r, %cast<tp,c:float|b:32>%(r0).r, _MM_SHUFFLE(0,0,0,1));
	%r<tp>% rs1 = %cast<c:float|b:32,tp>%(rsf);
	rs1.r = {{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(r0.r, rs1.r);
	rsf = %cast<tp,c:float|b:32>%(rs1);
	rsf.r = _mm256_shuffle_ps(rsf.r, rsf.r, _MM_SHUFFLE(1,0,3,2));
	%r<tp>% rs2 = %cast<c:float|b:32,tp>%(rsf);
	rs2.r = {{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(rs1.r, rs2.r);
	return rs2;""" },
	"reduce_32": { "format": "long", "code":
"""	%r<c:float|b:32>% rsf;
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
"""	%r<c:float|b:32>% rsf;
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
"""	%r<c:float|b:32>% rsf;
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
}

implems_avx = {
	"cast": [
		{ "instr_name": "cast", "datatypes": all_datatypes_cart_prod, "template": tpl_implem_avx["cast"] } ],
	"cast_k": [
		{ "instr_name": "cast", "datatypes": all_datatypes_cart_prod, "template": tpl_implem_avx["cast_k"] } ],
	"toreg": [
		{ "instr_name": "cast", "datatypes": all_datatypes, "template": tpl_implem_avx["toreg"] } ],
	"tomsk": [
		{ "instr_name": "cast", "datatypes": all_datatypes, "template": tpl_implem_avx["tomsk"] } ],
	"load": [
		{ "instr_name": "load", "datatypes": all_datatypes, "template": tpl_implem_avx["load"], "if": "defined(MIPP_ALIGNED_LOADS)" },
		{ "instr_name": "loadu", "datatypes": all_datatypes, "template": tpl_implem_avx["load"], "if": "!defined(MIPP_ALIGNED_LOADS)" } ],
	"loadu": [
		{ "instr_name": "loadu", "datatypes": all_datatypes, "template": tpl_implem_avx["load"] } ],
	"store": [
		{ "instr_name": "store", "datatypes": all_datatypes, "template": tpl_implem_avx["store"], "if": "defined(MIPP_ALIGNED_LOADS)" },
		{ "instr_name": "storeu", "datatypes": all_datatypes, "template": tpl_implem_avx["store"], "if": "!defined(MIPP_ALIGNED_LOADS)" } ],
	"storeu": [
		{ "instr_name": "storeu", "datatypes": all_datatypes, "template": tpl_implem_avx["store"] } ],
	"set1": [
		{ "instr_name": "set1", "datatypes": all_float, "template": tpl_implem_avx["set1"] },
		{ "instr_name": "set1", "datatypes": [int64], "template": tpl_implem_avx["set1x"] },
		{ "instr_name": "set1", "datatypes": [int32, int16, int8], "template": tpl_implem_avx["set1"] } ],
	"set0": [
			{ "instr_name": "setzero", "datatypes": all_datatypes, "template": tpl_implem_avx["set0"] } ],
	"set0_k": [
		{ "instr_name": "setzero", "datatypes": all_datatypes, "template": tpl_implem_avx["set0_k"] } ],
	"getfirst": [
	 		{ "instr_name": "extract", "datatypes": all_float+[int64, int32, uint64, uint32], "template": tpl_implem_avx["getfirst"] },
	 		{ "instr_name": "extract", "datatypes": [int16, int8, uint16, uint8], "template": tpl_implem_avx["getfirst"], "if": "defined(__AVX2__)" } ],
	"sqrt": [
		{ "instr_name": "sqrt", "datatypes": all_float, "template": tpl_implem_avx["arith_1arg"] } ],
	"rsqrt": [
		{ "instr_name": "rsqrt", "datatypes": [float32], "template": tpl_implem_avx["arith_1arg"] } ],
	"add": [
		{ "instr_name": "add", "datatypes": all_float, "template": tpl_implem_avx["arith_2args"] },
		{ "instr_name": "add", "datatypes": [int64, int32], "template": tpl_implem_avx["arith_2args"], "if": "defined(__AVX2__)" },
		{ "instr_name": "adds", "datatypes": [int16, int8, uint16, uint8], "template": tpl_implem_avx["arith_2args"], "if": "defined(__AVX2__)" } ],
	"sub": [
		{ "instr_name": "sub", "datatypes": all_float, "template": tpl_implem_avx["arith_2args"] },
		{ "instr_name": "sub", "datatypes": [int64, int32], "template": tpl_implem_avx["arith_2args"], "if": "defined(__AVX2__)" },
		{ "instr_name": "subs", "datatypes": [int16, int8, uint16, uint8], "template": tpl_implem_avx["arith_2args"], "if": "defined(__AVX2__)" } ],
	"mul": [
		{ "instr_name": "mul", "datatypes": all_float, "template": tpl_implem_avx["arith_2args"] },
		{ "instr_name": "mullo", "datatypes": [int32, int16], "template": tpl_implem_avx["arith_2args"], "if": "defined(__AVX2__)" }],
	"div": [
		{ "instr_name": "div", "datatypes": all_float, "template": tpl_implem_avx["arith_2args"] } ],
	"min": [
		{ "instr_name": "min", "datatypes": all_float, "template": tpl_implem_avx["arith_2args"] },
		{ "instr_name": "min", "datatypes": [int32, int16, int8, uint32, uint16, uint8], "template": tpl_implem_avx["arith_2args"], "if": "defined(__AVX2__)" } ],
	"max": [
		{ "instr_name": "max", "datatypes": all_float, "template": tpl_implem_avx["arith_2args"] },
		{ "instr_name": "max", "datatypes": [int32, int16, int8, uint32, uint16, uint8], "template": tpl_implem_avx["arith_2args"], "if": "defined(__AVX2__)" } ],
	"fmadd": [
		{ "instr_name": "fmadd", "datatypes": all_float, "template": tpl_implem_avx["arith_3args"], "if": "defined(__FMA__)" } ],
	"fmsub": [
		{ "instr_name": "fmsub", "datatypes": all_float, "template": tpl_implem_avx["arith_3args"], "if": "defined(__FMA__)" } ],
	"andb": [
		{ "instr_name": "and", "datatypes": all_float, "template": tpl_implem_avx["logi_2args"] },
		{ "instr_name": "andb", "datatypes": all_int_uint, "template": tpl_implem_avx["logi_2args_e"], "if": "!defined(__AVX2__)" },
		{ "instr_name": "and", "datatypes": all_int_uint, "template": tpl_implem_avx["logi_2args"], "if": "defined(__AVX2__)" } ],
	"andb_k": [
		{ "instr_name": "andb", "datatypes": all_int_uint, "template": tpl_implem_avx["logi_m_2args_e"], "if": "!defined(__AVX2__)" },
		{ "instr_name": "and", "datatypes": all_datatypes, "template": tpl_implem_avx["logi_m_2args"], "if": "defined(__AVX2__)" } ],
	"andnb": [
		{ "instr_name": "andnot", "datatypes": all_float, "template": tpl_implem_avx["logi_2args"] },
		{ "instr_name": "andnb", "datatypes": all_int_uint, "template": tpl_implem_avx["logi_2args_e"], "if": "!defined(__AVX2__)" },
		{ "instr_name": "andnot", "datatypes": all_int_uint, "template": tpl_implem_avx["logi_2args"], "if": "defined(__AVX2__)" } ],
	"andnb_k": [
		{ "instr_name": "andnb", "datatypes": all_int_uint, "template": tpl_implem_avx["logi_m_2args_e"], "if": "!defined(__AVX2__)" },
		{ "instr_name": "andnot", "datatypes": all_datatypes, "template": tpl_implem_avx["logi_m_2args"], "if": "defined(__AVX2__)" } ],
	"orb": [
		{ "instr_name": "or", "datatypes": all_float, "template": tpl_implem_avx["logi_2args"] },
		{ "instr_name": "orb", "datatypes": all_int_uint, "template": tpl_implem_avx["logi_2args_e"], "if": "!defined(__AVX2__)" },
		{ "instr_name": "or", "datatypes": all_int_uint, "template": tpl_implem_avx["logi_2args"], "if": "defined(__AVX2__)" } ],
	"orb_k": [
		{ "instr_name": "orb", "datatypes": all_int_uint, "template": tpl_implem_avx["logi_m_2args_e"], "if": "!defined(__AVX2__)" },
		{ "instr_name": "or", "datatypes": all_datatypes, "template": tpl_implem_avx["logi_m_2args"], "if": "defined(__AVX2__)" } ],
	"xorb": [
		{ "instr_name": "xor", "datatypes": all_float, "template": tpl_implem_avx["logi_2args"] },
		{ "instr_name": "xorb", "datatypes": all_int_uint, "template": tpl_implem_avx["logi_2args_e"], "if": "!defined(__AVX2__)" },
		{ "instr_name": "xor", "datatypes": all_int_uint, "template": tpl_implem_avx["logi_2args"], "if": "defined(__AVX2__)" } ],
	"xorb_k": [
		{ "instr_name": "xorb", "datatypes": all_int_uint, "template": tpl_implem_avx["logi_m_2args_e"], "if": "!defined(__AVX2__)" },
		{ "instr_name": "xor", "datatypes": all_datatypes, "template": tpl_implem_avx["logi_m_2args"], "if": "defined(__AVX2__)" } ],
	"cmpeq": [
		{ "instr_name": "cmp", "datatypes": all_float, "template": tpl_implem_avx["cmpeq_float"] },
		{ "instr_name": "cmpeq", "datatypes": all_int, "template": tpl_implem_avx["cmp_int"], "if": "defined(__AVX2__)" } ],
	"cmpneq": [
		{ "instr_name": "cmp", "datatypes": all_float, "template": tpl_implem_avx["cmpneq_float"] } ],
	"cmplt": [
		{ "instr_name": "cmp", "datatypes": all_float, "template": tpl_implem_avx["cmplt_float"] } ],
	"cmple": [
		{ "instr_name": "cmp", "datatypes": all_float, "template": tpl_implem_avx["cmple_float"] } ],
	"cmpge": [
		{ "instr_name": "cmp", "datatypes": all_float, "template": tpl_implem_avx["cmpge_float"] } ],
	"cmpgt": [
		{ "instr_name": "cmp", "datatypes": all_float, "template": tpl_implem_avx["cmpgt_float"], },
		{ "instr_name": "cmpgt", "datatypes": all_int, "template": tpl_implem_avx["cmp_int"], "if": "defined(__AVX2__)" } ],
	"blend": [
		{ "instr_name": "blendv", "datatypes": all_float, "template": tpl_implem_avx["blend_float"] },
		{ "instr_name": "blendv", "datatypes": all_int_uint, "template": tpl_implem_avx["blend_int"], "if": "defined(__AVX2__)" } ],
	"testz": [
		{ "instr_name": "testz", "datatypes": all_datatypes, "template": tpl_implem_avx["testz_2args"] } ],
	"hadd": [
		{ "instr_name": "add", "datatypes": [float64], "template": tpl_implem_avx["reduce_64"] },
		{ "instr_name": "add", "datatypes": [int64], "template": tpl_implem_avx["reduce_64"], "if": "defined(__AVX2__)" },
		{ "instr_name": "add", "datatypes": [float32], "template": tpl_implem_avx["reduce_32"] },
		{ "instr_name": "add", "datatypes": [int32], "template": tpl_implem_avx["reduce_32"], "if": "defined(__AVX2__)" },
		{ "instr_name": "adds", "datatypes": [int16, uint16], "template": tpl_implem_avx["reduce_16"], "if": "defined(__AVX2__)" },
		{ "instr_name": "adds", "datatypes": [int8, uint8], "template": tpl_implem_avx["reduce_8"], "if": "defined(__AVX2__)" } ],
	"hmul": [
		{ "instr_name": "mul", "datatypes": [float64], "template": tpl_implem_avx["reduce_64"] },
		{ "instr_name": "mul", "datatypes": [float32], "template": tpl_implem_avx["reduce_32"] },
		{ "instr_name": "mullo", "datatypes": [int32], "template": tpl_implem_avx["reduce_32"], "if": "defined(__AVX2__)" },
		{ "instr_name": "mullo", "datatypes": [int16], "template": tpl_implem_avx["reduce_16"], "if": "defined(__AVX2__)" } ],
	"hmin": [
		{ "instr_name": "min", "datatypes": [float64], "template": tpl_implem_avx["reduce_64"] },
		{ "instr_name": "min", "datatypes": [float32], "template": tpl_implem_avx["reduce_32"] },
		{ "instr_name": "min", "datatypes": [int32, uint32], "template": tpl_implem_avx["reduce_32"], "if": "defined(__AVX2__)" },
		{ "instr_name": "min", "datatypes": [int16, uint16], "template": tpl_implem_avx["reduce_16"], "if": "defined(__AVX2__)" },
		{ "instr_name": "min", "datatypes": [int8, uint8], "template": tpl_implem_avx["reduce_8"], "if": "defined(__AVX2__)" } ],
	"hmax": [
		{ "instr_name": "max", "datatypes": [float64], "template": tpl_implem_avx["reduce_64"] },
		{ "instr_name": "max", "datatypes": [float32], "template": tpl_implem_avx["reduce_32"] },
		{ "instr_name": "max", "datatypes": [int32, uint32], "template": tpl_implem_avx["reduce_32"], "if": "defined(__AVX2__)" },
		{ "instr_name": "max", "datatypes": [int16, uint16], "template": tpl_implem_avx["reduce_16"], "if": "defined(__AVX2__)" },
		{ "instr_name": "max", "datatypes": [int8, uint8], "template": tpl_implem_avx["reduce_8"], "if": "defined(__AVX2__)" } ],
}
