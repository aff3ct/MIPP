
from tools import *
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
    
    #from implem_emu_SVE.py
    "toreg-64" : { "format": "long", "code":
 """%r<tp>% one  = %set1<tp>%(0xFFFFFFFFFFFFFFFF);
    %r<tp>% zero = %set1<tp>%(0);
    
    %r<tp>% ret;
    ret.r = {{ isa.prefix }}_vmerge_vvm_{{ isa_dt_par.data_ext }}(zero.r, one.r, m0.m, %N<tp>%);
    return ret;"""
    },
    "toreg-32" : { "format": "long", "code":
 """%r<tp>% one  = %set1<tp>%(0xFFFFFFFF);
    %r<tp>% zero = %set1<tp>%(0);
    %r<tp>% ret;
    ret.r = {{ isa.prefix }}_vmerge_vvm_{{ isa_dt_par.data_ext }}(zero.r, one.r, m0.m, %N<tp>%);
    return ret;"""
    },
    "toreg-16" : { "format": "long", "code":
 """%r<tp>% one  = %set1<tp>%(0xFFFF);
    %r<tp>% zero = %set1<tp>%(0);
    
    %r<tp>% ret;
    ret.r = {{ isa.prefix }}_vmerge_vvm_{{ isa_dt_par.data_ext }}(zero.r, one.r, m0.m, %N<tp>%);
    return ret;"""
    },
    "toreg-8" : { "format": "long", "code":
 """%r<tp>% one  = %set1<tp>%(0xFF);
    %r<tp>% zero = %set1<tp>%(0);
    %r<tp>% ret;
    ret.r = {{ isa.prefix }}_vmerge_vvm_{{ isa_dt_par.data_ext }}(zero.r, one.r, m0.m, %N<tp>%);
    return ret;"""
    },
    
    #from implem emu avx.
    "get_k" : {"format" : "long", "code" : """
        uint8_t tmp[%N<tp>%];
	    %r<tp>% rmsk =%toreg<tp>%(m0);
	    %storeu<tp>%(tmp, rmsk);
	    return (int32_t) tmp[v0];
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
    
    "toreg":[ 
        # verifier genaralisation autres types
        { "datatypes":  [uint64, int64, float64], "template": tpl_implem_emu_rvv["toreg-64"]  } ,
        { "datatypes":  [uint32, int32, float32], "template": tpl_implem_emu_rvv["toreg-32"]  } ,
        { "datatypes":  [uint16, int16], "template": tpl_implem_emu_rvv["toreg-16"]  } ,
        { "datatypes":  [uint8, int8], "template": tpl_implem_emu_rvv["toreg-8"]  } ,
    ],
    "get_k" :[{"instr_name" : "get_k", "datatypes" : all_datatypes, "template" : tpl_implem_emu_rvv["get_k"]}],

}