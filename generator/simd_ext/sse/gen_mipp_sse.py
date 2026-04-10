#!/usr/bin/env python3
from jinja2 import Template, StrictUndefined
import json

from tools import *
from headers_def import *
from implem_sse import *
from implem_emu_sse import *
from c_generator import *
from generic_emu import *


def gen_mipp_sse():
	for iemu in implems_emu_sse:
		for sub_iemu in implems_emu_sse[iemu]:
			if "type" not in sub_iemu:
				sub_iemu["type"] = "emulated"

	file = open("../include/sse/mipp_impl_sse_gen.h", "w")

	tpl_header_sse = """#ifndef MY_INTRINSICS_PLUS_PLUS_IMPL_GEN_SSE_H_
#define MY_INTRINSICS_PLUS_PLUS_IMPL_GEN_SSE_H_
#include <immintrin.h>"""
	j2_template = Template(tpl_header_sse, undefined=StrictUndefined)
	print(j2_template.render(), file=file)

	gen_c_defines(isa_sse, file)
	gen_c_structures(isa_sse, file)
	print("Generate SSE")
	copy_mipp_funcs = copy.deepcopy(mipp_funcs)
	gen_c_functions(isa_sse, file, copy_mipp_funcs, implems_sse)
	gen_c_functions(isa_sse, file, copy_mipp_funcs, implems_emu_sse)
	gen_c_generic_functions(isa_sse, file, copy_mipp_funcs, implems_generic_emu)
	gen_c_missing_functions(isa_sse, file, copy_mipp_funcs)

	tpl_footer_sse = """#endif /* MY_INTRINSICS_PLUS_PLUS_IMPL_GEN_SSE_H_ */"""
	j2_template = Template(tpl_footer_sse, undefined=StrictUndefined)
	print(j2_template.render(), file=file)

	file.close()
