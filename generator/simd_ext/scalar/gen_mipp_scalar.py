#!/usr/bin/env python3

from jinja2 import Template, StrictUndefined
import json
import copy

from tools import *
from headers_def import *
from c_generator import *
from generic_emu import *

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
    # j2_template = Template(ff["template"]["code"], undefined=StrictUndefined)
    j2_template = Template(ff["implem"], undefined=StrictUndefined)
    # instr_name = ""
    # if "instr_name" in ff:
    #     instr_name = ff["instr_name"]

    return j2_template.render(
        isa=isa,
        # instr_name=instr_name,
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
            # print("\tres.r = ", end="", file=file)
        elif funcs_for_f["proto"]["ret"]["type"] == "msk":
            print(
                "\t" + build_type(funcs_for_f["proto"]["ret"]["type"], datatypes[dt_ret], isa, lmul=lmul) + " res;",
                file=file,
            )
            # print("\tres.m = ", end="", file=file)
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
            # print("\tres.m = ", end="", file=file)

# Important changes here!!
def _emit_function_body_scalar(funcs, f, isa, dt, dt_par, dt_ret, ff, post_rendering, file, masked_version=None, lmul=0):
    func_name = _build_func_name_scalar(isa, dt, dt_par, dt_ret, f)

    print("static " + build_proto(funcs[f]["proto"], dt_par, dt_ret, isa, func_name, masked_version = masked_version, lmul=lmul) + " {", file=file)

    # if ff["template"]["format"] == "short":
    #     # Original code had a redundant always-true condition; keep behavior identical.
    #     if funcs[f]["proto"]["args"] or (not funcs[f]["proto"]["args"]):
    #         _emit_short_format_prologue(funcs[f], dt_ret, isa, file,lmul=lmul)
    # else:
    #     print("\t", end='', file=file)
    if ff["type"] == "element-wide":
        # Original code had a redundant always-true condition; keep behavior identical.
        if funcs[f]["proto"]["args"] or (not funcs[f]["proto"]["args"]):
            print(f"\tstatic_assert(MIPP_SCALAR_N_{dt_par.upper()} > 0, \"MIPP_SCALAR_N_{dt_par.upper()} must be > 0\");", end="\n", file=file)
            if dt_par.upper() != dt_ret.upper():
                print(f"\tstatic_assert(MIPP_SCALAR_N_{dt_ret.upper()} > 0, \"MIPP_SCALAR_N_{dt_ret.upper()} must be > 0\");", end="\n", file=file)
            print("", end="\n", file=file)
            _emit_short_format_prologue_scalar(funcs[f], dt_ret, isa, file, lmul=lmul)
            print(f"\tfor (size_t i = 0; i < MIPP_SCALAR_N_{dt_par.upper()}; i++)", file=file)
            print("\t{", file=file)
        # cleaning
        post_rendering = post_rendering.lstrip()
        post_rendering = post_rendering.replace("\n", "\n\t\t")
        post_rendering = post_rendering.replace("\t\t\n", "\n")
        post_rendering = "\t\t" + post_rendering
    elif ff["type"] == "vector-wide":
        print(f"\tstatic_assert(MIPP_SCALAR_N_{dt_par.upper()} > 0, \"MIPP_SCALAR_N_{dt_par.upper()} must be > 0\");", end="\n", file=file)
        if dt_par.upper() != dt_ret.upper():
            print(f"\tstatic_assert(MIPP_SCALAR_N_{dt_ret.upper()} > 0, \"MIPP_SCALAR_N_{dt_ret.upper()} must be > 0\");", end="\n", file=file)
        print("", end="\n", file=file)
        print("\t", end='', file=file)
        # cleaning
        post_rendering = post_rendering.lstrip()
        post_rendering = post_rendering.replace("\n", "\n\t")
        post_rendering = post_rendering.replace("\t\n", "\n")
        # post_rendering = "\t" + post_rendering
    else:
        print("Panic: unsupported type '" + ff["type"] + "' in '_emit_function_body_scalar' function.")
        exit(-1)

    print(post_rendering, file=file)

    # if ff["template"]["format"] == "short":
    #     if funcs[f]["proto"]["ret"]["type"]:
    #         print("\treturn res;", file=file)
    if ff["type"] == "element-wide":
        print("\t}", file=file)
        if funcs[f]["proto"]["ret"]["type"]:
            print("\treturn res;", file=file)

    print("}", file=file)

# Important changes here!!
def _gen_c_functions_one_unmasked_scalar(isa, file, funcs, f, ff, dt):
    """
    the big glue guy that calls all the helpers
    to generate 1 fn for 1 dt. It's the logic of the big inner loop
    of gen_c_functions.
    """
    dt_par, dt_ret = _compute_dt_par_dt_ret_scalar(funcs, f, dt)
    dt_key = dt_par + "," + dt_ret

    # if not is_missing_func(funcs, f, dt_key):
    #     _emit_already_implemented_message(f, dt_key, file)
    #     return

    pre_rendering = _render_template_scalar(isa, ff, dt_par, dt_ret)

    ph_ret = _parse_placeholders_or_skip_scalar(
        pre_rendering=pre_rendering,
        isa=isa,
        funcs=funcs,
        f=f,
        dt_par=dt_par,
        dt_ret=dt_ret,
        dt_key=dt_key,
        file=file,
    )
    if ph_ret is None:
        return

    #ifd_prev = _build_previous_emulated_exclusion_ifdef(funcs, f, dt_key, ff)

    #_append_implem_status(funcs, f, dt_key, ff, ph_ret["requirements"])

    post_rendering = ph_ret["converted_ir"]

    #ifd = _combine_current_ifdefs(funcs, f, dt_key, ifd_prev)
    #_emit_ifdef_begin_and_update_emulated(funcs, f, dt_key, ff, ifd, file)

    _emit_function_body_scalar(funcs, f, isa, dt, dt_par, dt_ret, ff, post_rendering, file)

    #_emit_ifdef_end(ifd, file)
    #_maybe_print_emulated_implemented(f, dt_key, ff)

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
def gen_c_functions_scalar(isa, file, funcs, implems):
    """
    Looking leaner now.
    """
    for f in implems:
        if f in funcs:
            _emit_separator_scalar(f, file)
            for ff in implems[f]:
                if ff["datatypes"]:
                    for dt in ff["datatypes"]:
                        _gen_c_functions_one_unmasked_scalar(isa, file, funcs, f, ff, dt)
                else:
                    for dt in funcs[f]["datatypes"]:
                        _gen_c_functions_one_unmasked_scalar(isa, file, funcs, f, ff, dt)

        else:
            print("Panic: '" + f + "' function does not exist.")
            exit(-1)

def gen_mipp_scalar():
    # implementation C
    file = open("../include/scalar/mipp_impl_scalar_gen.h", "w")

    tpl_header_avx = """#ifndef MY_INTRINSICS_PLUS_PLUS_IMPL_GEN_SCALAR_H_
#define MY_INTRINSICS_PLUS_PLUS_IMPL_GEN_SCALAR_H_
#include <math.h> // sqrt, sqrtf, round, roundf
#include <string.h> // memcpy
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

#define BIT_CAST_N(dst_ptr, src_ptr, n) \\
	memcpy((dst_ptr), (src_ptr), (n) * sizeof(*(dst_ptr)))

#define BIT_CAST_1(dst_ptr, src_ptr) \\
	memcpy((dst_ptr), (src_ptr), sizeof(*(dst_ptr)))

#ifndef __cplusplus
	#ifndef static_assert
		#define static_assert _Static_assert
	#endif
#endif
"""
    j2_template = Template(tpl_header_avx, undefined=StrictUndefined)
    print(j2_template.render(), file=file)

    gen_c_defines(isa_scalar, file)
    gen_c_structures(isa_scalar, file, is_scalar=True)
    print("Generate Scalar...", end=" ")
    copy_mipp_funcs = copy.deepcopy(mipp_funcs)
    gen_c_functions_scalar(isa_scalar, file, copy_mipp_funcs, implems_scalar)

    # gen_c_missing_functions(isa_scalar, file, copy_mipp_funcs)

    tpl_footer_avx = """#endif /* MY_INTRINSICS_PLUS_PLUS_IMPL_GEN_SCALAR_H_ */"""
    j2_template = Template(tpl_footer_avx, undefined=StrictUndefined)
    print(j2_template.render(), file=file)

    file.close()
    print("Done.")
