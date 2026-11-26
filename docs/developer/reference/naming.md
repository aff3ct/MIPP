# Naming Conventions

The names of MIPPv2 follow a small set of rules, so that a name can be guessed from the operation and an operation read from its name. This page lists them, for the public API (the names the users write) and for the generator (the names the templates write). A new function, type or template should follow them.

---

## 1. Library Prefix

Everything public starts with `mipp`: the C functions (`mipp_add_float32`), the C++ namespace (`mipp::add`), the utilities (`mipp_malloc`, `mipp_free`) and the macros (`MIPP_N_FLOAT32`, `MIPP_REQUIRED_ALIGNMENT`). The C register types are the only exception (`vd_float32_t`, see below).

A shorter prefix would collide with other libraries in the global namespace of C (`mi_` is the prefix of mimalloc: `mi_malloc`, `mi_free`). In C++, a user who wants a shorter name writes a namespace alias:

```cpp
namespace mi = mipp;
mi::vd<float> a = mi::set1<float>(1.f);
```

---

## 2. Register Types

| | Data register | Mask register |
| :--- | :--- | :--- |
| C (LMUL 1) | `vd_float32_t` | `vm_float32_t` |
| C (other LMULs) | `vd_float32_m2_t`, `vd_float32_d2_t` | `vm_float32_m2_t`, `vm_float32_d2_t` |
| C, inside an ISA | `vd_sse_float32_m1_t` | `vm_sse_float32_m1_t` |
| C++ Functional API | `mipp::vd<float, 2>` | `mipp::vm<float, 2>` |
| C++ Object API | `mipp::Vd<float, 2>` | `mipp::Vm<float, 2>` |

`vd` is a **v**ector of **d**ata and `vm` a **v**ector **m**ask; the capital letter is the class of the Object API. The conversions between them are `tovd(m)` (a mask as a register of all-ones / all-zeros lanes) and `tovm(v)` (the non-zero lanes of a register as a mask).

### Fields

The C types are structures. Their fields have the names of the types:

| Field | Content |
| :--- | :--- |
| `.vd` | the native register of a data register (`__m128`, `float32x4_t`, `vfloat32m1_t`...) |
| `.vm` | the native mask of a mask register (`__mmask16`, `svbool_t`...) |
| `.lo`, `.hi` | the lower and upper halves of a software LMUL group, themselves registers of the LMUL below |

The halves have the names of the functions that extract them (`lo`, `hi`): `v.lo.hi.vd` is the native register of the second quarter of a group of LMUL 4. The fields are useful to mix MIPP and intrinsics, in C (`v.vd`) and in the C++ Object API, whose classes hold the register of the Functional API (`Vd::vd`, `Vm::vm`).

---

## 3. Function Names

### One word, `_` for the modifiers

A base name is **one word**, possibly with one-letter affixes glued to it: `hadd`, `cmpeq`, `ziplo`, `slideup`. The `_` never separates two words of a name: it introduces a **modifier** from a known family. `andb_k` reads as "`andb` on masks" and `ziplo_b128` as "`ziplo` in each block of 128 bits", in the same way.

This is the style of the intrinsics (`unpacklo`, `vslideup`) and of MIPPv1 (`interleavelo`), and it keeps the names short.

### Affixes

| Affix | Meaning | Examples |
| :--- | :--- | :--- |
| `c` (prefix) | complex numbers, in the interleaved layout | `cmul`, `cmulconj`, `cabs`, `cfmadd` |
| `h` (prefix) | horizontal: a reduction of the lanes | `hadd`, `hmul`, `hmin`, `hmax` |
| `n` / `w` (prefix) | narrowing / widening (LMUL change) | `ncvt`, `ncvts`, `wcvt` |
| `cmp` (prefix) | comparison, the predicate follows | `cmpeq`, `cmplt`, `cmpneq` |
| `s` (suffix) | saturated | `adds`, `subs`, `hadds`, `ncvts` |
| `b` (suffix) | bitwise | `andb`, `andnb`, `orb`, `xorb`, `notb` |
| `u` (suffix of a memory verb) | unaligned memory access | `loadu`, `storeu` |
| `lo` / `hi` | lower / upper half | `lo`, `hi`, `ziplo`, `ziphi`, `unziplo`, `unziphi` |
| `even` / `odd` | even / odd lanes | `dupeven`, `dupodd` |
| `2` | pairs of lanes, or two registers | `swap2`, `permute2` |

### Modifiers

| Modifier | Meaning | Examples |
| :--- | :--- | :--- |
| `_k` | the function on masks | `andb_k`, `set1_k`, `lo_k`, `combine_k`, `cast_k` |
| `_vs`, `_sv`, `_vsv`, `_vvs` | [scalar forms](../../user/scalar_forms.md): one letter per operand, `v` (register) or `s` (scalar) | `sub_vs`, `sub_sv`, `fmadd_vsv` |
| `_b128` | the operation in each block of 128 bits | `ziplo_b128`, `slide_b128`, `bcast_b128` |
| `_mask`, `_maskz`, `_masks` (C) | the [mask variants](../../user/masking_semantics.md) (`mipp::M`, `Z`, `S` in C++) | `mipp_add_float32_maskz` |
| `_m2`, `_m4`, `_m8`, `_d2` (C) | the LMUL of the arguments (none for LMUL 1) | `mipp_add_float32_m2` |

In C, the modifiers come in this order after the base name: form or `_b128`, datatype, mask variant, LMUL (`mipp_sub_vs_float32_maskz_m2`).

### Memory accesses

A function that reads or writes a block of memory **starts with its memory verb**: `load` / `store`, followed by `u` when the address needs no alignment. The operation applied to the data comes after a `_`, as a modifier of the access, with the rule `loadu_X(p) = X(loadu(p))` and `storeu_X(p, v) = storeu(p, X(v))`:

| Function | Meaning |
| :--- | :--- |
| `load`, `loadu`, `store`, `storeu` | plain accesses (aligned / unaligned) |
| `loadu_unzip(p)` | `unzip(loadu(p))`: separates the even and the odd elements of the memory |
| `storeu_zip(p, v)` | `storeu(p, zip(v))`: interleaves the two halves of the register in memory |
| `storeu_compress(p, v, m)` | stores exactly the active lanes, packed, and returns their number |
| `storeuf_compress(p, v, m)` | the same, but may write a **f**ull register (faster without a native masked store) |
| `loadu_expand(p, m)` | reads `count(m)` elements into the active lanes |

The memory layout is not in the name: `loadu_unzip` reads interleaved data and returns them separated, because it applies `unzip`. `gather` and `scatter` are the exception to the rule: they access element by element, without a block to align.

### Names that differ from the intrinsics

The operations are named after what they do on the lanes, not after one instruction set:

| MIPPv2 | x86 | ARM | RVV |
| :--- | :--- | :--- | :--- |
| `slide(a, b, n)` | `alignr` | `ext` | `vslidedown` + `vslideup` |
| `slideup` / `slidedown` | `slli_si128` / `srli_si128` (bytes) | `ext` with zeros | `vslideup` / `vslidedown` |
| `bcast(v, k)` | `shuffle` / `permutexvar` | `dup` (element) | `vrgather` |
| `ziplo` / `ziphi` | `unpacklo` / `unpackhi` | `zip1` / `zip2` | — |
| `unziplo` / `unziphi` | `shuffle` | `uzp1` / `uzp2` | — |
| `dupeven` / `dupodd` | `moveldup` / `movehdup` | `trn1(a, a)` / `trn2(a, a)` | — |
| `swap2` | `shuffle` | `rev64` | — |
| `select(m, a, b)` | `blendv(b, a, m)` | `bsl` | `vmerge` |
| `loadu_unzip` / `storeu_zip` | — | `vld2` / `vst2` | `vlseg2` / `vsseg2` |
| `xorsign` | — | — | `vfsgnjx` |

---

## 4. Parameters

The parameters are named by kind, each kind with its own counter:

| Kind | Names | Example |
| :--- | :--- | :--- |
| data register | `vd0`, `vd1`, `vd2`... | `add(vd0, vd1)` |
| mask register | `vm0`, `vm1`... | `select(vm0, vd0, vd1)` |
| scalar | `s0`, `s1`... | `rshift_vs(vd0, s0)` |
| pointer | `p0`, `p1`... | `storeu(p0, vd0)` |
| source register of the `masks` variant | `vdsrc` | `sub<S>(vm0, vdsrc, vd0, vd1)` |

These names appear in the prototypes of the three APIs, in the reference pages and in the templates. In the generated code, the copies of a parameter take a prefix: `s_vd0` (to the scalar ISA, in the scalar fallback), `w_vd0` (to the LMUL 1 register, in the half-vectors by mask).

---

## 5. Templating DSL

The markers of the [templating DSL](templating_dsl.md) use the same letters as the types: `%vd<tp>%` (data register), `%vm<tp>%` (mask register), `%s<tp>%` (scalar), `%N<tp>%` (number of lanes). A function is called by its name: `%ziplo<tp>%(vd0, vd1)`. The lexer of the documentation (`scripts/pygments_mipp`) highlights these markers.

---

## 6. What Keeps the Conventions of Other Projects

- The **mathematical functions** keep the names of the C library: `sqrt`, `atan2`, `copysign`, `trunc`, `round`, `roundeven` (C23)...; `signbit` is named after C99.
- The **macros** keep the `MIPP_` prefix and upper case: `MIPP_N_FLOAT32`, `MIPP_REQUIRED_ALIGNMENT`, `MIPP_RVV_LDIV_VL`.
- The **datatypes** are the ones of `<stdint.h>`, plus `float32_t` / `float64_t`.
