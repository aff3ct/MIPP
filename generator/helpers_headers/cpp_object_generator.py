from jinja2 import Template, StrictUndefined
import json
import re

from headers_def import *
from tools import *
from include_gen import IncludeManager

def gen_cpp_reg_operators(file):
	tpl_class_Rvd = """
 
template <typename T, int LMUL>
class Rvm;

template <typename T, int LMUL = 1>
class Rvd
{
public:
	rvd<T, LMUL> r;

	static constexpr int size() {return mipp::N<T, LMUL>(); };

	Rvd() {}
	Rvd(rvd<T, LMUL>  r) : r(r) {}
	Rvd(const T val)     : r(mipp::set1(val)) {}
	Rvd(const T *data)   : r(mipp::load(data)){}
	~Rvd() {}
	
	inline void set(const T vals[mipp::N<T, LMUL>()])       { r = mipp::set(vals);       }
	inline void set0(                  )       { r = mipp::set0<T>();       }
	inline void set1(const T val    )       { r = mipp::set1(val);       }
    inline Rvd<T,LMUL>	notb	(const Rvd<T,LMUL> rvd)	const                           { return mipp::notb(r, rvd.r);}
    inline Rvd<T,LMUL>	operator~() const 					                            { return this->notb();}
    inline void	load(const T* ptr) const 					                            { return mipp::load(ptr);}
"""
	template_reg = Template(tpl_class_Rvd, undefined=StrictUndefined)
	print(template_reg.render(), file=file)
	operator_reg_out = operators_arithm | operators_binary
	for f in mipp_funcs:
		if f in operator_reg_out:
			operator= operator_reg_out[f]
			template = """
	inline Rvd<T,LMUL>	{{op}}	          (const Rvd<T,LMUL> rvd) const                      { return mipp::{{op}}(r, rvd.r);}
	inline Rvd<T,LMUL>&	operator {{option}}    (const Rvd<T,LMUL>& rvd) 									{  r = this->{{op}}(rvd).r; return *this; }
	inline Rvd<T,LMUL>	operator {{operation}}     (const Rvd<T,LMUL> rvd) const 							{ return this->{{op}}(rvd);}
"""
			j2_template = Template(template, undefined=StrictUndefined)
			print(j2_template.render(option=operator["option"], op=f, operation=operator["operation"]), file=file)
			
		if f in operators_order:
			operator= operators_order[f]
			template_order = """
	inline Rvm<T,LMUL>	{{op}}	          (const Rvd<T,LMUL> rvd) const                      { return mipp::{{op}}(r, rvd.r);}
	inline Rvm<T,LMUL>	operator {{operation}}     (const Rvd<T,LMUL> rvd) const 							{ return this->{{op}}(rvd);}
"""
			j2_template_order = Template(template_order, undefined=StrictUndefined)
			print(j2_template_order.render(option=operator["option"], op=f, operation=operator["operation"]), file=file)

	tpl_MIPP_NO_INTRINSICS="""
	inline T operator[](const size_t index) const { return mipp::get(this->r, index); }

};"""
	j3_template = Template(tpl_MIPP_NO_INTRINSICS, undefined=StrictUndefined)
	print(j3_template.render(), file=file)
	
	# operators with mask 
def gen_cpp_msk_operators(file):
	print("// ------------------------------------------------------------------------------------------------------ operators (Msk) ",file=file)

	tpl_class_Rvm = """template <typename T, int LMUL = 1>
class Rvm
{

public:
	rvm<T, LMUL>  m;

	static constexpr int size() {return mipp::N<T, LMUL>(); };

	Rvm() {}
	Rvm(rvm<T, LMUL>  m) : m(m) {}
    Rvm(const int32_t vals[mipp::N<T, LMUL>()]) : m(mipp::set_k<T>(vals)) {}
    inline Rvd<T,LMUL> toReg() const                              { return Rvd<T,LMUL>(mipp::toreg(this->m)); }
    inline void set_k(const int32_t vals[mipp::N<T, LMUL>()])     { m = mipp::set_k<T>(vals); }
	inline void set0_k()                                          { m = mipp::set0_k<T>(); }
	inline void set1_k(const int32_t val)                         { m = mipp::set1_k<T>(val); }
	inline int32_t get(const size_t index) const                  { return mipp::get(m, index); }
"""
	template = Template(tpl_class_Rvm, undefined=StrictUndefined)
	print(template.render(), file=file)

	template_msk="""
    inline Rvm<T,LMUL>  {{op}}(const Rvm<T,LMUL>  rvm) const                 { return mipp::{{op}}(m, rvm.m);}
    inline Rvm<T,LMUL>& operator{{option}}(const Rvm<T,LMUL>& rvm) 			 { m = this->{{op}}(rvm).m; return *this; }
    inline Rvm<T,LMUL>  operator{{operation}}(const Rvm<T,LMUL>  rvm) const  { return this->{{op}}(rvm);}
""" 
	
	j4_template = Template(template_msk, undefined=StrictUndefined)
	operators = operators_order | operators_binary
	for op in operators:
		print(j4_template.render(option=operators[op]["option"],op=op, operation=operators[op]["operation"]), file=file)

	tpl_MIPP_NO_INTRINSICS="""
	inline T operator[](const size_t index) const { return mipp::get(this->m, index); }
};"""
	j5_template = Template(tpl_MIPP_NO_INTRINSICS, undefined=StrictUndefined)
	print(j5_template.render(), file=file)





""" -----------------------------------------------------------------------------------------------------"""

def generate_cpp_object(include_manager=None):
	
	file = open("../include/mipp_obj.hpp", "w")
	
	tpl_header_cpp = """#ifndef MY_INTRINSICS_PLUS_PLUS_OBJECT_HPP_
#define MY_INTRINSICS_PLUS_PLUS_OBJECT_HPP_
	#include <mipp.hpp>	

	namespace mipp
	{
	"""
	
	j2_template = Template(tpl_header_cpp, undefined=StrictUndefined)
	print(j2_template.render(), file=file)
	
	gen_cpp_reg_operators(file)
	gen_cpp_msk_operators(file)
	
	tpl_footer_cpp = """}
	
#endif /* MY_INTRINSICS_PLUS_PLUS_OBJECT_HPP_ */"""

	j2_template = Template(tpl_footer_cpp, undefined=StrictUndefined)
	print(j2_template.render(), file=file)
	
	file.close()
