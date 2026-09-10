# Generic Emulation Registries

Generic Level 2 emulations provide portable algorithmic fallbacks using other MIPP functions when an ISA lacks a direct hardware instruction.

They are defined in `generator/helpers_headers/`:

- `generic_emu_templates.json`: Algorithmic templates written using the [Mini-Templating DSL](../../../templating_dsl.md).
- `generic_emu_implems.json`: Mappings between functions, datatypes, and generic templates.
- `generic_emu_templates_mask.json` / `generic_emu_implems_mask.json`: Emulations for masked operations (`_mask`, `_maskz`, `_masks`).
- `generic_emu_templates_lmulh.json` / `generic_emu_implems_lmulh.json`: Emulations for horizontal reduction operations across vector chunks.

---

## 1. Template Definitions

In `generic_emu_templates.json`, operations are defined generically across data types:

```json
{
    "abs": {
        "format": "long",
        "code": [
            "%r<tp>% opp_r0 = %sub<tp>%( %set0<tp>%(), r0 );",
            "return %blend<tp>%(opp_r0, r0, %cmplt<tp>%(r0, %set0<tp>%()));"
        ]
    }
}
```

The DSL placeholders `%r<tp>%`, `%sub<tp>%`, `%set0<tp>%`, etc., are automatically resolved by `generator/helpers_headers/tools.py` for every targeted data type.

---

## 2. Implementation Mappings

In `generic_emu_implems.json`, functions are mapped to generic templates:

```json
{
    "abs": [
        {
            "datatypes": "all_float",
            "template_ref": "tpl_generic_emu.abs_float"
        },
        {
            "datatypes": "all_int",
            "template_ref": "tpl_generic_emu.abs"
        }
    ]
}
```

- `template_ref`: Namespaced reference to a template key in `generic_emu_templates.json` (prefix `tpl_generic_emu.`).
- `preferred_simd_ext` (optional): Restricts generic emulation preference to specific target ISAs when alternative implementations exist.