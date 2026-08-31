# Why MIPPv2: Architecture & Technical Relevance

## 1. Evolution from MIPPv1 to MIPPv2

MIPP was originally developed as a C++ header-only library providing a uniform interface over fixed-width SIMD intrinsics (SSE, AVX, AVX-512, NEON). While MIPPv1 demonstrated the viability of zero-overhead SIMD abstraction, scaling to new instruction set architectures, mixed vector lengths, and diverse masking behaviors revealed fundamental architectural limits:

- **Monolithic Hand-Written Headers**: MIPPv1 relied on manually maintained, deeply nested C++ template headers. Extending support for new data types or instruction sets required repetitive manual additions, increasing the likelihood of implementation divergence.
- **Incomplete Fallbacks**: Unsupported instruction/datatype combinations produced cryptic template instantiation errors or required ad-hoc emulation logic scattered across the codebase.
- **Single-Dialect Coupling**: The C++ object model was tightly coupled with internal intrinsic wrappers, making it impossible to consume MIPP from pure C codebases or embedded toolchains requiring a stable C ABI.


**MIPPv2** replaces hand-written headers with an automated code generator driven by JSON databases. It systematically resolves missing hardware instructions through a 4-level fallback engine and exposes three distinct APIs to answer different programming needs: pure C, C++ template functions, and C++ objects.

---

## 2. Key Architectural Advancements in MIPPv2

```
                       +-----------------------------+
                       |   Declarative JSON Schema   |
                       |  (Protos, Interfaces, ISAs) |
                       +-----------------------------+
                                      |
                                      v
                       +-----------------------------+
                       | Static Verification & Audit |
                       | (Dead-Code, Level Collisions)|
                       +-----------------------------+
                                      |
                                      v
                       +-----------------------------+
                       |   4-Tier Fallback Engine    |
                       |   L0 -> L1 -> L2 -> L3      |
                       +-----------------------------+
                                      |
         +----------------------------+----------------------------+
         |                            |                            |
         v                            v                            v
+------------------+         +------------------+         +------------------+
|     C99 API      |         | C++ Template API |         |  C++ Object API  |
|  (Pure C ABI)    |         | (Generic mipp::) |         |  (Rvd/Rvm Class) |
+------------------+         +------------------+         +------------------+
```

### 2.1. Declarative Architecture with Static Auditing
All instruction signatures, ISA mappings, and emulation templates are decoupled from generation logic into structured JSON registries. The generator pipeline executes strict static verification passes prior to header emission:

- **Dead-Code Elimination**: Detects unreachable emulations shadowed by native implementations.

- **Duplicate & Collision Audits**: Ensures no ambiguous or conflicting implementations exist for any `(ISA, Datatype, MaskVariant, LMUL)` tuple.

- **Schema Integrity Checks**: Validates logical integrity across categories, interfaces, and scalar baselines.

### 2.2. Deterministic 4-Tier Fallback Hierarchy
MIPPv2 guarantees 100% functional completeness across all 10 supported data types and all target ISAs by employing a deterministic 4-tier solver:

1. **Level 0 (Native Optimal)**: 1-to-1 mapping to native CPU hardware intrinsics (e.g., `_mm256_add_ps`, `vaddq_f32`, `__riscv_vfadd_vf_f32m1`).

2. **Level 1 (Specific ISA Emulation)**: Emulates missing functionality using other hardware instructions available within the *same* ISA (e.g., emulating integer multiplication via bitwise shifts and shuffles on early SSE/AVX subsets).

3. **Level 2 (Generic Portable Emulation)**: Composes higher-level operations using lower-level portable MIPP primitives (e.g., transcendental functions `sin`, `cos`, `exp`, or masked operations built via `blend` and logical operations).

4. **Level 3 (Transparent Scalar Loop Fallback)**: Automatically synthesizes a vectorized `memcpy` loop calling the scalar baseline implementation if no SIMD instruction exists.

This structure eliminates compile-time failures on less complete ISAs while maintaining optimal performance on platforms with full native support.

### 2.3. Generalized Length Multiplier (LMUL)
MIPPv2 generalizes the concept of Length Multipliers ($\text{LMUL} \in \{1, 2, 4, 8\}$) across all target instruction sets:

- **Hardware Register Grouping (RVV 1.0)**: Configures the hardware vector register group size directly using native types (e.g., `vfloat32m2_t`, `vfloat32m4_t`).

- **Software Recursive Binary Structs (x86, ARM, Scalar)**: Emulates multi-register grouping via hierarchical structures:
  ```c
  typedef struct { rvd_avx_float32_m1_t r1, r2; } rvd_avx_float32_m2_t;
  typedef struct { rvd_avx_float32_m2_t r1, r2; } rvd_avx_float32_m4_t;
  typedef struct { rvd_avx_float32_m4_t r1, r2; } rvd_avx_float32_m8_t;
  ```
  Operations on software LMUL registers automatically unroll across sub-registers at compile time, eliminating abstraction overhead.

### 2.4. Explicit 4-Variant Masking Model
Masking in MIPPv2 is treated as a first-class citizen with standardized semantics across all operations:
- **`unmasked`**: Standard unconditional computation.
- **`mask`**: Merges computed results with inactive elements of the destination register ($\text{res}_i = m_i \ ? \ f(a_i, b_i) : a_i$).
- **`maskz`**: Zeroes inactive elements ($\text{res}_i = m_i \ ? \ f(a_i, b_i) : 0$).
- **`masks`**: Preserves inactive elements from an explicit source vector ($\text{res}_i = m_i \ ? \ f(a_i, b_i) : \text{src}_i$).

MIPPv2 maps these semantics to hardware opmask registers (`__mmask*` on AVX-512) and vector mask registers (`vbool*` on RVV), or full-width vector blend instructions (SSE/AVX/NEON).

### 2.5. Scalable Vector Extension Backends
MIPPv2 incorporates native support for **RISC-V Vector 1.0** (RVV) and **ARM SVE** alongside traditional fixed-width x86/ARM extensions, accommodating architectures where vector lengths are determined by hardware implementation or runtime configuration.

### 2.6. Tri-Dialect API Surface
MIPPv2 provides three distinct programming interfaces catering to different software engineering requirements:
1. **C API (`<mipp.h>`)**: Pure C99 API suitable for systems programming, C projects, and FFIs.
2. **C++ Functional Template API (`<mipp.hpp>`)**: Type-safe parameterized functions (`mipp::add<float>(r0, r1)`).
3. **C++ Object API (`<mipp_obj.hpp>`)**: High-level `mipp::Rvd<T, LMUL>` and `mipp::Rvm<T, LMUL>` classes featuring full arithmetic, bitwise, and relational operator overloading.

---

## 3. Technical Relevance as a SIMD Abstraction Library

### 3.1. Generated Architecture: Robustness, Maintainability, and Correctness
Unlike traditional hand-written SIMD wrapper libraries (which often suffer from implementation drift and incomplete fallback matrices across architectures), MIPPv2 is **entirely generated from declarative JSON databases**. This generator-driven approach provides multiple advantages:
- **Exhaustive Correctness & Static Verification**: The generator enforces compile-time static audits on the database (dead-code detection, level placement consistency, and duplicate implementation checks), guaranteeing that no instruction combination produces invalid or undefined behavior.
- **Maintainability & Rapid Extension**: Adding a new hardware intrinsic, vector instruction, or hardware backend requires only updating the declarative JSON registries without manually touching or duplicating hundreds of template definitions across headers.
- **Automated Property-Based Testing**: Test suites are automatically synthesized across all dialects (C, C++, C++ Object), LMUL configurations, and masking variants with strict domain boundaries and precision tolerances.

### 3.2. Ground-Up Design Around SOTA SIMD Extensions
MIPPv2's abstraction layer was designed **around state-of-the-art SIMD paradigms** (AVX-512, ARM SVE, and RISC-V Vector 1.0):
- **First-Class 4-Way Masking Semantics**: Exposes native opmask and predication capabilities (`unmasked`, `mask`, `maskz`, `masks`) that map directly to hardware opmasks (`__mmask*` on AVX-512) and vector predicate registers (`vbool*` on RVV).
- **Generalized Hardware/Software LMUL**: Seamlessly models RISC-V dynamic register grouping ($V_{\text{type}}$) while providing equivalent zero-overhead software struct unrolling on fixed-width architectures.

### 3.3. Deterministic Assembly Generation
Auto-vectorization heuristics vary across compiler versions and flags. MIPP provides explicit SIMD semantics where every operation predictably maps to direct machine instructions without vendor intrinsics lock-in.

### 3.4. Zero-Overhead Abstraction Guarantee
Every MIPP function is declared `static inline` with pass-by-value parameter passing. Compilers inline MIPP operations completely, emitting assembly indistinguishable from hand-written vendor intrinsics.
