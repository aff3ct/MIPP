# Documentation Generator (`gen_mipp_docs.py`)

`generator/gen_mipp_docs.py` is the orchestrator that generates the API Reference (`docs/funcs_support/`) and Hardware Support (`docs/isas_support/`) sections of the documentation.

Instead of maintaining documentation tables by hand, they are synthesized directly from:

- `generator/helpers_headers/registry_interfaces.json` (canonical signatures and supported datatypes)
- `generator/helpers_headers/registry_categories.json` (functional groupings)
- `generator/helpers_headers/funcs_docs.json` (human-readable descriptions and mathematical equations)
- `generator/simd_ext/<isa>/<isa>_native_implems.json` (hardware support matrices)
- `generator/helpers_headers/generic_emu_implems.json` (Level 2 emulation coverage)

## Running the Documentation Generator

```bash
cd generator
.venv/bin/python gen_mipp_docs.py
```

The script updates:

- `docs/funcs_support/`: Function pages with C99 and C++ prototype tabs, parameter tables, and support matrices.
- `docs/isas_support/`: Hardware architecture pages showing instruction mappings and support levels per data type.