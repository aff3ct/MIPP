# Code Generation

This page describes what `gen_mipp_headers.py` does between the loaded JSON files and the headers of `include/`: the order of the generation, the candidate resolution that chooses an implementation level for each function, and the emission of the C code. It is meant for contributors who change the generator itself. To add functions or implementations, the [tutorials](../tutorials/add_function.md) are enough.

The options of the script are in the [Command-Line Reference](../reference/cli.md#gen_mipp_headers), and the files it writes in [Header Layout](header_layout.md).

---

## 1. Overview of a Run

| Step | What happens | Code |
| :--- | :--- | :--- |
| 1. Load | The registries are loaded and validated against their JSON Schemas when `registry.py` is imported. A validation error stops the script. | `helpers_headers/registry.py` |
| 2. Check | Cross-file validation checks (blocking) and the audits selected with `--audit` (warnings). | `helpers_headers/input_validation.py`, [Audits & Validation](../reference/audits.md) |
| 3. Discover the ISAs | Each directory of `simd_ext/` is an ISA. `--simd-ext` keeps the selected ISAs, their `sub_isa` chain and `scalar`. The ISAs are sorted so that a `sub_isa` comes before the ISAs built on it. | `discover_and_sort_isas()` in `gen_mipp_headers.py` |
| 4. ISA layers | One layer per ISA: `scalar` is emitted directly from `registry_scalar_implems.json`, the other ISAs go through the candidate resolution ([§2](#2-one-isa-layer)). | `simd_ext/scalar/scalar_gen.py`, `helpers_headers/c_generator.py` |
| 5. Wrappers | The C dispatch headers, the C++ Functional and C++ Object APIs, and the public headers. | `ci_generator.py`, `cpp_generator.py`, `obj_generator.py`, `generate_public_headers()` |
| 6. Summary | The table of the implementation levels per ISA ([§6](#6-summary-table)). | `print_summary_table()` in `gen_mipp_headers.py` |

`--layers` selects the layers of steps 4 and 5; the other steps always run.

---

## 2. One ISA Layer

`generate_c_layer()` (`c_generator.py`) builds the internal C headers of one ISA, in seven steps.

1. **Common header.** `simd_ext/<isa>/c/common.h` receives the `header_template` of the ISA descriptor, the ISA macros (`gen_c_defines()`) and the register types: `rvd_<isa>_<type>_t` for the data registers, `rvm_<isa>_<type>_t` for the masks, and their LMUL variants (`gen_c_structures()`).
2. **Hardware LMUL.** For LMUL `0` (the base registers) and each value of `hw_lmul`, the descriptor is specialized for this LMUL (`resolve_lmul_in_isa()`: a `{name}` placeholder in a field of a datatype takes the value of the field `name` of the same datatype, or of its `variables`, for this LMUL), the candidates are registered ([§3](#3-candidates)), resolved ([§4](#4-resolution)) and emitted ([§5](#5-emission)). Positive values come first, then the negative ones (half-vectors).
3. **Half-vectors on the sub-ISA.** With `"sw_ldiv_type": "sub_isa"`, `gen_c_ldiv()` writes the `_d2` functions as calls to the `sub_isa` functions (AVX `d2` calls SSE).
4. **Half-vectors by mask.** With `"sw_ldiv_type": "mask"` (SSE, NEON, SVE), `gen_c_ldiv_mask()` (`codegen/ldiv_mask.py`) writes each `_d2` function as a wrapper of the `m1` function on the same register (upper lanes ignored); the wrapper inherits the level of the `m1` function. Functions where the upper lanes are observable (load/store, gather/scatter, reductions, `testz`, `set`, `set_k`) use Jinja+C templates from `generic_ldiv_mask.json`, overridable per ISA in `simd_ext/<isa>/<isa>_ldiv_mask.json` (keys `a|b`, optional `variants`, `datatypes` and `level`). Types and element counts are written with the [mini-DSL](../reference/templating_dsl.md) relative to the LMUL of the function (`d2` for the half-vector functions, `m1` for `low` / `high`): `%r<tp>%`, `%N<tp>%`, `%N<tp|m:tp*2>%` (the elements of the full register), `%s<tp>%`, `%s<tp|c:uint>%`, and `%r<tr>%` / `%m<tr>%` for the result, whose LMUL is the one of the returned value for `low`, `high` and `combine`. Without `level`, the level of a template of an ISA file is detected with the rules of the level audit (L0: a single intrinsic or no instruction at all; L1: several intrinsics, or intrinsics and MIPP functions; L2: only MIPP functions, `call1`), and a template of the generic file is L2; the sequential ones (load, store, gather, scatter, `set`, `set_k`) are declared L3. An entry may have an `if` key (a C preprocessor condition such as `defined(__SSE4_1__)`): it is then only used when the condition holds, otherwise the generator falls back on the next matching entry (the other entries of the ISA file, then those of `generic_ldiv_mask.json`) down to an entry without `if`, or to the lane-wise wrapper of the `m1` function. `low`, `high` and `combine` have such a generic fallback (L3, through a buffer), so an ISA can restrict its native implementation with `if` without losing the function.
5. **LMUL 1 aliases.** `gen_c_lmul()` with `lmul1=True` first writes the LMUL 1 of `wcvt` and `combine`, which build a software LMUL 2 register from an LMUL 1 one. Then `gen_c_lmul1_aliases()` writes the functions without suffix, once every `_m1` function is known. For the functions that change the LMUL (`low`, `high`, `combine`, `wcvt`, `ncvt`, ...), several generators write the `_m1` functions (the half-vector templates, the software LMUL, the scalar templates): each declares what it writes with `record_lmul1_definition()`, and the aliases are written from this registry.
6. **Software LMUL.** For each positive value of `sw_lmul`, `gen_c_lmul()` (`codegen/lmul_orchestrator.py`) writes wrappers instead of resolving candidates:
    - `_m2`, `_m4`, `_m8` call the function of half the LMUL on each half of the register group;
    - the horizontal functions (`"horizontal": true` in the registry) use the templates of `generic_emu_templates_lmulh.json` instead, and get a panic stub when there is none.
7. **Dependencies and glue.** The `IncludeManager` adds the `#include` lines that each header needs and writes `simd_ext/<isa>/c/mipp_<isa>.h` ([Header Layout](header_layout.md)).

!!! note "LMUL `0` and `1`"
    Inside an ISA (`isa_name=True`) there is no level without suffix: `lmul_suffix()` of `name_builder.py` writes LMUL `0` (no LMUL) as `_m1`, for the types and for the functions (`rvd_avx_float32_m1_t`, `mipp_avx_add_float32_m1`). These are the definitions. The names without suffix (`rvd_avx_float32_t`, `mipp_avx_add_float32`) are their aliases: the types are `typedef`s written with the structures, and the functions are written by step 5 (`build_func_name_short(..., alias=True)`; in the C layer, `_ci_m1_level()` writes the `_m1` dispatchers and then the aliases). In the public C layer (`isa_name=False`), LMUL `0` stays the name without suffix.

!!! note "Sections of a header"
    A header of a function is split by banners (`emit_lmul_banner()`): `LMUL = 1 Aliases`, `Emulated LMUL > 1` (software registers) and, for the hardware LMUL > 1 of a coarse header, `Hardware LMUL > 1`. In fine granularity each header has the sections of its own LMUL. In coarse granularity, a single header has them one after the other: the native functions, then the aliases, then the emulated LMUL.

---

## 3. Candidates

A candidate is a possible implementation of one function, for one datatype (or datatype pair), one mask variant and one LMUL, on one ISA. `register_all_candidates()` creates one candidate per implementation entry and per datatype:

| Source | Candidate type | Level |
| :--- | :--- | :--- |
| `simd_ext/<isa>/<isa>_native_implems.json` | `native_or_emu` | <span class="mipp-isa-badge lvl-0">L0</span> |
| `simd_ext/<isa>/<isa>_emu_implems.json` | `native_or_emu` | <span class="mipp-isa-badge lvl-1">L1</span> |
| `helpers_headers/generic_emu_implems.json`, `generic_emu_implems_mask.json` | `generic_emu` | <span class="mipp-isa-badge lvl-2">L2</span> |
| added for every key (except on `scalar`) | `auto_scalar` | <span class="mipp-isa-badge lvl-3">L3</span> |
| added for every key | `stub` | <span class="mipp-isa-badge lvl-na">stub</span> |

In the code, the stubs have level 4.

The `if` condition of a candidate is the `if` of its entry, combined (`&&`) with the guard of its datatypes in the ISA descriptor (`datatypes.<type>.if`, or `datatypes.<type>.if_lmul.<lmul>` for one LMUL). A native or emulated candidate without condition gets the `define` of the ISA.

For each key (function, datatype pair, mask variant), the candidates are sorted by level, then by preference: first the entries whose `preferred_simd_ext` contains the ISA, then the entries without preference, then the entries that prefer other ISAs.

---

## 4. Resolution

`resolve_candidates()` (`codegen/candidate_resolver.py`) chooses, for each key, one or several candidates with disjoint conditions that together cover all the cases.

Each key has a **remaining condition**, initially *true*: the cases for which no implementation is chosen yet. The resolver repeats the following pass until nothing changes:

1. For each key whose remaining condition is not *false*, try the candidates in order, skipping those above the current maximum level and those whose `simd_size` does not match the register size of this LMUL.
2. The **target condition** of the candidate is its `if` intersected with the remaining condition. An empty intersection rejects the candidate.
3. The **dependencies** of the candidate are the MIPP functions called by its template (the `%function%` markers of the [templating DSL](../reference/templating_dsl.md)). Each dependency must already have an implementation whose condition is compatible with the target condition. The target condition is then restricted to the cases where the dependencies exist.
4. If the candidate is accepted, it is recorded with its target condition, and the remaining condition of the key becomes `remaining && !target`. The pass restarts.

The maximum level starts at <span class="mipp-isa-badge lvl-2">L2</span>. When a pass changes nothing, it is raised to <span class="mipp-isa-badge lvl-3">L3</span>, then to the stubs. This order matters: every vector implementation of every function is found before any scalar fallback is accepted, so that an <span class="mipp-isa-badge lvl-2">L2</span> sequence can rely on a native function that is resolved later in the same pass.

The conditions are C preprocessor expressions. `cond_utils.py` intersects, negates and simplifies them, and decides whether two conditions are mutually exclusive, knowing that the `define` of the ISA is true. This is how an AArch64-only native entry ends up as two branches:

```c
#if defined(__aarch64__)
static inline ... mipp_neon_<function>_float64(...) { /* Level 0 */ }
#endif
#if !defined(__aarch64__)
static inline ... mipp_neon_<function>_float64(...) { /* Level 3 */ }
#endif
```

**Dependencies of the scalar fallback.** On ISAs with hardware masks, the <span class="mipp-isa-badge lvl-3">L3</span> fallback converts the masks with `torvd` and `torvm` (`hw_mask_requires_torvd`), and extracts them with `store` (`hw_mask_extract_via_store`); with bitfield masks (`hw_mask_is_bitfield`, AVX-512) it copies the bits directly. These functions are dependencies of the fallback. On scalable layouts, the half-vector fallback is also guarded by the minimum vector length (`layout.vlen_guard_template`).

**Effective level.** After the resolution, the level of each chosen candidate becomes the highest level among itself and its dependencies (for a dependency with several branches, the best one counts). An <span class="mipp-isa-badge lvl-2">L2</span> sequence that calls an <span class="mipp-isa-badge lvl-3">L3</span> function is reported as <span class="mipp-isa-badge lvl-3">L3</span> in the generated comment, in the summary table and in the documentation.

---

## 5. Emission

`resolve_and_emit_missing_functions()` writes the resolved functions of one LMUL. For each function, it first writes the `static` prototypes of all its variants, so that the bodies can call each other in any order, then one body per chosen candidate, under `#if <target condition>` when the condition is not *true*:

- **Implementation entries** (`native_or_emu`, `generic_emu`). The template is rendered with Jinja2 (variables `isa`, `instr_name`, `dt_par`, `dt_ret`, `isa_dt_par`, `isa_dt_ret`, `cstdint_ret`, `func_name`, `lmul`, `mask_kind`), then the DSL markers are replaced by C names and calls (`parse_placeholders()` in `tools.py`). `emit_function_body()` (`codegen/emit_helpers.py`) writes the prototype, a `// Level N (...)` comment and the body.
- **Scalar fallback** (`auto_scalar`). `_gen_c_auto_scalar_fallback_one()` copies each register argument into a scalar register of the same size (`memcpy`), calls the `mipp_scalar_*` function and copies the result back.
- **Stub.** The body is `MIPP_PANIC_STUB("MIPP panic: '<function>' is unimplemented.");`. In C++ the macro throws `mipp::stub_exception`, which the generated tests catch and report as a warning; in C it prints the message and exits.

Example of an emitted <span class="mipp-isa-badge lvl-0">L0</span> function (`avx/c/functions/arithmetic/u/m1/add.h`, fine granularity):

```c
static inline rvd_avx_float32_t mipp_avx_add_float32(const rvd_avx_float32_t r0, const rvd_avx_float32_t r1) {
	// Level 0 (Native Hardware)
	rvd_avx_float32_t res;
	res.r = _mm256_add_ps(r0.r, r1.r);
	return res;
}
```

---

## 6. Summary Table

At the end of a run, `print_summary_table()` reads the generated `simd_ext/<isa>/c/functions/` headers and counts, per ISA and per level, the functions that carry a `// Level N` comment. The functions are split into three columns: `Std` (unmasked, LMUL 1), `Msk` (mask variants) and `LM/D` (LMUL > 1 and half-vectors). The `Stubs` column counts the `MIPP panic` lines.

!!! warning "The `LM/D` column is incomplete"
    The software LMUL wrappers ([§2](#2-one-isa-layer), step 3) and the `sub_isa` half-vectors (step 4) have no `// Level` comment, so they are not counted. The horizontal LMUL wrappers always carry `// Level 2`. On ISAs without hardware LMUL, the `LM/D` column therefore only counts the horizontal wrappers, and has the same value for every ISA.

---

## 7. Module Map

| File (in `generator/helpers_headers/`) | Role |
| :--- | :--- |
| `registry.py` | Loads and validates the registries; module-level data shared by the generators. |
| `input_validation.py` | Validation checks and header audits. |
| `tools.py` | ISA loading, datatype aliases, DSL parsing (`parse_placeholders()`, `get_requirements()`). |
| `datatypes.py`, `name_builder.py` | Datatypes; function names, prototypes and call arguments. |
| `cond_utils.py` | Parsing, simplification and algebra of preprocessor conditions. |
| `c_generator.py` | One ISA layer: common header, candidate registration, LMUL loops ([§2](#2-one-isa-layer)). |
| `codegen/candidate_resolver.py` | Candidate resolution, effective levels, emission, scalar fallback and stubs ([§4](#4-resolution), [§5](#5-emission)). |
| `codegen/lmul_orchestrator.py` | Software LMUL and `sub_isa` half-vector wrappers, horizontal LMUL wrappers. |
| `codegen/emit_helpers.py` | Function bodies, `// Level` comments, panic stubs, half-vector structures. |
| `codegen/implem_tracker.py` | Implementation status per function, datatype and mask variant (read by the dependency and include resolution). |
| `include_gen.py` | `IncludeManager`: files, includes and umbrella headers ([Header Layout](header_layout.md)). |
| `ci_generator.py`, `cpp_generator.py`, `obj_generator.py` | C dispatch headers, C++ Functional API, C++ Object API. |
