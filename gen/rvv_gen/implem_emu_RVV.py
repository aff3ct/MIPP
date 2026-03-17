
from tools import *
tpl_implem_emu_rvv = {
    "loadu" : { "format": "long", "code": """
        if ((((uint64_t)p0) & (8 - 1)) == 0) {
            %r<tp>% out;
            out.r = {{isa.prefix}}_vle{{isa_dt_par.data_ext_logi}}_v_{{isa_dt_par.data_ext}}(({{ isa_dt_par.to_ptr }}*)p0, MIPP_RVV_VL/sizeof({{isa_dt_par.to_ptr}}));
            return out;
        } else {
            alignas(8) {{isa_dt_par.to_ptr}} tmp[MIPP_RVV_VL/sizeof({{isa_dt_par.to_ptr}})];
            memcpy(tmp, p0, MIPP_RVV_VL);
            %r<tp>% out;
            out.r = {{ isa.prefix }}_vle{{ isa_dt_par.data_ext_logi }}_v_{{ isa_dt_par.data_ext }}(({{ isa_dt_par.to_ptr }}*) tmp, MIPP_RVV_VL/sizeof({{isa_dt_par.to_ptr}}));
            return out;
        } 
    """},
    "storeu" : { "format": "long", "code": """
        if ((((uint64_t)p0) & (8 - 1)) == 0) {
            return {{isa.prefix}}_vse{{isa_dt_par.data_ext_logi}}_v_{{isa_dt_par.data_ext}}(({{ isa_dt_par.to_ptr }}*)p0, r0.r, MIPP_RVV_VL/sizeof({{isa_dt_par.to_ptr}}));
        } else {
            alignas(8) {{isa_dt_par.to_ptr}} tmp[MIPP_RVV_VL/sizeof({{isa_dt_par.to_ptr}})];
            {{ isa.prefix }}_vse{{ isa_dt_par.data_ext_logi }}_v_{{ isa_dt_par.data_ext }}(({{ isa_dt_par.to_ptr }}*) tmp, r0.r, MIPP_RVV_VL/sizeof({{isa_dt_par.to_ptr}}));
            memcpy(p0, tmp, MIPP_RVV_VL);
            return;
        }
    """ },
    "scalar_get" : { "format": "long", "code": """              
        {{isa_dt_par.reg}} tmp;
        tmp = {{ isa.prefix }}_vslidedown_vx_{{isa_dt_par.data_ext}}(r0.r, v0, MIPP_RVV_VL/sizeof({{isa_dt_par.to_ptr}}));
        {{isa_dt_par.to_ptr}} out = {{isa.prefix}}_{{instr_name}}_x_s_{{isa_dt_par.data_ext}}_{{isa_dt_par.reg_dt_ext}}(tmp);
        
        return out;
    """ },
    
    "float_get" : { "format": "long", "code": """              
        {{isa_dt_par.reg}} tmp;
        tmp = {{ isa.prefix }}_vslidedown_vx_{{isa_dt_par.data_ext}}(r0.r, v0, MIPP_RVV_VL/sizeof({{isa_dt_par.to_ptr}}));
        {{isa_dt_par.to_ptr}} out = {{isa.prefix}}_{{instr_name}}_f_s_{{isa_dt_par.data_ext}}_{{isa_dt_par.reg_dt_ext}}(tmp);
        
        return out;
    """ },
    
    #this is jsut loadu.... maybe there is a way to get function arguments n factorise this n loadu?
    "set" : { "format": "long", "code": """
        if ((((uint64_t)vals) & (8 - 1)) == 0) {
            %r<tp>% out;
            out.r = {{isa.prefix}}_vle{{isa_dt_par.data_ext_logi}}_v_{{isa_dt_par.data_ext}}(({{ isa_dt_par.to_ptr }}*)vals, MIPP_RVV_VL/sizeof({{isa_dt_par.to_ptr}}));
            return out;
        } else {
            alignas(8) {{isa_dt_par.to_ptr}} tmp[MIPP_RVV_VL/sizeof({{isa_dt_par.to_ptr}})];
            memcpy(tmp, vals, MIPP_RVV_VL);
            %r<tp>% out;
            out.r = {{ isa.prefix }}_vle{{ isa_dt_par.data_ext_logi }}_v_{{ isa_dt_par.data_ext }}(({{ isa_dt_par.to_ptr }}*) tmp, MIPP_RVV_VL/sizeof({{isa_dt_par.to_ptr}}));
            return out;
        } 
    """},
    
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
    "set" : [{"instr_name" : "loadu", "datatypes": all_datatypes, "template": tpl_implem_emu_rvv["set"]}]

}