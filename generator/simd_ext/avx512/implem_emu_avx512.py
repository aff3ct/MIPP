from tools import *

tpl_implem_emu_avx512 = {
    "toreg": { "format": "long", "code":
"""// long format
	%r<tr>% res;
	%r<c:int>% zero = %set1<c:int>%(0);
	%r<c:int>% one = %set1<c:int>%(~0);
	res.r = %cast<c:int,tr>%(%blend<c:int>%(m0, one, zero));
	ret res;""" },
    "tomsk": { "format": "long", "code":
"""// long format
	%m<tr>% res;
	%r<tp>% zero = %set0<tp>%();
	res.m = %cmpeq<c:int|b:32>%(%cast<tp,c:int|b:32>%(r0), zero);
	ret res;""" },
    "set0-f64": { "format": "long", "code":
"""// long format
	return %set1<c:float|b:tp,tp>%(0.0);""" },
    "set0-f32": { "format": "long", "code":
"""// long format
	return %set1<c:float|b:tp,tp>%(0.f);""" },
    "set0-32": { "format": "long", "code":
"""// long format
	return %set1<c:int|b:tp,tp>%(0);""" },
    "set-64f": { "format": "long", "code":
"""// long format
	return %cast_k<c:float,tp>%(_mm512_set_pd(vals[7], vals[6], vals[5], vals[4], vals[3], vals[2], vals[1], vals[0]));""" },
    "set-32f": { "format": "long", "code":
"""// long format
	return _mm512_set_ps(
		vals[15], vals[14], vals[13], vals[12],vals[11], vals[10], vals[ 9], vals[ 8],
		vals[ 7], vals[ 6], vals[ 5], vals[ 4],vals[ 3], vals[ 2], vals[ 1], vals[ 0]);""" },
    "set-64": { "format": "long", "code":
"""// long format
	return %cast_k<c:float,tp>%(_mm512_set_epi64((
		vals[15], vals[14], vals[13], vals[12],
		vals[11], vals[10], vals[ 9], vals[ 8],
		vals[ 7], vals[ 6], vals[ 5], vals[ 4],
		vals[ 3], vals[ 2], vals[ 1], vals[ 0])));""" },
    "set-32": { "format": "long", "code":
"""// long format
	return %cast_k<c:float,tp>%(_mm512_castsi512_ps(_mm512_set_epi32(vals[15], vals[14], vals[13], vals[12], vals[11], vals[10], vals[ 9], vals[ 8],
	                                                                 vals[ 7], vals[ 6], vals[ 5], vals[ 4], vals[ 3], vals[ 2], vals[ 1], vals[ 0])));"""},
    "set-16": { "format": "long", "code":
"""// long format
	return %cast_k<c:float,tp>%(_mm512_castsi512_ps(_mm512_set_epi16(
		vals[31], vals[30], vals[29], vals[28],
		vals[27], vals[26], vals[25], vals[24],
		vals[23], vals[22], vals[21], vals[20],
		vals[19], vals[18], vals[17], vals[16],
		vals[15], vals[14], vals[13], vals[12],
		vals[11], vals[10], vals[ 9], vals[ 8],
		vals[ 7], vals[ 6], vals[ 5], vals[ 4],
		vals[ 3], vals[ 2], vals[ 1], vals[ 0]));""" },
    "set-8": { "format": "long", "code":
"""// long format
	return %cast_k<c:float,tp>%(_mm512_castsi512_ps(_mm512_set_epi8(
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
		vals[ 3], vals[ 2], vals[ 1], vals[ 0]));""" },
    "set_k-64": { "format": "long", "code":
"""// long format
	%v<tp>% t[%N<tp>%] = {
		vals[0] ? 0xFFFFFFFFFFFFFFFF : 0,
		vals[1] ? 0xFFFFFFFFFFFFFFFF : 0,
		vals[2] ? 0xFFFFFFFFFFFFFFFF : 0,
		vals[3] ? 0xFFFFFFFFFFFFFFFF : 0,
		vals[4] ? 0xFFFFFFFFFFFFFFFF : 0,
		vals[5] ? 0xFFFFFFFFFFFFFFFF : 0,
		vals[6] ? 0xFFFFFFFFFFFFFFFF : 0,
		vals[7] ? 0xFFFFFFFFFFFFFFFF : 0 };
	%r<c:int|b:tp>% r0_32 = %set<c:int|b:tp>%(*t);
	%r<c:int|b:tp>% r1_32 = %set1<c:int|b:tp>%(0xFFFFFFFFFFFFFFFF);
	return %cmpneq<c:int|b:tp>%(r0_32, r1_32);""" },
    "set_k-32": { "format": "long", "code":
"""// long format
	%v<tp>% t[%N<tp>%] = {
		vals[ 0] ? 0xFFFFFFFF : 0, vals[ 1] ? 0xFFFFFFFF : 0,
		vals[ 2] ? 0xFFFFFFFF : 0, vals[ 3] ? 0xFFFFFFFF : 0,
		vals[ 4] ? 0xFFFFFFFF : 0, vals[ 5] ? 0xFFFFFFFF : 0,
		vals[ 6] ? 0xFFFFFFFF : 0, vals[ 7] ? 0xFFFFFFFF : 0,
		vals[ 8] ? 0xFFFFFFFF : 0, vals[ 9] ? 0xFFFFFFFF : 0,
		vals[10] ? 0xFFFFFFFF : 0, vals[11] ? 0xFFFFFFFF : 0,
		vals[12] ? 0xFFFFFFFF : 0, vals[13] ? 0xFFFFFFFF : 0,
		vals[14] ? 0xFFFFFFFF : 0, vals[15] ? 0xFFFFFFFF : 0 };
	%r<c:int|b:tp>% r0_32 = %set<c:int|b:tp>%(*t);
	%r<c:int|b:tp>% r1_32 = %set1<c:int|b:tp>%(0xFFFFFFFF);
	return %cmpneq<c:int|b:tp>%(r0_32, r1_32);""" },
    "set_k-16": { "format": "long", "code":
"""// long format
	%v<tp>% t[%N<tp>%] = {
		vals[ 0] ? 0xFFFF : 0, vals[ 1] ? 0xFFFF : 0,
		vals[ 2] ? 0xFFFF : 0, vals[ 3] ? 0xFFFF : 0,
		vals[ 4] ? 0xFFFF : 0, vals[ 5] ? 0xFFFF : 0,
		vals[ 6] ? 0xFFFF : 0, vals[ 7] ? 0xFFFF : 0,
		vals[ 8] ? 0xFFFF : 0, vals[ 9] ? 0xFFFF : 0,
		vals[10] ? 0xFFFF : 0, vals[11] ? 0xFFFF : 0,
		vals[12] ? 0xFFFF : 0, vals[13] ? 0xFFFF : 0,
		vals[14] ? 0xFFFF : 0, vals[15] ? 0xFFFF : 0,
		vals[16] ? 0xFFFF : 0, vals[17] ? 0xFFFF : 0,
		vals[18] ? 0xFFFF : 0, vals[19] ? 0xFFFF : 0,
		vals[20] ? 0xFFFF : 0, vals[21] ? 0xFFFF : 0,
		vals[22] ? 0xFFFF : 0, vals[23] ? 0xFFFF : 0,
		vals[24] ? 0xFFFF : 0, vals[25] ? 0xFFFF : 0,
		vals[26] ? 0xFFFF : 0, vals[27] ? 0xFFFF : 0,
		vals[28] ? 0xFFFF : 0, vals[29] ? 0xFFFF : 0,
		vals[30] ? 0xFFFF : 0, vals[31] ? 0xFFFF : 0 };
	%r<c:int|b:tp>% r0_32 = %set<c:int|b:tp>%(*t);
	%r<c:int|b:tp>% r1_32 = %set1<c:int|b:tp>%(0xFFFF);
	return %cmpneq<c:int|b:tp>%(r0_32, r1_32);""" },
    "set_k-8": {"format": "long", "code":
"""// long format
	%v<tp>% t[%N<tp>%] = {
		vals[ 0] ? 0xFF : 0, vals[ 1] ? 0xFF : 0, vals[ 2] ? 0xFF : 0, vals[ 3] ? 0xFF : 0,
		vals[ 4] ? 0xFF : 0, vals[ 5] ? 0xFF : 0, vals[ 6] ? 0xFF : 0, vals[ 7] ? 0xFF : 0,
		vals[ 8] ? 0xFF : 0, vals[ 9] ? 0xFF : 0, vals[10] ? 0xFF : 0, vals[11] ? 0xFF : 0,
		vals[12] ? 0xFF : 0, vals[13] ? 0xFF : 0, vals[14] ? 0xFF : 0, vals[15] ? 0xFF : 0,
		vals[16] ? 0xFF : 0, vals[17] ? 0xFF : 0, vals[18] ? 0xFF : 0, vals[19] ? 0xFF : 0,
		vals[20] ? 0xFF : 0, vals[21] ? 0xFF : 0, vals[22] ? 0xFF : 0, vals[23] ? 0xFF : 0,
		vals[24] ? 0xFF : 0, vals[25] ? 0xFF : 0, vals[26] ? 0xFF : 0, vals[27] ? 0xFF : 0,
		vals[28] ? 0xFF : 0, vals[29] ? 0xFF : 0, vals[30] ? 0xFF : 0, vals[31] ? 0xFF : 0,
		vals[32] ? 0xFF : 0, vals[33] ? 0xFF : 0, vals[34] ? 0xFF : 0, vals[35] ? 0xFF : 0,
		vals[36] ? 0xFF : 0, vals[37] ? 0xFF : 0, vals[38] ? 0xFF : 0, vals[39] ? 0xFF : 0,
		vals[40] ? 0xFF : 0, vals[41] ? 0xFF : 0, vals[42] ? 0xFF : 0, vals[43] ? 0xFF : 0,
		vals[44] ? 0xFF : 0, vals[45] ? 0xFF : 0, vals[46] ? 0xFF : 0, vals[47] ? 0xFF : 0 };
	%r<c:int|b:tp>% r0_32 = %set<c:int|b:tp>%(*t);
	%r<c:int|b:tp>% r1_32 = %set1<c:int|b:tp>%(0xFF);
	return %cmpneq<c:int|b:tp>%(r0_32, r1_32);""" },
    "set1_k-8": { "format": "long", "code":
"""// long format
	%r<c:int|b:tp>% r0_32 = %set1<c:int|b:tp>%(r0 ? 0xFFFFFFFFFFFFFFFF : 0);
	%r<c:int|b:tp>% r1_32 = %set1<c:int|b:tp>%(     0xFFFFFFFFFFFFFFFF    );
	return = %cmpneq<c:int|b:tp>%(r0_32, r1_32);""" },
    "set1_k-16": { "format": "long", "code":
"""// long format
	%r<c:int|b:tp>% r0_32 = %set1<c:int|b:tp>%(r0 ? 0xFFFFFFFF : 0);
	%r<c:int|b:tp>% r1_32 = %set1<c:int|b:tp>%(     0xFFFFFFFF    );
	return %cmpneq<c:int|b:tp>%(r0_32, r1_32);""" },
    "set1_k-32": { "format": "long", "code":
"""// long format
	%r<c:int|b:tp>% r0_32 = %set1<c:int|b:tp>%(r0 ? 0xFFFF : 0);
	%r<c:int|b:tp>% r1_32 = %set1<c:int|b:tp>%(     0xFFFF    );
	return %cmpneq<c:int|b:tp>%(r0_32, r1_32);""" },
    "set1_k-64": { "format": "long", "code":
"""// long format
	%r<c:int|b:tp>% r0_32 = %set1<c:int|b:tp>%(r0 ? 0xFF : 0);
	%r<c:int|b:tp>% r1_32 = %set1<c:int|b:tp>%( 0xFF    );
	return %cmpneq<c:int|b:tp>%(r0_32, r1_32); """ },
    "set0_k": { "format": "long", "code":
"""// long format
	%m<c:int|b:tp>% m  = 0;
	return _mm512_kxor(m, m);""" },
    "andb_fk" : { "format": "long",  "code":
"""// long format
	return (m0 & m1);""" },
    "andnb_fk" : { "format": "long",  "code":
"""// long format
	return ((~m0) & m1);""" },
    "xorb_k": { "format": "long",  "code":
"""// long format
	return (m0 ^ m1);""" },
    "orb_k": { "format": "long",  "code":
"""// long format
	return (m0 | m1);""" },
    "msb-64": { "format": "long", "code":
"""// long format
	%r<tp>% rm = %cast<c:int|b:tp,tp>%(%set1<c:int|b:tp>%(0x8000000000000000));
	return %andb<tp>%(r0, rm);""" },
    "msb-32": { "format": "long", "code":
"""// long format
	%r<tp>% rm = %cast<c:int|b:tp,tp>%(%set1<c:int|b:tp>%(0x80000000));
	return %andb<tp>%(r0, rm);""" },
    "msb-16": { "format": "long", "code":
"""// long format
	%r<tp>% rm = %cast<c:int|b:tp,tp>%(%set1<c:int|b:tp>%(0x8000));
	return %andb<tp>%(r0, rm);""" },
    "msb-8": { "format": "long", "code":
"""// long format
	%r<tp>% rm = %cast<c:int|b:tp,tp>%(%set1<c:int|b:tp>%(0x80));
	return %andb<tp>%(r0, rm);""" },
    "notb-64": { "format": "long", "code":
"""// long format
	%r<tp>% rm = %cast<c:int|b:tp,tp>%(%set1<c:int|b:tp>%(0xFFFFFFFFFFFFFFFF));
	return %andnb<tp>%(r0, rm);""" },
    "notb-32": { "format": "long", "code":
"""// long format
	%r<tp>% rm = %cast<c:int|b:tp,tp>%(%set1<c:int|b:tp>%(0xFFFFFFFF));
	return %andnb<tp>%(r0, rm);""" },
    "notb-16": { "format": "long", "code":
"""// long format
	%r<tp>% rm = %cast<c:int|b:tp,tp>%(%set1<c:int|b:tp>%(0xFFFF));
	return %andnb<tp>%(r0, rm);""" },
    "notb-8": { "format": "long", "code":
"""// long format
	%r<tp>% rm = %cast<c:int|b:tp,tp>%(%set1<c:int|b:tp>%(0xFF));
	return %andnb<tp>%(r0, rm);""" },
    "notb_k-8": { "format": "long", "code":
"""// long format
	return _mm512_knot(m0);""" },
    "notb_k-16": { "format": "long", "code":
"""// long format
	return _mm512_knot(m0);""" },
    "notb_k-32": { "format": "long", "code":
"""// long format
	return ~(m0);""" },
    "notb_k-64": { "format": "long", "code":
"""// long foramt
	return ~(m0);""" },
    "testz_2-64": { "format": "long",  "code":
"""// long format
	%r<c:int|b:tp>% r32 = %set0<c:int|b:tp>%();
	%m<c:int|b:tp>% msk = %cmpneq<c:int|b:tp>%(r0, r32);
	return _mm512_kortestz(msk,%set0<c:int|b:8>%());""" },
    "testz-64": { "format": "long", "code":
"""// long format
	%r<c:int|b:tp>% r32 = %set0<c:int|b:tp>%();
	%m<c:int|b:tp>% msk = %cmpneq<c:int|b:tp>%(r0, r32);
	return _mm512_kortestz(msk,%set0<c:int|b:8>%());""" },
    "testz_2-32" : { "format": "long",  "code":
"""// long format
	%r<c:int|b:tp>% r0_32 = %andb<c:int|b:tp>%(r0, r1);
	%r<c:int|b:tp>% r1_32 = %set0<c:int|b:tp>%();
	%m<c:int|b:tp>% msk   = %cmpneq<c:int|b:tp>%(r0_32, r1_32);
	return _mm512_kortestz(m32, %set0<c:int|b:16>%());""" },
    "testz_2-16-8" : { "format": "long",  "code":
"""// long format
	%r<c:int|b:tp>% r0_32 = %andb<c:int|b:tp>%(r0, r1);
	%r<c:int|b:tp>% r1_32 = %set0<c:int|b:tp>%();
	%m<c:int|b:tp>% msk   = %cmpneq<c:int|b:tp>%(r0_32, r1_32);
	return %cast<c:uint|b:tp,tp>%(m32 == 0);""" },
    "testz-32": { "format": "long", "code":
"""// long format
	%r<c:int|b:tp>% r32 = %set0<c:int|b:tp>%();
	%m<c:int|b:tp>% msk = %cmpneq<c:int|b:tp>%(r0, r32);
	return _mm512_kortestz(msk,%set0<c:int|b:16>%());""" },
    "testz-64": { "format": "long", "code":
"""// long format
	%r<c:int|b:tp>% r32 = %set0<c:int|b:tp>%();
	%m<c:int|b:tp>% msk = %cmpneq<c:int|b:tp>%(r0, r32);
	return _mm512_kortestz(msk,%set0<c:int|b:8>%());""" },
    "testz-16": { "format": "long", "code":
"""// long format
	%r<c:int|b:tp>% r32 = %set0<c:int|b:tp>%();
	%m<c:int|b:tp>% msk = %cmpneq<c:int|b:tp>%(r0, r32);
	return %cast<c:uint|b:64,tp>%(msk == 0);""" },
    "testz-8": { "format": "long", "code":
"""// long format
	%r<c:int|b:tp>% r32 = %set0<c:int|b:tp>%();
	%m<c:int|b:tp>% msk = %cmpneq<c:int|b:tp>%(r0, r32);
	return %cast<c:uint|b:64,tp>%(msk == 0);""" },
    "maskz_add": { "format": "long", "code":
"""// long format
	%r<tp>% radd = %add<tp>%(r0, r1);
	%r<tp>% rmsk = %toreg<tp>%(m0);
	return %andb<tp>%(rmsk, radd);""" },
    "getfirst_fromstore": { "format": "long", "code":
"""// long format
	%v<tp>% tmp[%N<tp>%];
	%store<tp>%(tmp, r);
	return tmp[0];""" },
    "hadd_to_scal": { "format": "long", "code":
"""// long format
	%r<tp>% reduced = %hadd<tp>%(r0);
	return %getfirst<tp>%(reduced);""" },
}

implems_emu_avx512 = {
    "toreg"  : [
        { "datatypes": all_datatypes,                "template": tpl_implem_emu_avx512["toreg"]                                                                                 } ], # toreg
    "tomsk": [
        { "datatypes": all_datatypes,                "template": tpl_implem_emu_avx512["tomsk"]                                                                                 } ], # tomsk
    "set" :[
        { "datatypes": [float64],                    "template": tpl_implem_emu_avx512["set-64f"],      "if": "defined(__AVX512F__)"                                            },
        { "datatypes": [float32],                    "template": tpl_implem_emu_avx512["set-32f"],      "if": "defined(__AVX512F__)"                                            },
        { "datatypes": [int32],                      "template": tpl_implem_emu_avx512["set-32"],       "if": "defined(__AVX512F__)"                                            },
        { "datatypes": [int64],                      "template": tpl_implem_emu_avx512["set-64"],       "if": "defined(__AVX512F__)"                                            },
        { "datatypes": [int16],                      "template": tpl_implem_emu_avx512["set-16"],       "if": "defined(__AVX512BW__)"                                           },
        { "datatypes": [int8],                       "template": tpl_implem_emu_avx512["set-8"],        "if": "defined(__AVX512BW__)"                                           } ], # set
    "set_k" : [
        { "datatypes": [int8],                       "template": tpl_implem_emu_avx512["set_k-8"],      "if": "defined(__AVX512F__)"                                            },
        { "datatypes": [int16] ,                     "template": tpl_implem_emu_avx512["set_k-16"],     "if": "defined(__AVX512F__)"                                            },
        { "datatypes": [int32] ,                     "template": tpl_implem_emu_avx512["set_k-32"],     "if": "defined(__AVX512BW__)"                                           },
        { "datatypes": [int64] ,                     "template": tpl_implem_emu_avx512["set_k-64"],     "if": "defined(__AVX512BW__)"                                           } ], # set_k
    "set1_k":[
        { "datatypes": [int8],                       "template": tpl_implem_emu_avx512["set1_k-8"]                                                                              },
        { "datatypes": [int16] ,                     "template": tpl_implem_emu_avx512["set1_k-16"]                                                                             },
        { "datatypes": [int32] ,                     "template": tpl_implem_emu_avx512["set1_k-32"]                                                                             },
        { "datatypes": [int64] ,                     "template": tpl_implem_emu_avx512["set1_k-64"]                                                                             } ], # set1_k
    # "set0_mk":[
    #     { "datatypes": [float64],                    "template": tpl_implem_emu_avx512["set0-f64"],     "if": "defined(__MIC__) || (__KNCNI__)"                                 },
    #     { "datatypes": [float32],                    "template": tpl_implem_emu_avx512["set0-f32"],     "if": "defined(__MIC__) || (__KNCNI__)"                                 },
    #     { "datatypes": [int32],                      "template": tpl_implem_emu_avx512["set0-32"],      "if": "defined(__MIC__) || (__KNCNI__)"                                 } ], # set0_mk
    "set0_k":[
        { "datatypes": all_int_uint,                 "template": tpl_implem_emu_avx512["set0_k"]                                                                                } ], # set0_k
    "andb_k": [
        { "datatypes": all_float,                    "template": tpl_implem_emu_avx512["andb_fk"],      "if": "defined(__AVX512BW__)"                                           } ], # andb_k
    "andnb_k": [
        { "datatypes": all_float,                    "template": tpl_implem_emu_avx512["andnb_fk"],     "if": "defined(__AVX512BW__)"                                           } ], # andnb_k
    "xorb_k": [
        { "datatypes": all_float,                    "template": tpl_implem_emu_avx512["xorb_k"],       "if": "defined(__AVX512BW__)"                                           } ], # xorb_k
    "orb_k": [
        { "datatypes": all_float,                    "template": tpl_implem_emu_avx512["orb_k"],        "if": "defined(__AVX512BW__)"                                           } ], # orb_k
    "msb": [
        { "datatypes": [float64, int64, uint64],     "template": tpl_implem_emu_avx512["msb-64"]                                                                                },
        { "datatypes": [float32, int32, uint32],     "template": tpl_implem_emu_avx512["msb-32"]                                                                                },
        { "datatypes": [int16, uint16],              "template": tpl_implem_emu_avx512["msb-16"]                                                                                },
        { "datatypes": [int8, uint8],                "template": tpl_implem_emu_avx512["msb-8"]                                                                                 } ], # msb
    "notb": [
        { "datatypes": [float64, int64],             "template": tpl_implem_emu_avx512["notb-64"]                                                                               },
        { "datatypes": [float32, int32],             "template": tpl_implem_emu_avx512["notb-32"]                                                                               },
        { "datatypes": [int16],                      "template": tpl_implem_emu_avx512["notb-16"]                                                                               },
        { "datatypes": [int8],                       "template": tpl_implem_emu_avx512["notb-8"]                                                                                } ], # notb
    "notb_k": [
        { "datatypes": [float64, int64],             "template": tpl_implem_emu_avx512["notb_k-64"]                                                                             },
        { "datatypes": [float32, int32],             "template": tpl_implem_emu_avx512["notb_k-32"]                                                                             },
        { "datatypes": [int16],                      "template": tpl_implem_emu_avx512["notb_k-16"]                                                                             },
        { "datatypes": [int8],                       "template": tpl_implem_emu_avx512["notb_k-8"]                                                                              } ], # notb_k
    "testz": [
        { "datatypes": [int32,uint32],               "template": tpl_implem_emu_avx512["testz-32"],     "if": "defined (__AVX512F__) || defined(__MIC__) || defined(__KNCNI__)" },
        { "datatypes": [int64,uint64 ],              "template": tpl_implem_emu_avx512["testz-64"],     "if": "defined (__AVX512F__) || defined(__MIC__) || defined(__KNCNI__)" },
        { "datatypes": [int16,uint16],               "template": tpl_implem_emu_avx512["testz-16"],     "if": "defined (__AVX512BW__)"                                          },
        { "datatypes": [int8,uint8],                 "template": tpl_implem_emu_avx512["testz-8"],      "if": "defined (__AVX512BW__)"                                          } ], # testz
    "testz_2": [
        { "datatypes": [int32, uint32],              "template": tpl_implem_emu_avx512["testz_2-32"],   "if": "defined (__AVX512F__) || defined(__MIC__) || defined(__KNCNI__)" },
        { "datatypes": [int64, uint64],              "template": tpl_implem_emu_avx512["testz_2-64"],   "if": "defined (__AVX512F__) || defined(__MIC__) || defined(__KNCNI__)" },
        { "datatypes": [int16, int8, uint16, uint8], "template": tpl_implem_emu_avx512["testz_2-16-8"], "if": "defined (__AVX512BW__)"                                          } ], # testz_2
    "maskz_add": [
        { "datatypes" : all_int,                     "template": tpl_implem_emu_avx512["maskz_add"]                                                                             } ], # maskz_add
    "getfirst": [
        { "datatypes" : all_datatypes,               "template": tpl_implem_emu_avx512["getfirst_fromstore"]                                                                    } ], # getfirst
    "hadd_to_scal": [
        { "datatypes" : all_datatypes,               "template": tpl_implem_emu_avx512["hadd_to_scal"]                                                                          } ], # hadd_to_scal
}
