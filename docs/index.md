---
hide:
  - navigation
  - toc
---

<div class="mipp-hero">
  <h1 class="mipp-hero-title">My Intrinsics Plus Plus <span class="mippv2">MIPPv2</span></h1>
  <p class="mipp-hero-subtitle">
    Portable, zero-overhead SIMD computing for modern C and C++. Write once, vectorize everywhere across x86, ARM, and RISC-V targets with a guaranteed 4-level fallback engine.
  </p>

  <div class="mipp-hero-actions">
    <a href="user/getting_started/" class="mipp-btn mipp-btn-primary">
      <span>🚀</span> Get Started (5 min)
    </a>
    <a href="funcs_support/" class="mipp-btn mipp-btn-secondary">
      <span>📚</span> API Reference
    </a>
    <a href="https://github.com/aff3ct/MIPP/tree/develop" class="mipp-btn mipp-btn-secondary" target="_blank" rel="noopener">
      <svg viewBox="0 0 24 24" width="24" height="24" fill="currentColor" aria-hidden="true">
        <path d="M12 2A10 10 0 0 0 2 12c0 4.42 2.87 8.17 6.84 9.5.5.08.66-.23.66-.5v-1.69c-2.77.6-3.36-1.34-3.36-1.34-.46-1.16-1.11-1.47-1.11-1.47-.91-.62.07-.6.07-.6 1 .07 1.53 1.03 1.53 1.03.87 1.52 2.34 1.07 2.91.83.1-.65.35-1.09.63-1.34-2.22-.25-4.55-1.11-4.55-4.92 0-1.11.38-2 1.03-2.71-.1-.25-.45-1.29.1-2.64 0 0 .84-.27 2.75 1.02.79-.22 1.65-.33 2.5-.33.85 0 1.71.11 2.5.33 1.91-1.29 2.75-1.02 2.75-1.02.55 1.35.2 2.39.1 2.64.65.71 1.03 1.6 1.03 2.71 0 3.82-2.34 4.66-4.57 4.91.36.31.69.92.69 1.85V21c0 .27.16.59.67.5C19.14 20.16 22 16.42 22 12A10 10 0 0 0 12 2z"/>
      </svg> GitHub
    </a>
  </div>

  <div class="mipp-chips-container">
    <span class="mipp-chip"><b>x86</b> SSE · AVX · AVX-512</span>
    <span class="mipp-chip"><b>ARM</b> NEON · SVE (WIP)</span>
    <span class="mipp-chip"><b>RISC-V</b> RVV 1.0</span>
    <span class="mipp-chip"><b>Standards</b> C99 · C++11</span>
    <span class="mipp-chip"><b>Overhead</b> 0% Fully Inlined</span>
  </div>
</div>

<div class="mipp-grid-2x2">
  <div class="mipp-card">
    <div class="mipp-card-header">
      <div class="mipp-card-icon">🚀</div>
      <h3 class="mipp-card-title">Next-Gen ISAs & Scalable Vectors</h3>
    </div>
    <p class="mipp-card-desc">
      Native support for <b>AVX-512</b>, <b>ARM SVE</b>, and <b>RISC-V RVV</b>. Advanced features include register grouping (<b>LMUL/LDIV</b> up to x8/d2), full vector masking, and an <b>auto-generated</b>, <b>future-proof</b> codebase. Easily <b>extensible to new ISAs</b>.
    </p>
  </div>
  <div class="mipp-card">
    <div class="mipp-card-header">
      <div class="mipp-card-icon">🎯</div>
      <h3 class="mipp-card-title">Unique Tri-Dialect API</h3>
    </div>
    <p class="mipp-card-desc">
      Choose your paradigm: pure <b>C99</b> (<code>mipp_add_float32</code>) for <b>OS kernels and embedded targets</b>; generic <b>C++ Templates</b> (<code>mipp::add&lt;float&gt;</code>) for <b>HPC algorithms</b>; or expressive <b>C++ Objects</b> (<code>va + vb</code>) with full <b>operator overloading</b>.
    </p>
  </div>
  <div class="mipp-card">
    <div class="mipp-card-header">
      <div class="mipp-card-icon">🛡️</div>
      <h3 class="mipp-card-title">100% Fallback Guarantee</h3>
    </div>
    <p class="mipp-card-desc">
      Guaranteed completeness across all <b>10 datatypes</b> through a deterministic <b>4-level fallback engine</b>: <b>L0</b> (Native Intrinsic) &rarr; <b>L1</b> (Same-ISA Emulation) &rarr; <b>L2</b> (Portable Compose) &rarr; <b>L3</b> (Scalar Loop Fallback). <b>Zero missing-instruction errors</b>.
    </p>
  </div>
  <div class="mipp-card">
    <div class="mipp-card-header">
      <div class="mipp-card-icon">⚡</div>
      <h3 class="mipp-card-title">Zero-Overhead & Header-Only</h3>
    </div>
    <p class="mipp-card-desc">
      <b>No compilation</b>, <b>no external dependencies</b>, and <b>no linking</b> required. Simply include <code>&lt;mipp.h&gt;</code>, <code>&lt;mipp.hpp&gt;</code>, or <code>&lt;mipp_obj.hpp&gt;</code> into your include path: code inlines directly into bare-metal assembly with <b>zero runtime penalty</b>.
    </p>
  </div>
</div>

<!-- Featured MIPP API Explorer Showcase Card -->
<div class="mipp-explorer-showcase-card">
  <div class="mipp-explorer-showcase-content">
    <div class="mipp-explorer-showcase-badge">🔍 Interactive Catalog</div>
    <h2 class="mipp-explorer-showcase-title">MIPP API Explorer</h2>
    <p class="mipp-explorer-showcase-desc">
      Search and compare all <b>85 MIPP vector primitives</b> with <b>reverse vendor intrinsic lookup</b> (e.g. <code>_mm256_blendv_ps</code>, <code>vbslq_f32</code>, <code>__riscv_vmerge_vvm_f32m1</code>), live hardware acceleration matrices (L0..L3), and tri-dialect prototypes.
    </p>
    <div class="mipp-explorer-showcase-chips">
      <span>🔍 Reverse Intrinsic Lookup</span>
      <span>⚙️ SSE · AVX · AVX-512 · NEON · SVE · RVV</span>
      <span>🔄 C99 · C++ Functional · C++ Object</span>
    </div>
  </div>
  <div class="mipp-explorer-showcase-action">
    <a href="explorer/" class="mipp-btn mipp-btn-primary">
      Launch API Explorer &rarr;
    </a>
  </div>
</div>

---

## Interactive Code Preview : One Task, Three Dialects

See how simple and expressive vectorized code becomes with MIPP:

=== "C99 Low-Level API (`<mipp.h>`)"

    ```c
    #include <mipp.h>
    #include <stddef.h>

    void vector_add(const float* a, const float* b, float* c, size_t n) {

        const size_t vec_limit = (n / MIPP_N_FLOAT32) * MIPP_N_FLOAT32;

        for (size_t i = 0; i < vec_limit; i += MIPP_N_FLOAT32) {
            rvd_float32_t va, vb, vc;
            va = mipp_load_float32(a + i);
            vb = mipp_load_float32(b + i);
            vc = mipp_add_float32(va, vb); // Pure C99 explicit symbol
            mipp_store_float32(c + i, vc);
        }

        for (size_t i = vec_limit; i < n; i++) { // Clean scalar tail loop
            c[i] = a[i] + b[i];
        }
    }
    ```

=== "C++ Template Functional API (`<mipp.hpp>`)"

    ```cpp
    #include <mipp.hpp>
    #include <vector>

    void vector_add(const std::vector<float>& a, const std::vector<float>& b, std::vector<float>& c) {
        constexpr size_t N = mipp::N<float>();
        const size_t vec_limit = (a.size() / N) * N;

        for (size_t i = 0; i < vec_limit; i += N) {
            mipp::rvd<float> va, vb, vc;
            va = mipp::load<float>(&a[i]);
            vb = mipp::load<float>(&b[i]);
            vc = mipp::add(va, vb); // Type-parameterized template
            mipp::store(&c[i], vc);
        }

        for (size_t i = vec_limit; i < a.size(); i++) { // Clean scalar tail loop
            c[i] = a[i] + b[i];
        }
    }
    ```

=== "C++ Object API (`<mipp_obj.hpp>`)"

    ```cpp
    #include <mipp_obj.hpp>
    #include <vector>

    void vector_add(const std::vector<float>& a, const std::vector<float>& b, std::vector<float>& c) {
        constexpr size_t N = mipp::Rvd<float>::size();
        const size_t vec_limit = (a.size() / N) * N;

        for (size_t i = 0; i < vec_limit; i += N) {
            mipp::Rvd<float> va, vb, vc;
            va = &a[i];
            vb = &b[i];
            vc = va + vb; // Expressive overloaded operator
            mipp::store(&c[i], vc.r);
        }

        for (size_t i = vec_limit; i < a.size(); i++) { // Clean scalar tail loop
            c[i] = a[i] + b[i];
        }
    }
    ```

👉 **[See how MIPP compares to Google Highway, xsimd, Eve, Auto-vectorization and more](user/why_mippv2.md#simd-wrappers-comparison)**

---

## Architectural Hierarchy

```
       +-------------------------------------------------------------------+
       |                        Application Code                           |
       +-------------------------------------------------------------------+
                                         |
         +-------------------------------+-------------------------------+
         |                               |                               |
  +--------------+              +------------------+           +-------------------+
  |  C Low-Level |              |   C++ Template   |           |    C++ Object     |
  |  Interface   |              |    Functions     |           |     Interface     |
  |  (mipp.h)    |              |    (mipp.hpp)    |           |   (mipp_obj.hpp)  |
  +--------------+              +------------------+           +-------------------+
         |                               |                               |
         +-------------------------------+-------------------------------+
                                         |
       +-------------------------------------------------------------------+
       |                 MIPP Multi-Level Fallback Engine                  |
       |  Level 0: Native Hardware Intrinsics                              |
       |  Level 1: ISA-Specific Intrinsics Emulation                       |
       |  Level 2: Generic Portable MIPP Emulation                         |
       |  Level 3: Transparent Scalar Loop Fallback                        |
       +-------------------------------------------------------------------+
                                         |
  +------------+------------+------------+------------+------------+------------+
  |    SSE     |    AVX     |  AVX-512   |    NEON    | SVE (WIP)  |    RVV     |
  |   (128b)   |   (256b)   |   (512b)   |   (128b)   | (Scalable) | (Scalable) |
  +------------+------------+------------+------------+------------+------------+
```

---

## Supported Instruction Sets & Types

### Instruction Set Architectures (ISAs)

| Architecture Family | Target Extensions | Hardware Vector Width |
| :--- | :--- | :--- |
| **x86 / x86-64** | SSE, SSE2, SSE3, SSSE3, SSE4.1, SSE4.2 | 128 bits |
| **x86 / x86-64** | AVX, AVX2, AVX2+FMA | 256 bits |
| **x86 / x86-64** | AVX-512F, AVX-512BW, AVX-512DQ | 512 bits |
| **ARM (AArch32 / AArch64)** | NEON (ARMv7, ARMv8-A) | 128 bits |
| **ARM (AArch64)** | SVE *(WIP)* | Fixed / Configurable compile-time vector length |
| **RISC-V** | RVV 1.0 | Fixed / Configurable VLEN ($\ge 128\text{ bits}$) |
| **Generic** | Scalar fallback | Configurable width |

### Supported Datatypes

MIPP supports 10 fundamental numeric data types across all vector abstractions:

- **Floating-Point**: `float64` (`double`), `float32` (`float`)
- **Signed Integer**: `int64` (`int64_t`), `int32` (`int32_t`), `int16` (`int16_t`), `int8` (`int8_t`)
- **Unsigned Integer**: `uint64` (`uint64_t`), `uint32` (`uint32_t`), `uint16` (`uint16_t`), `uint8` (`uint8_t`)

---

## Documentation Overview

- **[Why MIPPv2](user/why_mippv2.md)**: Architectural evolution, technical relevance, and comparison with other SIMD wrappers.
- **[Getting Started](user/getting_started.md)**: Header integration, compiler flags, and a **5-minute tutorial with complete loop & tail-loop handling**.
- **[Programming Model](user/programming_model.md)**: In-depth exploration of C99, C++ functional, and C++ object APIs.
- **[Vector Types & LMUL](user/vector_types_and_lmul.md)**: Vector representations, element counts (`mipp::N<T, LMUL>()`), and software/hardware register multiplier scaling.
- **[Masking Semantics](user/masking_semantics.md)**: Mask generation, mask conversion, and execution variants (`unmasked`, `mask`, `maskz`, `masks`).
- **[Implementation Levels](user/implementation_levels.md)**: The 4-level fallback engine explained from an application performance standpoint.
- **[Memory & Alignment](user/memory_and_alignment.md)**: Alignment constraints, load/store primitives, and gather/scatter memory access.
- **[API Reference](funcs_support/index.md)**: Complete mathematical descriptions, prototypes, and hardware matrices for every function.
- **[Hardware Support](isas_support/index.md)**: Architecture compatibility matrices and universal intersection capabilities.
- **[Developer Guide](developper/index.md)**: Code generator architecture, declarative JSON database schema, **templating DSL**, and contribution guide.
