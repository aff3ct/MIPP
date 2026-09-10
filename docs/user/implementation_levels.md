# Implementation Levels & Fallback Solver

MIPP guarantees 100% API completeness across all supported architectures through a **4-tier fallback solver**. If an architecture lacks a native hardware instruction for a given datatype or operation, MIPP automatically resolves to the most optimal emulation strategy available.

---

## 1. The 4 Implementation Levels

Because all MIPP functions are declared `static inline`, the compiler inlines them directly at call sites without function call overhead. The implementation levels differentiate functions strictly by their **instruction mapping**, **instruction count**, and **level of vectorization**:

```
+-----------------------------------------------------------------------------+
|                     MIPP 4-Tier Fallback Hierarchy                          |
+-----------------------------------------------------------------------------+
|                                                                             |
|  [ Level 0: Optimal / Native ]                                              |
|    - 1:1 single-instruction mapping to a dedicated target SIMD intrinsic    |
|    - Minimal instruction count and optimal pipeline execution               |
|           |                                                                 |
|           v (if native single instruction does not exist)                   |
|  [ Level 1: Specific Emulated ]                                             |
|    - Target-specific multi-instruction sequence using ISA intrinsics        |
|    - Exploits architecture-specific hardware instructions & bit-tricks      |
|           |                                                                 |
|           v (if target-specific sequence is not implemented)                |
|  [ Level 2: Generic Emulated ]                                              |
|    - Algorithmic composition using portable MIPP SIMD primitives            |
|    - Fully vectorized, independent of target intrinsics                     |
|           |                                                                 |
|           v (if vectorized composition is unavailable)                      |
|  [ Level 3: Auto Scalar Fallback ]                                          |
|    - Sequential element-by-element scalar fallback                          |
|    - Guarantees complete API coverage and functional correctness            |
|    - Can be auto-vectorized by the compiler                                 |
|                                                                             |
+-----------------------------------------------------------------------------+
```

### Level 0: Optimal / Native
- **Definition**: Direct 1:1 mapping to a single hardware vector instruction or vendor intrinsic provided natively by the target ISA for that datatype.
- **Characteristics**: Lowest possible instruction count, minimum latency, and maximum hardware pipeline throughput.
- **Examples**:
    - `mipp_add_float32` on AVX $\to$ `_mm256_add_ps`
    - `mipp_add_float32` on RVV $\to$ `__riscv_vfadd_vv_f32m1`
    - `mipp_add_float32` on ARM NEON $\to$ `vaddq_f32`

### Level 1: Specific Emulated
- **Definition**: Target-specific emulation tailored to an ISA's instruction set when a single direct instruction is unavailable.
- **Performance**: High vector efficiency using handcrafted target assembly and intrinsic sequences.
- **Examples**:
    - Horizontal reduction on AVX (`hadd_float32`), using `_mm256_permute2f128_ps`, `_mm256_shuffle_ps`, and `_mm256_add_ps` to perform in-register tree reduction across 256-bit lanes.
    - Gather load emulation on baseline AVX prior to AVX2 hardware `vgather` instructions.

### Level 2: Generic Emulated
- **Definition**: Vectorized algorithms implemented on top of standard MIPP primitives.
- **Performance**: Fully vectorized execution across all SIMD lanes without scalar unrolling.
- **Examples**:
    - Composite arithmetic primitives on ISAs lacking dedicated instructions (e.g., emulating `fmadd(a, b, c)` as `add(mul(a, b), c)` on SSE or AVX without native FMA hardware).
    - Elementary math functions (such as vectorized `exp`, `log`, `sin`, `cos` polynomial expansions).
    - Software emulation of masked execution on targets lacking native instruction predication (evaluating unmasked operations and applying vector blending).

### Level 3: Auto Scalar Fallback
- **Definition**: Automated fallback to sequential scalar element processing.
- **Performance**: Functional fallback path with sequential latency.
- **Mechanics**: The vector register is unpacked into scalar values, processed element-by-element via scalar operators, and repacked into the output vector register. The code is generated in a way the compiler can auto-vectorized it but without guarantee.
- **Purpose**: Guarantees that no MIPP function call produces compilation or linking errors, allowing developers to write generic code across all supported datatypes regardless of hardware edge cases.

---

## 2. Inspecting Implementation Levels

Users can inspect the implementation level of any function through two mechanisms:

### 2.1. Header Comments
Every generated function definition in `<simd_ext/[isa]/c/functions/...>` contains an explicit comment declaring its level:

```c
static inline rvd_avx_float32_t mipp_avx_add_float32(const rvd_avx_float32_t r0, const rvd_avx_float32_t r1) {
    // Level 0 (Optimal / Native)
    rvd_avx_float32_t res;
    res.r = _mm256_add_ps(r0.r, r1.r);
    return res;
}
```

```c
static inline rvd_rvv_int64_t mipp_rvv_wcvt_int32_int64(const rvd_rvv_int32_t r0) {
    // Level 3 (Auto Scalar Fallback)
    rvd_scalar_int32_t s_r0 = {0};
    memcpy(&s_r0, &r0, sizeof(r0));
    rvd_scalar_int64_t sres = mipp_scalar_wcvt_int32_int64(s_r0);
    rvd_rvv_int64_t res;
    memcpy(&res, &sres, sizeof(res));
    return res;
}
```

### 2.2. Generator Summary Report
When regenerating MIPP headers via `python3 generator/gen_mipp_headers.py`, the generator produces an implementation matrix across all target ISAs.

Here is a example of output:
```
=====================================================================================
 MIPP Header Generator
=====================================================================================
  LMUL options: [1, 2, 4, 8] | LDIV options: [2]
-------------------------------------------------------------------------------------
  ➔ Cleaning old generated files... Done (elapsed time: 0.090 sec)!
  ➔ Generating SSE... Done (elapsed time: 0.753 sec)!
  ➔ Generating RVV1.0... Done (elapsed time: 3.474 sec)!
  ➔ Generating AVX... Done (elapsed time: 0.723 sec)!
  ➔ Generating AVX-512... Done (elapsed time: 0.769 sec)!
  ➔ Generating SVE... Done (elapsed time: 0.858 sec)!
  ➔ Generating NEON... Done (elapsed time: 0.615 sec)!
  ➔ Generating Scalar... Done (elapsed time: 1.552 sec)!
  ➔ Generating wrappers & C/C++ interface... Done (elapsed time: 0.827 sec)!

=======================================================================================================================================================================
 MIPP IMPLEMENTATION LEVEL SUMMARY
=======================================================================================================================================================================
Extension    |           Level 0 (Nat)           |           Level 1 (SpE)           |           Level 2 (GeE)           |           Level 3 (Sca)           |    Stubs
             |  Std   Msk   LM/D  |    Total     |  Std   Msk   LM/D  |    Total     |  Std   Msk   LM/D  |    Total     |  Std   Msk   LM/D  |    Total     |         
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
sse          |   340     0      0 |   340  (13%) |     0     0      0 |     0   (0%) |   223   426    519 |  1168  (45%) |   438   651      0 |  1089  (42%) |        0
rvv          |  1027   325   2500 |  3852  (29%) |   520   238   1397 |  2155  (16%) |   707   269   1779 |  2755  (21%) |  1054   438   2984 |  4476  (34%) |      762
avx          |   463     4      0 |   467  (16%) |    44     4      0 |    48   (2%) |   248   654    519 |  1421  (49%) |   304   672      0 |   976  (34%) |        0
avx512       |   491    30      0 |   521  (18%) |    25     8      0 |    33   (1%) |   253   652    519 |  1424  (48%) |   290   690      0 |   980  (33%) |      118
sve          |   348     0      0 |   348   (8%) |   364     0      0 |   364   (9%) |   994   654    519 |  2167  (53%) |   866   360      0 |  1226  (30%) |        0
neon         |   537     0      0 |   537  (20%) |    32     0      0 |    32   (1%) |   140   654    519 |  1313  (49%) |   266   555      0 |   821  (30%) |        0
scalar       |  2572  1014   7172 | 10758 (100%) |   N/A   N/A    N/A |          N/A |   N/A   N/A    N/A |          N/A |   N/A   N/A    N/A |          N/A |      N/A
=======================================================================================================================================================================
```

## 3. Performance Considerations Across Levels

Understanding implementation levels helps users interpret profiling data and compiler assembly:

- **Levels 0, 1, and 2 (Vectorized SIMD Paths)**:
    - **Level 0, Level 1, and Level 2 are all fully vectorized and highly performant**.
    - A function marked as **Level 2 (Generic Emulated)**, such as composite arithmetic (`fmadd`), horizontal reductions (`hadd`, `hmax`, `hmin`, `hmul`), or elementary math functions (`exp`, `log`, `sin`, `cos`), simply indicates that the target ISA lacks a dedicated, single hardware instruction for that operation. MIPP executes these via optimized, fully vectorized SIMD instruction sequences across all vector lanes with zero scalar serialization.
- **Level 3 (Sequential Scalar Fallback)**:
    - Level 3 is the only tier where the generated source code is sequential element-by-element rather than explicit SIMD instructions. In some cases, this code can be auto-vectorized by the compiler.
    - While Level 3 guarantees complete API coverage and functional correctness, performance-critical inner loops should avoid relying on Level 3 fallbacks. If a hotspot hits a Level 3 implementation, consider:
        - Checking if an alternative datatype has native hardware support on that architecture (e.g., using `float32` on architectures lacking 64-bit hardware floating-point units).
        - Contributing a Level 1 (target-specific intrinsic) or Level 2 (generic SIMD decomposition) implementation to the MIPP codebase.
