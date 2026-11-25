# Scalar Forms

Many functions take several data vectors: `sub(a, b)`, `fmadd(a, b, c)`, `cmplt(a, b)`... Their **scalar forms** take a scalar instead of some of these vectors: the scalar is used for every lane, as if it had been broadcast with `set1`.

---

## 1. Names

A form is written with one letter per data vector of the function, in order: `v` for a vector, `s` for a scalar of the element type. The function itself is the form with only `v` letters.

| Form | Meaning | C | C++ |
| :--- | :--- | :--- | :--- |
| `vv` | $a_i - b_i$ | `mipp_sub_float32(a, b)`, alias `mipp_sub_vv_float32` | `mipp::sub(a, b)` |
| `vs` | $a_i - s$ | `mipp_sub_vs_float32(a, s)` | `mipp::sub(a, s)` |
| `sv` | $s - b_i$ | `mipp_sub_sv_float32(s, b)` | `mipp::sub(s, b)` |
| `vsv` | $a_i \cdot s + c_i$ | `mipp_fmadd_vsv_float32(a, s, c)` | `mipp::fmadd(a, s, c)` |

- **C API.** The form comes right after the name of the function, before the type, the mask variant and the LMUL: `mipp_sub_sv_float32_maskz_m2`. Every function with scalar forms also has `_vv` aliases of its base names (`mipp_sub_vv_float32_maskz_m2` is `mipp_sub_float32_maskz_m2`), for code that spells all the forms.
- **C++ APIs.** The forms are overloads of the function: `mipp::sub(a, s)` and `mipp::sub(s, b)`. The scalar must have the element type exactly in the masked calls and in the Object API (`T` is deduced from it): `mipp::sub<mipp::M>(m, 10.f, va)` with a `float` register, not `10`.
- **Object API operators.** `va - 1.f`, `10.f - va` and `va < 0.f` already broadcast the scalar: they compute the same thing as the forms.

The forms exist for every datatype, mask variant and LMUL of their function. [§6](#6-functions-with-scalar-forms) lists them: the commutative functions have no `sv` form (`add(s, b)` is `add(b, s)`), and the functions whose scalar operand only gives a sign have the `vs` form only (`copysign`, `xorsign`).

---

## 2. Usage

=== "C API"

    ```c
    --8<-- "examples/doc/scalar_forms/c.c:forms"
    ```

=== "C++ Functional API"

    ```cpp
    --8<-- "examples/doc/scalar_forms/fun.cpp:forms"
    ```

=== "C++ Object API"

    ```cpp
    --8<-- "examples/doc/scalar_forms/obj.cpp:forms"
    ```

---

## 3. Masked Forms

The [mask variants](masking_semantics.md) apply to the forms. The merge masking (`M`, `_mask`) keeps the **first vector** of the form in the inactive lanes: for `sub_sv(s, b)`, the inactive lanes are $b_i$ (a scalar cannot be merged into). It is the convention of SVE (`svsubr_n_f32_m`).

=== "C API"

    ```c
    --8<-- "examples/doc/scalar_forms/c.c:masked"
    ```

=== "C++ Functional API"

    ```cpp
    --8<-- "examples/doc/scalar_forms/fun.cpp:masked"
    ```

=== "C++ Object API"

    ```cpp
    --8<-- "examples/doc/scalar_forms/obj.cpp:masked"
    ```

---

## 4. Shifts

The shifts take a count for each lane, in a register of the same type, or the same count for every lane:

| Function | Count | C | C++ | Object API |
| :--- | :--- | :--- | :--- | :--- |
| `lshift`, `rshift`, `rshiftl` | one per lane, a register | `mipp_lshift_int32(a, n)` | `mipp::lshift(a, n)` | `a << n` |
| `lshift_vs`, `rshift_vs`, `rshiftl_vs` | the same for every lane, an `int32_t` | `mipp_lshift_vs_int32(a, 3)` | `mipp::lshift(a, 3)` | `a << 3` |

With a constant count, the C++ APIs also have `mipp::lshift<3>(a)` / `mipp::rshift<3>(a)` / `mipp::rshiftl<3>(a)`, and the shift instructions with an immediate count are used (see [Constant Counts](rearrangements.md#31-constant-counts)). `rshift` is arithmetic (copies of the sign bit) for the signed types and logical (zeros) for the unsigned ones, like `>>` in C++20 (in C, the shift of a negative number is implementation-defined, and arithmetic with GCC, Clang and MSVC). `rshiftl` is logical for every type: a signed element is shifted as the unsigned integer of the same size, like `(int32_t)((uint32_t)a >> n)`. It has no operator. A count must be between 0 and the number of bits of the type minus 1: other counts are undefined behavior (the hardware differs). The per-lane shifts exist for the integers; `lshift_vs`, `rshift_vs` and `rshiftl_vs` also shift the bits of the floating-point numbers.

=== "C API"

    ```c
    --8<-- "examples/doc/scalar_forms/c.c:shifts"
    ```

=== "C++ Functional API"

    ```cpp
    --8<-- "examples/doc/scalar_forms/fun.cpp:shifts"
    ```

=== "C++ Object API"

    ```cpp
    --8<-- "examples/doc/scalar_forms/obj.cpp:shifts"
    ```

---

## 5. Implementation Levels

Every form has a generic implementation: the function with the scalar broadcast (`sub(a, set1(s))`). The broadcast is free, so a form has the [implementation level](implementation_levels.md) of its function. Some ISAs also have instructions that take a scalar operand, used directly:

- **RVV**: `.vx` / `.vf` instructions (`vfrsub.vf` for `sub_sv`, `vfmadd.vf` for `fmadd_vsv`, `vmslt.vx`...);
- **SVE**: `_n` intrinsics (`svsubr_n`, `svmla_n`, `svcmplt_n`...);
- **x86**, **NEON**: the broadcast and the operation of the function.

---

## 6. Functions with Scalar Forms

--8<-- "docs/includes/generated/forms.md"
