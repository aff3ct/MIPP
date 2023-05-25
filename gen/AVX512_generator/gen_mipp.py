#!/usr/bin/env python3

# ce fichier genère : mipp_v2_impl_AVX512_gen.h , mipp_v2_interface_gen.h , mipp_v2_gen.hpp
from jinja2 import Template, StrictUndefined
import json

from tools import *
from headers_def import *
from implem_AVX512 import *
from implem_emu_AVX512 import *
from c_generator import *
from ci_generator import *
from cpp_generator import *

for iemu in implems_emu512:
	for sub_iemu in implems_emu512[iemu]:
		if "type" not in sub_iemu:
			sub_iemu["type"] = "emulated"

file = open("../../include/avx512/mipp_v2_impl_AVX512_gen.h", "w")

tpl_header_avx512 = """#ifndef MY_INTRINSICS_PLUS_PLUS_IMPL_GEN_AVX512_H_
#define MY_INTRINSICS_PLUS_PLUS_IMPL_AVX512_H_
#include "mipp_v2_avx512.h"
#include <immintrin.h>"""
j2_template = Template(tpl_header_avx512, undefined=StrictUndefined)
print(j2_template.render(), file=file)

gen_c_defines(isa_avx512, file)
gen_c_structures(isa_avx512, file)

gen_c_functions(isa_avx512, file, mipp_funcs, implems_avx512)
gen_c_functions(isa_avx512, file, mipp_funcs, implems_emu512)
gen_c_missing_functions(isa_avx512, file, mipp_funcs)

#dump_dict_json(mipp_funcs, "test.json")

tpl_footer_avx512 = """#endif /* MY_INTRINSICS_PLUS_PLUS_IMPL_GEN_AVX512_H_ */"""
j2_template = Template(tpl_footer_avx512, undefined=StrictUndefined)
print(j2_template.render(), file=file)

file.close()

file = open("../../include/avx512/mipp_v2_interface_avx512_gen.h", "w")

tpl_header_interface = """#ifndef MY_INTRINSICS_PLUS_PLUS_INTERFACE_H_
#define MY_INTRINSICS_PLUS_PLUS_INTERFACE_H_
#include "mipp_v2_avx512.h" """
j2_template = Template(tpl_header_interface, undefined=StrictUndefined)
print(j2_template.render(), file=file)

gen_ci_defines([isa_avx512], file)
gen_ci_structures([isa_avx512], file)

gen_ci_functions([isa_avx512], file, mipp_funcs)
# gen_ci_functions(isa_avx512, file, mipp_funcs, implems_emu512)
# gen_ci_missing_functions(isa_avx512, file, mipp_funcs)

tpl_footer_interface = """#endif /* MY_INTRINSICS_PLUS_PLUS_INTERFACE_H_ */"""
j2_template = Template(tpl_footer_interface, undefined=StrictUndefined)
print(j2_template.render(), file=file)

file.close()

file = open("../../include/avx512/mipp_v2_avx512_gen.hpp", "w")

tpl_header_cpp = """#ifndef MY_INTRINSICS_PLUS_PLUS_HPP_
#define MY_INTRINSICS_PLUS_PLUS_HPP_

#include "mipp_v2_avx512.h"

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
