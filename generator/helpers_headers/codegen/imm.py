"""
Immediate versions of the functions whose integer argument is often a constant (`slide`, `broadcast_lane`, `get`,
`lshift_vs`...).

The integer argument of these functions is an ordinary argument: a variable or a constant. Many instructions only
take a constant, encoded in the instruction (an immediate: `palignr`, `vext`, `pshufd`, `vdupq_laneq`...), and a
static inline function cannot pass its parameter to them (clang checks the immediate before inlining). The generated
function therefore keeps its dynamic body and starts with a dispatch, used when the compiler knows the value:

    static inline rvd_sse_float32_m1_t mipp_sse_slide_float32_m1(const rvd_sse_float32_m1_t r0, ..., const int32_t s0) {
        // Level 2 (Generic Emulation)
    #if defined(__OPTIMIZE__) && (defined(__SSSE3__))
        if (__builtin_constant_p(s0)) { // immediate when s0 is a constant: alignr
            switch (s0) {
            case 0: { ... _mm_alignr_epi8(..., 0) ...; }
            case 1: { ... _mm_alignr_epi8(..., 4) ...; }
            ...
            default: break;
            }
        }
    #endif
        <dynamic body>
    }

Once the function is inlined with a constant, `__builtin_constant_p` is true, the switch is resolved at compile time
and only the immediate instruction is left; with a variable (or without optimization), the dynamic body runs.

Sources:
- `registry_interfaces.json`: `"imm": "<range>"` marks a function and gives the values of its integer argument
  (`IMM_RANGES`);
- `simd_ext/<isa>/<isa>_imm_templates.json` and `<isa>_imm_implems.json`: the bodies of an ISA, in the format of the
  emulation files (`datatypes`, `if`, `template`, `instr_name`). The template is rendered for each value with the
  Jinja variables of the other templates plus `imm` (the value), `lanes` (the number of lanes) and `block` (the number
  of lanes of a block of 128 bits); a body that renders to nothing is not a case (the dynamic body is used for this
  value). The bodies use intrinsics and the types of the DSL (`%r<tp>%`...) only: a call to a MIPP function would not
  be seen by the include resolution.

Only the unmasked functions of LMUL 1 of the ISAs with a fixed register size get a dispatch: the masked variants and
the other LMULs call them, and the constant goes through the inlining.

The switch counts in the size estimated by the inliner even with a variable: a function whose dynamic body already
compiles to the immediate instruction with a constant gets no bodies. `get` has a range (for its C++ template) and no
case: `storeu` then `t[s0]` with a constant is an extraction for GCC and Clang, and with a dispatch the larger `get`
and the `get_k` of the LMUL > 1 masks were not inlined in big translation units, which revealed a GCC 13 bug on the
AVX-512 mask groups passed by value (see docs/developer/internals/code_generation.md, immediate versions).
"""
import os

from jinja2 import Template, StrictUndefined

from luts import TEMPLATE_GLOBALS

# values of the integer argument, from the number of lanes N, the lanes of a block of 128 bits NB and the bits B of
# the elements (the same names as the `lane_index` of the test specs)
IMM_RANGES = {
    "lt_n": lambda n, nb, b: range(0, n),        # broadcast_lane, rotate, get
    "le_n": lambda n, nb, b: range(0, n + 1),    # slide, slide_up, slide_down
    "lt_nb": lambda n, nb, b: range(0, nb),      # the _b128 variants of the above
    "le_nb": lambda n, nb, b: range(0, nb + 1),
    "lt_bits": lambda n, nb, b: range(0, b),     # shift counts
}

_imm_cache = {}


def load_imm_implems(isa_name):
    """Immediate bodies of an ISA ({function: [entries]}, templates resolved), {} without the files."""
    if isa_name not in _imm_cache:
        from tools import load_implem_tables
        base_dir = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
        ext_dir = os.path.join(base_dir, "simd_ext", isa_name)
        tpl, impl = f"{isa_name}_imm_templates.json", f"{isa_name}_imm_implems.json"
        if os.path.exists(os.path.join(ext_dir, tpl)) and os.path.exists(os.path.join(ext_dir, impl)):
            _, _imm_cache[isa_name] = load_implem_tables(os.path.join(ext_dir, "__init__.py"), tpl, impl)
        else:
            _imm_cache[isa_name] = {}
    return _imm_cache[isa_name]


def _int_arg_name(proto):
    """Name of the integer argument of the prototype (`s<k>`: the scalars are numbered on their own)."""
    k = 0
    for a in proto["args"]:
        if a["type"] == "val":
            if a.get("fixeddatatype") not in (False, None, "par", "ret"):
                return f"s{k}"
            k += 1
    return None


def build_imm_dispatch(isa, funcs, f, dt, dt_par, dt_ret):
    """
    Lines of the dispatch of `f` for the datatype `dt` (unmasked, LMUL 1), to write at the beginning of the body, or
    None when there is no immediate body (function without `imm`, ISA without entry or without fixed register size).
    """
    from tools import datatypes, parse_placeholders
    rng = funcs[f].get("imm")
    if not rng or not isinstance(isa.get("size"), int):
        return None
    entries = [e for e in load_imm_implems(isa["name"]).get(f, []) if dt in e.get("datatypes", [])]
    if not entries:
        return None
    arg = _int_arg_name(funcs[f]["proto"])
    if arg is None:
        raise ValueError(f"'{f}' has an immediate range but no integer argument")
    n_bits = datatypes[dt_par]["n_bits"]
    lanes = isa["size"] // n_bits
    block = min(128 // n_bits, lanes)
    values = list(IMM_RANGES[rng](lanes, block, n_bits))

    lines = []
    for i, e in enumerate(entries):
        cond = "defined(__OPTIMIZE__)" + (f" && ({e['if']})" if e.get("if") else "")
        lines.append(("#if " if i == 0 else "#elif ") + cond)
        lines.append(f"\tif (__builtin_constant_p({arg})) {{ // immediate when {arg} is a constant: {e.get('instr_name', f)}")
        lines.append(f"\t\tswitch ({arg}) {{")
        code = e["template"]["code"]
        code = "\n".join(code) if isinstance(code, list) else code
        tpl = Template(code, undefined=StrictUndefined)
        tpl.globals.update(TEMPLATE_GLOBALS)
        for v in values:
            rendered = tpl.render(isa=isa, instr_name=e.get("instr_name", ""), dt_par=datatypes[dt_par],
                                  dt_ret=datatypes[dt_ret], isa_dt_par=isa["datatypes"][dt_par],
                                  isa_dt_ret=isa["datatypes"][dt_ret], cstdint_ret=datatypes[dt_ret]["cstd"],
                                  func_name=f, lmul=0, mask_kind=None, imm=v, lanes=lanes, block=block)
            if not rendered.strip():
                continue
            ph = parse_placeholders(rendered, isa, funcs, f, dt_par, dt_ret, lmul=0)
            calls = [g for g in ph.get("requirements", {}) if g != f]
            if calls:
                raise ValueError(f"immediate body of '{f}' ({isa['name']}, {dt}) calls MIPP functions {calls}: "
                                 "only intrinsics and the types of the DSL are allowed")
            lines.append(f"\t\tcase {v}: {{")
            lines += ["\t\t\t" + l.strip() for l in ph["converted_ir"].strip("\n").split("\n") if l.strip()]
            lines.append("\t\t}")
        lines.append("\t\tdefault: break;")
        lines.append("\t\t}")
        lines.append("\t}")
    lines.append("#endif")
    return lines
