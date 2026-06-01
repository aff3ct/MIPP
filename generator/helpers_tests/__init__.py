from .common import set_float_workaround, set_remove_k, test_function_name

def get_gen_test_dict(kind: str):
    if kind == "c":
        from . import layer_c
        return layer_c.gen_test_dict
    if kind == "cpp":
        from . import layer_cpp
        return layer_cpp.gen_test_dict
    if kind == "obj":
        from . import layer_obj
        return layer_obj.gen_test_dict
    raise ValueError(f"Unknown kind: {kind}")

def get_gen_test_dict_lmul(kind: str):
    if kind == "c":
        from . import layer_c_lmul
        return layer_c_lmul.gen_test_dict_lmul
    if kind == "cpp":
        from . import layer_cpp_lmul
        return layer_cpp_lmul.gen_test_dict_lmul
    if kind == "obj":
        from . import layer_obj_lmul
        return layer_obj_lmul.gen_test_dict_lmul
    raise ValueError(f"Unknown kind: {kind}")

def get_gen_test_dict_mask(kind: str):
    if kind == "c":
        from . import layer_c_mask
        return layer_c_mask.gen_test_dict_mask
    if kind == "cpp":
        from . import layer_cpp_mask
        return layer_cpp_mask.gen_test_dict_mask
    if kind == "obj":
        return {}
    raise ValueError(f"Unknown kind: {kind}")