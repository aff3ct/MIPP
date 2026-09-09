# Programming Model & API Tiers

MIPP provides three distinct API layers built on top of a unified code generation engine:

1. **C Low-Level API** (`<mipp.h>`): Explicit type-suffixed functions and plain C structs.
2. **C++ Functional Template API** (`<mipp.hpp>`): Type-parameterized template functions under namespace `mipp::`.
3. **C++ Object API** (`<mipp_obj.hpp>`): Class wrappers (`mipp::Rvd<T, LMUL>`, `mipp::Rvm<T, LMUL>`) with arithmetic and relational operator overloading.

All three tiers share the same zero-overhead inlined execution path and map to identical machine instructions.

---

## 1. Header Inclusion & Organization

```
include/
├── mipp.h                  # Pure C entry point (includes C interface & active ISA)
├── mipp.hpp                # C++ Functional Template entry point
├── mipp_obj.hpp            # C++ Object API entry point (includes mipp.hpp)
├── interfaces/
│   ├── c/                  # C dispatch declarations & common definitions
│   └── cpp/                # C++ namespace mipp:: template declarations
└── simd_ext/               # Generated backend headers per ISA (sse, avx, neon, rvv, etc.)
```

!!! warning "Direct Inclusion of `simd_ext/` Headers"
    The C headers under `include/simd_ext/<isa>/c/` can technically be included directly as standalone ISA-specific wrappers. However, this is **not recommended** for application code: these files are internal generator artifacts whose internal layout may evolve between MIPP releases without backward-compatibility guarantees.

---

## 2. Tier 1: C Low-Level API (`<mipp.h>`)

The C API provides explicit, type-safe C99 function identifiers and vector types for every `(operation, datatype, lmul, mask_variant)` combination.

### 2.1. Naming Convention
```text
mipp_[func]_[datatype][_lmul][_mask_variant]
```

When operating at standard vector length ($\text{LMUL}=1$), the `_m1` suffix is optional: functions without the suffix (e.g., `mipp_add_float32`) are direct aliases to their `_m1` counterparts (`mipp_add_float32_m1`).

- **Standard ($\text{LMUL}=1$, unmasked)**: `mipp_add_float32(r0, r1)` or `mipp_add_float32_m1(r0, r1)`
- **Multi-Register ($\text{LMUL}=2, 4, 8$)**: `mipp_add_float32_m2(r0, r1)`, `mipp_add_float32_m4(r0, r1)`
- **Masked ($\text{LMUL}=1$, blend update)**: `mipp_add_float32_m1_mask(m0, r0, r1)` or `mipp_add_float32_mask(m0, r0, r1)`
- **Zero-Masked**: `mipp_add_float32_m1_maskz(m0, r0, r1)` or `mipp_add_float32_maskz(m0, r0, r1)`
- **Source-Masked**: `mipp_add_float32_m1_masks(m0, rsrc, r0, r1)` or `mipp_add_float32_masks(m0, rsrc, r0, r1)`

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

## 3. Tier 2: C++ Functional Template API (`<mipp.hpp>`)

The C++ Functional API parameterizes operations over the element type `T`, an optional register multiplier `LMUL` (defaults to `1`), and an optional target instruction set `ISA_TYPE` (defaults to `mipp::DEFAULT_ISA`).

### 3.1. Template Parameter Domains

| Parameter | Domain / Supported Values | Description & Constraints |
| :--- | :--- | :--- |
| `typename T` | `float`, `double`, `int8_t`, `int16_t`, `int32_t`, `int64_t`, `uint8_t`, `uint16_t`, `uint32_t`, `uint64_t` | 10 standard numeric datatypes supported across all operations. |
| `int LMUL` | `1, 2, 4, 8` (integer multipliers) and fractional divisors (`-2` / `d2`) | Vector length multiplier (register grouping or fractional splitting). Defaults to `1`. |
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

### 3.4. Explicit Architecture Selection & Scalar Co-existence
Scalar types and operations are unconditionally compiled into MIPP headers. Developers can explicitly supply the third template parameter `ISA_TYPE` to instantiate specific ISA or scalar registers side-by-side in the same translation unit:

```cpp
// Default SIMD vector (uses active compiler target, e.g. AVX2):
mipp::rvd<float> v_simd = mipp::load<float>(ptr);

// Explicit scalar vector co-existing in the same code block:
mipp::rvd<float, 1, mipp::ISA::SCALAR> v_scalar = mipp::load<float, 1, mipp::ISA::SCALAR>(ptr);

// Compare/verify SIMD result against scalar baseline:
mipp::rvd<float> res_simd = mipp::add(v_simd, v_simd);
mipp::rvd<float, 1, mipp::ISA::SCALAR> res_scalar = mipp::add<float, 1, mipp::ISA::SCALAR>(v_scalar, v_scalar);
```

This co-existence mechanism is used extensively throughout MIPP's automated test suites to cross-validate SIMD execution against scalar arithmetic directly.

!!! warning "Portability Scope: `ISA::DEFAULT` and `ISA::SCALAR`"
    Cross-platform portability is **only guaranteed** when using `mipp::DEFAULT_ISA` (the default) or `mipp::ISA::SCALAR`. 
    
    Explicitly hardcoding a specific hardware instruction set (such as `mipp::ISA::SSE`, `mipp::ISA::AVX`, `mipp::ISA::NEON`, or `mipp::ISA::RVV`) is **non-portable by design**: the code will only compile on toolchains and targets that provide that specific ISA's intrinsics and register sets.

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

### 3.6. Masked Function Template Specialization
Masked operations in the C++ API use explicit template specialization via the `mipp::MKIND` enumeration:

```cpp
namespace mipp {
    enum MKIND { U, M, Z, S }; // Unmasked, Mask (merge), Zero-mask, Source-preserve
}
```

To invoke a masked operation, pass the mask kind as the first template parameter (`<mipp::M>`, `<mipp::Z>`, or `<mipp::S>`):

```cpp
auto m   = mipp::cmpeq(a, b);   // Mask condition
auto src = mipp::set1<float>(0.0f);

// 1. Merge Mask (M): res[i] = m[i] ? (a[i] + b[i]) : a[i]
auto c_merge = mipp::add<mipp::M>(m, a, b);

// 2. Zero Mask (Z): res[i] = m[i] ? (a[i] + b[i]) : 0
auto c_zero  = mipp::add<mipp::Z>(m, a, b);

// 3. Source Mask (S): res[i] = m[i] ? (a[i] + b[i]) : src[i]
auto c_src   = mipp::add<mipp::S>(m, src, a, b);
```

!!! note "Mask Variant Availability"
    Not every MIPP function supports all four mask variants (for example, load/store operations, reductions, and certain math routines only implement applicable variants). Refer to [Masking Semantics](masking_semantics.md) for detailed behavior.

---

## 4. Tier 3: C++ Object API (`<mipp_obj.hpp>`)

The Object API encapsulates raw vector and mask handles within classes:
- `mipp::Rvd<T, LMUL>` for numeric data vectors.
- `mipp::Rvm<T, LMUL>` for boolean mask vectors.

### 4.1. Class Structure & Accessors
```cpp
template <typename T, int LMUL = 1>
class Rvd {
public:
    rvd<T, LMUL> r; // Underlying low-level vector

    static constexpr int size(); // Returns mipp::N<T, LMUL>()

    // Constructors
    Rvd();
    Rvd(rvd<T, LMUL> r);
    Rvd(const T val);        // Broadcasts scalar via mipp::set1
    Rvd(const T* data);      // Loads from aligned pointer via mipp::load

    // Element Subscripting (calls mipp::get(r, idx))
    T operator[](const size_t index) const;
};
```

### 4.2. Overloaded Operators Reference

| Operation Category | Supported Operators | Operands | Return Type |
| :--- | :--- | :--- | :--- |
| **Arithmetic** | `+`, `-`, `*`, `/` | `Rvd<T>`, `Rvd<T>` | `Rvd<T>` |
| **Compound Assignment** | `+=`, `-=`, `*=`, `/=` | `Rvd<T>`, `Rvd<T>` | `Rvd<T>&` |
| **Bitwise** | `&`, `|`, `^`, `~` | `Rvd<T>`, `Rvd<T>` | `Rvd<T>` |
| **Relational / Comparison** | `==`, `!=`, `<`, `<=`, `>`, `>=` | `Rvd<T>`, `Rvd<T>` | `Rvm<T>` *(Mask)* |
| **Mask Logic** | `&`, `|`, `^` | `Rvm<T>`, `Rvm<T>` | `Rvm<T>` |

---

## 5. Comparative Example: Vector SAXPY ($Y = a \cdot X + Y$)

Below is an identical vectorized SAXPY loop ($Y[i] = a \cdot X[i] + Y[i]$) implemented across all three API tiers.

=== "C Low-Level API"
    ```c
    #include <mipp.h>

    void saxpy_c(size_t n, float a, const float* x, float* y)
    {
        const size_t step = MIPP_N_FLOAT32;
        rvd_float32_m1_t va = mipp_set1_float32_m1(a);

        size_t i = 0;
        for (; i + step <= n; i += step) {
            rvd_float32_m1_t vx = mipp_loadu_float32_m1(x + i);
            rvd_float32_m1_t vy = mipp_loadu_float32_m1(y + i);
            rvd_float32_m1_t vres = mipp_fmadd_float32_m1(va, vx, vy);
            mipp_storeu_float32_m1(y + i, vres);
        }
        for (; i < n; i++) {
            y[i] = a * x[i] + y[i];
        }
    }
    ```

=== "C++ Functional API"
    ```cpp
    #include <mipp.hpp>

    template <typename T = float, int LMUL = 1>
    void saxpy_cpp(size_t n, T a, const T* x, T* y)
    {
        constexpr size_t step = mipp::N<T, LMUL>();
        const auto va = mipp::set1<T, LMUL>(a);

        size_t i = 0;
        for (; i + step <= n; i += step) {
            auto vx = mipp::load<T, LMUL>(x + i);
            auto vy = mipp::load<T, LMUL>(y + i);
            auto vres = mipp::fmadd(va, vx, vy); // Fused multiply-add
            mipp::store(y + i, vres);
        }
        for (; i < n; i++) {
            y[i] = a * x[i] + y[i];
        }
    }
    ```

=== "C++ Object API"
    ```cpp
    #include <mipp_obj.hpp>

    void saxpy_obj(size_t n, float a, const float* x, float* y)
    {
        using RegF = mipp::Rvd<float>;
        constexpr size_t step = RegF::size();
        RegF va(a);

        size_t i = 0;
        for (; i + step <= n; i += step) {
            RegF vx(x + i);
            RegF vy(y + i);
            RegF vres = va * vx + vy; // Uses overloaded * and +
            mipp::store(y + i, vres.r);
        }
        for (; i < n; i++) {
            y[i] = a * x[i] + y[i];
        }
    }
    ```
