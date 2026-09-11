# MIPP: My Intrinsics Plus Plus

**MIPP** is an open-source, header-only C and C++ SIMD wrapper library designed for cross-architecture data-parallel computing. It provides a portable, zero-overhead abstraction layer over hardware SIMD instruction sets, enabling developers to write high-performance vectorized algorithms once and compile them efficiently across x86 (SSE, AVX, AVX-512), ARM (NEON, SVE in progress) and RISC-V (RVV 1.0) targets.

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

## Why Choose MIPP?

Unlike other SIMD libraries that force a modern C++ compiler or rely on unpredictable compiler auto-vectorization, MIPP is built with three core differentiators:

1. **Unique Tri-Dialect API**:

    - **Pure C99 API** (`<mipp.h>`): Explicit type suffixes (`mipp_add_float32`) ideal for pure C codebases, embedded systems, and OS kernels.
    - **C++ Template Functional API** (`<mipp.hpp>`): Type-parameterized functions under namespace `mipp::` (`mipp::add<float>(r0, r1)`).
    - **C++ Object API** (`<mipp_obj.hpp>`): Expressive operator overloading (`vc = va + vb`) with zero overhead.

2. **100% Functional Fallback Guarantee**:

    - Every operation is guaranteed to compile and execute on all supported data types and architectures through a 4-tier fallback engine (from native intrinsics down to transparent scalar loops). No cryptic compiler errors or missing intrinsic failures.

3. **Lightweight & Fast Compilation**:

    - Header-only, fully inlined, compatible with C99 and C++11 upwards, avoiding heavy template metaprogramming that slows down build times.

👉 **[See how MIPP compares to Google Highway, xsimd, Eve, and Auto-vectorization](user/why_mippv2.md#simd-wrappers-comparison)**

---

## Supported Instruction Sets & Types

### Instruction Set Architectures (ISAs)

| Architecture Family | Target Extensions | Hardware Vector Width |
| :--- | :--- | :--- |
| **x86 / x86-64** | SSE, SSE2, SSE3, SSSE3, SSE4.1, SSE4.2 | 128 bits |
| **x86 / x86-64** | AVX, AVX2, AVX2+FMA | 256 bits |
| **x86 / x86-64** | AVX-512F, AVX-512BW, AVX-512DQ | 512 bits |
| **ARM (AArch32 / AArch64)** | NEON (ARMv7, ARMv8-A) | 128 bits |
| **ARM (AArch64)** | SVE *(WIP / in progress)* | Fixed / Configurable compile-time vector length |
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
