# Header Generator (`gen_mipp_headers.py`)

`generator/gen_mipp_headers.py` is the main orchestrator script that emits the complete MIPP C and C++ header tree into `include/`.

---

## 1. What the Script Does

1. **Static Validation & Audits**: Runs integrity checks across registries in `helpers_headers/` and `simd_ext/`.
2. **ISA Emission**: For each detected ISA (discovered dynamically in `simd_ext/`), generates:
    - Low-level intrinsics wrappers
    - Typedefs and vector registers (`rvd` and `rvm`)
    - Level 0 (native), Level 1 (specific emulation), Level 2 (generic emulation), and Level 3 (scalar fallback) function implementations
3. **C API**: Emits the C headers (`include/mipp.h` and the per-function headers).
4. **C++ Functional API**: Emits the overloads and templates of namespace `mipp::` (`include/mipp.hpp`).
5. **C++ Object API**: Emits the `mipp::Rvd` and `mipp::Rvm` classes (`include/mipp_obj.hpp`).
6. **Summary Report**: Prints the implementation level distribution matrix across all target ISAs.

---

## 2. Usage & Options

From `generator/`, with the virtual environment activated (see `generator/README.md`):

```bash
./gen_mipp_headers.py [OPTIONS]
```

| Option | Default | Description |
| :--- | :--- | :--- |
| `--granularity {coarse,fine}` | `coarse` | `coarse` emits one public header per function (`<mipp/cpp/fun/add.hpp>`). `fine` additionally emits per-variant, per-LMUL and atomic headers (`<mipp/cpp/fun/m/add.hpp>`, `<mipp/cpp/fun/m2/add.hpp>`, `<mipp/cpp/fun/m/m2/add.hpp>`) and the corresponding umbrella headers. |
| `--simd-ext <isa> ...` | all discovered | Restricts the set of ISAs that exist in the generated tree. The `sub_isa` chain and the scalar fallback are always added. Use this option to produce a reduced distribution (e.g. `--simd-ext neon`). |
| `-l`, `--layers <layer> ...` | `all` | Selects which parts are (re)generated: ISA layers (one per directory of `simd_ext/`, e.g. `sse avx avx512 neon sve rvv scalar`; `--help` lists them), `all_isas`, `wrappers` (public C/C++/object headers) or `all`. Mainly useful together with `--no-clean` to regenerate one layer during development. |
| `--no-clean` | off | Do not delete `../include/` before generating. |
| `--header-type {function_header,category_header}` | `function_header` | Internal organization: one header per function, or one header per ISA category. |
| `--audit <audit> ...` | `all` | `levels`, `dead-code`, `duplicates`, `json-structure`, `all` or `none`. See [Static Audits](../../audits_and_verification.md). |

Examples:

```bash
./gen_mipp_headers.py --granularity fine             # full tree, as in the GitLab CI
./gen_mipp_headers.py --simd-ext avx512 --audit none # AVX-512 (+ AVX, SSE, scalar) only
./gen_mipp_headers.py --layers neon --no-clean       # regenerate the NEON layer in place
```