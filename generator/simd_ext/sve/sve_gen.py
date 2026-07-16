from jinja2 import Template, StrictUndefined
import json

from tools import *
from registry import *
sve_isa, sve_native_implems, sve_emu_implems = load_isa_config("sve")
from c_generator import *

from include_gen import IncludeManager

def gen_c_defines_sve_ls(file, isa_name, sve_size):
    print("#define MIPP_" + isa_name.upper() + str(sve_size) + "_RVD_SIZE_BIT " + str(sve_size), file=file)
    print("#define MIPP_" + isa_name.upper() + str(sve_size) + "_RVD_SIZE_BYTE " + str(int(sve_size / 8)), file=file)
    template = """#define MIPP_SVE{{sve_size}}_N_{{type_category_upper}}{{n_bits}} {{type_size}}"""
    j2_template = Template(template, undefined=StrictUndefined)
    for dt in sve_isa["datatypes"]:
        n_bits=datatypes[dt]["n_bits"]
        print(j2_template.render(sve_size=sve_size, n_bits=n_bits, type_size = int(sve_size/n_bits), type_category_upper=datatypes[dt]["category"].upper()), file=file)
    

def gen_c_structures_sve_ls(file, sve_size):
    template = """typedef {{ isa_datatype.reg }} fixed_{{ sve_size }}_{{isa_datatype.to_ptr}} __attribute__((arm_sve_vector_bits({{ sve_size }})));"""
    j2_template = Template(template, undefined=StrictUndefined)
    for dt in sve_isa["datatypes"]:
        print(j2_template.render(isa_datatype=sve_isa["datatypes"][dt],sve_size=sve_size), file=file)
        
    template = """typedef svbool_t fixed_{{sve_size}}_bool_t __attribute__((arm_sve_vector_bits({{sve_size}})));"""
    j2_template = Template(template, undefined=StrictUndefined)
    print(j2_template.render(sve_size=sve_size), file=file)
    
    template = """typedef struct { fixed_{{ sve_size }}_{{isa_datatype.to_ptr }} r; } rvd_{{ isa.name }}_{{ datatype.category }}{{ datatype.n_bits }}_t;"""
    j2_template = Template(template, undefined=StrictUndefined)
    for dt in sve_isa["datatypes"]:
        print(j2_template.render(isa=sve_isa,sve_size=sve_size,isa_datatype=sve_isa["datatypes"][dt], datatype=datatypes[dt]), file=file)

    template = """typedef struct { fixed_{{ sve_size }}_bool_t m; } rvm_{{ isa.name }}_{{ datatype.category }}{{ datatype.n_bits }}_t;"""
    j2_template = Template(template, undefined=StrictUndefined)
    for dt in sve_isa["datatypes"]:
        print(j2_template.render(isa=sve_isa,sve_size=sve_size,isa_datatype=sve_isa["datatypes"][dt], datatype=datatypes[dt]), file=file)

def sve_gen(include_manager=None):
    for iemu in sve_emu_implems:
        for sub_iemu in sve_emu_implems[iemu]:
            if "type" not in sub_iemu:
                sub_iemu["type"] = "emulated"

    import os
    os.makedirs("../include/simd_ext/sve", exist_ok=True)
    file = open("../include/simd_ext/sve/mipp_impl_sve_gen.h", "w")
    
    print("#if "+sve_isa["define"], file=file)
    
    all_sve_sizes = sorted(sve_isa["size"], reverse=True)
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
    
    
    ref_isa_name = sve_isa["name"]
    
    for current_sve_size in all_sve_sizes:
        
        sve_isa["name"] = ref_isa_name+str(current_sve_size)
        sve_isa["size"] = current_sve_size
        
        file = open("../include/simd_ext/sve/mipp_impl_sve"+str(current_sve_size)+"_gen.h", "w")
        
        tpl_header_sve = """#ifndef MY_INTRINSICS_PLUS_PLUS_IMPL_GEN_SVE{{ sve_size }}_H_
#define MY_INTRINSICS_PLUS_PLUS_IMPL_GEN_SVE{{ sve_size }}_H_
#if {{sve_define}}
#include <arm_sve.h>"""
        j2_template = Template(tpl_header_sve, undefined=StrictUndefined)
        print(j2_template.render(sve_size=current_sve_size, sve_define=sve_isa["define"]), file=file)# better take value sve_isa size
        
        gen_c_defines_sve_ls(file, ref_isa_name, current_sve_size)
        gen_c_structures_sve_ls(file, current_sve_size)
        
        copy_interfaces = copy.deepcopy(interfaces)
        
        gen_c_functions(sve_isa, file, copy_interfaces, sve_native_implems)
        gen_c_functions(sve_isa, file, copy_interfaces, sve_emu_implems)
        
        gen_c_missing_functions(sve_isa, file, copy_interfaces)

        tpl_footer_sve = """#endif /* {{ sve_define }} */
#endif /* MY_INTRINSICS_PLUS_PLUS_IMPL_GEN_SVE{{ sve_size }}_H_ */"""
        j2_template = Template(tpl_footer_sve, undefined=StrictUndefined)
        print(j2_template.render(sve_size=current_sve_size, sve_define=sve_isa["define"]), file=file)

        file.close()
        
    sve_isa["name"] = ref_isa_name 
    sve_isa["size"] = all_sve_sizes
