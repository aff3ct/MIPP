#!/usr/bin/env python3

from jinja2 import Template, StrictUndefined
import json

from tools import *
from headers_def import *
from implem_AVX import *
from implem_emu import *
from c_generator import *
from ci_generator import *
from cpp_generator import *

for iemu in implems_emu:
	for sub_iemu in implems_emu[iemu]:
		if "type" not in sub_iemu:
			sub_iemu["type"] = "emulated"

file = open("../../include/avx/mipp_v2_impl_AVX_gen.h", "w")

tpl_header_avx = """#ifndef MY_INTRINSICS_PLUS_PLUS_IMPL_GEN_AVX_H_
#define MY_INTRINSICS_PLUS_PLUS_IMPL_AVX_H_
#include "mipp_v2.h"
#include <immintrin.h>"""
j2_template = Template(tpl_header_avx, undefined=StrictUndefined)
print(j2_template.render(), file=file)

gen_c_defines(isa_avx, file)
gen_c_structures(isa_avx, file)

gen_c_functions(isa_avx, file, mipp_funcs, implems_avx)
gen_c_functions(isa_avx, file, mipp_funcs, implems_emu)
gen_c_missing_functions(isa_avx, file, mipp_funcs)

#dump_dict_json(mipp_funcs, "test.json")

tpl_footer_avx = """#endif /* MY_INTRINSICS_PLUS_PLUS_IMPL_GEN_AVX_H_ */"""
j2_template = Template(tpl_footer_avx, undefined=StrictUndefined)
print(j2_template.render(), file=file)

file.close()

file = open("../../include/avx/mipp_v2_interface_gen.h", "w")

tpl_header_interface = """#ifndef MY_INTRINSICS_PLUS_PLUS_INTERFACE_H_
#define MY_INTRINSICS_PLUS_PLUS_INTERFACE_H_
#include "mipp_v2.h" """
j2_template = Template(tpl_header_interface, undefined=StrictUndefined)
print(j2_template.render(), file=file)

gen_ci_defines([isa_avx], file)
gen_ci_structures([isa_avx], file)

gen_ci_functions([isa_avx], file, mipp_funcs)
# gen_ci_functions(isa_avx, file, mipp_funcs, implems_emu)
# gen_ci_missing_functions(isa_avx, file, mipp_funcs)

tpl_footer_interface = """#endif /* MY_INTRINSICS_PLUS_PLUS_INTERFACE_H_ */"""
j2_template = Template(tpl_footer_interface, undefined=StrictUndefined)
print(j2_template.render(), file=file)

file.close()

file = open("../../include/avx/mipp_v2_gen.hpp", "w")

tpl_header_cpp = """#ifndef MY_INTRINSICS_PLUS_PLUS_HPP_
#define MY_INTRINSICS_PLUS_PLUS_HPP_

#include "mipp_v2.h"

namespace mipp
{"""

j2_template = Template(tpl_header_cpp, undefined=StrictUndefined)
print(j2_template.render(), file=file)

gen_cpp_structures(file)
gen_cpp_constexpr_functions(file)
gen_cpp_functions(file, mipp_funcs)

tpl_footer_cpp = """}

#endif /* MY_INTRINSICS_PLUS_PLUS_HPP_ */"""
j2_template = Template(tpl_footer_cpp, undefined=StrictUndefined)
print(j2_template.render(), file=file)

file.close()
