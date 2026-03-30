from __future__ import annotations

from dataclasses import dataclass
from typing import Optional

# --------------------------------------------
# Miscelaneous utilities for layers
# --------------------------------------------

set_skip_float = {"andb", "orb", "xorb", "notb", "andnb", "notb_k", "msb"}
set_remove_k = {"andb_k", "orb_k", "xorb_k", "andnb_k", "notb_k"}

def test_function_name(kind: str, func: str):
    if kind in ("cpp", "obj") and func in set_remove_k:
        return func.replace("_k", "")
    return func


operators_binary_mask = {
    "xorb_k"   : {"operation" : "^", "option"  : "^="},
    "orb_k"    : {"operation" : "|", "option"  : "|="},
    "andb_k"   : {"operation" : "&", "option"  : "&="},
}

operators_reduction = {
    "hadd" : {"operation" : "+="},
    "hmul" : {"operation" : "*="},
}

# --------------------------------------------
# Shapes 
# --------------------------------------------

SHAPE_RET_REG_1ARG_PTR = "ret_reg_1arg_ptr"
SHAPE_RET_REG_2ARGS_MASK_PTR = "ret_reg_2args_msk_ptr"
SHAPE_RET_VOID_3ARGS_PTR_MSK_REG = "ret_void_3args_ptr_msk_reg"
SHAPE_RET_VOID_2ARGS_PTR_REG = "ret_void_2args_ptr_reg"
SHAPE_RET_REG_2ARGS_PTR_VINDEX = "ret_reg_2args_ptr_vindex"
SHAPE_RET_REG_3ARGS_PTR_VINDEX_MSK = "ret_reg_3args_ptr_vindex_msk"
SHAPE_RET_REG_1ARG_VAL = "ret_reg_1arg_val"
SHAPE_RET_REG_1ARG_NELE = "ret_reg_1arg_Nele"
SHAPE_RET_MSK_1ARG_NELE = "ret_msk_1arg_Nele"
SHAPE_RET_REG_1ARG_I32 = "ret_reg_1arg_i32"
SHAPE_RET_MSK_1ARG_I32 = "ret_msk_1arg_i32"
SHAPE_RET_MSK_1ARG_VAL = "ret_msk_1 arg_val"
SHAPE_RET_REG_0ARG = "ret_reg_0arg"
SHAPE_RET_MSK_0ARG = "ret_msk_0arg"
SHAPE_RET_REG_1ARG_REG = "ret_reg_1arg_reg"
SHAPE_RET_VAL_1ARG_REG = "ret_val_1arg_reg"
SHAPE_RET_MSK_1ARG_MSK = "ret_msk_1arg_msk"
SHAPE_RET_MSK_1ARG_REG = "ret_msk_1arg_reg"
SHAPE_RET_REG_1ARG_MSK = "ret_reg_1arg_msk"
SHAPE_RET_REG_2ARGS_REG = "ret_reg_2args_reg"
SHAPE_RET_REG_2ARGS_REG_MSK = "ret_reg_2args_reg_msk"
SHAPE_RET_MSK_2ARGS_REG = "ret_msk_2args_reg"
SHAPE_RET_MSK_2ARGS_MSK = "ret_msk_2args_msk"
SHAPE_RET_REG_2ARGS_REG_VAL = "ret_reg_2args_reg_val"
SHAPE_RET_REG_3ARGS_REG = "ret_reg_3args_reg"
SHAPE_RET_REG_3ARGS_2REG_1MSK = "ret_reg_3args_2reg_1msk"
SHAPE_RET_REG_3ARGS_1REG = "ret_reg_3args_1reg_2val"
SHAPE_RET_REG_3ARGS_1MSK_2REG = "ret_reg_3args_1msk_2reg"
SHAPE_RET_I32_1ARG_MSK = "ret_i32_1arg_msk"
SHAPE_RET_I32_2ARGS_MSK = "ret_i32_2args_msk"
SHAPE_RET_VAL_2ARGS_REG_VAL = "ret_val_2args_reg_val"
SHAPE_RET_VAL_2ARGS_MSK_VAL = "ret_val_2args_msk_val"


SUPPORTED_SHAPES = {
    SHAPE_RET_REG_2ARGS_REG, #shape for airthmetic and bitwise binary operators
    SHAPE_RET_MSK_2ARGS_REG, #shape for comparison operators (cmp_2reg)
    SHAPE_RET_REG_1ARG_PTR,
    SHAPE_RET_VOID_2ARGS_PTR_REG,
    SHAPE_RET_REG_1ARG_NELE, #shape for set only
    SHAPE_RET_MSK_1ARG_NELE, #shape for set_k only
    SHAPE_RET_REG_1ARG_VAL,
    SHAPE_RET_MSK_1ARG_I32,
    SHAPE_RET_REG_0ARG,
    SHAPE_RET_MSK_0ARG,
    SHAPE_RET_VAL_2ARGS_REG_VAL,
    SHAPE_RET_VAL_2ARGS_MSK_VAL,
    SHAPE_RET_VAL_1ARG_REG, #getfirst, hadd, hmul,...
    SHAPE_RET_REG_3ARGS_2REG_1MSK, #blend only
    SHAPE_RET_MSK_2ARGS_MSK, #shape for andb_k orb_k xorb_k andnb_k
    SHAPE_RET_MSK_1ARG_MSK, #shape for notb_k and cast_k
    SHAPE_RET_I32_2ARGS_MSK, #testz
    SHAPE_RET_I32_1ARG_MSK, #testz2
    SHAPE_RET_REG_3ARGS_1MSK_2REG, #for maskz_add. I wonder if its normal that's it's the "opposite order" from blend
    SHAPE_RET_MSK_1ARG_REG, #tomsk
    SHAPE_RET_REG_2ARGS_MASK_PTR, #maskz load
    SHAPE_RET_VOID_3ARGS_PTR_MSK_REG #shape for mask store (maskst)
}

def classify_mipp_proto(proto: dict):
    """
    proto is one of headers_def.protos[...] (ret/args with "type" keys).
    """
    ret_t = proto["ret"]["type"]              # "reg", "msk", "val", or False
    args_t = [a["type"] for a in proto["args"]]
    args_dt = [a["fixeddatatype"] for a in proto["args"]]
    ret_dt = proto["ret"]["fixeddatatype"]

    if ret_t == "reg" and args_t == ["reg", "reg"]:
        return SHAPE_RET_REG_2ARGS_REG
    if ret_t == "msk" and args_t == ["reg", "reg"]:
        return SHAPE_RET_MSK_2ARGS_REG
    if ret_t == "reg" and args_t == ["ptr"]:
        return SHAPE_RET_REG_1ARG_PTR
    if ret_t is False and args_t == ["ptr", "reg"]:
        return SHAPE_RET_VOID_2ARGS_PTR_REG
    if ret_t == "reg" and args_t == ["Nele"]:
        return SHAPE_RET_REG_1ARG_NELE
    if ret_t == "msk" and args_t == ["Nele"]:
        return SHAPE_RET_MSK_1ARG_NELE
    if ret_t == "reg" and args_t == ["val"]:
        return SHAPE_RET_REG_1ARG_VAL
    if ret_t == "msk" and args_t == ["val"] and args_dt == ["int32"]:
        return SHAPE_RET_MSK_1ARG_I32
    if ret_t == "reg" and args_t == []:
        return SHAPE_RET_REG_0ARG
    if ret_t == "msk" and args_t == []:
        return SHAPE_RET_MSK_0ARG
    if ret_t == "val" and args_t == ["reg", "val"]:
        return SHAPE_RET_VAL_2ARGS_REG_VAL
    if ret_t == "val" and args_t == ["msk", "val"]:
        return SHAPE_RET_VAL_2ARGS_MSK_VAL
    if ret_t == "val" and args_t == ["reg"]:
        return SHAPE_RET_VAL_1ARG_REG
    if ret_t == "reg" and args_t == ["reg", "reg", "msk"]:
        return SHAPE_RET_REG_3ARGS_2REG_1MSK
    if ret_t == "msk" and args_t == ["msk", "msk"]:
        return SHAPE_RET_MSK_2ARGS_MSK
    if ret_t == "reg" and args_t == ["reg"]:
        return SHAPE_RET_REG_1ARG_REG
    if ret_t == "msk" and args_t == ["msk"]:
        return SHAPE_RET_MSK_1ARG_MSK
    if ret_t == "reg" and args_t == ["msk"]:
        return SHAPE_RET_REG_1ARG_MSK
    if ret_t == "reg" and args_t == ["reg", "reg", "reg"]:
        return SHAPE_RET_REG_3ARGS_REG
    if ret_t == "val" and args_t == ["msk", "msk"] and ret_dt == "int32":
        return SHAPE_RET_I32_2ARGS_MSK
    if ret_t == "val" and args_t == ["msk"] and ret_dt == "int32":
        return SHAPE_RET_I32_1ARG_MSK
    if ret_t == "reg" and args_t == ["msk", "reg", "reg"]:
        return SHAPE_RET_REG_3ARGS_1MSK_2REG
    if ret_t == "msk" and args_t == ["reg"]:
        return SHAPE_RET_MSK_1ARG_REG
    if ret_t == "reg" and args_t == ["msk", "ptr"] and args_dt == ["int32", False]:
        return SHAPE_RET_REG_2ARGS_MASK_PTR
    if ret_t is False and args_t == ["ptr", "msk", "reg"]:
        return SHAPE_RET_VOID_3ARGS_PTR_MSK_REG
    return None

# --------------------------------------------
# Template contract expected by gen_files.py
# --------------------------------------------

@dataclass(frozen=True)
class TemplateParts:
    func_decl: str
    decl: str
    init: str
    load: str
    operation: str
    loop_body: str
    loop_assert: str

# --------------------------------------------
# 
# --------------------------------------------

def infer_op(func: str):
    """
    For arithmetic/binary/order operators, get the C++ operator symbol from tools.py maps.
    Returns "" for non-operators
    """
    from tools import operators_arithm, operators_binary, operators_order

    if func in operators_arithm:
        return operators_arithm[func]["operation"]
    if func in operators_binary:
        return operators_binary[func]["operation"]
    if func in operators_order:
        return operators_order[func]["operation"]
    if func in operators_binary_mask:
        return operators_binary_mask[func]["operation"]
    if func in operators_reduction:
        return operators_reduction[func]["operation"]
    return ""

# --------------------------------------------
# 
# --------------------------------------------

def infer_long_name(func: str):
    return func

def infer_short_name(func: str):
    return func

# --------------------------------------------
# Build gen_test_dict for a layer from mipp_funcs + shapes
# --------------------------------------------

def build_layer_gen_test_dict(
    *,
    layer_name: str,
    template: str,
    mipp_funcs: dict,
    shape_templates: dict[str, TemplateParts],
    deny_funcs: Optional[set[str]] = None,
):
    """
    Returns dict[func] with keys: template/long_name/short_name/op/proto.
    Skips funcs whose shape isn't implemented by this layer.
    """
    out = {}
    deny_funcs = deny_funcs or set()

    for func, meta in mipp_funcs.items():
        if func in deny_funcs:
            continue

        proto = meta["proto"]
        shape = classify_mipp_proto(proto)
        if shape is None:
            continue

        parts = shape_templates.get(shape)
        if parts is None:
            # layer doesn't implement this shape
            continue

        out[func] = {
            "template": template,
            "long_name": infer_long_name(func),
            "short_name": infer_short_name(func),
            "op": infer_op(func),
            "proto": {
                "func_decl": parts.func_decl,
                "decl": parts.decl,
                "init": parts.init,
                "load": parts.load,
                "operation": parts.operation,
                "loop_body": parts.loop_body,
                "loop_assert": parts.loop_assert,
            },
        }

    return out