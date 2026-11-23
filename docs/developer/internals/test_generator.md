# Test Generator

This page describes how `gen_mipp_tests.py` turns the function registry and the test specifications into Catch2 sources. The options of the script are in the [Command-Line Reference](../reference/cli.md#gen_mipp_tests), every field of `tests_specs.json` in [Test Specifications](../reference/registries/tests_specs.md), and building and running the tests in [Setup](../setup.md#4-build-and-run-the-unit-tests).

---

## 1. Principle

Every generated test compares the API under test with the **scalar reference** on the same random inputs:

1. fill the input arrays with random values, in the domain given by `tests_specs.json`;
2. load them into the registers of the selected ISA, and into the registers of the scalar target (`mipp_scalar_*` in C, `mipp::ISA::SCALAR` in C++);
3. call the function on both;
4. compare the results lane by lane: exactly, or within a tolerance for the floating-point functions.

The scalar target is generated from `registry_scalar_implems.json`, like the <span class="mipp-isa-badge lvl-3">L3</span> fallback. The test generator does not need the candidate resolution: it only knows the registry, so the same sources test every ISA, and the compiler flags choose the ISA under test.

A function that reaches a stub on the ISA under test throws `mipp::stub_exception`: the test catches it and reports a Catch2 warning instead of a failure.

The input and output arrays are aligned on 64 bytes, which suits `load` and `store` on every ISA. For `loadu` and `storeu` (`_UNALIGNED_PTR_FUNCS` in `tests_builder.py`), the call under test gets a pointer one element past an aligned buffer, never aligned on the register size; the scalar reference keeps the aligned arrays.

---

## 2. Generated Files

| API | Files (in `tests/src/`) | Content |
| :--- | :--- | :--- |
| C | `c/<category>/<m1\|m2\|m4\|m8\|d2>/<unmasked\|mask\|maskz\|masks>/<function>.cpp` | One file per function, LMUL and mask variant; one test function per datatype. |
| C++ Functional | `cpp/<category>/<function>.cpp` | One file per function: one template test (`<VARIANT, T, LMUL>`), instantiated in nested `SECTION`s for each mask variant, datatype and LMUL. |
| C++ Object | `obj/<category>/<function>.cpp` | Same structure, with `mipp::Vd` and `mipp::Vm`. |

`--lmul`, `--ldiv` and `--mask-kind` restrict the generated combinations; a function is only tested for the mask variants of its `variants`. `tests/CMakeLists.txt` compiles every `.cpp` found under `tests/src/`, with the helpers of `tests/src/utils/` (random generators, overflow checks, `abs_diff`).

---

## 3. Test Specifications

`helpers_tests/tests_specs.json` has a `default` entry and one entry per function in `functions`. A property missing in a function entry takes its value in `default`. The keys `unmasked`, `mask`, `maskz` and `masks` override the input properties (`domain`, `input_domain`, `domain_src`, `distribution`, `mask_pattern`) for one mask variant.

**Domains** (`domain_resolver.py`). The range of the random inputs is looked up in the section of the mask variant, then at the root of the entry, then in the `unmasked` section. Inside a domain, a matching rule of `rules` wins over `by_datatype`, which wins over `by_lmul`, which wins over `default`. A `by_define` entry becomes `#if defined(<macro>)` branches in the generated code, for the ranges that depend on the ISA (for example `MIPP_AVX2`). `input_domain` gives one domain per input, `domain_src` the domain of the source register of the Source-Masked variant.

**Comparison** (`tests_builder.py`). `comparison` selects the assertion:

| `comparison` | Assertion |
| :--- | :--- |
| `exact` | `REQUIRE(res == ref)` on each lane. |
| `tolerance` | On floating-point types, `REQUIRE(abs_diff(res, ref) <= tol)`, with `tol` computed from `tolerance`; integers stay exact. |
| `bitwise` | Bit-pattern equality (NaN-safe), possibly per datatype. |
| `logical` | Truth-value equality, used for masks. |

`tolerance` is `exact`, `max_abs_diff` (absolute value), `relative_percent` (fraction of `|ref|`) or `hybrid` (`abs_value + rel_value * |ref|`), possibly refined with `by_datatype`, `by_lmul` (a ternary on `LMUL` in C++) and `by_define` (preprocessor branches).

**Choosing a tolerance.** The inputs are random, with a new seed at each run (`--rng-seed` replays one): a tolerance taken from a few runs fails from time to time, on another seed. A tolerance is therefore derived from a bound of the error (the rounding of the operations, or the worst case measured over every input of the domain when it can be enumerated, as for the `float32` inputs), with a margin, never from the largest error of a few seeds. The tolerances changed after a measure are listed below, with their reason:

| Function | Datatype | Before | After | Reason |
| :--- | :--- | :--- | :--- | :--- |
| `fmadd`, `fmsub`, `fnmadd`, `fnmsub` (and their scalar forms) | `float32` | `relative_percent` 1e-3 | `hybrid` 6e-8 + 1e-3 &times; \|ref\| | A fused multiply-add and the scalar reference, when the compiler does not fuse it, differ by the rounding of `a * b`, at most half an ulp of `a * b`: $2^{-25} \approx 3 \cdot 10^{-8}$ for inputs in $[-1, 1]$. When `a * b` and `c` cancel, `|ref|` is tiny and a purely relative tolerance is below this difference: 28 seeds out of 300 failed on AVX-512 (largest difference $3 \cdot 10^{-8}$). The absolute part is $2^{-24}$, twice the bound. November 2026. |
| same | `float64` | `relative_percent` 1e-4 | `hybrid` 1.2e-16 + 1e-4 &times; \|ref\| | Same bound in double precision: $2^{-54}$, absolute part $\approx 2^{-53}$. No failure seen yet, a cancellation being much rarer at this relative tolerance. November 2026. |
| `acosh` | `float32` | `max_abs_diff` 2e-6 | `max_abs_diff` 3e-6 | `acosh` is ill-conditioned near 1 (derivative $1/\sqrt{x^2-1}$). Exhaustive comparison of every `float32` of the domain $[1, 10]$ with the scalar reference: largest difference $2.403 \cdot 10^{-6}$ at $x = 1.00017$, the same on AVX2, AVX-512, NEON, SVE and RVV, so 2e-6 failed on about 1 seed out of 150. November 2026. |


**Other properties.** `nan_inf_skip` ignores the lanes where the difference is NaN or infinite; `skip_condition` ignores the lanes that match a condition on the reference value (for example the halfway cases of `round`); `overflow_check` ignores the lanes where an addition, subtraction or multiplication overflows; `disabled` comments the test out, with `disabled_reason`; `support_obj: false` skips the Object API.

**Functions that change the LMUL or the type.** `wcvt`, `ncvt`, `lo`, `hi` and `combine` (and their `_k`) return a register of another LMUL than their arguments, and the conversions also change the datatype. Nothing is written per function: the result LMUL comes from `ret.lmul` in `registry_protos.json`, and the source/destination pairs from the `datatypes` of the function. The result is read with the lane count and type of its own LMUL (`size_out`, `LMUL_OUT` in C++), and compared with the scalar ISA like every other function. A test is not generated for an LMUL where the function does not exist (no `wcvt` from `m8`, no `lo` from `d2`). Since an ISA may not provide a function for an LMUL, each test (C) or section (C++ and Object) is wrapped in `#if defined(MIPP_<ISA>) || ...`, built from the same rule as the headers (`isa_provides_lmul`). In C++, `test_helpers::<function><T_dst>` forwards to the overload of the destination type (`mipp::wcvt_int64`, ...), because the destination is a template parameter of the test.

**Indexed functions.** `gather` and `scatter` take a pointer and a register of unsigned indices, which the generic builder cannot generate. They are generated for pairs `"data,index"`, the index having its own LMUL when its width differs from the one of the data (`mipp::details::idx_lmul<T, IDX>(LMUL)` in C++); a pair is only tested for the LMULs where this LMUL exists, and the mask has the type of the data. `helpers_tests/indexed_tests.py` writes their tests, with the same principle as the others: the result of the ISA under test is compared with the scalar reference (`gather`: the stored register; `scatter`: the memory written by both targets), for every datatype, LMUL, `d2` and mask variant, in the three APIs. The indices address a table larger than a register: $2^8$ elements for 8-bit indices, $2^{16}$ for 16-bit indices and $2^{17}$ for wider ones (and at least N), so that the whole range of the 8 and 16-bit indices is covered, including the byte offsets that overflow the index width. The indices of a `gather` are random values of the table; the ones of a `scatter` are N distinct positions of the table, so that the result does not depend on the order of the writes, and the whole table is compared. They have no entry in `tests_specs.json`.

!!! warning "Known gaps"
    - `overflow_check` with `add`, `sub` or `mul` is only applied in the C tests; the C++ tests only handle the `accumulate_*` values (reductions).
    - The `define` field of a domain rule is accepted by the schema but ignored.

---

## 4. Code Templates

The C++ code of the tests is not written in Python: it comes from `helpers_tests/tests_templates.json` ([Test Templates](../reference/registries/tests_templates.md)), which holds the file headers, the bodies of the test functions, the `TEST_CASE` and `SECTION` skeletons and the assertions. The templates contain `{{placeholder}}` variables filled by `tests_builder.py`, and `%token<datatype,lmul>(argument)%` markers that depend on the API (`%load<...>(p)%`, `%reg_type<...>%`, `%set_k<...>(p)%`, `%N<...>%`, ...).

These markers are resolved by the **dialect adapters** (`dialect_adapters.py`): for a load with LMUL 2, `CDialectAdapter` writes `mipp_load_float32_m2(p)`, `CppDialectAdapter` writes `mipp::load<T, 2>(p)`, `CppObjDialectAdapter` writes `mipp::Vd<T, 2>(p)`. The adapters only format expressions; the structure of the test is the same for the three APIs.

---

## 5. Module Map

| File (in `generator/`) | Role |
| :--- | :--- |
| `gen_mipp_tests.py` | Command line; loops over the APIs, LMUL values and mask variants. |
| `helpers_tests/tests_builder.py` | `TestsBuilderEngine`: loads and validates the JSON files, renders the tests (`TestsBuilderEngineC`, `TestsBuilderEngineCpp`, `TestsBuilderEngineObj`), tolerances and assertions, test audits. |
| `helpers_tests/domain_resolver.py` | `DomainResolver`: input domains and mask patterns per datatype, LMUL, mask variant and ISA. |
| `helpers_tests/dialect_adapters.py` | Expression syntax of the C, C++ Functional and C++ Object APIs. |
| `helpers_tests/tests_specs.json`, `tests_templates.json` | Test properties and code templates. |
| `helpers_tests/schemas/` | JSON Schemas of the two files above. |
