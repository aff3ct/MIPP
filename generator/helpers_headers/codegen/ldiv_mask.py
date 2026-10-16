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
import json
import os
import sys

# Add parent directory to sys.path to find tools.py
sys.path.insert(1, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

from jinja2 import Template, StrictUndefined
from tools import *
from tools import build_func_name_internal
from input_validation import validate_ldiv_mask_config
from codegen.emit_helpers import emit_panic_stub
from codegen.candidate_resolver import BASE_LEVELS
from codegen.lmul_orchestrator import maybe_emit_ldiv_separator

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
        if "versions" in entry and _VARIANT_OF[mask_kind] not in entry["versions"]:
            continue
        dts = entry.get("datatypes", "all_datatypes")
        if dts != "all_datatypes" and dt_par not in dts:
            continue
        return entry
    return None


def _params(proto, dt_par, isa, mask_kind):
    """Parameters of the function, in the order of its prototype (see name_builder.build_proto)."""
    params = []
    if mask_kind:
        msk_dt = datatypes[dt_par]
        if proto["_name"] in ("gather", "scatter"):
            msk_dt = datatypes["uint" + str(get_dt_par_size(dt_par))]
        params.append({"name": "m0", "kind": "msk", "dt": msk_dt})
        if mask_kind == "masks":
            params.append({"name": "rsrc", "kind": "reg", "dt": datatypes[dt_par]})
    cnt = {"reg": 0, "msk": 0 if not mask_kind else 1, "val": 0, "ptr": 0}
    for arg in proto["args"]:
        realdatatype = datatypes[dt_par]
        if arg["fixeddatatype"]:
            if arg["fixeddatatype"] not in datatypes and arg["fixeddatatype"] in all_categories:
                realdatatype = datatypes[arg["fixeddatatype"] + str(get_dt_par_size(dt_par))]
            elif arg["fixeddatatype"] in datatypes:
                realdatatype = datatypes[arg["fixeddatatype"]]
        kind = arg["type"]
        if kind in cnt:
            name = {"reg": "r", "msk": "m", "val": "v", "ptr": "p"}[kind] + str(cnt[kind])
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

    def __init__(self, isa, funcs, f, dt, dt_par, dt_ret, mask_kind, params, calls):
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

    def _suffix(self, d):
        return f"{d['category'].upper()}{d['n_bits']}"

    def N(self, dt=None):
        d = datatypes[dt or self.dt_par]
        return f"MIPP_{self.isa['name'].upper()}_N_{self._suffix(d)}"

    def N2(self, dt=None):
        return self.N(dt) + "_D2"

    def call1(self, fname, *args, mk=None, dt=None):
        """Call of the LMUL 1 function `fname` (registered as a dependency)."""
        dt = dt or self.dt_par
        self.calls.add((fname, _VARIANT_OF[mk]))
        return build_func_name_short(self.isa, dt, fname, True, masked_version=mk) + "(" + ", ".join(args) + ")"

    def wrap(self, *names):
        """Declares the LMUL 1 versions of d2 parameters: `w_<name>`."""
        lines = []
        for p in self.params:
            if p["name"] in names:
                m1 = build_type(p["kind"] if p["kind"] != "vindex" else "reg", p["dt"], self.isa, 0, True, False)
                member = "m" if p["kind"] == "msk" else "r"
                lines.append(f"{m1} w_{p['name']}; w_{p['name']}.{member} = {p['name']}.{member};")
        return "\n".join(lines)

    def ret_d2(self, expr):
        """Returns the LMUL 1 result `expr` as a d2 result."""
        ret = self.proto["ret"]
        if ret["type"] not in ("reg", "msk"):
            return f"return {expr};"
        realdt = datatypes[self.dt_ret]
        if ret["fixeddatatype"]:
            realdt = datatypes[ret["fixeddatatype"]]
        d2 = build_type(ret["type"], realdt, self.isa, -2, True, False)
        member = "r" if ret["type"] == "reg" else "m"
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


def _emit_one(isa, file, funcs, templates, f, dt, mask_kind, record_call):
    dt_par, dt_ret = compute_dt_par_dt_ret(funcs, f, dt)
    maybe_emit_ldiv_separator(isa["name"], f, file)
    name = build_func_name_internal(isa, dt, dt_par, dt_ret, f, masked_version=mask_kind, lmul=-2)
    proto = build_proto(funcs[f]["proto"], dt_par, dt_ret, isa, name, lmul=-2, isa_name=True, masked_version=mask_kind)

    proto_info = dict(funcs[f]["proto"])
    proto_info["_name"] = f
    params = _params(proto_info, dt_par, isa, mask_kind)
    calls = set()
    ctx = _Ctx(isa, funcs, f, dt, dt_par, dt_ret, mask_kind, params, calls)

    entry = _select_template(templates, f, dt_par, mask_kind)
    if entry is None:
        body = _wrapper_body(ctx, params)
        lvl = BASE_LEVELS.get((isa["name"], f, dt_par + "," + dt_ret, mask_kind), 2)
        level = _LEVEL_TEXT[lvl] + ": lane-wise, inherited from the LMUL 1 function on the same register"
    else:
        code = entry["code"]
        if isinstance(code, list):
            code = "\n".join(code)
        body = Template(code, undefined=StrictUndefined).render(
            ctx=ctx, f=f, dt=datatypes[dt_par], dt_ret=datatypes[dt_ret], mask_kind=mask_kind,
            isa=isa, isa_dt=isa["datatypes"][dt_par], D2=build_reg(datatypes[dt_ret], isa, -2, True, False), N=ctx.N(), N2=ctx.N2(), T=build_val(datatypes[dt_par], isa),
            call1=ctx.call1, wrap=ctx.wrap, ret_d2=ctx.ret_d2, lanemask=ctx.lanemask, neutral=ctx.neutral,
            R1=build_reg(datatypes[dt_par], isa, 0, True, False), M1=build_msk(datatypes[dt_par], isa, 0, True, False),
            UI="uint" + str(datatypes[dt_par]["n_bits"]), UT="uint" + str(datatypes[dt_par]["n_bits"]) + "_t",
        )
        if "level" in entry:
            lvl = entry["level"]
        else:
            lvl = 1 if entry.get("_dedicated") else 2
        level = _LEVEL_TEXT[lvl] + ": half-vector specific, the upper lanes are not read"

    guard = isa["datatypes"].get(dt_par, {}).get("if", None)
    print("", file=file)
    if guard:
        print(f"#if {guard}", file=file)
    print(f"static {proto} {{", file=file)
    print(f"\t// {level}", file=file)
    for line in body.split("\n"):
        if line.strip():
            print("\t" + line, file=file)
    print("}", file=file)
    if guard:
        print("#else", file=file)
        print(f"static {proto} {{", file=file)
        emit_panic_stub(name, file=file)
        print("}", file=file)
        print("#endif", file=file)
    for (callee, callee_variant) in calls:
        record_call(f, _VARIANT_OF[mask_kind], callee, callee_variant)


def gen_c_ldiv_mask(isa, include_manager, funcs):
    if not uses_mask_ldiv(isa):
        print(f"in ldiv_mask.gen_c_ldiv_mask : error : '{isa['name']}' does not declare 'sw_ldiv_type: mask' with -2 in sw_lmul")
        exit(-1)
    templates = _load_templates(isa, funcs)

    def record_call(f, variant, callee, callee_variant):
        include_manager.add_call_dependency(isa["name"], f, variant, "d2", callee, callee_variant, "m1")

    for f in funcs:
        mask_support = funcs[f]["mask_support"] if "mask_support" in funcs[f] else None
        kinds = [None]
        if mask_support:
            if mask_support.is_maskable():
                kinds.append("mask")
            if mask_support.is_maskzable():
                kinds.append("maskz")
            if mask_support.is_masksable():
                kinds.append("masks")
        for mask_kind in kinds:
            file_w = include_manager.get_fd(isa["name"], f, variant=_VARIANT_OF[mask_kind], lmul=-2)
            for dt in funcs[f]["datatypes"]:
                _emit_one(isa, file_w, funcs, templates, f, dt, mask_kind, record_call)
