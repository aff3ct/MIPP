"""
Implementation Tracker Module
Manages functions implementation status (implem_status) and preprocessor (#if/#endif) guards generation.
"""
import sys
import os

# Add parent directory to sys.path to find tools.py
sys.path.insert(1, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

from tools import *

def missing_build_negated_ifdef_for_existing_implems(funcs, f, dt_key, mask_kind=None):
    ifd = ""
    bucket = get_implem_bucket(funcs, f, dt_key, mask_kind)
    if bucket is not None:
        is_first = True
        for i in range(len(bucket)):
            ifd_sub = (build_ifdef_masked(funcs, f, dt_key, mask_kind, i)
                       if mask_kind is not None
                       else build_ifdef(funcs, f, dt_key, i))
            if ifd_sub:
                if not is_first:
                    ifd = ifd + " && "
                ifd = ifd + "!( " + ifd_sub + " )"
                is_first = False
    return ifd

def is_masked_implem(f, ff):
    """
    temporary skip of masks
    """
    if "version" in ff and ff["version"]:
        return True
    return False

def get_implem_bucket(funcs, f, dt_key, mask_kind=None, create=False):
    if mask_kind is None:
        if create:
            if "implem_status" not in funcs[f]:
                funcs[f]["implem_status"] = {}
            if dt_key not in funcs[f]["implem_status"]:
                funcs[f]["implem_status"][dt_key] = []
        if "implem_status" in funcs[f] and dt_key in funcs[f]["implem_status"]:
            return funcs[f]["implem_status"][dt_key]
        return None
    else:
        return get_masked_bucket(funcs, f, dt_key, mask_kind, create_missing_bucket=create)

def build_prev_exclusion_ifdef(funcs, f, dt_key, ff, mask_kind=None):
    ifd = ""
    if "type" in ff and ff["type"] == "emulated":
        ifd = missing_build_negated_ifdef_for_existing_implems(funcs, f, dt_key, mask_kind=mask_kind)
    return ifd

def append_implem_status(funcs, f, dt_key, ff, requirements, mask_kind=None):
    cur_implem_status = {"if": "", "requirements": {}}
    if "if" in ff:
        cur_implem_status["if"] = ff["if"]
    cur_implem_status["requirements"] = requirements

    bucket = get_implem_bucket(funcs, f, dt_key, mask_kind, create=True)
    bucket.append(cur_implem_status)

def combine_current_ifdefs(funcs, f, dt_key, ifd_prev, mask_kind=None):
    bucket = get_implem_bucket(funcs, f, dt_key, mask_kind)
    if bucket is None:
        return ifd_prev

    ifd_cur = (build_ifdef_masked(funcs, f, dt_key, mask_kind, len(bucket) - 1)
               if mask_kind is not None
               else build_ifdef(funcs, f, dt_key, len(bucket) - 1))

    if ifd_prev and ifd_cur:
        return simplify_cond_str(ifd_prev + " && (" + ifd_cur + ")")
    elif ifd_cur:
        return simplify_cond_str(ifd_cur)
    return simplify_cond_str(ifd_prev)

def update_emulated(funcs, f, dt_key, ff, ifd, mask_kind=None):
    if "type" in ff and ff["type"] == "emulated":
        bucket = get_implem_bucket(funcs, f, dt_key, mask_kind)
        if bucket:
            bucket[len(bucket) - 1]["if"] = ifd

def _gen_isdef_neg(funcs, f, dt_key):
    """
    generates the negation of an ifdef.
    """
    ret = build_ifdef_rec(funcs, f, dt_key)
    return "#if !" + ret + "" if ret else ""

def _add_guard_if_isdef(funcs, f, dt_key, file):
    """
    used in gen_c_generic_functions, creates the negation of an ifdef and writes it to the file. 
    It's used to guard the generic implementation with the negation of the conditions of previous implementations, if any.
    """
    if is_ifdef(funcs, f, dt_key):
        guard = _gen_isdef_neg(funcs, f, dt_key)
        print(guard, file=file)

def _add_endif_if_isdef(funcs, f, dt_key, file):
    """
    used in combination with _add_guard_if_isdef, writes #endif to file if there was an ifdef.
    """
    if is_ifdef(funcs, f, dt_key):
        print("#endif", file=file)
