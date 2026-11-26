"""
The functions to write first for a new ISA (tutorial "Add an ISA", step 4).

An ISA whose implementation files are empty is simulated with the candidate resolver of the
generator: every function then has its generic emulation (L2) or the scalar fallback (L3), and
an emulation that calls a function at L3 is at L3 too. A function "written" for the simulation
gets a native implementation (L0) for all its datatypes, unmasked: the masked variants and the
scalar forms keep their generic code.

- The core: a small set of functions that, once written, leaves no more entries at L3 than
  writing every function. It holds the functions that nothing replaces (each one, missing while
  all the others are written, sends entries to L3), completed greedily by the function that
  removes the most entries from L3, until that minimum is reached.
- The weight of a function of the core: the functions that go back to L3 without it, the rest of
  the core being written.

The resolver depends on the descriptor of the ISA (datatypes, LMUL, masks), not on its
implementations: the simulation uses the descriptor of an existing ISA, SIM_ISA.
"""
import copy
import multiprocessing

from registry import interfaces, form_functions
from gen_mipp_headers import discover_and_sort_isas
from c_generator import resolve_lmul_in_isa, register_all_candidates
from codegen.candidate_resolver import resolve_candidates

SIM_ISA = "neon"

_isa = None       # descriptor of SIM_ISA (set by _init, in the worker processes too)
_template = None  # any template of the ISA: the levels do not depend on the code


def _init(generator_dir):
    global _isa, _template
    isas, implems, _ = discover_and_sort_isas(generator_dir)
    _isa = isas[SIM_ISA]
    _template = next(iter(implems[SIM_ISA][0].values()))[0]["template"]


def _levels(written):
    """{(function, datatype, mask kind or None): effective level}, the functions `written` at L0."""
    native = {f: [{"instr_name": f, "datatypes": list(interfaces[f]["datatypes"]), "template": _template}]
              for f in written}
    isa = resolve_lmul_in_isa(_isa, "0")
    isa["candidates"] = []
    funcs = copy.deepcopy(interfaces)
    register_all_candidates(isa, funcs, native, {}, lmul=1)
    resolved = resolve_candidates(isa, funcs, lmul=1)
    return {k: min([c["level"] for c, cond in cands if cond != "0"] or [3]) for k, cands in resolved.items()}


def _n3(written):
    return sum(1 for v in _levels(written).values() if v == 3)


def _n3_without(args):
    written, f = args
    return f, _n3(set(written) - {f})


def _n3_with(args):
    written, f = args
    return f, _n3(set(written) | {f})


def _levels_without(args):
    written, f = args
    return f, _levels(set(written) - {f})


def _unmasked_levels(levels):
    """{function: set of the levels of its unmasked entries}"""
    out = {}
    for (f, _, mk), lv in levels.items():
        if mk is None:
            out.setdefault(f, set()).add(lv)
    return out


def compute(generator_dir):
    """
    Returns {"sim_isa", "n_functions", "empty": {"l3", "mixed", "l2"}, "core": [{"function",
    "functions", "forms", "masked", "examples"}] sorted by weight, "left_at_l3", "masked_left_at_l3"}:
    - the counts of "empty" are functions (unmasked) whose datatypes are all at L3, partly at L3,
      none at L3, with empty implementation files;
    - "functions" / "forms" are the functions / scalar forms that go back to L3 (unmasked) without
      the function of the core, "masked" the other functions whose masked variants go back to L3,
      "examples" the functions of "functions" that the fewest other functions of the core hold back;
    - "left_at_l3" / "masked_left_at_l3": functions still at L3 (unmasked / in a masked variant)
      once the core is written.
    """
    _init(generator_dir)
    names = sorted(interfaces)
    try:  # the worker processes inherit the registries (fork); otherwise a single process
        pool = multiprocessing.get_context("fork").Pool(initializer=_init, initargs=(generator_dir,))
    except ValueError:
        pool = None

    def run(fn, items):
        return pool.map(fn, items) if pool else [fn(x) for x in items]

    try:
        best = _n3(names)
        core = {f for f, n in run(_n3_without, [(names, f) for f in names]) if n > best}
        n3 = _n3(core)
        while n3 > best:
            f, n3 = min(run(_n3_with, [(sorted(core), f) for f in names if f not in core]),
                        key=lambda x: (x[1], x[0]))
            core.add(f)
        with_core = _levels(core)
        without = dict(run(_levels_without, [(sorted(core), f) for f in sorted(core)]))
        empty = _unmasked_levels(_levels(set()))
    finally:
        if pool:
            pool.close()
            pool.join()

    rows = []
    for f in sorted(core):
        fallen = [k for k, lv in without[f].items() if lv == 3 and with_core[k] != 3 and k[0] != f]
        unmasked = {k[0] for k in fallen if k[2] is None}
        rows.append({
            "function": f,
            "functions": sorted(x for x in unmasked if x not in form_functions),
            "forms": sorted(x for x in unmasked if x in form_functions),
            "masked": sorted({k[0] for k in fallen if k[2] is not None} - unmasked),
        })
    # functions of the core that hold back each function: its examples go to the most specific ones
    held_by = {}
    for r in rows:
        for g in r["functions"]:
            held_by[g] = held_by.get(g, 0) + 1
    for r in rows:
        r["examples"] = sorted(r["functions"], key=lambda g: (held_by[g], g))
    rows.sort(key=lambda r: (-len(r["functions"]), -len(r["forms"]), -len(r["masked"]), r["function"]))
    final = _unmasked_levels(with_core)
    return {
        "sim_isa": SIM_ISA,
        "n_functions": len(names),
        "empty": {
            "l3": sum(1 for lv in empty.values() if lv == {3}),
            "mixed": sum(1 for lv in empty.values() if 3 in lv and lv != {3}),
            "l2": sum(1 for lv in empty.values() if 3 not in lv),
        },
        "core": rows,
        "left_at_l3": sorted(f for f, lv in final.items() if 3 in lv),
        "masked_left_at_l3": sorted({k[0] for k, lv in with_core.items() if k[2] is not None and lv == 3}),
    }

