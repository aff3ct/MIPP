
from tools import *



#this is used for casts. RVV intrinsic to not define widening/narrowing casts for floating types. 
#i.e no f32->f64, f32->i8, u16->f64 etc.
datatypes_int_float_cart_prod = [
    "int8,float32", "int16,float32", "int64,float32",
    "int8,float64","int16,float64", "int32,float64"
]
datatypes_uint_float_cart_prod = [
    "uint8,float32", "uint16,float32", "uint64,float32",
    "uint8,float64","uint16,float64", "uint32,float64"
]


datatypes_float_float_cart_prod = ["float64,float32", "float32,float64"]
datatypes_float_int_cart_prod = [
    "float32,int8", "float32,int16", "float32,int64", 
    "float64,int8", "float64,int16", "float64,int32"
]
datatypes_float_uint_cart_prod = [
    "float32,uint8", "float32,uint16", "float32,uint64", 
    "float64,uint8", "float64,uint16", "float64,uint32"
]

datatypes_int_uint_cart_prod = [
    "int8,uint16", "int8,uint32", "int8,uint64", 
    "int16,uint8", "int16,uint32", "int16,uint64",
    "int32,uint16", "int32,uint8", "int32,uint64", 
    "int64,uint16", "int64,uint32", "int64,uint8"
]
datatypes_uint_int_cart_prod = [
    "uint16,int8", "uint32,int8", "uint64,int8",
    "uint8,int16", "uint32,int16", "uint64,int16",
    "uint16,int32", "uint8,int32", "uint64,int32",
    "uint16,int64", "uint32,int64", "uint8,int64",
]
datatypes_intuint_float_cart_prod = datatypes_int_float_cart_prod + datatypes_uint_float_cart_prod
datatypes_float_intuint_cart_prod = datatypes_float_int_cart_prod + datatypes_float_uint_cart_prod

datatypes_intuint_cart_prod = datatypes_uint_int_cart_prod + datatypes_int_uint_cart_prod

datatypes_problematic_cart_prod = datatypes_intuint_float_cart_prod + datatypes_float_intuint_cart_prod  + datatypes_intuint_cart_prod + datatypes_float_float_cart_prod

datatypes_unproblematic_cart_prod =  list(filter(lambda x : x not in datatypes_problematic_cart_prod, all_datatypes_cart_prod))

#cast_k types
datatypes_same_size = [
    # identity (a == b)
    "int8,int8",
    "uint8,uint8",
    "int16,int16",
    "uint16,uint16",
    "int32,int32",
    "uint32,uint32",
    "float32,float32",
    "int64,int64",
    "uint64,uint64",
    "float64,float64",

    # existing same-size cross-type pairs
    "int8,uint8", "uint8,int8",

    "int16,uint16", "uint16,int16",

    "int32,uint32", "uint32,int32",
    "int32,float32", "float32,int32",
    "uint32,float32", "float32,uint32",

    "int64,uint64", "uint64,int64",
    "int64,float64", "float64,int64",
    "uint64,float64", "float64,uint64",
]

datatypes_narrowing = [
    # 16 -> 8
    "int16,int8", "int16,uint8",
    "uint16,int8", "uint16,uint8",

    # 32 -> 16
    "int32,int16", "int32,uint16",
    "uint32,int16", "uint32,uint16",
    "float32,int16", "float32,uint16",

    # 32 -> 8
    "int32,int8", "int32,uint8",
    "uint32,int8", "uint32,uint8",
    "float32,int8", "float32,uint8",

    # 64 -> 32
    "int64,int32", "int64,uint32", "int64,float32",
    "uint64,int32", "uint64,uint32", "uint64,float32",
    "float64,int32", "float64,uint32", "float64,float32",

    # 64 -> 16
    "int64,int16", "int64,uint16",
    "uint64,int16", "uint64,uint16",
    "float64,int16", "float64,uint16",

    # 64 -> 8
    "int64,int8", "int64,uint8",
    "uint64,int8", "uint64,uint8",
    "float64,int8", "float64,uint8",
]

datatypes_widening = [
    # 8 -> 16
    "int8,int16", "int8,uint16",
    "uint8,int16", "uint8,uint16",

    # 8 -> 32
    "int8,int32", "int8,uint32", "int8,float32",
    "uint8,int32", "uint8,uint32", "uint8,float32",

    # 8 -> 64
    "int8,int64", "int8,uint64", "int8,float64",
    "uint8,int64", "uint8,uint64", "uint8,float64",

    # 16 -> 32
    "int16,int32", "int16,uint32", "int16,float32",
    "uint16,int32", "uint16,uint32", "uint16,float32",

    # 16 -> 64
    "int16,int64", "int16,uint64", "int16,float64",
    "uint16,int64", "uint16,uint64", "uint16,float64",

    # 32 -> 64
    "int32,int64", "int32,uint64", "int32,float64",
    "uint32,int64", "uint32,uint64", "uint32,float64",
    "float32,int64", "float32,uint64", "float32,float64",
]

tpl_implem_emu_rvv = {
    "loadu" : { "format": "long", "code": """
        if ((((uint64_t)p0) & (8 - 1)) == 0) {
            %r<tp>% out;
            out.r = {{isa.prefix}}_vle{{isa_dt_par.data_ext_logi}}_v_{{isa_dt_par.data_ext}}(({{ isa_dt_par.to_ptr }}*)p0, %N<tp>%);
            return out;
        } else {
            alignas(8) {{isa_dt_par.to_ptr}} tmp[%N<tp>%];
            memcpy(tmp, p0, %N<tp>%);
            %r<tp>% out;
            out.r = {{ isa.prefix }}_vle{{ isa_dt_par.data_ext_logi }}_v_{{ isa_dt_par.data_ext }}(({{ isa_dt_par.to_ptr }}*) tmp, %N<tp>%);
            return out;
        } 
    """},
    "storeu" : { "format": "long", "code": """
        if ((((uint64_t)p0) & (8 - 1)) == 0) {
            return {{isa.prefix}}_vse{{isa_dt_par.data_ext_logi}}_v_{{isa_dt_par.data_ext}}(({{ isa_dt_par.to_ptr }}*)p0, r0.r, %N<tp>%);
        } else {
            alignas(8) {{isa_dt_par.to_ptr}} tmp[%N<tp>%];
            {{ isa.prefix }}_vse{{ isa_dt_par.data_ext_logi }}_v_{{ isa_dt_par.data_ext }}(({{ isa_dt_par.to_ptr }}*) tmp, r0.r, %N<tp>%);
            memcpy(p0, tmp, %N<tp>%);
            return;
        }
    """ },
    
    "scalar_get" : { "format": "long", "code": """              
        {{isa_dt_par.reg}} tmp;
        tmp = {{ isa.prefix }}_vslidedown_vx_{{isa_dt_par.data_ext}}(r0.r, v0, %N<tp>%);
        {{isa_dt_par.to_ptr}} out = {{isa.prefix}}_{{instr_name}}_x_s_{{isa_dt_par.data_ext}}_{{isa_dt_par.reg_dt_ext}}(tmp);
        
        return out;
    """ },
    "float_get" : { "format": "long", "code": """              
        {{isa_dt_par.reg}} tmp;
        tmp = {{ isa.prefix }}_vslidedown_vx_{{isa_dt_par.data_ext}}(r0.r, v0, %N<tp>%);
        {{isa_dt_par.to_ptr}} out = {{isa.prefix}}_{{instr_name}}_f_s_{{isa_dt_par.data_ext}}_{{isa_dt_par.reg_dt_ext}}(tmp);
        
        return out;
    """ },
    
    #this is jsut loadu.... maybe there is a way to get function arguments n factorise this n loadu?
    "set" : { "format": "long", "code": """
        if ((((uint64_t)vals) & (8 - 1)) == 0) {
            %r<tp>% out;
            out.r = {{isa.prefix}}_vle{{isa_dt_par.data_ext_logi}}_v_{{isa_dt_par.data_ext}}(({{ isa_dt_par.to_ptr }}*)vals, %N<tp>%);
            return out;
        } else {
            alignas(8) {{isa_dt_par.to_ptr}} tmp[%N<tp>%];
            memcpy(tmp, vals, %N<tp>%);
            %r<tp>% out;
            out.r = {{ isa.prefix }}_vle{{ isa_dt_par.data_ext_logi }}_v_{{ isa_dt_par.data_ext }}(({{ isa_dt_par.to_ptr }}*) tmp, %N<tp>%);
            return out;
        } 
    """},
    
    "set_k" : {"format" : "long", "code" : """
         
        size_t nbytes = (%N<tp>% + 7) / 8;  
        uint8_t packed[nbytes];
        memset(packed, 0, nbytes);    
        for(unsigned i = 0 ; i < %N<tp>%; i++){
            if (vals[i] != 0) packed[i >> 3] |= (uint8_t)1 << (i & 7);
        }
        %m<tp>% out;
        out.m = {{isa.prefix}}_vlm_v_{{isa_dt_par.data_ext_msk}}(packed, %N<tp>%);
        return out;
    """},
    
    "set1_k" : {"format" : "long", "code" : """
        int32_t vals[%N<tp>%];
        memset(vals,v0,%N<tp>%*sizeof(int32_t));
        return %set_k<tp>%(vals);
    """},
    
    "set0_k" : {"format" : "long", "code" : """        
        return %set1_k<tp>%(0);
    """},
    
    #from implem_emu_SVE.py
    "toreg-64" : { "format": "long", "code":"""
        %r<tp>% one  = %set1<tp>%(0xFFFFFFFFFFFFFFFF);
        %r<tp>% zero = %set1<tp>%(0);
        
        %r<tp>% ret;
        ret.r = {{ isa.prefix }}_vmerge_vvm_{{ isa_dt_par.data_ext }}(zero.r, one.r, m0.m, %N<tp>%);
        return ret;
    """},
    "toreg-32" : { "format": "long", "code":"""
        %r<tp>% one  = %set1<tp>%(0xFFFFFFFF);
        %r<tp>% zero = %set1<tp>%(0);
        %r<tp>% ret;
        ret.r = {{ isa.prefix }}_vmerge_vvm_{{ isa_dt_par.data_ext }}(zero.r, one.r, m0.m, %N<tp>%);
        return ret;
    """},
    "toreg-16" : { "format": "long", "code":"""
        %r<tp>% one  = %set1<tp>%(0xFFFF);
        %r<tp>% zero = %set1<tp>%(0);
        
        %r<tp>% ret;
        ret.r = {{ isa.prefix }}_vmerge_vvm_{{ isa_dt_par.data_ext }}(zero.r, one.r, m0.m, %N<tp>%);
        return ret;
    """},
    
    "toreg-8" : { "format": "long", "code":"""
        %r<tp>% one  = %set1<tp>%(0xFF);
        %r<tp>% zero = %set1<tp>%(0);
        %r<tp>% ret;
        ret.r = {{ isa.prefix }}_vmerge_vvm_{{ isa_dt_par.data_ext }}(zero.r, one.r, m0.m, %N<tp>%);
        return ret;
    """},
    
    #from implem emu avx.
    "get_k" : {"format" : "long", "code" : """
        %v<tp>% tmp[%N<tp>%];
	    %r<tp>% rmsk =%toreg<tp>%(m0);
	    %storeu<tp>%(tmp, rmsk);
	    return (int32_t) tmp[v0];
    """},
    
    "maskz_inst": {"format" : "long", "code" : """
    
    %r<tp>% ret = %set1<tp>%(0);
        ret.r = {{ isa.prefix }}_v{{ instr_name }}_vv_{{ isa_dt_par.data_ext }}_mu(m0.m, ret.r, r0.r, r1.r, %N<tp>%);
        return ret;
    """},
    
    "scalar_andnb": {"format" : "long", "code" : """
        %r<tp>% ret = %set1<tp>%(-1);
        ret = %xorb<tp>%(r0, ret);
        ret = %andb<tp>%(r1, ret);  
        return ret;  
    """},
    
    "float_andnb" : {"format" : "long", "code" : """
        {{isa_dt_par.to_uint}} tmp0,tmp1, tmpm1;
        
        tmp0 = {{isa.prefix}}_vfcvt_xu_f_v_{{isa_dt_par.uint_data_ext}}(r0.r, %N<tp>%);
        tmp1 = {{isa.prefix}}_vfcvt_xu_f_v_{{isa_dt_par.uint_data_ext}}(r1.r, %N<tp>%);
        tmpm1 = {{isa.prefix}}_vmv_s_x_{{isa_dt_par.uint_data_ext}}(-1,%N<tp>%);
        
        tmp0 = {{ isa.prefix }}_vxor_vv_{{ isa_dt_par.uint_data_ext }}(tmp0, tmpm1, %N<tp>%);
        tmp0 = {{ isa.prefix }}_vand_vv_{{ isa_dt_par.uint_data_ext }}(tmp0, tmp1, %N<tp>%);
        %r<tp>% ret;
        ret.r = {{ isa.prefix }}_vfcvt_f_xu_v_{{isa_dt_par.data_ext}}(tmp0, %N<tp>%);
        return ret;
    """},
    
    "andnb_k" : {"format" : "long", "code" : """
        %m<tp>% ret = %set1_k<tp>%(-1);
        ret = %xorb_k<tp>%(m0,ret);
        ret = %andb_k<tp>%(m1,ret);
        return ret;
    """},
    
    "maskzld" : {"format" : "long", "code" : """
        %r<tp>% ret = %set1<tp>%(0);
        ret.r = {{ isa.prefix }}_vle{{ isa_dt_par.data_ext_logi }}_v_{{ isa_dt_par.data_ext }}_mu(m0.m,ret.r,({{isa_dt_par.to_ptr}}*)p0, %N<tp>%);
        return ret;
    """},  
    
     #suitable for hadd and hmax on unsigned ints
    "hadd_hmax_uint":{"format" : "long", "code":"""
                %r<tp>% ret = %set1<tp>%(0);
                ret.r = {{isa.prefix}}_v{{instr_name}}_vs_{{isa_dt_par.data_ext}}_{{isa_dt_par.data_ext}}(r0.r,ret.r,%N<tp>%);
                return ret;
    """},
    
    "hmax_int":{"format" : "long", "code":"""
                %r<tp>% ret = %set1<tp>%(INT{{isa_dt_par.data_ext_logi}}_MIN);
                ret.r = {{isa.prefix}}_v{{instr_name}}_vs_{{isa_dt_par.data_ext}}_{{isa_dt_par.data_ext}}(r0.r,ret.r,%N<tp>%);
                return ret;
    """},
    
    "hmax_float32":{"format" : "long", "code":"""
                %r<tp>% ret = %set1<tp>%(FLT_MIN);
                ret.r = {{isa.prefix}}_v{{instr_name}}_vs_{{isa_dt_par.data_ext}}_{{isa_dt_par.data_ext}}(r0.r,ret.r,%N<tp>%);
                return ret;
    """},
    
    "hmax_float64":{"format" : "long", "code":"""
                %r<tp>% ret = %set1<tp>%(DBL_MIN);
                ret.r = {{isa.prefix}}_v{{instr_name}}_vs_{{isa_dt_par.data_ext}}_{{isa_dt_par.data_ext}}(r0.r,ret.r,%N<tp>%);
                return ret;
    """},
    
    "hmin_int":{"format" : "long", "code":"""
                %r<tp>% ret = %set1<tp>%(INT{{isa_dt_par.data_ext_logi}}_MAX);
                ret.r = {{isa.prefix}}_v{{instr_name}}_vs_{{isa_dt_par.data_ext}}_{{isa_dt_par.data_ext}}(r0.r,ret.r,%N<tp>%);
                return ret;
    """},
    
    "hmin_uint":{"format" : "long", "code":"""
                %r<tp>% ret = %set1<tp>%(UINT{{isa_dt_par.data_ext_logi}}_MAX);
                ret.r = {{isa.prefix}}_v{{instr_name}}_vs_{{isa_dt_par.data_ext}}_{{isa_dt_par.data_ext}}(r0.r,ret.r,%N<tp>%);
                return ret;
    """},
    
    "hmin_float32":{"format" : "long", "code":"""
                %r<tp>% ret = %set1<tp>%(FLT_MAX);
                ret.r = {{isa.prefix}}_v{{instr_name}}_vs_{{isa_dt_par.data_ext}}_{{isa_dt_par.data_ext}}(r0.r,ret.r,%N<tp>%);
                return ret;
    """},
    
    "hmin_float64":{"format" : "long", "code":"""
                %r<tp>% ret = %set1<tp>%(DBL_MAX);
                ret.r = {{isa.prefix}}_v{{instr_name}}_vs_{{isa_dt_par.data_ext}}_{{isa_dt_par.data_ext}}(r0.r,ret.r,%N<tp>%);
                return ret;
    """},  
    
    "notb_k":{"format":"long", "code": """
        %m<tp>% ret;
        ret = %set1_k<tp>%(0);
        ret.m = {{isa.prefix}}_v{{instr_name}}_mm_{{isa_dt_par.data_ext_msk}}(ret.m,m0.m, %N<tp>%);
        return ret;
   """},
    
    "testz":{"format":"long", "code": """
        return %testz_2<tp>%(m0) && %testz_2<tp>%(m1);
    """},
    
    "hmul_int_uint":{"format":"long", "code": """
    
    %r<tp>% tmp; 
    tmp.r = r0.r;
    size_t vl = %N<tp>%;
    for (size_t off = 1; off < vl; off <<= 1) {
        %r<tp>% shifted; 
        shifted.r =  {{isa.prefix}}_vslidedown_vx_{{isa_dt_par.data_ext}}(tmp.r,off,vl);
        tmp.r = {{isa.prefix}}_{{instr_name}}_vv_{{isa_dt_par.data_ext}}(tmp.r, shifted.r, vl);
    }
    //return {{isa.prefix}}_vmv_x_s_{{isa_dt_par.data_ext}}_{{isa_dt_par.reg_dt_ext}}(tmp.r);
    return tmp;
    """},
    
    "hmul_float":{"format":"long", "code": """

    %r<tp>% tmp;
    tmp.r = r0.r;
    size_t vl = %N<tp>%;
    for (size_t off = 1; off < vl; off <<= 1) {
        %r<tp>% shifted;
        shifted.r =  {{isa.prefix}}_vslidedown_vx_{{isa_dt_par.data_ext}}(tmp.r,off,vl);
        tmp.r = {{isa.prefix}}_{{instr_name}}_vv_{{isa_dt_par.data_ext}}(tmp.r, shifted.r, vl);
    }
    //return {{isa.prefix}}_vfmv_f_s_{{isa_dt_par.data_ext}}_{{isa_dt_par.reg_dt_ext}}(tmp.r);
    return tmp;
    """},
    
    "hadd_to_scal": {"format": "long", "code":"""
    %r<tp>% tmp = %hadd<tp>%(r0);
    return {{isa.prefix}}_{{instr_name}}_s_{{isa_dt_par.data_ext}}_{{isa_dt_par.reg_dt_ext}}(tmp.r);
    """},
    
    #generic cast for "unproblematic" i.e single intrinsic casts
    "cast":{ "format": "short", "code": "{% if isa_dt_par.data_ext != isa_dt_ret.data_ext -%} {{ isa.prefix }}_{{ instr_name }}_v_{{isa_dt_par.data_ext}}_{{isa_dt_ret.data_ext}}(r0.r);{% else -%} r0.r;{% endif %}"},
    
    #cast float->other
    "cast_float_other" : { "format" : "long", "code":"""
    %r<c:int|b:tp>% rint = %cast<tp,c:int|b:tp>%(r0); 
    %r<c:int|b:tr>% rint2 = %cast<c:int|b:tp,c:int|b:tr>%(rint);
    
    return %cast<c:int|b:tr,tr>%(rint2);            
    """},

    #used for int to float, int to uint, uint to int
    "cast_intuint_other" : { "format" : "long", "code":"""
    %r<c:tp|b:tr>% r1 = %cast<c:tp|b:tp,c:tp|b:tr>%(r0);
    return %cast<c:tp|b:tr,c:tr|b:tr>%(r1);
    """},
    
    "tomsk" : {"format" : "long", "code" : """       
    %r<tp>% r1 = %set1<tp>%(0); 
    return %cmpneq<tp>%(r1,r0);
    """},
    
    "msb-64": { "format": "long", "code":
"""	%r<tp>% rm = %cast<c:int|b:tp,tp>%(%set1<c:int|b:tp>%(0x8000000000000000));
	return %andb<tp>%(r0, rm);"""
	},
	"msb-32": { "format": "long", "code":
"""	%r<tp>% rm = %cast<c:int|b:tp,tp>%(%set1<c:int|b:tp>%(0x80000000));
	return %andb<tp>%(r0, rm);"""
	},
	"msb-16": { "format": "long", "code":
"""	%r<tp>% rm = %cast<c:int|b:tp,tp>%(%set1<c:int|b:tp>%(0x8000));
	return %andb<tp>%(r0, rm);"""
	},
	"msb-8": { "format": "long", "code":
"""	%r<tp>% rm = %cast<c:int|b:tp,tp>%(%set1<c:int|b:tp>%(0x80));
	return %andb<tp>%(r0, rm);"""
	},
 
    "cast_k_same_size":{"format":"short", "code":"m0.m;"},
    
    "cast_k_diff_size":{"format":"long", "code":"""
        %r<tp>% r0 =  %toreg<tp>%(m0);
        %r<tr>% r1 = %cast<tp,tr>%(r0);
        %r<c:uint|b:tr>% rtmp0;
        rtmp0.r = {{isa.prefix}}_vid_v_u{{isa_dt_ret.data_ext_logi}}m1(%N<tp>%);
        %r<tr>% rtmp = %cast<c:uint|b:tr,tr>%(rtmp0);
        %r<tr>% rtmp1;
        rtmp1 = %set0<tr>%();
        rtmp = %andb<tr>%(rtmp,rtmp1);
        r1 = %andb<tr>%(r1,rtmp);
        return %tomsk<tr>%(r1);
    """},

    "cast_k_narrowing":{"format":"long", "code":"""
        %r<tp>% r0 = %toreg<tp>%(m0);
        %r<tr>% r1 = %cast<tp,tr>%(r0);
        %r<tr>% rtmp;
        rtmp.r = {{isa.prefix}}_vid_v_u{{isa_dt_re.data_ext_logi}}m1(%N<tr>%);
        %r<tr>% rtmp1;
        rtmp1 = %set0<tr>%(1);
        rtmp = %andb<tr>%(rtmp,rtmp1);
        r1 = %andb<tr>%(r1,rtmp);
        return %tomsk<tr>%(r1);
    """}

}

implems_emu_rvv = {
    
    #emulation : load if aligned, else copy buffer to tmp stack buffer, and load it.
    "loadu" : [{"instr_name" : "loadu", "datatypes": all_datatypes, "template": tpl_implem_emu_rvv["loadu"]}],
    #emulation : store if aligned, else store to aligned tmp stack buffer and then copy it.
    "storeu" : [{"instr_name" : "storeu", "datatypes": all_datatypes, "template": tpl_implem_emu_rvv["storeu"]}],
    
    #emulation : slidedown to lane0, mv lane0 to a register
    "get" : [{"instr_name" : "vmv", "datatypes": all_int_uint, "template": tpl_implem_emu_rvv["scalar_get"]},
             {"instr_name" : "vfmv", "datatypes": all_float, "template": tpl_implem_emu_rvv["float_get"]}],
    
    #emulation : loadu.
    "set" : [{"instr_name" : "loadu", "datatypes": all_datatypes, "template": tpl_implem_emu_rvv["set"]}],
    "set_k" : [{"instr_name" : "set_k", "datatypes": all_datatypes, "template": tpl_implem_emu_rvv["set_k"]}],
    # error when generating for all dttypes : Panic: unsupported type for 'set1_k<float64,float64>' function.
    # "set1_k" : [{"instr_name" : "set1_k", "datatypes": all_datatypes, "template": tpl_implem_emu_rvv["set1_k"]}],
    "set1_k" : [{"instr_name" : "set1_k", "datatypes": all_int_uint, "template": tpl_implem_emu_rvv["set1_k"]}],
    "set0_k" : [{"instr_name" : "set0_k", "datatypes": all_datatypes, "template": tpl_implem_emu_rvv["set0_k"]}],
    
    "toreg":[ 
        # verifier genaralisation autres types
        { "datatypes":  [uint64, int64, float64], "template": tpl_implem_emu_rvv["toreg-64"]  } ,
        { "datatypes":  [uint32, int32, float32], "template": tpl_implem_emu_rvv["toreg-32"]  } ,
        { "datatypes":  [uint16, int16], "template": tpl_implem_emu_rvv["toreg-16"]  } ,
        { "datatypes":  [uint8, int8], "template": tpl_implem_emu_rvv["toreg-8"]  } ,
    ],
    "get_k" :[{"instr_name" : "get_k", "datatypes" : all_datatypes, "template" : tpl_implem_emu_rvv["get_k"]}],

    "andnb" : [{"instr_name" : "get_k", "datatypes" : all_int_uint, "template" : tpl_implem_emu_rvv["scalar_andnb"]},
              {"instr_name" : "get_k", "datatypes" : all_float, "template" : tpl_implem_emu_rvv["float_andnb"]}],
    
    "andnb_k":[{"instr_name": "andnb_k", "datatypes" : all_int_uint, "template" : tpl_implem_emu_rvv["andnb_k"]}],

    
    "maskz_add": [
        { "instr_name" : "add", "datatypes" : all_int_uint, "template" : tpl_implem_emu_rvv["maskz_inst"]},
        { "instr_name" : "fadd", "datatypes" : all_float, "template" : tpl_implem_emu_rvv["maskz_inst"]}
    ],
    
    #"maskz_sub": [
    #    { "instr_name" : "add", "datatypes" : all_int_uint, "template" : tpl_implem_emu_rvv["maskz_inst"]},
    #    { "instr_name" : "fadd", "datatypes" : all_float, "template" : tpl_implem_emu_rvv["maskz_inst"]}
    #],
    
    #"maskzld":[
	#    { "instr_name": "maskload", "datatypes": all_float, "template": tpl_implem_emu_rvv["maskzld"] },
	#	{ "instr_name": "maskload", "datatypes": all_int_uint, "template": tpl_implem_emu_rvv["maskzld"]}
    #],
    
    "hadd" : [
        {"instr_name": "redsum", "datatypes": all_int_uint, "template": tpl_implem_emu_rvv["hadd_hmax_uint"]},
        #I could use fredusum for unordered sum as well.
        {"instr_name": "fredosum", "datatypes": all_float, "template": tpl_implem_emu_rvv["hadd_hmax_uint"]},
    ],
   
   #redmul does not exist in rvv :((((
   #"hmul":
           
   #can't use same template bc I need min value / max value for the types....
   "hmin":[
        {"instr_name": "redmin", "datatypes": all_int, "template": tpl_implem_emu_rvv["hmin_int"]},
        {"instr_name": "redminu", "datatypes": all_uint, "template": tpl_implem_emu_rvv["hmin_uint"]},


        {"instr_name": "fredmin", "datatypes": [float32], "template": tpl_implem_emu_rvv["hmin_float32"]},
        {"instr_name": "fredmin", "datatypes": [float64], "template": tpl_implem_emu_rvv["hmin_float64"]},

   ],
   "hmax":[
        {"instr_name": "redmax", "datatypes": all_int, "template": tpl_implem_emu_rvv["hmax_int"]},
 
        {"instr_name": "redmaxu", "datatypes": all_uint, "template": tpl_implem_emu_rvv["hadd_hmax_uint"]},
        
        {"instr_name": "fredmax", "datatypes": [float32], "template": tpl_implem_emu_rvv["hmax_float32"]},
        {"instr_name": "fredmax", "datatypes": [float64], "template": tpl_implem_emu_rvv["hmax_float64"]},
   ],
   
   "notb_k" : [{"instr_name" : "morn", "datatypes" : all_datatypes, "template" : tpl_implem_emu_rvv["notb_k"]}],
   
   #pourquoi testz_2?
   "testz" : [{"instr_name" : "cpop", "datatypes" : all_datatypes, "template" : tpl_implem_emu_rvv["testz"]}],
   "hmul"  : [
       {"instr_name" : "vmul", "datatypes" : all_int_uint, "template" : tpl_implem_emu_rvv["hmul_int_uint"]},
       {"instr_name" : "vfmul", "datatypes" : all_float, "template" : tpl_implem_emu_rvv["hmul_float"]},
    
    ],
   
   "hadd_to_scal" : [
       {"instr_name" : "vmv_x", "datatypes" : all_int_uint, "template" : tpl_implem_emu_rvv["hadd_to_scal"]},
       {"instr_name" : "vfmv_f", "datatypes" : all_float, "template" : tpl_implem_emu_rvv["hadd_to_scal"]},
   ],
   
   "cast" : [
       {"instr_name" : "vreinterpret", "datatypes" : datatypes_unproblematic_cart_prod, "template" : tpl_implem_emu_rvv["cast"]},
       {"instr_name": "vreinterpret", "datatypes" : datatypes_intuint_float_cart_prod, "template" : tpl_implem_emu_rvv["cast_intuint_other"]},
       {"instr_name": "vreinterpret", "datatypes" : datatypes_intuint_cart_prod, "template" : tpl_implem_emu_rvv["cast_intuint_other"]},
       {"instr_name": "vreinterpret", "datatypes" : datatypes_float_float_cart_prod, "template" : tpl_implem_emu_rvv["cast_float_other"]},
       {"instr_name": "vreinterpret", "datatypes" : datatypes_float_intuint_cart_prod, "template" : tpl_implem_emu_rvv["cast_float_other"]},

   ],
    
   "tomsk"  : [{"instr_name": "tomsk", "datatypes": all_datatypes, "template" : tpl_implem_emu_rvv["tomsk"]}],   

    #from avx2
    
    "msb": [
		{ "datatypes": [float64, int64, uint64], "template": tpl_implem_emu_rvv["msb-64"] },
		{ "datatypes": [float32, int32, uint32], "template": tpl_implem_emu_rvv["msb-32"] },
		{ "datatypes": [int16, uint16], "template": tpl_implem_emu_rvv["msb-16"] },
		{ "datatypes": [int8, uint8], "template": tpl_implem_emu_rvv["msb-8"] }, ],
    
    "cast_k" : [
      #no problem
      {"instr_name" : "vid", "datatypes" : datatypes_same_size, "template" : tpl_implem_emu_rvv["cast_k_same_size"]},
      #use toreg->cast->vid+and(1)->tomask
      {"instr_name" : "vid", "datatypes" : datatypes_narrowing, "template" : tpl_implem_emu_rvv["cast_k_diff_size"]},
      #dont know how its supposed to work
      {"instr_name" : "vid", "datatypes" : datatypes_widening, "template" : tpl_implem_emu_rvv["cast_k_diff_size"]},
    ],
    
}