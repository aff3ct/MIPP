# MIPPv2 Developer & Contributor Guide

Welcome to the internal architecture guide for MIPPv2. This documentation is intended for developers contributing new vector instructions, adding new CPU target backends, or improving the code generation and test infrastructure.

---

## 1. Architectural Philosophy: Declarative Code Generation

MIPPv1 relied on thousands of manually maintained, deeply nested C++ template headers. This approach suffered from template explosion, subtle divergence between architectures, and impossible maintenance when scaling to modern architectures like RISC-V Vector (RVV) and ARM SVE.

**MIPPv2 completely decouples architecture definitions from code generation:**

```
+-------------------------------------------------------------------------------+
|                           Declarative Data Layer                              |
|  - helpers_headers/registry_*.json : Functions, protos, categories, scalar    |
|  - helpers_headers/generic_emu_*.json: Portable algorithmic Level 2 emulations|
|  - simd_ext/<isa>/*_isa.json       : Architecture types, registers, macros    |
|  - simd_ext/<isa>/*_native_*.json  : Hardware intrinsics & templates (L0)     |
+-------------------------------------------------------------------------------+
                                        |
                                        v
+-------------------------------------------------------------------------------+
|                      Static Verification & Audit Engine                       |
|  - Dead-Code Detection (shadowed templates)                                   |
|  - Collision Audits (datatype / level conflicts)                              |
|  - JSON Schema & Ordering Validators                                          |
+-------------------------------------------------------------------------------+
                                        |
                                        v
+-------------------------------------------------------------------------------+
|                          Multi-Tier Fallback Solver                           |
|    Level 0 (Native) -> Level 1 (SpecEmu) -> Level 2 (GenEmu) -> Level 3       |
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

The code generator lives in the `generator/` directory:

```text
generator/
├── gen_mipp_headers.py              # Top-level header emission orchestrator
├── gen_mipp_tests.py                # Test suite generator
├── gen_mipp_docs.py                 # Documentation and matrix generator
│
├── helpers_headers/                 # Core engine & declarative registries
│   ├── registry_interfaces.json     # Canonical database of all MIPP functions
│   ├── registry_protos.json         # Generic function prototypes & signatures
│   ├── registry_categories.json     # Function categories (arithmetic, logic, etc.)
│   ├── registry_scalar_implems.json # Scalar Level 3 reference implementations
│   ├── registry_scalar_isa.json     # Scalar architecture configuration
│   ├── generic_emu_implems*.json    # Generic Level 2 emulation mappings
│   ├── generic_emu_templates*.json  # Templated generic emulations
│   ├── funcs_docs.json              # Function descriptions and math equations
│   ├── input_validation.py          # Static database verification & audit passes
│   ├── registry.py                  # Database loading and resolution
│   ├── tools.py                     # DSL parsing, type resolution, LMUL solver
│   ├── c_generator.py               # C99 interface emission & typedef generation
│   ├── cpp_generator.py             # C++ template wrapper emission
│   ├── cpp_object_generator.py      # C++ Rvd/Rvm class wrapper emission
│   └── include_gen.py               # IncludeManager and header dependency graph
│
├── helpers_tests/                   # Test generation engine
│   ├── tests_builder.py             # Test suite compiler & runner
│   └── tests_specs.json             # Test input ranges and tolerances
│
└── simd_ext/                        # Target-specific database per ISA
    ├── scalar/                      # Scalar baseline definitions
    ├── sse/                         # SSE / SSE2 / SSSE3 / SSE4.1 / SSE4.2
    ├── avx/                         # AVX / AVX2 / FMA
    ├── avx512/                      # AVX-512F / BW / DQ
    ├── neon/                        # ARM NEON (ARMv7 / ARMv8-A)
    ├── sve/                         # ARM SVE
    └── rvv/                         # RISC-V Vector 1.0
```

---

## 3. Key Sections in the Developer Guide

- **[Mini-Templating DSL Reference](templating_dsl.md)**: Master the `%r<...>%`, `%m<...>%`, and Jinja2 templating syntax used to write generic emulation templates without repeating code across 10 data types.
- **[Adding a Function or ISA](adding_isa_or_function.md)**: Step-by-step workflow to add a new function or target architecture.
- **[Static Audits & Integrity Verification](audits_and_verification.md)**: How MIPP guarantees zero dead-code, no duplicate levels, and deterministic fallbacks.
