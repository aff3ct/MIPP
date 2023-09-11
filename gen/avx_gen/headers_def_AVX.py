from tools import *

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
	"ret_reg_2args_ptr_reg": {
		"ret" :
			{"type": "reg", "charac": "WO", "fixeddatatype": False},
		"args" : [
			{"type": "ptr", "charac": "WO", "fixeddatatype": False},
			{"type": "reg", "charac": "RO", "fixeddatatype": False}
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
	"ret_val_1arg_reg": {
		"ret" :
			{"type": "val", "charac": "WO", "fixeddatatype": False},
		"args" : [
			{"type": "reg", "charac": "RO", "fixeddatatype": False},
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

mipp_funcs = {
    "cast":    { "proto": protos["ret_reg_1arg_reg"            ], "datatypes": all_datatypes_cart_prod, "horizontal": False },
	"cast_k":  { "proto": protos["ret_msk_1arg_msk"            ], "datatypes": all_datatypes_cart_prod, "horizontal": False },
	"toreg":   { "proto": protos["ret_reg_1arg_msk"            ], "datatypes": all_datatypes          , "horizontal": False },
	"tomsk":   { "proto": protos["ret_msk_1arg_reg"            ], "datatypes": all_datatypes          , "horizontal": False },
	"load":    { "proto": protos["ret_reg_1arg_ptr"            ], "datatypes": all_datatypes          , "horizontal": False },
	"loadu":   { "proto": protos["ret_reg_1arg_ptr"            ], "datatypes": all_datatypes          , "horizontal": False },
	"store":   { "proto": protos["ret_void_2args_ptr_reg"      ], "datatypes": all_datatypes          , "horizontal": False },
	"storeu":  { "proto": protos["ret_void_2args_ptr_reg"      ], "datatypes": all_datatypes          , "horizontal": False },
	"set" :    { "proto": protos["ret_reg_1arg_Nele"           ], "datatypes": all_datatypes          , "horizontal": True },
	"set_k" :  { "proto": protos["ret_msk_1arg_Nele"           ], "datatypes": all_datatypes          , "horizontal": False },	
	"set1":    { "proto": protos["ret_reg_1arg_val"            ], "datatypes": all_datatypes          , "horizontal": False },
	"maskzld": { "proto": protos["ret_reg_2args_msk_ptr"       ], "datatypes": all_datatypes          , "horizontal": False },
	"maskst":  { "proto": protos["ret_void_3args_ptr_msk_reg"  ], "datatypes": all_datatypes          , "horizontal": False },
	"set0":    { "proto": protos["ret_reg_0arg"                ], "datatypes": all_datatypes          , "horizontal": False },
	"set0_k":  { "proto": protos["ret_msk_0arg"                ], "datatypes": all_datatypes          , "horizontal": False },
	"get":     { "proto": protos["ret_val_2args_reg_val"       ], "datatypes": all_datatypes          , "horizontal": True  },
	"getfirst":{ "proto": protos["ret_val_1arg_reg"            ], "datatypes": all_datatypes          , "horizontal": True  },
	"gather_seq":{ "proto": protos["ret_reg_2args_ptr_reg"     ], "datatypes": all_int_uint          , "horizontal": False  },
	"sqrt":    { "proto": protos["ret_reg_1arg_reg"            ], "datatypes": all_float              , "horizontal": False },
	"rsqrt":   { "proto": protos["ret_reg_1arg_reg"            ], "datatypes": all_float              , "horizontal": False },
	"add":     { "proto": protos["ret_reg_2args_reg"           ], "datatypes": all_datatypes          , "horizontal": False },
	"sub":     { "proto": protos["ret_reg_2args_reg"           ], "datatypes": all_datatypes          , "horizontal": False },
	"mul":     { "proto": protos["ret_reg_2args_reg"           ], "datatypes": all_datatypes          , "horizontal": False },
	"div":     { "proto": protos["ret_reg_2args_reg"           ], "datatypes": all_float              , "horizontal": False },
	"min":     { "proto": protos["ret_reg_2args_reg"           ], "datatypes": all_datatypes          , "horizontal": False },
	"max":     { "proto": protos["ret_reg_2args_reg"           ], "datatypes": all_datatypes          , "horizontal": False },
	"fmadd":   { "proto": protos["ret_reg_3args_reg"           ], "datatypes": all_float              , "horizontal": False },
	"fmsub":   { "proto": protos["ret_reg_3args_reg"           ], "datatypes": all_float              , "horizontal": False },
	"andb":    { "proto": protos["ret_reg_2args_reg"           ], "datatypes": all_datatypes          , "horizontal": False },
	"andb_k":  { "proto": protos["ret_msk_2args_msk"           ], "datatypes": all_datatypes          , "horizontal": False },
	"andnb":   { "proto": protos["ret_reg_2args_reg"           ], "datatypes": all_datatypes          , "horizontal": False },
	"andnb_k": { "proto": protos["ret_msk_2args_msk"           ], "datatypes": all_datatypes          , "horizontal": False },
	"orb":     { "proto": protos["ret_reg_2args_reg"           ], "datatypes": all_datatypes          , "horizontal": False },
	"orb_k":   { "proto": protos["ret_msk_2args_msk"           ], "datatypes": all_datatypes          , "horizontal": False },
	"xorb":    { "proto": protos["ret_reg_2args_reg"           ], "datatypes": all_datatypes          , "horizontal": False },
	"xorb_k":  { "proto": protos["ret_msk_2args_msk"           ], "datatypes": all_datatypes          , "horizontal": False },
	"msb":     { "proto": protos["ret_reg_1arg_reg"            ], "datatypes": all_datatypes          , "horizontal": False },
	"notb":    { "proto": protos["ret_reg_1arg_reg"            ], "datatypes": all_datatypes          , "horizontal": False },
	"notb_k":  { "proto": protos["ret_msk_1arg_msk"            ], "datatypes": all_datatypes          , "horizontal": False },
	"cmpeq":   { "proto": protos["ret_msk_2args_reg"           ], "datatypes": all_datatypes          , "horizontal": False },
	"cmpneq":  { "proto": protos["ret_msk_2args_reg"           ], "datatypes": all_datatypes          , "horizontal": False },
    "cmplt":   { "proto": protos["ret_msk_2args_reg"           ], "datatypes": all_datatypes          , "horizontal": False },
	"cmple":   { "proto": protos["ret_msk_2args_reg"           ], "datatypes": all_datatypes          , "horizontal": False },
	"cmpge":   { "proto": protos["ret_msk_2args_reg"           ], "datatypes": all_datatypes          , "horizontal": False },
	"cmpgt":   { "proto": protos["ret_msk_2args_reg"           ], "datatypes": all_datatypes          , "horizontal": False },
	"round":   { "proto": protos["ret_val_1arg_reg"            ], "datatypes": all_datatypes          , "horizontal": False },
	"blend":   { "proto": protos["ret_reg_3args_2reg_1msk"     ], "datatypes": all_datatypes          , "horizontal": False },
	"testz":   { "proto": protos["ret_i32_2args_msk"           ], "datatypes": all_datatypes          , "horizontal": True  },
	"testz_2": { "proto": protos["ret_i32_1arg_msk"            ], "datatypes": all_datatypes          , "horizontal": True  },
	"hadd":    { "proto": protos["ret_reg_1arg_reg"            ], "datatypes": all_datatypes          , "horizontal": True  },
	"hmul":    { "proto": protos["ret_reg_1arg_reg"            ], "datatypes": all_datatypes          , "horizontal": True  },
	"hmin":    { "proto": protos["ret_reg_1arg_reg"            ], "datatypes": all_datatypes          , "horizontal": True  },
	"hmax":    { "proto": protos["ret_reg_1arg_reg"            ], "datatypes": all_datatypes          , "horizontal": True  },
}
