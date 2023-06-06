#!/usr/bin/env python3

from jinja2 import Template, StrictUndefined
import json

from tools import *
from headers_def import *
from implem_AVX512 import *
from implem_emu_AVX512 import *
from c_generator import *
from ci_generator import *
from cpp_generator import *

for iemu512 in implems_emu512:
	for sub_iemu512 in implems_emu512[iemu512]:
		if "type" not in sub_iemu512:
			sub_iemu512["type"] = "emulated"
file = open("../../include/avx512/mipp_v2_interface_gen.h", "w")

tpl_header_interface = """#ifndef MY_INTRINSICS_PLUS_PLUS_INTERFACE_H_
#define MY_INTRINSICS_PLUS_PLUS_INTERFACE_H_
#include "mipp_v2.h" """

j2_template = Template(tpl_header_interface, undefined=StrictUndefined)
print(j2_template.render(), file=file)

gen_ci_defines([isa_avx512], file)
gen_ci_structures([isa_avx512], file)

gen_ci_functions([isa_avx512], file, mipp_funcs)
# gen_ci_functions(isa_avx, file, mipp_funcs, implems_emu)
# gen_ci_missing_functions(isa_avx, file, mipp_funcs)

tpl_footer_interface = """#endif /* MY_INTRINSICS_PLUS_PLUS_INTERFACE_H_ */"""
j2_template = Template(tpl_footer_interface, undefined=StrictUndefined)
print(j2_template.render(), file=file)

file.close()
