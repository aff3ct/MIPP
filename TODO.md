# MIPPv2 Release Roadmap & Pending Tasks

This document tracks pending engineering tasks, missing functionality relative to MIPPv1, architectural coverage gaps, planned generator enhancements, and future metaprogramming features for upcoming MIPPv2 releases.

---

## 1. MIPPv1 Function Parity & Missing Interfaces

MIPPv2 currently defines and generates **144 core vector primitives** across arithmetic, logic, comparison, math, reduction, load/store, conversions, selection, rearrangements and complex numbers, plus their scalar forms (`sub_vs`, `fmadd_vsv`...). The MIPPv1 families below are migrated on the `feat/mippv1-parity` branch; not needed (`sincos`, `cossin`: the compiler merges `sin` and `cos`; `interleavex*`: written with `lo`, `hi`, `combine` and `zip`), low priority (shift of the lanes of a mask, `MIPP_STATIC_LIB` tables of `compress`) or deliberately not reproduced (`cmask`).

### 1.1. Complex Arithmetic (`regx2` / Coordinate Pairs)

MIPPv1 provided complex-number vector arithmetic defined on register pairs (`regx2` representing interleaved or split real and imaginary components). MIPPv2 works on the interleaved layout, in ordinary `float32` / `float64` registers (category `complex`, see `docs/user/complex_numbers.md`); the split layout is written with the real functions:
- [x] `cadd`: Complex addition $((a_r + b_r) + i(a_i + b_i))$: `add` on the interleaved layout.
- [x] `csub`: Complex subtraction $((a_r - b_r) + i(a_i - b_i))$: `sub`.
- [x] `cmul`: Complex multiplication $((a_r b_r - a_i b_i) + i(a_r b_i + a_i b_r))$, with `cfmadd` ($a b + c$).
- [x] `cmulconj`: Complex multiplication with conjugate second operand $((a_r b_r + a_i b_i) + i(a_i b_r - a_r b_i))$.
- [x] `cdiv`: Complex division ($\frac{a \cdot \bar{b}}{|b|^2}$), with the algorithm of Smith (no overflow of $|b|^2$).
- [x] `conj`: Complex conjugation ($a_r - i a_i$).
- [x] `norm`: Complex squared Euclidean norm ($a_r^2 + a_i^2$): `cnorm`, and `cabs` for the modulus.
- [x] `sincos`, `cossin`: Simultaneous evaluation of sine and cosine returning register pairs (`regx2` with sine/cosine or cosine/sine components). Not needed: `sin` and `cos` share their range reduction and their two polynomials, and once inlined the compiler computes them once (clang -O2, float32: 64 instructions for `sin`, 75 for `sin` and `cos` on NEON; 50 and 61 on AVX2). `cossin` gave $e^{ix}$ in the split layout of MIPPv1, which MIPPv2 does not use for complex numbers.

### 1.2. Vector Interleaving & Deinterleaving

MIPPv1 provided a set of multi-stride interleaving and deinterleaving primitives for vector transpositions:
- [x] `interleavelo`, `interleavehi`: Low/high lane interleaving of two registers: `ziplo`, `ziphi` (and `unziplo`, `unziphi` for the inverse).
- [x] `interleavelo2`, `interleavehi2`: 2-element granular low/high interleaving: `ziplo_b128`, `ziphi_b128` (per 128-bit block, see below).
- [x] `interleavelo4`, `interleavehi4`: 4-element granular low/high interleaving: same `_b128` variants.
- [x] `interleave`, `deinterleave`: Full two-register zip and unzip operations returning `regx2`: the result is a register of LMUL 2 (`combine(ziplo(a, b), ziphi(a, b))`); `zip(a)` / `unzip(a)` in one register, and `loadu_unzip` / `storeu_zip`.
- [x] `interleave2`, `interleave4`: Multi-stride 2-way and 4-way register interleaving returning `regx2`. In MIPPv1 the block is relative to the register (a half or a quarter, i.e. 256 bits on AVX-512): MIPPv2 uses fixed 128-bit blocks instead (`_b128` variants).
- [x] `interleavex2`, `interleavex4`, `interleavex16`: Cross-lane intra-register interleaving permutations. Not needed: `interleavex2(a, b)` is `combine(lo(a), lo(b))` and `combine(hi(a), hi(b))`, `interleavex16` the `zip` of a register cast to `int16`, and `interleavex4` put back the order of the quarters after a `pack` of AVX2 (MIPPv2 `ncvts` and `zip` work on the whole register).

### 1.3. Permutation, Shuffling & Packing

- [x] `shuff`, `shuff2`, `shuff4`: Arbitrary intra-vector element shuffling governed by **runtime index registers only** (MIPPv1 has no immediate shuffle masks). `shuff2`/`shuff4` apply the same pattern to each half/quarter of the register. Done as `permute` / `permute2` (whole vector) and `permute_b128`, plus `permute<P>` / `permute2<P>` with a pattern known at compile time (C++17).
- [ ] `cmask`, `cmask2`, `cmask4`: Opaque, ISA-specific encoding of the shuffle indices (byte indices for `pshufb`/`vtbl`), prepared once. MIPPv2 starts with plain index registers; a prepared type will only be added if measurements require it.
- [x] `combine<S>(a, b)`: Lanes `S` to `S + N - 1` of the concatenation of `a` and `b` (`alignr` / `ext`). Done as `slide(a, b, n)` (and `slideup`, `slidedown`, `_b128`), since `combine` is the concatenation of two halves in MIPPv2. The count is an ordinary argument, not an immediate.
- [x] `transpose`, `transpose8x8`, `transpose2`, `transpose28x8`: Register-block transposes (a few datatypes and ISAs only in MIPPv1). Done in the three APIs as `transpose(t)` (an array of N registers, in place) and `transpose_b128(t)` (16 / sizeof(T) registers, a matrix per block of 128 bits), for every type, LMUL and ISA: steps of `ziplo` / `ziphi`, `_b128` then an exchange of the halves on AVX. No equivalent of `transpose2<int8_t>` of SSE (two 8 x 8 matrices in the halves of 64 bits).
- [x] `compress`: Contiguous stream compaction (compressing active elements governed by a boolean mask into contiguous vector lanes, e.g., `_mm256_maskz_compress_epi32` / `vcompress`), with `expand`, `count`, `storeu_compress` (exact), `storeuf_compress` (a whole register written) and `loadu_expand`.
- [ ] `MIPP_STATIC_LIB`: compiled shuffle tables of `compress` for the 8 and 16-bit elements on SSSE3, AVX2 and NEON (Level 3 today), and the large tables out of the headers.
- [x] `low`, `high`, `combine` (and `_k` mask versions): Half-register extraction and slice concatenation (`lo`, `hi`, `combine`), done on every ISA (`d2` ↔ `m1` ↔ `m2` ↔ ...). Native mask versions on RVV.
- [x] `pack`: Saturating register narrowing from two inputs: `ncvts` (saturating `ncvt`, integers of the same signedness, one input at the LMUL above) in the three APIs; the `pack` of two registers is `ncvts(combine(a, b))`.
  > **Note:** `wcvt` (widening, input at a lower LMUL: `d2` → `m1` → `m2`) and `ncvt` (narrowing by truncation, the inverse) are implemented with the LMUL-changing infrastructure (`ret.lmul` in the registry). Half-register slicing (`lo`/`hi`) and element conversions are now separate primitives.

### 1.4. Vector Rotations & Dynamic Shifts

- [x] `lrot`, `rrot`: Rotation of the **lanes** of a register by one position (not a bitwise rotation of the elements): `rotate(v, n)` (`rotate(v, 1)`, `rotate(v, N - 1)`), and `rotate_b128`.
- [x] `lshiftr`, `rshiftr`: Variable element-wise vector-by-vector left and right logical/arithmetic bit shifts (where shift counts vary per lane, e.g., `_mm256_sllv_epi32`): `lshift(a, n)` / `rshift(a, n)` with a register of counts; the same count for every lane is `lshift_vs` / `rshift_vs`.
- [x] Immediate arguments (`alignr`, `vext`, `svext`, shifts by a constant): with a constant count, `slide`, `slideup`, `slidedown`, `rotate`, `bcast` (and their `_b128` variants) and the shifts select the immediate instructions at compile time (`__builtin_constant_p`), in C and C++; the C++ APIs also have `mipp::slide<S>(a, b)`, `mipp::lshift<3>(a)`... (see `docs/user/rearrangements.md`, Constant Counts).
- [ ] `lshift<N>`, `rshift<N>` on `msk`, `Msk << n`: shift of the lanes of a mask. Low priority (rarely used): native only on AVX-512 (`kshift`) and RVV (`vslideup` / `vslidedown` of the mask register); elsewhere through `tovd`, `slideup` / `slidedown` and `tovm`.

### 1.5. Memory Management & Dynamic Buffers

- [x] `isAligned`: `mipp_is_aligned(p)` / `mipp::is_aligned(p)` against `MIPP_REQUIRED_ALIGNMENT` (the register size).
- [x] `oloadu`: The unaligned load that returns a register object (`Reg<T>`), not a load with an offset: covered by the Object API (`mipp::Vd<T>` constructors and `mipp::loadu`).
- [x] `malloc`, `free`: `mipp_malloc` / `mipp_free` (C), `mipp::malloc<T>` / `mipp::free` (C++).
- [x] `mipp::allocator<T>`: STL-compliant allocator ensuring aligned dynamic allocations for `std::vector`.
- [x] `mipp::vector<T>`: Type alias for `std::vector<T, mipp::allocator<T>>`.

### 1.6. Reductions, Aliases & Diagnostics

- [x] `reduction<T, OP>`: `mipp::reduce(v, op)` and `mipp::reduce<T, LMUL>(ptr, n, op)` in the Object API, with the operations of `mipp::op` (`add`, `mul`, `min`, `max`, `andb`, `orb`, `xorb`) or any functor.
- [x] `sum`: not needed: `hadd(v)` (wraps) or `hadds(v)` (saturates, as the MIPPv1 `sum` on the 8-bit and 16-bit integers). An alias of `hadd` would silently wrap where MIPPv1 saturated.
- [x] `sat`: Dynamic clamping of vector elements between runtime bounds $[min, max]$, distinct from the MIPPv2 `adds`/`subs` type-boundary saturation: `clamp(v, lo, hi)`, with its scalar forms (`clamp(v, 0.f, 1.f)`).
- [x] `dump`: `mipp_dump_<type>[_<lmul>]` / `mipp_fdump_...` (C, `_k` for the masks), `mipp::dump<T, LMUL>` / `mipp::dump_k` (C++ Functional), `operator<<` on `Vd` and `Vm` (C++ Object).
- [x] `neg(r, s)`, `copysign(r, s)`, `sign(r)`: `xorsign(a, b)` (negates `a` where `b` is negative: the MIPPv1 `neg` / `copysign`), `copysign(a, b)` (IEEE: magnitude of `a`, sign of `b`) and `signbit(v)` (mask of the negative lanes, including -0.0).
- [x] `any`, `all` (with `none` and `testz`): Boolean mask reductions returning `int32_t`, native on every ISA (movemask, testz/testc, kortest, maxv/minv, ptest, vcpop).

### 1.7. Summary of Function Renames & Architectural Evolution in MIPPv2

| MIPPv1 Concept | MIPPv2 Implementation | Architectural Rationale |
| :--- | :--- | :--- |
| `mipp::load_2<T>`, `mipp::loadu_2<T>` | `mipp::load<T, -2>` / `mipp_load_*_d2` | Handled natively via MIPPv2 Length Division ($\text{LDIV} / LMUL=-2$). |
| `mipp::mask<T, fn>`, `mipp::maskz<T, fn>` | `_mask`, `_maskz`, `_masks` variants on all functions | Masking promoted to a first-class execution mode across all 4 variants rather than higher-order function pointer wrappers. |
| `mipp::cvt<T1, T2>` (all conversions) | `cvt` (same-size), `wcvt` (widening), `ncvt` (narrowing, truncating), `cast` (reinterpreting) | Disambiguates arithmetic casting, widening/narrowing conversions, and zero-cost bit reinterpretation into dedicated primitives. |
| `mipp::pack<T1, T2>`, `low`, `high` | `ncvts` (saturating), `ncvt` (truncating), `ncvts(combine(a, b))`, `lo` / `hi` / `combine` & $\text{LDIV}$ | Narrowing and half-register slicing are separate primitives. |
| `mipp::sat(r, min, max)` | `clamp` | Clamping between runtime bounds. Not to be confused with `adds`/`subs`, the saturated arithmetic at the type boundaries (`vsadd.vv`, `vqadd`, `_mm_adds_epi16`). |
| Mask arrays `bool[N]` | Strongly typed `vm<T>` / `vm_*_t` | Eliminates raw boolean unpacking overhead; masks match hardware opmask or full-vector representations. |
| `mipp::toreg<N>(m)` | `tovd(m)` / `tovm(r)` | Dedicated bidirectional conversion primitives with exact truthiness and bit-expansion semantics. |
| `mipp::neg(r, s)`, `mipp::copysign(r, s)`, `mipp::sign(r)` | `xorsign(a, b)`, `copysign(a, b)`, `signbit(v)` | The MIPPv1 `copysign` was a sign flip (`xorsign`); MIPPv2 `copysign` follows IEEE 754. `signbit` is named after C99. |
| `mipp::blend(r1, r2, m)` | `select(m, r1, r2)` | Renamed after the operation (`m ? r1 : r2`), mask first as in every masked MIPPv2 function. |
| `mipp::interleavelo/hi`, `interleave2/4`, `deinterleave` | `ziplo` / `ziphi`, `unziplo` / `unziphi`, `_b128` variants | Named after the operation; the blocks are fixed (128 bits) instead of relative to the register size, and two-register results are registers of LMUL 2. |
| `mipp::shuff`, `shuff2`, `shuff4` | `permute`, `permute2`, `permute_b128`, `permute<P>` | Indices in a register of unsigned integers of the width of the elements; compile-time patterns in C++17. |
| `mipp::combine<S>(a, b)`, `lrot`, `rrot` | `slide(a, b, n)`, `rotate(v, n)` | `combine` concatenates two halves in MIPPv2; the counts are ordinary arguments. |
| `mipp::cmul`, `norm`, ... on `regx2` | `cmul`, `cnorm`, `cabs`, `cdiv`... on one register | Interleaved layout in ordinary registers; `cdiv` with the algorithm of Smith. |

---

## 2. Target ISA Coverage & Fallback Optimization

In MIPP's design, **Level 2 (Generic Vector Emulation) is a core feature**: higher-level mathematical functions (e.g., hyperbolic functions `asinh`/`acosh`/`atanh`/`tanh`, composite logic, and multi-step algorithms) are designed to compose portably from elementary Level 0/1 primitives across all architectures. 100% Level 0/1 coverage is neither necessary nor a design goal.

The optimization goals for ISA coverage are:
1. **Eliminate Level 3 (Sequential Scalar Fallback)** on workloads where vector operations can be synthesized via Level 0, 1, or 2.
2. **Implement Level 0 (Native Hardware)** and **Level 1 (Dedicated Emulation)** for high-throughput primitives where hardware instructions or architecture-specific sequences exist.

---

## 3. Hardware Predication on AVX-512, SVE & RVV

AVX-512, SVE and RVV have hardware masks (`hw_mask`): a masked function uses the predicated form of its instruction when the ISA has one. The other masked functions compute the unmasked operation and select the inactive lanes (`select`, with zeros for the Zero-Masked variant): GCC and Clang fold this selection into the masked instruction on AVX-512, not on RVV. SSE, AVX and NEON have no predication: a mask is a register of all-ones or zero lanes.

- [x] **AVX-512 Hardware Opmask (`k`-register) Integration**:
  - `vm<T>` is bound to the opmask types (`__mmask8` ... `__mmask64`). The masked variants call the `_mm512_mask_*` / `_mm512_maskz_*` form of the instruction when the unmasked function is one intrinsic (arithmetic, logic, FMA, comparisons, shifts, `sqrt`, `rsqrt`, `trunc`, `permute`, `permute2`, `permute_b128`, `reverse`, `dupeven`, `dupodd`, `swap2`, `zip` / `unzip` halves, loads, stores, gather, scatter), and when a short sequence ends with such a form (`neg`, `notb`, `copysign`, `xorsign`, `msb`, `clamp`, `div2`, `div4`, the reductions with `_mm512_mask_reduce_*`).
  - Without a masked form at the granularity of the lanes (8 and 16-bit shifts and logic, `shuffle_epi32` on 64-bit lanes), for the functions with an immediate count (`slide`, `rotate`, `bcast`, dispatched to the immediate instructions) and for the compositions (math, complex numbers, `round`), the selection after the unmasked operation is kept.
- [x] **ARM SVE Predicate (`svbool_t`) Integration**:
  - `vm<T>` is bound to `svbool_t`. The predicated forms (`_m`, `_z`) are used for the arithmetic, FMA, comparisons, logic (`notb`, `andnb` Zero-Masked), shifts, `div2` / `div4`, `neg`, `abs`, `round`, `trunc`, `sqrt`, `clamp`, `msb`, `copysign`, `xorsign`, the saturated `adds` / `subs` (SVE2), the reductions, loads, stores, gather and scatter.
  - The rearrangements (`svtbl`, `svzip1`, `svrev`, `svext`...), `rsqrte` / `recpe` and `hmul` have no predicated form, and the Merge-Masked `andnb` cannot use `svbic_m` (it keeps the other operand): `svsel` after the unmasked operation.
- [x] **RISC-V Vector Mask Policies**:
  - The masked variants use the `_mu` policy (inactive lanes from the merge operand: the first register, the source register, or a register of zeros for the Zero-Masked variant) for the arithmetic, FMA (`fnmadd` / `fnmsub` with `vfnmsub` / `vfnmadd`), logic, shifts, `abs`, `neg`, `clamp`, `msb`, `copysign` / `xorsign` (`vfsgnj` / `vfsgnjx`), the gathers of `permute`, `bcast`, `reverse`, `dupeven`, `dupodd` and `swap2`, the reductions, loads, stores, gather and scatter.
  - The slides (`slide`, `rotate`), `zip` / `unzip` and the compositions keep the selection (`vmerge`) after the unmasked operation.

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

- [x] **Mixed Vector-Scalar Function Variants (`_vf` / `_vs`)**: done as the scalar forms (`add_vs`, `sub_sv`, `fmadd_vsv`..., C++ overloads of `mipp::add`..., see `docs/user/scalar_forms.md`), with native bodies on RVV (`.vx` / `.vf`, and `vrsub` / `vfrsub` / `vfrdiv` for the `sv` forms) and SVE (`_n` intrinsics), and the broadcast (`set1`) elsewhere.
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
- [x] **Harmonized Widening/Narrowing & Register Slicing Specification (`wcvt`, `ncvt`, `lo`/`hi`)**: resolved. `wcvt` takes a register at the LMUL below and returns the LMUL above; `ncvt` is its truncating inverse; `lo`/`hi`/`combine` slice and join registers. All are available on every ISA (compile-checked only on SVE/AVX-512/RVV).
  - Remaining open point: the register-tuple alternative below.
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


