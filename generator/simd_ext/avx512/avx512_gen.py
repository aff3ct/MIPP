#!/usr/bin/env python3

from jinja2 import Template, StrictUndefined
import json


from tools import *
from registry import *
avx512_isa, avx512_native_implems, avx512_emu_implems = load_isa_config("avx512")

from c_generator import *

from include_gen import IncludeManager

avx_isa, _, _ = load_isa_config("avx")

def avx512_gen(include_manager):
    for iemu in avx512_emu_implems:
        for sub_iemu in avx512_emu_implems[iemu]:
            if "type" not in sub_iemu:
                sub_iemu["type"] = "emulated"

    # implementation C

    file_common = include_manager.get_fd(avx512_isa["name"], "common")
     
    tpl_header_avx = """#ifndef MY_INTRINSICS_PLUS_PLUS_IMPL_GEN_AVX512_H_
#define MY_INTRINSICS_PLUS_PLUS_IMPL_GEN_AVX512_H_
#include <immintrin.h>
#include <simd_ext/avx/avx_common.h> // ldiv2 support"""
    j2_template = Template(tpl_header_avx, undefined=StrictUndefined)
    print(j2_template.render(), file=file_common)
    gen_c_defines(avx512_isa, file_common)
    gen_c_structures(avx512_isa, file_common)
 
    tpl_footer_avx = """#endif /* MY_INTRINSICS_PLUS_PLUS_IMPL_GEN_AVX512_H_ */"""
    j2_template = Template(tpl_footer_avx, undefined=StrictUndefined)
    print(j2_template.render(), file=file_common)

    copy_interfaces = copy.deepcopy(interfaces)
    gen_c_functions(avx512_isa, include_manager, copy_interfaces, avx512_native_implems)
    gen_c_functions(avx512_isa, include_manager, copy_interfaces, avx512_emu_implems)
    
    gen_c_functions(avx512_isa, include_manager, copy_interfaces, implems_mask_generic_emu)
    
    gen_c_missing_functions(avx512_isa, include_manager, copy_interfaces)
    gen_c_lmul(avx512_isa, include_manager, copy_interfaces)

    gen_c_ldiv(avx512_isa, avx_isa, include_manager, copy_interfaces)

 
    include_manager.resolve_all_dependencies(avx512_isa["name"], copy_interfaces)
    include_manager.create_glue_file(avx512_isa["name"], "../include/avx512/mipp_impl_avx512_gen.h")
    include_manager.close_layer_fds(avx512_isa["name"])

