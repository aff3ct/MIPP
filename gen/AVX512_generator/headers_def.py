from tools import *

protos = {
	"ret_reg_1arg_ptr": {
		"ret" :
			{"type": "reg", "charac": "WO", "fixeddatatype": False},
		"args" : [
			{"type": "ptr", "charac": "RO", "fixeddatatype": False}
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
	"ret_reg_1arg_val": {
		"ret" :
			{"type": "reg", "charac": "WO", "fixeddatatype": False},
		"args" : [
			{"type": "val", "charac": "RO", "fixeddatatype": False}
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
	"ret_i32_0arg_msk": {
		"ret" :
			{"type": "val", "charac": "WO", "fixeddatatype": int32},
		"args" : []
	},
	"ret_msk_0arg_msk": {
		"ret" :
			{"type": "msk", "charac": "WO", "fixeddatatype": False},
		"args" : []
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

mipp_funcs = {
	"cast"     : { "proto": protos["ret_reg_1arg_reg"            ], "datatypes": all_datatypes_cart_prod, "horizontal": False },
	"cast_k"   : { "proto": protos["ret_msk_1arg_msk"            ], "datatypes": all_datatypes_cart_prod, "horizontal": False },
	"toreg"    : { "proto": protos["ret_reg_1arg_msk"            ], "datatypes": all_datatypes          , "horizontal": False },
	"tomsk"    : { "proto": protos["ret_msk_1arg_reg"            ], "datatypes": all_datatypes          , "horizontal": False },
	"load"     : { "proto": protos["ret_reg_1arg_ptr"            ], "datatypes": all_datatypes          , "horizontal": False },
	"loadu"    : { "proto": protos["ret_reg_1arg_ptr"            ], "datatypes": all_datatypes          , "horizontal": False },
	"store"    : { "proto": protos["ret_void_2args_ptr_reg"      ], "datatypes": all_datatypes          , "horizontal": False },
	"storeu"   : { "proto": protos["ret_void_2args_ptr_reg"      ], "datatypes": all_datatypes          , "horizontal": False },
	"getfirst" : { "proto": protos["ret_val_1arg_reg"            ], "datatypes": all_float              , "horizontal": True  },
	"set"      : { "proto": protos["ret_reg_1arg_val"            ], "datatypes": all_datatypes          , "horizontal": False },	
	"set_k"    : { "proto": protos["ret_reg_1arg_val"            ], "datatypes": all_int                , "horizontal": False },		
	"set1"     : { "proto": protos["ret_reg_1arg_val"            ], "datatypes": all_datatypes          , "horizontal": False },
	"set1_k"   : { "proto": protos["ret_msk_0arg"                ], "datatypes": all_datatypes          , "horizontal": False },
	"set0"     : { "proto": protos["ret_reg_0arg"                ], "datatypes": all_datatypes          , "horizontal": False },
	"set0_k"   : { "proto": protos["ret_msk_0arg_msk"            ], "datatypes": all_datatypes          , "horizontal": False },
	"set0_mk"  : { "proto": protos["ret_msk_0arg_msk"            ], "datatypes": all_float+[int32]      , "horizontal": False },
	"low"      : { "proto": protos["ret_val_1arg_reg"            ], "datatypes": all_float+[int64 , int32 , int16 , int8]      , "horizontal": True  },
	"high"     : { "proto": protos["ret_val_1arg_reg"            ], "datatypes": all_float+[int64 , int32 , int16 , int8]      , "horizontal": True  },
	"sqrt"     : { "proto": protos["ret_reg_1arg_reg"            ], "datatypes": all_float              , "horizontal": False },
	"rsqrt"    : { "proto": protos["ret_reg_1arg_reg"            ], "datatypes": [float32]              , "horizontal": False },
	"add"      : { "proto": protos["ret_reg_2args_reg"           ], "datatypes": all_datatypes          , "horizontal": False },
	"sub"      : { "proto": protos["ret_reg_2args_reg"           ], "datatypes": all_float+[int64, int32,int16, int8]          , "horizontal": False },
	"mul"      : { "proto": protos["ret_reg_2args_reg"           ], "datatypes": all_float+[int32,int16], "horizontal": False },
	"div"      : { "proto": protos["ret_reg_2args_reg"           ], "datatypes": all_float              , "horizontal": False },
	"min"      : { "proto": protos["ret_reg_2args_reg"           ], "datatypes": all_float+[int64,int32,int16 ,int8]           , "horizontal": False },
	"max"      : { "proto": protos["ret_reg_2args_reg"           ], "datatypes": all_float+[int64,int32,int16 ,int8]           , "horizontal": False },
	"fmadd"    : { "proto": protos["ret_reg_3args_reg"           ], "datatypes": all_float+[int32]      , "horizontal": False },
	"fmsub"    : { "proto": protos["ret_reg_3args_reg"           ], "datatypes": all_float+[int32]      , "horizontal": False },
	"andb"     : { "proto": protos["ret_reg_2args_reg"           ], "datatypes": all_datatypes          , "horizontal": False },
	"andb_k"   : { "proto": protos["ret_msk_2args_msk"           ], "datatypes": all_float+[int8, int16], "horizontal": False },
	"andnb"    : { "proto": protos["ret_reg_2args_reg"           ], "datatypes": all_datatypes          , "horizontal": False },
	"andnb_k"  : { "proto": protos["ret_msk_2args_msk"           ], "datatypes": all_float+[int8, int16], "horizontal": False },
	"orb"      : { "proto": protos["ret_reg_2args_reg"           ], "datatypes": all_datatypes          , "horizontal": False },
	"orb_k"    : { "proto": protos["ret_msk_2args_msk"           ], "datatypes": all_datatypes          , "horizontal": False },
	"xorb"     : { "proto": protos["ret_reg_2args_reg"           ], "datatypes": all_datatypes          , "horizontal": False },
	"xorb_k"   : { "proto": protos["ret_msk_2args_msk"           ], "datatypes": all_datatypes          , "horizontal": False },
	"msb"      : { "proto": protos["ret_reg_1arg_reg"            ], "datatypes": all_datatypes          , "horizontal": False },
	"notb"     : { "proto": protos["ret_reg_1arg_reg"            ], "datatypes": all_datatypes          , "horizontal": False },
	"notb_k"   : { "proto": protos["ret_msk_1arg_msk"            ], "datatypes": all_datatypes          , "horizontal": False },
	"cmpeq"    : { "proto": protos["ret_msk_2args_reg"           ], "datatypes": all_datatypes          , "horizontal": False },
	"cmpneq"   : { "proto": protos["ret_msk_2args_reg"           ], "datatypes": all_datatypes          , "horizontal": False },
	"cmplt"    : { "proto": protos["ret_msk_2args_reg"           ], "datatypes": all_datatypes          , "horizontal": False },
	"cmple"    : { "proto": protos["ret_msk_2args_reg"           ], "datatypes": all_datatypes          , "horizontal": False },
	"cmpge"    : { "proto": protos["ret_msk_2args_reg"           ], "datatypes": all_datatypes          , "horizontal": False },
	"cmpgt"    : { "proto": protos["ret_msk_2args_reg"           ], "datatypes": all_datatypes          , "horizontal": False },
	"round"    : { "proto": protos["ret_val_1arg_reg"            ], "datatypes": all_float              , "horizontal": False },
	"blend"    : { "proto": protos["ret_reg_3args_2reg_1msk"     ], "datatypes": all_datatypes          , "horizontal": False },
	"testz"    : { "proto": protos["ret_i32_2args_msk"            ], "datatypes": all_int_uint           , "horizontal": True  },
	"testz"    : { "proto": protos["ret_i32_1arg_msk"            ], "datatypes": all_int_uint           , "horizontal": True  },
	"testz_2"  : { "proto": protos["ret_i32_2args_msk"           ], "datatypes": all_int_uint           , "horizontal": True  },
	"hadd"     : { "proto": protos["ret_reg_1arg_reg"            ], "datatypes": all_datatypes          , "horizontal": True  },
	"hmul"     : { "proto": protos["ret_reg_1arg_reg"            ], "datatypes": all_float+[int32,int16], "horizontal": True  },
	"hmin"     : { "proto": protos["ret_reg_1arg_reg"            ], "datatypes": all_datatypes          , "horizontal": True  },
	"hmax"     : { "proto": protos["ret_reg_1arg_reg"            ], "datatypes": all_datatypes          , "horizontal": True  },
}