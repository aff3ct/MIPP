# MIPPv2 Developer & Contributor Guide

This guide is intended for developers who add vector operations, add CPU target backends, or improve the code generation and test infrastructure.

---

## 1. Architectural Philosophy: Declarative Code Generation

MIPPv1 relied on thousands of manually maintained, deeply nested C++ template headers. This approach suffered from template explosion, subtle divergence between architectures, and costly maintenance when scaling to modern architectures like RISC-V Vector (RVV) and ARM SVE.

**MIPPv2 decouples architecture definitions from code generation.** The headers in `include/` are not versioned: they are generated from a declarative JSON database.

```
+-------------------------------------------------------------------------------+
|                           Declarative Data Layer                              |
|  - helpers_headers/registry_*.json  : functions, prototypes, categories,      |
|                                       scalar reference implementations (L3)   |
|  - helpers_headers/generic_emu_*.json: portable emulations (L2)               |
|  - simd_ext/<isa>/<isa>_isa.json    : registers, datatypes, LMUL, macros      |
|  - simd_ext/<isa>/<isa>_native_*.json: hardware intrinsics (L0)               |
|  - simd_ext/<isa>/<isa>_emu_*.json  : ISA-specific emulations (L1)            |
+-------------------------------------------------------------------------------+
                                        |
                                        v
+-------------------------------------------------------------------------------+
|                     Validation (blocking) & Audits (warnings)                 |
|  - JSON Schemas, cross-references, scalar coverage                            |
|  - levels, dead-code, duplicates, json-structure                              |
+-------------------------------------------------------------------------------+
                                        |
                                        v
+-------------------------------------------------------------------------------+
|                    Candidate Resolution (codegen/)                            |
|    Level 0 (Native) -> Level 1 (ISA-specific) -> Level 2 (Generic) -> Level 3 |
+-------------------------------------------------------------------------------+
                                        |
            +---------------------------+---------------------------+
            |                           |                           |
            v                           v                           v
+-----------------------+   +-----------------------+   +-----------------------+
| C/C++ Headers         |   | Test Generator        |   | Doc Generator         |
| (include/)            |   | (tests/src/)          |   | (docs/)               |
+-----------------------+   +-----------------------+   +-----------------------+
```

---

## 2. Directory Layout of `generator/`

```text
generator/
├── gen_mipp_headers.py              # Header generator (C, C++ functional, C++ object APIs)
├── gen_mipp_tests.py                # Test generator (Catch2 sources in tests/src/)
├── gen_mipp_docs.py                 # Function Support / Hardware Support pages
├── gen_mipp_api_data.py             # API Explorer index (called by gen_mipp_docs.py)
├── requirements.txt                 # Python dependencies (Jinja2, jsonschema, colorama)
│
├── helpers_headers/                 # Header generation engine and core registries
│   ├── registry_interfaces.json     # Declaration of every MIPP function
│   ├── registry_protos.json         # Abstract prototypes
│   ├── registry_categories.json     # Function categories
│   ├── registry_scalar_implems.json # Scalar reference implementations (Level 3)
│   ├── registry_scalar_isa.json     # Scalar "ISA" descriptor
│   ├── generic_emu_templates*.json  # Generic emulation templates (Level 2)
│   ├── generic_emu_implems*.json    # Generic emulation mappings (Level 2)
│   ├── funcs_docs.json              # Function descriptions and formulas
│   ├── jinja_keywords.json          # Jinja2 keywords (not to be parsed as DSL placeholders)
│   ├── schemas/                     # JSON Schemas of all the files above and of ISA files
│   ├── templates/                   # Static header templates (mipp_info, object API, ...)
│   ├── codegen/                     # Candidate resolver, LMUL orchestrator, emission helpers
│   ├── registry.py                  # Loads the registries
│   ├── input_validation.py          # Validation checks and audits
│   ├── tools.py                     # DSL placeholder parsing, datatype aliases, ISA loading
│   ├── datatypes.py                 # Datatypes, categories and datatype pair groupings
│   ├── name_builder.py              # Function names, prototypes and call arguments
│   ├── cond_utils.py                # Preprocessor condition parsing and simplification
│   ├── include_gen.py               # IncludeManager: header layout and dependencies
│   ├── c_generator.py               # Per-ISA C implementation headers
│   ├── ci_generator.py              # C API dispatch headers
│   ├── cpp_generator.py             # C++ functional API (namespace mipp::)
│   └── obj_generator.py             # C++ object API (Rvd / Rvm) and public per-function headers
│
├── helpers_tests/                   # Test generation engine
│   ├── tests_builder.py             # Test engine
│   ├── dialect_adapters.py          # C / C++ / object syntax adapters
│   ├── domain_resolver.py           # Input domains and mask patterns
│   ├── tests_specs.json             # Per-function test properties
│   ├── tests_templates.json         # Test code templates
│   └── schemas/                     # JSON Schemas of the two files above
│
└── simd_ext/                        # One directory per target
    ├── scalar/                      # scalar_gen.py (Level 3 emission)
    ├── sse/                         # SSE ... SSE4.2
    ├── avx/                         # AVX / AVX2 / FMA
    ├── avx512/                      # AVX-512F / BW / DQ / ...
    ├── neon/                        # ARM NEON (ARMv7 / ARMv8-A)
    ├── sve/                         # ARM SVE (work in progress)
    └── rvv/                         # RISC-V Vector 1.0
```

The internals of `codegen/` are described in `generator/helpers_headers/codegen/README.md`. Building and running the tests is described in `tests/README.md` and in [Test Generator](generator/generating_tests/gen_mipp_tests.md).

---

## 3. Key Sections in the Developer Guide

- **[Mini-Templating DSL Reference](templating_dsl.md)**: The `%r<...>%`, `%m<...>%` and function-call placeholders used to write templates once for all datatypes.
- **[Adding a Function or ISA](adding_isa_or_function.md)**: Step-by-step workflow to add a new function or target architecture.
- **[Static Audits & Database Verification](audits_and_verification.md)**: Blocking validation checks, warning-only audits and CI pipelines.
- **Generator Internals**: Command-line reference of each generator and description of each registry family.
