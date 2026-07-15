"""
Emit Helpers Module
Handles formatting and writing of C/C++ function prototypes and bodies, preprocessor blocks,
and specialized AVX ldiv structures.
"""
import sys
import os

# Add parent directory to sys.path to find tools.py
sys.path.insert(1, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

from tools import *
from tools import _build_func_name
from codegen.implem_tracker import _update_emulated

def _emit_ifdef_begin_and_update_emulated(funcs, f, dt_key, ff, ifd, file, mask_kind=None):
    if ifd:
        print("#if " + ifd, file=file)
        _update_emulated(funcs, f, dt_key, ff, ifd, mask_kind=mask_kind)

def _emit_short_format_prologue(funcs_for_f, dt_ret, isa, file, lmul=0):
    # Keep same layout as original.
    if funcs_for_f["proto"]["args"]:
        if funcs_for_f["proto"]["ret"]["type"] == "reg":
            print(
                "\t" + build_type(funcs_for_f["proto"]["ret"]["type"], datatypes[dt_ret], isa, lmul=lmul) + " res;",
                file=file,
            )
            print("\tres.r = ", end="", file=file)
        elif funcs_for_f["proto"]["ret"]["type"] == "msk":
            print(
                "\t" + build_type(funcs_for_f["proto"]["ret"]["type"], datatypes[dt_ret], isa, lmul=lmul) + " res;",
                file=file,
            )
            print("\tres.m = ", end="", file=file)
    else:
        if funcs_for_f["proto"]["ret"]["type"] == "reg":
            print(
                "\t" + build_type(funcs_for_f["proto"]["ret"]["type"], datatypes[dt_ret], isa, lmul=lmul) + " res;",
                file=file,
            )
            print("\tres.r = ", end="", file=file)
        elif funcs_for_f["proto"]["ret"]["type"] == "msk":
            print(
                "\t" + build_type(funcs_for_f["proto"]["ret"]["type"], datatypes[dt_ret], isa, lmul=lmul) + " res;",
                file=file,
            )
            print("\tres.m = ", end="", file=file)

def _emit_function_body(funcs, f, isa, dt, dt_par, dt_ret, ff, post_rendering, file, masked_version=None, lmul=0, level=None):
    func_name = _build_func_name(isa, dt, dt_par, dt_ret, f, masked_version=masked_version, lmul=lmul)

    print("static " + build_proto(funcs[f]["proto"], dt_par, dt_ret, isa, func_name, masked_version = masked_version, lmul=lmul) + " {", file=file)

    if level is None and ff is not None:
        level = ff.get("level", 1 if ("type" in ff and ff["type"] == "emulated") else 0)

    if level is not None:
        level_comments = {
            0: "Level 0 (Optimal / Native)",
            1: "Level 1 (Specific Emulated)",
            2: "Level 2 (Generic Emulated)",
            3: "Level 3 (Auto Scalar Fallback)"
        }
        if level in level_comments:
            print(f"\t// {level_comments[level]}", file=file)

    if ff["template"]["format"] == "short":
        # Original code had a redundant always-true condition; keep behavior identical.
        if funcs[f]["proto"]["args"] or (not funcs[f]["proto"]["args"]):
            _emit_short_format_prologue(funcs[f], dt_ret, isa, file,lmul=lmul)
    else:
        if not post_rendering.startswith("\t"):
            print("\t", end='', file=file)

    print(post_rendering, file=file)

    if ff["template"]["format"] == "short":
        if funcs[f]["proto"]["ret"]["type"]:
            print("\treturn res;", file=file)

    print("}", file=file)


def _emit_ifdef_end(ifd, file):
    """writes #endif to a file."""
    if ifd:
        print("#endif", file=file)

def _emit_already_implemented_message(f, dt_key, file, generic=False):
    """print skip message because function already exists in file"""
    generic_str = "Generic " if generic else ""
    print("// '" + generic_str +  f + "<" + dt_key + ">' has been skipped (reason: \"Info: It has been implemented before.\").", file=file)

def _emit_ifdef_begin(ifd, file):
    if ifd:
        print("#if " + ifd, file=file)

def _gen_ldiv_structs_avx(isa_base, isa_div, file):
    template = """typedef struct { rvd_{{ isa_div.name }}_{{ datatype.category }}{{ datatype.n_bits }}_t r1, r2; } rvd_{{ isa.name }}_{{ datatype.category }}{{ datatype.n_bits }}_d2_t;
typedef struct { rvm_{{ isa_div.name }}_{{ datatype.category }}{{ datatype.n_bits }}_t m1, m2; } rvm_{{ isa.name }}_{{ datatype.category }}{{ datatype.n_bits }}_d2_t;"""
    j2_template = Template(template, undefined=StrictUndefined)
    for dt in isa_base["datatypes"]:
        if "ldiv" in isa_base["datatypes"][dt] and len(isa_base["datatypes"][dt]["ldiv"]) > 0:
            print(j2_template.render(isa=isa_base, isa_div=isa_div, datatype=datatypes[dt]), file=file)

def _gen_ldiv_defines_avx(isa_base, isa_div, file):
    template = """#define MIPP_{{isa_name_upper}}_N_{{type_category_upper}}{{n_bits}}_D2 {{n_elmts_d2}}"""
    j2_template = Template(template, undefined=StrictUndefined)
    for dt in isa_base["datatypes"]:
        if "ldiv" in isa_base["datatypes"][dt] and len(isa_base["datatypes"][dt]["ldiv"]) > 0:
            n_elmts_d2 = int(isa_base["size"] / (2 * datatypes[dt]["n_bits"]))
            print(
                j2_template.render(
                    isa_name_upper=isa_base["name"].upper(),
                    type_category_upper=datatypes[dt]["category"].upper(),
                    n_bits=datatypes[dt]["n_bits"],
                    n_elmts_d2=n_elmts_d2,
                ),
                file=file,
            )
