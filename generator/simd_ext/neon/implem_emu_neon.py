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
    "msb-64": { "format": "long", "code":
"""// long format
	%r<tp>% rm = %cast<c:int|b:tp,tp>%(%set1<c:int|b:tp>%((int64_t)0x8000000000000000));
	return %andb<tp>%(r0, rm);""" },
    "msb-32": { "format": "long", "code":
"""// long format
	%r<tp>% rm = %cast<c:int|b:tp,tp>%(%set1<c:int|b:tp>%((int32_t)0x80000000));
	return %andb<tp>%(r0, rm);""" },
    "msb-16": { "format": "long", "code":
"""// long format
	%r<tp>% rm = %cast<c:int|b:tp,tp>%(%set1<c:int|b:tp>%((int16_t)0x8000));
	return %andb<tp>%(r0, rm);""" },
    "msb-8": { "format": "long", "code":
"""// long format
	%r<tp>% rm = %cast<c:int|b:tp,tp>%(%set1<c:int|b:tp>%((int8_t)0x80));
	return %andb<tp>%(r0, rm);""" },
    "min_emu": { "format": "long", "code": "return %blend<tp>%(r0, r1, %cmplt<tp>%(r0, r1));" },
    "max_emu": { "format": "long", "code": "return %blend<tp>%(r0, r1, %cmpgt<tp>%(r0, r1));" },
    "hadd_emu": { "format": "long", "code":
"""// long format
{% if isa_dt_par.to_ptr == 'float64_t' or isa_dt_par.to_ptr == 'int64_t' or isa_dt_par.to_ptr == 'uint64_t' -%}
	%r<tp>% r1;
	r1.r = vextq_{{ isa_dt_par.data_ext }}(r0.r, r0.r, 1);
	%r<tp>% res = %add<tp>%(r0, r1);
	return %get<tp>%(res, 0);
{% elif isa_dt_par.to_ptr == 'float32_t' or isa_dt_par.to_ptr == 'int32_t' or isa_dt_par.to_ptr == 'uint32_t' -%}
	%r<tp>% r1;
	r1.r = vextq_{{ isa_dt_par.data_ext }}(r0.r, r0.r, 2);
	%r<tp>% r2 = %add<tp>%(r0, r1);
	%r<tp>% r3;
	r3.r = vextq_{{ isa_dt_par.data_ext }}(r2.r, r2.r, 1);
	%r<tp>% res = %add<tp>%(r2, r3);
	return %get<tp>%(res, 0);
{% elif isa_dt_par.to_ptr == 'int16_t' or isa_dt_par.to_ptr == 'uint16_t' -%}
	%r<tp>% r1;
	r1.r = vextq_{{ isa_dt_par.data_ext }}(r0.r, r0.r, 4);
	%r<tp>% r2 = %add<tp>%(r0, r1);
	%r<tp>% r3;
	r3.r = vextq_{{ isa_dt_par.data_ext }}(r2.r, r2.r, 2);
	%r<tp>% r4 = %add<tp>%(r2, r3);
	%r<tp>% r5;
	r5.r = vextq_{{ isa_dt_par.data_ext }}(r4.r, r4.r, 1);
	%r<tp>% res = %add<tp>%(r4, r5);
	return %get<tp>%(res, 0);
{% else -%}
	%r<tp>% r1;
	r1.r = vextq_{{ isa_dt_par.data_ext }}(r0.r, r0.r, 8);
	%r<tp>% r2 = %add<tp>%(r0, r1);
	%r<tp>% r3;
	r3.r = vextq_{{ isa_dt_par.data_ext }}(r2.r, r2.r, 4);
	%r<tp>% r4 = %add<tp>%(r2, r3);
	%r<tp>% r5;
	r5.r = vextq_{{ isa_dt_par.data_ext }}(r4.r, r4.r, 2);
	%r<tp>% r6 = %add<tp>%(r4, r5);
	%r<tp>% r7;
	r7.r = vextq_{{ isa_dt_par.data_ext }}(r6.r, r6.r, 1);
	%r<tp>% res = %add<tp>%(r6, r7);
	return %get<tp>%(res, 0);
{% endif -%}""" },
    "hmul_emu": { "format": "long", "code":
"""// long format
{% if isa_dt_par.to_ptr == 'float64_t' or isa_dt_par.to_ptr == 'int64_t' or isa_dt_par.to_ptr == 'uint64_t' -%}
	%r<tp>% r1;
	r1.r = vextq_{{ isa_dt_par.data_ext }}(r0.r, r0.r, 1);
	%r<tp>% res = %mul<tp>%(r0, r1);
	return %get<tp>%(res, 0);
{% elif isa_dt_par.to_ptr == 'float32_t' or isa_dt_par.to_ptr == 'int32_t' or isa_dt_par.to_ptr == 'uint32_t' -%}
	%r<tp>% r1;
	r1.r = vextq_{{ isa_dt_par.data_ext }}(r0.r, r0.r, 2);
	%r<tp>% r2 = %mul<tp>%(r0, r1);
	%r<tp>% r3;
	r3.r = vextq_{{ isa_dt_par.data_ext }}(r2.r, r2.r, 1);
	%r<tp>% res = %mul<tp>%(r2, r3);
	return %get<tp>%(res, 0);
{% elif isa_dt_par.to_ptr == 'int16_t' or isa_dt_par.to_ptr == 'uint16_t' -%}
	%r<tp>% r1;
	r1.r = vextq_{{ isa_dt_par.data_ext }}(r0.r, r0.r, 4);
	%r<tp>% r2 = %mul<tp>%(r0, r1);
	%r<tp>% r3;
	r3.r = vextq_{{ isa_dt_par.data_ext }}(r2.r, r2.r, 2);
	%r<tp>% r4 = %mul<tp>%(r2, r3);
	%r<tp>% r5;
	r5.r = vextq_{{ isa_dt_par.data_ext }}(r4.r, r4.r, 1);
	%r<tp>% res = %mul<tp>%(r4, r5);
	return %get<tp>%(res, 0);
{% else -%}
	%r<tp>% r1;
	r1.r = vextq_{{ isa_dt_par.data_ext }}(r0.r, r0.r, 8);
	%r<tp>% r2 = %mul<tp>%(r0, r1);
	%r<tp>% r3;
	r3.r = vextq_{{ isa_dt_par.data_ext }}(r2.r, r2.r, 4);
	%r<tp>% r4 = %mul<tp>%(r2, r3);
	%r<tp>% r5;
	r5.r = vextq_{{ isa_dt_par.data_ext }}(r4.r, r4.r, 2);
	%r<tp>% r6 = %mul<tp>%(r4, r5);
	%r<tp>% r7;
	r7.r = vextq_{{ isa_dt_par.data_ext }}(r6.r, r6.r, 1);
	%r<tp>% res = %mul<tp>%(r6, r7);
	return %get<tp>%(res, 0);
{% endif -%}""" },
    "hmin_emu": { "format": "long", "code":
"""// long format
{% if isa_dt_par.to_ptr == 'float64_t' or isa_dt_par.to_ptr == 'int64_t' or isa_dt_par.to_ptr == 'uint64_t' -%}
	%r<tp>% r1;
	r1.r = vextq_{{ isa_dt_par.data_ext }}(r0.r, r0.r, 1);
	%r<tp>% res = %min<tp>%(r0, r1);
	return %get<tp>%(res, 0);
{% elif isa_dt_par.to_ptr == 'float32_t' or isa_dt_par.to_ptr == 'int32_t' or isa_dt_par.to_ptr == 'uint32_t' -%}
	%r<tp>% r1;
	r1.r = vextq_{{ isa_dt_par.data_ext }}(r0.r, r0.r, 2);
	%r<tp>% r2 = %min<tp>%(r0, r1);
	%r<tp>% r3;
	r3.r = vextq_{{ isa_dt_par.data_ext }}(r2.r, r2.r, 1);
	%r<tp>% res = %min<tp>%(r2, r3);
	return %get<tp>%(res, 0);
{% elif isa_dt_par.to_ptr == 'int16_t' or isa_dt_par.to_ptr == 'uint16_t' -%}
	%r<tp>% r1;
	r1.r = vextq_{{ isa_dt_par.data_ext }}(r0.r, r0.r, 4);
	%r<tp>% r2 = %min<tp>%(r0, r1);
	%r<tp>% r3;
	r3.r = vextq_{{ isa_dt_par.data_ext }}(r2.r, r2.r, 2);
	%r<tp>% r4 = %min<tp>%(r2, r3);
	%r<tp>% r5;
	r5.r = vextq_{{ isa_dt_par.data_ext }}(r4.r, r4.r, 1);
	%r<tp>% res = %min<tp>%(r4, r5);
	return %get<tp>%(res, 0);
{% else -%}
	%r<tp>% r1;
	r1.r = vextq_{{ isa_dt_par.data_ext }}(r0.r, r0.r, 8);
	%r<tp>% r2 = %min<tp>%(r0, r1);
	%r<tp>% r3;
	r3.r = vextq_{{ isa_dt_par.data_ext }}(r2.r, r2.r, 4);
	%r<tp>% r4 = %min<tp>%(r2, r3);
	%r<tp>% r5;
	r5.r = vextq_{{ isa_dt_par.data_ext }}(r4.r, r4.r, 2);
	%r<tp>% r6 = %min<tp>%(r4, r5);
	%r<tp>% r7;
	r7.r = vextq_{{ isa_dt_par.data_ext }}(r6.r, r6.r, 1);
	%r<tp>% res = %min<tp>%(r6, r7);
	return %get<tp>%(res, 0);
{% endif -%}""" },
    "hmax_emu": { "format": "long", "code":
"""// long format
{% if isa_dt_par.to_ptr == 'float64_t' or isa_dt_par.to_ptr == 'int64_t' or isa_dt_par.to_ptr == 'uint64_t' -%}
	%r<tp>% r1;
	r1.r = vextq_{{ isa_dt_par.data_ext }}(r0.r, r0.r, 1);
	%r<tp>% res = %max<tp>%(r0, r1);
	return %get<tp>%(res, 0);
{% elif isa_dt_par.to_ptr == 'float32_t' or isa_dt_par.to_ptr == 'int32_t' or isa_dt_par.to_ptr == 'uint32_t' -%}
	%r<tp>% r1;
	r1.r = vextq_{{ isa_dt_par.data_ext }}(r0.r, r0.r, 2);
	%r<tp>% r2 = %max<tp>%(r0, r1);
	%r<tp>% r3;
	r3.r = vextq_{{ isa_dt_par.data_ext }}(r2.r, r2.r, 1);
	%r<tp>% res = %max<tp>%(r2, r3);
	return %get<tp>%(res, 0);
{% elif isa_dt_par.to_ptr == 'int16_t' or isa_dt_par.to_ptr == 'uint16_t' -%}
	%r<tp>% r1;
	r1.r = vextq_{{ isa_dt_par.data_ext }}(r0.r, r0.r, 4);
	%r<tp>% r2 = %max<tp>%(r0, r1);
	%r<tp>% r3;
	r3.r = vextq_{{ isa_dt_par.data_ext }}(r2.r, r2.r, 2);
	%r<tp>% r4 = %max<tp>%(r2, r3);
	%r<tp>% r5;
	r5.r = vextq_{{ isa_dt_par.data_ext }}(r4.r, r4.r, 1);
	%r<tp>% res = %max<tp>%(r4, r5);
	return %get<tp>%(res, 0);
{% else -%}
	%r<tp>% r1;
	r1.r = vextq_{{ isa_dt_par.data_ext }}(r0.r, r0.r, 8);
	%r<tp>% r2 = %max<tp>%(r0, r1);
	%r<tp>% r3;
	r3.r = vextq_{{ isa_dt_par.data_ext }}(r2.r, r2.r, 4);
	%r<tp>% r4 = %max<tp>%(r2, r3);
	%r<tp>% r5;
	r5.r = vextq_{{ isa_dt_par.data_ext }}(r4.r, r4.r, 2);
	%r<tp>% r6 = %max<tp>%(r4, r5);
	%r<tp>% r7;
	r7.r = vextq_{{ isa_dt_par.data_ext }}(r6.r, r6.r, 1);
	%r<tp>% res = %max<tp>%(r6, r7);
	return %get<tp>%(res, 0);
{% endif -%}""" },
    "fmadd": { "format": "long", "code":
"""// long format
	%r<tp>% rmul = %mul<tp>%(r0, r1);
	%r<tp>% res = %add<tp>%(rmul, r2);
	return res;""" },
    "fnmadd": { "format": "long", "code":
"""// long format
	%r<tp>% rmul = %mul<tp>%(r0, r1);
	%r<tp>% tmp = %set0<tp>%();
	tmp = %sub<tp>%(tmp, rmul);
	%r<tp>% res = %add<tp>%(tmp, r2);
	return res;""" },
    "fmsub": { "format": "long", "code":
"""// long format
	%r<tp>% rmul = %mul<tp>%(r0, r1);
	%r<tp>% res = %sub<tp>%(rmul, r2);
	return res;""" },
    "fnmsub": { "format": "long", "code":
"""// long format
	%r<tp>% rmul = %mul<tp>%(r0, r1);
	%r<tp>% tmp = %set0<tp>%();
	tmp = %sub<tp>%(tmp, rmul);
	%r<tp>% res = %sub<tp>%(tmp, r2);
	return res;""" },
    "mul_emu_64": { "format": "long", "code":
"""// long format
	{{isa_dt_par.to_ptr}} tab[%N<tp>%] = {
		%get<tp>%(r0, 0) * %get<tp>%(r1, 0),
		%get<tp>%(r0, 1) * %get<tp>%(r1, 1)
	};
	return %set<tp>%(tab);""" },
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
    "msb": [
        { "datatypes": [float64, int64, uint64],         "template": tpl_implem_emu_neon["msb-64"],     "if": "defined(__aarch64__)" },
        { "datatypes": [float32, int32, uint32],         "template": tpl_implem_emu_neon["msb-32"]                                   },
        { "datatypes": [int16, uint16],                  "template": tpl_implem_emu_neon["msb-16"]                                   },
        { "datatypes": [int8, uint8],                    "template": tpl_implem_emu_neon["msb-8"]                                    } ], # msb
    "min": [
        { "datatypes": [int64, uint64],                  "template": tpl_implem_emu_neon["min_emu"],    "if": "defined(__aarch64__)" } ], # min
    "max": [
        { "datatypes": [int64, uint64],                  "template": tpl_implem_emu_neon["max_emu"],    "if": "defined(__aarch64__)" } ], # max
    "hadd": [
        { "datatypes": [float64],                        "template": tpl_implem_emu_neon["hadd_emu"],   "if": "defined(__aarch64__)" },
        { "datatypes": [float32] + all_int_uint,         "template": tpl_implem_emu_neon["hadd_emu"],                                } ], # hadd
    "hmul": [
        { "datatypes": [float64],                        "template": tpl_implem_emu_neon["hmul_emu"],   "if": "defined(__aarch64__)" },
        { "datatypes": [float32] + all_int_uint,         "template": tpl_implem_emu_neon["hmul_emu"],                                } ], # hmul
    "hmin": [
        { "datatypes": [float64],                        "template": tpl_implem_emu_neon["hmin_emu"],   "if": "defined(__aarch64__)" },
        { "datatypes": [float32] + all_int_uint,         "template": tpl_implem_emu_neon["hmin_emu"],                                } ], # hmin
    "hmax": [
        { "datatypes": [float64],                        "template": tpl_implem_emu_neon["hmax_emu"],   "if": "defined(__aarch64__)" },
        { "datatypes": [float32] + all_int_uint,         "template": tpl_implem_emu_neon["hmax_emu"],                                } ], # hmax
    "fmadd": [
        { "datatypes": [float64],                        "template": tpl_implem_emu_neon["fmadd"],      "if": "defined(__aarch64__)" },
        { "datatypes": [float32, int32],                 "template": tpl_implem_emu_neon["fmadd"]                                    } ], # fmadd
    "fnmadd": [
        { "datatypes": [float64],                        "template": tpl_implem_emu_neon["fnmadd"],     "if": "defined(__aarch64__)" },
        { "datatypes": [float32, int32],                 "template": tpl_implem_emu_neon["fnmadd"]                                   } ], # fnmadd
    "fmsub": [
        { "datatypes": [float64],                        "template": tpl_implem_emu_neon["fmsub"],      "if": "defined(__aarch64__)" },
        { "datatypes": [float32, int32],                 "template": tpl_implem_emu_neon["fmsub"]                                    } ], # fmsub
    "fnmsub": [
        { "datatypes": [float64],                        "template": tpl_implem_emu_neon["fnmsub"],     "if": "defined(__aarch64__)" },
        { "datatypes": [float32, int32],                 "template": tpl_implem_emu_neon["fnmsub"]                                   } ], # fnmsub
    "mul": [
        { "datatypes": [int64, uint64],                  "template": tpl_implem_emu_neon["mul_emu_64"], "if": "defined(__aarch64__)" } ], # mul
}
