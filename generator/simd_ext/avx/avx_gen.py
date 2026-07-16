#!/usr/bin/env python3

from jinja2 import Template, StrictUndefined
import json
import copy

from tools import *
from registry import *
avx_isa, avx_native_implems, avx_emu_implems = load_isa_config("avx")
sse_isa, _, _ = load_isa_config("sse")
from c_generator import *


from include_gen import IncludeManager


def avx_gen(include_manager):
    for iemu in avx_emu_implems:
        for sub_iemu in avx_emu_implems[iemu]:
            if "type" not in sub_iemu:
                sub_iemu["type"] = "emulated"
    # implementation C
    file_common = include_manager.get_fd(avx_isa["name"], "common")
    if file_common is None:
        print("Panic: common.h file descriptor not found for AVX.")
        exit(-1)

    tpl_header_avx = """#ifndef MY_INTRINSICS_PLUS_PLUS_IMPL_GEN_AVX_H_
#define MY_INTRINSICS_PLUS_PLUS_IMPL_GEN_AVX_H_
#include <immintrin.h>
#include <simd_ext/sse/sse_common.h> // ldiv 2 support"""
    j2_template = Template(tpl_header_avx, undefined=StrictUndefined)
    print(j2_template.render(), file=file_common)

    gen_c_defines(avx_isa, file_common)
    gen_c_structures(avx_isa, file_common)
    
    tpl_footer_avx = """#endif /* MY_INTRINSICS_PLUS_PLUS_IMPL_GEN_AVX_H_ */"""
    j2_template = Template(tpl_footer_avx, undefined=StrictUndefined)
    print(j2_template.render(), file=file_common)

    copy_interfaces = copy.deepcopy(interfaces)
    gen_c_functions(avx_isa, include_manager, copy_interfaces, avx_native_implems)
    gen_c_functions(avx_isa, include_manager, copy_interfaces, avx_emu_implems)
    gen_c_generic_functions(avx_isa, include_manager, copy_interfaces, implems_generic_emu) 
 
    gen_c_functions(avx_isa, include_manager, copy_interfaces, implems_mask_generic_emu)
 
    gen_c_missing_functions(avx_isa, include_manager, copy_interfaces)
    gen_c_lmul(avx_isa, include_manager, copy_interfaces)
    gen_c_ldiv(avx_isa, sse_isa, include_manager, copy_interfaces)


    include_manager.resolve_all_dependencies(avx_isa["name"], copy_interfaces)
    include_manager.create_glue_file(avx_isa["name"], "../include/avx/mipp_impl_avx_gen.h")
    include_manager.close_layer_fds(avx_isa["name"])


