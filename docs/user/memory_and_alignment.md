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
// POSIX aligned allocation (C99 / C++):
float* data_c = NULL;
posix_memalign((void**)&data_c, alignment, N_elements * sizeof(float));
free(data_c);

// C++17 aligned allocation:
constexpr size_t alignment = mipp::req_alignment(); // Defaults to active host ISA
float* data = static_cast<float*>(std::aligned_alloc(alignment, N_elements * sizeof(float)));
std::free(data);
```

---

## 2. Contiguous Memory Operations

MIPP distinguishes between **aligned** (`load`, `store`) and **unaligned** (`loadu`, `storeu`) operations.

### 2.1. Aligned vs. Unaligned Access & The `MIPP_ALIGNED_LOADS` Macro

MIPP provides both explicit unaligned primitives (`loadu`, `storeu`) and default primitives (`load`, `store`):

| Operation | C99 Function Identifier | C++ Template Wrapper | Safety & Alignment Requirement |
| :--- | :--- | :--- | :--- |
| **Default Load** | `mipp_load_[type]_[lmul]` | `mipp::load<T, LMUL>(ptr)` | Emits **unaligned** loads by default; emits **aligned** loads if `MIPP_ALIGNED_LOADS` is defined. |
| **Explicit Unaligned Load** | `mipp_loadu_[type]_[lmul]` | `mipp::loadu<T, LMUL>(ptr)` | **Always safe on arbitrary addresses** regardless of macro definitions. |
| **Default Store** | `mipp_store_[type]_[lmul]` | `mipp::store(ptr, val)` | Emits **unaligned** stores by default; emits **aligned** stores if `MIPP_ALIGNED_LOADS` is defined. |
| **Explicit Unaligned Store** | `mipp_storeu_[type]_[lmul]` | `mipp::storeu(ptr, val)` | **Always safe on arbitrary addresses** regardless of macro definitions. |

!!! warning "Portability & Implementation Scope of `MIPP_ALIGNED_LOADS`"
    - `MIPP_ALIGNED_LOADS` is a legacy configuration flag retained from earlier MIPP versions primarily affecting **x86 backends** (SSE, AVX, AVX-512).
    - On architectures such as **RISC-V Vector (RVV)** and **ARM SVE**, vector load instructions (`vle32.v`, `svld1`) inherently handle memory access according to the ISA specification, and the `MIPP_ALIGNED_LOADS` macro is currently not enforced.
    - Because of this non-uniformity across backends, developers should rely on explicit `loadu` / `storeu` whenever unaligned memory access must be strictly guaranteed in portable code. Future MIPP revisions may either standardize alignment toggling homogeneously across all targets or deprecate the macro.

```c
// C API:
rvd_float32_t va_default   = mipp_load_float32(ptr);
rvd_float32_t va_unaligned = mipp_loadu_float32(ptr);

mipp_store_float32(out_ptr, va_default);
mipp_storeu_float32(out_ptr, va_unaligned);
```

```cpp
// C++ API:
auto va_default   = mipp::load<float>(ptr);       // Unaligned by default; aligned if -DMIPP_ALIGNED_LOADS
auto va_unaligned = mipp::loadu<float>(ptr);      // Always unaligned

mipp::store(out_ptr, va_default);
mipp::storeu(out_ptr, va_unaligned);
```

### 2.2. Masked Loads & Stores

MIPP supports conditional memory access to safely read and write vector elements without accessing out-of-bounds memory at array boundaries:

```c
// C API:
rvm_float32_t m = mipp_cmplt_float32(indices, limit_vec);

rvd_float32_t v_loaded = mipp_load_float32_maskz(m, ptr);

rvd_float32_t v_loaded_s = mipp_load_float32_masks(m, v_src, ptr);

mipp_store_float32_mask(m, out_ptr, v_result);
```

```cpp
// C++ API:
auto m = mipp::cmplt(indices, limit_vec);

// Zero-masked load (loads memory where m=1, zeroes remaining elements):
auto v_loaded = mipp::load<mipp::Z>(m, ptr);

// Source-masked load (preserves src vector where m=0):
auto v_loaded_s = mipp::load<mipp::S>(m, v_src, ptr);

// Masked store (writes only active elements to memory):
mipp::store<mipp::M>(m, out_ptr, v_result);
```

---

## 3. Non-Contiguous Memory Access: Gather & Scatter

When data elements reside at non-sequential memory addresses, MIPP provides vectorized **gather** and **scatter** operations using index vectors.

### 3.1. Gather (Vectorized Indirect Load)
Loads elements from a base address using a vector of integer offsets:

$$\text{res}_i = \text{base}_{ptr}[\text{indices}_i]$$

```c
// C API:
const float32_t* base_ptr = table;
rvd_uint32_t indices = mipp_load_uint32(idx_ptr);

rvd_float32_t res = mipp_gather_float32_float32(base_ptr, indices);
```

```cpp
// C++ API:
const float* base_ptr = table;
mipp::rvd<uint32_t> indices = mipp::load<uint32_t>(idx_ptr);

// Unmasked gather:
mipp::rvd<float> res = mipp::gather(base_ptr, indices);

// Masked gather (zero-masked):
auto m = mipp::cmplt(indices, max_idx_vec);
mipp::rvd<float> res_z = mipp::gather<mipp::Z>(m, base_ptr, indices);
```

### 3.2. Scatter (Vectorized Indirect Store)
Writes elements of a vector into memory locations specified by a vector of integer offsets:

$$\text{base}_{ptr}[\text{indices}_i] = \text{val}_i$$


```c
// C API:
float32_t* base_ptr = output_table;
rvd_uint32_t indices = mipp_load_uint32(idx_ptr);
rvd_float32_t values = compute_results();

mipp_scatter_float32_float32(base_ptr, indices, values);
```

```cpp
// C++ API:
float* base_ptr = output_table;
mipp::rvd<uint32_t> indices = mipp::load<uint32_t>(idx_ptr);
mipp::rvd<float> values = compute_results();

// Unmasked scatter:
mipp::scatter(base_ptr, indices, values);

// Masked scatter:
mipp::scatter<mipp::M>(m, base_ptr, indices, values);
```

---

## 4. Scalar Element Extraction

MIPP provides primitives to extract individual scalar values from vector and mask registers:

| Operation | C99 Function Identifier | C++ Template / Function | Description |
| :--- | :--- | :--- | :--- |
| **Extract Element** | `mipp_get_[type]_[lmul](v, idx)` | `mipp::get(v, idx)` | Extracts the scalar element at index `idx` ($0 \le \text{idx} < N$). |
| **Extract Mask Element** | `mipp_get_k_[type]_[lmul](m, idx)` | `mipp::get_k(m, idx)` | Extracts the boolean truthiness of mask element `idx`. |
| **Get First Element** | `mipp_getfirst_[type]_[lmul](v)` | `mipp::getfirst(v)` | Optimized extraction of element 0 (`v[0]`) without shuffle overhead. |

```c
// C API:
rvd_float32_t v = mipp_load_float32(ptr);

float32_t first_val = mipp_getfirst_float32(v);
float32_t third_val = mipp_get_float32(v, 2);

rvm_float32_t m = mipp_cmplt_float32(v, limit);
int32_t mask_val = mipp_get_k_float32(m, 2);
```

```cpp
// C++ API:
mipp::rvd<float> v = mipp::load<float>(ptr);

float first_val = mipp::getfirst(v);       // Fast element 0 extraction
float third_val = mipp::get(v, 2);          // Dynamic index extraction

mipp::rvm<float> m = mipp::cmplt(v, limit);
int32_t mask_val = mipp::get_k(m, 2);       // Mask element extraction
```
