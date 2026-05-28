from jinja2 import Template, StrictUndefined
import json
import re

from tools import *
from headers_def import *
from include_gen import IncludeManager
from ci_generator import duplicate_isa_sve_along_size


# -------------------------------------------------------------------------------------------------
# Exported functions
# -------------------------------------------------------------------------------------------------

def generate_mipp_hpp(include_manager=None):
    file = open("../include/mipp.hpp", "w")

    content = "#pragma once\n"
    content += '#include "cpp/common.hpp"\n'
    for func in mipp_funcs:
        content += f'#include "cpp/functions/{func}.hpp"\n'
    print(content, file=file)

def generate_cpp(include_manager=None, isa_list=None):
    file_common = include_manager.get_fd("cpp", "common")

    tpl_header_cpp = """#ifndef MY_INTRINSICS_PLUS_PLUS_HPP_
#define MY_INTRINSICS_PLUS_PLUS_HPP_

// #include "mipp.h"
#include "c/common.h"
#include "simd_ext/scalar/scalar_common.h"
#include <iostream>

namespace mipp
{

typedef double float64_t;
typedef float float32_t;    
"""

    j2_template = Template(tpl_header_cpp, undefined=StrictUndefined)
    print(j2_template.render(), file=file_common)

    gen_cpp_structures(file_common)
    gen_cpp_constexpr_functions(file_common)
 
    tpl_footer_cpp = """}

#endif /* MY_INTRINSICS_PLUS_PLUS_HPP_ */"""
    j2_template = Template(tpl_footer_cpp, undefined=StrictUndefined)
    print(j2_template.render(), file=file_common)
 



    for isa in isa_list:
        file_isa_common = include_manager.get_fd(isa["name"] + "_cpp", "common")
        gen_cpp_structures_isa(file_isa_common, isa)
        gen_cpp_constexpr_functions_isa(file_isa_common, isa)
        gen_cpp_functions_isa(include_manager, isa, mipp_funcs)
        include_manager.move_to_new_dir("simd_ext_cpp", [isa["name"] + "_cpp"])
    
    # definition of the enum used by everyone in cpp layer
    file_isa_enum = open("../include/simd_ext_cpp/isa_enum.hpp", "w")
    print("#pragma once\n", file=file_isa_enum)
    print("namespace mipp {\n", file=file_isa_enum)
    print("enum ISA { SCALAR, SSE, AVX, AVX512, NEON, SVE, RVV };", file=file_isa_enum)
    print("enum MKIND { NO, M, Z, S }; //mask enum for function templates", file=file_isa_enum)

    isa_list_copy = duplicate_isa_sve_along_size(isa_list) # this is the function that sets the gen_define key for every ISAs for some reason

    for index, isa in enumerate(isa_list_copy):
        if isa["name"].startswith("sve"): # idk about sve
            continue
        if index == 0:
            print("#if " + isa["gen_define"], file=file_isa_enum)
        else:
            print("#elif " + isa["gen_define"], file=file_isa_enum)
        print(f"inline constexpr ISA DEFAULT_ISA = ISA::{isa["name"].upper()};", file=file_isa_enum)
    print("#else\n#error \"No ISA defined for cpp wrapper\"\n#endif", file=file_isa_enum)

    print("template<typename T, int LMUL=1, ISA ISA_TYPE=DEFAULT_ISA> struct rvd_type{};", file=file_isa_enum)
    print("template<typename T, int LMUL=1, ISA ISA_TYPE=DEFAULT_ISA> struct rvm_type{};", file=file_isa_enum)
    # print("template<typename T, int LMUL=1, ISA ISA_TYPE=DEFAULT_ISA> using rvd = typename rvd_type<T,LMUL,ISA_TYPE>::type;", file=file_isa_enum)
    # print("template<typename T, int LMUL=1, ISA ISA_TYPE=DEFAULT_ISA> using rvm = typename rvm_type<T,LMUL,ISA_TYPE>::type;", file=file_isa_enum)
    print("template<typename T, int LMUL=1, ISA ISA_TYPE=DEFAULT_ISA> constexpr uint32_t N(){ return 0; }", file=file_isa_enum)

    print("}\n", file=file_isa_enum)

    gen_cpp_functions(include_manager, copy_mipp_funcs)    
    generate_mipp_hpp(include_manager)

def gen_cpp_structures(file):
    # glue file similar to ci generator but for cpp layer, it will define the rvd and rvm templates for the generic cpp layer (not isa-specific)
    # template = """template<> struct rvd_type<{{ datatype.cstd }}, {{ lmul }}, ISA::DEFAULT>{ using type = rvd_{{ datatype.category }}{{ datatype.n_bits }}_m{{ lmul }}_t; };"""
    # j2_template = Template(template, undefined=StrictUndefined)
    # for lmul in all_lmul:
    #     for dt in datatypes:
    #         print(j2_template.render(datatype=datatypes[dt], lmul=str(lmul)), file=file)

    # for index, isa in enumerate(isa_list):
    #     if index == 0:
    #         print("#if " + isa["gen_define"], file=file)
    #     else:
    #         print("#elif " + isa["gen_define"], file=file)
        
    #     template = 
    return 0

def gen_cpp_constexpr_functions(file):
    print("// should throw an exception", file=file)
    print("template<typename T, int LMUL=1, ISA ISA_TYPE=ISA::DEFAULT> constexpr uint32_t N(){ return 0; }", file=file)

    template = """template<> constexpr uint32_t N<{{ datatype.cstd }}, {{ lmul }}>(){ return MIPP_N_{{type_category_upper}}{{ datatype.n_bits }}{{ lmul_suffix }}; }"""
    j2_template = Template(template, undefined=StrictUndefined)
    for lmul in all_lmul:
        if lmul == 1:
            lmul_suffix = ""
        else:
            lmul_suffix = "_M" + str(lmul)
        for dt in datatypes:
            print(j2_template.render(datatype=datatypes[dt], lmul=str(lmul), type_category_upper=datatypes[dt]["category"].upper(), lmul_suffix=lmul_suffix), file=file)

    # template = """template<> constexpr uint32_t N<{{ datatype.cstd }}, -{{ ldiv }}>(){ return MIPP_N_{{type_category_upper}}{{ datatype.n_bits }}{{ ldiv_suffix }}; }"""
    # j2_template = Template(template, undefined=StrictUndefined)
    # for ldiv in all_ldiv:
    #     if ldiv == 1:
    #         ldiv_suffix = ""
    #     else:            
    #         ldiv_suffix = "_D" + str(ldiv)
    #     print("#if defined(MIPP_ENABLE_LDIV" + str(ldiv) + ")", file=file)
    #     for dt in datatypes:
    #         print(j2_template.render(datatype=datatypes[dt], ldiv=str(ldiv), type_category_upper=datatypes[dt]["category"].upper(), ldiv_suffix=ldiv_suffix), file=file)
    #     print("#endif // defined(MIPP_ENABLE_LDIV" + str(ldiv) + ")", file=file)
    
        # lmul constexpr for scalar 
    template = """template<> constexpr uint32_t N<{{ datatype.cstd }}, {{ lmul }}, ISA::SCALAR>(){ return MIPP_SCALAR_N_{{type_category_upper}}{{ datatype.n_bits }}{{ lmul_suffix }}; }"""
    j2_template = Template(template, undefined=StrictUndefined)
    for lmul in all_lmul:
        if lmul == 1:
            lmul_suffix = ""
        else:
            lmul_suffix = "_M" + str(lmul)
        for dt in datatypes:
            print(j2_template.render(datatype=datatypes[dt], lmul=str(lmul), type_category_upper=datatypes[dt]["category"].upper(), lmul_suffix=lmul_suffix), file=file)


def gen_cpp_functions(include_manager, funcs):
    set_functions = ["set0", "set0_k", "set", "set_k", "set1", "set1_k", "load", "loadu"]
    for f in funcs:
        
        file = include_manager.get_fd("cpp", f)
        prefix = _cpp_custom_prefix_generator(f)
        print(prefix, file=file)
        if "mask_support" in funcs[f] and funcs[f]["mask_support"] is not None:
                is_cast = f == "cast" or f == "cast_k"

                ms = funcs[f]["mask_support"]
                proto = funcs[f]["proto"]
                if (ms.is_maskable()) or (ms.is_maskzable()):
                    _generic_mask_decl(file, f, proto, "mask")
                if (ms.is_masksable()):
                    _generic_mask_decl(file, f, proto, "masks")

        if f in set_functions:
            gen_set_func_error(f, file)
                    
        for dt in funcs[f]["datatypes"]:
            is_cast = len(dt.split(',')) > 1

            if not is_cast:
                dt_par = dt.split(',')[0]
                dt_ret = dt.split(',')[0]
            else:
                dt_par = dt.split(',')[0]
                dt_ret = dt.split(',')[1]

            dt_key = dt_par + "," + dt_ret

            if not is_cast:
                c_func_name = build_func_name_short("", dt_par, f, False)
                c_scalar_func_name = build_func_name_short(isa_scalar, dt_par, f, True)
                cpp_func_name = build_cpp_func_name_short(funcs[f]["proto"], dt_ret, f)

            else:
                c_func_name = build_func_name("", dt_par, dt_ret, f, False)
                c_scalar_func_name = build_func_name(isa_scalar, dt_par, dt_ret, f, True)
                cpp_func_name = build_cpp_func_name(dt_ret, f)
    
            for lmul in all_lmul:
                print(build_proto(funcs[f]["proto"], dt_par, dt_ret, {}, cpp_func_name, lmul, False, True) + " {", file=file)
                print("\t" + build_call(funcs[f]["proto"], dt_par, dt_ret, "", c_func_name + "_m" + str(lmul), lmul, False) + ";", file=file)
                print("}", file=file)


                print(build_proto(funcs[f]["proto"], dt_par, dt_ret, isa_scalar, cpp_func_name, lmul, True, True) + " {", file=file)
                print("\t" + build_call(funcs[f]["proto"], dt_par, dt_ret, "", c_scalar_func_name + "_m" + str(lmul), lmul, True) + ";", file=file)
                print("}", file=file)

            # for ldiv in all_ldiv:
            #     print("#if defined(MIPP_ENABLE_LDIV" + str(ldiv) + ")", file=file)
            #     print(build_proto(funcs[f]["proto"], dt_par, dt_ret, {}, cpp_func_name, -ldiv, False, True) + " {", file=file)
            #     print("\t" + build_call(funcs[f]["proto"], dt_par, dt_ret, "", c_func_name + "_d" + str(ldiv), lmul, False) + ";", file=file)
            #     print("}", file=file)
            #     print("#endif // defined(MIPP_ENABLE_LDIV" + str(ldiv) + ")", file=file)


            if is_cast:
                continue

            if "mask_support" not in funcs[f] or funcs[f]["mask_support"] is None:
                continue
            ms = funcs[f]["mask_support"]

            if (not ms.is_maskable()) and (not ms.is_maskzable()) and (not ms.is_masksable()):
                continue

            proto = funcs[f]["proto"]
            c_base = _masked_c_symbol(dt_par, dt_ret, f, is_cast=False)

            for lmul in all_lmul:
                if ms.is_maskable():
                    _mask_tpl_spec(file, proto, dt_par, dt_ret, cpp_func_name, c_base, "M", "mask",lmul=lmul)
                if ms.is_maskzable():
                    _mask_tpl_spec(file, proto, dt_par, dt_ret, cpp_func_name, c_base, "Z", "maskz",lmul=lmul)
                if ms.is_masksable():
                    _mask_tpl_spec(file, proto, dt_par, dt_ret, cpp_func_name, c_base, "S", "masks",lmul=lmul)
        print(_cpp_close_namespace(), file=file)


# -------------------------------------------------------------------------------------------------
# Helpers
# -------------------------------------------------------------------------------------------------

# will be changed dtl
def _cpp_custom_prefix_generator(func,isa_name=""):
    """
    include c_mipp version of the function + set namespace to mipp for the cpp wrapper.
    """
    s = "#pragma once\n"

    if isa_name:
        if func is None: # common file
            s += f'#include "../../simd_ext/{isa_name}/{isa_name}_common.h"\n'
            s+= f'#include "../isa_enum.hpp"\n'
        if func is not None: # function file
            s += f'#include "../{isa_name}_cpp_common.hpp"\n'
            s += f'#include "../../simd_ext/{isa_name}/functions/{isa_name}_{func}.h"\n'
        #s += f'#include "../../simd_ext/scalar/functions/scalar_{func}.h"\n'

    else: 
        s += f'#include "../{isa_name}common.hpp"\n'
        s += f'#include "../../c/functions/{func}.h"\n'
        s+= f'#include "../../simd_ext/scalar/functions/scalar_{func}.h"\n'
    s += "namespace mipp {\n"
    return s

# maybe there is such thing as too much helpers tbh
def _cpp_close_namespace():
    return "}\n"



# -------------------------------------------------------------------------------------------------
# Masked C++ wrappers (proto-driven: correct names m0/rsrc/r0..., correct arity)
# -------------------------------------------------------------------------------------------------
def _masked_c_symbol(dt_par, dt_ret, f, is_cast, isa=None, isa_name=False):
    # Base C symbol without lmul suffix.
    if not is_cast:
        return build_func_name_short(isa, dt_par, f, isa_name=isa_name)
    return build_func_name(isa, dt_par, dt_ret, f, isa_name=isa_name)


def _tpl_scalar_for_arg(arg):
        # Returns a string type name usable in C++ template decls: "T" or "int32_t" etc.
    if arg.get("fixeddatatype"):
        return datatypes[arg["fixeddatatype"]]["cstd"]
    return "T"

def _generic_mask_decl(file, cpp_func_name, proto, mask_kind):
    """
    Emit a generic template declaration with correct *names* (m0/rsrc/r0/v0/p0...),
    but *types* expressed in terms of T and LMUL.

    mask_kind:
      - "mask" / "maskz": prepend 'rvm<T,LMUL> m0'
      - "masks": prepend 'const rvm<T,LMUL> m0, rvd<T,LMUL> rsrc'
    """
    # Template header differs for S because default MK differs.
    if mask_kind in ("mask", "maskz"):
        print("template <MKIND MK=M, typename T, int LMUL=1>", file=file)
    else:
        print("template <MKIND MK=S, typename T, int LMUL=1>", file=file)

    # Return type: generic on T,LMUL (only valid for non-cast funcs; you already skip casts)
    ret = "inline " + ("rvd<T,LMUL>" if proto["ret"]["type"] == "reg" else
                      "rvm<T,LMUL>" if proto["ret"]["type"] == "msk" else
                      "T" if proto["ret"]["type"] == "val" else
                      "void")

    s = f"{ret} {cpp_func_name}("

    is_first = True
    cnt_reg = 0
    cnt_msk = 0
    cnt_val = 0
    cnt_ptr = 0

    # masked prefix args (names must match build_call expectations)
    if mask_kind in ("mask", "maskz"):
        s += "rvm<T,LMUL> m0"
        is_first = False
    elif mask_kind == "masks":
        s += "const rvm<T,LMUL> m0, rvd<T,LMUL> rsrc"
        is_first = False

    for arg in proto["args"]:
        if not is_first:
            s += ", "
        if arg["charac"] == "RO":
            s += "const "

        # decide the scalar type for this argument
        A = _tpl_scalar_for_arg(arg)

        if arg["type"] == "reg":
            s += f"rvd<{A},LMUL> r{cnt_reg}"
            cnt_reg += 1
        elif arg["type"] == "msk":
            s += f"rvm<{A},LMUL> m{cnt_msk}"
            cnt_msk += 1
        elif arg["type"] == "val":
            s += f"{A} v{cnt_val}"
            cnt_val += 1
        elif arg["type"] == "ptr":
            s += f"{A}* p{cnt_ptr}"
            cnt_ptr += 1
        elif arg["type"] == "Nele":
            s += f"{A} vals[N<{A},LMUL>()]"
        elif arg["type"] == "vindex":
            s += "rvd<int32_t,LMUL> vi"
        else:
            s += "void* _"

        is_first = False
    s += ");" + "\n"
    if cpp_func_name == "loadu":
            print(s)
    print(s, file=file)


def _mask_tpl_spec(file, proto, dt_par, dt_ret, cpp_func_name, c_base, mk_letter, mask_kind, lmul=1, isa=None, isa_name=False):
    """
    Emit explicit specialization for masked template for a given LMUL.

    Example (storeu, uint32_t, LMUL=2):
      template <>
      inline void storeu<M, uint32_t, 2>(rvm<uint32_t,2> m0, uint32_t* p0, const rvd<uint32_t,2> r0) {
          mipp_storeu_uint32_mask_m2(m0, p0, r0);
      }
    """
    Tret = datatypes[dt_ret]["cstd"]

    print("template <>", file=file)

    # Build the masked signature at the right LMUL, then rewrite the name into the template-id form.
    sig = build_proto(proto, dt_par, dt_ret, isa, cpp_func_name, lmul, isa_name=isa_name, cpp=True, masked_version=mask_kind)
    sig = sig.replace(
        f"{cpp_func_name}_{mask_kind}(",
        f"{cpp_func_name}<{mk_letter}, {Tret}, {lmul}>("
    )
    print(sig + " {", file=file)

    # C masked symbol naming:
    # - if your C layer has no _m1 for masked: use base for LMUL=1, and add _mX for LMUL>1
    # - if it DOES have _m1 too, change this to always suffix.
    if int(lmul) == 1:
        c_symbol = f"{c_base}_{mask_kind}"
    else:
        c_symbol = f"{c_base}_{mask_kind}_m{int(lmul)}"

    call = build_call(proto, dt_par, dt_ret, isa, c_symbol, lmul, isa_name=isa_name, masked_version=mask_kind)
    print("\t" + call + ";", file=file)
    print("}", file=file)


# -------------------------------------------------------------------------------------------------
# CPP REWORK WIP !!!
# -------------------------------------------------------------------------------------------------


# regular cpp functions r overloads HOWEVER masked functions r template specialization 
# so we want to define the generic template in a single place n then specialize them in every header 
# the idea is to have a directory called simd_ext_cpp/templates n put the generic templates in there
# n then include them to every isa header and specialize them there with the correct types and names
def gen_cpp_generic_templates(file):
    print("Hello gen_cpp_generic_templates I'm a wip function that will generate the generic templates for masked functions")
    print("Now I'll stop ur generator sry ;o")
    exit(1)

def gen_cpp_structures_isa(file, isa):

    isa_cpp_type = isa["name"].upper()
    isa_c_name = isa["name"].lower()


    print(_cpp_custom_prefix_generator(None, isa["name"]), file=file)

    template = """template<> struct rvd_type<{{ datatype.cstd }}, {{ lmul }}, ISA::{{isa_cpp_type}}>{ using type = rvd_{{isa_c_name}}_{{ datatype.category }}{{ datatype.n_bits }}_m{{ lmul }}_t; };"""
    j2_template = Template(template, undefined=StrictUndefined)
    for lmul in all_lmul:
        for dt in datatypes:
            print(j2_template.render(datatype=datatypes[dt], lmul=str(lmul), isa_cpp_type=isa_cpp_type, isa_c_name=isa_c_name), file=file)

    print(f"template <typename T, int LMUL=1, ISA ISA_TYPE=ISA::{isa_cpp_type}> using rvd = typename rvd_type<T,LMUL,ISA_TYPE>::type;", file=file)

    print(f"template<typename T, int LMUL=1, ISA ISA_TYPE=ISA::{isa_cpp_type}> struct rvm_type{{}};", file=file)

    template = """template<> struct rvm_type<{{ datatype.cstd }}, {{ lmul }}, ISA::{{isa_cpp_type}}>{ using type = rvm_{{isa_c_name}}_{{ datatype.category }}{{ datatype.n_bits }}_m{{ lmul }}_t; };"""
    j2_template = Template(template, undefined=StrictUndefined)
    for lmul in all_lmul:
        for dt in datatypes:
            print(j2_template.render(datatype=datatypes[dt], lmul=str(lmul), isa_cpp_type=isa_cpp_type, isa_c_name=isa_c_name), file=file)

    print(f"template <typename T, int LMUL=1, ISA ISA_TYPE=ISA::{isa_cpp_type}> using rvm = typename rvm_type<T,LMUL,ISA_TYPE>::type;", file=file)
    # maybe enum shouldn't be defined here idk

def gen_cpp_constexpr_functions_isa(file, isa):
    isa_cpp_type = isa["name"].upper()
    print("// should throw an exception", file=file)

    print("template<typename T, int LMUL=1, ISA ISA_TYPE=ISA::" + isa_cpp_type + "> constexpr uint32_t N(){ return 0; }", file=file)

    template = """template<> constexpr uint32_t N<{{ datatype.cstd }}, {{ lmul }}, ISA::{{isa_cpp_type}} >(){ return MIPP_{{isa_cpp_type}}_N_{{type_category_upper}}{{ datatype.n_bits }}{{ lmul_suffix }}; }"""
    j2_template = Template(template, undefined=StrictUndefined)
    for lmul in all_lmul:
        if lmul == 1:
            lmul_suffix = ""
        else:
            lmul_suffix = "_M" + str(lmul)
        for dt in datatypes:
            print(j2_template.render(datatype=datatypes[dt], lmul=str(lmul), type_category_upper=datatypes[dt]["category"].upper(), lmul_suffix=lmul_suffix, isa_cpp_type=isa_cpp_type), file=file)
    
    print(_cpp_close_namespace(), file=file) # hacky -> implies it HAS to be called after gen_cpp_structures_isa ...

def gen_cpp_functions_isa(include_manager, isa, funcs):
    layer_name = isa["name"] + "_cpp"
    for f in funcs:

        file = include_manager.get_fd(layer_name, f)
        prefix = _cpp_custom_prefix_generator(f, isa["name"])
        print(prefix, file=file)

        for dt in funcs[f]["datatypes"]:
            is_cast = len(dt.split(',')) > 1

            if not is_cast:
                dt_par = dt.split(',')[0]
                dt_ret = dt.split(',')[0]
            else:
                dt_par = dt.split(',')[0]
                dt_ret = dt.split(',')[1]

            if not is_cast:
                c_func_name = build_func_name_short(isa, dt_par, f, isa_name=True)
                cpp_func_name = build_cpp_func_name_short(funcs[f]["proto"], dt_ret, f)

            else:
                c_func_name = build_func_name(isa, dt_par, dt_ret, f, isa_name=True)
                cpp_func_name = build_cpp_func_name(dt_ret, f)

            # print(build_proto(funcs[f]["proto"], dt_par, dt_ret, isa, cpp_func_name, lmul=0, isa_name=True, cpp=True, masked_version=False) + " {", file=file)
            # print("\t" + build_call(funcs[f]["proto"], dt_par, dt_ret, "", c_func_name, lmul=0, isa_name=True) + ";", file=file)
            # print("}", file=file)

            for lmul in all_lmul:
                print(build_proto(funcs[f]["proto"], dt_par, dt_ret, isa, cpp_func_name, lmul, isa_name=True, cpp=True) + " {", file=file)
                print("\t" + build_call(funcs[f]["proto"], dt_par, dt_ret, "", c_func_name + "_m" + str(lmul), lmul, False) + ";", file=file)
                print("}", file=file)
            # mask_status = funcs[f]["mask_support"]
            # if mask_status and (mask_status.is_maskable() or mask_status.is_maskzable() or mask_status.is_masksable()):
            #     proto = funcs[f]["proto"]
            #     c_base = _masked_c_symbol(dt_par, dt_ret, f, is_cast, isa=isa, isa_name=True)

            #     for lmul in all_lmul:
            #         if mask_status.is_maskable():
            #             _mask_tpl_spec(file, proto, dt_par, dt_ret, cpp_func_name, c_base, "M", "mask", lmul=lmul, isa = isa, isa_name=True)
            #         if mask_status.is_maskzable():
            #             _mask_tpl_spec(file, proto, dt_par, dt_ret, cpp_func_name, c_base, "Z", "maskz", lmul=lmul, isa = isa, isa_name=True)
            #         if mask_status.is_masksable():
            #             _mask_tpl_spec(file, proto, dt_par, dt_ret, cpp_func_name, c_base, "S", "masks", lmul=lmul, isa = isa, isa_name=True)

        print(_cpp_close_namespace(), file=file)