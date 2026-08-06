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
        print("\t// Level 2 (Generic Emulated)", file=file)


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
        mask_support = funcs[f]["mask_support"]
        if not mask_support.is_supported(mask_type):
            print(f"Panic: unsupported mask type '{mask_type}' for '{f}' function.")
            exit(-1)

    if f not in implems_horiz_lmul_generic_emu:
        name = func_name_for_panic or f
        emit_panic_stub(f"{name}_m{int(lmul)}", file=file)
        return

    emitted_any = False
    for ff in implems_horiz_lmul_generic_emu[f]:
        if "version" in ff and ff["version"] not in (None, "", "horiz_lmul"):
            continue
        if "datatypes" in ff and dt not in ff["datatypes"]:
            continue

        _gen_c_horiz_lmul_one(isa=isa, file=file, funcs=funcs, f=f, ff=ff, dt=dt, lmul=lmul, mkind=mask_type, dummy=dummy)
        emitted_any = True

    if not emitted_any:
        name = func_name_for_panic or f
        emit_panic_stub(f"{name}_m{int(lmul)}", file=file)

def _c_lmul_writer(f, dt, dt_par, dt_ret, isa, funcs, file, mask_type=None, lmul=0):
    maybe_emit_lmul_separator(isa["name"], f, file)

    if len(dt.split(',')) <= 1:
        func_name = build_func_name_short(isa, dt_par, f, lmul=0, masked_version=mask_type)
        func_name_lmul = build_func_name_short(isa, dt_par, f, lmul=lmul, masked_version=mask_type)
        func_name_half_lmul = build_func_name_short(isa, dt_par, f, lmul=int(lmul/2), masked_version=mask_type)
    else:
        func_name = build_func_name(isa, dt_par, dt_ret, f, lmul=0, masked_version=mask_type)
        func_name_lmul = build_func_name(isa, dt_par, dt_ret, f, lmul=lmul, masked_version=mask_type)
        func_name_half_lmul = build_func_name(isa, dt_par, dt_ret, f, lmul=int(lmul/2), masked_version=mask_type)
  
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
        file_w = include_manager.get_fd(isa["name"], f)

        for dt in funcs[f]["datatypes"]:
            dt_par, dt_ret = compute_dt_par_dt_ret(funcs, f, dt)
            for lmul in sw_lmuls:
                _c_lmul_writer(f=f, dt=dt, dt_par=dt_par, dt_ret=dt_ret, isa=isa, funcs=funcs, file=file_w, lmul=lmul)
        
            for lmul in sw_lmuls:
                mask_status = ""
                if "mask_support" in funcs[f]:
                    mask_status = funcs[f]["mask_support"]
                else:
                    mask_status = MaskSupport()

                if not mask_status.is_any_mask():
                    continue
                if mask_status.is_maskable():
                    _c_lmul_writer(f, dt, dt_par, dt_ret, isa, funcs, file_w, mask_type="mask", lmul=lmul)
                if mask_status.is_maskzable():
                    _c_lmul_writer(f, dt, dt_par, dt_ret, isa, funcs, file_w, mask_type="maskz", lmul=lmul)
                if mask_status.is_masksable():
                    _c_lmul_writer(f, dt, dt_par, dt_ret, isa, funcs, file_w, mask_type="masks", lmul=lmul)

def gen_c_ldiv(isa_base, isa_div, include_manager, funcs):
    if isa_base["name"] != "avx512" and isa_base["name"] != "avx": 
        print(f"in c_generator.gen_c_ldiv : error : ldiv not yet supported in {isa_div['name']}")
        exit(-1)
    for f in funcs:
        file_w = include_manager.get_fd(isa_base["name"], f)
        for dt in funcs[f]["datatypes"]:
            dt_par, dt_ret = compute_dt_par_dt_ret(funcs, f, dt)
            _gen_c_function_one_ldiv_avx(isa_base=isa_base, isa_div=isa_div, file=file_w, funcs=funcs, f=f, ff=None, dt=dt, mask_kind=None, ldiv=2)
        mask_support = funcs[f]["mask_support"] if "mask_support" in funcs[f] else None
        if mask_support and mask_support.is_maskable():
            for dt in funcs[f]["datatypes"]:
                dt_par, dt_ret = compute_dt_par_dt_ret(funcs, f, dt)
                _gen_c_function_one_ldiv_avx(isa_base=isa_base, isa_div=isa_div, file=file_w, funcs=funcs, f=f, ff=None, dt=dt, mask_kind="mask", ldiv=2)
        if mask_support and mask_support.is_maskzable():
            for dt in funcs[f]["datatypes"]:
                dt_par, dt_ret = compute_dt_par_dt_ret(funcs, f, dt)
                _gen_c_function_one_ldiv_avx(isa_base=isa_base, isa_div=isa_div, file=file_w, funcs=funcs, f=f, ff=None, dt=dt, mask_kind="maskz", ldiv=2)
        if mask_support and mask_support.is_masksable():
            for dt in funcs[f]["datatypes"]:
                dt_par, dt_ret = compute_dt_par_dt_ret(funcs, f, dt)
                _gen_c_function_one_ldiv_avx(isa_base=isa_base, isa_div=isa_div, file=file_w, funcs=funcs, f=f, ff=None, dt=dt, mask_kind="masks", ldiv=2)
