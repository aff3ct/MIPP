# Memory Operations & Alignment

SIMD performance heavily depends on efficient data movement between system memory and vector registers. MIPP provides comprehensive primitives for aligned and unaligned contiguous memory access, non-contiguous indexed loads and stores (gather/scatter), and scalar element extraction.

---

## 1. Memory Alignment Requirements

SIMD vector instructions operate most efficiently when data addresses align with hardware vector register boundaries.

### 1.1. Required Alignment per Architecture

MIPP provides the `mipp::req_alignment<ISA>()` compile-time helper (and architecture sizing macros `MIPP_[ISA]_RVD_SIZE_BYTE`) declaring the required byte alignment:

| Architecture | Vector Register Width | Required Alignment (`req_alignment`) |
| :--- | :--- | :--- |
| **x86 SSE (1..4.2)** | 128-bit | **16 bytes** |
| **ARM NEON** | 128-bit | **16 bytes** |
| **x86 AVX / AVX2** | 256-bit | **32 bytes** |
| **x86 AVX-512** | 512-bit | **64 bytes** |
| **RISC-V Vector (RVV)** | `VLEN` bits | `MIPP_RVV_RVD_SIZE_BYTE` |
| **ARM SVE** | `VL` bits | `MIPP_SVE_RVD_SIZE_BYTE` |
| **Scalar Target** | Sized to `MIPP_SCALAR_SIZE` | `MIPP_SCALAR_RVD_SIZE_BYTE` |

### 1.2. Allocating Aligned Memory

MIPP allocates memory aligned for its aligned loads and stores (on the register size of the target, `MIPP_REQUIRED_ALIGNMENT` bytes):

```cpp
--8<-- "examples/doc/memory_and_alignment/alloc.cpp:alloc"
```

In C: `mipp_malloc(bytes)` (the size is rounded up to a multiple of the alignment, `NULL` on failure), `mipp_free(p)` and `mipp_is_aligned(p)`. `MIPP_REQUIRED_ALIGNMENT` is `MIPP_RVD_SIZE_BYTE`.

---

## 2. Contiguous Memory Operations

MIPP distinguishes between **aligned** (`load`, `store`) and **unaligned** (`loadu`, `storeu`) operations.

### 2.1. Aligned vs. Unaligned Access

| Operation | C API | C++ Functional API | C++ Object API | Pointer Requirement |
| :--- | :--- | :--- | :--- | :--- |
| **Aligned Load** | `mipp_load_[type]_[lmul]` | `mipp::load<T, LMUL>(ptr)` | `mipp::load_obj<T, LMUL>(ptr)` | Aligned on the register size ([§1.1](#11-required-alignment-per-architecture)) |
| **Unaligned Load** | `mipp_loadu_[type]_[lmul]` | `mipp::loadu<T, LMUL>(ptr)` | `mipp::loadu_obj<T, LMUL>(ptr)` or `Rvd<T, LMUL>(ptr)` | Any address |
| **Aligned Store** | `mipp_store_[type]_[lmul]` | `mipp::store(ptr, r)` | `mipp::store(ptr, r)` | Aligned on the register size ([§1.1](#11-required-alignment-per-architecture)) |
| **Unaligned Store** | `mipp_storeu_[type]_[lmul]` | `mipp::storeu(ptr, r)` | `mipp::storeu(ptr, r)` | Any address |

!!! warning "Alignment is a precondition"
    Passing a misaligned pointer to `load` or `store` is undefined behavior. On x86 (SSE, AVX, AVX-512), the aligned instructions fault. On ARM and RISC-V, the hardware does not distinguish aligned and unaligned vector accesses, so the same code may run there and fail on x86: respect the contract on every target, and use `loadu` / `storeu` whenever alignment is not guaranteed. On modern CPUs, `loadu` / `storeu` on data that happens to be aligned cost the same as `load` / `store`.

For a multi-register vector (`LMUL > 1`), the alignment required is still the size of one register: each register is loaded from an aligned address.

=== "C API"

    ```c
    --8<-- "examples/doc/memory_and_alignment/c.c:load_store"
    ```

=== "C++ Functional API"

    ```cpp
    --8<-- "examples/doc/memory_and_alignment/fun.cpp:load_store"
    ```

=== "C++ Object API"

    ```cpp
    --8<-- "examples/doc/memory_and_alignment/obj.cpp:load_store"
    ```

!!! note "Migrating from MIPP v1"
    The `MIPP_ALIGNED_LOADS` macro of MIPP v1 (unaligned `load` / `store` by default, aligned only when the macro was defined) no longer exists: `load` / `store` are always aligned. Code that relied on the default must call `loadu` / `storeu`.

### 2.2. Masked Loads & Stores

A masked access reads or writes the active lanes only: inactive lanes are never accessed, so a mask can guard the end of an array (see the [masked remainder example](programming_model.md#5-example-remainder-handled-with-masked-memory-accesses)). Loads exist in the Zero-Masked (`Z`, inactive lanes set to 0) and Source-Masked (`S`, inactive lanes taken from `src`) variants, stores in the Merge-Masked variant (`M`, memory of inactive lanes left unchanged). The alignment contract of [§2.1](#21-aligned-vs-unaligned-access) is unchanged: masked `load` / `store` require an aligned pointer, masked `loadu` / `storeu` accept any address.

=== "C API"

    ```c
    --8<-- "examples/doc/memory_and_alignment/c.c:masked"
    ```

=== "C++ Functional API"

    ```cpp
    --8<-- "examples/doc/memory_and_alignment/fun.cpp:masked"
    ```

=== "C++ Object API"

    ```cpp
    --8<-- "examples/doc/memory_and_alignment/obj.cpp:masked"
    ```

In the Object API, loads are named `load_obj` / `loadu_obj` (masked or not) so that they return an `Rvd`; stores keep the names `store` / `storeu`.

In the C++ Functional API, a masked access deduces `T` from the pointer and assumes `LMUL = 1`: the mask type does not allow the deduction of `LMUL`, so give `T` and `LMUL` for a multi-register vector (`mipp::loadu<mipp::Z, float, 2>`). In the C++ Object API, `T` and `LMUL` are deduced from the `Rvm` mask.

---

## 3. Non-Contiguous Memory Access: Gather & Scatter

When data elements reside at non-sequential memory addresses, MIPP provides vectorized **gather** and **scatter** operations using index vectors. The index vector holds unsigned integers counted in elements, not in bytes (`uint32_t` indices for `float` data, `uint64_t` indices for `double` data). The C names give the type of the data then the type of the index: `mipp_gather_float32_uint32`. For the masked variants, the mask has the type of the **data** (`rvm<float>` for a `float` gather, as for the masked loads); a mask computed on the indices is converted with `cast_k`. In the C++ Functional API, the masked variants cannot deduce the types: give `T` and the index type (`mipp::gather<mipp::Z, float, uint32_t>`). In the C++ Object API, they are deduced from the arguments.

### 3.0. Indices of Another Width than the Data

The indices can also be `uint32_t` or `uint64_t` whatever the width of the data: `uint32_t` indices for `double` data (`mipp_gather_float64_uint32`), `uint64_t` indices for `float` or `int8_t` data, etc. There is one index per element of data, so the index register then has **its own LMUL**: the LMUL of the data times $\text{size(index)} / \text{size(data)}$. With `double` data at LMUL 1, the `uint32_t` indices are a half-vector (`d2`); with `float` data at LMUL 1, the `uint64_t` indices are an LMUL 2 register. The LMUL in the name of the function is the one of the data, and the function only exists where the LMUL of the index does: from `m1` to `m8` for 32-bit indices of 64-bit data, from `m1` to `m4` for 64-bit indices of 32-bit data, etc. (not for the half-vectors of the data).

| Data | Index | Index LMUL for data at `m1` | Native |
| :--- | :--- | :--- | :--- |
| `float64`, `int64`, `uint64` | `uint32` | `d2` | AVX2, AVX-512 (`vgatherdpd`, `vscatterdpd`), SVE (`svunpklo` + gather), RVV |
| 32, 16 or 8-bit types | `uint64` | `m2`, `m4` or `m8` | RVV |
| 16 or 8-bit types | `uint32` | `m2` or `m4` | RVV |

Elsewhere the scalar fallback applies, as for the gathers of 8 and 16-bit elements on x86. With the C++ Object API, the LMUL of the result is deduced from the index (`mipp::gather(table, idx)` with an `Rvd<uint32_t, -2>` gives an `Rvd<double, 1>`); with the C++ Functional API, it is the LMUL of the data (`mipp::gather<mipp::Z, double, uint32_t, 1>`).

!!! warning "Range of the indices"
    Every index must address an element of the array. The 8-bit and 16-bit indices can take any value of their type. The 32-bit indices must be lower than $2^{31}$: the x86 gather and scatter instructions read them as signed integers. On RVV, the byte offset of a 32-bit element, $\text{index} \times 4$, is computed on 32 bits: the indices must be lower than $2^{30}$ (arrays of at most 4 GiB).

### 3.1. Gather (Vectorized Indirect Load)
Loads elements from a base address using a vector of indices:

$$\text{res}_i = \text{base}_{ptr}[\text{indices}_i]$$

Masked variants: Zero-Masked (`Z`) and Source-Masked (`S`). Inactive lanes are not read.

=== "C API"

    ```c
    --8<-- "examples/doc/memory_and_alignment/c.c:gather"
    ```

=== "C++ Functional API"

    ```cpp
    --8<-- "examples/doc/memory_and_alignment/fun.cpp:gather"
    ```

=== "C++ Object API"

    ```cpp
    --8<-- "examples/doc/memory_and_alignment/obj.cpp:gather"
    ```

### 3.2. Scatter (Vectorized Indirect Store)
Writes elements of a vector into memory locations specified by a vector of indices:

$$\text{base}_{ptr}[\text{indices}_i] = \text{val}_i$$

Masked variants: Merge-Masked (`M`), where the inactive lanes are not written, and Zero-Masked (`Z`), where they write zeros.

=== "C API"

    ```c
    --8<-- "examples/doc/memory_and_alignment/c.c:scatter"
    ```

=== "C++ Functional API"

    ```cpp
    --8<-- "examples/doc/memory_and_alignment/fun.cpp:scatter"
    ```

=== "C++ Object API"

    ```cpp
    --8<-- "examples/doc/memory_and_alignment/obj.cpp:scatter"
    ```

---

## 4. Scalar Element Extraction

MIPP provides primitives to extract individual scalar values from vector and mask registers:

| Operation | C API | C++ Functional API | C++ Object API | Returns |
| :--- | :--- | :--- | :--- | :--- |
| **Extract Element** | `mipp_get_[type]_[lmul](v, idx)` | `mipp::get(v, idx)` | `v[idx]` or `mipp::get(v, idx)` | Element `idx`, type `T`, with $0 \le \text{idx} < N$ and $N$ = `mipp::N<T, LMUL>()` (all the lanes of all the registers of the group) |
| **Get First Element** | `mipp_getfirst_[type]_[lmul](v)` | `mipp::getfirst(v)` | `mipp::getfirst(v)` | Element 0, type `T`, without shuffle |
| **Extract Mask Lane** | `mipp_get_k_[type]_[lmul](m, idx)` | `mipp::get(m, idx)` | `m[idx]` or `mipp::get(m, idx)` | Object API: `bool`. C and C++ Functional: see the warning below |

In C++, the mask-lane extraction has no `_k` suffix: it is the `get` overload taking a mask.

!!! warning "Mask-lane extraction in the C and C++ Functional APIs"
    `mipp_get_k_*` and `mipp::get(rvm, idx)` currently return the raw lane with the element type `T`: zero for an inactive lane, all bits set for an active one, which is **NaN** for `float` / `double`, `-1` for signed and the maximum value for unsigned types. Do not convert this value to an integer (converting a NaN is undefined behavior). Until these functions return a `0` / `1` value, read mask lanes with the Object API (`m[idx]` returns a `bool`).

=== "C API"

    ```c
    --8<-- "examples/doc/memory_and_alignment/c.c:extract"
    ```

=== "C++ Functional API"

    ```cpp
    --8<-- "examples/doc/memory_and_alignment/fun.cpp:extract"
    ```

=== "C++ Object API"

    ```cpp
    --8<-- "examples/doc/memory_and_alignment/obj.cpp:extract"
    ```
