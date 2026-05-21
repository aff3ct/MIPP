
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

  
  
	"div4" : { "format" :"long", "code" :"""
        %r<tp>% tmp = %set1<tp>%(4);
        %r<tp>% res = %div<tp>%(r0, tmp);
		return res;
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
	
	# This is annoying. Doing it w loads and stores. 
	# >:(
	"blend": { "format" :"long", "code" :"""
           %v<tp>% ptr1[%N<tp>%];
           %v<tp>% ptr2[%N<tp>%];
           %store<tp>%(ptr1, r0);
           %store<tp>%(ptr2, r1);
           for(unsigned i = 0; i < %N<tp>%; i++){
               ptr1[i] = %get_k<tp>%(m0, i) ? ptr1[i] : ptr2[i];
		   }
		   return %load<tp>%(ptr1);
    """},
}

implems_generic_emu = {
	
	"set1" : [
		{ "instr_name": "set1",  "datatypes" : all_datatypes, "template" : tpl_generic_emu["set1_scalar"]}],
	
	"div" : [
		{ "instr_name": "div",  "datatypes" : all_float, "template" : tpl_generic_emu["div_scalar"]}],
	
	"div2" : [
		{ "instr_name": "div2",  "datatypes" : all_float, "template" : tpl_generic_emu["div2"]},
	],
 
	"div4" : [
		{ "instr_name": "div4",  "datatypes" : all_float, "template" : tpl_generic_emu["div4"]},
	],
	
	# "fmadd" : [
	# 	{ "instr_name": "fmadd",  "datatypes" : all_float+[int32], "template" : tpl_generic_emu["fmadd"]}],
 
	"blend" : [
		{ "instr_name": "blend",  "datatypes" : all_datatypes, "template" : tpl_generic_emu["blend"]},
	],
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
	
	"load_msks" : { "format" :"long", "code" :"""
		// we want to guarantee that load doesn't touch the memory of masked out elems
		%v<tp>% buff[%N<tp>%];
  
		for(unsigned i = 0; i < %N<tp>%; i++){
			if(%get_k<tp>%(m0, i))
				buff[i] = p0[i];
			else
				buff[i] = %get<tp>%(rsrc, i);
		}
		return %load<tp>%(buff);
	"""},
	"load_mskz" : { "format" :"long", "code" :"""
		// we want to guarantee that load doesn't touch the memory of masked out elems
		%v<tp>% buff[%N<tp>%];
		for(unsigned i = 0; i < %N<tp>%; i++){
			if(%get_k<tp>%(m0, i))
				buff[i] = p0[i];
			else
				buff[i] = 0;
		}
		return %load<tp>%(buff);
	"""},
	
	"set" : { "format" :"long", "code" :"""
		%r<tp>% op = %set<tp>%(vals);
	"""},
	
	"set1" : { "format" :"long", "code" :"""
		%r<tp>% op = %set1<tp>%(v0);
	"""},
    
	"set0" : { "format" :"long", "code" :"""
		%r<tp>% op = %set0<tp>%();
	"""},
	
		
	"ret_msk_2args_reg" : { "format" :"long", "code" :"""
		%m<tp>% op = %{{func_name}}<tp>%(r0, r1);
	"""},
	
	"store_msk" : { "format" :"long", "code" :"""
		for(unsigned i = 0; i < %N<tp>%; i++){
			if(%get_k<tp>%(m0, i))
				p0[i] = %get<tp>%(r0, i);
		}
	"""},
 
	"store_mskz" : { "format" :"long", "code" :"""
        for(unsigned i = 0; i < %N<tp>%; i++){
            if(%get_k<tp>%(m0, i))
				p0[i] = %get<tp>%(r0, i);
			else
				p0[i] = 0;
		}
  	"""},

	"storeu_msk" : { "format" :"long", "code" :"""
    	%v<tp>% buff[%N<tp>%];
		%v<tp>% mask_buff[%N<tp>%];
        %r<tp>% msk_reg = %toreg<tp>%(m0);
        
        %storeu<tp>%(buff, r0);
        %storeu<tp>%(mask_buff, msk_reg);
		for(unsigned i = 0; i < %N<tp>%; i++)
            if(mask_buff[i])
                p0[i] = buff[i];   
    """},
    
	"storeu_mskz" : { "format" :"long", "code" :"""
    	%v<tp>% buff[%N<tp>%];
		%v<tp>% mask_buff[%N<tp>%];
        %r<tp>% msk_reg = %toreg<tp>%(m0);
        
        %storeu<tp>%(buff, r0);
        %storeu<tp>%(mask_buff, msk_reg);
		for(unsigned i = 0; i < %N<tp>%; i++)
            if(mask_buff[i])
                p0[i] = buff[i];  
            else
				p0[i] = 0;
    """},
    
	"cmp_2args" : { "format" :"long", "code" :"""
	%m<tp>% op = %{{func_name}}<tp>%(r0, r1);
    %m<tp>% res = %andb_k<tp>%(op, m0);
    return res;
	"""},
	

	"hadd_maskz" : { "format" :"long", "code" :"""
	%r<tp>% zero = %set0<tp>%();
	%r<tp>% blended = %blend<tp>%(r0, zero, m0);
	%v<tp>% op = %hadd<tp>%(blended);
    return op;
	"""},

	"hmul_maskz" : { "format" :"long", "code" :"""
    %r<tp>% ones = %set1<tp>%(1);
    %r<tp>% blended = %blend<tp>%(r0, ones, m0);
    %v<tp>% op = %hmul<tp>%(blended);
    return op;
	"""},

	"hmin_maskz_u64" : { "format" :"long", "code" :"""
	%r<tp>% max = %set1<tp>%(UINT64_MAX);
	%r<tp>% blended = %blend<tp>%(r0, max, m0);
	%v<tp>% op = %hmin<tp>%(blended);
	return op;
	"""},
    
	"hmin_maskz_u32" : { "format" :"long", "code" :"""
	%r<tp>% max = %set1<tp>%(UINT32_MAX);
	%r<tp>% blended = %blend<tp>%(r0, max, m0);
	%v<tp>% op = %hmin<tp>%(blended);
	return op;
	"""},

	"hmin_maskz_u16" : { "format" :"long", "code" :"""
	%r<tp>% max = %set1<tp>%(UINT16_MAX);
	%r<tp>% blended = %blend<tp>%(r0, max, m0);
	%v<tp>% op = %hmin<tp>%(blended);
	return op;
	"""},

	"hmin_maskz_u8" : { "format" :"long", "code" :"""
	%r<tp>% max = %set1<tp>%(UINT8_MAX);
	%r<tp>% blended = %blend<tp>%(r0, max, m0);
	%v<tp>% op = %hmin<tp>%(blended);
	return op;
	"""},

	"hmin_maskz_f32" : { "format" :"long", "code" :"""
	%r<tp>% max = %set1<tp>%(FLT_MAX);
	%r<tp>% blended = %blend<tp>%(r0, max, m0);
	%v<tp>% op = %hmin<tp>%(blended);
	return op;
	"""},
    
	"hmin_maskz_f64" : { "format" :"long", "code" :"""
	%r<tp>% max = %set1<tp>%(DBL_MAX);
	%r<tp>% blended = %blend<tp>%(r0, max, m0);
	%v<tp>% op = %hmin<tp>%(blended);
	return op;
	"""},

	"hmin_maskz_i64" : { "format" :"long", "code" :"""
	%r<tp>% max = %set1<tp>%(INT64_MAX);
	%r<tp>% blended = %blend<tp>%(r0, max, m0);
	%v<tp>% op = %hmin<tp>%(blended);
	return op;
	"""},

    "hmin_maskz_i32" : { "format" :"long", "code" :"""
	%r<tp>% max = %set1<tp>%(INT32_MAX);
	%r<tp>% blended = %blend<tp>%(r0, max, m0);
	%v<tp>% op = %hmin<tp>%(blended);
	return op;
	"""},

	"hmin_maskz_i16" : { "format" :"long", "code" :"""
	%r<tp>% max = %set1<tp>%(INT16_MAX);
	%r<tp>% blended = %blend<tp>%(r0, max, m0);
	%v<tp>% op = %hmin<tp>%(blended);
	return op;
	"""},

	"hmin_maskz_i8" : { "format" :"long", "code" :"""
	%r<tp>% max = %set1<tp>%(INT8_MAX);
	%r<tp>% blended = %blend<tp>%(r0, max, m0);
	%v<tp>% op = %hmin<tp>%(blended);
	return op;
	"""},
    
	"hmax_maskz_u" : { "format" :"long", "code" :"""
	%r<tp>% min = %set1<tp>%(0u);
	%r<tp>% blended = %blend<tp>%(r0, min, m0);
	%v<tp>% op = %hmax<tp>%(blended);
	return op;
	"""},

	"hmax_maskz_f32" : { "format" :"long", "code" :"""
	%r<tp>% min = %set1<tp>%(-FLT_MAX);
	%r<tp>% blended = %blend<tp>%(r0, min, m0);
	%v<tp>% op = %hmax<tp>%(blended);
	return op;
	"""},

	"hmax_maskz_f64" : { "format" :"long", "code" :"""
	%r<tp>% min = %set1<tp>%(-DBL_MAX);
	%r<tp>% blended = %blend<tp>%(r0, min, m0);
	%v<tp>% op = %hmax<tp>%(blended);
	return op;
	"""},
    
	"hmax_maskz_i64" : { "format" :"long", "code" :"""
	%r<tp>% min = %set1<tp>%(INT64_MIN);
	%r<tp>% blended = %blend<tp>%(r0, min, m0);
	%v<tp>% op = %hmax<tp>%(blended);
	return op;
	"""},

	"hmax_maskz_i32" : { "format" :"long", "code" :"""
	%r<tp>% min = %set1<tp>%(INT32_MIN);
	%r<tp>% blended = %blend<tp>%(r0, min, m0);
	%v<tp>% op = %hmax<tp>%(blended);
	return op;
	"""},

	"hmax_maskz_i16" : { "format" :"long", "code" :"""
	%r<tp>% min = %set1<tp>%(INT16_MIN);
	%r<tp>% blended = %blend<tp>%(r0, min, m0);
	%v<tp>% op = %hmax<tp>%(blended);
	return op;
	"""},
    
	"hmax_maskz_i8" : { "format" :"long", "code" :"""
	%r<tp>% min = %set1<tp>%(INT8_MIN);
	%r<tp>% blended = %blend<tp>%(r0, min, m0);
	%v<tp>% op = %hmax<tp>%(blended);
	return op;
	"""},
}

implems_mask_generic_emu = {
    
    
    # STORE 
	"store" : [
		{ "instr_name": "store",  "datatypes" : all_datatypes, "version" : "mask", "template" : tpl_mask_generic_emu["store_msk"]},
		{ "instr_name": "store",  "datatypes" : all_datatypes, "version" : "maskz", "template" : tpl_mask_generic_emu["store_mskz"]},
	],
	
 	# uses get
	"storeu" : [
		{ "instr_name": "storeu",  "datatypes" : all_datatypes, "version" : "mask", "template" : tpl_mask_generic_emu["storeu_msk"]},
		{ "instr_name": "storeu",  "datatypes" : all_datatypes, "version" : "maskz", "template" : tpl_mask_generic_emu["storeu_mskz"]},
	],
 
 	# LOAD 
	"load" : [
		{ "instr_name": "load",  "datatypes" : all_datatypes, "version" : "masks", "template" : tpl_mask_generic_emu["load_msks"]},
		{ "instr_name": "load",  "datatypes" : all_datatypes, "version" : "maskz", "template" : tpl_mask_generic_emu["load_mskz"]},
	],
	
	"loadu" : [
		{ "instr_name": "loadu",  "datatypes" : all_datatypes, "version" : "masks", "template" : tpl_mask_generic_emu["load_msks"]},
		{ "instr_name": "loadu",  "datatypes" : all_datatypes, "version" : "maskz", "template" : tpl_mask_generic_emu["load_mskz"]},
	],

	"set" : [
		{ "instr_name": "set",  "datatypes" : all_datatypes, "version" : "masks", "template" : { "format" :"long", "code" : tpl_mask_generic_emu["set"]["code"] + SNIPPET_END_MSKS}},
	],
    
	"set1" : [
		{ "instr_name": "set1",  "datatypes" : all_datatypes, "version" : "masks", "template" : { "format" :"long", "code" : tpl_mask_generic_emu["set1"]["code"] + SNIPPET_END_MSKS}},
	],

	"set0" : [
		{ "instr_name": "set0",  "datatypes" : all_datatypes, "version" : "masks", "template" : { "format" :"long", "code" : tpl_mask_generic_emu["set0"]["code"] + SNIPPET_END_MSKS}},
	],

    
    # ARITHMETIC
	"add" : [
		#add SNIPPEt_END_MSK to the template code
		{ "instr_name": "add",  "datatypes" : all_datatypes, "version" : "mask", "template" : { "format" :"long", "code" : tpl_mask_generic_emu["ret_reg_2args_reg"]["code"] + SNIPPET_END_MSK}},
		{ "instr_name": "add",  "datatypes" : all_datatypes, "version" : "maskz", "template" : { "format" :"long", "code" : tpl_mask_generic_emu["ret_reg_2args_reg"]["code"] + SNIPPET_END_MSKZ}},
		{ "instr_name": "add",  "datatypes" : all_datatypes, "version" : "masks", "template" : { "format" :"long", "code" : tpl_mask_generic_emu["ret_reg_2args_reg"]["code"] + SNIPPET_END_MSKS}},
 	],
 
 	"sub" : [
		{ "instr_name": "sub",  "datatypes" : all_datatypes, "version" : "mask", "template" : { "format" :"long", "code" : tpl_mask_generic_emu["ret_reg_2args_reg"]["code"] + SNIPPET_END_MSK}},
		{ "instr_name": "sub",  "datatypes" : all_datatypes, "version" : "maskz", "template" : { "format" :"long", "code" : tpl_mask_generic_emu["ret_reg_2args_reg"]["code"] + SNIPPET_END_MSKZ}},
		{ "instr_name": "sub",  "datatypes" : all_datatypes, "version" : "masks", "template" : { "format" :"long", "code" : tpl_mask_generic_emu["ret_reg_2args_reg"]["code"] + SNIPPET_END_MSKS}},
 	],
  
	"mul" : [
		{ "instr_name": "mul",  "datatypes" : all_datatypes, "version" : "mask", "template" : { "format" :"long", "code" : tpl_mask_generic_emu["ret_reg_2args_reg"]["code"] + SNIPPET_END_MSK}},
		{ "instr_name": "mul",  "datatypes" : all_datatypes, "version" : "maskz", "template" : { "format" :"long", "code" : tpl_mask_generic_emu["ret_reg_2args_reg"]["code"] + SNIPPET_END_MSKZ}},
		{ "instr_name": "mul",  "datatypes" : all_datatypes, "version" : "masks", "template" : { "format" :"long", "code" : tpl_mask_generic_emu["ret_reg_2args_reg"]["code"] + SNIPPET_END_MSKS}},
	],
 
 	"div" : [
		{ "instr_name": "div",  "datatypes" : all_float, "version" : "mask", "template" : { "format" :"long", "code" : tpl_mask_generic_emu["ret_reg_2args_reg"]["code"] + SNIPPET_END_MSK}},
		{ "instr_name": "div",  "datatypes" : all_float, "version" : "maskz", "template" : { "format" :"long", "code" : tpl_mask_generic_emu["ret_reg_2args_reg"]["code"] + SNIPPET_END_MSKZ}},
		{ "instr_name": "div",  "datatypes" : all_float, "version" : "masks", "template" : { "format" :"long", "code" : tpl_mask_generic_emu["ret_reg_2args_reg"]["code"] + SNIPPET_END_MSKS}},
	],
  
	"div2" : [
		{ "instr_name": "div2",  "datatypes" : all_float, "version" : "mask", "template" : { "format" :"long", "code" : tpl_mask_generic_emu["ret_reg_1arg_reg"]["code"] + SNIPPET_END_MSK}},
		{ "instr_name": "div2",  "datatypes" : all_float, "version" : "maskz", "template" : { "format" :"long", "code" : tpl_mask_generic_emu["ret_reg_1arg_reg"]["code"] + SNIPPET_END_MSKZ}},
		{ "instr_name": "div2",  "datatypes" : all_float, "version" : "masks", "template" : { "format" :"long", "code" : tpl_mask_generic_emu["ret_reg_1arg_reg"]["code"] + SNIPPET_END_MSKS}},
  	],
 
	"fmadd" : [
		{ "instr_name": "fmadd",  "datatypes" : all_float+[int32], "version" : "mask", "template" : { "format" :"long", "code" : tpl_mask_generic_emu["ret_reg_3args_reg"]["code"] + SNIPPET_END_MSK}},
		{ "instr_name": "fmadd",  "datatypes" : all_float+[int32], "version" : "maskz", "template" : { "format" :"long", "code" : tpl_mask_generic_emu["ret_reg_3args_reg"]["code"] + SNIPPET_END_MSKZ}},
		{ "instr_name": "fmadd",  "datatypes" : all_float+[int32], "version" : "masks", "template" : { "format" :"long", "code" : tpl_mask_generic_emu["ret_reg_3args_reg"]["code"] + SNIPPET_END_MSKS}},
	],
 
	"fmsub" : [
		{ "instr_name": "fmsub",  "datatypes" : all_float+[int32], "version" : "mask", "template" : { "format" :"long", "code" : tpl_mask_generic_emu["ret_reg_3args_reg"]["code"] + SNIPPET_END_MSK}},
		{ "instr_name": "fmsub",  "datatypes" : all_float+[int32], "version" : "maskz", "template" : { "format" :"long", "code" : tpl_mask_generic_emu["ret_reg_3args_reg"]["code"] + SNIPPET_END_MSKZ}},
		{ "instr_name": "fmsub",  "datatypes" : all_float+[int32], "version" : "masks", "template" : { "format" :"long", "code" : tpl_mask_generic_emu["ret_reg_3args_reg"]["code"] + SNIPPET_END_MSKS}},
	],
 
	"fnmadd" : [
		{ "instr_name": "fnmadd",  "datatypes" : all_float+[int32], "version" : "mask", "template" : { "format" :"long", "code" : tpl_mask_generic_emu["ret_reg_3args_reg"]["code"] + SNIPPET_END_MSK}},
		{ "instr_name": "fnmadd",  "datatypes" : all_float+[int32], "version" : "maskz", "template" : { "format" :"long", "code" : tpl_mask_generic_emu["ret_reg_3args_reg"]["code"] + SNIPPET_END_MSKZ}},
		{ "instr_name": "fnmadd",  "datatypes" : all_float+[int32], "version" : "masks", "template" : { "format" :"long", "code" : tpl_mask_generic_emu["ret_reg_3args_reg"]["code"] + SNIPPET_END_MSKS}},
	],
 
	"fnmsub" : [
		{ "instr_name": "fnmsub",  "datatypes" : all_float+[int32], "version" : "mask", "template" : { "format" :"long", "code" : tpl_mask_generic_emu["ret_reg_3args_reg"]["code"] + SNIPPET_END_MSK}},
		{ "instr_name": "fnmsub",  "datatypes" : all_float+[int32], "version" : "maskz", "template" : { "format" :"long", "code" : tpl_mask_generic_emu["ret_reg_3args_reg"]["code"] + SNIPPET_END_MSKZ}},
		{ "instr_name": "fnmsub",  "datatypes" : all_float+[int32], "version" : "masks", "template" : { "format" :"long", "code" : tpl_mask_generic_emu["ret_reg_3args_reg"]["code"] + SNIPPET_END_MSKS}},
	],
 
	"div4" : [
		{ "instr_name": "div4",  "datatypes" : all_float, "version" : "mask", "template" : { "format" :"long", "code" : tpl_mask_generic_emu["ret_reg_1arg_reg"]["code"] + SNIPPET_END_MSK}},
		{ "instr_name": "div4",  "datatypes" : all_float, "version" : "maskz", "template" : { "format" :"long", "code" : tpl_mask_generic_emu["ret_reg_1arg_reg"]["code"] + SNIPPET_END_MSKZ}},
		{ "instr_name": "div4",  "datatypes" : all_float, "version" : "masks", "template" : { "format" :"long", "code" : tpl_mask_generic_emu["ret_reg_1arg_reg"]["code"] + SNIPPET_END_MSKS}},
	],
 
 
	# COMPARISON
	# only maskz for comparison
    
    "cmpeq" : [
        {"instr_name": "cmpeq",  "datatypes" : all_datatypes, "version" : "maskz", "template" : { "format" :"long", "code" : tpl_mask_generic_emu["cmp_2args"]["code"]}},
	],
    "cmpneq" : [
        {"instr_name": "cmpneq",  "datatypes" : all_datatypes, "version" : "maskz", "template" : { "format" :"long", "code" : tpl_mask_generic_emu["cmp_2args"]["code"]}},
	],
    "cmpgt" : [
		{"instr_name": "cmpgt",  "datatypes" : all_datatypes, "version" : "maskz", "template" : { "format" :"long", "code" : tpl_mask_generic_emu["cmp_2args"]["code"]}},
	],
    "cmpge" : [
		{"instr_name": "cmpge",  "datatypes" : all_datatypes, "version" : "maskz", "template" : { "format" :"long", "code" : tpl_mask_generic_emu["cmp_2args"]["code"]}},
	],
	"cmplt" : [
		{"instr_name": "cmplt",  "datatypes" : all_datatypes, "version" : "maskz", "template" : { "format" :"long", "code" : tpl_mask_generic_emu["cmp_2args"]["code"]}},
	],
	"cmple" : [
		{"instr_name": "cmple",  "datatypes" : all_datatypes, "version" : "maskz", "template" : { "format" :"long", "code" : tpl_mask_generic_emu["cmp_2args"]["code"]}},
	],

	# MATH 
	"sqrt" : [
		{ "instr_name": "sqrt",  "datatypes" : all_float, "version" : "mask", "template" : { "format" :"long", "code" : tpl_mask_generic_emu["ret_reg_1arg_reg"]["code"] + SNIPPET_END_MSK}},
		{ "instr_name": "sqrt",  "datatypes" : all_float, "version" : "maskz", "template" : { "format" :"long", "code" : tpl_mask_generic_emu["ret_reg_1arg_reg"]["code"] + SNIPPET_END_MSKZ}},
		{ "instr_name": "sqrt",  "datatypes" : all_float, "version" : "masks", "template" : { "format" :"long", "code" : tpl_mask_generic_emu["ret_reg_1arg_reg"]["code"] + SNIPPET_END_MSKS}},
	],
	
	"rsqrt" : [
		{ "instr_name": "rsqrt",  "datatypes" : all_float, "version" : "mask", "template" : { "format" :"long", "code" : tpl_mask_generic_emu["ret_reg_1arg_reg"]["code"] + SNIPPET_END_MSK}},
		{ "instr_name": "rsqrt",  "datatypes" : all_float, "version" : "maskz", "template" : { "format" :"long", "code" : tpl_mask_generic_emu["ret_reg_1arg_reg"]["code"] + SNIPPET_END_MSKZ}},
		{ "instr_name": "rsqrt",  "datatypes" : all_float, "version" : "masks", "template" : { "format" :"long", "code" : tpl_mask_generic_emu["ret_reg_1arg_reg"]["code"] + SNIPPET_END_MSKS}},
  	],
 
	"round" : [
		{ "instr_name": "round",  "datatypes" : all_datatypes, "version" : "mask", "template" : { "format" :"long", "code" : tpl_mask_generic_emu["ret_reg_1arg_reg"]["code"] + SNIPPET_END_MSK}},
		{ "instr_name": "round",  "datatypes" : all_datatypes, "version" : "maskz", "template" : { "format" :"long", "code" : tpl_mask_generic_emu["ret_reg_1arg_reg"]["code"] + SNIPPET_END_MSKZ}},
		{ "instr_name": "round",  "datatypes" : all_datatypes, "version" : "masks", "template" : { "format" :"long", "code" : tpl_mask_generic_emu["ret_reg_1arg_reg"]["code"] + SNIPPET_END_MSKS}},
  	],
 
	# LOGIC 
 
	# blend uses andb, andnb, xorb for avx2. So we can't really include blend.h in andb.h, xorb.h or andnb.h ...
	# afaik it's only an issue with avx2 since no other isa uses those functions for blend. The easiest 
	# solution might be to change blend in avx2 and add an implicit rule which would be 
	# "blend can't be emulated by calling other mipp functions" or smtg like that.
 
	"andb" : [
		{ "instr_name": "andb",  "datatypes" : all_datatypes, "version" : "mask", "template" : { "format" :"long", "code" : tpl_mask_generic_emu["ret_reg_2args_reg"]["code"] + SNIPPET_END_MSK}},
		{ "instr_name": "andb",  "datatypes" : all_datatypes, "version" : "maskz", "template" : { "format" :"long", "code" : tpl_mask_generic_emu["ret_reg_2args_reg"]["code"] + SNIPPET_END_MSKZ}},
		{ "instr_name": "andb",  "datatypes" : all_datatypes, "version" : "masks", "template" : { "format" :"long", "code" : tpl_mask_generic_emu["ret_reg_2args_reg"]["code"] + SNIPPET_END_MSKS}},
	],
 
	"andnb" : [
		{ "instr_name": "andnb",  "datatypes" : all_datatypes, "version" : "mask", "template" : { "format" :"long", "code" : tpl_mask_generic_emu["ret_reg_2args_reg"]["code"] + SNIPPET_END_MSK}},
		{ "instr_name": "andnb",  "datatypes" : all_datatypes, "version" : "maskz", "template" : { "format" :"long", "code" : tpl_mask_generic_emu["ret_reg_2args_reg"]["code"] + SNIPPET_END_MSKZ}},
		{ "instr_name": "andnb",  "datatypes" : all_datatypes, "version" : "masks", "template" : { "format" :"long", "code" : tpl_mask_generic_emu["ret_reg_2args_reg"]["code"] + SNIPPET_END_MSKS}},
	],
 
	"orb" : [
		{ "instr_name": "orb",  "datatypes" : all_datatypes, "version" : "mask", "template" : { "format" :"long", "code" : tpl_mask_generic_emu["ret_reg_2args_reg"]["code"] + SNIPPET_END_MSK}},
		{ "instr_name": "orb",  "datatypes" : all_datatypes, "version" : "maskz", "template" : { "format" :"long", "code" : tpl_mask_generic_emu["ret_reg_2args_reg"]["code"] + SNIPPET_END_MSKZ}},
		{ "instr_name": "orb",  "datatypes" : all_datatypes, "version" : "masks", "template" : { "format" :"long", "code" : tpl_mask_generic_emu["ret_reg_2args_reg"]["code"] + SNIPPET_END_MSKS}},
	],
 
	"xorb" : [
		{ "instr_name": "xorb",  "datatypes" : all_datatypes, "version" : "mask", "template" : { "format" :"long", "code" : tpl_mask_generic_emu["ret_reg_2args_reg"]["code"] + SNIPPET_END_MSK}},
		{ "instr_name": "xorb",  "datatypes" : all_datatypes, "version" : "maskz", "template" : { "format" :"long", "code" : tpl_mask_generic_emu["ret_reg_2args_reg"]["code"] + SNIPPET_END_MSKZ}},
		{ "instr_name": "xorb",  "datatypes" : all_datatypes, "version" : "masks", "template" : { "format" :"long", "code" : tpl_mask_generic_emu["ret_reg_2args_reg"]["code"] + SNIPPET_END_MSKS}},
	],
 
	"msb" : [
		{ "instr_name": "msb",  "datatypes" : all_datatypes, "version" : "mask", "template" : { "format" :"long", "code" : tpl_mask_generic_emu["ret_reg_1arg_reg"]["code"] + SNIPPET_END_MSK}},
		{ "instr_name": "msb",  "datatypes" : all_datatypes, "version" : "maskz", "template" : { "format" :"long", "code" : tpl_mask_generic_emu["ret_reg_1arg_reg"]["code"] + SNIPPET_END_MSKZ}},
		{ "instr_name": "msb",  "datatypes" : all_datatypes, "version" : "masks", "template" : { "format" :"long", "code" : tpl_mask_generic_emu["ret_reg_1arg_reg"]["code"] + SNIPPET_END_MSKS}},
	],
	
	"notb" : [
		{ "instr_name": "notb",  "datatypes" : all_datatypes, "version" : "mask", "template" : { "format" :"long", "code" : tpl_mask_generic_emu["ret_reg_1arg_reg"]["code"] + SNIPPET_END_MSK}},
		{ "instr_name": "notb",  "datatypes" : all_datatypes, "version" : "maskz", "template" : { "format" :"long", "code" : tpl_mask_generic_emu["ret_reg_1arg_reg"]["code"] + SNIPPET_END_MSKZ}},
		{ "instr_name": "notb",  "datatypes" : all_datatypes, "version" : "masks", "template" : { "format" :"long", "code" : tpl_mask_generic_emu["ret_reg_1arg_reg"]["code"] + SNIPPET_END_MSKS}},
	],
 
	
 	# REDUCTIONS
	# only mask. Policy for reduction is to apply reduction + broadcast and then select elements based on the mask. Only support mask.
    "hadd" : [
		{ "instr_name": "hadd",  "datatypes" : all_datatypes, "version" : "maskz", "template" : tpl_mask_generic_emu["hadd_maskz"]},
	],
    "hmul" : [
		{ "instr_name": "hmul",  "datatypes" : all_datatypes, "version" : "maskz", "template" : tpl_mask_generic_emu["hmul_maskz"]},
	],
	"hmin" : [
        { "instr_name": "hmin",  "datatypes" : [float32], "version" : "maskz", "template" : tpl_mask_generic_emu["hmin_maskz_f32"]},
        { "instr_name": "hmin",  "datatypes" : [float64], "version" : "maskz", "template" : tpl_mask_generic_emu["hmin_maskz_f64"]},
        { "instr_name": "hmin",  "datatypes" : [int64],   "version" : "maskz", "template" : tpl_mask_generic_emu["hmin_maskz_i64"]},
		{ "instr_name": "hmin",  "datatypes" : [int32],   "version" : "maskz", "template" : tpl_mask_generic_emu["hmin_maskz_i32"]},
        { "instr_name": "hmin",  "datatypes" : [int16],   "version" : "maskz", "template" : tpl_mask_generic_emu["hmin_maskz_i16"]},
		{ "instr_name": "hmin",  "datatypes" : [int8],    "version" : "maskz", "template" : tpl_mask_generic_emu["hmin_maskz_i8"]},
        { "instr_name": "hmin",  "datatypes" : [uint64],   "version" : "maskz", "template" : tpl_mask_generic_emu["hmin_maskz_u64"]},
		{ "instr_name": "hmin",  "datatypes" : [uint32],   "version" : "maskz", "template" : tpl_mask_generic_emu["hmin_maskz_u32"]},
        { "instr_name": "hmin",  "datatypes" : [uint16],   "version" : "maskz", "template" : tpl_mask_generic_emu["hmin_maskz_u16"]},
		{ "instr_name": "hmin",  "datatypes" : [uint8],    "version" : "maskz", "template" : tpl_mask_generic_emu["hmin_maskz_u8"]},
	],
	"hmax" : [
		{"instr_name": "hmax",  "datatypes" : all_uint,  "version" : "maskz", "template" : tpl_mask_generic_emu["hmax_maskz_u"]},
		{"instr_name": "hmax",  "datatypes" : [float32], "version" : "maskz", "template" : tpl_mask_generic_emu["hmax_maskz_f32"]},
		{"instr_name": "hmax",  "datatypes" : [float64], "version" : "maskz", "template" : tpl_mask_generic_emu["hmax_maskz_f64"]},
		{"instr_name": "hmax",  "datatypes" : [int64],   "version" : "maskz", "template" : tpl_mask_generic_emu["hmax_maskz_i64"]},
		{"instr_name": "hmax",  "datatypes" : [int32],   "version" : "maskz", "template" : tpl_mask_generic_emu["hmax_maskz_i32"]},
		{"instr_name": "hmax",  "datatypes" : [int16],   "version" : "maskz", "template" : tpl_mask_generic_emu["hmax_maskz_i16"]},
		{"instr_name": "hmax",  "datatypes" : [int8],    "version" : "maskz", "template" : tpl_mask_generic_emu["hmax_maskz_i8"]},
	],
 
	# SELECTION
	"min" : [
		{ "instr_name": "min",  "datatypes" : all_datatypes, "version" : "mask", "template" : { "format" :"long", "code" : tpl_mask_generic_emu["ret_reg_2args_reg"]["code"] + SNIPPET_END_MSK}},
		{ "instr_name": "min",  "datatypes" : all_datatypes, "version" : "maskz", "template" : { "format" :"long", "code" : tpl_mask_generic_emu["ret_reg_2args_reg"]["code"] + SNIPPET_END_MSKZ}},
		{ "instr_name": "min",  "datatypes" : all_datatypes, "version" : "masks", "template" : { "format" :"long", "code" : tpl_mask_generic_emu["ret_reg_2args_reg"]["code"] + SNIPPET_END_MSKS}},
	],
 
	"max" : [
		{ "instr_name": "max",  "datatypes" : all_datatypes, "version" : "mask", "template" : { "format" :"long", "code" : tpl_mask_generic_emu["ret_reg_2args_reg"]["code"] + SNIPPET_END_MSK}},
		{ "instr_name": "max",  "datatypes" : all_datatypes, "version" : "maskz", "template" : { "format" :"long", "code" : tpl_mask_generic_emu["ret_reg_2args_reg"]["code"] + SNIPPET_END_MSKZ}},
		{ "instr_name": "max",  "datatypes" : all_datatypes, "version" : "masks", "template" : { "format" :"long", "code" : tpl_mask_generic_emu["ret_reg_2args_reg"]["code"] + SNIPPET_END_MSKS}},
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
	const %v<tp>% *ptr = vals + %N<tp>% / 2;
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
    
    "tpl_testz" : { "format" :"long", "code" :"""
{% if lmul == 1 %}
	return %testz<tp>%(m0, m1);
{% else %}
	return %testz<c:tp|b:tp|m:tp/2>%(m0.m1, m0.m2) && %testz<c:tp|b:tp|m:tp/2>%(m1.m1, m1.m2);
{% endif %}"""},
    
    "tpl_testz_2" : { "format" :"long", "code" :"""
{% if lmul == 1 %}
	return %testz_2<tp>%(m0);
{% else %}
	return %testz_2<c:tp|b:tp|m:tp/2>%(m0.m1) && %testz_2<c:tp|b:tp|m:tp/2>%(m0.m2);
{% endif %}"""},

	
	"hadd_to_scal" : { "format" :"long", "code" :"""
{% if lmul == 1 %}
	return %hadd_to_scal<tp>%(r0);
{% else %}
	
  	%v<tp>% v0 = %hadd_to_scal<c:tp|b:tp|m:tp/2>%(r0.r1);
	%v<tp>% v1 = %hadd_to_scal<c:tp|b:tp|m:tp/2>%(r0.r2);	
	return v0 + v1;
{% endif %}"""},

	"hadd" : { "format" :"long", "code" :"""
{% if lmul == 1 %}
	return %hadd<tp>%(r0);
{% else %}
	
  	%v<tp>% v0 = %hadd<c:tp|b:tp|m:tp/2>%(r0.r1);
	%v<tp>% v1 = %hadd<c:tp|b:tp|m:tp/2>%(r0.r2);	
	return v0 + v1;
{% endif %}"""},

	
	"hmul" : { "format" :"long", "code" :"""
{% if lmul == 1 %}
	return %hmul<tp>%(r0);
{% else %}
	
	%v<tp>% v1, v2;
  	v1 = %hmul<c:tp|b:tp|m:tp/2>%(r0.r1);
	v2 = %hmul<c:tp|b:tp|m:tp/2>%(r0.r2);	
	return v1 * v2;
{% endif %}"""},

 
	"hmin" : { "format" :"long", "code" :"""
{% if lmul == 1 %}
	return %hmin<tp>%(r0);
{% else %}
	
	%v<tp>% v1, v2;
  	v1 = %hmin<c:tp|b:tp|m:tp/2>%(r0.r1);
	v2 = %hmin<c:tp|b:tp|m:tp/2>%(r0.r2);

	return v1 < v2 ? v1 : v2;
{% endif %}"""},
	
	"hmax" : { "format" :"long", "code" :"""
{% if lmul == 1 %}
	return %hmax<tp>%(r0);
{% else %}
	
	%v<tp>% v1, v2;
  	v1 = %hmax<c:tp|b:tp|m:tp/2>%(r0.r1);
	v2 = %hmax<c:tp|b:tp|m:tp/2>%(r0.r2);
	return v1 > v2 ? v1 : v2;
{% endif %}"""},


	"hadd_maskz" : { "format" :"long", "code" :"""
{% if lmul == 1 %}
	return %hadd<tp>%(r0);
{% else %}
	
  	%v<tp>% v0 = %hadd<c:tp|b:tp|m:tp/2>%(r0.r1);
	%v<tp>% v1 = %hadd<c:tp|b:tp|m:tp/2>%(r0.r2);	
	return v0 + v1;
{% endif %}"""},

	
	"hmul_maskz" : { "format" :"long", "code" :"""
{% if lmul == 1 %}
	return %hmul<tp>%(r0);
{% else %}
	
	%v<tp>% v1, v2;
  	v1 = %hmul<c:tp|b:tp|m:tp/2>%(r0.r1);
	v2 = %hmul<c:tp|b:tp|m:tp/2>%(r0.r2);	
	return v1 * v2;
{% endif %}"""},

 
	"hmin_maskz" : { "format" :"long", "code" :"""
{% if lmul == 1 %}
	return %hmin<tp>%(r0);
{% else %}
	
	%v<tp>% v1, v2;
  	v1 = %hmin<c:tp|b:tp|m:tp/2>%(r0.r1);
	v2 = %hmin<c:tp|b:tp|m:tp/2>%(r0.r2);

	return v1 < v2 ? v1 : v2;
{% endif %}"""},
	
	"hmax_maskz" : { "format" :"long", "code" :"""
{% if lmul == 1 %}
	return %hmax<tp>%(r0);
{% else %}
	
	%v<tp>% v1, v2;
  	v1 = %hmax<c:tp|b:tp|m:tp/2>%(r0.r1);
	v2 = %hmax<c:tp|b:tp|m:tp/2>%(r0.r2);
	return v1 > v2 ? v1 : v2;
{% endif %}"""},

}

# dependencies key is a hacky solution but that's life.
# the maskz versions are likely useless. Currently their template are "wrong" and the generation only works bc of a hack.
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
 
	"testz" : [
		{ "instr_name": "testz",  "datatypes" : all_datatypes, "version" : "horiz_lmul", "template" : tpl_horiz_lmul_generic_emu["tpl_testz"]},
	],
		
 	"testz_2" : [
		{ "instr_name": "testz_2",  "datatypes" : all_datatypes, "version" : "horiz_lmul", "template" : tpl_horiz_lmul_generic_emu["tpl_testz_2"]},
	],
	"hadd" : [
     		{ "instr_name": "hadd",  "datatypes" : all_datatypes, "version" : "horiz_lmul", "template" : tpl_horiz_lmul_generic_emu["hadd"], "dependencies" : {"add"}},
        	{ "instr_name": "hadd",  "datatypes" : all_datatypes, "version" : "maskz", 		"template" : tpl_horiz_lmul_generic_emu["hadd_maskz"], "dependencies" : {"add"}},
	],
	"hmul" : [
     		{ "instr_name": "hmul",  "datatypes" : all_datatypes, "version" : "horiz_lmul", "template" : tpl_horiz_lmul_generic_emu["hmul"], "dependencies" : {"mul"}},
        	{ "instr_name": "hmul",  "datatypes" : all_datatypes, "version" : "maskz", 		"template" : tpl_horiz_lmul_generic_emu["hmul_maskz"], "dependencies" : {"mul"}},
	],
 	"hmin" : [
	 		{ "instr_name": "hmin",  "datatypes" : all_datatypes, "version" : "horiz_lmul", "template" : tpl_horiz_lmul_generic_emu["hmin"], "dependencies" : {"min"}},
			{ "instr_name": "hmin",  "datatypes" : all_datatypes, "version" : "maskz", 		"template" : tpl_horiz_lmul_generic_emu["hmin_maskz"], "dependencies" : {"min"}},
	],
	"hmax" : [
     	 	{ "instr_name": "hmax",  "datatypes" : all_datatypes, "version" : "horiz_lmul", "template" : tpl_horiz_lmul_generic_emu["hmax"], "dependencies" : {"max"}},
			{ "instr_name": "hmax",  "datatypes" : all_datatypes, "version" : "maskz", 		"template" : tpl_horiz_lmul_generic_emu["hmax_maskz"], "dependencies" : {"max"}},
	],
	"hadd_to_scal" : [
     	 	{ "instr_name": "hadd_to_scal",  "datatypes" : all_datatypes, "version" : "horiz_lmul", "template" : tpl_horiz_lmul_generic_emu["hadd_to_scal"]},
	],
}