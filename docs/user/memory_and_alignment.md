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

When allocating buffers for aligned MIPP operations, use standard aligned memory allocators:

```cpp
// Alignment required by the active target ISA (e.g. 32 bytes on AVX2):
constexpr size_t alignment = mipp::req_alignment();

// POSIX aligned allocation (C99 / C++):
float* data_c = NULL;
posix_memalign((void**)&data_c, alignment, n_elements * sizeof(float));
free(data_c);

// C++17 aligned allocation (the size must be a multiple of the alignment):
const size_t bytes = ((n_elements * sizeof(float) + alignment - 1) / alignment) * alignment;
float* data = static_cast<float*>(std::aligned_alloc(alignment, bytes));
std::free(data);
```

In C, the equivalent constant is `MIPP_RVD_SIZE_BYTE`.

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

```c
// C API:
rvd_float32_t a = mipp_load_float32(ptr);   // ptr aligned on MIPP_RVD_SIZE_BYTE
rvd_float32_t b = mipp_loadu_float32(uptr); // any address

mipp_store_float32(out_ptr, a);
mipp_storeu_float32(uout, b);
```

```cpp
// C++ Functional API:
mipp::rvd<float> a = mipp::load<float>(ptr);   // ptr aligned on mipp::req_alignment()
mipp::rvd<float> b = mipp::loadu<float>(uptr); // any address

mipp::store(out_ptr, a);
mipp::storeu(uout, b);
```

```cpp
// C++ Object API:
mipp::Rvd<float> a = mipp::load_obj<float>(ptr);   // ptr aligned on mipp::req_alignment()
mipp::Rvd<float> b = mipp::loadu_obj<float>(uptr); // any address
mipp::Rvd<float> c(uptr);                          // the constructor performs an unaligned load

mipp::store(out_ptr, a);
mipp::storeu(uout, b + c);
```

!!! note "Migrating from MIPP v1"
    The `MIPP_ALIGNED_LOADS` macro of MIPP v1 (unaligned `load` / `store` by default, aligned only when the macro was defined) no longer exists: `load` / `store` are always aligned. Code that relied on the default must call `loadu` / `storeu`.

### 2.2. Masked Loads & Stores

A masked access reads or writes the active lanes only: inactive lanes are never accessed, so a mask can guard the end of an array (see the [masked remainder example](programming_model.md#5-example-remainder-handled-with-masked-memory-accesses)). Loads exist in the Zero-Masked (`Z`, inactive lanes set to 0) and Source-Masked (`S`, inactive lanes taken from `src`) variants, stores in the Merge-Masked variant (`M`, memory of inactive lanes left unchanged). The alignment contract of [§2.1](#21-aligned-vs-unaligned-access) is unchanged: masked `load` / `store` require an aligned pointer, masked `loadu` / `storeu` accept any address.

```c
// C API:
rvm_float32_t m = mipp_cmplt_float32(va, vlimit);

rvd_float32_t v_z = mipp_load_float32_maskz(m, ptr);        // inactive lanes: 0
rvd_float32_t v_s = mipp_load_float32_masks(m, v_src, ptr); // inactive lanes: v_src
mipp_store_float32_mask(m, out_ptr, v_z);                   // inactive lanes: memory unchanged

// LMUL = 2:
rvm_float32_m2_t m2  = mipp_cmplt_float32_m2(wa, wlimit);
rvd_float32_m2_t w_z = mipp_loadu_float32_maskz_m2(m2, uptr);
mipp_storeu_float32_mask_m2(m2, uout, w_z);
```

```cpp
// C++ Functional API:
mipp::rvm<float> m = mipp::cmplt(va, vlimit);

auto v_z = mipp::load<mipp::Z>(m, ptr);        // T deduced from the pointer, LMUL = 1
auto v_s = mipp::load<mipp::S>(m, v_src, ptr);
mipp::store<mipp::M>(m, out_ptr, v_z);

// LMUL = 2: the mask type does not allow the deduction of LMUL, give T and LMUL
mipp::rvm<float, 2> m2 = mipp::cmplt(wa, wlimit);
auto w_z = mipp::loadu<mipp::Z, float, 2>(m2, uptr);
mipp::storeu<mipp::M, float, 2>(m2, uout, w_z);
```

```cpp
// C++ Object API (T and LMUL deduced from the Rvm mask):
mipp::Rvm<float> m = (oa < olimit);

mipp::Rvd<float> v_z = mipp::load_obj<mipp::Z>(m, ptr);
mipp::Rvd<float> v_s = mipp::load_obj<mipp::S>(m, o_src, ptr);
mipp::store<mipp::M>(m, out_ptr, v_z);

mipp::Rvm<float, 2> m2 = (ow < owlimit);
mipp::Rvd<float, 2> w_z = mipp::loadu_obj<mipp::Z>(m2, uptr);
mipp::storeu<mipp::M>(m2, uout, w_z);
```

In the Object API, loads are named `load_obj` / `loadu_obj` (masked or not) so that they return an `Rvd`; stores keep the names `store` / `storeu`.

---

## 3. Non-Contiguous Memory Access: Gather & Scatter

When data elements reside at non-sequential memory addresses, MIPP provides vectorized **gather** and **scatter** operations using index vectors. The index vector holds unsigned integers of the same size as the data elements (`uint32_t` indices for `float` data, `uint64_t` indices for `double` data), counted in elements, not in bytes. For the masked variants, the mask has the type of the **index** vector (`rvm<uint32_t>` for a `float` gather).

### 3.1. Gather (Vectorized Indirect Load)
Loads elements from a base address using a vector of indices:

$$\text{res}_i = \text{base}_{ptr}[\text{indices}_i]$$

Masked variants: Zero-Masked (`Z`) and Source-Masked (`S`). Inactive lanes are not read.

```c
// C API:
rvd_uint32_t indices = mipp_load_uint32(idx_ptr);
rvd_float32_t res = mipp_gather_float32_float32(table, indices);

rvm_uint32_t m = mipp_cmplt_uint32(indices, vmax_idx);
rvd_float32_t res_z = mipp_gather_float32_float32_maskz(m, table, indices);
```

```cpp
// C++ Functional API:
mipp::rvd<uint32_t> indices = mipp::load<uint32_t>(idx_ptr);
mipp::rvd<float> res = mipp::gather(table, indices);

// Masked: the index type cannot be deduced, give T and the index type
mipp::rvm<uint32_t> m = mipp::cmplt(indices, vmax_idx);
mipp::rvd<float> res_z = mipp::gather<mipp::Z, float, uint32_t>(m, table, indices);
```

```cpp
// C++ Object API (T, the index type and LMUL deduced from the arguments):
mipp::Rvd<uint32_t> indices(idx_ptr);
mipp::Rvd<float> res = mipp::gather(table, indices);

mipp::Rvm<uint32_t> m = (indices < max_idx);
mipp::Rvd<float> res_z = mipp::gather<mipp::Z>(m, table, indices);
```

### 3.2. Scatter (Vectorized Indirect Store)
Writes elements of a vector into memory locations specified by a vector of indices:

$$\text{base}_{ptr}[\text{indices}_i] = \text{val}_i$$

Masked variant: Merge-Masked (`M`). Inactive lanes are not written.

```c
// C API:
rvd_uint32_t indices = mipp_load_uint32(idx_ptr);
mipp_scatter_float32_float32(out_table, indices, values);

rvm_uint32_t m = mipp_cmplt_uint32(indices, vmax_idx);
mipp_scatter_float32_float32_mask(m, out_table, indices, values);
```

```cpp
// C++ Functional API:
mipp::rvd<uint32_t> indices = mipp::load<uint32_t>(idx_ptr);
mipp::scatter(out_table, indices, values);

mipp::rvm<uint32_t> m = mipp::cmplt(indices, vmax_idx);
mipp::scatter<mipp::M, float, uint32_t>(m, out_table, indices, values);
```

```cpp
// C++ Object API:
mipp::Rvd<uint32_t> indices(idx_ptr);
mipp::scatter(out_table, indices, o_values);

mipp::Rvm<uint32_t> m = (indices < max_idx);
mipp::scatter<mipp::M>(m, out_table, indices, o_values);
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

```c
// C API:
rvd_float32_t v = mipp_load_float32(ptr);
float32_t first_val = mipp_getfirst_float32(v);
float32_t third_val = mipp_get_float32(v, 2);

// LMUL = 2: idx goes up to MIPP_N_FLOAT32_M2 - 1
rvd_float32_m2_t w = mipp_load_float32_m2(ptr);
float32_t w_first = mipp_getfirst_float32_m2(w);
float32_t w_last  = mipp_get_float32_m2(w, MIPP_N_FLOAT32_M2 - 1);
```

```cpp
// C++ Functional API:
mipp::rvd<float> v = mipp::load<float>(ptr);
float first_val = mipp::getfirst(v);
float third_val = mipp::get(v, 2);

// LMUL = 2: idx goes up to mipp::N<float, 2>() - 1
mipp::rvd<float, 2> w = mipp::load<float, 2>(ptr);
float w_first = mipp::getfirst(w);
float w_last  = mipp::get(w, mipp::N<float, 2>() - 1);
```

```cpp
// C++ Object API:
mipp::Rvd<float> v = mipp::load_obj<float>(ptr);
float first_val = mipp::getfirst(v);
float third_val = v[2];

// LMUL = 2: idx goes up to mipp::N<float, 2>() - 1
mipp::Rvd<float, 2> w = mipp::load_obj<float, 2>(ptr);
float w_first = mipp::getfirst(w);
float w_last  = w[mipp::N<float, 2>() - 1];

// Mask lanes (bool, Object API only until the warning above is lifted):
mipp::Rvm<float, 2> m = (w < limit);
bool last_active = m[mipp::N<float, 2>() - 1];
```
