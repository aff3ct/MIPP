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


<a id="half-vectors"></a>
## 4. Half-Vectors (`d2`)

In addition to multi-register expansion ($\text{LMUL} > 1$), MIPP provides **half-vectors**: vectors holding half the elements of a base register. The same concept appears under several notations, which all mean the same thing:

| Context | Notation |
| :--- | :--- |
| Concept | half-vector, length divider $\text{LDIV} = 2$ (equivalently $\text{LMUL} = 1/2$) |
| C API types and functions | `d2` suffix: `rvd_float32_d2_t`, `mipp_add_float32_d2` |
| C++ Functional and Object APIs | `LMUL` template argument `-2`: `mipp::rvd<float, -2>`, `mipp::Rvd<float, -2>` |
| Availability macro | `MIPP_LDIV_2` |
| Generator (`sw_lmul`, `hw_lmul`, `--ldiv`) | factor `-2`, or `--ldiv 2` |

```cpp
// C++ Functional API: half-vector capacity query and types
constexpr int n_half = mipp::N<float, -2>();
mipp::rvd<float, -2> v_half = mipp::set0<float, -2>();

// C API: d2 types and operations
rvd_float32_d2_t r_half = mipp_add_float32_d2(r0, r1);
```

### 4.1. Availability

Half-vectors are **not available on every target**. When they are, MIPP defines the `MIPP_LDIV_2` macro, which portable code should use as a guard:

```c
#ifdef MIPP_LDIV_2
    rvd_float32_d2_t h = mipp_set0_float32_d2();
#endif
```

| Target Architecture | `d2` Available | Representation |
| :--- | :---: | :--- |
| **AVX / AVX2** | Yes | Native 128-bit SSE registers (`__m128`, `__m128d`, `__m128i`). |
| **AVX-512** | Yes | Native 256-bit AVX registers. |
| **RISC-V Vector (RVV)** | Yes | Native fractional register types (`vfloat32mf2_t`, ...) for 8 to 32-bit elements. For 64-bit elements, where the RVV constraint $\text{SEW} / \text{LMUL} \le \text{ELEN}$ forbids fractional types, MIPP stores the half-vector in a plain array. Some of these 64-bit operations are not implemented yet (see [Implementation Levels](implementation_levels.md#known-limitations)). |
| **SSE / NEON** | No | 128 bits is the smallest register width; no `d2` types are generated. |
| **ARM SVE** | No | Not generated yet. |
| **Scalar** | No | Not generated. |

### 4.2. Scope and Constraints of Deeper Fractional Division

While RISC-V Vector supports $\text{LMUL} \in \{1/2, 1/4, 1/8\}$, generalizing deeper divisions ($\text{LDIV} = 4, 8$) across ISAs is constrained by element capacity:

- On a 128-bit register (SSE / NEON), a 64-bit datatype (`float64`, `int64`) has an element capacity of $N=2$ at $\text{LMUL}=1$.
- Defining $\text{LDIV} = 4$ for a 64-bit type would result in $N = 2 / 4 = 0.5$ elements, which has no meaning.

For this reason, MIPP only exposes $\text{LDIV} = 2$ (`d2`), and deeper divisions are not part of the API.
