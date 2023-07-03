from jinja2 import Template, StrictUndefined
import json
import re
from avx_gen.headers_def_AVX import *
from tools import *



def gen_cpp_operators(file):
	template = """
inline Rvd<{{ datatype.cstd }}>& operator{{op}} (const Rvd<{{ datatype.cstd }}>& rvd) { r = this->{{func}}(rvd).r; return *this; }
inline Rvd<{{ datatype.cstd }}> operator{{op}} (Rvd<{{ datatype.cstd }}>& rvd) const { return this->{{func}}(rvd); }
"""
	j2_template = Template(template, undefined=StrictUndefined)
	for dt in datatypes:
		for op, func in operators.items():
			print(j2_template.render(datatype=datatypes[dt], op=op, func=func), file=file)
	for dt in datatypes:
		for op, func in operators_msk.items():
			print(j2_template.render(datatype=datatypes[dt], op=op, func=func), file=file)
	tpl_end_class_rvd = """}
"""
	rvd_end = Template(tpl_end_class_rvd, undefined=StrictUndefined)
	print(rvd_end.render(), file=file)
# operators with mask 
	print("// ------------------------------------------------------------------------------------------------------ operators (Msk) ",file=file)

	tpl_class_Rvm = """class Rvm
{
public:
	rvm<T, LMUL>  m;

	static constexpr int size() {return mipp::N<T, LMUL>(); };

	Rvm() {}
	Rvm(rvm<T, LMUL>  m) : m(m) {}
"""
	template = Template(tpl_class_Rvm, undefined=StrictUndefined)
	print(template.render(), file=file)

	template_msk= """inline Rvm<N<{{ datatype.cstd }}>()> operator{{op}} (rvm<{{ datatype.cstd }}> rvm) const { return this->{{func}} (rvm);}"""
	j3_template = Template(template_msk, undefined=StrictUndefined)
	for dt in datatypes:
		for op, func in operators_msk.items():
			print(j3_template.render(datatype=datatypes[dt], op=op, func=func), file=file)

	tpl_end_class_rvm = """}
"""
	rvm_end = Template(tpl_end_class_rvm, undefined=StrictUndefined)
	print(rvm_end.render(), file=file)


file = open("../include/mipp_operator_v2_gen.hpp", "w")

tpl_header_cpp = """#ifndef MY_INTRINSICS_PLUS_PLUS_OBJECT_HPP_
#define MY_INTRINSICS_PLUS_PLUS_OPERATORS_HPP_


namespace mipp
{

template <typename T, int LMUL = 1>
class Rvd
{
public:
	rvd<T, LMUL> r;

	static constexpr int size() {return mipp::N<T, LMUL>(); };

	Rvd() {}
	Rvd(rvd<T, LMUL>  r) : r(r) {}"""
j2_template = Template(tpl_header_cpp, undefined=StrictUndefined)
print(j2_template.render(), file=file)
print("// ------------------------------------------------------------------------------------------------------ operators ",file=file)

gen_cpp_operators(file)

tpl_MIPP_NO_INTRINSICS="""#ifndef MIPP_NO_INTRINSICS
	inline bool operator[](const size_t index) const { return mipp::get<N>(this->, index); }
#else
	inline bool operator[](const size_t index) const { return m; }
#endif
};"""
j3_template = Template(tpl_MIPP_NO_INTRINSICS, undefined=StrictUndefined)
print(j3_template.render(), file=file)
tpl_footer_cpp = """}

#endif /* MY_INTRINSICS_PLUS_PLUS_OBJECT_HPP_ */"""
j2_template = Template(tpl_footer_cpp, undefined=StrictUndefined)
print(j2_template.render(), file=file)

file.close()
