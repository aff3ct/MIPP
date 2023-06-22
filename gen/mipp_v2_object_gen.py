from jinja2 import Template, StrictUndefined
import json
import re

from tools import *
datatypes = {
    float64 : { "name" : float64, "category": cfloat, "n_bits" : 64, "cstd": "float64_t", },
    float32 : { "name" : float32, "category": cfloat, "n_bits" : 32, "cstd": "float32_t", },
      int64 : { "name" :   int64, "category":   cint, "n_bits" : 64, "cstd":   "int64_t", },
      int32 : { "name" :   int32, "category":   cint, "n_bits" : 32, "cstd":   "int32_t", },
      int16 : { "name" :   int16, "category":   cint, "n_bits" : 16, "cstd":   "int16_t", },
       int8 : { "name" :    int8, "category":   cint, "n_bits" :  8, "cstd":    "int8_t", },
     uint64 : { "name" :  uint64, "category":  cuint, "n_bits" : 64, "cstd":  "uint64_t", },
     uint32 : { "name" :  uint32, "category":  cuint, "n_bits" : 32, "cstd":  "uint32_t", },
     uint16 : { "name" :  uint16, "category":  cuint, "n_bits" : 16, "cstd":  "uint16_t", },
      uint8 : { "name" :   uint8, "category":  cuint, "n_bits" :  8, "cstd":   "uint8_t", },
}

operators = {

    "+=": "add",
    "+": "add",
    "-=": "sub",
    "-": "sub",
    "*=": "mul",
    "*": "mul",
    "/=": "div",
    "/": "div",
    "~": "notb",
    "^=": "xorb",
    "^": "xorb",
    "|=": "orb",
    "|": "orb",
    "&=": "andb",
    "&": "andb",
    "==": "cmpeq",
    "!=": "cmpneq",
    "<": "cmplt",
    "<=": "cmple",
    ">": "cmpgt",
    ">=": "cmpge",

}



def gen_cpp_operators(file):
    template = """
inline rvd_type<{{ datatype.cstd }}>& operator{{op}} (const rvd_type<{{ datatype.cstd }}>& v) { r = this->{{func}}(v).r; return *this;}
inline rvd_type<{{ datatype.cstd }}> operator{{op}} (const rvd_type<{{ datatype.cstd }}>& v) const { return this->{{func}}(v);}
"""
    j2_template = Template(template, undefined=StrictUndefined)
    for dt in datatypes:
        for op, func in operators.items():
            print(j2_template.render(datatype=datatypes[dt], op=op, func=func), file=file)


file = open("../include/mipp_object_v2_AVX512_gen.hpp", "w")

tpl_header_cpp = """#ifndef MY_INTRINSICS_PLUS_PLUS_OBJECT_HPP_
#define MY_INTRINSICS_PLUS_PLUS_OBJECT_HPP_

#include "mipp_v2.hpp"

namespace mipp
{

template <typename T, int LMUL = 1>
class Rvd
{
public:
    rvd<T, LMUL> m;

    static constexpr int size() {return mipp::N<T, LMUL>(); };"""
j2_template = Template(tpl_header_cpp, undefined=StrictUndefined)
print(j2_template.render(), file=file)

gen_cpp_operators(file)

tpl_footer_cpp = """}

#endif /* MY_INTRINSICS_PLUS_PLUS_OBJECT_HPP_ */"""
j2_template = Template(tpl_footer_cpp, undefined=StrictUndefined)
print(j2_template.render(), file=file)

file.close()
