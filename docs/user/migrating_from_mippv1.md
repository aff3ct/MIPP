# Migrating from MIPPv1

MIPPv2 is a new library, not MIPPv1 with more functions: the headers are generated, the types have other names, and a few functions give another result under the same name. A program written for MIPPv1 does not compile with MIPPv2, and a part of the work is not a renaming. MIPPv1 stays available on the [`master` branch](https://github.com/aff3ct/mipp/tree/master).

This page goes from what matters most to what is mechanical:

1. [what changes in depth](#1-what-changes-in-depth),
2. [the same loop in both versions](#2-the-same-loop-in-both-versions), and the new types,
3. [the functions that keep their name and change their result](#3-same-name-other-result): read this section before renaming anything,
4. [the correspondence tables](#4-correspondence-tables),
5. [what has no equivalent](#5-no-equivalent).

The results given for MIPPv1 were measured with MIPPv1 on SSE4.2, AVX2 and NEON (AArch64). The results given for MIPPv2 are checked by the tests of this documentation, on every target.

---

## 1. What Changes in Depth

| | MIPPv1 | MIPPv2 |
| :--- | :--- | :--- |
| **Headers** | Written by hand and copied with the project (`mipp.h` and its `.hxx` files). | Generated from a declarative database: a release archive, or the generator ([Getting Started](getting_started.md#1-installation)). |
| **APIs** | C++ only: raw registers (`mipp::reg`) and objects (`mipp::Reg<T>`). | A C API, a C++ Functional API (`mipp::vd<T>`) and a C++ Object API (`mipp::Vd<T>`) ([Programming Model](programming_model.md)). |
| **Register types** | `mipp::reg` is the same type for every element type: a register of `float` can be given to a function of `int32_t`. | A register carries its element type: `mipp::vd<float>` and `mipp::vd<int32_t>` are two types, and mixing them is a compile error. |
| **Mask types** | `mipp::Msk<N>`, by number of elements. | `mipp::Vm<T>`, by element type. |
| **Function missing for a type or a target** | The call compiles, then throws `std::runtime_error` (`... is undefined!`) at run time. | Every function exists for its datatypes on every target, at one of four [implementation levels](implementation_levels.md) (see its [known limitations](implementation_levels.md#known-limitations)). |
| **Targets** | SSE, AVX, AVX-512, NEON, and a part of SVE. | SSE, AVX, AVX-512, NEON, SVE, RVV, and a scalar target. |
| **Register sizes** | A register, and a half register (`mipp::Reg_2<T>`). | LMUL: half-vectors and groups of 2, 4 or 8 registers ([Vector Types & LMUL](vector_types_and_lmul.md)). |
| **Masked operations** | `mask<T, OP>` and `maskz<T, OP>`: the operation on every lane, then a blend. | Three variants of each function (`M`, `Z`, `S`), native where the target has masked instructions ([Masking Semantics](masking_semantics.md)). |
| **Math functions** | `float` only with GCC, Clang and MSVC (`double` with the Intel compiler). | `float` and `double` on every target, and more functions (`asin`, `acos`, `atan`, `atan2`, `pow`). |
| **Complex numbers** | `mipp::Regx2<T>`: the real parts in one register, the imaginary parts in another. | Interleaved layout in ordinary registers ([Complex Numbers](complex_numbers.md)). |
| **Sequential mode** | `MIPP_NO_INTRINSICS`: registers of one element. | `-DMIPP_SCALAR`: a scalar target whose registers have the size of the registers of the host by default (`MIPP_SCALAR_SIZE`). |
| **Compiled part** | `compress` needs a static library (`MIPP_STATIC_LIB`) on SSE, AVX and NEON. | Header-only. |
| **Build system** | A CMake package (`find_package(MIPP)`). | An include directory. |

---

## 2. The Same Loop in Both Versions

### 2.1. With Objects

Most MIPPv1 programs use the objects `mipp::Reg<T>` and `mipp::Msk<N>`. Their counterpart is the C++ Object API.

**MIPPv1:**

<!-- not-compiled: MIPPv1 code -->
```cpp
#include "mipp.h"

// y[i] = x[i] < 0 ? alpha * x[i] : x[i], n being a multiple of N
void leaky_relu(std::size_t n, float alpha, const float* x, float* y)
{
    constexpr int N = mipp::N<float>();
    for (std::size_t i = 0; i < n; i += N) {
        mipp::Reg<float> rx = &x[i];                          // load, unaligned by default
        mipp::Msk<N>     m  = rx < 0.f;                       // the mask is typed by a number of elements
        mipp::Reg<float> ry = mipp::blend(rx * alpha, rx, m); // m ? rx * alpha : rx
        ry.store(&y[i]);                                      // member function
    }
}
```

**MIPPv2:**

```cpp
--8<-- "examples/doc/migrating_from_mippv1/obj.cpp:includes"

--8<-- "examples/doc/migrating_from_mippv1/obj.cpp:loop"
```

What changed:

- **The header.** `"mipp.h"` becomes `<mipp_obj.hpp>`.
- **The types.** `mipp::Reg<T>` becomes `mipp::Vd<T>`, and `mipp::Msk<N>` becomes `mipp::Vm<T>`: a mask is written with the element type of the registers it goes with.
- **`blend` is `select`**, with the mask first: `blend(a, b, m)` becomes `select(m, a, b)`. Both take `a` where the mask is set.
- **No member functions.** `r.store(p)`, `a.add(b)` or `r.sqrt()` become the free functions `mipp::storeu(p, v)`, `mipp::add(a, b)` and `mipp::sqrt(v)`. Only `N()`, `operator[]`, `lo()`, `hi()` and `combine()` are members.
- **The stores name their alignment.** The constructor from a pointer is still an unaligned load, but `store` now requires an aligned pointer ([§3](#3-same-name-other-result)): the counterpart of `r.store(p)` is `mipp::storeu(p, v)`.
- **Scalar operands.** A scalar can be on both sides of an operator (`0.75f * v`), and the named functions accept scalars too (`mipp::max(v, 2.f)`, see [Scalar Forms](scalar_forms.md)). The scalar must have the element type exactly: `v + 1` does not compile for a `Vd<float>`, write `v + 1.f`.

!!! warning "`<mipp.h>` still exists, and it is the C API"
    A MIPPv1 program that keeps `#include "mipp.h"` finds the header of MIPPv2 and fails on every `mipp::` name. The C++ headers are `<mipp_obj.hpp>` (objects) and `<mipp.hpp>` (functions).

### 2.2. With Raw Registers

The low level of MIPPv1 (`mipp::reg`, `mipp::msk`, and functions that take the element type at each call) becomes the C++ Functional API.

**MIPPv1:**

<!-- not-compiled: MIPPv1 code -->
```cpp
const mipp::reg rzero  = mipp::set0<float>();
const mipp::reg ralpha = mipp::set1<float>(alpha);
for (std::size_t i = 0; i < n; i += N) {
    mipp::reg rx = mipp::loadu<float>(&x[i]);
    mipp::msk m  = mipp::cmplt<float>(rx, rzero);                            // T is given at each call
    mipp::reg ry = mipp::blend<float>(mipp::mul<float>(rx, ralpha), rx, m); // m ? rx * alpha : rx
    mipp::storeu<float>(&y[i], ry);
}
```

**MIPPv2:**

```cpp
--8<-- "examples/doc/migrating_from_mippv1/fun.cpp:includes"

--8<-- "examples/doc/migrating_from_mippv1/fun.cpp:loop"
```

`mipp::reg` and `mipp::msk` become `mipp::vd<T>` and `mipp::vm<T>`. The element type is deduced from the registers, so it is only written for the functions that take none (`mipp::set1<float>(alpha)`, `mipp::loadu<float>(p)`). The functions on masks no longer take the number of elements: `mipp::notb<N>(m)` becomes `mipp::notb(m)`. The conversions name their destination: `mipp::cvt<float, int32_t>(r)` becomes `mipp::cvt_int32(v)` (see [Vector Types & LMUL](vector_types_and_lmul.md)).

### 2.3. Types

| MIPPv1 | MIPPv2, C++ Object API | MIPPv2, C++ Functional API |
| :--- | :--- | :--- |
| `mipp::Reg<T>` | `mipp::Vd<T>` | `mipp::vd<T>` |
| `mipp::Msk<mipp::N<T>()>` | `mipp::Vm<T>` | `mipp::vm<T>` |
| `mipp::Reg_2<T>` (half register) | `mipp::Vd<T, -2>` | `mipp::vd<T, -2>` |
| `mipp::Regx2<T>` (two registers) | `mipp::Vd<T, 2>` | `mipp::vd<T, 2>` |
| `mipp::reg`, `mipp::msk` | (the members `v.vd` and `m.vm`) | `mipp::vd<T>`, `mipp::vm<T>` |
| `r.r`, `m.m` (raw members) | `v.vd`, `m.vm` | |
| `mipp::N<T>()` | `mipp::Vd<T>::N()` or `mipp::N<T>()` | `mipp::N<T>()` |

An object converts implicitly to its register (`mipp::Vd<T>` to `mipp::vd<T>`) and back, so the two C++ APIs can be mixed. `mipp::Regx2<T>` used for complex numbers has another counterpart: see [§4.5](#45-complex-numbers).

---

## 3. Same Name, Other Result

These functions exist in both versions and compile after the renaming of the types, but they do not compute the same thing. MIPPv2 follows the C language: integer arithmetic that wraps, conversions that truncate, shifts of signed integers that keep the sign. MIPPv1 exposed the behavior of the x86 instruction it had chosen for each function.

| Function | MIPPv1 | MIPPv2 | To get the result of MIPPv1 |
| :--- | :--- | :--- | :--- |
| `add`, `sub`, `+`, `-`, `hadd`, `sum` on 8-bit and 16-bit integers | Saturate: `100 + 100` is `127` in `int8_t`. | Wrap: `100 + 100` is `-56`. | [`adds`](../funcs_support/arithmetic/adds.md), [`subs`](../funcs_support/arithmetic/subs.md), [`hadds`](../funcs_support/reduction/hadds.md) |
| `rshift`, `>>` on signed integers | Logical: `-16 >> 2` is `0x3FFFFFFC` in `int32_t`. | Arithmetic: `-16 >> 2` is `-4`. | Shift the unsigned type (`cast`). |
| `cvt` from a floating-point type to an integer | Rounds to the nearest integer: `2.7f` gives `3`. | Truncates, as a C cast: `2.7f` gives `2`. | `cvt` of `round(v)`, except for the ties (next row). |
| `round`, for a tie | To the even integer: `2.5f` gives `2`. | Away from zero: `2.5f` gives `3`. | None. |
| `div2`, `div4` on negative integers | Toward zero: `-7` gives `-3` and `-1`. | Arithmetic shift: `-7` gives `-4` and `-2`. | Add 1 (3 for `div4`) to the negative elements first. |
| `load`, `store`, `r.load(p)`, `r.store(p)` | Unaligned, unless `MIPP_ALIGNED_LOADS` is defined. | Aligned: a pointer that is not aligned is undefined behavior (a fault on x86). | `loadu`, `storeu` ([Memory & Alignment](memory_and_alignment.md)). |
| `copysign(a, b)` | Flips the sign of `a` where `b` is negative (an alias of `neg(a, b)`): `copysign(-3, -1)` is `3`. | Magnitude of `a`, sign of `b`, as `std::copysign`: `-3`. | [`xorsign(a, b)`](../funcs_support/math/xorsign.md) |
| `sign(r)`, now `signbit(v)` | `r < 0`: false for `-0.0`. | Sign bit set: true for `-0.0`. | `v < 0` |

The 8-bit and 16-bit additions are the change that is the easiest to miss, since most programs never overflow in their tests:

```cpp
--8<-- "examples/doc/migrating_from_mippv1/obj.cpp:saturation"
```

Shifts and conversions:

```cpp
--8<-- "examples/doc/migrating_from_mippv1/obj.cpp:shift"
--8<-- "examples/doc/migrating_from_mippv1/obj.cpp:conversion"
```

Signs:

```cpp
--8<-- "examples/doc/migrating_from_mippv1/obj.cpp:signs"
```

Two other differences are compile errors, not silent changes. The indices of `gather` and `scatter` are **unsigned** integers (`mipp::Vd<uint32_t>` for `float`), where MIPPv1 took signed ones. And the constructor of a mask from an array takes `int32_t` values, not `bool` ([Programming Model §4.1](programming_model.md#41-class-structure-constructors)).

---

## 4. Correspondence Tables

The MIPPv2 column is written with the C++ Object API. The C++ Functional API has the same function names (on `mipp::vd<T>` and `mipp::vm<T>`), and the C API adds the type to the name (`mipp_add_float32`).

Most functions keep their name and their meaning: `mul`, `div`, `fmadd`, `fnmadd`, `fmsub`, `fnmsub`, `min`, `max`, `abs`, `sqrt`, `rsqrt`, `trunc`, `andb`, `andnb`, `orb`, `xorb`, `notb`, `msb`, `cmpeq`, `cmpneq`, `cmplt`, `cmple`, `cmpgt`, `cmpge`, `select`, `exp`, `log`, `sin`, `cos`, `tan`, `sinh`, `cosh`, `tanh`, `asinh`, `acosh`, `atanh`, `hmul`, `hmin`, `hmax`, `get`, `getfirst`, `gather`, `scatter`, and the operators of the objects. The tables below list the others.

### 4.1. Memory and Initialization

| MIPPv1 | MIPPv2 | Notes |
| :--- | :--- | :--- |
| `Reg<T> r = p`, `r.load(p)`, `r.loadu(p)`, `mipp::oload<T>(p)`, `mipp::oloadu<T>(p)` | `Vd<T> v(p)`, `mipp::loadu_obj<T>(p)` | `mipp::load_obj<T>(p)` for an aligned pointer. |
| `r.store(p)`, `r.storeu(p)`, `mipp::store(p, r)` | `mipp::storeu(p, v)` | `mipp::store(p, v)` for an aligned pointer. |
| `Reg<T> r = val`, `r.set1(val)`, `mipp::oset1<T>(val)` | `Vd<T> v(val)`, `mipp::set1_obj<T>(val)` | |
| `r.set0()`, `mipp::oset0<T>()` | `mipp::set0_obj<T>()` | |
| `Reg<T> r = {a, b, c, d}`, `r.set(vals)`, `mipp::oset<T>(vals)` | `Vd<T> v = {a, b, c, d}`, `mipp::set_obj<T>(vals)` | The list has `N()` values, or one value that is broadcast. |
| `Msk<N> m = {true, false, ...}`, `Msk<N>(bools)` | `Vm<T> m = {true, false, ...}`, `mipp::set_k_obj<T>(ints)` | An array of `int32_t`, not of `bool`. |
| `mipp::maskzld(m, p)`, `mipp::maskzlds(m, p)` | `mipp::loadu_obj<mipp::Z>(m, p)` | The inactive lanes are never read. |
| `mipp::maskst(m, p, r)`, `mipp::masksts(m, p, r)` | `mipp::storeu<mipp::M>(m, p, v)` | The inactive lanes are never written. |
| `mipp::maskzgat(m, p, idx)`, `mipp::masksca(m, p, idx, r)` | `mipp::gather<mipp::Z>(m, p, idx)`, `mipp::scatter<mipp::M>(m, p, idx, v)` | Unsigned indices. |
| `mipp::malloc<T>(n)`, `mipp::free(p)`, `mipp::vector<T>`, `mipp::allocator<T>` | Same names. | |
| `mipp::isAligned(p)` | `mipp::is_aligned(p)` | It always returned `true` in MIPPv1 without `MIPP_ALIGNED_LOADS`. |
| `mipp::RequiredAlignment` | `mipp::required_alignment()` | The macro `MIPP_REQUIRED_ALIGNMENT` is unchanged. |
| `std::cout << r`, `mipp::dump<T>(reg)` | `std::cout << v`, `mipp::dump<T>(vd)` | |

### 4.2. Arithmetic, Logic and Masks

| MIPPv1 | MIPPv2 | Notes |
| :--- | :--- | :--- |
| `blend(a, b, m)` | `select(m, a, b)` | |
| `sat(r, lo, hi)` | `clamp(v, lo, hi)` | Registers or scalars as bounds. |
| `neg(r, m)` | `neg<mipp::M>(m, v)` | A masked negation. |
| `neg(a, b)`, `copysign(a, b)` | `xorsign(a, b)` | `copysign` exists, with another meaning ([§3](#3-same-name-other-result)). |
| `sign(r)` | `signbit(v)` | |
| `msb(a, b)` | `msb(a ^ b)` | |
| `lshiftr(a, b)`, `rshiftr(a, b)`, `a << b`, `a >> b` (two registers) | `lshift(a, b)`, `rshift(a, b)` | No operator for a count per lane. |
| `lshift(r, n)`, `rshift(r, n)`, `r << n`, `r >> n` | Same. | `rshift` is arithmetic on the signed types ([§3](#3-same-name-other-result)). |
| `sum(r)`, `r.sum()` | `sum(v)`, `hadd(v)` | |
| `testz(m)` | `none(m)` | With `any`, `all` and `count`. |
| `testz(m1, m2)` | `testz(m1, m2)` | |
| `testz(r)`, `testz(a, b)` (registers) | `none(tovm(v))`, `none(tovm(a & b))` | `testz` only takes masks. |
| `m.toReg<T>()`, `mipp::toReg<T>(m)` | `tovd(m)` | The inverse is `tovm(v)`. |
| `mipp::andb(m, r)` (a mask and a register) | `v & tovd(m)` | Or the `Z` variant of the function that produced `v`. |
| `mipp::mask<T, mipp::op>(m, src, a, b)` | `mipp::op<mipp::S>(m, src, a, b)` | `mipp::op<mipp::M>(m, a, b)` when `src` is `a`. |
| `mipp::maskz<T, mipp::op>(m, a, b)` | `mipp::op<mipp::Z>(m, a, b)` | |
| `mipp::Reduction<T, mipp::op>::sapply(r)` | `mipp::reduce(v, mipp::op::add())` | `add`, `mul`, `min`, `max`, `andb`, `orb`, `xorb`, or a functor. |
| `mipp::Reduction<T, mipp::op>::apply(p, n)` | `mipp::reduce(p, n, mipp::op::add())` | Any `n` above 0 (a multiple of N in MIPPv1). |
| `sincos(r, s, c)`, `sincos(r)`, `cossin(r)` | `sin(v)` and `cos(v)` | Two calls. |

```cpp
--8<-- "examples/doc/migrating_from_mippv1/obj.cpp:masked"
```

```cpp
--8<-- "examples/doc/migrating_from_mippv1/obj.cpp:reductions"
```

### 4.3. Conversions and Half Registers

| MIPPv1 | MIPPv2 | Notes |
| :--- | :--- | :--- |
| `mipp::cvt<T1, T2>(r)`, `r.cvt<T2>()` | `mipp::cvt<T2>(v)` | Truncates ([§3](#3-same-name-other-result)). |
| `mipp::cast<T1, T2>(r)`, `r.cast<T2>()` | `mipp::cast<T2>(v)` | |
| `mipp::low(r)`, `mipp::high(r)` | `v.lo()`, `v.hi()`, `mipp::lo(v)`, `mipp::hi(v)` | A `Vd<T, -2>`, for every type. |
| `mipp::combine(lo, hi)` | `mipp::combine(lo, hi)`, `lo.combine(hi)` | |
| `mipp::cvt<T1, T2>(Reg_2<T1>)` (widening) | `mipp::wcvt<T2>(v.lo())` | `wcvt` of a whole register gives a group of LMUL 2. |
| `mipp::pack<T1, T2>(a, b)` | `mipp::pack<T2>(a, b)` | Saturates to the range of `T2`, unsigned types included. |

```cpp
--8<-- "examples/doc/migrating_from_mippv1/obj.cpp:halves"
```

### 4.4. Rearrangements

MIPPv2 names the rearrangements after what happens to the lanes, and each one works on the whole register on every target ([Rearrangements](rearrangements.md)). The variants `_b128` apply the operation in each block of 128 bits: they are the counterpart of the MIPPv1 functions with a `2` suffix on AVX, and with a `4` suffix on AVX-512.

| MIPPv1 | MIPPv2 | Notes |
| :--- | :--- | :--- |
| `lrot(r)` | `rotate(v, 1)` | |
| `rrot(r)` | `rotate(v, N - 1)` | |
| `combine<S>(a, b)` | `slide(a, b, S)` | `S` is an ordinary argument. |
| `interleavelo(a, b)`, `interleavehi(a, b)` | `ziplo(a, b)`, `ziphi(a, b)` | |
| `interleave(a, b)` | `combine(ziplo(a, b), ziphi(a, b))` | A group of LMUL 2. |
| `deinterleave(a, b)` | `unziplo(a, b)`, `unziphi(a, b)` | |
| `interleavelo2`, `interleavehi2` on AVX, `interleavelo4`, `interleavehi4` on AVX-512 | `ziplo_b128(a, b)`, `ziphi_b128(a, b)` | |
| `interleave(r)` (one register) | `zip(v)` | The inverse is `unzip(v)`. |
| `cmask(ids)` then `shuff(r, cm)` | `permute(v, idx)` | `idx` is a register of unsigned integers that holds the indices themselves. |
| `cmask2`, `cmask4` then `shuff2`, `shuff4` | `permute_b128(v, idx)`, or `permute` | `permute_b128` when the parts are blocks of 128 bits. |
| `compress(r, m)` | `compress(v, m)` | No library to link. With `expand`, and `storeu_compress` to filter an array. |

```cpp
--8<-- "examples/doc/migrating_from_mippv1/obj.cpp:rearrangements"
```

### 4.5. Complex Numbers

MIPPv1 keeps N complex numbers in a `mipp::Regx2<T>`: N real parts in one register, N imaginary parts in the other. MIPPv2 has no complex type. Its complex functions work on the **interleaved layout**, the one of `std::complex<T>` arrays: a register of N lanes holds N / 2 complex numbers, the real part in the even lane.

| MIPPv1 | MIPPv2 | Notes |
| :--- | :--- | :--- |
| `Regx2<T> z = p` after a `deinterleave` | `Vd<T> z(p)` | An array of `std::complex<T>` is loaded as it is. |
| `cadd(a, b)`, `csub(a, b)`, `a + b`, `a - b` | `a + b`, `a - b` | The ordinary functions. |
| `cmul(a, b)`, `cmulconj(a, b)`, `cdiv(a, b)`, `conj(a)` | Same names. | On the interleaved layout. |
| `norm(a)` | `cnorm(a)` | The squared modulus, in both lanes of each pair. `cabs(a)` is the modulus. |

```cpp
--8<-- "examples/doc/migrating_from_mippv1/obj.cpp:complex"
```

A program that keeps the real and imaginary parts in two arrays does not need these functions: the ordinary ones compute on N complex numbers at a time ([Complex Numbers §3](complex_numbers.md#3-split-layout)).

### 4.6. Configuration and Introspection

| MIPPv1 | MIPPv2 | Notes |
| :--- | :--- | :--- |
| `MIPP_NO_INTRINSICS` | `MIPP_SCALAR` | The registers keep their size: N is not 1. |
| `MIPP_ALIGNED_LOADS` | None. | The alignment is in the name of the function (`load`, `loadu`). |
| `MIPP_STATIC_LIB` | None. | Nothing to link. |
| `MIPP_ENABLE_BACKTRACE` | None. | No function throws for a missing implementation. |
| `mipp::nElReg<T>()`, `mipp::nElmtsPerRegister<T>()` | `mipp::N<T>()` | |
| `mipp::InstructionType`, `mipp::InstructionFullType`, `mipp::InstructionVersion`, `mipp::InstructionExtensions()` | `mipp_info()` | It prints the target. The macros `MIPP_SSE`, `MIPP_AVX`, `MIPP_AVX512`, `MIPP_NEON`, `MIPP_SVE`, `MIPP_RVV` and `MIPP_SCALAR` select code at compile time. |
| `mipp::RegisterSizeBit`, `MIPP_REGISTER_SIZE` | `MIPP_RVD_SIZE_BYTE` | In bytes. |
| `find_package(MIPP)` and the target `MIPP::mipp` | The include directory of the headers. | |

---

## 5. No Equivalent

A few parts of MIPPv1 have no counterpart in MIPPv2:

- **Transpositions** (`transpose`, `transpose2`, `transpose8x8`, `transpose28x8`) and the functions `interleavex2`, `interleavex4` and `interleavex16`.
- **Shifts of the lanes of a mask** (`m << n`, `mipp::lshift<N>(m, n)`).
- **Interleaving by halves that are not blocks of 128 bits**: `interleavelo2` and `interleavehi2` on SSE and NEON (halves of 64 bits) and on AVX-512 (halves of 256 bits).
- **`sincos` and `cossin`**: call `sin` and `cos`.
- **`mipp::Lanes`**: the functions `_b128` replace the code that depended on it.
- **Run-time errors for a missing implementation**, and `MIPP_ENABLE_BACKTRACE` with them: what MIPPv1 reported at run time compiles in MIPPv2, or is a compile error.
- **Member functions** for the operations (`a.add(b)`, `r.sqrt()`, `a.blend(b, m)`).
