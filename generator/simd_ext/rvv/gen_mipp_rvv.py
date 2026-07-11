#!/usr/bin/env python3

from jinja2 import Template, StrictUndefined
import json
import copy
import sys
sys.path.insert(1, '.')

from tools import *
from headers_def import *
from implem_rvv import *
from implem_emu_rvv import *
from generic_emu import *
from c_generator import gen_c_functions_rvv, gen_c_missing_functions_lmul

from include_gen import IncludeManager

def seen_lmul(funcs, f, dt_key, lmul):
    if "implem_status" in funcs[f] :
        if "lmul" in funcs[f]["implem_status"] :
            if (lmul,dt_key) in funcs[f]["implem_status"]["lmul"]:
                return True
    return False

def gen_c_defines_rvv_ls(file, isa_name, rvv_size):
    print("#define MIPP_" + isa_name.upper() + "_RVD_SIZE_BIT " + str(rvv_size), file=file)
    print("#define MIPP_" + isa_name.upper() + "_RVD_SIZE_BYTE " + str(rvv_size + "/ 8"), file=file)
    template = """#define MIPP_RVV_N_{{type_category_upper}}{{n_bits}} {{type_size}}"""
    j2_template = Template(template, undefined=StrictUndefined)
    for dt in isa_rvv["datatypes"]:
        n_bits=datatypes[dt]["n_bits"]
        print(j2_template.render(rvv_size=rvv_size, n_bits=n_bits, type_size = str(f'{rvv_size}/{n_bits}'), type_category_upper=datatypes[dt]["category"].upper()), file=file)
    
    for lmul in all_lmul:
        for dt in isa_rvv["datatypes"]:
            n_bits=datatypes[dt]["n_bits"]
            type_size = f'{rvv_size}/{n_bits}*{lmul}'
            template = """#define MIPP_RVV_N_{{type_category_upper}}{{n_bits}}_M{{lmul}} {{type_size}}"""
            j2_template = Template(template, undefined=StrictUndefined)
            print(j2_template.render(rvv_size=rvv_size, n_bits=n_bits, type_size = type_size, type_category_upper=datatypes[dt]["category"].upper(), lmul=lmul), file=file)
    ldiv = 2
    for dt in isa_rvv["datatypes"]:
        n_bits=datatypes[dt]["n_bits"]
        type_size = f'{rvv_size}/{n_bits}/{ldiv}'
        template = """#define MIPP_RVV_N_{{type_category_upper}}{{n_bits}}_D{{ldiv}} {{type_size}}"""
        j2_template = Template(template, undefined=StrictUndefined)
        print(j2_template.render(rvv_size=rvv_size, n_bits=n_bits, type_size = type_size, type_category_upper=datatypes[dt]["category"].upper(), ldiv=ldiv), file=file)

def gen_c_structures_rvv_ls(file, rvv_size):
    
    #rvd type generation
    template = """typedef {{ isa_datatype.reg }} fixed_{lsuffix_mipp}_{{isa_datatype.to_ptr}} __attribute__((riscv_rvv_vector_bits({{ rvv_size }}{lmul})));"""
    j2_template = Template(template, undefined=StrictUndefined)
    for lmul in all_lmul:
        for dt in isa_rvv["datatypes"]:
            guard = isa_rvv["datatypes"][dt].get("if", None)
            if guard:
                print(f"#if {guard}", file=file)
            template = j2_template.render(isa_datatype=isa_rvv["datatypes"][dt],rvv_size=rvv_size)
            template = template.format(lsuffix = "m" + str(lmul), lsuffix_mipp = "m" + str(lmul), lmul = "*" + str(lmul)) # lmul hack ;)
            print(template, file=file)
            if guard:
                print(f"#endif", file=file)

    ldiv = 2
    for dt in isa_rvv["datatypes"]:
         # if size == 64 _mf2 type not define, use _m1 w smaller vl instead.
        guard = isa_rvv["datatypes"][dt].get("if", None)
        if guard:
            print(f"#if {guard}", file=file)
        if isa_rvv["datatypes"][dt]["width"] == "64":
            template = j2_template.render(isa_datatype=isa_rvv["datatypes"][dt],rvv_size=rvv_size)
            template = template.format(lsuffix = "m1" , lmul = "", lsuffix_mipp = "d2" )
        else :
            template = j2_template.render(isa_datatype=isa_rvv["datatypes"][dt],rvv_size=rvv_size)
            template = template.format(lsuffix = "mf" + str(ldiv), lmul = "/" + str(ldiv), lsuffix_mipp = "d" + str(ldiv)) # lmul hack ;)
        print(template, file=file)
        if guard:
            print(f"#endif", file=file)
     
    #rvm type generation
    template = """typedef {{isa_datatype.msk}} fixed_{lsuffix_mipp}_bool{n_bits}_t __attribute__((riscv_rvv_vector_bits({{ rvv_size }}{lmul}/(8*sizeof({{isa_datatype.to_ptr}})))));"""
    j2_template = Template(template, undefined=StrictUndefined)
    dt_list = [uint64, uint32, uint16, uint8]
    for lmul in all_lmul:
        for dt in dt_list:
            guard = isa_rvv["datatypes"][dt].get("if", None)
            if guard:
                print(f"#if {guard}", file=file)
            n_bits = datatypes[dt]["n_bits"]
            nb_elem = f'{rvv_size} / {n_bits}'  	
            tmp = j2_template.render(rvv_size=rvv_size, isa_datatype=isa_rvv["datatypes"][dt], nb_elem=nb_elem)  
            tmp = tmp.format(lsuffix = "m" + str(lmul), 
                             lsuffix_mipp = "m" + str(lmul), 
                             lmul = "*" + str(lmul), 
                             eew_emul = str(int(n_bits/(lmul))), 
                             n_bits = str(n_bits))
            print(tmp, file=file)
            if guard:
                print(f"#endif", file=file)

    ldiv = 2 
    for dt in dt_list:
        guard = isa_rvv["datatypes"][dt].get("if", None)
        if guard:
            print(f"#if {guard}", file=file)
        if isa_rvv["datatypes"][dt]["width"] == "64":
            n_bits = datatypes[dt]["n_bits"]
            nb_elem = f'{rvv_size} / {n_bits}'  	
            tmp = j2_template.render(rvv_size=rvv_size, isa_datatype=isa_rvv["datatypes"][dt], nb_elem=nb_elem)  
            tmp = tmp.format(lsuffix = "m1",
                             lsuffix_mipp = "d2",
                             lmul = "", 
                             eew_emul = str(int(n_bits)), 
                             n_bits = str(n_bits))
        else : 
            n_bits = datatypes[dt]["n_bits"]
            nb_elem = f'{rvv_size} / {n_bits}'  	
            tmp = j2_template.render(rvv_size=rvv_size, isa_datatype=isa_rvv["datatypes"][dt], nb_elem=nb_elem)  
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
        for dt in isa_rvv["datatypes"]:
            n_bits = datatypes[dt]["n_bits"]
            nb_elem = f'{rvv_size} / {n_bits} * {lmul}'
            tmp = template.replace("{lsuffix}", "m" + str(lmul))
            j2_template = Template(tmp, undefined=StrictUndefined)
            guard = isa_rvv["datatypes"][dt].get("if", None)
            if guard:
                print(f"#if {guard}", file=file)
            print(j2_template.render(isa=isa_rvv,rvv_size=rvv_size,isa_datatype=isa_rvv["datatypes"][dt], datatype=datatypes[dt], lmul=lmul), file=file)
            if guard:
                print(f"#else", file=file)
                print(f"    #include \"../scalar/scalar_common.h\"", file=file)
                print(f"    typedef rvd_scalar_{datatypes[dt]['category']}{datatypes[dt]['n_bits']}_t rvd_rvv_{datatypes[dt]['category']}{datatypes[dt]['n_bits']}_m{lmul}_t;", file=file)
                print(f"#endif", file=file)
    
    ldiv = 2
    for dt in isa_rvv["datatypes"]:
        n_bits = datatypes[dt]["n_bits"]
        nb_elem = f'{rvv_size} / {n_bits} / {ldiv}'
        tmp = template.replace("{lsuffix}", "d" + str(ldiv))
        j2_template = Template(tmp, undefined=StrictUndefined)
        guard = isa_rvv["datatypes"][dt].get("if", None)
        if guard:
            print(f"#if {guard}", file=file)
        print(j2_template.render(isa=isa_rvv,rvv_size=rvv_size,isa_datatype=isa_rvv["datatypes"][dt], datatype=datatypes[dt], lmul=ldiv), file=file)
        if guard:
            print(f"#else", file=file)
            print(f"    #include \"../scalar/scalar_common.h\"", file=file)
            print(f"    typedef rvd_scalar_{datatypes[dt]['category']}{datatypes[dt]['n_bits']}_t rvd_rvv_{datatypes[dt]['category']}{datatypes[dt]['n_bits']}_d{ldiv}_t;", file=file)
            print(f"#endif", file=file)

    #typedef of rvd m1 to no suffix
    template = """typedef rvd_{{ isa.name }}_{{ datatype.category }}{{ datatype.n_bits }}_m1_t rvd_{{ isa.name }}_{{ datatype.category }}{{ datatype.n_bits }}_t;"""
    for dt in isa_rvv["datatypes"]:
        n_bits = datatypes[dt]["n_bits"]
        nb_elem = f'{rvv_size} / {n_bits}'
        tmp = template.replace("_m{lmul}", "")
        j2_template = Template(tmp, undefined=StrictUndefined)
        guard = isa_rvv["datatypes"][dt].get("if", None)
        if guard:
            print(f"#if {guard}", file=file)
        print(j2_template.render(isa=isa_rvv,rvv_size=rvv_size,isa_datatype=isa_rvv["datatypes"][dt], datatype=datatypes[dt], lmul=""), file=file)
        if guard:
            print(f"#else", file=file)
            print(f"    #include \"../scalar/scalar_common.h\"", file=file)
            print(f"    typedef rvd_scalar_{datatypes[dt]['category']}{datatypes[dt]['n_bits']}_t rvd_rvv_{datatypes[dt]['category']}{datatypes[dt]['n_bits']}_t;", file=file)
            print(f"#endif", file=file)
    
    #rvm struct generation
    template = """typedef struct { fixed_{lsuffix}_bool{n_bits}_t m; } rvm_{{ isa.name }}_{{ datatype.category }}{{ datatype.n_bits }}_{lsuffix}_t;"""
    j2_template = Template(template, undefined=StrictUndefined)
       
    for lmul in all_lmul:
        for dt in isa_rvv["datatypes"]:
            n_bits = datatypes[dt]["n_bits"]
            nb_elem = f'{rvv_size} / {n_bits} * {lmul}'
            tmp = template.replace("{lsuffix}", "m" + str(lmul))
            tmp = tmp.replace("{n_bits}", str(n_bits))
            j2_template = Template(tmp, undefined=StrictUndefined)
            guard = isa_rvv["datatypes"][dt].get("if", None)
            if guard:
                print(f"#if {guard}", file=file)
            print(j2_template.render(isa=isa_rvv,rvv_size=rvv_size,isa_datatype=isa_rvv["datatypes"][dt], datatype=datatypes[dt], lmul=lmul), file=file)
            if guard:
                print(f"#else", file=file)
                print(f"    typedef rvm_scalar_{datatypes[dt]['category']}{datatypes[dt]['n_bits']}_t rvm_rvv_{datatypes[dt]['category']}{datatypes[dt]['n_bits']}_m{lmul}_t;", file=file)
                print(f"#endif", file=file)

    ldiv = 2
    for dt in isa_rvv["datatypes"]:
        n_bits = datatypes[dt]["n_bits"]
        nb_elem = f'{rvv_size} / {n_bits} / {ldiv}'
        tmp = template.replace("{lsuffix}", "d" + str(ldiv))
        tmp = tmp.replace("{n_bits}", str(n_bits))
        j2_template = Template(tmp, undefined=StrictUndefined)
        guard = isa_rvv["datatypes"][dt].get("if", None)
        if guard:
            print(f"#if {guard}", file=file)
        print(j2_template.render(isa=isa_rvv,rvv_size=rvv_size,isa_datatype=isa_rvv["datatypes"][dt], datatype=datatypes[dt], lmul=ldiv), file=file)
        if guard:
            print(f"#else", file=file)
            print(f"    typedef rvm_scalar_{datatypes[dt]['category']}{datatypes[dt]['n_bits']}_t rvm_rvv_{datatypes[dt]['category']}{datatypes[dt]['n_bits']}_d{ldiv}_t;", file=file)
            print(f"#endif", file=file)
    
    template = """typedef rvm_{{ isa.name }}_{{ datatype.category }}{{ datatype.n_bits }}_m1_t rvm_{{ isa.name }}_{{ datatype.category }}{{ datatype.n_bits }}_t;"""
    for dt in isa_rvv["datatypes"]:
        n_bits = datatypes[dt]["n_bits"]
        nb_elem = f'{rvv_size} / {n_bits}'
        tmp = template.replace("_m{lmul}", "")
        j2_template = Template(tmp, undefined=StrictUndefined)
        guard = isa_rvv["datatypes"][dt].get("if", None)
        if guard:
            print(f"#if {guard}", file=file)
        print(j2_template.render(isa=isa_rvv,rvv_size=rvv_size,isa_datatype=isa_rvv["datatypes"][dt], datatype=datatypes[dt], lmul=""), file=file)
        if guard:
            print(f"#else", file=file)
            print(f"    typedef rvm_scalar_{datatypes[dt]['category']}{datatypes[dt]['n_bits']}_t rvm_rvv_{datatypes[dt]['category']}{datatypes[dt]['n_bits']}_t;", file=file)
            print(f"#endif", file=file)
#taken from gen_mipp_avx.py (changed)

def resolve_lmul_in_isa(isa, lmul):
    if lmul == "0" or lmul == 0:
        lmul = "1"
    
    lsuffix = "m" + str(lmul)

    if int(lmul) < 0 : 
        lsuffix = "mf" + str(-int(lmul))

    lsuffix_tmp = lsuffix
    lmul_tmp = lmul
    resolved_isa = copy.deepcopy(isa)
    for dt in resolved_isa["datatypes"]:
        if isa_rvv["datatypes"][dt]["width"] == "64" and int(lmul) < 0:
            lsuffix = "m1"
            lmul = "1"
        else :
            lsuffix = lsuffix_tmp
            lmul = lmul_tmp

        for key in resolved_isa["datatypes"][dt]:
            if "{lsuffix}" in resolved_isa["datatypes"][dt][key]:
                resolved_isa["datatypes"][dt][key] = resolved_isa["datatypes"][dt][key].format(lsuffix=lsuffix)
            if "{eew_emul}" in resolved_isa["datatypes"][dt][key]:
                n_bits = datatypes[dt]["n_bits"]
                eew_emul = 0
                if int(lmul) == 0:
                    eew_emul = 1
                elif int(lmul) < 0 :
                    eew_emul = str(int(int(n_bits)*int(-lmul)))
                else :
                    eew_emul = str(int(int(n_bits)/int(lmul)))
                resolved_isa["datatypes"][dt][key] = resolved_isa["datatypes"][dt][key].format(eew_emul=eew_emul)
    return resolved_isa

def gen_mipp_rvv(include_manager, vlen="__riscv_v_fixed_vlen"):
    file_common = include_manager.get_fd(isa_rvv["name"], "common")
    if file_common is None:
        print("Panic: common.h file descriptor not found for RVV.")
        exit(-1)

    tpl_header_rvv = """#ifndef MY_INTRINSICS_PLUS_PLUS_IMPL_GEN_RVV_H_
#define MY_INTRINSICS_PLUS_PLUS_IMPL_GEN_RVV_H_
#include <riscv_vector.h>
#include <string.h>
#include <float.h>
#include <stdint.h>
#include <stdio.h>//remove after debug
#include <stdlib.h>//remove after debug
#define MIPP_RVV_VLEN {{vlen}}
typedef float float32_t;//remove after debug
typedef double float64_t;//remove after debug"""
    j2_template = Template(tpl_header_rvv, undefined=StrictUndefined)
    print(j2_template.render(vlen=vlen), file=file_common)

    ref_isa_name = isa_rvv["name"]
    #for function prototypes that use arrays declared w macros like MIPP_RVV256_N_FLOAT64 
    #we want the name to contain size. This is optional atm 
    #but if we want smth similar to sve it will become useful
    isa_rvv["name"] = ref_isa_name #+str(vl) # Adrien: I commented "+str(vl)" because I use this field to generate "#if define(MIPP_RVV)" in the interfaces
    gen_c_defines_rvv_ls(file_common,ref_isa_name,vlen)
    gen_c_structures_rvv_ls(file_common,vlen)
    
    tpl_footer_rvv = """#endif /* MY_INTRINSICS_PLUS_PLUS_IMPL_GEN_RVV_H_ */"""
    j2_template = Template(tpl_footer_rvv, undefined=StrictUndefined)
    print(j2_template.render(), file=file_common)
    
    copy_mipp_funcs = copy.deepcopy(mipp_funcs)
        
    isa_rvv_lmul1 = resolve_lmul_in_isa(isa_rvv, "1")
    
    for lmul in [0] + all_lmul:
        resolved_isa = resolve_lmul_in_isa(isa_rvv, str(lmul))
        gen_c_functions_rvv(resolved_isa, include_manager, copy_mipp_funcs, implems_rvv, lmul=lmul)
        #ret = fix_reductions(resolved_isa, isa_rvv_lmul1, copy_mipp_funcs, implems_emu_rvv, lmul)

        gen_c_functions_rvv(resolved_isa, include_manager, copy_mipp_funcs, implems_emu_rvv, lmul=lmul)
        
        #rvv doesn't have any "if" in implems rvv so we can get away with calling gen_c_functions rvv instead of a
        #separate gen_c_generic_functions_rvv FOR NOW.
        #change this line if this ever changes.
        gen_c_functions_rvv(resolved_isa, include_manager, copy_mipp_funcs, implems_generic_emu, lmul=lmul, cand_type="generic_emu")
        
        gen_c_functions_rvv(resolved_isa, include_manager, copy_mipp_funcs, implems_mask_generic_emu, lmul=lmul, cand_type="generic_emu")
        gen_c_missing_functions_lmul(resolved_isa, include_manager, copy_mipp_funcs, lmul=lmul)
    
    ldiv = -2
    resolved_isa = resolve_lmul_in_isa(isa_rvv, ldiv)
    gen_c_functions_rvv(resolved_isa, include_manager, copy_mipp_funcs, implems_rvv, lmul=ldiv)
    gen_c_functions_rvv(resolved_isa, include_manager, copy_mipp_funcs, implems_emu_rvv, lmul=ldiv)
    gen_c_functions_rvv(resolved_isa, include_manager, copy_mipp_funcs, implems_generic_emu, lmul=ldiv, cand_type="generic_emu")
    gen_c_functions_rvv(resolved_isa, include_manager, copy_mipp_funcs, implems_mask_generic_emu, lmul=ldiv, cand_type="generic_emu")
    gen_c_missing_functions_lmul(resolved_isa, include_manager, copy_mipp_funcs, lmul=ldiv)
    
    #now that dependencies are resolved and functions are generated we can generate the headers for the functions with the correct includes
    include_manager.resolve_all_dependencies(isa_rvv["name"], copy_mipp_funcs)
    include_manager.create_glue_file(isa_rvv["name"], "../include/rvv/mipp_impl_rvv_gen.h")
    include_manager.close_layer_fds(isa_rvv["name"])