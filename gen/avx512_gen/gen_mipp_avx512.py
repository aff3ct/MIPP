#!/usr/bin/env python3

from jinja2 import Template, StrictUndefined
import json


from tools import *
from headers_def import *
from implem_AVX512 import *
from implem_emu_AVX512 import *
from c_generator import *

def gen_mipp_avx512():
	for iemu in implems_emu_avx512:
		for sub_iemu in implems_emu_avx512[iemu]:
			if "type" not in sub_iemu:
				sub_iemu["type"] = "emulated"

	# implementation C
	
	file = open("../include/avx512/mipp_v2_impl_AVX512_gen.h", "w")
	
	tpl_header_avx = """#ifndef MY_INTRINSICS_PLUS_PLUS_IMPL_GEN_AVX512_H_
#define MY_INTRINSICS_PLUS_PLUS_IMPL_GEN_AVX512_H_
#include <immintrin.h>"""
	j2_template = Template(tpl_header_avx, undefined=StrictUndefined)
	print(j2_template.render(), file=file)
	gen_c_defines(isa_avx512, file)
	gen_c_structures(isa_avx512, file)
	print("Generate AVX512")
	copy_mipp_funcs = copy.deepcopy(mipp_funcs)
	gen_c_functions(isa_avx512, file, copy_mipp_funcs, implems_avx512)
	gen_c_functions(isa_avx512, file, copy_mipp_funcs, implems_emu_avx512)
	gen_c_missing_functions(isa_avx512, file, copy_mipp_funcs)
	
	tpl_footer_avx = """#endif /* MY_INTRINSICS_PLUS_PLUS_IMPL_GEN_AVX512_H_ */"""
	j2_template = Template(tpl_footer_avx, undefined=StrictUndefined)
	print(j2_template.render(), file=file)
	
	file.close()

