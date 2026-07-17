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
    gen_ldiv_defines_avx,
    gen_ldiv_structs_avx,
)
from codegen.candidate_resolver import resolve_and_emit_missing_functions
from codegen.lmul_orchestrator import gen_c_lmul, gen_c_ldiv


def gen_c_defines(isa, file):
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

def gen_c_structures(isa, file, is_scalar=False):
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
    
    if isa["name"] == "avx512": 
        sub_isa = load_isa_config("avx")[0]
        if sub_isa:
            gen_ldiv_structs_avx(isa, sub_isa, file)
            gen_ldiv_defines_avx(isa, sub_isa, file)
    if isa["name"] == "avx": 
        sub_isa = load_isa_config("sse")[0]
        if sub_isa:
            gen_ldiv_structs_avx(isa, sub_isa, file)
            gen_ldiv_defines_avx(isa, sub_isa, file)

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

def gen_c_defines_rvv_ls(file, isa_name, rvv_size, rvv_isa):
    print("#define MIPP_" + isa_name.upper() + "_RVD_SIZE_BIT " + str(rvv_size), file=file)
    print("#define MIPP_" + isa_name.upper() + "_RVD_SIZE_BYTE " + str(rvv_size + "/ 8"), file=file)
    template = """#define MIPP_RVV_N_{{type_category_upper}}{{n_bits}} {{type_size}}"""
    j2_template = Template(template, undefined=StrictUndefined)
    for dt in rvv_isa["datatypes"]:
        n_bits=datatypes[dt]["n_bits"]
        print(j2_template.render(rvv_size=rvv_size, n_bits=n_bits, type_size = str(f'{rvv_size}/{n_bits}'), type_category_upper=datatypes[dt]["category"].upper()), file=file)
    
    for lmul in all_lmul:
        for dt in rvv_isa["datatypes"]:
            n_bits=datatypes[dt]["n_bits"]
            type_size = f'{rvv_size}/{n_bits}*{lmul}'
            template = """#define MIPP_RVV_N_{{type_category_upper}}{{n_bits}}_M{{lmul}} {{type_size}}"""
            j2_template = Template(template, undefined=StrictUndefined)
            print(j2_template.render(rvv_size=rvv_size, n_bits=n_bits, type_size = type_size, type_category_upper=datatypes[dt]["category"].upper(), lmul=lmul), file=file)
    ldiv_options = [abs(x) for x in rvv_isa.get("hw_lmul", []) if x < 0]
    for ldiv in ldiv_options:
        for dt in rvv_isa["datatypes"]:
            n_bits=datatypes[dt]["n_bits"]
            type_size = f'{rvv_size}/{n_bits}/{ldiv}'
            template = """#define MIPP_RVV_N_{{type_category_upper}}{{n_bits}}_D{{ldiv}} {{type_size}}"""
            j2_template = Template(template, undefined=StrictUndefined)
            print(j2_template.render(rvv_size=rvv_size, n_bits=n_bits, type_size = type_size, type_category_upper=datatypes[dt]["category"].upper(), ldiv=ldiv), file=file)

def gen_c_structures_rvv_ls(file, rvv_size, rvv_isa):
    #rvd type generation
    template = """typedef {{ isa_datatype.reg }} fixed_{lsuffix_mipp}_{{isa_datatype.to_ptr}} __attribute__((riscv_rvv_vector_bits({{ rvv_size }}{lmul})));"""
    j2_template = Template(template, undefined=StrictUndefined)
    for lmul in all_lmul:
        for dt in rvv_isa["datatypes"]:
            guard = rvv_isa["datatypes"][dt].get("if", None)
            if guard:
                print(f"#if {guard}", file=file)
            template_rendered = j2_template.render(isa_datatype=rvv_isa["datatypes"][dt],rvv_size=rvv_size)
            template_rendered = template_rendered.format(lsuffix = "m" + str(lmul), lsuffix_mipp = "m" + str(lmul), lmul = "*" + str(lmul)) # lmul hack ;)
            print(template_rendered, file=file)
            if guard:
                print(f"#endif", file=file)

    ldiv_options = [abs(x) for x in rvv_isa.get("hw_lmul", []) if x < 0]
    for ldiv in ldiv_options:
        for dt in rvv_isa["datatypes"]:
            if "if_lmul" in rvv_isa["datatypes"][dt] and str(-ldiv) in rvv_isa["datatypes"][dt]["if_lmul"]:
                guard = rvv_isa["datatypes"][dt]["if_lmul"][str(-ldiv)]
            else:
                guard = rvv_isa["datatypes"][dt].get("if", None)
            if guard == "0":
                continue
            if guard:
                print(f"#if {guard}", file=file)
            template_rendered = j2_template.render(isa_datatype=rvv_isa["datatypes"][dt],rvv_size=rvv_size)
            template_rendered = template_rendered.format(lsuffix = "mf" + str(ldiv), lmul = "/" + str(ldiv), lsuffix_mipp = "d" + str(ldiv)) # lmul hack ;)
            print(template_rendered, file=file)
            if guard:
                print(f"#endif", file=file)
     
    #rvm type generation
    template = """typedef {{isa_datatype.msk}} fixed_{lsuffix_mipp}_bool{n_bits}_t __attribute__((riscv_rvv_vector_bits({{ rvv_size }}{lmul}/(8*sizeof({{isa_datatype.to_ptr}})))));"""
    j2_template = Template(template, undefined=StrictUndefined)
    dt_list = [uint64, uint32, uint16, uint8]
    for lmul in all_lmul:
        for dt in dt_list:
            guard = rvv_isa["datatypes"][dt].get("if", None)
            if guard:
                print(f"#if {guard}", file=file)
            n_bits = datatypes[dt]["n_bits"]
            nb_elem = f'{rvv_size} / {n_bits}'  	
            tmp = j2_template.render(rvv_size=rvv_size, isa_datatype=rvv_isa["datatypes"][dt], nb_elem=nb_elem)  
            tmp = tmp.format(lsuffix = "m" + str(lmul), 
                             lsuffix_mipp = "m" + str(lmul), 
                             lmul = "*" + str(lmul), 
                             eew_emul = str(int(n_bits/(lmul))), 
                             n_bits = str(n_bits))
            print(tmp, file=file)
            if guard:
                print(f"#endif", file=file)

    ldiv_options = [abs(x) for x in rvv_isa.get("hw_lmul", []) if x < 0]
    for ldiv in ldiv_options:
        for dt in dt_list:
            if "if_lmul" in rvv_isa["datatypes"][dt] and str(-ldiv) in rvv_isa["datatypes"][dt]["if_lmul"]:
                guard = rvv_isa["datatypes"][dt]["if_lmul"][str(-ldiv)]
            else:
                guard = rvv_isa["datatypes"][dt].get("if", None)
            if guard == "0":
                continue
            if guard:
                print(f"#if {guard}", file=file)
            n_bits = datatypes[dt]["n_bits"]
            nb_elem = f'{rvv_size} / {n_bits}'  	
            tmp = j2_template.render(rvv_size=rvv_size, isa_datatype=rvv_isa["datatypes"][dt], nb_elem=nb_elem)  
            tmp = tmp.format(lsuffix = "d" + str(ldiv), 
                             lsuffix_mipp = "d" + str(ldiv),  
                             lmul = "/" + str(ldiv), 
                             eew_emul = str(int(n_bits*(ldiv))), 
                             n_bits = str(n_bits)) 
            print(tmp, file=file)
            if guard:
                print(f"#endif", file=file)

    #rvd struct generation
    template = """typedef struct { fixed_{lsuffix}_{{isa_datatype.to_ptr }} r; } rvd_{{ isa.name }}_{{ datatype.category }}{{ datatype.n_bits }}_{lsuffix}_t;"""
    for lmul in all_lmul:
        for dt in rvv_isa["datatypes"]:
            n_bits = datatypes[dt]["n_bits"]
            nb_elem = f'{rvv_size} / {n_bits} * {lmul}'
            tmp = template.replace("{lsuffix}", "m" + str(lmul))
            j2_template = Template(tmp, undefined=StrictUndefined)
            guard = rvv_isa["datatypes"][dt].get("if", None)
            if guard:
                print(f"#if {guard}", file=file)
            print(j2_template.render(isa=rvv_isa,rvv_size=rvv_size,isa_datatype=rvv_isa["datatypes"][dt], datatype=datatypes[dt], lmul=lmul), file=file)
            if guard:
                print(f"#else", file=file)
                print(f"	#include \"../scalar/scalar_common.h\"", file=file)
                print(f"	typedef rvd_scalar_{datatypes[dt]['category']}{datatypes[dt]['n_bits']}_t rvd_rvv_{datatypes[dt]['category']}{datatypes[dt]['n_bits']}_m{lmul}_t;", file=file)
                print(f"#endif", file=file)
    
    ldiv_options = [abs(x) for x in rvv_isa.get("hw_lmul", []) if x < 0]
    for ldiv in ldiv_options:
        for dt in rvv_isa["datatypes"]:
            n_bits = datatypes[dt]["n_bits"]
            nb_elem = f'{rvv_size} / {n_bits} / {ldiv}'
            tmp = template.replace("{lsuffix}", "d" + str(ldiv))
            j2_template = Template(tmp, undefined=StrictUndefined)
            if "if_lmul" in rvv_isa["datatypes"][dt] and str(-ldiv) in rvv_isa["datatypes"][dt]["if_lmul"]:
                guard = rvv_isa["datatypes"][dt]["if_lmul"][str(-ldiv)]
            else:
                guard = rvv_isa["datatypes"][dt].get("if", None)
            if guard == "0":
                # Native type does not exist; emit scalar alias directly
                print(f"#include \"../scalar/scalar_common.h\"", file=file)
                print(f"typedef rvd_scalar_{datatypes[dt]['category']}{datatypes[dt]['n_bits']}_t rvd_rvv_{datatypes[dt]['category']}{datatypes[dt]['n_bits']}_d{ldiv}_t;", file=file)
            else:
                if guard:
                    print(f"#if {guard}", file=file)
                print(j2_template.render(isa=rvv_isa,rvv_size=rvv_size,isa_datatype=rvv_isa["datatypes"][dt], datatype=datatypes[dt], lmul=ldiv), file=file)
                if guard:
                    print(f"#else", file=file)
                    print(f"	#include \"../scalar/scalar_common.h\"", file=file)
                    print(f"	typedef rvd_scalar_{datatypes[dt]['category']}{datatypes[dt]['n_bits']}_t rvd_rvv_{datatypes[dt]['category']}{datatypes[dt]['n_bits']}_d{ldiv}_t;", file=file)
                    print(f"#endif", file=file)

    #typedef of rvd m1 to no suffix
    template = """typedef rvd_{{ isa.name }}_{{ datatype.category }}{{ datatype.n_bits }}_m1_t rvd_{{ isa.name }}_{{ datatype.category }}{{ datatype.n_bits }}_t;"""
    for dt in rvv_isa["datatypes"]:
        n_bits = datatypes[dt]["n_bits"]
        nb_elem = f'{rvv_size} / {n_bits}'
        tmp = template.replace("_m{lmul}", "")
        j2_template = Template(tmp, undefined=StrictUndefined)
        guard = rvv_isa["datatypes"][dt].get("if", None)
        if guard:
            print(f"#if {guard}", file=file)
        print(j2_template.render(isa=rvv_isa,rvv_size=rvv_size,isa_datatype=rvv_isa["datatypes"][dt], datatype=datatypes[dt], lmul=""), file=file)
        if guard:
            print(f"#else", file=file)
            print(f"	#include \"../scalar/scalar_common.h\"", file=file)
            print(f"	typedef rvd_scalar_{datatypes[dt]['category']}{datatypes[dt]['n_bits']}_t rvd_rvv_{datatypes[dt]['category']}{datatypes[dt]['n_bits']}_t;", file=file)
            print(f"#endif", file=file)
    
    #rvm struct generation
    template = """typedef struct { fixed_{lsuffix}_bool{n_bits}_t m; } rvm_{{ isa.name }}_{{ datatype.category }}{{ datatype.n_bits }}_{lsuffix}_t;"""
    j2_template = Template(template, undefined=StrictUndefined)
       
    for lmul in all_lmul:
        for dt in rvv_isa["datatypes"]:
            n_bits = datatypes[dt]["n_bits"]
            nb_elem = f'{rvv_size} / {n_bits} * {lmul}'
            tmp = template.replace("{lsuffix}", "m" + str(lmul))
            tmp = tmp.replace("{n_bits}", str(n_bits))
            j2_template = Template(tmp, undefined=StrictUndefined)
            guard = rvv_isa["datatypes"][dt].get("if", None)
            if guard:
                print(f"#if {guard}", file=file)
            print(j2_template.render(isa=rvv_isa,rvv_size=rvv_size,isa_datatype=rvv_isa["datatypes"][dt], datatype=datatypes[dt], lmul=lmul), file=file)
            if guard:
                print(f"#else", file=file)
                print(f"	typedef rvm_scalar_{datatypes[dt]['category']}{datatypes[dt]['n_bits']}_t rvm_rvv_{datatypes[dt]['category']}{datatypes[dt]['n_bits']}_m{lmul}_t;", file=file)
                print(f"#endif", file=file)

    ldiv_options = [abs(x) for x in rvv_isa.get("hw_lmul", []) if x < 0]
    for ldiv in ldiv_options:
        for dt in rvv_isa["datatypes"]:
            n_bits = datatypes[dt]["n_bits"]
            nb_elem = f'{rvv_size} / {n_bits} / {ldiv}'
            tmp = template.replace("{lsuffix}", "d" + str(ldiv))
            tmp = tmp.replace("{n_bits}", str(n_bits))
            j2_template = Template(tmp, undefined=StrictUndefined)
            if "if_lmul" in rvv_isa["datatypes"][dt] and str(-ldiv) in rvv_isa["datatypes"][dt]["if_lmul"]:
                guard = rvv_isa["datatypes"][dt]["if_lmul"][str(-ldiv)]
            else:
                guard = rvv_isa["datatypes"][dt].get("if", None)
            if guard == "0":
                # Native mask type does not exist; emit scalar alias directly
                print(f"typedef rvm_scalar_{datatypes[dt]['category']}{datatypes[dt]['n_bits']}_t rvm_rvv_{datatypes[dt]['category']}{datatypes[dt]['n_bits']}_d{ldiv}_t;", file=file)
            else:
                if guard:
                    print(f"#if {guard}", file=file)
                print(j2_template.render(isa=rvv_isa,rvv_size=rvv_size,isa_datatype=rvv_isa["datatypes"][dt], datatype=datatypes[dt], lmul=ldiv), file=file)
                if guard:
                    print(f"#else", file=file)
                    print(f"	typedef rvm_scalar_{datatypes[dt]['category']}{datatypes[dt]['n_bits']}_t rvm_rvv_{datatypes[dt]['category']}{datatypes[dt]['n_bits']}_d{ldiv}_t;", file=file)
                    print(f"#endif", file=file)
    
    template = """typedef rvm_{{ isa.name }}_{{ datatype.category }}{{ datatype.n_bits }}_m1_t rvm_{{ isa.name }}_{{ datatype.category }}{{ datatype.n_bits }}_t;"""
    for dt in rvv_isa["datatypes"]:
        n_bits = datatypes[dt]["n_bits"]
        nb_elem = f'{rvv_size} / {n_bits}'
        tmp = template.replace("_m{lmul}", "")
        j2_template = Template(tmp, undefined=StrictUndefined)
        guard = rvv_isa["datatypes"][dt].get("if", None)
        if guard:
            print(f"#if {guard}", file=file)
        print(j2_template.render(isa=rvv_isa,rvv_size=rvv_size,isa_datatype=rvv_isa["datatypes"][dt], datatype=datatypes[dt], lmul=""), file=file)
        if guard:
            print(f"#else", file=file)
            print(f"	typedef rvm_scalar_{datatypes[dt]['category']}{datatypes[dt]['n_bits']}_t rvm_rvv_{datatypes[dt]['category']}{datatypes[dt]['n_bits']}_t;", file=file)
            print(f"#endif", file=file)

def generate_c_layer(isa, include_manager, native_implems, emu_implems):
    # Pre-process emu_implems to set default type
    for iemu in emu_implems:
        for sub_iemu in emu_implems[iemu]:
            if "type" not in sub_iemu:
                sub_iemu["type"] = "emulated"

    # 1. Émission du header commun propre à l'ISA
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

    # 2. Émission des defines et des structures
    if isa["name"] == "rvv":
        gen_c_defines_rvv_ls(file_common, isa["name"], "__riscv_v_fixed_vlen", isa)
        gen_c_structures_rvv_ls(file_common, "__riscv_v_fixed_vlen", isa)
    else:
        gen_c_defines(isa, file_common)
        gen_c_structures(isa, file_common, is_scalar=(isa["name"] == "scalar"))

    print(f"#endif /* MY_INTRINSICS_PLUS_PLUS_IMPL_GEN_{isa['name'].upper()}_H_ */", file=file_common)

    # 3. Enregistrement et résolution des candidats matériels (HW LMUL)
    copy_interfaces = copy.deepcopy(interfaces)
    hw_lmuls = isa.get("hw_lmul", [1])
    
    # Positive / non-negative hw_lmul (0 is added explicitly; negative values like -2 are processed separately)
    hw_lmuls_pos = sorted(list(set([0] + [int(x) for x in hw_lmuls if int(x) >= 0])))
    for lmul in hw_lmuls_pos:
        resolved_isa = resolve_lmul_in_isa(isa, str(lmul))
        resolved_isa["candidates"] = []
        register_candidates(resolved_isa, copy_interfaces, native_implems, lmul=lmul)
        register_candidates(resolved_isa, copy_interfaces, emu_implems, lmul=lmul)
        if resolved_isa["name"] != "avx512":
            register_candidates(resolved_isa, copy_interfaces, implems_generic_emu, cand_type="generic_emu", lmul=lmul)
        register_candidates(resolved_isa, copy_interfaces, implems_mask_generic_emu, cand_type="generic_emu", lmul=lmul)
        
        # Résolution et émission par le solver générique
        resolve_and_emit_missing_functions(resolved_isa, include_manager, copy_interfaces, lmul=lmul, emit_separators=(lmul != 0))

    # Cas ldiv = -2 pour RVV (s'il est présent)
    if -2 in hw_lmuls or "-2" in hw_lmuls:
        resolved_isa = resolve_lmul_in_isa(isa, "-2")
        resolved_isa["candidates"] = []
        register_candidates(resolved_isa, copy_interfaces, native_implems, lmul=-2)
        register_candidates(resolved_isa, copy_interfaces, emu_implems, lmul=-2)
        if resolved_isa["name"] != "avx512":
            register_candidates(resolved_isa, copy_interfaces, implems_generic_emu, cand_type="generic_emu", lmul=-2)
        register_candidates(resolved_isa, copy_interfaces, implems_mask_generic_emu, cand_type="generic_emu", lmul=-2)
        
        resolve_and_emit_missing_functions(resolved_isa, include_manager, copy_interfaces, lmul=-2, emit_separators=True)

    # 4. Génération des wrappers logiciels (SW LMUL)
    sw_lmuls = isa.get("sw_lmul", [])
    if sw_lmuls:
        # Génération des wrappers logiciels (équivalant à ce que fait gen_c_lmul)
        gen_c_lmul(isa, include_manager, copy_interfaces, sw_lmuls)

    # Generate ldiv wrappers for AVX/AVX512
    if isa["name"] == "avx":
        sub_isa = load_isa_config("sse")[0]
        gen_c_ldiv(isa, sub_isa, include_manager, copy_interfaces)
    elif isa["name"] == "avx512":
        sub_isa = load_isa_config("avx")[0]
        gen_c_ldiv(isa, sub_isa, include_manager, copy_interfaces)

    # 5. Resolve dependencies and create glue file
    include_manager.resolve_all_dependencies(isa["name"], copy_interfaces)
    include_manager.create_glue_file(isa["name"], f"../include/{isa['name']}/mipp_impl_{isa['name']}_gen.h")
    include_manager.close_layer_fds(isa["name"])
