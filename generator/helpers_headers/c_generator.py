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

    if isa["hw_lmul"] == False:
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
        sub_isa = GLOBAL_ISA_REGISTRY.get("avx")
        if sub_isa:
            gen_ldiv_structs_avx(isa, sub_isa, file)
            gen_ldiv_defines_avx(isa, sub_isa, file)
    if isa["name"] == "avx": 
        sub_isa = GLOBAL_ISA_REGISTRY.get("sse")
        if sub_isa:
            gen_ldiv_structs_avx(isa, sub_isa, file)
            gen_ldiv_defines_avx(isa, sub_isa, file)

def gen_c_functions(isa, file, funcs, implems):
    if "candidates" not in isa:
        isa["candidates"] = []
    for f in implems:
        if f in funcs:
            for ff in implems[f]:
                for dt in ff["datatypes"]:
                    isa["candidates"].append({
                        "type": "native_or_emu",
                        "f": f,
                        "ff": ff,
                        "dt": dt,
                        "level": ff.get("level", 1 if ("type" in ff and ff["type"] == "emulated") else 0)
                    })
        else:
            print("Panic: '" + f + "' function does not exist.")
            exit(-1)

def gen_c_generic_functions(isa, file, funcs, implems):
    if "candidates" not in isa:
        isa["candidates"] = []
    for f in implems:
        if f in funcs:
            for ff in implems[f]:
                for dt in ff["datatypes"]:
                    isa["candidates"].append({
                        "type": "generic_emu",
                        "f": f,
                        "ff": ff,
                        "dt": dt,
                        "level": 2
                    })
        else:
            print("Panic: '" + f + "' function does not exist.")
            exit(-1)

def gen_c_missing_functions(isa, file, funcs):
    resolve_and_emit_missing_functions(isa, file, funcs, lmul=0, emit_separators=False)

def gen_c_missing_functions_lmul(isa, file, funcs, lmul):
    resolve_and_emit_missing_functions(isa, file, funcs, lmul=lmul, emit_separators=True)
