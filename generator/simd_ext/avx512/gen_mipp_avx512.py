#!/usr/bin/env python3

from jinja2 import Template, StrictUndefined
import json


from tools import *
from headers_def import *
from implem_avx512 import *
from implem_emu_avx512 import *
from generic_emu import *
from c_generator import *

from include_gen import IncludeManager

def gen_mipp_avx512(include_manager):
    for iemu in implems_emu_avx512:
        for sub_iemu in implems_emu_avx512[iemu]:
            if "type" not in sub_iemu:
                sub_iemu["type"] = "emulated"

    # implementation C
    
    file_common = include_manager.get_fd(isa_avx512["name"], "common")
     
    tpl_header_avx = """#ifndef MY_INTRINSICS_PLUS_PLUS_IMPL_GEN_AVX512_H_
#define MY_INTRINSICS_PLUS_PLUS_IMPL_GEN_AVX512_H_
#include <immintrin.h>"""
    j2_template = Template(tpl_header_avx, undefined=StrictUndefined)
    print(j2_template.render(), file=file_common)
    gen_c_defines(isa_avx512, file_common)
    gen_c_structures(isa_avx512, file_common)
 
    tpl_footer_avx = """#endif /* MY_INTRINSICS_PLUS_PLUS_IMPL_GEN_AVX512_H_ */"""
    j2_template = Template(tpl_footer_avx, undefined=StrictUndefined)
    print(j2_template.render(), file=file_common)
 
    print("Generate AVX512")
    copy_mipp_funcs = copy.deepcopy(mipp_funcs)
    gen_c_functions(isa_avx512, include_manager, copy_mipp_funcs, implems_avx512)
    gen_c_functions(isa_avx512, include_manager, copy_mipp_funcs, implems_emu_avx512)
 
    gen_c_functions(isa_avx512, include_manager, copy_mipp_funcs, implems_mask_generic_emu)
    
    gen_c_missing_functions(isa_avx512, include_manager, copy_mipp_funcs)
    gen_c_lmul(isa_avx512, include_manager, copy_mipp_funcs)


 
    include_manager.resolve_all_dependencies(isa_avx512["name"], copy_mipp_funcs)
    include_manager.create_glue_file(isa_avx512["name"], "../include/avx512/mipp_impl_avx512_gen.h")
    include_manager.close_layer_fds(isa_avx512["name"])

