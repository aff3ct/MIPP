# Why MIPPv2: Architecture & Technical Relevance

## 1. Evolution from MIPPv1 to MIPPv2

MIPP was originally developed as a C++ header-only library providing a uniform interface over fixed-width SIMD intrinsics (SSE, AVX, AVX-512, NEON). While MIPPv1 demonstrated the viability of zero-overhead SIMD abstraction, scaling to modern instruction set architectures, mixed vector lengths, and diverse masking behaviors revealed three fundamental limits:

- **Monolithic Hand-Written Headers**: MIPPv1 relied on manually maintained, deeply nested C++ template headers. Extending support for new data types or instruction sets required repetitive manual additions, increasing the likelihood of implementation divergence.
- **Incomplete Fallbacks**: Unsupported instruction/datatype combinations produced cryptic template instantiation errors or required ad-hoc emulation logic scattered across the codebase.
- **Single-Dialect Coupling**: The C++ object model was tightly coupled with internal intrinsic wrappers, making it impossible to consume MIPP from pure C codebases or embedded toolchains requiring a stable C ABI.

**MIPPv2** redesigns the library from the ground up:

- It replaces hand-written headers with an automated code generator driven by declarative JSON databases.
- It systematically resolves missing hardware instructions through a **deterministic 4-level fallback engine**, guaranteeing that every function works across all 10 supported data types.
- It exposes **three distinct APIs** to answer different programming needs: pure C99, C++ template functions, and C++ object operators.

---

## 2. Key Architectural Advancements

```
                         +-----------------------------+
                         |      User Application       |
                         +-----------------------------+
                                        |
          +-----------------------------+-----------------------------+
          |                             |                             |
          v                             v                             v
+-------------------+         +-------------------+         +-------------------+
|      C99 API      |         | C++ Template API  |         |  C++ Object API   |
|   (Pure C ABI)    |         | (Generic mipp::)  |         |  (Rvd/Rvm Class)  |
|     <mipp.h>      |         |    <mipp.hpp>     |         |  <mipp_obj.hpp>   |
+-------------------+         +-------------------+         +-------------------+
          |                             |                             |
          +-----------------------------+-----------------------------+
                                        |
                         +-----------------------------+
                         |   4-Tier Fallback Engine    |
                         |    L0 -> L1 -> L2 -> L3     |
                         +-----------------------------+
                                        |
     +-----------+-----------+----------+----------+-----------+-----------+
     |    SSE    |    AVX    | AVX-512  |   NEON   | SVE (WIP) |    RVV    |
     +-----------+-----------+----------+----------+-----------+-----------+
```

### 2.1. Tri-Dialect API Surface
MIPPv2 caters to different software engineering constraints through three distinct interfaces:

1. **C99 API (`<mipp.h>`)**: Pure C99 type-explicit functions (`mipp_add_float32(r0, r1)`). Perfect for pure C codebases, systems programming, embedded devices, and Linux kernel modules.
2. **C++ Functional Template API (`<mipp.hpp>`)**: Type-parameterized functions under namespace `mipp::` (`mipp::add<float>(r0, r1)`).
3. **C++ Object API (`<mipp_obj.hpp>`)**: Expressive `mipp::Rvd<T, LMUL>` and `mipp::Rvm<T, LMUL>` wrapper classes featuring full arithmetic (`+`, `-`, `*`, `/`), bitwise, and relational operator overloading.

### 2.2. Deterministic 4-Tier Fallback Hierarchy
MIPPv2 guarantees **100% functional completeness** across all 10 supported data types and all target ISAs by employing a deterministic 4-tier solver:

1. **Level 0 (Native Optimal)**: Direct 1-to-1 mapping to native CPU hardware intrinsics (e.g., `_mm256_add_ps`, `vaddq_f32`, `__riscv_vfadd_vf_f32m1`).
2. **Level 1 (Specific ISA Emulation)**: Emulates missing functionality using other hardware instructions available within the *same* ISA (e.g., emulating integer multiplication via bitwise shifts and shuffles on early SSE/AVX subsets).
3. **Level 2 (Generic Portable Emulation)**: Composes operations using lower-level portable MIPP primitives (e.g., transcendental functions `sin`, `cos`, `exp`, or masked operations built via `blend` and logical gates).
4. **Level 3 (Transparent Scalar Loop Fallback)**: Automatically executes an element-wise scalar loop if no SIMD instruction exists.

This structure eliminates compile-time failures on older or less complete instruction sets while maintaining peak performance on platforms with full native support.

### 2.3. Generalized Length Multiplier (LMUL)
MIPPv2 generalizes the concept of Length Multipliers ($\text{LMUL} \in \{1, 2, 4, 8\}$) across both variable-length and fixed-width instruction sets:

- **Hardware Register Grouping (RVV 1.0)**: Maps directly to native hardware vector register groups (e.g., `vfloat32m2_t`, `vfloat32m4_t`).
- **Software Recursive Binary Structures (x86, ARM, Scalar)**: Emulates multi-register grouping via hierarchical structures that compilers unroll cleanly at compile time, eliminating abstraction overhead.

### 2.4. Explicit 4-Variant Masking Model
Masking in MIPPv2 is treated as a first-class citizen with standardized semantics across all operations:

- **`unmasked`**: Standard unconditional computation.
- **`mask`**: Merges computed results with inactive elements of the destination register ($\text{res}_i = m_i \ ? \ f(a_i, b_i) : a_i$).
- **`maskz`**: Zeroes inactive elements ($\text{res}_i = m_i \ ? \ f(a_i, b_i) : 0$).
- **`masks`**: Preserves inactive elements from an explicit source vector ($\text{res}_i = m_i \ ? \ f(a_i, b_i) : \text{src}_i$).

---

<a id="simd-wrappers-comparison"></a>
## 3. Comparison with Existing SIMD Solutions

Choosing the right SIMD strategy depends on portability requirements, language constraints, and performance determinism. The following matrix compares MIPPv2 with the most prominent alternatives:

| Capability / Metric | [**MIPPv2**](https://github.com/aff3ct/mipp/tree/develop) | [**MIPPv1**](https://github.com/aff3ct/mipp/tree/master) | [**Google Highway**](https://github.com/google/highway) | [**xsimd**](https://github.com/xtensor-stack/xsimd) | [**Eve**](https://github.com/jfalcou/eve) | [**nSIMD**](https://github.com/agenium-scale/nsimd) | [**Vc**](https://github.com/VcDevel/Vc) | [**VCL**](https://github.com/vectorclass/version2) | **Raw Intrinsics** | **Auto-Vectorization** (`-O3`) |
| :--- | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| **License** | [![License](https://img.shields.io/github/license/aff3ct/mipp?style=flat)](https://github.com/aff3ct/mipp/blob/develop/LICENSE) | [![License](https://img.shields.io/github/license/aff3ct/mipp?style=flat)](https://github.com/aff3ct/mipp/blob/master/LICENSE) | [![License](https://img.shields.io/badge/license-Apache_2.0_%7C_BSD--3-blue)](https://github.com/google/highway/blob/master/LICENSE) | [![License](https://img.shields.io/github/license/xtensor-stack/xsimd?style=flat)](https://github.com/xtensor-stack/xsimd/blob/master/LICENSE) | [![License](https://img.shields.io/github/license/jfalcou/eve?style=flat)](https://github.com/jfalcou/eve/blob/main/LICENSE.md) | [![License](https://img.shields.io/github/license/agenium-scale/nsimd?style=flat)](https://github.com/agenium-scale/nsimd/blob/master/LICENSE) | [![License](https://img.shields.io/github/license/VcDevel/Vc?style=flat)](https://github.com/VcDevel/Vc/blob/master/LICENSE) | [![License](https://img.shields.io/github/license/vectorclass/version2?style=flat)](https://github.com/vectorclass/version2/blob/master/LICENSE) | ⚠️ Vendor specific | ⚠️ Compiler license |
| **GitHub Stars** | [![Stars](https://img.shields.io/github/stars/aff3ct/mipp?style=flat&label=%E2%AD%90)](https://github.com/aff3ct/mipp) | [![Stars](https://img.shields.io/github/stars/aff3ct/mipp?style=flat&label=%E2%AD%90)](https://github.com/aff3ct/mipp) | [![Stars](https://img.shields.io/github/stars/google/highway?style=flat&label=%E2%AD%90)](https://github.com/google/highway) | [![Stars](https://img.shields.io/github/stars/xtensor-stack/xsimd?style=flat&label=%E2%AD%90)](https://github.com/xtensor-stack/xsimd) | [![Stars](https://img.shields.io/github/stars/jfalcou/eve?style=flat&label=%E2%AD%90)](https://github.com/jfalcou/eve) | [![Stars](https://img.shields.io/github/stars/agenium-scale/nsimd?style=flat&label=%E2%AD%90)](https://github.com/agenium-scale/nsimd) | [![Stars](https://img.shields.io/github/stars/VcDevel/Vc?style=flat&label=%E2%AD%90)](https://github.com/VcDevel/Vc) | [![Stars](https://img.shields.io/github/stars/vectorclass/version2?style=flat&label=%E2%AD%90)](https://github.com/vectorclass/version2) | ⚠️ N/A | ⚠️ N/A |
| **Activity (Commits/Yr)** | [![Commits/yr](https://img.shields.io/github/commit-activity/y/aff3ct/mipp/develop?style=flat&label=commits)](https://github.com/aff3ct/mipp/commits/develop) | [![Commits/yr](https://img.shields.io/github/commit-activity/y/aff3ct/mipp/master?style=flat&label=commits)](https://github.com/aff3ct/mipp/commits/master) | [![Commits/yr](https://img.shields.io/github/commit-activity/y/google/highway?style=flat&label=commits)](https://github.com/google/highway/pulse) | [![Commits/yr](https://img.shields.io/github/commit-activity/y/xtensor-stack/xsimd?style=flat&label=commits)](https://github.com/xtensor-stack/xsimd/pulse) | [![Commits/yr](https://img.shields.io/github/commit-activity/y/jfalcou/eve?style=flat&label=commits)](https://github.com/jfalcou/eve/pulse) | [![Commits/yr](https://img.shields.io/github/commit-activity/y/agenium-scale/nsimd?style=flat&label=commits)](https://github.com/agenium-scale/nsimd/pulse) | [![Commits/yr](https://img.shields.io/github/commit-activity/y/VcDevel/Vc?style=flat&label=commits)](https://github.com/VcDevel/Vc/pulse) | [![Commits/yr](https://img.shields.io/github/commit-activity/y/vectorclass/version2?style=flat&label=commits)](https://github.com/vectorclass/version2/pulse) | ⚠️ N/A | ⚠️ N/A |
| **Contributors** | [![Contributors](https://img.shields.io/github/contributors/aff3ct/mipp?style=flat&label=%F0%9F%91%A5)](https://github.com/aff3ct/mipp/graphs/contributors) | [![Contributors](https://img.shields.io/github/contributors/aff3ct/mipp?style=flat&label=%F0%9F%91%A5)](https://github.com/aff3ct/mipp/graphs/contributors) | [![Contributors](https://img.shields.io/github/contributors/google/highway?style=flat&label=%F0%9F%91%A5)](https://github.com/google/highway/graphs/contributors) | [![Contributors](https://img.shields.io/github/contributors/xtensor-stack/xsimd?style=flat&label=%F0%9F%91%A5)](https://github.com/xtensor-stack/xsimd/graphs/contributors) | [![Contributors](https://img.shields.io/github/contributors/jfalcou/eve?style=flat&label=%F0%9F%91%A5)](https://github.com/jfalcou/eve/graphs/contributors) | [![Contributors](https://img.shields.io/github/contributors/agenium-scale/nsimd?style=flat&label=%F0%9F%91%A5)](https://github.com/agenium-scale/nsimd/graphs/contributors) | [![Contributors](https://img.shields.io/github/contributors/VcDevel/Vc?style=flat&label=%F0%9F%91%A5)](https://github.com/VcDevel/Vc/graphs/contributors) | [![Contributors](https://img.shields.io/github/contributors/vectorclass/version2?style=flat&label=%F0%9F%91%A5)](https://github.com/vectorclass/version2/graphs/contributors) | ⚠️ N/A | ⚠️ N/A |
| **Last Commit** | [![Last commit](https://img.shields.io/github/last-commit/aff3ct/mipp/develop?style=flat&label=last)](https://github.com/aff3ct/mipp/commits/develop) | [![Last commit](https://img.shields.io/github/last-commit/aff3ct/mipp/master?style=flat&label=last)](https://github.com/aff3ct/mipp/commits/master) | [![Last commit](https://img.shields.io/github/last-commit/google/highway?style=flat&label=last)](https://github.com/google/highway/commits) | [![Last commit](https://img.shields.io/github/last-commit/xtensor-stack/xsimd?style=flat&label=last)](https://github.com/xtensor-stack/xsimd/commits) | [![Last commit](https://img.shields.io/github/last-commit/jfalcou/eve?style=flat&label=last)](https://github.com/jfalcou/eve/commits) | [![Last commit](https://img.shields.io/github/last-commit/agenium-scale/nsimd?style=flat&label=last)](https://github.com/agenium-scale/nsimd/commits) | [![Last commit](https://img.shields.io/github/last-commit/VcDevel/Vc?style=flat&label=last)](https://github.com/VcDevel/Vc/commits) | [![Last commit](https://img.shields.io/github/last-commit/vectorclass/version2?style=flat&label=last)](https://github.com/vectorclass/version2/commits) | ⚠️ N/A | ⚠️ N/A |
| **Pure C99 API** | ✅ **Yes (`<mipp.h>`)** | ❌ No (C++ only) | ❌ No (C++ only) | ❌ No (C++ only) | ❌ No (C++ only) | ✅ Yes (`nsimd.h`) | ❌ No (C++ only) | ❌ No (C++ only) | ⚠️ Vendor specific | ⚠️ N/A |
| **C++ Operator Overloading** | ✅ **Yes (`Rvd`)** | ✅ Yes (`Reg`) | ❌ No (Named functions) | ✅ Yes (`batch`) | ✅ Yes (`wide`) | ✅ Yes (`pack`) | ✅ Yes (`Vector`) | ✅ Yes (`Vec...`) | ❌ No | ⚠️ N/A |
| **100% Fallback Guarantee** | ✅ **Levels 0 to 3** | ❌ Incomplete (Ad-hoc) | ⚠️ Partial emulations | ❌ Compile error | ❌ Compile error | ⚠️ Macro CPU fallback | ⚠️ Partial scalar | ⚠️ x86 subsets only | ❌ Compile error | ❌ Silent failure |
| **RISC-V Vector 1.0 (RVV)** | ⚠️ **Fixed-width only** | ❌ No | ✅ Scalable & Fixed | ⚠️ Fixed-width / WIP | ❌ No | ⚠️ Fixed-width (Draft) | ❌ No | ❌ No (x86 only) | ⚠️ Built-ins (VLA/Fixed) | ⚠️ Unpredictable |
| **ARM SVE Support** | ⚠️ **Fixed-width only** / WIP | ❌ No | ✅ Scalable & Fixed | ⚠️ Fixed-width / WIP | ⚠️ Fixed-width only | ⚠️ Fixed-width only | ❌ No | ❌ No (x86 only) | ⚠️ ACLE (VLA/Fixed) | ⚠️ Unpredictable |
| **Generalized LMUL ($1,2,4,8$)** | ✅ **Yes** | ❌ No | ✅ Yes (`ScalableTag`) | ❌ No | ❌ No | ❌ No | ❌ No | ❌ No | ❌ No (RVV only) | ❌ No |
| **Dispatch** | **Static** | **Static** | **Static & Dynamic** | **Static & Dynamic** | **Static** | **Static & Dynamic** | **Static** | **Static** *(Manual dynamic)* | **Static** *(Manual dynamic)* | **Static** *(Dynamic with `target_clones`)* |
| **C++ Standard Required** | **C++11** (or C99) | C++11 | C++11 | C++17 | C++20 required | C98 / C++11 | C++11 / C++14 | C++11 / C++17 | C99 / C++11 | C99 / C++11 |
| **Compilation Overhead** | ⚡ **Fast** (Simple inlines) | Medium (Deep templates) | 🐢 Heavy templates | Medium | 🐌 Very heavy | 🐌 Heavy (Macro bloat) | Medium / Heavy | ⚡ Fast (Inline headers) | ⚡ Very fast | ⚡ Zero lib overhead |
| **Assembly Determinism** | 🎯 **100% Explicit** | 🎯 Explicit | 🎯 Explicit | 🎯 Explicit | 🎯 Explicit | 🎯 Explicit | 🎯 Explicit | 🎯 100% Explicit | 🎯 100% Explicit | 🎲 Heuristic-driven |

### Key Differentiators for MIPPv2:

1.  **Seamless Dual-Ecosystem: Clean C99 & Modern C++**:

    Most modern wrappers (Google Highway, xsimd, Eve, Vc, VCL) are exclusively designed for C++ (often requiring C++17 or even C++20). While nSIMD provides a C interface, it relies on heavy macro preprocessing. MIPPv2 provides clean, inlined, type-safe C99 functions without macro obfuscation, making it effortless to integrate into pure C codebases, embedded systems, and Linux kernel modules.

2.  **Expressive Syntax without Sacrificing Portability**:

    To support runtime-variable vectors (VLA), Google Highway explicitly avoids C++ operator overloading (`a + b`), requiring explicit named functions (`hn::Add(d, a, b)`). MIPPv2 provides the best of both worlds for fixed-width workflows: functional C99 / C++ APIs for low-level control, plus full operator overloading (`mipp::Rvd`) that works consistently across all target architectures.

3.  **Never Breaks Compilation (Deterministic 4-Tier Fallbacks)**:

    In libraries like xsimd, Eve, or Vc, calling an operation not natively supported by the target CPU produces a hard compilation failure. MIPP automatically falls back through an ISA-specific emulation (Level 1), a generic MIPP emulation (Level 2), or a scalar loop (Level 3), guaranteeing complete functional coverage across all 10 supported data types.

4.  **Pragmatic Fixed-Width Design for RVV & SVE**:

    While Google Highway is built from the ground up for runtime Variable-Length Arrays (VLA), MIPPv2 intentionally chooses a compile-time fixed-width model (`-mrvv-vector-bits` / `-msve-vector-bits`). Fully implemented for RISC-V RVV 1.0 and currently being integrated for the upcoming ARM SVE backend, this deliberate engineering trade-off enables compile-time known sizes (`MIPP_N`), straightforward C-struct memory layouts, and standard C++ operator overloading without the runtime overhead of dynamic stripmining.

5.  **Predictable Performance vs. Compiler Auto-Vectorization**:

    While compilers have made great progress with `-O3 -ftree-vectorize`, auto-vectorization remains fragile: subtle changes in loop bounds, pointer aliasing, or compiler version updates can cause loops to silently de-vectorize. MIPP guarantees deterministic, explicit SIMD assembly.
