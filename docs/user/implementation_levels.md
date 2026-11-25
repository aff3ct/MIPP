# Implementation Levels & Fallback Solver

Every MIPP function exists for all its datatypes on every supported target, through a **4-level fallback solver**: if an architecture lacks a native hardware instruction for a given datatype or operation, MIPP resolves to the best emulation available, down to a scalar loop. The few configurations where a function compiles but is not implemented are listed in [Known Limitations](#known-limitations).

---

## 1. The 4 Implementation Levels

Because all MIPP functions are declared `static inline`, the compiler inlines them directly at call sites without function call overhead. The implementation levels differentiate functions strictly by their **instruction mapping**, **instruction count**, and **level of vectorization**. The same badges mark the levels in the [API Explorer](../explorer/index.md) and the [Function Support](../funcs_support/index.md) pages: <span class="mipp-isa-badge lvl-0">L0</span> Native Hardware, <span class="mipp-isa-badge lvl-1">L1</span> Dedicated Emulation, <span class="mipp-isa-badge lvl-2">L2</span> Generic Emulation, <span class="mipp-isa-badge lvl-3">L3</span> Scalar Fallback.

![MIPP 4-level fallback hierarchy: L0 native hardware (one intrinsic), otherwise L1 dedicated emulation (sequence of intrinsics for this ISA), otherwise L2 generic emulation (composition of MIPP primitives), otherwise L3 scalar fallback (loop over the elements), with one example per level](../assets/images/fallback_levels.svg){ width="680" }

### <span class="mipp-isa-badge lvl-0">L0</span> Level 0: Native Hardware
- **Definition**: Direct 1:1 mapping to a single hardware vector instruction or vendor intrinsic provided natively by the target ISA for that datatype. The constants it needs do not count: a broadcast of a literal (`_mm512_set1_epi32(INT32_MIN)`, `vdupq_n_f32(0.5f)`) or an all-true predicate (`svptrue_b32()`) is materialized once, out of the loops, and a reinterpretation of a register (`svreinterpret_u32_s32`, `vreinterpretq_u32_f32`) generates no instruction. For example `mipp_neg_float32_mask` on AVX-512 is `_mm512_mask_xor_epi32` with the sign bit, and the unpredicated SVE operations are their `_x` form under `svptrue`.
- **Characteristics**: Lowest possible instruction count, minimum latency, and maximum hardware pipeline throughput.
- **Examples**:
    - `mipp_add_float32` on AVX $\to$ `_mm256_add_ps`
    - `mipp_add_float32` on RVV $\to$ `__riscv_vfadd_vv_f32m1`
    - `mipp_add_float32` on ARM NEON $\to$ `vaddq_f32`

### <span class="mipp-isa-badge lvl-1">L1</span> Level 1: Dedicated Emulation
- **Definition**: Target-specific emulation tailored to an ISA's instruction set when a single direct instruction is unavailable.
- **Performance**: High vector efficiency using handcrafted target assembly and intrinsic sequences.
- **Examples**:
    - Horizontal reduction on AVX (`hadd_float32`), using `_mm256_permute2f128_ps`, `_mm256_shuffle_ps`, and `_mm256_add_ps` to perform in-register tree reduction across 256-bit lanes.
    - Vectorized `exp` / `log` on AVX2 (`exp_float32`, `log_float32`), written once with AVX intrinsics (range reduction and polynomial evaluation on `__m256`) because the ISA has no instruction for them.

### <span class="mipp-isa-badge lvl-2">L2</span> Level 2: Generic Emulation
- **Definition**: Vectorized algorithms implemented on top of standard MIPP primitives.
- **Performance**: Fully vectorized execution across all SIMD lanes without scalar unrolling.
- **Examples**:
    - Composite arithmetic primitives on ISAs lacking dedicated instructions (e.g., emulating `fmadd(a, b, c)` as `add(mul(a, b), c)` on SSE or AVX without native FMA hardware).
    - Elementary math functions (such as vectorized `exp`, `log`, `sin`, `cos` polynomial expansions) on the ISAs that have no dedicated implementation of them.
    - Software emulation of masked execution on targets lacking native instruction predication (evaluating unmasked operations and applying vector blending).

### <span class="mipp-isa-badge lvl-3">L3</span> Level 3: Scalar Fallback
- **Definition**: Automated fallback to sequential scalar element processing.
- **Performance**: Functional fallback path with sequential latency.
- **Mechanics**: The vector register is unpacked into scalar values, processed element-by-element via scalar operators, and repacked into the output vector register. The code is written so that the compiler can auto-vectorize it, without guarantee.
- **Purpose**: Guarantees that MIPP function calls compile on every target, allowing developers to write generic code across all supported datatypes regardless of hardware edge cases (see [Known Limitations](#known-limitations) for the few remaining exceptions).

---

## 2. Inspecting Implementation Levels

Users can inspect the implementation level of any function through two mechanisms:

### 2.1. Header Comments
Every generated implementation in `include/mipp/internal/simd_ext/<isa>/c/functions/<category>/...` contains an explicit comment declaring its level (the short names without the `_m1` suffix are aliases of these functions):

<!-- not-compiled: example of generated code (include/mipp/internal/), not user code -->

```c
static inline vd_avx_float32_m1_t mipp_avx_add_float32_m1(const vd_avx_float32_m1_t vd0, const vd_avx_float32_m1_t vd1) {
    // Level 0 (Native Hardware)
    vd_avx_float32_m1_t res;
    res.vd = _mm256_add_ps(vd0.vd, vd1.vd);
    return res;
}
```

NEON has no 64-bit integer multiplication, so `mul` on `int64` falls back to the scalar reference:

<!-- not-compiled: example of generated code (include/mipp/internal/), not user code -->

```c
static inline vd_neon_int64_m1_t mipp_neon_mul_int64_m1(const vd_neon_int64_m1_t vd0, const vd_neon_int64_m1_t vd1) {
    // Level 3 (Scalar Fallback)
    vd_scalar_int64_m1_t s_vd0 = {0};
    memcpy(&s_vd0, &vd0, sizeof(vd0));
    vd_scalar_int64_m1_t s_vd1 = {0};
    memcpy(&s_vd1, &vd1, sizeof(vd1));
    vd_scalar_int64_m1_t sres = mipp_scalar_mul_int64_m1(s_vd0, s_vd1);
    vd_neon_int64_m1_t res;
    memcpy(&res, &sres, sizeof(res));
    return res;
}
```

### 2.2. Hardware Support Documentation
The online documentation provides complete capability breakdowns:

- **[Hardware Support Dashboard](../isas_support/index.md)**: Displays implementation level breakdowns and coverage statistics across all target architectures.
- **[Universal Intersection Matrix](../isas_support/intersection.md)**: Gives, for each function and datatype, the lowest level reached on every target (the worst level among the ISAs, Level 3 included).
- **[API Reference](../funcs_support/index.md)**: Each function reference page includes an interactive implementation matrix across all ISAs and masking modes.

## 3. Transitive Dependency Propagation & Hybrid Execution

In real-world SIMD code generation, algorithms are frequently composed of smaller primitives (e.g., polynomial evaluations, horizontal reductions, masking, or type casts). MIPP employs a **transitive level propagation solver** to guarantee both **optimal hybrid execution** and **honest performance reporting**:

### 3.1. Hybrid Vector-Scalar Execution (Performance Preservation)
When an operation is implemented via a composite template (such as elementary math functions or generic masked wrappers):

- If the majority of sub-operations are vectorized (Levels 0, 1, or 2), but a single helper operation requires a Level 3 scalar fallback on that specific target, **MIPP does not discard the vector template**.
- Dropping an entire multi-step function down to an element-by-element loop (`auto_scalar`) would discard the massive throughput gains provided by the 90%+ vectorized operations.
- Instead, MIPP generates the **hybrid SIMD + scalar implementation**, preserving the hardware vector acceleration across all available instructions.

### 3.2. Transitive Bottleneck Propagation (Honest Classification)
While the hybrid implementation is emitted for optimal execution, its official **implementation level** in the API reference matrices, header comments, and dashboard is determined by the **weakest link in its dependency graph**:

$$\text{EffectiveLevel}(F) = \max \Big( \text{BaseLevel}(F), \; \max_{D \in \text{Dependencies}(F)} \text{EffectiveLevel}(D) \Big)$$

- **Pure Vector Path**: If a Level 2 generic algorithm only invokes Level 0, 1, or 2 sub-operations, its effective level remains **Level 2 (Generic Emulation)**.
- **Transitive Scalar Fallback**: If a Level 2 (or Level 1) template invokes at least one operation that transitively resolves to a Level 3 scalar fallback on the target architecture, its effective level is evaluated as:
  $$\max(2, 3) = \mathbf{3}$$
  It is classified and documented as **Level 3 (Scalar Fallback)**.

!!! note
    **Concrete Example**: On AVX, `min` on `int64` is the generic composition `select(cmplt(a, b), a, b)` (Level 2). `select` is native (`_mm256_blendv_*`), but `cmplt` on `int64` is a scalar fallback, so `min_int64` is reported as **Level 3** even though the `select` stays vectorized.

---

## 4. Performance Considerations Across Levels

Understanding implementation levels helps users interpret profiling data and compiler assembly:

- **Levels 0, 1, and 2 (Vectorized SIMD Paths)**:
    - **Level 0, Level 1, and Level 2 are all fully vectorized and highly performant**.
    - A function marked as **Level 1 (Dedicated Emulation)** or **Level 2 (Generic Emulation)**, such as composite arithmetic (`fmadd` without FMA hardware), horizontal reductions (`hadd`, `hmax`, `hmin`), or elementary math functions (`exp`, `log`, `sin`, `cos`), simply indicates that the target ISA lacks a dedicated, single hardware instruction for that operation. MIPP executes these via fully vectorized SIMD instruction sequences with no scalar serialization.
- **Level 3 (Scalar Fallback)**:
    - Level 3 is the only level where the generated source code can be sequential element-by-element rather than explicit SIMD instructions (a Level 3 reached by propagation, [§3.2](#32-transitive-bottleneck-propagation-honest-classification), keeps its vector parts). In some cases, this code can be auto-vectorized by the compiler.
    - While Level 3 guarantees complete API coverage and functional correctness, performance-critical inner loops should avoid relying on Level 3 fallbacks. If a hotspot hits a Level 3 implementation, consider:
        - Checking if an alternative datatype has native hardware support on that architecture (e.g., using `float32` on architectures lacking 64-bit hardware floating-point units).
        - Contributing a Level 1 (Dedicated Emulation) or Level 2 (Generic Emulation) implementation to the MIPP codebase.

---

<a id="known-limitations"></a>
## 5. Known Limitations

The fallback hierarchy covers every `(function, datatype, LMUL, mask variant, ISA)` combination on the main configurations of each target. In two configurations, a few functions compile but are not implemented yet:

| Configuration | Affected functions |
| :--- | :--- |
| **NEON on ARMv7** (32-bit Arm, no `__aarch64__`) | `float64` [half-vectors](vector_types_and_lmul.md#half-vectors) (`d2`): loads, stores, gathers, scatters, reductions, `set`, `set_k`, `testz`, `none`, `combine`; and the functions that turn an `m1` register into a `d2` one or back for `float64` (`lo` and `hi`, also on masks, `ncvt` to `float32`, `wcvt` from `float32`). |
| **RVV without 64-bit elements or with VLEN < 128** (`__riscv_v_elen < 64`, `__riscv_v_elen_fp < 64` for `float64`, or `__riscv_v_fixed_vlen < 128`, as with the `Zve32*` and `Zve64*` embedded profiles) | Most 64-bit half-vector (`d2`) operations, and `lo`, `hi`, `combine`, `wcvt` and `ncvt` on 64-bit elements at every LMUL. With `MIPP_RVV_LDIV_VL` or `MIPP_RVV_LDIV_HYBRID` ([Vector Types & LMUL §4.3](vector_types_and_lmul.md#43-rvv-half-vectors-hardware-or-by-vl)), the 64-bit half-vectors are native when the core has 64-bit elements. |

With the standard RVV `V` extension (VLEN $\ge$ 128, 64-bit elements) and on AArch64, every function is implemented. When one of the functions above is called, it reports the following message, then terminates the program in C (`exit(-1)`) or throws `mipp::stub_exception` in C++:

```text
MIPP panic: 'mipp_<isa>_<function>_<datatype>[_<variant>]_<lmul>' is unimplemented.
```
