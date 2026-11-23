# Rearrangements

The rearrangements move lanes inside a register, or between two registers: reverse the lanes, interleave two registers, extract a window, broadcast a lane...

---

## 1. Whole Register, Whole Group

A rearrangement works on the **whole register**, and on the **whole group** of N × LMUL lanes for an LMUL above 1: `reverse` of a `float32` register of LMUL 2 reverses its 2N lanes, the lanes of the second register coming first. This is the only semantics that does not depend on the size of the registers (SVE and RVV) and on the way an ISA builds the LMUL groups (one register of RVV, several registers elsewhere).

Most functions also have a variant **by block of 128 bits**, suffix `_b128`: the operation is applied in each block of 128 bits of the register, independently. It is the native semantics of many x86 instructions (`unpcklps`, `shufps`, `palignr`), and the right one for data made of small fixed blocks (4 × `float32` coordinates, pairs of `float64` complex numbers). When the register is not larger than 128 bits (SSE, NEON, half-vectors), `f_b128` is `f`.

| Function | Result | `_b128` |
| :--- | :--- | :---: |
| `reverse(a)` | `a[N-1], ..., a[0]` | yes |
| `swap2(a)` | `a1, a0, a3, a2, ...` | (pairs) |
| `dupeven(a)` / `dupodd(a)` | `a0, a0, a2, a2, ...` / `a1, a1, a3, a3, ...` | (pairs) |
| `ziplo(a, b)` / `ziphi(a, b)` | `a0, b0, a1, b1, ...` from the lower / upper halves | yes |
| `unziplo(a, b)` / `unziphi(a, b)` | even / odd lanes of `a` then `b` | yes |
| `zip(a)` / `unzip(a)` | planar to interleaved layout and back, in one register | — |
| `slide(a, b, n)` | window of N lanes at `n` in `a` then `b` (0 ≤ n ≤ N) | yes |
| `slideup(a, n)` / `slidedown(a, n)` | lanes moved up / down by `n`, zeros entering | yes |
| `rotate(a, n)` | lane i receives `a[(i + n) mod N]` (0 ≤ n < N) | yes |
| `bcast(a, k)` | `a[k]` in every lane (0 ≤ k < N) | yes |
| `loadu_unzip(p)` / `storeu_zip(p, a)` | `unzip(loadu(p))` / `storeu(p, zip(a))` | — |
| `permute(a, idx)` | `a[idx[0]], a[idx[1]], ...` (indices < N) | yes |
| `permute2(a, b, idx)` | the same in `a` then `b` (indices < 2N) | — |
| `compress(a, m)` / `expand(a, m)` | active lanes packed first, zeros after / the inverse | — |
| `storeu_compress(p, a, m)` / `storeuf_compress(p, a, m)` | active lanes stored, their count returned | — |
| `loadu_expand(p, m)` | `count(m)` elements loaded into the active lanes | — |

`swap2`, `dupeven` and `dupodd` work on pairs of lanes, which never straddle two blocks: they have no `_b128` variant. The numbers of lanes (`n`, `k`) are counted in the whole group, or in a block for the `_b128` variants; a value out of the range is undefined behavior. They are ordinary `int32_t` arguments: a constant or a variable (see [§3.1](#31-constant-counts) for the constants).

The [mask variants](masking_semantics.md) apply the mask after the rearrangement (the merge masking keeps the lanes of the first register).

The names describe what happens to the lanes, not the instructions of one ISA ([Naming Conventions](../developer/reference/naming.md#names-that-differ-from-the-intrinsics)). The closest instructions, for the names that differ:

| MIPP | x86 | ARM | RVV |
| :--- | :--- | :--- | :--- |
| `slide(a, b, n)` | `alignr` | `ext` | `vslidedown` + `vslideup` |
| `slideup` / `slidedown` | `slli_si128` / `srli_si128` (bytes) | `ext` with zeros | `vslideup` / `vslidedown` |
| `bcast(a, k)` | `shuffle` / `permutexvar` | `dup` (element) | `vrgather` |
| `ziplo` / `ziphi` | `unpacklo` / `unpackhi` | `zip1` / `zip2` | — |
| `unziplo` / `unziphi` | `shuffle` | `uzp1` / `uzp2` | — |
| `dupeven` / `dupodd` | `moveldup` / `movehdup` | `trn1(a, a)` / `trn2(a, a)` | — |
| `swap2` | `shuffle` | `rev64` | — |
| `loadu_unzip` / `storeu_zip` | — | `vld2` / `vst2` | `vlseg2` / `vsseg2` |
| `compress` | `vcompressps` (AVX-512) | `svcompact` (SVE) | `vcompress` |

---

## 2. Named Rearrangements

Two registers interleaved, then separated again. The interleaving of two registers of LMUL 1 is a register of LMUL 2: `combine(ziplo(a, b), ziphi(a, b))`, whose halves `lo` and `hi` give back `a` and `b` with `unziplo` and `unziphi`.

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

`slide(a, b, n)` is the `alignr` of x86 and the `ext` of ARM (MIPPv1 `combine<n>`); `rotate(a, n)` is `slide(a, a, n)`, and `slidedown(a, n)` is `slide(a, 0, n)`.

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

### 3.1. Constant Counts

The number of lanes of `slide`, `slideup`, `slidedown`, `rotate`, `bcast` (and their `_b128` variants), the lane of `get` and the count of `lshift` / `rshift` (`lshift_vs` / `rshift_vs` in C) are often constants. Many instructions only exist with a constant encoded in them, an **immediate**: `palignr`, `pshufd`, `pextrd` on x86, `ext`, `dup` (element), `umov`, `shl` / `sshr` on NEON. The same function serves both cases:

- with a **variable**, the function runs its dynamic body: `slide` through `permute2` and indices `i + n` (`pshufb`, `vpermps`, `vpermt2ps`, `tbl`), `svsplice` on SVE, `vslidedown` / `vslideup` on RVV;
- with a **constant**, once the function is inlined (any optimization level but `-O0`), the immediate instruction: the function tests `__builtin_constant_p(n)` and selects it at compile time, at no run-time cost. `get` needs no such test: its dynamic body (store, then read of the lane) already becomes an extraction (`pextrd`, `vextracti128`, `umov`...) when the lane is a constant, with GCC as with Clang.

The C++ APIs also have a **template version**, `mipp::slide<2>(a, b)`, `mipp::get<3>(r)`, `mipp::lshift<4>(r)`, as the MIPPv1 `combine<2>(a, b)`: the value must be a constant, and a value out of the range is a compilation error (`static_assert`). It calls the same function with the constant.

=== "C API"

    ```c
    --8<-- "examples/doc/rearrangements/c.c:immediates"
    ```

=== "C++ Functional API"

    ```cpp
    --8<-- "examples/doc/rearrangements/fun.cpp:immediates"
    ```

=== "C++ Object API"

    ```cpp
    --8<-- "examples/doc/rearrangements/obj.cpp:immediates"
    ```

The immediate instructions are written for the unmasked functions of LMUL 1 on SSE, AVX2, AVX-512 and NEON (AArch64), where the instruction exists for the type. The masked variants call them; with an LMUL above 1, `slide` (and `rotate`, `slideup`, `slidedown`) slides the registers of the groups two by two with the LMUL 1 function when the count is a constant, and the other functions work register by register: the constant reaches the immediate instructions through the inlining. With `-O0`, or when the compiler does not inline the function, the dynamic body runs: the result is the same.

---

## 4. Interleaved Data

`loadu_unzip` loads N elements and separates the even and the odd ones: with LMUL 2, the two registers of LMUL 1 are the even and the odd elements of 2N elements, as ARM `vld2`. Below, the real and imaginary parts of N complex numbers.

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

- `storeu_compress(p, a, m)` writes **exactly** the `count(m)` active lanes and returns this count;
- `storeuf_compress(p, a, m)` writes a **whole register** (the lanes after the count are unspecified) and returns the count: faster on the ISAs without a native masked store (SSE, AVX2, NEON). The memory of N elements from `p` must be writable: in a filter loop, each call overwrites the extra elements of the previous one, and the output needs N elements of margin.

`loadu_expand(p, m)` reads exactly `count(m)` elements. These functions have no half-vector (`d2`) version.

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

## 7. Patterns Known at Compile Time (C++17)

With C++17, `mipp::permute<P>(a)` and `mipp::permute2<P>(a, b)` take the indices from a **pattern** `P`: a type with a function `static constexpr int get(int i, int n)` that gives the source lane of the lane `i` of the result, `n` being the number of lanes of the whole group (`[0, n)` for `permute`, `[0, 2n)` for `permute2`), or `-1` for a zero. The registers can be of any LMUL, half-vectors included. The number of lanes is a constant of the compilation on every ISA (SVE and RVV with a fixed register size), so the indices are known by the compiler:

- a pattern of a named rearrangement is replaced by its function: `reverse`, `rotate`, `bcast`, `slideup`, `slidedown`, `swap2`, `dupeven`, `dupodd` for one register; `slide`, `ziplo`, `ziphi`, `unziplo`, `unziphi` for two registers (and `permute` when all the indices of `permute2` are in one register);
- the other patterns are a `permute` / `permute2` with a constant table of indices, then a `select` for the zeros; with 8-bit elements and more than 256 lanes (or 128 for `permute2`), through memory.

An index out of `[-1, n)` (`[-1, 2n)` for `permute2`) is a compilation error. The patterns are an option of C++17: the C++11 API has the functions with indices in a register ([§5](#5-permutations)). They are in `mipp/cpp/patterns.hpp` and `mipp/obj/patterns.hpp`, included by `mipp.hpp` and `mipp_obj.hpp` but not by the [per-function headers](headers_and_compile_time.md): they pull about twenty rearrangement functions.

=== "C++ Functional API"

    ```cpp
    --8<-- "examples/doc/patterns/fun.cpp:patterns"
    --8<-- "examples/doc/patterns/fun.cpp:calls"
    ```

=== "C++ Object API"

    ```cpp
    --8<-- "examples/doc/patterns/obj.cpp:patterns"
    --8<-- "examples/doc/patterns/obj.cpp:calls"
    ```

---

## 8. Implementation Levels

The rearrangements are native on most ISAs: `svrev`, `svzip1`, `svuzp1`, `svsplice`, `svdup_lane`, `svtbl`, `svcompact` on SVE; `vzip1q`, `vuzp1q`, `vtrn1q`, `vrev64q`, `vqtbl1q` on NEON (AArch64); `unpcklps`, `shufps`, `vpermps`, `vpermt2ps`, `pshufb`, `vcompressps` on x86; `vrgather`, `vcompress`, `viota`, `vslideup` / `vslidedown` on RVV. `permute` of SSE and NEON computes the byte indices of the lanes for `pshufb` / `vqtbl1q`, and `compress` of SSE, AVX2 and NEON (32 and 64-bit elements) reads the shuffle of the mask in a small table of the headers. The others are generic (a slide through memory, `get` and `set1` for a broadcast) or, for some types and ISAs, written lane by lane (Level 3); the levels of each function are in its [reference page](../funcs_support/index.md).

With a software LMUL (every ISA but RVV), the LMUL > 1 versions combine the LMUL 1 functions on the registers of the group (`reverse` of LMUL 2: the two registers swapped and reversed). The half-vectors of SSE, NEON and SVE (a register of which only the lower half is used) go through the scalar functions.
