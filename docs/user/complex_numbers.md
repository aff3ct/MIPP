# Complex Numbers

MIPP has no complex type: a register of `float32` or `float64` holds complex numbers in the **interleaved layout**, the layout of `std::complex<T>` and C `_Complex` arrays in memory. The real part of each complex number is in an even lane, its imaginary part in the next odd lane: a register of N lanes holds N / 2 complex numbers.

---

## 1. Functions

| Function | Result, for each pair of lanes |
| :--- | :--- |
| `cmul(a, b)` | $a b$ |
| `cmulconj(a, b)` | $a \bar{b}$ |
| `cfmadd(a, b, c)` | $a b + c$ |
| `cdiv(a, b)` | $a / b$ |
| `conj(a)` | $\bar{a}$ |
| `cnorm(a)` | $\lvert a \rvert^2 = a_r^2 + a_i^2$, in both lanes |
| `cabs(a)` | $\lvert a \rvert$, in both lanes |

- `cabs` does not overflow when $a_r^2 + a_i^2$ does: it divides the two parts by the larger one before squaring them (as `hypot`). It is $+\infty$ when a part is infinite, and $0$ for $0$.
- `cdiv` uses the algorithm of Smith: it divides by the part of $b$ of the larger absolute value, which avoids the overflows and most of the losses of $b_r^2 + b_i^2$. A division by $0$ gives infinities or NaNs, as the scalar division.
- `cnorm` and `cabs` write the result in the two lanes of each pair, so that it can divide or scale the complex numbers directly (`div(a, cabs(a))` normalizes them).

The functions exist for `float32` and `float64`, for every LMUL and [mask variant](masking_semantics.md); the masks are applied lane by lane, like any other function (use a mask whose lanes go by pairs to select complex numbers). A pair never straddles two registers of a group: with LMUL 2, the N / 2 first complex numbers are in the first register. The functions have no half-vector (`d2`) version.

---

## 2. Interleaved Layout

The complex numbers are loaded as they are in memory: `Z` below is an array of complex numbers `{re0, im0, re1, im1, ...}`.

=== "C API"

    ```c
    --8<-- "examples/doc/complex_numbers/c.c:interleaved"
    ```

=== "C++ Functional API"

    ```cpp
    --8<-- "examples/doc/complex_numbers/fun.cpp:interleaved"
    ```

=== "C++ Object API"

    ```cpp
    --8<-- "examples/doc/complex_numbers/obj.cpp:interleaved"
    ```

---

## 3. Split Layout

When the real and imaginary parts are in two separate arrays (structure of arrays), the ordinary functions compute the complex operations on N complex numbers at a time, with all the lanes useful and without moving them: this is usually the fastest layout for long loops. `load_interleaved2` gives the two parts from interleaved data, and `store_interleaved2` stores them back (see [Rearrangements](rearrangements.md)).

=== "C API"

    ```c
    --8<-- "examples/doc/complex_numbers/c.c:split"
    ```

=== "C++ Functional API"

    ```cpp
    --8<-- "examples/doc/complex_numbers/fun.cpp:split"
    ```

=== "C++ Object API"

    ```cpp
    --8<-- "examples/doc/complex_numbers/obj.cpp:split"
    ```

---

## 4. Implementation Levels

`cmul`, `cmulconj` and `cfmadd` are native on ARM: `vcmlaq` on NEON (Armv8.3 complex extension, `__ARM_FEATURE_COMPLEX`) and `svcmla` on SVE, two instructions per product. On x86, `cmul` uses `fmaddsub` (with FMA) or `addsub` (SSE3), and `moveldup` / `movehdup` to duplicate the parts. The other functions, and every function on the other ISAs, are generic: they combine `dup_even`, `dup_odd`, `swap_pairs` and arithmetic functions. The levels of each function are in its [reference page](../funcs_support/index.md).
