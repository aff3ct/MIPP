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
    if "vla" in isa:
        # Generic VLA define generation
        vla_config = isa["vla"]
        template_def = vla_config["defines_template"]
        j2_template = Template(template_def, undefined=StrictUndefined)
        
        # Determine the size symbol
        size_symbol = str(vla_size) if vla_size is not None else vla_config["size_symbol"]
        
        # Print RVD size defines
        isa_name_upper = isa["name"].upper()
        print(f"#define MIPP_{isa_name_upper}_RVD_SIZE_BIT {size_symbol}", file=file)
        if vla_size is None or isinstance(vla_size, str):
            # VLA size is symbol (e.g. __riscv_v_fixed_vlen)
            print(f"#if MIPP_{isa_name_upper}_RVD_SIZE_BIT == 0", file=file)
            print(f"\t#error \"MIPP_{isa_name_upper}_RVD_SIZE_BIT can't be null\"", file=file)
            print(f"#endif", file=file)
            print(f"#define MIPP_{isa_name_upper}_RVD_SIZE_BYTE {size_symbol}/8", file=file)
            print(f"#if MIPP_{isa_name_upper}_RVD_SIZE_BYTE == 0", file=file)
            print(f"\t#error \"MIPP_{isa_name_upper}_RVD_SIZE_BYTE can't be null\"", file=file)
            print(f"#endif", file=file)
        else:
            # Fixed VLA size (e.g. SVE size as int)
            print(f"#define MIPP_{isa_name_upper}_RVD_SIZE_BYTE {int(vla_size / 8)}", file=file)
        
        # Positive lmuls
        for lmul in [x for x in isa.get("hw_lmul", [1]) if x > 0]:
            lsuffix_upper = "M" + str(lmul)
            coeff = "*" + str(lmul) if lmul > 1 else ""
            for dt in isa["datatypes"]:
                n_bits = datatypes[dt]["n_bits"]
                if vla_size is not None and not isinstance(vla_size, str):
                    type_size = int(vla_size / n_bits) if lmul == 1 else int(vla_size / n_bits * lmul)
                else:
                    type_size = f"{size_symbol}/{n_bits}{coeff}"
                print(j2_template.render(
                    vla_size=size_symbol,
                    n_bits=n_bits,
                    type_size=type_size,
                    type_category_upper=datatypes[dt]["category"].upper(),
                    lsuffix_upper=lsuffix_upper
                ), file=file)

        # Negative lmuls (ldivs)
        for ldiv in [abs(x) for x in isa.get("hw_lmul", []) if x < 0]:
            lsuffix_upper = "D" + str(ldiv)
            for dt in isa["datatypes"]:
                n_bits = datatypes[dt]["n_bits"]
                if vla_size is not None and not isinstance(vla_size, str):
                    type_size = int(vla_size / (n_bits * ldiv))
                else:
                    type_size = f"{size_symbol}/{n_bits}/{ldiv}"
                print(j2_template.render(
                    vla_size=size_symbol,
                    n_bits=n_bits,
                    type_size=type_size,
                    type_category_upper=datatypes[dt]["category"].upper(),
                    lsuffix_upper=lsuffix_upper
                ), file=file)
        return

    """
    Writes the number of elements in the SIMD 
    register for each supported datatype for a given ISA.
    Also writes the size of the SIMD register in bits and bytes.
    """
    print("#define MIPP_" + isa["name"].upper() + "_RVD_SIZE_BIT " + str(isa["size"]), file=file)

    if isinstance(isa["size"], str):
        print("#if MIPP_" + isa["name"].upper() + "_RVD_SIZE_BIT == 0", file=file)
        print("\t#error \"MIPP_" + isa["name"].upper() + "_RVD_SIZE_BIT can't be null\"", file=file)
        print("#endif", file=file)

    if isinstance(isa["size"], str):
        print("#define MIPP_" + isa["name"].upper() + "_RVD_SIZE_BYTE " + isa["size"] + "/8", file=file)
    else:
        print("#define MIPP_" + isa["name"].upper() + "_RVD_SIZE_BYTE " + str(int(isa["size"] / 8)), file=file)

    if isinstance(isa["size"], str):
        print("#if MIPP_" + isa["name"].upper() + "_RVD_SIZE_BYTE == 0", file=file)
        print("\t#error \"MIPP_" + isa["name"].upper() + "_RVD_SIZE_BYTE can't be null\"", file=file)
        print("#endif", file=file)

    template1 = """#define MIPP_{{isa_name_upper}}_N_{{type_category_upper}}{{n_bits}}{{lmul_suffix}} {{n_elmts}}{{coeff}}"""
    template2 = """#define MIPP_{{isa_name_upper}}_N_{{type_category_upper}}{{n_bits}}{{lmul_suffix}} {{n_elmts}}{{coeff}}
#if MIPP_{{isa_name_upper}}_N_{{type_category_upper}}{{n_bits}} == 0
    #error "MIPP_{{isa_name_upper}}_N_{{type_category_upper}}{{n_bits}} can't be null\"
#endif"""

    if isinstance(isa["size"], str):
        j2_template = Template(template2, undefined=StrictUndefined)
    else:
        j2_template = Template(template1, undefined=StrictUndefined)

    for lmul in [0] + all_lmul: # 0 to generate size w/o lmul suffix
        lmul_suffix = "_M" + str(lmul) if lmul >= 1 else ""
        coeff = "*" + str(lmul) if lmul > 1 else ""
        for dt in isa["datatypes"]:
            if isinstance(isa["size"], str):
                n_elmts = isa["size"] + "/" + str(datatypes[dt]["n_bits"])
            else:
                n_elmts = int(isa["size"] / datatypes[dt]["n_bits"])
            print(
                j2_template.render(
                    isa_name_upper=isa["name"].upper(),
                    type_category_upper=datatypes[dt]["category"].upper(),
                    n_bits=datatypes[dt]["n_bits"],
                    n_elmts=n_elmts,
                    lmul_suffix=lmul_suffix,
                    coeff=coeff
                ),
                file=file,
            )

def gen_c_structures(isa, file, is_scalar=False, vla_size=None):
    if "vla" in isa:
        vla_config = isa["vla"]
        size_symbol = str(vla_size) if vla_size is not None else vla_config["size_symbol"]
        
        # 1. Vector typedefs
        j2_vector_typedef = Template(vla_config["vector_typedef_template"], undefined=StrictUndefined)
        # Positive lmuls
        for lmul in [x for x in isa.get("hw_lmul", [1]) if x > 0]:
            lsuffix_mipp = "m" + str(lmul)
            lmul_expr = "*" + str(lmul) if lmul > 1 else ""
            for dt in isa["datatypes"]:
                guard = isa["datatypes"][dt].get("if", None)
                if guard:
                    print(f"#if {guard}", file=file)
                print(j2_vector_typedef.render(
                    isa_datatype=isa["datatypes"][dt],
                    vla_size=size_symbol,
                    lsuffix_mipp=lsuffix_mipp,
                    lmul_expr=lmul_expr
                ), file=file)
                if guard:
                    print(f"#endif", file=file)
                    
        # Negative lmuls (ldivs)
        for ldiv in [abs(x) for x in isa.get("hw_lmul", []) if x < 0]:
            lsuffix_mipp = "d" + str(ldiv)
            lmul_expr = "/" + str(ldiv)
            for dt in isa["datatypes"]:
                if "if_lmul" in isa["datatypes"][dt] and str(-ldiv) in isa["datatypes"][dt]["if_lmul"]:
                    guard = isa["datatypes"][dt]["if_lmul"][str(-ldiv)]
                else:
                    guard = isa["datatypes"][dt].get("if", None)
                if guard == "0":
                    continue
                if guard:
                    print(f"#if {guard}", file=file)
                print(j2_vector_typedef.render(
                    isa_datatype=isa["datatypes"][dt],
                    vla_size=size_symbol,
                    lsuffix_mipp=lsuffix_mipp,
                    lmul_expr=lmul_expr
                ), file=file)
                if guard:
                    print(f"#endif", file=file)

        # 2. Mask typedefs
        j2_mask_typedef = Template(vla_config["mask_typedef_template"], undefined=StrictUndefined)
        # Positive lmuls
        for lmul in [x for x in isa.get("hw_lmul", [1]) if x > 0]:
            lsuffix_mipp = "m" + str(lmul)
            lmul_expr = "*" + str(lmul) if lmul > 1 else ""
            for dt in isa["datatypes"]:
                guard = isa["datatypes"][dt].get("if", None)
                if guard:
                    print(f"#if {guard}", file=file)
                print(j2_mask_typedef.render(
                    isa_datatype=isa["datatypes"][dt],
                    vla_size=size_symbol,
                    lsuffix_mipp=lsuffix_mipp,
                    lmul_expr=lmul_expr,
                    n_bits=datatypes[dt]["n_bits"]
                ), file=file)
                if guard:
                    print(f"#endif", file=file)
                    
        # Negative lmuls (ldivs)
        for ldiv in [abs(x) for x in isa.get("hw_lmul", []) if x < 0]:
            lsuffix_mipp = "d" + str(ldiv)
            lmul_expr = "/" + str(ldiv)
            for dt in isa["datatypes"]:
                if "if_lmul" in isa["datatypes"][dt] and str(-ldiv) in isa["datatypes"][dt]["if_lmul"]:
                    guard = isa["datatypes"][dt]["if_lmul"][str(-ldiv)]
                else:
                    guard = isa["datatypes"][dt].get("if", None)
                if guard == "0":
                    continue
                if guard:
                    print(f"#if {guard}", file=file)
                print(j2_mask_typedef.render(
                    isa_datatype=isa["datatypes"][dt],
                    vla_size=size_symbol,
                    lsuffix_mipp=lsuffix_mipp,
                    lmul_expr=lmul_expr,
                    n_bits=datatypes[dt]["n_bits"]
                ), file=file)
                if guard:
                    print(f"#endif", file=file)

        # 3. Rvd structs
        j2_rvd_struct = Template(vla_config["rvd_struct_template"], undefined=StrictUndefined)
        # Positive lmuls
        for lmul in [x for x in isa.get("hw_lmul", [1]) if x > 0]:
            lsuffix_mipp = "m" + str(lmul)
            for dt in isa["datatypes"]:
                guard = isa["datatypes"][dt].get("if", None)
                if guard:
                    print(f"#if {guard}", file=file)
                print(j2_rvd_struct.render(
                    isa=isa,
                    datatype=datatypes[dt],
                    isa_datatype=isa["datatypes"][dt],
                    vla_size=size_symbol,
                    lsuffix_mipp=lsuffix_mipp
                ), file=file)
                if guard:
                    print(f"#else", file=file)
                    print(f"	#include \"../scalar/scalar_common.h\"", file=file)
                    print(f"	typedef rvd_scalar_{datatypes[dt]['category']}{datatypes[dt]['n_bits']}_t rvd_{isa['name']}_{datatypes[dt]['category']}{datatypes[dt]['n_bits']}_m{lmul}_t;", file=file)
                    print(f"#endif", file=file)
                    
        # Negative lmuls (ldivs)
        for ldiv in [abs(x) for x in isa.get("hw_lmul", []) if x < 0]:
            lsuffix_mipp = "d" + str(ldiv)
            for dt in isa["datatypes"]:
                if "if_lmul" in isa["datatypes"][dt] and str(-ldiv) in isa["datatypes"][dt]["if_lmul"]:
                    guard = isa["datatypes"][dt]["if_lmul"][str(-ldiv)]
                else:
                    guard = isa["datatypes"][dt].get("if", None)
                if guard == "0":
                    print(f"#include \"../scalar/scalar_common.h\"", file=file)
                    print(f"typedef rvd_scalar_{datatypes[dt]['category']}{datatypes[dt]['n_bits']}_t rvd_{isa['name']}_{datatypes[dt]['category']}{datatypes[dt]['n_bits']}_d{ldiv}_t;", file=file)
                else:
                    if guard:
                        print(f"#if {guard}", file=file)
                    print(j2_rvd_struct.render(
                        isa=isa,
                        datatype=datatypes[dt],
                        isa_datatype=isa["datatypes"][dt],
                        vla_size=size_symbol,
                        lsuffix_mipp=lsuffix_mipp
                    ), file=file)
                    if guard:
                        print(f"#else", file=file)
                        print(f"	#include \"../scalar/scalar_common.h\"", file=file)
                        print(f"	typedef rvd_scalar_{datatypes[dt]['category']}{datatypes[dt]['n_bits']}_t rvd_{isa['name']}_{datatypes[dt]['category']}{datatypes[dt]['n_bits']}_d{ldiv}_t;", file=file)
                        print(f"#endif", file=file)

        # 4. Rvm structs
        j2_rvm_struct = Template(vla_config["rvm_struct_template"], undefined=StrictUndefined)
        # Positive lmuls
        for lmul in [x for x in isa.get("hw_lmul", [1]) if x > 0]:
            lsuffix_mipp = "m" + str(lmul)
            for dt in isa["datatypes"]:
                guard = isa["datatypes"][dt].get("if", None)
                if guard:
                    print(f"#if {guard}", file=file)
                print(j2_rvm_struct.render(
                    isa=isa,
                    datatype=datatypes[dt],
                    isa_datatype=isa["datatypes"][dt],
                    vla_size=size_symbol,
                    lsuffix_mipp=lsuffix_mipp
                ), file=file)
                if guard:
                    print(f"#else", file=file)
                    print(f"	typedef rvm_scalar_{datatypes[dt]['category']}{datatypes[dt]['n_bits']}_t rvm_{isa['name']}_{datatypes[dt]['category']}{datatypes[dt]['n_bits']}_m{lmul}_t;", file=file)
                    print(f"#endif", file=file)
                    
        # Negative lmuls (ldivs)
        for ldiv in [abs(x) for x in isa.get("hw_lmul", []) if x < 0]:
            lsuffix_mipp = "d" + str(ldiv)
            for dt in isa["datatypes"]:
                if "if_lmul" in isa["datatypes"][dt] and str(-ldiv) in isa["datatypes"][dt]["if_lmul"]:
                    guard = isa["datatypes"][dt]["if_lmul"][str(-ldiv)]
                else:
                    guard = isa["datatypes"][dt].get("if", None)
                if guard == "0":
                    print(f"typedef rvm_scalar_{datatypes[dt]['category']}{datatypes[dt]['n_bits']}_t rvm_{isa['name']}_{datatypes[dt]['category']}{datatypes[dt]['n_bits']}_d{ldiv}_t;", file=file)
                else:
                    if guard:
                        print(f"#if {guard}", file=file)
                    print(j2_rvm_struct.render(
                        isa=isa,
                        datatype=datatypes[dt],
                        isa_datatype=isa["datatypes"][dt],
                        vla_size=size_symbol,
                        lsuffix_mipp=lsuffix_mipp
                    ), file=file)
                    if guard:
                        print(f"#else", file=file)
                        print(f"	typedef rvm_scalar_{datatypes[dt]['category']}{datatypes[dt]['n_bits']}_t rvm_{isa['name']}_{datatypes[dt]['category']}{datatypes[dt]['n_bits']}_d{ldiv}_t;", file=file)
                        print(f"#endif", file=file)

        # 5. Type Aliases for m1 / standard types
        template_m1_alias = """typedef rvd_{{ isa.name }}_{{ datatype.category }}{{ datatype.n_bits }}_m1_t rvd_{{ isa.name }}_{{ datatype.category }}{{ datatype.n_bits }}_t;"""
        if "{{lsuffix_mipp}}" in vla_config["rvd_struct_template"]:
            j2_rvd_m1 = Template(template_m1_alias, undefined=StrictUndefined)
            j2_rvm_m1 = Template("""typedef rvm_{{ isa.name }}_{{ datatype.category }}{{ datatype.n_bits }}_m1_t rvm_{{ isa.name }}_{{ datatype.category }}{{ datatype.n_bits }}_t;""", undefined=StrictUndefined)
            for dt in isa["datatypes"]:
                guard = isa["datatypes"][dt].get("if", None)
                if guard:
                    print(f"#if {guard}", file=file)
                print(j2_rvd_m1.render(isa=isa, datatype=datatypes[dt]), file=file)
                if guard:
                    print(f"#else", file=file)
                    print(f"	typedef rvd_scalar_{datatypes[dt]['category']}{datatypes[dt]['n_bits']}_t rvd_{isa['name']}_{datatypes[dt]['category']}{datatypes[dt]['n_bits']}_t;", file=file)
                    print(f"#endif", file=file)
            for dt in isa["datatypes"]:
                guard = isa["datatypes"][dt].get("if", None)
                if guard:
                    print(f"#if {guard}", file=file)
                print(j2_rvm_m1.render(isa=isa, datatype=datatypes[dt]), file=file)
                if guard:
                    print(f"#else", file=file)
                    print(f"	typedef rvm_scalar_{datatypes[dt]['category']}{datatypes[dt]['n_bits']}_t rvm_{isa['name']}_{datatypes[dt]['category']}{datatypes[dt]['n_bits']}_t;", file=file)
                    print(f"#endif", file=file)
        return

    """
    Writes the C structures corresponding to the supported datatypes for a given ISA, for both vector and mask types.
    """
    if is_scalar:
        template = """typedef struct { {{ isa_datatype.reg }} r[MIPP_{{isa_name_upper}}_N_{{type_category_upper}}{{datatype.n_bits}}]; } rvd_{{ isa.name }}_{{ datatype.category }}{{ datatype.n_bits }}_t;"""
    else:
        template = """typedef struct { {{ isa_datatype.reg }} r; } rvd_{{ isa.name }}_{{ datatype.category }}{{ datatype.n_bits }}_t;"""
    j2_template = Template(template, undefined=StrictUndefined)

    template_alt = """
#if {{ isa_datatype.if }}
	typedef struct { {{ isa_datatype.reg }} r; } rvd_{{ isa.name }}_{{ datatype.category }}{{ datatype.n_bits }}_t;
#else
	#include "../scalar/scalar_common.h"
	typedef  rvd_scalar_{{ datatype.category }}{{ datatype.n_bits }}_t rvd_{{ isa.name }}_{{ datatype.category }}{{ datatype.n_bits }}_t;
#endif // {{ isa_datatype.if }}
"""
    j2_template_alt = Template(template_alt, undefined=StrictUndefined)

    for dt in isa["datatypes"]:
        if "if" not in isa["datatypes"][dt]:
            print(
                j2_template.render(
                    isa=isa,
                    isa_datatype=isa["datatypes"][dt],
                    datatype=datatypes[dt],
                    isa_name_upper=isa["name"].upper(),
                    type_category_upper=datatypes[dt]["category"].upper(),
                    ),
                    file=file)
        else:
            print(j2_template_alt.render(isa=isa, isa_datatype=isa["datatypes"][dt], datatype=datatypes[dt]), file=file)

    if is_scalar:
        template = """typedef struct { {{ isa_datatype.msk }} m[MIPP_{{isa_name_upper}}_N_{{type_category_upper}}{{datatype.n_bits}}]; } rvm_{{ isa.name }}_{{ datatype.category }}{{ datatype.n_bits }}_t;"""
    else:
        template = """typedef struct { {{ isa_datatype.msk }} m; } rvm_{{ isa.name }}_{{ datatype.category }}{{ datatype.n_bits }}_t;"""
    j2_template = Template(template, undefined=StrictUndefined)

    for dt in isa["datatypes"]:
        print(
            j2_template.render(
                isa=isa,
                isa_datatype=isa["datatypes"][dt],
                datatype=datatypes[dt],
                isa_name_upper=isa["name"].upper(),
                type_category_upper=datatypes[dt]["category"].upper(),
            ),
            file=file)

    hw_lmuls = isa.get("hw_lmul", [1])
    if len(hw_lmuls) <= 1:
        template = """typedef rvd_{{ isa.name }}_{{ datatype.category }}{{ datatype.n_bits }}_t rvd_{{ isa.name }}_{{ datatype.category }}{{ datatype.n_bits }}_m1_t;"""
        j2_template = Template(template, undefined=StrictUndefined)

        for dt in isa["datatypes"]:
            print(j2_template.render(isa=isa, datatype=datatypes[dt]), file=file)

        template = """typedef rvm_{{ isa.name }}_{{ datatype.category }}{{ datatype.n_bits }}_t rvm_{{ isa.name }}_{{ datatype.category }}{{ datatype.n_bits }}_m1_t;"""
        j2_template = Template(template, undefined=StrictUndefined)

        for dt in isa["datatypes"]:
            print(j2_template.render(isa=isa, datatype=datatypes[dt]), file=file)
        for lmul in all_lmul[1:]:
            lmul_2 = int(lmul / 2)
            template = """typedef struct { rvd_{{isa.name}}_{{ datatype.category }}{{ datatype.n_bits }}_m{{ lmul_2 }}_t r1, r2; } rvd_{{ isa.name }}_{{ datatype.category }}{{ datatype.n_bits }}_m{{ lmul }}_t;"""
            j2_template = Template(template, undefined=StrictUndefined)
            for dt in isa["datatypes"]:
                print(j2_template.render(isa=isa, datatype=datatypes[dt], lmul=str(lmul), lmul_2=str(lmul_2)), file=file)
        for lmul in all_lmul[1:]:
            lmul_2 = int(lmul / 2)
            template = """typedef struct { rvm_{{isa.name}}_{{ datatype.category }}{{ datatype.n_bits }}_m{{ lmul_2 }}_t m1, m2; } rvm_{{ isa.name }}_{{ datatype.category }}{{ datatype.n_bits }}_m{{ lmul }}_t;"""
            j2_template = Template(template, undefined=StrictUndefined)
            for dt in isa["datatypes"]:
                print(j2_template.render(isa=isa, datatype=datatypes[dt], lmul=str(lmul), lmul_2=str(lmul_2)), file=file)
    
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
    # Validate sw_ldiv_type and negative lmuls/ldivs combo
    sw_ldiv_type = isa.get("sw_ldiv_type", "native")
    hw_lmuls = isa.get("hw_lmul", [1])
    sw_lmuls = isa.get("sw_lmul", [])
    all_ldivs = [int(x) for x in (hw_lmuls + sw_lmuls) if int(x) < 0]
    if sw_ldiv_type == "sub_isa":
        if "sub_isa" not in isa or not isa["sub_isa"]:
            print(f"Error: ISA '{isa['name']}' has sw_ldiv_type='sub_isa' but is missing the 'sub_isa' field defining the underlying sub-architecture.", file=sys.stderr)
            sys.exit(1)
        for ldiv in all_ldivs:
            if ldiv != -2:
                print(f"Error: ISA '{isa['name']}' has sw_ldiv_type='sub_isa' but specifies unsupported ldiv factor '{ldiv}'. Only ldiv = -2 is supported with sub_isa.", file=sys.stderr)
                sys.exit(1)

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

    # 2. Emit the defines and structures
    gen_c_defines(isa, file_common)
    gen_c_structures(isa, file_common, is_scalar=(isa["name"] == "scalar"))

    print(f"#endif /* MY_INTRINSICS_PLUS_PLUS_IMPL_GEN_{isa['name'].upper()}_H_ */", file=file_common)

    # 3. Register and resolve hardware candidates (HW LMUL)
    copy_interfaces = copy.deepcopy(interfaces)
    hw_lmuls = isa.get("hw_lmul", [1])
    
    # Positive / non-negative hw_lmul (0 is added explicitly; negative values like -2 are processed separately)
    hw_lmuls_pos = sorted(list(set([0] + [int(x) for x in hw_lmuls if int(x) >= 0])))
    for lmul in hw_lmuls_pos:
        resolved_isa = resolve_lmul_in_isa(isa, str(lmul))
        resolved_isa["candidates"] = []
        register_candidates(resolved_isa, copy_interfaces, native_implems, lmul=lmul)
        register_candidates(resolved_isa, copy_interfaces, emu_implems, lmul=lmul)
        register_candidates(resolved_isa, copy_interfaces, implems_generic_emu, cand_type="generic_emu", lmul=lmul)
        register_candidates(resolved_isa, copy_interfaces, implems_mask_generic_emu, cand_type="generic_emu", lmul=lmul)
        
        # Resolution and emission by the generic solver
        resolve_and_emit_missing_functions(resolved_isa, include_manager, copy_interfaces, lmul=lmul, emit_separators=(lmul != 0))

    # Negative hw_lmul values (fractional LMUL/ldiv like -2, -4, -8, if present)
    hw_lmuls_neg = sorted([int(x) for x in hw_lmuls if int(x) < 0])
    for lmul_neg in hw_lmuls_neg:
        resolved_isa = resolve_lmul_in_isa(isa, str(lmul_neg))
        resolved_isa["candidates"] = []
        register_candidates(resolved_isa, copy_interfaces, native_implems, lmul=lmul_neg)
        register_candidates(resolved_isa, copy_interfaces, emu_implems, lmul=lmul_neg)
        register_candidates(resolved_isa, copy_interfaces, implems_generic_emu, cand_type="generic_emu", lmul=lmul_neg)
        register_candidates(resolved_isa, copy_interfaces, implems_mask_generic_emu, cand_type="generic_emu", lmul=lmul_neg)

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
    include_manager.create_glue_file(isa["name"], f"../include/{isa['name']}/mipp_impl_{isa['name']}_gen.h")
    include_manager.close_layer_fds(isa["name"])
