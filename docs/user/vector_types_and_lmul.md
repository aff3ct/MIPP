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

The same loop in the three APIs (half-vectors are not available on every target, hence the `MIPP_LDIV_2` guard, see [§4.1](#41-availability)):

```c
// C API:
#ifdef MIPP_LDIV_2
for (size_t i = 0; i + MIPP_N_FLOAT32_D2 <= n; i += MIPP_N_FLOAT32_D2) {
    rvd_float32_d2_t a = mipp_loadu_float32_d2(in_a + i);
    rvd_float32_d2_t b = mipp_loadu_float32_d2(in_b + i);
    rvd_float32_d2_t c = mipp_add_float32_d2(a, b);
    mipp_storeu_float32_d2(out + i, c);
}
#endif
```

```cpp
// C++ Functional API:
#ifdef MIPP_LDIV_2
constexpr size_t n_half = mipp::N<float, -2>();
for (size_t i = 0; i + n_half <= n; i += n_half) {
    mipp::rvd<float, -2> a = mipp::loadu<float, -2>(in_a + i);
    mipp::rvd<float, -2> b = mipp::loadu<float, -2>(in_b + i);
    mipp::rvd<float, -2> c = mipp::add(a, b);
    mipp::storeu(out + i, c);
}
#endif
```

```cpp
// C++ Object API:
#ifdef MIPP_LDIV_2
constexpr size_t n_half = mipp::N<float, -2>();
for (size_t i = 0; i + n_half <= n; i += n_half) {
    mipp::Rvd<float, -2> a = mipp::loadu_obj<float, -2>(in_a + i);
    mipp::Rvd<float, -2> b = mipp::loadu_obj<float, -2>(in_b + i);
    mipp::Rvd<float, -2> c = a + b;
    mipp::storeu(out + i, c);
}
#endif
```

### 4.1. Availability

Half-vectors are **not available on every target**. When they are, MIPP defines the `MIPP_LDIV_2` macro (except on the scalar target for now, see below), which portable code should use as a guard:

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
| **Scalar** | Yes, see below | Plain array of half the elements. |

!!! warning "Scalar target and `MIPP_LDIV_2`"
    The scalar target generates the `d2` types and functions, but does not define `MIPP_LDIV_2` yet. Code guarded by `#ifdef MIPP_LDIV_2` therefore skips half-vectors when compiled with `-DMIPP_SCALAR`, although they are available.

### 4.2. Scope and Constraints of Deeper Fractional Division

While RISC-V Vector supports $\text{LMUL} \in \{1/2, 1/4, 1/8\}$, generalizing deeper divisions ($\text{LDIV} = 4, 8$) across ISAs is constrained by element capacity:

- On a 128-bit register (SSE / NEON), a 64-bit datatype (`float64`, `int64`) has an element capacity of $N=2$ at $\text{LMUL}=1$.
- Defining $\text{LDIV} = 4$ for a 64-bit type would result in $N = 2 / 4 = 0.5$ elements, which has no meaning.

For this reason, MIPP only exposes $\text{LDIV} = 2$ (`d2`), and deeper divisions are not part of the API.

---

## 5. Type Conversions

MIPP provides three conversions between data vectors. They differ in what they preserve: the bits (`cast`), the values (`cvt`), or the values with a wider type (`wcvt`).

| Operation | Effect | C API | C++ Functional API | C++ Object API |
| :--- | :--- | :--- | :--- | :--- |
| **`cast`** | Reinterprets the bits of the register as another type. No value is converted, no instruction is emitted. | `mipp_cast_[src]_[dst]_[lmul](v)` | `mipp::cast_[dst](v)` | `mipp::cast<T_DST>(v)` |
| **`cvt`** | Converts the value of each element to another type **of the same width**. | `mipp_cvt_[src]_[dst]_[lmul](v)` | `mipp::cvt_[dst](v)` | `mipp::cvt<T_DST>(v)` |
| **`wcvt`** | Converts the value of the elements of the **lower half** to the type **twice as wide**. | `mipp_wcvt_[src]_[dst]_[lmul](v)` | `mipp::wcvt_[dst](v)` | `mipp::wcvt<T_DST>(v)` |

The three keep the `LMUL` of their input. Masks have their own reinterpretation, `cast_k` (see [Masking Semantics §6.1](masking_semantics.md#61-strong-mask-typing-cast_k-mask-to-mask-conversion)), and masks convert to and from data vectors with `toreg` / `tomsk` ([§6.2](masking_semantics.md#62-tomsk-data-vector-to-mask), [§6.3](masking_semantics.md#63-toreg-mask-to-data-vector)).

```c
// C API:
rvd_float32_t v  = mipp_loadu_float32(ptr);       // {-2.7, -1.4, -0.1, 1.2, ...}
rvd_int32_t   vb = mipp_cast_float32_int32(v);    // {0xC02CCCCD, ...}: IEEE-754 bit patterns
rvd_int32_t   vi = mipp_cvt_float32_int32(v);     // {-2, -1, 0, 1, ...}: truncation
rvd_float64_t vw = mipp_wcvt_float32_float64(v);  // {-2.7, -1.4, ...}: lower half only
```

```cpp
// C++ Functional API:
mipp::rvd<float>   v  = mipp::loadu<float>(ptr);  // {-2.7, -1.4, -0.1, 1.2, ...}
mipp::rvd<int32_t> vb = mipp::cast_int32(v);      // {0xC02CCCCD, ...}: IEEE-754 bit patterns
mipp::rvd<int32_t> vi = mipp::cvt_int32(v);       // {-2, -1, 0, 1, ...}: truncation
mipp::rvd<double>  vw = mipp::wcvt_float64(v);    // {-2.7, -1.4, ...}: lower half only
```

```cpp
// C++ Object API:
mipp::Rvd<float>   v  = mipp::loadu_obj<float>(ptr); // {-2.7, -1.4, -0.1, 1.2, ...}
mipp::Rvd<int32_t> vb = mipp::cast<int32_t>(v);      // {0xC02CCCCD, ...}: IEEE-754 bit patterns
mipp::Rvd<int32_t> vi = mipp::cvt<int32_t>(v);       // {-2, -1, 0, 1, ...}: truncation
mipp::Rvd<double>  vw = mipp::wcvt<double>(v);       // {-2.7, -1.4, ...}: lower half only
```

### 5.1. `cast` (Bit Reinterpretation)

`cast` exists for every pair of the 10 datatypes. The register keeps its size, so the number of elements changes when the widths differ: `cast` from `rvd<float>` to `rvd<int8_t>` gives 4 times more lanes, each holding one byte of the original floats. Typical uses are bit manipulations on floating-point values (sign, exponent) and feeding integer-only operations with floating-point data.

### 5.2. `cvt` (Value Conversion, Same Width)

`cvt` converts each element like a C cast. Available pairs: `float32` $\leftrightarrow$ `int32` / `uint32`, `float64` $\leftrightarrow$ `int64` / `uint64`, and signed $\leftrightarrow$ unsigned integers of the same width (`int8` $\leftrightarrow$ `uint8`, ..., `int64` $\leftrightarrow$ `uint64`).

- **Floating-point to integer**: truncation toward zero (`-2.7f` gives `-2`). Values out of the range of the destination type, and NaN, give a result that depends on the target.
- **Integer to floating-point**: rounded to the nearest representable value (`int32` above $2^{24}$ loses precision in `float`).
- **Signed to unsigned and back**: modular, the bit pattern is unchanged (`-1` gives `4294967295` in `uint32`); the result is the same as `cast`.

### 5.3. `wcvt` (Widening Value Conversion)

`wcvt` converts to the type twice as wide: `int8` $\to$ `int16`, `int16` $\to$ `int32`, `int32` $\to$ `int64`, the same for the unsigned types, and `float32` $\to$ `float64`. As the result keeps the same `LMUL`, it holds half as many elements: `wcvt` converts the first `mipp::N<T_DST, LMUL>()` elements (the lower half of the input, of the whole register group when $\text{LMUL} > 1$) and ignores the others.

There is no function to widen the upper half, and no narrowing conversion. To widen a whole array, step through it by `mipp::N<T_DST, LMUL>()` elements: each `loadu` reads a full input register and only its lower half is converted, so the input buffer must extend half a register beyond the last converted element.
