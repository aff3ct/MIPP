from .common import set_skip_float, set_remove_k, test_function_name
#from .layer_c import gen_test_dict as gen_test_dict_c
#from .layer_cpp import gen_test_dict as gen_test_dict_cpp
#from .layer_obj import gen_test_dict as gen_test_dict_obj

def get_gen_test_dict(kind: str) -> dict:
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