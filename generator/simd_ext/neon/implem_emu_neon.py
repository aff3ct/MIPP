from tools import *

tpl_implem_emu_neon = {
    "set0":   { "format": "long", "code": "return %set1<tp>%(0);"},
    "set0_k": { "format": "long", "code": "return %tomsk<tp>%(%set1<tp>%(0));"},
    "set":    { "format": "long", "code": "return %loadu<tp>%(vals);"},
    "get":    { "format": "long", "code":
"""// long format
	%v<tp>% t[%N<tp>%];
	%storeu<tp>%(t, r0);
	return t[v0];""" },
    "get_k":  { "format": "long", "code": "return %get<tp>%(%toreg<tp>%(m0), v0);"},
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
    "set_k-64": { "format": "long", "code":
"""//long format
	uint64_t tab[%N<tp>%] = {
		vals[0] ? (uint64_t)0xFFFFFFFFFFFFFFFFU : (uint64_t)0,
		vals[1] ? (uint64_t)0xFFFFFFFFFFFFFFFFU : (uint64_t)0 };
	return %tomsk<tp>%(%cast<c:uint,tp>%(%set<c:uint>%(tab)));""" },
    "set_k-32": { "format": "long", "code":
"""//long format
	uint32_t tab[%N<tp>%] = {
		vals[0] ? (uint32_t)0xFFFFFFFFU : (uint32_t)0, vals[1] ? (uint32_t)0xFFFFFFFFU : (uint32_t)0,
		vals[2] ? (uint32_t)0xFFFFFFFFU : (uint32_t)0, vals[3] ? (uint32_t)0xFFFFFFFFU : (uint32_t)0 };
	return %tomsk<tp>%(%cast<c:uint,tp>%(%set<c:uint>%(tab)));""" },
    "set_k-16": { "format": "long", "code":
"""//long format
	uint16_t tab[%N<tp>%] = {
		vals[ 0] ? (uint16_t)0xFFFFU : (uint16_t)0, vals[ 1] ? (uint16_t)0xFFFFU : (uint16_t)0,
		vals[ 2] ? (uint16_t)0xFFFFU : (uint16_t)0, vals[ 3] ? (uint16_t)0xFFFFU : (uint16_t)0,
		vals[ 4] ? (uint16_t)0xFFFFU : (uint16_t)0, vals[ 5] ? (uint16_t)0xFFFFU : (uint16_t)0,
		vals[ 6] ? (uint16_t)0xFFFFU : (uint16_t)0, vals[ 7] ? (uint16_t)0xFFFFU : (uint16_t)0 };
	return %tomsk<tp>%(%cast<c:uint,tp>%(%set<c:uint>%(tab)));""" },
    "set_k-8": { "format": "long", "code":
"""//long format
	uint8_t tab[%N<tp>%] = {
		vals[ 0] ? (uint8_t)0xFFU : (uint8_t)0, vals[ 1] ? (uint8_t)0xFFU : (uint8_t)0, vals[ 2] ? (uint8_t)0xFFU : (uint8_t)0, (uint8_t)vals[ 3] ? (uint8_t)0xFFU : (uint8_t)0,
		vals[ 4] ? (uint8_t)0xFFU : (uint8_t)0, vals[ 5] ? (uint8_t)0xFFU : (uint8_t)0, vals[ 6] ? (uint8_t)0xFFU : (uint8_t)0, (uint8_t)vals[ 7] ? (uint8_t)0xFFU : (uint8_t)0,
		vals[ 8] ? (uint8_t)0xFFU : (uint8_t)0, vals[ 9] ? (uint8_t)0xFFU : (uint8_t)0, vals[10] ? (uint8_t)0xFFU : (uint8_t)0, (uint8_t)vals[11] ? (uint8_t)0xFFU : (uint8_t)0,
		vals[12] ? (uint8_t)0xFFU : (uint8_t)0, vals[13] ? (uint8_t)0xFFU : (uint8_t)0, vals[14] ? (uint8_t)0xFFU : (uint8_t)0, (uint8_t)vals[15] ? (uint8_t)0xFFU : (uint8_t)0 };
	return %tomsk<tp>%(%cast<c:uint,tp>%(%set<c:uint>%(tab)));""" },
    "notb": { "format": "long", "code":
"""// long format
	%r<c:int>% ones = %set1<c:int>%(-1);
	%r<c:int>% r0i = %cast<tp,c:int>%(r0);
	return %cast<c:int,tp>%(%andnb<c:int>%(r0i, ones));""" },
    "notb_k": { "format": "long", "code":
"""// long format
	%r<c:int>% ones = %set1<c:int>%(-1);
	%r<c:int>% r0i = %cast<tp,c:int>%(%toreg<tp>%(m0));
	return %tomsk<tp>%(%cast<c:int,tp>%(%andnb<c:int>%(r0i, ones)));""" },
    "cmpneq": { "format": "long", "code": "return %notb_k<tp>%(%cmpeq<tp>%(r0, r1));" },
}

implems_emu_neon = {
    "set0": [
        { "datatypes": all_64bit,                        "template": tpl_implem_emu_neon["set0"],       "if": "defined(__aarch64__)" },
        { "datatypes": all_32bit + all_16bit + all_8bit, "template": tpl_implem_emu_neon["set0"],                                    } ], # set0
    "set0_k": [
        { "datatypes": all_64bit,                        "template": tpl_implem_emu_neon["set0_k"],     "if": "defined(__aarch64__)" },
        { "datatypes": all_32bit + all_16bit + all_8bit, "template": tpl_implem_emu_neon["set0_k"],                                  } ], # set0_k
    "set": [
        { "datatypes": all_64bit,                        "template": tpl_implem_emu_neon["set"],        "if": "defined(__aarch64__)" },
        { "datatypes": all_32bit + all_16bit + all_8bit, "template": tpl_implem_emu_neon["set"],                                     } ], # set
    "set1_k":[
        { "datatypes": all_8bit,                         "template": tpl_implem_emu_neon["set1_k-8"],                                },
        { "datatypes": all_16bit,                        "template": tpl_implem_emu_neon["set1_k-16"],                               },
        { "datatypes": all_32bit,                        "template": tpl_implem_emu_neon["set1_k-32"],                               },
        { "datatypes": all_64bit,                        "template": tpl_implem_emu_neon["set1_k-64"],  "if": "defined(__aarch64__)" } ], # set1_k
    "set_k" : [
        { "datatypes": [int8, uint8],                    "template": tpl_implem_emu_neon["set_k-8"],                                 },
        { "datatypes": [int16, uint16],                  "template": tpl_implem_emu_neon["set_k-16"],                                },
        { "datatypes": [int32, uint32],                  "template": tpl_implem_emu_neon["set_k-32"],                                },
        { "datatypes": [int64, uint64],                  "template": tpl_implem_emu_neon["set_k-64"],   "if": "defined(__aarch64__)" },
        { "datatypes": [float64],                        "template": tpl_implem_emu_neon["set_k-xxf"],  "if": "defined(__aarch64__)" },
        { "datatypes": [float32],                        "template": tpl_implem_emu_neon["set_k-xxf"],                               } ], # set_k
    "get": [
        { "datatypes": all_64bit,                        "template": tpl_implem_emu_neon["get"],        "if": "defined(__aarch64__)" },
        { "datatypes": all_32bit + all_16bit + all_8bit, "template": tpl_implem_emu_neon["get"],                                     } ], # get
    "get_k": [
        { "datatypes": all_64bit,                        "template": tpl_implem_emu_neon["get_k"],      "if": "defined(__aarch64__)" },
        { "datatypes": all_32bit + all_16bit + all_8bit, "template": tpl_implem_emu_neon["get_k"],                                   } ], # get_k
    "notb": [
        { "datatypes": all_datatypes,                    "template": tpl_implem_emu_neon["notb"],                                    } ], # notb
    "notb_k": [
        { "datatypes": all_datatypes,                    "template": tpl_implem_emu_neon["notb_k"],                                  } ], # notb_k
    "cmpneq": [
        { "datatypes": all_64bit,                        "template": tpl_implem_emu_neon["cmpneq"],     "if": "defined(__aarch64__)" },
        { "datatypes": all_32bit + all_16bit + all_8bit, "template": tpl_implem_emu_neon["cmpneq"],                                  } ], # cmpneq
}
