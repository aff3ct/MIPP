"""Test properties of the functions, as the generated unit tests apply them.

The Function Support pages ("Test & Verification Specifications") and the "Verification Specs" tab
of the API Explorer show, for each function, mask variant and datatype, how the unit tests draw the
inputs and how they compare each lane with the scalar reference. These properties are resolved here
with the test generator itself (helpers_tests: TestsBuilderEngine and DomainResolver), following the
C API tests, and are checked against the code that the test generator writes: a mismatch is reported
on the standard error, so that the documentation never silently drifts from the tests.
"""
import contextlib
import io
import os
import sys

from helpers_tests.tests_builder import TestsBuilderEngine
from helpers_tests.indexed_tests import INDEXED_FUNCS

VARIANTS = ("unmasked", "mask", "maskz", "masks")
INPUT_VARS = ("inputs1", "inputs2", "inputs3")

MASK_PATTERN_TEXT = {
    "uniform_bool": "random (each lane active with probability 1/2)",
    "alternating": "even lanes active",
    "sparse": "one lane in four active",
    "dense": "three lanes in four active",
    "all_true": "all lanes active",
    "all_false": "all lanes inactive",
}

_FLOATS = ("float32", "float64")
_TOL_LEAF_KEYS = frozenset({"type", "value", "abs_value", "rel_value"})

_engine = None


def get_engine(repo_root):
    """The test generator (loaded once, without its console output)."""
    global _engine
    if _engine is None:
        with contextlib.redirect_stdout(io.StringIO()):
            _engine = TestsBuilderEngine(base_dir=repo_root, active_audits=set())
    return _engine


# ---------------------------------------------------------------------------
# Text of the values
# ---------------------------------------------------------------------------

def _num(v, dt):
    """A bound as the test uses it: static_cast to the datatype."""
    if not dt.startswith("float"):
        return str(int(v))
    v = float(v)
    if v.is_integer() and abs(v) < 1e15:
        return str(int(v))
    return repr(v)


def _define_name(define):
    return define[5:] if define.startswith("MIPP_") else define


def _spec_text(spec, dt, dist, sigma):
    """Values drawn by rnd:: for a resolved domain spec (see DomainResolver._spec_to_random_call
    and tests/src/utils/random.hpp)."""
    is_float = dt.startswith("float")
    normal = dist == "normal"
    spec = spec or {}
    mn, mx = spec.get("min"), spec.get("max")
    if mn is not None and mx is not None:
        txt = f"[{_num(mn, dt)}, {_num(mx, dt)}]"
        if normal:
            sig = sigma if sigma is not None else (mx - mn) / 6
            txt = f"normal in {txt}, σ = {sig:g}"
        if spec.get("exclude_zero"):
            txt += " ∖ {0}"
        return txt
    named = [
        ("strictly_positive", "(0, 1]", "[1, max]", "> 0"),
        ("positive", "[0, 1]", "[0, max]", "≥ 0"),
        ("strictly_negative", "[-1, 0)", "[min, -1]", "< 0"),
        ("negative", "[-1, 0]", "[min, 0]", "≤ 0"),
    ]
    for key, f_txt, i_txt, sign in named:
        if spec.get(key):
            if normal:
                return f"normal, {sign}, σ = {sigma if sigma is not None else 1:g}"
            return f_txt if is_float else i_txt
    if normal:
        txt = f"normal, μ = 0, σ = {sigma if sigma is not None else 1:g}"
    else:
        txt = "[-1, 1]" if is_float else "full range"
    if spec.get("exclude_zero"):
        txt += " ∖ {0}"
    return txt


def _spec_range(spec, dt):
    """Numeric bounds of a resolved spec (example values of the Algorithm modal), or None."""
    spec = spec or {}
    if spec.get("min") is not None and spec.get("max") is not None:
        return [spec["min"], spec["max"]]
    if not dt.startswith("float"):
        return None
    if spec.get("strictly_positive"):
        return [0.001, 1]
    if spec.get("positive"):
        return [0, 1]
    if spec.get("strictly_negative"):
        return [-1, -0.001]
    if spec.get("negative"):
        return [-1, 0]
    return [-1, 1]


def _branches_text(branches, dt, dist, sigma):
    """Text of the `#if defined(...)` branches of an input: default first, then the targets."""
    default = next(s for d, s in branches if d is None)
    txt = _spec_text(default, dt, dist, sigma)
    others = [f"{_define_name(d)}: {_spec_text(s, dt, dist, sigma)}" for d, s in branches if d is not None]
    return txt + (f" ({'; '.join(others)})" if others else "")


# ---------------------------------------------------------------------------
# Resolution (mirrors DomainResolver._render_input_filling_base and
# TestsBuilderEngine.render_c_validation_block, C dialect)
# ---------------------------------------------------------------------------

def _input_branches(dr, func_spec, var, dt_cstd, mkind, dt_pair):
    """[(define or None, spec)]: the domain of an input in each `#if defined(define)` branch of the
    C test, the default (#else, or no #if) last."""
    node = dr._get_domain_node(func_spec, var, mkind=mkind)
    if isinstance(node, dict) and "by_define" in node:
        idx = dr._get_var_idx(var)
        branches = [(d, dr._resolve_c_spec_from_node(n, dt_cstd, idx)) for d, n in node["by_define"].items()]
        branches.append((None, dr.resolve_domain_spec(func_spec, var_name=var, dt=dt_cstd, lmul="m1", mkind=mkind)))
        return branches
    return [(None, dr.resolve_domain_spec(func_spec, var_name=var, dt=dt_cstd, lmul="m1", mkind=mkind,
                                          dt_pair=dt_pair))]


def _render_branches(dr, branches, var, dt_cstd, dist, sigma):
    """C lines of the branches (to check them against the test generator)."""
    def line(spec):
        expr = dr._spec_to_random_call(spec, is_cpp=False, dt_cstd=dt_cstd, distribution=dist, sigma=sigma)
        return f"\t\t\t{var}[i] = {expr};"
    if len(branches) == 1:
        return [line(branches[0][1])]
    out = []
    for k, (d, s) in enumerate(branches[:-1]):
        out.append(f"{'#if' if k == 0 else '#elif'} defined({d})")
        out.append(line(s))
    out.append("#else")
    out.append(line(branches[-1][1]))
    out.append("#endif")
    return out


def _tol_leaf(spec, dt):
    """Tolerance of a datatype (mirrors TestsBuilderEngine._tol_spec_to_expr, concrete type)."""
    if not spec or spec.get("type") == "exact":
        return {"type": "exact"}
    content = _TOL_LEAF_KEYS | {"by_lmul", "by_datatype"}
    if "default" in spec and not any(k in spec for k in content):
        spec = spec["default"]
        if not spec or spec.get("type") == "exact":
            return {"type": "exact"}
    if "by_datatype" in spec:
        default_sub = (spec.get("default")
                       or {k: v for k, v in spec.items() if k in _TOL_LEAF_KEYS | {"by_lmul"}}
                       or {"type": "exact"})
        return _tol_leaf(spec["by_datatype"].get(dt, default_sub), dt)
    leaf = {"type": spec.get("type", "max_abs_diff"), "value": spec.get("value", 0.001)}
    if "by_lmul" in spec:
        leaf["by_lmul"] = spec["by_lmul"]
    elif leaf["type"] == "hybrid":
        leaf.update(abs_value=spec.get("abs_value", 0.0), rel_value=spec.get("rel_value", 0.0))
    return leaf


def _tol_branches(engine, func_spec):
    """[(define or None, tolerance spec)] (mirrors render_tolerance_declaration)."""
    default_tol = engine.specs.get("default", {}).get("tolerance", {"type": "exact"})
    tol = func_spec.get("tolerance", default_tol)
    if isinstance(tol, dict) and "by_define" in tol:
        fallback = {k: v for k, v in tol.items() if k != "by_define"} or default_tol
        fb_dt = fallback.get("by_datatype", {})
        out = []
        for d, ds in tol["by_define"].items():
            if "by_datatype" in ds and fb_dt:
                ds = {**ds, "by_datatype": {**fb_dt, **ds["by_datatype"]}}
            out.append((d, ds))
        out.append((None, fallback))
        return out
    return [(None, tol)]


def _leaf_text(leaf):
    t = leaf["type"]
    if t == "exact":
        return "exact"
    if "by_lmul" in leaf:
        vals = [f"{leaf['value']:g}"] + [f"LMUL {k}: {float(v):g}" for k, v in leaf["by_lmul"].items()]
        scale = " × |ref|" if t == "relative_percent" else ""
        return f"|r − ref| ≤ {vals[0]}{scale} ({'; '.join(vals[1:])})"
    if t == "relative_percent":
        return f"|r − ref| ≤ {leaf['value'] * 100:g} % of |ref|"
    if t == "hybrid":
        return f"|r − ref| ≤ {leaf['abs_value']:g} + {leaf['rel_value']:g} × |ref|"
    return f"|r − ref| ≤ {leaf['value']:g}"


def _comparison(engine, func, func_spec, dt1, dt2, is_msk_ret):
    """(text, exact): how a lane is compared with the scalar reference."""
    comp = func_spec.get("comparison", "exact")
    if isinstance(comp, dict):
        comp = comp.get("by_datatype", {}).get(dt2, comp.get("default", "exact"))
    has_tol = "tolerance" in func_spec or comp == "tolerance"
    if comp == "bitwise":
        return "Same bits", True
    if comp == "logical" or is_msk_ret or func.endswith("_k"):
        return "Same truth value", True
    if has_tol and (dt2 in _FLOATS or dt1 in _FLOATS):
        tdt = dt2 if dt2 in _FLOATS else dt1
        branches = _tol_branches(engine, func_spec)
        default = next(_tol_leaf(s, tdt) for d, s in branches if d is None)
        txt = _leaf_text(default)
        others = [f"{_define_name(d)}: {_leaf_text(_tol_leaf(s, tdt))}" for d, s in branches
                  if d is not None and _tol_leaf(s, tdt) != default]
        if others:
            txt += f" ({'; '.join(others)})"
        exact = default["type"] == "exact" and not others
        return ("Exact" if exact else txt), exact
    return "Exact", True


def _check_tolerance(engine, func, func_spec, dt2):
    """The tolerance expressions of the test generator rebuilt from the resolved leaves."""
    if dt2 not in _FLOATS:
        return True
    cdt = f"{dt2}_t"
    for _, s in _tol_branches(engine, func_spec):
        if engine._tol_spec_to_expr(_tol_leaf(s, dt2), cdt, "ref") != engine._tol_spec_to_expr(s, cdt, "ref"):
            return False
    return True


def _warn(msg):
    print(f"[test_specs] warning: {msg}", file=sys.stderr)


def resolve_function(engine, func):
    """Test properties of a function: rows per mask variant and datatype, and notes."""
    dr = engine.domain_resolver
    func_spec = engine.specs["functions"].get(func, {})
    default_spec = engine.specs.get("default", {})
    iface = engine.interfaces[func]
    proto_ref = iface.get("proto_ref", "")
    func_variants = iface.get("variants", ["u", "m", "z", "s"])
    variants = [v for v in VARIANTS
                if v == "unmasked" or engine._is_mask_kind_supported(func_variants, v)]
    datatypes = engine._resolve_datatypes(func)
    indexed = func in INDEXED_FUNCS
    if indexed:
        # gather / scatter: one test per data type (the index type follows it)
        datatypes = list(dict.fromkeys(str(d).split(",")[0].strip() for d in datatypes))

    n_inputs = 1
    if not engine.proto_is_1arg(proto_ref) or engine.scalar_arg_from_inputs2(func):
        n_inputs = 2
    if engine.proto_is_3arg(proto_ref):
        n_inputs = 3
    is_msk_ret = engine.proto_is_msk_ret(proto_ref)

    out_variants = {}
    for v in variants:
        mkind = "" if v == "unmasked" else v
        dist, sigma = dr._extract_distribution(func_spec, mkind=mkind)
        rows = []
        for dt_name in datatypes:
            parts = [p.strip() for p in str(dt_name).split(",")]
            dt1, dt2 = parts[0], (parts[1] if len(parts) > 1 else parts[0])
            dt_cstd = f"{dt1}_t"
            dt_pair = dt_name if "," in dt_name else ""
            inputs, ranges = [], []
            if indexed:
                inputs.append(_spec_text(None, dt1, "uniform", None))
                ranges.append(_spec_range(None, dt1))
            else:
                for k in range(n_inputs):
                    var = INPUT_VARS[k]
                    branches = _input_branches(dr, func_spec, var, dt_cstd, mkind, dt_pair if k == 0 else "")
                    expected = dr._render_input_filling_base(func_spec, var, "c", dt_cstd, "m1", "", mkind,
                                                             dt_pair if k == 0 else "")
                    if _render_branches(dr, branches, var, dt_cstd, dist, sigma) != expected:
                        _warn(f"{func} ({v}, {dt_name}, {var}): domain differs from the generated test")
                    inputs.append(_branches_text(branches, dt1, dist, sigma))
                    ranges.append(_spec_range(next(s for d, s in branches if d is None), dt1))
            src = None
            if v == "masks" and not indexed:
                src_br = _input_branches(dr, func_spec, "inputs_src", dt_cstd, mkind, "")
                src_txt = _branches_text(src_br, dt1, dist, sigma)
                if src_txt != inputs[0]:
                    src = src_txt
            if indexed:
                comp_txt, exact = "Exact", True
            else:
                comp_txt, exact = _comparison(engine, func, func_spec, dt1, dt2, is_msk_ret)
                if not _check_tolerance(engine, func, func_spec, dt2):
                    _warn(f"{func} ({dt_name}): tolerance differs from the generated test")
            rows.append({"datatype": dt_name, "inputs": inputs, "src": src,
                         "comparison": comp_txt, "exact": exact, "ranges": ranges})
        pattern = None
        if v != "unmasked":
            pattern = "uniform_bool" if indexed else (
                (func_spec.get(v) or {}).get("mask_pattern") or func_spec.get("mask_pattern", "uniform_bool"))
        out_variants[v] = {"rows": rows, "mask_pattern": pattern,
                           "mask_text": MASK_PATTERN_TEXT.get(pattern, pattern) if pattern else None}

    # Notes of the function (same for every variant and datatype)
    notes = []
    if indexed:
        if func == "gather":
            notes.append("Indices: random values of [0, N) (N lanes); data: random values (default range).")
        else:
            notes.append("Indices: a permutation of [0, N) (N lanes), so that the result does not depend on "
                         "the order of the writes; data: random values (default range). The memory written "
                         "by both targets is compared.")
    ovf = None if indexed else func_spec.get("overflow_check")
    if ovf in ("add", "sub", "mul"):
        op = {"add": "+", "sub": "−", "mul": "×"}[ovf]
        notes.append(f"Lanes where a {op} b overflows the datatype are skipped (C API tests).")
    elif ovf in ("accumulate_add", "accumulate_mul"):
        what = "sum" if ovf == "accumulate_add" else "product"
        notes.append(f"An iteration is skipped when the {what} of the lanes overflows the datatype.")
    if not indexed and func_spec.get("nan_inf_skip"):
        notes.append("Lanes where the result or the reference is NaN or infinite are skipped.")
    skip = func_spec.get("skip_condition", default_spec.get("skip_condition"))
    if not indexed and isinstance(skip, dict) and skip.get("type") == "fractional_part":
        notes.append(f"Lanes whose reference has a fractional part within {skip['tol']:g} of "
                     f"{skip['value']:g} are skipped (rounding ties).")
    if func_spec.get("disabled"):
        notes.append(f"The test is disabled: {func_spec.get('disabled_reason') or 'see tests_specs.json'}.")
    elif not func_spec.get("support_obj", default_spec.get("support_obj", True)):
        notes.append("No C++ Object API test (the function has no Object overload).")

    special = {}
    sv = func_spec.get("special_values")
    if not indexed and isinstance(sv, dict):
        special = {dt: list(vals) for dt, vals in sv.get("by_datatype", {}).items()}

    return {"variants": out_variants, "notes": notes, "special_values": special, "n_inputs": n_inputs}


def resolve_all(repo_root, funcs):
    engine = get_engine(repo_root)
    return {f: resolve_function(engine, f) for f in funcs if f in engine.interfaces}


# ---------------------------------------------------------------------------
# Helpers shared by the renderers
# ---------------------------------------------------------------------------

def inputs_cell(row):
    """One text for all the inputs when they are drawn alike, else one per input (in1, in2, ...)."""
    ins = row["inputs"]
    parts = [ins[0]] if len(set(ins)) == 1 else [f"in{k + 1}: {t}" for k, t in enumerate(ins)]
    if row.get("src"):
        parts.append(f"src: {row['src']}")
    return parts


def variants_alike(spec):
    """True when every mask variant draws and compares the same way (one table is enough)."""
    vs = list(spec["variants"].values())
    key = lambda v: [(r["inputs"], r["src"], r["comparison"]) for r in v["rows"]]
    masked = [v["mask_pattern"] for v in vs if v["mask_pattern"]]
    return all(key(v) == key(vs[0]) for v in vs) and len(set(masked)) <= 1


def group_rows(rows):
    """Rows with the same cells grouped: [(datatypes, row)], in the order of the first datatype."""
    groups = []
    for r in rows:
        k = (tuple(inputs_cell(r)), r["comparison"])
        for g in groups:
            if g[0] == k:
                g[1].append(r["datatype"])
                break
        else:
            groups.append((k, [r["datatype"]], r))
    return [(dts, r) for _, dts, r in groups]


def datatypes_label(dts, all_dts):
    """Label of a group of datatypes ("float32 → any" for all the targets of a source type)."""
    if list(dts) == list(all_dts) and len(dts) > 1:
        return ["all"]
    if not all("," in d for d in dts):
        return list(dts)
    by_src, all_by_src = {}, {}
    for d in all_dts:
        all_by_src.setdefault(d.split(",")[0].strip(), []).append(d)
    for d in dts:
        by_src.setdefault(d.split(",")[0].strip(), []).append(d)
    out = []
    for src, ds in by_src.items():
        if len(ds) > 1 and ds == all_by_src[src]:
            out.append(f"{src} → any")
        else:
            out.extend(f"{a.strip()} → {b.strip()}" for a, b in (x.split(",") for x in ds))
    return out
