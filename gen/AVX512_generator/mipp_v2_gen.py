from jinja2 import Template, StrictUndefined
import json

file = open("mipp_v2_gen.h", "w")

tpl_header_interface = """#ifndef MY_INTRINSICS_PLUS_PLUS__H_
#define MY_INTRINSICS_PLUS_PLUS_H_
#include "mipp_v2.h" """

j2_template = Template(tpl_header_interface, undefined=StrictUndefined)
print(j2_template.render(), file=file)

data_types = {
    'float64_t': 'float64',
    'float32_t': 'float32',
    'int64_t': 'int64',
    'int32_t': 'int32',
    'int16_t': 'int16',
    'int8_t': 'int8',
    'uint64_t': 'uint64',
    'uint32_t': 'uint32',
    'uint16_t': 'uint16',
    'uint8_t': 'uint8'
}
functions = []

for data_type, dtype in data_types.items():
    for m in [1, 2, 4, 8]:
        function_tmpl = f"void storeu({data_type} *mem_addr, const rvd<{dtype},{m}> rvd)"
        function_call = f"mipp_storeu_{dtype}_m{m}(mem_addr, rvd)"
        function_def  = f"{function_tmpl} {{ {function_call}; }}"
        functions.append(function_def)

gen_func = '\n'.join(functions)

print(gen_func,file=file)

tpl_footer_avx = """#endif /* MY_INTRINSICS_PLUS_PLUS_H_*/"""
j2_template = Template(tpl_footer_avx, undefined=StrictUndefined)
print(j2_template.render(), file=file)

file.close()
