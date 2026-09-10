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
     |    SSE    |    AVX    | AVX-512  |   NEON   |    SVE    |    RVV    |
     +-----------+-----------+----------+----------+-----------+-----------+
```

### 2.1. Tri-Dialect API Surface
MIPPv2 caters to different software engineering constraints through three distinct interfaces:

1. **C99 API (`<mipp.h>`)**: Pure C99 type-explicit functions (`mipp_add_float32(r0, r1)`). Perfect for systems programming, C libraries, Linux kernel modules, and foreign function interfaces (Python ctypes/CFFI, Rust FFI).
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

| Capability / Feature | **MIPPv2** | **MIPPv1** | **Google Highway** | **xsimd** | **Eve** | **nSIMD** | **Vc** | **Raw Intrinsics** | **Auto-Vectorization** (`-O3`) |
| :--- | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| **Pure C99 API (C ABI)** | ✅ **Yes (`<mipp.h>`)** | ❌ No (C++ only) | ❌ No (C++ only) | ❌ No (C++ only) | ❌ No (C++ only) | ✅ Yes (`nsimd.h`) | ❌ No (C++ only) | ⚠️ Vendor specific | ⚠️ N/A |
| **C++ Operator Overloading** | ✅ **Yes (`Rvd`)** | ✅ Yes (`Reg`) | ❌ No (Named functions) | ✅ Yes (`batch`) | ✅ Yes (`wide`) | ✅ Yes (`pack`) | ✅ Yes (`Vector`) | ❌ No | ⚠️ N/A |
| **100% Fallback Guarantee** | ✅ **Levels 0 to 3** | ❌ Incomplete (Ad-hoc) | ⚠️ Partial emulations | ❌ Compile error | ❌ Compile error | ⚠️ Macro CPU fallback | ⚠️ Partial scalar | ❌ Compile error | ❌ Silent failure |
| **RISC-V Vector 1.0 (RVV)** | ⚠️ **Fixed-width only** | ❌ No | ✅ Scalable & Fixed | ⚠️ Fixed-width / WIP | ❌ No | ⚠️ Fixed-width (Draft) | ❌ No | ⚠️ Built-ins (VLA/Fixed) | ⚠️ Unpredictable |
| **ARM SVE Support** | ⚠️ **Fixed-width only** | ❌ No | ✅ Scalable & Fixed | ⚠️ Fixed-width / WIP | ⚠️ Fixed-width only | ⚠️ Fixed-width only | ❌ No | ⚠️ ACLE (VLA/Fixed) | ⚠️ Unpredictable |
| **Runtime Scalable Vectors (VLA)** | ❌ No (Fixed-width) | ❌ No | ✅ **Yes (True VLA)** | ❌ No | ❌ No | ❌ No | ❌ No | ⚠️ Manual stripmining | ⚠️ Compiler-dependent |
| **Generalized LMUL ($1,2,4,8$)** | ✅ **Yes** | ❌ No ($1$ only) | ✅ Yes (`ScalableTag`) | ❌ No | ❌ No | ❌ No | ❌ No | ❌ No (RVV only) | ❌ No |
| **C++ Standard Required** | **C++11** (or C99) | C++11 | C++11 | C++17 | C++20 required | C98 / C++11 | C++11 / C++14 | C99 / C++11 | C99 / C++11 |
| **Compilation Overhead** | ⚡ **Fast** (Simple inlines) | Medium (Deep templates) | 🐢 Heavy templates | Medium | 🐌 Very heavy | 🐌 Heavy (Macro bloat) | Medium / Heavy | ⚡ Very fast | ⚡ Zero lib overhead |
| **Assembly Determinism** | 🎯 **100% Explicit** | 🎯 Explicit | 🎯 Explicit | 🎯 Explicit | 🎯 Explicit | 🎯 Explicit | 🎯 Explicit | 🎯 100% Explicit | 🎲 Heuristic-driven |

### Key Differentiators for MIPPv2:

1.  **Seamless Dual-Ecosystem: Clean C99 ABI & Modern C++**:

    Most modern wrappers (Google Highway, xsimd, Eve, Vc) are exclusively designed for C++ (often requiring C++17 or even C++20). While nSIMD provides a C interface, it relies on heavy macro preprocessing. MIPPv2 provides clean, inlined, type-safe C99 functions without macro obfuscation, making it effortless to integrate into pure C codebases, Linux kernel modules, or foreign-function interfaces (FFI for Python, Julia, Rust).

2.  **Expressive Syntax without Sacrificing Portability**:

    To support runtime-variable vectors (VLA), Google Highway explicitly avoids C++ operator overloading (`a + b`), requiring explicit named functions (`hn::Add(d, a, b)`). MIPPv2 provides the best of both worlds for fixed-width workflows: functional C99 / C++ APIs for low-level control, plus full operator overloading (`mipp::Rvd`) that works consistently across all target architectures.

3.  **Never Breaks Compilation (Deterministic 4-Tier Fallbacks)**:

    In libraries like xsimd, Eve, or Vc, calling an operation not natively supported by the target CPU produces a hard compilation failure. MIPP automatically falls back through an ISA-specific emulation (Level 1), a generic MIPP emulation (Level 2), or a scalar loop (Level 3), guaranteeing complete functional coverage across all 10 supported data types.

4.  **Pragmatic Fixed-Width Design for RVV & SVE**:

    While Google Highway is built from the ground up for runtime Variable-Length Arrays (VLA), MIPPv2 intentionally chooses a compile-time fixed-width model (`-mrvv-vector-bits` / `-msve-vector-bits`). This deliberate engineering trade-off enables compile-time known sizes (`MIPP_N`), straightforward C-struct memory layouts, and standard C++ operator overloading without the runtime overhead of dynamic stripmining.

5.  **Predictable Performance vs. Compiler Auto-Vectorization**:

    While compilers have made great progress with `-O3 -ftree-vectorize`, auto-vectorization remains fragile: subtle changes in loop bounds, pointer aliasing, or compiler version updates can cause loops to silently de-vectorize. MIPP guarantees deterministic, explicit SIMD assembly.
