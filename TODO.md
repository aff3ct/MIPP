# MIPPv2 Release Roadmap & Pending Tasks

This document tracks pending engineering tasks, missing functionality relative to MIPPv1, architectural coverage gaps, planned generator enhancements, and future metaprogramming features for upcoming MIPPv2 releases.

---

## 1. MIPPv1 Function Parity & Missing Interfaces

MIPPv2 currently defines and generates **92 core vector primitives** across arithmetic, logic, comparison, math, reduction, load/store, conversions, and selection. Several specialized function families and utility modules from MIPPv1 have not yet been migrated to the MIPPv2 code generation pipeline.

### 1.1. Complex Arithmetic (`regx2` / Coordinate Pairs)
MIPPv1 provided complex-number vector arithmetic defined on register pairs (`regx2` representing interleaved or split real and imaginary components):
- [ ] `cadd`: Complex addition $((a_r + b_r) + i(a_i + b_i))$.
- [ ] `csub`: Complex subtraction $((a_r - b_r) + i(a_i - b_i))$.
- [ ] `cmul`: Complex multiplication $((a_r b_r - a_i b_i) + i(a_r b_i + a_i b_r))$.
- [ ] `cmulconj`: Complex multiplication with conjugate second operand $((a_r b_r + a_i b_i) + i(a_i b_r - a_r b_i))$.
- [ ] `cdiv`: Complex division ($\frac{a \cdot \bar{b}}{|b|^2}$).
- [ ] `conj`: Complex conjugation ($a_r - i a_i$).
- [ ] `norm`: Complex squared Euclidean norm ($a_r^2 + a_i^2$).
- [ ] `sincos`, `cossin`: Simultaneous evaluation of sine and cosine returning register pairs (`regx2` with sine/cosine or cosine/sine components).

### 1.2. Vector Interleaving & Deinterleaving
MIPPv1 provided a set of multi-stride interleaving and deinterleaving primitives for vector transpositions:
- [ ] `interleavelo`, `interleavehi`: Low/high lane interleaving of two registers.
- [ ] `interleavelo2`, `interleavehi2`: 2-element granular low/high interleaving.
- [ ] `interleavelo4`, `interleavehi4`: 4-element granular low/high interleaving.
- [ ] `interleave`, `deinterleave`: Full two-register zip and unzip operations returning `regx2`.
- [ ] `interleave2`, `interleave4`: Multi-stride 2-way and 4-way register interleaving returning `regx2`.
- [ ] `interleavex2`, `interleavex4`, `interleavex16`: Cross-lane intra-register interleaving permutations.

### 1.3. Permutation, Shuffling & Packing
- [ ] `shuff`, `shuff2`, `shuff4`: Arbitrary intra-vector element shuffling governed by control index vectors or immediate masks.
- [ ] `cmask`, `cmask2`, `cmask4`: Constant shuffle mask generation helpers for cross-lane byte swizzling.
- [ ] `compress`: Contiguous stream compaction (compressing active elements governed by a boolean mask into contiguous vector lanes, e.g., `_mm256_maskz_compress_epi32` / `vcompress`).
- [x] `low`, `high`, `combine` (and `_k` mask versions): Half-register extraction and slice concatenation, done on every ISA (`d2` ↔ `m1` ↔ `m2` ↔ ...). Native mask versions on RVV.
- [ ] `pack`: Saturating register narrowing from two inputs. `ncvt` (truncating, one input) covers the non-saturating case; a saturating `pack` is postponed.
  > **Note:** `wcvt` (widening, input at a lower LMUL: `d2` → `m1` → `m2`) and `ncvt` (narrowing by truncation, the inverse) are implemented with the LMUL-changing infrastructure (`ret.lmul` in the registry). Half-register slicing (`low`/`high`) and element conversions are now separate primitives.

### 1.4. Vector Rotations & Dynamic Shifts
- [ ] `lrot`, `rrot`: Left and right circular bitwise rotations of elements.
- [ ] `lshiftr`, `rshiftr`: Variable element-wise vector-by-vector left and right logical/arithmetic bit shifts (where shift counts vary per lane, e.g., `_mm256_sllv_epi32`).

### 1.5. Memory Management & Dynamic Buffers
- [ ] `isAligned`: Pointer alignment verification against target ISA alignment constraints (`MIPP_REQUIRED_ALIGNMENT`).
- [ ] `oloadu`: Unaligned load with explicit byte or element offset.
- [ ] `malloc`, `free`: Alignment-aware heap allocation wrappers ensuring memory conforms to target ISA alignment constraints (`MIPP_REQUIRED_ALIGNMENT`).
- [ ] `mipp::allocator<T>`: STL-compliant allocator ensuring aligned dynamic allocations for `std::vector`.
- [ ] `mipp::vector<T>`: Type alias for `std::vector<T, mipp::allocator<T>>`.

### 1.6. Reductions, Aliases & Diagnostics
- [ ] `reduction<T, OP>`: Higher-order template reduction engine evaluating arbitrary associative binary operators (`OP`) across vectors and raw array buffers.
- [ ] `sum`: Reduction alias for horizontal addition (`hadd`).
- [ ] `sat`: Dynamic clamping of vector elements between runtime scalar bounds $[min, max]$ (distinct from MIPPv2 `adds`/`subs` type-boundary saturation).
- [ ] `dump`: Formatted debug printing of vector and mask register contents to standard output streams.
- [ ] `any`, `all` (with `none` and `testz`): Boolean mask reductions returning `int32_t`. `none(m)` (no active lane, ex-`testz_2`) and `testz(m0, m1)` (AND of two masks) exist; `any(m)` (at least one active lane) and `all(m)` (all lanes active) are to be added.
  - Declare them in the registry (`ret_i32_1arg_msk`, `horizontal`, variant `u`), `funcs_docs.json`, categories, scalar implementation, tests specs, and the object API (`int32_t` return).
  - Generic Level 2: `any = !none(m)`, `all = none(notb_k(m))`. Beware: `all` via `notb_k` is wrong if the complement touches unused lanes (AVX-512 whole `__mmask`, partial LMUL such as `d2`): mask to the lane count or use a native form. Test all-zero, all-one, single-lane, `d2` and `m2` masks.
  - Later (optional) native Level 1 versions: `kortest` (AVX-512), `vfirst` / `vmsbf` (RVV), `svptest_any` (SVE), `vmaxvq` (NEON).

### 1.7. Summary of Function Renames & Architectural Evolution in MIPPv2
| MIPPv1 Concept | MIPPv2 Implementation | Architectural Rationale |
| :--- | :--- | :--- |
| `mipp::load_2<T>`, `mipp::loadu_2<T>` | `mipp::load<T, -2>` / `mipp_load_*_d2` | Handled natively via MIPPv2 Length Division ($\text{LDIV} / LMUL=-2$). |
| `mipp::mask<T, fn>`, `mipp::maskz<T, fn>` | `_mask`, `_maskz`, `_masks` variants on all functions | Masking promoted to a first-class execution mode across all 4 variants rather than higher-order function pointer wrappers. |
| `mipp::cvt<T1, T2>` (all conversions) | `cvt` (same-size), `wcvt` (widening), `ncvt` (narrowing, truncating), `cast` (reinterpreting) | Disambiguates arithmetic casting, widening/narrowing conversions, and zero-cost bit reinterpretation into dedicated primitives. |
| `mipp::pack<T1, T2>`, `low`, `high` | `ncvt` (truncating), `low` / `high` / `combine` & $\text{LDIV}$ | Narrowing and half-register slicing are separate primitives; a saturating `pack` is still to be defined. |
| `mipp::sat(r, min, max)` | `adds`, `subs` | Replaced ad-hoc clamping with hardware saturated arithmetic instructions (`vsadd.vv`, `vqadd`, `_mm_adds_epi16`). |
| Mask arrays `bool[N]` | Strongly typed `rvm<T>` / `rvm_*_t` | Eliminates raw boolean unpacking overhead; masks match hardware opmask or full-vector representations. |
| `mipp::toreg<N>(m)` | `torvd(m)` / `torvm(r)` | Dedicated bidirectional conversion primitives with exact truthiness and bit-expansion semantics. |
| `mipp::blend(r1, r2, m)` | `select(m, r1, r2)` | Renamed after the operation (`m ? r1 : r2`), mask first as in every masked MIPPv2 function. |

---

## 2. Target ISA Coverage & Fallback Optimization

In MIPP's design, **Level 2 (Generic Vector Emulation) is a core feature**: higher-level mathematical functions (e.g., hyperbolic functions `asinh`/`acosh`/`atanh`/`tanh`, composite logic, and multi-step algorithms) are designed to compose portably from elementary Level 0/1 primitives across all architectures. 100% Level 0/1 coverage is neither necessary nor a design goal.

The optimization goals for ISA coverage are:
1. **Eliminate Level 3 (Sequential Scalar Fallback)** on workloads where vector operations can be synthesized via Level 0, 1, or 2.
2. **Implement Level 0 (Native Hardware)** and **Level 1 (Dedicated Emulation)** for high-throughput primitives where hardware instructions or architecture-specific sequences exist.

---

## 3. Hardware Predication on AVX-512 & SVE

Currently, MIPPv2 classifies mask execution into native predication (RISC-V Vector), partially native predication (AVX-512, and native masked load/store on RVV), and full-vector emulation (SSE, NEON, AVX, SVE).

- [ ] **AVX-512 Hardware Opmask (`k`-register) Integration** (partially done):
  - Current state: `rvm<T>` is bound to native opmask types (`__mmask8` ... `__mmask64`). Native masked instructions are used for part of the functions (e.g., `_mm512_mask_add_*`, native masked `load`/`store` including unsigned types); the others are evaluated as an unmasked operation followed by `_mm512_mask_blend_*` (Level 2).
  - Target state: Route all masked operations that have a native predicated intrinsic (e.g., `_mm512_maskz_mul_epi32`) to it.
- [ ] **ARM SVE Predicate (`svbool_t`) Integration** (partially done):
  - Current state: `rvm<T>` is bound to native `svbool_t`, but masked operations are emulated through unmasked execution and `svsel` (Level 2); predicated forms are not used.
  - Target state: Generate predicated instruction forms governed by active predicates (`svadd_f32_m`, `svmul_s32_z`).

---

## 4. Generator Tooling & Dependency Introspection

The header and documentation generation pipeline requires developer tools to analyze implementation dependencies and minimize scalar fallbacks:

- [ ] **Minimal ISA Implementation Subset Analyzer**:
  - Implement a CLI tool / generator query to compute the minimal irreducible subset of Level 0/1 functions that must be implemented for a given ISA target to eliminate all Level 3 (scalar fallback) degradations across the entire library.
  - Identify optimal implementation order based on transitive dependency fan-out (e.g., implementing `cmpeq`, `select`, and `set0` first unlocks generic Level 2 implementations for dozens of derived operations).
- [ ] **Transitive Dependency Graph Visualizer**:
  - Implement a tool to export the full directed acyclic graph (DAG) of prerequisites for any function, datatype, and masking variant on a specified ISA.
  - Support exporting dependency graphs to Graphviz DOT diagram format.

---

## 5. Upcoming MIPPv2 Features (Improvements over MIPPv1)

- [ ] **Mixed Vector-Scalar Function Variants (`_vf` / `_vs`)**:
  - Define function variants that accept a scalar value as the second operand directly (e.g., `mipp::add(va, scalar_b)`, `mipp::fmadd(va, vb, scalar_c)` / `mipp_add_vf_float32`).
  - Enables the code generator to emit native vector-scalar instructions without generating an explicit vector broadcast (`set1` / `_mm256_set1_ps` / `vdupq_n_f32`):
    - RISC-V Vector: Emits native `.vf` / `.vx` instructions (e.g., `vfmadd.vf`, `vadd.vx`, `vmul.vx`).
    - ARM SVE: Emits scalar-operand instruction forms (e.g., `fadd z0.s, p0/m, z0.s, #imm`).
    - x86: Allows compiler to fold memory-broadcast addressing modes into arithmetic instructions (e.g., `vaddps ymm0, ymm1, [rdi]`).
- [ ] **2D Matrix Accelerator Architecture Support (Intel AMX, ARM SME, RISC-V Matrix)**:
  - Target hardware 2D matrix and tile acceleration units:
    - **Intel AMX** (Advanced Matrix Extensions): 2D tile registers (`TMM0-TMM7`), tile configuration, tile load/store (`TILELOADD`/`TILESTORED`), and tile matrix multiplication (`TDPBUSD`, `TDPBF16PS`, `TDPFP16PS`).
    - **ARM SME / SME2** (Scalable Matrix Extension): 2D matrix accumulator tile storage (`ZA`), streaming vector mode (Streaming SVE), and outer-product matrix compute engines (`FMOPA`, `SMOPA`, `UMOPA`).
    - **RISC-V Matrix Extension** (RME / draft matrix proposals): 2D matrix register configuration and tile-based matrix multiply-accumulate operations.
  - Expand MIPPv2 datatype registry to support low-precision floating-point and sub-byte integer formats required by matrix compute engines:
    - IEEE 754 half-precision (`float16` / `_Float16`).
    - Brain Floating Point (`bfloat16` / `__bf16`).
    - 8-bit floating point formats (`fp8` E4M3 / E5M2).
    - Sub-byte quantized integer formats (`int4`, `uint4`).
- [ ] **Integration with Vectorized Math Libraries (SLEEF, libmvec, SVML, ARMPL, AMD LibM)**:
  - Add backend options in the code generator to delegate transcendental and elementary mathematical functions (`sin`, `cos`, `tan`, `exp`, `log`, `pow`, `asin`, `acos`, `atan`, `atan2`, `sinh`, `cosh`, `tanh`, etc.) to established high-performance vectorized math libraries:
    - **SLEEF** (portable, SIMD library with standardized 1.0 ULP and 3.5 ULP modes across SSE, AVX, AVX-512, NEON, SVE, RVV).
    - **GLIBC `libmvec`** (standard GNU C vector math library on x86-64).
    - **Intel SVML** (Intel Short Vector Math Library).
    - **ARM Performance Libraries (ARMPL)** / `libamath` (AArch64 math routines).
    - **AMD AOCL-LibM** (AMD Zen-optimized vectorized transcendental routines).
- [x] **Harmonized Widening/Narrowing & Register Slicing Specification (`wcvt`, `ncvt`, `low`/`high`)**: resolved. `wcvt` takes a register at the LMUL below and returns the LMUL above; `ncvt` is its truncating inverse; `low`/`high`/`combine` slice and join registers. All are available on every ISA (compile-checked only on SVE/AVX-512/RVV).
  - Remaining open point: a saturating `pack`, and the register-tuple alternative below.
  - (Original question) Finalize API contracts to determine whether conversions operate on half-width register inputs (`LMUL=-2`) to produce full registers (`LMUL=1`), or consume full registers to produce register tuples (`Tuple<T, 2>` / `regx2`), ensuring uniform behavior across fixed-length (SSE, AVX) and scalable (SVE, RVV) architectures.

---

## 6. Metaprogramming & Auto-Tuning Roadmap

### 6.1. `min_lmul` Constexpr Trait
- *Status*: Specified design, pending implementation in constexpr type traits.
- [ ] Implement compile-time metaprogramming helper `mipp::min_lmul<T>(size_t vector_length)` to deduce the smallest valid Length Multiplier ($\text{LMUL}$) needed to store `vector_length` elements of type `T` in a register. This could be used to automatically select the appropriate register width for different datatypes and ISAs to perform automatic loop unrolling at compile time. For example, `mipp::min_lmul<float>(16)` should return
4 on `SSE` or `NEON`, 2 on `AVX` or `RVV-256`, 1 on `RVV-512` or `AVX-512`.  

### 6.2. `Tuple` Type for Transparent Register Blocking
- *Status*: Well-defined concept and user experience goals, but implementation strategy, scope, edge cases, and code generation mechanisms are unfinalized (currently unsupported).
- [ ] Implement `mipp::Tuple<T, N_VECTORS, int LMUL = 1>` template abstraction for transparent multi-register unrolling, register tiling, and register blocking.
- [ ] **Transparent Register Block Manipulation**:
  - Eliminate manual declaration of discrete vector accumulators (`v0, v1, ..., vn`) and hand-unrolled loop bodies by expressing register blocks directly as tuples.
  - `LMUL` serves as the intra-register width multiplier, while `N_VECTORS` acts as the compile-time loop unrolling and register tile factor.
- [ ] **Heterogeneous & Broadcast Tuple Operators**:
  - Overload arithmetic operators (`+`, `-`, `*`, `/`, `fmadd`) across homogeneous and heterogeneous tuple dimensions to allow automatic broadcasting and unrolling across register tiles:
    ```cpp
    mipp::Tuple<float, 2> a; // 2-vector register block
    mipp::Tuple<float, 4> b; // 4-vector register block

    // Automatic tiling and unrolling across block dimensions:
    mipp::Tuple<float, 4> c = b + a; // a is broadcast/unrolled across b
    mipp::Tuple<float, 2> d = a + b[0];
    ```
  - Maximizes instruction-level parallelism (ILP) and hides functional unit latency on out-of-order superscalar pipelines without manual register management.

### 6.3. Micro-Benchmark & Empirical Auto-Tuning Suite
- *Status*: Long-term vision / distant roadmap goal. The high-level intent is established, but the architectural design, harness infrastructure, and feedback loop into the generator remain to be designed.
- [ ] Implement an automated micro-benchmarking test harness measuring throughput (cycles/vector), instruction latency, and cache/pipeline metrics across Level 0 (Native), Level 1 (Dedicated Emulation), and Level 2 (Generic Emulation) candidates for each ISA.
- [ ] **Precision & Accuracy Profiles (ULP Targets)**:
  - Quantify numerical precision and Unit in the Last Place ($\text{ULP}$) error across polynomial approximations, Newton-Raphson iterations, and math library backends.
  - Support user-specified accuracy targets during template generation / selection:
    - **High Accuracy (Strict IEEE)**: Higher-degree polynomials or strict math library bindings.
    - **Relaxed / Fast Math**: Low-latency polynomial expansions and reciprocal square root approximations.
- [ ] **Energy Efficiency & Power Telemetry**:
  - Integrate hardware energy profiling via Linux `perf` power events, Intel/AMD **RAPL** (Running Average Power Limit) MSRs, and ARM energy telemetry interfaces, leverage `likwid` when possible to collect energy measurements.
  - Track **Joules per vector element** and **Energy-Delay Product ($\text{EDP} = \text{Energy} \times \text{Delay}$)** to evaluate the energy trade-offs of hardware-intensive instructions vs polynomial software approximations.
- [ ] **Data-Driven Template Selection (Exploratory Concept)**:
  - Explore automated heuristics or profile-guided mechanisms to select candidate implementation templates based on target microarchitecture profiles.
  - Potential objective metrics under consideration (non-exhaustive):
    - **Throughput**: Maximizing vector issue rate and arithmetic instruction density.
    - **Latency**: Shortening critical dependency chains for sequential computations.
    - **Precision / Error Bound**: Tailoring polynomial order to strict ($\le 0.5\text{ ULP}$) vs relaxed ($\le 3.5\text{ ULP}$) accuracy targets.
    - **Register Pressure**: Favoring templates that minimize live register count and spilling in complex loops.
    - **Energy / EDP**: Minimizing power consumption and Joules per vector operation.
    - **Pareto Trade-offs**: Multi-objective balance across latency, throughput, precision, and resource utilization.


