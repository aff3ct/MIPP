# Code Generation

This page describes what `gen_mipp_headers.py` does between the loaded JSON files and the headers of `include/`: the order of the generation, the candidate resolution that chooses an implementation level for each function, and the emission of the C code. It is meant for contributors who change the generator itself. To add functions or implementations, the [tutorials](../tutorials/add_function.md) are enough.

The options of the script are in the [Command-Line Reference](../reference/cli.md#gen_mipp_headers), and the files it writes in [Header Layout](header_layout.md).

---

## 1. Overview of a Run

| Step | What happens | Code |
| :--- | :--- | :--- |
| 1. Load | The registries are loaded and validated against their JSON Schemas when `registry.py` is imported. A validation error stops the script. The [scalar forms](../../user/scalar_forms.md) (`"forms"` of an interface) are expanded into functions of their own: prototype, category, scalar reference, and generic body appended to the generic tables (`forms.py`). | `helpers_headers/registry.py`, `helpers_headers/forms.py` |
| 2. Check | Cross-file validation checks (blocking) and the audits selected with `--audit` (warnings). | `helpers_headers/input_validation.py`, [Audits & Validation](../reference/audits.md) |
| 3. Discover the ISAs | Each directory of `simd_ext/` is an ISA. `--simd-ext` keeps the selected ISAs, their `sub_isa` chain and `scalar`. The ISAs are sorted so that a `sub_isa` comes before the ISAs built on it. | `discover_and_sort_isas()` in `gen_mipp_headers.py` |
| 4. ISA layers | One layer per ISA: `scalar` is emitted directly from `registry_scalar_implems.json`, the other ISAs go through the candidate resolution ([§2](#2-one-isa-layer)). | `simd_ext/scalar/scalar_gen.py`, `helpers_headers/c_generator.py` |
| 5. Wrappers | The global C header `mipp.h`, the C dispatch headers, the C++ Functional and C++ Object APIs, the public headers, and the hand-written utilities of the three APIs (`mipp/{c,cpp,obj}/utils.h(pp)`). | `generate_mipp_h()` in `include_gen.py`, `ci_generator.py`, `cpp_generator.py`, `obj_generator.py`, `generate_public_headers()`, `utils_generator.py` |
| 6. Summary | The table of the implementation levels per ISA ([§6](#6-summary-table)). | `print_summary_table()` in `gen_mipp_headers.py` |

`--layers` selects the layers of steps 4 and 5; the other steps always run.

---

## 2. One ISA Layer

`generate_c_layer()` (`c_generator.py`) builds the internal C headers of one ISA, in seven steps.

1. **Common header.** `simd_ext/<isa>/c/common.h` receives the `header_template` of the ISA descriptor, the ISA macros (`gen_c_defines()`) and the register types: `vd_<isa>_<type>_t` for the data registers, `vm_<isa>_<type>_t` for the masks, and their LMUL variants (`gen_c_structures()`).
2. **Hardware LMUL.** For each value of `hw_lmul` (default `[1]`), and for LMUL `0` (the base registers) when `hw_lmul` does not contain `1` (SSE, AVX, AVX-512, NEON: inside an ISA, LMUL `0` and `1` are the same `_m1` functions, see the note below), the descriptor is specialized for this LMUL (`resolve_lmul_in_isa()`: a `{name}` placeholder in a field of a datatype takes the value of the field `name` of the same datatype, or of its `variables`, for this LMUL), the candidates are registered ([§3](#3-candidates)), resolved ([§4](#4-resolution)) and emitted ([§5](#5-emission)). Positive values come first, then the negative ones (half-vectors).
    With several half-vector representations (`ldiv_modes` in the ISA descriptor, RVV: `MIPP_RVV_LDIV_HW`, `_VL`, `_HYBRID`), the half-vector types of `common.h`, the `d2` functions and the functions that change the LMUL between `m1` and `d2` are written once per mode, under `#if defined(<macro>)`, from a copy of the descriptor where the half-vector of the `vl_datatypes` of the mode is the register of LMUL 1 (`codegen/ldiv_modes.py`: the `lsuffix`, `eew_emul`... of `-2` take their value of LMUL 1, `if_lmul["-2"]` is dropped, `ldiv_vl` is set). The number of lanes, hence the `vl` of the intrinsics (`MIPP_RVV_N_<TYPE>_D2`), does not change: the native templates are the same in every mode. The templates that change the LMUL (`rvv_ldiv_mask.json`) detect a half-vector by `vl` by comparing `ctx.ext(dt, -2)` with `ctx.ext(dt, 1)`. The prototypes, identical in every mode, are written once per mode without guard. The documented levels are the ones of the last mode of the list (the default mode, `hw`).
3. **Half-vectors on the sub-ISA.** With `"sw_ldiv_type": "sub_isa"`, `gen_c_ldiv()` writes the `_d2` functions as calls to the `sub_isa` functions (AVX `d2` calls SSE). When the ISA has a `<isa>_ldiv_mask.json` (AVX, AVX-512), the functions that change the LMUL between `m1` and `d2` (`lo`, `hi`, `combine`, `wcvt`, `ncvt`) come from the templates of step 4 instead (`gen_c_ldiv_mask(..., only_changing=True)`). RVV, with hardware half-vectors and register groups, also writes these functions from the templates of `rvv_ldiv_mask.json`, between every pair of consecutive hardware LMULs.
4. **Half-vectors by mask.** With `"sw_ldiv_type": "mask"` (SSE, NEON, SVE), `gen_c_ldiv_mask()` (`codegen/ldiv_mask.py`) writes each `_d2` function as a wrapper of the `m1` function on the same register (upper lanes ignored); the wrapper inherits the level of the `m1` function. Functions where the upper lanes are observable (load/store, gather/scatter, reductions, `testz`, `set`, `set_k`) use Jinja+C templates from `generic_ldiv_mask.json`, overridable per ISA in `simd_ext/<isa>/<isa>_ldiv_mask.json` (keys `a|b`, optional `variants`, `datatypes` and `level`). Types and element counts are written with the [mini-DSL](../reference/templating_dsl.md) relative to the LMUL of the function (`d2` for the half-vector functions, `m1` for `lo` / `hi`): `%vd<tp>%`, `%N<tp>%`, `%N<tp|m:tp*2>%` (the elements of the full register), `%s<tp>%`, `%s<tp|c:uint>%`, and `%vd<tr>%` / `%vm<tr>%` for the result, whose LMUL is the one of the returned value for `lo`, `hi` and `combine`. Without `level`, the level of a template of an ISA file is detected with the rules of the level audit (L0: a single intrinsic or no instruction at all; L1: several intrinsics, or intrinsics and MIPP functions; L2: only MIPP functions, `call1`), and a template of the generic file is L2; the sequential ones (load, store, gather, scatter, `set`, `set_k`) are declared L3. An entry may have an `if` key (a C preprocessor condition such as `defined(__SSE4_1__)`): it is then only used when the condition holds, otherwise the generator falls back on the next matching entry (the other entries of the ISA file, then those of `generic_ldiv_mask.json`) down to an entry without `if`, or to the lane-wise wrapper of the `m1` function. `lo`, `hi` and `combine` have such a generic fallback (L3, through a buffer), so an ISA can restrict its native implementation with `if` without losing the function.
5. **LMUL 1 aliases.** `gen_c_lmul()` with `lmul1=True` first writes the LMUL 1 of `wcvt` and `combine`, which build a software LMUL 2 register from an LMUL 1 one. The generic `wcvt` (`m1` → `m2`) converts each half of the argument (`lo` / `hi`, then the `d2` → `m1` conversion), and the generic `ncvt` (`m2` → `m1`) joins the conversions of the two registers with `combine`. An ISA can write these two bodies itself in `simd_ext/<isa>/<isa>_sw_lmul.json` ([Software LMUL Templates](../reference/registries/sw_lmul.md)): `gen_c_sw_lmul()` (`codegen/sw_lmul.py`) writes them first, with the template engine of the half-vectors, and `lmul_orchestrator.py` skips the generic body (SVE: `svunpklo` / `svunpkhi` instead of `svext` + `svunpklo`, a single `svuzp1` for `ncvt`). Without an entry, the generic bodies are written. The documented level of the function stays the one of its `m1` ↔ `d2` template. Then `gen_c_lmul1_aliases()` writes the functions without suffix, once every `_m1` function is known. For the functions that change the LMUL (`lo`, `hi`, `combine`, `wcvt`, `ncvt`, ...), several generators write the `_m1` functions (the half-vector templates, the software LMUL, the scalar templates): each declares what it writes with `record_lmul1_definition()`, and the aliases are written from this registry.
6. **Software LMUL.** For each positive value of `sw_lmul`, `gen_c_lmul()` (`codegen/lmul_orchestrator.py`) writes wrappers instead of resolving candidates:
    - `_m2`, `_m4`, `_m8` call the function of half the LMUL on each half of the register group;
    - the horizontal functions (`"horizontal": true` in the registry) use the templates of `generic_emu_templates_lmulh.json` instead, and get a panic stub when there is none;
    - so do the functions that move lanes across the register (`"lane_crossing": true`: `reverse`, `slide`, `ziplo`...), whose operation on two halves would be wrong: their template combines the `m1` functions on the registers of the group (a Jinja macro `piece(v, j)` gives the path `v.lo.hi...` of the register j, and the calls are written at `m:tp/{{ lmul }}`, the LMUL 1: the functions of LMUL > 1 have no prototype in the headers of the other functions), or calls functions of the same LMUL that are not lane-crossing. A lane-crossing function without such a template is a generation error. Their half-vectors by mask (step 4) are not the wrapper of the `m1` function either: without a template, the unmasked `d2` function copies its registers into the arrays of the scalar ISA and calls its `d2` function (Level 3, `_lane_crossing_body`), and the masked ones are the unmasked one followed by `select`.
7. **Dependencies and glue.** The `IncludeManager` adds the `#include` lines that each header needs and writes `simd_ext/<isa>/c/mipp_<isa>.h` ([Header Layout](header_layout.md)).

!!! note "LMUL `0` and `1`"
    Inside an ISA (`isa_name=True`) there is no level without suffix: `lmul_suffix()` of `name_builder.py` writes LMUL `0` (no LMUL) as `_m1`, for the types and for the functions (`vd_avx_float32_m1_t`, `mipp_avx_add_float32_m1`). These are the definitions. The names without suffix (`vd_avx_float32_t`, `mipp_avx_add_float32`) are their aliases: the types are `typedef`s written with the structures, and the functions are written by step 5 (`build_func_name_short(..., alias=True)`; in the C layer, `_ci_m1_level()` writes the `_m1` dispatchers and then the aliases). In the public C layer (`isa_name=False`), LMUL `0` stays the name without suffix.

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

### 4.1. Resolution Passes

Each key has a **remaining condition**, initially *true*: the cases for which no implementation is chosen yet. The resolver repeats the following pass until nothing changes:

1. For each key whose remaining condition is not *false*, try the candidates in order, skipping those above the current maximum level and those whose `simd_size` does not match the register size of this LMUL. An entry with `simd_size` is never used on the ISAs whose `size` is not a fixed number (SVE, RVV, scalar).
2. The **target condition** of the candidate is its `if` intersected with the remaining condition. An empty intersection rejects the candidate.
3. The **dependencies** of the candidate are the MIPP functions called by its template (the `%function%` markers of the [templating DSL](../reference/templating_dsl.md)). Each dependency must already have an implementation whose condition is compatible with the target condition. The target condition is then restricted to the cases where the dependencies exist.
4. If the candidate is accepted, it is recorded with its target condition, and the remaining condition of the key becomes `remaining && !target`. The pass then goes on with the next key: it accepts at most one candidate per key.

A candidate is **deferred** while one of its dependencies can still gain branches at the current maximum level, in the cases of its target condition (`dep_pending()`): deciding its condition now would restrict it to the branches of the dependency resolved so far. The lower candidates of the key are not tried in this pass either. When a pass changes nothing and some candidates were deferred (a dependency cycle), one more pass runs without deferral (`allow_pending`): the deferred candidates are then resolved with the branches available.

The maximum level starts at <span class="mipp-isa-badge lvl-2">L2</span>. When a pass changes nothing (after the pass without deferral, if any), it is raised to <span class="mipp-isa-badge lvl-3">L3</span>, then to the stubs. This order matters: every vector implementation of every function is found before any scalar fallback is accepted, so that an <span class="mipp-isa-badge lvl-2">L2</span> sequence can rely on a native function that is resolved later in the same pass.

### 4.2. Preprocessor Conditions

The conditions are C preprocessor expressions. `cond_utils.py` intersects, negates and simplifies them, and decides whether two conditions are mutually exclusive, knowing that the `define` of the ISA is true. This is how an AArch64-only native entry ends up as two branches:

```c
#if defined(__aarch64__)
static inline ... mipp_neon_<function>_float64(...) { /* Level 0 */ }
#endif
#if !defined(__aarch64__)
static inline ... mipp_neon_<function>_float64(...) { /* Level 3 */ }
#endif
```

### 4.3. Dependencies of the Scalar Fallback

On ISAs with hardware masks, the <span class="mipp-isa-badge lvl-3">L3</span> fallback converts the masks with `tovd` and `tovm` (`hw_mask_requires_tovd`), and extracts them with `store` (`hw_mask_extract_via_store`); with bitfield masks (`hw_mask_is_bitfield`, AVX-512) it copies the bits directly. These functions are dependencies of the fallback. On scalable layouts, the half-vector fallback is also guarded by the minimum vector length (`layout.vlen_guard_template`). With `scalar_fallback_attributes` (RVV), the fallbacks get attributes against compiler bugs, see [GCC Bugs in the Scalar Fallback](#54-gcc-bugs-in-the-scalar-fallback).

### 4.4. Effective Level

After the resolution, the level of each chosen candidate becomes the highest level among itself and its dependencies (for a dependency with several branches, the best one counts). An <span class="mipp-isa-badge lvl-2">L2</span> sequence that calls an <span class="mipp-isa-badge lvl-3">L3</span> function is reported as <span class="mipp-isa-badge lvl-3">L3</span> in the generated comment, in the summary table and in the documentation.

The generic body of a scalar form (`derived_form`, see `forms.py`) then takes the level of its base function for the same datatype and mask variant: the broadcast of the scalar (`set1`) is free.

---

## 5. Emission

`resolve_and_emit_missing_functions()` writes the resolved functions of one LMUL. For each function, it first writes the `static` prototypes of all its variants, so that the bodies can call each other in any order, then one body per chosen candidate, under `#if <target condition>` when the condition is not *true*.

### 5.1. Bodies per Candidate Type


- **Implementation entries** (`native_or_emu`, `generic_emu`). The template is rendered with Jinja2 (variables `isa`, `instr_name`, `dt_par`, `dt_ret`, `isa_dt_par`, `isa_dt_ret`, `cstdint_ret`, `func_name`, `lmul`, `mask_kind`), then the DSL markers are replaced by C names and calls (`parse_placeholders()` in `tools.py`). `emit_function_body()` (`codegen/emit_helpers.py`) writes the prototype, a `// Level N (...)` comment and the body.
- **Scalar fallback** (`auto_scalar`). `_gen_c_auto_scalar_fallback_one()` copies each register argument into a scalar register of the same size, calls the `mipp_scalar_*` function and copies the result back (`memcpy`). The arguments go through a union (`union { <register> v; <scalar register> s; }`, see `_register_to_scalar()`), not through a `memcpy` from the parameter: once a fallback is inlined in a function taking a group of registers by value (LMUL > 1), the SRA passes of GCC miscompile that `memcpy` (internal compiler error in `classify_argument` with GCC 12 and 13 on x86, wrong lanes with GCC 14 on RISC-V). On RVV the union is not enough, and the fallbacks compiled by GCC are neither inlined nor vectorized ([5.4](#54-gcc-bugs-in-the-scalar-fallback)).
- **Stub.** The body is `MIPP_PANIC_STUB("MIPP panic: '<function>' is unimplemented.");`. In C++ the macro throws `mipp::stub_exception`, which the generated tests catch and report as a warning; in C it prints the message and exits. When a datatype is only available under a condition (e.g. NEON `float64` on AArch64), the `#else` branch of a lane-wise half-vector function is not a stub: it is an L3 body that calls the LMUL 1 function, copying the registers with `memcpy` (on ARMv7 the d2 types are arrays). The functions that change the LMUL or the datatype (`combine`, `gather`, conversions…) still get a stub there.

### 5.2. Example

An emitted <span class="mipp-isa-badge lvl-0">L0</span> function (`avx/c/functions/arithmetic/u/m1/add.h`, fine granularity):

```c
static inline vd_avx_float32_m1_t mipp_avx_add_float32_m1(const vd_avx_float32_m1_t vd0, const vd_avx_float32_m1_t vd1) {
	// Level 0 (Native Hardware)
	vd_avx_float32_m1_t res;
	res.vd = _mm256_add_ps(vd0.vd, vd1.vd);
	return res;
}
```

and, in the `LMUL = 1 Aliases` section of the same header, its alias without suffix (step 5 of [§2](#2-one-isa-layer)), which has no `// Level` comment:

```c
static inline vd_avx_float32_m1_t mipp_avx_add_float32(const vd_avx_float32_m1_t vd0, const vd_avx_float32_m1_t vd1) {
	return mipp_avx_add_float32_m1(vd0, vd1);
}
```


### 5.3. Immediate Versions

Some instructions only take a constant encoded in them (an immediate: `palignr`, `pshufd`, `ext`, `dup` element, `shl` immediate...), and a `static inline` function cannot pass its parameter to them: clang checks the immediate before inlining. The functions whose integer argument is often a constant are marked in `registry_interfaces.json` with the range of this argument, `"imm": "le_n"` (`slide`), `"lt_n"` (`rotate`, `bcast`, `get`), `"le_nb"` / `"lt_nb"` (the `_b128` variants), `"lt_bits"` (`lshift_vs`, `rshift_vs`). An ISA writes the bodies for the constant values in `simd_ext/<isa>/<isa>_imm_templates.json` and `<isa>_imm_implems.json`, in the format of the emulation files (`datatypes`, `if`, `template`, `instr_name`). A template is rendered for each value of the range, with the variables of the other templates plus `imm` (the value), `lanes` and `block` (the lanes of the register and of a block of 128 bits): one template describes all the cases, with Jinja conditions on `imm` when the instructions depend on the value. A value that renders to nothing has no case.

`codegen/imm.py` writes the cases at the beginning of the unmasked LMUL 1 function, before its dynamic body (chosen by the usual resolution), under `defined(__OPTIMIZE__)` and the `if` of the entry (several entries: `#if` / `#elif`):

```c
#if defined(__OPTIMIZE__) && (defined(__SSSE3__))
	if (__builtin_constant_p(s0)) { // immediate when s0 is a constant: palignr
		switch (s0) {
		case 1: { vd_sse_float32_m1_t res; res.vd = ..._mm_alignr_epi8(..., 4)...; return res; }
		...
		default: break;
		}
	}
#endif
```

Inlined with a constant, `__builtin_constant_p` is true and the switch is resolved at compile time; with a variable, the dynamic body runs.

The switch weighs in the size the inliner estimates even when the argument is a variable: a function with a dispatch, and the LMUL > 1 or masked functions that call it, are less often inlined. A function whose dynamic body the compiler already turns into the immediate instruction gets no bodies: `get` keeps its `"imm"` range (for its C++ template) but no ISA writes a case, since `storeu` then `t[s0]` with a constant `s0` already compiles to an extraction (`pextrd`, `vextracti128`, `valignq`, `umov`), with GCC 12 / 13 and Clang 18. With a dispatch, the larger `get` was not inlined any more in big translation units, and passing the AVX-512 mask groups by value to `get_k` revealed a GCC 13 bug (wrong lanes in `cmplt` on a test of 16 files compiled together). The immediate bodies use intrinsics and the types of the DSL only (a call to a MIPP function is an error: the include resolution would not see it). The masked variants call the unmasked function; the LMUL > 1 template of `slide` (`generic_emu_templates_lmulh.json`) has its own constant path, which slides the registers of the groups with the LMUL 1 function.

The C++ APIs get a template per concrete overload, `template <int S> vd<float32_t,1,SSE> slide(vd0, vd1)`, with a `static_assert` on the range, which calls the C function with the constant (`_emit_imm_template()` of `cpp_generator.py`), and its `Vd` / `Vm` version (`obj_generator.py`).

### 5.4. GCC Bugs in the Scalar Fallback

The scalar fallback reinterprets registers: it copies the registers of the ISA into registers of the scalar ISA (C arrays), calls the scalar function and copies the result back. Once the fallback is inlined, these copies have revealed bugs of GCC in the passes that split the aggregates into scalars (SRA) and in the vectorizer:

| Compiler | Target | Symptom | Workaround in the generator |
| :--- | :--- | :--- | :--- |
| GCC 12, 13 | x86 | internal compiler error in `classify_argument`, when a fallback is inlined in a function taking a group of registers (LMUL > 1) by value | copy of the arguments through a union instead of a `memcpy` from the parameter (`_register_to_scalar()`) |
| GCC 14.2 | RISC-V (RVV) | wrong lanes, without any error or warning: zeros, or bytes of the stack, instead of the lanes of the argument | with GCC, fallbacks neither inlined nor vectorized (`MIPP_RVV_FALLBACK_ATTRIBUTES`, ISA key `scalar_fallback_attributes`) |
| GCC 14.2 | RISC-V (RVV) | internal compiler error in the register allocation (`maximum number of generated reload insns per insn achieved`) on a fallback compiled out of line, when the vectorizer turns its scalar loop into a widening reduction of a copied register | the same: no vectorization of the fallbacks |

**Where the RVV bug strikes.** In the default mode `MIPP_RVV_LDIV_HW`, the 64-bit half-vectors are C arrays, since RVV has no fractional register of 64-bit elements (`vfloat64mf2_t` does not exist): all the functions on these types are scalar fallbacks, and they are the most exposed. The bug has been met twice:

- `broadcast_lane_b128` on 64-bit lanes, with the constant lane 0: bytes of the stack (`0x30303030`) in some lanes. This function now has a generic body (`permute`), without fallback.
- `slideup` on the `float64`, `int64` and `uint64` half-vectors: zeros instead of the slid lanes, for every seed.

**It depends on the context, not on the function.** The generated code of `slideup` was the same before and after the renaming of the API (`slide_up` → `slideup`); only the grouping of the test files changed: the unit tests are compiled in unity batches of 16 files, in alphabetical order, and `slideup.cpp` moved to another batch. In the failing batch, the test function is entirely inlined in the Catch2 test case, and the copies of the fallback are miscompiled. The same test compiled alone passes, every pair of this test with one of the 15 other files of the batch passes, and removing any single file of the batch does not hide the bug: the decisions of the inliner depend on the size of the translation unit. The bug disappears with any of `-fno-tree-sra`, `-fno-ipa-sra`, `-fno-strict-aliasing`, `-fno-tree-vectorize` or `-O2`, which is not a fix for the users. The union copy (with or without its `memset`) does not hide it; a `memcpy` to a scalar variable hides it in this context, but it is the copy that the first bug forced to replace.

**The workaround.** The fallbacks of RVV are written `static MIPP_RVV_FALLBACK_ATTRIBUTES inline`, the macro being defined in `rvv/c/common.h` (from `header_template`) as `__attribute__((noinline, optimize("no-tree-vectorize")))` with GCC, and empty with the other compilers:

- `noinline`: kept out of line, the copies are always compiled in the same context, the body of the fallback alone, whatever the code of the caller. This alone fixes `slideup`, but compiles every fallback alone, and GCC 14 then stops with the internal error above on some of them: `hadds` of the `int8` half-vectors, in the three half-vector modes, with the union (`MIPP_RVV_LDIV_VL`) or with a `memcpy` (`MIPP_RVV_LDIV_HW`, `MIPP_RVV_LDIV_HYBRID`), for a program that only calls this function.
- `optimize("no-tree-vectorize")`: the scalar loop of the fallback is not vectorized, which removes the internal error in the three modes (with the union or a `memcpy`) and keeps `slideup` right. Vectorizing the loop of a scalar fallback brings little anyway.

The cost is small: a fallback is a sequential loop through memory, and a call adds little to it. The prototypes written at the top of the RVV headers have no `inline` (`declaration_proto()`), since GCC warns when a definition with `noinline` follows an inline declaration (more than 100,000 warnings in the build of the tests); the definitions keep `inline`, so that an unused function does not cause a warning. **Clang** does not have these bugs: the whole test suite compiled with Clang 20.1.8 for RVV (`-march=rv64gcv_zvl256b`), with the fallbacks inlined (union, no attribute), passes in the modes `MIPP_RVV_LDIV_HW` and `MIPP_RVV_LDIV_VL`, including the unity batch where GCC returns wrong lanes for `slideup` and the `hadds` on which GCC fails; the macro is therefore empty with Clang (which does not know `optimize` anyway). The other ISAs keep their fallbacks inline and vectorized, since these bugs have not been seen there; the key is per ISA (`<isa>_isa.json`), so it can be set for another one. On RVV, a program that wants native 64-bit half-vectors uses `MIPP_RVV_LDIV_VL` or `MIPP_RVV_LDIV_HYBRID` ([Vector Types and LMUL](../../user/vector_types_and_lmul.md)).

**If it happens again.** The signs: a test fails in the full build for every seed and passes when compiled alone, and the function is a Level 3 (or calls one). To reproduce, compile the unity file of the failing test alone (`CMakeFiles/tests_exe.dir/Unity/unity_<n>_cxx.cxx` in the build directory) with `tests/src/main.cpp`, then compare with `-fno-tree-sra` and `-fno-tree-vectorize`: if one of these flags hides the failure, it is this family of bugs.

---

## 6. Summary Table

At the end of a run, `print_summary_table()` reads the generated `simd_ext/<isa>/c/functions/` headers and counts, per ISA and per level, the functions that carry a `// Level N` comment. The functions are split into three columns: `Std` (unmasked, LMUL 1), `Msk` (mask variants of LMUL 1) and `LM/D` (LMUL > 1 and half-vectors, masked or not). The `Stubs` column counts the `MIPP panic` lines.

!!! warning "The `LM/D` column is incomplete"
    The software LMUL wrappers ([§2](#2-one-isa-layer), step 6), the `sub_isa` half-vectors (step 3) and the LMUL 1 aliases (step 5) have no `// Level` comment, so they are not counted. The `LM/D` column counts the hardware LMUL functions (RVV), the half-vectors by mask (step 4, which carry the level of the LMUL 1 function or of their template) and the horizontal LMUL wrappers (`// Level 2`). Its value therefore depends on the `sw_ldiv_type` of the ISA: AVX and AVX-512 (`sub_isa`) count fewer functions than SSE, NEON and SVE (`mask`).

---

## 7. Module Map

| File (in `generator/helpers_headers/`) | Role |
| :--- | :--- |
| `registry.py` | Loads and validates the registries; module-level data shared by the generators. |
| `forms.py` | Scalar forms (`sub_vs`, `sub_sv`, `fmadd_vsv`...): derived prototypes, interfaces, categories, scalar references, documentation and generic bodies (`sub(vd0, set1(s0))`, marked `derived_form`), and the C aliases `mipp_<f>_vv_<...>`. Also used by the test and documentation generators. |
| `input_validation.py` | Validation checks and header audits. |
| `tools.py` | ISA loading, datatype aliases, DSL parsing (`parse_placeholders()`, `get_requirements()`). |
| `datatypes.py`, `name_builder.py` | Datatypes; function names, prototypes and call arguments. |
| `cond_utils.py` | Parsing, simplification and algebra of preprocessor conditions. |
| `c_generator.py` | One ISA layer: common header, candidate registration, LMUL loops ([§2](#2-one-isa-layer)). |
| `codegen/candidate_resolver.py` | Candidate resolution, effective levels, emission, scalar fallback and stubs ([§4](#4-resolution), [§5](#5-emission)). |
| `codegen/imm.py` | Immediate versions ([§5.3](#53-immediate-versions)): the functions marked `"imm"` in the registry get, in their unmasked LMUL 1 version, a dispatch on the constant values of their integer argument (`__builtin_constant_p`, then a `switch` of the bodies of `<isa>_imm_implems.json` rendered for each value), and C++ templates `f<S>(...)` (`cpp_generator.py`, `obj_generator.py`). |
| `luts.py` | Constant tables of the implementation templates computed at generation time (`compress_lut`: the shuffle of `compress` for each value of the mask; `iota`, `iota_mod`, `iota_block`), available in the implementation and immediate templates as Jinja globals (`TEMPLATE_GLOBALS`, `render_template()`), not in the half-vector templates ([Templating DSL](../reference/templating_dsl.md#62-constant-tables)). |
| `codegen/lmul_orchestrator.py` | Software LMUL and `sub_isa` half-vector wrappers, horizontal LMUL wrappers. |
| `codegen/ldiv_modes.py` | Half-vector representations selected at compile time (`ldiv_modes`, RVV): the descriptor of each mode, its macro. |
| `codegen/sw_lmul.py` | `wcvt` (`m1` → `m2`) and `ncvt` (`m2` → `m1`) of a software LMUL written by the ISA (`<isa>_sw_lmul.json`), rendered with the engine of `ldiv_mask.py`. |
| `codegen/ldiv_mask.py` | Half-vectors by mask (`"sw_ldiv_type": "mask"`), and the functions that change the LMUL between `m1` and `d2` (`lo`, `hi`, `combine`, `wcvt`, `ncvt`): templates of `generic_ldiv_mask.json` and `<isa>_ldiv_mask.json`, level detection ([§2](#2-one-isa-layer), step 4). |
| `codegen/emit_helpers.py` | Function bodies, `// Level` comments, panic stubs, half-vector structures. |
| `codegen/implem_tracker.py` | Implementation status per function, datatype and mask variant (read by the dependency and include resolution). |
| `include_gen.py` | `IncludeManager`: files, includes and umbrella headers ([Header Layout](header_layout.md)). |
| `ci_generator.py`, `cpp_generator.py`, `obj_generator.py` | C dispatch headers, C++ Functional API, C++ Object API. |
| `utils_generator.py` | Utilities written by hand in `templates/` (aligned allocation, printing, `reduce`): `include/mipp/{c,cpp,obj}/utils.h(pp)`, one `dump` function per datatype and LMUL in C; the compile-time permutations of C++17 (`permute<P>`, `permute2<P>`): `include/mipp/{cpp,obj}/patterns.hpp`; the transpositions (`transpose`, `transpose_b128`): `include/mipp/c/transpose.h`, `include/mipp/{cpp,obj}/transpose.hpp`. |
