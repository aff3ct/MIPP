#!/usr/bin/env python3

from jinja2 import Template, StrictUndefined
import json
import copy

from tools import *
from headers_def import *
from implem_AVX import *
from implem_emu_AVX import *
from c_generator import *
from cpp_generator import *


def gen_mipp_avx():
	for iemu in implems_emu_avx:
		for sub_iemu in implems_emu_avx[iemu]:
			if "type" not in sub_iemu:
				sub_iemu["type"] = "emulated"

	file = open("../include/avx/mipp_v2_impl_AVX_gen.h", "w")

	tpl_header_avx = """#ifndef MY_INTRINSICS_PLUS_PLUS_IMPL_GEN_AVX_H_
#define MY_INTRINSICS_PLUS_PLUS_IMPL_GEN_AVX_H_
#include <immintrin.h>"""
	j2_template = Template(tpl_header_avx, undefined=StrictUndefined)
	print(j2_template.render(), file=file)

	gen_c_defines(isa_avx, file)
	gen_c_structures(isa_avx, file)
	print("Generate AVX")
	my_mipp_funcs = copy.deepcopy(mipp_funcs)
	gen_c_functions(isa_avx, file, my_mipp_funcs, implems_avx)
	gen_c_functions(isa_avx, file, my_mipp_funcs, implems_emu_avx)
	gen_c_missing_functions(isa_avx, file, my_mipp_funcs)

	#dump_dict_json(mipp_funcs, "test.json")

	tpl_footer_avx = """#endif /* MY_INTRINSICS_PLUS_PLUS_IMPL_GEN_AVX_H_ */"""
	j2_template = Template(tpl_footer_avx, undefined=StrictUndefined)
	print(j2_template.render(), file=file)

	file.close()

	file = open("../include/avx/mipp_v2_AVX_gen.hpp", "w")

	tpl_header_cpp = """#ifndef MY_INTRINSICS_PLUS_PLUS_HPP_
#define MY_INTRINSICS_PLUS_PLUS_HPP_

namespace mipp
{"""

	j2_template = Template(tpl_header_cpp, undefined=StrictUndefined)
	print(j2_template.render(), file=file)

	gen_cpp_structures(isa_avx,file)
	gen_cpp_constexpr_functions(isa_avx,file)
	gen_cpp_functions(isa_avx, file, my_mipp_funcs)

	tpl_footer_cpp = """}

#endif /* MY_INTRINSICS_PLUS_PLUS_HPP_ */"""
	j2_template = Template(tpl_footer_cpp, undefined=StrictUndefined)
	print(j2_template.render(), file=file)

	file.close()
