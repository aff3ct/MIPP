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

def gen_func_obj(isa,file, funcs):
	template = """
template <typename T> inline Rvd<T> {{func_name}}() const { return Rvd<T>(this->r);         }"""
	j2_template = Template(template, undefined=StrictUndefined)
	for f in funcs:
		for dt in funcs[f]["datatypes"]:
			if len(dt.split(',')) <= 1:
				dt_par = dt.split(',')[0]
				dt_ret = dt.split(',')[0]
			else:
				dt_par = dt.split(',')[0]
				dt_ret = dt.split(',')[1]
				dtk = dt_par + "," + dt_ret
			dt_key = dt_par + "," + dt_ret
			
			if len(dt.split(',')) <= 1:
				#cast
				c_func_name  = build_func_name_short_object(isa, dt_par, f, False);
				#print(j2_template.render(func_name=c_func_name), file=file)
				
			else:
				dt_par = dt.split(',')[0]
				dt_ret = dt.split(',')[1]
				#other_functions
				c_func_name = build_func_name_object(isa,dt_par, dt_ret, f);

			for lmul in [1]:
				print("inline "+ build_proto_object(funcs[f]["proto"], dt_par, dt_ret,lmul, c_func_name, lmul, False, True ) +";", file=file)
				#print(j2_template.render(func_name=c_func_name), file=file)
		


def gen_cpp_operators(file):
	template = """
inline Rvd<T,LMUL>	{{op}}	(const Rvd<T,LMUL>& rvd)								 	{ return {{op}}(r, rvd.r);}
inline Rvd<T,LMUL>&	operator{{option}}(const Rvd<T,LMUL>& rvd) 								{  r = this->{{op}}(rvd).r; return *this; }
inline Rvd<T,LMUL>	operator{{operation}}(const Rvd<T,LMUL>& rvd) const 						{ return this->{{op}}(rvd);}
"""

	j2_template = Template(template, undefined=StrictUndefined)
	for op in operators:
		print(j2_template.render(option=operators[op]["option"],op=op, operation=operators[op]["operation"]), file=file)

	tpl_end_class_rvd = """};
"""
	rvd_end = Template(tpl_end_class_rvd, undefined=StrictUndefined)
	print(rvd_end.render(), file=file)

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
inline Rvm<T,LMUL>  {{op}}(const Rvm<T,LMUL>& rvm)             						{ return {{op}}(m, rvm.m);}
inline Rvm<T,LMUL>& operator{{option}}(const Rvm<T,LMUL>& rvm) 								{ m = this->{{op}}(rvm).m; return *this; }
inline Rvm<T,LMUL>  operator{{operation}}(const Rvm<T,LMUL>& rvm) const 						{ return this->{{op}}(rvm);}
""" 
	"""inline Rvm<T,LMUL> operator{{op}} (Rvm<T,LMUL> rvm) const { return this->{{func}} (rvm);}
	"""
	
	j3_template = Template(template_msk, undefined=StrictUndefined)
	for op in operators_msk:
		print(j3_template.render(option=operators[op]["option"],op=op, operation=operators[op]["operation"]), file=file)

	tpl_MIPP_NO_INTRINSICS="""
#ifndef MIPP_NO_INTRINSICS
	inline bool operator[](const size_t index) const { return mipp::get<N>(this->, index); }
#else
	inline bool operator[](const size_t index) const { return m; }
#endif
};"""
	j3_template = Template(tpl_MIPP_NO_INTRINSICS, undefined=StrictUndefined)
	print(j3_template.render(), file=file)





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
inline Rvd<T,LMUL>	notb	(const Rvd<T,LMUL>& rvd)								{ return notb(r, rvd.r);}
inline Rvd<T,LMUL>	operator~() const 					                            { return this->notb();}

"""
j2_template = Template(tpl_header_cpp, undefined=StrictUndefined)
print(j2_template.render(), file=file)

gen_cpp_operators(file)
#gen_func_obj(isa_avx,file, mipp_funcs)


tpl_footer_cpp = """}

#endif /* MY_INTRINSICS_PLUS_PLUS_OBJECT_HPP_ */"""
j2_template = Template(tpl_footer_cpp, undefined=StrictUndefined)
print(j2_template.render(), file=file)

file.close()
