"""
Utilities of the three APIs, written by hand in `templates/` and rendered here:

- `include/mipp/c/utils.h` (C API, `mipp_utils.tpl.h`): aligned allocation (`mipp_malloc`, `mipp_free`,
  `mipp_is_aligned`, `MIPP_REQUIRED_ALIGNMENT`) and the printing of the registers and masks
  (`mipp_dump_<type>[_<lmul>]`, `mipp_fdump_...`, `_k` for the masks), one function per datatype and LMUL;
- `include/mipp/cpp/utils.hpp` (C++ Functional API, `mipp_utils.tpl.hpp`): `mipp::malloc`, `mipp::free`,
  `mipp::allocator`, `mipp::vector`, `mipp::dump`, `mipp::sum`;
- `include/mipp/obj/utils.hpp` (C++ Object API, `mipp_obj_utils.tpl.hpp`): `operator<<`, `reduce` and the
  operations of `mipp::op`;
- `include/mipp/cpp/patterns.hpp` and `include/mipp/obj/patterns.hpp` (C++17, `mipp_patterns.tpl.hpp`,
  `mipp_obj_patterns.tpl.hpp`): `permute<P>` and `permute2<P>`, permutations whose pattern is known at compile time.
  They pull about 20 rearrangement functions: only the global headers include them, not the utils headers.
- `include/mipp/c/transpose.h`, `include/mipp/cpp/transpose.hpp` and `include/mipp/obj/transpose.hpp`
  (`mipp_transpose.tpl.h`, `mipp_transpose.tpl.hpp`, `mipp_obj_transpose.tpl.hpp`): `transpose` and `transpose_b128`,
  in place on an array of registers (steps of ziplo/ziphi), one C function per datatype and LMUL. Only the global
  headers include them.

These functions are not in the registry: they are not implemented per ISA, they are written once on top of the
generated functions (storeu, tovd, hadd, combine, ncvts, ...). `mipp.h`, `mipp.hpp` and `mipp_obj.hpp` include them.
The API Explorer lists them in the category `utilities` from `registry_utilities.json`: a new utility gets an
entry there (signatures in the three APIs, header, section of the user documentation).
"""
import os

from jinja2 import Environment, FileSystemLoader, StrictUndefined

_TEMPLATES_DIR = os.path.join(os.path.dirname(os.path.abspath(__file__)), "templates")

# printf format and cast of each datatype (dump of the C API)
_C_DATATYPES = [
    {"name": "float64", "cstd": "float64_t", "fmt": "%g", "cast": "double"},
    {"name": "float32", "cstd": "float32_t", "fmt": "%g", "cast": "double"},
    {"name": "int64", "cstd": "int64_t", "fmt": "%lld", "cast": "long long"},
    {"name": "int32", "cstd": "int32_t", "fmt": "%ld", "cast": "long"},
    {"name": "int16", "cstd": "int16_t", "fmt": "%d", "cast": "int"},
    {"name": "int8", "cstd": "int8_t", "fmt": "%d", "cast": "int"},
    {"name": "uint64", "cstd": "uint64_t", "fmt": "%llu", "cast": "unsigned long long"},
    {"name": "uint32", "cstd": "uint32_t", "fmt": "%lu", "cast": "unsigned long"},
    {"name": "uint16", "cstd": "uint16_t", "fmt": "%u", "cast": "unsigned"},
    {"name": "uint8", "cstd": "uint8_t", "fmt": "%u", "cast": "unsigned"},
]

# public C names: no suffix for LMUL 1; `n` multiplies the MIPP_N_<TYPE> macro (lanes of LMUL 1)
_C_LMULS = [
    {"sfx": "", "n": "", "guard": None},
    {"sfx": "_m2", "n": " * 2", "guard": None},
    {"sfx": "_m4", "n": " * 4", "guard": None},
    {"sfx": "_m8", "n": " * 8", "guard": None},
    {"sfx": "_d2", "n": " / 2", "guard": "defined(MIPP_LDIV_2)"},
]


def generate_utils(output_dir="../include"):
    """Renders the utility headers of the three APIs in `output_dir/mipp/{c,cpp,obj}/utils.h(pp)`."""
    env = Environment(loader=FileSystemLoader(_TEMPLATES_DIR), undefined=StrictUndefined,
                      keep_trailing_newline=True, trim_blocks=False)
    outputs = [
        ("mipp_utils.tpl.h", os.path.join(output_dir, "mipp", "c", "utils.h")),
        ("mipp_utils.tpl.hpp", os.path.join(output_dir, "mipp", "cpp", "utils.hpp")),
        ("mipp_obj_utils.tpl.hpp", os.path.join(output_dir, "mipp", "obj", "utils.hpp")),
        ("mipp_patterns.tpl.hpp", os.path.join(output_dir, "mipp", "cpp", "patterns.hpp")),
        ("mipp_obj_patterns.tpl.hpp", os.path.join(output_dir, "mipp", "obj", "patterns.hpp")),
        ("mipp_transpose.tpl.h", os.path.join(output_dir, "mipp", "c", "transpose.h")),
        ("mipp_transpose.tpl.hpp", os.path.join(output_dir, "mipp", "cpp", "transpose.hpp")),
        ("mipp_obj_transpose.tpl.hpp", os.path.join(output_dir, "mipp", "obj", "transpose.hpp")),
    ]
    for tpl, path in outputs:
        os.makedirs(os.path.dirname(path), exist_ok=True)
        content = env.get_template(tpl).render(datatypes=_C_DATATYPES, lmuls=_C_LMULS)
        with open(path, "w", encoding="utf-8") as f:
            f.write(content)
