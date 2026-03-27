# Shared helpers + function catalog (layer-agnostic)

# float support of logical operators is odd. Will come back to them later.
set_skip_float = {
    "andb",
    "orb",
    "xorb",
    "notb",
    "andnb",
}

# In cpp/obj some *_k are overloads without "_k" in the function name.
set_remove_k = {"andb_k", "orb_k", "xorb_k", "andnb_k", "notb_k"}

def test_function_name(kind: str, func: str):
    if kind in ("cpp", "obj") and func in set_remove_k:
        return func.replace("_k", "")
    return func

# -----------------------------------------------------------------------------
# Template key names (kept close to old code, but simplified)
# -----------------------------------------------------------------------------
K_FUNC_DECL = "func_decl"
K_DECL = "decl"
K_INIT = "init"
K_LOAD = "load"
K_OP = "operation"
K_LOOP_BODY = "loop_body"
K_LOOP_ASRT = "loop_assert"

def lang_proto(*, func_decl, decl, init, load, operation, loop_body, loop_assert):
    return {
        K_FUNC_DECL: func_decl,
        K_DECL: decl,
        K_INIT: init,
        K_LOAD: load,
        K_OP: operation,
        K_LOOP_BODY: loop_body,
        K_LOOP_ASRT: loop_assert,
    }

def override(proto: dict, **updates):
    out = dict(proto)
    out.update(updates)
    return out

def classify_proto(proto: dict):
    ret_t = proto["ret"]["type"]          # "reg", "msk", "val", False
    args_t = [a["type"] for a in proto["args"]]

    if ret_t == "reg" and args_t == ["reg", "reg"]:
        return "reg_2reg_binop"
    if ret_t == "msk" and args_t == ["reg", "reg"]:
        return "cmp_2reg"          # cmpeq/cmpgt/...
    if ret_t == "msk" and args_t == ["msk", "msk"]:
        return "msk_2msk_binop"
    if ret_t == "reg" and args_t == ["ptr"]:
        return "load"
    if ret_t is False and args_t == ["ptr", "reg"]:
        return "store"
    ...
    return "unknown"

# -----------------------------------------------------------------------------
# Function catalog (shared for all layers)
# proto_key selects which prototype to use for that layer.
# op is used in the 2-level templating in gen_files.py.
# -----------------------------------------------------------------------------
FUNCTION_SPECS = {
    # arithmetic
    "add":     dict(long_name="Addition",     short_name="add",     op="+",  proto_key="arith_2args"),
    "sub":     dict(long_name="Subtraction",  short_name="sub",     op="-",  proto_key="sub_2args"),
    "mul":     dict(long_name="Multiplication", short_name="mul",   op="*",  proto_key="arith_2args"),
    "div":     dict(long_name="Division",     short_name="div",     op="/",  proto_key="arith_2args"),
    "andb":    dict(long_name="Bitwise And",  short_name="andb",    op="&",  proto_key="arith_2args"),
    "orb":     dict(long_name="Bitwise Or",   short_name="orb",     op="|",  proto_key="arith_2args"),
    "xorb":    dict(long_name="Bitwise Xor",  short_name="xorb",    op="^",  proto_key="arith_2args"),

    # memory access
    "load":    dict(long_name="Load",         short_name="load",    op="",   proto_key="load"),
    "loadu":   dict(long_name="Load Unaligned", short_name="loadu", op="",   proto_key="load"),
    "store":   dict(long_name="Store",        short_name="store",   op="",   proto_key="store"),
    "storeu":  dict(long_name="Store Unaligned", short_name="storeu", op="", proto_key="store"),

    # set / get
    "set":     dict(long_name="Set",          short_name="set",     op="",   proto_key="set"),
    "set_k":   dict(long_name="Set Mask",     short_name="set_k",   op="",   proto_key="set_k"),
    "set1":    dict(long_name="Set to scalar", short_name="set1",   op="",   proto_key="set1"),
    "set1_k":  dict(long_name="Set Mask to scalar", short_name="set1_k", op="", proto_key="set1_k"),
    "set0":    dict(long_name="Set to zero",  short_name="set0",    op="",   proto_key="set0"),
    "set0_k":  dict(long_name="Set Mask to zero", short_name="set0_k", op="", proto_key="set0_k"),

    "get":     dict(long_name="Get",          short_name="get",     op="",   proto_key="load"),
    "getfirst":dict(long_name="Get First Lane", short_name="getfirst", op="", proto_key="getfirst"),
    "blend":   dict(long_name="Blend",        short_name="blend",   op="",   proto_key="blend"),

    # mask logical ops
    "andb_k":  dict(long_name="Bitwise And with Mask", short_name="andb_k", op="&", proto_key="logical_2ops_msk"),
    "orb_k":   dict(long_name="Bitwise Or with Mask",  short_name="orb_k",  op="|", proto_key="logical_2ops_msk"),
    "xorb_k":  dict(long_name="Bitwise Xor with Mask", short_name="xorb_k", op="^", proto_key="logical_2ops_msk"),

    "andnb_k": dict(long_name="Bitwise And Not with Mask", short_name="andnb_k", op="", proto_key="andnb_k"),
    "andnb":   dict(long_name="Bitwise And Not", short_name="andnb", op="", proto_key="andnb"),

    "notb":    dict(long_name="Bitwise Not", short_name="notb", op="~", proto_key="arith_1arg"),
    "notb_k":  dict(long_name="Bitwise Not with Mask", short_name="notb_k", op="~", proto_key="logi_1op_msk"),
    
    "cmpeq" : dict(long_name="Comparison equal", short_name="cmpeq", op="==", proto_key="arith_2args_r3msk"),
}

def mk_gen_test_dict(*, template: str, prototype_registry: dict):
    out = {}
    for func, spec in FUNCTION_SPECS.items():
        proto_key = spec["proto_key"]
        proto = prototype_registry.get(proto_key)
        if proto is None:
            print(KeyError + proto_key)
            continue

        out[func] = {
            "template": template,
            "long_name": spec["long_name"],
            "short_name": spec["short_name"],
            "op": spec["op"],
            "proto": proto,
        }
    return out