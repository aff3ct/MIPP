# MIPP: My Intrinsics Plus Plus

**MIPP** is an open-source, header-only C and C++ SIMD wrapper library designed for cross-architecture data-parallel computing. It provides a portable, zero-overhead abstraction layer over hardware SIMD instruction sets, enabling developers to write high-performance vectorized algorithms once and compile them efficiently across x86 (SSE, AVX, AVX-512), ARM (NEON, SVE) and RISC-V (RVV) targets.

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
  |    SSE     |    AVX     |  AVX-512   |    NEON    |    SVE     |    RVV     |
  |   (128b)   |   (256b)   |   (512b)   |   (128b)   | (Scalable) | (Scalable) |
  +------------+------------+------------+------------+------------+------------+
```

---

## Key Technical Features

- **Multi-Dialect API**:
  - **C Low-Level API** (`<mipp.h>`): Pure C99 type-explicit intrinsic wrappers.
  - **C++ Template API** (`<mipp.hpp>`): Type-safe functional abstractions under namespace `mipp::`.
  - **C++ Object API** (`<mipp_obj.hpp>`): Expressive `mipp::Rvd<T, LMUL>` and `mipp::Rvm<T, LMUL>` classes with overloaded arithmetic, bitwise, and comparison operators.
- **Unified 4-Tier Fallback Hierarchy**: Guarantees functional completeness across all datatypes and architectures without undefined behavior or compilation errors.
- **Generalized Length Multiplier (LMUL)**: Native register grouping on RISC-V Vector (RVV 1.0) and recursive binary software structures on fixed SIMD ISAs ($\text{LMUL} \in \{1, 2, 4, 8\}$).
- **First-Class Masking Semantics**: Uniform support for unconditional operations, masked updates (`mask`), zero-masking (`maskz`), and source-preserving masking (`masks`).
- **Zero Overhead**: Inlined at compile time to map directly to hardware machine instructions without pointer indirection, dynamic dispatch, or virtual table lookups.

---

## Supported Instruction Sets & Types

### Instruction Set Architectures (ISAs)

| Architecture Family | Target Extensions | Hardware Vector Width |
| :--- | :--- | :--- |
| **x86 / x86-64** | SSE, SSE2, SSE3, SSSE3, SSE4.1, SSE4.2 | 128 bits |
| **x86 / x86-64** | AVX, AVX2, AVX2+FMA | 256 bits |
| **x86 / x86-64** | AVX-512F, AVX-512BW, AVX-512DQ | 512 bits |
| **ARM (AArch32 / AArch64)** | NEON (ARMv7, ARMv8-A) | 128 bits |
| **ARM (AArch64)** | SVE | Fixed / Configurable vector length |
| **RISC-V** | RVV 1.0 | Fixed / Configurable VLEN ($\ge 128\text{ bits}$) |
| **Generic** | Scalar fallback | Configurable |

### Supported Datatypes

MIPP supports 10 fundamental numeric data types across all vector abstractions:

- **Floating-Point**: `float64` (`double`), `float32` (`float`)
- **Signed Integer**: `int64` (`int64_t`), `int32` (`int32_t`), `int16` (`int16_t`), `int8` (`int8_t`)
- **Unsigned Integer**: `uint64` (`uint64_t`), `uint32` (`uint32_t`), `uint16` (`uint16_t`), `uint8` (`uint8_t`)

---

## Documentation Roadmap

- **[Why MIPPv2](user/why_mippv2.md)**: Architectural evolution, technical relevance, and comparison with compiler auto-vectorization and vendor abstractions.
- **[Getting Started](user/getting_started.md)**: Header integration, compiler flags, target ISA selection, and quick-start examples.
- **[Programming Model](user/programming_model.md)**: In-depth exploration of C, C++ functional, and C++ object APIs.
- **[Vector Types & LMUL](user/vector_types_and_lmul.md)**: Vector representations, element counts (`mipp::N<T, LMUL>()`), and software/hardware register multiplier scaling.
- **[Masking Semantics](user/masking_semantics.md)**: Mask generation, mask conversion, and execution variants (`unmasked`, `mask`, `maskz`, `masks`).
- **[Implementation Levels](user/implementation_levels.md)**: The 4-level fallback engine and performance considerations.
- **[Memory & Alignment](user/memory_and_alignment.md)**: Alignment constraints, load/store primitives, and gather/scatter memory access.
- **[Developer Guide](developper/generator/simd_ext/simd_ext.md)**: Internal generator architecture, JSON database schema, and test generation workflows.
