from .common import set_skip_float, set_remove_k, test_function_name

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
    raise ValueError(f"Unknown kind: {kind!r}")