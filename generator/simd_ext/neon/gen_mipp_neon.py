#!/usr/bin/env python3
from jinja2 import Template, StrictUndefined
import json

from tools import *
from headers_def import *
from implem_neon import *
from implem_emu_neon import *
from generic_emu import *
from c_generator import *
from include_gen import IncludeManager


def gen_mipp_neon(include_manager):
    for iemu in implems_emu_neon:
        for sub_iemu in implems_emu_neon[iemu]:
            if "type" not in sub_iemu:
                sub_iemu["type"] = "emulated"

    file_common = include_manager.get_fd(isa_neon["name"], "common")


    tpl_header_neon = """#ifndef MY_INTRINSICS_PLUS_PLUS_IMPL_GEN_NEON_H_
#define MY_INTRINSICS_PLUS_PLUS_IMPL_GEN_NEON_H_
#include <arm_neon.h>"""
    j2_template = Template(tpl_header_neon, undefined=StrictUndefined)
    print(j2_template.render(), file=file_common)

    gen_c_defines(isa_neon, file_common)
    gen_c_structures(isa_neon, file_common)
    
    tpl_footer_neon = """#endif /* MY_INTRINSICS_PLUS_PLUS_IMPL_GEN_NEON_H_ */"""
    j2_template = Template(tpl_footer_neon, undefined=StrictUndefined)
    print(j2_template.render(), file=file_common)
    
    print("Generate NEON")
    copy_mipp_funcs = copy.deepcopy(mipp_funcs)
    gen_c_functions(isa_neon, include_manager, copy_mipp_funcs, implems_neon)
    gen_c_functions(isa_neon, include_manager, copy_mipp_funcs, implems_emu_neon)
    
    gen_c_functions(isa_neon, include_manager, copy_mipp_funcs, implems_mask_generic_emu)

    gen_c_missing_functions(isa_neon, include_manager, copy_mipp_funcs)
    gen_c_lmul(isa_neon, include_manager, copy_mipp_funcs)


    include_manager.resolve_all_dependencies(isa_neon["name"], copy_mipp_funcs)
    include_manager.create_glue_file(isa_neon["name"], "../include/neon/mipp_impl_neon_gen.h")
    include_manager.close_layer_fds(isa_neon["name"])