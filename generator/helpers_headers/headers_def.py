from tools import *
import copy

"""
"protos" dictionary:
	- Defines prototypes of SIMD functions presented in a dictionary. 
	- Each prototype is defined with a key representing a specific function model. 
	- For each model, specifications for the return type and arguments are provided. 
	- Details include the type ("reg" for register , "msk" to designate masks, "r" , "val" for values, "ptr" for pointers and "Nele" for number of elements).
	- The attribute (such as "WO" for Write Only or "RO" for Read Only)
	-"fixeddatatype" is defined as a Boolean value, thus determining whether a variation in data type is allowed or not.
"""
protos = {
	"ret_reg_1arg_ptr": {
		"ret" :
			{"type": "reg", "charac": "WO", "fixeddatatype": False},
		"args" : [
			{"type": "ptr", "charac": "RO", "fixeddatatype": False}
		]
	},
	"ret_reg_2args_msk_ptr": {
		"ret" :
			{"type": "reg", "charac": "WO", "fixeddatatype": False},
		"args" : [
		    {"type": "msk", "charac": "RO", "fixeddatatype": int32},
			{"type": "ptr", "charac": "RO", "fixeddatatype": False}
		]
	},
	"ret_void_3args_ptr_msk_reg":{
		"ret" :
			{"type": False, "fixeddatatype": False},
		"args" : [
			{"type": "ptr", "charac": "WO", "fixeddatatype": False},
		    {"type": "msk", "charac": "RO", "fixeddatatype": int32},
			{"type": "reg", "charac": "RO", "fixeddatatype": False}
		]
	},
	"ret_void_2args_ptr_reg": {
		"ret" :
			{"type": False, "fixeddatatype": False},
		"args" : [
			{"type": "ptr", "charac": "WO", "fixeddatatype": False},
			{"type": "reg", "charac": "RO", "fixeddatatype": False}
		]
	},
	"ret_reg_2args_ptr_vindex": {
		"ret" :
			{"type": "reg", "charac": "WO", "fixeddatatype": False},
		"args" : [
			{"type": "ptr", "charac": "WO", "fixeddatatype": False},
			{"type": "vindex", "charac": "RO", "fixeddatatype": False}
		]
	},
	"ret_reg_3args_ptr_vindex_msk": {
		"ret" :
			{"type": "reg", "charac": "WO", "fixeddatatype": False},
		"args" : [
			{"type": "ptr", "charac": "WO", "fixeddatatype": False},
			{"type": "vindex", "charac": "RO", "fixeddatatype": False},
			{"type": "msk", "charac": "RO", "fixeddatatype": False}
		]
	},
	"ret_reg_1arg_val": {
		"ret" :
			{"type": "reg", "charac": "WO", "fixeddatatype": False},
		"args" : [
			{"type": "val", "charac": "RO", "fixeddatatype": False}
		]
	},
	"ret_reg_1arg_Nele": {
		"ret" :
			{"type": "reg", "charac": "WO", "fixeddatatype": False},
		"args" : [
			{"type": "Nele", "charac": "RO", "fixeddatatype": False}
		]
	},
	"ret_msk_1arg_Nele": {
		"ret" :
			{"type": "msk", "charac": "WO", "fixeddatatype": False},
		"args" : [
			{"type": "Nele", "charac": "RO", "fixeddatatype": int32}
		]
	},
	"ret_reg_1arg_i32": {
		"ret" :
			{"type": "reg", "charac": "WO", "fixeddatatype": False},
		"args" : [
			{"type": "val", "charac": "RO", "fixeddatatype": int32}
		]
	},
	"ret_msk_1arg_i32": {
		"ret" :
			{"type": "msk", "charac": "WO", "fixeddatatype": False},
		"args" : [
			{"type": "val", "charac": "RO", "fixeddatatype": int32}
		]
	},
	"ret_msk_1arg_val": {
		"ret" :
			{"type": "msk", "charac": "WO", "fixeddatatype": False},
		"args" : [
			{"type": "val", "charac": "RO", "fixeddatatype": False}
		]
	},
	"ret_reg_0arg": {
		"ret" :
			{"type": "reg", "charac": "WO", "fixeddatatype": False},
		"args" : []
	},
    "ret_msk_0arg": {
  	    "ret" :
 		    {"type": "msk", "charac": "WO", "fixeddatatype": False},
	    "args" : []
    },
	"ret_reg_1arg_reg": {
		"ret" :
			{"type": "reg", "charac": "WO", "fixeddatatype": False},
		"args" : [
			{"type": "reg", "charac": "RO", "fixeddatatype": False},
		]
	},
	"ret_val_1arg_reg": {
		"ret" :
			{"type": "val", "charac": "WO", "fixeddatatype": False},
		"args" : [
			{"type": "reg", "charac": "RO", "fixeddatatype": False},
		]
	},
	"ret_msk_1arg_msk": {
		"ret" :
			{"type": "msk", "charac": "WO", "fixeddatatype": False},
		"args" : [
			{"type": "msk", "charac": "RO", "fixeddatatype": False},
		]
	},
	"ret_msk_1arg_reg": {
		"ret" :
			{"type": "msk", "charac": "WO", "fixeddatatype": False},
		"args" : [
			{"type": "reg", "charac": "RO", "fixeddatatype": False},
		]
	},
	"ret_reg_1arg_msk": {
		"ret" :
			{"type": "reg", "charac": "WO", "fixeddatatype": False},
		"args" : [
			{"type": "msk", "charac": "RO", "fixeddatatype": False},
		]
	},
	"ret_reg_2args_reg": {
		"ret" :
			{"type": "reg", "charac": "WO", "fixeddatatype": False},
		"args" : [
			{"type": "reg", "charac": "RO", "fixeddatatype": False},
			{"type": "reg", "charac": "RO", "fixeddatatype": False},
		]
	},
	"ret_reg_2args_reg_msk": {
		"ret" :
			{"type": "reg", "charac": "WO", "fixeddatatype": False},
		"args" : [
			{"type": "reg", "charac": "RO", "fixeddatatype": False},
			{"type": "msk", "charac": "RO", "fixeddatatype": False},
		]
	},
	"ret_msk_2args_reg": {
		"ret" :
			{"type": "msk", "charac": "WO", "fixeddatatype": False},
		"args" : [
			{"type": "reg", "charac": "RO", "fixeddatatype": False},
			{"type": "reg", "charac": "RO", "fixeddatatype": False},
		]
	},
	"ret_msk_2args_msk": {
		"ret" :
			{"type": "msk", "charac": "WO", "fixeddatatype": False},
		"args" : [
			{"type": "msk", "charac": "RO", "fixeddatatype": False},
			{"type": "msk", "charac": "RO", "fixeddatatype": False},
		]
	},
	"ret_reg_2args_reg_val": {
		"ret" :
			{"type": "reg", "charac": "WO", "fixeddatatype": False},
		"args" : [
			{"type": "reg", "charac": "RO", "fixeddatatype": False},
			{"type": "val", "charac": "RO", "fixeddatatype": int32},
		]
	},
	"ret_reg_3args_reg": {
		"ret" :
			{"type": "reg", "charac": "WO", "fixeddatatype": False},
		"args" : [
			{"type": "reg", "charac": "RO", "fixeddatatype": False},
			{"type": "reg", "charac": "RO", "fixeddatatype": False},
			{"type": "reg", "charac": "RO", "fixeddatatype": False},
		]
	},
	"ret_reg_3args_2reg_1msk": {
		"ret" :
			{"type": "reg", "charac": "WO", "fixeddatatype": False},
		"args" : [
			{"type": "reg", "charac": "RO", "fixeddatatype": False},
			{"type": "reg", "charac": "RO", "fixeddatatype": False},
			{"type": "msk", "charac": "RO", "fixeddatatype": False},
		]
	},
	"ret_reg_3args_1reg_2val": {
		"ret" :
			{"type": "reg", "charac": "WO", "fixeddatatype": False},
		"args" : [
			{"type": "reg", "charac": "RO", "fixeddatatype": False},
			{"type": "val", "charac": "RO", "fixeddatatype": False},
			{"type": "val", "charac": "RO", "fixeddatatype": False},
		]
	},
	"ret_reg_3args_2reg_1msk": {
		"ret" :
			{"type": "reg", "charac": "WO", "fixeddatatype": False},
		"args" : [
			{"type": "reg", "charac": "RO", "fixeddatatype": False},
			{"type": "reg", "charac": "RO", "fixeddatatype": False},
			{"type": "msk", "charac": "RO", "fixeddatatype": False},
		]
	},
	"ret_reg_3args_2reg_1msk_1reg": {
		"ret" :
			{"type": "reg", "charac": "WO", "fixeddatatype": False},
		"args" : [
			{"type": "reg", "charac": "RO", "fixeddatatype": False},
			{"type": "reg", "charac": "RO", "fixeddatatype": False},
			{"type": "msk", "charac": "RO", "fixeddatatype": False},
			{"type": "reg", "charac": "RO", "fixeddatatype": False},
		]
	},
	
	"ret_reg_3args_1msk_2reg": {
		"ret" :
			{"type": "reg", "charac": "WO", "fixeddatatype": False},
		"args" : [
			{"type": "msk", "charac": "RO", "fixeddatatype": False},
			{"type": "reg", "charac": "RO", "fixeddatatype": False},
			{"type": "reg", "charac": "RO", "fixeddatatype": False},
		]
	},
	"ret_i32_1arg_msk": {
		"ret" :
			{"type": "val", "charac": "WO", "fixeddatatype": int32},
		"args" : [
			{"type": "msk", "charac": "RO", "fixeddatatype": False},
		]
	},
	"ret_i32_2args_msk": {
		"ret" :
			{"type": "val", "charac": "WO", "fixeddatatype": int32},
		"args" : [
			{"type": "msk", "charac": "RO", "fixeddatatype": False},
			{"type": "msk", "charac": "RO", "fixeddatatype": False},
		]
	},
	"ret_val_2args_reg_val": {
		"ret" :
			{"type": "val", "charac": "WO", "fixeddatatype": False},
		"args" : [
			{"type": "reg", "charac": "RO", "fixeddatatype": False},
			{"type": "val", "charac": "RO", "fixeddatatype": uint32},
		]
	},
	"ret_val_2args_msk_val": {
		"ret" :
			{"type": "val", "charac": "WO", "fixeddatatype": False},
		"args" : [
			{"type": "msk", "charac": "RO", "fixeddatatype": False},
			{"type": "val", "charac": "RO", "fixeddatatype": uint32},
		]
	},
	"ret_val_1arg_reg": {
		"ret" :
			{"type": "val", "charac": "WO", "fixeddatatype": False},
		"args" : [
			{"type": "reg", "charac": "RO", "fixeddatatype": False},
		]
	},
}
"""
	"mipp_funcs" dictionnary : contains different MIPP functions specific to the "AVX/AVX2" architecture. 
		-Each function is associated with a prototype model based on its key in the "protos" dictionary, with the data types
		(for which the function is to be generated are specified, along with other parameters such as the parameters such as the "horizontal" flag
"""

mipp_funcs_concepts = {
	"all_casts": ["cast","cast_k","toreg","tomsk"],
	"all_loads": ["load","loadu","set","set_k","set1","set0","set0_k","maskzld","gather"],
	"all_acces": ["store","storeu","get", "getfirst","scatter","maskst"],
	"all_arithm_op": ["add","sub","mul","div"],
	"all_fused_arithm_op":["fmadd","fmsub", "fnmadd","fnmsub"],
	"all_order_op":["cmpeq","cmpneq","cmplt","cmpge","cmpgt"],
	"all_maths_functions":["sqrt","rsqrt"],
	"all_binary_op":["andb","andb_k","andnb","andnb_k","orb","orb_k","xorb","xorb_k","msb","notb","notb_k"],
	"all_reductions":["hadd","hmul","hmin","hmax"],
	"a_trier":["round","blend","testz","testz_2"]
	}

mipp_funcs = {
    "cast":    { "proto": protos["ret_reg_1arg_reg"            ], "datatypes": all_datatypes_cart_prod, "horizontal": False , "maskable": False , "maskzable": False } ,
	"cast_k":  { "proto": protos["ret_msk_1arg_msk"            ], "datatypes": all_datatypes_cart_prod, "horizontal": False , "maskable": False , "maskzable": False } ,
	"toreg":   { "proto": protos["ret_reg_1arg_msk"            ], "datatypes": all_datatypes          , "horizontal": False , "maskable": False , "maskzable": False } ,
	"tomsk":   { "proto": protos["ret_msk_1arg_reg"            ], "datatypes": all_datatypes          , "horizontal": False , "maskable": False , "maskzable": False } ,
	"load":    { "proto": protos["ret_reg_1arg_ptr"            ], "datatypes": all_datatypes          , "horizontal": False , "maskable": True  , "maskzable": True } ,
	"loadu":   { "proto": protos["ret_reg_1arg_ptr"            ], "datatypes": all_datatypes          , "horizontal": False , "maskable": True  , "maskzable": True } ,
	"store":   { "proto": protos["ret_void_2args_ptr_reg"      ], "datatypes": all_datatypes          , "horizontal": False , "maskable": True  , "maskzable": True } ,
	"storeu":  { "proto": protos["ret_void_2args_ptr_reg"      ], "datatypes": all_datatypes          , "horizontal": False , "maskable": True  , "maskzable": True } ,
	"set" :    { "proto": protos["ret_reg_1arg_Nele"           ], "datatypes": all_datatypes          , "horizontal": True  , "maskable": True  , "maskzable": True } ,
	"set_k" :  { "proto": protos["ret_msk_1arg_Nele"           ], "datatypes": all_datatypes          , "horizontal": False , "maskable": False , "maskzable": False } ,
	"set1":    { "proto": protos["ret_reg_1arg_val"            ], "datatypes": all_datatypes          , "horizontal": False , "maskable": False , "maskzable": True  } ,
	"set1_k":  { "proto": protos["ret_msk_1arg_i32"            ], "datatypes": all_datatypes          , "horizontal": False , "maskable": False , "maskzable": False } ,
	"maskzld": { "proto": protos["ret_reg_2args_msk_ptr"       ], "datatypes": all_datatypes          , "horizontal": False , "maskable": False , "maskzable": False  } ,
	"maskst":  { "proto": protos["ret_void_3args_ptr_msk_reg"  ], "datatypes": all_datatypes          , "horizontal": False , "maskable": False , "maskzable": False  } ,
	"set0":    { "proto": protos["ret_reg_0arg"                ], "datatypes": all_datatypes          , "horizontal": False , "maskable": False , "maskzable": False  } ,
	#"low_k":   { "proto": protos["ret_msk_0arg"                ], "datatypes": all_datatypes          , "horizontal": False },
	"get":     { "proto": protos["ret_val_2args_reg_val"       ], "datatypes": all_datatypes          , "horizontal": True  , "maskable": False , "maskzable": False } ,
	"get_k":   { "proto": protos["ret_val_2args_msk_val"       ], "datatypes": all_datatypes          , "horizontal": True  , "maskable": False , "maskzable": False } ,
	"getfirst":{ "proto": protos["ret_val_1arg_reg"            ], "datatypes": all_datatypes          , "horizontal": True  , "maskable": False , "maskzable": False } ,
	#"gather"  :{ "proto": protos["ret_reg_2args_ptr_vindex"    ], "datatypes": all_datatypes          , "horizontal": False  },
	#"mask_gather":{ "proto": protos["ret_reg_3args_ptr_vindex_msk" ], "datatypes": all_datatypes          , "horizontal": False  },
	"sqrt":    { "proto": protos["ret_reg_1arg_reg"            ], "datatypes": all_float              , "horizontal": False , "maskable": True , "maskzable": True  } ,
	"rsqrt":   { "proto": protos["ret_reg_1arg_reg"            ], "datatypes": all_float              , "horizontal": False , "maskable": True , "maskzable": True  } ,
	"add":     { "proto": protos["ret_reg_2args_reg"           ], "datatypes": all_datatypes          , "horizontal": False , "maskable": True , "maskzable": True  } ,
	"sub":     { "proto": protos["ret_reg_2args_reg"           ], "datatypes": all_datatypes          , "horizontal": False , "maskable": True , "maskzable": True  } ,
	"mul":     { "proto": protos["ret_reg_2args_reg"           ], "datatypes": all_datatypes          , "horizontal": False , "maskable": True , "maskzable": True  } ,
	"div":     { "proto": protos["ret_reg_2args_reg"           ], "datatypes": all_float              , "horizontal": False , "maskable": True , "maskzable": True  } ,
	"min":     { "proto": protos["ret_reg_2args_reg"           ], "datatypes": all_datatypes          , "horizontal": False , "maskable": True , "maskzable": True  } ,
	"max":     { "proto": protos["ret_reg_2args_reg"           ], "datatypes": all_datatypes          , "horizontal": False , "maskable": True , "maskzable": True  } ,
	"fmadd":   { "proto": protos["ret_reg_3args_reg"           ], "datatypes": all_float+[int32]      , "horizontal": False , "maskable": True , "maskzable": True  } ,
	"fmsub":   { "proto": protos["ret_reg_3args_reg"           ], "datatypes": all_float+[int32]      , "horizontal": False , "maskable": True , "maskzable": True  } ,
	"andb":    { "proto": protos["ret_reg_2args_reg"           ], "datatypes": all_datatypes          , "horizontal": False , "maskable": True , "maskzable": True  } ,
	"andb_k":  { "proto": protos["ret_msk_2args_msk"           ], "datatypes": all_datatypes          , "horizontal": False , "maskable": False , "maskzable": False  } ,
	"andnb":   { "proto": protos["ret_reg_2args_reg"           ], "datatypes": all_datatypes          , "horizontal": False , "maskable": True , "maskzable": True  } ,
	"andnb_k": { "proto": protos["ret_msk_2args_msk"           ], "datatypes": all_datatypes          , "horizontal": False , "maskable": False , "maskzable": False  } ,
	"orb":     { "proto": protos["ret_reg_2args_reg"           ], "datatypes": all_datatypes          , "horizontal": False , "maskable": True , "maskzable": True  } ,
	"orb_k":   { "proto": protos["ret_msk_2args_msk"           ], "datatypes": all_datatypes          , "horizontal": False , "maskable": False , "maskzable": False  } ,
	"xorb":    { "proto": protos["ret_reg_2args_reg"           ], "datatypes": all_datatypes          , "horizontal": False , "maskable": True , "maskzable": True  } ,
	"xorb_k":  { "proto": protos["ret_msk_2args_msk"           ], "datatypes": all_datatypes          , "horizontal": False , "maskable": False , "maskzable": False  } ,
	"msb":     { "proto": protos["ret_reg_1arg_reg"            ], "datatypes": all_datatypes          , "horizontal": False , "maskable": True , "maskzable": True  } ,
	"notb":    { "proto": protos["ret_reg_1arg_reg"            ], "datatypes": all_datatypes          , "horizontal": False , "maskable": True , "maskzable": True  } ,
	"notb_k":  { "proto": protos["ret_msk_1arg_msk"            ], "datatypes": all_datatypes          , "horizontal": False , "maskable": False , "maskzable": False  } ,
	"cmpeq":   { "proto": protos["ret_msk_2args_reg"           ], "datatypes": all_datatypes          , "horizontal": False , "maskable": False , "maskzable": False  } ,
	"cmpneq":  { "proto": protos["ret_msk_2args_reg"           ], "datatypes": all_datatypes          , "horizontal": False , "maskable": False , "maskzable": False  } ,
    "cmplt":   { "proto": protos["ret_msk_2args_reg"           ], "datatypes": all_datatypes          , "horizontal": False , "maskable": False , "maskzable": False  } ,
	"cmple":   { "proto": protos["ret_msk_2args_reg"           ], "datatypes": all_datatypes          , "horizontal": False , "maskable": False , "maskzable": False  } ,
	"cmpge":   { "proto": protos["ret_msk_2args_reg"           ], "datatypes": all_datatypes          , "horizontal": False , "maskable": False , "maskzable": False  } ,
	"cmpgt":   { "proto": protos["ret_msk_2args_reg"           ], "datatypes": all_datatypes          , "horizontal": False , "maskable": False , "maskzable": False  } ,
	"round":   { "proto": protos["ret_reg_1arg_reg"            ], "datatypes": all_datatypes          , "horizontal": False , "maskable": True  , "maskzable": True  } ,
	"blend":   { "proto": protos["ret_reg_3args_2reg_1msk"     ], "datatypes": all_datatypes          , "horizontal": False , "maskable": False , "maskzable": True  } ,
	"set0_k":  { "proto": protos["ret_msk_0arg"                ], "datatypes": all_datatypes          , "horizontal": False , "maskable": False , "maskzable": False  } ,
	"testz":   { "proto": protos["ret_i32_2args_msk"           ], "datatypes": all_datatypes          , "horizontal": True  , "maskable": False , "maskzable": False  } ,
	"testz_2": { "proto": protos["ret_i32_1arg_msk"            ], "datatypes": all_datatypes          , "horizontal": True  , "maskable": False , "maskzable": False  } ,
	"hadd":    { "proto": protos["ret_reg_1arg_reg"            ], "datatypes": all_datatypes          , "horizontal": True  , "maskable": True  , "maskzable": False } ,
	"hmul":    { "proto": protos["ret_reg_1arg_reg"            ], "datatypes": all_datatypes          , "horizontal": True  , "maskable": True  , "maskzable": False } ,
	"hmin":    { "proto": protos["ret_reg_1arg_reg"            ], "datatypes": all_datatypes          , "horizontal": True  , "maskable": True  , "maskzable": False } ,
	"hmax":    { "proto": protos["ret_reg_1arg_reg"            ], "datatypes": all_datatypes          , "horizontal": True  , "maskable": True  , "maskzable": False } ,
	"hadd_to_scal":    { "proto": protos["ret_val_1arg_reg"            ], "datatypes": all_datatypes          , "horizontal": True  , "maskable": True  , "maskzable": False } ,
	#"hmul_to_scal":    { "proto": protos["ret_val_1arg_reg"            ], "datatypes": all_datatypes          , "horizontal": True  },
	#"hmin_to_scal":    { "proto": protos["ret_val_1arg_reg"            ], "datatypes": all_datatypes          , "horizontal": True  },
	#"hmax_to_scal":    { "proto": protos["ret_val_1arg_reg"            ], "datatypes": all_datatypes          , "horizontal": True  },
	"maskz_add":{ "proto": protos["ret_reg_3args_1msk_2reg" ], "datatypes": all_datatypes          , "horizontal": True  , "maskable": False , "maskzable": False } ,
	"fnmadd":  { "proto": protos["ret_reg_3args_reg"           ], "datatypes": all_float+[int32]      , "horizontal": False , "maskable": True , "maskzable": True  } ,
	"fnmsub":  { "proto": protos["ret_reg_3args_reg"           ], "datatypes": all_float+[int32]      , "horizontal": False , "maskable": True , "maskzable": True  } ,
	"div2":    { "proto": protos["ret_reg_1arg_reg"            ], "datatypes": all_float              , "horizontal": False , "maskable": True , "maskzable": True  } ,
	"div4":	   { "proto": protos["ret_reg_1arg_reg"            ], "datatypes": all_float              , "horizontal": False , "maskable": True , "maskzable": True  } ,
	"rshift":  { "proto": protos["ret_reg_2args_reg_val"       ], "datatypes": all_int                , "horizontal": False , "maskable": True , "maskzable": True  } ,
	"lshift":  { "proto": protos["ret_reg_2args_reg_val"       ], "datatypes": all_int                , "horizontal": False , "maskable": True , "maskzable": True  } ,
}

copy_mipp_funcs = copy.deepcopy(mipp_funcs)
