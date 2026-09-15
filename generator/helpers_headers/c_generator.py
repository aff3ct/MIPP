"""
C Generator Module
Orchestrates the generation of C-style SIMD headers, registry defines, typedefs,
and fallback implementations for each SIMD ISA.
"""
from jinja2 import Template, StrictUndefined
import json
import re
import sys
import os
import copy

# Add the directory containing c_generator.py to path
sys.path.insert(1, os.path.dirname(os.path.abspath(__file__)))

from tools import *
from include_gen import *
from registry import *

from codegen.emit_helpers import (
    emit_ifdef_begin_and_update_emulated,
    emit_short_format_prologue,
    emit_ifdef_end,
    emit_already_implemented_message,
    emit_ifdef_begin,
    gen_ldiv_defines_sub_isa,
    gen_ldiv_structs_sub_isa,
)
from codegen.candidate_resolver import resolve_and_emit_missing_functions
from codegen.lmul_orchestrator import gen_c_lmul, gen_c_ldiv


def gen_c_defines(isa, file, vla_size=None):
    layout = isa.get("layout", None)
    if layout:
        template_def = layout["defines_template"]
    else:
        template_def = "#define MIPP_{{isa_name_upper}}_N_{{type_category_upper}}{{n_bits}}_{{lsuffix_upper}} {{type_size}}"

    j2_template = Template(template_def, undefined=StrictUndefined)

    # 1. Print RVD size defines
    isa_name_upper = isa["name"].upper()
    if layout and "size_symbol" in layout:
        size_symbol = str(vla_size) if vla_size is not None else layout["size_symbol"]
    else:
        size_symbol = str(isa["size"])

    print(f"#define MIPP_{isa_name_upper}_RVD_SIZE_BIT {size_symbol}", file=file)
    if not layout or vla_size is None or isinstance(vla_size, str) or isinstance(isa["size"], str):
        print(f"#if MIPP_{isa_name_upper}_RVD_SIZE_BIT == 0", file=file)
        print(f"\t#error \"MIPP_{isa_name_upper}_RVD_SIZE_BIT can't be null\"", file=file)
        print(f"#endif", file=file)

    if layout and "size_symbol" in layout and (vla_size is None or isinstance(vla_size, str)):
        print(f"#define MIPP_{isa_name_upper}_RVD_SIZE_BYTE {size_symbol}/8", file=file)
        print(f"#if MIPP_{isa_name_upper}_RVD_SIZE_BYTE == 0", file=file)
        print(f"\t#error \"MIPP_{isa_name_upper}_RVD_SIZE_BYTE can't be null\"", file=file)
        print(f"#endif", file=file)
    else:
        val = int(vla_size / 8) if (vla_size is not None and not isinstance(vla_size, str)) else int(isa["size"] / 8)
        print(f"#define MIPP_{isa_name_upper}_RVD_SIZE_BYTE {val}", file=file)

    # 2. Base N defines
    for dt in isa["datatypes"]:
        n_bits = datatypes[dt]["n_bits"]
        if layout and "size_symbol" in layout and (vla_size is None or isinstance(vla_size, str)):
            type_size = f"{size_symbol}/{n_bits}"
        else:
            type_size = str(int((vla_size if vla_size is not None else isa["size"]) / n_bits))
        
        print(f"#define MIPP_{isa_name_upper}_N_{datatypes[dt]['category'].upper()}{n_bits} {type_size}", file=file)

    # 3. Positive lmuls
    lmuls = [x for x in (isa.get("hw_lmul", [1]) if layout else [1]) + isa.get("sw_lmul", []) if x > 0]
    seen = set()
    lmuls = [x for x in lmuls if not (x in seen or seen.add(x))]
    if 1 in lmuls and "{{lsuffix_upper}}" not in template_def:
        lmuls = [x for x in lmuls if x != 1]

    for lmul in lmuls:
        lsuffix_upper = f"M{lmul}"
        coeff = f"*{lmul}" if lmul > 1 else ""
        for dt in isa["datatypes"]:
            n_bits = datatypes[dt]["n_bits"]
            if layout and "size_symbol" in layout and (vla_size is None or isinstance(vla_size, str)):
                type_size = f"{size_symbol}/{n_bits}{coeff}"
            else:
                type_size = str(int((vla_size if vla_size is not None else isa["size"]) / n_bits * lmul))
            print(j2_template.render(
                isa_name_upper=isa_name_upper,
                vla_size=size_symbol,
                n_bits=n_bits,
                type_size=type_size,
                type_category_upper=datatypes[dt]["category"].upper(),
                lsuffix_upper=lsuffix_upper
            ), file=file)

    # 4. Negative lmuls (ldivs)
    ldivs = [abs(x) for x in isa.get("hw_lmul", []) if x < 0] if layout else []
    for ldiv in ldivs:
        lsuffix_upper = f"D{ldiv}"
        for dt in isa["datatypes"]:
            n_bits = datatypes[dt]["n_bits"]
            if layout and "size_symbol" in layout and (vla_size is None or isinstance(vla_size, str)):
                type_size = f"{size_symbol}/{n_bits}/{ldiv}"
            else:
                type_size = str(int((vla_size if vla_size is not None else isa["size"]) / (n_bits * ldiv)))
            print(j2_template.render(
                isa_name_upper=isa_name_upper,
                vla_size=size_symbol,
                n_bits=n_bits,
                type_size=type_size,
                type_category_upper=datatypes[dt]["category"].upper(),
                lsuffix_upper=lsuffix_upper
            ), file=file)

def gen_c_structures(isa, file, is_scalar=False, vla_size=None):
    layout = isa.get("layout", None)
    if not layout:
        if is_scalar:
            rvd_tmpl = "typedef struct __attribute__((aligned(MIPP_{{isa_name_upper}}_RVD_SIZE_BYTE))) { {{isa_datatype.reg}} r[MIPP_{{isa_name_upper}}_N_{{type_category_upper}}{{datatype.n_bits}}]; } rvd_{{isa.name}}_{{datatype.category}}{{datatype.n_bits}}_t;"
            rvm_tmpl = "typedef struct __attribute__((aligned(MIPP_{{isa_name_upper}}_RVD_SIZE_BYTE))) { {{isa_datatype.msk}} m[MIPP_{{isa_name_upper}}_N_{{type_category_upper}}{{datatype.n_bits}}]; } rvm_{{isa.name}}_{{datatype.category}}{{datatype.n_bits}}_t;"
        else:
            rvd_tmpl = "typedef struct { {{ isa_datatype.reg }} r; } rvd_{{ isa.name }}_{{ datatype.category }}{{ datatype.n_bits }}_t;"
            rvm_tmpl = "typedef struct { {{ isa_datatype.msk }} m; } rvm_{{ isa.name }}_{{ datatype.category }}{{ datatype.n_bits }}_t;"
        
        layout = {
            "rvd_struct_template": rvd_tmpl,
            "rvm_struct_template": rvm_tmpl
        }

    size_symbol = str(vla_size) if vla_size is not None else layout.get("size_symbol", None)

    # 1. Vector typedefs (VLA only)
    if "vector_typedef_template" in layout:
        j2_vector_typedef = Template(layout["vector_typedef_template"], undefined=StrictUndefined)
        for lmul in [x for x in isa.get("hw_lmul", [1]) if x > 0]:
            resolved_isa = resolve_lmul_in_isa(isa, lmul)
            lsuffix_mipp = f"m{lmul}"
            lmul_expr = f"*{lmul}" if lmul > 1 else ""
            for dt in resolved_isa["datatypes"]:
                guard = resolved_isa["datatypes"][dt].get("if", None)
                if guard:
                    print(f"#if {guard}", file=file)
                print(j2_vector_typedef.render(
                    isa_datatype=resolved_isa["datatypes"][dt],
                    vla_size=size_symbol,
                    lsuffix_mipp=lsuffix_mipp,
                    lmul_expr=lmul_expr
                ), file=file)
                if guard:
                    print(f"#endif", file=file)
        for ldiv in [abs(x) for x in isa.get("hw_lmul", []) if x < 0]:
            resolved_isa = resolve_lmul_in_isa(isa, -ldiv)
            lsuffix_mipp = f"d{ldiv}"
            lmul_expr = f"/{ldiv}"
            for dt in resolved_isa["datatypes"]:
                if "if_lmul" in resolved_isa["datatypes"][dt] and str(-ldiv) in resolved_isa["datatypes"][dt]["if_lmul"]:
                    guard = resolved_isa["datatypes"][dt]["if_lmul"][str(-ldiv)]
                else:
                    guard = resolved_isa["datatypes"][dt].get("if", None)
                if guard == "0":
                    continue
                if guard:
                    print(f"#if {guard}", file=file)
                print(j2_vector_typedef.render(
                    isa_datatype=resolved_isa["datatypes"][dt],
                    vla_size=size_symbol,
                    lsuffix_mipp=lsuffix_mipp,
                    lmul_expr=lmul_expr
                ), file=file)
                if guard:
                    print(f"#endif", file=file)

    # 2. Mask typedefs (VLA only)
    if "mask_typedef_template" in layout:
        j2_mask_typedef = Template(layout["mask_typedef_template"], undefined=StrictUndefined)
        for lmul in [x for x in isa.get("hw_lmul", [1]) if x > 0]:
            resolved_isa = resolve_lmul_in_isa(isa, lmul)
            lsuffix_mipp = f"m{lmul}"
            lmul_expr = f"*{lmul}" if lmul > 1 else ""
            for dt in resolved_isa["datatypes"]:
                guard = resolved_isa["datatypes"][dt].get("if", None)
                if guard:
                    print(f"#if {guard}", file=file)
                print(j2_mask_typedef.render(
                    isa_datatype=resolved_isa["datatypes"][dt],
                    vla_size=size_symbol,
                    lsuffix_mipp=lsuffix_mipp,
                    lmul_expr=lmul_expr,
                    n_bits=datatypes[dt]["n_bits"]
                ), file=file)
                if guard:
                    print(f"#endif", file=file)
        for ldiv in [abs(x) for x in isa.get("hw_lmul", []) if x < 0]:
            resolved_isa = resolve_lmul_in_isa(isa, -ldiv)
            lsuffix_mipp = f"d{ldiv}"
            lmul_expr = f"/{ldiv}"
            for dt in resolved_isa["datatypes"]:
                if "if_lmul" in resolved_isa["datatypes"][dt] and str(-ldiv) in resolved_isa["datatypes"][dt]["if_lmul"]:
                    guard = resolved_isa["datatypes"][dt]["if_lmul"][str(-ldiv)]
                else:
                    guard = resolved_isa["datatypes"][dt].get("if", None)
                if guard == "0":
                    continue
                if guard:
                    print(f"#if {guard}", file=file)
                print(j2_mask_typedef.render(
                    isa_datatype=resolved_isa["datatypes"][dt],
                    vla_size=size_symbol,
                    lsuffix_mipp=lsuffix_mipp,
                    lmul_expr=lmul_expr,
                    n_bits=datatypes[dt]["n_bits"]
                ), file=file)
                if guard:
                    print(f"#endif", file=file)

    # 3. Rvd structs (native or emulated)
    j2_rvd_struct = Template(layout["rvd_struct_template"], undefined=StrictUndefined)
    hw_lmuls = isa.get("hw_lmul", [])
    if not hw_lmuls:
        hw_lmuls = [1]
    sw_lmuls_pos = [x for x in isa.get("sw_lmul", []) if int(x) > 0 and int(x) not in hw_lmuls]
    
    # Loop over all lmuls (1, 2, 4, 8)
    lmuls_to_gen = sorted(list(set([1] + all_lmul)))
    for lmul in lmuls_to_gen:
        lsuffix_mipp = f"m{lmul}"
        if lmul in hw_lmuls:
            # Native implementation using template
            resolved_isa = resolve_lmul_in_isa(isa, lmul)
            for dt in resolved_isa["datatypes"]:
                guard = resolved_isa["datatypes"][dt].get("if", None)
                indent = "\t" if guard else ""
                if guard:
                    print(f"#if {guard}", file=file)
                struct_str = j2_rvd_struct.render(
                    isa=resolved_isa,
                    datatype=datatypes[dt],
                    isa_datatype=resolved_isa["datatypes"][dt],
                    vla_size=size_symbol,
                    lsuffix_mipp=lsuffix_mipp,
                    isa_name_upper=resolved_isa["name"].upper(),
                    type_category_upper=datatypes[dt]["category"].upper(),
                )
                print(f"{indent}{struct_str}", file=file)
                
                # Immediate _m1 alias generation
                if lmul == 1:
                    if "{{lsuffix_mipp}}" in layout["rvd_struct_template"]:
                        print(f"{indent}typedef rvd_{isa['name']}_{datatypes[dt]['category']}{datatypes[dt]['n_bits']}_m1_t rvd_{isa['name']}_{datatypes[dt]['category']}{datatypes[dt]['n_bits']}_t;", file=file)
                    else:
                        print(f"{indent}typedef rvd_{isa['name']}_{datatypes[dt]['category']}{datatypes[dt]['n_bits']}_t rvd_{isa['name']}_{datatypes[dt]['category']}{datatypes[dt]['n_bits']}_m1_t;", file=file)
                
                if guard:
                    print(f"#else", file=file)
                    c_type = f"{datatypes[dt]['category']}{datatypes[dt]['n_bits']}_t"
                    if lmul == 1:
                        if "{{lsuffix_mipp}}" in layout["rvd_struct_template"]:
                            print(f"	typedef struct __attribute__((aligned(MIPP_{isa['name'].upper()}_RVD_SIZE_BYTE))) {{ {c_type} r[MIPP_{isa['name'].upper()}_N_{datatypes[dt]['category'].upper()}{datatypes[dt]['n_bits']}]; }} rvd_{isa['name']}_{datatypes[dt]['category']}{datatypes[dt]['n_bits']}_m1_t;", file=file)
                            print(f"	typedef rvd_{isa['name']}_{datatypes[dt]['category']}{datatypes[dt]['n_bits']}_m1_t rvd_{isa['name']}_{datatypes[dt]['category']}{datatypes[dt]['n_bits']}_t;", file=file)
                        else:
                            print(f"	typedef struct __attribute__((aligned(MIPP_{isa['name'].upper()}_RVD_SIZE_BYTE))) {{ {c_type} r[MIPP_{isa['name'].upper()}_N_{datatypes[dt]['category'].upper()}{datatypes[dt]['n_bits']}]; }} rvd_{isa['name']}_{datatypes[dt]['category']}{datatypes[dt]['n_bits']}_t;", file=file)
                            print(f"	typedef rvd_{isa['name']}_{datatypes[dt]['category']}{datatypes[dt]['n_bits']}_t rvd_{isa['name']}_{datatypes[dt]['category']}{datatypes[dt]['n_bits']}_m1_t;", file=file)
                    else:
                        print(f"	typedef struct __attribute__((aligned(MIPP_{isa['name'].upper()}_RVD_SIZE_BYTE))) {{ {c_type} r[MIPP_{isa['name'].upper()}_N_{datatypes[dt]['category'].upper()}{datatypes[dt]['n_bits']}_M{lmul}]; }} rvd_{isa['name']}_{datatypes[dt]['category']}{datatypes[dt]['n_bits']}_{lsuffix_mipp}_t;", file=file)
                    print(f"#endif", file=file)
        elif lmul in sw_lmuls_pos:
            # Emulated pairwise implementation
            lmul_2 = int(lmul / 2)
            for dt in isa["datatypes"]:
                print(f"typedef struct {{ rvd_{isa['name']}_{datatypes[dt]['category']}{datatypes[dt]['n_bits']}_m{lmul_2}_t r1, r2; }} rvd_{isa['name']}_{datatypes[dt]['category']}{datatypes[dt]['n_bits']}_m{lmul}_t;", file=file)

    # Negative lmuls (ldivs, VLA only)
    for ldiv in [abs(x) for x in isa.get("hw_lmul", []) if x < 0]:
        lsuffix_mipp = f"d{ldiv}"
        resolved_isa = resolve_lmul_in_isa(isa, -ldiv)
        for dt in resolved_isa["datatypes"]:
            dt_cat = datatypes[dt]['category']
            n_bits = datatypes[dt]['n_bits']
            c_type = f"{dt_cat}{n_bits}_t"
            if "if_lmul" in resolved_isa["datatypes"][dt] and str(-ldiv) in resolved_isa["datatypes"][dt]["if_lmul"]:
                guard = resolved_isa["datatypes"][dt]["if_lmul"][str(-ldiv)]
            else:
                guard = resolved_isa["datatypes"][dt].get("if", None)

            def print_ldiv_fallback_typedef_rvd(indent=""):
                if size_symbol and ldiv > 1:
                    min_vlen = n_bits * ldiv
                    print(f"{indent}#if defined({size_symbol}) && {size_symbol} >= {min_vlen}", file=file)
                    print(f"{indent}\ttypedef struct __attribute__((aligned((MIPP_{isa['name'].upper()}_RVD_SIZE_BYTE) / {ldiv}))) {{ {c_type} r[MIPP_{isa['name'].upper()}_N_{dt_cat.upper()}{n_bits}_D{ldiv}]; }} rvd_{isa['name']}_{dt_cat}{n_bits}_{lsuffix_mipp}_t;", file=file)
                    print(f"{indent}#else", file=file)
                    print(f"{indent}\ttypedef struct __attribute__((aligned(MIPP_{isa['name'].upper()}_RVD_SIZE_BYTE))) {{ {c_type} r[MIPP_{isa['name'].upper()}_N_{dt_cat.upper()}{n_bits}]; }} rvd_{isa['name']}_{dt_cat}{n_bits}_{lsuffix_mipp}_t;", file=file)
                    print(f"{indent}#endif", file=file)
                else:
                    print(f"{indent}typedef struct __attribute__((aligned(MIPP_{isa['name'].upper()}_RVD_SIZE_BYTE))) {{ {c_type} r[MIPP_{isa['name'].upper()}_N_{dt_cat.upper()}{n_bits}]; }} rvd_{isa['name']}_{dt_cat}{n_bits}_{lsuffix_mipp}_t;", file=file)

            if guard == "0":
                print_ldiv_fallback_typedef_rvd("")
            else:
                if guard:
                    print(f"#if {guard}", file=file)
                print(j2_rvd_struct.render(
                    isa=resolved_isa,
                    datatype=datatypes[dt],
                    isa_datatype=resolved_isa["datatypes"][dt],
                    vla_size=size_symbol,
                    lsuffix_mipp=lsuffix_mipp,
                    isa_name_upper=resolved_isa["name"].upper(),
                    type_category_upper=datatypes[dt]["category"].upper(),
                ), file=file)
                if guard:
                    print(f"#else", file=file)
                    print_ldiv_fallback_typedef_rvd("\t")
                    print(f"#endif", file=file)

    # 4. Rvm structs (native or emulated)
    j2_rvm_struct = Template(layout["rvm_struct_template"], undefined=StrictUndefined)
    for lmul in lmuls_to_gen:
        lsuffix_mipp = f"m{lmul}"
        if lmul in hw_lmuls:
            # Native implementation using template
            resolved_isa = resolve_lmul_in_isa(isa, lmul)
            for dt in resolved_isa["datatypes"]:
                guard = resolved_isa["datatypes"][dt].get("if", None)
                indent = "\t" if guard else ""
                if guard:
                    print(f"#if {guard}", file=file)
                struct_str = j2_rvm_struct.render(
                    isa=resolved_isa,
                    datatype=datatypes[dt],
                    isa_datatype=resolved_isa["datatypes"][dt],
                    vla_size=size_symbol,
                    lsuffix_mipp=lsuffix_mipp,
                    isa_name_upper=resolved_isa["name"].upper(),
                    type_category_upper=datatypes[dt]["category"].upper(),
                )
                print(f"{indent}{struct_str}", file=file)
                
                # Immediate _m1 alias generation
                if lmul == 1:
                    if "{{lsuffix_mipp}}" in layout["rvd_struct_template"]:
                        print(f"{indent}typedef rvm_{isa['name']}_{datatypes[dt]['category']}{datatypes[dt]['n_bits']}_m1_t rvm_{isa['name']}_{datatypes[dt]['category']}{datatypes[dt]['n_bits']}_t;", file=file)
                    else:
                        print(f"{indent}typedef rvm_{isa['name']}_{datatypes[dt]['category']}{datatypes[dt]['n_bits']}_t rvm_{isa['name']}_{datatypes[dt]['category']}{datatypes[dt]['n_bits']}_m1_t;", file=file)

                if guard:
                    print(f"#else", file=file)
                    mask_type = f"uint{datatypes[dt]['n_bits']}_t"
                    if lmul == 1:
                        if "{{lsuffix_mipp}}" in layout["rvd_struct_template"]:
                            print(f"	typedef struct __attribute__((aligned(MIPP_{isa['name'].upper()}_RVD_SIZE_BYTE))) {{ {mask_type} m[MIPP_{isa['name'].upper()}_N_{datatypes[dt]['category'].upper()}{datatypes[dt]['n_bits']}]; }} rvm_{isa['name']}_{datatypes[dt]['category']}{datatypes[dt]['n_bits']}_m1_t;", file=file)
                            print(f"	typedef rvm_{isa['name']}_{datatypes[dt]['category']}{datatypes[dt]['n_bits']}_m1_t rvm_{isa['name']}_{datatypes[dt]['category']}{datatypes[dt]['n_bits']}_t;", file=file)
                        else:
                            print(f"	typedef struct __attribute__((aligned(MIPP_{isa['name'].upper()}_RVD_SIZE_BYTE))) {{ {mask_type} m[MIPP_{isa['name'].upper()}_N_{datatypes[dt]['category'].upper()}{datatypes[dt]['n_bits']}]; }} rvm_{isa['name']}_{datatypes[dt]['category']}{datatypes[dt]['n_bits']}_t;", file=file)
                            print(f"	typedef rvm_{isa['name']}_{datatypes[dt]['category']}{datatypes[dt]['n_bits']}_t rvm_{isa['name']}_{datatypes[dt]['category']}{datatypes[dt]['n_bits']}_m1_t;", file=file)
                    else:
                        print(f"	typedef struct __attribute__((aligned(MIPP_{isa['name'].upper()}_RVD_SIZE_BYTE))) {{ {mask_type} m[MIPP_{isa['name'].upper()}_N_{datatypes[dt]['category'].upper()}{datatypes[dt]['n_bits']}_M{lmul}]; }} rvm_{isa['name']}_{datatypes[dt]['category']}{datatypes[dt]['n_bits']}_{lsuffix_mipp}_t;", file=file)
                    print(f"#endif", file=file)
        elif lmul in sw_lmuls_pos:
            # Emulated pairwise implementation
            lmul_2 = int(lmul / 2)
            for dt in isa["datatypes"]:
                print(f"typedef struct {{ rvm_{isa['name']}_{datatypes[dt]['category']}{datatypes[dt]['n_bits']}_m{lmul_2}_t m1, m2; }} rvm_{isa['name']}_{datatypes[dt]['category']}{datatypes[dt]['n_bits']}_m{lmul}_t;", file=file)

    # Negative lmuls (ldivs, VLA only)
    for ldiv in [abs(x) for x in isa.get("hw_lmul", []) if x < 0]:
        lsuffix_mipp = f"d{ldiv}"
        resolved_isa = resolve_lmul_in_isa(isa, -ldiv)
        for dt in resolved_isa["datatypes"]:
            dt_cat = datatypes[dt]['category']
            n_bits = datatypes[dt]['n_bits']
            mask_type = f"uint{n_bits}_t"
            if "if_lmul" in resolved_isa["datatypes"][dt] and str(-ldiv) in resolved_isa["datatypes"][dt]["if_lmul"]:
                guard = resolved_isa["datatypes"][dt]["if_lmul"][str(-ldiv)]
            else:
                guard = resolved_isa["datatypes"][dt].get("if", None)

            def print_ldiv_fallback_typedef_rvm(indent=""):
                if size_symbol and ldiv > 1:
                    min_vlen = n_bits * ldiv
                    print(f"{indent}#if defined({size_symbol}) && {size_symbol} >= {min_vlen}", file=file)
                    print(f"{indent}\ttypedef struct __attribute__((aligned((MIPP_{isa['name'].upper()}_RVD_SIZE_BYTE) / {ldiv}))) {{ {mask_type} m[MIPP_{isa['name'].upper()}_N_{dt_cat.upper()}{n_bits}_D{ldiv}]; }} rvm_{isa['name']}_{dt_cat}{n_bits}_{lsuffix_mipp}_t;", file=file)
                    print(f"{indent}#else", file=file)
                    print(f"{indent}\ttypedef struct __attribute__((aligned(MIPP_{isa['name'].upper()}_RVD_SIZE_BYTE))) {{ {mask_type} m[MIPP_{isa['name'].upper()}_N_{dt_cat.upper()}{n_bits}]; }} rvm_{isa['name']}_{dt_cat}{n_bits}_{lsuffix_mipp}_t;", file=file)
                    print(f"{indent}#endif", file=file)
                else:
                    print(f"{indent}typedef struct __attribute__((aligned(MIPP_{isa['name'].upper()}_RVD_SIZE_BYTE))) {{ {mask_type} m[MIPP_{isa['name'].upper()}_N_{dt_cat.upper()}{n_bits}]; }} rvm_{isa['name']}_{dt_cat}{n_bits}_{lsuffix_mipp}_t;", file=file)

            if guard == "0":
                print_ldiv_fallback_typedef_rvm("")
            else:
                if guard:
                    print(f"#if {guard}", file=file)
                print(j2_rvm_struct.render(
                    isa=resolved_isa,
                    datatype=datatypes[dt],
                    isa_datatype=resolved_isa["datatypes"][dt],
                    vla_size=size_symbol,
                    lsuffix_mipp=lsuffix_mipp,
                    isa_name_upper=resolved_isa["name"].upper(),
                    type_category_upper=datatypes[dt]["category"].upper(),
                ), file=file)
                if guard:
                    print(f"#else", file=file)
                    print_ldiv_fallback_typedef_rvm("\t")
                    print(f"#endif", file=file)

    sub_isa_name = isa.get("sub_isa", None)
    if sub_isa_name:
        sub_isa = load_isa_config(sub_isa_name)[0]
        if sub_isa:
            gen_ldiv_structs_sub_isa(isa, sub_isa, file)
            gen_ldiv_defines_sub_isa(isa, sub_isa, file)

def register_candidates(isa, funcs, implems, cand_type="native_or_emu", lmul=0):
    if "candidates" not in isa:
        isa["candidates"] = []
    for f in implems:
        if f not in funcs:
            print("Panic: '" + f + "' function does not exist.")
            exit(-1)
        for ff in implems[f]:
            for dt in ff["datatypes"]:
                dt_par, dt_ret = compute_dt_par_dt_ret(funcs, f, dt)
                ff_local = ff.copy()
                guards = []
                if cand_type in ["native_or_emu", "generic_emu"]:
                    g_par = None
                    g_ret = None
                    if "if_lmul" in isa.get("datatypes", {}).get(dt_par, {}) and str(lmul) in isa["datatypes"][dt_par]["if_lmul"]:
                        g_par = isa["datatypes"][dt_par]["if_lmul"][str(lmul)]
                    if "if_lmul" in isa.get("datatypes", {}).get(dt_ret, {}) and str(lmul) in isa["datatypes"][dt_ret]["if_lmul"]:
                        g_ret = isa["datatypes"][dt_ret]["if_lmul"][str(lmul)]
                    if not g_par:
                        g_par = isa.get("datatypes", {}).get(dt_par, {}).get("if", None)
                    if not g_ret:
                        g_ret = isa.get("datatypes", {}).get(dt_ret, {}).get("if", None)
                    if g_par: guards.append(g_par)
                    if g_ret and g_ret not in guards: guards.append(g_ret)

                guard = " && ".join(guards) if guards else None
                if guard:
                    if "if" in ff_local and ff_local["if"]:
                        ff_local["if"] = ff_local["if"] + " && " + guard
                    else:
                        ff_local["if"] = guard

                level = ff.get("level", 1 if ("type" in ff and ff["type"] == "emulated") else 0)
                if cand_type == "generic_emu":
                    level = 2

                c_dict = {
                    "type": cand_type,
                    "f": f,
                    "ff": ff_local,
                    "dt": dt,
                    "emitted": False,
                    "level": level
                }
                if c_dict not in isa["candidates"]:
                    isa["candidates"].append(c_dict)

def register_all_candidates(isa, funcs, native_implems, emu_implems, lmul=0):
    register_candidates(isa, funcs, native_implems, cand_type="native_or_emu", lmul=lmul)
    register_candidates(isa, funcs, emu_implems, cand_type="native_or_emu", lmul=lmul)
    register_candidates(isa, funcs, implems_generic_emu, cand_type="generic_emu", lmul=lmul)
    register_candidates(isa, funcs, implems_mask_generic_emu, cand_type="generic_emu", lmul=lmul)

def gen_c_functions(isa, file, funcs, implems, lmul=0):
    register_candidates(isa, funcs, implems, cand_type="native_or_emu", lmul=lmul)

def gen_c_generic_functions(isa, file, funcs, implems, lmul=0):
    register_candidates(isa, funcs, implems, cand_type="generic_emu", lmul=lmul)

def gen_c_missing_functions(isa, file, funcs):
    resolve_and_emit_missing_functions(isa, file, funcs, lmul=0, emit_separators=False)

def gen_c_missing_functions_lmul(isa, file, funcs, lmul):
    resolve_and_emit_missing_functions(isa, file, funcs, lmul=lmul, emit_separators=True)

def resolve_lmul_in_isa(isa, lmul):
    resolved_isa = copy.deepcopy(isa)
    for dt in resolved_isa["datatypes"]:
        dt_cfg = resolved_isa["datatypes"][dt]
        
        # 1. Scan for all placeholders in string values of this datatype
        placeholders = set()
        for val in dt_cfg.values():
            if isinstance(val, str):
                placeholders.update(re.findall(r'\{([a-zA-Z0-9_]+)\}', val))
                
        # 2. Resolve values for each found placeholder with strict checks
        fmt_params = {}
        for p in placeholders:
            if p not in dt_cfg:
                print(f"Error: Datatype '{dt}' in ISA '{isa['name']}' has a template referencing placeholder '{{{p}}}', "
                      f"but '{p}' is not defined as a field in its configuration in the JSON file.", file=sys.stderr)
                sys.exit(1)
                
            if isinstance(dt_cfg[p], dict):
                # Check if current lmul exists in mapping dictionary
                if str(lmul) not in dt_cfg[p]:
                    print(f"Error: Datatype '{dt}' in ISA '{isa['name']}' defines a mapping for placeholder '{{{p}}}', "
                          f"but is missing a configuration for the current lmul value '{lmul}'. "
                          f"Available lmul keys: {list(dt_cfg[p].keys())}", file=sys.stderr)
                    sys.exit(1)
                fmt_params[p] = dt_cfg[p][str(lmul)]
            else:
                # Constant value
                fmt_params[p] = str(dt_cfg[p])

        # 3. Format the configurations of this datatype
        for key in list(dt_cfg.keys()):
            if isinstance(dt_cfg[key], str):
                # Only format if placeholders in the string are resolved
                active_placeholders = re.findall(r'\{([a-zA-Z0-9_]+)\}', dt_cfg[key])
                sub_params = {p: fmt_params[p] for p in active_placeholders if p in fmt_params}
                if sub_params:
                    dt_cfg[key] = dt_cfg[key].format(**sub_params)
                    
    return resolved_isa

def generate_c_layer(isa, include_manager, native_implems, emu_implems):


    # Pre-process emu_implems to set default type
    for iemu in emu_implems:
        for sub_iemu in emu_implems[iemu]:
            if "type" not in sub_iemu:
                sub_iemu["type"] = "emulated"

    # 1. Emit the common header specific to the ISA
    file_common = include_manager.get_fd(isa["name"], "common")
    if file_common is None:
        print(f"Panic: common.h file descriptor not found for {isa['name']}.", file=sys.stderr)
        exit(-1)

    if "header_template" not in isa:
        print(f"Panic: 'header_template' is missing from {isa['name']}_isa.json config file.", file=sys.stderr)
        exit(-1)

    header_tpl_val = isa["header_template"]
    if isinstance(header_tpl_val, list):
        header_tpl_val = "\n".join(header_tpl_val)
    tpl_header = Template(header_tpl_val, undefined=StrictUndefined).render(name=isa["name"], name_upper=isa["name"].upper())
    print(tpl_header, file=file_common)
    print("", file=file_common)

    # 2. Emit the defines and structures
    gen_c_defines(isa, file_common)
    print("", file=file_common)

    gen_c_structures(isa, file_common, is_scalar=isa.get("is_scalar", False))
    print("", file=file_common)

    print(f"#endif /* MY_INTRINSICS_PLUS_PLUS_IMPL_GEN_{isa['name'].upper()}_H_ */", file=file_common)

    # 3. Register and resolve hardware candidates (HW LMUL)
    copy_interfaces = copy.deepcopy(interfaces)
    hw_lmuls = isa.get("hw_lmul", [1])
    
    # Positive / non-negative hw_lmul (0 is added explicitly; negative values like -2 are processed separately)
    hw_lmuls_pos = sorted(list(set([0] + [int(x) for x in hw_lmuls if int(x) >= 0])))
    for lmul in hw_lmuls_pos:
        resolved_isa = resolve_lmul_in_isa(isa, str(lmul))
        resolved_isa["candidates"] = []
        register_all_candidates(resolved_isa, copy_interfaces, native_implems, emu_implems, lmul=lmul)
        resolve_and_emit_missing_functions(resolved_isa, include_manager, copy_interfaces, lmul=lmul, emit_separators=(lmul != 0))

    # Negative hw_lmul values (fractional LMUL/ldiv like -2, -4, -8, if present)
    hw_lmuls_neg = sorted([int(x) for x in hw_lmuls if int(x) < 0])
    for lmul_neg in hw_lmuls_neg:
        resolved_isa = resolve_lmul_in_isa(isa, str(lmul_neg))
        resolved_isa["candidates"] = []
        register_all_candidates(resolved_isa, copy_interfaces, native_implems, emu_implems, lmul=lmul_neg)
        resolve_and_emit_missing_functions(resolved_isa, include_manager, copy_interfaces, lmul=lmul_neg, emit_separators=True)

    # 4. Generate software wrappers (SW LMUL)
    sw_lmuls = [x for x in isa.get("sw_lmul", []) if int(x) > 0]
    if sw_lmuls:
        # Generate software wrappers
        gen_c_lmul(isa, include_manager, copy_interfaces, sw_lmuls)

    # Generate ldiv wrappers if sub_isa is specified
    sub_isa_name = isa.get("sub_isa", None)
    if sub_isa_name:
        sub_isa = load_isa_config(sub_isa_name)[0]
        if sub_isa:
            gen_c_ldiv(isa, sub_isa, include_manager, copy_interfaces)

    # 5. Resolve dependencies and create glue file
    include_manager.resolve_all_dependencies(isa["name"], copy_interfaces)
    include_manager.create_glue_file(isa["name"], f"mipp_{isa['name']}.h")
    include_manager.close_layer_fds(isa["name"])
