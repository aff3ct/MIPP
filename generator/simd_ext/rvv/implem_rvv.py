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
                   "to_float" : "vfloat64m1_t", "uint_data_ext" : "u64m1", "int_data_ext" : "i64m1", "reg_dt_ext": "f64"} ,#added to_int_ptr to convert float to int before bitwise operations. I'll see if I can find a better solution later.
        
        float32 : {"data_ext" :    "f32m1", "data_ext_logi":    "32", "data_ext_msk": "b32", "reg" : "vfloat32m1_t", "msk" : "vbool32_t",
                   "to_ptr": "float32_t", "to_int": "vint64m1_t", "to_uint" : "vuint32m1_t", 
                   "to_float": "vfloat32m1_t", "uint_data_ext" : "u32m1", "int_data_ext" : "i32m1", "reg_dt_ext" : "f32"} ,#added to_int_ptr to convert float to int before bitwise operations. I'll see if I can find a better solution later.
        
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

#list of templates 4 intrinsics
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
    "arith_1arg":  { "format": "short", "code": "{{ isa.prefix }}_v{{ instr_name }}_v_{{ isa_dt_par.data_ext }}(r0.r, %N<tp>%);" },
      
    "arith_2args":  { "format": "short", "code": "{{ isa.prefix }}_v{{ instr_name }}_vv_{{ isa_dt_par.data_ext }}(r0.r, r1.r, %N<tp>%);" },
    "mask_2args": { "format": "short", "code": "{{ isa.prefix }}_v{{ instr_name }}(m0.m, m1.m, %N<tp>%);" },


    #arith_2args but with mask dt extension at the end
    "arith_msk_type_2args":  { "format": "short", "code": "{{ isa.prefix }}_v{{ instr_name }}_vv_{{ isa_dt_par.data_ext }}_{{isa_dt_par.data_ext_msk}}(r0.r, r1.r, %N<tp>%);" },
    
    
    "float_bitwise": { "format": "long", "code": """
                         {{isa_dt_par.to_uint}} tmp1, tmp2;
                         tmp1 = {{ isa.prefix }}_vreinterpret_v_{{isa_dt_par.data_ext}}_{{isa_dt_par.uint_data_ext}}(r0.r);
                         tmp2 = {{ isa.prefix }}_vreinterpret_v_{{isa_dt_par.data_ext}}_{{isa_dt_par.uint_data_ext}}(r1.r);
                         tmp1 = {{ isa.prefix }}_v{{ instr_name }}_vv_{{ isa_dt_par.uint_data_ext }}(tmp1, tmp2, %N<tp>%);
                         %r<tp>% ret;
                         ret.r = {{ isa.prefix }}_vreinterpret_v_{{isa_dt_par.uint_data_ext}}_{{isa_dt_par.data_ext}}(tmp1);
                         return ret;
                         """},
      
    "float_set1":{"format": "long", "code" :"""
        %r<tp>% r0;
        r0.r = {{isa.prefix}}_{{ instr_name }}_v_f_{{isa_dt_par.data_ext}}(v0,%N<tp>%);
        //r0.r = {{isa.prefix}}_vrgather_vx_{{isa_dt_par.data_ext}}(r0.r,0,%N<tp>%);
        return r0;
    """},
    "scalar_set1":{"format": "long", "code" :"""
        %r<tp>% r0;
        r0.r = {{isa.prefix}}_{{ instr_name }}_v_x_{{isa_dt_par.data_ext}}(v0,%N<tp>%);
        //r0.r = {{isa.prefix}}_vrgather_vx_{{isa_dt_par.data_ext}}(r0.r,0,%N<tp>%);
        return r0;
    """},
      
    "float_set0":{"format": "short", "code" :"{{isa.prefix}}_{{ instr_name }}_v_f_{{isa_dt_par.data_ext}}(0.f,%N<tp>%);"},
    "scalar_set0":{"format": "short", "code" :"{{isa.prefix}}_{{ instr_name }}_v_x_{{isa_dt_par.data_ext}}(0,%N<tp>%);"},

    #same as arith_2args except "vvm" instead of "vv"
    "merge":  { "format": "short", "code": "{{ isa.prefix }}_v{{ instr_name }}_vvm_{{ isa_dt_par.data_ext }}(r1.r, r0.r, m0.m, %N<tp>%);" },

    #arithmetic w predicate (mask)
    "arithmsk_2args":{ "format": "short", "code": "{{ isa.prefix }}_v{{ instr_name }}_vv_{{ isa_dt_par.data_ext }}_mu(m0.m, r0.r, r0.r, r1.r, %N<tp>%);" },

    "arith_3args":{"format": "short", "code":"{{ isa.prefix }}_v{{ instr_name }}_vv_{{ isa_dt_par.data_ext }}(r0.r, r1.r, r2.r, %N<tp>%);"},

    "maskst" : {"format" : "short", "code" : "{{ isa.prefix }}_vse{{ isa_dt_par.data_ext_logi }}_v_{{ isa_dt_par.data_ext }}_m(m0.m,({{isa_dt_par.to_ptr}}*)p0, r0.r, %N<tp>%);"},

    "scalar_getfirst":{"format":"short", "code": "{{isa_dt_par.to_ptr}} res = {{ isa.prefix }}_v{{ instr_name }}_x_s_{{isa_dt_par.data_ext}}_{{isa_dt_par.reg_dt_ext}}(r0.r);"},
    "float_getfirst":{"format":"short", "code": "{{isa_dt_par.to_ptr}} res = {{ isa.prefix }}_v{{ instr_name }}_f_s_{{isa_dt_par.data_ext}}_{{isa_dt_par.reg_dt_ext}}(r0.r);"},


    "scalar_notb":{"format":"short", "code": "{{isa.prefix}}_v{{instr_name}}_vx_{{isa_dt_par.data_ext}}(r0.r, -1, %N<tp>%);"},
    "float_notb":{"format": "long", "code": """
        {{isa_dt_par.to_uint}} tmp = {{ isa.prefix }}_vreinterpret_v_{{isa_dt_par.data_ext}}_{{isa_dt_par.uint_data_ext}}(r0.r);
        tmp = {{isa.prefix}}_v{{instr_name}}_vx_{{isa_dt_par.uint_data_ext}}(tmp, -1, %N<tp>%);
        %r<tp>% ret;
        ret.r = {{ isa.prefix }}_vreinterpret_v_{{isa_dt_par.uint_data_ext}}_{{isa_dt_par.data_ext}}(tmp);
        return ret;
    """},
    
    "testz_2" : {"format": "short", "code": "   int32_t res = !({{isa.prefix}}_v{{instr_name}}_m_{{isa_dt_par.data_ext_msk}}(m0.m, %N<tp>%));"},

   "round_intuint": {"format": "short", "code": "res = r0;"},
   "round_float": {"format": "short", "code": "{{isa.prefix}}_{{instr_name}}_x_f_v_{{isa_dt_par.int_data_ext}}(r0.r,__RISCV_FRM_RNE,%N<tp>%)"},



   "fmadd_int" : {"format" : "long", "code" : """
    %r<tp>% res = %mul<tp>%(r0, r1);
    res = %add<tp>%(res, r2);
    return res;
   """},
   
   "fmsub_int" : {"format" : "long", "code" : """
    %r<tp>% res = %mul<tp>%(r0, r1);
    res = %sub<tp>%(res, r2);
    return res;
    """},
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
    
    "div": [{ "instr_name": "fdiv", "datatypes": all_float, "template": tpl_implem_rvv["arith_2args"]}],
    "sqrt": [{ "instr_name": "fsqrt", "datatypes": all_float, "template": tpl_implem_rvv["arith_1arg"]}],
    "rsqrt": [{ "instr_name": "frsqrt7", "datatypes": all_float, "template": tpl_implem_rvv["arith_1arg"]},],
    
    #bitwise either use arith_2args or a float emulation which casts to int, does the ob and cast back
    "andb":[ {"instr_name": "and", "datatypes": all_int_uint, "template": tpl_implem_rvv["arith_2args"]},
            {"instr_name": "and", "datatypes": all_float, "template": tpl_implem_rvv["float_bitwise"]} ],
    "orb":[ {"instr_name": "or", "datatypes": all_int_uint, "template": tpl_implem_rvv["arith_2args"]},
            {"instr_name": "or", "datatypes": all_float, "template": tpl_implem_rvv["float_bitwise"]} ],
    "xorb":[ {"instr_name": "xor", "datatypes": all_int_uint, "template": tpl_implem_rvv["arith_2args"]},
            {"instr_name": "xor", "datatypes": all_float, "template": tpl_implem_rvv["float_bitwise"]} ],

    #masked ops
    "andb_k":[{"instr_name": "mand", "datatypes" : all_datatypes, "template" : tpl_implem_rvv["mask_2args"]}],
    "orb_k":[{"instr_name": "mor", "datatypes" : all_datatypes, "template" : tpl_implem_rvv["mask_2args"]}],
    "xorb_k":[{"instr_name": "mxor", "datatypes" : all_datatypes, "template" : tpl_implem_rvv["mask_2args"]}],
    
    "set1": [ {"instr_name": "vmv", "datatypes" : all_int_uint, "template":tpl_implem_rvv["scalar_set1"] },
              {"instr_name": "vfmv","datatypes": all_float, "template":tpl_implem_rvv["float_set1"]}],
    "set0": [ {"instr_name": "vmv", "datatypes" : all_int_uint, "template":tpl_implem_rvv["scalar_set0"] },
              {"instr_name": "vfmv","datatypes": all_float, "template":tpl_implem_rvv["float_set0"]}],
    
    "blend": [{"instr_name": "merge", "datatypes": all_datatypes, "template" : tpl_implem_rvv["merge"]}],
    #"select" : [{"instr_name": "select", "datatypes": all_datatypes, "template" : tpl_implem_rvv["merge"]}],
    
    #mask_add": [
    #    { "instr_name" : "add", "datatypes" : all_int_uint, "template" : tpl_implem_rvv["arithmsk_2args"]},
    #    { "instr_name": "fadd", "datatypes": all_float, "template": tpl_implem_rvv["arithmsk_2args"]},
    #],
    
    #"cvt": [{"instr_name": "cvt", "datatypes": all_datatypes, "template" : tpl_implem_rvv["cvt"]}],
    
    "fmadd": [{"instr_name": "fmadd", "datatypes": all_float, "template" : tpl_implem_rvv["arith_3args"]}, 
              {"instr_name": "fmadd", "datatypes": [int32], "template" : tpl_implem_rvv["fmadd_int"]}
    ],
    #"fnmadd": [{"instr_name": "fnmadd", "datatypes": all_float, "template" : tpl_implem_rvv["arith_3args"]}],
    "fmsub": [{"instr_name": "fmsub", "datatypes": all_float, "template" : tpl_implem_rvv["arith_3args"]},
              {"instr_name": "fmadd", "datatypes": [int32], "template" : tpl_implem_rvv["fmsub_int"]}
    ],
    #"fnmsub": [{"instr_name": "fnmsub", "datatypes": all_float, "template" : tpl_implem_rvv["arith_3args"]}],
    
    "cmplt" : [
            {"instr_name": "mslt", "datatypes": all_int, "template" : tpl_implem_rvv["arith_msk_type_2args"]},
            {"instr_name": "msltu", "datatypes": all_uint, "template" : tpl_implem_rvv["arith_msk_type_2args"]},
            {"instr_name": "mflt", "datatypes": all_float, "template" : tpl_implem_rvv["arith_msk_type_2args"]},
    ],
    
    "cmple" : [
            {"instr_name": "msle", "datatypes": all_int, "template" : tpl_implem_rvv["arith_msk_type_2args"]},
            {"instr_name": "msleu", "datatypes": all_uint, "template" : tpl_implem_rvv["arith_msk_type_2args"]},
            {"instr_name": "mfle", "datatypes": all_float, "template" : tpl_implem_rvv["arith_msk_type_2args"]},
    ],
    
    "cmpgt" : [
            {"instr_name": "msgt", "datatypes": all_int, "template" : tpl_implem_rvv["arith_msk_type_2args"]},
            {"instr_name": "msgtu", "datatypes": all_uint, "template" : tpl_implem_rvv["arith_msk_type_2args"]},
            {"instr_name": "mfgt", "datatypes": all_float, "template" : tpl_implem_rvv["arith_msk_type_2args"]},
    ],
    
    "cmpge" : [
            {"instr_name": "msge", "datatypes": all_int, "template" : tpl_implem_rvv["arith_msk_type_2args"]},
            {"instr_name": "msgeu", "datatypes": all_uint, "template" : tpl_implem_rvv["arith_msk_type_2args"]},
            {"instr_name": "mfge", "datatypes": all_float, "template" : tpl_implem_rvv["arith_msk_type_2args"]},
    ],
    
    "cmpeq" : [
            {"instr_name": "mseq", "datatypes": all_int_uint, "template" : tpl_implem_rvv["arith_msk_type_2args"]},
            {"instr_name": "mfeq", "datatypes": all_float, "template" : tpl_implem_rvv["arith_msk_type_2args"]},
    ],
    
    "cmpneq" : [
            {"instr_name": "msne", "datatypes": all_int_uint, "template" : tpl_implem_rvv["arith_msk_type_2args"]},
            {"instr_name": "mfne", "datatypes": all_float, "template" : tpl_implem_rvv["arith_msk_type_2args"]},
    ],    
    
    "getfirst" : [
            {"instr_name": "mv", "datatypes": all_int_uint, "template": tpl_implem_rvv["scalar_getfirst"]},
            {"instr_name": "fmv", "datatypes": all_float, "template": tpl_implem_rvv["float_getfirst"]},
    ],
    
    #"maskst":[{ "instr_name": "maskload", "datatypes": all_datatypes, "template": tpl_implem_rvv["maskst"] }],

   "min" : [
            {"instr_name": "min", "datatypes": all_int, "template": tpl_implem_rvv["arith_2args"]},
            {"instr_name": "minu", "datatypes": all_uint, "template": tpl_implem_rvv["arith_2args"]},
            {"instr_name": "fmin", "datatypes": all_float, "template": tpl_implem_rvv["arith_2args"]},
   ],
   
   "max" : [
            {"instr_name": "max", "datatypes": all_int, "template": tpl_implem_rvv["arith_2args"]},
            {"instr_name": "maxu", "datatypes": all_uint, "template": tpl_implem_rvv["arith_2args"]},
            {"instr_name": "fmax", "datatypes": all_float, "template": tpl_implem_rvv["arith_2args"]},
   ],
   
   "notb" : [
           {"instr_name" : "xor", "datatypes" : all_int_uint, "template" : tpl_implem_rvv["scalar_notb"]},
           {"instr_name" : "xor", "datatypes" : all_float, "template" : tpl_implem_rvv["float_notb"]},      
   ],   
   
   "testz_2" : [{"instr_name" : "cpop", "datatypes" : all_datatypes, "template" : tpl_implem_rvv["testz_2"]}],
   
   #"round" :  [
   #        {"instr_name" : "vfcvt", "datatypes" : all_float, "template" : tpl_implem_rvv["round_float"]},
   #        {"instr_name" : "", "datatypes" : all_int_uint, "template" : tpl_implem_rvv["round_intuint"]},       
   #], 

}