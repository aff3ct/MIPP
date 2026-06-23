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
    # "ret_reg_2args_ptr_vindex": {
    #     "ret" :
    #         {"type": "reg", "charac": "WO", "fixeddatatype": False},
    #     "args" : [
    #         {"type": "ptr", "charac": "WO", "fixeddatatype": False},
    #         {"type": "vindex", "charac": "RO", "fixeddatatype": False}
    #     ]
    # },
    # "ret_reg_3args_ptr_vindex_msk": {
    #     "ret" :
    #         {"type": "reg", "charac": "WO", "fixeddatatype": False},
    #     "args" : [
    #         {"type": "ptr", "charac": "WO", "fixeddatatype": False},
    #         {"type": "vindex", "charac": "RO", "fixeddatatype": False},
    #         {"type": "msk", "charac": "RO", "fixeddatatype": False}
    #     ]
    # },
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

    # offset lmul is a way to tell tools.build_call_lmul to NOT offset the ptr 
    # by the size of the vector register when building the generic lmul functions. 
    
    # This behavior is good in load / stores but is NOT what we want for gather / scatter.
    "ret_reg_2args_ptr_reg" : { # gather
        "ret" :
            {"type": "reg", "charac": "WO", "fixeddatatype": False},
        "args" : [
            {"type": "ptr", "charac": "RO", "fixeddatatype": False, "offset_lmul" : False},
            {"type": "reg", "charac": "RO", "fixeddatatype": "uint"}, # idx reg
        ]
    },

    "ret_void_3args_ptr_reg_reg" : { # scatter
        "ret" :
            {"type": False, "charac": "WO", "fixeddatatype": False},
        "args" : [
            {"type": "ptr", "charac": "WO", "fixeddatatype": False, "offset_lmul" : False},
            # I like that idx is r0 in both gather/scatter
            {"type": "reg", "charac": "RO", "fixeddatatype": "uint"},
            {"type": "reg", "charac": "RO", "fixeddatatype": False},
        ]
    }
}

mipp_funcs_concepts = {
    "reinterpret": [ "cast", "cast_k", "toreg", "tomsk" ],
    "load":        [ "load", "loadu", "set", "set_k", "set1", "set1_k", "set0", "set0_k", "maskzld", "gather" ],
    "store":       [ "store", "storeu", "get", "get_k", "getfirst", "scatter", "maskst" ],
    "arithmetic":  [ "add", "adds", "sub", "subs", "mul", "div", "div2", "div4", "maskz_add", "fmadd", "fmsub", "fnmadd", "fnmsub" ],
    "comparison":  [ "cmpeq", "cmpneq", "cmple", "cmplt", "cmpge", "cmpgt" ],
    "math":        [ "sqrt", "rsqrt", "round", "exp", "log", "pow"],
    "logic":       [ "andb", "andb_k", "andnb", "andnb_k", "orb", "orb_k", "xorb", "xorb_k", "msb", "notb", "notb_k", "lshift", "rshift"],
    "reduction":   [ "hadd", "hadds", "hmul", "hmin", "hmax", "hadd_to_scal", "hadds_to_scal", "testz", "testz_2" ],
    "selection":   [ "blend", "min", "max" ],
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
    
    def is_supported(self, mask_str):
        if mask_str == "mask":
            return self.maskable
        elif mask_str == "maskz":
            return self.maskzable
        elif mask_str == "masks":
            return self.masksable
        else:
            raise ValueError(f"Invalid mask type: {mask_str}")

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
    "cast":          { "proto": protos["ret_reg_1arg_reg"],             "datatypes": all_datatypes_cart_prod, "horizontal": False, "mask_support": no_mask         },
    "cast_k":        { "proto": protos["ret_msk_1arg_msk"],             "datatypes": all_datatypes_cart_prod, "horizontal": False, "mask_support": no_mask         },
    "toreg":         { "proto": protos["ret_reg_1arg_msk"],             "datatypes": all_datatypes,           "horizontal": False, "mask_support": no_mask         },
    "tomsk":         { "proto": protos["ret_msk_1arg_reg"],             "datatypes": all_datatypes,           "horizontal": False, "mask_support": no_mask         },
    "load":          { "proto": protos["ret_reg_1arg_ptr"],             "datatypes": all_datatypes,           "horizontal": False, "mask_support": maskz_and_masks },
    "loadu":         { "proto": protos["ret_reg_1arg_ptr"],             "datatypes": all_datatypes,           "horizontal": False, "mask_support": maskz_and_masks },
    "store":         { "proto": protos["ret_void_2args_ptr_reg"],       "datatypes": all_datatypes,           "horizontal": False, "mask_support": mask_and_maskz  },
    "storeu":        { "proto": protos["ret_void_2args_ptr_reg"],       "datatypes": all_datatypes,           "horizontal": False, "mask_support": mask_and_maskz  },
    "set":           { "proto": protos["ret_reg_1arg_Nele"],            "datatypes": all_datatypes,           "horizontal": True,  "mask_support": only_masks      },
    "set_k":         { "proto": protos["ret_msk_1arg_Nele"],            "datatypes": all_datatypes,           "horizontal": True, "mask_support": no_mask         },
    "set1":          { "proto": protos["ret_reg_1arg_val"],             "datatypes": all_datatypes,           "horizontal": False, "mask_support": only_masks      },
    "set1_k":        { "proto": protos["ret_msk_1arg_i32"],             "datatypes": all_datatypes,           "horizontal": False, "mask_support": no_mask         },
    "maskzld":       { "proto": protos["ret_reg_2args_msk_ptr"],        "datatypes": all_32bit+all_64bit,     "horizontal": False, "mask_support": no_mask         },
    "maskst":        { "proto": protos["ret_void_3args_ptr_msk_reg"],   "datatypes": all_32bit+all_64bit,     "horizontal": False, "mask_support": no_mask         },
    "set0":          { "proto": protos["ret_reg_0arg"],                 "datatypes": all_datatypes,           "horizontal": False, "mask_support": only_masks      },
#   "low_k":         { "proto": protos["ret_msk_0arg"],                 "datatypes": all_datatypes,           "horizontal": False                                  },
    "get":           { "proto": protos["ret_val_2args_reg_val"],        "datatypes": all_datatypes,           "horizontal": True,  "mask_support": no_mask         },
    "get_k":         { "proto": protos["ret_val_2args_msk_val"],        "datatypes": all_datatypes,           "horizontal": True,  "mask_support": no_mask         },
    "getfirst":      { "proto": protos["ret_val_1arg_reg"],             "datatypes": all_datatypes,           "horizontal": True,  "mask_support": no_mask         },
    "gather":        { "proto": protos["ret_reg_2args_ptr_reg"],        "datatypes": all_datatypes_idx_pair,  "horizontal": False, "mask_support": maskz_and_masks },
    "scatter":       { "proto": protos["ret_void_3args_ptr_reg_reg"],   "datatypes": all_datatypes_idx_pair,  "horizontal": False, "mask_support": mask_and_maskz  },
#   "mask_gather":   { "proto": protos["ret_reg_3args_ptr_vindex_msk"], "datatypes": all_datatypes,           "horizontal": False                                  },
    "sqrt":          { "proto": protos["ret_reg_1arg_reg"],             "datatypes": all_float,               "horizontal": False, "mask_support": all_mask        },
    "rsqrt":         { "proto": protos["ret_reg_1arg_reg"],             "datatypes": all_float,               "horizontal": False, "mask_support": all_mask        },
    "add":           { "proto": protos["ret_reg_2args_reg"],            "datatypes": all_datatypes,           "horizontal": False, "mask_support": all_mask        },
    "adds":          { "proto": protos["ret_reg_2args_reg"],            "datatypes": all_uint+all_int,        "horizontal": False, "mask_support": all_mask        },
    "sub":           { "proto": protos["ret_reg_2args_reg"],            "datatypes": all_datatypes,           "horizontal": False, "mask_support": all_mask        },
    "subs":          { "proto": protos["ret_reg_2args_reg"],            "datatypes": all_uint+all_int,        "horizontal": False, "mask_support": all_mask        },
    "mul":           { "proto": protos["ret_reg_2args_reg"],            "datatypes": all_datatypes,           "horizontal": False, "mask_support": all_mask        },
    "div":           { "proto": protos["ret_reg_2args_reg"],            "datatypes": all_float,               "horizontal": False, "mask_support": all_mask        },
    "min":           { "proto": protos["ret_reg_2args_reg"],            "datatypes": all_datatypes,           "horizontal": False, "mask_support": all_mask        },
    "max":           { "proto": protos["ret_reg_2args_reg"],            "datatypes": all_datatypes,           "horizontal": False, "mask_support": all_mask        },
    "fmadd":         { "proto": protos["ret_reg_3args_reg"],            "datatypes": all_float+[int32],       "horizontal": False, "mask_support": all_mask        },
    "fmsub":         { "proto": protos["ret_reg_3args_reg"],            "datatypes": all_float+[int32],       "horizontal": False, "mask_support": all_mask        },
    "andb":          { "proto": protos["ret_reg_2args_reg"],            "datatypes": all_datatypes,           "horizontal": False, "mask_support": all_mask        },
    "andb_k":        { "proto": protos["ret_msk_2args_msk"],            "datatypes": all_datatypes,           "horizontal": False, "mask_support": no_mask         },
    "andnb":         { "proto": protos["ret_reg_2args_reg"],            "datatypes": all_datatypes,           "horizontal": False, "mask_support": all_mask        },
    "andnb_k":       { "proto": protos["ret_msk_2args_msk"],            "datatypes": all_datatypes,           "horizontal": False, "mask_support": no_mask         },
    "orb":           { "proto": protos["ret_reg_2args_reg"],            "datatypes": all_datatypes,           "horizontal": False, "mask_support": all_mask        },
    "orb_k":         { "proto": protos["ret_msk_2args_msk"],            "datatypes": all_datatypes,           "horizontal": False, "mask_support": no_mask         },
    "xorb":          { "proto": protos["ret_reg_2args_reg"],            "datatypes": all_datatypes,           "horizontal": False, "mask_support": all_mask        },
    "xorb_k":        { "proto": protos["ret_msk_2args_msk"],            "datatypes": all_datatypes,           "horizontal": False, "mask_support": no_mask         },
    "msb":           { "proto": protos["ret_reg_1arg_reg"],             "datatypes": all_datatypes,           "horizontal": False, "mask_support": all_mask        },
    "notb":          { "proto": protos["ret_reg_1arg_reg"],             "datatypes": all_datatypes,           "horizontal": False, "mask_support": all_mask        },
    "notb_k":        { "proto": protos["ret_msk_1arg_msk"],             "datatypes": all_datatypes,           "horizontal": False, "mask_support": no_mask         },
    "cmpeq":         { "proto": protos["ret_msk_2args_reg"],            "datatypes": all_datatypes,           "horizontal": False, "mask_support": only_maskz      },
    "cmpneq":        { "proto": protos["ret_msk_2args_reg"],            "datatypes": all_datatypes,           "horizontal": False, "mask_support": only_maskz      },
    "cmplt":         { "proto": protos["ret_msk_2args_reg"],            "datatypes": all_datatypes,           "horizontal": False, "mask_support": only_maskz      },
    "cmple":         { "proto": protos["ret_msk_2args_reg"],            "datatypes": all_datatypes,           "horizontal": False, "mask_support": only_maskz      },
    "cmpge":         { "proto": protos["ret_msk_2args_reg"],            "datatypes": all_datatypes,           "horizontal": False, "mask_support": only_maskz      },
    "cmpgt":         { "proto": protos["ret_msk_2args_reg"],            "datatypes": all_datatypes,           "horizontal": False, "mask_support": only_maskz      },
    "round":         { "proto": protos["ret_reg_1arg_reg"],             "datatypes": all_datatypes,           "horizontal": False, "mask_support": all_mask        },
    "blend":         { "proto": protos["ret_reg_3args_2reg_1msk"],      "datatypes": all_datatypes,           "horizontal": False, "mask_support": no_mask         },
    "set0_k":        { "proto": protos["ret_msk_0arg"],                 "datatypes": all_datatypes,           "horizontal": False, "mask_support": no_mask         },
    "testz":         { "proto": protos["ret_i32_2args_msk"],            "datatypes": all_datatypes,           "horizontal": True,  "mask_support": no_mask         },
    "testz_2":       { "proto": protos["ret_i32_1arg_msk"],             "datatypes": all_datatypes,           "horizontal": True,  "mask_support": no_mask         },
    "hadd":          { "proto": protos["ret_val_1arg_reg"],             "datatypes": all_datatypes,           "horizontal": True,  "mask_support": only_maskz       },
    "hadds":         { "proto": protos["ret_val_1arg_reg"],             "datatypes": all_uint+all_int,        "horizontal": True,  "mask_support": only_maskz      },
    "hmul":          { "proto": protos["ret_val_1arg_reg"],             "datatypes": all_datatypes,           "horizontal": True,  "mask_support": only_maskz      },
    "hmin":          { "proto": protos["ret_val_1arg_reg"],             "datatypes": all_datatypes,           "horizontal": True,  "mask_support": only_maskz       },
    "hmax":          { "proto": protos["ret_val_1arg_reg"],             "datatypes": all_datatypes,           "horizontal": True,  "mask_support": only_maskz       },
    "hadd_to_scal":  { "proto": protos["ret_val_1arg_reg"],             "datatypes": all_datatypes,           "horizontal": True,  "mask_support": no_mask         },
    "hadds_to_scal": { "proto": protos["ret_val_1arg_reg"],             "datatypes": all_uint+all_int,        "horizontal": True,  "mask_support": no_mask         },
#   "hmul_to_scal":  { "proto": protos["ret_val_1arg_reg"],             "datatypes": all_datatypes,           "horizontal": True                                   },
#   "hmin_to_scal":  { "proto": protos["ret_val_1arg_reg"],             "datatypes": all_datatypes,           "horizontal": True                                   },
#   "hmax_to_scal":  { "proto": protos["ret_val_1arg_reg"],             "datatypes": all_datatypes,           "horizontal": True                                   },
    "maskz_add":     { "proto": protos["ret_reg_3args_1msk_2reg"],      "datatypes": all_datatypes,           "horizontal": False,  "mask_support": no_mask         },
    "fnmadd":        { "proto": protos["ret_reg_3args_reg"],            "datatypes": all_float+[int32],       "horizontal": False, "mask_support": all_mask        },
    "fnmsub":        { "proto": protos["ret_reg_3args_reg"],            "datatypes": all_float+[int32],       "horizontal": False, "mask_support": all_mask        },
    "div2":          { "proto": protos["ret_reg_1arg_reg"],             "datatypes": all_datatypes,           "horizontal": False, "mask_support": all_mask        },
    "div4":          { "proto": protos["ret_reg_1arg_reg"],             "datatypes": all_datatypes,           "horizontal": False, "mask_support": all_mask        },
    "rshift":        { "proto": protos["ret_reg_2args_reg_val"],        "datatypes": all_datatypes,           "horizontal": False, "mask_support": all_mask        },
    "lshift":        { "proto": protos["ret_reg_2args_reg_val"],        "datatypes": all_datatypes,           "horizontal": False, "mask_support": all_mask        },

    "exp":          { "proto": protos["ret_reg_1arg_reg"],             "datatypes": all_float,                "horizontal": False, "mask_support": all_mask        },
    "log":          { "proto": protos["ret_reg_1arg_reg"],             "datatypes": all_float,                "horizontal": False, "mask_support": all_mask        },
    # "pow":          { "proto": protos["ret_reg_2args_reg_val"],        "datatypes": all_datatypes,           "horizontal": False, "mask_support": all_mask        },
    "pow2":         { "proto": protos["ret_reg_2args_reg_val"],        "datatypes": all_datatypes,            "horizontal": False, "mask_support": all_mask        },
}

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

# #define BIT_CAST_N(dst_ptr, src_ptr, n) \
#     memcpy((dst_ptr), (src_ptr), (n) * sizeof(*(dst_ptr)))

# #define BIT_CAST_1(dst_ptr, src_ptr) \
#     memcpy((dst_ptr), (src_ptr), sizeof(*(dst_ptr)))

#define EXPF(x) (expf(x))
#define EXPD(x) (exp(x))
#define LOGF(x) (logf(x))
#define LOGD(x) (log(x))

#define POW(x, y) (powf(x, y))
#define POWD(x, y) (pow(x, y))

implems_scalar = {
    "cast": [ # -------------------------------------------------------------------------------------------------- cast
        { "type": "vector-wide", "datatypes": all_defs, "mask_variants": all_defs, "implem":
"""
%r<tr>% res;
BIT_CAST_N(res.r, r0.r, %N<tr>%);
return res;
"""
        },
    ],
    "cast_k": [ # ---------------------------------------------------------------------------------------------- cast_k
        { "type": "vector-wide", "datatypes": all_defs, "mask_variants": all_defs, "implem":
"""
%m<tr>% res;
BIT_CAST_N(res.m, m0.m, %N<tr>%);
return res;
"""
        },
    ],
    "toreg": [ # ------------------------------------------------------------------------------------------------ toreg
        { "type": "vector-wide", "datatypes": all_defs, "mask_variants": all_defs, "implem":
"""
%r<tr>% res;
BIT_CAST_N(res.r, m0.m, %N<tr>%);
return res;
"""
        },
    ],
    "tomsk": [ # ------------------------------------------------------------------------------------------------ tomsk
        { "type": "vector-wide", "datatypes": all_defs, "mask_variants": all_defs, "implem":
"""
%m<tr>% res;
BIT_CAST_N(res.m, r0.r, %N<tr>%);
return res;
"""
        },
    ],
    "load": [ # -------------------------------------------------------------------------------------------------- load
        { "type": "element-wide", "datatypes": all_defs, "mask_variants": all_defs, "implem":
"""
res.r[i] = %!pred_cond!% p0[i] %!pred_alt!%;
"""
        },
    ],
    "loadu": [ # ------------------------------------------------------------------------------------------------ loadu
        { "type": "element-wide", "datatypes": all_defs, "mask_variants": all_defs, "implem":
"""
res.r[i] = %!pred_cond!% p0[i] %!pred_alt!%;
"""
        },
    ],
    "store": [ # ------------------------------------------------------------------------------------------------ store
        { "type": "element-wide", "datatypes": all_defs, "mask_variants": ["no_mask", "maskz"], "implem":
"""
p0[i] = %!pred_cond!% r0.r[i] %!pred_alt!%;
"""
        },
        { "type": "element-wide", "datatypes": all_defs, "mask_variants": ["mask"], "implem":
"""
if (m0.m[i]) p0[i] = r0.r[i];
"""
        },
    ],
    "storeu": [ # ---------------------------------------------------------------------------------------------- storeu
        { "type": "element-wide", "datatypes": all_defs, "mask_variants": ["no_mask", "maskz"], "implem":
"""
p0[i] = %!pred_cond!% r0.r[i] %!pred_alt!%;
"""
        },
        { "type": "element-wide", "datatypes": all_defs, "mask_variants": ["mask"], "implem":
"""
if (m0.m[i]) p0[i] = r0.r[i];
"""
        },
    ],
    "set": [ # ---------------------------------------------------------------------------------------------------- set
        { "type": "element-wide", "datatypes": all_defs, "mask_variants": all_defs, "implem":
"""
res.r[i] = %!pred_cond!% vals[i] %!pred_alt!%;
"""
        },
    ],
    "set_k": [ # ------------------------------------------------------------------------------------------------ set_k
        { "type": "element-wide", "datatypes": all_defs, "mask_variants": all_defs, "implem":
"""
%v<c:int|b:tr>% m_tmp = vals[i] ? -1 : 0;
BIT_CAST_1(&res.m[i], &m_tmp);
"""
        },
    ],
    "set1": [ # -------------------------------------------------------------------------------------------------- set1
        { "type": "element-wide", "datatypes": all_defs, "mask_variants": all_defs, "implem":
"""
res.r[i] = %!pred_cond!% v0 %!pred_alt!%;
"""
        },
    ],
    "set1_k": [ # ---------------------------------------------------------------------------------------------- set1_k
        { "type": "vector-wide", "datatypes": all_defs, "mask_variants": all_defs, "implem":
"""
%m<tr>% res;
%v<c:int|b:tr>% m_tmp = v0 ? -1 : 0;
for (size_t i = 0; i < %N<tr>%; i++)
	BIT_CAST_1(&res.m[i], &m_tmp);
return res;
"""
        },
    ],
    "maskzld": [ # -------------------------------------------------------------------------------------------- maskzld
        { "type": "element-wide", "datatypes": all_defs, "mask_variants": all_defs, "implem":
"""
res.r[i] = m0.m[i] ? p0[i] : 0;
"""
        },
    ],
    "maskst": [ # ---------------------------------------------------------------------------------------------- maskst
        { "type": "element-wide", "datatypes": all_defs, "mask_variants": all_defs, "implem":
"""
if (m0.m[i]) p0[i] = r0.r[i];
"""
        },
    ],
    "set0": [ # -------------------------------------------------------------------------------------------------- set0
        { "type": "element-wide", "datatypes": all_defs, "mask_variants": all_defs, "implem":
"""
res.r[i] = %!pred_cond!% 0 %!pred_alt!%;
"""
        },
    ],
    "get": [ # ---------------------------------------------------------------------------------------------------- get
        { "type": "vector-wide", "datatypes": all_defs, "mask_variants": all_defs, "implem":
"""
return r0.r[v0];
"""
        },
    ],
    "get_k": [ # ------------------------------------------------------------------------------------------------ get_k
        { "type": "vector-wide", "datatypes": all_defs, "mask_variants": all_defs, "implem":
"""
return m0.m[v0];
"""
        },
    ],
    "getfirst": [ # ------------------------------------------------------------------------------------------ getfirst
        { "type": "vector-wide", "datatypes": all_defs, "mask_variants": all_defs, "implem":
"""
return r0.r[0];
"""
        },
    ],
    "sqrt": [ # -------------------------------------------------------------------------------------------------- sqrt
        { "type": "element-wide", "datatypes": [float64], "mask_variants": all_defs, "implem":
"""
// requires #include <math.h>
res.r[i] = %!pred_cond!% sqrt(r0.r[i]) %!pred_alt!%;
"""
        },
        { "type": "element-wide", "datatypes": [float32], "mask_variants": all_defs, "implem":
"""
// requires #include <math.h>
res.r[i] = %!pred_cond!% sqrtf(r0.r[i]) %!pred_alt!%;
"""
        },
    ],
    "rsqrt": [ # ------------------------------------------------------------------------------------------------ rsqrt
        { "type": "element-wide", "datatypes": [float64], "mask_variants": all_defs, "implem":
"""
// requires #include <math.h>
res.r[i] = %!pred_cond!% 1.0 / sqrt(r0.r[i]) %!pred_alt!%;
"""
        },
        { "type": "element-wide", "datatypes": [float32], "mask_variants": all_defs, "implem":
"""
// requires #include <math.h>
res.r[i] = %!pred_cond!% 1.0f / sqrtf(r0.r[i]) %!pred_alt!%;
"""
        },
    ],
    "add": [ # ---------------------------------------------------------------------------------------------------- add
        { "type": "element-wide", "datatypes": all_defs, "mask_variants": all_defs, "implem":
"""
res.r[i] = %!pred_cond!% r0.r[i] + r1.r[i] %!pred_alt!%;
"""
        },
    ],
    "adds": [ # -------------------------------------------------------------------------------------------------- adds
        { "type": "element-wide", "datatypes": all_int, "mask_variants": all_defs, "implem":
"""
int{{ dt_par.n_bits }}_t a = r0.r[i];
int{{ dt_par.n_bits }}_t b = r1.r[i];

int{{ dt_par.n_bits }}_t c =
	(b > 0 && a > INT{{ dt_par.n_bits }}_MAX - b) ? (int{{ dt_par.n_bits }}_t)INT{{ dt_par.n_bits }}_MAX :
	(b < 0 && a < INT{{ dt_par.n_bits }}_MIN - b) ? (int{{ dt_par.n_bits }}_t)INT{{ dt_par.n_bits }}_MIN :
	(int{{ dt_par.n_bits }}_t)(a + b);

res.r[i] = %!pred_cond!% c %!pred_alt!%;
"""
        },
        { "type": "element-wide", "datatypes": all_uint, "mask_variants": all_defs, "implem":
"""
uint{{ dt_par.n_bits }}_t a = r0.r[i];
uint{{ dt_par.n_bits }}_t b = r1.r[i];

uint{{ dt_par.n_bits }}_t c =
	(a > UINT{{ dt_par.n_bits }}_MAX - b) ? UINT{{ dt_par.n_bits }}_MAX :
	(uint{{ dt_par.n_bits }}_t)(a + b);

res.r[i] = %!pred_cond!% c %!pred_alt!%;
"""
        },
    ],
    "sub": [ # ---------------------------------------------------------------------------------------------------- sub
        { "type": "element-wide", "datatypes": all_defs, "mask_variants": all_defs, "implem":
"""
res.r[i] = %!pred_cond!% r0.r[i] - r1.r[i] %!pred_alt!%;
"""
        },
    ],
    "subs": [ # -------------------------------------------------------------------------------------------------- subs
{ "type": "element-wide", "datatypes": all_int, "mask_variants": all_defs, "implem":
"""
int{{ dt_par.n_bits }}_t a = r0.r[i];
int{{ dt_par.n_bits }}_t b = r1.r[i];

int{{ dt_par.n_bits }}_t c =
	(b < 0 && a > INT{{ dt_par.n_bits }}_MAX + b) ? INT{{ dt_par.n_bits }}_MAX :
	(b > 0 && a < INT{{ dt_par.n_bits }}_MIN + b) ? INT{{ dt_par.n_bits }}_MIN :
	(int{{ dt_par.n_bits }}_t)(a - b);

res.r[i] = %!pred_cond!% c %!pred_alt!%;
"""
        },
        { "type": "element-wide", "datatypes": all_uint, "mask_variants": all_defs, "implem":
"""
uint{{ dt_par.n_bits }}_t a = r0.r[i];
uint{{ dt_par.n_bits }}_t b = r1.r[i];

uint{{ dt_par.n_bits }}_t c =
	(a < b) ? 0 :
	(uint{{ dt_par.n_bits }}_t)(a - b);

res.r[i] = %!pred_cond!% c %!pred_alt!%;
"""
        },
    ],
    "mul": [ # ---------------------------------------------------------------------------------------------------- mul
        { "type": "element-wide", "datatypes": all_defs, "mask_variants": all_defs, "implem":
"""
res.r[i] = %!pred_cond!% r0.r[i] * r1.r[i] %!pred_alt!%;
"""
        },
    ],
    "div": [ # ---------------------------------------------------------------------------------------------------- div
        { "type": "element-wide", "datatypes": all_defs, "mask_variants": all_defs, "implem":
"""
res.r[i] = %!pred_cond!% r0.r[i] / r1.r[i] %!pred_alt!%;
"""
        },
    ],
    "min": [ # ---------------------------------------------------------------------------------------------------- min
        { "type": "element-wide", "datatypes": all_defs, "mask_variants": all_defs, "implem":
"""
res.r[i] = %!pred_cond!% r0.r[i] < r1.r[i] ? r0.r[i] : r1.r[i] %!pred_alt!%;
"""
        },
    ],
    "max": [ # ---------------------------------------------------------------------------------------------------- max
        { "type": "element-wide", "datatypes": all_defs, "mask_variants": all_defs, "implem":
"""
res.r[i] = %!pred_cond!% r0.r[i] > r1.r[i] ? r0.r[i] : r1.r[i] %!pred_alt!%;
"""
        },
    ],
    "fmadd": [ # ------------------------------------------------------------------------------------------------ fmadd
        { "type": "element-wide", "datatypes": all_defs, "mask_variants": all_defs, "implem":
"""
res.r[i] = %!pred_cond!% r0.r[i] * r1.r[i] + r2.r[i] %!pred_alt!%;
"""
        },
    ],
    "fmsub": [ # ------------------------------------------------------------------------------------------------ fmsub
        { "type": "element-wide", "datatypes": all_defs, "mask_variants": all_defs, "implem":
"""
res.r[i] = %!pred_cond!% r0.r[i] * r1.r[i] - r2.r[i] %!pred_alt!%;
"""
        },
    ],
    "andb": [ # -------------------------------------------------------------------------------------------------- andb
        { "type": "element-wide", "datatypes": all_int + all_uint, "mask_variants": all_defs, "implem":
"""
res.r[i] = %!pred_cond!% r0.r[i] & r1.r[i] %!pred_alt!%;
"""
        },
        { "type": "element-wide", "datatypes": all_float, "mask_variants": all_defs, "implem":
"""
%v<c:uint|b:tp>% r0i, r1i;
BIT_CAST_1(&r0i, &r0.r[i]);
BIT_CAST_1(&r1i, &r1.r[i]);
%v<c:uint|b:tp>% resi = r0i & r1i;
%v<tr>% resv;
BIT_CAST_1(&resv, &resi);
res.r[i] = %!pred_cond!% resv %!pred_alt!%;
"""
        },
    ],
    "andb_k": [ # ---------------------------------------------------------------------------------------------- andb_k
        { "type": "element-wide", "datatypes": all_defs, "mask_variants": all_defs, "implem":
"""
res.m[i] = m0.m[i] & m1.m[i];
"""
        },
    ],
    "andnb": [ # ------------------------------------------------------------------------------------------------ andnb
        { "type": "element-wide", "datatypes": all_int + all_uint, "mask_variants": all_defs, "implem":
"""
res.r[i] = %!pred_cond!% (~r0.r[i]) & r1.r[i] %!pred_alt!%;
"""
        },
        { "type": "element-wide", "datatypes": all_float, "mask_variants": all_defs, "implem":
"""
%v<c:uint|b:tp>% r0i, r1i;
BIT_CAST_1(&r0i, &r0.r[i]);
BIT_CAST_1(&r1i, &r1.r[i]);
%v<c:uint|b:tp>% resi = (~r0i) & r1i;
%v<tr>% resv;
BIT_CAST_1(&resv, &resi);
res.r[i] = %!pred_cond!% resv %!pred_alt!%;
"""
        },
    ],
    "andnb_k": [ # -------------------------------------------------------------------------------------------- andnb_k
        { "type": "element-wide", "datatypes": all_defs, "mask_variants": all_defs, "implem":
"""
res.m[i] = (~m0.m[i]) & m1.m[i];
"""
        },
    ],
    "orb": [ # ---------------------------------------------------------------------------------------------------- orb
        { "type": "element-wide", "datatypes": all_int + all_uint, "mask_variants": all_defs, "implem":
"""
res.r[i] = %!pred_cond!% r0.r[i] | r1.r[i] %!pred_alt!%;
"""
        },
        { "type": "element-wide", "datatypes": all_float, "mask_variants": all_defs, "implem":
"""
%v<c:uint|b:tp>% r0i, r1i;
BIT_CAST_1(&r0i, &r0.r[i]);
BIT_CAST_1(&r1i, &r1.r[i]);
%v<c:uint|b:tp>% resi = r0i | r1i;
%v<tr>% resv;
BIT_CAST_1(&resv, &resi);
res.r[i] = %!pred_cond!% resv %!pred_alt!%;
"""
        },
    ],
    "orb_k": [ # ------------------------------------------------------------------------------------------------ orb_k
        { "type": "element-wide", "datatypes": all_defs, "mask_variants": all_defs, "implem":
"""
res.m[i] = m0.m[i] | m1.m[i];
"""
        },
    ],
    "xorb": [ # -------------------------------------------------------------------------------------------------- xorb
        { "type": "element-wide", "datatypes": all_int + all_uint, "mask_variants": all_defs, "implem":
"""
res.r[i] = %!pred_cond!% r0.r[i] ^ r1.r[i] %!pred_alt!%;
"""
        },
        { "type": "element-wide", "datatypes": all_float, "mask_variants": all_defs, "implem":
"""
%v<c:uint|b:tp>% r0i, r1i;
BIT_CAST_1(&r0i, &r0.r[i]);
BIT_CAST_1(&r1i, &r1.r[i]);
%v<c:uint|b:tp>% resi = r0i ^ r1i;
%v<tr>% resv;
BIT_CAST_1(&resv, &resi);
res.r[i] = %!pred_cond!% resv %!pred_alt!%;
"""
        },
    ],
    "xorb_k": [ # ---------------------------------------------------------------------------------------------- xorb_k
        { "type": "element-wide", "datatypes": all_defs, "mask_variants": all_defs, "implem":
"""
res.m[i] = m0.m[i] ^ m1.m[i];
"""
        },
    ],
    "msb": [ # ---------------------------------------------------------------------------------------------------- msb
        { "type": "element-wide", "datatypes": all_64bit, "mask_variants": all_defs, "implem":
"""
%v<c:uint|b:tp>% msk = 0x8000000000000000ULL;
%v<c:uint|b:tp>% ri;
BIT_CAST_1(&ri, &r0.r[i]);
%v<c:uint|b:tp>% resi = ri & msk;
%v<tr>% resv;
BIT_CAST_1(&resv, &resi);
res.r[i] = %!pred_cond!% resv %!pred_alt!%;
"""
        },
        { "type": "element-wide", "datatypes": all_32bit, "mask_variants": all_defs, "implem":
"""
%v<c:uint|b:tp>% msk = 0x80000000;
%v<c:uint|b:tp>% ri;
BIT_CAST_1(&ri, &r0.r[i]);
%v<c:uint|b:tp>% resi = ri & msk;
%v<tr>% resv;
BIT_CAST_1(&resv, &resi);
res.r[i] = %!pred_cond!% resv %!pred_alt!%;
"""
        },
        { "type": "element-wide", "datatypes": all_16bit, "mask_variants": all_defs, "implem":
"""
%v<c:uint|b:tp>% msk = 0x8000;
%v<c:uint|b:tp>% ri;
BIT_CAST_1(&ri, &r0.r[i]);
%v<c:uint|b:tp>% resi = ri & msk;
%v<tr>% resv;
BIT_CAST_1(&resv, &resi);
res.r[i] = %!pred_cond!% resv %!pred_alt!%;
"""
        },
        { "type": "element-wide", "datatypes": all_8bit, "mask_variants": all_defs, "implem":
"""
%v<c:uint|b:tp>% msk = 0x80;
%v<c:uint|b:tp>% ri;
BIT_CAST_1(&ri, &r0.r[i]);
%v<c:uint|b:tp>% resi = ri & msk;
%v<tr>% resv;
BIT_CAST_1(&resv, &resi);
res.r[i] = %!pred_cond!% resv %!pred_alt!%;
"""
        },
    ],
    "notb": [ # -------------------------------------------------------------------------------------------------- notb
        { "type": "element-wide", "datatypes": all_int + all_uint, "mask_variants": all_defs, "implem":
"""
res.r[i] = %!pred_cond!% ~r0.r[i] %!pred_alt!%;
"""
        },
        { "type": "element-wide", "datatypes": all_float, "mask_variants": all_defs, "implem":
"""
%v<c:uint|b:tp>% r0i;
BIT_CAST_1(&r0i, &r0.r[i]);
%v<c:uint|b:tp>% resi = ~r0i;
%v<tr>% resv;
BIT_CAST_1(&resv, &resi);
res.r[i] = %!pred_cond!% resv %!pred_alt!%;
"""
        },
    ],
    "notb_k": [ # ---------------------------------------------------------------------------------------------- notb_k
        { "type": "element-wide", "datatypes": all_defs, "mask_variants": all_defs, "implem":
"""
res.m[i] = ~m0.m[i];
"""
        },
    ],
    "cmpeq": [ # ------------------------------------------------------------------------------------------------ cmpeq
        { "type": "element-wide", "datatypes": all_defs, "mask_variants": all_defs, "implem":
"""
res.m[i] = %!pred_cond!% (r0.r[i] == r1.r[i]) ? (%v<c:uint|b:tr>%)-1 : 0 %!pred_alt!%;
"""
        },
    ],
    "cmpneq": [ # ---------------------------------------------------------------------------------------------- cmpneq
        { "type": "element-wide", "datatypes": all_defs, "mask_variants": all_defs, "implem":
"""
res.m[i] = %!pred_cond!% (r0.r[i] != r1.r[i]) ? (%v<c:uint|b:tr>%)-1 : 0 %!pred_alt!%;
"""
        },
    ],
    "cmplt": [ # ------------------------------------------------------------------------------------------------ cmplt
        { "type": "element-wide", "datatypes": all_defs, "mask_variants": all_defs, "implem":
"""
res.m[i] = %!pred_cond!% (r0.r[i] < r1.r[i]) ? (%v<c:uint|b:tr>%)-1 : 0 %!pred_alt!%;
"""
        },
    ],
    "cmple": [ # ------------------------------------------------------------------------------------------------ cmple
        { "type": "element-wide", "datatypes": all_defs, "mask_variants": all_defs, "implem":
"""
res.m[i] = %!pred_cond!% (r0.r[i] <= r1.r[i]) ? (%v<c:uint|b:tr>%)-1 : 0 %!pred_alt!%;
"""
        },
    ],
    "cmpge": [ # ------------------------------------------------------------------------------------------------ cmpge
        { "type": "element-wide", "datatypes": all_defs, "mask_variants": all_defs, "implem":
"""
res.m[i] = %!pred_cond!% (r0.r[i] >= r1.r[i]) ? (%v<c:uint|b:tr>%)-1 : 0 %!pred_alt!%;
"""
        },
    ],
    "cmpgt": [ # ------------------------------------------------------------------------------------------------ cmpgt
        { "type": "element-wide", "datatypes": all_defs, "mask_variants": all_defs, "implem":
"""
res.m[i] = %!pred_cond!% (r0.r[i] > r1.r[i]) ? (%v<c:uint|b:tr>%)-1 : 0 %!pred_alt!%;
"""
        },
    ],
    "round": [ # ------------------------------------------------------------------------------------------------ round
        { "type": "element-wide", "datatypes": all_int + all_uint, "mask_variants": all_defs, "implem":
"""
// do nothing, it is weird to define round on integers...
res.r[i] = %!pred_cond!% r0.r[i] %!pred_alt!%;
"""
        },
        { "type": "element-wide", "datatypes": [float64], "mask_variants": all_defs, "implem":
"""
// requires #include <math.h>
res.r[i] = %!pred_cond!% round(r0.r[i]) %!pred_alt!%;
"""
        },
        { "type": "element-wide", "datatypes": [float32], "mask_variants": all_defs, "implem":
"""
// requires #include <math.h>
res.r[i] = %!pred_cond!% roundf(r0.r[i]) %!pred_alt!%;
"""
        },
    ],
    "blend": [ # ------------------------------------------------------------------------------------------------ blend
        { "type": "element-wide", "datatypes": all_defs, "mask_variants": all_defs, "implem":
"""
res.r[i] = m0.m[i] ? r0.r[i] : r1.r[i];
"""
        },
    ],
    "set0_k": [ # ---------------------------------------------------------------------------------------------- set0_k
        { "type": "element-wide", "datatypes": all_defs, "mask_variants": all_defs, "implem":
"""
res.m[i] = 0;
"""
        },
    ],
    "testz": [ # ------------------------------------------------------------------------------------------------ testz
        { "type": "vector-wide", "datatypes": all_defs, "mask_variants": all_defs, "implem":
"""
%v<c:int|b:32>% res = 0;
for (size_t i = 0; i < %N<tp>%; i++) // early termination is possible here but won't help the compiler vectorizer
	res += (m0.m[i] & m1.m[i]) ? 1 : 0;
return res ? 0 : 1;
"""
        },
    ],
    "testz_2": [ # -------------------------------------------------------------------------------------------- testz_2
        { "type": "vector-wide", "datatypes": all_defs, "mask_variants": all_defs, "implem":
"""
%v<c:int|b:32>% res = 0;
for (size_t i = 0; i < %N<tp>%; i++) // early termination is possible here but won't help the compiler vectorizer
	res += m0.m[i] == 0 ? 0 : 1;
return res ? 0 : 1;
"""
        },
    ],
    "hadd": [ # -------------------------------------------------------------------------------------------------- hadd
        { "type": "vector-wide", "datatypes": all_defs, "mask_variants": all_defs, "implem":
"""
%v<tr>% resv = 0;
for (size_t i = 0; i < %N<tp>%; i++)
	resv +=  %!pred_cond!%  r0.r[i] %!pred_alt!%;
return resv;
"""
        },
    ],
    "hadds": [ # ------------------------------------------------------------------------------------------------ hadds
        { "type": "vector-wide", "datatypes": [uint64], "mask_variants": all_defs, "implem":
"""
uint64_t resv64 = 0;
for (size_t i = 0; i < %N<tp>%; i++)
{
	uint64_t a = r0.r[i];
	uint64_t b = resv64;
    
	resv64 =
		(a > UINT64_MAX - b) ? UINT64_MAX :
		(uint64_t)(a + b);
}
    return resv64;
"""
        },
        { "type": "vector-wide", "datatypes": [uint32,uint16,uint8], "mask_variants": all_defs, "implem":
"""
uint64_t resv64 = 0;
%v<tr>% resv;
for (size_t i = 0; i < %N<tp>%; i++){
	resv64 += r0.r[i];

    resv =
        resv64 > UINT{{ dt_par.n_bits }}_MAX ? (%v<tr>%)UINT{{ dt_par.n_bits }}_MAX :
        (%v<tr>%)resv64;
}
return resv;


"""
        },
        { "type": "vector-wide", "datatypes": [int64], "mask_variants": all_defs, "implem":
"""
int64_t resv64 = 0;
for (size_t i = 0; i < %N<tp>%; i++)
{
	int64_t a = r0.r[i];
	int64_t b = resv64;

	resv64 =
		(b > 0 && a > INT64_MAX - b) ? (int64_t)INT64_MAX :
		(b < 0 && a < INT64_MIN - b) ? (int64_t)INT64_MIN :
		(int64_t)(a + b);
}
return resv64;
"""
        },
        { "type": "vector-wide", "datatypes": [int32,int16,int8], "mask_variants": all_defs, "implem":
"""
int64_t resv64 = 0;
%v<tr>% resv;
for (size_t i = 0; i < %N<tp>%; i++){
	resv64 += r0.r[i];

    resv =
	    resv64 > INT{{ dt_par.n_bits }}_MAX ? (%v<tr>%)INT{{ dt_par.n_bits }}_MAX :
	    resv64 < INT{{ dt_par.n_bits }}_MIN ? (%v<tr>%)INT{{ dt_par.n_bits }}_MIN :
        (%v<tr>%)resv64;
}
return resv;
"""
        },
    ],
    "hmul": [ # -------------------------------------------------------------------------------------------------- hmul
        { "type": "vector-wide", "datatypes": all_defs, "mask_variants": all_defs, "implem":
"""
%v<tr>% resv = 1;
for (size_t i = 0; i < %N<tp>%; i++)
	resv *=  %!pred_cond!% r0.r[i] %!pred_alt!%;

return resv;
"""
        },
    ],
    "hmin": [ # -------------------------------------------------------------------------------------------------- hmin
        { "type": "vector-wide", "datatypes": all_uint, "mask_variants": all_defs, "implem":
"""
%v<tr>% resv = UINT{{ dt_par.n_bits }}_MAX;
for (size_t i = 0; i < %N<tp>%; i++) // start from 0 to ease compiler autovec
	resv = %!pred_cond!% (r0.r[i] < resv) ? r0.r[i] : resv %!pred_alt!%;
return resv;
"""
        },
        { "type": "vector-wide", "datatypes": all_int, "mask_variants": all_defs, "implem":
"""%v<tr>% resv = INT{{ dt_par.n_bits }}_MAX;
for (size_t i = 0; i < %N<tp>%; i++) // start from 0 to ease compiler autovec
    resv = %!pred_cond!% (r0.r[i] < resv) ? r0.r[i] : resv %!pred_alt!%;
return resv;
"""
        },
        { "type": "vector-wide", "datatypes": [float32], "mask_variants": all_defs, "implem":
"""%v<tr>% resv = FLT_MAX;
for (size_t i = 0; i < %N<tp>%; i++) // start from 0 to ease compiler autovec
    resv = %!pred_cond!% (r0.r[i] < resv) ? r0.r[i] : resv %!pred_alt!%;
return resv;
"""
        },
        { "type": "vector-wide", "datatypes": [float64], "mask_variants": all_defs, "implem":
"""%v<tr>% resv = DBL_MAX;
for (size_t i = 0; i < %N<tp>%; i++) // start from 0 to ease compiler autovec
    resv = %!pred_cond!% (r0.r[i] < resv) ? r0.r[i] : resv %!pred_alt!%;
return resv;
"""
        },
    ],
    "hmax": [ # -------------------------------------------------------------------------------------------------- hmax
        { "type": "vector-wide", "datatypes": all_uint, "mask_variants": all_defs, "implem":
"""
%v<tr>% resv = 0;
for (size_t i = 0; i < %N<tp>%; i++) // start from 0 to ease compiler autovec
	resv =   %!pred_cond!% (r0.r[i] > resv) ? r0.r[i] : resv %!pred_alt!%;
return resv;
"""
        },
        { "type": "vector-wide", "datatypes": all_int, "mask_variants": all_defs, "implem":
"""%v<tr>% resv = INT{{ dt_par.n_bits }}_MIN;
for (size_t i = 0; i < %N<tp>%; i++) // start from 0 to ease compiler autovec
    resv = %!pred_cond!% (r0.r[i] > resv) ? r0.r[i] : resv %!pred_alt!%;
return resv;
"""
        },
        { "type": "vector-wide", "datatypes": [float32], "mask_variants": all_defs, "implem":
"""%v<tr>% resv = -FLT_MAX;
for (size_t i = 0; i < %N<tp>%; i++) // start from 0 to ease compiler autovec
    resv = %!pred_cond!% (r0.r[i] > resv) ? r0.r[i] : resv %!pred_alt!%;
return resv;
"""
        },
        { "type": "vector-wide", "datatypes": [float64], "mask_variants": all_defs, "implem":
"""%v<tr>% resv = -DBL_MAX;
for (size_t i = 0; i < %N<tp>%; i++) // start from 0 to ease compiler autovec
    resv = %!pred_cond!% (r0.r[i] > resv) ? r0.r[i] : resv %!pred_alt!%;
return resv;
"""
        },
    ],
    "hadd_to_scal": [ # ---------------------------------------------------------------------------------- hadd_to_scal
        { "type": "vector-wide", "datatypes": all_defs, "mask_variants": all_defs, "implem":
"""
%v<tr>% resv = 0;
for (size_t i = 0; i < %N<tp>%; i++)
	resv += r0.r[i];
return resv;
"""
        },
    ],
     "hadds_to_scal": [ # ------------------------------------------------------------------------------- hadds_to_scal
        { "type": "vector-wide", "datatypes": [uint64], "mask_variants": all_defs, "implem":
"""
uint64_t resv64 = 0;
for (size_t i = 0; i < %N<tp>%; i++)
{
	uint64_t a = r0.r[i];
	uint64_t b = resv64;
	resv64 =
		(a > UINT64_MAX - b) ? UINT64_MAX :
		(uint64_t)(a + b);
}
return resv64;
"""
        },
        { "type": "vector-wide", "datatypes": [uint32,uint16,uint8], "mask_variants": all_defs, "implem":
"""
uint64_t resv64 = 0;
for (size_t i = 0; i < %N<tp>%; i++)
	resv64 += r0.r[i];

%v<tr>% resv =
	resv64 > UINT{{ dt_par.n_bits }}_MAX ? (%v<tr>%)UINT{{ dt_par.n_bits }}_MAX :
	(%v<tr>%)resv64;

return resv;
"""
        },
        { "type": "vector-wide", "datatypes": [int64], "mask_variants": all_defs, "implem":
"""
int64_t resv64 = 0;
for (size_t i = 0; i < %N<tp>%; i++)
{
	int64_t a = r0.r[i];
	int64_t b = resv64;

	resv64 =
		(b > 0 && a > INT64_MAX - b) ? (int64_t)INT64_MAX :
		(b < 0 && a < INT64_MIN - b) ? (int64_t)INT64_MIN :
		(int64_t)(a + b);
}
return resv64;
"""
        },
        { "type": "vector-wide", "datatypes": [int32,int16,int8], "mask_variants": all_defs, "implem":
"""
int64_t resv64 = 0;
for (size_t i = 0; i < %N<tp>%; i++)
	resv64 += r0.r[i];

%v<tr>% resv =
	resv64 > INT{{ dt_par.n_bits }}_MAX ? (%v<tr>%)INT{{ dt_par.n_bits }}_MAX :
	resv64 < INT{{ dt_par.n_bits }}_MIN ? (%v<tr>%)INT{{ dt_par.n_bits }}_MIN :
	(%v<tr>%)resv64;

return resv;
"""
        },
    ],
    "maskz_add": [ # ---------------------------------------------------------------------------------------- maskz_add
        { "type": "element-wide", "datatypes": all_defs, "mask_variants": all_defs, "implem":
"""
res.r[i] = m0.m[i] ? r0.r[i] + r1.r[i] : 0;
"""
        },
    ],
    "fnmadd": [ # ---------------------------------------------------------------------------------------------- fnmadd
        { "type": "element-wide", "datatypes": all_defs, "mask_variants": all_defs, "implem":
"""
res.r[i] = %!pred_cond!% -(r0.r[i] * r1.r[i]) + r2.r[i] %!pred_alt!%;
"""
        },
    ],
    "fnmsub": [ # ---------------------------------------------------------------------------------------------- fnmsub
        { "type": "element-wide", "datatypes": all_defs, "mask_variants": all_defs, "implem":
"""
res.r[i] = %!pred_cond!% -(r0.r[i] * r1.r[i]) - r2.r[i] %!pred_alt!%;
"""
        },
    ],
    "div2": [ # -------------------------------------------------------------------------------------------------- div2
        { "type": "element-wide", "datatypes": all_int + all_uint, "mask_variants": all_defs, "implem":
"""
res.r[i] = %!pred_cond!% r0.r[i] >> 1 %!pred_alt!%;
"""
        },
        { "type": "element-wide", "datatypes": [float64], "mask_variants": all_defs, "implem":
"""
res.r[i] = %!pred_cond!% r0.r[i] / 2.0 %!pred_alt!%;
"""
        },
        { "type": "element-wide", "datatypes": [float32], "mask_variants": all_defs, "implem":
"""
res.r[i] = %!pred_cond!% r0.r[i] / 2.f %!pred_alt!%;
"""
        },
    ],
    "div4": [ # -------------------------------------------------------------------------------------------------- div4
        { "type": "element-wide", "datatypes": all_int + all_uint, "mask_variants": all_defs, "implem":
"""
res.r[i] = %!pred_cond!% r0.r[i] >> 2 %!pred_alt!%;
"""
        },
        { "type": "element-wide", "datatypes": [float64], "mask_variants": all_defs, "implem":
"""
res.r[i] = %!pred_cond!% r0.r[i] / 4.0 %!pred_alt!%;
"""
        },
        { "type": "element-wide", "datatypes": [float32], "mask_variants": all_defs, "implem":
"""
res.r[i] = %!pred_cond!% r0.r[i] / 4.f %!pred_alt!%;
"""
        },
    ],
    "rshift": [ # ---------------------------------------------------------------------------------------------- rshift
        { "type": "element-wide", "datatypes": all_int + all_uint, "mask_variants": all_defs, "implem":
"""
res.r[i] = %!pred_cond!% r0.r[i] >> v0 %!pred_alt!%;
"""
        },
        { "type": "element-wide", "datatypes": all_float, "mask_variants": all_defs, "implem":
"""
%v<c:uint|b:tp>% r0i;
BIT_CAST_1(&r0i, &r0.r[i]);
r0i >>= v0;
%v<tr>% resv;
BIT_CAST_1(&resv, &r0i);
res.r[i] = %!pred_cond!% resv %!pred_alt!%;
"""
        },
    ],
    "lshift": [ # ---------------------------------------------------------------------------------------------- lshift
        { "type": "element-wide", "datatypes": all_int + all_uint, "mask_variants": all_defs, "implem":
"""
res.r[i] = %!pred_cond!% r0.r[i] << v0 %!pred_alt!%;
"""
        },
        { "type": "element-wide", "datatypes": all_float, "mask_variants": all_defs, "implem":
"""
%v<c:uint|b:tp>% r0i;
BIT_CAST_1(&r0i, &r0.r[i]);
r0i <<= v0;
%v<tr>% resv;
BIT_CAST_1(&resv, &r0i);
res.r[i] = %!pred_cond!% resv %!pred_alt!%;
"""
        },
    ],

    "gather": [ # ---------------------------------------------------------------------------------------------- gather
        { "type": "element-wide", "datatypes": all_defs, "mask_variants": all_defs, "implem":
"""
res.r[i] = %!pred_cond!% p0[r0.r[i]] %!pred_alt!%;
"""
        },
    ],

    "scatter": [ # --------------------------------------------------------------------------------------------- scatter
        { "type": "element-wide", "datatypes": all_defs, "mask_variants": ["no_mask", "maskz"], "implem":
"""p0[r0.r[i]] = %!pred_cond!% r1.r[i] %!pred_alt!%;
"""
        },
        { "type": "element-wide", "datatypes": all_defs, "mask_variants": ["mask"], "implem":
"""if (m0.m[i]) p0[r0.r[i]] = r1.r[i];"""
        },
    ],


    "exp": [ # -------------------------------------------------------------------------------------------------- exp
        { "type": "element-wide", "datatypes": [float32], "mask_variants": all_defs, "implem":
"""
res.r[i] = %!pred_cond!% EXPF(r0.r[i]) %!pred_alt!%;
"""
        },
        { "type": "element-wide", "datatypes": [float64], "mask_variants": all_defs, "implem":
"""res.r[i] = %!pred_cond!% EXPD(r0.r[i]) %!pred_alt!%;
"""
        },
    ],

    "log": [ # -------------------------------------------------------------------------------------------------- log
        { "type": "element-wide", "datatypes": [float32], "mask_variants": all_defs, "implem":
"""
res.r[i] = %!pred_cond!% LOGF(r0.r[i]) %!pred_alt!%;
"""
        },
        { "type": "element-wide", "datatypes": [float64], "mask_variants": all_defs, "implem":
"""res.r[i] = %!pred_cond!% LOGD(r0.r[i]) %!pred_alt!%;
"""
        },
    ],
    "pow2": [ # ------------------------------------------------------------------------------------------------- pow2
        { "type": "element-wide", "datatypes": [float32], "mask_variants": all_defs, "implem":
"""
    res.r[i] = %!pred_cond!% POWF(2.f, r0.r[i]) %!pred_alt!%;
"""
        },
        { "type": "element-wide", "datatypes": [float64], "mask_variants": all_defs, "implem":
"""
    res.r[i] = %!pred_cond!% POW(2., r0.r[i]) %!pred_alt!%;
"""
        },
    
        {"type": "element-wide", "datatypes": all_uint, "mask_variants": all_defs, "implem":
"""
    res.r[i] = %!pred_cond!% 1ULL << r0.r[i] %!pred_alt!%;
""" },
        {"type": "vector-wide", "datatypes": all_int, "mask_variants": all_defs, "implem":
"""
%r<tp>% res;
for (size_t i = 0; i < %N<tp>%; i++){
    res.r[i] = %!pred_cond!% 1 << (uint8_t)r0.r[i] %!pred_alt!%;
}
return res;
""" },
],

#     "pow": [ # -------------------------------------------------------------------------------------------------- pow
#         { "type": "element-wide", "datatypes": [float32], "mask_variants": all_defs, "implem":
# """res.r[i] = %!pred_cond!% POWF(r0.r[i], v0) %!pred_alt!%;
# """
#         },
#         { "type": "element-wide", "datatypes": [float64], "mask_variants": all_defs, "implem":
# """res.r[i] = %!pred_cond!% POW(r0.r[i], v0) %!pred_alt!%;
# """
#         },

#         { "type": "vector-wide", "datatypes": all_int + all_uint, "mask_variants": all_defs, "implem":
# """
#     %r<tp>% res;

#     for (int32_t i = 0; i < v0; i++){
#         for (size_t j = 0; j < %N<tp>%; j++){
#             res.r[j] = %!pred_cond!% res.r[j] * r0.r[j] %!pred_alt!%;
#         }
#     }
#     return resv;
# """}]
}

copy_mipp_funcs = copy.deepcopy(mipp_funcs)
