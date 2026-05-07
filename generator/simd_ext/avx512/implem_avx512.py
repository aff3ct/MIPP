from tools import *

isa_avx512 = {
    "name": "avx512",
    "prefix": "_mm512",
    "size": 512,
    "define": 'defined(__MIC__) || defined(__KNCNI__) || defined(__AVX512__) || defined(__AVX512F__)',
    "architecture": "x86",
    "hw_lmul": False,
    "datatypes": {
        float64: { "data_ext": "pd",    "data_ext_logi": "pd",    "data_ext_msk": "si512", "reg": "__m512d", "msk": "__mmask8",  "msk_short": "mask8",  "to_ptr": "float64_t" },
        float32: { "data_ext": "ps",    "data_ext_logi": "ps",    "data_ext_msk": "si512", "reg": "__m512" , "msk": "__mmask16", "msk_short": "mask16", "to_ptr": "float32_t" },
        int64:   { "data_ext": "epi64", "data_ext_logi": "si512", "data_ext_msk": "si512", "reg": "__m512i", "msk": "__mmask8",  "msk_short": "mask8",  "to_ptr": "int64_t"   },
        int32:   { "data_ext": "epi32", "data_ext_logi": "si512", "data_ext_msk": "si512", "reg": "__m512i", "msk": "__mmask16", "msk_short": "mask16", "to_ptr": "int32_t"   },
        int16:   { "data_ext": "epi16", "data_ext_logi": "si512", "data_ext_msk": "si512", "reg": "__m512i", "msk": "__mmask32", "msk_short": "mask32", "to_ptr": "int16_t"   },
        int8:    { "data_ext": "epi8",  "data_ext_logi": "si512", "data_ext_msk": "si512", "reg": "__m512i", "msk": "__mmask64", "msk_short": "mask64", "to_ptr": "int8_t"    },
        uint64:  { "data_ext": "epu64", "data_ext_logi": "si512", "data_ext_msk": "si512", "reg": "__m512i", "msk": "__mmask8",  "msk_short": "mask8",  "to_ptr": "uint64_t"  },
        uint32:  { "data_ext": "epu32", "data_ext_logi": "si512", "data_ext_msk": "si512", "reg": "__m512i", "msk": "__mmask16", "msk_short": "mask16", "to_ptr": "uint32_t"  },
        uint16:  { "data_ext": "epu16", "data_ext_logi": "si512", "data_ext_msk": "si512", "reg": "__m512i", "msk": "__mmask32", "msk_short": "mask32", "to_ptr": "uint16_t"  },
        uint8:   { "data_ext": "epu8",  "data_ext_logi": "si512", "data_ext_msk": "si512", "reg": "__m512i", "msk": "__mmask64", "msk_short": "mask64", "to_ptr": "uint8_t"   }
    }
}

tpl_implem_avx512 = {
    "cast":             { "format": "short", "code": "{% if isa_dt_par.data_ext_logi != isa_dt_ret.data_ext_logi -%}{{ isa.prefix }}_{{ instr_name }}{{isa_dt_par.data_ext_logi}}_{{isa_dt_ret.data_ext_logi}}(r0.r);{% else -%} r0.r;{% endif %}" },
    "cast_k":           { "format": "short", "code": "{% if isa_dt_par.msk != isa_dt_ret.msk -%}({{ isa_dt_ret.msk }})m0.m;{% else -%}m0.m;{% endif %}"},
    "load":             { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext_logi }}(({{ isa_dt_par.to_ptr }}*) p0);" },
    "store":            { "format": "short", "code": "\t{{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext_logi }}(({{ isa_dt_par.to_ptr }}*) p0, r0.r);" },
    "set0":             { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext_logi }}();"},
    "set0_k":           { "format": "short", "code": "0;" },
#   "low_k":            { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext_msk }}();" },
    "set1":             { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(v0);"},
    "arith_1arg":       { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(r0.r);" },
    "arith_2args":      { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(r0.r, r1.r);" },
    "arithmsk_2args":   { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(m0.m, r0.r, r1.r);" },
    "logi_2args":       { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext_logi }}(r0.r, r1.r);" },
    "logi_m_2args":     { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}(m0.m, m1.m);" },
    "arith_3args":      { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(r0.r, r1.r, r2.r);" },
    "lshift":           { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(r0.r, r1.r, r2.r);" },
    "cmp_int":          { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}_mask(r0.r, r1.r);" },
    "cmpeq_float":      { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}_mask(r0.r, r1.r, _CMP_EQ_OQ);" },
    "cmpneq_float":     { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}_mask(r0.r, r1.r, _CMP_NEQ_OQ);" },
    "cmplt_float":      { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}_mask(r0.r, r1.r, _CMP_LT_OS);" },
    "cmple_float":      { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}_mask(r0.r, r1.r, _CMP_LE_OS);" },
    "cmpgt_float":      { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}_mask(r0.r, r1.r, _CMP_GT_OS);" },
    "cmpge_float":      { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}_mask(r0.r, r1.r, _CMP_GE_OS);" },
    "blend":            { "format": "short", "code": "{{ isa.prefix }}_mask_{{ instr_name }}_{{ isa_dt_par.data_ext }}(m0.m, r1.r, r0.r);" },
    "round":            { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(r0.r, _MM_FROUND_TO_NEAREST_INT);" },
    "roundf":           { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(r0.r, _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC, _MM_EXPADJ_NONE);" },
    "bitwise_1arg":     { "format": "short", "code": "_{{ instr_name }}_{{ isa_dt_par.msk_short }}(m0.m);" },
    "bitwise_2args":    { "format": "short", "code": "_{{ instr_name }}_{{ isa_dt_par.msk_short }}(m0.m, m1.m);" },
    "testz_1arg":       { "format": "long",  "code": "return (int32_t)_{{ instr_name }}_{{ isa_dt_par.msk_short }}_u8(m0.m, m0.m);" },
    "testz_2args":      { "format": "long",  "code": "return (int32_t)_{{ instr_name }}_{{ isa_dt_par.msk_short }}_u8(m0.m, m1.m);" },
    "set-64": { "format": "long", "code":
"""// long format
	%r<tp>% res;
	res.r = {{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(vals[7], vals[6], vals[5], vals[4], vals[3], vals[2], vals[1], vals[0]);
	return res;""" },
    "set-32": { "format": "long", "code":
"""// long format
	%r<tp>% res;
	res.r = {{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(
		vals[15], vals[14], vals[13], vals[12],vals[11], vals[10], vals[ 9], vals[ 8],
		vals[ 7], vals[ 6], vals[ 5], vals[ 4],vals[ 3], vals[ 2], vals[ 1], vals[ 0]);
	return res;""" },
    "set-16": { "format": "long", "code":
"""// long format
	%r<tp>% res;
	res.r = {{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(
		vals[31], vals[30], vals[29], vals[28],
		vals[27], vals[26], vals[25], vals[24],
		vals[23], vals[22], vals[21], vals[20],
		vals[19], vals[18], vals[17], vals[16],
		vals[15], vals[14], vals[13], vals[12],
		vals[11], vals[10], vals[ 9], vals[ 8],
		vals[ 7], vals[ 6], vals[ 5], vals[ 4],
		vals[ 3], vals[ 2], vals[ 1], vals[ 0]);
	return res;""" },
    "set-8": { "format": "long", "code":
"""// long format
	%r<tp>% res;
	res.r = {{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(
		vals[63], vals[62], vals[61], vals[60],
		vals[59], vals[58], vals[57], vals[56],
		vals[55], vals[54], vals[53], vals[52],
		vals[51], vals[50], vals[49], vals[48],
		vals[47], vals[46], vals[45], vals[44],
		vals[43], vals[42], vals[41], vals[40],
		vals[39], vals[38], vals[37], vals[36],
		vals[35], vals[34], vals[33], vals[32],
		vals[31], vals[30], vals[29], vals[28],
		vals[27], vals[26], vals[25], vals[24],
		vals[23], vals[22], vals[21], vals[20],
		vals[19], vals[18], vals[17], vals[16],
		vals[15], vals[14], vals[13], vals[12],
		vals[11], vals[10], vals[ 9], vals[ 8],
		vals[ 7], vals[ 6], vals[ 5], vals[ 4],
		vals[ 3], vals[ 2], vals[ 1], vals[ 0]);
	return res;""" },
    "set0_k": { "format": "long", "code":
"""// long format
	%m<tp>% m;
	m.m = 0;
	return m;""" },
    "getfirst": { "format": "long", "code":
"""// long format
	return {{ isa.prefix }}_{{ instr_name }}(r0.r);""" },
    "getfirst-hack64": { "format": "long", "code":
"""// long format
	float64_t tmp1 = {{ isa.prefix }}_{{ instr_name }}(%cast<tp,c:float>%(r0).r);
	void* tmp2 = (void*)(&tmp1);
	return *({{isa_dt_ret.to_ptr}}*)tmp2;""" },
    "getfirst-hack32": { "format": "long", "code":
"""// long format
	float32_t tmp1 = {{ isa.prefix }}_{{ instr_name }}(%cast<tp,c:float>%(r0).r);
	void* tmp2 = (void*)(&tmp1);
	return *({{isa_dt_ret.to_ptr}}*)tmp2;""" },
    "reduce_64": { "format": "long", "code":
"""// long format
	%r<c:float|b:32>% rsf;
	%r<c:int|b:32>% rsi32;

	rsf.r = _mm512_permutexvar_ps(_mm512_set_epi32( 7, 6, 5, 4, 3, 2, 1, 0,15,14,13,12,11,10,9,8), %cast<tp,c:float|b:32>%(r0).r);
	%r<tp>% rs1 = %cast<c:float|b:32,tp>%(rsf);
	rs1.r = {{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(r0.r, rs1.r);

	rsf.r = _mm512_permutexvar_ps(_mm512_set_epi32(11,10, 9, 8,15,14,13,12, 3, 2, 1, 0, 7, 6,5,4), %cast<tp,c:float|b:32>%(rs1).r);
	%r<tp>% rs2 = %cast<c:float|b:32,tp>%(rsf);
	rs2.r = {{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(rs1.r, rs2.r);

#ifdef __cplusplus
	rsi32.r = _mm512_shuffle_epi32(%cast<tp,c:int|b:32>%(rs2).r, _MM_PERM_ENUM(_MM_SHUFFLE(1,0,3,2)));
#else
	rsi32.r = _mm512_shuffle_epi32(%cast<tp,c:int|b:32>%(rs2).r, _MM_SHUFFLE(1,0,3,2));
#endif
	%r<tp>% rs3 = %cast<c:int|b:32,tp>%(rsi32);
	rs3.r = {{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(rs2.r, rs3.r);

	return rs3;""" },
    "reduce_32": { "format": "long", "code":
"""// long format
	%r<c:float|b:32>% rsf;
	%r<c:int|b:32>% rsi32;

	rsf.r = _mm512_permutexvar_ps(_mm512_set_epi32( 7, 6, 5, 4, 3, 2, 1, 0,15,14,13,12,11,10,9,8), %cast<tp,c:float|b:32>%(r0).r);
	%r<tp>% rs1 = %cast<c:float|b:32,tp>%(rsf);
	rs1.r = {{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(r0.r, rs1.r);

	rsf.r = _mm512_permutexvar_ps(_mm512_set_epi32(11,10, 9, 8,15,14,13,12, 3, 2, 1, 0, 7, 6,5,4), %cast<tp,c:float|b:32>%(rs1).r);
	%r<tp>% rs2 = %cast<c:float|b:32,tp>%(rsf);
	rs2.r = {{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(rs1.r, rs2.r);

#ifdef __cplusplus
	rsi32.r = _mm512_shuffle_epi32(%cast<tp,c:int|b:32>%(rs2).r, _MM_PERM_ENUM(_MM_SHUFFLE(1,0,3,2)));
#else
	rsi32.r = _mm512_shuffle_epi32(%cast<tp,c:int|b:32>%(rs2).r, _MM_SHUFFLE(1,0,3,2));
#endif
	%r<tp>% rs3 = %cast<c:int|b:32,tp>%(rsi32);
	rs3.r = {{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(rs2.r, rs3.r);

#ifdef __cplusplus
	rsi32.r = _mm512_shuffle_epi32(%cast<tp,c:int|b:32>%(rs3).r, _MM_PERM_ENUM(_MM_SHUFFLE(2,3,0,1)));
#else
	rsi32.r = _mm512_shuffle_epi32(%cast<tp,c:int|b:32>%(rs3).r, _MM_SHUFFLE(2,3,0,1));
#endif
	%r<tp>% rs4 = %cast<c:int|b:32,tp>%(rsi32);
	rs4.r = {{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(rs3.r, rs4.r);

	return rs4;""" },
    "reduce_16": { "format": "long", "code":
"""// long format
	%r<c:float|b:32>% rsf;
	%r<c:int|b:32>% rsi32;
	%r<c:int|b:8>% rsi8;

	rsf.r = _mm512_permutexvar_ps(_mm512_set_epi32( 7, 6, 5, 4, 3, 2, 1, 0,15,14,13,12,11,10,9,8), %cast<tp,c:float|b:32>%(r0).r);
	%r<tp>% rs1 = %cast<c:float|b:32,tp>%(rsf);
	rs1.r = {{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(r0.r, rs1.r);

	rsf.r = _mm512_permutexvar_ps(_mm512_set_epi32(11,10, 9, 8,15,14,13,12, 3, 2, 1, 0, 7, 6,5,4), %cast<tp,c:float|b:32>%(rs1).r);
	%r<tp>% rs2 = %cast<c:float|b:32,tp>%(rsf);
	rs2.r = {{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(rs1.r, rs2.r);

#ifdef __cplusplus
	rsi32.r = _mm512_shuffle_epi32(%cast<tp,c:int|b:32>%(rs2).r, _MM_PERM_ENUM(_MM_SHUFFLE(1,0,3,2)));
#else
	rsi32.r = _mm512_shuffle_epi32(%cast<tp,c:int|b:32>%(rs2).r, _MM_SHUFFLE(1,0,3,2));
#endif
	%r<tp>% rs3 = %cast<c:int|b:32,tp>%(rsi32);
	rs3.r = {{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(rs2.r, rs3.r);

#ifdef __cplusplus
	rsi32.r = _mm512_shuffle_epi32(%cast<tp,c:int|b:32>%(rs3).r, _MM_PERM_ENUM(_MM_SHUFFLE(2,3,0,1)));
#else
	rsi32.r = _mm512_shuffle_epi32(%cast<tp,c:int|b:32>%(rs3).r, _MM_SHUFFLE(2,3,0,1));
#endif
	%r<tp>% rs4 = %cast<c:int|b:32,tp>%(rsi32);
	rs4.r = {{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(rs3.r, rs4.r);

	__m512i mask_16 = _mm512_set_epi8(61,60,63,62,57,56,59,58,53,52,55,54,49,48,51,50,
	                                  45,44,47,46,41,40,43,42,37,36,39,38,33,32,35,34,
	                                  29,28,31,30,25,24,27,26,21,20,23,22,17,16,19,18,
	                                  13,12,15,14, 9, 8,11,10, 5, 4, 7, 6, 1, 0, 3, 2);
	rsi8.r = _mm512_shuffle_epi8(%cast<tp,c:int|b:8>%(rs4).r, mask_16);
	%r<tp>% rs5 = %cast<c:int|b:8,tp>%(rsi8);
	rs5.r = {{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(rs4.r, rs5.r);

	return rs5;"""},
    "reduce_8": { "format": "long", "code":
"""// long format
	%r<c:float|b:32>% rsf;
	%r<c:int|b:32>% rsi32;
	%r<c:int|b:8>% rsi8;

	rsf.r = _mm512_permutexvar_ps(_mm512_set_epi32( 7, 6, 5, 4, 3, 2, 1, 0,15,14,13,12,11,10,9,8), %cast<tp,c:float|b:32>%(r0).r);
	%r<tp>% rs1 = %cast<c:float|b:32,tp>%(rsf);
	rs1.r = {{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(r0.r, rs1.r);

	rsf.r = _mm512_permutexvar_ps(_mm512_set_epi32(11,10, 9, 8,15,14,13,12, 3, 2, 1, 0, 7, 6,5,4), %cast<tp,c:float|b:32>%(rs1).r);
	%r<tp>% rs2 = %cast<c:float|b:32,tp>%(rsf);
	rs2.r = {{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(rs1.r, rs2.r);

#ifdef __cplusplus
	rsi32.r = _mm512_shuffle_epi32(%cast<tp,c:int|b:32>%(rs2).r, _MM_PERM_ENUM(_MM_SHUFFLE(1,0,3,2)));
#else
	rsi32.r = _mm512_shuffle_epi32(%cast<tp,c:int|b:32>%(rs2).r, _MM_SHUFFLE(1,0,3,2));
#endif
	%r<tp>% rs3 = %cast<c:int|b:32,tp>%(rsi32);
	rs3.r = {{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(rs2.r, rs3.r);

#ifdef __cplusplus
	rsi32.r = _mm512_shuffle_epi32(%cast<tp,c:int|b:32>%(rs3).r, _MM_PERM_ENUM(_MM_SHUFFLE(2,3,0,1)));
#else
	rsi32.r = _mm512_shuffle_epi32(%cast<tp,c:int|b:32>%(rs3).r, _MM_SHUFFLE(2,3,0,1));
#endif
	%r<tp>% rs4 = %cast<c:int|b:32,tp>%(rsi32);
	rs4.r = {{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(rs3.r, rs4.r);

	__m512i mask_16 = _mm512_set_epi8(61,60,63,62,57,56,59,58,53,52,55,54,49,48,51,50,
	                                  45,44,47,46,41,40,43,42,37,36,39,38,33,32,35,34,
	                                  29,28,31,30,25,24,27,26,21,20,23,22,17,16,19,18,
	                                  13,12,15,14, 9, 8,11,10, 5, 4, 7, 6, 1, 0, 3, 2);
	rsi8.r = _mm512_shuffle_epi8(%cast<tp,c:int|b:8>%(rs4).r, mask_16);
	%r<tp>% rs5 = %cast<c:int|b:8,tp>%(rsi8);
	rs5.r = {{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(rs4.r, rs5.r);

	__m512i mask_8  = _mm512_set_epi8(62,63,60,61,58,59,56,57,54,55,52,53,50,51,48,49,
	                                  46,47,44,45,42,43,40,41,38,39,36,37,34,35,32,33,
	                                  30,31,28,29,26,27,24,25,22,23,20,21,18,19,16,17,
	                                  14,15,12,13,10,11, 8, 9, 6, 7, 4, 5, 2, 3, 0, 1);
	rsi8.r = _mm512_shuffle_epi8(%cast<tp,c:int|b:8>%(rs5).r, mask_8);
	%r<tp>% rs6 = %cast<c:int|b:8,tp>%(rsi8);
	rs6.r = {{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(rs5.r, rs6.r);

	return rs6;""" },
    
    "arith_2args_msk": { "format": "short", "code": "{{ isa.prefix }}_mask_{{ instr_name }}_{{ isa_dt_par.data_ext }}(r0.r, m0.m, r0.r, r1.r);" },
    
    "andb_emu": {"format": "long", "code":
"""// long format
    %r<c:int|b:tp>% tmp0, tmp1;
    tmp0 = %cast<tp,c:int|b:tp>%(r0);
    tmp1 = %cast<tp,c:int|b:tp>%(r1);
    tmp0 = %andb<c:int|b:tp>%(tmp0, tmp1);
    return %cast<c:int|b:tp,tp>%(tmp0);"""
    },

    "blend_emu": {"format": "long", "code":
"""// long format
    %r<c:int|b:tp>% tmp0, tmp1;
    tmp0 = %cast<tp,c:int|b:tp>%(r0);
    tmp1 = %cast<tp,c:int|b:tp>%(r1);
    %m<c:int|b:tp>% mtmp = %cast_k<tp,c:int|b:tp>%(m0);
    tmp0 = %blend<c:int|b:tp>%(tmp0, tmp1, mtmp);
    return %cast<c:int|b:tp,tp>%(tmp0);"""
    },
    "set1_emu": {"format": "long", "code":
"""// long format
    %r<c:int|b:tp>% tmp0;
    tmp0 = %set1<c:int|b:tp>%( (%v<c:int|b:tp>%)v0);
    return %cast<c:int|b:tp,tp>%(tmp0);"""
    },
}

implems_avx512 = {
    "cast"   : [
        { "instr_name": "cast",       "datatypes": all_datatypes_cart_prod,      "template": tpl_implem_avx512["cast"],                                                                                                         } ], # cast
    "cast_k" : [
        { "instr_name": "cast",       "datatypes": all_datatypes_cart_prod,      "template": tpl_implem_avx512["cast_k"],                                                                                                       } ], # cast_k
    "set" :[
        { "instr_name": "set",        "datatypes": [float64, int64],             "template": tpl_implem_avx512["set-64"],         "if": "defined(__AVX512F__)"                                                                  },
        { "instr_name": "set",        "datatypes": [float32, int32],             "template": tpl_implem_avx512["set-32"],         "if": "defined(__AVX512F__)"                                                                  },
        { "instr_name": "set",        "datatypes": [int16],                      "template": tpl_implem_avx512["set-16"],         "if": "defined(__AVX512BW__)"                                                                 },
        { "instr_name": "set",        "datatypes": [int8],                       "template": tpl_implem_avx512["set-8"],          "if": "defined(__AVX512BW__)"                                                                 } ], # set
    "load": [
        { "instr_name": "load",       "datatypes": all_datatypes,                "template": tpl_implem_avx512["load"],           "if": "defined(MIPP_ALIGNED_LOADS)"                                                           },
        { "instr_name": "loadu",      "datatypes": all_datatypes,                "template": tpl_implem_avx512["load"],           "if": "!defined(MIPP_ALIGNED_LOADS)"                                                          } ], # load
    "loadu": [
        { "instr_name": "loadu",      "datatypes": all_datatypes,                "template": tpl_implem_avx512["load"],                                                                                                         } ], # loadu
    "store": [
        { "instr_name": "store",      "datatypes": all_datatypes,                "template": tpl_implem_avx512["store"],          "if": "defined(MIPP_ALIGNED_LOADS)"                                                           },
        { "instr_name": "storeu",     "datatypes": all_datatypes,                "template": tpl_implem_avx512["store"],          "if": "!defined(MIPP_ALIGNED_LOADS)"                                                          } ], # store
    "storeu": [
        { "instr_name": "storeu",     "datatypes": all_datatypes,                "template": tpl_implem_avx512["store"],                                                                                                        } ], # storeu
    "getfirst": [
        { "instr_name": "cvtsd_f64",  "datatypes": [float64],                    "template": tpl_implem_avx512["getfirst"],                                                                                                     },
        { "instr_name": "cvtss_f32",  "datatypes": [float32],                    "template": tpl_implem_avx512["getfirst"],                                                                                                     },
        { "instr_name": "cvtsd_f64",  "datatypes": [int64, uint64],              "template": tpl_implem_avx512["getfirst-hack64"],                                                                                              },
        { "instr_name": "cvtss_f32",  "datatypes": [int32, uint32],              "template": tpl_implem_avx512["getfirst-hack32"],                                                                                              } ], # getfirst
    "set1": [
        { "instr_name": "set1",       "datatypes": all_float + all_int,          "template": tpl_implem_avx512["set1"],                                                                                                         }, 
        { "instr_name": "set1",       "datatypes": all_uint,                     "template": tpl_implem_avx512["set1_emu"]                                                                                                      }], # set1
    "set0": [
        { "instr_name": "setzero",    "datatypes": all_datatypes,                "template": tpl_implem_avx512["set0"],                                                                                                         } ], # set0
    "set0_k": [
        { "instr_name": "setzero",    "datatypes": all_datatypes,                "template": tpl_implem_avx512["set0_k"],                                                                                                       } ], # set0_k
#   "low_k": [
#       { "instr_name": "kunpackd",   "datatypes": [float64, int64],             "template": tpl_implem_avx512["low_k"],                                                                                                        },
#       { "instr_name": "kunpackw",   "datatypes": [float32, int32],             "template": tpl_implem_avx512["low_k"],                                                                                                        },
#       { "instr_name": "kunpackb",   "datatypes": [int16],                      "template": tpl_implem_avx512["low_k"],                                                                                                        } ], # low_k
    "sqrt": [
        { "instr_name": "sqrt",       "datatypes": all_float,                    "template": tpl_implem_avx512["arith_1arg"],                                                                                                   } ], # sqrt
    "rsqrt": [
        { "instr_name": "rsqrt14",    "datatypes": [float64, float32],           "template": tpl_implem_avx512["arith_1arg"],                                                                                                   } ], # rsqrt
    "add": [
        { "instr_name": "add",        "datatypes": all_float + [int32],          "template": tpl_implem_avx512["arith_2args"],                                                                                                  },
        { "instr_name": "add",        "datatypes": [int64],                      "template": tpl_implem_avx512["arith_2args"],                                                                                                  },
        { "instr_name": "adds",       "datatypes": [int16, int8, uint16, uint8], "template": tpl_implem_avx512["arith_2args"],    "if": "defined(__AVX512BW__)"                                                                 }, 
        { "instr_name": "add",        "datatypes": all_float,                    "template": tpl_implem_avx512["arith_2args_msk"], "version" : "mask"}], # add
    "sub": [
        { "instr_name": "sub",        "datatypes": all_float,                    "template": tpl_implem_avx512["arith_2args"],                                                                                                  },
        { "instr_name": "sub",        "datatypes": [int64, int32],               "template": tpl_implem_avx512["arith_2args"],                                                                                                  },
        { "instr_name": "subs",       "datatypes": [int16, int8],                "template": tpl_implem_avx512["arith_2args"],    "if": "defined(__AVX512BW__)"                                                                 } ], # sub
    "mul": [
        { "instr_name": "mul",        "datatypes": all_float,                    "template": tpl_implem_avx512["arith_2args"],                                                                                                  },
        { "instr_name": "mullo",      "datatypes": [int32],                      "template": tpl_implem_avx512["arith_2args"],                                                                                                  },
        { "instr_name": "mullo",      "datatypes": [int16],                      "template": tpl_implem_avx512["arith_2args"],    "if": "defined(__AVX512BW__)"                                                                 } ], # mul
    "div": [
        { "instr_name": "div",        "datatypes": all_float,                    "template": tpl_implem_avx512["arith_2args"],    "if": "defined(__AVX512BW__)"                                                                 } ], # div
    "min": [
        { "instr_name": "min",        "datatypes": all_float + [int64, int32],   "template": tpl_implem_avx512["arith_2args"],                                                                                                  },
        { "instr_name": "min",        "datatypes": [int16, int8],                "template": tpl_implem_avx512["arith_2args"],    "if": "defined(__AVX512BW__)"                                                                 },
        { "instr_name": "gmin",       "datatypes": all_float,                    "template": tpl_implem_avx512["arith_2args"],    "if": "(defined(__MIC__) || defined(__KNCNI__))"                                                } ], # min
    "max": [
        { "instr_name": "max",        "datatypes": all_float + [int64, int32],   "template": tpl_implem_avx512["arith_2args"],                                                                                                  },
        { "instr_name": "max",        "datatypes": [int16, int8],                "template": tpl_implem_avx512["arith_2args"],    "if": "defined(__AVX512BW__)"                                                                 },
        { "instr_name": "gmax",       "datatypes": all_float,                    "template": tpl_implem_avx512["arith_2args"],    "if": "(defined(__MIC__) || defined(__KNCNI__))"                                                } ], # max
    "fmadd": [
        { "instr_name": "fmadd",      "datatypes": all_float,                    "template": tpl_implem_avx512["arith_3args"],                                                                                                  },
        { "instr_name": "fmadd",      "datatypes": [int32],                      "template": tpl_implem_avx512["arith_3args"],    "if": "(defined(__MIC__) || defined(__KNCNI__))"                                                } ], # fmadd
    "fmsub": [
        { "instr_name": "fmsub",      "datatypes": all_float,                    "template": tpl_implem_avx512["arith_3args"],                                                                                                  } ], # fmsub
    "notb_k": [
        { "instr_name": "knot",       "datatypes": all_64bit,                    "template": tpl_implem_avx512["bitwise_1arg"],   "if": "defined(__AVX512DQ__)"                                                                 },
        { "instr_name": "knot",       "datatypes": all_32bit,                    "template": tpl_implem_avx512["bitwise_1arg"],                                                                                                 },
        { "instr_name": "knot",       "datatypes": all_16bit,                    "template": tpl_implem_avx512["bitwise_1arg"],   "if": "defined(__AVX512BW__)"                                                                 },
        { "instr_name": "knot",       "datatypes": all_8bit,                     "template": tpl_implem_avx512["bitwise_1arg"],   "if": "defined(__AVX512BW__)"                                                                 } ], # notb_k
    "andb": [
        { "instr_name": "and",        "datatypes": all_float,                    "template": tpl_implem_avx512["logi_2args"],     "if": "defined(__AVX512DQ__)"                                                                 },
        { "instr_name": "and",        "datatypes": [int64, uint64],              "template": tpl_implem_avx512["logi_2args"],                                                                                                   },
        { "instr_name": "and",        "datatypes": [int32, uint32],              "template": tpl_implem_avx512["logi_2args"],                                                                                                   },
        { "instr_name": "and",        "datatypes": [int16, uint16],              "template": tpl_implem_avx512["logi_2args"],     "if": "defined(__AVX512BW__)"                                                                 },
        { "instr_name": "and",        "datatypes": [int8, uint8],                "template": tpl_implem_avx512["logi_2args"],     "if": "defined(__AVX512BW__)"                                                                 }, 
        { "instr_name": "and",        "datatypes": all_float,                    "template": tpl_implem_avx512["andb_emu"],       "if": "!defined(__AVX512DQ__)"                                                                },], # andb
    "andb_k": [
        { "instr_name": "kand",       "datatypes": all_64bit,                    "template": tpl_implem_avx512["bitwise_2args"],  "if": "defined(__AVX512DQ__)"                                                                 },
        { "instr_name": "kand",       "datatypes": all_32bit,                    "template": tpl_implem_avx512["bitwise_2args"],                                                                                                },
        { "instr_name": "kand",       "datatypes": all_16bit,                    "template": tpl_implem_avx512["bitwise_2args"],  "if": "defined(__AVX512BW__)"                                                                 },
        { "instr_name": "kand",       "datatypes": all_8bit,                     "template": tpl_implem_avx512["bitwise_2args"],  "if": "defined(__AVX512BW__)"                                                                 } ], # andb_k
    "andnb": [
        { "instr_name": "andnot",     "datatypes": all_float,                    "template": tpl_implem_avx512["logi_2args"],     "if": "defined(__AVX512DQ__)"                                                                 },
        { "instr_name": "andnot",     "datatypes": [int64, uint64],              "template": tpl_implem_avx512["logi_2args"],                                                                                                   },
        { "instr_name": "andnot",     "datatypes": [int32, uint32],              "template": tpl_implem_avx512["logi_2args"],                                                                                                   },
        { "instr_name": "andnot",     "datatypes": [int16, uint16],              "template": tpl_implem_avx512["logi_2args"],     "if": "defined(__AVX512BW__)"                                                                 },
        { "instr_name": "andnot",     "datatypes": [int8, uint8],                "template": tpl_implem_avx512["logi_2args"],     "if": "defined(__AVX512BW__)"                                                                 } ], # andnb
    "andnb_k": [
        { "instr_name": "kandn",      "datatypes": all_64bit,                    "template": tpl_implem_avx512["bitwise_2args"],  "if": "defined(__AVX512DQ__)"                                                                 },
        { "instr_name": "kandn",      "datatypes": all_32bit,                    "template": tpl_implem_avx512["bitwise_2args"],                                                                                                },
        { "instr_name": "kandn",      "datatypes": all_16bit,                    "template": tpl_implem_avx512["bitwise_2args"],  "if": "defined(__AVX512BW__)"                                                                 },
        { "instr_name": "kandn",      "datatypes": all_8bit,                     "template": tpl_implem_avx512["bitwise_2args"],  "if": "defined(__AVX512BW__)"                                                                 } ], # kandn
    "xorb": [
        { "instr_name": "xor",        "datatypes": all_float,                    "template": tpl_implem_avx512["logi_2args"],     "if": "defined(__AVX512DQ__)"                                                                 },
        { "instr_name": "xor",        "datatypes": [int64, uint64],              "template": tpl_implem_avx512["logi_2args"],                                                                                                   },
        { "instr_name": "xor",        "datatypes": [int32, uint32],              "template": tpl_implem_avx512["logi_2args"],                                                                                                   },
        { "instr_name": "xor",        "datatypes": [int16, uint16],              "template": tpl_implem_avx512["logi_2args"],     "if": "defined(__AVX512BW__)"                                                                 },
        { "instr_name": "xor",        "datatypes": [int8, uint8],                "template": tpl_implem_avx512["logi_2args"],     "if": "defined(__AVX512BW__)"                                                                 } ], # xorb
    "xorb_k": [
        { "instr_name": "kxor",       "datatypes": all_64bit,                    "template": tpl_implem_avx512["bitwise_2args"],  "if": "defined(__AVX512DQ__)"                                                                 },
        { "instr_name": "kxor",       "datatypes": all_32bit,                    "template": tpl_implem_avx512["bitwise_2args"],                                                                                                },
        { "instr_name": "kxor",       "datatypes": all_16bit,                    "template": tpl_implem_avx512["bitwise_2args"],  "if": "defined(__AVX512BW__)"                                                                 },
        { "instr_name": "kxor",       "datatypes": all_8bit,                     "template": tpl_implem_avx512["bitwise_2args"],  "if": "defined(__AVX512BW__)"                                                                 } ], # xorb_k
    "orb": [
        { "instr_name": "or",         "datatypes": all_float,                    "template": tpl_implem_avx512["logi_2args"],     "if": "defined(__AVX512DQ__)"                                                                 },
        { "instr_name": "or",         "datatypes": [int64, uint64],              "template": tpl_implem_avx512["logi_2args"],                                                                                                   },
        { "instr_name": "or",         "datatypes": [int32, uint32],              "template": tpl_implem_avx512["logi_2args"],                                                                                                   },
        { "instr_name": "or",         "datatypes": [int16, uint16],              "template": tpl_implem_avx512["logi_2args"],     "if": "defined(__AVX512BW__)"                                                                 },
        { "instr_name": "or",         "datatypes": [int8, uint8],                "template": tpl_implem_avx512["logi_2args"],     "if": "defined(__AVX512BW__)"                                                                 } ], # orb
    "orb_k": [
        { "instr_name": "kor",        "datatypes": all_64bit,                    "template": tpl_implem_avx512["bitwise_2args"],  "if": "defined(__AVX512DQ__)"                                                                 },
        { "instr_name": "kor",        "datatypes": all_32bit,                    "template": tpl_implem_avx512["bitwise_2args"],                                                                                                },
        { "instr_name": "kor",        "datatypes": all_16bit,                    "template": tpl_implem_avx512["bitwise_2args"],  "if": "defined(__AVX512BW__)"                                                                 },
        { "instr_name": "kor",        "datatypes": all_8bit,                     "template": tpl_implem_avx512["bitwise_2args"],  "if": "defined(__AVX512BW__)"                                                                 } ], # orb_k
    "testz": [
        { "instr_name": "kortestz",   "datatypes": [int64, uint64],              "template": tpl_implem_avx512["testz_2args"],    "if": "defined(__AVX512DQ__)"                                                                 },
        { "instr_name": "kortestz",   "datatypes": [int32, uint32],              "template": tpl_implem_avx512["testz_2args"],    "if": "(defined (__AVX512F__) || defined(__MIC__) || defined(__KNCNI__))"                       },
        { "instr_name": "kortestz",   "datatypes": [int16, uint16],              "template": tpl_implem_avx512["testz_2args"],    "if": "defined (__AVX512BW__)"                                                                },
        { "instr_name": "kortestz",   "datatypes": [int8, uint8],                "template": tpl_implem_avx512["testz_2args"],    "if": "defined (__AVX512BW__)"                                                                } ], # testz
    "testz_2": [
        { "instr_name": "kortestz",   "datatypes": [int64, uint64],              "template": tpl_implem_avx512["testz_1arg"],     "if": "defined(__AVX512DQ__)"                                                                 },
        { "instr_name": "kortestz",   "datatypes": [int32, uint32],              "template": tpl_implem_avx512["testz_1arg"],     "if": "(defined (__AVX512F__) || defined(__MIC__) || defined(__KNCNI__))"                       },
        { "instr_name": "kortestz",   "datatypes": [int16, uint16],              "template": tpl_implem_avx512["testz_1arg"],     "if": "defined (__AVX512BW__)"                                                                },
        { "instr_name": "kortestz",   "datatypes": [int8, uint8],                "template": tpl_implem_avx512["testz_1arg"],     "if": "defined (__AVX512BW__)"                                                                } ], # testz_2
    "cmpeq": [
        { "instr_name": "cmpeq",      "datatypes": [int32, int64],               "template": tpl_implem_avx512["cmp_int"],                                                                                                      },
        { "instr_name": "cmpeq",      "datatypes": [int16, int8] ,               "template": tpl_implem_avx512["cmp_int"],        "if": "defined(__AVX512BW__)"                                                                 },
        { "instr_name": "cmp",        "datatypes": all_float,                    "template": tpl_implem_avx512["cmpeq_float"],                                                                                                  } ], # cmpeq
    "cmpneq": [
        { "instr_name": "cmp",        "datatypes": all_float,                    "template": tpl_implem_avx512["cmpneq_float"],                                                                                                 },
        { "instr_name": "cmpneq",     "datatypes": [int32, int64],               "template": tpl_implem_avx512["cmp_int"],                                                                                                      },
        { "instr_name": "cmpneq",     "datatypes": [int16, int8],                "template": tpl_implem_avx512["cmp_int"],        "if": "defined(__AVX512BW__)"                                                                 } ], # cmpneq
    "cmplt": [
        { "instr_name": "cmp",        "datatypes": all_float,                    "template": tpl_implem_avx512["cmplt_float"],                                                                                                  },
        { "instr_name": "cmplt",      "datatypes": [int32, int64],               "template": tpl_implem_avx512["cmp_int"],                                                                                                      },
        { "instr_name": "cmplt",      "datatypes": [int16, int8],                "template": tpl_implem_avx512["cmp_int"],        "if": "defined(__AVX512BW__)"                                                                 } ], # cmplt
    "cmple": [
        { "instr_name": "cmp",        "datatypes": all_float,                    "template": tpl_implem_avx512["cmple_float"],                                                                                                  },
        { "instr_name": "cmple",      "datatypes": [int32, int64],               "template": tpl_implem_avx512["cmp_int"],                                                                                                      },
        { "instr_name": "cmple",      "datatypes": [int16, int8],                "template": tpl_implem_avx512["cmp_int"],        "if": "defined(__AVX512BW__)"                                                                 } ], # cmple
    "cmpge": [
        { "instr_name": "cmpge",      "datatypes": [int32, int64],               "template": tpl_implem_avx512["cmp_int"],                                                                                                      },
        { "instr_name": "cmpge",      "datatypes": [int16, int8],                "template": tpl_implem_avx512["cmp_int"],        "if": "defined(__AVX512BW__)"                                                                 },
        { "instr_name": "cmp",        "datatypes": all_float,                    "template": tpl_implem_avx512["cmpge_float"],                                                                                                  } ], # cmpge
    "cmpgt": [
        { "instr_name": "cmp",        "datatypes": all_float,                    "template": tpl_implem_avx512["cmpgt_float"],                                                                                                  },
        { "instr_name": "cmpgt",      "datatypes": [int32, int64],               "template": tpl_implem_avx512["cmp_int"],                                                                                                      },
        { "instr_name": "cmpgt",      "datatypes": [int16, int8],                "template": tpl_implem_avx512["cmp_int"],        "if": "defined(__AVX512BW__)"                                                                 } ], # cmpgt
    "round": [
        { "instr_name": "round",      "datatypes": all_float,                    "template": tpl_implem_avx512["roundf"],         "if": "(defined(__MIC__) || defined(__KNCNI__))"                                                },
        { "instr_name": "roundscale", "datatypes": all_float,                    "template": tpl_implem_avx512["round"],          "if": "defined(__AVX512F__)"                                                                  } ], # round
    "blend": [
        { "instr_name": "blend",      "datatypes": all_float + [int64, int32],   "template": tpl_implem_avx512["blend"],          "if": "(defined(__MIC__) || defined(__KNCNI__) || defined(__AVX512__) || defined(__AVX512F__))" },
        { "instr_name": "blend",      "datatypes": [int8, int16],                "template": tpl_implem_avx512["blend"],          "if": "defined(__AVX512BW__)"                                                                 },
        { "instr_name": "blend",      "datatypes": all_uint,                     "template": tpl_implem_avx512["blend_emu"]                                                                                                     },], # blend
    "hadd": [
        { "instr_name": "add",        "datatypes": [float64, int64],             "template": tpl_implem_avx512["reduce_64"],                                                                                                    },
        { "instr_name": "add",        "datatypes": [float32, int32],             "template": tpl_implem_avx512["reduce_32"],                                                                                                    },
        { "instr_name": "adds",       "datatypes": [int16, uint16],              "template": tpl_implem_avx512["reduce_16"],      "if": "defined(__AVX512BW__)"                                                                 },
        { "instr_name": "adds",       "datatypes": [int8, uint8],                "template": tpl_implem_avx512["reduce_8"],       "if": "defined(__AVX512BW__)"                                                                 } ], # hadd
    "hmul": [
        { "instr_name": "mul",        "datatypes": [float64],                    "template": tpl_implem_avx512["reduce_64"],      "if": "defined(__AVX512F__)"                                                                  },
        { "instr_name": "mul",        "datatypes": [float32],                    "template": tpl_implem_avx512["reduce_32"],      "if": "defined(__AVX512F__)"                                                                  },
#       # this cannot work on (u)int32 because "_mm512_mul_epi32" is working on 64-bit elements
#       { "instr_name": "mul",        "datatypes": [int32],                      "template": tpl_implem_avx512["reduce_32"],      "if": "defined(__AVX512F__)"                                                                  },
        { "instr_name": "mullo",      "datatypes": [int16],                      "template": tpl_implem_avx512["reduce_16"],      "if": "defined(__AVX512BW__)"                                                                 } ], # hmul
    "hmin": [
        { "instr_name": "min",        "datatypes": [float64],                    "template": tpl_implem_avx512["reduce_64"],      "if": "defined(__AVX512F__)"                                                                  },
        { "instr_name": "min",        "datatypes": [float32],                    "template": tpl_implem_avx512["reduce_32"],      "if": "defined(__AVX512F__)"                                                                  },
        { "instr_name": "gmin",       "datatypes": [float64],                    "template": tpl_implem_avx512["reduce_64"],      "if": "(defined(__MIC__) || defined(__KNCNI__))"                                                },
        { "instr_name": "gmin",       "datatypes": [float32],                    "template": tpl_implem_avx512["reduce_32"],      "if": "(defined(__MIC__) || defined(__KNCNI__))"                                                },
        { "instr_name": "min",        "datatypes": [int32],                      "template": tpl_implem_avx512["reduce_32"],      "if": "defined(__AVX512F__)"                                                                  },
        { "instr_name": "min",        "datatypes": [int16],                      "template": tpl_implem_avx512["reduce_16"],      "if": "defined(__AVX512BW__)"                                                                 },
        { "instr_name": "min",        "datatypes": [int8],                       "template": tpl_implem_avx512["reduce_8"],       "if": "defined(__AVX512BW__)"                                                                 } ], # hmin
    "hmax": [
        { "instr_name": "max",        "datatypes": [float64],                    "template": tpl_implem_avx512["reduce_64"],      "if": "defined(__AVX512F__)"                                                                  },
        { "instr_name": "max",        "datatypes": [float32],                    "template": tpl_implem_avx512["reduce_32"],      "if": "defined(__AVX512F__)"                                                                  },
        { "instr_name": "gmax",       "datatypes": [float64],                    "template": tpl_implem_avx512["reduce_64"],      "if": "(defined(__MIC__) || defined(__KNCNI__))"                                                },
        { "instr_name": "gmax",       "datatypes": [float32],                    "template": tpl_implem_avx512["reduce_32"],      "if": "(defined(__MIC__) || defined(__KNCNI__))"                                                },
        { "instr_name": "max",        "datatypes": [int32],                      "template": tpl_implem_avx512["reduce_32"],      "if": "defined(__AVX512F__)"                                                                  },
        { "instr_name": "max",        "datatypes": [int16],                      "template": tpl_implem_avx512["reduce_16"],      "if": "defined(__AVX512BW__)"                                                                 },
        { "instr_name": "max",        "datatypes": [int8],                       "template": tpl_implem_avx512["reduce_8"],       "if": "defined(__AVX512BW__)"                                                                 } ], # hmax
    "maskz_add": [
        { "instr_name": "maskz_add",  "datatypes": all_float,                    "template": tpl_implem_avx512["arithmsk_2args"], "if": "defined(__AVX512F__)"                                                                  } ], # maskz_add
 }
