# Vector Types & Generalized LMUL

MIPP provides a unified vector type system supporting 10 standard numeric datatypes across configurable register multipliers ($\text{LMUL}$).

---

## 1. Supported Datatypes Matrix

MIPP standardizes naming across C and C++ interfaces:

| MIPP Datatype | Scalar Type (`T`) | C Vector Type (`LMUL=1`) | C Mask Type (`LMUL=1`) |
| :--- | :--- | :--- | :--- |
| `float64` | `double` / `float64_t` | `rvd_float64_t` | `rvm_float64_t` |
| `float32` | `float` / `float32_t` | `rvd_float32_t` | `rvm_float32_t` |
| `int64` | `int64_t` | `rvd_int64_t` | `rvm_int64_t` |
| `int32` | `int32_t` | `rvd_int32_t` | `rvm_int32_t` |
| `int16` | `int16_t` | `rvd_int16_t` | `rvm_int16_t` |
| `int8` | `int8_t` | `rvd_int8_t` | `rvm_int8_t` |
| `uint64` | `uint64_t` | `rvd_uint64_t` | `rvm_uint64_t` |
| `uint32` | `uint32_t` | `rvd_uint32_t` | `rvm_uint32_t` |
| `uint16` | `uint16_t` | `rvd_uint16_t` | `rvm_uint16_t` |
| `uint8` | `uint8_t` | `rvd_uint8_t` | `rvm_uint8_t` |

---

## 2. Vector Type Representation

### 2.1. Vector Handles
- **Value Registers**: `mipp::rvd<T, LMUL>` (underlying C struct / hardware handle) and `mipp::Rvd<T, LMUL>` (C++ class).
- **Mask Registers**: `mipp::rvm<T, LMUL>` and `mipp::Rvm<T, LMUL>`.

### 2.2. Compile-Time Element Capacity (`N`)
The total number of elements contained in a vector is retrieved via `mipp::N<T, LMUL>()`:

$$N(T, \text{LMUL}) = \left( \frac{\text{VectorBitWidth}}{\text{sizeof}(T) \times 8} \right) \times \text{LMUL}$$

```cpp
constexpr int n_f32_m1 = mipp::N<float, 1>(); // 8 on AVX2 (256-bit / 32-bit * 1)
constexpr int n_f32_m4 = mipp::N<float, 4>(); // 32 on AVX2 (8 * 4)
```

---

## 3. Generalized LMUL (Length Multiplier) Semantics

The Length Multiplier ($\text{LMUL} \in \{1, 2, 4, 8\}$) originates from **RISC-V Vector 1.0 (RVV)**, where hardware registers are grouped to scale vector capacity. To support RVV natively while maintaining an identical API across all backends, MIPP generalizes the LMUL concept across all supported ISAs.

On fixed-width architectures (x86, ARM), software LMUL functions as a **structured multi-register unrolling mechanism**: operations on $\text{LMUL}=2$ or $\text{LMUL}=4$ expand into discrete SIMD instructions across separate registers, increasing instruction-level parallelism (ILP) without manual loop unrolling, while developer discretion is required to manage register pressure at high LMUL values.

!!! tip "Optimization Practice: Parameterizing Kernels by LMUL"
    When developing compute kernels in C++, parameterizing functions by `int LMUL = 1` makes it simple to explore the unrolling optimization space:
    
    ```cpp
    template <typename T, int LMUL = 1>
    void compute_kernel(const T* in, T* out, size_t n);
    ```
    
    - **`LMUL=2` or `LMUL=4`** typically can yield performance gains in compute-bound loops by saturating execution units and interleaving instruction latencies.
    - **`LMUL=8`** often exhibits diminishing returns or regressions due to register spilling.

```
+-----------------------------------------------------------------------------+
|                               LMUL Modes                                    |
+-----------------------------------------------------------------------------+
|                                                                             |
|  LMUL = 1: [ Register 1 ]                                                   |
|                                                                             |
|  LMUL = 2: [ Register 1 ] [ Register 2 ]                                    |
|                                                                             |
|  LMUL = 4: [ Register 1 ] [ Register 2 ] [ Register 3 ] [ Register 4 ]      |
|                                                                             |
|  LMUL = 8: [ Reg 1 ] [ Reg 2 ] [ Reg 3 ] [ Reg 4 ] [ Reg 5 ] ... [ Reg 8 ]  |
+-----------------------------------------------------------------------------+
```

### 3.1. Hardware LMUL (RISC-V Vector 1.0)
On architectures with native register grouping support (RVV `v` extension), MIPP maps directly to hardware types:

- $\text{LMUL}=1$: `vfloat32m1_t`
- $\text{LMUL}=2$: `vfloat32m2_t` (2 adjacent hardware registers)
- $\text{LMUL}=4$: `vfloat32m4_t` (4 adjacent hardware registers)
- $\text{LMUL}=8$: `vfloat32m8_t` (8 adjacent hardware registers)

The vector execution unit operates on grouped registers as single wide units in hardware.

### 3.2. Software Recursive Binary Structs (x86, ARM)
On fixed-width SIMD architectures (SSE, AVX, AVX-512, NEON, SVE), MIPP emulates LMUL in software via **hierarchical binary structures**:

```c
/* Base Level: LMUL = 1 (Single hardware vector) */
typedef struct { __m256 r; } rvd_avx_float32_m1_t;

/* Multiplied Level: LMUL = 2 (Pair of LMUL=1 structs) */
typedef struct { rvd_avx_float32_m1_t r1, r2; } rvd_avx_float32_m2_t;

/* Multiplied Level: LMUL = 4 (Pair of LMUL=2 structs) */
typedef struct { rvd_avx_float32_m2_t r1, r2; } rvd_avx_float32_m4_t;

/* Multiplied Level: LMUL = 8 (Pair of LMUL=4 structs) */
typedef struct { rvd_avx_float32_m4_t r1, r2; } rvd_avx_float32_m8_t;
```

#### Compilation & Zero-Overhead Execution
When calling an operation on a multiplied vector (e.g., `mipp::add(va, vb)` on `LMUL=2`), the generator emits code evaluating the sub-components recursively:

```c
static inline rvd_avx_float32_m2_t mipp_avx_add_float32_m2(
    const rvd_avx_float32_m2_t r0,
    const rvd_avx_float32_m2_t r1)
{
    rvd_avx_float32_m2_t res;
    res.r1 = mipp_avx_add_float32_m1(r0.r1, r1.r1); // _mm256_add_ps
    res.r2 = mipp_avx_add_float32_m1(r0.r2, r1.r2); // _mm256_add_ps
    return res;
}
```

The compiler places `r1` and `r2` into separate CPU vector registers (e.g., `%ymm0` and `%ymm1`), inlining the calls into dual-issue instructions without memory round-trips.

### 3.3. Flattened Array Representation (Scalar Target)
In the scalar fallback backend, multi-register vectors are represented as flat arrays sized by the total capacity:

```c
typedef struct { float32_t r[MIPP_SCALAR_N_FLOAT32_M1]; } rvd_scalar_float32_m1_t;
typedef struct { float32_t r[MIPP_SCALAR_N_FLOAT32_M2]; } rvd_scalar_float32_m2_t;
typedef struct { float32_t r[MIPP_SCALAR_N_FLOAT32_M4]; } rvd_scalar_float32_m4_t;
typedef struct { float32_t r[MIPP_SCALAR_N_FLOAT32_M8]; } rvd_scalar_float32_m8_t;
```

Scalar operations execute flat sequential loops over all $N \times \text{LMUL}$ elements.

---


## 4. Fractional LMUL & Vector Division ($\text{LDIV} = 1/2$)

In addition to multi-register expansion ($\text{LMUL} > 1$), MIPP provides homogeneous support for **half-vectors** ($\text{LDIV} = 1/2$, expressed as `d2` in C or `LMUL = -2` in C++ templates).

```cpp
// C++ API: half-vector capacity query and types
constexpr int n_half = mipp::N<float, -2>(); 
mipp::rvd<float, -2> v_half = mipp::set0<float, -2>();

// C API: d2 types and operations
rvd_float32_d2_t r_half = mipp_add_float32_d2(r0, r1);
```

### 4.1. Architectural Implementation Strategies

Achieving a uniform $\text{LDIV} = 1/2$ abstraction across disparate hardware requires tailored architectural strategies:

| Target Architecture | Implementation Mechanism for $\text{LDIV} = 1/2$ |
| :--- | :--- |
| **SSE / NEON** | **Generic Bitwise Masking**: No smaller native vector registers exist. Operations execute on standard 128-bit registers and mask out upper elements via bitwise `andb` or blend operations. |
| **AVX / AVX2** | **Inter-ISA Wrapping**: AVX natively contains 128-bit SSE types (`__m128`, `__m128d`, `__m128i`). Half-vectors (`d2`) map directly to native SSE intrinsics. Instructions with masking (e.g. gather, masked loads) can also emulate half-length execution. |
| **AVX-512** | **Opmask Predication & AVX2 Wrapping**: Can execute using native AVX2 256-bit registers/intrinsics, or operate on 512-bit registers restricted by hardware opmasks (`k`-registers). |
| **ARM SVE** | **Governing Predicates**: Half-vector execution is achieved by configuring governing predicates (`svbool_t`) to activate only the lower half of vector lanes. |
| **RISC-V Vector (RVV)** | **Fractional Types, Masking & VL Parameter**: <br>• RVV natively supports fractional LMUL (`vfloat32mf2_t`).<br>• Where architectural constraints prevent native fractional types (e.g. `SEW / LMUL > ELEN` on 64-bit types), MIPP emulates $\text{LDIV}=1/2$ via hardware masks or by dynamically passing the Vector Length (`vl = N/2`) parameter to intrinsics. |

### 4.2. Scope and Constraints of Deeper Fractional Division

While RISC-V Vector supports $\text{LMUL} \in \{1/2, 1/4, 1/8\}$, universally generalizing deeper fractional divisions ($\text{LDIV} = 1/4, 1/8$) across all ISAs is mathematically constrained by element capacity:

- On a 128-bit register (SSE / NEON), a 64-bit datatype (`float64`, `int64`) has an element capacity of $N=2$ at $\text{LMUL}=1$.
- Defining $\text{LDIV} = 1/4$ for a 64-bit type would result in $N = 2 / 4 = 0.5$ elements, which has no physical or semantic meaning.

For this reason, **MIPPv2 guarantees homogeneous support strictly for $\text{LDIV} = 1/2$ (`d2`)** across all supported datatypes and targets. Deeper fractional divisions remain **non-standardized**.
