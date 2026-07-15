from jinja2 import Template, StrictUndefined
import json

from tools import *
from headers_def import *
isa_sve, implems_sve, implems_emu_sve = load_isa_config("sve")
from c_generator import *

from include_gen import IncludeManager

def gen_c_defines_sve_ls(file, isa_name, sve_size):
    print("#define MIPP_" + isa_name.upper() + str(sve_size) + "_RVD_SIZE_BIT " + str(sve_size), file=file)
    print("#define MIPP_" + isa_name.upper() + str(sve_size) + "_RVD_SIZE_BYTE " + str(int(sve_size / 8)), file=file)
    template = """#define MIPP_SVE{{sve_size}}_N_{{type_category_upper}}{{n_bits}} {{type_size}}"""
    j2_template = Template(template, undefined=StrictUndefined)
    for dt in isa_sve["datatypes"]:
        n_bits=datatypes[dt]["n_bits"]
        print(j2_template.render(sve_size=sve_size, n_bits=n_bits, type_size = int(sve_size/n_bits), type_category_upper=datatypes[dt]["category"].upper()), file=file)
    

def gen_c_structures_sve_ls(file, sve_size):
    template = """typedef {{ isa_datatype.reg }} fixed_{{ sve_size }}_{{isa_datatype.to_ptr}} __attribute__((arm_sve_vector_bits({{ sve_size }})));"""
    j2_template = Template(template, undefined=StrictUndefined)
    for dt in isa_sve["datatypes"]:
        print(j2_template.render(isa_datatype=isa_sve["datatypes"][dt],sve_size=sve_size), file=file)
        
    template = """typedef svbool_t fixed_{{sve_size}}_bool_t __attribute__((arm_sve_vector_bits({{sve_size}})));"""
    j2_template = Template(template, undefined=StrictUndefined)
    print(j2_template.render(sve_size=sve_size), file=file)
    
    template = """typedef struct { fixed_{{ sve_size }}_{{isa_datatype.to_ptr }} r; } rvd_{{ isa.name }}_{{ datatype.category }}{{ datatype.n_bits }}_t;"""
    j2_template = Template(template, undefined=StrictUndefined)
    for dt in isa_sve["datatypes"]:
        print(j2_template.render(isa=isa_sve,sve_size=sve_size,isa_datatype=isa_sve["datatypes"][dt], datatype=datatypes[dt]), file=file)

    template = """typedef struct { fixed_{{ sve_size }}_bool_t m; } rvm_{{ isa.name }}_{{ datatype.category }}{{ datatype.n_bits }}_t;"""
    j2_template = Template(template, undefined=StrictUndefined)
    for dt in isa_sve["datatypes"]:
        print(j2_template.render(isa=isa_sve,sve_size=sve_size,isa_datatype=isa_sve["datatypes"][dt], datatype=datatypes[dt]), file=file)

def gen_mipp_sve(include_manager=None):
    for iemu in implems_emu_sve:
        for sub_iemu in implems_emu_sve[iemu]:
            if "type" not in sub_iemu:
                sub_iemu["type"] = "emulated"

    import os
    os.makedirs("../include/simd_ext/sve", exist_ok=True)
    file = open("../include/simd_ext/sve/mipp_impl_sve_gen.h", "w")
    
    print("#if "+isa_sve["define"], file=file)
    
    all_sve_sizes = sorted(isa_sve["size"], reverse=True)
    for index, sve_size in enumerate(all_sve_sizes):
        if index == 0:
            print("#if __ARM_FEATURE_SVE_BITS == "+ str(sve_size), file=file)
        else:
            print("#elif __ARM_FEATURE_SVE_BITS == "+ str(sve_size), file=file)
        #print("#define DEFAULT_ARM_SVE_"+ str(sve_size), file=file)
        # include lower size implems
        #for sub_size in all_sve_sizes[index:]:
        print("#include \"mipp_impl_sve"+str(sve_size)+"_gen.h\"", file=file)
        #for sub_size in all_sve_sizes[index:]:
        print("#define MIPP_SVE_"+str(sve_size), file=file)
    
    template = """#else
#error Only -msve-vector-bits = {{all_sve_sizes}} is supported)
#endif
#endif"""
    j2_template = Template(template, undefined=StrictUndefined)
    print(j2_template.render(all_sve_sizes=str(all_sve_sizes)), file=file)
    
    file.close()
    
    
    ref_isa_name = isa_sve["name"]
    
    for current_sve_size in all_sve_sizes:
        
        isa_sve["name"] = ref_isa_name+str(current_sve_size)
        isa_sve["size"] = current_sve_size
        
        file = open("../include/simd_ext/sve/mipp_impl_sve"+str(current_sve_size)+"_gen.h", "w")
        
        tpl_header_sve = """#ifndef MY_INTRINSICS_PLUS_PLUS_IMPL_GEN_SVE{{ sve_size }}_H_
#define MY_INTRINSICS_PLUS_PLUS_IMPL_GEN_SVE{{ sve_size }}_H_
#if {{sve_define}}
#include <arm_sve.h>"""
        j2_template = Template(tpl_header_sve, undefined=StrictUndefined)
        print(j2_template.render(sve_size=current_sve_size, sve_define=isa_sve["define"]), file=file)# better take value isa_sve size
        
        gen_c_defines_sve_ls(file, ref_isa_name, current_sve_size)
        gen_c_structures_sve_ls(file, current_sve_size)
        
        copy_mipp_funcs = copy.deepcopy(mipp_funcs)
        
        gen_c_functions(isa_sve, file, copy_mipp_funcs, implems_sve)
        gen_c_functions(isa_sve, file, copy_mipp_funcs, implems_emu_sve)
        
        gen_c_missing_functions(isa_sve, file, copy_mipp_funcs)

        tpl_footer_sve = """#endif /* {{ sve_define }} */
#endif /* MY_INTRINSICS_PLUS_PLUS_IMPL_GEN_SVE{{ sve_size }}_H_ */"""
        j2_template = Template(tpl_footer_sve, undefined=StrictUndefined)
        print(j2_template.render(sve_size=current_sve_size, sve_define=isa_sve["define"]), file=file)

        file.close()
        
    isa_sve["name"] = ref_isa_name 
    isa_sve["size"] = all_sve_sizes
