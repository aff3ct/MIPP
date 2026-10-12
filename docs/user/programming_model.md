# Programming Model & API Tiers

MIPP provides three distinct API layers built on top of a unified code generation engine:

1. **C Low-Level API** (`<mipp.h>`): Explicit type-suffixed functions and plain C structs.
2. **C++ Functional Template API** (`<mipp.hpp>`): Type-parameterized template functions under namespace `mipp::`.
3. **C++ Object API** (`<mipp_obj.hpp>`): Class wrappers (`mipp::Rvd<T, LMUL>`, `mipp::Rvm<T, LMUL>`) with arithmetic and relational operator overloading.

All three tiers share the same zero-overhead inlined execution path and map to identical machine instructions.

---

## 1. Header Inclusion & Organization

MIPP provides two header inclusion paradigms: **Monolithic Inclusion** and **Modular Granular Inclusion**.

```text
include/
├── mipp.h                       # Pure C99 monolithic entry point
├── mipp.hpp                     # C++ Functional Template monolithic entry point
├── mipp_obj.hpp                 # C++ Object API monolithic entry point
└── mipp/                        # Namespaced headers
    ├── c/
    │   ├── cat/<category>.h     # Granular C category header (e.g. arithmetic.h)
    │   └── fun/<function>.h     # Granular C function header (e.g. add.h)
    ├── cpp/
    │   ├── cat/<category>.hpp   # Granular C++ category header
    │   └── fun/<function>.hpp   # Granular C++ function header
    ├── obj/
    │   ├── cat/<category>.hpp   # Granular C++ Object category header
    │   └── fun/<function>.hpp   # Granular C++ Object function header
    └── internal/                # Private implementation details (do not include directly)
        ├── interfaces/          # Architecture-independent dispatch interfaces
        ├── simd_ext/            # Generated ISA-specific backend implementations
        └── templates/           # Common C++ templates and enums
```

### 1.1. Option 1: Monolithic Inclusion (Prototyping)

Monolithic entry points include all MIPP SIMD functions and data types across the entire library in a single directive:

- `<mipp.h>` for C Low-Level API
- `<mipp.hpp>` for C++ Functional Template API
- `<mipp_obj.hpp>` for C++ Object API

This is the fastest and most convenient approach when starting a project or writing small self-contained algorithms.

### 1.2. Option 2: Granular Inclusion (Production & Scale)

Granular headers expose either a single SIMD function or an entire category of functions across all variants and LMULs:

- **Function headers**: `<mipp/c/fun/<func>.h>`, `<mipp/cpp/fun/<func>.hpp>`, `<mipp/obj/fun/<func>.hpp>`
- **Category headers**: `<mipp/c/cat/<cat>.h>`, `<mipp/cpp/cat/<cat>.hpp>`, `<mipp/obj/cat/<cat>.hpp>` (e.g. `arithmetic.hpp`, `load.hpp`, `comparison.hpp`)

Granular headers dramatically accelerate compilation time (often 5x to 10x faster parsing) and reduce compiler peak memory consumption (RSS), which is critical for large C++ codebases with dozens of compilation units.

<a id="fine-grained-headers"></a>
### 1.3. Fine-Grained & Atomic 2D Headers (`--granularity fine`)

When MIPP headers are emitted with `--granularity fine`, the generator creates an ultra-modular matrix of atomic header files across both dimensions: execution variant (`u`, `m`, `z`, `s`) and register multiplier LMUL (`m1`, `m2`, `m4`, `m8`, `d2`). This allows large-scale projects to include **only the exact variant and LMUL** required by each translation unit:

```text
include/mipp/obj/
├── fun/
│   ├── add.hpp                  # Coarse: All variants (U, M, Z, S) and all LMULs
│   ├── m/                       # 1D Variant Umbrella: 'm' variant across all LMULs
│   │   ├── add.hpp
│   │   └── m2/                  # 2D Atomic: 'm' variant + LMUL=2 specifically
│   │       └── add.hpp
│   └── m2/                      # 1D LMUL Umbrella: LMUL=2 across all variants
│       └── add.hpp
└── cat/
    ├── arithmetic.hpp           # Coarse: Category umbrella
    ├── m/arithmetic.hpp         # 1D Variant category umbrella
    └── m/m2/arithmetic.hpp      # 2D Atomic category umbrella
```

#### Inclusion Levels

1. **Coarse Function Header**: `<mipp/obj/fun/<func>.hpp>` (includes all variants and LMULs for `<func>`).
2. **1D Variant Umbrella**: `<mipp/obj/fun/<variant>/<func>.hpp>` (e.g. `m/add.hpp`, includes only masked `add` across all LMULs).
3. **1D LMUL Umbrella**: `<mipp/obj/fun/<lmul>/<func>.hpp>` (e.g. `m2/add.hpp`, includes only LMUL=2 `add` across all variants).
4. **2D Atomic Leaf**: `<mipp/obj/fun/<variant>/<lmul>/<func>.hpp>` (e.g. `m/m2/add.hpp`, includes only the exact kernel needed).

#### Compilation & Scalability Benefits

Benchmarking across large workloads demonstrates that 2D atomic inclusion provides significant advantages:

- **Minimal Preprocessor Expansion**: The preprocessor parses only the minimal set of templates needed by each translation unit.
- **Lower Compiler Peak RSS**: Peak memory consumption during compilation is substantially reduced, preventing out-of-memory issues during highly parallel multi-threaded builds.

---

## 2. Tier 1: C Low-Level API (`<mipp.h>`)

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

## 3. Tier 2: C++ Functional Template API (`<mipp.hpp>`)

The C++ Functional API parameterizes operations over the element type `T`, an optional register multiplier `LMUL` (defaults to `1`), and an optional target instruction set `ISA_TYPE` (defaults to `mipp::DEFAULT_ISA`).

### 3.1. Template Parameter Domains

| Parameter | Domain / Supported Values | Description & Constraints |
| :--- | :--- | :--- |
| `typename T` | `float`, `double`, `int8_t`, `int16_t`, `int32_t`, `int64_t`, `uint8_t`, `uint16_t`, `uint32_t`, `uint64_t` | 10 standard numeric datatypes supported across all operations. |
| `int LMUL` | `1, 2, 4, 8` (integer multipliers) and the fractional divisor `-2` (half vector, AVX / AVX-512 / RVV only) | Vector length multiplier (register grouping or fractional splitting). Defaults to `1`. See [Vector Types & LMUL](vector_types_and_lmul.md). |
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

### 3.6. Masked Function Template Specialization
Masked operations in the C++ Functional API use the `mipp::VARIANT` template parameter (`<mipp::M>`, `<mipp::Z>`, `<mipp::S>`). Because `mipp::rvd<T, LMUL>` is a type alias to an internal type trait (`rvd_type<T, LMUL>::type`), C++ template argument deduction cannot deduce `T`. Therefore, the datatype `T` (and `LMUL` if different from `1`) must be explicitly supplied:

```cpp
auto m   = mipp::cmpeq(a, b);   // Mask condition
auto src = mipp::set1<float>(0.0f);

// 1. Merge Mask (M): res[i] = m[i] ? (a[i] + b[i]) : a[i]
auto c_merge = mipp::add<mipp::M, float>(m, a, b);

// 2. Zero Mask (Z): res[i] = m[i] ? (a[i] + b[i]) : 0
auto c_zero  = mipp::add<mipp::Z, float>(m, a, b);

// 3. Source Mask (S): res[i] = m[i] ? (a[i] + b[i]) : src[i]
auto c_src   = mipp::add<mipp::S, float>(m, src, a, b);
```

For comprehensive coverage of masking rules, conversions, and hardware mappings, see [Masking Semantics](masking_semantics.md).

---

## 4. Tier 3: C++ Object API (`<mipp_obj.hpp>`)

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
    Rvd(rvd<T, LMUL> r);     // Wraps a low-level rvd register
    Rvd(const T val);        // Broadcasts a scalar (mipp::set1)
    Rvd(const T* data);      // Loads from memory, no alignment requirement (mipp::loadu)

    // Implicit conversion to the low-level register (interoperability with the C++ Functional API)
    operator rvd<T, LMUL>() const;

    // Element access
    T operator[](const size_t index) const; // Reads one element (mipp::get)
};

template <typename T, int LMUL = 1>
struct Rvm {
    rvm<T, LMUL> m; // Underlying low-level mask register

    Rvm() = default;
    Rvm(rvm<T, LMUL> m);             // Wraps a low-level rvm register
    Rvm(const bool val);             // All lanes active or inactive (mipp::set1_k)
    Rvm(const int32_t vals[]);       // Per-lane initialization (mipp::set_k)

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

### 4.4. Masked Operations Support
Masked operations in the C++ Object API are fully supported via the standard `VARIANT` template parameter (`M`, `Z`, `S`), taking `Rvm` and `Rvd` objects:

```cpp
mipp::Rvm<float> m = (a > b); // Mask from operator comparison
mipp::Rvd<float> src = 0.0f;

// 1. Merge Mask (M): res[i] = m[i] ? (a[i] + b[i]) : a[i]
auto c_merge = mipp::add<mipp::M>(m, a, b);

// 2. Zero Mask (Z): res[i] = m[i] ? (a[i] + b[i]) : 0.0f
auto c_zero  = mipp::add<mipp::Z>(m, a, b);

// 3. Source Mask (S): res[i] = m[i] ? (a[i] + b[i]) : src[i]
auto c_src   = mipp::add<mipp::S>(m, src, a, b);
```

!!! tip "Idiomatic Masking with Automatic Template Deduction"
    Because operand types and LMUL are deduced from `Rvm` and `Rvd`, importing the variant symbol allows writing concise expressions:
    ```cpp
    using mipp::M;
    auto c = mipp::add<M>(m, a, b); // Automatically deduces T=float and LMUL
    ```
    There is no need to write `mipp::add<mipp::M, float, 1>(m, a, b)`.


### 4.5. Idiomatic Coding Guidelines

1. **Prefer Operator Overloads**: When an operator exists (`a + b`, `a * b`, `a == b`, `m1 & m2`), use it over named function calls for maximum readability.
2. **Use Free Functions**: For non-operator routines (e.g. `mipp::fmadd`, `mipp::sqrt`, `mipp::min`, `mipp::store`), use free functions under `namespace mipp::`.
3. **No Member Syntax**: Operations are not exposed as member functions (there is no `a.add(b)`); use operators and free functions.

---

## 5. Comparative Example: Vector SAXPY ($Y = a \cdot X + Y$)

Below is an identical vectorized SAXPY loop ($Y[i] = a \cdot X[i] + Y[i]$) implemented across all three API tiers.

=== "C Low-Level API"
    ```c
    #include <mipp.h>

    void saxpy_c(size_t n, float a, const float* x, float* y)
    {
        const size_t N = MIPP_N_FLOAT32;
        const size_t vec_limit = (n / N) * N;
        rvd_float32_m1_t va = mipp_set1_float32_m1(a);

        for (size_t i = 0; i < vec_limit; i += N) {
            rvd_float32_m1_t vx = mipp_loadu_float32_m1(x + i);
            rvd_float32_m1_t vy = mipp_loadu_float32_m1(y + i);
            rvd_float32_m1_t vres = mipp_fmadd_float32_m1(va, vx, vy);
            mipp_storeu_float32_m1(y + i, vres);
        }
        for (size_t i = vec_limit; i < n; i++) {
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
        constexpr size_t N = mipp::N<T, LMUL>();
        const size_t vec_limit = (n / N) * N;
        const auto va = mipp::set1<T, LMUL>(a);

        for (size_t i = 0; i < vec_limit; i += N) {
            auto vx = mipp::loadu<T, LMUL>(x + i);
            auto vy = mipp::loadu<T, LMUL>(y + i);
            auto vres = mipp::fmadd(va, vx, vy); // Fused multiply-add
            mipp::storeu(y + i, vres);
        }
        for (size_t i = vec_limit; i < n; i++) {
            y[i] = a * x[i] + y[i];
        }
    }
    ```

=== "C++ Object API"
    ```cpp
    #include <mipp_obj.hpp>

    template <typename T = float, int LMUL = 1>
    void saxpy_obj(size_t n, T a, const T* x, T* y)
    {
        constexpr size_t N = mipp::Rvd<T, LMUL>::N();
        const size_t vec_limit = (n / N) * N;
        mipp::Rvd<T, LMUL> va(a);

        for (size_t i = 0; i < vec_limit; i += N) {
            mipp::Rvd<T, LMUL> vx(x + i);
            mipp::Rvd<T, LMUL> vy(y + i);
            mipp::Rvd<T, LMUL> vres = va * vx + vy; // Uses overloaded * and +
            mipp::storeu(y + i, vres);              // Idiomatic free function store
        }
        for (size_t i = vec_limit; i < n; i++) {
            y[i] = a * x[i] + y[i];
        }
    }
    ```
