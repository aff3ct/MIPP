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
    
    #the datatypes dict contains k/v pairs with relevant information
    #to generate intrinsics. You can write {{isa_dt_reg.key}} and it will be replace 
    #with the value. Useful for genericity. 
    
    #I'm adding fields to it rn. It makes it more crowded and less legible. But it works.
    "datatypes": {
        float64 : {"data_ext" :    "f64m1", "data_ext_logi":    "64", "data_ext_msk": "b64", "reg" : "vfloat64m1_t", "msk" : "vbool64_t",
                   "to_ptr": "float64_t", "to_int": "vint64m1_t", "to_uint" : "vuint64m1_t", 
                   "to_float" : "vfloat64m1_t", "uint_data_ext" : "u64m1", "reg_dt_ext": "f64"} ,#added to_int_ptr to convert float to int before bitwise operations. I'll see if I can find a better solution later.
        
        float32 : {"data_ext" :    "f32m1", "data_ext_logi":    "32", "data_ext_msk": "b32", "reg" : "vfloat32m1_t", "msk" : "vbool32_t",
                   "to_ptr": "float32_t", "to_int": "vint64m1_t", "to_uint" : "vuint32m1_t", 
                   "to_float": "vfloat32m1_t", "uint_data_ext" : "u32m1", "reg_dt_ext" : "f32"} ,#added to_int_ptr to convert float to int before bitwise operations. I'll see if I can find a better solution later.
        
        int64   : {"data_ext" :    "i64m1", "data_ext_logi":    "64", "data_ext_msk": "b64", "reg" : "vint64m1_t",   "msk" : "vbool64_t",
                   "to_ptr": "int64_t", "to_int": "vint64m1_t", "to_uint" : "vuint64m1_t",
                   "to_float": "vfloat64m1_t", "reg_dt_ext" : "i64"} ,
        
        int32   : {"data_ext" :    "i32m1", "data_ext_logi":    "32", "data_ext_msk": "b32", "reg" : "vint32m1_t",   "msk" : "vbool32_t",
                   "to_ptr": "int32_t", "to_int": "vint32m1_t", "to_uint" : "vuint32m1_t",
                   "to_float": "vfloat32m1_t", "reg_dt_ext" : "i32"} ,
        
        int16   : {"data_ext" :    "i16m1", "data_ext_logi":    "16", "data_ext_msk": "b16", "reg" : "vint16m1_t",   "msk" : "vbool16_t",
                   "to_ptr": "int16_t", "to_int": "vint16m1_t", "to_uint" : "vuint16m1_t",
                   "to_float": "vfloat32m1_t", "reg_dt_ext" : "i16"} ,
        
        int8    : {"data_ext" :    "i8m1",  "data_ext_logi":    "8", "data_ext_msk": "b8", "reg" : "vint8m1_t",    "msk" : "vbool8_t",
                   "to_ptr": "int8_t", "to_int": "vint8m1_t", "to_uint" : "vuint8m1_t",
                   "to_float": "vfloat32m1_t", "reg_dt_ext" : "i8"} ,
        
        uint64  : {"data_ext" :    "u64m1", "data_ext_logi":    "64", "data_ext_msk": "b64", "reg" : "vuint64m1_t",  "msk" : "vbool64_t",
                   "to_ptr": "uint64_t", "to_int": "vint64m1_t", "to_uint" : "vuint64m1_t",
                   "to_float": "vfloat64m1_t", "reg_dt_ext" : "u64"} ,
        
        uint32  : {"data_ext" :    "u32m1", "data_ext_logi":    "32", "data_ext_msk": "b32", "reg" : "vuint32m1_t",  "msk" : "vbool32_t",
                   "to_ptr": "uint32_t", "to_int": "vint32m1_t", "to_uint" : "vuint32m1_t",
                   "to_float": "vfloat32m1_t", "reg_dt_ext" : "u32"} ,
        
        uint16  : {"data_ext" :    "u16m1", "data_ext_logi":    "16", "data_ext_msk": "b16", "reg" : "vuint16m1_t",  "msk" : "vbool16_t",
                   "to_ptr": "uint16_t", "to_int": "vint16m1_t", "to_uint" : "vuint16m1_t",
                   "to_float": "vfloat32m1_t", "reg_dt_ext" : "u16"} ,
        
        uint8   : {"data_ext" :    "u8m1",  "data_ext_logi":    "8", "data_ext_msk": "b8", "reg" : "vuint8m1_t",   "msk" : "vbool8_t",
                   "to_ptr": "uint8_t", "to_int": "vint8m1_t", "to_uint" : "vuint8m1_t",
                   "to_float": "vfloat32m1_t", "reg_dt_ext": "u8"} ,
    },
}#I added a bunch of keys to datatypes dictionnary bc they will be necessary for conversion.
#this solution is really unelegant and I might want to do it differently.

#list of templates 4 mnemonics 
"""
Load/store currently working. 

One smart thing I'll try to do is to "factorize" template 
i.e instructions sharing the same naming convention should be regrouped as much as possible. 

See : https://github.com/riscv-non-isa/riscv-rvv-intrinsic-doc/blob/main/doc/rvv-intrinsic-spec.adoc#explicit-naming-scheme 
for details
"""
tpl_implem_rvv = {
    "load":         { "format": "short", "code": "{{ isa.prefix }}_vle{{ isa_dt_par.data_ext_logi }}_v_{{ isa_dt_par.data_ext }}(({{ isa_dt_par.to_ptr }}*) p0, %N<tp>%);" },
	"store":        { "format": "short", "code": "{{ isa.prefix }}_vse{{ isa_dt_par.data_ext_logi}}_v_{{ isa_dt_par.data_ext }}(({{ isa_dt_par.to_ptr }}*) p0, r0.r , %N<tp>%);" },
      
    "arith_2args":  { "format": "short", "code": "{{ isa.prefix }}_v{{ instr_name }}_vv_{{ isa_dt_par.data_ext }}(r0.r, r1.r, %N<tp>%);" },
    "arith_m_2args": { "format": "short", "code": "{{ isa.prefix }}_v{{ instr_name }}(m0.m, m1.m, %N<tp>%);" },
      
    "float_bitwise": { "format": "long", "code": """
                         {{isa_dt_par.to_uint}} tmp1, tmp2;
                         tmp1 = {{isa.prefix}}_vfcvt_xu_f_v_{{isa_dt_par.uint_data_ext}}(r0.r, %N<tp>%);
                         tmp2 = {{isa.prefix}}_vfcvt_xu_f_v_{{isa_dt_par.uint_data_ext}}(r1.r, %N<tp>%);
                         tmp1 = {{ isa.prefix }}_v{{ instr_name }}_vv_{{ isa_dt_par.uint_data_ext }}(tmp1, tmp2, %N<tp>%);
                         %r<tp>% ret;
                         ret.r = {{ isa.prefix }}_vfcvt_f_xu_v_{{isa_dt_par.data_ext}}(tmp1, %N<tp>%);
                         return ret;
                         """},
      
    "float_set1":{"format": "short", "code" :"{{isa.prefix}}_{{ instr_name }}_s_f_{{isa_dt_par.data_ext}}(v0,%N<tp>%);"},
    "scalar_set1":{"format": "short", "code" :"{{isa.prefix}}_{{ instr_name }}_s_x_{{isa_dt_par.data_ext}}(v0,%N<tp>%);"},
      
    "float_set0":{"format": "short", "code" :"{{isa.prefix}}_{{ instr_name }}_s_f_{{isa_dt_par.data_ext}}(0.f,%N<tp>%);"},
    "scalar_set0":{"format": "short", "code" :"{{isa.prefix}}_{{ instr_name }}_s_x_{{isa_dt_par.data_ext}}(0,%N<tp>%);"},

    #same as arith_2args except "vvm" instead of "vv"
    "merge":  { "format": "short", "code": "{{ isa.prefix }}_v{{ instr_name }}_vvm_{{ isa_dt_par.data_ext }}(r1.r, r0.r, m0.m, %N<tp>%);" },

}

"""
this dictionnary keeps track of which instructions r implemented. 
Which template to use to generate them. Which type should be used w which template n so on.
"""
implems_rvv = {
    "load": [{ "instr_name": "load", "datatypes": all_datatypes, "template": tpl_implem_rvv["load"] }],
    "store": [{ "instr_name": "store", "datatypes": all_datatypes, "template": tpl_implem_rvv["store"] }],
    
    
    #arith_2args functions
    "add": [
		  { "instr_name": "fadd", "datatypes": all_float, "template": tpl_implem_rvv["arith_2args"]},
		  { "instr_name": "add", "datatypes": all_int_uint, "template": tpl_implem_rvv["arith_2args"] },
		],
    "sub": [
        { "instr_name": "fsub", "datatypes": all_float, "template": tpl_implem_rvv["arith_2args"]},
        { "instr_name": "sub", "datatypes": all_int_uint, "template": tpl_implem_rvv["arith_2args"] },
    ],
    
    "mul": [
        { "instr_name": "fmul", "datatypes": all_float, "template": tpl_implem_rvv["arith_2args"]},
		{ "instr_name": "mul", "datatypes": all_int_uint, "template": tpl_implem_rvv["arith_2args"] },
    ],
    
    "div": [{ "instr_name": "fdiv", "datatypes": all_float, "template": tpl_implem_rvv["arith_2args"]},],
    
    #bitwise either use arith_2args or a float emulation which casts to int, does the ob and cast back
    "andb":[ {"instr_name": "and", "datatypes": all_int_uint, "template": tpl_implem_rvv["arith_2args"]},
            {"instr_name": "and", "datatypes": all_float, "template": tpl_implem_rvv["float_bitwise"]} ],
    "orb":[ {"instr_name": "or", "datatypes": all_int_uint, "template": tpl_implem_rvv["arith_2args"]},
            {"instr_name": "or", "datatypes": all_float, "template": tpl_implem_rvv["float_bitwise"]} ],
    "xorb":[ {"instr_name": "xor", "datatypes": all_int_uint, "template": tpl_implem_rvv["arith_2args"]},
            {"instr_name": "xor", "datatypes": all_float, "template": tpl_implem_rvv["float_bitwise"]} ],

    #masked ops
    "andb_k":[{"instr_name": "mand", "datatypes" : all_datatypes, "template" : tpl_implem_rvv["arith_m_2args"]}],
    "orb_k":[{"instr_name": "mor", "datatypes" : all_datatypes, "template" : tpl_implem_rvv["arith_m_2args"]}],
    "xorb_k":[{"instr_name": "mxor", "datatypes" : all_datatypes, "template" : tpl_implem_rvv["arith_m_2args"]}],
    
    "set1": [ {"instr_name": "vmv", "datatypes" : all_int_uint, "template":tpl_implem_rvv["scalar_set1"] },
              {"instr_name": "vfmv","datatypes": all_float, "template":tpl_implem_rvv["float_set1"]}],
    "set0": [ {"instr_name": "vmv", "datatypes" : all_int_uint, "template":tpl_implem_rvv["scalar_set0"] },
              {"instr_name": "vfmv","datatypes": all_float, "template":tpl_implem_rvv["float_set0"]}],
    "blend": [{"instr_name": "merge", "datatypes": all_datatypes, "template" : tpl_implem_rvv["merge"]}],
}