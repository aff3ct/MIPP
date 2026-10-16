"""
LMUL Orchestrator Module
Manages dynamic register grouping (LMUL) and divisions (LDIV) generation loops for RISC-V Vector
and horizontal reductions wrappers.
"""
import sys
import os

# Add parent directory to sys.path to find tools.py
sys.path.insert(1, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

from tools import *
from tools import build_func_name_internal
from codegen.implem_tracker import (
    append_implem_status,
    is_masked_implem,
    build_prev_exclusion_ifdef,
    combine_current_ifdefs,
)
from codegen.emit_helpers import (
    emit_ifdef_begin_and_update_emulated,
    emit_function_body,
    emit_ifdef_end,
    emit_panic_stub,
)
from codegen.candidate_resolver import render_template, parse_placeholders_or_skip

seen_lmul_separators = set()
seen_ldiv_separators = set()

def maybe_emit_lmul_separator(isa_name, f, file):
    key = (isa_name, f)
    if key not in seen_lmul_separators:
        seen_lmul_separators.add(key)
        print("", file=file)
        print("// " + "=" * 117, file=file)
        print("// " + " " * 113 + "LMUL", file=file)
        print("// " + "=" * 117, file=file)

def maybe_emit_ldiv_separator(isa_name, f, file):
    key = (isa_name, f)
    if key not in seen_ldiv_separators:
        seen_ldiv_separators.add(key)
        print("", file=file)
        print("// " + "=" * 117, file=file)
        print("// " + " " * 113 + "LDIV", file=file)
        print("// " + "=" * 117, file=file)

def _rvv_seen_lmul(funcs, f, dt_key, lmul):
    if "implem_status" in funcs[f]:
        if "lmul" in funcs[f]["implem_status"]:
            if (lmul, dt_key) in funcs[f]["implem_status"]["lmul"]:
                return True
    return False

def _rvv_mark_lmul_seen(funcs, f, dt_key, lmul):
    if "implem_status" not in funcs[f]:
        funcs[f]["implem_status"] = {}
    if "lmul" in funcs[f]["implem_status"]:
        funcs[f]["implem_status"]["lmul"].add((lmul, dt_key))
    else:
        funcs[f]["implem_status"]["lmul"] = {(lmul, dt_key)}

def _rvv_seen_lmul_masked(funcs, f, dt_key, mask_kind, lmul):
    bucket = get_masked_bucket(funcs, f, dt_key, mask_kind)
    if not bucket:
        return False
    last = bucket[-1]
    return "lmul" in last and (lmul, dt_key) in last["lmul"]

def _rvv_mark_lmul_seen_masked(funcs, f, dt_key, mask_kind, lmul):
    bucket = get_masked_bucket(funcs, f, dt_key, mask_kind)
    if not bucket:
        return
    last = bucket[-1]
    if "lmul" in last:
        last["lmul"].add((lmul, dt_key))
    else:
        last["lmul"] = {(lmul, dt_key)}

def _gen_c_horiz_lmul_one(isa, file, funcs, f, ff, dt, lmul, mkind=None, dummy=False):
    dt_par, dt_ret = compute_dt_par_dt_ret(funcs, f, dt)
    dt_key = dt_par + "," + dt_ret

    if _rvv_seen_lmul(funcs, f, dt_key, lmul) and mkind is None:
        return

    def _ensure_fake_implemented(func_name, dep_dt_key):
        if func_name not in funcs:
            return
        if "implem_status" not in funcs[func_name]:
            funcs[func_name]["implem_status"] = {}
        if dep_dt_key not in funcs[func_name]["implem_status"]:
            funcs[func_name]["implem_status"][dep_dt_key] = [{"if": "", "requirements": {}}]

    ff_local = dict(ff)
    ff_local["type"] = "emulated"

    pre_rendering = render_template(isa, ff_local, dt_par, dt_ret, func_name=f, lmul=lmul, mask_kind=mkind)
    requirements = get_requirements(
        ir=pre_rendering,
        isa=isa,
        funcs=funcs,
        func_name=f,
        dt_par=dt_par,
        dt_ret=dt_ret,
        lmul=lmul,
        isa_name=False,
    )
    
    for req in requirements:
        for req_dt_key in requirements[req]:
            _ensure_fake_implemented(req, req_dt_key)

    isa_name = dummy
    ph_ret = parse_placeholders_or_skip(
        pre_rendering=pre_rendering,
        isa=isa,
        funcs=funcs,
        f=f,
        dt_par=dt_par,
        dt_ret=dt_ret,
        dt_key=dt_key,
        file=file,
        lmul=lmul,
        isa_name=isa_name,
    )
    if ph_ret is None:
        return

    if dummy:
        dt_par, dt_ret = compute_dt_par_dt_ret(funcs, f, dt)
        func_name = build_func_name_internal(isa, dt, dt_par, dt_ret, f, masked_version=mkind, lmul=lmul)
        proto = build_proto(funcs[f]["proto"], dt_par, dt_ret, isa, func_name, lmul=lmul, isa_name=True, masked_version=mkind)
        print("\nstatic " + proto + " {", file=file)
        print("\t// Level 2 (Generic Emulation)", file=file)


    lines = [line for line in ph_ret["converted_ir"].split("\n") if line.strip()]
    for line in lines:
        if not line.startswith("\t"):
            line = "\t" + line
        print(line, file=file)

    if dummy:
        print("}", file=file)

    _rvv_mark_lmul_seen(funcs, f, dt_key, lmul)    
    append_implem_status(funcs, f, dt_key, ff, ph_ret["requirements"])

def gen_c_horiz_lmul(isa, file, funcs, f, dt, lmul, implems_horiz_lmul_generic_emu, func_name_for_panic=None, mask_type=None, dummy=False):
    if lmul <= 1:
        return

    if f not in funcs:
        print("Panic: '" + f + "' function does not exist.")
        exit(-1)

    if not funcs[f].get("horizontal", False):
        return

    if mask_type is not None:
        variant_set = funcs[f]["variants"]
        if not variant_set.is_supported(mask_type):
            print(f"Panic: unsupported mask type '{mask_type}' for '{f}' function.")
            exit(-1)

    if f not in implems_horiz_lmul_generic_emu:
        name = func_name_for_panic or f
        emit_panic_stub(f"{name}_m{int(lmul)}", file=file)
        return

    emitted_any = False
    for ff in implems_horiz_lmul_generic_emu[f]:
        if ff_mask_kind(ff) not in (None, "horiz_lmul"):
            continue
        if "datatypes" in ff and dt not in ff["datatypes"]:
            continue

        _gen_c_horiz_lmul_one(isa=isa, file=file, funcs=funcs, f=f, ff=ff, dt=dt, lmul=lmul, mkind=mask_type, dummy=dummy)
        emitted_any = True

    if not emitted_any:
        name = func_name_for_panic or f
        emit_panic_stub(f"{name}_m{int(lmul)}", file=file)

def _c_lmul_widening_writer(f, dt_par, dt_ret, isa, funcs, file, func_name_lmul, lmul, include_manager):
    """
    wcvt from LMUL 1 or a software LMUL (a struct of two halves) to the next one: each half of the
    result is the conversion of one half of the argument (`low` / `high` then the d2 -> m1
    conversion for m1 -> m2, the conversion of the halves of one LMUL below otherwise).
    """
    proto = funcs[f]["proto"]
    res_type = build_type("reg", datatypes[dt_ret], isa, resolve_ret_lmul(proto["ret"], lmul), True)
    print("\nstatic " + build_proto(proto, dt_par, dt_ret, isa, func_name_lmul, lmul=lmul, isa_name=True) + " {", file=file)
    print("\t// Level 2 (Generic Emulation): each half of the result converts one half of the argument", file=file)
    print(f"\t{res_type} res;", file=file)
    if lmul == 1:
        low = build_func_name_short(isa, dt_par, "low", True, lmul=1)
        high = build_func_name_short(isa, dt_par, "high", True, lmul=1)
        conv = build_func_name(isa, dt_par, dt_ret, f, True, lmul=-2)
        print(f"\tres.r1 = {conv}({low}(r0));", file=file)
        print(f"\tres.r2 = {conv}({high}(r0));", file=file)
        callees = [("low", "m1"), ("high", "m1"), (f, "d2")]
    else:
        conv = build_func_name(isa, dt_par, dt_ret, f, True, lmul=lmul // 2)
        print(f"\tres.r1 = {conv}(r0.r1);", file=file)
        print(f"\tres.r2 = {conv}(r0.r2);", file=file)
        callees = [(f, f"m{lmul // 2}")]
    print("\treturn res;", file=file)
    print("}", file=file)
    if include_manager is not None:
        for callee, callee_lmul in callees:
            include_manager.add_call_dependency(isa["name"], f, "u", f"m{lmul}", callee, "u", callee_lmul)

def _c_lmul_narrowing_writer(f, dt_par, dt_ret, isa, funcs, file, func_name_lmul, lmul, include_manager):
    """
    ncvt from a software LMUL (a struct of two halves) to the LMUL below: the conversions of the two
    halves joined by `combine` for m2 -> m1, the conversion of each half otherwise.
    """
    proto = funcs[f]["proto"]
    res_type = build_type("reg", datatypes[dt_ret], isa, resolve_ret_lmul(proto["ret"], lmul), True)
    print("\nstatic " + build_proto(proto, dt_par, dt_ret, isa, func_name_lmul, lmul=lmul, isa_name=True) + " {", file=file)
    print("\t// Level 2 (Generic Emulation): each half of the result converts one half of the argument", file=file)
    conv = build_func_name(isa, dt_par, dt_ret, f, True, lmul=lmul // 2)
    if lmul == 2:
        comb = build_func_name_short(isa, dt_ret, "combine", True, lmul=-2)
        print(f"\treturn {comb}({conv}(r0.r1), {conv}(r0.r2));", file=file)
        callees = [(f, "m1"), ("combine", "d2")]
    else:
        print(f"\t{res_type} res;", file=file)
        print(f"\tres.r1 = {conv}(r0.r1);", file=file)
        print(f"\tres.r2 = {conv}(r0.r2);", file=file)
        print("\treturn res;", file=file)
        callees = [(f, f"m{lmul // 2}")]
    print("}", file=file)
    if include_manager is not None:
        for callee, callee_lmul in callees:
            include_manager.add_call_dependency(isa["name"], f, "u", f"m{lmul}", callee, "u", callee_lmul)

def _c_lmul_changing_writer(f, dt_par, dt_ret, isa, funcs, file, func_name_lmul, lmul, include_manager=None):
    """
    low / high / combine on a software LMUL register (a struct of two halves 'r1' and 'r2', or
    'm1' and 'm2' for masks): no intrinsic, the result is one of the halves or the pair of arguments.
    """
    proto = funcs[f]["proto"]
    if is_narrowing(proto):
        if lmul >= 2 and isa_provides_lmul(isa, proto, lmul):
            _c_lmul_narrowing_writer(f, dt_par, dt_ret, isa, funcs, file, func_name_lmul, lmul, include_manager)
        return
    if is_widening(proto):
        if lmul >= 1 and isa_provides_lmul(isa, proto, lmul):
            _c_lmul_widening_writer(f, dt_par, dt_ret, isa, funcs, file, func_name_lmul, lmul, include_manager)
        return
    if not isa_provides_lmul(isa, proto, lmul) or -2 in (lmul, resolve_ret_lmul(proto["ret"], lmul)):
        # half-vectors (d2) are provided by the representation of the ISA
        return
    kind = proto["ret"]["type"]
    member = "r" if kind == "reg" else "m"
    arg = "r" if kind == "reg" else "m"
    base = f[:-2] if f.endswith("_k") else f
    print("\nstatic " + build_proto(proto, dt_par, dt_ret, isa, func_name_lmul, lmul=lmul, isa_name=True) + " {", file=file)
    print("\t// Level 0 (Native Hardware): half of the software LMUL register", file=file)
    if base == "low":
        print(f"\treturn {arg}0.{member}1;", file=file)
    elif base == "high":
        print(f"\treturn {arg}0.{member}2;", file=file)
    else:
        res_type = build_type(kind, datatypes[dt_ret], isa, resolve_ret_lmul(proto["ret"], lmul), True)
        print(f"\t{res_type} res;", file=file)
        print(f"\tres.{member}1 = {arg}0;", file=file)
        print(f"\tres.{member}2 = {arg}1;", file=file)
        print("\treturn res;", file=file)
    print("}", file=file)

def _c_lmul_writer(f, dt, dt_par, dt_ret, isa, funcs, file, mask_type=None, lmul=0, include_manager=None):
    maybe_emit_lmul_separator(isa["name"], f, file)

    if len(dt.split(',')) <= 1:
        func_name = build_func_name_short(isa, dt_par, f, lmul=0, masked_version=mask_type)
        func_name_lmul = build_func_name_short(isa, dt_par, f, lmul=lmul, masked_version=mask_type)
        func_name_half_lmul = build_func_name_short(isa, dt_par, f, lmul=int(lmul/2), masked_version=mask_type)
    else:
        func_name = build_func_name(isa, dt_par, dt_ret, f, lmul=0, masked_version=mask_type)
        func_name_lmul = build_func_name(isa, dt_par, dt_ret, f, lmul=lmul, masked_version=mask_type)
        func_name_half_lmul = build_func_name(isa, dt_par, dt_ret, f, lmul=int(lmul/2), masked_version=mask_type)
  
    if changes_lmul(funcs[f]["proto"]):
        _c_lmul_changing_writer(f, dt_par, dt_ret, isa, funcs, file, func_name_lmul, lmul, include_manager)
        return

    if lmul == 1:
        print("\nstatic " + build_proto(funcs[f]["proto"], dt_par, dt_ret, isa, func_name_lmul, lmul=lmul, isa_name=True, masked_version=mask_type) + " {", file=file)
        print("\t" + build_call(funcs[f]["proto"], dt_par, dt_ret, isa, func_name, lmul=0, isa_name=True, masked_version=mask_type) + ";", file=file)
        print("}", file=file)
        return

    if not funcs[f]["horizontal"]:
        print("\nstatic " + build_proto(funcs[f]["proto"], dt_par, dt_ret, isa, func_name_lmul, lmul=lmul, isa_name=True, masked_version=mask_type) + " {", file=file)
        print(build_call_lmul(funcs[f]["proto"], dt_par, dt_ret, isa, func_name_half_lmul, lmul=lmul, isa_name=True, masked_version=mask_type), file=file)
        print("}", file=file)
    else:
        # Avoid direct import loop by resolving dynamically or calling local gen_c_horiz_lmul
        from registry import implems_horiz_lmul_generic_emu
        gen_c_horiz_lmul(
            isa=isa,
            file=file,
            funcs=funcs,
            f=f,
            dt=dt,
            lmul=lmul,
            implems_horiz_lmul_generic_emu=implems_horiz_lmul_generic_emu,
            func_name_for_panic=func_name,
            mask_type=mask_type,
            dummy = True,
        )

def _gen_c_function_one_ldiv_avx(isa_base, isa_div, file, funcs, f, ff, dt, mask_kind, ldiv=-2):
    maybe_emit_ldiv_separator(isa_base["name"], f, file)
    print("", file=file)
    dt_par, dt_ret = compute_dt_par_dt_ret(funcs, f, dt)
    dt_key = dt_par + "," + dt_ret

    if len(dt.split(',')) <= 1:
        dt_par = dt.split(',')[0]
        dt_ret = dt.split(',')[0]
    else:
        dt_par = dt.split(',')[0]
        dt_ret = dt.split(',')[1]
        
    dt_key = dt_par + "," + dt_ret

    if len(dt.split(',')) <= 1:
        func_name = build_func_name_short(isa_base, dt_par, f, True, masked_version=mask_kind, lmul=-2)
    else:
        func_name = build_func_name(isa_base, dt_par, dt_ret, f, True, masked_version=mask_kind, lmul=-2)

    print("static " + build_proto(funcs[f]["proto"], dt_par, dt_ret, isa_base, func_name, lmul=-2,  isa_name=True, masked_version=mask_kind) + " {", file=file)
   
    if len(dt.split(',')) <= 1:
        func_name_impl = build_func_name_short(isa_div, dt_par, f, True, masked_version=mask_kind)
    else:
        func_name_impl = build_func_name(isa_div, dt_par, dt_ret, f, True, masked_version=mask_kind)

    print("\t" + build_call(funcs[f]["proto"], dt_par, dt_ret, isa_div, func_name_impl, masked_version=mask_kind) + ";", file=file)
    print("}", file=file)

def gen_c_lmul(isa, include_manager, funcs, sw_lmuls=None):
    if sw_lmuls is None:
        sw_lmuls = all_lmul
    for f in funcs:
        for dt in funcs[f]["datatypes"]:
            dt_par, dt_ret = compute_dt_par_dt_ret(funcs, f, dt)
            # combine builds a software LMUL register from two LMUL 1 ones
            lmuls_u = sorted(set([1] + list(sw_lmuls))) if changes_lmul(funcs[f]["proto"]) else sw_lmuls
            for lmul in lmuls_u:
                file_w = include_manager.get_fd(isa["name"], f, variant="u", lmul=lmul)
                _c_lmul_writer(f=f, dt=dt, dt_par=dt_par, dt_ret=dt_ret, isa=isa, funcs=funcs, file=file_w, lmul=lmul, include_manager=include_manager)
        
            for lmul in sw_lmuls:
                mask_status = ""
                if "variants" in funcs[f]:
                    mask_status = funcs[f]["variants"]
                else:
                    mask_status = VariantSet()

                if not mask_status.is_any_mask():
                    continue
                if mask_status.is_maskable():
                    file_w = include_manager.get_fd(isa["name"], f, variant="m", lmul=lmul)
                    _c_lmul_writer(f, dt, dt_par, dt_ret, isa, funcs, file_w, mask_type="mask", lmul=lmul)
                if mask_status.is_maskzable():
                    file_w = include_manager.get_fd(isa["name"], f, variant="z", lmul=lmul)
                    _c_lmul_writer(f, dt, dt_par, dt_ret, isa, funcs, file_w, mask_type="maskz", lmul=lmul)
                if mask_status.is_masksable():
                    file_w = include_manager.get_fd(isa["name"], f, variant="s", lmul=lmul)
                    _c_lmul_writer(f, dt, dt_par, dt_ret, isa, funcs, file_w, mask_type="masks", lmul=lmul)

def gen_c_ldiv(isa_base, isa_div, include_manager, funcs):
    if not uses_sub_isa_ldiv(isa_base):
        print(f"in lmul_orchestrator.gen_c_ldiv : error : '{isa_base['name']}' does not declare sub_isa half-vectors (sw_ldiv_type: sub_isa, -2 in sw_lmul)")
        exit(-1)
    for f in funcs:
        if changes_lmul(funcs[f]["proto"]):
            continue
        for dt in funcs[f]["datatypes"]:
            dt_par, dt_ret = compute_dt_par_dt_ret(funcs, f, dt)
            file_w = include_manager.get_fd(isa_base["name"], f, variant="u", lmul=-2)
            _gen_c_function_one_ldiv_avx(isa_base=isa_base, isa_div=isa_div, file=file_w, funcs=funcs, f=f, ff=None, dt=dt, mask_kind=None, ldiv=2)
        variant_set = funcs[f]["variants"] if "variants" in funcs[f] else None
        if variant_set and variant_set.is_maskable():
            for dt in funcs[f]["datatypes"]:
                dt_par, dt_ret = compute_dt_par_dt_ret(funcs, f, dt)
                file_w = include_manager.get_fd(isa_base["name"], f, variant="m", lmul=-2)
                _gen_c_function_one_ldiv_avx(isa_base=isa_base, isa_div=isa_div, file=file_w, funcs=funcs, f=f, ff=None, dt=dt, mask_kind="mask", ldiv=2)
        if variant_set and variant_set.is_maskzable():
            for dt in funcs[f]["datatypes"]:
                dt_par, dt_ret = compute_dt_par_dt_ret(funcs, f, dt)
                file_w = include_manager.get_fd(isa_base["name"], f, variant="z", lmul=-2)
                _gen_c_function_one_ldiv_avx(isa_base=isa_base, isa_div=isa_div, file=file_w, funcs=funcs, f=f, ff=None, dt=dt, mask_kind="maskz", ldiv=2)
        if variant_set and variant_set.is_masksable():
            for dt in funcs[f]["datatypes"]:
                dt_par, dt_ret = compute_dt_par_dt_ret(funcs, f, dt)
                file_w = include_manager.get_fd(isa_base["name"], f, variant="s", lmul=-2)
                _gen_c_function_one_ldiv_avx(isa_base=isa_base, isa_div=isa_div, file=file_w, funcs=funcs, f=f, ff=None, dt=dt, mask_kind="masks", ldiv=2)

