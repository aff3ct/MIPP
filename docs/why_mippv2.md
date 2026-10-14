---
hide:
  - navigation
---

# Why MIPPv2: Architecture & Technical Relevance

MIPPv2 provides portable, zero-overhead SIMD computing across x86, ARM, and RISC-V targets through an offline code generation pipeline, a deterministic fallback engine, and three APIs (C, C++ Functional, C++ Object) sharing the same implementation.

---

## 1. Key Architectural Principles

![MIPPv2 architecture: three APIs (C, C++ Functional, C++ Object) share one implementation that picks, per function, datatype and target, the first available level among L0 native, L1 dedicated emulation, L2 generic emulation and L3 scalar fallback; targets SSE, AVX, AVX-512, NEON, SVE, RVV and Scalar](assets/images/architecture.svg){ width="680" }

### 1.1. Three APIs
Three complementary interfaces mapping to the same inlined instructions:

- **C API (`<mipp.h>`, C99)**: Explicit type-suffixed functions (`mipp_add_float32`) for pure C codebases, embedded targets, and Linux kernel modules.
- **C++ Functional API (`<mipp.hpp>`)**: Overloaded functions under namespace `mipp::` (`mipp::add(a, b)`), with datatype and LMUL deduced from the register types.
- **C++ Object API (`<mipp_obj.hpp>`)**: Register classes (`mipp::Rvd`, `mipp::Rvm`) with complete operator overloading.

### 1.2. Deterministic 4-Level Fallback Hierarchy
Every function is implemented on every target, for all 10 data types, at the best available level: **Level 0 (Native Hardware)**, **Level 1 (Dedicated Emulation)**, **Level 2 (Generic Emulation)** or **Level 3 (Scalar Fallback)**. See [Implementation Levels](user/implementation_levels.md), including its [known limitations](user/implementation_levels.md#known-limitations).

### 1.3. Generalized Length Multiplier (LMUL)

Uniform vector register grouping ($\text{LMUL} \in \{1, 2, 4, 8\}$):

- **Hardware (RVV 1.0)**: Native vector register grouping (`vfloat32m2_t`, `vfloat32m4_t`).
- **Software (x86, ARM, Scalar)**: Binary register pairs unrolled cleanly at compile time.

### 1.4. Explicit 4-Variant Masking Model

Standardized execution semantics across all operations:

- **Unmasked** (`U`, no suffix): Unconditional vector computation.
- **Merge-Masked** (`M`, `_mask`): Inactive elements keep the first operand ($\text{res}_i = m_i \ ? \ f(a_i, b_i) : a_i$).
- **Zero-Masked** (`Z`, `_maskz`): Zeroes inactive elements ($\text{res}_i = m_i \ ? \ f(a_i, b_i) : 0$).
- **Source-Masked** (`S`, `_masks`): Inactive elements take the values of a source vector ($\text{res}_i = m_i \ ? \ f(a_i, b_i) : \text{src}_i$).

See [Masking Semantics](user/masking_semantics.md) for the complete reference.

---

<a id="simd-wrappers-comparison"></a>
<a id="3-comparison-with-existing-simd-solutions"></a>
## 2. Comparison with Existing SIMD Solutions

Choosing the right SIMD library depends on language requirements, compilation constraints, and portability goals:

| Capability / Metric | [**MIPPv2**](https://github.com/aff3ct/mipp/tree/develop) | [**MIPPv1**](https://github.com/aff3ct/mipp/tree/master) | [**Google Highway**](https://github.com/google/highway) | [**xsimd**](https://github.com/xtensor-stack/xsimd) | [**Eve**](https://github.com/jfalcou/eve) | [**nSIMD**](https://github.com/agenium-scale/nsimd) | [**Vc**](https://github.com/VcDevel/Vc) | [**VCL**](https://github.com/vectorclass/version2) | [**std::simd**](https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2024/p1928r15.pdf) *(C++26)* | **Raw Intrinsics** | **Auto-Vectorization** (`-O3`) |
| :--- | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| **C API (C99)** | ✅ **Yes (`<mipp.h>`)** | ❌ No (C++ only) | ❌ No (C++ only) | ❌ No (C++ only) | ❌ No (C++ only) | ✅ Yes (`nsimd.h`) | ❌ No (C++ only) | ❌ No (C++ only) | ❌ No (C++ only) | ⚠️ Vendor specific | N/A |
| **C++ Operator Overloading** | ✅ **Yes (`Rvd`)** | ✅ Yes (`Reg`) | ❌ No (Named functions) | ✅ Yes (`batch`) | ✅ Yes (`wide`) | ✅ Yes (`pack`) | ✅ Yes (`Vector`) | ✅ Yes (`Vec...`) | ✅ Yes (`simd`) | ❌ No | N/A |
| **100% Fallback Guarantee** | ✅ **Levels 0 to 3** | ❌ Incomplete (Ad-hoc) | ⚠️ Partial emulations | ❌ Compile error | ❌ Compile error | ⚠️ Macro CPU fallback | ⚠️ Partial scalar | ⚠️ x86 subsets only | ✅ Guaranteed (ISO spec) | ❌ Compile error | ❌ Silent failure |
| **RISC-V Vector 1.0 (RVV)** | ⚠️ **Fixed-width only** | ❌ No | ✅ Scalable & Fixed | ⚠️ Fixed-width / WIP | ❌ No | ⚠️ Fixed-width (Draft) | ❌ No | ❌ No (x86 only) | ⚠️ Fixed-width only (WIP) | ⚠️ Built-ins (VLA/Fixed) | ⚠️ Unpredictable |
| **ARM SVE Support** | ⚠️ **Fixed-width only / WIP** | ❌ No | ✅ Scalable & Fixed | ⚠️ Fixed-width / WIP | ⚠️ Fixed-width only | ⚠️ Fixed-width only | ❌ No | ❌ No (x86 only) | ⚠️ Fixed-width only (WIP) | ⚠️ ACLE (VLA/Fixed) | ⚠️ Unpredictable |
| **Generalized LMUL ($1,2,4,8$)** | ✅ **Yes** | ❌ No | ✅ Yes (`ScalableTag`) | ❌ No | ❌ No | ❌ No | ❌ No | ❌ No | ❌ No | ❌ No (RVV only) | ❌ No |
| **Dispatch** | **Static** | **Static** | **Static & Dynamic** | **Static & Dynamic** | **Static** | **Static & Dynamic** | **Static** | **Static** *(Manual dynamic)* | **Static** | **Static** *(Manual dynamic)* | **Static** *(Dynamic with `target_clones`)* |
| **C++ Standard Required** | **C99 / C++11** | C++11 | C++11 | C++17 | C++20 | C89 / C++98 | C++11 / C++14 | C++11 / C++17 | C++26 | C99 / C++11 | C99 / C++11 |
| **Compilation Overhead** | **Fast** (Simple inlines) | Medium (Deep templates) | Heavy templates | Medium | Very heavy | Heavy (Macro bloat) | Medium / Heavy | Fast (Inline headers) | Heavy templates | Very fast | Zero lib overhead |
| **Assembly Determinism** | **Explicit** | Explicit | Explicit | Explicit | Explicit | Explicit | Explicit | Explicit | Explicit | Explicit | Heuristic-driven |
| **Implementation Approach** | **Code-generated (Python)** | Handwritten (C++) | Handwritten (Templates) | Handwritten (Templates) | Handwritten (C++20) | Code-generated (Python + Macros) | Handwritten (Templates) | Handwritten (Classes) | Handwritten (Templates) | Handwritten (Manual) | Compiler-generated |
| **License** | [![License](https://img.shields.io/github/license/aff3ct/mipp?style=flat)](https://github.com/aff3ct/mipp/blob/develop/LICENSE) | [![License](https://img.shields.io/github/license/aff3ct/mipp?style=flat)](https://github.com/aff3ct/mipp/blob/master/LICENSE) | [![License](https://img.shields.io/badge/license-Apache_2.0_%7C_BSD--3-blue)](https://github.com/google/highway/blob/master/LICENSE) | [![License](https://img.shields.io/github/license/xtensor-stack/xsimd?style=flat)](https://github.com/xtensor-stack/xsimd/blob/master/LICENSE) | [![License](https://img.shields.io/github/license/jfalcou/eve?style=flat)](https://github.com/jfalcou/eve/blob/main/LICENSE.md) | [![License](https://img.shields.io/github/license/agenium-scale/nsimd?style=flat)](https://github.com/agenium-scale/nsimd/blob/master/LICENSE) | [![License](https://img.shields.io/github/license/VcDevel/Vc?style=flat)](https://github.com/VcDevel/Vc/blob/master/LICENSE) | [![License](https://img.shields.io/github/license/vectorclass/version2?style=flat)](https://github.com/vectorclass/version2/blob/master/LICENSE) | Compiler / STL license | ⚠️ Vendor specific | ⚠️ Compiler license |
| **GitHub Stars** | [![Stars](https://img.shields.io/github/stars/aff3ct/mipp?style=flat&label=%E2%AD%90)](https://github.com/aff3ct/mipp) | [![Stars](https://img.shields.io/github/stars/aff3ct/mipp?style=flat&label=%E2%AD%90)](https://github.com/aff3ct/mipp) | [![Stars](https://img.shields.io/github/stars/google/highway?style=flat&label=%E2%AD%90)](https://github.com/google/highway) | [![Stars](https://img.shields.io/github/stars/xtensor-stack/xsimd?style=flat&label=%E2%AD%90)](https://github.com/xtensor-stack/xsimd) | [![Stars](https://img.shields.io/github/stars/jfalcou/eve?style=flat&label=%E2%AD%90)](https://github.com/jfalcou/eve) | [![Stars](https://img.shields.io/github/stars/agenium-scale/nsimd?style=flat&label=%E2%AD%90)](https://github.com/agenium-scale/nsimd) | [![Stars](https://img.shields.io/github/stars/VcDevel/Vc?style=flat&label=%E2%AD%90)](https://github.com/VcDevel/Vc) | [![Stars](https://img.shields.io/github/stars/vectorclass/version2?style=flat&label=%E2%AD%90)](https://github.com/vectorclass/version2) | N/A | N/A | N/A |
| **Activity (Commits/Yr)** | [![Commits/yr](https://img.shields.io/github/commit-activity/y/aff3ct/mipp/develop?style=flat&label=commits)](https://github.com/aff3ct/mipp/commits/develop) | [![Commits/yr](https://img.shields.io/github/commit-activity/y/aff3ct/mipp/master?style=flat&label=commits)](https://github.com/aff3ct/mipp/commits/master) | [![Commits/yr](https://img.shields.io/github/commit-activity/y/google/highway?style=flat&label=commits)](https://github.com/google/highway/pulse) | [![Commits/yr](https://img.shields.io/github/commit-activity/y/xtensor-stack/xsimd?style=flat&label=commits)](https://github.com/xtensor-stack/xsimd/pulse) | [![Commits/yr](https://img.shields.io/github/commit-activity/y/jfalcou/eve?style=flat&label=commits)](https://github.com/jfalcou/eve/pulse) | [![Commits/yr](https://img.shields.io/github/commit-activity/y/agenium-scale/nsimd?style=flat&label=commits)](https://github.com/agenium-scale/nsimd/pulse) | [![Commits/yr](https://img.shields.io/github/commit-activity/y/VcDevel/Vc?style=flat&label=commits)](https://github.com/VcDevel/Vc/pulse) | [![Commits/yr](https://img.shields.io/github/commit-activity/y/vectorclass/version2?style=flat&label=commits)](https://github.com/vectorclass/version2/pulse) | N/A | N/A | N/A |
| **Contributors** | [![Contributors](https://img.shields.io/github/contributors/aff3ct/mipp?style=flat&label=%F0%9F%91%A5)](https://github.com/aff3ct/mipp/graphs/contributors) | [![Contributors](https://img.shields.io/github/contributors/aff3ct/mipp?style=flat&label=%F0%9F%91%A5)](https://github.com/aff3ct/mipp/graphs/contributors) | [![Contributors](https://img.shields.io/github/contributors/google/highway?style=flat&label=%F0%9F%91%A5)](https://github.com/google/highway/graphs/contributors) | [![Contributors](https://img.shields.io/github/contributors/xtensor-stack/xsimd?style=flat&label=%F0%9F%91%A5)](https://github.com/xtensor-stack/xsimd/graphs/contributors) | [![Contributors](https://img.shields.io/github/contributors/jfalcou/eve?style=flat&label=%F0%9F%91%A5)](https://github.com/jfalcou/eve/graphs/contributors) | [![Contributors](https://img.shields.io/github/contributors/agenium-scale/nsimd?style=flat&label=%F0%9F%91%A5)](https://github.com/agenium-scale/nsimd/graphs/contributors) | [![Contributors](https://img.shields.io/github/contributors/VcDevel/Vc?style=flat&label=%F0%9F%91%A5)](https://github.com/VcDevel/Vc/graphs/contributors) | [![Contributors](https://img.shields.io/github/contributors/vectorclass/version2?style=flat&label=%F0%9F%91%A5)](https://github.com/vectorclass/version2/graphs/contributors) | N/A | N/A | N/A |
| **Last Commit** | [![Last commit](https://img.shields.io/github/last-commit/aff3ct/mipp/develop?style=flat&label=last)](https://github.com/aff3ct/mipp/commits/develop) | [![Last commit](https://img.shields.io/github/last-commit/aff3ct/mipp/master?style=flat&label=last)](https://github.com/aff3ct/mipp/commits/master) | [![Last commit](https://img.shields.io/github/last-commit/google/highway?style=flat&label=last)](https://github.com/google/highway/commits) | [![Last commit](https://img.shields.io/github/last-commit/xtensor-stack/xsimd?style=flat&label=last)](https://github.com/xtensor-stack/xsimd/commits) | [![Last commit](https://img.shields.io/github/last-commit/jfalcou/eve?style=flat&label=last)](https://github.com/jfalcou/eve/commits) | [![Last commit](https://img.shields.io/github/last-commit/agenium-scale/nsimd?style=flat&label=last)](https://github.com/agenium-scale/nsimd/commits) | [![Last commit](https://img.shields.io/github/last-commit/VcDevel/Vc?style=flat&label=last)](https://github.com/VcDevel/Vc/commits) | [![Last commit](https://img.shields.io/github/last-commit/vectorclass/version2?style=flat&label=last)](https://github.com/vectorclass/version2/commits) | N/A | N/A | N/A |

### Key Differentiators for MIPPv2

1. **Dual-Ecosystem (C & Modern C++)**: Most modern wrappers require C++17/C++20, while nSIMD relies on heavy macro preprocessing. MIPPv2 provides clean, strongly-typed C99 inline functions (C API) alongside the C++ Functional and C++ Object APIs.
2. **Expressive Syntax without Portability Sacrifices**: While Google Highway omits operator overloading to accommodate runtime VLA vectors, MIPPv2 retains natural operator expressions (`va + vb`) across all fixed-width targets.
3. **Deterministic 4-Level Fallback Guarantee**: Missing CPU instructions never cause compilation failures. MIPP falls back hierarchically through ISA emulation, generic portable primitives, or scalar loops, covering virtually the entire function / datatype matrix across all 10 datatypes.
4. **Pragmatic Fixed-Width Design (RVV & SVE)**: Targeting compile-time vector widths (`-mrvv-vector-bits` / `-msve-vector-bits`) preserves compile-time constants (`MIPP_N`), straightforward struct layouts, and standard operator syntax without runtime stripmining overhead.
5. **Predictable Assembly vs. Auto-Vectorization**: Compiler auto-vectorization (`-O3`) is fragile and can silently de-vectorize loops upon subtle code changes. MIPP guarantees explicit, deterministic SIMD instructions.
6. **Automated Offline Code Generation**: Shifting metaprogramming offline into a Python engine (`generator/`) yields three major engineering benefits:
    - **Fine-Grained Modular Headers**: Programmatic synthesis enables headers restricted to one function, one masking variant and one LMUL (e.g. `<mipp/obj/fun/m/m2/add.hpp>`). Including only what is needed makes compilation 2× to 4× faster than with the umbrella header (see [Headers & Compile Time](user/headers_and_compile_time.md)).
    - **Declarative Single Source of Truth**: Opcode mappings, fallbacks, unit tests, and documentation are generated from central JSON registries, enabling rapid maintenance and eliminating documentation drift.
    - **Fast Builds with Zero Indirection**: Replaces deep C++ template instantiations and macro bloat with flat, strongly typed inlines where IDEs jump directly to native intrinsics.
