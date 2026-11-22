"""
Half-vector (d2) representations selectable at compile time by the user (`ldiv_modes` of the ISA descriptor).

An ISA with hardware fractional registers (RVV: `mf2`) may also represent a half-vector of some datatypes with the
register of LMUL 1, used with a vector length `vl` = N/2 ("by vl"): the lane-wise intrinsics, the loads, the stores
and the reductions then process the N/2 lanes of the half-vector with no mask and no fault. This is the only native
representation of the 64-bit half-vectors on RVV (`i64mf2` is illegal), which are otherwise C arrays (Level 3).

Each mode of `ldiv_modes` gives a macro and the datatypes whose half-vector is "by vl" (`vl_datatypes`): the d2 layer
of the ISA (types, functions, and the functions that change the LMUL between m1 and d2) is generated once per mode,
each time under `#if defined(<macro>)`. The other datatypes keep the hardware fractional register.
"""
import copy
import os
import sys

sys.path.insert(1, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

from tools import DATATYPES_MAP


def ldiv_modes(isa):
    """The modes of the ISA (list of dicts), or [] when it has a single d2 representation."""
    return isa.get("ldiv_modes", [])


def mode_guard(mode):
    """Preprocessor condition under which the d2 layer of `mode` is compiled."""
    return f"defined({mode['macro']})"


def mode_vl_datatypes(mode):
    """Names of the datatypes whose half-vector is the LMUL 1 register used with vl = N/2 in `mode`."""
    dts = mode.get("vl_datatypes", [])
    if isinstance(dts, str):
        dts = [dts]
    names = []
    for d in dts:
        if d in DATATYPES_MAP:
            names += [x["name"] if isinstance(x, dict) else x for x in DATATYPES_MAP[d]]
        else:
            names.append(d)
    return set(names)


def is_vl_ldiv(isa_dt):
    """True when the half-vector of this datatype entry (of a descriptor given by apply_ldiv_mode) is 'by vl'."""
    return bool(isa_dt.get("ldiv_vl", False))


def apply_ldiv_mode(isa, mode):
    """
    Copy of the ISA descriptor where the half-vector of the `vl_datatypes` of `mode` is the LMUL 1 register: the
    placeholders that depend on the LMUL (`lsuffix`, `eew_emul`...) take for `-2` their value of LMUL 1, the guard of
    the half-vector (`if_lmul["-2"]`, which disables the illegal 64-bit fractional registers) is dropped, and the
    datatype is marked `ldiv_vl` (full-size register typedef, see c_generator.gen_c_structures). The number of
    lanes of the half-vector (`MIPP_<ISA>_N_<TYPE>_D2`, the `vl` of its intrinsics) is unchanged.
    """
    misa = copy.deepcopy(isa)
    vl_dts = mode_vl_datatypes(mode)
    for dt, cfg in misa["datatypes"].items():
        if dt not in vl_dts:
            continue
        for key, val in list(cfg.items()):
            if isinstance(val, dict) and "-2" in val and ("1" in val or "0" in val):
                val["-2"] = val.get("1", val.get("0"))
        if isinstance(cfg.get("if_lmul"), dict):
            cfg["if_lmul"].pop("-2", None)
        cfg["ldiv_vl"] = True
    misa["ldiv_mode"] = mode["name"]
    return misa
