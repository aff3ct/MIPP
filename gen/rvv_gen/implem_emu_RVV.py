
from tools import *
tpl_implem_emu_rvv = {
    "loadu" : { "format": "long", "code": """
    static inline vint64m1_t rvv_vle64_u_i64m1(const void *ptr, size_t vl)
    {
        if ((((uintptr_t)ptr) & (8 - 1)) == 0) {
            return __riscv_vle64_v_i64m1((const int64_t*)ptr, vl);
        } else {
            alignas(8) int64_t tmp[vl];
            memcpy(tmp, ptr, vl * sizeof(int64_t));
            return __riscv_vle64_v_i64m1(tmp, vl);
        }
    }  
    """},
    "storeu" : { "format": "long", "code": """
                """ },
}#NOT DONE!!!!

implems_emu_rvv = {
    #"loadu" : [{"instr_name" : "loadu", "datatypes": all_datatypes, "template": tpl_implem_emu_rvv["loadu"]}],
    #"storeu" : [{"instr_name" : "storeu", "datatypes": all_datatypes, "template": tpl_implem_emu_rvv["storeu"]}],
}