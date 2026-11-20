# Code Generation Sub-Modules (`codegen`)

Candidate resolution and emission of the per-ISA C code, used by `c_generator.py`:

| File | Role |
| :--- | :--- |
| `candidate_resolver.py` | Candidate resolution (levels 0 to 2, scalar fallback, stubs), effective levels, emission of the function bodies. |
| `lmul_orchestrator.py` | Software LMUL and `sub_isa` half-vector wrappers, horizontal LMUL wrappers. |
| `ldiv_mask.py` | Half-vectors by mask (`"sw_ldiv_type": "mask"`) and the functions that change the LMUL between `m1` and `d2` (`low`, `high`, `combine`, `wcvt`, `ncvt`), from `generic_ldiv_mask.json` and `<isa>_ldiv_mask.json`. |
| `emit_helpers.py` | Function bodies, `// Level N` comments, panic stubs (`MIPP_PANIC_STUB`). |
| `implem_tracker.py` | Implementation status per function, datatype and mask variant. |

The algorithm is described in the Developer Guide: [Code Generation](../../../docs/developer/internals/code_generation.md) (online: <https://aff3ct.github.io/MIPP/developer/internals/code_generation/>).
