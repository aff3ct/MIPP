
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
    #"get" :         { "format": "long", "code": """              
    #    {{isa_dt_par.reg}} tmp;
    #    tmp ={{ isa.prefix }}_vslidedown_vx_{{isa_dt_par.data_ext}}(r0.r, v0, MIPP_RVV_VL/sizeof({{isa_dt_par.to_ptr}}));
    #    {{isa_dt_par.to_ptr}} out;
    #    
    #    __asm__ volatile ("vmv.x.s ??'0, ??'1"
    #    : "=r"(out)
    #    : "v"(tmp));
    #
    #    return out;
    #""" },
    
    "get" :         { "format": "long", "code": """              

        {{isa_dt_par.to_ptr}} out;
        //idk man stack alloc an array or smth
        {{isa_dt_par.to_ptr}} tmp_arr[MIPP_RVV_VL/sizeof({{isa_dt_par.to_ptr}})];
        {{ isa.prefix }}_vse{{ isa_dt_par.data_ext_logi}}_v_{{ isa_dt_par.data_ext }}(({{ isa_dt_par.to_ptr }}*) tmp_arr, r0.r, MIPP_RVV_VL/sizeof({{isa_dt_par.to_ptr}}));
        out = tmp_arr[v0];
        return out;
        
    """ },

}

implems_emu_rvv = {
    "loadu" : [{"instr_name" : "loadu", "datatypes": all_datatypes, "template": tpl_implem_emu_rvv["loadu"]}],
    "storeu" : [{"instr_name" : "storeu", "datatypes": all_datatypes, "template": tpl_implem_emu_rvv["storeu"]}],
    "get" : [{"instr_name" : "get", "datatypes": all_datatypes, "template": tpl_implem_emu_rvv["get"]}],
    #fix : terrible hacky solution bc mipp doesn't want me to use % characters....

}