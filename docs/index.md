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
    <a href="explorer/" class="mipp-btn mipp-btn-secondary">
      <span>🔍</span> API Explorer
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

<div class="mipp-home-grid">
  <div class="mipp-home-card">
    <div class="mipp-home-card-header">
      <div class="mipp-home-card-icon">🚀</div>
      <h3 class="mipp-home-card-title">Next-Gen ISAs & Scalable Vectors</h3>
    </div>
    <p class="mipp-home-card-desc">
      Native support for <b>AVX-512</b>, <b>ARM SVE</b>, and <b>RISC-V RVV</b>. Advanced features include register grouping (<b>LMUL/LDIV</b> up to x8/d2), full vector masking, and an <b>auto-generated</b>, <b>future-proof</b> codebase. Easily <b>extensible to new ISAs</b>.
    </p>
  </div>
  <div class="mipp-home-card">
    <div class="mipp-home-card-header">
      <div class="mipp-home-card-icon">🎯</div>
      <h3 class="mipp-home-card-title">Three APIs, One Engine</h3>
    </div>
    <p class="mipp-home-card-desc">
      Choose your paradigm: the <b>C API</b> (<code>mipp_add_float32</code>, C99) for <b>OS kernels and embedded targets</b>; the generic <b>C++ Functional API</b> (<code>mipp::add(va, vb)</code>) for <b>HPC algorithms</b>; or the expressive <b>C++ Object API</b> (<code>va + vb</code>) with full <b>operator overloading</b>.
    </p>
  </div>
  <div class="mipp-home-card">
    <div class="mipp-home-card-header">
      <div class="mipp-home-card-icon">🛡️</div>
      <h3 class="mipp-home-card-title">100% Fallback Guarantee</h3>
    </div>
    <p class="mipp-home-card-desc">
      Guaranteed completeness across all <b>10 datatypes</b> through a deterministic <b>4-level fallback engine</b>: <b>L0</b> (Native Hardware) &rarr; <b>L1</b> (Dedicated Emulation) &rarr; <b>L2</b> (Generic Emulation) &rarr; <b>L3</b> (Scalar Fallback). <b>No missing-instruction compilation errors</b>.
    </p>
  </div>
  <div class="mipp-home-card">
    <div class="mipp-home-card-header">
      <div class="mipp-home-card-icon">⚡</div>
      <h3 class="mipp-home-card-title">Zero-Overhead & Header-Only</h3>
    </div>
    <p class="mipp-home-card-desc">
      <b>No compilation</b>, <b>no external dependencies</b>, and <b>no linking</b> required. Simply include <code>&lt;mipp.h&gt;</code>, <code>&lt;mipp.hpp&gt;</code>, or <code>&lt;mipp_obj.hpp&gt;</code> into your include path: code inlines directly into bare-metal assembly with <b>zero runtime penalty</b>.
    </p>
  </div>
</div>

<p style="text-align: center; margin-top: 1.5rem; margin-bottom: 2rem;">
  👉 <b><a href="user/why_mippv2/#3-comparison-with-existing-simd-solutions">See how MIPP compares to Google Highway, xsimd, Eve, and auto-vectorization</a></b>
</p>

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

- **Floating-Point**: `float32_t`, `float64_t`
- **Signed Integer**: `int8_t`, `int16_t`, `int32_t`, `int64_t`
- **Unsigned Integer**: `uint8_t`, `uint16_t`, `uint32_t`, `uint64_t`

---

## Documentation Overview

- **[Why MIPPv2](user/why_mippv2.md)**: Architectural evolution, technical relevance, and comparison with other SIMD wrappers (Highway, xsimd, Eve).
- **[Getting Started](user/getting_started.md)**: Header integration, compiler flags, and a **5-minute tutorial across the C, C++ Functional, and C++ Object APIs**.
- **[Programming Model](user/programming_model.md)**: In-depth exploration of the C, C++ Functional, and C++ Object APIs.
- **[Vector Types & LMUL](user/vector_types_and_lmul.md)**: Vector representations, element counts (`mipp::N<T, LMUL>()`), and software/hardware register multiplier scaling.
- **[Masking Semantics](user/masking_semantics.md)**: Mask generation, mask conversion, and execution variants (`unmasked`, `mask`, `maskz`, `masks`).
- **[Implementation Levels](user/implementation_levels.md)**: The 4-level fallback engine explained from an application performance standpoint.
- **[Memory & Alignment](user/memory_and_alignment.md)**: Alignment constraints, load/store primitives, and gather/scatter memory access.
- **[API Explorer](explorer/index.md)**: Interactive catalog with instant search, reverse vendor intrinsic lookup, and switching between the three APIs.
- **[Specifications](funcs_support/index.md)**: Complete function prototypes, mathematical descriptions, and target ISA capability matrices.
- **[Developer Guide](developer/index.md)**: Code generator architecture, declarative JSON database schema, **templating DSL**, and contribution guide.
