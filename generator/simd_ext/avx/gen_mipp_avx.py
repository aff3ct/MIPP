#!/usr/bin/env python3

from jinja2 import Template, StrictUndefined
import json
import copy

from tools import *
from headers_def import *
isa_avx, implems_avx, implems_emu_avx = load_isa_config("avx")
isa_sse, _, _ = load_isa_config("sse")
from c_generator import *
from generic_emu import *

from include_gen import IncludeManager


def gen_mipp_avx(include_manager):
    for iemu in implems_emu_avx:
        for sub_iemu in implems_emu_avx[iemu]:
            if "type" not in sub_iemu:
                sub_iemu["type"] = "emulated"
    # implementation C
    file_common = include_manager.get_fd(isa_avx["name"], "common")
    if file_common is None:
        print("Panic: common.h file descriptor not found for AVX.")
        exit(-1)

    tpl_header_avx = """#ifndef MY_INTRINSICS_PLUS_PLUS_IMPL_GEN_AVX_H_
#define MY_INTRINSICS_PLUS_PLUS_IMPL_GEN_AVX_H_
#include <immintrin.h>
#include <simd_ext/sse/sse_common.h> // ldiv 2 support"""
    j2_template = Template(tpl_header_avx, undefined=StrictUndefined)
    print(j2_template.render(), file=file_common)

    gen_c_defines(isa_avx, file_common)
    gen_c_structures(isa_avx, file_common)
    
    tpl_footer_avx = """#endif /* MY_INTRINSICS_PLUS_PLUS_IMPL_GEN_AVX_H_ */"""
    j2_template = Template(tpl_footer_avx, undefined=StrictUndefined)
    print(j2_template.render(), file=file_common)

    copy_mipp_funcs = copy.deepcopy(mipp_funcs)
    gen_c_functions(isa_avx, include_manager, copy_mipp_funcs, implems_avx)
    gen_c_functions(isa_avx, include_manager, copy_mipp_funcs, implems_emu_avx)
    gen_c_generic_functions(isa_avx, include_manager, copy_mipp_funcs, implems_generic_emu) 
 
    gen_c_functions(isa_avx, include_manager, copy_mipp_funcs, implems_mask_generic_emu)
 
    gen_c_missing_functions(isa_avx, include_manager, copy_mipp_funcs)
    gen_c_lmul(isa_avx, include_manager, copy_mipp_funcs)
    gen_c_ldiv(isa_avx, isa_sse, include_manager, copy_mipp_funcs)


    include_manager.resolve_all_dependencies(isa_avx["name"], copy_mipp_funcs)
    include_manager.create_glue_file(isa_avx["name"], "../include/avx/mipp_impl_avx_gen.h")
    include_manager.close_layer_fds(isa_avx["name"])


