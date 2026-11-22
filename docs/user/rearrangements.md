# Rearrangements

The rearrangements move lanes inside a register, or between two registers: reverse the lanes, interleave two registers, extract a window, broadcast a lane...

---

## 1. Whole Register, Whole Group

A rearrangement works on the **whole register**, and on the **whole group** of N × LMUL lanes for an LMUL above 1: `reverse` of a `float32` register of LMUL 2 reverses its 2N lanes, the lanes of the second register coming first. This is the only semantics that does not depend on the size of the registers (SVE and RVV) and on the way an ISA builds the LMUL groups (one register of RVV, several registers elsewhere).

Most functions also have a variant **by block of 128 bits**, suffix `_b128`: the operation is applied in each block of 128 bits of the register, independently. It is the native semantics of many x86 instructions (`unpcklps`, `shufps`, `palignr`), and the right one for data made of small fixed blocks (4 × `float32` coordinates, pairs of `float64` complex numbers). When the register is not larger than 128 bits (SSE, NEON, half-vectors), `f_b128` is `f`.

| Function | Result | `_b128` |
| :--- | :--- | :---: |
| `reverse(a)` | `a[N-1], ..., a[0]` | yes |
| `swap_pairs(a)` | `a1, a0, a3, a2, ...` | (pairs) |
| `dup_even(a)` / `dup_odd(a)` | `a0, a0, a2, a2, ...` / `a1, a1, a3, a3, ...` | (pairs) |
| `zip_lo(a, b)` / `zip_hi(a, b)` | `a0, b0, a1, b1, ...` from the lower / upper halves | yes |
| `unzip_even(a, b)` / `unzip_odd(a, b)` | even / odd lanes of `a` then `b` | yes |
| `interleave(a)` / `deinterleave(a)` | planar to interleaved layout and back, in one register | — |
| `slide(a, b, n)` | window of N lanes at `n` in `a` then `b` (0 ≤ n ≤ N) | yes |
| `slide_up(a, n)` / `slide_down(a, n)` | lanes moved up / down by `n`, zeros entering | yes |
| `rotate(a, n)` | lane i receives `a[(i + n) mod N]` (0 ≤ n < N) | yes |
| `broadcast_lane(a, k)` | `a[k]` in every lane (0 ≤ k < N) | yes |
| `load_interleaved2(p)` / `store_interleaved2(p, a)` | `deinterleave(loadu(p))` / `storeu(p, interleave(a))` | — |
| `permute(a, idx)` | `a[idx[0]], a[idx[1]], ...` (indices < N) | yes |
| `permute2(a, b, idx)` | the same in `a` then `b` (indices < 2N) | — |
| `compress(a, m)` / `expand(a, m)` | active lanes packed first, zeros after / the inverse | — |
| `compress_store(p, a, m)` / `compress_store_full(p, a, m)` | active lanes stored, their count returned | — |
| `expand_load(p, m)` | `count(m)` elements loaded into the active lanes | — |

`swap_pairs`, `dup_even` and `dup_odd` work on pairs of lanes, which never straddle two blocks: they have no `_b128` variant. The numbers of lanes (`n`, `k`) are counted in the whole group, or in a block for the `_b128` variants; a value out of the range is undefined behavior. They are ordinary `int32_t` arguments, not immediates: a constant or a variable.

The [mask variants](masking_semantics.md) apply the mask after the rearrangement (the merge masking keeps the lanes of the first register).

---

## 2. Named Rearrangements

Two registers interleaved, then separated again. The interleaving of two registers of LMUL 1 is a register of LMUL 2: `combine(zip_lo(a, b), zip_hi(a, b))`, whose halves `low` and `high` give back `a` and `b` with `unzip_even` and `unzip_odd`.

=== "C API"

    ```c
    --8<-- "examples/doc/rearrangements/c.c:named"
    ```

=== "C++ Functional API"

    ```cpp
    --8<-- "examples/doc/rearrangements/fun.cpp:named"
    ```

=== "C++ Object API"

    ```cpp
    --8<-- "examples/doc/rearrangements/obj.cpp:named"
    ```

---

## 3. Windows and Broadcasts

`slide(a, b, n)` is the `alignr` of x86 and the `ext` of ARM (MIPPv1 `combine<n>`); `rotate(a, n)` is `slide(a, a, n)`, and `slide_down(a, n)` is `slide(a, 0, n)`.

=== "C API"

    ```c
    --8<-- "examples/doc/rearrangements/c.c:slide"
    ```

=== "C++ Functional API"

    ```cpp
    --8<-- "examples/doc/rearrangements/fun.cpp:slide"
    ```

=== "C++ Object API"

    ```cpp
    --8<-- "examples/doc/rearrangements/obj.cpp:slide"
    ```

---

## 4. Interleaved Data

`load_interleaved2` loads N elements and separates the even and the odd ones: with LMUL 2, the two registers of LMUL 1 are the even and the odd elements of 2N elements, as ARM `vld2`. Below, the real and imaginary parts of N complex numbers.

=== "C API"

    ```c
    --8<-- "examples/doc/rearrangements/c.c:interleaved"
    ```

=== "C++ Functional API"

    ```cpp
    --8<-- "examples/doc/rearrangements/fun.cpp:interleaved"
    ```

=== "C++ Object API"

    ```cpp
    --8<-- "examples/doc/rearrangements/obj.cpp:interleaved"
    ```

---

## 5. Permutations

`permute(a, idx)` gives `a[idx[i]]` in the lane i. The indices are a register of unsigned integers of the width of the elements (`uint32_t` for `float32`), below N, the number of lanes of the whole group (2N for `permute2`, the number of lanes of a block for `permute_b128`); other values are undefined behavior. The indices of the 8-bit types cannot reach the lanes from 256.

=== "C API"

    ```c
    --8<-- "examples/doc/rearrangements/c.c:permute"
    ```

=== "C++ Functional API"

    ```cpp
    --8<-- "examples/doc/rearrangements/fun.cpp:permute"
    ```

=== "C++ Object API"

    ```cpp
    --8<-- "examples/doc/rearrangements/obj.cpp:permute"
    ```

---

## 6. Compress and Expand

`compress(a, m)` packs the active lanes of `a` at the beginning of the register, in order, and zeroes the other lanes; `expand(a, m)` is the inverse. `count(m)` is the number of active lanes. To store the result:

- `compress_store(p, a, m)` writes **exactly** the `count(m)` active lanes and returns this count;
- `compress_store_full(p, a, m)` writes a **whole register** (the lanes after the count are unspecified) and returns the count: faster on the ISAs without a native masked store (SSE, AVX2, NEON). The memory of N elements from `p` must be writable: in a filter loop, each call overwrites the extra elements of the previous one, and the output needs N elements of margin.

`expand_load(p, m)` reads exactly `count(m)` elements. These functions have no half-vector (`d2`) version.

=== "C API"

    ```c
    --8<-- "examples/doc/rearrangements/c.c:filter"
    ```

=== "C++ Functional API"

    ```cpp
    --8<-- "examples/doc/rearrangements/fun.cpp:filter"
    ```

=== "C++ Object API"

    ```cpp
    --8<-- "examples/doc/rearrangements/obj.cpp:filter"
    ```

---

## 7. Implementation Levels

The rearrangements are native on most ISAs: `svrev`, `svzip1`, `svuzp1`, `svsplice`, `svdup_lane`, `svtbl`, `svcompact` on SVE; `vzip1q`, `vuzp1q`, `vtrn1q`, `vrev64q`, `vqtbl1q` on NEON (AArch64); `unpcklps`, `shufps`, `vpermps`, `vpermt2ps`, `pshufb`, `vcompressps` on x86; `vrgather`, `vcompress`, `viota`, `vslideup` / `vslidedown` on RVV. `permute` of SSE and NEON computes the byte indices of the lanes for `pshufb` / `vqtbl1q`, and `compress` of SSE, AVX2 and NEON (32 and 64-bit elements) reads the shuffle of the mask in a small table of the headers. The others are generic (a slide through memory, `get` and `set1` for a broadcast) or, for some types and ISAs, written lane by lane (Level 3); the levels of each function are in its [reference page](../funcs_support/index.md).

With a software LMUL (every ISA but RVV), the LMUL > 1 versions combine the LMUL 1 functions on the registers of the group (`reverse` of LMUL 2: the two registers swapped and reversed). The half-vectors of SSE, NEON and SVE (a register of which only the lower half is used) go through the scalar functions.
