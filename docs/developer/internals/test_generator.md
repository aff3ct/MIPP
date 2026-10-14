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

---

## 2. Generated Files

| API | Files (in `tests/src/`) | Content |
| :--- | :--- | :--- |
| C | `c/<category>/<m1\|m2\|m4\|m8\|d2>/<unmasked\|mask\|maskz\|masks>/<function>.cpp` | One file per function, LMUL and mask variant; one test function per datatype. |
| C++ Functional | `cpp/<category>/<function>.cpp` | One file per function: one template test (`<VARIANT, T, LMUL>`), instantiated in nested `SECTION`s for each mask variant, datatype and LMUL. |
| C++ Object | `obj/<category>/<function>.cpp` | Same structure, with `mipp::Rvd` and `mipp::Rvm`. |

`--lmul`, `--ldiv` and `--mask-kind` restrict the generated combinations; a function is only tested for the mask variants of its `mask_support`. `tests/CMakeLists.txt` compiles every `.cpp` found under `tests/src/`, with the helpers of `tests/src/utils/` (random generators, overflow checks, `abs_diff`).

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

`tolerance` is `exact`, `max_abs_diff` (absolute value) or `relative_percent` (fraction of `|ref|`), possibly refined with `by_datatype`, `by_lmul` (a ternary on `LMUL` in C++) and `by_define` (preprocessor branches).

**Other properties.** `nan_inf_skip` ignores the lanes where the difference is NaN or infinite; `skip_condition` ignores the lanes that match a condition on the reference value (for example the halfway cases of `round`); `overflow_check` ignores the lanes where an addition, subtraction or multiplication overflows; `disabled` comments the test out, with `disabled_reason`; `support_obj: false` skips the Object API.

!!! warning "Known gaps"
    - The tolerance type `hybrid` (used by `cosh`, `sin`, `sinh`) is accepted by the schema but not implemented: these tests fall back to an absolute tolerance of `0.001`.
    - `overflow_check` with `add`, `sub` or `mul` is only applied in the C tests; the C++ tests only handle the `accumulate_*` values (reductions).
    - The `define` field of a domain rule is accepted by the schema but ignored.

---

## 4. Code Templates

The C++ code of the tests is not written in Python: it comes from `helpers_tests/tests_templates.json` ([Test Templates](../reference/registries/tests_templates.md)), which holds the file headers, the bodies of the test functions, the `TEST_CASE` and `SECTION` skeletons and the assertions. The templates contain `{{placeholder}}` variables filled by `tests_builder.py`, and `%token<datatype,lmul>(argument)%` markers that depend on the API (`%load<...>(p)%`, `%reg_type<...>%`, `%set_k<...>(p)%`, `%N<...>%`, ...).

These markers are resolved by the **dialect adapters** (`dialect_adapters.py`): for a load with LMUL 2, `CDialectAdapter` writes `mipp_load_float32_m2(p)`, `CppDialectAdapter` writes `mipp::load<T, 2>(p)`, `CppObjDialectAdapter` writes `mipp::Rvd<T, 2>(p)`. The adapters only format expressions; the structure of the test is the same for the three APIs.

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
