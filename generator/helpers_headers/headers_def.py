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

class MaskSupport:
	def __init__(self, maskable=False, maskzable=False, masksable=False):
		self.maskable = maskable
		self.maskzable = maskzable
		self.masksable = masksable
	
	def is_maskable(self):
		return self.maskable
	def is_maskzable(self):
		return self.maskzable
   
	def is_masksable(self):
		return self.masksable

	def is_any_mask(self):
		return self.maskable or self.maskzable or self.masksable

only_maskz = MaskSupport(maskable=False, maskzable=True, masksable=False)
only_mask = MaskSupport(maskable=True, maskzable=False, masksable=False)
only_masks = MaskSupport(maskable=False, maskzable=False, masksable=True)
mask_and_maskz = MaskSupport(maskable=True, maskzable=True, masksable=False)
mask_and_masks = MaskSupport(maskable=True, maskzable=False, masksable=True)
maskz_and_masks = MaskSupport(maskable=False, maskzable=True, masksable=True)
all_mask = MaskSupport(maskable=True, maskzable=True, masksable=True)
no_mask = MaskSupport(maskable=False, maskzable=False, masksable=False)

mipp_funcs = {
    "cast":    { "proto": protos["ret_reg_1arg_reg"            ], "datatypes": all_datatypes_cart_prod, "horizontal": False , "mask_support" : no_mask} ,
	"cast_k":  { "proto": protos["ret_msk_1arg_msk"            ], "datatypes": all_datatypes_cart_prod, "horizontal": False , "mask_support" : no_mask} ,
	"toreg":   { "proto": protos["ret_reg_1arg_msk"            ], "datatypes": all_datatypes          , "horizontal": False , "mask_support" : no_mask} ,
	"tomsk":   { "proto": protos["ret_msk_1arg_reg"            ], "datatypes": all_datatypes          , "horizontal": False , "mask_support" : no_mask} ,
	"load":    { "proto": protos["ret_reg_1arg_ptr"            ], "datatypes": all_datatypes          , "horizontal": False , "mask_support" : all_mask},
	"loadu":   { "proto": protos["ret_reg_1arg_ptr"            ], "datatypes": all_datatypes          , "horizontal": False , "mask_support" : all_mask} ,
	"store":   { "proto": protos["ret_void_2args_ptr_reg"      ], "datatypes": all_datatypes          , "horizontal": False , "mask_support" : mask_and_maskz} ,
	"storeu":  { "proto": protos["ret_void_2args_ptr_reg"      ], "datatypes": all_datatypes          , "horizontal": False , "mask_support" : mask_and_maskz} ,
	"set" :    { "proto": protos["ret_reg_1arg_Nele"           ], "datatypes": all_datatypes          , "horizontal": True  , "mask_support" : only_masks} ,
	"set_k" :  { "proto": protos["ret_msk_1arg_Nele"           ], "datatypes": all_datatypes          , "horizontal": False , "mask_support" : no_mask} ,
	"set1":    { "proto": protos["ret_reg_1arg_val"            ], "datatypes": all_datatypes          , "horizontal": False , "mask_support" : only_masks} ,
	"set1_k":  { "proto": protos["ret_msk_1arg_i32"            ], "datatypes": all_datatypes          , "horizontal": False , "mask_support" : no_mask} ,
	"maskzld": { "proto": protos["ret_reg_2args_msk_ptr"       ], "datatypes": all_datatypes          , "horizontal": False , "mask_support" : no_mask} ,
	"maskst":  { "proto": protos["ret_void_3args_ptr_msk_reg"  ], "datatypes": all_datatypes          , "horizontal": False , "mask_support" : no_mask} ,
	"set0":    { "proto": protos["ret_reg_0arg"                ], "datatypes": all_datatypes          , "horizontal": False , "mask_support" : only_masks} ,
	#"low_k":   { "proto": protos["ret_msk_0arg"                ], "datatypes": all_datatypes          , "horizontal": False },
	"get":     { "proto": protos["ret_val_2args_reg_val"       ], "datatypes": all_datatypes          , "horizontal": True  , "mask_support" : no_mask} ,
	"get_k":   { "proto": protos["ret_val_2args_msk_val"       ], "datatypes": all_datatypes          , "horizontal": True  , "mask_support" : no_mask} ,
	"getfirst":{ "proto": protos["ret_val_1arg_reg"            ], "datatypes": all_datatypes          , "horizontal": True  , "mask_support" : no_mask} ,
	#"gather"  :{ "proto": protos["ret_reg_2args_ptr_vindex"    ], "datatypes": all_datatypes          , "horizontal": False  },
	#"mask_gather":{ "proto": protos["ret_reg_3args_ptr_vindex_msk" ], "datatypes": all_datatypes          , "horizontal": False  },
	"sqrt":    { "proto": protos["ret_reg_1arg_reg"            ], "datatypes": all_float              , "horizontal": False , "mask_support" : all_mask} ,
	"rsqrt":   { "proto": protos["ret_reg_1arg_reg"            ], "datatypes": all_float              , "horizontal": False , "mask_support" : all_mask} ,
	"add":     { "proto": protos["ret_reg_2args_reg"           ], "datatypes": all_datatypes          , "horizontal": False , "mask_support" : all_mask} ,
	"sub":     { "proto": protos["ret_reg_2args_reg"           ], "datatypes": all_datatypes          , "horizontal": False , "mask_support" : all_mask} ,
	"mul":     { "proto": protos["ret_reg_2args_reg"           ], "datatypes": all_datatypes          , "horizontal": False , "mask_support" : all_mask} ,
	"div":     { "proto": protos["ret_reg_2args_reg"           ], "datatypes": all_float              , "horizontal": False , "mask_support" : all_mask} ,
	"min":     { "proto": protos["ret_reg_2args_reg"           ], "datatypes": all_datatypes          , "horizontal": False , "mask_support" : all_mask} ,
	"max":     { "proto": protos["ret_reg_2args_reg"           ], "datatypes": all_datatypes          , "horizontal": False , "mask_support" : all_mask} ,
	"fmadd":   { "proto": protos["ret_reg_3args_reg"           ], "datatypes": all_float+[int32]      , "horizontal": False , "mask_support" : all_mask} ,
	"fmsub":   { "proto": protos["ret_reg_3args_reg"           ], "datatypes": all_float+[int32]      , "horizontal": False , "mask_support" : all_mask} ,
	"andb":    { "proto": protos["ret_reg_2args_reg"           ], "datatypes": all_datatypes          , "horizontal": False , "mask_support" : all_mask} ,
	"andb_k":  { "proto": protos["ret_msk_2args_msk"           ], "datatypes": all_datatypes          , "horizontal": False ,  "mask_support" : no_mask} ,
	"andnb":   { "proto": protos["ret_reg_2args_reg"           ], "datatypes": all_datatypes          , "horizontal": False , "mask_support" : all_mask} ,
	"andnb_k": { "proto": protos["ret_msk_2args_msk"           ], "datatypes": all_datatypes          , "horizontal": False , "mask_support" : no_mask} ,
	"orb":     { "proto": protos["ret_reg_2args_reg"           ], "datatypes": all_datatypes          , "horizontal": False , "mask_support" : all_mask} ,
	"orb_k":   { "proto": protos["ret_msk_2args_msk"           ], "datatypes": all_datatypes          , "horizontal": False , "mask_support" : no_mask} ,
	"xorb":    { "proto": protos["ret_reg_2args_reg"           ], "datatypes": all_datatypes          , "horizontal": False , "mask_support" : all_mask} ,
	"xorb_k":  { "proto": protos["ret_msk_2args_msk"           ], "datatypes": all_datatypes          , "horizontal": False , "mask_support" : no_mask} ,
	"msb":     { "proto": protos["ret_reg_1arg_reg"            ], "datatypes": all_datatypes          , "horizontal": False , "mask_support" : all_mask} ,
	"notb":    { "proto": protos["ret_reg_1arg_reg"            ], "datatypes": all_datatypes          , "horizontal": False , "mask_support" : all_mask} ,
	"notb_k":  { "proto": protos["ret_msk_1arg_msk"            ], "datatypes": all_datatypes          , "horizontal": False , "mask_support" : no_mask} ,
	"cmpeq":   { "proto": protos["ret_msk_2args_reg"           ], "datatypes": all_datatypes          , "horizontal": False , "mask_support" : all_mask} ,
	"cmpneq":  { "proto": protos["ret_msk_2args_reg"           ], "datatypes": all_datatypes          , "horizontal": False , "mask_support" : all_mask} ,
    "cmplt":   { "proto": protos["ret_msk_2args_reg"           ], "datatypes": all_datatypes          , "horizontal": False , "mask_support" : all_mask} ,
	"cmple":   { "proto": protos["ret_msk_2args_reg"           ], "datatypes": all_datatypes          , "horizontal": False , "mask_support" : all_mask} ,
	"cmpge":   { "proto": protos["ret_msk_2args_reg"           ], "datatypes": all_datatypes          , "horizontal": False , "mask_support" : all_mask} ,
	"cmpgt":   { "proto": protos["ret_msk_2args_reg"           ], "datatypes": all_datatypes          , "horizontal": False , "mask_support" : all_mask} ,
	"round":   { "proto": protos["ret_reg_1arg_reg"            ], "datatypes": all_datatypes          , "horizontal": False , "mask_support" : all_mask} ,
	"blend":   { "proto": protos["ret_reg_3args_2reg_1msk"     ], "datatypes": all_datatypes          , "horizontal": False , "mask_support" : no_mask} ,
	"set0_k":  { "proto": protos["ret_msk_0arg"                ], "datatypes": all_datatypes          , "horizontal": False , "mask_support" : no_mask} ,
	"testz":   { "proto": protos["ret_i32_2args_msk"           ], "datatypes": all_datatypes          , "horizontal": True  , "mask_support" : no_mask} ,
	"testz_2": { "proto": protos["ret_i32_1arg_msk"            ], "datatypes": all_datatypes          , "horizontal": True  , "mask_support" : no_mask} ,
	"hadd":    { "proto": protos["ret_reg_1arg_reg"            ], "datatypes": all_datatypes          , "horizontal": True  , "mask_support" : only_mask} ,
	"hmul":    { "proto": protos["ret_reg_1arg_reg"            ], "datatypes": all_datatypes          , "horizontal": True  , "mask_support" : only_mask} ,
	"hmin":    { "proto": protos["ret_reg_1arg_reg"            ], "datatypes": all_datatypes          , "horizontal": True  , "mask_support" : only_mask} ,
	"hmax":    { "proto": protos["ret_reg_1arg_reg"            ], "datatypes": all_datatypes          , "horizontal": True  , "mask_support" : only_mask} ,
	"hadd_to_scal":{ "proto": protos["ret_val_1arg_reg"        ], "datatypes": all_datatypes          , "horizontal": True  , "mask_support" : only_mask},
	#"hmul_to_scal":    { "proto": protos["ret_val_1arg_reg"            ], "datatypes": all_datatypes          , "horizontal": True  },
	#"hmin_to_scal":    { "proto": protos["ret_val_1arg_reg"            ], "datatypes": all_datatypes          , "horizontal": True  },
	#"hmax_to_scal":    { "proto": protos["ret_val_1arg_reg"            ], "datatypes": all_datatypes          , "horizontal": True  },
	"maskz_add":{ "proto": protos["ret_reg_3args_1msk_2reg" ], "datatypes": all_datatypes          , "horizontal": True  , "mask_support" : no_mask} ,
	"fnmadd":  { "proto": protos["ret_reg_3args_reg"           ], "datatypes": all_float+[int32]      , "horizontal": False , "mask_support": all_mask} ,
	"fnmsub":  { "proto": protos["ret_reg_3args_reg"           ], "datatypes": all_float+[int32]      , "horizontal": False , "mask_support": all_mask} ,
	"div2":    { "proto": protos["ret_reg_1arg_reg"            ], "datatypes": all_float              , "horizontal": False , "mask_support": all_mask} ,
	"div4":	   { "proto": protos["ret_reg_1arg_reg"            ], "datatypes": all_float              , "horizontal": False , "mask_support": all_mask} ,
	"rshift":  { "proto": protos["ret_reg_2args_reg_val"       ], "datatypes": all_int                , "horizontal": False , "mask_support": all_mask} ,
	"lshift":  { "proto": protos["ret_reg_2args_reg_val"       ], "datatypes": all_int                , "horizontal": False , "mask_support": all_mask} ,
}

copy_mipp_funcs = copy.deepcopy(mipp_funcs)
