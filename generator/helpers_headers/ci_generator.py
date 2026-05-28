from jinja2 import Template, StrictUndefined, Environment, FileSystemLoader
import json
import re

from tools import *
from headers_def import *
from include_gen import IncludeManager

from c_generator import gen_c_horiz_lmul 
from generic_emu import implems_horiz_lmul_generic_emu

def get_sub_isa(isa, ldiv, isa_list):
    for sub_isa in isa_list:
        if isa["architecture"] == "AArch64":
                return 
        elif isa["architecture"] == sub_isa["architecture"] :
            # pas genial sve list int x86 int (mettre un tableau de taille 1 pour x86)
            if isinstance(isa["size"], int) and isa["size"]/ldiv == sub_isa["size"] :
                return sub_isa
            
def duplicate_isa_sve_along_size(isa_list):			
    isa_list_copy = copy.deepcopy(isa_list)
    isa_sve = []
    current_index = -1
    isa_sve_size = []
    for index, isa in enumerate(isa_list_copy):
        if isa["name"]=="sve":
            isa_sve = isa
            current_index = index
            all_sve_sizes = list(isa["size"])
        else:
            isa["gen_define"] = "defined(MIPP_" + isa["name"].upper() + ")"
    del isa_list_copy[current_index]
    all_sve_sizes = sorted(isa_sve["size"], reverse=True)
    for reg_size in all_sve_sizes:
        isa_sve_copy = copy.deepcopy(isa_sve)
        isa_sve_copy["gen_define"]="defined(MIPP_" + isa_sve_copy["name"].upper() + "_" + str(reg_size) + ")"
        isa_sve_copy["name"]="sve"+str(reg_size)
        isa_sve_copy["size"]=reg_size
        isa_list_copy.append(isa_sve_copy)
    return isa_list_copy


def _isa_include_common(isa):
    content =  "\n#include \"../simd_ext/"+isa["name"]+"/" + isa["name"] + "_common.h\"\n"
    if isa["name"] == "avx" : 
        # also include sse common for avx since it relies on sse types
        content +=  "\n#include \"../simd_ext/sse/sse_common.h\"\n"
    elif isa["name"] == "avx512" :
        # also include avx common for avx512 since it relies on avx types
        content +=  "\n#include \"../simd_ext/avx/avx_common.h\"\n"
    return content


def _isa_include_function(isa, func):
    
    
    if isa == "c":
        content = "\n#include \"" + func + ".h\"\n"
        return content
    
    content = "\n#include \"../../simd_ext/"+isa["name"]+"/" + "functions/" + isa["name"] + "_" + func + ".h\"\n"
    if isa["name"] == "avx" : 
        # also include sse functions for avx since it relies on sse types
        content += "\n#include \"../../simd_ext/sse/" + "functions/" + "sse_" + func + ".h\"\n"
    elif isa["name"] == "avx512" :
        # also include avx functions for avx512 since it relies on avx types
        content += "\n#include \"../../simd_ext/avx/" + "functions/" + "avx_" + func + ".h\"\n"
    return content


def _custom_prefix_generator(func, isa_list, is_common=False):
    """
    Creates custom prefix for the function inside of c/functions/name.h 
    
    These function should include every isa/common.h 
    and the relevant isa/function/name.h 
    also adds #pragma once @ the start of the file.
    
    returns a string with the content of the prefix.
    """
    content = "#pragma once\n\n"
    if is_common:
        is_first = True
        
        content += """

#define MIPP

#include <stdint.h>
#include <float.h>
#include <stdio.h>
#include <stdlib.h>

//typedef double float64_t;
//typedef float float32_t;

// ------------------------------------------------------------------------------------------------- includes files

//#if defined(__MIC__) || defined(__KNCNI__) || defined(__AVX512__) || defined(__AVX512F__)
//#include "avx512/mipp_impl_avx512_gen.h"
//#endif
//#if defined(__AVX__)
//#include "avx/mipp_impl_avx_gen.h"
//#endif

//#if defined(__SSE__)
//#include "sse/mipp_impl_sse_gen.h"
//#endif

//#if defined(__ARM_FEATURE_SVE)
//#include "sve/mipp_impl_sve_gen.h"
//#endif

//#if defined(__riscv_v_intrinsic)
//#include "rvv/mipp_impl_rvv_gen.h"
//#endif

//#if defined(__ARM_NEON__) || defined(__ARM_NEON)
//#include "neon/mipp_impl_neon_gen.h"
//#endif

// utiles pour l'instant pour les tests
// pourrait clairement etre utile pour les generateurs au dela du if #define

#if defined(MIPP_SCALAR)

#elif defined(__MIC__) || defined(__KNCNI__) || defined(__AVX512__) || defined(__AVX512F__)
    #define MIPP_AVX512
    #define MIPP_INSTR_VERSION 1
    #define MIPP_64BIT
#ifdef __AVX512BW__
    #define MIPP_BW
#endif
#ifdef __AVX512VBMI2__
    #define MIPP_BMI2
#endif
#ifdef __FMA__
    #define MIPP_FMA
#endif

#elif defined(__AVX__)
    #define MIPP_AVX
    #define MIPP_64BIT
#ifdef __AVX2__
    #define MIPP_AVX2
    #define MIPP_INSTR_VERSION 2
    #define MIPP_BW
#else
    #define MIPP_INSTR_VERSION 1
#endif
#ifdef __BMI2__
    #define MIPP_BMI2
#endif
#ifdef __FMA__
    #define MIPP_FMA
#endif

#elif defined(__SSE__)
    #define MIPP_SSE
#ifdef __SSE2__
    #define MIPP_64BIT
    #define MIPP_BW
#endif

#elif defined(__ARM_FEATURE_SVE)
#define MIPP_SVE
#define MIPP_FMA
#define MIPP_64BIT
// not yet generated
//#define MIPP_BW
#define MIPP_INSTR_VERSION 1

#elif defined(__ARM_NEON__) || defined(__ARM_NEON)
#define MIPP_NEON
#define MIPP_BW
#if defined(__ARM_FEATURE_FMA)
#define MIPP_FMA
#endif
#if defined(__aarch64__)
#define MIPP_64BIT
#define MIPP_INSTR_VERSION 2
#else
#define MIPP_INSTR_VERSION 1
#endif
#endif

#ifdef __riscv_v_intrinsic
#define MIPP_RVV
#define MIPP_64BIT
#define MIPP_BW
#endif

// end utiles pour l'instant pour les tests...        
"""
        content += "typedef double float64_t;\n"
        content += "typedef float float32_t;\n\n"

        for isa in isa_list:
            if is_first:
                content += "#if " + "defined(MIPP_" + isa["name"].upper() + ")\n"
                is_first = False
            else:
                content += "#elif " + "defined(MIPP_" + isa["name"].upper() + ")\n"
            content += _isa_include_common(isa)
        content += "#else\n#error \"Unsupported architecture, MIPP may not work properly\"\n#endif\n"
        
        
    else : 
        is_first = True

        content += "#include \"../common.h\"\n"
        for isa in isa_list:
            if is_first:
                content += "\n#if " + "defined(MIPP_" + isa["name"].upper() + ")\n"
                is_first = False
            else:
                content += "\n#elif " + "defined(MIPP_" + isa["name"].upper() + ")\n"
                
            content += _isa_include_function(isa, func)
        content += "#endif\n"
    
        # here we go through implems_horiz_lmul_generic_emu to check for "dependencies" of the lmul variants 
        # this is a hacky fix bc we don't do dependency resolution in the C layer and above. 
        if func in implems_horiz_lmul_generic_emu:
            
            for implem in implems_horiz_lmul_generic_emu[func]:
                if "dependencies" in implem:
                    for dep in implem["dependencies"]:
                        content += _isa_include_function("c", dep)

        
    return content
    
    

def generate_c_interface(isa_list, include_manager=None):
    
    # file = open("../include/mipp.h", "a")
    file_common = include_manager.get_fd("c", "common")
    custom_prefix = _custom_prefix_generator("common", isa_list, is_common=True)
    print(custom_prefix, file=file_common)
    
    tpl_header_interface = """#ifndef MY_INTRINSICS_PLUS_PLUS_INTERFACE_H_
#define MY_INTRINSICS_PLUS_PLUS_INTERFACE_H_ """
    j2_template = Template(tpl_header_interface, undefined=StrictUndefined)
    print(j2_template.render(), file=file_common)
    # use try ldiv sve
    isa_list = duplicate_isa_sve_along_size(isa_list)
    gen_ci_defines(isa_list, file_common)
    gen_ci_structures(isa_list, file_common)

    # Add mipp_info function to mipp.h
    env = Environment(loader=FileSystemLoader("./helpers_headers/templates/"))
    template_mipp_info = env.get_template("mipp_info.tpl.h")
    str_mipp_info = template_mipp_info.render(name="Unused for now :-)")
    print(str_mipp_info, file=file_common)

    gen_ci_functions(isa_list, include_manager, copy_mipp_funcs)

    tpl_footer_interface = """#endif /* MY_INTRINSICS_PLUS_PLUS_INTERFACE_H_ */"""
    j2_template = Template(tpl_footer_interface, undefined=StrictUndefined)
    print(j2_template.render(), file=file_common)

def gen_ci_defines(isa_list, file):
    for i, isa in enumerate(isa_list):
        if i == 0:
            print("#if " + isa["gen_define"], file=file)
        else:
            print("#elif " + isa["gen_define"], file=file)
            
        print("#define MIPP_RVD_SIZE_BYTE MIPP_"+isa["name"].upper()+"_RVD_SIZE_BYTE", file=file)

        template = """#define MIPP_N_{{type_category_upper}}{{n_bits}} MIPP_{{isa_name_upper}}_N_{{type_category_upper}}{{n_bits}}"""
        
        for lmul in all_lmul:
            tmp = "\n#define MIPP_N_{{type_category_upper}}{{n_bits}}_M{ lmul } MIPP_{{isa_name_upper}}_N_{{type_category_upper}}{{n_bits}} * { lmul }"
            tmp = tmp.replace("{ lmul }", str(lmul))
            template += tmp
            
        for ldiv in all_ldiv:
            tmp = "\n#define MIPP_N_{{type_category_upper}}{{n_bits}}_D{ ldiv } MIPP_{{isa_name_upper}}_N_{{type_category_upper}}{{n_bits}} / { ldiv }"
            tmp = tmp.replace("{ ldiv }", str(ldiv))
            template += tmp
            
        for dt in isa["datatypes"]:
            j2_template = Template(template, undefined=StrictUndefined)
            print(j2_template.render(isa_name_upper=isa["name"].upper(), n_bits=datatypes[dt]["n_bits"], type_category_upper=datatypes[dt]["category"].upper()), file=file)

        if i == len(isa_list)-1:
            print("#endif", file=file)
           
    print("#define MIPP_LMUL_STRIDE(elmt_byte, m) ((MIPP_RVD_SIZE_BYTE) / (elmt_byte) * (m))", file=file)


def gen_ci_structures(isa_list, file):

    isa_rvv = next((isa for isa in isa_list if isa["name"].startswith("rvv")), None)
    isa_scalar = next((isa for isa in isa_list if isa["name"].startswith("scalar")), None)
    
    for index, isa in enumerate(isa_list):
        
        if index == 0:
            print("#if " + isa["gen_define"], file=file)
        else:
            print("#elif " + isa["gen_define"], file=file)

        template = """typedef rvd_{{ isa.name }}_{{ datatype.category }}{{ datatype.n_bits }}_t rvd_{{ datatype.category }}{{ datatype.n_bits }}_t;"""
        j2_template = Template(template, undefined=StrictUndefined)

        for dt in isa["datatypes"]:
            print(j2_template.render(isa=isa, datatype=datatypes[dt]), file=file)

        template = """typedef rvm_{{ isa.name }}_{{ datatype.category }}{{ datatype.n_bits }}_t rvm_{{ datatype.category }}{{ datatype.n_bits }}_t;"""
        j2_template = Template(template, undefined=StrictUndefined)

        for dt in isa["datatypes"]:
            print(j2_template.render(isa=isa, datatype=datatypes[dt]), file=file)
        
        #sub_isa_list = isa_list[index+1:]
        
        for ldiv in all_ldiv:
            sub_isa = get_sub_isa(isa, ldiv, isa_list)
            if sub_isa :
                print("#if " + sub_isa["define"], file=file)
                used_sub_isa = sub_isa
                print("#define MIPP_ENABLE_LDIV"+str(ldiv), file=file)
            else :
                break
                
            template = """typedef rvd_{{ used_sub_isa.name }}_{{ datatype.category }}{{ datatype.n_bits }}_t rvd_{{ datatype.category }}{{ datatype.n_bits }}_d{{ ldiv }}_t;"""
            j2_template = Template(template, undefined=StrictUndefined)
            for dt in isa["datatypes"]:
                print(j2_template.render(used_sub_isa=used_sub_isa, datatype=datatypes[dt], ldiv=str(ldiv)), file=file)
            template = """typedef rvm_{{ used_sub_isa.name }}_{{ datatype.category }}{{ datatype.n_bits }}_t rvm_{{ datatype.category }}{{ datatype.n_bits }}_d{{ ldiv }}_t;"""
            j2_template = Template(template, undefined=StrictUndefined)
            for dt in isa["datatypes"]:
                print(j2_template.render(used_sub_isa=used_sub_isa, datatype=datatypes[dt], ldiv=str(ldiv)), file=file)
            
            if sub_isa :	
                print("#endif /** '"+sub_isa["define"]+"' under '"+isa["define"]+"' **/", file=file)
            
        if index == len(isa_list)-1:
            print("#endif", file=file)

    template = """typedef rvd_{{ datatype.category }}{{ datatype.n_bits }}_t rvd_{{ datatype.category }}{{ datatype.n_bits }}_m1_t;"""
    j2_template = Template(template, undefined=StrictUndefined)

    for dt in isa["datatypes"]:
        print(j2_template.render(isa=isa, datatype=datatypes[dt]), file=file)

    for index, isa in enumerate(isa_list):
        if index == 0:
            print("#if " + isa["gen_define"], file=file)
        else:
            print("#elif " + isa["gen_define"], file=file)
        for lmul in all_lmul:
            template = """typedef rvd_{{ isa.name }}_{{ datatype.category }}{{ datatype.n_bits }}_m{{ lmul }}_t rvd_{{ datatype.category }}{{ datatype.n_bits }}_m{{ lmul }}_t;"""
            j2_template = Template(template, undefined=StrictUndefined)
            for dt in isa["datatypes"]:
                print(j2_template.render(isa=isa, datatype=datatypes[dt], lmul=str(lmul)), file=file)
            template = """typedef rvm_{{ isa.name }}_{{ datatype.category }}{{ datatype.n_bits }}_m{{ lmul }}_t rvm_{{ datatype.category }}{{ datatype.n_bits }}_m{{ lmul }}_t;"""
            j2_template = Template(template, undefined=StrictUndefined)
            for dt in isa["datatypes"]:
                print(j2_template.render(isa=isa, datatype=datatypes[dt], lmul=str(lmul)), file=file)
    print("#endif", file=file)    
   
 

def ci_mask_writer(func, dt, isa_list, file, mask_type, func_name="", lmul=0):
    
    if len(dt.split(',')) <= 1:
        dt_par = dt.split(',')[0]
        dt_ret = dt.split(',')[0]
    else :
        dt_par = dt.split(',')[0]
        dt_ret = dt.split(',')[1]
  
    proto = build_proto(mipp_funcs[func]["proto"], dt_par, dt_ret, isa_list[0], func_name, lmul, False, False, mask_type)
    template = f'static {proto} {{'
    j2_template = Template(template, undefined=StrictUndefined)
    print(j2_template.render(), file=file)
    for i, isa in  enumerate(isa_list):
        if i == 0:
            print("#if " + isa["gen_define"], file=file)
        else:
            print("#elif " + isa["gen_define"], file=file)

        if len(dt.split(',')) <= 1:
            func_name_impl = build_func_name_short(isa, dt_par, func, True, lmul, mask_type);
        else:
            func_name_impl = build_func_name(isa, dt_par, dt_ret, f, True, lmul, mask_type);
        print("\t" + build_call(mipp_funcs[func]["proto"], dt_par, dt_ret, isa, func_name_impl, masked_version = mask_type) + ";", file=file)
        if i == len(isa_list)-1:
            print("#else", file=file)
            print("\tprintf(\"MIPP panic: '%s', unsupported case, this should never happen.\\n\", \""+func_name+"\");", file=file);
            print("\texit(-1);", file=file);
            print("#endif", file=file)
            print("}", file=file)

def gen_ci_mask_functions(func, dt, isa_list, file,lmul=0, func_name=""):
    maskable = "mask_support" in mipp_funcs[func] and mipp_funcs[func]["mask_support"].is_maskable()
    maskzable = "mask_support" in mipp_funcs[func] and mipp_funcs[func]["mask_support"].is_maskzable()
    masksable = "mask_support" in mipp_funcs[func] and mipp_funcs[func]["mask_support"].is_masksable()
    
    if maskable:
        ci_mask_writer(func, dt, isa_list, file, "mask", func_name, lmul)
    if maskzable:
        ci_mask_writer(func, dt, isa_list, file, "maskz", func_name, lmul)
    if masksable:
        ci_mask_writer(func, dt, isa_list, file, "masks", func_name, lmul)
  
  
def ci_lmul_writer(f,func_name, dt, dt_par, dt_ret, isa_list, funcs, file, mask_type=None, lmul=0):
    # now that lmul funcs have been moved to simd_ext layer, this is just a wrapper to call the correct function depending on the ISA.

    print("static " + build_proto(funcs[f]["proto"], dt_par, dt_ret, {}, func_name, lmul, False, False, mask_type) + " {", file=file)
    for i, isa in  enumerate(isa_list):
        if i == 0:
            print("#if " + isa["gen_define"], file=file)
        else:
            print("#elif " + isa["gen_define"], file=file)
                       
        if len(dt.split(',')) <= 1:
            func_name_impl = build_func_name_short(isa, dt_par, f, True, lmul, mask_type)
        else:
            func_name_impl = build_func_name(isa, dt_par, dt_ret, f, True, lmul, mask_type)
        print("\t" + build_call(funcs[f]["proto"], dt_par, dt_ret, isa, func_name_impl, masked_version=mask_type) + ";", file=file)
    print("#else", file=file)

    mask_str = ""
    if mask_type is not None:
        mask_str = "_" + mask_type
    print("\tprintf(\"MIPP panic: '%s' is unimplemented.\\n\", \""+func_name+"_m"+str(lmul)+mask_str+"\");", file=file);
    print("\texit(-1);", file=file);
    print("#endif", file=file)
    print("}", file=file)

  
 

def ci_ldiv_writer(f,func_name, dt, dt_par, dt_ret, isa_list, funcs, file, mask_type=None, ldiv=0):
    if not funcs[f]["horizontal"]: #and funcs[f]["half_regiser"]:
        print("#if defined(MIPP_ENABLE_LDIV"+str(ldiv)+")", file=file)
        print("static " + build_proto(funcs[f]["proto"], dt_par, dt_ret, isa_list[0], func_name+"_d"+str(ldiv), -ldiv, False) + " {", file=file)
        for i, isa in  enumerate(isa_list):
            sub_isa = sub_isa = get_sub_isa(isa, ldiv, isa_list)
            if sub_isa :
                if i == 0:
                    print("#if " + isa["gen_define"] + " && " + sub_isa["define"], file=file)
                else:
                    print("#elif " + isa["gen_define"] + " && " + sub_isa["define"], file=file)
                           
                if len(dt.split(',')) <= 1:
                    func_name_impl = build_func_name_short(sub_isa, dt_par, f);
                else:
                    func_name_impl = build_func_name(sub_isa, dt_par, dt_ret, f);
                print("\t" + build_call(funcs[f]["proto"], dt_par, dt_ret, sub_isa, func_name_impl) + ";", file=file)	
                    
        print("#else", file=file)
        print("\tprintf(\"MIPP panic: '%s' is unimplemented.\\n\", \""+func_name+"_d"+str(ldiv)+"\");", file=file);
        print("\texit(-1);", file=file);
        print("#endif", file=file)
        print("}", file=file)
        print("#endif // defined(MIPP_ENABLE_LDIV"+str(ldiv)+")", file=file)
    else :
        print("#if defined(MIPP_ENABLE_LDIV"+str(ldiv)+")", file=file)
        print("static " + build_proto(funcs[f]["proto"], dt_par, dt_ret, isa_list[0], func_name+"_d"+str(ldiv), -ldiv, False) + " {", file=file)
        print("\tprintf(\"MIPP panic: '%s' is unimplemented.\\n\", \""+func_name+"_d"+str(ldiv)+"\");", file=file);
        print("\texit(-1);", file=file);
        print("}", file=file)
        print("#endif // defined(MIPP_ENABLE_LDIV"+str(ldiv)+")"+")", file=file)

def gen_ci_functions(isa_list, include_manager, funcs):
    isa_rvv = next((isa for isa in isa_list if isa["name"].startswith("rvv")), None)
    isa_scalar = next((isa for isa in isa_list if isa["name"].startswith("scalar")), None)
    
    include_manager.move_to_new_dir("simd_ext", [isa["name"] for isa in isa_list ])
    for f in funcs:
        file = include_manager.get_fd("c", f)
        for dt in funcs[f]["datatypes"]:
            if len(dt.split(',')) <= 1:
                dt_par = dt.split(',')[0]
                dt_ret = dt.split(',')[0]
            else:
                dt_par = dt.split(',')[0]
                dt_ret = dt.split(',')[1]
                dtk = dt_par + "," + dt_ret
            dt_key = dt_par + "," + dt_ret

            if len(dt.split(',')) <= 1:
                func_name = build_func_name_short(isa_list[0], dt_par, f, False);
            else:
                func_name = build_func_name(isa_list[0], dt_par, dt_ret, f, False);
            print("static " + build_proto(funcs[f]["proto"], dt_par, dt_ret, isa_list[0], func_name, 0, False) + " {", file=file)
            for i, isa in  enumerate(isa_list):
                if i == 0:
                    print("#if " + isa["gen_define"], file=file)
                else:
                    print("#elif " + isa["gen_define"], file=file)
   
                if len(dt.split(',')) <= 1:
                    func_name_impl = build_func_name_short(isa, dt_par, f);
                else:
                    func_name_impl = build_func_name(isa, dt_par, dt_ret, f);
                print("\t" + build_call(funcs[f]["proto"], dt_par, dt_ret, isa, func_name_impl) + ";", file=file)
                if i == len(isa_list)-1:
                    print("#else", file=file)
                    print("\tprintf(\"MIPP panic: '%s', unsupported case, this should never happen.\\n\", \""+func_name+"\");", file=file);
                    print("\texit(-1);", file=file);
                    print("#endif", file=file)

            print("}", file=file)

            print("static " + build_proto(funcs[f]["proto"], dt_par, dt_ret, isa_list[0], func_name, 1, False) + " {", file=file)
            print("\t" + build_call(funcs[f]["proto"], dt_par, dt_ret, isa_list[0], func_name) + ";", file=file)
            print("}", file=file)
   
            gen_ci_mask_functions(f, dt, isa_list, file, 0, func_name=func_name)
            
            for lmul in all_lmul[1:]:
                ci_lmul_writer(f, func_name, dt, dt_par, dt_ret, isa_list, funcs, file, lmul=lmul)
                
    
            for lmul in all_lmul:
                mask_status = ""
                if "mask_support" in funcs[f] :
                    mask_status = funcs[f]["mask_support"]
                else :
                    mask_status = MaskSupport()

                if not mask_status.is_any_mask() :
                    continue
                if mask_status.is_maskable() :
                    ci_lmul_writer(f, func_name, dt, dt_par, dt_ret, isa_list, funcs, file, mask_type="mask", lmul=lmul)
                
                if mask_status.is_maskzable() :
                    ci_lmul_writer(f, func_name, dt, dt_par, dt_ret, isa_list, funcs, file, mask_type="maskz", lmul=lmul)
                if mask_status.is_masksable() :			
                    ci_lmul_writer(f, func_name, dt, dt_par, dt_ret, isa_list, funcs, file, mask_type="masks", lmul=lmul)
            
            # for ldiv in all_ldiv:
            #     ci_ldiv_writer(f, func_name, dt, dt_par, dt_ret, isa_list, funcs, file, ldiv=ldiv)
                
        custom_prefix = _custom_prefix_generator(f, isa_list)
        include_manager.write_custom_prefix("c", f, custom_prefix)
