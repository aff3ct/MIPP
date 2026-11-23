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

- **C API (`<mipp.h>`, C11)**: Explicit type-suffixed functions (`mipp_add_float32`) for pure C codebases, embedded targets, and Linux kernel modules.
- **C++ Functional API (`<mipp.hpp>`, C++11)**: Overloaded functions under namespace `mipp::` (`mipp::add(a, b)`), with datatype and LMUL deduced from the register types.
- **C++ Object API (`<mipp_obj.hpp>`, C++11)**: Register classes (`mipp::Vd`, `mipp::Vm`) with complete operator overloading.

### 1.2. Deterministic 4-Level Fallback Hierarchy
Every function compiles on every target, for all its data types, and uses the best available level: **Level 0 (Native Hardware)**, **Level 1 (Dedicated Emulation)**, **Level 2 (Generic Emulation)** or **Level 3 (Scalar Fallback)**. A few functions are not implemented yet in two configurations (ARMv7 NEON, RVV without 64-bit elements): they compile but stop at run time. See [Implementation Levels](user/implementation_levels.md) and its [known limitations](user/implementation_levels.md#known-limitations).

### 1.3. Generalized Length Multiplier (LMUL)

Uniform vector register grouping ($\text{LMUL} \in \{1, 2, 4, 8\}$), plus half-vectors (`d2`, $\text{LMUL} = 1/2$):

- **Hardware (RVV 1.0)**: Native vector register grouping (`vfloat32m2_t`, `vfloat32m4_t`) and fractional registers (`vfloat32mf2_t`).
- **Software (x86, ARM)**: Binary register pairs unrolled at compile time.
- **Scalar target**: Flat arrays of $N \times \text{LMUL}$ elements.

See [Vector Types & LMUL](user/vector_types_and_lmul.md).

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

Choosing the right SIMD library depends on language requirements, compilation constraints, and portability goals. The tables below reflect the state of each project as of October 2026.

### Features

<div class="mipp-compare" markdown>

| | [MIPPv2](https://github.com/aff3ct/mipp/tree/develop) | [MIPPv1](https://github.com/aff3ct/mipp/tree/master) | [Highway](https://github.com/google/highway) | [xsimd](https://github.com/xtensor-stack/xsimd) | [Eve](https://github.com/jfalcou/eve) | [nSIMD](https://github.com/agenium-scale/nsimd) | [Vc](https://github.com/VcDevel/Vc) | [VCL](https://github.com/vectorclass/version2) | [std::simd](https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2024/p1928r15.pdf) | Raw intrinsics | Auto-vectorization |
| :--- | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| C API | <span class="y">✓</span> <small>`<mipp.h>`</small> | <span class="n">—</span> | <span class="n">—</span> | <span class="n">—</span> | <span class="n">—</span> | <span class="y">✓</span> <small>`nsimd.h`</small> | <span class="n">—</span> | <span class="n">—</span> | <span class="n">—</span> | <span class="p">◐</span> <small>Vendor-specific</small> | <span class="na">n/a</span> |
| C++ operator overloading | <span class="y">✓</span> <small>`Vd`</small> | <span class="y">✓</span> <small>`Reg`</small> | <span class="p">◐</span> <small>Not on SVE / RVV</small> | <span class="y">✓</span> <small>`batch`</small> | <span class="y">✓</span> <small>`wide`</small> | <span class="y">✓</span> <small>`pack`</small> | <span class="y">✓</span> <small>`Vector`</small> | <span class="y">✓</span> <small>`Vec…`</small> | <span class="y">✓</span> <small>`simd`</small> | <span class="n">—</span> | <span class="na">n/a</span> |
| Complete fallback | <span class="y">✓</span> <small>Levels 0–3 ([exceptions](user/implementation_levels.md#known-limitations))</small> | <span class="n">—</span> <small>Ad hoc</small> | <span class="y">✓</span> <small>`EMU128` / `SCALAR`</small> | <span class="p">◐</span> <small>Opt-in `emulated`</small> | <span class="y">✓</span> <small>`emulated_` ABI</small> | <span class="y">✓</span> <small>CPU emulation</small> | <span class="y">✓</span> <small>Scalar implementation</small> | <span class="p">◐</span> <small>x86 only, down to SSE2</small> | <span class="y">✓</span> <small>Mandated by ISO</small> | <span class="n">—</span> <small>Compile error</small> | <span class="n">—</span> <small>Silent scalar code</small> |
| RISC-V Vector 1.0 | <span class="p">◐</span> <small>Fixed-width</small> | <span class="n">—</span> | <span class="y">✓</span> <small>Scalable & fixed</small> | <span class="p">◐</span> <small>Fixed-width</small> | <span class="p">◐</span> <small>Fixed-width, unreleased</small> | <span class="n">—</span> | <span class="n">—</span> | <span class="n">—</span> | <span class="p">◐</span> <small>Fixed-width, WIP</small> | <span class="p">◐</span> <small>Built-ins, VLA / fixed</small> | <span class="p">◐</span> <small>Unpredictable</small> |
| ARM SVE | <span class="p">◐</span> <small>Fixed-width</small> | <span class="n">—</span> | <span class="y">✓</span> <small>Scalable & fixed</small> | <span class="p">◐</span> <small>Fixed-width</small> | <span class="p">◐</span> <small>Fixed-width</small> | <span class="y">✓</span> <small>Scalable & fixed</small> | <span class="n">—</span> | <span class="n">—</span> | <span class="p">◐</span> <small>Fixed-width, WIP</small> | <span class="p">◐</span> <small>ACLE, VLA / fixed</small> | <span class="p">◐</span> <small>Unpredictable</small> |
| Generalized LMUL ($1,2,4,8$) | <span class="y">✓</span> <small>Plus half-vectors</small> | <span class="n">—</span> | <span class="p">◐</span> <small>RVV only (`kPow2`)</small> | <span class="n">—</span> | <span class="n">—</span> | <span class="n">—</span> | <span class="n">—</span> | <span class="n">—</span> | <span class="n">—</span> | <span class="n">—</span> <small>RVV only</small> | <span class="n">—</span> |
| Dispatch | Static | Static | Static & dynamic | Static & dynamic | Static | Static & dynamic | Static | Static <small>Manual dynamic</small> | Static | Static <small>Manual dynamic</small> | Static <small>Dynamic via `target_clones`</small> |
| Minimum standard | C11 / C++11 | C++11 | C++17 | C++17 | C++20 | C89 / C++98 | C++11 | C++17 | C++26 | C99 / C++11 | C99 / C++11 |
| Compile-time cost | Low <small>Flat inlines</small> | Medium <small>Deep templates</small> | High <small>Templates</small> | Medium | Very high | High <small>Macros</small> | Medium to high | Low <small>Inline headers</small> | High <small>Templates</small> | Very low | None |
| Generated assembly | Explicit | Explicit | Explicit | Explicit | Explicit | Explicit | Explicit | Explicit | Explicit | Explicit | Heuristic |
| Implementation | Generated <small>Python</small> | Handwritten <small>C++</small> | Handwritten <small>Templates</small> | Handwritten <small>Templates</small> | Handwritten <small>C++20</small> | Generated <small>Python + macros</small> | Handwritten <small>Templates</small> | Handwritten <small>Classes</small> | Handwritten <small>Templates</small> | Manual | Compiler |

</div>

<p class="mipp-compare-legend"><span class="y">✓</span> Supported &nbsp;·&nbsp; <span class="p">◐</span> Partial &nbsp;·&nbsp; <span class="n">—</span> Not supported</p>

### Project Status

<div class="mipp-compare mipp-compare--status" markdown>

| Project | Latest release | License | Stars | Commits / year | Contributors | Last commit |
| :--- | :--- | :--- | :---: | :---: | :---: | :---: |
| [MIPPv2](https://github.com/aff3ct/mipp/tree/develop) | v2.2.0 <small>2026-10-18</small> | MIT | [![Stars](https://img.shields.io/github/stars/aff3ct/mipp?style=flat-square&label=&color=64748b)](https://github.com/aff3ct/mipp) | [![Commits per year](https://img.shields.io/github/commit-activity/y/aff3ct/mipp/develop?style=flat-square&label=&color=64748b)](https://github.com/aff3ct/mipp/commits/develop) | [![Contributors](https://img.shields.io/github/contributors/aff3ct/mipp?style=flat-square&label=&color=64748b)](https://github.com/aff3ct/mipp/graphs/contributors) | [![Last commit](https://img.shields.io/github/last-commit/aff3ct/mipp/develop?style=flat-square&label=&color=64748b)](https://github.com/aff3ct/mipp/commits/develop) |
| [MIPPv1](https://github.com/aff3ct/mipp/tree/master) | Untagged <small>`master`, 2026-04-15</small> | MIT | [![Stars](https://img.shields.io/github/stars/aff3ct/mipp?style=flat-square&label=&color=64748b)](https://github.com/aff3ct/mipp) | [![Commits per year](https://img.shields.io/github/commit-activity/y/aff3ct/mipp/master?style=flat-square&label=&color=64748b)](https://github.com/aff3ct/mipp/commits/master) | [![Contributors](https://img.shields.io/github/contributors/aff3ct/mipp?style=flat-square&label=&color=64748b)](https://github.com/aff3ct/mipp/graphs/contributors) | [![Last commit](https://img.shields.io/github/last-commit/aff3ct/mipp/master?style=flat-square&label=&color=64748b)](https://github.com/aff3ct/mipp/commits/master) |
| [Highway](https://github.com/google/highway) | 1.4.0 <small>2026-04-23</small> | Apache-2.0 / BSD-3-Clause | [![Stars](https://img.shields.io/github/stars/google/highway?style=flat-square&label=&color=64748b)](https://github.com/google/highway) | [![Commits per year](https://img.shields.io/github/commit-activity/y/google/highway?style=flat-square&label=&color=64748b)](https://github.com/google/highway/commits) | [![Contributors](https://img.shields.io/github/contributors/google/highway?style=flat-square&label=&color=64748b)](https://github.com/google/highway/graphs/contributors) | [![Last commit](https://img.shields.io/github/last-commit/google/highway?style=flat-square&label=&color=64748b)](https://github.com/google/highway/commits) |
| [xsimd](https://github.com/xtensor-stack/xsimd) | 14.3.0 <small>2026-07-15</small> | BSD-3-Clause | [![Stars](https://img.shields.io/github/stars/xtensor-stack/xsimd?style=flat-square&label=&color=64748b)](https://github.com/xtensor-stack/xsimd) | [![Commits per year](https://img.shields.io/github/commit-activity/y/xtensor-stack/xsimd?style=flat-square&label=&color=64748b)](https://github.com/xtensor-stack/xsimd/commits) | [![Contributors](https://img.shields.io/github/contributors/xtensor-stack/xsimd?style=flat-square&label=&color=64748b)](https://github.com/xtensor-stack/xsimd/graphs/contributors) | [![Last commit](https://img.shields.io/github/last-commit/xtensor-stack/xsimd?style=flat-square&label=&color=64748b)](https://github.com/xtensor-stack/xsimd/commits) |
| [Eve](https://github.com/jfalcou/eve) | v2023.02.15 <small>2023-02-15</small> | BSL-1.0 | [![Stars](https://img.shields.io/github/stars/jfalcou/eve?style=flat-square&label=&color=64748b)](https://github.com/jfalcou/eve) | [![Commits per year](https://img.shields.io/github/commit-activity/y/jfalcou/eve?style=flat-square&label=&color=64748b)](https://github.com/jfalcou/eve/commits) | [![Contributors](https://img.shields.io/github/contributors/jfalcou/eve?style=flat-square&label=&color=64748b)](https://github.com/jfalcou/eve/graphs/contributors) | [![Last commit](https://img.shields.io/github/last-commit/jfalcou/eve?style=flat-square&label=&color=64748b)](https://github.com/jfalcou/eve/commits) |
| [nSIMD](https://github.com/agenium-scale/nsimd) | v3.0.1 <small>2021-10-19</small> | MIT | [![Stars](https://img.shields.io/github/stars/agenium-scale/nsimd?style=flat-square&label=&color=64748b)](https://github.com/agenium-scale/nsimd) | [![Commits per year](https://img.shields.io/github/commit-activity/y/agenium-scale/nsimd?style=flat-square&label=&color=64748b)](https://github.com/agenium-scale/nsimd/commits) | [![Contributors](https://img.shields.io/github/contributors/agenium-scale/nsimd?style=flat-square&label=&color=64748b)](https://github.com/agenium-scale/nsimd/graphs/contributors) | [![Last commit](https://img.shields.io/github/last-commit/agenium-scale/nsimd?style=flat-square&label=&color=64748b)](https://github.com/agenium-scale/nsimd/commits) |
| [Vc](https://github.com/VcDevel/Vc) | 1.4.5 <small>2024-06-06, maintenance mode</small> | BSD-3-Clause | [![Stars](https://img.shields.io/github/stars/VcDevel/Vc?style=flat-square&label=&color=64748b)](https://github.com/VcDevel/Vc) | [![Commits per year](https://img.shields.io/github/commit-activity/y/VcDevel/Vc?style=flat-square&label=&color=64748b)](https://github.com/VcDevel/Vc/commits) | [![Contributors](https://img.shields.io/github/contributors/VcDevel/Vc?style=flat-square&label=&color=64748b)](https://github.com/VcDevel/Vc/graphs/contributors) | [![Last commit](https://img.shields.io/github/last-commit/VcDevel/Vc?style=flat-square&label=&color=64748b)](https://github.com/VcDevel/Vc/commits) |
| [VCL](https://github.com/vectorclass/version2) | v2.02.03 <small>2026-04-14</small> | Apache-2.0 | [![Stars](https://img.shields.io/github/stars/vectorclass/version2?style=flat-square&label=&color=64748b)](https://github.com/vectorclass/version2) | [![Commits per year](https://img.shields.io/github/commit-activity/y/vectorclass/version2?style=flat-square&label=&color=64748b)](https://github.com/vectorclass/version2/commits) | [![Contributors](https://img.shields.io/github/contributors/vectorclass/version2?style=flat-square&label=&color=64748b)](https://github.com/vectorclass/version2/graphs/contributors) | [![Last commit](https://img.shields.io/github/last-commit/vectorclass/version2?style=flat-square&label=&color=64748b)](https://github.com/vectorclass/version2/commits) |
| [std::simd](https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2024/p1928r15.pdf) | C++26 <small>P1928R15, 2024</small> | Compiler / standard library | <span class="na">n/a</span> | <span class="na">n/a</span> | <span class="na">n/a</span> | <span class="na">n/a</span> |

</div>

### Key Differentiators for MIPPv2

1. **Dual-Ecosystem (C & Modern C++)**: Most modern wrappers require C++17/C++20, while nSIMD relies on heavy macro preprocessing. MIPPv2 provides clean, strongly-typed C11 inline functions (C API) alongside the C++ Functional and C++ Object APIs.
2. **Expressive Syntax without Portability Sacrifices**: While Google Highway restricts operator overloading to fixed-width targets to accommodate sizeless SVE / RVV vectors, MIPPv2 retains natural operator expressions (`va + vb`) across all fixed-width targets.
3. **Deterministic 4-Level Fallback Guarantee**: Missing CPU instructions never cause compilation failures. MIPP falls back hierarchically through ISA emulation, generic portable primitives, or scalar loops, covering the function / datatype matrix across all 10 datatypes (except the few [known limitations](user/implementation_levels.md#known-limitations)).
4. **Pragmatic Fixed-Width Design (RVV & SVE)**: Targeting compile-time vector widths (`-mrvv-vector-bits` / `-msve-vector-bits`) preserves compile-time constants (`MIPP_N`), straightforward struct layouts, and standard operator syntax without runtime stripmining overhead.
5. **Predictable Assembly vs. Auto-Vectorization**: Compiler auto-vectorization (`-O3`) is fragile and can silently de-vectorize loops upon subtle code changes. MIPP guarantees explicit, deterministic SIMD instructions.
6. **Automated Offline Code Generation**: Shifting metaprogramming offline into a Python engine (`generator/`) yields three major engineering benefits:
    - **Fine-Grained Modular Headers**: Programmatic synthesis enables headers restricted to one function, one masking variant and one LMUL (e.g. `<mipp/obj/fun/m/m2/add.hpp>`). Including only what is needed makes compilation 2× to 4× faster than with the umbrella header (see [Headers & Compile Time](user/headers_and_compile_time.md)).
    - **Declarative Single Source of Truth**: Opcode mappings, fallbacks, unit tests, and documentation are generated from central JSON registries, enabling rapid maintenance and eliminating documentation drift.
    - **Fast Builds with Zero Indirection**: Replaces deep C++ template instantiations and macro bloat with flat, strongly typed inlines where IDEs jump directly to native intrinsics.
