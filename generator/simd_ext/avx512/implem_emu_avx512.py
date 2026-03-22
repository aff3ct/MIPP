from tools import *

tpl_implem_emu_avx512 = {
    "toreg": { "format": "long", "code":
"""// long format
	%r<tr>% res;
	%r<c:int>% zero = %set1<c:int>%(0);
	%r<c:int>% one = %set1<c:int>%(~0);
	res = %cast<c:int,tr>%(%blend<c:int>%(one, zero, %cast_k<tp,c:int>%(m0)));
	return res;""" },
    "tomsk": { "format": "long", "code":
"""// long format
	%m<tr>% res;
	%r<c:int>% zero = %set0<c:int>%();
	res = %cast_k<c:int,tr>%(%cmpeq<c:int>%(%cast<tp,c:int>%(r0), zero));
	return res;""" },
    "set1_k-8": { "format": "long", "code":
"""// long format
	%r<c:int|b:tp>% r0_32 = %set1<c:int|b:tp>%(v0 ? 0xFFFFFFFFFFFFFFFF : 0);
	%r<c:int|b:tp>% r1_32 = %set1<c:int|b:tp>%(     0xFFFFFFFFFFFFFFFF    );
	return %cmpneq<c:int|b:tp>%(r0_32, r1_32);""" },
    "set1_k-16": { "format": "long", "code":
"""// long format
	%r<c:int|b:tp>% r0_32 = %set1<c:int|b:tp>%(v0 ? 0xFFFFFFFF : 0);
	%r<c:int|b:tp>% r1_32 = %set1<c:int|b:tp>%(     0xFFFFFFFF    );
	return %cmpneq<c:int|b:tp>%(r0_32, r1_32);""" },
    "set1_k-32": { "format": "long", "code":
"""// long format
	%r<c:int|b:tp>% r0_32 = %set1<c:int|b:tp>%(v0 ? 0xFFFF : 0);
	%r<c:int|b:tp>% r1_32 = %set1<c:int|b:tp>%(     0xFFFF    );
	return %cmpneq<c:int|b:tp>%(r0_32, r1_32);""" },
    "set1_k-64": { "format": "long", "code":
"""// long format
	%r<c:int|b:tp>% r0_32 = %set1<c:int|b:tp>%(v0 ? 0xFF : 0);
	%r<c:int|b:tp>% r1_32 = %set1<c:int|b:tp>%( 0xFF    );
	return %cmpneq<c:int|b:tp>%(r0_32, r1_32); """ },
    "set_k-64": { "format": "long", "code":
"""// long format
	%v<tp>% t[%N<tp>%] = {
		(int64_t)(vals[0] ? 0xFFFFFFFFFFFFFFFF : 0),
		(int64_t)(vals[1] ? 0xFFFFFFFFFFFFFFFF : 0),
		(int64_t)(vals[2] ? 0xFFFFFFFFFFFFFFFF : 0),
		(int64_t)(vals[3] ? 0xFFFFFFFFFFFFFFFF : 0),
		(int64_t)(vals[4] ? 0xFFFFFFFFFFFFFFFF : 0),
		(int64_t)(vals[5] ? 0xFFFFFFFFFFFFFFFF : 0),
		(int64_t)(vals[6] ? 0xFFFFFFFFFFFFFFFF : 0),
		(int64_t)(vals[7] ? 0xFFFFFFFFFFFFFFFF : 0) };
	%r<c:int|b:tp>% r0_32 = %set<c:int|b:tp>%(t);
	%r<c:int|b:tp>% r1_32 = %set1<c:int|b:tp>%(0xFFFFFFFFFFFFFFFF);
	return %cmpneq<c:int|b:tp>%(r0_32, r1_32);""" },
    "set_k-32": { "format": "long", "code":
"""// long format
	%v<tp>% t[%N<tp>%] = {
		(int32_t)(vals[ 0] ? 0xFFFFFFFF : 0), (int32_t)(vals[ 1] ? 0xFFFFFFFF : 0),
		(int32_t)(vals[ 2] ? 0xFFFFFFFF : 0), (int32_t)(vals[ 3] ? 0xFFFFFFFF : 0),
		(int32_t)(vals[ 4] ? 0xFFFFFFFF : 0), (int32_t)(vals[ 5] ? 0xFFFFFFFF : 0),
		(int32_t)(vals[ 6] ? 0xFFFFFFFF : 0), (int32_t)(vals[ 7] ? 0xFFFFFFFF : 0),
		(int32_t)(vals[ 8] ? 0xFFFFFFFF : 0), (int32_t)(vals[ 9] ? 0xFFFFFFFF : 0),
		(int32_t)(vals[10] ? 0xFFFFFFFF : 0), (int32_t)(vals[11] ? 0xFFFFFFFF : 0),
		(int32_t)(vals[12] ? 0xFFFFFFFF : 0), (int32_t)(vals[13] ? 0xFFFFFFFF : 0),
		(int32_t)(vals[14] ? 0xFFFFFFFF : 0), (int32_t)(vals[15] ? 0xFFFFFFFF : 0) };
	%r<c:int|b:tp>% r0_32 = %set<c:int|b:tp>%(t);
	%r<c:int|b:tp>% r1_32 = %set1<c:int|b:tp>%(0xFFFFFFFF);
	return %cmpneq<c:int|b:tp>%(r0_32, r1_32);""" },
    "set_k-16": { "format": "long", "code":
"""// long format
	%v<tp>% t[%N<tp>%] = {
		(int16_t)(vals[ 0] ? 0xFFFF : 0), (int16_t)(vals[ 1] ? 0xFFFF : 0),
		(int16_t)(vals[ 2] ? 0xFFFF : 0), (int16_t)(vals[ 3] ? 0xFFFF : 0),
		(int16_t)(vals[ 4] ? 0xFFFF : 0), (int16_t)(vals[ 5] ? 0xFFFF : 0),
		(int16_t)(vals[ 6] ? 0xFFFF : 0), (int16_t)(vals[ 7] ? 0xFFFF : 0),
		(int16_t)(vals[ 8] ? 0xFFFF : 0), (int16_t)(vals[ 9] ? 0xFFFF : 0),
		(int16_t)(vals[10] ? 0xFFFF : 0), (int16_t)(vals[11] ? 0xFFFF : 0),
		(int16_t)(vals[12] ? 0xFFFF : 0), (int16_t)(vals[13] ? 0xFFFF : 0),
		(int16_t)(vals[14] ? 0xFFFF : 0), (int16_t)(vals[15] ? 0xFFFF : 0),
		(int16_t)(vals[16] ? 0xFFFF : 0), (int16_t)(vals[17] ? 0xFFFF : 0),
		(int16_t)(vals[18] ? 0xFFFF : 0), (int16_t)(vals[19] ? 0xFFFF : 0),
		(int16_t)(vals[20] ? 0xFFFF : 0), (int16_t)(vals[21] ? 0xFFFF : 0),
		(int16_t)(vals[22] ? 0xFFFF : 0), (int16_t)(vals[23] ? 0xFFFF : 0),
		(int16_t)(vals[24] ? 0xFFFF : 0), (int16_t)(vals[25] ? 0xFFFF : 0),
		(int16_t)(vals[26] ? 0xFFFF : 0), (int16_t)(vals[27] ? 0xFFFF : 0),
		(int16_t)(vals[28] ? 0xFFFF : 0), (int16_t)(vals[29] ? 0xFFFF : 0),
		(int16_t)(vals[30] ? 0xFFFF : 0), (int16_t)(vals[31] ? 0xFFFF : 0) };
	%r<c:int|b:tp>% r0_32 = %set<c:int|b:tp>%(t);
	%r<c:int|b:tp>% r1_32 = %set1<c:int|b:tp>%(0xFFFF);
	return %cmpneq<c:int|b:tp>%(r0_32, r1_32);""" },
    "set_k-8": {"format": "long", "code":
"""// long format
	%v<tp>% t[%N<tp>%] = {
		(int8_t)(vals[ 0] ? 0xFF : 0), (int8_t)(vals[ 1] ? 0xFF : 0), (int8_t)(vals[ 2] ? 0xFF : 0), (int8_t)(vals[ 3] ? 0xFF : 0),
		(int8_t)(vals[ 4] ? 0xFF : 0), (int8_t)(vals[ 5] ? 0xFF : 0), (int8_t)(vals[ 6] ? 0xFF : 0), (int8_t)(vals[ 7] ? 0xFF : 0),
		(int8_t)(vals[ 8] ? 0xFF : 0), (int8_t)(vals[ 9] ? 0xFF : 0), (int8_t)(vals[10] ? 0xFF : 0), (int8_t)(vals[11] ? 0xFF : 0),
		(int8_t)(vals[12] ? 0xFF : 0), (int8_t)(vals[13] ? 0xFF : 0), (int8_t)(vals[14] ? 0xFF : 0), (int8_t)(vals[15] ? 0xFF : 0),
		(int8_t)(vals[16] ? 0xFF : 0), (int8_t)(vals[17] ? 0xFF : 0), (int8_t)(vals[18] ? 0xFF : 0), (int8_t)(vals[19] ? 0xFF : 0),
		(int8_t)(vals[20] ? 0xFF : 0), (int8_t)(vals[21] ? 0xFF : 0), (int8_t)(vals[22] ? 0xFF : 0), (int8_t)(vals[23] ? 0xFF : 0),
		(int8_t)(vals[24] ? 0xFF : 0), (int8_t)(vals[25] ? 0xFF : 0), (int8_t)(vals[26] ? 0xFF : 0), (int8_t)(vals[27] ? 0xFF : 0),
		(int8_t)(vals[28] ? 0xFF : 0), (int8_t)(vals[29] ? 0xFF : 0), (int8_t)(vals[30] ? 0xFF : 0), (int8_t)(vals[31] ? 0xFF : 0),
		(int8_t)(vals[32] ? 0xFF : 0), (int8_t)(vals[33] ? 0xFF : 0), (int8_t)(vals[34] ? 0xFF : 0), (int8_t)(vals[35] ? 0xFF : 0),
		(int8_t)(vals[36] ? 0xFF : 0), (int8_t)(vals[37] ? 0xFF : 0), (int8_t)(vals[38] ? 0xFF : 0), (int8_t)(vals[39] ? 0xFF : 0),
		(int8_t)(vals[40] ? 0xFF : 0), (int8_t)(vals[41] ? 0xFF : 0), (int8_t)(vals[42] ? 0xFF : 0), (int8_t)(vals[43] ? 0xFF : 0),
		(int8_t)(vals[44] ? 0xFF : 0), (int8_t)(vals[45] ? 0xFF : 0), (int8_t)(vals[46] ? 0xFF : 0), (int8_t)(vals[47] ? 0xFF : 0) };
	%r<c:int|b:tp>% r0_32 = %set<c:int|b:tp>%(t);
	%r<c:int|b:tp>% r1_32 = %set1<c:int|b:tp>%(0xFF);
	return %cmpneq<c:int|b:tp>%(r0_32, r1_32);""" },
    "andb_k" : { "format": "long",  "code":
"""// long format
	return (m0 & m1);""" },
    "andnb_k" : { "format": "long",  "code":
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
    "notb": { "format": "long", "code":
"""// long format
	%r<tp>% rm = %cast<c:int|b:tp,tp>%(%set1<c:int|b:tp>%(~0));
	return %andnb<tp>%(r0, rm);""" },
    "notb_k": { "format": "long", "code":
"""// long format
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
    "set1_k":[
        { "datatypes": [int64],                      "template": tpl_implem_emu_avx512["set1_k-8"]                                                                              },
        { "datatypes": [int32],                      "template": tpl_implem_emu_avx512["set1_k-16"]                                                                             },
        { "datatypes": [int16],                      "template": tpl_implem_emu_avx512["set1_k-32"]                                                                             },
        { "datatypes": [int8],                       "template": tpl_implem_emu_avx512["set1_k-64"]                                                                             } ], # set1_k
    "set_k" : [
        { "datatypes": [int64],                      "template": tpl_implem_emu_avx512["set_k-64"],                                                                             },
        { "datatypes": [int32],                      "template": tpl_implem_emu_avx512["set_k-32"],                                                                             },
        { "datatypes": [int16],                      "template": tpl_implem_emu_avx512["set_k-16"],                                                                             },
        { "datatypes": [int8],                       "template": tpl_implem_emu_avx512["set_k-8"],                                                                              } ], # set_k
    # "andb_k": [
    #     { "datatypes": all_datatypes,                "template": tpl_implem_emu_avx512["andb_k"],       "if": "defined(__AVX512BW__)"                                           } ], # andb_k
    # "andnb_k": [
    #     { "datatypes": all_datatypes,                "template": tpl_implem_emu_avx512["andnb_k"],      "if": "defined(__AVX512BW__)"                                           } ], # andnb_k
    # "xorb_k": [
    #     { "datatypes": all_datatypes,                "template": tpl_implem_emu_avx512["xorb_k"],       "if": "defined(__AVX512BW__)"                                           } ], # xorb_k
    # "orb_k": [
    #     { "datatypes": all_datatypes,                "template": tpl_implem_emu_avx512["orb_k"],        "if": "defined(__AVX512BW__)"                                           } ], # orb_k
    # "notb_k": [
    #     { "datatypes": all_datatypes,                "template": tpl_implem_emu_avx512["notb_k"]                                                                                } ], # notb_k
    "msb": [
        { "datatypes": [float64, int64, uint64],     "template": tpl_implem_emu_avx512["msb-64"]                                                                                },
        { "datatypes": [float32, int32, uint32],     "template": tpl_implem_emu_avx512["msb-32"]                                                                                },
        { "datatypes": [int16, uint16],              "template": tpl_implem_emu_avx512["msb-16"]                                                                                },
        { "datatypes": [int8, uint8],                "template": tpl_implem_emu_avx512["msb-8"]                                                                                 } ], # msb
    "notb": [
        { "datatypes": all_datatypes,                "template": tpl_implem_emu_avx512["notb"]                                                                                  } ], # notb
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
