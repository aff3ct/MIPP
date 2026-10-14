# Header Layout

This page describes the tree that `gen_mipp_headers.py` writes in `include/`, and how the `IncludeManager` (`generator/helpers_headers/include_gen.py`) decides which file receives each function and which headers it includes. The user side of the same tree (which header to include, compile times) is described in [Headers & Compile Time](../../user/headers_and_compile_time.md).

---

## 1. Tree

```text
include/
├── mipp.h, mipp.hpp, mipp_obj.hpp     # Global headers: C, C++ Functional, C++ Object
└── mipp/
    ├── c/   {cat,fun}/                 # Public headers of the C API
    ├── cpp/ {cat,fun}/                 # Public headers of the C++ Functional API
    ├── obj/ {cat,fun}/                 # Public headers of the C++ Object API
    └── internal/
        ├── interfaces/
        │   ├── c/                      # C API: dispatch to the selected ISA
        │   ├── cpp/                    # C++ Functional API: dispatch to the selected ISA
        │   └── obj/                    # C++ Object API (Rvd, Rvm)
        ├── templates/cpp/              # Declarations of the C++ function templates
        └── simd_ext/<isa>/
            ├── c/                      # Resolved implementations of one ISA
            │   ├── common.h            # Register types and ISA macros
            │   ├── mipp_<isa>.h        # Includes every function of the ISA
            │   └── functions/<category>/...
            └── cpp/                    # C++ overloads of one ISA (mipp::rvd<T,LMUL,ISA>)
```

The public headers contain nothing but `#include` lines to `mipp/internal/`: `mipp/cpp/fun/add.hpp` includes `mipp/internal/interfaces/cpp/functions/arithmetic/add.hpp`. Users never include `mipp/internal/` directly.

---

## 2. Layers

The `IncludeManager` handles one **layer** per output directory. A function is written once per layer:

| Layer | Directory (in `include/mipp/internal/`) | Written by |
| :--- | :--- | :--- |
| `<isa>` | `simd_ext/<isa>/c/` | `c_generator.py` ([Code Generation](code_generation.md)), `simd_ext/scalar/scalar_gen.py` |
| `<isa>_cpp` | `simd_ext/<isa>/cpp/` | `cpp_generator.py` |
| `c` | `interfaces/c/` | `ci_generator.py` |
| `cpp` | `interfaces/cpp/` | `cpp_generator.py` |
| `templates` | `templates/cpp/` | `cpp_generator.py` |
| `obj` | `interfaces/obj/` | `obj_generator.py` |

The generators never open files themselves: they ask the manager for a file object with `get_fd(layer, function, variant, lmul)`, and the manager chooses the path according to the granularity.

---

## 3. Coarse Granularity

With `--granularity coarse` (default), each layer has one header per function, `functions/<category>/<function>.h` (`.hpp` for the C++ layers). This header contains every datatype, mask variant and LMUL of the function. Its includes are computed after the layer is generated, from the dependencies recorded during the resolution (`resolve_all_dependencies()`), plus:

- the scalar header of the function, for the <span class="mipp-isa-badge lvl-3">L3</span> fallbacks;
- the header of the `sub_isa` for the ISAs whose half-vectors are built on it (`"sw_ldiv_type": "sub_isa"`).

---

## 4. Fine Granularity

With `--granularity fine`, the functions are split into **atoms**, one per function, mask variant and LMUL:

```text
functions/<category>/<v>/<l>/<function>.h

<v>: u (unmasked), m (Merge-Masked), z (Zero-Masked), s (Source-Masked)
<l>: m1 (LMUL 0 and 1), m2, m4, m8, d2
```

Each atom includes exactly what its functions call: the atoms of its dependencies (same ISA), the scalar atoms for the <span class="mipp-isa-badge lvl-3">L3</span> fallbacks, the atom of half the LMUL for the software LMUL wrappers, the `sub_isa` atom for the half-vectors. The atoms are written to memory first and flushed with their includes at the end of the layer.

**Umbrella** headers group the atoms (`generate_umbrella_headers()`):

| Umbrella | Includes |
| :--- | :--- |
| `functions/<category>/<v>/<function>.h` | the atoms of one mask variant, every LMUL |
| `functions/<category>/<l>/<function>.h` | the atoms of one LMUL, every mask variant |
| `functions/<category>/<function>.h` | the whole function (same path as the coarse header) |

The public headers follow the same scheme: `mipp/cpp/fun/m/m2/add.hpp` includes one atom, `mipp/cpp/fun/add.hpp` the whole function. The coarse public headers therefore exist with both granularities.

---

## 5. ISA Dispatch

The interface layers select the ISA at compile time:

1. `interfaces/c/common.h` tests the compiler macros and defines one `MIPP_<ISA>` macro (`__AVX512F__` → `MIPP_AVX512`, `__AVX__` → `MIPP_AVX`, ...), unless `MIPP_SCALAR` is already defined. The detection block of each ISA comes from its descriptor (`define`, `mipp_definitions`).
2. Each interface header includes the implementation of the selected ISA:

```c
// interfaces/c/functions/arithmetic/u/m1/add.h
#if defined(MIPP_SSE)
#include "mipp/internal/simd_ext/sse/c/functions/arithmetic/u/m1/add.h"
#elif defined(MIPP_AVX)
#include "mipp/internal/simd_ext/avx/c/functions/arithmetic/u/m1/add.h"
...
#endif
```

3. The C interface functions (`mipp_add_float32`) call the ISA functions (`mipp_avx_add_float32`) under the same `#if` chain; the C++ overloads of `simd_ext/<isa>/cpp/` wrap them for `mipp::rvd<T, LMUL, ISA>`.

Only the ISAs selected with `--simd-ext` appear in these chains. The C++ `mipp::ISA` enum lists every directory of `simd_ext/`, whatever the selection.

---

## 6. Category Headers

`--header-type category_header` writes one header per category instead of one per function. This mode is experimental: the code marks it as work in progress, and it is not tested by the CI. Use the default `function_header`.
