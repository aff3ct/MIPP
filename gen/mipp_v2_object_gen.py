from jinja2 import Template, StrictUndefined
import json
import re

from avx_gen.implem_AVX import *
from avx_gen.implem_emu_AVX import *
from avx512_gen.implem_AVX512 import *
from avx512_gen.implem_emu_AVX512 import *
from avx_gen.headers_def_AVX import *
from avx512_gen.headers_def_AVX512 import *
from c_generator import *
from cpp_generator import *
from tools import *


def gen_cpp_operators(file):
	template = """
inline Rvd<T,LMUL>	{{op}}	          (const Rvd<T,LMUL> rvd)								   const{ return mipp::{{op}}(r, rvd.r);}
inline Rvd<T,LMUL>&	operator{{option}}    (const Rvd<T,LMUL>& rvd) 									{  r = this->{{op}}(rvd).r; return *this; }
inline Rvd<T,LMUL>	operator{{operation}}     (const Rvd<T,LMUL> rvd) const 							{ return this->{{op}}(rvd);}
"""

	j2_template = Template(template, undefined=StrictUndefined)
	for op in operators:
		print(j2_template.render(option=operators[op]["option"],op=op, operation=operators[op]["operation"]), file=file)

	tpl_MIPP_NO_INTRINSICS="""
inline T operator[](const size_t index) const { return mipp::get(this->r, index); }
};"""
	j3_template = Template(tpl_MIPP_NO_INTRINSICS, undefined=StrictUndefined)
	print(j3_template.render(), file=file)


	# operators with mask 
	print("// ------------------------------------------------------------------------------------------------------ operators (Msk) ",file=file)

	tpl_class_Rvm = """template <typename T, int LMUL = 1>
class Rvm
{

public:
	rvm<T, LMUL>  m;

	static constexpr int size() {return mipp::N<T, LMUL>(); };

	Rvm() {}
	Rvm(rvm<T, LMUL>  m) : m(m) {}
"""
	template = Template(tpl_class_Rvm, undefined=StrictUndefined)
	print(template.render(), file=file)

	template_msk="""
inline Rvm<T,LMUL>  {{op}}(const Rvm<T,LMUL>  rvm)             						const{ return mipp::{{op}}(m, rvm.m);}
inline Rvm<T,LMUL>& operator{{option}}(const Rvm<T,LMUL>& rvm) 								{ m = this->{{op}}(rvm).m; return *this; }
inline Rvm<T,LMUL>  operator{{operation}}(const Rvm<T,LMUL>  rvm) const 						{ return this->{{op}}(rvm);}
""" 
	"""inline Rvm<T,LMUL> operator{{op}} (Rvm<T,LMUL> rvm) const { return this->{{func}} (rvm);}
	"""
	
	j4_template = Template(template_msk, undefined=StrictUndefined)
	for op in operators_msk:
		print(j4_template.render(option=operators[op]["option"],op=op, operation=operators[op]["operation"]), file=file)

	tpl_MIPP_NO_INTRINSICS="""
	inline T operator[](const size_t index) const { return mipp::get(this->m, index); }
};"""
	j5_template = Template(tpl_MIPP_NO_INTRINSICS, undefined=StrictUndefined)
	print(j5_template.render(), file=file)





""" -----------------------------------------------------------------------------------------------------"""

file = open("../include/mipp_operator_v2_gen.hpp", "w")

tpl_header_cpp = """#ifndef MY_INTRINSICS_PLUS_PLUS_OBJECT_HPP_
#define MY_INTRINSICS_PLUS_PLUS_OBJECT_HPP_

namespace mipp
{

template <typename T, int LMUL = 1>
class Rvd
{
public:
	rvd<T, LMUL> r;

	static constexpr int size() {return mipp::N<T, LMUL>(); };

	Rvd() {}
	Rvd(rvd<T, LMUL>  r) : r(r) {}
inline Rvd<T,LMUL>	notb	(const Rvd<T,LMUL> rvd)								const{ return mipp::notb(r, rvd.r);}
inline Rvd<T,LMUL>	operator~() const 					                            { return this->notb();}

"""
j2_template = Template(tpl_header_cpp, undefined=StrictUndefined)
print(j2_template.render(), file=file)

gen_cpp_operators(file)


tpl_footer_cpp = """}

#endif /* MY_INTRINSICS_PLUS_PLUS_OBJECT_HPP_ */"""
j2_template = Template(tpl_footer_cpp, undefined=StrictUndefined)
print(j2_template.render(), file=file)

file.close()
