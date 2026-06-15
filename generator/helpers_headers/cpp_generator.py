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
    file_common = open("../include/simd_ext_cpp/common.hpp", "w")
    print("#pragma once\n", file=file_common)
    print("namespace mipp {\n", file=file_common)
    print("enum ISA { SCALAR, SSE, AVX, AVX512, NEON, SVE, RVV };", file=file_common)
    print("enum MKIND { NO, M, Z, S }; //mask enum for function templates", file=file_common)

    isa_list_copy = duplicate_isa_sve_along_size(isa_list) # this is the function that sets the gen_define key for every ISAs for some reason

    for index, isa in enumerate(isa_list_copy):
        if isa["name"].startswith("sve"): # idk about sve
            continue
        if index == 0:
            print("#if " + isa["gen_define"], file=file_common)
        else:
            print("#elif " + isa["gen_define"], file=file_common)
        print(f"// uh-oh technically UB", file=file_common)
        print(f"constexpr ISA DEFAULT_ISA = ISA::{isa["name"].upper()};", file=file_common)
    print("#else\n#error \"No ISA defined for cpp wrapper\"\n#endif", file=file_common)

    print("template<typename T, int LMUL=1, ISA ISA_TYPE=DEFAULT_ISA> struct rvd_type{};", file=file_common)
    print("template<typename T, int LMUL=1, ISA ISA_TYPE=DEFAULT_ISA> struct rvm_type{};", file=file_common)
    print("template<typename T, int LMUL=1, ISA ISA_TYPE=DEFAULT_ISA> using rvd = typename rvd_type<T,LMUL,ISA_TYPE>::type;", file=file_common)
    print("template<typename T, int LMUL=1, ISA ISA_TYPE=DEFAULT_ISA> using rvm = typename rvm_type<T,LMUL,ISA_TYPE>::type;", file=file_common)
    print("template<typename T, int LMUL=1, ISA ISA_TYPE=DEFAULT_ISA> constexpr uint32_t N(){ return 0; }", file=file_common)
    print("template<ISA ISA_TYPE=DEFAULT_ISA> constexpr uint32_t rvd_sz_bits(){ return 0; }", file=file_common)
    print("template<ISA ISA_TYPE=DEFAULT_ISA> constexpr uint32_t rvd_sz_bytes(){ return 0; }", file=file_common)
    print("template<ISA ISA_TYPE=DEFAULT_ISA> constexpr uint32_t req_alignment(){ return 0; }", file=file_common)

    print("}\n", file=file_common)
    file_common.close()

    gen_cpp_generic_templates(include_manager, isa_list_copy, mipp_funcs)
    include_manager.move_to_new_dir("simd_ext_cpp", ["templates"])
    
    file_common_glue = include_manager.get_fd("cpp", "common")
    gen_cpp_common(isa_list_copy, file_common_glue)
    gen_cpp_functions(isa_list_copy, include_manager, copy_mipp_funcs)    
    generate_mipp_hpp(include_manager)

def gen_cpp_common(isa_list, file):
    # glue file similar to ci generator's way of generating c/common.h but for cpp layer. I don't think it needs to redefine anything, just include stuff.
    print("#pragma once\n", file=file)
    for index, isa in enumerate(isa_list):
        if index == 0:
            print("#if " + isa["gen_define"], file=file)
        else:
            print("#elif " + isa["gen_define"], file=file)
        
        print(f'#include "../simd_ext_cpp/{isa["name"].lower()}_cpp/{isa["name"].lower()}_cpp_common.hpp"\n', file=file)
    print("#else\n#error \"No ISA defined for cpp wrapper\"\n#endif", file=file)

def gen_cpp_functions(isa_list, include_manager, funcs):
    for f in funcs.keys():
        file = include_manager.get_fd("cpp", f)
        print("#pragma once\n", file=file)
        print('#include "../common.hpp"\n', file=file)
        for index, isa in enumerate(isa_list):
            if index == 0:
                print("#if " + isa["gen_define"], file=file)
            else:
                print("#elif " + isa["gen_define"], file=file)
            print(f'#include "../../simd_ext_cpp/{isa["name"].lower()}_cpp/functions/{isa["name"].lower()}_cpp_{f}.hpp"\n', file=file)
        print("#else\n#error \"No ISA defined for cpp wrapper\"\n#endif", file=file)

# -------------------------------------------------------------------------------------------------
# Helpers
# -------------------------------------------------------------------------------------------------

set_functions = ["set0", "set0_k", "set", "set_k", "set1", "set1_k", "load", "loadu"]


# duplicate of c_generator ...
def _compute_dt_par_dt_ret(funcs, f, dt):
    """
    returns dt_par and dt_ret based on dt.  len(dt.split(',')) > 1 for cast and cast_k 
    """
    # Returns (dt_par, dt_ret) or exits on unsupported type (same behavior as original).
    if len(dt.split(',')) <= 1:
        dt_par = dt.split(',')[0]
        dt_ret = dt.split(',')[0]
        if dt_par not in funcs[f]["datatypes"]:
            print("Panic: unsupported type for '" + f + "<" + dt_par + "," + dt_par + ">' function.")
            exit(-1)
    else:
        dt_par = dt.split(',')[0]
        dt_ret = dt.split(',')[1]

        dtk = dt_par + "," + dt_ret
        if dtk not in funcs[f]["datatypes"]:
            print("Panic: unsupported type for '" + f + "<" + dt_par + "," + dt_ret + ">' function.")
            exit(-1)

    return dt_par, dt_ret

def _cpp_custom_prefix_generator(f,isa_name="", funcs=None):
    """
    include c_mipp version of the function + set namespace to mipp for the cpp wrapper.
    """
    s = "#pragma once\n"

    if isa_name:
        if f is None: # common file
            s += f'#include "../common.hpp"\n'
            s += f'#include "../../simd_ext/{isa_name}/{isa_name}_common.h"\n'
        
        if f is not None: # function file
            s += f'#include "../{isa_name}_cpp_common.hpp"\n'
            s += f'#include "../../../simd_ext/{isa_name}/functions/{isa_name}_{f}.h"\n'

            masks_support = None
            if funcs is not None:
                mask_support = funcs[f]["mask_support"]
            
            if f in set_functions:
                 s+= f'#include "../../templates/functions/templates_{f}.hpp"\n'
            elif mask_support and mask_support.is_any_mask():
                s+= f'#include "../../templates/functions/templates_{f}.hpp"\n'
                # include the template 

    else: 
        s += f'#include "../{isa_name}common.hpp"\n'
        s += f'#include "../../c/functions/{f}.h"\n'
        s+= f'#include "../../simd_ext/scalar/functions/scalar_{f}.h"\n'
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

def _get_dt_par_size(dt_par):
    if dt_par in datatypes:
        return datatypes[dt_par]["n_bits"]
    else:
        print(f"error: data type {dt_par} not found in datatypes")
        exit(-1)

def _tpl_scalar_for_arg(arg):
    # Returns a string type name usable in C++ template decls: "T" or "int32_t" etc.
    if arg.get("fixeddatatype"):
        if arg["fixeddatatype"] not in datatypes and arg["fixeddatatype"] in all_categories:
                return "U"
        elif arg["fixeddatatype"] in datatypes:
                realdatatype = datatypes[arg["fixeddatatype"]]
                return realdatatype["cstd"]
       # return datatypes[arg["fixeddatatype"]]["cstd"]
    return "T"

def _generic_mask_decl_gather_scatter(file, cpp_func_name, proto, mask_kind):

    if mask_kind == "mask" or mask_kind == "maskz":
        ret = "template <MKIND MK=M, typename T, typename U,int LMUL=1, ISA ISA_TYPE=DEFAULT_ISA>"
    else:
        ret = "template <MKIND MK=S, typename T, typename U,int LMUL=1, ISA ISA_TYPE=DEFAULT_ISA>"

    ret += "inline " + ("rvd<T,LMUL,ISA_TYPE>" if proto["ret"]["type"] == "reg" else
                      "rvm<T,LMUL,ISA_TYPE>" if proto["ret"]["type"] == "msk" else
                      "T" if proto["ret"]["type"] == "val" else
                      "void")
    s = "{{ret}} {{cpp_func_name}}("

    is_first = True
    cnt_reg = 0
    cnt_msk = 0
    cnt_val = 0
    cnt_ptr = 0

    if mask_kind in ("mask", "maskz"):
        s += "rvm<U,LMUL,ISA_TYPE> m0"
        is_first = False
    elif mask_kind == "masks":
        s += "const rvm<U,LMUL,ISA_TYPE> m0, rvd<T,LMUL,ISA_TYPE> rsrc"
        is_first = False
    for args in proto["args"]:

        tmp_str = ""
        if not is_first:
            tmp_str += ", "
        if args["charac"] == "RO":
            tmp_str += "const "

        A = _tpl_scalar_for_arg(args)

        if args["type"] == "reg":
            tmp_str += "rvd<{{A}},LMUL,ISA_TYPE> r" + str(cnt_reg)
            cnt_reg += 1
        elif args["type"] == "msk":
            tmp_str += "rvm<{{A}},LMUL,ISA_TYPE> m" + str(cnt_msk)
            cnt_msk += 1
        elif args["type"] == "val":
            tmp_str += "{{A}} v" + str(cnt_val)
            cnt_val += 1
        elif args["type"] == "ptr":
            tmp_str += "T* p" + str(cnt_ptr)
            cnt_ptr += 1
        elif args["type"] == "Nele":
            tmp_str += "{{A}} vals[N<{{A}},LMUL,ISA_TYPE>()]"
        elif args["type"] == "vindex":
            tmp_str += "rvd<int32_t,LMUL,ISA_TYPE> vi"
        else:
            tmp_str += "void* _"

        tmp_template = Template(tmp_str, undefined=StrictUndefined)
        s += tmp_template.render(A=A) # render the current arg to update s for the next iteration (for correct comma placement and const keywords)

        is_first = False
    s += ");" + "\n"
    template = Template(s, undefined=StrictUndefined)
    # for dt in all_datatypes:
        # cpp_fname_dt = cpp_func_name
    tpl = template.render(cpp_func_name=cpp_func_name, ret=ret)
    print(tpl, file=file)

    #print(s, file=file)
    
def _generic_mask_decl(file, cpp_func_name, proto, mask_kind):
    """
    Emit a generic template declaration with correct *names* (m0/rsrc/r0/v0/p0...),
    but *types* expressed in terms of T and LMUL.

    mask_kind:
      - "mask" / "maskz": prepend 'rvm<T,LMUL> m0'
      - "masks": prepend 'const rvm<T,LMUL> m0, rvd<T,LMUL> rsrc'
    """

    if "gather" in cpp_func_name or "scatter" in cpp_func_name:
        return _generic_mask_decl_gather_scatter(file, cpp_func_name, proto, mask_kind)
    # Template header differs for S because default MK differs.
    if mask_kind in ("mask", "maskz"):
        print("template <MKIND MK=M, typename T, int LMUL=1, ISA ISA_TYPE=DEFAULT_ISA>", file=file)
    else:
        print("template <MKIND MK=S, typename T, int LMUL=1, ISA ISA_TYPE=DEFAULT_ISA>", file=file)

    # Return type: generic on T,LMUL (only valid for non-cast funcs; you already skip casts)
    ret = "inline " + ("rvd<T,LMUL,ISA_TYPE>" if proto["ret"]["type"] == "reg" else
                      "rvm<T,LMUL,ISA_TYPE>" if proto["ret"]["type"] == "msk" else
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
        s += "rvm<T,LMUL,ISA_TYPE> m0"
        is_first = False
    elif mask_kind == "masks":
        s += "const rvm<T,LMUL,ISA_TYPE> m0, rvd<T,LMUL,ISA_TYPE> rsrc"
        is_first = False

    for arg in proto["args"]:
        if not is_first:
            s += ", "
        if arg["charac"] == "RO":
            s += "const "

        # decide the scalar type for this argument
        A = _tpl_scalar_for_arg(arg)

        if arg["type"] == "reg":
            s += f"rvd<{A},LMUL,ISA_TYPE> r{cnt_reg}"
            cnt_reg += 1
        elif arg["type"] == "msk":
            s += f"rvm<{A},LMUL,ISA_TYPE> m{cnt_msk}"
            cnt_msk += 1
        elif arg["type"] == "val":
            s += f"{A} v{cnt_val}"
            cnt_val += 1
        elif arg["type"] == "ptr":
            s += f"{A}* p{cnt_ptr}"
            cnt_ptr += 1
        elif arg["type"] == "Nele":
            s += f"{A} vals[N<{A},LMUL,ISA_TYPE>()]"
        elif arg["type"] == "vindex":
            s += "rvd<int32_t,LMUL,ISA_TYPE> vi"
        else:
            s += "void* _"

        is_first = False
    s += ");" + "\n"

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


    if isa is not None:
        sig = sig.replace(
            f"{cpp_func_name}_{mask_kind}(",
            f"{cpp_func_name}<{mk_letter}, {Tret}, {lmul}, {isa["name"].upper()}>("
        )
    else :
        sig = sig.replace(
            f"{cpp_func_name}_{mask_kind}(",
            f"{cpp_func_name}<{mk_letter}, {Tret}, {lmul}>("
        )


    print(sig + " {", file=file)

    # # C masked symbol naming:
    # # - if your C layer has no _m1 for masked: use base for LMUL=1, and add _mX for LMUL>1
    # # - if it DOES have _m1 too, change this to always suffix.
    # if int(lmul) == 1:
    #     c_symbol = f"{c_base}_{mask_kind}"
    # else:
    lmul_str = "m" + str(lmul)
    if lmul < 0: 
        lmul_str = "d" + str(-lmul)
    c_symbol = f"{c_base}_{mask_kind}_{lmul_str}"

    call = build_call(proto, dt_par, dt_ret, isa, c_symbol, lmul, isa_name=isa_name, masked_version=mask_kind)
    print("\t" + call + ";", file=file)
    print("}", file=file)


# -------------------------------------------------------------------------------------------------
# CPP REWORK WIP :)
# -------------------------------------------------------------------------------------------------

# regular cpp functions r overloads HOWEVER masked functions r template specialization 
# n.b : functions in set_functions r also template specializations bc they don't have any register arguments 
#       so they can't really be overloaded ...
# so we want to define the generic template in a single place n then specialize them in every header 
# the idea is to have a directory called simd_ext_cpp/templates n put the generic templates in there
# n then include them to every isa header and specialize them there with the correct types and names
def gen_cpp_generic_templates(include_manager, isa, funcs):
    # this function will generate the generic template of every masked function in separate headers 4 each func
    for f in funcs:

        if ( f not in set_functions ) and ( "mask_support" not in funcs[f] or funcs[f]["mask_support"] is None ):
            continue
        file = include_manager.get_fd("templates", f)

        print("#pragma once\n", file=file)
        print('#include "../../common.hpp"\n', file=file)
        print("namespace mipp {\n", file=file)

        if f in set_functions:
            gen_set_func_error(f, file)

        ms = funcs[f]["mask_support"]
        proto = funcs[f]["proto"]

        dt_par, dr_ret = _compute_dt_par_dt_ret(funcs, f, funcs[f]["datatypes"][0]) # we just need one dt to build the template since it's generic on T
        cpp_func_name = build_cpp_func_name_short(funcs[f]["proto"], dt_par, f) # THIS IS A HACK BC build_cpp_func_name_short explodes w/o concrete type ...

        if ms.is_maskable() or ms.is_maskzable():
            _generic_mask_decl(file, cpp_func_name, proto, "mask")

        if ms.is_masksable():
            _generic_mask_decl(file, cpp_func_name, proto, "masks")

        print("}\n", file=file)
def gen_cpp_structures_isa(file, isa):

    isa_cpp_type = isa["name"].upper()
    isa_c_name = isa["name"].lower()

    print(_cpp_custom_prefix_generator(None, isa["name"]), file=file)

    template = """template<> struct rvd_type<{{ datatype.cstd }}, {{ lmul }}, ISA::{{isa_cpp_type}}>{ using type = rvd_{{isa_c_name}}_{{ datatype.category }}{{ datatype.n_bits }}_m{{ lmul }}_t; };"""
    j2_template = Template(template, undefined=StrictUndefined)
    for lmul in all_lmul:
        for dt in datatypes:
            print(j2_template.render(datatype=datatypes[dt], lmul=str(lmul), isa_cpp_type=isa_cpp_type, isa_c_name=isa_c_name), file=file)

    template = """template<> struct rvm_type<{{ datatype.cstd }}, {{ lmul }}, ISA::{{isa_cpp_type}}>{ using type = rvm_{{isa_c_name}}_{{ datatype.category }}{{ datatype.n_bits }}_m{{ lmul }}_t; };"""
    j2_template = Template(template, undefined=StrictUndefined)
    for lmul in all_lmul:
        for dt in datatypes:
            print(j2_template.render(datatype=datatypes[dt], lmul=str(lmul), isa_cpp_type=isa_cpp_type, isa_c_name=isa_c_name), file=file)
    # maybe enum shouldn't be defined here idk

    # ldiv
    # THE IF IS A TEMPORARY HACK
    if isa["name"] == "avx512" or isa["name"] == "scalar" or isa["name"] == "avx" or isa["name"] == "rvv":
        ldiv = 2
        ldiv_m = -2
        template = """template<> struct rvd_type<{{ datatype.cstd }}, {{ ldiv_m }}, ISA::{{isa_cpp_type}}>{ using type = rvd_{{isa_c_name}}_{{ datatype.category }}{{ datatype.n_bits }}_d{{ ldiv }}_t; };"""
        template_msk = """template<> struct rvm_type<{{ datatype.cstd }}, {{ ldiv_m }}, ISA::{{isa_cpp_type}}>{ using type = rvm_{{isa_c_name}}_{{ datatype.category }}{{ datatype.n_bits }}_d{{ ldiv }}_t; };"""
        j2_template = Template(template, undefined=StrictUndefined)
        j2_template_msk = Template(template_msk, undefined=StrictUndefined)
        for dt in datatypes:
            print(j2_template.render(datatype=datatypes[dt], ldiv_m=str(ldiv_m), isa_cpp_type=isa_cpp_type, isa_c_name=isa_c_name, ldiv=str(ldiv)), file=file)
        for dt in datatypes:
            print(j2_template_msk.render(datatype=datatypes[dt], ldiv_m=str(ldiv_m), isa_cpp_type=isa_cpp_type, isa_c_name=isa_c_name, ldiv=str(ldiv)), file=file)

def gen_cpp_constexpr_functions_isa(file, isa):
    isa_cpp_type = isa["name"].upper()

    template = """template<> constexpr uint32_t rvd_sz_bits<ISA::{{isa_cpp_type}}>(){ return MIPP_{{isa_cpp_type}}_RVD_SIZE_BIT; }"""
    j2_template = Template(template, undefined=StrictUndefined)
    print(j2_template.render(isa_cpp_type=isa_cpp_type), file=file)
    template = """template<> constexpr uint32_t rvd_sz_bytes<ISA::{{isa_cpp_type}}>(){ return MIPP_{{isa_cpp_type}}_RVD_SIZE_BYTE; }"""
    j2_template = Template(template, undefined=StrictUndefined)
    print(j2_template.render(isa_cpp_type=isa_cpp_type), file=file)
    template = """template<> constexpr uint32_t req_alignment<ISA::{{isa_cpp_type}}>(){ return MIPP_{{isa_cpp_type}}_RVD_SIZE_BYTE; } // placeholder """
    j2_template = Template(template, undefined=StrictUndefined)
    print(j2_template.render(isa_cpp_type=isa_cpp_type), file=file)

    template = """template<> constexpr uint32_t N<{{ datatype.cstd }}, {{ lmul }}, ISA::{{isa_cpp_type}} >(){ return MIPP_{{isa_cpp_type}}_N_{{type_category_upper}}{{ datatype.n_bits }}{{ lmul_suffix }}; }"""
    j2_template = Template(template, undefined=StrictUndefined)
    for lmul in all_lmul:
        if lmul == 1:
            lmul_suffix = ""
        else:
            lmul_suffix = "_M" + str(lmul)
        for dt in datatypes:
            print(j2_template.render(datatype=datatypes[dt], lmul=str(lmul), type_category_upper=datatypes[dt]["category"].upper(), lmul_suffix=lmul_suffix, isa_cpp_type=isa_cpp_type), file=file)

    # once every isa supports ldiv. This can be moved to the loop above.
    # THE IF IS A TEMPORARY HACK
    if isa["name"] == "avx512" or isa["name"] == "scalar" or isa["name"] == "avx" or isa["name"] == "rvv":
        ldiv = -2
        ldiv_suffix = "_D" + str(-ldiv)
        template = """template<> constexpr uint32_t N<{{ datatype.cstd }}, {{ ldiv }}, ISA::{{isa_cpp_type}} >(){ return MIPP_{{isa_cpp_type}}_N_{{type_category_upper}}{{ datatype.n_bits }}{{ ldiv_suffix }}; }"""
        j2_template = Template(template, undefined=StrictUndefined)
        for dt in datatypes:
            print(j2_template.render(datatype=datatypes[dt], ldiv=str(ldiv), type_category_upper=datatypes[dt]["category"].upper(), ldiv_suffix=ldiv_suffix, isa_cpp_type=isa_cpp_type), file=file)


    print(_cpp_close_namespace(), file=file) # hacky -> implies it HAS to be called after gen_cpp_structures_isa ...

def gen_cpp_functions_isa(include_manager, isa, funcs):
    layer_name = isa["name"] + "_cpp"
    for f in funcs:


        file = include_manager.get_fd(layer_name, f)
        prefix = _cpp_custom_prefix_generator(f, isa["name"], funcs)
        print(prefix, file=file)

        for dt in funcs[f]["datatypes"]:
            is_cast = len(dt.split(',')) > 1
            is_gthr_scttr =  ("gather" in f) or ("scatter" in f)
            is_cast = is_cast

            if not is_cast:
                dt_par = dt.split(',')[0]
                dt_ret = dt.split(',')[0]
            elif is_gthr_scttr:
                dt_par = dt.split(',')[0]
                dt_ret = dt.split(',')[1]
            else:
                dt_par = dt.split(',')[0]
                dt_ret = dt.split(',')[1]

            if not is_cast and not is_gthr_scttr:
                c_func_name = build_func_name_short(isa, dt_par, f, isa_name=True)
                cpp_func_name = build_cpp_func_name_short(funcs[f]["proto"], dt_ret, f)
            elif is_gthr_scttr:
                c_func_name = build_func_name(isa, dt_par, dt_ret, f, isa_name=True)                
                cpp_func_name = build_cpp_func_name_short(funcs[f]["proto"], dt_ret, f)
            else:
                c_func_name = build_func_name(isa, dt_par, dt_ret, f, isa_name=True)
                cpp_func_name = build_cpp_func_name(dt_ret, f)

            for lmul in all_lmul:
                print(build_proto(funcs[f]["proto"], dt_par, dt_ret, isa, cpp_func_name, lmul, isa_name=True, cpp=True) + " {", file=file)
                print("\t" + build_call(funcs[f]["proto"], dt_par, dt_ret, "", c_func_name + "_m" + str(lmul), lmul, False) + ";", file=file)
                print("}", file=file)
            mask_status = funcs[f]["mask_support"]

            # THE IF IS A TEMPORARY HACK
            if isa["name"] == "avx512" or isa["name"] == "scalar" or isa["name"] == "avx" or isa["name"] == "rvv":
                ldiv = -2
                print(build_proto(funcs[f]["proto"], dt_par, dt_ret, isa, cpp_func_name, ldiv, isa_name=True, cpp=True) + " {", file=file)
                print("\t" + build_call(funcs[f]["proto"], dt_par, dt_ret, "", c_func_name + "_d" + str(-ldiv), ldiv, False) + ";", file=file)
                print("}", file=file)
            
            if mask_status and mask_status.is_any_mask():
                proto = funcs[f]["proto"]
                c_base = _masked_c_symbol(dt_par, dt_ret, f, is_cast, isa=isa, isa_name=True)

                for lmul in all_lmul:
                    if mask_status.is_maskable():
                        _mask_tpl_spec(file, proto, dt_par, dt_ret, cpp_func_name, c_base, "M", "mask", lmul=lmul, isa = isa, isa_name=True)
                    if mask_status.is_maskzable():
                        _mask_tpl_spec(file, proto, dt_par, dt_ret, cpp_func_name, c_base, "Z", "maskz", lmul=lmul, isa = isa, isa_name=True)
                    if mask_status.is_masksable():
                        _mask_tpl_spec(file, proto, dt_par, dt_ret, cpp_func_name, c_base, "S", "masks", lmul=lmul, isa = isa, isa_name=True)

                # THE IF IS A TEMPORARY HACK
                if isa["name"] == "avx512" or isa["name"] == "scalar" or isa["name"] == "avx" or isa["name"] == "rvv":
                    ldiv = -2
                    if mask_status.is_maskable():
                        _mask_tpl_spec(file, proto, dt_par, dt_ret, cpp_func_name, c_base, "M", "mask", lmul=ldiv, isa = isa, isa_name=True)
                    if mask_status.is_maskzable():
                        _mask_tpl_spec(file, proto, dt_par, dt_ret, cpp_func_name, c_base, "Z", "maskz", lmul=ldiv, isa = isa, isa_name=True)
                    if mask_status.is_masksable():
                        _mask_tpl_spec(file, proto, dt_par, dt_ret, cpp_func_name, c_base, "S", "masks", lmul=ldiv, isa = isa, isa_name=True)
        print(_cpp_close_namespace(), file=file)