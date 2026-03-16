from tools import *

"""
From what I understand I can kinda do whatever I want with 
WHAT I put inside of the keys of the dictionnary, as long as I don't touch them. 
Touching them implies modifying c_generator.py. Which I don't want to do if I don't have to. 

data_ext field : contains the name of the type in intrinsics. 

data_ext_logi : repurposed to hold size as plain text which is used sometimes
data_ext_msk : repurposed to hold vector2register (vf/vx) operation
reg : contains the vector types
msk : contains the mask type used w this vector type
to_ptr : the scalar type to convert to

IMPORTANT : atm we'll make things easy by only supporting lmul=1. 

rvv intrinsincs/types embed the lmul value in their notation 
i.e the format is : v{type}{size}{lmul}_t 

So we'll limit ourselves to v{type}{size}m1_t rn
I'm not sure how easy it would be to add lmul support w this code structure. I'll ask.

If I want to add stuff, I think I just need to add elements in line 62 of c_generator.py 
i.e : pre_rendering = j2_template.render(isa=isa, instr_name=instr_name, dt_par=datatypes[dt_par], dt_ret=datatypes[dt_ret], isa_dt_par=isa["datatypes"][dt_par], isa_dt_ret=isa["datatypes"][dt_ret], cstdint_ret=datatypes[dt_ret]["cstd"])


n.b : data_ext_msk not used atm. Could be leveraged 4 optimisation (using registers instead of vectors and so on)
"""
isa_rvv = {
    "name": "rvv",#idk
    "prefix": "__riscv", #to prefix intrinsics, not used for types
    "size": {128 , 256 , 512 , 1024 , 2048}, #Support lmul at some point
    "define": "__riscv_v_intrinsic", #define to check is isa exists
    "architecture": "Risc-V",#used for smth ig
    "hw_lmul": True, #yeah
    "datatypes": {
        float64 : {"data_ext" :    "f64m1", "data_ext_logi":    "64", "data_ext_msk": "vf", "reg" : "vfloat64m1_t", "msk" : "vbool1_t", "to_ptr": "float64_t"} ,
        float32 : {"data_ext" :    "f32m1", "data_ext_logi":    "32", "data_ext_msk": "vf", "reg" : "vfloat32m1_t", "msk" : "vbool1_t", "to_ptr": "float32_t"} ,
        int64   : {"data_ext" :    "i64m1", "data_ext_logi":    "64", "data_ext_msk": "vx", "reg" : "vint64m1_t",   "msk" : "vbool1_t", "to_ptr": "int64_t"} ,
        int32   : {"data_ext" :    "i32m1", "data_ext_logi":    "32", "data_ext_msk": "vx", "reg" : "vint32m1_t",   "msk" : "vbool1_t", "to_ptr": "int32_t"} ,
        int16   : {"data_ext" :    "i16m1", "data_ext_logi":    "16", "data_ext_msk": "vx", "reg" : "vint16m1_t",   "msk" : "vbool1_t", "to_ptr": "int16_t"} ,
        int8    : {"data_ext" :    "i8m1",  "data_ext_logi":    "8", "data_ext_msk": "vx", "reg" : "vint8m1_t",    "msk" : "vbool1_t", "to_ptr": "int8_t"} ,
        uint64  : {"data_ext" :    "u64m1", "data_ext_logi":    "64", "data_ext_msk": "vx", "reg" : "vuint64m1_t",  "msk" : "vbool1_t", "to_ptr": "uint64_t"} ,
        uint32  : {"data_ext" :    "u32m1", "data_ext_logi":    "32", "data_ext_msk": "vx", "reg" : "vuint32m1_t",  "msk" : "vbool1_t", "to_ptr": "uint32_t"} ,
        uint16  : {"data_ext" :    "u16m1", "data_ext_logi":    "16", "data_ext_msk": "vx", "reg" : "vuint16m1_t",  "msk" : "vbool1_t", "to_ptr": "uint16_t"} ,
        uint8   : {"data_ext" :    "u8m1",  "data_ext_logi":    "8", "data_ext_msk": "vx", "reg" : "vuint8m1_t",   "msk" : "vbool1_t", "to_ptr": "uint8_t"} ,
    },
}#I think this is ok to start doing things :)

#list of templates 4 mnemonics 
"""
Load/store currently working. 

One smart thing I'll try to do is to "factorize" template 
i.e instructions sharing the same naming convention should be regrouped as much as possible. 

See : https://github.com/riscv-non-isa/riscv-rvv-intrinsic-doc/blob/main/doc/rvv-intrinsic-spec.adoc#explicit-naming-scheme 
for details
"""
tpl_implem_rvv = {
    	"load":         { "format": "short", "code": "{{ isa.prefix }}_vle{{ isa_dt_par.data_ext_logi }}_v_{{ isa_dt_par.data_ext }}(({{ isa_dt_par.to_ptr }}*) p0, MIPP_RVV_VL/sizeof({{isa_dt_par.to_ptr}}));" },
	    "store":        { "format": "short", "code": "{{ isa.prefix }}_vse{{ isa_dt_par.data_ext_logi}}_v_{{ isa_dt_par.data_ext }}(({{ isa_dt_par.to_ptr }}*) p0, r0.r , MIPP_RVV_VL/sizeof({{isa_dt_par.to_ptr}}));" },
        "arith_2args":  { "format": "short", "code": "{{ isa.prefix }}_v{{ instr_name }}_vv_{{ isa_dt_par.data_ext }}(r0.r, r1.r, MIPP_RVV_VL/sizeof({{isa_dt_par.to_ptr}}));" },

}

"""
this dictionnary keeps track of which instructions r implemented. 
Which template to use to generate them. Which type should be used w which template n so on.
"""
implems_rvv = {
    "load": [{ "instr_name": "load", "datatypes": all_datatypes, "template": tpl_implem_rvv["load"] }],
    "store": [{ "instr_name": "store", "datatypes": all_datatypes, "template": tpl_implem_rvv["store"] }],
    "add": [
		{ "instr_name": "fadd", "datatypes": all_float, "template": tpl_implem_rvv["arith_2args"]},
		{ "instr_name": "add", "datatypes": all_int_uint, "template": tpl_implem_rvv["arith_2args"] },
		],
    "sub": [
        { "instr_name": "fsub", "datatypes": all_float, "template": tpl_implem_rvv["arith_2args"]},
        { "instr_name": "sub", "datatypes": all_int_uint, "template": tpl_implem_rvv["arith_2args"] },
        ],
  }