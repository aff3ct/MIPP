# MyIntrinsics++ (MIPP)

<p align="center">
  <img src="docs/assets/images/mipp.jpg" alt="MIPP Banner" width="600"/>
</p>

<p align="center">
  <a href="https://github.com/aff3ct/mipp/actions/workflows/ci.yml"><img src="https://github.com/aff3ct/mipp/actions/workflows/ci.yml/badge.svg" alt="MIPP CI"/></a>
  <a href="https://aff3ct.github.io/MIPP/"><img src="https://img.shields.io/badge/docs-online-blue.svg" alt="Documentation"/></a>
  <a href="LICENSE"><img src="https://img.shields.io/badge/License-MIT-yellow.svg" alt="License: MIT"/></a>
  <img src="https://img.shields.io/badge/C%2B%2B-11%20%7C%2014%20%7C%2017%20%7C%2020%20%7C%2023-blue.svg" alt="C++ Standards"/>
  <img src="https://img.shields.io/badge/C-C99-blue.svg" alt="C99 Standard"/>
</p>

<p align="center">
  <img src="https://img.shields.io/badge/x86-SSE%20%7C%20AVX%20%7C%20AVX--512-orange.svg" alt="x86 Support"/>
  <img src="https://img.shields.io/badge/ARM-NEON%20%7C%20SVE%20(WIP)-red.svg" alt="ARM Support"/>
  <img src="https://img.shields.io/badge/RISC--V-RVV%201.0-green.svg" alt="RISC-V Support"/>
  <img src="https://img.shields.io/badge/Fallback-Scalar%20(100%25)-lightgrey.svg" alt="Scalar Fallback"/>
</p>

---

**MIPP** (*My Intrinsics Plus Plus*) is an open-source, header-only C and C++ SIMD wrapper library designed for cross-architecture data-parallel computing. It provides a portable, zero-overhead abstraction layer over hardware SIMD instruction sets, enabling developers to write high-performance vectorized algorithms once and compile them efficiently across **x86** (SSE, AVX, AVX-512), **ARM** (NEON, SVE in progress), and **RISC-V** (RVV 1.0) targets.

📖 **Official Documentation**: [https://aff3ct.github.io/MIPP/](https://aff3ct.github.io/MIPP/)

---

## 🚀 Key Highlights & Architectural Differentiators

```
       +-------------------------------------------------------------------+
       |                        Application Code                           |
       +---------------------------------+---------------------------------+
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
       +---------------------------------+---------------------------------+
       |                 MIPP Multi-Level Fallback Engine                  |
       |  Level 0: Native Hardware Intrinsics                              |
       |  Level 1: ISA-Specific Intrinsics Emulation                       |
       |  Level 2: Generic Portable MIPP Emulation                         |
       |  Level 3: Transparent Scalar Loop Fallback                        |
       +---------------------------------+---------------------------------+
                                         |
  +------------+------------+------------+------------+------------+------------+
  |    SSE     |    AVX     |  AVX-512   |    NEON    | SVE (WIP)  |    RVV     |
  |   (128b)   |   (256b)   |   (512b)   |   (128b)   | (Scalable) | (Scalable) |
  +------------+------------+------------+------------+------------+------------+
```

### 1. Unique Tri-Dialect API Surface

MIPP caters to different software engineering constraints through three distinct interfaces:

* **Pure C99 API (`<mipp.h>`)**: Explicit type suffixes (e.g., `mipp_add_float32(r0, r1)`). Ideal for pure C codebases, embedded systems, OS kernels, and foreign function interfaces (FFIs like Python `ctypes`/CFFI or Rust FFI).
* **C++ Functional Template API (`<mipp.hpp>`)**: Generic parameterized functions under namespace `mipp::` (e.g., `mipp::add<float>(r0, r1)`).
* **C++ Object API (`<mipp_obj.hpp>`)**: Expressive `mipp::Rvd<T, LMUL>` and `mipp::Rvm<T, LMUL>` wrapper classes featuring full arithmetic (`+`, `-`, `*`, `/`), bitwise, and relational operator overloading with zero abstraction overhead.

### 2. Deterministic 4-Tier Fallback Engine (100% Functional Completeness)

Every operation is guaranteed to compile and execute across all **10 supported numeric data types** (`float64`, `float32`, `int64`...`int8`, `uint64`...`uint8`) and all targets:

* **Level 0 (Native Optimal)**: 1-to-1 direct mapping to CPU hardware intrinsics (`_mm256_add_ps`, `vaddq_f32`, `__riscv_vfadd_vf_f32m1`).
* **Level 1 (Specific ISA Emulation)**: Emulates missing functionality using instructions available within the *same* ISA (e.g., integer multiplication via shifts and shuffles on early SSE).
* **Level 2 (Generic Portable Emulation)**: Composes complex operations from portable MIPP primitives (e.g., transcendental functions `sin`, `cos`, `exp`, or masked blend operations).
* **Level 3 (Transparent Scalar Loop Fallback)**: Automatically executes an element-wise scalar loop if no SIMD instruction exists.

### 3. Generalized Length Multiplier (LMUL $\in \{1, 2, 4, 8\}$)

* **Hardware Register Grouping (RVV 1.0)**: Maps directly to native hardware vector register groups (`vfloat32m2_t`, `vfloat32m4_t`).
* **Software Grouping (x86, ARM, Scalar)**: Emulates multi-register grouping via hierarchical structures that compilers unroll cleanly at compile time.

### 4. Explicit 4-Variant Masking Model

* `unmasked`: Standard unconditional vector execution.
* `mask`: Merges computed results with inactive elements of the destination register ($res_i = m_i \ ? \ f(a_i, b_i) : a_i$).
* `maskz`: Zeroes inactive elements ($res_i = m_i \ ? \ f(a_i, b_i) : 0$).
* `masks`: Preserves inactive elements from an explicit source vector ($res_i = m_i \ ? \ f(a_i, b_i) : src_i$).

### 5. Lightweight & Fast Compilation

* Pure header-only library with no runtime dependencies.
* Fully compatible with standard **C99** and **C++11** upwards.
* Avoids heavy template metaprogramming bloat, ensuring near-instantaneous project build times.

---

## 📊 Comparison with Existing SIMD Solutions

| Capability / Metric | [**MIPPv2**](https://github.com/aff3ct/mipp/tree/develop) | [**MIPPv1**](https://github.com/aff3ct/mipp/tree/master) | [**Google Highway**](https://github.com/google/highway) | [**xsimd**](https://github.com/xtensor-stack/xsimd) | [**Eve**](https://github.com/jfalcou/eve) | [**VCL**](https://github.com/vectorclass/version2) |
| :--- | :---: | :---: | :---: | :---: | :---: | :---: |
| **GitHub Stars** | [![Stars](https://img.shields.io/github/stars/aff3ct/mipp?style=flat&label=%E2%AD%90)](https://github.com/aff3ct/mipp) | [![Stars](https://img.shields.io/github/stars/aff3ct/mipp?style=flat&label=%E2%AD%90)](https://github.com/aff3ct/mipp) | [![Stars](https://img.shields.io/github/stars/google/highway?style=flat&label=%E2%AD%90)](https://github.com/google/highway) | [![Stars](https://img.shields.io/github/stars/xtensor-stack/xsimd?style=flat&label=%E2%AD%90)](https://github.com/xtensor-stack/xsimd) | [![Stars](https://img.shields.io/github/stars/jfalcou/eve?style=flat&label=%E2%AD%90)](https://github.com/jfalcou/eve) | [![Stars](https://img.shields.io/github/stars/vectorclass/version2?style=flat&label=%E2%AD%90)](https://github.com/vectorclass/version2) |
| **License** | [![License](https://img.shields.io/github/license/aff3ct/mipp?style=flat)](https://github.com/aff3ct/mipp/blob/develop/LICENSE) | [![License](https://img.shields.io/github/license/aff3ct/mipp?style=flat)](https://github.com/aff3ct/mipp/blob/master/LICENSE) | [![License](https://img.shields.io/badge/license-Apache_2.0_%7C_BSD--3-blue)](https://github.com/google/highway/blob/master/LICENSE) | [![License](https://img.shields.io/github/license/xtensor-stack/xsimd?style=flat)](https://github.com/xtensor-stack/xsimd/blob/master/LICENSE) | [![License](https://img.shields.io/github/license/jfalcou/eve?style=flat)](https://github.com/jfalcou/eve/blob/main/LICENSE.md) | [![License](https://img.shields.io/github/license/vectorclass/version2?style=flat)](https://github.com/vectorclass/version2/blob/master/LICENSE) |
| **Pure C99 API (C ABI)** | ✅ **Yes (`<mipp.h>`)** | ❌ No (C++ only) | ❌ No (C++ only) | ❌ No (C++ only) | ❌ No (C++ only) | ❌ No (C++ only) |
| **C++ Operator Overloading** | ✅ **Yes (`Rvd`)** | ✅ Yes (`Reg`) | ❌ No (Named functions) | ✅ Yes (`batch`) | ✅ Yes (`wide`) | ✅ Yes (`Vec...`) |
| **100% Fallback Guarantee** | ✅ **Levels 0 to 3** | ❌ Incomplete | ⚠️ Partial | ❌ Compile error | ❌ Compile error | ⚠️ x86 subsets only |
| **RISC-V (RVV) & ARM (SVE)** | ⚠️ **RVV (Fixed) / SVE (WIP)** | ❌ No | ✅ Scalable & Fixed | ⚠️ Fixed / WIP | ⚠️ SVE only (Fixed) | ❌ No (x86 only) |
| **Dispatch** | **Static** | **Static** | **Static & Dynamic** | **Static & Dynamic** | **Static** | **Static** *(Manual)* |
| **Language Standard Required** | **C99 / C++11** | C++11 | C++11 | C++17 | C++20 required | C++11 / C++17 |
| **Compilation Overhead** | ⚡ **Fast** | Medium | 🐢 Heavy | Medium | 🐌 Very heavy | ⚡ Fast |

👉 **[Read the comprehensive 10-column comparison matrix in the documentation](https://aff3ct.github.io/MIPP/user/why_mippv2/#simd-wrappers-comparison)**

---

## ⚡ Quick Start (60 Seconds)

### 1. Header-Only Integration

MIPP is completely header-only. Simply add the `include/` directory to your compiler's search path:

* `<mipp.h>`: For pure C99 codebases.
* `<mipp.hpp>`: For generic C++ template functional programming.
* `<mipp_obj.hpp>`: For expressive C++ vector object programming with operator overloading.

### 2. C++ Object API Example (with Tail-Loop Handling)

```cpp
#include <iostream>
#include <vector>
#include <mipp_obj.hpp>

void vector_add(const float* a, const float* b, float* c, size_t size) {
    constexpr int N = mipp::N<float>(); // Number of elements per SIMD register
    size_t vec_limit = size - (size % N);

    // 1. Vector Main Loop (Processes contiguous chunks of N elements)
    for (size_t i = 0; i < vec_limit; i += N) {
        mipp::Rvd<float> va(&a[i]);
        mipp::Rvd<float> vb(&b[i]);
        mipp::Rvd<float> vc = va + vb;
        vc.store(&c[i]);
    }

    // 2. Tail Loop (Handles remaining elements)
    for (size_t i = vec_limit; i < size; ++i) {
        c[i] = a[i] + b[i];
    }
}
```

### 3. Pure C99 API Example

```c
#include <stdio.h>
#include <mipp.h>

void vector_add_c(const float* a, const float* b, float* c, size_t size) {
    const int N = MIPP_N_FLOAT32;
    size_t vec_limit = size - (size % N);

    for (size_t i = 0; i < vec_limit; i += N) {
        rvd_float32_t va = mipp_load_float32(&a[i]);
        rvd_float32_t vb = mipp_load_float32(&b[i]);
        rvd_float32_t vc = mipp_add_float32(va, vb);
        mipp_store_float32(&c[i], vc);
    }

    for (size_t i = vec_limit; i < size; ++i) {
        c[i] = a[i] + b[i];
    }
}
```

### 4. Compilation Flags

MIPP automatically detects the target architecture via standard compiler preprocessor macros:

```bash
# x86-64 (AVX2 + FMA)
g++ -O3 -mavx2 -mfma -Iinclude main.cpp -o app

# x86-64 (AVX-512)
g++ -O3 -mavx512f -mavx512bw -mavx512dq -Iinclude main.cpp -o app

# ARMv8-A (NEON)
g++ -O3 -march=armv8-a+simd -Iinclude main.cpp -o app

# RISC-V (RVV 1.0)
riscv64-unknown-linux-gnu-g++ -O3 -march=rv64gcv_zvl256b -mrvv-vector-bits=zvl -Iinclude main.cpp -o app
```

👉 **[See the Complete Getting Started Tutorial & Optimization Guide](https://aff3ct.github.io/MIPP/user/getting_started/)**

---

## 📚 Official Documentation Hub

Explore the full documentation hosted at **[https://aff3ct.github.io/MIPP/](https://aff3ct.github.io/MIPP/)**:

* **User Guides**:
    * 📘 **[Why MIPPv2](https://aff3ct.github.io/MIPP/user/why_mippv2/)**: Evolution from MIPPv1, design goals, and comparative analysis.
    * 🚀 **[Getting Started](https://aff3ct.github.io/MIPP/user/getting_started/)**: Compiler flags, build setup, and tail-loop processing.
    * 💡 **[Programming Models](https://aff3ct.github.io/MIPP/user/programming_model/)**: Detailed guide to C99, C++ Functional, and C++ Object APIs.
    * 📐 **[Vector Types & LMUL](https://aff3ct.github.io/MIPP/user/vector_types_and_lmul/)**: Vector layout, register grouping, and element counting (`mipp::N<T>()`).
    * 🎭 **[Masking Semantics](https://aff3ct.github.io/MIPP/user/masking_semantics/)**: Unconditional, merging (`mask`), zeroing (`maskz`), and source-preserving (`masks`) executions.
    * 🛡️ **[Implementation Levels](https://aff3ct.github.io/MIPP/user/implementation_levels/)**: How the 4-tier fallback engine optimizes performance.
    * 💾 **[Memory & Alignment](https://aff3ct.github.io/MIPP/user/memory_and_alignment/)**: Alignment constraints, load/store primitives, and gather/scatter memory access.
* **API & Hardware References**:
    * 📖 **[API Reference Matrix](https://aff3ct.github.io/MIPP/funcs_support/)**: Mathematical definitions, prototypes, and hardware support for every function.
    * ⚙️ **[Hardware Support Matrix](https://aff3ct.github.io/MIPP/isas_support/)**: Complete ISA compatibility and instruction coverage.
* **Developer & Contribution**:
    * 🛠️ **[Developer Guide](https://aff3ct.github.io/MIPP/developper/)**: Generator architecture, declarative JSON database schema, and contribution steps.
    * 📝 **[Templating DSL](https://aff3ct.github.io/MIPP/developper/templating_dsl/)**: Jinja2-based domain-specific language for adding new SIMD instructions.

---

## 👥 Contributors & Institutional Support

MIPP is developed and maintained through collaborative research and engineering efforts supported by leading academic and industrial institutions:

<table>
  <tr>
    <td align="center" width="33%" valign="middle">
      <a href="https://www.sorbonne-universite.fr/" target="_blank">
        <img src="docs/assets/images/logos/sorbonne_universite.svg" alt="Sorbonne Université" height="60"/><br/><br/>
        <b>Sorbonne Université</b>
      </a>
      <br/>
      <sub>LIP6 Laboratory / Faculty of Science and Engineering</sub>
    </td>
    <td align="center" width="33%" valign="middle">
      <a href="https://www.ifpenergiesnouvelles.fr/" target="_blank">
        <img src="docs/assets/images/logos/ifpen.jpg" alt="IFP Energies nouvelles" height="60"/><br/><br/>
        <b>IFP Energies nouvelles</b>
      </a>
      <br/>
      <sub>Energy, Transport & High-Performance Computing Research</sub>
    </td>
    <td align="center" width="33%" valign="middle">
      <a href="https://www.inria.fr/" target="_blank">
        <img src="docs/assets/images/logos/inria.svg" alt="Inria" height="50"/><br/><br/>
        <b>Inria</b>
      </a>
      <br/>
      <sub>National Institute for Research in Digital Science and Technology</sub>
    </td>
  </tr>
</table>

---

## 🛠️ Code Generation & Local Development

MIPP headers, tests, and documentation are generated automatically via Python scripts driven by declarative JSON databases:

```bash
# 1. Install generator dependencies
pip install -r generator/requirements.txt

# 2. Generate C/C++ headers in include/
cd generator
./gen_mipp_headers.py --simd-ext sse avx avx512 rvv neon scalar

# 3. Generate unit tests in tests/src/
./gen_mipp_tests.py cpp --lmul 0 8 --ldiv 2 --mask-kind "unmasked" "mask" "maskz" "masks"

# 4. Generate documentation pages in docs/
./gen_mipp_docs.py

# 5. Serve documentation locally
cd ..
pip install -r docs/requirements.txt
mkdocs serve
```

---

## 📄 License

MIPP is licensed under the permissive **[MIT License](LICENSE)**. You are free to use, modify, and distribute MIPP in both open-source and proprietary commercial software.
