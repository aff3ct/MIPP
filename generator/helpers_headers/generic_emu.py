
from headers_def import *
from tools import *
from c_generator import *


################################# GENERIC FUNCTIONS ############################################

tpl_generic_emu = {

  "div_scalar" : { "format" :"long", "code" :"""
	{{isa_dt_par.to_ptr}} ptr1[%N<tp>%];
	{{isa_dt_par.to_ptr}} ptr2[%N<tp>%];
	%storeu<tp>%(ptr1, r0);
	for(unsigned i = 0; i < %N<tp>%; i++)
		ptr2[i] = ptr1[i] / 2;
	return %loadu<tp>%(ptr2);
   """},
  
  "div2" : { "format" :"long", "code" :"""
			%r<tp>% tmp = %set1<tp>%(2);
			%r<tp>% res = %div<tp>%(r0, tmp);
			return res;
	"""},
  "div2_scalar" : { "format" :"long", "code" :"""
			%v<tp>% ptr[%N<tp>%];
			%store<tp>%(ptr, r0);        
			for(unsigned i = 0; i < %N<tp>%; i++)
				ptr[i] /= 2;
			return %load<tp>%(ptr);
	"""},
  
	"set1_scalar" : { "format" :"long", "code" :"""
			%v<tp>% ptr[%N<tp>%];
			for(unsigned i = 0; i < %N<tp>%; i++)
				ptr[i] = v0;
			return %load<tp>%(ptr);
	"""},
	
	"fmadd" : { "format" :"long", "code" :"""
			%r<tp>% res = %mul<tp>%(r0, r1);
			res = %add<tp>%(res, r2);
			return res;
	"""},
}

implems_generic_emu = {
	
	"set1" : [
		{ "instr_name": "set1",  "datatypes" : all_datatypes, "template" : tpl_generic_emu["set1_scalar"]}],
	
	"div" : [
		{ "instr_name": "div",  "datatypes" : all_float, "template" : tpl_generic_emu["div_scalar"]}],
	
	"div2" : [
		{ "instr_name": "div2",  "datatypes" : all_float, "template" : tpl_generic_emu["div2"]},
		{ "instr_name": "div2",  "datatypes" : all_float, "template" : tpl_generic_emu["div2_scalar"]}],
	
	"fmadd" : [
		{ "instr_name": "fmadd",  "datatypes" : all_float, "template" : tpl_generic_emu["fmadd"]}],
}

#for functions with conditition, we want a way to generate the global not of the condition to be used 
#let's we have function :
#if defined(__SSE2__) && defined(__AVX__)
#void my_func() {
#}
#we want to generate the global condition for the generic function to be
#if !(defined(__SSE2__) && defined(__AVX__))
#void my_func() {
#}

################################# MASKED FUNCTION ############################################

SNIPPET_END_MSK = """
	%r<tp>% res = %blend<tp>%(op, r0, m0);
	return res;
"""       

SNIPPET_END_MSKZ = """
	%r<tp>% tmp = %toreg<tp>%(m0);
	%r<tp>% res = %andb<tp>%(op, tmp);
	return res;
"""

SNIPPET_END_MSKS = """
	%r<tp>% res = %blend<tp>%(op, rsrc, m0);
	return res;
"""
	
				
tpl_mask_generic_emu = {
	"ret_reg_2args_reg" : { "format" :"long", "code" :"""
		%r<tp>% op = %{{func_name}}<tp>%(r0, r1);
	"""},
	
	"ret_reg_3args_reg" : { "format" :"long", "code" :"""
		%r<tp>% op = %{{func_name}}<tp>%( r0, r1, r2);
	"""},
	
	"ret_reg_1arg_reg" : { "format" :"long", "code" :"""
		%r<tp>% op = %{{func_name}}<tp>%(r0);
	"""},
	
	"load" : { "format" :"long", "code" :"""
		%r<tp>% op = %load<tp>%(m0,p0);
	"""},
	
	"set" : { "format" :"long", "code" :"""
		%r<tp>% op = %set<tp>%(vals);
	"""},
	
	"set1" : { "format" :"long", "code" :"""
		%r<tp>% op = %set1<tp>%(v0);
	"""},
	
		
	"ret_msk_2args_reg" : { "format" :"long", "code" :"""
		%m<tp>% op = %{{func_name}}<tp>%(r0, r1);
	"""},
	
	#will need a custom thing
	"store" : { "format" :"long", "code" :"""
		exit(-1); //huuuuh idk
	"""},
	

	"reductions" : { "format" :"long", "code" :"""
		exit(-1); //huuuuh idk
	"""},
   
}

implems_mask_generic_emu = {
	"add" : [
		#add SNIPPEt_END_MSK to the template code
		{ "instr_name": "add",  "datatypes" : all_datatypes, "version" : "mask", "template" : { "format" :"long", "code" : tpl_mask_generic_emu["ret_reg_2args_reg"]["code"] + SNIPPET_END_MSK}},
		{ "instr_name": "add",  "datatypes" : all_datatypes, "version" : "maskz", "template" : { "format" :"long", "code" : tpl_mask_generic_emu["ret_reg_2args_reg"]["code"] + SNIPPET_END_MSKZ}},
		{ "instr_name": "add",  "datatypes" : all_datatypes, "version" : "masks", "template" : { "format" :"long", "code" : tpl_mask_generic_emu["ret_reg_2args_reg"]["code"] + SNIPPET_END_MSKS}},
 	],
}

################################# HORIZONTAL LMUL FUNCTIONS ############################################

tpl_horiz_lmul_generic_emu = {
    "tpl_set" : { "format" :"long", "code" :"""
{% if lmul == 1 %}
	%r<tp>% res = %set<tp>%(vals);
	return res;
{% else %}
	// pass first half of the vector to 
	%r<tp>% res;
	res.r1 = %set<c:tp|b:tp|m:tp/2>%(vals);
	%v<tp>% *ptr = vals + %N<tp>% / 2;
	res.r2 = %set<c:tp|b:tp|m:tp/2>%(ptr);
	return res;
{% endif %}"""},
    
    
    "tpl_get" : { "format" :"long", "code" :"""
{% if lmul == 1 %}
	return %get<tp>%(r0, v0);
{% else %}
	if(v0 < %N<tp>% / 2)
		return %get<c:tp|b:tp|m:tp/2>%(r0.r1, v0);
	else {
		%v<tp>% tmp = v0 - %N<tp>% / 2;
		return %get<c:tp|b:tp|m:tp/2>%(r0.r2, tmp);
	}
{% endif %}"""},
    
    
    "tpl_get_k" : { "format" :"long", "code" :"""
{% if lmul == 1 %}
	return %get_k<tp>%(m0, v0);
{% else %}
	if(v0 < %N<tp>% / 2)
		return %get_k<c:tp|b:tp|m:tp/2>%(m0.m1, v0);
	else {
		%v<tp>% tmp = v0 - %N<tp>% / 2;
		return %get_k<c:tp|b:tp|m:tp/2>%(m0.m2, tmp);
	}
{% endif %}"""},
    
    
    "tpl_getfirst" : { "format" :"long", "code" :"""
{% if lmul == 1 %}
	return %getfirst<tp>%(r0);
{% else %}
	return %getfirst<c:tp|b:tp|m:tp/2>%(r0.r1);
{% endif %}"""},

}

implems_horiz_lmul_generic_emu = {
    
	"set" : [ 
		{ "instr_name": "set",  "datatypes" : all_datatypes, "version" : "horiz_lmul", "template" : tpl_horiz_lmul_generic_emu["tpl_set"]},
	],
	"get" : [ 
     	{ "instr_name": "get",  "datatypes" : all_datatypes, "version" : "horiz_lmul", "template" : tpl_horiz_lmul_generic_emu["tpl_get"]},
	],
	"get_k" : [
     	{ "instr_name": "get_k",  "datatypes" : all_datatypes, "version" : "horiz_lmul", "template" : tpl_horiz_lmul_generic_emu["tpl_get_k"]},
	],
	"getfirst" : [
	 	{ "instr_name": "getfirst",  "datatypes" : all_datatypes, "version" : "horiz_lmul", "template" : tpl_horiz_lmul_generic_emu["tpl_getfirst"]},
	],
 
	# "testz" : [],
	# "testz_2" : [],
	# "hadd" : [],
	# "hmul" : [],
	# "hmin" : [],
	# "hmax" : [],
	# "hadd_to_scal" : []
}