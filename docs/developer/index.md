# Developer Guide Overview

This guide is for contributors who add functions, implementations or targets to MIPP, or who work on the generators themselves. To use MIPP in an application, read the [User Guide](../user/getting_started.md) instead.

MIPP has no hand-written vector code. The headers in `include/`, the unit tests in `tests/src/` and the reference pages of this site are **generated** from a database of JSON files in `generator/`. Contributing to MIPP means editing that database, then regenerating.

| I want to... | Read |
| :--- | :--- |
| Generate the headers, build and run the tests | [Setup](setup.md) |
| Add a new function (e.g. `absdiff`) | [Add a Function](tutorials/add_function.md) |
| Make an existing function faster on one target | [Add an Implementation](tutorials/add_implementation.md) |
| Support a new instruction set | [Add an ISA](tutorials/add_isa.md) |
| Understand a warning or an error of the generator | [Audits & Validation](reference/audits.md) |
| Look up an option of a generator or a field of a JSON file | [Command-Line](reference/cli.md), [Registries](reference/registries/index.md) |
| Work on the generators themselves | [Internals](internals/code_generation.md) |
| Understand the CI or publish a release | [Continuous Integration](process/ci.md), [Release](process/release.md) |

---

## 1. The Generation Pipeline

![Pipeline of the MIPP generators: the declarative JSON inputs go through blocking validation and warning-only audits; the candidate resolution picks one implementation level per function, datatype, mask variant, LMUL and ISA; gen_mipp_headers.py writes include/, gen_mipp_docs.py writes docs/, and gen_mipp_tests.py writes tests/src/ without the resolution](../assets/images/generator_pipeline.svg){ width="680" }

1. **Inputs.** The core registries declare each function once (prototype, datatypes, masking variants, scalar reference). Each ISA directory describes the registers of one target and maps functions to intrinsics. The test specifications tune the input domains and tolerances of the generated tests.
2. **Checks.** Every file is validated against its JSON Schema, and the cross-references between files are checked. A validation error stops the generator. The audits only print warnings. See [Audits & Validation](reference/audits.md).
3. **Candidate resolution** (`generator/helpers_headers/codegen/`). For each combination of function, datatype, mask variant, LMUL and ISA, the resolver collects the candidate implementations and keeps the first one whose dependencies are available, in the order <span class="mipp-isa-badge lvl-0">L0</span>, <span class="mipp-isa-badge lvl-1">L1</span>, <span class="mipp-isa-badge lvl-2">L2</span>, <span class="mipp-isa-badge lvl-3">L3</span>. The [Implementation Levels](../user/implementation_levels.md) page describes the four levels from the user side, and [Code Generation](internals/code_generation.md) the resolver itself.
4. **Emission.** `gen_mipp_headers.py` writes the three APIs. `gen_mipp_docs.py` runs the same resolution to fill the Function Support and Hardware Support pages and the API Explorer data. `gen_mipp_tests.py` does not need the resolution: each generated test compares the API under test with the scalar reference.

---

## 2. Invariants

These rules hold for the whole code base. The tutorials rely on them.

- **Generated files are never edited.** `include/`, `tests/src/{c,cpp,obj}/`, `docs/funcs_support/`, `docs/isas_support/`, `docs/assets/data/`, `docs/developer/reference/cli.md` and `docs/developer/reference/registries/` are ignored by Git and overwritten at each generation. Fix the JSON input or the generator instead.
- **The scalar reference is the specification.** Every declared function has a scalar implementation for exactly its declared datatypes, otherwise the generator stops. This implementation is both the <span class="mipp-isa-badge lvl-3">L3</span> fallback and the reference of every generated test.
- **Every combination exists on every generated ISA.** If no <span class="mipp-isa-badge lvl-0">L0</span>, <span class="mipp-isa-badge lvl-1">L1</span> or <span class="mipp-isa-badge lvl-2">L2</span> candidate applies, the resolver emits the <span class="mipp-isa-badge lvl-3">L3</span> fallback, which converts the registers to scalar arrays and calls the scalar reference. The only exception today is a set of half-vector (`d2`) functions on RVV, which compile but stop at run time when called (see [Known Limitations](../user/implementation_levels.md#5-known-limitations)).
- **Conditions split, they do not replace.** An entry with an `if` condition is emitted under `#if <condition>`. For the rest of the condition space, the resolver keeps looking for another candidate. For instance, an AArch64-only native entry gives <span class="mipp-isa-badge lvl-0">L0</span> under `#if defined(__aarch64__)` and the <span class="mipp-isa-badge lvl-3">L3</span> fallback under `#if !defined(__aarch64__)`.
- **Levels propagate.** The effective level of an <span class="mipp-isa-badge lvl-1">L1</span> or <span class="mipp-isa-badge lvl-2">L2</span> implementation is the highest level among its dependencies. An <span class="mipp-isa-badge lvl-2">L2</span> sequence that calls an <span class="mipp-isa-badge lvl-3">L3</span> function is reported as <span class="mipp-isa-badge lvl-3">L3</span>. The summary table of `gen_mipp_headers.py` and the API Explorer report effective levels.
- **ISAs are discovered.** Each directory of `generator/simd_ext/` is an ISA. Adding a target does not require any change in the Python code.
- **JSON files are sorted.** The top-level keys of every JSON file are sorted alphabetically (checked by the `json-structure` audit).

---

## 3. Glossary

| Term | Meaning |
| :--- | :--- |
| **Function** | An entry of `registry_interfaces.json`, such as `add`. Its C names follow `mipp_<function>_<type>[_<variant>][_<lmul>]` (`mipp_add_float32_maskz_m2`). |
| **Datatype** | One of the 10 element types: `float64`, `float32`, `int64`, `int32`, `int16`, `int8`, `uint64`, `uint32`, `uint16`, `uint8`. Conversions use **datatype pairs** (`float32,int32`). Aliases such as `all_float` or `all_int` are listed in `DATATYPES_MAP` (`generator/helpers_headers/tools.py`). |
| **Prototype** | An abstract signature of `registry_protos.json`, such as `ret_reg_2args_reg` (two registers in, one register out). |
| **Mask variant** | `unmasked`, `mask` (Merge-Masked, `M`), `maskz` (Zero-Masked, `Z`) or `masks` (Source-Masked, `S`). A function declares the variants it supports with `mask_support`. See [Masking Semantics](../user/masking_semantics.md). |
| **LMUL** | Register multiplier: `1`, `2`, `4`, `8`, and `-2` for half-vectors (`d2`). An ISA lists the LMUL values it emulates in software (`sw_lmul`) or supports in hardware (`hw_lmul`). See [Vector Types & LMUL](../user/vector_types_and_lmul.md). |
| **ISA**, **SIMD extension** | A target backend: one directory of `generator/simd_ext/` (`sse`, `avx`, `avx512`, `neon`, `sve`, `rvv`, and the special `scalar`). |
| **Level** | <span class="mipp-isa-badge lvl-0">L0</span> native, <span class="mipp-isa-badge lvl-1">L1</span> dedicated emulation, <span class="mipp-isa-badge lvl-2">L2</span> generic emulation, <span class="mipp-isa-badge lvl-3">L3</span> scalar fallback. The source of an implementation determines its level: `<isa>_native_*.json` (<span class="mipp-isa-badge lvl-0">L0</span>), `<isa>_emu_*.json` (<span class="mipp-isa-badge lvl-1">L1</span>), `generic_emu_*.json` (<span class="mipp-isa-badge lvl-2">L2</span>), scalar reference (<span class="mipp-isa-badge lvl-3">L3</span>). |
| **Template** | A code snippet (Jinja2 plus the [templating DSL](reference/templating_dsl.md)) stored in a `*_templates.json` file. |
| **Implementation entry** | An element of a `*_implems.json` file: it maps a function and a set of datatypes to a template, with an optional `if` condition. |
| **Candidate** | An implementation entry, or the automatic <span class="mipp-isa-badge lvl-3">L3</span> fallback, considered by the resolver for one function, datatype, mask variant, LMUL and ISA. |
| **Layer** | A unit of regeneration of `gen_mipp_headers.py`: one per ISA, plus `wrappers` (the public C, C++ Functional and C++ Object headers). |
| **Granularity** | Layout of the public headers: `coarse` (one header per function) or `fine` (also one **atom** per variant and LMUL, grouped by **umbrella** headers). See [Headers & Compile Time](../user/headers_and_compile_time.md). |
| **API**, **dialect** | C, C++ Functional and C++ Object. The test generator calls them `c`, `cpp` and `obj`. |

---

## 4. Directory Layout of `generator/`

All the generators are run from this directory (see [Setup](setup.md)).

```text
generator/
├── gen_mipp_headers.py              # Header generator (C, C++ Functional, C++ Object)
├── gen_mipp_tests.py                # Test generator (Catch2 sources in tests/src/)
├── gen_mipp_docs.py                 # Generated pages of the documentation
├── gen_mipp_api_data.py             # API Explorer data (called by gen_mipp_docs.py)
├── requirements.txt                 # Python dependencies (Jinja2, jsonschema, colorama)
│
├── helpers_docs/                    # Developer Guide reference: CLI (argparse) and Registries (schemas)
│
├── helpers_headers/                 # Header generation engine and core registries
│   ├── registry_interfaces.json     # Declaration of every function
│   ├── registry_protos.json         # Abstract prototypes
│   ├── registry_categories.json     # Function categories
│   ├── registry_scalar_implems.json # Scalar reference (Level 3)
│   ├── registry_scalar_isa.json     # Descriptor of the scalar target
│   ├── generic_emu_templates*.json  # Generic emulation templates (Level 2)
│   ├── generic_emu_implems*.json    # Generic emulation entries (Level 2)
│   ├── funcs_docs.json              # Function descriptions and formulas
│   ├── jinja_keywords.json          # Jinja2 keywords (not parsed as DSL placeholders)
│   ├── schemas/                     # JSON Schemas of all the registries and ISA files
│   ├── templates/                   # Static header templates (mipp_info, Object API, ...)
│   ├── codegen/                     # Candidate resolver, LMUL orchestrator, emission helpers
│   ├── registry.py                  # Loads and validates the registries
│   ├── input_validation.py          # Validation checks and header audits
│   ├── tools.py                     # DSL parsing, datatype aliases, ISA loading
│   ├── datatypes.py                 # Datatypes, categories and datatype pairs
│   ├── name_builder.py              # Function names, prototypes and call arguments
│   ├── cond_utils.py                # Preprocessor condition parsing and simplification
│   ├── include_gen.py               # IncludeManager: header layout and dependencies
│   ├── c_generator.py               # Per-ISA C implementation headers
│   ├── ci_generator.py              # C API dispatch headers
│   ├── cpp_generator.py             # C++ Functional API (namespace mipp)
│   └── obj_generator.py             # C++ Object API (Rvd, Rvm) and public per-function headers
│
├── helpers_tests/                   # Test generation engine
│   ├── tests_builder.py             # Test engine and test audits
│   ├── dialect_adapters.py          # C, C++ Functional and C++ Object syntax adapters
│   ├── domain_resolver.py           # Input domains and mask patterns
│   ├── tests_specs.json             # Per-function test properties
│   ├── tests_templates.json         # Test code templates
│   └── schemas/                     # JSON Schemas of the two files above
│
└── simd_ext/                        # One directory per target
    ├── scalar/                      # scalar_gen.py: emits the scalar target from the registries
    ├── sse/                         # SSE to SSE4.2
    ├── avx/                         # AVX, AVX2, FMA
    ├── avx512/                      # AVX-512F, BW, DQ, ...
    ├── neon/                        # Arm NEON (ARMv7, ARMv8-A)
    ├── sve/                         # Arm SVE (work in progress)
    └── rvv/                         # RISC-V Vector 1.0
```

Each ISA directory holds `<isa>_isa.json`, `<isa>_native_templates.json` and `<isa>_native_implems.json`, plus the optional `<isa>_emu_*.json` (<span class="mipp-isa-badge lvl-1">L1</span>) and `<isa>_explorer.json` (API Explorer metadata). See [Add an ISA](tutorials/add_isa.md).
