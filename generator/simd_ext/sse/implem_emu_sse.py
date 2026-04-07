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
}

implems_emu_sse = {
    "toreg"  : [
        { "datatypes": all_datatypes,                "template": tpl_implem_emu_sse["toreg"]                                    } ], # toreg
    "tomsk": [
        { "datatypes": all_datatypes,                "template": tpl_implem_emu_sse["tomsk"]                                    } ], # tomsk
    "get": [
        { "datatypes": all_datatypes,                "template": tpl_implem_emu_sse["get"]                                      } ], # get
    "get_k": [
        { "datatypes": all_datatypes,                "template": tpl_implem_emu_sse["get_k"]                                    } ], # get_k
    "set1_k":[
        { "datatypes": [int8, uint8],                  "template": tpl_implem_emu_sse["set1_k-8"],                              },
        { "datatypes": [int16, uint16],                "template": tpl_implem_emu_sse["set1_k-16"],                             },
        { "datatypes": [int32, uint32, float32],       "template": tpl_implem_emu_sse["set1_k-32"],                             },
        { "datatypes": [int64, uint64, float64],       "template": tpl_implem_emu_sse["set1_k-64"],                             } ], # set1_k
     "set_k" : [
        { "datatypes": [int8, uint8],                  "template": tpl_implem_emu_sse["set_k-8"],    "if": "defined(__SSE2__)"  },
        { "datatypes": [int16, uint16],                "template": tpl_implem_emu_sse["set_k-16"],   "if": "defined(__SSE2__)"  },
        { "datatypes": [int32, uint32],                "template": tpl_implem_emu_sse["set_k-32"],   "if": "defined(__SSE2__)"  },
        { "datatypes": [int64, uint64],                "template": tpl_implem_emu_sse["set_k-64"],   "if": "defined(__SSE2__)"  },
        { "datatypes": [float64],                      "template": tpl_implem_emu_sse["set_k-xxf"],  "if": "defined(__SSE2__)"  },
        { "datatypes": [float32],                      "template": tpl_implem_emu_sse["set_k-xxf"],  "if": "defined(__SSE2__)"  } ], # set_k
}
