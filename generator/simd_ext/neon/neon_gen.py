#!/usr/bin/env python3
from jinja2 import Template, StrictUndefined
import json

from tools import *
from registry import *
neon_isa, neon_native_implems, neon_emu_implems = load_isa_config("neon")

from c_generator import *
from include_gen import IncludeManager


def neon_gen(include_manager):
    for iemu in neon_emu_implems:
        for sub_iemu in neon_emu_implems[iemu]:
            if "type" not in sub_iemu:
                sub_iemu["type"] = "emulated"

    file_common = include_manager.get_fd(neon_isa["name"], "common")


    tpl_header_neon = """#ifndef MY_INTRINSICS_PLUS_PLUS_IMPL_GEN_NEON_H_
#define MY_INTRINSICS_PLUS_PLUS_IMPL_GEN_NEON_H_
#include <arm_neon.h>"""
    j2_template = Template(tpl_header_neon, undefined=StrictUndefined)
    print(j2_template.render(), file=file_common)

    gen_c_defines(neon_isa, file_common)
    gen_c_structures(neon_isa, file_common)
    
    tpl_footer_neon = """#endif /* MY_INTRINSICS_PLUS_PLUS_IMPL_GEN_NEON_H_ */"""
    j2_template = Template(tpl_footer_neon, undefined=StrictUndefined)
    print(j2_template.render(), file=file_common)
    
    copy_interfaces = copy.deepcopy(interfaces)
    gen_c_functions(neon_isa, include_manager, copy_interfaces, neon_native_implems)
    gen_c_functions(neon_isa, include_manager, copy_interfaces, neon_emu_implems)
    
    gen_c_generic_functions(neon_isa, include_manager, copy_interfaces, implems_generic_emu)
    gen_c_functions(neon_isa, include_manager, copy_interfaces, implems_mask_generic_emu)

    gen_c_missing_functions(neon_isa, include_manager, copy_interfaces)
    gen_c_lmul(neon_isa, include_manager, copy_interfaces)


    include_manager.resolve_all_dependencies(neon_isa["name"], copy_interfaces)
    include_manager.create_glue_file(neon_isa["name"], "../include/neon/mipp_impl_neon_gen.h")
    include_manager.close_layer_fds(neon_isa["name"])