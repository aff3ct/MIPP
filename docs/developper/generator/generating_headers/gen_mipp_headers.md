# Header Generator (`gen_mipp_headers.py`)

`generator/gen_mipp_headers.py` is the main orchestrator script that emits the complete MIPP C and C++ header tree into `include/`.

---

## 1. What the Script Does

1. **Static Validation & Audits**: Runs integrity checks across registries in `helpers_headers/` and `simd_ext/`.
2. **ISA Emission**: For each detected ISA (discovered dynamically in `simd_ext/`), generates:
    - Low-level intrinsics wrappers
    - Typedefs and vector registers (`rvd` and `rvm`)
    - Level 0 (native), Level 1 (specific emulation), Level 2 (generic emulation), and Level 3 (scalar fallback) function implementations
3. **C Interface**: Emits canonical C99 headers (`include/mipp.h` and ISA-specific C function headers).
4. **C++ Interface**: Generates generic C++ template wrappers (`include/mipp.hpp`).
5. **C++ Object Model**: Generates the high-level `rvd` and `rvm` object classes (`include/mipp_object.hpp`).
6. **Summary Report**: Prints the implementation level distribution matrix across all target ISAs.

---

## 2. Usage & Options

```bash
cd generator
.venv/bin/python gen_mipp_headers.py [OPTIONS]
```

### Useful CLI Flags

- `--layers <isa1> <isa2> ...`: Restricts generation to specific target ISAs (e.g. `--layers sse avx`).
- `--audit <type>`: Selects static validation checks (`all`, `levels`, `dead-code`, `duplicates`, `json-structure`, `none`).
- `--clean`: Wipes the destination `include/` directory before emission.