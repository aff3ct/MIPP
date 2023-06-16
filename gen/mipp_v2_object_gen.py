from jinja2 import Template, StrictUndefined
import json
import re

from tools import *
file = open("mipp_object_v2_AVX512_gen.hpp", "w")

tpl_header_cpp = """#ifndef MY_INTRINSICS_PLUS_PLUS_OBJECT_HPP_
#define MY_INTRINSICS_PLUS_PLUS_OBJECT_HPP_

#include "mipp_v2.hpp"

namespace mipp
{"""

j2_template = Template(tpl_header_cpp, undefined=StrictUndefined)
print(j2_template.render(), file=file)

operators = {

    ('+=', 'add'),
    ('+', 'add'),
    ('-=', 'sub'),
    ('-', 'sub'),
    ('*=', 'mul'),
    ('*', 'mul'),
    ('/=', 'div'),
    ('/', 'div'),
    ('~', 'notb'),
    ('^=', 'xorb'),
    ('^', 'xorb'),
    ('|=', 'orb'),
    ('|', 'orb'),
    ('&=', 'andb'),
    ('&', 'andb'),
    ('==', 'cmpeq'),
    ('!=', 'cmpneq'),
    ('<', 'cmplt'),
    ('<=', 'cmple'),
    ('>', 'cmpgt'),
    ('>=', 'cmpge'),
}
template = """
inline rvm_type<{{ datatype.cstd }}>& operator{op} (const rvm_type<{{ datatype.cstd }}>& v) {{ r = this->{func}(v).r; return *this;} }}
inline rvm_type<{{ datatype.cstd }}> operator{op} (const rvm_type<{{ datatype.cstd }}>& v) const const {{ return this->{func}(v);} }}
"""
j3_template = Template(template, undefined=StrictUndefined)

for op, func in operators:
    print(j3_template.render(op=operators[op], func=operators[func].upper()), file=file)


tpl_footer_cpp = """}

#endif /* MY_INTRINSICS_PLUS_PLUS_OBJECT_HPP_ */"""
j2_template = Template(tpl_footer_cpp, undefined=StrictUndefined)
print(j2_template.render(), file=file)

file.close()
