#!/usr/bin/env python3

from jinja2 import Template, StrictUndefined
import json
import copy

from tools import *
from headers_def import *
from c_generator import *
from generic_emu import *

from include_gen import IncludeManager

def _compute_dt_par_dt_ret_scalar(funcs, f, dt):
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

# Important changes here!!
def _render_template_scalar(isa, ff, dt_par, dt_ret, func_name=""):
    """
    renders the Jinja template. Can raise exceptions
    if the template is not well formed!
    """
    j2_template = Template(ff["implem"], undefined=StrictUndefined)

    return j2_template.render(
        isa=isa,
        dt_par=datatypes[dt_par],
        dt_ret=datatypes[dt_ret],
        isa_dt_par=isa["datatypes"][dt_par],
        isa_dt_ret=isa["datatypes"][dt_ret],
        cstdint_ret=datatypes[dt_ret]["cstd"],
        func_name = func_name,
    )

def _parse_placeholders_or_skip_scalar(pre_rendering, isa, funcs, f, dt_par, dt_ret, dt_key, file,lmul=0):
    """
    tries to parse placeholders in pre-rendered and returns converted IR. In gen c_funcs
    it was the call to parse_placeholders + affectation post_rendering = ph_ret["converted_ir"]
    """
    try:
        return parse_placeholders(pre_rendering, isa, funcs, f, dt_par, dt_ret, lmul=lmul)
    except Exception as err:
        err_message = "'" + f + "<" + dt_key + ">' has been skipped (reason: \"{0}\").".format(err)
        print(" -> " + err_message)
        print("// " + err_message, file=file)
        return None

def _build_func_name_scalar(isa, dt, dt_par, dt_ret, f, masked_version=False):
    """
    wrapper around build_func_name and build_func_name_short.
    Which function to call is decided if the type isn't a "double type"
    (i.e the function is not cast or cast_k)
    """
    if len(dt.split(',')) <= 1:
        return build_func_name_short(isa, dt_par, f, True, masked_version=masked_version)
    else:
        return build_func_name(isa, dt_par, dt_ret, f, True, masked_version=masked_version)

# Important changes here!!
def _emit_short_format_prologue_scalar(funcs_for_f, dt_ret, isa, file, lmul=0):
    # Keep same layout as original.
    if funcs_for_f["proto"]["args"]:
        if funcs_for_f["proto"]["ret"]["type"] == "reg":
            print(
                "\t" + build_type(funcs_for_f["proto"]["ret"]["type"], datatypes[dt_ret], isa, lmul=lmul) + " res;",
                file=file,
            )
        elif funcs_for_f["proto"]["ret"]["type"] == "msk":
            print(
                "\t" + build_type(funcs_for_f["proto"]["ret"]["type"], datatypes[dt_ret], isa, lmul=lmul) + " res;",
                file=file,
            )
    else:
        if funcs_for_f["proto"]["ret"]["type"] == "reg":
            print(
                "\t" + build_type(funcs_for_f["proto"]["ret"]["type"], datatypes[dt_ret], isa, lmul=lmul) + " res;",
                file=file,
            )
            # print("\tres.r = ", end="", file=file)
        elif funcs_for_f["proto"]["ret"]["type"] == "msk":
            print(
                "\t" + build_type(funcs_for_f["proto"]["ret"]["type"], datatypes[dt_ret], isa, lmul=lmul) + " res;",
                file=file,
            )

# Important changes here!!
def _emit_function_body_scalar(funcs, f, isa, dt, dt_par, dt_ret, ff, post_rendering, file, masked_version=None, lmul=0):
    func_name = _build_func_name_scalar(isa, dt, dt_par, dt_ret, f)

    print("static " + build_proto(funcs[f]["proto"], dt_par, dt_ret, isa, func_name, masked_version = masked_version, lmul=lmul) + " {", file=file)

    lmul_str = ""
    if lmul == 0:
        lmul_str = ""
    elif lmul >= 1:
        lmul_str = "_M" + str(lmul)
    elif lmul < 0:
        lmul_str = "_D" + str(int(-lmul))

    if ff["type"] == "element-wide":
        # Original code had a redundant always-true condition; keep behavior identical.
        if funcs[f]["proto"]["args"] or (not funcs[f]["proto"]["args"]):
            _emit_short_format_prologue_scalar(funcs[f], dt_ret, isa, file, lmul=lmul)
            print(f"\tfor (size_t i = 0; i < MIPP_SCALAR_N_{dt_par.upper()}{lmul_str}; i++)", file=file)
            print("\t{", file=file)
        # cleaning
        post_rendering = post_rendering.lstrip()
        post_rendering = post_rendering.replace("\n", "\n\t\t")
        post_rendering = post_rendering.replace("\t\t\n", "\n")
        post_rendering = "\t\t" + post_rendering
    elif ff["type"] == "vector-wide":
        print("\t", end='', file=file)
        # cleaning
        post_rendering = post_rendering.lstrip()
        post_rendering = post_rendering.replace("\n", "\n\t")
        post_rendering = post_rendering.replace("\t\n", "\n")
    else:
        print("Panic: unsupported type '" + ff["type"] + "' in '_emit_function_body_scalar' function.")
        exit(-1)

    print(post_rendering, file=file)

    if ff["type"] == "element-wide":
        print("\t}", file=file)
        if funcs[f]["proto"]["ret"]["type"]:
            print("\treturn res;", file=file)

    print("}", file=file)

# Important changes here!!
def gen_c_functions_scalar_one(isa, file, funcs, f, ff, dt, lmul=0):
        
    if ff["mask_variants"]:
        mask_variants = ff["mask_variants"]
    else:
        mask_variants = ["no_mask"]
        if "mask_support" in mipp_funcs[f]:
            support = mipp_funcs[f]["mask_support"]
            if support.is_maskable():
                mask_variants = mask_variants + ["mask"]
            if support.is_maskzable():
                mask_variants = mask_variants + ["maskz"]
            if support.is_masksable():
                mask_variants = mask_variants + ["masks"]

    for mask_variant in mask_variants:

        dt_par, dt_ret = _compute_dt_par_dt_ret_scalar(funcs, f, dt)
        dt_key = dt_par + "," + dt_ret

        pre_rendering = _render_template_scalar(isa, ff, dt_par, dt_ret)

        if mask_variant == "no_mask":
            pre_rendering = pre_rendering.replace("%!pred_cond!% ", "")
            pre_rendering = pre_rendering.replace("%!pred_cond!%", "")
            pre_rendering = pre_rendering.replace(" %!pred_alt!%", "")
            pre_rendering = pre_rendering.replace("%!pred_alt!%", "")
        else:
            pre_rendering = pre_rendering.replace("%!pred_cond!% ", "m0.m[i] ? (")
            pre_rendering = pre_rendering.replace("%!pred_cond!%", "m0.m[i] ? (")
            if mask_variant == "mask":
                pre_rendering = pre_rendering.replace(" %!pred_alt!%", ") : r0.r[i]")
                pre_rendering = pre_rendering.replace("%!pred_alt!%", ") : r0.r[i]")
            elif mask_variant == "maskz":
                if f == "hmax" or f == "hmin":
                    pre_rendering = pre_rendering.replace(" %!pred_alt!%", ") : resv")
                elif f == "hmul":
                    pre_rendering = pre_rendering.replace(" %!pred_alt!%", ") : 1")
                else:
                    pre_rendering = pre_rendering.replace(" %!pred_alt!%", ") : 0")
                    pre_rendering = pre_rendering.replace("%!pred_alt!%", ") : 0")
            elif mask_variant == "masks":
                pre_rendering = pre_rendering.replace(" %!pred_alt!%", ") : rsrc.r[i]")
                pre_rendering = pre_rendering.replace("%!pred_alt!%", ") : rsrc.r[i]")

        ph_ret = _parse_placeholders_or_skip_scalar(
            pre_rendering=pre_rendering,
            isa=isa,
            funcs=funcs,
            f=f,
            dt_par=dt_par,
            dt_ret=dt_ret,
            dt_key=dt_key,
            file=file,
            lmul=lmul,
        )
        if ph_ret is None:
            return

        post_rendering = ph_ret["converted_ir"]

        if mask_variant == "no_mask":
            mask_kind = None
        else:
            mask_kind = mask_variant

        _emit_function_body_scalar(
            funcs=funcs,
            f=f,
            isa=isa,
            dt=dt,
            dt_par=dt_par,
            dt_ret=dt_ret,
            ff=ff,
            post_rendering=post_rendering,
            file=file,
            masked_version=mask_kind,
            lmul=lmul,
        )

def _emit_separator_scalar(f, file):
    """
    Writes a separator comment for a given function name, to improve readability of the generated code.
    """
    n_dashes = 120 - 5 - len(f)
    print("// ", end="", file=file)
    while n_dashes > 0:
        print("-", end="", file=file)
        n_dashes = n_dashes - 1
    print(f" {f}", file=file)

# Important changes here!!
def gen_c_functions_scalar(isa, include_manager, funcs, implems, lmul=0):
    for f in implems:
        file = include_manager.get_fd(isa["name"], f)
        if f in funcs:
            _emit_separator_scalar(f, file)
            for ff in implems[f]:
                if ff["datatypes"]:
                    datatypes = ff["datatypes"]
                else:
                    datatypes = funcs[f]["datatypes"]
                for dt in datatypes:
                    gen_c_functions_scalar_one(isa, file, funcs, f, ff, dt, lmul=lmul)
        else:
            print("Panic: '" + f + "' function does not exist.")
            exit(-1)


def gen_c_defines_scalar(isa, file):
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

    template1 = """#define MIPP_{{isa_name_upper}}_N_{{type_category_upper}}{{n_bits}} {{n_elmts}}"""
    template2 = """#define MIPP_{{isa_name_upper}}_N_{{type_category_upper}}{{n_bits}} {{n_elmts}}
#if MIPP_{{isa_name_upper}}_N_{{type_category_upper}}{{n_bits}} == 0
    #error "MIPP_{{isa_name_upper}}_N_{{type_category_upper}}{{n_bits}} can't be null\"
#endif"""

    if isinstance(isa["size"], str):
        j2_template = Template(template2, undefined=StrictUndefined)
    else:
        j2_template = Template(template1, undefined=StrictUndefined)

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
            ),
            file=file,
        )  
    
    for lmul in all_lmul:
        for dt in isa["datatypes"]:
            if isinstance(isa["size"], str):
                n_elmts = f'{isa["size"]}/{datatypes[dt]["n_bits"]}*{lmul}'
            else:
                n_elmts = int(isa["size"] / datatypes[dt]["n_bits"])*lmul
            template = """#define MIPP_{{isa_name_upper}}_N_{{type_category_upper}}{{n_bits}}_M{{lmul}} {{n_elmts}}"""
            j2_template = Template(template, undefined=StrictUndefined)
            print(
                j2_template.render(
                    isa_name_upper=isa["name"].upper(),
                    type_category_upper=datatypes[dt]["category"].upper(),
                    n_bits=datatypes[dt]["n_bits"],
                    n_elmts=n_elmts,
                    lmul=lmul,
                ),
                file=file,
            )    
    # ldiv defines
    # 
    ldiv = 2
    for dt in isa["datatypes"]:
        if isinstance(isa["size"], str):
            n_elmts = f'{isa["size"]}/{datatypes[dt]["n_bits"]}/{ldiv}'
        else:
            n_elmts = int(isa["size"] / datatypes[dt]["n_bits"])/ldiv
        template = """#define MIPP_{{isa_name_upper}}_N_{{type_category_upper}}{{n_bits}}_D{{ldiv}} {{n_elmts}}"""
        j2_template = Template(template, undefined=StrictUndefined)
        print(
            j2_template.render(
                isa_name_upper=isa["name"].upper(),
                type_category_upper=datatypes[dt]["category"].upper(),
                n_bits=datatypes[dt]["n_bits"],
                n_elmts=n_elmts,
                ldiv=ldiv,
            ),
            file=file,
        )      
            
def gen_c_structures_scalar(isa, file):
    """
    Writes the C structures corresponding to the supported datatypes for a given ISA, for both vector and mask types.
    """
    template = """typedef struct { {{ isa_datatype.reg }} r[MIPP_{{isa_name_upper}}_N_{{type_category_upper}}{{datatype.n_bits}}]; } rvd_{{ isa.name }}_{{ datatype.category }}{{ datatype.n_bits }}_t;"""

    template_alt = """typedef struct {
#if {{ isa_datatype.if }}
    {{ isa_datatype.reg }} r;
#else
    int r; // this is a hack to compile when the datatype is not suported by the SIMD extension
#endif // {{ isa_datatype.if }}
} rvd_{{ isa.name }}_{{ datatype.category }}{{ datatype.n_bits }}_t;"""
    j2_template_alt = Template(template_alt, undefined=StrictUndefined)
    j2_template = Template(template, undefined=StrictUndefined)

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


    template = """typedef struct { {{ isa_datatype.msk }} m[MIPP_{{isa_name_upper}}_N_{{type_category_upper}}{{datatype.n_bits}}]; } rvm_{{ isa.name }}_{{ datatype.category }}{{ datatype.n_bits }}_t;"""
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
        
    for lmul in all_lmul:
        template = """typedef struct { {{ isa_datatype.reg }} r[MIPP_{{isa_name_upper}}_N_{{type_category_upper}}{{datatype.n_bits}}_M{{lmul}}]; } rvd_{{ isa.name }}_{{ datatype.category }}{{ datatype.n_bits }}_m{{lmul}}_t;"""
        template_msk = """typedef struct { {{ isa_datatype.msk }} m[MIPP_{{isa_name_upper}}_N_{{type_category_upper}}{{datatype.n_bits}}_M{{lmul}}]; } rvm_{{ isa.name }}_{{ datatype.category }}{{ datatype.n_bits }}_m{{lmul}}_t;"""
        
        j2_template = Template(template, undefined=StrictUndefined)
        j2_template_msk = Template(template_msk, undefined=StrictUndefined)
        for dt in isa["datatypes"]:
            print(
                j2_template.render(
                    isa=isa,
                    isa_datatype=isa["datatypes"][dt],
                    datatype=datatypes[dt],
                    isa_name_upper=isa["name"].upper(),
                    type_category_upper=datatypes[dt]["category"].upper(),
                    lmul=lmul,
                ),
                file=file,
            )
        for dt in isa["datatypes"]:
            print(
                j2_template_msk.render(
                    isa=isa,
                    isa_datatype=isa["datatypes"][dt],
                    datatype=datatypes[dt],
                    isa_name_upper=isa["name"].upper(),
                    type_category_upper=datatypes[dt]["category"].upper(),
                    lmul=lmul,
                ),
                file=file,
            )

    ldiv = 2
    template = """typedef struct { {{ isa_datatype.reg }} r[MIPP_{{isa_name_upper}}_N_{{type_category_upper}}{{datatype.n_bits}}_D{{ldiv}}]; } rvd_{{ isa.name }}_{{ datatype.category }}{{ datatype.n_bits }}_d{{ldiv}}_t;"""
    template_msk = """typedef struct { {{ isa_datatype.msk }} m[MIPP_{{isa_name_upper}}_N_{{type_category_upper}}{{datatype.n_bits}}_D{{ldiv}}]; } rvm_{{ isa.name }}_{{ datatype.category }}{{ datatype.n_bits }}_d{{ldiv}}_t;"""
    
    j2_template = Template(template, undefined=StrictUndefined)
    j2_template_msk = Template(template_msk, undefined=StrictUndefined)
    for dt in isa["datatypes"]:
        print(
            j2_template.render(
                isa=isa,
                isa_datatype=isa["datatypes"][dt],
                datatype=datatypes[dt],
                isa_name_upper=isa["name"].upper(),
                type_category_upper=datatypes[dt]["category"].upper(),
                ldiv=ldiv,
            ),
            file=file,
        )
    for dt in isa["datatypes"]:
        print(
            j2_template_msk.render(
                isa=isa,
                isa_datatype=isa["datatypes"][dt],
                datatype=datatypes[dt],
                isa_name_upper=isa["name"].upper(),
                type_category_upper=datatypes[dt]["category"].upper(),
                ldiv=ldiv,
            ),
            file=file,
        )

def gen_mipp_scalar(include_manager):
    
    # implementation C
    
    file_common = include_manager.get_fd(isa_scalar["name"], "common")
    # file = open("../include/scalar/mipp_impl_scalar_gen.h", "w")

    tpl_header_scalar = """#ifndef MY_INTRINSICS_PLUS_PLUS_IMPL_GEN_SCALAR_H_
#define MY_INTRINSICS_PLUS_PLUS_IMPL_GEN_SCALAR_H_
#include <math.h> // sqrt, sqrtf, round, roundf
#include <string.h> // memcpy
#include <stdint.h>
#include <float.h> // FLT_MAX, DBL_MAX
#include <limits.h>
#if !defined(MIPP_SCALAR_SIZE)
	#if defined(__MIC__) || defined(__KNCNI__) || defined(__AVX512__) || defined(__AVX512F__)
		#define MIPP_SCALAR_SIZE 512
	#elif defined(__AVX__)
		#define MIPP_SCALAR_SIZE 256
	#elif defined(__SSE__)
		#define MIPP_SCALAR_SIZE 128
	#elif defined(__ARM_FEATURE_SVE)
		#if defined(MIPP_SVE_2048)
			#define MIPP_SCALAR_SIZE 2048
		#elif defined(MIPP_SVE_1024)
			#define MIPP_SCALAR_SIZE 1024
		#elif defined(MIPP_SVE_512)
			#define MIPP_SCALAR_SIZE 512
		#elif defined(MIPP_SVE_256)
			#define MIPP_SCALAR_SIZE 256
		#elif defined(MIPP_SVE_128)
			#define MIPP_SCALAR_SIZE 128
		#else
			#error "MIPP_SVE_[SIZE] (SIZE in {128, 256, 512, 1024, 2048}) is undefined, user should define -DMIPP_SVE_[SIZE] at compile time!"
		#endif
	#elif defined(__ARM_NEON__) || defined(__ARM_NEON)
		#define MIPP_SCALAR_SIZE 128
	#elif __riscv_v_intrinsic
		#define MIPP_SCALAR_SIZE __riscv_v_fixed_vlen
	#else
		#if defined(MIPP_SCALAR)
			#error "You probably forgot to define -DMIPP_SCALAR_SIZE=[bits]"
		#else
			#error "Your architecture is not supported by MIPP (yet), you can fallback to the scalar mode with -DMIPP_SCALAR and -DMIPP_SCALAR_SIZE=[bits] definitions"
		#endif
	#endif
#endif // !defined(MIPP_SCALAR_SIZE)

#if MIPP_SCALAR_SIZE == 0
	#error "MIPP_SCALAR_SIZE can't be null"
#endif

#define BIT_CAST_N(dst_ptr, src_ptr, n) \\
	memcpy((dst_ptr), (src_ptr), (n) * sizeof(*(dst_ptr)))

#define BIT_CAST_1(dst_ptr, src_ptr) \\
	memcpy((dst_ptr), (src_ptr), sizeof(*(dst_ptr)))

typedef float float32_t;
typedef double float64_t;
"""
    j2_template = Template(tpl_header_scalar, undefined=StrictUndefined)
    print(j2_template.render(), file=file_common)

    gen_c_defines_scalar(isa_scalar, file_common)
    gen_c_structures_scalar(isa_scalar, file_common)
    print("Generate Scalar...", end=" ")
    copy_mipp_funcs = copy.deepcopy(mipp_funcs)
    
    gen_c_functions_scalar(isa_scalar, include_manager, copy_mipp_funcs, implems_scalar)
    for lmul in all_lmul:
        gen_c_functions_scalar(isa_scalar, include_manager, copy_mipp_funcs, implems_scalar, lmul=lmul)

    ldiv = -2
    gen_c_functions_scalar(isa_scalar, include_manager, copy_mipp_funcs, implems_scalar, lmul=ldiv)

    tpl_footer_scalar = """#endif /* MY_INTRINSICS_PLUS_PLUS_IMPL_GEN_SCALAR_H_ */"""
    j2_template = Template(tpl_footer_scalar, undefined=StrictUndefined)
    print(j2_template.render(), file=file_common)
    
    include_manager.resolve_all_dependencies(isa_scalar["name"], copy_mipp_funcs)
    include_manager.create_glue_file(isa_scalar["name"], "../include/scalar/mipp_impl_scalar_gen.h")
    include_manager.close_layer_fds(isa_scalar["name"])

    print("Done.")
