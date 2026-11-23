"""
LDIV 'mask' Module
Generates the half-vector (d2) functions of an ISA whose half-vector is a full register of the ISA
itself, only the lower half of the lanes being meaningful (`sw_ldiv_type: mask`).

- Most functions are lane-wise: the d2 function re-wraps its arguments in the LMUL 1 types (same
  member `r` / `m`), calls the LMUL 1 function and re-wraps the result.
- The others (load, store, set, gather, scatter, reductions, testz...) must not look at the upper
  lanes, which hold garbage: they are given by templates (Jinja2 + C) in `generic_ldiv_mask.json`
  and, per ISA, in `simd_ext/<isa>/<isa>_ldiv_mask.json` (the latter has priority).
"""
import io
import json
import os
import sys

# Add parent directory to sys.path to find tools.py
sys.path.insert(1, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

from jinja2 import Template, StrictUndefined
from tools import *
from tools import build_func_name_internal
from input_validation import validate_ldiv_mask_config, make_level_detector
from codegen.emit_helpers import emit_panic_stub
from codegen.candidate_resolver import BASE_LEVELS, BASE_LEVEL_BRANCHES
from codegen.lmul_orchestrator import maybe_emit_ldiv_separator, record_lmul1_definition, emit_lmul_banner

_HELPERS_DIR = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
_VARIANT_OF = {None: "u", "mask": "m", "maskz": "z", "masks": "s"}
_LEVEL_TEXT = {
    0: "Level 0 (Native Hardware)",
    1: "Level 1 (Dedicated Emulation)",
    2: "Level 2 (Generic Emulation)",
    3: "Level 3 (Scalar Fallback)",
}


def _load_templates(isa, functions):
    """Special d2 implementations: the ones of the ISA first, then the generic ones."""
    paths = [
        os.path.join(_HELPERS_DIR, "..", "simd_ext", isa["name"], f"{isa['name']}_ldiv_mask.json"),
        os.path.join(_HELPERS_DIR, "generic_ldiv_mask.json"),
    ]
    templates = {}
    for path in paths:
        if not os.path.exists(path):
            continue
        if uses_sub_isa_ldiv(isa) and path.endswith("generic_ldiv_mask.json"):
            # the d2 of a sub_isa is the register of the sub_isa: the generic templates do not apply
            continue
        with open(path, "r", encoding="utf-8") as fd:
            data = json.load(fd)
        dedicated = not path.endswith("generic_ldiv_mask.json")
        validate_ldiv_mask_config(data, os.path.relpath(path, os.path.join(_HELPERS_DIR, "..")))
        for names, entries in data.items():
            for f in names.split("|"):
                if f not in functions:
                    print(f"in {os.path.basename(path)} : error : unknown function '{f}'")
                    sys.exit(1)
                for entry in entries:
                    dts = entry.get("datatypes", "all_datatypes")
                    for dt in ([] if dts == "all_datatypes" else dts):
                        if dt not in datatypes:
                            print(f"in {os.path.basename(path)} : error : unknown datatype '{dt}' for '{f}'")
                            sys.exit(1)
                templates.setdefault(f, []).extend(dict(e, _dedicated=dedicated) for e in entries)
    return templates


def _select_template(templates, f, dt_par, mask_kind):
    for entry in templates.get(f, []):
        if "variants" in entry and _VARIANT_OF[mask_kind] not in entry["variants"]:
            continue
        dts = entry.get("datatypes", "all_datatypes")
        if dts != "all_datatypes" and dt_par not in dts:
            continue
        return entry
    return None


def _select_templates(templates, f, dt_par, mask_kind):
    """All the matching entries, in priority order, up to (and including) the first without \"if\"."""
    chain = []
    for entry in templates.get(f, []):
        if "variants" in entry and _VARIANT_OF[mask_kind] not in entry["variants"]:
            continue
        dts = entry.get("datatypes", "all_datatypes")
        if dts != "all_datatypes" and dt_par not in dts:
            continue
        chain.append(entry)
        if "if" not in entry:
            break
    return chain


def _params(proto, dt_par, isa, mask_kind, dt_ret=None):
    """Parameters of the function, in the order of its prototype (see name_builder.build_proto)."""
    params = []
    if mask_kind:
        # the mask has the datatype of the function (gather / scatter: the one of the data)
        msk_dt = datatypes[dt_par]
        params.append({"name": "vm0", "kind": "msk", "dt": msk_dt})
        if mask_kind == "masks":
            params.append({"name": "vdsrc", "kind": "reg", "dt": datatypes[dt_par]})
    cnt = {"reg": 0, "msk": 0 if not mask_kind else 1, "val": 0, "ptr": 0}
    for arg in proto["args"]:
        realdatatype = resolve_param_datatype(arg, dt_par, dt_ret or dt_par)
        kind = arg["type"]
        if kind in cnt:
            name = {"reg": "vd", "msk": "vm", "val": "s", "ptr": "p"}[kind] + str(cnt[kind])
            cnt[kind] += 1
        elif kind == "vindex":
            name = "vi"
        elif kind == "Nele":
            name = "vals"
        else:
            print(f"in ldiv_mask : error : unknown argument type '{kind}'")
            exit(-1)
        params.append({"name": name, "kind": kind, "dt": realdatatype})
    return params


class _Ctx:
    """Everything a template can use to write the body of a d2 function."""

    def __init__(self, isa, funcs, f, dt, dt_par, dt_ret, mask_kind, params, calls, lmul_in=-2):
        self.isa = isa
        self.funcs = funcs
        self.f = f
        self.dt = dt
        self.dt_par = dt_par
        self.dt_ret = dt_ret
        self.mask_kind = mask_kind
        self.params = params
        self.calls = calls
        self.proto = funcs[f]["proto"]
        self.lmul_in = lmul_in
        self.lmul_out = resolve_ret_lmul(self.proto["ret"], lmul_in) if changes_lmul(self.proto) else lmul_in

    def _suffix(self, d):
        return f"{d['category'].upper()}{d['n_bits']}"

    def N(self, dt=None):
        d = datatypes[dt or self.dt_par]
        return f"MIPP_{self.isa['name'].upper()}_N_{self._suffix(d)}"

    def N2(self, dt=None):
        return self.N(dt) + "_D2"

    def ext(self, dt, lmul):
        """`data_ext` of the datatype `dt` (e.g. `i32m1`) at the LMUL `lmul`, for the ISAs whose intrinsics carry it."""
        d = self.isa["datatypes"][dt]
        return d["data_ext"].replace("{lsuffix}", d["lsuffix"][str(lmul)])

    def uext(self, dt, lmul):
        """`data_ext` of the unsigned integer type of the same width as `dt` (e.g. `u32mf2`) at the LMUL `lmul`."""
        d = self.isa["datatypes"][dt]
        return d["uint_data_ext"].replace("{lsuffix}", d["lsuffix"][str(lmul)])

    def bext(self, dt, lmul):
        """Suffix of the mask type (e.g. `b64`) of the datatype `dt` at the LMUL `lmul`."""
        d = self.isa["datatypes"][dt]
        return d["data_ext_logi"].replace("{eew_emul}", d["eew_emul"][str(lmul)])

    def call1(self, fname, *args, mk=None, dt=None):
        """Call of the LMUL 1 function `fname` (registered as a dependency)."""
        dt = dt or self.dt_par
        self.calls.add((fname, _VARIANT_OF[mk]))
        return build_func_name_short(self.isa, dt, fname, True, masked_version=mk) + "(" + ", ".join(args) + ")"

    def ret_type(self):
        """C type of the returned register / mask, at the LMUL of the result (see the `lmul` key of `ret`)."""
        ret = self.proto["ret"]
        if ret["type"] not in ("reg", "msk"):
            return "void"
        realdt = resolve_param_datatype(ret, self.dt_par, self.dt_ret, is_ret=True)
        lmul_in = {"down": 1, "up": -2}.get(ret.get("lmul", "same"))
        lmul_out = resolve_ret_lmul(ret, lmul_in) if lmul_in else -2
        return build_type(ret["type"], realdt, self.isa, lmul_out, True, False)

    def wrap(self, *names):
        """Declares the LMUL 1 versions of d2 parameters: `w_<name>`."""
        lines = []
        for p in self.params:
            if p["name"] in names:
                m1 = build_type(p["kind"] if p["kind"] != "vindex" else "reg", p["dt"], self.isa, 0, True, False)
                member = "vm" if p["kind"] == "msk" else "vd"
                lines.append(f"{m1} w_{p['name']}; w_{p['name']}.{member} = {p['name']}.{member};")
        return "\n".join(lines)

    def ret_d2(self, expr):
        """Returns the LMUL 1 result `expr` as a d2 result."""
        ret = self.proto["ret"]
        if ret["type"] not in ("reg", "msk"):
            return f"return {expr};"
        realdt = resolve_param_datatype(ret, self.dt_par, self.dt_ret, is_ret=True)
        d2 = build_type(ret["type"], realdt, self.isa, -2, True, False)
        member = "vd" if ret["type"] == "reg" else "vm"
        return f"{d2} res;\nres.{member} = ({expr}).{member};\nreturn res;"

    def lanemask(self, name="lm"):
        """Declares the LMUL 1 mask `name`: true on the lower half of the lanes."""
        M1 = build_msk(datatypes[self.dt_par], self.isa, 0, True, False)
        return (
            f"int32_t {name}_v[{self.N()}];\n"
            f"for (unsigned i = 0; i < {self.N()}; i++)\n"
            f"\t{name}_v[i] = (i < {self.N2()});\n"
            f"{M1} {name} = {self.call1('set_k', name + '_v')};"
        )

    def neutral(self, f):
        """Neutral element of the reduction `f`, as a C expression of the element type."""
        d = datatypes[self.dt_par]
        is_float = d["category"] == "float"
        is_uint = d["category"] == "uint"
        bits = d["n_bits"]
        if f in ("hadd", "hadds"):
            return "0"
        if f == "hmul":
            return "1"
        if f == "hmin":
            if is_float:
                return "FLT_MAX" if bits == 32 else "DBL_MAX"
            return f"UINT{bits}_MAX" if is_uint else f"INT{bits}_MAX"
        if f == "hmax":
            if is_float:
                return "-FLT_MAX" if bits == 32 else "-DBL_MAX"
            return "0" if is_uint else f"INT{bits}_MIN"
        print(f"in ldiv_mask : error : no neutral element for '{f}'")
        exit(-1)


def _wrapper_body(ctx, params):
    """Lane-wise function: the LMUL 1 function on the same registers, re-wrapped."""
    lines, args = [], []
    for p in params:
        if p["kind"] in ("reg", "msk", "vindex"):
            lines.append(ctx.wrap(p["name"]))
            args.append("w_" + p["name"])
        elif p["kind"] == "Nele":
            args.append("vals")
        else:
            args.append(p["name"])
    call = build_func_name_internal(ctx.isa, ctx.dt, ctx.dt_par, ctx.dt_ret, ctx.f, masked_version=ctx.mask_kind, lmul=0)
    ctx.calls.add((ctx.f, _VARIANT_OF[ctx.mask_kind]))
    call += "(" + ", ".join(args) + ")"
    if ctx.proto["ret"]["type"]:
        lines.append(ctx.ret_d2(call))
    else:
        lines.append(call + ";")
    return "\n".join(lines)


def _wrapper_body_memcpy(ctx, params):
    """
    Level 3 version of `_wrapper_body`, for the targets where the d2 types are not the same kind of object as
    the LMUL 1 ones (e.g. float64 on ARMv7, where they are arrays): the registers are copied with memcpy.
    """
    lines, args = [], []
    for p in params:
        if p["kind"] in ("reg", "msk", "vindex"):
            m1 = build_type(p["kind"] if p["kind"] != "vindex" else "reg", p["dt"], ctx.isa, 0, True, False)
            n = p["name"]
            lines.append(f"{m1} w_{n}; memset(&w_{n}, 0, sizeof(w_{n})); memcpy(&w_{n}, &{n}, sizeof({n}));")
            args.append("w_" + n)
        elif p["kind"] == "Nele":
            args.append("vals")
        else:
            args.append(p["name"])
    call = build_func_name_internal(ctx.isa, ctx.dt, ctx.dt_par, ctx.dt_ret, ctx.f, masked_version=ctx.mask_kind, lmul=0)
    ctx.calls.add((ctx.f, _VARIANT_OF[ctx.mask_kind]))
    call += "(" + ", ".join(args) + ")"
    ret = ctx.proto["ret"]
    if ret["type"] in ("reg", "msk"):
        lines.append(f"{ctx.ret_type()} res; memset(&res, 0, sizeof(res));")
        lines.append(f"__typeof__({call}) w_res = {call};")
        lines.append("memcpy(&res, &w_res, sizeof(res));")
        lines.append("return res;")
    elif ret["type"]:
        lines.append(f"return {call};")
    else:
        lines.append(call + ";")
    return "\n".join(lines)


def _lane_crossing_body(ctx, params):
    """
    d2 body of a function that moves lanes across the register (`lane_crossing`: reverse, slide, ziplo...): the
    LMUL 1 function would read the upper lanes, which hold garbage. Unmasked: Level 3, through the d2 function of the
    scalar ISA (the lanes of the d2 register are copied to its array, and back). Masked: the unmasked d2 function,
    then the d2 `select` (lane-wise) of the mask variant.
    """
    from registry import scalar_isa
    lines = []
    d2 = lambda name, dt=None: build_func_name_internal(ctx.isa, ctx.dt, dt or ctx.dt_par, dt or ctx.dt_ret, name,
                                                         lmul=-2)
    if ctx.mask_kind:
        args = [p["name"] for p in params if p["name"] not in ("vm0", "vdsrc")]
        unmasked = build_func_name_internal(ctx.isa, ctx.dt, ctx.dt_par, ctx.dt_ret, ctx.f, lmul=-2)
        ctx.calls.add((ctx.f, "u"))
        ctx.calls.add(("select", "u"))
        lines.append(f"{ctx.ret_type()} t = {unmasked}({', '.join(args)});")
        other = {"mask": "vd0", "masks": "vdsrc"}.get(ctx.mask_kind)
        if other is None:
            ctx.calls.add(("set0", "u"))
            other = f"{d2('set0')}()"
        lines.append(f"return {d2('select')}(vm0, t, {other});")
        return "\n".join(lines)
    args = []
    for p in params:
        n = p["name"]
        if p["kind"] == "reg":
            # through a union, not a memcpy from the parameter: see candidate_resolver._register_to_scalar
            s_type = build_reg(p["dt"], scalar_isa, -2, True, False)
            v_type = build_reg(p["dt"], ctx.isa, -2, True, False)
            lines.append(f"union {{ {v_type} v; {s_type} s; }} s_{n}; memset(&s_{n}, 0, sizeof(s_{n})); "
                         f"s_{n}.v = {n};")
            args.append(f"s_{n}.s")
        elif p["kind"] in ("val", "ptr"):
            args.append(n)
        else:
            print(f"in ldiv_mask : error : '{ctx.f}' (lane_crossing): argument kind '{p['kind']}' not supported")
            sys.exit(1)
    scalar_f = build_func_name_internal(scalar_isa, ctx.dt, ctx.dt_par, ctx.dt_ret, ctx.f, lmul=-2)
    if ctx.proto["ret"]["type"] == "val":
        # a value (count of storeu_compress): the one of the scalar function
        lines.append(f"return {scalar_f}({', '.join(args)});")
        return "\n".join(lines)
    if ctx.proto["ret"]["type"] != "reg":
        # store-like function: the scalar function writes the memory
        lines.append(f"{scalar_f}({', '.join(args)});")
        return "\n".join(lines)
    s_ret = build_reg(datatypes[ctx.dt_ret], scalar_isa, -2, True, False)
    lines.append(f"{s_ret} sres = {scalar_f}({', '.join(args)});")
    lines.append(f"{ctx.ret_type()} res; memset(&res, 0, sizeof(res));")
    lines.append("memcpy(&res, &sres, MIPP_MIN_SIZEOF(res, sres));")
    lines.append("return res;")
    return "\n".join(lines)


_level_detectors = {}

# Level of the templates of the functions that change the LMUL (lo, hi, combine, wcvt, ncvt), per
# (isa, function, "dt_par,dt_ret"): the level of the first template of the chain. Filled by _emit_one,
# read by the documentation and the API Explorer (see compute_changing_levels).
CHANGING_LEVELS = {}


def _auto_level(isa, code, calls):
    """
    Level of a template of an ISA file without explicit "level": the rules of the level audit
    (`input_validation.make_level_detector`) applied to the text of the template, where the
    `call1` calls (`calls`) are MIPP functions:
    - 0: a single intrinsic, no MIPP function (a template with neither intrinsic nor MIPP
         function, such as an identity, is also level 0);
    - 1: several intrinsics, or intrinsics with MIPP functions;
    - 2: only MIPP functions.
    Level 3 (sequential code) has to be given with the "level" key.
    """
    if isa["name"] not in _level_detectors:
        _level_detectors[isa["name"]] = make_level_detector(isa)
    level, deps, has_hardware = _level_detectors[isa["name"]](code)
    if not has_hardware and not deps and not calls:
        return 0
    if calls and level == 0:
        return 1
    return level


def _emit_one(isa, file, funcs, templates, f, dt, mask_kind, record_call, lmul_in=-2, sw_lmul=False):
    """
    Writes one function from its templates. `sw_lmul`: the templates are those of `<isa>_sw_lmul.json`
    (wcvt m1 -> m2, ncvt m2 -> m1 of a software LMUL, see codegen/sw_lmul.py).
    """
    dt_par, dt_ret = compute_dt_par_dt_ret(funcs, f, dt)
    changing = changes_lmul(funcs[f]["proto"])
    if not changing:
        maybe_emit_ldiv_separator(isa["name"], f, file)
    # LMUL of the arguments (and suffix of the name): d2, or m1 / d2 for the functions that change it
    name = build_func_name_internal(isa, dt, dt_par, dt_ret, f, masked_version=mask_kind, lmul=lmul_in)
    proto = build_proto(funcs[f]["proto"], dt_par, dt_ret, isa, name, lmul=lmul_in, isa_name=True, masked_version=mask_kind)

    proto_info = dict(funcs[f]["proto"])
    proto_info["_name"] = f
    params = _params(proto_info, dt_par, isa, mask_kind, dt_ret)
    calls = set()
    ctx = _Ctx(isa, funcs, f, dt, dt_par, dt_ret, mask_kind, params, calls, lmul_in)

    def render(entry):
        code = entry["code"]
        if isinstance(code, list):
            code = "\n".join(code)
        body = Template(code, undefined=StrictUndefined).render(
            ctx=ctx, f=f, dt=datatypes[dt_par], dt_ret=datatypes[dt_ret], mask_kind=mask_kind,
            isa=isa, isa_dt=isa["datatypes"][dt_par],
            call1=ctx.call1, wrap=ctx.wrap, ret_d2=ctx.ret_d2, lanemask=ctx.lanemask, neutral=ctx.neutral,
            UI="uint" + str(datatypes[dt_par]["n_bits"]),
        )
        # mini-DSL (%vd<tp>%, %N<tp>%...) relative to the LMUL of the function: d2, or m1 for lo / hi
        body = parse_placeholders(body, isa, funcs, f, dt_par, dt_ret, lmul=lmul_in, isa_name=True)["converted_ir"]
        if "level" in entry:
            lvl = entry["level"]
        else:
            lvl = _auto_level(isa, code, calls) if entry.get("_dedicated") else 2
        return body, lvl

    # Candidates in order of priority (ISA file, then generic file). An entry with an "if" is only
    # used when the C condition holds, otherwise the next one is: the chain stops at the first entry
    # without "if" or, for the lane-wise functions, at the wrapper of the LMUL 1 function.
    chain = _select_templates(templates, f, dt_par, mask_kind)
    if not chain and changing:
        print(f"in ldiv_mask : error : no template for '{f}' ({dt_par}) on '{isa['name']}'")
        sys.exit(1)
    if changing and "if" in chain[-1]:
        print(f"in ldiv_mask : error : '{f}' ({dt_par}) on '{isa['name']}' : every template has an \"if\", "
              f"a fallback without \"if\" is needed (generic_ldiv_mask.json)")
        sys.exit(1)
    level_lines = None
    # the body copies the registers to the scalar ISA (Level 3): attributes of the fallbacks
    copies_to_scalar = False
    if not chain and funcs[f].get("lane_crossing", False):
        body = _lane_crossing_body(ctx, params)
        lvl = 3 if not mask_kind else 2
        copies_to_scalar = not mask_kind
        level = _LEVEL_TEXT[lvl] + (": lanes moved across the register, through the scalar d2 function"
                                    if not mask_kind else ": the unmasked d2 function, then select")
        chain = None
    elif not chain:
        body = _wrapper_body(ctx, params)
        key = (isa["name"], f, dt_par + "," + dt_ret, mask_kind)
        lvl = BASE_LEVELS.get(key, 2)
        level = _LEVEL_TEXT[lvl] + ": lane-wise, inherited from the LMUL 1 function on the same register"
        # the LMUL 1 function has branches of different levels (e.g. L2 if defined(__SSE2__), L3
        # otherwise): the level of each branch under its own condition, not the worst of them
        branches = BASE_LEVEL_BRANCHES.get(key, [])
        if len({b_lvl for _, b_lvl in branches}) > 1 and all(c for c, _ in branches):
            by_level = {}
            for cond, b_lvl in branches:
                by_level.setdefault(b_lvl, []).append(cond)
            level_lines = []
            for k, (b_lvl, conds) in enumerate(sorted(by_level.items())):
                cond = conds[0] if len(conds) == 1 else " || ".join(f"({c})" for c in conds)
                level_lines.append(f"#{'if' if k == 0 else 'elif'} {cond}")
                level_lines.append(f"\t// {_LEVEL_TEXT[b_lvl]}: lane-wise, inherited from the LMUL 1 function on the same register")
            level_lines.append("#endif")
    else:
        parts = []
        for k, entry in enumerate(chain):
            e_body, e_lvl = render(entry)
            if k == 0:
                lvl = e_lvl
            parts.append((entry.get("if"), e_body))
        if "if" in chain[-1]:
            # no default entry: the wrapper of the LMUL 1 function (lane-wise functions only)
            parts.append((None, _wrapper_body(ctx, params)))
        body = ""
        for k, (cond, e_body) in enumerate(parts):
            if k == 0 and cond is None:
                body = e_body
                break
            body += (f"#if {cond}\n" if k == 0 else (f"#elif {cond}\n" if cond else "#else\n")) + e_body + "\n"
        if len(parts) > 1 or parts[0][0] is not None:
            body += "#endif"
        if sw_lmul:
            level = _LEVEL_TEXT[lvl] + ": software LMUL specific, written by the ISA for the registers of the result"
        else:
            level = _LEVEL_TEXT[lvl] + ": half-vector specific, the upper lanes are not read"
        if len(parts) > 1:
            level += " (with fallback if the native condition does not hold)"
    if changing and not sw_lmul:
        # the documented level is the one of the half-vector function (m1 <-> d2)
        CHANGING_LEVELS[(isa["name"], f, dt_par + "," + dt_ret)] = lvl

    # the guards of the datatype of the argument and, for the conversions, of the result
    guards = [isa["datatypes"].get(d, {}).get("if", None) for d in dict.fromkeys((dt_par, dt_ret))]
    guard = " && ".join(f"({g})" if len(guards) > 1 else g for g in guards if g) or None
    if sw_lmul:
        emit_lmul_banner(isa["name"], f, file, "emulated")
    print("", file=file)
    if guard:
        print(f"#if {guard}", file=file)
    print(f"static {fallback_attributes(isa) if copies_to_scalar else ''}{proto} {{", file=file)
    if changing and lmul_in == 1:
        # the function without suffix is generated afterwards, as the alias of this one
        record_lmul1_definition(isa["name"], f, dt, mask_kind)
    if level_lines:
        for line in level_lines:
            print(line, file=file)
    else:
        print(f"\t// {level}", file=file)
    for line in body.split("\n"):
        if line.strip():
            print("\t" + line, file=file)
    print("}", file=file)
    if guard:
        print("#else", file=file)
        lane_crossing_else = funcs[f].get("lane_crossing", False) and not changing
        memcpy_else = not lane_crossing_else and not chain and not changing
        attrs = fallback_attributes(isa) if (copies_to_scalar if lane_crossing_else else memcpy_else) else ""
        print(f"static {attrs}{proto} {{", file=file)
        if lane_crossing_else:
            # the scalar d2 function does not depend on the guard of the datatype
            print(f"\t// {level}", file=file)
            for line in body.split("\n"):
                if line.strip():
                    print("\t" + line, file=file)
        elif memcpy_else:
            # lane-wise function: Level 3 fallback through the LMUL 1 function
            print(f"\t// {_LEVEL_TEXT[3]}: lane-wise, through the LMUL 1 function (memcpy of the registers)", file=file)
            for line in _wrapper_body_memcpy(ctx, params).split("\n"):
                print("\t" + line, file=file)
        else:
            emit_panic_stub(name, file=file)
        print("}", file=file)
        print("#endif", file=file)
    for (callee, callee_variant) in calls:
        record_call(f, _VARIANT_OF[mask_kind], callee, callee_variant)


class _NullIncludeManager:
    """Include manager that discards the code: used to compute the levels without writing headers."""
    def get_fd(self, *args, **kwargs):
        return io.StringIO()

    def add_call_dependency(self, *args, **kwargs):
        pass


def compute_changing_levels(isa, funcs):
    """
    Levels of the functions that change the LMUL for an ISA with half-vectors by mask: the dict
    {(function, "dt_par,dt_ret"): level}. Empty for the other ISAs (their functions are not
    given yet, or they are made of the software LMUL registers).
    """
    if not uses_ldiv_templates(isa):
        return {}
    gen_c_ldiv_mask(isa, _NullIncludeManager(), funcs, only_changing=True)
    return {(f, k): lvl for (n, f, k), lvl in CHANGING_LEVELS.items() if n == isa["name"]}


def gen_c_ldiv_mask(isa, include_manager, funcs, only_changing=False, ldiv_pairs=True, other_pairs=True, outer_guard=None):
    """
    Half-vector functions of an ISA with half-vectors by mask, and the functions that change the LMUL. For the ISAs with
    hardware register groups (RVV), `ldiv_pairs` / `other_pairs` select the functions between m1 and d2 / between
    the other LMULs, and `outer_guard` wraps what is written: with several half-vector representations
    (`ldiv_modes`), the functions between m1 and d2 are written once per mode (codegen/ldiv_modes.py).
    """
    if not uses_ldiv_templates(isa):
        print(f"in ldiv_mask.gen_c_ldiv_mask : error : '{isa['name']}' does not declare 'sw_ldiv_type: mask' with -2 in sw_lmul")
        exit(-1)
    templates = _load_templates(isa, funcs)

    def record_call(f, variant, callee, callee_variant):
        include_manager.add_call_dependency(isa["name"], f, variant, "d2", callee, callee_variant, "m1")

    for f in funcs:
        variant_set = funcs[f]["variants"] if "variants" in funcs[f] else None
        if changes_lmul(funcs[f]["proto"]):
            # lo / hi (m1 -> d2) and combine (d2 -> m1), only if the templates of the ISA give them
            proto = funcs[f]["proto"]
            if uses_hw_ldiv_templates(isa):
                lmuls_in = [int(x) for x in isa.get("hw_lmul", [1])]
            else:
                lmuls_in = [1 if proto["ret"]["lmul"] == "down" else -2]
            for lmul_in in lmuls_in:
                if not isa_provides_lmul(isa, proto, lmul_in):
                    continue
                is_ldiv_pair = -2 in (lmul_in, resolve_ret_lmul(proto["ret"], lmul_in))
                if (is_ldiv_pair and not ldiv_pairs) or (not is_ldiv_pair and not other_pairs):
                    continue
                file_w = include_manager.get_fd(isa["name"], f, variant="u", lmul=lmul_in)
                for dt in funcs[f]["datatypes"]:
                    if outer_guard:
                        print(f"\n#if {outer_guard}", file=file_w)
                    _emit_one(isa, file_w, funcs, templates, f, dt, None, record_call, lmul_in=lmul_in)
                    if outer_guard:
                        print("#endif", file=file_w)
            continue
        if only_changing:
            continue
        kinds = [None]
        if variant_set:
            if variant_set.is_maskable():
                kinds.append("mask")
            if variant_set.is_maskzable():
                kinds.append("maskz")
            if variant_set.is_masksable():
                kinds.append("masks")
        for mask_kind in kinds:
            file_w = include_manager.get_fd(isa["name"], f, variant=_VARIANT_OF[mask_kind], lmul=-2)
            for dt in funcs[f]["datatypes"]:
                if not is_defined_for_dt_lmul(funcs[f]["proto"], dt, -2):
                    # gather / scatter with an index of another width than the data: not for the half-vectors
                    continue
                _emit_one(isa, file_w, funcs, templates, f, dt, mask_kind, record_call)
