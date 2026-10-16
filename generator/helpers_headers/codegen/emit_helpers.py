"""
Emit Helpers Module
Handles formatting and writing of C/C++ function prototypes and bodies, preprocessor blocks,
and specialized AVX ldiv structures.
"""
import sys
import re
import os

# Add parent directory to sys.path to find tools.py
sys.path.insert(1, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

from tools import *
from tools import build_func_name_internal
from codegen.implem_tracker import update_emulated

def emit_ifdef_begin_and_update_emulated(funcs, f, dt_key, ff, ifd, file, mask_kind=None):
    if ifd:
        print("#if " + ifd, file=file)
        update_emulated(funcs, f, dt_key, ff, ifd, mask_kind=mask_kind)

def emit_short_format_prologue(funcs_for_f, dt_ret, isa, file, lmul=0):
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

def emit_function_body(funcs, f, isa, dt, dt_par, dt_ret, ff, post_rendering, file, masked_version=None, lmul=0, level=None):
    func_name = build_func_name_internal(isa, dt, dt_par, dt_ret, f, masked_version=masked_version, lmul=lmul)

    print("static " + build_proto(funcs[f]["proto"], dt_par, dt_ret, isa, func_name, masked_version = masked_version, lmul=lmul) + " {", file=file)

    if level is None and ff is not None:
        level = ff.get("level", 1 if ("type" in ff and ff["type"] == "emulated") else 0)

    if level is not None:
        level_comments = {
            0: "Level 0 (Native Hardware)",
            1: "Level 1 (Dedicated Emulation)",
            2: "Level 2 (Generic Emulation)",
            3: "Level 3 (Scalar Fallback)"
        }
        if level in level_comments:
            print(f"\t// {level_comments[level]}", file=file)

    post_rendering = post_rendering.strip("\n")

    is_short = (ff["template"]["format"] == "short")
    has_res_assign = is_short and (funcs[f]["proto"]["ret"]["type"] in ("reg", "msk"))

    if is_short:
        # Original code had a redundant always-true condition; keep behavior identical.
        if funcs[f]["proto"]["args"] or (not funcs[f]["proto"]["args"]):
            emit_short_format_prologue(funcs[f], dt_ret, isa, file, lmul=lmul)
    
    body_lines = []
    first_code_line = True
    for line in post_rendering.split("\n"):
        if line.strip():
            if first_code_line and has_res_assign:
                line = line.lstrip()
                first_code_line = False
            elif not line.startswith("\t"):
                line = "\t" + line
            body_lines.append(line)
        else:
            body_lines.append("")

    print("\n".join(body_lines), file=file)

    if ff["template"]["format"] == "short":
        if funcs[f]["proto"]["ret"]["type"]:
            print("\treturn res;", file=file)

    print("}", file=file)


def emit_ifdef_end(ifd, file):
    """writes #endif to a file."""
    if ifd:
        print("#endif", file=file)

def emit_already_implemented_message(f, dt_key, file, generic=False):
    """print skip message because function already exists in file"""
    generic_str = "Generic " if generic else ""
    print("// '" + generic_str +  f + "<" + dt_key + ">' has been skipped (reason: \"Info: It has been implemented before.\").", file=file)

def emit_ifdef_begin(ifd, file):
    if ifd:
        print("#if " + ifd, file=file)

def gen_ldiv_structs_sub_isa(isa_base, isa_div, file):
    template = """typedef rvd_{{ isa_div.name }}_{{ datatype.category }}{{ datatype.n_bits }}_t rvd_{{ isa.name }}_{{ datatype.category }}{{ datatype.n_bits }}_d2_t;
typedef rvm_{{ isa_div.name }}_{{ datatype.category }}{{ datatype.n_bits }}_t rvm_{{ isa.name }}_{{ datatype.category }}{{ datatype.n_bits }}_d2_t;"""
    j2_template = Template(template, undefined=StrictUndefined)
    ldivs = [x for x in (isa_base.get("hw_lmul", []) + isa_base.get("sw_lmul", [])) if int(x) < 0]
    if any(int(x) == -2 for x in ldivs):
        for dt in isa_base["datatypes"]:
            print(j2_template.render(isa=isa_base, isa_div=isa_div, datatype=datatypes[dt]), file=file)

def gen_ldiv_defines_sub_isa(isa_base, isa_div, file):
    template = """#define MIPP_{{isa_name_upper}}_N_{{type_category_upper}}{{n_bits}}_D2 {{n_elmts_d2}}"""
    j2_template = Template(template, undefined=StrictUndefined)
    ldivs = [x for x in (isa_base.get("hw_lmul", []) + isa_base.get("sw_lmul", [])) if int(x) < 0]
    if any(int(x) == -2 for x in ldivs):
        for dt in isa_base["datatypes"]:
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

def gen_ldiv_structs_mask(isa, file):
    """
    d2 registers of the 'mask' strategy: a distinct type from the LMUL 1 one, with the same member
    (`r` or `m`), so that the lane-wise functions of LMUL 1 can be reused on it.
    """
    layout = isa.get("layout", None)
    if layout:
        # VLA ISAs (SVE): the member is the fixed-size type of LMUL 1, as in the LMUL 1 struct
        j2_rvd = Template(layout["rvd_struct_template"], undefined=StrictUndefined)
        j2_rvm = Template(layout["rvm_struct_template"], undefined=StrictUndefined)
        for dt in isa["datatypes"]:
            args = dict(
                isa=isa, datatype=datatypes[dt], isa_datatype=isa["datatypes"][dt], lsuffix_mipp="m1",
                vla_size=layout.get("size_symbol", None), isa_name_upper=isa["name"].upper(),
                type_category_upper=datatypes[dt]["category"].upper(),
            )
            for rendered in (j2_rvd.render(**args), j2_rvm.render(**args)):
                print(re.sub(r"_m1_t;$", "_d2_t;", rendered.strip()), file=file)
        return
    for dt in isa["datatypes"]:
        d = datatypes[dt]
        isa_dt = isa["datatypes"][dt]
        guard = isa_dt.get("if", None)
        name = f"{isa['name']}_{d['category']}{d['n_bits']}"
        n_macro = f"MIPP_{isa['name'].upper()}_N_{d['category'].upper()}{d['n_bits']}_D2"
        if guard:
            print(f"#if {guard}", file=file)
        print(f"typedef struct {{ {isa_dt['reg']} r; }} rvd_{name}_d2_t;", file=file)
        print(f"typedef struct {{ {isa_dt['msk']} m; }} rvm_{name}_d2_t;", file=file)
        if guard:
            print("#else", file=file)
            print(f"typedef struct {{ {d['category']}{d['n_bits']}_t r[{n_macro}]; }} rvd_{name}_d2_t;", file=file)
            print(f"typedef struct {{ uint{d['n_bits']}_t m[{n_macro}]; }} rvm_{name}_d2_t;", file=file)
            print("#endif", file=file)

def gen_ldiv_defines_mask(isa, file):
    layout = isa.get("layout", None)
    if layout and "defines_template" in layout:
        j2 = Template(layout["defines_template"], undefined=StrictUndefined)
        for dt in isa["datatypes"]:
            n_bits = datatypes[dt]["n_bits"]
            print(j2.render(
                type_category_upper=datatypes[dt]["category"].upper(), n_bits=n_bits, lsuffix_upper="D2",
                type_size=f"{layout['size_symbol']}/{n_bits}/2", vla_size=layout["size_symbol"],
            ), file=file)
        return
    gen_ldiv_defines_sub_isa(isa, None, file)

def emit_panic_stub(func_name: str, file=None, indent: str = "\t", unused_args=()) -> str:
    """
    Emits a single-line panic stub using the MIPP_PANIC_STUB macro.
    `unused_args`: names of the parameters to mark as unused (when no other branch uses them).
    """
    line = f"{indent}MIPP_PANIC_STUB(\"MIPP panic: '{func_name}' is unimplemented.\");"
    for name in unused_args:
        line = f"{indent}(void){name};\n" + line
    if file:
        print(line, file=file)
    return line
