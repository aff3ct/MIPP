"""
Software LMUL Module
Writes the bodies that an ISA gives itself, in `simd_ext/<isa>/<isa>_sw_lmul.json`, for the functions that
change a software LMUL (a struct of two LMUL 1 registers `r1` / `r2`): wcvt m1 -> m2 and ncvt m2 -> m1.
Without an entry, lmul_orchestrator writes the generic bodies (low / high and the half-vector conversions,
or combine); with one, it skips them (has_sw_lmul_entry). The entries are rendered by the half-vector
template engine (ldiv_mask._emit_one): Jinja2 + templating DSL, level detected with the audit rules.
"""
import os
import sys

# Add parent directory to sys.path to find tools.py
sys.path.insert(1, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

from tools import *
from input_validation import validate_sw_lmul_config
from codegen.ldiv_mask import _emit_one


def _load_entries(isa, funcs):
    """The entries of `<isa>_sw_lmul.json`, validated: {function: [entries]}."""
    path = sw_lmul_path(isa)
    entries = sw_lmul_entries(isa)
    label = os.path.relpath(path, os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))
    validate_sw_lmul_config(entries, label)
    sw = [int(x) for x in isa.get("sw_lmul", [])]
    hw = [int(x) for x in isa.get("hw_lmul", [1])]
    if 2 not in sw or 2 in hw:
        print(f"in {os.path.basename(path)} : error : '{isa['name']}' has no software LMUL 2 registers")
        sys.exit(1)
    for f, f_entries in entries.items():
        if f not in funcs:
            print(f"in {os.path.basename(path)} : error : unknown function '{f}'")
            sys.exit(1)
        for entry in f_entries:
            dts = entry.get("datatypes", "all_datatypes")
            for dt in ([] if dts == "all_datatypes" else dts):
                if dt not in datatypes:
                    print(f"in {os.path.basename(path)} : error : unknown datatype '{dt}' for '{f}'")
                    sys.exit(1)
    # entries of an ISA file: the level is detected from the code (see ldiv_mask._auto_level)
    return {f: [dict(e, _dedicated=True) for e in f_entries] for f, f_entries in entries.items()}


def gen_c_sw_lmul(isa, include_manager, funcs):
    """Writes the wcvt m1 -> m2 / ncvt m2 -> m1 bodies given by the ISA, before lmul_orchestrator."""
    if not sw_lmul_entries(isa):
        return
    templates = _load_entries(isa, funcs)
    for f, lmul in SW_LMUL_FUNCS.items():
        if f not in templates or not isa_provides_lmul(isa, funcs[f]["proto"], lmul):
            continue

        def record_call(func, variant, callee, callee_variant, lmul=lmul):
            include_manager.add_call_dependency(isa["name"], func, variant, f"m{lmul}", callee, callee_variant, "m1")

        file_w = include_manager.get_fd(isa["name"], f, variant="u", lmul=lmul)
        for dt in funcs[f]["datatypes"]:
            dt_par, _ = compute_dt_par_dt_ret(funcs, f, dt)
            if has_sw_lmul_entry(isa, f, lmul, dt_par):
                _emit_one(isa, file_w, funcs, templates, f, dt, None, record_call, lmul_in=lmul, sw_lmul=True)
