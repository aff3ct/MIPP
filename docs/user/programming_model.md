# Programming Model & APIs

MIPP provides three distinct API layers built on top of a unified code generation engine:

1. **C API** (`<mipp.h>`): Explicit type-suffixed functions and plain C structs.
2. **C++ Functional API** (`<mipp.hpp>`): Type-parameterized template functions under namespace `mipp::`.
3. **C++ Object API** (`<mipp_obj.hpp>`): Class wrappers (`mipp::Rvd<T, LMUL>`, `mipp::Rvm<T, LMUL>`) with arithmetic and relational operator overloading.

All three APIs share the same zero-overhead inlined execution path and map to identical machine instructions.

---

## 1. Headers

Each API has an umbrella header (`<mipp.h>`, `<mipp.hpp>`, `<mipp_obj.hpp>`) and finer headers under `<mipp/c/>`, `<mipp/cpp/>` and `<mipp/obj/>` that include a single category, function, masking variant or LMUL. The header tree, the available granularities and their effect on compile time are described in [Headers & Compile Time](headers_and_compile_time.md).

---

## 2. C API (`<mipp.h>`)

The C API provides explicit, type-safe C99 function identifiers and vector types for every `(operation, datatype, lmul, mask_variant)` combination.

### 2.1. Naming Convention
```text
mipp_[func]_[datatype][_mask_variant][_lmul]
```

When operating at standard vector length ($\text{LMUL}=1$), the `_m1` suffix is optional: functions without the suffix (e.g., `mipp_add_float32`) are direct aliases to their `_m1` counterparts (`mipp_add_float32_m1`).

- **Standard ($\text{LMUL}=1$, unmasked)**: `mipp_add_float32(r0, r1)` or `mipp_add_float32_m1(r0, r1)`
- **Multi-Register ($\text{LMUL}=2, 4, 8$)**: `mipp_add_float32_m2(r0, r1)`, `mipp_add_float32_m4(r0, r1)`
- **Masked ($\text{LMUL}=1$)**: `mipp_add_float32_mask(m0, r0, r1)` or `mipp_add_float32_mask_m1(m0, r0, r1)`
- **Zero-Masked**: `mipp_add_float32_maskz(m0, r0, r1)` or `mipp_add_float32_maskz_m1(m0, r0, r1)`
- **Source-Masked**: `mipp_add_float32_masks(m0, rsrc, r0, r1)` or `mipp_add_float32_masks_m1(m0, rsrc, r0, r1)`
- **Masked + Multi-Register**: `mipp_add_float32_mask_m2(m0, r0, r1)`

### 2.2. Vector & Mask Datatypes (`rvd` and `rvm`)
MIPP defines distinct data register (`rvd`) and mask register (`rvm`) types for each of the 10 supported data types across all LMUL configurations:

| Category | Type Suffix / Format | Concrete Examples | Description |
| :--- | :--- | :--- | :--- |
| **Standard Data Vector** | `rvd_[type]_t` / `rvd_[type]_m1_t` | `rvd_float32_t`, `rvd_int32_m1_t` | Single hardware vector register ($\text{LMUL}=1$). |
| **Multi-Register Data** | `rvd_[type]_m[2|4|8]_t` | `rvd_float32_m2_t`, `rvd_float32_m4_t` | Group of $2\times, 4\times, 8\times$ vector registers. |
| **Standard Mask Vector** | `rvm_[type]_t` / `rvm_[type]_m1_t` | `rvm_float32_t`, `rvm_int32_m1_t` | Single mask/predicate register ($\text{LMUL}=1$). |
| **Multi-Register Mask** | `rvm_[type]_m[2|4|8]_t` | `rvm_float32_m2_t`, `rvm_float32_m4_t` | Group of $2\times, 4\times, 8\times$ mask registers. |

Multi-register types (`m2`, `m4`, `m8`) map directly to native vector register groups on RVV 1.0, or to hierarchical zero-overhead structures on fixed-width ISAs. See [Vector Types & LMUL](vector_types_and_lmul.md) for full structural details and memory layouts.

### 2.3. Vector Capacity Macros
Predefined compile-time constants provide the number of elements per vector type:

- `MIPP_N_FLOAT32` or `MIPP_N_FLOAT32_M1`: Number of `float` elements in an $\text{LMUL}=1$ vector.
- `MIPP_N_FLOAT32_M2`, `MIPP_N_FLOAT32_M4`, `MIPP_N_FLOAT32_M8`: Multiplied element capacities.
- Equivalent macros exist for all 10 types (`MIPP_N_INT32`, `MIPP_N_FLOAT64`, `MIPP_N_UINT8`, etc.).

---

## 3. C++ Functional API (`<mipp.hpp>`)

The C++ Functional API parameterizes operations over the element type `T`, an optional register multiplier `LMUL` (defaults to `1`), and an optional target instruction set `ISA_TYPE` (defaults to `mipp::DEFAULT_ISA`).

### 3.1. Template Parameter Domains

| Parameter | Domain / Supported Values | Description & Constraints |
| :--- | :--- | :--- |
| `typename T` | `float`, `double`, `int8_t`, `int16_t`, `int32_t`, `int64_t`, `uint8_t`, `uint16_t`, `uint32_t`, `uint64_t` | 10 standard numeric datatypes supported across all operations. |
| `int LMUL` | `1, 2, 4, 8` (integer multipliers) and `-2` for [half-vectors](vector_types_and_lmul.md#half-vectors) (`d2`, AVX / AVX-512 / RVV only) | Vector length multiplier (register grouping, or half-vector). Defaults to `1`. See [Vector Types & LMUL](vector_types_and_lmul.md). |
| `mipp::ISA ISA_TYPE` | `mipp::ISA::SCALAR`, `mipp::ISA::SSE`, `mipp::ISA::AVX`, `mipp::ISA::AVX512`, `mipp::ISA::NEON`, `mipp::ISA::SVE`, `mipp::ISA::RVV` | Target instruction set architecture. Defaults to `mipp::DEFAULT_ISA`. |

### 3.2. Types & Function Signatures
- **Data Vector**: `mipp::rvd<typename T, int LMUL = 1, mipp::ISA ISA_TYPE = mipp::DEFAULT_ISA>`
- **Mask Vector**: `mipp::rvm<typename T, int LMUL = 1, mipp::ISA ISA_TYPE = mipp::DEFAULT_ISA>`
- **Capacity Query**: `mipp::N<typename T, int LMUL = 1, mipp::ISA ISA_TYPE = mipp::DEFAULT_ISA>()`
- **Memory Alignment Query**: `mipp::req_alignment<mipp::ISA ISA_TYPE = mipp::DEFAULT_ISA>()`

### 3.3. `DEFAULT_ISA` Selection Priority
At compile time, `mipp::DEFAULT_ISA` automatically resolves to the highest hardware instruction set extension enabled by compiler flags:

- **x86 / x86-64**: `AVX-512` > `AVX2 / AVX` > `SSE`
- **ARM**: `SVE` > `NEON`
- **RISC-V**: `RVV`
- **Scalar**: Configured as `DEFAULT_ISA` when compiling with `-DMIPP_SCALAR`. By default, scalar registers match the bitwidth of the highest detected host ISA (e.g. 256 bits on an AVX host, 128 bits on NEON/SSE). The bitwidth can be explicitly overridden at compile time via `-DMIPP_SCALAR_SIZE=[bits]` (e.g. `-DMIPP_SCALAR_SIZE=256`).

### 3.4. Explicit Architecture Selection
The third template parameter `ISA_TYPE` defaults to `mipp::DEFAULT_ISA`, which is the only value that should be used in portable code.

!!! warning "Portability Scope of `ISA_TYPE`"
    Explicitly hardcoding a specific hardware instruction set (such as `mipp::ISA::SSE`, `mipp::ISA::AVX`, `mipp::ISA::NEON`, or `mipp::ISA::RVV`) is **non-portable by design**: the code will only compile on toolchains and targets that provide that specific ISA's intrinsics and register sets. Always rely on the default `mipp::DEFAULT_ISA` in application code.

### 3.5. Template Deduction & `auto` Type Inference
When operations take vector arguments, the compiler automatically deduces `T`, `LMUL`, and `ISA_TYPE`. Using the `auto` keyword eliminates verbose vector type declarations:

```cpp
auto a = mipp::load<float>(ptr_a); // Deduced as mipp::rvd<float, 1, DEFAULT_ISA>
auto b = mipp::load<float>(ptr_b);

// Automatically deduces T=float, LMUL=1, and ISA_TYPE=DEFAULT_ISA:
auto c = mipp::add(a, b); 
```

For functions without vector arguments, explicit template parameters are supplied:
```cpp
auto zeroes = mipp::set0<double, 2>();       // mipp::rvd<double, 2>
auto scalar_val = mipp::set1<int32_t>(42);   // mipp::rvd<int32_t, 1>
```

### 3.6. Masked Operations
Masked operations take the variant as first template argument (`mipp::M`, `mipp::Z` or `mipp::S`). Because `mipp::rvd<T, LMUL>` is an alias to an internal type trait, `T` cannot be deduced from the arguments and must be given explicitly (plus `LMUL` when it is not `1`):

```cpp
auto c = mipp::add<mipp::M, float>(m, a, b); // res[i] = m[i] ? a[i] + b[i] : a[i]
```

The four variants, their semantics and the syntax in each API are described in [Masking Semantics](masking_semantics.md).

---

## 4. C++ Object API (`<mipp_obj.hpp>`)

The Object API encapsulates raw SIMD registers and predicates inside high-level C++ classes:
- `mipp::Rvd<T, LMUL>` for numeric data vectors.
- `mipp::Rvm<T, LMUL>` for boolean mask vectors.

### 4.1. Class Structure & Constructors

```cpp
template <typename T, int LMUL = 1>
struct Rvd {
    rvd<T, LMUL> r; // Underlying low-level SIMD register

    static constexpr int N(); // Number of elements (mipp::N<T, LMUL>())

    // Constructors
    Rvd() = default;
    Rvd(rvd<T, LMUL> r); // Wraps a low-level rvd register
    Rvd(const T val);    // Broadcasts a scalar (mipp::set1)
    Rvd(const T* data);  // Loads from memory, no alignment requirement (mipp::loadu)

    // Implicit conversion to the low-level register (interoperability with the C++ Functional API)
    operator rvd<T, LMUL>() const;

    // Element access
    T operator[](const size_t index) const; // Reads one element (mipp::get)
};

template <typename T, int LMUL = 1>
struct Rvm {
    rvm<T, LMUL> m; // Underlying low-level mask register

    Rvm() = default;
    Rvm(rvm<T, LMUL> m);       // Wraps a low-level rvm register
    Rvm(const bool val);       // All lanes active or inactive (mipp::set1_k)
    Rvm(const int32_t vals[]); // Per-lane initialization (mipp::set_k)

    operator rvm<T, LMUL>() const;   // Implicit conversion to the low-level mask
    bool operator[](const size_t index) const; // Reads one lane (mipp::get)
};
```

### 4.2. Overloaded Operators Reference

The C++ Object API provides an extensive set of operator overloads for both data vectors (`Rvd`) and mask vectors (`Rvm`):

| Operation Category | Supported Operators | Operands | Return Type |
| :--- | :--- | :--- | :--- |
| **Arithmetic** | `+`, `-`, `*`, `/`, unary `-` | `Rvd<T>`, `Rvd<T>` | `Rvd<T>` |
| **Compound Assignment** | `+=`, `-=`, `*=`, `/=`, `&=`, `\|=`, `^=` | `Rvd<T>`, `Rvd<T>` | `Rvd<T>&` |
| **Bitwise & Shifts** | `&`, `\|`, `^`, `~`, `<<`, `>>` | `Rvd<T>`, `Rvd<T>` / `int` | `Rvd<T>` |
| **Relational / Comparison** | `==`, `!=`, `<`, `<=`, `>`, `>=` | `Rvd<T>`, `Rvd<T>` | `Rvm<T>` *(Mask)* |
| **Mask Logic & Inversion** | `&`, `\|`, `^`, `~` | `Rvm<T>`, `Rvm<T>` | `Rvm<T>` |

### 4.3. Free Functions in Namespace `mipp::`

Every MIPP SIMD operation is exposed as a free function under `namespace mipp::` that directly accepts `Rvd` and `Rvm` instances:

```cpp
auto a = mipp::Rvd<float>(ptr_a);
auto b = mipp::Rvd<float>(ptr_b);
auto c = mipp::Rvd<float>(ptr_c);

// Free functions on Rvd:
auto res_fma = mipp::fmadd(a, b, c); // Fused multiply-add
auto res_abs = mipp::abs(a);         // Absolute value
auto res_min = mipp::min(a, b);      // Element-wise minimum
auto res_red = mipp::hadd(a);        // Horizontal sum (returns scalar float)

// Store directly using free function:
mipp::store(ptr_out, res_fma);
```

### 4.4. Masked Operations
With `Rvm` and `Rvd` objects, the compiler deduces `T` and `LMUL`: only the variant is needed.

```cpp
mipp::Rvm<float> m = (a > b);
auto c = mipp::add<mipp::M>(m, a, b); // res[i] = m[i] ? a[i] + b[i] : a[i]
```

See [Masking Semantics](masking_semantics.md) for the four variants.


### 4.5. Idiomatic Coding Guidelines

1. **Prefer Operator Overloads**: When an operator exists (`a + b`, `a * b`, `a == b`, `m1 & m2`), use it over named function calls for maximum readability.
2. **Use Free Functions**: For non-operator routines (e.g. `mipp::fmadd`, `mipp::sqrt`, `mipp::min`, `mipp::store`), use free functions under `namespace mipp::`.
3. **No Member Syntax**: Operations are not exposed as member functions (there is no `a.add(b)`); use operators and free functions.

---

## 5. Example: Remainder Handled with Masked Memory Accesses

[Getting Started](getting_started.md#3-real-world-tutorial-vectorizing-a-loop-handling-tail-loops) shows the same SAXPY loop in the three APIs, with a scalar loop for the last elements. MIPP can also process these last elements with SIMD code: a mask selects the valid lanes, and masked loads and stores never access memory outside them.

```cpp
#include <cstddef>
#include <cstdint>
#include <mipp.hpp>

// y[i] = a * x[i] + y[i]
void saxpy(std::size_t n, float a, const float* x, float* y)
{
    constexpr std::size_t N = mipp::N<float>();
    const auto va = mipp::set1<float>(a);

    std::size_t i = 0;
    for (; i + N <= n; i += N) {
        auto vx = mipp::loadu<float>(x + i);
        auto vy = mipp::loadu<float>(y + i);
        mipp::storeu(y + i, mipp::fmadd(va, vx, vy));
    }

    if (i < n) { // fewer than N elements left
        int32_t active[N];
        for (std::size_t j = 0; j < N; j++)
            active[j] = (i + j < n);
        auto m  = mipp::set_k<float>(active); // lane j active iff i + j < n
        auto vx = mipp::loadu<mipp::Z>(m, x + i); // inactive lanes are not read (set to 0)
        auto vy = mipp::loadu<mipp::Z>(m, y + i);
        mipp::storeu<mipp::M>(m, y + i, mipp::fmadd(va, vx, vy)); // inactive lanes are not written
    }
}
```

!!! note "Performance"
    Masked loads and stores map to native instructions on AVX-512 (8-bit and 16-bit types require AVX-512BW), and masked stores also on RVV. In the other cases they are currently emulated element by element, so the masked remainder is not faster than a scalar loop: its benefit is a single code path, with no scalar copy of the loop body. The implementation level of each target is given in [`load`](../funcs_support/load/load.md) and [`store`](../funcs_support/store/store.md).
