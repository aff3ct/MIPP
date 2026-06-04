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
i.e the format is : v{type}{size}m{lmul}_t 

So we'll limit ourselves to v{type}{size}m1_t rn
I'm not sure how easy it would be to add lmul support w this code structure. I'll ask.

If I want to add stuff, I think I just need to add elements in line 62 of c_generator.py 
i.e : pre_rendering = j2_template.render(isa=isa, instr_name=instr_name, dt_par=datatypes[dt_par], dt_ret=datatypes[dt_ret], isa_dt_par=isa["datatypes"][dt_par], isa_dt_ret=isa["datatypes"][dt_ret], cstdint_ret=datatypes[dt_ret]["cstd"])


n.b : data_ext_msk not used atm. Could be leveraged 4 optimisation (using registers instead of vectors and so on)
"""
isa_rvv = {
    "name" : "rvv",#idk
    "prefix" : "__riscv", #to prefix intrinsics, not used for types
    "size" : {128 , 256 , 512 , 1024 , 2048}, #Support lmul at some point
    "define" : "defined(__riscv_v_intrinsic)", #define to check is isa exists
    "architecture" : "Risc-V",#used for smth ig
    "hw_lmul" : True, #yeah
    
    #the datatypes dict contains k/v pairs with relevant information
    #to generate intrinsics. You can write {{isa_dt_reg.key}} and it will be replace 
    #with the value. Useful for genericity. 
    
    #I'm adding fields to it rn. It makes it more crowded and less legible. But it works.
    "datatypes" : {
        float64 : {"data_ext" : "f64m{lmul}", "data_ext_logi" : "b{eew_emul}",         "data_ext_msk"  : "b64",        "reg" : "vfloat64m{lmul}_t", "msk" : "vbool{eew_emul}_t",
                   "to_ptr"   : "float64_t",  "reg_dt_ext"    : "f64",        "uint_data_ext" : "u64m{lmul}",      "int_data_ext" : "i64m{lmul}", "width": "64" } ,#added to_int_ptr to convert float to int before bitwise operations. I'll see if I can find a better solution later.
        
        float32 : {"data_ext" : "f32m{lmul}", "data_ext_logi" : "b{eew_emul}",         "data_ext_msk"  : "b32",        "reg" : "vfloat32m{lmul}_t", "msk" : "vbool{eew_emul}_t",
                   "to_ptr"   : "float32_t",  "reg_dt_ext"    : "f32",        "uint_data_ext" : "u32m{lmul}",      "int_data_ext" : "i32m{lmul}", "width" : "32" } ,#added to_int_ptr to convert float to int before bitwise operations. I'll see if I can find a better solution later.
        
        int64   : {"data_ext" : "i64m{lmul}", "data_ext_logi" : "b{eew_emul}",         "data_ext_msk"  : "b64",        "reg" : "vint64m{lmul}_t",   "msk" : "vbool{eew_emul}_t",
                   "to_ptr"   : "int64_t",    "reg_dt_ext"    : "i64", "width" : "64"} ,
        
        int32   : {"data_ext" : "i32m{lmul}", "data_ext_logi" : "b{eew_emul}",         "data_ext_msk" : "b32",         "reg" : "vint32m{lmul}_t",   "msk" : "vbool{eew_emul}_t",
                   "to_ptr"   : "int32_t",    "reg_dt_ext"    : "i32", "width" : "32"} ,
        
        int16   : {"data_ext" : "i16m{lmul}", "data_ext_logi" : "b{eew_emul}",         "data_ext_msk" : "b16",         "reg" : "vint16m{lmul}_t",   "msk" : "vbool{eew_emul}_t",
                   "to_ptr"   : "int16_t",    "reg_dt_ext"    : "i16", "width" : "16"} ,
        
        int8    : {"data_ext" : "i8m{lmul}",  "data_ext_logi" : "b{eew_emul}",         "data_ext_msk"  : "b8",          "reg" : "vint8m{lmul}_t",    "msk" : "vbool{eew_emul}_t",
                   "to_ptr"   : "int8_t",     "reg_dt_ext"    : "i8", "width" : "8"} ,
        
        uint64  : {"data_ext" : "u64m{lmul}", "data_ext_logi" : "b{eew_emul}",         "data_ext_msk" : "b64",         "reg" : "vuint64m{lmul}_t",  "msk" : "vbool{eew_emul}_t",
                   "to_ptr"   : "uint64_t",   "reg_dt_ext"    : "u64", "width" : "64"} ,
        
        uint32  : {"data_ext" : "u32m{lmul}", "data_ext_logi" : "b{eew_emul}",         "data_ext_msk" : "b32",         "reg" : "vuint32m{lmul}_t",  "msk" : "vbool{eew_emul}_t",
                   "to_ptr"   : "uint32_t",   "reg_dt_ext"    : "u32", "width" : "32"} ,
        
        uint16  : {"data_ext" : "u16m{lmul}", "data_ext_logi" : "b{eew_emul}",         "data_ext_msk" : "b16",         "reg" : "vuint16m{lmul}_t",  "msk" : "vbool{eew_emul}_t",
                   "to_ptr"   : "uint16_t",   "reg_dt_ext"    : "u16", "width" : "16"} ,
        
        uint8   : {"data_ext" : "u8m{lmul}",  "data_ext_logi" : "b{eew_emul}",         "data_ext_msk" : "b8",           "reg" : "vuint8m{lmul}_t",   "msk" : "vbool{eew_emul}_t",
                   "to_ptr"   : "uint8_t",    "reg_dt_ext"    : "u8", "width" : "8"} ,
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
    "load"                 : { "format" : "short", "code" : "{{ isa.prefix }}_vle{{ isa_dt_par.width }}_v_{{ isa_dt_par.data_ext }}(({{ isa_dt_par.to_ptr }}*) p0, %N<tp>%);"},
    "load_msks"            : { "format" : "short", "code" : "{{ isa.prefix }}_vle{{ isa_dt_par.width }}_v_{{ isa_dt_par.data_ext }}_mu(m0.m, rsrc.r, ({{ isa_dt_par.to_ptr }}*) p0, %N<tp>%);"},
    
    "store"                : { "format" : "short", "code" : "{{ isa.prefix }}_vse{{ isa_dt_par.width}}_v_{{ isa_dt_par.data_ext }}(({{ isa_dt_par.to_ptr }}*) p0, r0.r , %N<tp>%);"},
    "store_msk"            : { "format" : "short", "code" : "{{ isa.prefix }}_vse{{ isa_dt_par.width}}_v_{{ isa_dt_par.data_ext }}_m(m0.m, ({{ isa_dt_par.to_ptr }}*) p0, r0.r , %N<tp>%);"},
    
    "arith_1arg"           : { "format" : "short", "code" : "{{ isa.prefix }}_v{{ instr_name }}_v_{{ isa_dt_par.data_ext }}(r0.r, %N<tp>%);"},
    "arith_1arg_msk"       : { "format" : "short", "code" : "{{ isa.prefix }}_v{{ instr_name }}_v_{{ isa_dt_par.data_ext }}_mu(m0.m, r0.r, r0.r, %N<tp>%);"},
    "arith_1arg_msks"      : { "format" : "short", "code" : "{{ isa.prefix }}_v{{ instr_name }}_v_{{ isa_dt_par.data_ext }}_mu(m0.m, rsrc.r, r0.r, %N<tp>%);"},
    
    "arith_2args"          : { "format" : "short", "code" : "{{ isa.prefix }}_v{{ instr_name }}_vv_{{ isa_dt_par.data_ext }}(r0.r, r1.r, %N<tp>%);"},
    "arith_2args_msk"     : { "format" : "short", "code" : "{{ isa.prefix }}_v{{ instr_name }}_vv_{{ isa_dt_par.data_ext }}_mu(m0.m, r0.r, r0.r, r1.r, %N<tp>%);"},
    "arith_2args_msks"    : { "format" : "short", "code" : "{{ isa.prefix }}_v{{ instr_name }}_vv_{{ isa_dt_par.data_ext }}_mu(m0.m, rsrc.r, r0.r, r1.r, %N<tp>%);"},

    "mask_2args"           : { "format" : "short", "code" : "{{ isa.prefix }}_v{{ instr_name }}(m0.m, m1.m, %N<tp>%);" },
    
    #arith_2args but with mask dt extension at the end
    "arith_msk_type_2args" : { "format" : "short", "code" : "{{ isa.prefix }}_v{{ instr_name }}_vv_{{ isa_dt_par.data_ext }}_{{isa_dt_par.data_ext_logi}}(r0.r, r1.r, %N<tp>%);"},

    "float_set0"           : { "format" : "short", "code" : "{{isa.prefix}}_{{ instr_name }}_v_f_{{isa_dt_par.data_ext}}(0.f,%N<tp>%);"},
    "scalar_set0"          : { "format" : "short", "code" : "{{isa.prefix}}_{{ instr_name }}_v_x_{{isa_dt_par.data_ext}}(0,%N<tp>%);"},
    #same as arith_2args except "vvm" instead of "vv"
    "merge"                : { "format" : "short", "code" : "{{ isa.prefix }}_v{{ instr_name }}_vvm_{{ isa_dt_par.data_ext }}(r1.r, r0.r, m0.m, %N<tp>%);"},
    #arithmetic w predicate (mask)
    #"arithmsk_2args"       : { "format" : "short", "code" : "{{ isa.prefix }}_v{{ instr_name }}_vv_{{ isa_dt_par.data_ext }}_mu(m0.m, r0.r, r0.r, r1.r, %N<tp>%);"},
    
    "arith_3args"          : { "format" : "short", "code" : "{{ isa.prefix }}_v{{ instr_name }}_vv_{{ isa_dt_par.data_ext }}(r0.r, r1.r, r2.r, %N<tp>%);"},
    "arith_3args_msk"      : { "format" : "short", "code" : "{{ isa.prefix }}_v{{ instr_name }}_vv_{{ isa_dt_par.data_ext }}_mu(m0.m, r0.r, r1.r, r2.r, %N<tp>%);"},
    #"maskst"               : { "format" : "short", "code" : "{{ isa.prefix }}_vse{{ isa_dt_par.width }}_v_{{ isa_dt_par.data_ext }}_m(m0.m,({{isa_dt_par.to_ptr}}*)p0, r0.r, %N<tp>%);"},
    
    "scalar_getfirst"      : { "format" : "short", "code" : "{{isa_dt_par.to_ptr}} res = {{ isa.prefix }}_v{{ instr_name }}_x_s_{{isa_dt_par.data_ext}}_{{isa_dt_par.reg_dt_ext}}(r0.r);"},
    "float_getfirst"       : { "format" : "short", "code" : "{{isa_dt_par.to_ptr}} res = {{ isa.prefix }}_v{{ instr_name }}_f_s_{{isa_dt_par.data_ext}}_{{isa_dt_par.reg_dt_ext}}(r0.r);"},
    # certainly the templates of all time
    "round_int"            : { "format" : "short", "code" : "r0.r;"},
    "round_int_msk"       : { "format" : "short", "code" : "r0.r;"},
    # If u think about it masks round on int/uint is technically a blend
    "round_int_msks"      : { "format" : "short", "code" : "{{isa.prefix}}_vmerge_vvm_{{isa_dt_par.data_ext}}(rsrc.r, r0.r, m0.m, %N<tp>%);"},

    "testz_2"              : { "format" : "short", "code" : "   int32_t res = !({{isa.prefix}}_v{{instr_name}}_m_{{isa_dt_par.data_ext_logi}}(m0.m, %N<tp>%));"},

    "scalar_notb"          : { "format" : "short", "code" : "{{isa.prefix}}_v{{instr_name}}_vx_{{isa_dt_par.data_ext}}(r0.r, -1, %N<tp>%);"},
    "scalar_notb_msk"      : { "format" : "short", "code" : "{{isa.prefix}}_v{{instr_name}}_vx_{{isa_dt_par.data_ext}}_mu(m0.m, r0.r, r0.r, -1, %N<tp>%);"},
    "scalar_notb_msks"     : { "format" : "short", "code" : "{{isa.prefix}}_v{{instr_name}}_vx_{{isa_dt_par.data_ext}}_mu(m0.m, rsrc.r, r0.r, -1, %N<tp>%);"},

    "shift_scalar"         : { "format" : "short", "code" : "{{isa.prefix}}_v{{instr_name}}_vx_{{isa_dt_par.data_ext}}(r0.r, v0, %N<tp>%);"},
    "shift_scalar_msk"     : { "format" : "short", "code" : "{{isa.prefix}}_v{{instr_name}}_vx_{{isa_dt_par.data_ext}}_mu(m0.m, r0.r, r0.r, v0, %N<tp>%);"},
    "shift_scalar_msks"    : { "format" : "short", "code" : "{{isa.prefix}}_v{{instr_name}}_vx_{{isa_dt_par.data_ext}}_mu(m0.m, rsrc.r, r0.r, v0, %N<tp>%);"},

    "div2_scalar"          : { "format" : "short", "code" : "{{isa.prefix}}_v{{instr_name}}_vx_{{isa_dt_par.data_ext}}(r0.r, 1, %N<tp>%);"},
    "div2_scalar_msk"      : { "format" : "short", "code" : "{{isa.prefix}}_v{{instr_name}}_vx_{{isa_dt_par.data_ext}}_mu(m0.m, r0.r, r0.r, 1, %N<tp>%);"},
    "div2_scalar_msks"     : { "format" : "short", "code" : "{{isa.prefix}}_v{{instr_name}}_vx_{{isa_dt_par.data_ext}}_mu(m0.m, rsrc.r, r0.r, 1, %N<tp>%);"},

    "div4_scalar"          : { "format" : "short", "code" : "{{isa.prefix}}_v{{instr_name}}_vx_{{isa_dt_par.data_ext}}(r0.r, 2, %N<tp>%);"},
    "div4_scalar_msk"      : { "format" : "short", "code" : "{{isa.prefix}}_v{{instr_name}}_vx_{{isa_dt_par.data_ext}}_mu(m0.m, r0.r, r0.r, 2, %N<tp>%);"},
    "div4_scalar_msks"     : { "format" : "short", "code" : "{{isa.prefix}}_v{{instr_name}}_vx_{{isa_dt_par.data_ext}}_mu(m0.m, rsrc.r, r0.r, 2, %N<tp>%);"},

    "div2_float"    : { "format" : "short", "code" : "{{isa.prefix}}_v{{instr_name}}_vf_{{isa_dt_par.data_ext}}(r0.r, 2, %N<tp>%);"},
    "div2_float_msk"    : { "format" : "short", "code" : "{{isa.prefix}}_v{{instr_name}}_vf_{{isa_dt_par.data_ext}}_mu(m0.m, r0.r, r0.r, 2, %N<tp>%);"},
    "div2_float_msks"     : { "format" : "short", "code" : "{{isa.prefix}}_v{{instr_name}}_vf_{{isa_dt_par.data_ext}}_mu(m0.m, rsrc.r, r0.r, 2, %N<tp>%);"},
    "div2_float_mskz"     : { "format" : "short", "code" : "{{isa.prefix}}_v{{instr_name}}_vf_{{isa_dt_par.data_ext}}_mu(m0.m, r0.r, r0.r, 2, %N<tp>%);"},

    "div4_float"    : { "format" : "short", "code" : "{{isa.prefix}}_v{{instr_name}}_vf_{{isa_dt_par.data_ext}}(r0.r, 4, %N<tp>%);"},
    "div4_float_msk"    : { "format" : "short", "code" : "{{isa.prefix}}_v{{instr_name}}_vf_{{isa_dt_par.data_ext}}_mu(m0.m, r0.r, r0.r, 4, %N<tp>%);"},
    "div4_float_msks"     : { "format" : "short", "code" : "{{isa.prefix}}_v{{instr_name}}_vf_{{isa_dt_par.data_ext}}_mu(m0.m, rsrc.r, r0.r, 4, %N<tp>%);"},
    "div4_float_mskz"     : { "format" : "short", "code" : "{{isa.prefix}}_v{{instr_name}}_vf_{{isa_dt_par.data_ext}}_mu(m0.m, r0.r, r0.r, 4, %N<tp>%);"},

    "float_bitwise"        : { "format" : "long", "code" : """
                %r<c:uint|b:tp>% tmp1, tmp2;
                tmp1.r = {{ isa.prefix }}_vreinterpret_v_{{isa_dt_par.data_ext}}_{{isa_dt_par.uint_data_ext}}(r0.r);
                tmp2.r = {{ isa.prefix }}_vreinterpret_v_{{isa_dt_par.data_ext}}_{{isa_dt_par.uint_data_ext}}(r1.r);
                tmp1.r = {{ isa.prefix }}_v{{ instr_name }}_vv_{{ isa_dt_par.uint_data_ext }}(tmp1.r, tmp2.r, %N<tp>%);
                %r<tp>% ret;
                ret.r = {{ isa.prefix }}_vreinterpret_v_{{isa_dt_par.uint_data_ext}}_{{isa_dt_par.data_ext}}(tmp1.r);
                return ret;
    """},

    "float_set1" :{"format" : "long", "code" :"""
        %r<tp>% r0;
        r0.r = {{isa.prefix}}_{{ instr_name }}_v_f_{{isa_dt_par.data_ext}}(v0,%N<tp>%);
        //r0.r = {{isa.prefix}}_vrgather_vx_{{isa_dt_par.data_ext}}(r0.r,0,%N<tp>%);
        return r0;
    """},

    "scalar_set1" :{"format" : "long", "code" :"""
        %r<tp>% r0;
        r0.r = {{isa.prefix}}_{{ instr_name }}_v_x_{{isa_dt_par.data_ext}}(v0,%N<tp>%);
        //r0.r = {{isa.prefix}}_vrgather_vx_{{isa_dt_par.data_ext}}(r0.r,0,%N<tp>%);
        return r0;
    """},
      

    "float_notb" :{"format" : "long", "code" : """
        %r<c:uint|b:tp>% tmp;
        tmp.r = {{ isa.prefix }}_vreinterpret_v_{{isa_dt_par.data_ext}}_{{isa_dt_par.uint_data_ext}}(r0.r);
        tmp.r = {{isa.prefix}}_v{{instr_name}}_vx_{{isa_dt_par.uint_data_ext}}(tmp.r, -1, %N<tp>%);
        %r<tp>% ret;
        ret.r = {{ isa.prefix }}_vreinterpret_v_{{isa_dt_par.uint_data_ext}}_{{isa_dt_par.data_ext}}(tmp.r);
        return ret;
    """},

    "float_notb_msk" :{"format" : "long", "code" : """
        %r<c:uint|b:tp>% tmp;
        tmp.r = {{ isa.prefix }}_vreinterpret_v_{{isa_dt_par.data_ext}}_{{isa_dt_par.uint_data_ext}}(r0.r);
        tmp.r = {{isa.prefix}}_v{{instr_name}}_vx_{{isa_dt_par.uint_data_ext}}_mu(m0.m, tmp.r, tmp.r, -1, %N<tp>%);
        %r<tp>% ret;
        ret.r = {{ isa.prefix }}_vreinterpret_v_{{isa_dt_par.uint_data_ext}}_{{isa_dt_par.data_ext}}(tmp.r);
        return ret;
    """},


    "float_notb_msks" :{"format" : "long", "code" : """
        %r<c:uint|b:tp>% tmp, tmp1;
        tmp1.r = {{ isa.prefix }}_vreinterpret_v_{{isa_dt_par.data_ext}}_{{isa_dt_par.uint_data_ext}}(rsrc.r);
        tmp.r = {{ isa.prefix }}_vreinterpret_v_{{isa_dt_par.data_ext}}_{{isa_dt_par.uint_data_ext}}(r0.r);
        tmp.r = {{isa.prefix}}_v{{instr_name}}_vx_{{isa_dt_par.uint_data_ext}}_mu(m0.m, tmp1.r, tmp.r, -1, %N<tp>%);
        %r<tp>% ret; 
        ret.r = {{ isa.prefix }}_vreinterpret_v_{{isa_dt_par.uint_data_ext}}_{{isa_dt_par.data_ext}}(tmp.r);
        return ret;
    """},

    "float_notb_mskz" :{"format" : "long", "code" : """
        %r<c:uint|b:tp>% tmp, tmp1;
        tmp1 = %set0<c:uint|b:tp>%();
        tmp.r = {{ isa.prefix }}_vreinterpret_v_{{isa_dt_par.data_ext}}_{{isa_dt_par.uint_data_ext}}(r0.r);
        tmp.r = {{isa.prefix}}_v{{instr_name}}_vx_{{isa_dt_par.uint_data_ext}}_mu(m0.m, tmp1.r, tmp.r, -1, %N<tp>%); 
        %r<tp>% ret; 
        ret.r = {{ isa.prefix }}_vreinterpret_v_{{isa_dt_par.uint_data_ext}}_{{isa_dt_par.data_ext}}(tmp.r);
        return ret;
    """},

    "fmadd_int" : {"format" : "long", "code" : """
        %r<tp>% res = %mul<tp>%(r0, r1);
        res = %add<tp>%(res, r2);
        return res;
   """},
   
    "fmsub_int" : {"format" : "long", "code" : """
        /*%r<tp>% neg_r2 = %sub<tp>%(%set0<tp>%(), r2));
        res.r = {{isa.prefix}}_{{instr_name}}_vv_{{isa_dt_par.data_ext}}(r0.r, r1.r, r2.r, %N<tp>%);*/
        %r<tp>% res = %mul<tp>%(r0, r1);
        res = %sub<tp>%(res, r2);
        return res;
    """},

    "fmsub_int_msk" : {"format" : "long", "code" : """
        /*%r<tp>% neg_r2 = %sub<tp>%(%set0<tp>%(), r2));
        res.r = {{isa.prefix}}_{{instr_name}}_vv_{{isa_dt_par.data_ext}}_mu(m0.r,r0.r, r1.r, r2.r, %N<tp>%);*/
        %r<tp>% res = %mul<tp>%(r0, r1);
        res = %sub<tp>%(res, r2);
        return res;
    """},
  
    
    "round_float" : { "format" : "long", "code" : """
        %r<c:int|b:tp>%  tmp;
        tmp.r = {{isa.prefix}}_{{instr_name}}_x_f_v_{{isa_dt_par.int_data_ext}}_rm(r0.r,__RISCV_FRM_RNE,%N<tp>%);
        %r<tp>% ret;
        ret.r = {{isa.prefix}}_{{instr_name}}_f_x_v_{{isa_dt_par.data_ext}}(tmp.r,%N<tp>%);
        return ret;
    """},

    "shift_float" : { "format" : "long", "code" : """
        %r<c:uint|b:tp>% tmp1;
        tmp1.r = {{ isa.prefix }}_vreinterpret_v_{{isa_dt_par.data_ext}}_{{isa_dt_par.uint_data_ext}}(r0.r);
        tmp1.r = {{ isa.prefix }}_v{{ instr_name }}_vx_{{ isa_dt_par.uint_data_ext }}(tmp1.r, v0, %N<tp>%);
        %r<tp>% ret;
        ret.r = {{ isa.prefix }}_vreinterpret_v_{{isa_dt_par.uint_data_ext}}_{{isa_dt_par.data_ext}}(tmp1.r);
        return ret;
    """},
    # this is a bit hacky but I **THINK** that the underlying mask types r always the same for floats and uints of the same size.
    # So it's ok to use m0.m (which is a float mask) for a uint shift.
    "shift_float_msk" : { "format" : "long", "code" : """
        %r<c:uint|b:tp>% tmp1;
        tmp1.r = {{ isa.prefix }}_vreinterpret_v_{{isa_dt_par.data_ext}}_{{isa_dt_par.uint_data_ext}}(r0.r);
        tmp1.r = {{ isa.prefix }}_v{{ instr_name }}_vx_{{ isa_dt_par.uint_data_ext }}_mu(m0.m, tmp1.r, tmp1.r, v0, %N<tp>%);
        %r<tp>% ret;
        ret.r = {{ isa.prefix }}_vreinterpret_v_{{isa_dt_par.uint_data_ext}}_{{isa_dt_par.data_ext}}(tmp1.r);
        return ret;
    """},

    "shift_float_mskz" : { "format" : "long", "code" : """
        %r<c:uint|b:tp>% tmp1;
        %r<c:uint|b:tp>% zeroes = %set0<c:uint|b:tp>%();
        tmp1.r = {{ isa.prefix }}_vreinterpret_v_{{isa_dt_par.data_ext}}_{{isa_dt_par.uint_data_ext}}(r0.r);
        tmp1.r = {{ isa.prefix }}_v{{ instr_name }}_vx_{{ isa_dt_par.uint_data_ext }}_mu(m0.m, zeroes.r, tmp1.r, v0, %N<tp>%);
        %r<tp>% ret;
        ret.r = {{ isa.prefix }}_vreinterpret_v_{{isa_dt_par.uint_data_ext}}_{{isa_dt_par.data_ext}}(tmp1.r);
        return ret;
    """},

    "shift_float_msks" : { "format" : "long", "code" : """
        %r<c:uint|b:tp>% tmp1;
        %r<c:uint|b:tp>% rsrc_u;
        rsrc_u.r = {{ isa.prefix }}_vreinterpret_v_{{isa_dt_par.data_ext}}_{{isa_dt_par.uint_data_ext}}(rsrc.r);

        tmp1.r = {{ isa.prefix }}_vreinterpret_v_{{isa_dt_par.data_ext}}_{{isa_dt_par.uint_data_ext}}(r0.r);
        tmp1.r = {{ isa.prefix }}_v{{ instr_name }}_vx_{{ isa_dt_par.uint_data_ext }}_mu(m0.m, rsrc_u.r, tmp1.r, v0, %N<tp>%);
        %r<tp>% ret;
        ret.r = {{ isa.prefix }}_vreinterpret_v_{{isa_dt_par.uint_data_ext}}_{{isa_dt_par.data_ext}}(tmp1.r);
        return ret;
    """},

    "arith_2args_mskz"   : { "format" : "long", "code" : 
    """
        %r<tp>% tmp; 
        tmp = %set0<tp>%();
        tmp.r ={{ isa.prefix }}_v{{ instr_name }}_vv_{{ isa_dt_par.data_ext }}_mu(m0.m, tmp.r, r0.r, r1.r, %N<tp>%);
        return tmp;
    """},


    "store_mskz" : { "format" : "long", "code" : """
        %r<tp>% tmp;
        tmp = %set0<tp>%();
        tmp.r = {{ isa.prefix }}_vmerge_vvm_{{ isa_dt_par.data_ext }}(tmp.r, r0.r, m0.m, %N<tp>%);
        // store w regular vse
        {{ isa.prefix }}_vse{{ isa_dt_par.width}}_v_{{ isa_dt_par.data_ext }}(({{ isa_dt_par.to_ptr }}*) p0, tmp.r , %N<tp>%);
    """},

    "load_mskz" : { "format" : "long", "code" : """
        %r<tp>% tmp;
        tmp = %set0<tp>%();
        tmp.r = {{ isa.prefix }}_vle{{ isa_dt_par.width }}_v_{{ isa_dt_par.data_ext }}_mu(m0.m, tmp.r, ({{ isa_dt_par.to_ptr }}*) p0, %N<tp>%);
        return tmp;
    """},

    "arith_1arg_mskz" : { "format" : "long", "code" : """
        %r<tp>% tmp;
        tmp = %set0<tp>%();
        tmp.r = {{ isa.prefix }}_v{{ instr_name }}_v_{{ isa_dt_par.data_ext }}_mu(m0.m, tmp.r, r0.r, %N<tp>%);
        return tmp;
    """},

    "scalar_notb_mskz" : { "format" : "long", "code" : """
        %r<tp>% tmp;
        tmp = %set0<tp>%();
        tmp.r = {{isa.prefix}}_v{{instr_name}}_vx_{{isa_dt_par.data_ext}}_mu(m0.m, tmp.r, r0.r, -1, %N<tp>%);
        return tmp;
    """},

    "shift_scalar_mskz" : { "format" : "long", "code" : """
        %r<tp>% tmp;
        tmp = %set0<tp>%();
        tmp.r = {{isa.prefix}}_v{{instr_name}}_vx_{{isa_dt_par.data_ext}}_mu(m0.m, tmp.r, r0.r, v0, %N<tp>%);
        return tmp;
    """},


    # hack to avoid tomsk circular dep w cmpneq. 
    # this is the symptom of a wider issue of the generator that should be fix asp
    "arith_msk_type_2args_mskz" : { "format" : "long", "code" : """
        %m<tp>% zeroes = %set0_k<tp>%();
        %m<tp>% tmp;
        tmp.m = {{ isa.prefix }}_v{{ instr_name }}_vv_{{ isa_dt_par.data_ext }}_{{isa_dt_par.data_ext_logi}}_mu(m0.m, zeroes.m, r0.r, r1.r, %N<tp>%); 
        return tmp;
    """},

    "arith_msk_type_2args_mskz_cmpneq" : { "format" : "long", "code" : """
        %r<tp>% zeroes;
        zeroes = %set0<tp>%();
        
        %m<tp>% tmp;
        tmp.m = {{ isa.prefix }}_v{{ instr_name }}_vv_{{ isa_dt_par.data_ext }}_{{isa_dt_par.data_ext_logi}}(zeroes.r, zeroes.r, %N<tp>%);
        tmp.m = {{ isa.prefix }}_v{{ instr_name }}_vv_{{ isa_dt_par.data_ext }}_{{isa_dt_par.data_ext_logi}}_mu(m0.m, tmp.m, r0.r, r1.r, %N<tp>%); 
        return tmp;
    """},

    "tomsk" : { "format" : "long", "code" : 
    """       
    %r<tp>% r1 = %set1<tp>%(0); 
    return %cmpneq<tp>%(r1,r0);
    """},

    "set0_k" : { "format" : "long", "code" :
    """        
    %r<tp>% tmp;
    tmp = %set0<tp>%();
    return %cmpneq<tp>%(tmp,tmp);
    """},

    "div2_scalar_mskz" : { "format" : "long", "code" : """
        %r<tp>% tmp;
        tmp = %set0<tp>%();
        tmp.r = {{isa.prefix}}_v{{instr_name}}_vx_{{isa_dt_par.data_ext}}_mu(m0.m, tmp.r, r0.r, 1, %N<tp>%);
        return tmp;
    """},

    "div4_scalar_mskz" : { "format" : "long", "code" : """
        %r<tp>% tmp;
        tmp = %set0<tp>%();
        tmp.r = {{isa.prefix}}_v{{instr_name}}_vx_{{isa_dt_par.data_ext}}_mu(m0.m, tmp.r, r0.r, 2, %N<tp>%);
        return tmp;
    """},

    "div2_float_mskz" : { "format" : "long", "code" : """
        %r<tp>% tmp;
        tmp = %set0<tp>%();
        tmp.r = {{isa.prefix}}_v{{instr_name}}_vf_{{isa_dt_par.data_ext}}_mu(m0.m, tmp.r, r0.r, 2, %N<tp>%);
        return tmp;
    """},

    "div4_float_mskz" : { "format" : "long", "code" : """
        %r<tp>% tmp;
        tmp = %set0<tp>%();
        tmp.r = {{isa.prefix}}_v{{instr_name}}_vf_{{isa_dt_par.data_ext}}_mu(m0.m, tmp.r, r0.r, 4, %N<tp>%);
        return tmp;
    """},

    "round_int_mskz" : { "format" : "long", "code" : """
        %r<tp>% tmp;
        tmp = %set0<tp>%();
        tmp.r = {{isa.prefix}}_vmerge_vvm_{{ isa_dt_par.data_ext }}(tmp.r, r0.r, m0.m, %N<tp>%);
        return tmp;
    """},

}

"""
this dictionnary keeps track of which instructions r implemented. 
Which template to use to generate them. Which type should be used w which template n so on.
"""
implems_rvv = {

    # Keeping those near the top bc the generator might get mad otherwise ...
    "load" : [
        { "instr_name" : "load",    "datatypes" : all_datatypes, "template" : tpl_implem_rvv["load"] },
        { "instr_name" : "load",    "datatypes" : all_datatypes, "template" : tpl_implem_rvv["load_msks"], "version" : "masks"},
    ],
    "store" : [
        { "instr_name" : "store",   "datatypes" : all_datatypes, "template" : tpl_implem_rvv["store"] },
        { "instr_name" : "store",   "datatypes" : all_datatypes, "template" : tpl_implem_rvv["store_msk"], "version"  : "mask"},
        { "instr_name" : "store",   "datatypes" : all_datatypes, "template" : tpl_implem_rvv["store_mskz"], "version" : "maskz"},],

    "set1" : [
        { "instr_name" : "vmv",     "datatypes" : all_int_uint,  "template" :tpl_implem_rvv["scalar_set1"] },
        { "instr_name" : "vfmv",    "datatypes" : all_float,     "template" :tpl_implem_rvv["float_set1"]}],
    "set0" : [ 
        { "instr_name" : "vmv",     "datatypes" : all_int_uint,  "template" :tpl_implem_rvv["scalar_set0"] },
        { "instr_name" : "vfmv",    "datatypes" : all_float,     "template" :tpl_implem_rvv["float_set0"]}],
    "blend" : [
        { "instr_name" : "merge",   "datatypes" : all_datatypes, "template" : tpl_implem_rvv["merge"]}],

    #arith_2args functions
    "add" : [
	    { "instr_name" : "fadd",    "datatypes" : all_float,    "template" : tpl_implem_rvv["arith_2args"]},
	    { "instr_name" : "add",     "datatypes" : all_int_uint, "template" : tpl_implem_rvv["arith_2args"]},#],
        
        { "instr_name" : "add",     "datatypes" : all_int_uint, "template" : tpl_implem_rvv["arith_2args_msk" ], "version" : "mask"},
        { "instr_name" : "fadd",    "datatypes" : all_float,    "template" : tpl_implem_rvv["arith_2args_msk" ], "version" : "mask"},

        { "instr_name" : "add",     "datatypes" : all_int_uint, "template" : tpl_implem_rvv["arith_2args_mskz"], "version" : "maskz"},
        { "instr_name" : "fadd",    "datatypes" : all_float,    "template" : tpl_implem_rvv["arith_2args_mskz"], "version" : "maskz"},

        { "instr_name" : "add",     "datatypes" : all_int_uint, "template" : tpl_implem_rvv["arith_2args_msks"], "version" : "masks"},
        { "instr_name" : "fadd",    "datatypes" : all_float,    "template" : tpl_implem_rvv["arith_2args_msks"], "version" : "masks"},
    ],

    "sub" : [
        { "instr_name" : "fsub",    "datatypes" : all_float,    "template" : tpl_implem_rvv["arith_2args"]},
        { "instr_name" : "sub",     "datatypes" : all_int_uint, "template" : tpl_implem_rvv["arith_2args"]},
        
        { "instr_name" : "sub",     "datatypes" : all_int_uint, "template" : tpl_implem_rvv["arith_2args_msk"], "version" : "mask"},
        { "instr_name" : "fsub",    "datatypes" : all_float,    "template" : tpl_implem_rvv["arith_2args_msk"], "version" : "mask"},

        { "instr_name" : "sub",     "datatypes" : all_int_uint, "template" : tpl_implem_rvv["arith_2args_mskz"], "version" : "maskz"},
        { "instr_name" : "fsub",    "datatypes" : all_float,    "template" : tpl_implem_rvv["arith_2args_mskz"], "version" : "maskz"},

        { "instr_name" : "sub",     "datatypes" : all_int_uint, "template" : tpl_implem_rvv["arith_2args_msks"], "version" : "masks"},
        { "instr_name" : "fsub",    "datatypes" : all_float,    "template" : tpl_implem_rvv["arith_2args_msks"], "version" : "masks"},
    ],

    "mul" : [
        { "instr_name" : "fmul",    "datatypes" : all_float,    "template" : tpl_implem_rvv["arith_2args"]},
	    { "instr_name" : "mul",     "datatypes" : all_int_uint, "template" : tpl_implem_rvv["arith_2args"]},

        { "instr_name" : "mul",     "datatypes" : all_int_uint, "template" : tpl_implem_rvv["arith_2args_msk"], "version" : "mask"},
        { "instr_name" : "fmul",    "datatypes" : all_float,    "template" : tpl_implem_rvv["arith_2args_msk"], "version" : "mask"},

        { "instr_name" : "mul",     "datatypes" : all_int_uint, "template" : tpl_implem_rvv["arith_2args_mskz"], "version" : "maskz"},
        { "instr_name" : "fmul",    "datatypes" : all_float,    "template" : tpl_implem_rvv["arith_2args_mskz"], "version" : "maskz"},

        { "instr_name" : "mul",     "datatypes" : all_int_uint, "template" : tpl_implem_rvv["arith_2args_msks"], "version" : "masks"},
        { "instr_name" : "fmul",    "datatypes" : all_float,    "template" : tpl_implem_rvv["arith_2args_msks"], "version" : "masks"},
    ],

    "div" : [
        { "instr_name" : "fdiv",    "datatypes" : all_float,    "template" : tpl_implem_rvv["arith_2args"]},
        { "instr_name" : "fdiv",    "datatypes" : all_float,    "template" : tpl_implem_rvv["arith_2args_msk"],  "version" : "mask"},
        { "instr_name" : "fdiv",    "datatypes" : all_float,    "template" : tpl_implem_rvv["arith_2args_mskz"], "version" : "maskz"},
        { "instr_name" : "fdiv",    "datatypes" : all_float,    "template" : tpl_implem_rvv["arith_2args_msks"], "version" : "masks"},
    ],

    # bitwise either use arith_2args or a float emulation which casts to int, does the op and cast back
    # todo :  support of native masks for floats, emulation will do for now. Wouldn't be hard to do tbh.
    "andb" :[
        { "instr_name" : "and",     "datatypes" : all_int_uint,  "template" : tpl_implem_rvv["arith_2args"]},
        { "instr_name" : "and",     "datatypes" : all_float,     "template" : tpl_implem_rvv["float_bitwise"]},
        
        {"instr_name" : "and",     "datatypes"  : all_int_uint,  "template" : tpl_implem_rvv["arith_2args_msk" ], "version" : "mask"},
        { "instr_name" : "and",     "datatypes" : all_int_uint,  "template" : tpl_implem_rvv["arith_2args_mskz"], "version" : "maskz"},
        { "instr_name" : "and",     "datatypes" : all_int_uint,  "template" : tpl_implem_rvv["arith_2args_msks"], "version" : "masks"},
    ],

    "orb" :[
        { "instr_name" : "or",      "datatypes" : all_int_uint,  "template" : tpl_implem_rvv["arith_2args"]},
        { "instr_name" : "or",      "datatypes" : all_float,     "template" : tpl_implem_rvv["float_bitwise"]},
        
        { "instr_name" : "or",      "datatypes" : all_int_uint,  "template" : tpl_implem_rvv["arith_2args_msk"  ], "version" : "mask"},
        { "instr_name" : "or",     "datatypes"  : all_int_uint,   "template" : tpl_implem_rvv["arith_2args_mskz"], "version" : "maskz"},
        { "instr_name" : "or",     "datatypes"  : all_int_uint,   "template" : tpl_implem_rvv["arith_2args_msks"], "version" : "masks"},
    ],
    "xorb" :[
        { "instr_name" : "xor",     "datatypes" : all_int_uint,  "template" : tpl_implem_rvv["arith_2args"]},
        { "instr_name" : "xor",     "datatypes" : all_float,     "template" : tpl_implem_rvv["float_bitwise"]},
        
        { "instr_name" : "xor",     "datatypes" : all_int_uint,  "template" : tpl_implem_rvv["arith_2args_msk" ], "version" : "mask"},
        { "instr_name" : "xor",     "datatypes" : all_int_uint,  "template" : tpl_implem_rvv["arith_2args_mskz"], "version" : "maskz"},
        { "instr_name" : "xor",     "datatypes" : all_int_uint,  "template" : tpl_implem_rvv["arith_2args_msks"], "version" : "masks"},
    ],
    
    "min" : [
        { "instr_name" : "min",    "datatypes" : all_int,        "template" : tpl_implem_rvv["arith_2args"]},
        { "instr_name" : "minu",   "datatypes" : all_uint,       "template" : tpl_implem_rvv["arith_2args"]},
        { "instr_name" : "fmin",   "datatypes" : all_float,      "template" : tpl_implem_rvv["arith_2args"]},
        
        
        { "instr_name" : "min",    "datatypes" : all_int,        "template" : tpl_implem_rvv["arith_2args_msk"], "version" : "mask"},
        { "instr_name" : "minu",   "datatypes" : all_uint,       "template" : tpl_implem_rvv["arith_2args_msk"], "version" : "mask"},
        { "instr_name" : "fmin",   "datatypes" : all_float,      "template" : tpl_implem_rvv["arith_2args_msk"], "version" : "mask"},

        { "instr_name" : "min",    "datatypes" : all_int,        "template" : tpl_implem_rvv["arith_2args_msks"], "version" : "masks"},
        { "instr_name" : "minu",   "datatypes" : all_uint,       "template" : tpl_implem_rvv["arith_2args_msks"], "version" : "masks"},
        { "instr_name" : "fmin",   "datatypes" : all_float,      "template" : tpl_implem_rvv["arith_2args_msks"], "version" : "masks"},

        { "instr_name" : "min",    "datatypes" : all_int,        "template" : tpl_implem_rvv["arith_2args_mskz"], "version" : "maskz"},
        { "instr_name" : "minu",   "datatypes" : all_uint,       "template" : tpl_implem_rvv["arith_2args_mskz"], "version" : "maskz"},
        { "instr_name" : "fmin",   "datatypes" : all_float,      "template" : tpl_implem_rvv["arith_2args_mskz"], "version" : "maskz"},           
    ],
    "max" : [
        { "instr_name" : "max",    "datatypes" : all_int,        "template" : tpl_implem_rvv["arith_2args"]},
        { "instr_name" : "maxu",   "datatypes" : all_uint,       "template" : tpl_implem_rvv["arith_2args"]},
        { "instr_name" : "fmax",   "datatypes" : all_float,      "template" : tpl_implem_rvv["arith_2args"]},
        
        { "instr_name" : "max",    "datatypes" : all_int,        "template" : tpl_implem_rvv["arith_2args_msk"], "version" : "mask"},
        { "instr_name" : "maxu",   "datatypes" : all_uint,       "template" : tpl_implem_rvv["arith_2args_msk"], "version" : "mask"},
        { "instr_name" : "fmax",   "datatypes" : all_float,      "template" : tpl_implem_rvv["arith_2args_msk"], "version" : "mask"},
        
        { "instr_name" : "max",    "datatypes" : all_int,        "template" : tpl_implem_rvv["arith_2args_msks"], "version" : "masks"},
        { "instr_name" : "maxu",   "datatypes" : all_uint,       "template" : tpl_implem_rvv["arith_2args_msks"], "version" : "masks"},
        { "instr_name" : "fmax",   "datatypes" : all_float,      "template" : tpl_implem_rvv["arith_2args_msks"], "version" : "masks"},

        { "instr_name" : "max",    "datatypes" : all_int,        "template" : tpl_implem_rvv["arith_2args_mskz"], "version" : "maskz"},
        { "instr_name" : "maxu",   "datatypes" : all_uint,       "template" : tpl_implem_rvv["arith_2args_mskz"], "version" : "maskz"},
        { "instr_name" : "fmax",   "datatypes" : all_float,      "template" : tpl_implem_rvv["arith_2args_mskz"], "version" : "maskz"},
    ],

    "adds" : [
        { "instr_name" : "sadd",   "datatypes" : all_int,        "template" : tpl_implem_rvv["arith_2args"]}, 
        { "instr_name" : "saddu",  "datatypes" : all_uint,       "template" : tpl_implem_rvv["arith_2args"]},
    
        { "instr_name" : "sadd",   "datatypes" : all_int,        "template" : tpl_implem_rvv["arith_2args_msk"], "version" : "mask"}, 
        { "instr_name" : "saddu",  "datatypes" : all_uint,       "template" : tpl_implem_rvv["arith_2args_msk"], "version" : "mask"},

        { "instr_name" : "sadd",   "datatypes" : all_int,        "template" : tpl_implem_rvv["arith_2args_mskz"], "version" : "maskz"},
        { "instr_name" : "saddu",  "datatypes" : all_uint,       "template" : tpl_implem_rvv["arith_2args_mskz"], "version" : "maskz"},

        { "instr_name" : "sadd",   "datatypes" : all_int,        "template" : tpl_implem_rvv["arith_2args_msks"], "version" : "masks"}, 
        { "instr_name" : "saddu",  "datatypes" : all_uint,       "template" : tpl_implem_rvv["arith_2args_msks"], "version" : "masks"},
    ],
    
    "subs" : [
        { "instr_name" : "ssub",   "datatypes" : all_int,  "template" : tpl_implem_rvv["arith_2args"]},
        { "instr_name" : "ssubu",  "datatypes" : all_uint, "template" : tpl_implem_rvv["arith_2args"]},
    
        { "instr_name" : "ssub",   "datatypes" : all_int,  "template" : tpl_implem_rvv["arith_2args_msk"], "version" : "mask"},
        { "instr_name" : "ssubu",  "datatypes" : all_uint, "template" : tpl_implem_rvv["arith_2args_msk"], "version" : "mask"},

        { "instr_name" : "ssub",   "datatypes" : all_int,  "template" : tpl_implem_rvv["arith_2args_mskz"], "version" : "maskz"},
        { "instr_name" : "ssubu",  "datatypes" : all_uint, "template" : tpl_implem_rvv["arith_2args_mskz"], "version" : "maskz"},

        { "instr_name" : "ssub",   "datatypes" : all_int,  "template" : tpl_implem_rvv["arith_2args_msks"], "version" : "masks"},
        { "instr_name" : "ssubu",  "datatypes" : all_uint, "template" : tpl_implem_rvv["arith_2args_msks"], "version" : "masks"}, 
    ],

    # Arith 1 arg templates
    "sqrt" : [
        { "instr_name" : "fsqrt",   "datatypes" : all_float,    "template" : tpl_implem_rvv["arith_1arg"]},
        { "instr_name" : "fsqrt",   "datatypes" : all_float,    "template" : tpl_implem_rvv["arith_1arg_msk"], "version" : "mask"},
        { "instr_name" : "fsqrt",   "datatypes" : all_float,    "template" : tpl_implem_rvv["arith_1arg_mskz"], "version" : "maskz"},
        { "instr_name" : "fsqrt",   "datatypes" : all_float,    "template" : tpl_implem_rvv["arith_1arg_msks"], "version" : "masks"},
    ],
    "rsqrt" : [
        { "instr_name" : "frsqrt7", "datatypes" : all_float,     "template" : tpl_implem_rvv["arith_1arg"]},
        { "instr_name" : "frsqrt7", "datatypes" : all_float,     "template" : tpl_implem_rvv["arith_1arg_msk"], "version" : "mask"},
        { "instr_name" : "frsqrt7", "datatypes" : all_float,     "template" : tpl_implem_rvv["arith_1arg_mskz"], "version" : "maskz"},
        { "instr_name" : "frsqrt7", "datatypes" : all_float,     "template" : tpl_implem_rvv["arith_1arg_msks"], "version" : "masks"},
    ],

    #ops on masks
    "andb_k" :[
        { "instr_name" : "mand",    "datatypes" : all_datatypes, "template" : tpl_implem_rvv["mask_2args"]}],
    "orb_k" :[
        { "instr_name" : "mor",     "datatypes" : all_datatypes, "template" : tpl_implem_rvv["mask_2args"]}],
    "xorb_k" :[
        { "instr_name" : "mxor",    "datatypes" : all_datatypes, "template" : tpl_implem_rvv["mask_2args"]}],

    # Arith 3args templates
    # I think maskz and masks need to be emulated for 3args funcs :-(
    "fmadd" : [
        { "instr_name" : "fmadd",   "datatypes" : all_float,     "template" : tpl_implem_rvv["arith_3args"]}, 
        { "instr_name" : "madd",   "datatypes" : [int32],       "template" : tpl_implem_rvv["arith_3args"]},

        { "instr_name" : "fmadd",   "datatypes" : all_float,     "template" : tpl_implem_rvv["arith_3args_msk"], "version" : "mask"},
        { "instr_name" : "madd",   "datatypes" : [int32],       "template" : tpl_implem_rvv["arith_3args_msk"], "version" : "mask"},
    ],
    
    "fmsub" : [
        { "instr_name" : "fmsub",   "datatypes" : all_float,     "template" : tpl_implem_rvv["arith_3args"]},
        { "instr_name" : "madd",   "datatypes" : [int32],        "template" : tpl_implem_rvv["fmsub_int"]},

        { "instr_name" : "fmsub",   "datatypes" : all_float,     "template" : tpl_implem_rvv["arith_3args_msk"], "version" : "mask"},
        # { "instr_name" : "madd",   "datatypes" : [int32],        "template" : tpl_implem_rvv["fmsub_int_msk"], "version" : "mask"},
    ],
    
    # aritm_msk_type_2args templates
    "cmpneq" : [
        { "instr_name" : "msne",   "datatypes" : all_int_uint,   "template" : tpl_implem_rvv["arith_msk_type_2args"]},
        { "instr_name" : "mfne",   "datatypes" : all_float,      "template" : tpl_implem_rvv["arith_msk_type_2args"]},

        { "instr_name" : "msne",   "datatypes" : all_int_uint,   "template" : tpl_implem_rvv["arith_msk_type_2args_mskz_cmpneq"], "version" : "maskz"},
        { "instr_name" : "mfne",   "datatypes" : all_float,      "template" : tpl_implem_rvv["arith_msk_type_2args_mskz_cmpneq"], "version" : "maskz"},  
    ], 

    "set0_k" : [
        { "instr_name" : "set0_k", "datatypes" : all_datatypes,       "template" : tpl_implem_rvv["set0_k"]}],

    "tomsk"  : [
        { "instr_name" : "tomsk",  "datatypes" : all_datatypes,   "template" : tpl_implem_rvv["tomsk"]}],  

    "cmplt" : [
        { "instr_name" : "mslt",    "datatypes" : all_int,       "template" : tpl_implem_rvv["arith_msk_type_2args"]},
        { "instr_name" : "msltu",   "datatypes" : all_uint,      "template" : tpl_implem_rvv["arith_msk_type_2args"]},
        { "instr_name" : "mflt",    "datatypes" : all_float,     "template" : tpl_implem_rvv["arith_msk_type_2args"]},

        { "instr_name" : "mslt",    "datatypes" : all_int,       "template" : tpl_implem_rvv["arith_msk_type_2args_mskz"], "version" : "maskz"},
        { "instr_name" : "msltu",   "datatypes" : all_uint,      "template" : tpl_implem_rvv["arith_msk_type_2args_mskz"], "version" : "maskz"},
        { "instr_name" : "mflt",    "datatypes" : all_float,     "template" : tpl_implem_rvv["arith_msk_type_2args_mskz"], "version" : "maskz"},    
    ],
    "cmple" : [
        { "instr_name" : "msle",    "datatypes" : all_int,       "template" : tpl_implem_rvv["arith_msk_type_2args"]},
        { "instr_name" : "msleu",   "datatypes" : all_uint,      "template" : tpl_implem_rvv["arith_msk_type_2args"]},
        { "instr_name" : "mfle",    "datatypes" : all_float,     "template" : tpl_implem_rvv["arith_msk_type_2args"]},
    
        { "instr_name" : "msle",    "datatypes" : all_int,       "template" : tpl_implem_rvv["arith_msk_type_2args_mskz"], "version" : "maskz"},
        { "instr_name" : "msleu",   "datatypes" : all_uint,      "template" : tpl_implem_rvv["arith_msk_type_2args_mskz"], "version" : "maskz"},
        { "instr_name" : "mfle",    "datatypes" : all_float,     "template" : tpl_implem_rvv["arith_msk_type_2args_mskz"], "version" : "maskz"},
    ],
    "cmpgt" : [
        { "instr_name" : "msgt",    "datatypes" : all_int,       "template" : tpl_implem_rvv["arith_msk_type_2args"]},
        { "instr_name" : "msgtu",   "datatypes" : all_uint,      "template" : tpl_implem_rvv["arith_msk_type_2args"]},
        { "instr_name" : "mfgt",    "datatypes" : all_float,     "template" : tpl_implem_rvv["arith_msk_type_2args"]},
    
        { "instr_name" : "msgt",    "datatypes" : all_int,       "template" : tpl_implem_rvv["arith_msk_type_2args_mskz"], "version" : "maskz"},
        { "instr_name" : "msgtu",   "datatypes" : all_uint,      "template" : tpl_implem_rvv["arith_msk_type_2args_mskz"], "version" : "maskz"},
        { "instr_name" : "mfgt",    "datatypes" : all_float,     "template" : tpl_implem_rvv["arith_msk_type_2args_mskz"], "version" : "maskz"},
    ],
    "cmpge" : [
        { "instr_name" : "msge",    "datatypes" : all_int,       "template" : tpl_implem_rvv["arith_msk_type_2args"]},
        { "instr_name" : "msgeu",   "datatypes" : all_uint,      "template" : tpl_implem_rvv["arith_msk_type_2args"]},
        { "instr_name" : "mfge",    "datatypes" : all_float,     "template" : tpl_implem_rvv["arith_msk_type_2args"]},

        { "instr_name" : "msge",    "datatypes" : all_int,       "template" : tpl_implem_rvv["arith_msk_type_2args_mskz"], "version" : "maskz"},
        { "instr_name" : "msgeu",   "datatypes" : all_uint,      "template" : tpl_implem_rvv["arith_msk_type_2args_mskz"], "version" : "maskz"},
        { "instr_name" : "mfge",    "datatypes" : all_float,     "template" : tpl_implem_rvv["arith_msk_type_2args_mskz"], "version" : "maskz"},
    ],
    "cmpeq" : [
        { "instr_name" : "mseq",   "datatypes" : all_int_uint,   "template" : tpl_implem_rvv["arith_msk_type_2args"]},
        { "instr_name" : "mfeq",   "datatypes" : all_float,      "template" : tpl_implem_rvv["arith_msk_type_2args"]},

        { "instr_name" : "mseq",   "datatypes" : all_int_uint,   "template" : tpl_implem_rvv["arith_msk_type_2args_mskz"], "version" : "maskz"},
        { "instr_name" : "mfeq",   "datatypes" : all_float,      "template" : tpl_implem_rvv["arith_msk_type_2args_mskz"], "version" : "maskz"},
    ],

    "getfirst" : [
        { "instr_name" : "mv",     "datatypes" : all_int_uint,   "template" : tpl_implem_rvv["scalar_getfirst"]},
        { "instr_name" : "fmv",    "datatypes" : all_float,      "template" : tpl_implem_rvv["float_getfirst"]},],

    "notb" : [
        { "instr_name" : "xor",    "datatypes" : all_int_uint,   "template" : tpl_implem_rvv["scalar_notb"]},
        { "instr_name" : "xor",    "datatypes" : all_float,      "template" : tpl_implem_rvv["float_notb"]},
        
        { "instr_name" : "xor",    "datatypes" : all_int_uint,   "template" : tpl_implem_rvv["scalar_notb_msk"], "version" : "mask"},
        { "instr_name" : "xor",    "datatypes" : all_float,      "template" : tpl_implem_rvv["float_notb_msk"], "version" : "mask"},

        { "instr_name" : "xor",    "datatypes" : all_int_uint,   "template" : tpl_implem_rvv["scalar_notb_mskz"], "version" : "maskz"},
        { "instr_name" : "xor",    "datatypes" : all_float,      "template" : tpl_implem_rvv["float_notb_mskz"], "version" : "maskz"},

        {"instr_name" : "xor",    "datatypes" : all_int_uint,   "template" : tpl_implem_rvv["scalar_notb_msks"], "version" : "masks"},
        {"instr_name" : "xor",    "datatypes" : all_float,      "template" : tpl_implem_rvv["float_notb_msks"], "version" : "masks"},
    ],

    "testz_2" : [
        { "instr_name" : "cpop",   "datatypes" : all_datatypes,  "template" : tpl_implem_rvv["testz_2"]}],

    
    # I can't think of a better way to do masked ops than emulation bc we don't have a dedicated round and the op is currentlt cvt int -> cvt f 
    "round" :  [
        { "instr_name" : "vfcvt",   "datatypes" : all_float,     "template" : tpl_implem_rvv["round_float"]},
        { "instr_name" : "vfcvt",   "datatypes" : all_int_uint,  "template" : tpl_implem_rvv["round_int"]},

        # { "instr_name" : "vfcvt",   "datatypes" : all_float,     "template" : tpl_implem_rvv["round_float_msk"],  "version" : "mask"},
        { "instr_name" : "vfcvt",   "datatypes" : all_int_uint,  "template" : tpl_implem_rvv["round_int_msk"],    "version" : "mask"},

        # { "instr_name" : "vfcvt",   "datatypes" : all_float,     "template" : tpl_implem_rvv["round_float_mskz"], "version" : "maskz"},
        { "instr_name" : "vfcvt",   "datatypes" : all_int_uint,  "template" : tpl_implem_rvv["round_int_mskz"],   "version" : "maskz"},

        # { "instr_name" : "vfcvt",   "datatypes" : all_float,     "template" : tpl_implem_rvv["round_float_msks"], "version" : "masks"},
        { "instr_name" : "vfcvt",   "datatypes" : all_int_uint,  "template" : tpl_implem_rvv["round_int_msks"],   "version" : "masks"},
    ],

    "lshift" : [
        { "instr_name" : "sll",     "datatypes" : all_int_uint,  "template" : tpl_implem_rvv["shift_scalar"]},
        { "instr_name" : "sll",     "datatypes" : all_float,     "template" : tpl_implem_rvv["shift_float"] },
        
        { "instr_name" : "sll",     "datatypes" : all_int_uint,  "template" : tpl_implem_rvv["shift_scalar_msk"], "version" : "mask"},
        { "instr_name" : "sll",     "datatypes" : all_float,     "template" : tpl_implem_rvv["shift_float_msk"], "version" : "mask"},

        { "instr_name" : "sll",     "datatypes" : all_int_uint,  "template" : tpl_implem_rvv["shift_scalar_mskz"], "version" : "maskz"},
        { "instr_name" : "sll",     "datatypes" : all_float,     "template" : tpl_implem_rvv["shift_float_mskz"], "version" : "maskz"},

        { "instr_name" : "sll",     "datatypes" : all_int_uint,  "template" : tpl_implem_rvv["shift_scalar_msks"], "version" : "masks"},
        { "instr_name" : "sll",     "datatypes" : all_float,     "template" : tpl_implem_rvv["shift_float_msks"], "version" : "masks"},
    ],

    "rshift" : [
        { "instr_name" : "srl",     "datatypes" : all_uint,  "template" : tpl_implem_rvv["shift_scalar"]},
        { "instr_name" : "sra",     "datatypes" : all_int,   "template" : tpl_implem_rvv["shift_scalar"]},
        { "instr_name" : "srl",     "datatypes" : all_float,     "template" : tpl_implem_rvv["shift_float"]},

        { "instr_name" : "srl",     "datatypes" : all_uint,  "template" : tpl_implem_rvv["shift_scalar_msk"], "version" : "mask"},
        { "instr_name" : "sra",     "datatypes" : all_int,   "template" : tpl_implem_rvv["shift_scalar_msk"], "version" : "mask"},
        { "instr_name" : "srl",     "datatypes" : all_float,     "template" : tpl_implem_rvv["shift_float_msk"], "version" : "mask"},

        { "instr_name" : "srl",     "datatypes" : all_uint,  "template" : tpl_implem_rvv["shift_scalar_mskz"], "version" : "maskz"},
        { "instr_name" : "sra",     "datatypes" : all_int,   "template" : tpl_implem_rvv["shift_scalar_mskz"], "version" : "maskz"},
        { "instr_name" : "srl",     "datatypes" : all_float,     "template" : tpl_implem_rvv["shift_float_mskz"], "version" : "maskz"},

        { "instr_name" : "srl",     "datatypes" : all_uint,  "template" : tpl_implem_rvv["shift_scalar_msks"], "version" : "masks"},
        { "instr_name" : "sra",     "datatypes" : all_int,   "template" : tpl_implem_rvv["shift_scalar_msks"], "version" : "masks"},
        { "instr_name" : "srl",     "datatypes" : all_float,     "template" : tpl_implem_rvv["shift_float_msks"], "version" : "masks"},
    ],

    "div2" : [
        { "instr_name" : "srl",     "datatypes" : all_uint,      "template" : tpl_implem_rvv["div2_scalar"]},
        { "instr_name" : "sra",     "datatypes" : all_int,       "template" : tpl_implem_rvv["div2_scalar"]},
        { "instr_name" : "fdiv",    "datatypes" : all_float,     "template" : tpl_implem_rvv["div2_float"]},

        { "instr_name" : "srl",     "datatypes" : all_uint,      "template" : tpl_implem_rvv["div2_scalar_msk"], "version" : "mask"},
        { "instr_name" : "sra",     "datatypes" : all_int,       "template" : tpl_implem_rvv["div2_scalar_msk"], "version" : "mask"},
        { "instr_name" : "fdiv",    "datatypes" : all_float,     "template" : tpl_implem_rvv["div2_float_msk"], "version" : "mask"},

        { "instr_name" : "srl",     "datatypes" : all_uint,      "template" : tpl_implem_rvv["div2_scalar_mskz"], "version" : "maskz"},
        { "instr_name" : "sra",     "datatypes" : all_int,       "template" : tpl_implem_rvv["div2_scalar_mskz"], "version" : "maskz"},
        { "instr_name" : "fdiv",    "datatypes" : all_float,     "template" : tpl_implem_rvv["div2_float_mskz"], "version" : "maskz"},

        { "instr_name" : "srl",     "datatypes" : all_uint,      "template" : tpl_implem_rvv["div2_scalar_msks"], "version" : "masks"},
        { "instr_name" : "sra",     "datatypes" : all_int,       "template" : tpl_implem_rvv["div2_scalar_msks"], "version" : "masks"},
        { "instr_name" : "fdiv",    "datatypes" : all_float,     "template" : tpl_implem_rvv["div2_float_msks"], "version" : "masks"},    
    ],

    "div4" : [
        { "instr_name" : "srl",     "datatypes" : all_uint,      "template" : tpl_implem_rvv["div4_scalar"]},
        { "instr_name" : "sra",     "datatypes" : all_int,       "template" : tpl_implem_rvv["div4_scalar"]},
        { "instr_name" : "fdiv",    "datatypes" : all_float,     "template" : tpl_implem_rvv["div4_float"]},

        { "instr_name" : "srl",     "datatypes" : all_uint,      "template" : tpl_implem_rvv["div4_scalar_msk"], "version" : "mask"},
        { "instr_name" : "sra",     "datatypes" : all_int,       "template" : tpl_implem_rvv["div4_scalar_msk"], "version" : "mask"},
        { "instr_name" : "fdiv",    "datatypes" : all_float,     "template" : tpl_implem_rvv["div4_float_msk"], "version" : "mask"},

        { "instr_name" : "srl",     "datatypes" : all_uint,      "template" : tpl_implem_rvv["div4_scalar_mskz"], "version" : "maskz"},
        { "instr_name" : "sra",     "datatypes" : all_int,       "template" : tpl_implem_rvv["div4_scalar_mskz"], "version" : "maskz"},
        { "instr_name" : "fdiv",    "datatypes" : all_float,     "template" : tpl_implem_rvv["div4_float_mskz"], "version" : "maskz"},

        { "instr_name" : "srl",     "datatypes" : all_uint,      "template" : tpl_implem_rvv["div4_scalar_msks"], "version" : "masks"},
        { "instr_name" : "sra",     "datatypes" : all_int,       "template" : tpl_implem_rvv["div4_scalar_msks"], "version" : "masks"},
        { "instr_name" : "fdiv",    "datatypes" : all_float,     "template" : tpl_implem_rvv["div4_float_msks"], "version" : "masks"},
    ],
}