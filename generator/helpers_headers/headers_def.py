from tools import *
import copy

"""
"protos" dictionary:
    - Defines prototypes of SIMD functions presented in a dictionary.
    - Each prototype is defined with a key representing a specific function model.
    - For each model, specifications for the return type and arguments are provided.
    - Details include the type ("reg" for register , "msk" to designate masks, "r" , "val" for values, "ptr" for pointers and "Nele" for number of elements).
    - The attribute (such as "WO" for Write Only or "RO" for Read Only)
    - "fixeddatatype" is defined as a Boolean value, thus determining whether a variation in data type is allowed or not.
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
    def is_none(self):
        return not self.is_any_mask()

only_maskz = MaskSupport(maskable=False, maskzable=True, masksable=False)
only_mask = MaskSupport(maskable=True, maskzable=False, masksable=False)
only_masks = MaskSupport(maskable=False, maskzable=False, masksable=True)
mask_and_maskz = MaskSupport(maskable=True, maskzable=True, masksable=False)
mask_and_masks = MaskSupport(maskable=True, maskzable=False, masksable=True)
maskz_and_masks = MaskSupport(maskable=False, maskzable=True, masksable=True)
all_mask = MaskSupport(maskable=True, maskzable=True, masksable=True)
no_mask = MaskSupport(maskable=False, maskzable=False, masksable=False)

"""
    "mipp_funcs" dictionary: contains different MIPP functions for all the SIMD extension, it is the MIPP interface.
    - Each function is associated with a prototype model based on its key in the "protos" dictionary, with the data types
     (for which the function is to be generated are specified, along with other parameters such as the parameters such as the "horizontal" flag
"""
mipp_funcs = {
    "cast":         { "proto": protos["ret_reg_1arg_reg"],             "datatypes": all_datatypes_cart_prod, "horizontal": False, "mask_support": no_mask        },
    "cast_k":       { "proto": protos["ret_msk_1arg_msk"],             "datatypes": all_datatypes_cart_prod, "horizontal": False, "mask_support": no_mask        },
    "toreg":        { "proto": protos["ret_reg_1arg_msk"],             "datatypes": all_datatypes,           "horizontal": False, "mask_support": no_mask        },
    "tomsk":        { "proto": protos["ret_msk_1arg_reg"],             "datatypes": all_datatypes,           "horizontal": False, "mask_support": no_mask        },
    "load":         { "proto": protos["ret_reg_1arg_ptr"],             "datatypes": all_datatypes,           "horizontal": False, "mask_support": all_mask       },
    "loadu":        { "proto": protos["ret_reg_1arg_ptr"],             "datatypes": all_datatypes,           "horizontal": False, "mask_support": all_mask       },
    "store":        { "proto": protos["ret_void_2args_ptr_reg"],       "datatypes": all_datatypes,           "horizontal": False, "mask_support": mask_and_maskz },
    "storeu":       { "proto": protos["ret_void_2args_ptr_reg"],       "datatypes": all_datatypes,           "horizontal": False, "mask_support": mask_and_maskz },
    "set":          { "proto": protos["ret_reg_1arg_Nele"],            "datatypes": all_datatypes,           "horizontal": True,  "mask_support": only_masks     },
    "set_k":        { "proto": protos["ret_msk_1arg_Nele"],            "datatypes": all_datatypes,           "horizontal": False, "mask_support": no_mask        },
    "set1":         { "proto": protos["ret_reg_1arg_val"],             "datatypes": all_datatypes,           "horizontal": False, "mask_support": only_masks     },
    "set1_k":       { "proto": protos["ret_msk_1arg_i32"],             "datatypes": all_datatypes,           "horizontal": False, "mask_support": no_mask        },
    "maskzld":      { "proto": protos["ret_reg_2args_msk_ptr"],        "datatypes": all_32bit+all_64bit,     "horizontal": False, "mask_support": no_mask        },
    "maskst":       { "proto": protos["ret_void_3args_ptr_msk_reg"],   "datatypes": all_32bit+all_64bit,     "horizontal": False, "mask_support": no_mask        },
    "set0":         { "proto": protos["ret_reg_0arg"],                 "datatypes": all_datatypes,           "horizontal": False, "mask_support": only_masks     },
#   "low_k":        { "proto": protos["ret_msk_0arg"],                 "datatypes": all_datatypes,           "horizontal": False                                 },
    "get":          { "proto": protos["ret_val_2args_reg_val"],        "datatypes": all_datatypes,           "horizontal": True,  "mask_support": no_mask        },
    "get_k":        { "proto": protos["ret_val_2args_msk_val"],        "datatypes": all_datatypes,           "horizontal": True,  "mask_support": no_mask        },
    "getfirst":     { "proto": protos["ret_val_1arg_reg"],             "datatypes": all_datatypes,           "horizontal": True,  "mask_support": no_mask        },
#   "gather":       { "proto": protos["ret_reg_2args_ptr_vindex"],     "datatypes": all_datatypes,           "horizontal": False                                 },
#   "mask_gather":  { "proto": protos["ret_reg_3args_ptr_vindex_msk"], "datatypes": all_datatypes,           "horizontal": False                                 },
    "sqrt":         { "proto": protos["ret_reg_1arg_reg"],             "datatypes": all_float,               "horizontal": False, "mask_support": all_mask       },
    "rsqrt":        { "proto": protos["ret_reg_1arg_reg"],             "datatypes": all_float,               "horizontal": False, "mask_support": all_mask       },
    "add":          { "proto": protos["ret_reg_2args_reg"],            "datatypes": all_datatypes,           "horizontal": False, "mask_support": all_mask       },
    "sub":          { "proto": protos["ret_reg_2args_reg"],            "datatypes": all_datatypes,           "horizontal": False, "mask_support": all_mask       },
    "mul":          { "proto": protos["ret_reg_2args_reg"],            "datatypes": all_datatypes,           "horizontal": False, "mask_support": all_mask       },
    "div":          { "proto": protos["ret_reg_2args_reg"],            "datatypes": all_float,               "horizontal": False, "mask_support": all_mask       },
    "min":          { "proto": protos["ret_reg_2args_reg"],            "datatypes": all_datatypes,           "horizontal": False, "mask_support": all_mask       },
    "max":          { "proto": protos["ret_reg_2args_reg"],            "datatypes": all_datatypes,           "horizontal": False, "mask_support": all_mask       },
    "fmadd":        { "proto": protos["ret_reg_3args_reg"],            "datatypes": all_float+[int32],       "horizontal": False, "mask_support": all_mask       },
    "fmsub":        { "proto": protos["ret_reg_3args_reg"],            "datatypes": all_float+[int32],       "horizontal": False, "mask_support": all_mask       },
    "andb":         { "proto": protos["ret_reg_2args_reg"],            "datatypes": all_datatypes,           "horizontal": False, "mask_support": all_mask       },
    "andb_k":       { "proto": protos["ret_msk_2args_msk"],            "datatypes": all_datatypes,           "horizontal": False, "mask_support": no_mask        },
    "andnb":        { "proto": protos["ret_reg_2args_reg"],            "datatypes": all_datatypes,           "horizontal": False, "mask_support": all_mask       },
    "andnb_k":      { "proto": protos["ret_msk_2args_msk"],            "datatypes": all_datatypes,           "horizontal": False, "mask_support": no_mask        },
    "orb":          { "proto": protos["ret_reg_2args_reg"],            "datatypes": all_datatypes,           "horizontal": False, "mask_support": all_mask       },
    "orb_k":        { "proto": protos["ret_msk_2args_msk"],            "datatypes": all_datatypes,           "horizontal": False, "mask_support": no_mask        },
    "xorb":         { "proto": protos["ret_reg_2args_reg"],            "datatypes": all_datatypes,           "horizontal": False, "mask_support": all_mask       },
    "xorb_k":       { "proto": protos["ret_msk_2args_msk"],            "datatypes": all_datatypes,           "horizontal": False, "mask_support": no_mask        },
    "msb":          { "proto": protos["ret_reg_1arg_reg"],             "datatypes": all_datatypes,           "horizontal": False, "mask_support": all_mask       },
    "notb":         { "proto": protos["ret_reg_1arg_reg"],             "datatypes": all_datatypes,           "horizontal": False, "mask_support": all_mask       },
    "notb_k":       { "proto": protos["ret_msk_1arg_msk"],             "datatypes": all_datatypes,           "horizontal": False, "mask_support": no_mask        },
    "cmpeq":        { "proto": protos["ret_msk_2args_reg"],            "datatypes": all_datatypes,           "horizontal": False, "mask_support": all_mask       },
    "cmpneq":       { "proto": protos["ret_msk_2args_reg"],            "datatypes": all_datatypes,           "horizontal": False, "mask_support": all_mask       },
    "cmplt":        { "proto": protos["ret_msk_2args_reg"],            "datatypes": all_datatypes,           "horizontal": False, "mask_support": all_mask       },
    "cmple":        { "proto": protos["ret_msk_2args_reg"],            "datatypes": all_datatypes,           "horizontal": False, "mask_support": all_mask       },
    "cmpge":        { "proto": protos["ret_msk_2args_reg"],            "datatypes": all_datatypes,           "horizontal": False, "mask_support": all_mask       },
    "cmpgt":        { "proto": protos["ret_msk_2args_reg"],            "datatypes": all_datatypes,           "horizontal": False, "mask_support": all_mask       },
    "round":        { "proto": protos["ret_reg_1arg_reg"],             "datatypes": all_datatypes,           "horizontal": False, "mask_support": all_mask       },
    "blend":        { "proto": protos["ret_reg_3args_2reg_1msk"],      "datatypes": all_datatypes,           "horizontal": False, "mask_support": no_mask        },
    "set0_k":       { "proto": protos["ret_msk_0arg"],                 "datatypes": all_datatypes,           "horizontal": False, "mask_support": no_mask        },
    "testz":        { "proto": protos["ret_i32_2args_msk"],            "datatypes": all_datatypes,           "horizontal": True,  "mask_support": no_mask        },
    "testz_2":      { "proto": protos["ret_i32_1arg_msk"],             "datatypes": all_datatypes,           "horizontal": True,  "mask_support": no_mask        },
    "hadd":         { "proto": protos["ret_reg_1arg_reg"],             "datatypes": all_datatypes,           "horizontal": True,  "mask_support": only_mask      },
    "hmul":         { "proto": protos["ret_reg_1arg_reg"],             "datatypes": all_datatypes,           "horizontal": True,  "mask_support": only_mask      },
    "hmin":         { "proto": protos["ret_reg_1arg_reg"],             "datatypes": all_datatypes,           "horizontal": True,  "mask_support": only_mask      },
    "hmax":         { "proto": protos["ret_reg_1arg_reg"],             "datatypes": all_datatypes,           "horizontal": True,  "mask_support": only_mask      },
    "hadd_to_scal": { "proto": protos["ret_val_1arg_reg"],             "datatypes": all_datatypes,           "horizontal": True,  "mask_support": no_mask        },
#   "hmul_to_scal": { "proto": protos["ret_val_1arg_reg"],             "datatypes": all_datatypes,           "horizontal": True                                  },
#   "hmin_to_scal": { "proto": protos["ret_val_1arg_reg"],             "datatypes": all_datatypes,           "horizontal": True                                  },
#   "hmax_to_scal": { "proto": protos["ret_val_1arg_reg"],             "datatypes": all_datatypes,           "horizontal": True                                  },
    "maskz_add":    { "proto": protos["ret_reg_3args_1msk_2reg"],      "datatypes": all_datatypes,           "horizontal": True,  "mask_support": no_mask        },
    "fnmadd":       { "proto": protos["ret_reg_3args_reg"],            "datatypes": all_float+[int32],       "horizontal": False, "mask_support": all_mask       },
    "fnmsub":       { "proto": protos["ret_reg_3args_reg"],            "datatypes": all_float+[int32],       "horizontal": False, "mask_support": all_mask       },
    "div2":         { "proto": protos["ret_reg_1arg_reg"],             "datatypes": all_datatypes,           "horizontal": False, "mask_support": all_mask       },
    "div4":         { "proto": protos["ret_reg_1arg_reg"],             "datatypes": all_datatypes,           "horizontal": False, "mask_support": all_mask       },
    "rshift":       { "proto": protos["ret_reg_2args_reg_val"],        "datatypes": all_datatypes,           "horizontal": False, "mask_support": all_mask       },
    "lshift":       { "proto": protos["ret_reg_2args_reg_val"],        "datatypes": all_datatypes,           "horizontal": False, "mask_support": all_mask       },
}

# === WARNING ===                                    === WARNING ===                                    === WARNING ===
# We need to have a distinction for:
#  - 'add' and 'adds'
#  - 'sub' and 'subs'
#  - 'hadd' and 'hadds'
#  - 'hsub' and 'hsubs'
# For int/uint on 8-bit and 16-bit. This is very important to implement well the following scalar dictionary.
# === WARNING ===                                    === WARNING ===                                    === WARNING ===

isa_scalar = {
    "name": "scalar",
    "size": "MIPP_SCALAR_SIZE",
    "hw_lmul": False,
    "architecture": "all",
    "datatypes": {
        float64: { "reg": "float64_t", "msk": "uint64_t", "to_ptr": "float64_t", },
        float32: { "reg": "float32_t", "msk": "uint32_t", "to_ptr": "float32_t", },
        int64:   { "reg": "int64_t",   "msk": "uint64_t", "to_ptr": "int64_t",   },
        int32:   { "reg": "int32_t",   "msk": "uint32_t", "to_ptr": "int32_t",   },
        int16:   { "reg": "int16_t",   "msk": "uint16_t", "to_ptr": "int16_t",   },
        int8:    { "reg": "int8_t",    "msk": "uint8_t",  "to_ptr": "int8_t",    },
        uint64:  { "reg": "uint64_t",  "msk": "uint64_t", "to_ptr": "uint64_t",  },
        uint32:  { "reg": "uint32_t",  "msk": "uint32_t", "to_ptr": "uint32_t",  },
        uint16:  { "reg": "uint16_t",  "msk": "uint16_t", "to_ptr": "uint16_t",  },
        uint8:   { "reg": "uint8_t",   "msk": "uint8_t",  "to_ptr": "uint8_t",   },
    },
}

implems_scalar = {
    "cast": [ # -------------------------------------------------------------------------------------------------- cast
        { "type": "vector-wide", "datatypes": all_defs, "implem":
"""
%r<tr>% res;

// The commented snippet code below produces "error: dereferencing type-punned pointer will break strict-aliasing rules"
// %v<tr>%* ptr = (%v<tr>%*)r0.r;
// for (size_t i = 0; i < %N<tr>%; i++)
//	res.r[i] = ptr[i];

// requires #include <string.h>
memcpy(res.r, r0.r, sizeof(%v<tr>%) * %N<tr>%); // C / C++ compilers should be able to optimize this in -O2 or -O3

return res;
"""
        },
    ],
    "cast_k": [ # ---------------------------------------------------------------------------------------------- cast_k
        { "type": "vector-wide", "datatypes": all_defs, "implem":
"""
%m<tr>% res;

// The commented snippet code below produces "error: dereferencing type-punned pointer will break strict-aliasing rules"
// {{isa_dt_ret.msk}}* ptr = ({{isa_dt_ret.msk}}*)m0.m;
// for (size_t i = 0; i < %N<tr>%; i++)
// 	res.m[i] = ptr[i];

// requires #include <string.h>
memcpy(res.m, m0.m, sizeof({{isa_dt_ret.msk}}) * %N<tr>%); // C / C++ compilers should be able to optimize this in -O2 or -O3

return res;
"""
        },
    ],
    "toreg": [ # ------------------------------------------------------------------------------------------------ toreg
        { "type": "vector-wide", "datatypes": all_defs, "implem":
"""
%r<tr>% res;

// The commented snippet code below produces "error: dereferencing type-punned pointer will break strict-aliasing rules"
// {{isa_dt_ret.reg}}* ptr = ({{isa_dt_ret.reg}}*)m0.m;
// for (size_t i = 0; i < %N<tr>%; i++)
// 	res.r[i] = ptr[i];

for (size_t i = 0; i < %N<tr>%; i++)
	// compiler should identify the following pattern: res.r[i] = std::bit_cast<{{isa_dt_ret.reg}}>(m0.m[i]);
	// requires #include <string.h>
	memcpy(&res.r[i], &m0.m[i], sizeof({{isa_dt_ret.reg}}));

return res;
"""
        },
    ],
    "tomsk": [ # ------------------------------------------------------------------------------------------------ tomsk
        { "type": "vector-wide", "datatypes": all_defs, "implem":
"""
%m<tr>% res;

// The commented snippet code below produces "error: dereferencing type-punned pointer will break strict-aliasing rules"
// {{isa_dt_ret.msk}}* ptr = ({{isa_dt_ret.msk}}*)r0.r;
// for (size_t i = 0; i < %N<tr>%; i++)
// 	res.m[i] = ptr[i];

for (size_t i = 0; i < %N<tr>%; i++)
	// compiler should identify the following pattern: res.m[i] = std::bit_cast<{{isa_dt_ret.msk}}>(r0.r[i]);
	// requires #include <string.h>
	memcpy(&res.m[i], &r0.r[i], sizeof({{isa_dt_ret.msk}}));

return res;
"""
        },
    ],
    "load": [ # -------------------------------------------------------------------------------------------------- load
        { "type": "element-wide", "datatypes": all_defs, "implem":
"""
res.r[i] = %!pred_cond!% p0[i] %!pred_alt!%;
"""
        },
    ],
    "loadu": [ # ------------------------------------------------------------------------------------------------ loadu
        { "type": "element-wide", "datatypes": all_defs, "implem":
"""
res.r[i] = %!pred_cond!% p0[i] %!pred_alt!%;
"""
        },
    ],
    "store": [ # ------------------------------------------------------------------------------------------------ store
        { "type": "element-wide", "datatypes": all_defs, "implem":
"""
p0[i] = %!pred_cond!% r0.r[i] %!pred_alt!%;
"""
        },
    ],
    "storeu": [ # ---------------------------------------------------------------------------------------------- storeu
        { "type": "element-wide", "datatypes": all_defs, "implem":
"""
p0[i] = %!pred_cond!% r0.r[i] %!pred_alt!%;
"""
        },
    ],
    "set": [ # ---------------------------------------------------------------------------------------------------- set
        { "type": "element-wide", "datatypes": all_defs, "implem":
"""
res.r[i] = %!pred_cond!% vals[i] %!pred_alt!%;
"""
        },
    ],
    "set_k": [ # ------------------------------------------------------------------------------------------------ set_k
        { "type": "element-wide", "datatypes": all_defs, "implem":
"""
%v<c:int|b:tr>% m_tmp = vals[i] ? -1 : 0;
// res.m[i] = *({{isa_dt_ret.msk}}*)((void*)(&m_tmp));
// requires #include <string.h>
memcpy(&res.m[i], &m_tmp, sizeof({{isa_dt_ret.msk}}));
"""
        },
    ],
    "set1": [ # -------------------------------------------------------------------------------------------------- set1
        { "type": "element-wide", "datatypes": all_defs, "implem":
"""
res.r[i] = %!pred_cond!% v0 %!pred_alt!%;
"""
        },
    ],
    "set1_k": [ # ---------------------------------------------------------------------------------------------- set1_k
        { "type": "vector-wide", "datatypes": all_defs, "implem":
"""
%m<tr>% res;
%v<c:int|b:tr>% m_tmp = v0 ? -1 : 0;
for (size_t i = 0; i < %N<tp>%; i++)
	// The commented snippet code below produces "error: dereferencing type-punned pointer will break strict-aliasing rules"
	// res.m[i] = *({{isa_dt_ret.msk}}*)((void*)(&m_tmp));

	// compiler should identify the following pattern: res.m[i] = std::bit_cast<{{isa_dt_ret.msk}}>(m_tmp);
	// requires #include <string.h>
	memcpy(&res.m[i], &m_tmp, sizeof({{isa_dt_ret.msk}}));
return res;
"""
        },
    ],
    "maskzld": [ # -------------------------------------------------------------------------------------------- maskzld
        { "type": "element-wide", "datatypes": all_defs, "implem":
"""
res.r[i] = m0.m[i] ? p0[i] : 0;
"""
        },
    ],
    "maskst": [ # ---------------------------------------------------------------------------------------------- maskst
        { "type": "element-wide", "datatypes": all_defs, "implem":
"""
if (m0.m[i]) p0[i] = r0.r[i];
"""
        },
    ],
    "set0": [ # -------------------------------------------------------------------------------------------------- set0
        { "type": "element-wide", "datatypes": all_defs, "implem":
"""
res.r[i] = %!pred_cond!% 0 %!pred_alt!%;
"""
        },
    ],
    "get": [ # ---------------------------------------------------------------------------------------------------- get
        { "type": "vector-wide", "datatypes": all_defs, "implem":
"""
return r0.r[v0];
"""
        },
    ],
    "get_k": [ # ------------------------------------------------------------------------------------------------ get_k
        { "type": "vector-wide", "datatypes": all_defs, "implem":
"""
return m0.m[v0];
"""
        },
    ],
    "getfirst": [ # ------------------------------------------------------------------------------------------ getfirst
        { "type": "vector-wide", "datatypes": all_defs, "implem":
"""
return r0.r[0];
"""
        },
    ],
    "sqrt": [ # -------------------------------------------------------------------------------------------------- sqrt
        { "type": "element-wide", "datatypes": [float64], "implem":
"""
// requires #include <math.h>
res.r[i] = %!pred_cond!% sqrt(r0.r[i]) %!pred_alt!%;
"""
        },
        { "type": "element-wide", "datatypes": [float32], "implem":
"""
// requires #include <math.h>
res.r[i] = %!pred_cond!% sqrtf(r0.r[i]) %!pred_alt!%;
"""
        },
    ],
    "rsqrt": [ # ------------------------------------------------------------------------------------------------ rsqrt
        { "type": "element-wide", "datatypes": [float64], "implem":
"""
// requires #include <math.h>
res.r[i] = %!pred_cond!% 1.0 / sqrt(r0.r[i]) %!pred_alt!%;
"""
        },
        { "type": "element-wide", "datatypes": [float32], "implem":
"""
// requires #include <math.h>
res.r[i] = %!pred_cond!% 1.0f / sqrtf(r0.r[i]) %!pred_alt!%;
"""
        },
    ],
    "add": [ # ---------------------------------------------------------------------------------------------------- add
        { "type": "element-wide", "datatypes": all_defs, "implem":
"""
res.r[i] = %!pred_cond!% r0.r[i] + r1.r[i] %!pred_alt!%;
"""
        },
    ],
    "sub": [ # ---------------------------------------------------------------------------------------------------- sub
        { "type": "element-wide", "datatypes": all_defs, "implem":
"""
res.r[i] = %!pred_cond!% r0.r[i] - r1.r[i] %!pred_alt!%;
"""
        },
    ],
    "mul": [ # ---------------------------------------------------------------------------------------------------- mul
        { "type": "element-wide", "datatypes": all_defs, "implem":
"""
res.r[i] = %!pred_cond!% r0.r[i] * r1.r[i] %!pred_alt!%;
"""
        },
    ],
    "div": [ # ---------------------------------------------------------------------------------------------------- div
        { "type": "element-wide", "datatypes": all_defs, "implem":
"""
res.r[i] = %!pred_cond!% r0.r[i] / r1.r[i] %!pred_alt!%;
"""
        },
    ],
    "min": [ # ---------------------------------------------------------------------------------------------------- min
        { "type": "element-wide", "datatypes": all_defs, "implem":
"""
res.r[i] = %!pred_cond!% r0.r[i] < r1.r[i] ? r0.r[i] : r1.r[i] %!pred_alt!%;
"""
        },
    ],
    "max": [ # ---------------------------------------------------------------------------------------------------- max
        { "type": "element-wide", "datatypes": all_defs, "implem":
"""
res.r[i] = %!pred_cond!% r0.r[i] > r1.r[i] ? r0.r[i] : r1.r[i] %!pred_alt!%;
"""
        },
    ],
    "fmadd": [ # ------------------------------------------------------------------------------------------------ fmadd
        { "type": "element-wide", "datatypes": all_defs, "implem":
"""
res.r[i] = %!pred_cond!% r0.r[i] * r1.r[i] + r2.r[i] %!pred_alt!%;
"""
        },
    ],
    "fmsub": [ # ------------------------------------------------------------------------------------------------ fmsub
        { "type": "element-wide", "datatypes": all_defs, "implem":
"""
res.r[i] = %!pred_cond!% r0.r[i] * r1.r[i] - r2.r[i] %!pred_alt!%;
"""
        },
    ],
    "andb": [ # -------------------------------------------------------------------------------------------------- andb
        { "type": "element-wide", "datatypes": all_int + all_uint, "implem":
"""
res.r[i] = %!pred_cond!% r0.r[i] & r1.r[i] %!pred_alt!%;
"""
        },
        { "type": "element-wide", "datatypes": all_float, "implem":
"""
// The commented snippet code below produces "error: dereferencing type-punned pointer will break strict-aliasing rules"
// %v<c:uint|b:tp>% r0i = *({{isa_dt_par.msk}}*)((void*)&r0.r[i]);
// %v<c:uint|b:tp>% r1i = *({{isa_dt_par.msk}}*)((void*)&r1.r[i]);

%v<c:uint|b:tp>% r0i, r1i;
// compiler should identify the following pattern: rxi = std::bit_cast<{{isa_dt_par.msk}}>(rx.r[i]);
// requires #include <string.h>
memcpy(&r0i, &r0.r[i], sizeof({{isa_dt_par.msk}}));
memcpy(&r1i, &r1.r[i], sizeof({{isa_dt_par.msk}}));

%v<c:uint|b:tp>% resi = r0i & r1i;

%v<tr>% resv;
// compiler should identify the following pattern: resv = std::bit_cast<{{isa_dt_ret.reg}}>(resi);
// requires #include <string.h>
memcpy(&resv, &resi, sizeof({{isa_dt_ret.reg}}));

res.r[i] = %!pred_cond!% resv %!pred_alt!%;
"""
        },
    ],
    "andb_k": [ # ---------------------------------------------------------------------------------------------- andb_k
        { "type": "element-wide", "datatypes": all_defs, "implem":
"""
res.m[i] = m0.m[i] & m1.m[i];
"""
        },
    ],
    "andnb": [ # ------------------------------------------------------------------------------------------------ andnb
        { "type": "element-wide", "datatypes": all_int + all_uint, "implem":
"""
res.r[i] = %!pred_cond!% (~r0.r[i]) & r1.r[i] %!pred_alt!%;
"""
        },
        { "type": "element-wide", "datatypes": all_float, "implem":
"""
// The commented snippet code below produces "error: dereferencing type-punned pointer will break strict-aliasing rules"
// %v<c:uint|b:tp>% r0i = *({{isa_dt_par.msk}}*)((void*)&r0.r[i]);
// %v<c:uint|b:tp>% r1i = *({{isa_dt_par.msk}}*)((void*)&r1.r[i]);

%v<c:uint|b:tp>% r0i, r1i;
// compiler should identify the following pattern: rxi = std::bit_cast<{{isa_dt_par.msk}}>(rx.r[i]);
// requires #include <string.h>
memcpy(&r0i, &r0.r[i], sizeof({{isa_dt_par.msk}}));
memcpy(&r1i, &r1.r[i], sizeof({{isa_dt_par.msk}}));

%v<c:uint|b:tp>% resi = (~r0i) & r1i;

%v<tr>% resv;
// compiler should identify the following pattern: resv = std::bit_cast<{{isa_dt_ret.reg}}>(resi);
// requires #include <string.h>
memcpy(&resv, &resi, sizeof({{isa_dt_ret.reg}}));

res.r[i] = %!pred_cond!% resv %!pred_alt!%;
"""
        },
    ],
    "andnb_k": [ # -------------------------------------------------------------------------------------------- andnb_k
        { "type": "element-wide", "datatypes": all_defs, "implem":
"""
res.m[i] = (~m0.m[i]) & m1.m[i];
"""
        },
    ],
    "orb": [ # ---------------------------------------------------------------------------------------------------- orb
        { "type": "element-wide", "datatypes": all_int + all_uint, "implem":
"""
res.r[i] = %!pred_cond!% r0.r[i] | r1.r[i] %!pred_alt!%;
"""
        },
        { "type": "element-wide", "datatypes": all_float, "implem":
"""
// The commented snippet code below produces "error: dereferencing type-punned pointer will break strict-aliasing rules"
// %v<c:uint|b:tp>% r0i = *({{isa_dt_par.msk}}*)((void*)&r0.r[i]);
// %v<c:uint|b:tp>% r1i = *({{isa_dt_par.msk}}*)((void*)&r1.r[i]);

%v<c:uint|b:tp>% r0i, r1i;
// compiler should identify the following pattern: rxi = std::bit_cast<{{isa_dt_par.msk}}>(rx.r[i]);
// requires #include <string.h>
memcpy(&r0i, &r0.r[i], sizeof({{isa_dt_par.msk}}));
memcpy(&r1i, &r1.r[i], sizeof({{isa_dt_par.msk}}));

%v<c:uint|b:tp>% resi = r0i | r1i;

%v<tr>% resv;
// compiler should identify the following pattern: resv = std::bit_cast<{{isa_dt_ret.reg}}>(resi);
// requires #include <string.h>
memcpy(&resv, &resi, sizeof({{isa_dt_ret.reg}}));

res.r[i] = %!pred_cond!% resv %!pred_alt!%;
"""
        },
    ],
    "orb_k": [ # ------------------------------------------------------------------------------------------------ orb_k
        { "type": "element-wide", "datatypes": all_defs, "implem":
"""
res.m[i] = m0.m[i] | m1.m[i];
"""
        },
    ],
    "xorb": [ # -------------------------------------------------------------------------------------------------- xorb
        { "type": "element-wide", "datatypes": all_int + all_uint, "implem":
"""
res.r[i] = %!pred_cond!% r0.r[i] ^ r1.r[i] %!pred_alt!%;
"""
        },
        { "type": "element-wide", "datatypes": all_float, "implem":
"""
// The commented snippet code below produces "error: dereferencing type-punned pointer will break strict-aliasing rules"
// %v<c:uint|b:tp>% r0i = *({{isa_dt_par.msk}}*)((void*)&r0.r[i]);
// %v<c:uint|b:tp>% r1i = *({{isa_dt_par.msk}}*)((void*)&r1.r[i]);

%v<c:uint|b:tp>% r0i, r1i;
// compiler should identify the following pattern: rxi = std::bit_cast<{{isa_dt_par.msk}}>(rx.r[i]);
// requires #include <string.h>
memcpy(&r0i, &r0.r[i], sizeof({{isa_dt_par.msk}}));
memcpy(&r1i, &r1.r[i], sizeof({{isa_dt_par.msk}}));

%v<c:uint|b:tp>% resi = r0i ^ r1i;

%v<tr>% resv;
// compiler should identify the following pattern: resv = std::bit_cast<{{isa_dt_ret.reg}}>(resi);
// requires #include <string.h>
memcpy(&resv, &resi, sizeof({{isa_dt_ret.reg}}));

res.r[i] = %!pred_cond!% resv %!pred_alt!%;
"""
        },
    ],
    "xorb_k": [ # ---------------------------------------------------------------------------------------------- xorb_k
        { "type": "element-wide", "datatypes": all_defs, "implem":
"""
res.m[i] = m0.m[i] ^ m1.m[i];
"""
        },
    ],
    "msb": [ # ---------------------------------------------------------------------------------------------------- msb
        { "type": "element-wide", "datatypes": all_64bit, "implem":
"""
%v<c:uint|b:tp>% msk = 0x8000000000000000ULL;

// The commented snippet code below produces "error: dereferencing type-punned pointer will break strict-aliasing rules"
// %v<c:uint|b:tp>% ri = *({{isa_dt_par.msk}}*)((void*)&r0.r[i]);

%v<c:uint|b:tp>% ri;
// compiler should identify the following pattern: ri = std::bit_cast<{{isa_dt_par.msk}}>(r0.r[i]);
// requires #include <string.h>
memcpy(&ri, &r0.r[i], sizeof({{isa_dt_par.msk}}));

%v<c:uint|b:tp>% resi = ri & msk;

%v<tr>% resv;
// compiler should identify the following pattern: resv = std::bit_cast<{{isa_dt_ret.reg}}>(resi);
// requires #include <string.h>
memcpy(&resv, &resi, sizeof({{isa_dt_ret.reg}}));

res.r[i] = %!pred_cond!% resv %!pred_alt!%;
"""
        },
        { "type": "element-wide", "datatypes": all_32bit, "implem":
"""
%v<c:uint|b:tp>% msk = 0x80000000;

// The commented snippet code below produces "error: dereferencing type-punned pointer will break strict-aliasing rules"
// %v<c:uint|b:tp>% ri = *({{isa_dt_par.msk}}*)((void*)&r0.r[i]);

%v<c:uint|b:tp>% ri;
// compiler should identify the following pattern: ri = std::bit_cast<{{isa_dt_par.msk}}>(r0.r[i]);
// requires #include <string.h>
memcpy(&ri, &r0.r[i], sizeof({{isa_dt_par.msk}}));

%v<c:uint|b:tp>% resi = ri & msk;

%v<tr>% resv;
// compiler should identify the following pattern: resv = std::bit_cast<{{isa_dt_ret.reg}}>(resi);
// requires #include <string.h>
memcpy(&resv, &resi, sizeof({{isa_dt_ret.reg}}));

res.r[i] = %!pred_cond!% resv %!pred_alt!%;
"""
        },
        { "type": "element-wide", "datatypes": all_16bit, "implem":
"""
%v<c:uint|b:tp>% msk = 0x8000;

// The commented snippet code below produces "error: dereferencing type-punned pointer will break strict-aliasing rules"
// %v<c:uint|b:tp>% ri = *({{isa_dt_par.msk}}*)((void*)&r0.r[i]);

%v<c:uint|b:tp>% ri;
// compiler should identify the following pattern: ri = std::bit_cast<{{isa_dt_par.msk}}>(r0.r[i]);
// requires #include <string.h>
memcpy(&ri, &r0.r[i], sizeof({{isa_dt_par.msk}}));

%v<c:uint|b:tp>% resi = ri & msk;

%v<tr>% resv;
// compiler should identify the following pattern: resv = std::bit_cast<{{isa_dt_ret.reg}}>(resi);
// requires #include <string.h>
memcpy(&resv, &resi, sizeof({{isa_dt_ret.reg}}));

res.r[i] = %!pred_cond!% resv %!pred_alt!%;
"""
        },
        { "type": "element-wide", "datatypes": all_8bit, "implem":
"""
%v<c:uint|b:tp>% msk = 0x80;

// The commented snippet code below produces "error: dereferencing type-punned pointer will break strict-aliasing rules"
// %v<c:uint|b:tp>% ri = *({{isa_dt_par.msk}}*)((void*)&r0.r[i]);

%v<c:uint|b:tp>% ri;
// compiler should identify the following pattern: ri = std::bit_cast<{{isa_dt_par.msk}}>(r0.r[i]);
// requires #include <string.h>
memcpy(&ri, &r0.r[i], sizeof({{isa_dt_par.msk}}));

%v<c:uint|b:tp>% resi = ri & msk;

%v<tr>% resv;
// compiler should identify the following pattern: resv = std::bit_cast<{{isa_dt_ret.reg}}>(resi);
// requires #include <string.h>
memcpy(&resv, &resi, sizeof({{isa_dt_ret.reg}}));

res.r[i] = %!pred_cond!% resv %!pred_alt!%;
"""
        },
    ],
    "notb": [ # -------------------------------------------------------------------------------------------------- notb
        { "type": "element-wide", "datatypes": all_int + all_uint, "implem":
"""
res.r[i] = %!pred_cond!% ~r0.r[i] %!pred_alt!%;
"""
        },
        { "type": "element-wide", "datatypes": all_float, "implem":
"""
// The commented snippet code below produces "error: dereferencing type-punned pointer will break strict-aliasing rules"
// %v<c:uint|b:tp>% r0i = *({{isa_dt_par.msk}}*)((void*)&r0.r[i]);

%v<c:uint|b:tp>% r0i;
// compiler should identify the following pattern: rxi = std::bit_cast<{{isa_dt_par.msk}}>(rx.r[i]);
// requires #include <string.h>
memcpy(&r0i, &r0.r[i], sizeof({{isa_dt_par.msk}}));

%v<c:uint|b:tp>% resi = ~r0i;

%v<tr>% resv;
// compiler should identify the following pattern: resv = std::bit_cast<{{isa_dt_ret.reg}}>(resi);
// requires #include <string.h>
memcpy(&resv, &resi, sizeof({{isa_dt_ret.reg}}));

res.r[i] = %!pred_cond!% resv %!pred_alt!%;
"""
        },
    ],
    "notb_k": [ # ---------------------------------------------------------------------------------------------- notb_k
        { "type": "element-wide", "datatypes": all_defs, "implem":
"""
res.m[i] = ~m0.m[i];
"""
        },
    ],
    "cmpeq": [ # ------------------------------------------------------------------------------------------------ cmpeq
        { "type": "element-wide", "datatypes": all_int, "implem":
"""
res.m[i] = %!pred_cond!% (r0.r[i] == r1.r[i]) ? -1 : 0 %!pred_alt!%;
"""
        },
        { "type": "vector-wide", "datatypes": all_uint + all_float, "implem":
"""
%v<c:int|b:tp>% onesi = -1;

%v<tr>% ones;
// compiler should identify the following pattern: ones = std::bit_cast<{{isa_dt_ret.reg}}>(onesi);
// requires #include <string.h>
memcpy(&ones, &onesi, sizeof({{isa_dt_ret.reg}}));

%m<tr>% res;
for (size_t i = 0; i < %N<tr>%; i++)
	res.m[i] = %!pred_cond!% (r0.r[i] == r1.r[i]) ? ones : 0 %!pred_alt!%;
return res;
"""
        },
    ],
    "cmpneq": [ # ---------------------------------------------------------------------------------------------- cmpneq
        { "type": "element-wide", "datatypes": all_int, "implem":
"""
res.m[i] = %!pred_cond!% (r0.r[i] != r1.r[i]) ? -1 : 0 %!pred_alt!%;
"""
        },
        { "type": "vector-wide", "datatypes": all_uint + all_float, "implem":
"""
%v<c:int|b:tp>% onesi = -1;

%v<tr>% ones;
// compiler should identify the following pattern: ones = std::bit_cast<{{isa_dt_ret.reg}}>(onesi);
// requires #include <string.h>
memcpy(&ones, &onesi, sizeof({{isa_dt_ret.reg}}));

%m<tr>% res;
for (size_t i = 0; i < %N<tr>%; i++)
	res.m[i] = %!pred_cond!% (r0.r[i] != r1.r[i]) ? ones : 0 %!pred_alt!%;
return res;
"""
        },
    ],
    "cmplt": [ # ------------------------------------------------------------------------------------------------ cmplt
        { "type": "element-wide", "datatypes": all_int, "implem":
"""
res.m[i] = %!pred_cond!% (r0.r[i] < r1.r[i]) ? -1 : 0 %!pred_alt!%;
"""
        },
        { "type": "vector-wide", "datatypes": all_uint + all_float, "implem":
"""
%v<c:int|b:tp>% onesi = -1;

%v<tr>% ones;
// compiler should identify the following pattern: ones = std::bit_cast<{{isa_dt_ret.reg}}>(onesi);
// requires #include <string.h>
memcpy(&ones, &onesi, sizeof({{isa_dt_ret.reg}}));

%m<tr>% res;
for (size_t i = 0; i < %N<tr>%; i++)
	res.m[i] = %!pred_cond!% (r0.r[i] < r1.r[i]) ? ones : 0 %!pred_alt!%;
return res;
"""
        },
    ],
    "cmple": [ # ------------------------------------------------------------------------------------------------ cmple
        { "type": "element-wide", "datatypes": all_int, "implem":
"""
res.m[i] = %!pred_cond!% (r0.r[i] <= r1.r[i]) ? -1 : 0 %!pred_alt!%;
"""
        },
        { "type": "vector-wide", "datatypes": all_uint + all_float, "implem":
"""
%v<c:int|b:tp>% onesi = -1;

%v<tr>% ones;
// compiler should identify the following pattern: ones = std::bit_cast<{{isa_dt_ret.reg}}>(onesi);
// requires #include <string.h>
memcpy(&ones, &onesi, sizeof({{isa_dt_ret.reg}}));

%m<tr>% res;
for (size_t i = 0; i < %N<tr>%; i++)
	res.m[i] = %!pred_cond!% (r0.r[i] <= r1.r[i]) ? ones : 0 %!pred_alt!%;
return res;
"""
        },
    ],
    "cmpge": [ # ------------------------------------------------------------------------------------------------ cmpge
        { "type": "element-wide", "datatypes": all_int, "implem":
"""
res.m[i] = %!pred_cond!% (r0.r[i] >= r1.r[i]) ? -1 : 0 %!pred_alt!%;
"""
        },
        { "type": "vector-wide", "datatypes": all_uint + all_float, "implem":
"""
%v<c:int|b:tp>% onesi = -1;

%v<tr>% ones;
// compiler should identify the following pattern: ones = std::bit_cast<{{isa_dt_ret.reg}}>(onesi);
// requires #include <string.h>
memcpy(&ones, &onesi, sizeof({{isa_dt_ret.reg}}));

%m<tr>% res;
for (size_t i = 0; i < %N<tr>%; i++)
	res.m[i] = %!pred_cond!% (r0.r[i] >= r1.r[i]) ? ones : 0 %!pred_alt!%;
return res;
"""
        },
    ],
    "cmpgt": [ # ------------------------------------------------------------------------------------------------ cmpgt
        { "type": "element-wide", "datatypes": all_int, "implem":
"""
res.m[i] = %!pred_cond!% (r0.r[i] > r1.r[i]) ? -1 : 0 %!pred_alt!%;
"""
        },
        { "type": "vector-wide", "datatypes": all_uint + all_float, "implem":
"""
%v<c:int|b:tp>% onesi = -1;

%v<tr>% ones;
// compiler should identify the following pattern: ones = std::bit_cast<{{isa_dt_ret.reg}}>(onesi);
// requires #include <string.h>
memcpy(&ones, &onesi, sizeof({{isa_dt_ret.reg}}));

%m<tr>% res;
for (size_t i = 0; i < %N<tr>%; i++)
	res.m[i] = %!pred_cond!% (r0.r[i] > r1.r[i]) ? ones : 0 %!pred_alt!%;
return res;
"""
        },
    ],
    "round": [ # ------------------------------------------------------------------------------------------------ round
        { "type": "element-wide", "datatypes": all_int + all_uint, "implem":
"""
// do nothing, it is weird to define round on integers...
res.r[i] = %!pred_cond!% r0.r[i] %!pred_alt!%;
"""
        },
        { "type": "element-wide", "datatypes": [float64], "implem":
"""
// requires #include <math.h>
res.r[i] = %!pred_cond!% round(r0.r[i]) %!pred_alt!%;
"""
        },
        { "type": "element-wide", "datatypes": [float32], "implem":
"""
// requires #include <math.h>
res.r[i] = %!pred_cond!% roundf(r0.r[i]) %!pred_alt!%;
"""
        },
    ],
    "blend": [ # ------------------------------------------------------------------------------------------------ blend
        { "type": "element-wide", "datatypes": all_defs, "implem":
"""
res.r[i] = m0.m[i] ? r0.r[i] : r1.r[i];
"""
        },
    ],
    "set0_k": [ # ---------------------------------------------------------------------------------------------- set0_k
        { "type": "element-wide", "datatypes": all_defs, "implem":
"""
res.m[i] = 0;
"""
        },
    ],
    "testz": [ # ------------------------------------------------------------------------------------------------ testz
        { "type": "vector-wide", "datatypes": all_defs, "implem":
"""
%v<c:int|b:32>% res = 0;
for (size_t i = 0; i < %N<tp>%; i++) // early termination is possible here but won't help the compiler vectorizer
	res += (m0.m[i] & m1.m[i]) ? 1 : 0;
return res ? 0 : 1;
"""
        },
    ],
    "testz_2": [ # -------------------------------------------------------------------------------------------- testz_2
        { "type": "vector-wide", "datatypes": all_defs, "implem":
"""
%v<c:int|b:32>% res = 0;
for (size_t i = 0; i < %N<tp>%; i++) // early termination is possible here but won't help the compiler vectorizer
	res += m0.m[i] == 0 ? 0 : 1;
return res ? 0 : 1;
"""
        },
    ],
    "hadd": [ # -------------------------------------------------------------------------------------------------- hadd
        { "type": "vector-wide", "datatypes": all_defs, "implem":
"""
%v<tr>% resv = 0;
for (size_t i = 0; i < %N<tp>%; i++)
	resv += r0.r[i];

%r<tr>% res;
for (size_t i = 0; i < %N<tp>%; i++)
	res.r[i] = %!pred_cond!% resv %!pred_alt!%;
return res;
"""
        },
    ],
    "hmul": [ # -------------------------------------------------------------------------------------------------- hmul
        { "type": "vector-wide", "datatypes": all_defs, "implem":
"""
%v<tr>% resv = 1;
for (size_t i = 0; i < %N<tp>%; i++)
	resv *= r0.r[i];

%r<tr>% res;
for (size_t i = 0; i < %N<tp>%; i++)
	res.r[i] = %!pred_cond!% resv %!pred_alt!%;
return res;
"""
        },
    ],
    "hmin": [ # -------------------------------------------------------------------------------------------------- hmin
        { "type": "vector-wide", "datatypes": all_defs, "implem":
"""
%v<tr>% resv = r0.r[0];
for (size_t i = 0; i < %N<tp>%; i++) // start from 0 to ease compiler autovec
	resv = (r0.r[i] < resv) ? r0.r[i] : resv;

%r<tr>% res;
for (size_t i = 0; i < %N<tp>%; i++)
	res.r[i] = %!pred_cond!% resv %!pred_alt!%;
return res;
"""
        },
    ],
    "hmax": [ # -------------------------------------------------------------------------------------------------- hmax
        { "type": "vector-wide", "datatypes": all_defs, "implem":
"""
%v<tr>% resv = r0.r[0];
for (size_t i = 0; i < %N<tp>%; i++) // start from 0 to ease compiler autovec
	resv = (r0.r[i] > resv) ? r0.r[i] : resv;

%r<tr>% res;
for (size_t i = 0; i < %N<tp>%; i++)
	res.r[i] = %!pred_cond!% resv %!pred_alt!%;
return res;
"""
        },
    ],
    "hadd_to_scal": [ # ---------------------------------------------------------------------------------- hadd_to_scal
        { "type": "vector-wide", "datatypes": all_defs, "implem":
"""
%v<tr>% resv = 0;
for (size_t i = 0; i < %N<tp>%; i++)
	resv += r0.r[i];
return resv;
"""
        },
    ],
    "maskz_add": [ # ---------------------------------------------------------------------------------------- maskz_add
        { "type": "element-wide", "datatypes": all_defs, "implem":
"""
res.r[i] = m0.m[i] ? r0.r[i] + r1.r[i] : 0;
"""
        },
    ],
    "fnmadd": [ # ---------------------------------------------------------------------------------------------- fnmadd
        { "type": "element-wide", "datatypes": all_defs, "implem":
"""
res.r[i] = %!pred_cond!% -(r0.r[i] * r1.r[i]) + r2.r[i] %!pred_alt!%;
"""
        },
    ],
    "fnmsub": [ # ---------------------------------------------------------------------------------------------- fnmsub
        { "type": "element-wide", "datatypes": all_defs, "implem":
"""
res.r[i] = %!pred_cond!% -(r0.r[i] * r1.r[i]) - r2.r[i] %!pred_alt!%;
"""
        },
    ],
    "div2": [ # -------------------------------------------------------------------------------------------------- div2
        { "type": "element-wide", "datatypes": all_int + all_uint, "implem":
"""
res.r[i] = %!pred_cond!% r0.r[i] >> 1 %!pred_alt!%;
"""
        },
        { "type": "element-wide", "datatypes": [float64], "implem":
"""
res.r[i] = %!pred_cond!% r0.r[i] / 2.0 %!pred_alt!%;
"""
        },
        { "type": "element-wide", "datatypes": [float32], "implem":
"""
res.r[i] = %!pred_cond!% r0.r[i] / 2.f %!pred_alt!%;
"""
        },
    ],
    "div4": [ # -------------------------------------------------------------------------------------------------- div4
        { "type": "element-wide", "datatypes": all_int + all_uint, "implem":
"""
res.r[i] = %!pred_cond!% r0.r[i] >> 2 %!pred_alt!%;
"""
        },
        { "type": "element-wide", "datatypes": [float64], "implem":
"""
res.r[i] = %!pred_cond!% r0.r[i] / 4.0 %!pred_alt!%;
"""
        },
        { "type": "element-wide", "datatypes": [float32], "implem":
"""
res.r[i] = %!pred_cond!% r0.r[i] / 4.f %!pred_alt!%;
"""
        },
    ],
    "rshift": [ # ---------------------------------------------------------------------------------------------- rshift
        { "type": "element-wide", "datatypes": all_int + all_uint, "implem":
"""
res.r[i] = %!pred_cond!% r0.r[i] >> v0 %!pred_alt!%;
"""
        },
        { "type": "element-wide", "datatypes": all_float, "implem":
"""
// The commented snippet code below produces "error: dereferencing type-punned pointer will break strict-aliasing rules"
// %v<c:uint|b:tp>% r0i = *({{isa_dt_par.msk}}*)((void*)&r0.r[i]);

%v<c:uint|b:tp>% r0i;
// compiler should identify the following pattern: rxi = std::bit_cast<{{isa_dt_par.msk}}>(rx.r[i]);
// requires #include <string.h>
memcpy(&r0i, &r0.r[i], sizeof({{isa_dt_par.msk}}));

r0i >>= v0;

%v<tr>% resv;
// compiler should identify the following pattern: resv = std::bit_cast<{{isa_dt_ret.reg}}>(r0i);
// requires #include <string.h>
memcpy(&resv, &r0i, sizeof({{isa_dt_ret.reg}}));

res.r[i] = %!pred_cond!% resv %!pred_alt!%;
"""
        },
    ],
    "lshift": [ # ---------------------------------------------------------------------------------------------- lshift
        { "type": "element-wide", "datatypes": all_int + all_uint, "implem":
"""
res.r[i] = %!pred_cond!% r0.r[i] << v0 %!pred_alt!%;
"""
        },
        { "type": "element-wide", "datatypes": all_float, "implem":
"""
// The commented snippet code below produces "error: dereferencing type-punned pointer will break strict-aliasing rules"
// %v<c:uint|b:tp>% r0i = *({{isa_dt_par.msk}}*)((void*)&r0.r[i]);

%v<c:uint|b:tp>% r0i;
// compiler should identify the following pattern: rxi = std::bit_cast<{{isa_dt_par.msk}}>(rx.r[i]);
// requires #include <string.h>
memcpy(&r0i, &r0.r[i], sizeof({{isa_dt_par.msk}}));

r0i <<= v0;

%v<tr>% resv;
// compiler should identify the following pattern: resv = std::bit_cast<{{isa_dt_ret.reg}}>(r0i);
// requires #include <string.h>
memcpy(&resv, &r0i, sizeof({{isa_dt_ret.reg}}));

res.r[i] = %!pred_cond!% resv %!pred_alt!%;
"""
        },
    ],
}

copy_mipp_funcs = copy.deepcopy(mipp_funcs)
