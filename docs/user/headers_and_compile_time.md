# Headers & Compile Time

MIPP is header-only, so every translation unit that includes it pays for parsing the headers it pulls in. MIPP lets you choose how much you include, from one umbrella header down to a single function for one masking variant and one LMUL.

---

## 1. Header Tree

```text
include/
├── mipp.h                         # C API: everything
├── mipp.hpp                       # C++ Functional API: everything
├── mipp_obj.hpp                   # C++ Object API: everything
└── mipp/
    ├── c/                         # C API
    │   ├── cat/<category>.h       #   one category (e.g. arithmetic.h)
    │   ├── fun/<function>.h       #   one function (e.g. add.h)
    │   ├── utils.h                #   allocation, alignment, dump
    │   └── transpose.h            #   transpositions
    ├── cpp/                       # C++ Functional API (same layout, .hpp, plus patterns.hpp)
    ├── obj/                       # C++ Object API (same layout, .hpp, plus patterns.hpp)
    └── internal/                  # implementation details: never include directly
```

The `cat/` and `fun/` directories exist for the three APIs. Categories are the ones listed in [Function Support](../funcs_support/index.md) (`arithmetic`, `comparison`, `load`, `store`, `math`, ...).

The umbrella headers also include `utils`, `transpose` and `patterns`, which the `cat/` and `fun/` headers do not include. With these headers, include them yourself when you use what they define:

- `utils.h` / `utils.hpp`: `mipp_malloc`, `mipp_free`, `MIPP_REQUIRED_ALIGNMENT`, `mipp::malloc`, `mipp::vector`, the dump functions (`mipp_dump_*`, `mipp::dump`) and, in the Object API, `operator<<` and `mipp::reduce`;
- `transpose.h` / `transpose.hpp`: the transpositions (see [Rearrangements](rearrangements.md#7-transpositions));
- `patterns.hpp` (C++17): `mipp::permute<P>` and `mipp::permute2<P>` with a compile-time pattern (see [Rearrangements](rearrangements.md#8-patterns-known-at-compile-time-c17)).

---

## 2. Three Inclusion Levels

| Level | Example | Contents | Available in |
| :--- | :--- | :--- | :--- |
| **Monolithic** | `#include <mipp.hpp>` | All functions, all masking variants, all LMULs | Every distribution |
| **Coarse** (per function or category) | `#include <mipp/cpp/fun/add.hpp>` | One function (or category), all variants, all LMULs | Every distribution |
| **Fine** (per variant and/or LMUL) | `#include <mipp/cpp/fun/m/m2/add.hpp>` | One function, one variant, one LMUL | Release archives, or headers generated with `--granularity fine` |

### 2.1. Fine-Grained Headers

Fine-grained headers split each function along two axes: the masking variant (`u`, `m`, `z`, `s`, see [Masking Semantics](masking_semantics.md)) and the LMUL (`m1`, `m2`, `m4`, `m8`, and `d2` where [half-vectors](vector_types_and_lmul.md#half-vectors) exist):

```text
include/mipp/obj/fun/
├── add.hpp              # coarse: all variants, all LMULs
├── m/add.hpp            # variant umbrella: masked add, all LMULs
├── m2/add.hpp           # LMUL umbrella: add with LMUL = 2, all variants
└── m/m2/add.hpp         # atom: masked add with LMUL = 2 only
```

The same layout exists for categories (`cat/m/m2/arithmetic.hpp`) and for the three APIs.

!!! warning "Include what you call"
    With fine-grained headers, a call only compiles if the matching granule is included. For example, `mipp::add<mipp::Z>(m, a, b)` requires the `z` granule (`z/add.hpp`, `z/m1/add.hpp`, or a coarser header). Several granules of the same function can be included in the same translation unit.

    The [scalar forms](scalar_forms.md) have their own headers, at every granularity: `mipp::add(a, 2.f)` needs `fun/add_vs.hpp`, `mipp::sub(2.f, a)` needs `fun/sub_sv.hpp`, `mipp::fmadd(a, 2.f, c)` needs `fun/fmadd_vsv.hpp`. `fun/add.hpp` does not provide them; the category headers (`cat/arithmetic.hpp`) and the umbrella headers do.

---

## 3. Measured Impact

Compile time (wall clock, median of 2 runs) and compiler peak memory (RSS) for a translation unit containing **128 SIMD kernels**:

| API | Inclusion | Clang: time | Clang: peak RSS | GCC: time | GCC: peak RSS |
| :--- | :--- | ---: | ---: | ---: | ---: |
| C | Monolithic | 0.87 s | 155 MB | 0.90 s | 308 MB |
| | Coarse | 0.43 s | 106 MB | 0.62 s | 173 MB |
| | Fine | **0.23 s** | **80 MB** | **0.48 s** | **94 MB** |
| C++ Functional | Monolithic | 2.03 s | 326 MB | 2.32 s | 492 MB |
| | Coarse | 1.11 s | 215 MB | 1.37 s | 328 MB |
| | Fine | **0.67 s** | **157 MB** | **0.81 s** | **187 MB** |
| C++ Object | Monolithic | 2.03 s | 326 MB | 2.35 s | 500 MB |
| | Coarse | 1.14 s | 216 MB | 1.42 s | 340 MB |
| | Fine | **0.79 s** | **157 MB** | **0.89 s** | **197 MB** |
| *Raw intrinsics (reference)* | — | 0.16 s | 65 MB | 0.35 s | 68 MB |

Going from monolithic to fine-grained headers makes compilation **2× to 4× faster** and divides peak memory by **2 to 3**.

!!! note "Measurement setup"
    Apple M1 Pro (ARM NEON, LMUL = 1), AppleClang 21 and GCC 16, `-O3`, `-std=c99` for the C API (the C API targets C11 for `mipp_malloc`, which calls `aligned_alloc`: the libc of macOS also declares it in C99) and `-std=c++20` for the C++ APIs, October 2026. Kernels cycle over `float`, `double`, `int32_t` and `int64_t`, half of them using masked operations.

---

## 4. Which Level Should I Use?

| Situation | Recommendation |
| :--- | :--- |
| Prototyping, tests, small programs | Monolithic: one `#include`, nothing to maintain |
| Libraries and applications with many translation units | Coarse: include each function you use |
| Large builds, CI time or memory constrained, highly parallel builds | Fine: include only the variants and LMULs you call |

Switching level never changes the generated code: only the amount of parsing work changes.
