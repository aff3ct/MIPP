from tools import *

tpl_implem_emu_sse = {
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
	res = %cast_k<c:int,tr>%(%cmpneq<c:int>%(%cast<tp,c:int>%(r0), zero));
	return res;""" },
    "get": { "format": "long", "code":
"""// long format
	%v<tp>% t[%N<tp>%];
	%storeu<tp>%(t, r0);
	return t[v0];""" },
    "get_k": { "format": "long", "code":
"""// long format
	%v<tp>% tmp[%N<tp>%];
	%r<tp>% rmsk = %toreg<tp>%(m0);
	%storeu<tp>%(tmp, rmsk);
	return (int32_t) tmp[v0];""" },
    "set1_k-8": { "format": "long", "code":
"""// long format
	%r<c:int>% tmp1 = %set1<c:int>%(v0 ? (int8_t)0xFF : (int8_t)0);
	%r<tp>% tmp2 = %cast<c:int,tp>%(tmp1);
	return %tomsk<tp>%(tmp2);""" },
    "set1_k-16": { "format": "long", "code":
"""// long format
	%r<c:int>% tmp1 = %set1<c:int>%(v0 ? (int16_t)0xFFFF : (int16_t)0);
	%r<tp>% tmp2 = %cast<c:int,tp>%(tmp1);
	return %tomsk<tp>%(tmp2);""" },
    "set1_k-32": { "format": "long", "code":
"""// long format
	%r<c:int>% tmp1 = %set1<c:int>%(v0 ? (int32_t)0xFFFFFFFF : (int32_t)0);
	%r<tp>% tmp2 = %cast<c:int,tp>%(tmp1);
	return %tomsk<tp>%(tmp2);""" },
    "set1_k-64": { "format": "long", "code":
"""// long format
	%r<c:int>% tmp1 = %set1<c:int>%(v0 ? (int64_t)0xFFFFFFFFFFFFFFFF : (int64_t)0);
	%r<tp>% tmp2 = %cast<c:int,tp>%(tmp1);
	return %tomsk<tp>%(tmp2);""" },
    "set_k-xxf":  { "format": "long",  "code": "return %cast_k<c:int,tr>%(%set_k<c:int>%(vals));" },
    "set_k-64": { "format": "short", "code": """_mm_set_epi64x(
		vals[1] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0,
		vals[0] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0);""" },
    "set_k-32": { "format": "short", "code": """_mm_set_epi32(
		vals[3] ? 0xFFFFFFFF : 0, vals[2] ? 0xFFFFFFFF : 0,
		vals[1] ? 0xFFFFFFFF : 0, vals[0] ? 0xFFFFFFFF : 0);""" },
    "set_k-16": { "format": "short", "code": """_mm_set_epi16(
		vals[ 7] ? 0xFFFF : 0, vals[ 6] ? 0xFFFF : 0,
		vals[ 5] ? 0xFFFF : 0, vals[ 4] ? 0xFFFF : 0,
		vals[ 3] ? 0xFFFF : 0, vals[ 2] ? 0xFFFF : 0,
		vals[ 1] ? 0xFFFF : 0, vals[ 0] ? 0xFFFF : 0);""" },
    "set_k-8": { "format": "short", "code": """_mm_set_epi8(
		vals[15] ? 0xFF : 0, vals[14] ? 0xFF : 0, vals[13] ? 0xFF : 0, vals[12] ? 0xFF : 0,
		vals[11] ? 0xFF : 0, vals[10] ? 0xFF : 0, vals[ 9] ? 0xFF : 0, vals[ 8] ? 0xFF : 0,
		vals[ 7] ? 0xFF : 0, vals[ 6] ? 0xFF : 0, vals[ 5] ? 0xFF : 0, vals[ 4] ? 0xFF : 0,
		vals[ 3] ? 0xFF : 0, vals[ 2] ? 0xFF : 0, vals[ 1] ? 0xFF : 0, vals[ 0] ? 0xFF : 0);""" },
        
	"andb_k_emu": { "format": "long", "code":
"""// long format
	%r<tp>% tmp1 = %toreg<tp>%(m0);
	%r<tp>% tmp2 = %toreg<tp>%(m1);
	%r<tp>% res = %andb<tp>%(tmp1, tmp2);
	return %tomsk<tp>%(res);""" },
    
	"fmadd": { "format": "long", "code":
"""// long format
	%r<tp>% res = %mul<tp>%(r0, r1);
	res = %add<tp>%(res, r2);
	return res;""" },
	"notb-64": { "format": "long", "code":
"""// long format
	%r<tp>% rm = %cast<c:int|b:tp,tp>%(%set1<c:int|b:tp>%((int64_t)0xFFFFFFFFFFFFFFFF));
	return %andnb<tp>%(r0, rm);""" },
	"notb-32": { "format": "long", "code":
"""// long format
	%r<tp>% rm = %cast<c:int|b:tp,tp>%(%set1<c:int|b:tp>%((int32_t)0xFFFFFFFF));
	return %andnb<tp>%(r0, rm);""" },
	"notb-16": { "format": "long", "code":
"""// long format
	%r<tp>% rm = %cast<c:int|b:tp,tp>%(%set1<c:int|b:tp>%((int16_t)0xFFFF));
	return %andnb<tp>%(r0, rm);""" },
	"notb-8": { "format": "long", "code":
"""// long format
	%r<tp>% rm = %cast<c:int|b:tp,tp>%(%set1<c:int|b:tp>%((int8_t)0xFF));
	return %andnb<tp>%(r0, rm);""" },
	"notb_k-64": { "format": "long", "code":
"""// long format
	%m<tp>% mm = %cast_k<c:int|b:tp,tp>%(%tomsk<c:int|b:tp>%(%set1<c:int|b:tp>%((int64_t)0xFFFFFFFFFFFFFFFF)));
	return %andnb_k<tp>%(m0, mm);""" },
	"notb_k-32": { "format": "long", "code":
"""// long format
	%m<tp>% mm = %cast_k<c:int|b:tp,tp>%(%tomsk<c:int|b:tp>%(%set1<c:int|b:tp>%((int32_t)0xFFFFFFFF)));
	return %andnb_k<tp>%(m0, mm);""" },
	"notb_k-16": { "format": "long", "code":
"""// long format
	%m<tp>% mm = %cast_k<c:int|b:tp,tp>%(%tomsk<c:int|b:tp>%(%set1<c:int|b:tp>%((int16_t)0xFFFF)));
	return %andnb_k<tp>%(m0, mm);""" },
	"notb_k-8": { "format": "long", "code":
"""// long format
	%m<tp>% mm = %cast_k<c:int|b:tp,tp>%(%tomsk<c:int|b:tp>%(%set1<c:int|b:tp>%((int8_t)0xFF)));
	return %andnb_k<tp>%(m0, mm);""" },
	"orb_k_emu": { "format": "long", "code":
"""// long format
	%r<tp>% tmp1 = %toreg<tp>%(m0);
	%r<tp>% tmp2 = %toreg<tp>%(m1);
	%r<tp>% res = %orb<tp>%(tmp1, tmp2);
	return %tomsk<tp>%(res);""" },
	"xorb_k_emu": { "format": "long", "code":
"""// long format
	%r<tp>% tmp1 = %toreg<tp>%(m0);
	%r<tp>% tmp2 = %toreg<tp>%(m1);
	%r<tp>% res = %xorb<tp>%(tmp1, tmp2);
	return %tomsk<tp>%(res);""" },
	"andnb_k_emu": { "format": "long", "code":
"""// long format
	%r<tp>% tmp1 = %toreg<tp>%(m0);
	%r<tp>% tmp2 = %toreg<tp>%(m1);
	%r<tp>% res = %andnb<tp>%(tmp1, tmp2);
	return %tomsk<tp>%(res);""" },
	"cmpeq_u": { "format": "long", "code":
"""// long format
	%r<c:int|b:tp>% r0s = %cast<tp,c:int|b:tp>%(r0);
	%r<c:int|b:tp>% r1s = %cast<tp,c:int|b:tp>%(r1);
	return %cast_k<c:int|b:tp,tp>%(%cmpeq<c:int|b:tp>%(r0s, r1s));""" },
	"cmpneq": { "format": "long", "code":
"""// long format
	return %notb_k<tp>%(%cmpeq<tp>%(r0, r1));""" },
	"cmpgt_u-64": { "format": "long", "code":
"""// long format
	%r<tp>% bias = %set1<tp>%((int64_t)0x8000000000000000);
	%r<tp>% r0_biased = %xorb<tp>%(r0, bias);
	%r<tp>% r1_biased = %xorb<tp>%(r1, bias);
	%r<c:int|b:tp>% r0s = %cast<tp,c:int|b:tp>%(r0_biased);
	%r<c:int|b:tp>% r1s = %cast<tp,c:int|b:tp>%(r1_biased);
	return %cast_k<c:int|b:tp,tp>%(%cmpgt<c:int|b:tp>%(r0s, r1s));""" },
	"cmpgt_u-32": { "format": "long", "code":
"""// long format
	%r<tp>% bias = %set1<tp>%((int32_t)0x80000000);
	%r<tp>% r0_biased = %xorb<tp>%(r0, bias);
	%r<tp>% r1_biased = %xorb<tp>%(r1, bias);
	%r<c:int|b:tp>% r0s = %cast<tp,c:int|b:tp>%(r0_biased);
	%r<c:int|b:tp>% r1s = %cast<tp,c:int|b:tp>%(r1_biased);
	return %cast_k<c:int|b:tp,tp>%(%cmpgt<c:int|b:tp>%(r0s, r1s));""" },
	"cmpgt_u-16": { "format": "long", "code":
"""// long format
	%r<tp>% bias = %set1<tp>%((int16_t)0x8000);
	%r<tp>% r0_biased = %xorb<tp>%(r0, bias);
	%r<tp>% r1_biased = %xorb<tp>%(r1, bias);
	%r<c:int|b:tp>% r0s = %cast<tp,c:int|b:tp>%(r0_biased);
	%r<c:int|b:tp>% r1s = %cast<tp,c:int|b:tp>%(r1_biased);
	return %cast_k<c:int|b:tp,tp>%(%cmpgt<c:int|b:tp>%(r0s, r1s));""" },
	"cmpgt_u-8": { "format": "long", "code":
"""// long format
	%r<tp>% bias = %set1<tp>%((int8_t)0x80);
	%r<tp>% r0_biased = %xorb<tp>%(r0, bias);
	%r<tp>% r1_biased = %xorb<tp>%(r1, bias);
	%r<c:int|b:tp>% r0s = %cast<tp,c:int|b:tp>%(r0_biased);
	%r<c:int|b:tp>% r1s = %cast<tp,c:int|b:tp>%(r1_biased);
	return %cast_k<c:int|b:tp,tp>%(%cmpgt<c:int|b:tp>%(r0s, r1s));""" },
	"cmplt_u_emu": { "format": "long", "code":
"""// long format
	return %cmpgt<tp>%(r1, r0);""" },
	"cmple_u_emu": { "format": "long", "code":
"""// long format
	return %notb_k<tp>%(%cmpgt<tp>%(r0, r1));""" },
	"cmpge_u_emu": { "format": "long", "code":
"""// long format
	return %notb_k<tp>%(%cmpgt<tp>%(r1, r0));""" },
}

implems_emu_sse = {
    "toreg"  : [
        { "datatypes": all_datatypes,            "template": tpl_implem_emu_sse["toreg"]                                    } ], # toreg
    "tomsk": [
        { "datatypes": all_datatypes,            "template": tpl_implem_emu_sse["tomsk"]                                    } ], # tomsk
    "get": [
        { "datatypes": all_datatypes,            "template": tpl_implem_emu_sse["get"]                                      } ], # get
    "get_k": [
        { "datatypes": all_datatypes,            "template": tpl_implem_emu_sse["get_k"]                                    } ], # get_k
    "set1_k":[
        { "datatypes": all_8bit,                 "template": tpl_implem_emu_sse["set1_k-8"]                                 },
        { "datatypes": all_16bit,                "template": tpl_implem_emu_sse["set1_k-16"]                                },
        { "datatypes": all_32bit,                "template": tpl_implem_emu_sse["set1_k-32"]                                },
        { "datatypes": all_64bit,                "template": tpl_implem_emu_sse["set1_k-64"]                                } ], # set1_k
    "set_k" : [
        { "datatypes": all_8bit,                 "template": tpl_implem_emu_sse["set_k-8"],     "if": "defined(__SSE2__)"   },
        { "datatypes": all_16bit,                "template": tpl_implem_emu_sse["set_k-16"],    "if": "defined(__SSE2__)"   },
        { "datatypes": [int32, uint32],          "template": tpl_implem_emu_sse["set_k-32"],    "if": "defined(__SSE2__)"   },
        { "datatypes": [int64, uint64],          "template": tpl_implem_emu_sse["set_k-64"],    "if": "defined(__SSE2__)"   },
        { "datatypes": [float64],                "template": tpl_implem_emu_sse["set_k-xxf"],   "if": "defined(__SSE2__)"   },
        { "datatypes": [float32],                "template": tpl_implem_emu_sse["set_k-xxf"],   "if": "defined(__SSE2__)"   } ], # set_k
    "andb_k": [
        { "datatypes": all_datatypes,            "template": tpl_implem_emu_sse["andb_k_emu"],  "if": "defined(__SSE2__)"   } ], # andb_k
        
    "fmadd" : [
        { "datatypes": all_float,                "template": tpl_implem_emu_sse["fmadd"]                                    } ], # fmadd
    "notb": [
        { "datatypes": all_64bit,                "template": tpl_implem_emu_sse["notb-64"],     "if": "defined(__SSE2__)"   },
        { "datatypes": all_32bit,                "template": tpl_implem_emu_sse["notb-32"],     "if": "defined(__SSE2__)"   },
        { "datatypes": all_16bit,                "template": tpl_implem_emu_sse["notb-16"],     "if": "defined(__SSE2__)"   },
        { "datatypes": all_8bit,                 "template": tpl_implem_emu_sse["notb-8"],      "if": "defined(__SSE2__)"   } ], # notb
    "notb_k": [
        { "datatypes": all_64bit,                "template": tpl_implem_emu_sse["notb_k-64"],   "if": "defined(__SSE2__)"   },
        { "datatypes": all_32bit,                "template": tpl_implem_emu_sse["notb_k-32"],   "if": "defined(__SSE2__)"   },
        { "datatypes": all_16bit,                "template": tpl_implem_emu_sse["notb_k-16"],   "if": "defined(__SSE2__)"   },
        { "datatypes": all_8bit,                 "template": tpl_implem_emu_sse["notb_k-8"],    "if": "defined(__SSE2__)"   } ], # notb_k
    "orb_k": [
        { "datatypes": all_datatypes,            "template": tpl_implem_emu_sse["orb_k_emu"],   "if": "defined(__SSE2__)"   } ], # orb_k
    "xorb_k": [
        { "datatypes": all_datatypes,            "template": tpl_implem_emu_sse["xorb_k_emu"],  "if": "defined(__SSE2__)"   } ], # xorb_k
    "andnb_k": [
        { "datatypes": all_datatypes,            "template": tpl_implem_emu_sse["andnb_k_emu"], "if": "defined(__SSE2__)"   } ], # andnb_k
    "cmpeq": [
        { "datatypes": [uint8, uint16, uint32],  "template": tpl_implem_emu_sse["cmpeq_u"],     "if": "defined(__SSE2__)"   },
        { "datatypes": [uint64],                 "template": tpl_implem_emu_sse["cmpeq_u"],     "if": "defined(__SSE4_1__)" } ], # cmpeq
    "cmpneq": [
        { "datatypes": [float64],                "template": tpl_implem_emu_sse["cmpneq"],      "if": "defined(__SSE2__)"   },
        { "datatypes": [int8, int16, int32],     "template": tpl_implem_emu_sse["cmpneq"],      "if": "defined(__SSE2__)"   },
        { "datatypes": [uint8, uint16, uint32],  "template": tpl_implem_emu_sse["cmpneq"],      "if": "defined(__SSE2__)"   },
        { "datatypes": [int64, uint64],          "template": tpl_implem_emu_sse["cmpneq"],      "if": "defined(__SSE4_1__)" } ], # cmpneq
    "cmpgt": [
        { "datatypes": [uint64],                 "template": tpl_implem_emu_sse["cmpgt_u-64"],  "if": "defined(__SSE4_2__)" },
        { "datatypes": [uint32],                 "template": tpl_implem_emu_sse["cmpgt_u-32"],  "if": "defined(__SSE2__)"   },
        { "datatypes": [uint16],                 "template": tpl_implem_emu_sse["cmpgt_u-16"],  "if": "defined(__SSE2__)"   },
        { "datatypes": [uint8],                  "template": tpl_implem_emu_sse["cmpgt_u-8"],   "if": "defined(__SSE2__)"   } ], # cmpgt
    "cmplt": [
        { "datatypes": [uint64],                 "template": tpl_implem_emu_sse["cmplt_u_emu"], "if": "defined(__SSE4_2__)" },
        { "datatypes": [uint32, uint16, uint8],  "template": tpl_implem_emu_sse["cmplt_u_emu"], "if": "defined(__SSE2__)"   } ], # cmplt
    "cmple": [
        { "datatypes": [uint64],                 "template": tpl_implem_emu_sse["cmple_u_emu"], "if": "defined(__SSE4_2__)" },
        { "datatypes": [uint32, uint16, uint8],  "template": tpl_implem_emu_sse["cmple_u_emu"], "if": "defined(__SSE2__)"   } ], # cmple
    "cmpge": [
        { "datatypes": [uint64],                 "template": tpl_implem_emu_sse["cmpge_u_emu"], "if": "defined(__SSE4_2__)" },
        { "datatypes": [uint32, uint16, uint8],  "template": tpl_implem_emu_sse["cmpge_u_emu"], "if": "defined(__SSE2__)"   } ], # cmpge
}
