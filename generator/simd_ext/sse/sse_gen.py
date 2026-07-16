#!/usr/bin/env python3
from jinja2 import Template, StrictUndefined
import json

from tools import *
from registry import *
sse_isa, sse_native_implems, sse_emu_implems = load_isa_config("sse")
from c_generator import *


from include_gen import IncludeManager


def sse_gen(include_manager):
    for iemu in sse_emu_implems:
        for sub_iemu in sse_emu_implems[iemu]:
            if "type" not in sub_iemu:
                sub_iemu["type"] = "emulated"

    file_common = include_manager.get_fd(sse_isa["name"], "common")
    if file_common is None:
        print("Panic: common.h file descriptor not found for SSE.")
        exit(-1)

    tpl_header_sse = """#ifndef MY_INTRINSICS_PLUS_PLUS_IMPL_GEN_SSE_H_
#define MY_INTRINSICS_PLUS_PLUS_IMPL_GEN_SSE_H_
#include <immintrin.h>"""
    j2_template = Template(tpl_header_sse, undefined=StrictUndefined)
    print(j2_template.render(), file=file_common)

    gen_c_defines(sse_isa, file_common)
    gen_c_structures(sse_isa, file_common)
    
    tpl_footer_sse = """#endif /* MY_INTRINSICS_PLUS_PLUS_IMPL_GEN_SSE_H_ */"""
    j2_template = Template(tpl_footer_sse, undefined=StrictUndefined)
    print(j2_template.render(), file=file_common)

    copy_interfaces = copy.deepcopy(interfaces)
    gen_c_functions(sse_isa, include_manager, copy_interfaces, sse_native_implems)
    gen_c_functions(sse_isa, include_manager, copy_interfaces, sse_emu_implems)
    gen_c_generic_functions(sse_isa, include_manager, copy_interfaces, implems_generic_emu)
    gen_c_functions(sse_isa, include_manager, copy_interfaces, implems_mask_generic_emu)

    gen_c_missing_functions(sse_isa, include_manager, copy_interfaces)
    gen_c_lmul(sse_isa, include_manager, copy_interfaces)

    
    include_manager.resolve_all_dependencies(sse_isa["name"], copy_interfaces)
    include_manager.create_glue_file(sse_isa["name"], "../include/sse/mipp_impl_sse_gen.h")
    include_manager.close_layer_fds(sse_isa["name"])
