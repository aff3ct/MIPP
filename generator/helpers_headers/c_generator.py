from jinja2 import Template, StrictUndefined
import json
import re

from tools import *
from tools import _get_dt_par_size, _build_func_name
from tools import negate_cond as tool_negate_cond
from tools import are_conds_mutually_exclusive as tool_are_conds_mutually_exclusive
from tools import intersect_conds as tool_intersect_conds

from include_gen import *
from generic_emu import *



seen_lmul_separators = set()
seen_ldiv_separators = set()

def _maybe_emit_lmul_separator(isa_name, f, file):
    key = (isa_name, f)
    if key not in seen_lmul_separators:
        seen_lmul_separators.add(key)
        print("", file=file)
        print("// " + "=" * 117, file=file)
        print("// " + " " * 113 + "LMUL", file=file)
        print("// " + "=" * 117, file=file)

def _maybe_emit_ldiv_separator(isa_name, f, file):
    key = (isa_name, f)
    if key not in seen_ldiv_separators:
        seen_ldiv_separators.add(key)
        print("", file=file)
        print("// " + "=" * 117, file=file)
        print("// " + " " * 113 + "LDIV", file=file)
        print("// " + "=" * 117, file=file)

def _gen_ldiv_structs_avx(isa_base, isa_div, file):
    # hardcoded d2 is not very good looking tbh.
    template = """typedef rvd_{{ isa_div.name }}_{{datatype.category}}{{datatype.n_bits}}_t rvd_{{ isa.name }}_{{ datatype.category }}{{ datatype.n_bits }}_d2_t;"""
    j2_template = Template(template, undefined=StrictUndefined)
    for dt in isa_base["datatypes"]:
        if "ldiv" in isa_base["datatypes"][dt] and len(isa_base["datatypes"][dt]["ldiv"]) > 0:
            print(j2_template.render(isa=isa_base, isa_div=isa_div, datatype=datatypes[dt]), file=file)

    template = """typedef rvm_{{ isa_div.name }}_{{datatype.category}}{{datatype.n_bits}}_t rvm_{{ isa.name }}_{{ datatype.category }}{{ datatype.n_bits }}_d2_t;"""
    j2_template = Template(template, undefined=StrictUndefined)
    for dt in isa_base["datatypes"]:
        if "ldiv" in isa_base["datatypes"][dt] and len(isa_base["datatypes"][dt]["ldiv"]) > 0:
            print(j2_template.render(isa=isa_base, isa_div=isa_div, datatype=datatypes[dt]), file=file)

def _gen_ldiv_defines_avx(isa_base, isa_div, file):
    template = """#define MIPP_{{isa_name_upper}}_N_{{type_category_upper}}{{n_bits}}_D2 {{n_elmts_d2}}"""
    j2_template = Template(template, undefined=StrictUndefined)
    for dt in isa_base["datatypes"]:
        if "ldiv" in isa_base["datatypes"][dt] and len(isa_base["datatypes"][dt]["ldiv"]) > 0:
            n_elmts_d2 = int(isa_base["size"] / (2 * datatypes[dt]["n_bits"]))
            print(j2_template.render(isa_name_upper=isa_base["name"].upper(), type_category_upper=datatypes[dt]["category"].upper(), n_bits=datatypes[dt]["n_bits"], n_elmts_d2=n_elmts_d2), file=file)

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
    template2 = """#define MIPP_{{isa_name_upper}}_N_{{type_category_upper}}{{n_bits}}{{lmul_suffix}} {{n_elmts}}{{coeff}}"""
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

    # if isa doesn't support hw_lmul -> gen generic lmul / ldiv types
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
    
    if isa["name"] == "avx512" : 
        sub_isa = GLOBAL_ISA_REGISTRY.get("avx")
        if sub_isa:
            _gen_ldiv_structs_avx(isa, sub_isa, file)
            _gen_ldiv_defines_avx(isa, sub_isa, file)
    if isa["name"] == "avx" : 
        sub_isa = GLOBAL_ISA_REGISTRY.get("sse")
        if sub_isa:
            _gen_ldiv_structs_avx(isa, sub_isa, file)
            _gen_ldiv_defines_avx(isa, sub_isa, file)

# ----------------------------------------------------------------------------------------------------------------------
# Shared helpers
# ----------------------------------------------------------------------------------------------------------------------

def _is_masked_implem(f, ff):
    """
    temporary skip of masks
    """
    if "version" in ff and ff["version"]:
        #print(
        #	"Info: '" + f + "<" + ff["version"] + ">' has been skipped (reason: \"Info: Masked functions are not supported yet.\")."
        #)
        return True
    return False

def _render_template(isa, ff, dt_par, dt_ret, func_name="", lmul=0):
    """
    renders the Jinja template. Can raise exceptions 
    if the template is not well formed!
    """
    j2_template = Template(ff["template"]["code"], undefined=StrictUndefined)
    instr_name = ""
    if "instr_name" in ff:
        instr_name = ff["instr_name"]

    return j2_template.render(
        isa=isa,
        instr_name=instr_name,
        dt_par=datatypes[dt_par],
        dt_ret=datatypes[dt_ret],
        isa_dt_par=isa["datatypes"][dt_par],
        isa_dt_ret=isa["datatypes"][dt_ret],
        cstdint_ret=datatypes[dt_ret]["cstd"],
        func_name = func_name,
        lmul = lmul
    )

def _parse_placeholders_or_skip(pre_rendering, isa, funcs, f, dt_par, dt_ret, dt_key, file,lmul=0, isa_name=True):
    """
    tries to parse placeholders in pre-rendered and returns converted IR. In gen c_funcs 
    it was the call to parse_placeholders + affectation post_rendering = ph_ret["converted_ir"]
    """
    try:
        return parse_placeholders(pre_rendering, isa, funcs, f, dt_par, dt_ret, lmul=lmul, isa_name=isa_name)
    except Exception as err:
        err_message = "'" + f + "<" + dt_key + ">' has been skipped (reason: \"{0}\").".format(err)
        print("// " + err_message, file=file)
        return None

def _get_implem_bucket(funcs, f, dt_key, mask_kind=None, create=False):
    if mask_kind is None:
        if create:
            if "implem_status" not in funcs[f]:
                funcs[f]["implem_status"] = {}
            if dt_key not in funcs[f]["implem_status"]:
                funcs[f]["implem_status"][dt_key] = []
        if "implem_status" in funcs[f] and dt_key in funcs[f]["implem_status"]:
            return funcs[f]["implem_status"][dt_key]
        return None
    else:
        return get_masked_bucket(funcs, f, dt_key, mask_kind, create_missing_bucket=create)

def _build_prev_exclusion_ifdef(funcs, f, dt_key, ff, mask_kind=None):
    ifd = ""
    if "type" in ff and ff["type"] == "emulated":
        ifd = _missing_build_negated_ifdef_for_existing_implems(funcs, f, dt_key, mask_kind=mask_kind)
    return ifd

def _append_implem_status(funcs, f, dt_key, ff, requirements, mask_kind=None):
    cur_implem_status = {"if": "", "requirements": {}}
    if "if" in ff:
        cur_implem_status["if"] = ff["if"]
    cur_implem_status["requirements"] = requirements

    bucket = _get_implem_bucket(funcs, f, dt_key, mask_kind, create=True)
    bucket.append(cur_implem_status)

def _combine_current_ifdefs(funcs, f, dt_key, ifd_prev, mask_kind=None):
    bucket = _get_implem_bucket(funcs, f, dt_key, mask_kind)
    if bucket is None:
        return ifd_prev

    ifd_cur = (build_ifdef_masked(funcs, f, dt_key, mask_kind, len(bucket) - 1)
               if mask_kind is not None
               else build_ifdef(funcs, f, dt_key, len(bucket) - 1))

    if ifd_prev and ifd_cur:
        return simplify_cond_str(ifd_prev + " && (" + ifd_cur + ")")
    elif ifd_cur:
        return simplify_cond_str(ifd_cur)
    return simplify_cond_str(ifd_prev)


def _update_emulated(funcs, f, dt_key, ff, ifd, mask_kind=None):
    if "type" in ff and ff["type"] == "emulated":
        bucket = _get_implem_bucket(funcs, f, dt_key, mask_kind)
        if bucket:
            bucket[len(bucket) - 1]["if"] = ifd

def _emit_ifdef_begin_and_update_emulated(funcs, f, dt_key, ff, ifd, file, mask_kind=None):
    if ifd:
        print("#if " + ifd, file=file)
        _update_emulated(funcs, f, dt_key, ff, ifd, mask_kind=mask_kind)

def _emit_short_format_prologue(funcs_for_f, dt_ret, isa, file, lmul=0):
        # Keep same layout as original.
    if funcs_for_f["proto"]["args"]:
        if funcs_for_f["proto"]["ret"]["type"] == "reg":
            print(
                "\t" + build_type(funcs_for_f["proto"]["ret"]["type"], datatypes[dt_ret], isa, lmul=lmul) + " res;",
                file=file,
            )
            print("\tres.r = ", end="", file=file)
        elif funcs_for_f["proto"]["ret"]["type"] == "msk":
            print(
                "\t" + build_type(funcs_for_f["proto"]["ret"]["type"], datatypes[dt_ret], isa, lmul=lmul) + " res;",
                file=file,
            )
            print("\tres.m = ", end="", file=file)
    else:
        if funcs_for_f["proto"]["ret"]["type"] == "reg":
            print(
                "\t" + build_type(funcs_for_f["proto"]["ret"]["type"], datatypes[dt_ret], isa, lmul=lmul) + " res;",
                file=file,
            )
            print("\tres.r = ", end="", file=file)
        elif funcs_for_f["proto"]["ret"]["type"] == "msk":
            print(
                "\t" + build_type(funcs_for_f["proto"]["ret"]["type"], datatypes[dt_ret], isa, lmul=lmul) + " res;",
                file=file,
            )
            print("\tres.m = ", end="", file=file)

def _emit_function_body(funcs, f, isa, dt, dt_par, dt_ret, ff, post_rendering, file, masked_version=None, lmul=0, level=None):
    func_name = _build_func_name(isa, dt, dt_par, dt_ret, f, masked_version=masked_version, lmul=lmul)

    print("static " + build_proto(funcs[f]["proto"], dt_par, dt_ret, isa, func_name, masked_version = masked_version, lmul=lmul) + " {", file=file)

    if level is None and ff is not None:
        level = ff.get("level", 1 if ("type" in ff and ff["type"] == "emulated") else 0)

    if level is not None:
        level_comments = {
            0: "Level 0 (Optimal / Native)",
            1: "Level 1 (Specific Emulated)",
            2: "Level 2 (Generic Emulated)",
            3: "Level 3 (Auto Scalar Fallback)"
        }
        if level in level_comments:
            print(f"\t// {level_comments[level]}", file=file)

    if ff["template"]["format"] == "short":
        # Original code had a redundant always-true condition; keep behavior identical.
        if funcs[f]["proto"]["args"] or (not funcs[f]["proto"]["args"]):
            _emit_short_format_prologue(funcs[f], dt_ret, isa, file,lmul=lmul)
    else:
        print("\t", end='', file=file)

    print(post_rendering, file=file)

    if ff["template"]["format"] == "short":
        if funcs[f]["proto"]["ret"]["type"]:
            print("\treturn res;", file=file)

    print("}", file=file)


def _emit_ifdef_end(ifd, file):
    """writes #endif to a file."""
    if ifd:
        print("#endif", file=file)

def _emit_already_implemented_message(f, dt_key, file, generic=False):
    """print skip message because function already exists in file"""
    # Centralize the message string to avoid drift; must remain identical.
    generic_str = "Generic " if generic else ""
    print("// '" + generic_str +  f + "<" + dt_key + ">' has been skipped (reason: \"Info: It has been implemented before.\").", file=file)

def _gen_isdef_neg(funcs, f, dt_key):
    """
    generates the negation of an ifdef.
    """
    ret =  build_ifdef_rec(funcs, f, dt_key)
    return "#if !" + ret + "" if ret else ""

def _add_guard_if_isdef(funcs, f, dt_key, file):
    """
    used in gen_c_generic_functions, creates the negation of an ifdef and writes it to the file. 
    It's used to guard the generic implementation with the negation of the conditions of previous implementations, if any.
    """
    if is_ifdef(funcs, f, dt_key):
        guard = _gen_isdef_neg(funcs, f, dt_key)
        print(guard, file=file)

def _add_endif_if_isdef(funcs, f, dt_key, file):
    """
    used in combination with _add_guard_if_isdef, writes #endif to file if there was an ifdef.
    """
    if is_ifdef(funcs, f, dt_key):
        print("#endif", file=file)

# to prevent gen_c_missing_functions to generate the missing prototypes
def _remove_cond_implem_status(funcs, f, dt_key):
    """
    Removes the "if" condition in implem_status for a given function + dt_key
    If you don't do that, gen_c_missing_functions will generate the 
    fn prototype as a missing function. 
    
    Used in gen_c_generic_functions after adding the generic implementation. 
    Since the guard of the function made by gen_c_generic_functions 
    is the negation of the conditions of previous implementations, 
    it's as if you have if A && !A which is false.
    
    This feels "cleaner" than adding the negation to implem_status and then having 
    gen_c_missing_functions generate a fn  with a guard that
    prevents it from being reached.....
    """
    if "implem_status" in funcs[f] and dt_key in funcs[f]["implem_status"]:
        for implem in funcs[f]["implem_status"][dt_key]:
            if "if" in implem and implem["if"]:
                implem["if"] = ""

# same...
def _mark_as_implemented(funcs, f, dt_key):
    """
    adds/create the "if" and "requirements" keys in implem_status for 
    a given function + dt_key and initializes them to the correct values 
    ("" and {} if there is no conditions or the correct ifdef and requirements)
    
    I'm not sure this is correct tbh
    """
    done_implem_status = {"if": "", "requirements": {}}
    if "implem_status" in funcs[f] and dt_key in funcs[f]["implem_status"]:
        for implem in funcs[f]["implem_status"][dt_key]:
            if "if" in implem and implem["if"]:
                done_implem_status["if"] = implem["if"]
            if "requirements" in implem and implem["requirements"]:
                done_implem_status["requirements"] = implem["requirements"]
    if "implem_status" not in funcs[f]:
        funcs[f]["implem_status"] = {}
    funcs[f]["implem_status"][dt_key] = [done_implem_status]

def _missing_build_negated_ifdef_for_existing_implems(funcs, f, dt_key, mask_kind=None):
    ifd = ""
    bucket = _get_implem_bucket(funcs, f, dt_key, mask_kind)
    if bucket is not None:
        is_first = True
        for i in range(len(bucket)):
            ifd_sub = (build_ifdef_masked(funcs, f, dt_key, mask_kind, i)
                       if mask_kind is not None
                       else build_ifdef(funcs, f, dt_key, i))
            if ifd_sub:
                if not is_first:
                    ifd = ifd + " && "
                ifd = ifd + "!( " + ifd_sub + " )"
                is_first = False
    return ifd

def _missing_emit_ifdef_begin(ifd, file):
    """
    ifd != is_ifdef so not the same helper....
    """
    if ifd:
        print("#if " + ifd, file=file)

def _missing_emit_stub(file, funcs, f, dt_par, dt_ret, isa, func_name, masked_version = None, lmul=0):
    """
    writes the "body" of the missing function. 
    Which prints a panic messages and terminates the program.
    """
    full_func_name = _build_func_name(isa, dt_par, dt_par, dt_ret, f, masked_version=masked_version, lmul=lmul)
    print("static " + build_proto(funcs[f]["proto"], dt_par, dt_ret, isa, func_name, lmul, True, masked_version=masked_version) + " {", file=file)
    print("\tprintf(\"MIPP panic: '%s' is unimplemented.\\n\", \"" + full_func_name + "\");", file=file)
    print("\texit(-1);", file=file)
    print("}", file=file)

def _missing_emit_ifdef_end(ifd, file):
    """
    ifd != is_ifdef so not the same helper....
    """
    if ifd:
        print("#endif", file=file)

# ----------------------------------------------------------------------------------------------------------------------
# Generator of one function 
# ----------------------------------------------------------------------------------------------------------------------

def _gen_c_functions_one_unmasked(isa, file, funcs, f, ff, dt):
    """
    the big glue guy that calls all the helpers 
    to generate 1 fn for 1 dt. It's the logic of the big inner loop 
    of gen_c_functions.
    """
    dt_par, dt_ret = compute_dt_par_dt_ret(funcs, f, dt)
    dt_key = dt_par + "," + dt_ret

    if not is_missing_func(funcs, f, dt_key):
        _emit_already_implemented_message(f, dt_key, file)
        return

    pre_rendering = _render_template(isa, ff, dt_par, dt_ret)

    ph_ret = _parse_placeholders_or_skip(
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

    ifd_prev = _build_prev_exclusion_ifdef(funcs, f, dt_key, ff)

    _append_implem_status(funcs, f, dt_key, ff, ph_ret["requirements"])

    post_rendering = ph_ret["converted_ir"]

    ifd = _combine_current_ifdefs(funcs, f, dt_key, ifd_prev)
    print("", file=file)
    _emit_ifdef_begin_and_update_emulated(funcs, f, dt_key, ff, ifd, file)

    _emit_function_body(funcs, f, isa, dt, dt_par, dt_ret, ff, post_rendering, file)

    _emit_ifdef_end(ifd, file)

def _gen_c_function_one_masked(isa, file, funcs, f, ff, dt):
    
    dt_par, dt_ret = compute_dt_par_dt_ret(funcs, f, dt)
    dt_key = dt_par + "," + dt_ret

    mask_kind = ff["version"]
    mask_support = funcs[f]["mask_support"] if "mask_support" in funcs[f] else None
 
    #maybe not a panic but a skip would be more reasonable idk
    if not is_supported_mask_kind(mask_support, mask_kind):
        print("Panic: unsupported mask kind '" + mask_kind + "' for '" + f + "<" + dt_key + ">' function.")
        exit(-1)

    if not is_missing_masked_func(funcs, f, dt_key, mask_kind):
        _emit_already_implemented_message(f + "<" + mask_kind + ">", dt_key, file)
        return

    pre_rendering = _render_template(isa, ff, dt_par, dt_ret)
    
    ph_ret = _parse_placeholders_or_skip(
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
    post_rendering = ph_ret["converted_ir"]

    ifd_prev = _build_prev_exclusion_ifdef(funcs, f, dt_key, ff, mask_kind=mask_kind)

    _append_implem_status(funcs, f, dt_key, ff, ph_ret["requirements"], mask_kind=mask_kind)
 
    ifd = _combine_current_ifdefs(funcs, f, dt_key, ifd_prev, mask_kind=mask_kind)        
    print("", file=file)
    _emit_ifdef_begin_and_update_emulated(funcs, f, dt_key, ff, ifd, file, mask_kind=mask_kind)
    _emit_function_body(
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
    )
    
    _emit_ifdef_end(ifd, file)


#### WIP 

def _c_lmul_writer(f, dt, dt_par, dt_ret, isa, funcs, file, mask_type=None, lmul=0):
    _maybe_emit_lmul_separator(isa["name"], f, file)
    print("", file=file)

    if len(dt.split(',')) <= 1:
        func_name = build_func_name_short(isa, dt_par, f, lmul=0, masked_version=mask_type)
        func_name_lmul = build_func_name_short(isa, dt_par, f, lmul=lmul, masked_version=mask_type)
        func_name_half_lmul = build_func_name_short(isa, dt_par, f, lmul=int(lmul/2), masked_version=mask_type)
    else:
        func_name = build_func_name(isa, dt_par, dt_ret, f, lmul=0, masked_version=mask_type)
        func_name_lmul = build_func_name(isa, dt_par, dt_ret, f, lmul=lmul, masked_version=mask_type)
        func_name_half_lmul = build_func_name(isa, dt_par, dt_ret, f, lmul=int(lmul/2), masked_version=mask_type)
  
    
    if lmul == 1:
        #call non_lmul version
        print("static " + build_proto(funcs[f]["proto"], dt_par, dt_ret, isa, func_name_lmul, lmul=lmul, isa_name=True, masked_version=mask_type) + " {", file=file)
        print("\t" + build_call(funcs[f]["proto"], dt_par, dt_ret, isa, func_name, lmul=0, isa_name=True, masked_version=mask_type) + ";", file=file)
        print("}", file=file)
        return

    if not funcs[f]["horizontal"]:
        print("static " + build_proto(funcs[f]["proto"], dt_par, dt_ret, isa, func_name_lmul, lmul=lmul, isa_name=True, masked_version=mask_type) + " {", file=file)

        print(build_call_lmul(funcs[f]["proto"], dt_par, dt_ret, isa, func_name_half_lmul, lmul=lmul, isa_name=True, masked_version=mask_type), file=file)
        print("}", file=file)
    else:
        # print("\tprintf(\"MIPP panic: '%s' is unimplemented.\\n\", \""+func_name+"\");", file=file);
        # print("\texit(-1);", file=file);
        
        gen_c_horiz_lmul(
            isa=isa,
            file=file,
            funcs=funcs,
            f=f,
            dt=dt,
            lmul=lmul,
            implems_horiz_lmul_generic_emu=implems_horiz_lmul_generic_emu,
            func_name_for_panic=func_name,  # so the runtime message matches the wrapper name
            mask_type=mask_type,            # kept for future; currently stubs if not None
            dummy = True, # dummy argument to differentiate from version used in ci_generator. Will be removed asp
        )
    
def _gen_c_generic_one(isa, file, funcs, f, ff, dt):
    """
    same as _gen_c_functions_one_unmasked but for gen_c_generic_functions. 
    The logic difference is that it adds a guard for 
    the generic implementation if they are previous implementations 
    guarded by ifdefs. The generic implementation is guarded 
    by the negation of the conditions of previous implementations.
    """

    dt_par, dt_ret = compute_dt_par_dt_ret(funcs, f, dt)
    dt_key = dt_par + "," + dt_ret

    if not is_missing_func(funcs, f, dt_key):
        _emit_already_implemented_message(f, dt_key, file)
        return

    # Guard generic implementation with negation of previous guarded implementations, if any.
    _add_guard_if_isdef(funcs, f, dt_key, file)

    pre_rendering = _render_template(isa, ff, dt_par, dt_ret)

    # Same placeholder parse try/except printing + comment emission + skip semantics, delegated.
    ph_ret = _parse_placeholders_or_skip(
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

    post_rendering = ph_ret["converted_ir"]

    # Same C function emission as original, delegated (proto + body + short/long formatting).
    print("", file=file)
    _emit_function_body(
        funcs=funcs,
        f=f,
        isa=isa,
        dt=dt,
        dt_par=dt_par,
        dt_ret=dt_ret,
        ff=ff,
        post_rendering=post_rendering,
        file=file,
        level=2,
    )

    _add_endif_if_isdef(funcs, f, dt_key, file)

    # The whole purpose of generic implementations is that 
    # they don't have "if" conditions. 
    # removing "requirements" MIGHT be an issue. 
    # Not sure. 
    # Update : it was an issue.
    _remove_cond_implem_status(funcs, f, dt_key)
    _mark_as_implemented(funcs, f, dt_key)
    # add requirements to implem_status to prevent future generic implementations and to keep track of the fact that this function is now implemented
    _append_implem_status(funcs, f, dt_key, ff, ph_ret["requirements"])
    
 
def _gen_c_missing_one_dt(isa, file, funcs, f, dt, lmul=0):
    dt_par, dt_ret = compute_dt_par_dt_ret(None, None, dt, check_support=False)
    dt_key = dt_par + "," + dt_ret

    if is_missing_func(funcs, f, dt_key):
        ifd = _missing_build_negated_ifdef_for_existing_implems(funcs, f, dt_key)
        _missing_emit_ifdef_begin(ifd, file)

        func_name = _build_func_name(isa, dt, dt_par, dt_ret, f, lmul=lmul)
        
        _missing_emit_stub(file, funcs, f, dt_par, dt_ret, isa, func_name, lmul=lmul)
        _missing_emit_ifdef_end(ifd, file)

def _gen_c_missing_one_masked(isa, file, funcs, f, dt, mask_kind, lmul=0):
    dt_par, dt_ret = compute_dt_par_dt_ret(None, None, dt, check_support=False)
    dt_key = dt_par + "," + dt_ret

    mask_support = funcs[f]["mask_support"] if "mask_support" in funcs[f] else None
 
    #maybe not a panic but a skip would be more reasonable idk
    if not is_supported_mask_kind(mask_support, mask_kind):
        print("Panic: unsupported mask kind '" + mask_kind + "' for '" + f + "<" + dt_key + ">' function.")
        exit(-1)
 
    fully_missing = is_fully_missing_masked_func(funcs, f, dt_key, mask_kind)
    ifdef_guarded = is_ifdef_masked(funcs, f, dt_key, mask_kind)

    #if is fully mising => no guard, emit directly the stub
    #if is ifdef guarded missing => guard with the negation of the ifdef conditions of existing implementations and emit the stub in this guard
    func_name = _build_func_name(isa, dt, dt_par, dt_ret, f, masked_version=mask_kind, lmul=lmul)

    if fully_missing:
        _missing_emit_stub(file, funcs, f, dt_par, dt_ret, isa, func_name, masked_version=mask_kind, lmul=lmul)

    elif ifdef_guarded:
        ifd = _missing_build_negated_ifdef_for_existing_implems(funcs, f, dt_key, mask_kind=mask_kind)
        # check that ifd isn't a blank line 
    
        # use a regex to check if there are actual characters in a-z A-Z 0-9 or _ in ifd, if not consider it as blankmipp_sse_set_uint16
        if not re.search(r'[a-zA-Z0-9_]', ifd):

            return
       
        _missing_emit_ifdef_begin(ifd, file)
  
        _missing_emit_stub(file, funcs, f, dt_par, dt_ret, isa, func_name, masked_version=mask_kind, lmul=lmul)
  
        _missing_emit_ifdef_end(ifd, file)

def _gen_c_function_one_ldiv_avx(isa_base, isa_div, file, funcs, f, ff, dt, mask_kind, ldiv=-2):
    _maybe_emit_ldiv_separator(isa_base["name"], f, file)
    print("", file=file)
    """
    fairly straightforward the uint32_d2 avx function is JUST the uint32_m1 version of avx so wrapper to it.
    smth like : 

    static inline mipp_avx512_add_float32_d2(rvd_avx512_float32_d2 r0, rvd_avx512_float32_d2 r1){
        return mipp_avx_add_float32_m1(r0, r1);
    }
    a d4 function would be the sse version.
    """
    dt_par, dt_ret = compute_dt_par_dt_ret(funcs, f, dt)
    dt_key = dt_par + "," + dt_ret

    if len(dt.split(',')) <= 1:
        dt_par = dt.split(',')[0]
        dt_ret = dt.split(',')[0]
    else:
        dt_par = dt.split(',')[0]
        dt_ret = dt.split(',')[1]
        dtk = dt_par + "," + dt_ret
    dt_key = dt_par + "," + dt_ret

    if len(dt.split(',')) <= 1:
        func_name = build_func_name_short(isa_base, dt_par, f, True, masked_version=mask_kind, lmul=-2)
    else:
        func_name = build_func_name(isa_base, dt_par, dt_ret, f, True, masked_version=mask_kind, lmul=-2)

    print("static " + build_proto(funcs[f]["proto"], dt_par, dt_ret, isa_base, func_name, lmul=-2,  isa_name=True, masked_version=mask_kind) + " {", file=file)
   
    if len(dt.split(',')) <= 1:
        func_name_impl = build_func_name_short(isa_div, dt_par, f, True, masked_version=mask_kind)
    else:
        func_name_impl = build_func_name(isa_div, dt_par, dt_ret, f, True, masked_version=mask_kind)

    print("\t" + build_call(funcs[f]["proto"], dt_par, dt_ret, isa_div, func_name_impl, masked_version=mask_kind) + ";", file=file)
    print("}", file=file)

# ----------------------------------------------------------------------------------------------------------------------
# Generators
# ----------------------------------------------------------------------------------------------------------------------
def _get_candidate_reqs(cand, isa, funcs):
    if "reqs" in cand:
        return cand["reqs"]
    f = cand["f"]
    ff = cand["ff"]
    dt = cand["dt"]
    dt_par, dt_ret = compute_dt_par_dt_ret(funcs, f, dt)
    pre_rendering = _render_template(isa, ff, dt_par, dt_ret, func_name=f)
    try:
        reqs = get_requirements(pre_rendering, isa, funcs, f, dt_par, dt_ret)
    except Exception:
        reqs = {}
    cand["reqs"] = reqs
    return reqs

def _append_resolved_status(funcs, f, dt_key, mask_kind, cond, reqs):
    cur_implem_status = {"if": cond, "requirements": reqs}
    if mask_kind is None:
        if "implem_status" not in funcs[f]:
            funcs[f]["implem_status"] = {}
        if dt_key not in funcs[f]["implem_status"]:
            funcs[f]["implem_status"][dt_key] = []
        funcs[f]["implem_status"][dt_key].append(cur_implem_status)
    else:
        bucket = get_masked_bucket(funcs, f, dt_key, mask_kind, create_missing_bucket=True)
        bucket.append(cur_implem_status)

def _is_guard_dead_under_cond(guard, cond):
    """
    Returns True if `guard` is always False when `cond` is True,
    i.e. the function is compiled under #if !(<guard>), making any
    #if <guard> block inside the body unreachable dead code.
    """
    if not guard or guard == "0" or not cond:
        return False
    # Normalize whitespace before comparing
    neg_guard = f"!( {guard} )"
    return (neg_guard.replace(" ", "") == cond.replace(" ", ""))

def _gen_c_auto_scalar_fallback_one(isa, file, funcs, f, dt, mask_kind, cond, lmul=0):
    dt_par, dt_ret = compute_dt_par_dt_ret(None, None, dt, check_support=False)
    dt_key = dt_par + "," + dt_ret
    func_name = _build_func_name(isa, dt, dt_par, dt_ret, f, masked_version=mask_kind, lmul=lmul)
    
    if cond:
        print(f"#if {cond}", file=file)
        
    proto_str = build_proto(funcs[f]["proto"], dt_par, dt_ret, isa, func_name, lmul=lmul, isa_name=True, masked_version=mask_kind)
    print("static " + proto_str + " {", file=file)
    print("\t// Level 3 (Auto Scalar Fallback)", file=file)
    
    proto = funcs[f]["proto"]
    
    call_args = []
    
    cnt_reg = 0
    cnt_msk = 0
    cnt_val = 0
    cnt_ptr = 0
    
    if mask_kind is not None:
        msk_dt = datatypes[dt_par]
        if "gather" in f or "scatter" in f:
            msk_dt = datatypes["uint" + str(_get_dt_par_size(dt_par))]
        elif funcs[f]["proto"]["ret"].get("fixeddatatype"):
            msk_dt = datatypes[funcs[f]["proto"]["ret"]["fixeddatatype"]]
        m0_scalar_type = build_type("msk", msk_dt, isa_scalar, lmul, True, False)
        print(f"\t{m0_scalar_type} s_m0;", file=file)
        if isa.get("hw_mask", False):
            msk_dt_name = msk_dt["name"]
            reg_vector_type = build_reg(msk_dt, isa, lmul, True, False)
            reg_scalar_type = build_reg(msk_dt, isa_scalar, lmul, True, False)
            scalar_tomsk_func = _build_func_name(isa_scalar, msk_dt_name, msk_dt_name, msk_dt_name, "tomsk", lmul=lmul)
            if isa.get("hw_mask_is_bitfield", False):
                n_elements = isa["size"] // _get_dt_par_size(msk_dt_name)
                print(f"\tfor (int i = 0; i < {n_elements}; ++i) {{", file=file)
                print(f"\t\ts_m0.m[i] = (m0.m & (1ULL << i)) ? ~0 : 0;", file=file)
                print(f"\t}}", file=file)
            else:
                toreg_func = _build_func_name(isa, msk_dt_name, msk_dt_name, msk_dt_name, "toreg", lmul=lmul)
                if lmul < 0 and "if_ldiv" in isa["datatypes"].get(dt_par, {}):
                    guard = isa["datatypes"][dt_par]["if_ldiv"].get(str(-lmul), None)
                else:
                    guard = isa["datatypes"].get(dt_par, {}).get("if", None)
                if guard == "0" or _is_guard_dead_under_cond(guard, cond):
                    # Native path does not exist (or is dead code in this
                    # compilation context); use scalar fallback directly.
                    print(f"\tmemcpy(&s_m0, &m0, sizeof(s_m0));", file=file)
                else:
                    if guard:
                        print(f"#if {guard}", file=file)
                    print(f"\t{reg_vector_type} r_m0 = {toreg_func}(m0);", file=file)
                    print(f"\t{reg_scalar_type} s_r_m0;", file=file)
                    print(f"\tmemcpy(&s_r_m0, &r_m0, sizeof(s_r_m0));", file=file)
                    print(f"\ts_m0 = {scalar_tomsk_func}(s_r_m0);", file=file)
                    if guard:
                        print(f"#else", file=file)
                        print(f"\tmemcpy(&s_m0, &m0, sizeof(s_m0));", file=file)
                        print(f"#endif", file=file)
        else:
            print(f"\tmemcpy(&s_m0, &m0, sizeof(s_m0));", file=file)
        call_args.append("s_m0")
        cnt_msk += 1
        
        if mask_kind == "masks":
            rsrc_vector_type = build_reg(datatypes[dt_par], isa, lmul, True, False)
            rsrc_scalar_type = build_reg(datatypes[dt_par], isa_scalar, lmul, True, False)
            print(f"\t{rsrc_scalar_type} s_rsrc;", file=file)
            print(f"\tmemcpy(&s_rsrc, &rsrc, sizeof(s_rsrc));", file=file)
            call_args.append("s_rsrc")
            
    for arg in proto["args"]:
        arg_type_name = arg["type"]
        realdatatype = datatypes[dt_par]
        if arg.get("fixeddatatype"):
            if arg["fixeddatatype"] not in datatypes and arg["fixeddatatype"] in all_categories:
                dt_str = arg["fixeddatatype"] + str(_get_dt_par_size(dt_par))
                realdatatype = datatypes[dt_str]
            elif arg["fixeddatatype"] in datatypes:
                realdatatype = datatypes[arg["fixeddatatype"]]
        elif arg_type_name == "ret":
            realdatatype = datatypes[dt_ret]
            
        if arg_type_name == "reg" or arg_type_name == "ret":
            arg_name = f"r{cnt_reg}"
            cnt_reg += 1
            vector_type = build_type("reg", realdatatype, isa, lmul, True, False)
            scalar_type = build_type("reg", realdatatype, isa_scalar, lmul, True, False)
            print(f"\t{scalar_type} s_{arg_name};", file=file)
            print(f"\tmemcpy(&s_{arg_name}, &{arg_name}, sizeof(s_{arg_name}));", file=file)
            call_args.append(f"s_{arg_name}")
        elif arg_type_name == "msk":
            arg_name = f"m{cnt_msk}"
            cnt_msk += 1
            vector_type = build_type("msk", realdatatype, isa, lmul, True, False)
            scalar_type = build_type("msk", realdatatype, isa_scalar, lmul, True, False)
            print(f"\t{scalar_type} s_{arg_name};", file=file)
            if isa.get("hw_mask", False):
                if isa.get("hw_mask_is_bitfield", False) and f in ["toreg", "tomsk", "cast_k"]:
                    n_elements = 512 // _get_dt_par_size(realdatatype["name"])
                    print(f"\tfor (int i = 0; i < {n_elements}; ++i) {{", file=file)
                    print(f"\t\ts_{arg_name}.m[i] = ({arg_name}.m & (1ULL << i)) ? ~0 : 0;", file=file)
                    print(f"\t}}", file=file)
                else:
                    realdatatype_name = realdatatype["name"]
                    reg_vector_type = build_reg(realdatatype, isa, lmul, True, False)
                    reg_scalar_type = build_reg(realdatatype, isa_scalar, lmul, True, False)
                    toreg_func = _build_func_name(isa, realdatatype_name, realdatatype_name, realdatatype_name, "toreg", lmul=lmul)
                    scalar_tomsk_func = _build_func_name(isa_scalar, realdatatype_name, realdatatype_name, realdatatype_name, "tomsk", lmul=lmul)
                    if lmul < 0 and "if_ldiv" in isa["datatypes"].get(realdatatype_name, {}):
                        arg_guard = isa["datatypes"][realdatatype_name]["if_ldiv"].get(str(-lmul), None)
                    else:
                        arg_guard = isa["datatypes"].get(realdatatype_name, {}).get("if", None)
                    if arg_guard == "0" or _is_guard_dead_under_cond(arg_guard, cond):
                        # Native path does not exist (or is dead code in this
                        # compilation context); use scalar fallback directly.
                        print(f"\tmemcpy(&s_{arg_name}, &{arg_name}, sizeof(s_{arg_name}));", file=file)
                    else:
                        if arg_guard:
                            print(f"#if {arg_guard}", file=file)
                        print(f"\t{reg_vector_type} r_{arg_name} = {toreg_func}({arg_name});", file=file)
                        print(f"\t{reg_scalar_type} s_r_{arg_name};", file=file)
                        if isa.get("hw_mask_extract_via_store", False):
                            store_func = _build_func_name(isa, realdatatype_name, realdatatype_name, realdatatype_name, "store", lmul=lmul)
                            print(f"\t{store_func}(s_r_{arg_name}.r, r_{arg_name});", file=file)
                        else:
                            print(f"\tmemcpy(&s_r_{arg_name}, &r_{arg_name}, sizeof(s_r_{arg_name}));", file=file)
                        print(f"\ts_{arg_name} = {scalar_tomsk_func}(s_r_{arg_name});", file=file)
                        if arg_guard:
                            print(f"#else", file=file)
                            print(f"\tmemcpy(&s_{arg_name}, &{arg_name}, sizeof(s_{arg_name}));", file=file)
                            print(f"#endif", file=file)
            else:
                print(f"\tmemcpy(&s_{arg_name}, &{arg_name}, sizeof(s_{arg_name}));", file=file)
            call_args.append(f"s_{arg_name}")
        elif arg_type_name == "vindex":
            arg_name = "vi"
            same_size_integer_datatype = find_one_data_types_from({"n_bits": realdatatype["n_bits"], "category": cint})
            vector_type = build_reg(same_size_integer_datatype, isa, lmul, True, False)
            scalar_type = build_reg(same_size_integer_datatype, isa_scalar, lmul, True, False)
            print(f"\t{scalar_type} s_vi;", file=file)
            if isa["name"] == "rvv":
                vi_dt_name = same_size_integer_datatype["name"]
                store_func = _build_func_name(isa, vi_dt_name, vi_dt_name, vi_dt_name, "store", lmul=lmul)
                print(f"\t{store_func}(s_vi.r, vi);", file=file)
            else:
                print(f"\tmemcpy(&s_vi, &vi, sizeof(s_vi));", file=file)
            call_args.append("s_vi")
        elif arg_type_name == "val":
            arg_name = f"v{cnt_val}"
            cnt_val += 1
            call_args.append(arg_name)
        elif arg_type_name == "ptr":
            arg_name = f"p{cnt_ptr}"
            cnt_ptr += 1
            call_args.append(arg_name)
        elif arg_type_name == "Nele":
            call_args.append("vals")
            
    scalar_func_name = _build_func_name(isa_scalar, dt, dt_par, dt_ret, f, masked_version=mask_kind, lmul=lmul)
    call_args_str = ", ".join(call_args)
    
    ret_type_name = proto["ret"]["type"]
    if ret_type_name == "reg" or ret_type_name == "msk":
        realdatatype_ret = datatypes[dt_ret]
        if proto["ret"].get("fixeddatatype"):
            realdatatype_ret = datatypes[proto["ret"]["fixeddatatype"]]
        scalar_ret_type = build_type(ret_type_name, realdatatype_ret, isa_scalar, lmul, True, False)
        vector_ret_type = build_type(ret_type_name, realdatatype_ret, isa, lmul, True, False)
        
        print(f"\t{scalar_ret_type} sres = {scalar_func_name}({call_args_str});", file=file)
        use_safe_conversion = (ret_type_name == "msk") and isa.get("hw_mask", False)
        if use_safe_conversion:
            if isa.get("hw_mask_is_bitfield", False) and f in ["toreg", "tomsk", "cast_k"]:
                n_elements = 512 // _get_dt_par_size(realdatatype_ret["name"])
                print(f"\t{vector_ret_type} res;", file=file)
                print(f"\tres.m = 0;", file=file)
                print(f"\tfor (int i = 0; i < {n_elements}; ++i) {{", file=file)
                print(f"\t\tif (sres.m[i]) {{", file=file)
                print(f"\t\t\tres.m |= (1ULL << i);", file=file)
                print(f"\t\t}}", file=file)
                print(f"\t}}", file=file)
            else:
                realdatatype_ret_name = realdatatype_ret["name"]
                reg_vector_type = build_reg(realdatatype_ret, isa, lmul, True, False)
                reg_scalar_type = build_reg(realdatatype_ret, isa_scalar, lmul, True, False)
                scalar_toreg_func = _build_func_name(isa_scalar, realdatatype_ret_name, realdatatype_ret_name, realdatatype_ret_name, "toreg", lmul=lmul)
                tomsk_func = _build_func_name(isa, realdatatype_ret_name, realdatatype_ret_name, realdatatype_ret_name, "tomsk", lmul=lmul)
                # Read guard from if_ldiv when lmul < 0 (ldiv), just like the arg path does.
                # This prevents infinite recursion when if_ldiv == "0" (no native type for that ldiv).
                if lmul < 0 and "if_ldiv" in isa["datatypes"].get(realdatatype_ret_name, {}):
                    guard = isa["datatypes"][realdatatype_ret_name]["if_ldiv"].get(str(-lmul), None)
                else:
                    guard = isa["datatypes"].get(dt_ret, {}).get("if", None)
                if guard == "0":
                    # No native type for this ldiv: use memcpy fallback directly, no recursive call
                    print(f"\t{vector_ret_type} res;", file=file)
                    print(f"\tmemcpy(&res, &sres, sizeof(res));", file=file)
                else:
                    if guard:
                        print(f"#if {guard}", file=file)
                    print(f"\t{reg_scalar_type} s_r_res = {scalar_toreg_func}(sres);", file=file)
                    print(f"\t{reg_vector_type} r_res;", file=file)
                    print(f"\tmemcpy(&r_res, &s_r_res, sizeof(r_res));", file=file)
                    print(f"\t{vector_ret_type} res = {tomsk_func}(r_res);", file=file)
                    if guard:
                        print(f"#else", file=file)
                        print(f"\t{vector_ret_type} res;", file=file)
                        print(f"\tmemcpy(&res, &sres, sizeof(res));", file=file)
                        print(f"#endif", file=file)
        else:
            print(f"\t{vector_ret_type} res;", file=file)
            print(f"\tmemcpy(&res, &sres, sizeof(res));", file=file)
        print(f"\treturn res;", file=file)
    elif ret_type_name == "val":
        print(f"\treturn {scalar_func_name}({call_args_str});", file=file)
    else:
        print(f"\t{scalar_func_name}({call_args_str});", file=file)
        
    print("}", file=file)
    if cond:
        print("#endif", file=file)

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

def _resolve_and_emit_missing_functions(isa, file, funcs, lmul=0, emit_separators=False):
    is_inc_mgr = hasattr(file, "get_fd")
    
    candidates_map = {}
    collected_candidates = isa.get("candidates", [])
    
    for f in funcs:
        for dt in funcs[f]["datatypes"]:
            dt_par, dt_ret = compute_dt_par_dt_ret(None, None, dt, check_support=False)
            dt_key = dt_par + "," + dt_ret
            
            mask_kinds = [None]
            if "mask_support" in funcs[f]:
                support = funcs[f]["mask_support"]
                if support.is_maskable():
                    mask_kinds.append("mask")
                if support.is_maskzable():
                    mask_kinds.append("maskz")
                if support.is_masksable():
                    mask_kinds.append("masks")
                    
            for mask_kind in mask_kinds:
                key = (f, dt_key, mask_kind)
                candidates_map[key] = []
                
                for c in collected_candidates:
                    c_f = c["f"]
                    c_dt = c["dt"]
                    c_dt_par, c_dt_ret = compute_dt_par_dt_ret(funcs, c_f, c_dt)
                    c_dt_key = c_dt_par + "," + c_dt_ret
                    c_mask_kind = c["ff"].get("version", None)
                    if c_f == f and c_dt_key == dt_key and c_mask_kind == mask_kind:
                        candidates_map[key].append(c)
                
                if isa["name"] != "scalar":
                    auto_scalar_reqs = {}
                    
                    if isa.get("hw_mask_requires_toreg", False):
                        if not (isa.get("hw_mask_is_bitfield", False) and f in ["toreg", "tomsk", "cast_k"]):
                            # Mask arguments need toreg/tomsk on dt_par
                            has_msk_arg = any(arg["type"] == "msk" for arg in funcs[f]["proto"]["args"]) or mask_kind is not None
                            if has_msk_arg:
                                single_dt_par = dt_par.split(",")[0]
                                req_dt_par = single_dt_par + "," + single_dt_par
                                auto_scalar_reqs.setdefault("toreg", []).append(req_dt_par)
                                auto_scalar_reqs.setdefault("tomsk", []).append(req_dt_par)
                                if isa.get("hw_mask_extract_via_store", False):
                                    auto_scalar_reqs.setdefault("store", []).append(req_dt_par)
                            
                            # Mask return needs toreg/tomsk on dt_ret
                            if funcs[f]["proto"]["ret"]["type"] == "msk":
                                single_dt_ret = dt_ret.split(",")[0]
                                req_dt_ret = single_dt_ret + "," + single_dt_ret
                                if req_dt_ret not in auto_scalar_reqs.get("toreg", []):
                                    auto_scalar_reqs.setdefault("toreg", []).append(req_dt_ret)
                                    auto_scalar_reqs.setdefault("tomsk", []).append(req_dt_ret)
                                    if isa.get("hw_mask_extract_via_store", False):
                                        if req_dt_ret not in auto_scalar_reqs.get("store", []):
                                            auto_scalar_reqs.setdefault("store", []).append(req_dt_ret)

                    # vindex arguments need store for the corresponding int type (RVV specific fallback logic)
                    if isa["name"] == "rvv":
                        for arg in funcs[f]["proto"]["args"]:
                            if arg["type"] == "vindex":
                                single_dt_par = dt_par.split(",")[0]
                                c_int = datatypes[single_dt_par].get("category", "int")
                                same_size_integer_datatype = find_one_data_types_from({"n_bits": datatypes[single_dt_par]["n_bits"], "category": c_int})
                                vi_dt_name = same_size_integer_datatype["name"]
                                req_vi_dt = vi_dt_name + "," + vi_dt_name
                                if req_vi_dt not in auto_scalar_reqs.get("store", []):
                                    auto_scalar_reqs.setdefault("store", []).append(req_vi_dt)

                    auto_scalar_cand_if = ""
                    if isa["name"] == "rvv" and lmul < 0:
                        single_dt = dt_par.split(",")[0]
                        if "width" in isa.get("datatypes", {}).get(single_dt, {}):
                            width = isa["datatypes"][single_dt]["width"]
                            req_vlen = int(width) * abs(lmul)
                            vlen_guard = f"__riscv_v_fixed_vlen >= {req_vlen}"
                            base_guard = isa["datatypes"][single_dt].get("if", "")
                            if base_guard:
                                auto_scalar_cand_if = f"({base_guard}) && {vlen_guard}"
                            else:
                                auto_scalar_cand_if = vlen_guard

                    candidates_map[key].append({
                        "type": "auto_scalar",
                        "f": f,
                        "dt_key": dt_key,
                        "dt_par": dt_par,
                        "dt_ret": dt_ret,
                        "mask_kind": mask_kind,
                        "level": 3,
                        "reqs": auto_scalar_reqs,
                        "ff": {"if": auto_scalar_cand_if}
                    })
                    
                candidates_map[key].append({
                    "type": "stub",
                    "f": f,
                    "dt_key": dt_key,
                    "dt_par": dt_par,
                    "dt_ret": dt_ret,
                    "mask_kind": mask_kind,
                    "level": 4,
                    "reqs": {}
                })
                
                candidates_map[key].sort(key=lambda c: c["level"])
                
    isa_known_true = [isa["define"]] if "define" in isa and isa["define"] else []

    def normalize_cond(c):
        return simplify_cond_str(c, known_true_conds=isa_known_true)

    def negate_cond(c):
        return tool_negate_cond(c)

    def are_conds_mutually_exclusive(c1, c2):
        return tool_are_conds_mutually_exclusive(c1, c2, known_true_conds=isa_known_true)

    def intersect_conds(c1, c2):
        return tool_intersect_conds(c1, c2, known_true_conds=isa_known_true)

    def is_req_satisfied(req_f, req_dt_key, target_cond, working_impls):
        if target_cond is None:
            return True
        req_key = (req_f, req_dt_key, None)
        if req_key not in working_impls:
            return False
        norm_target = normalize_cond(target_cond)
        if norm_target == "":
            return True
        for w_cond in working_impls[req_key]:
            norm_w = normalize_cond(w_cond)
            if norm_w == "" or ("define" in isa and isa["define"] and norm_w == normalize_cond(isa["define"])):
                return True
            if norm_w == norm_target:
                return True
        return False

    resolved = {key: [] for key in candidates_map}
    remaining_conds = {key: "" for key in candidates_map}
    working_impls = {key: [] for key in candidates_map}
    
    # Pre-resolve candidates that were already emitted
    for key in candidates_map:
        for cand in candidates_map[key]:
            if cand.get("emitted", False):
                cand_if = cand["ff"].get("if", "")
                if cand["type"] == "native_or_emu" and not cand_if and "define" in isa and isa["define"]:
                    cand_if = isa["define"]

                restricted_target_cond = normalize_cond(cand_if)
                resolved[key].append((cand, restricted_target_cond))
                cand["resolved"] = True

                if cand["level"] < 4:
                    working_impls[key].append(restricted_target_cond)
                    if restricted_target_cond == "":
                        working_impls[key] = [""]

                neg_resolved = negate_cond(restricted_target_cond)
                new_rem = intersect_conds(remaining_conds[key], neg_resolved)
                remaining_conds[key] = new_rem

    max_level = 2
    changed = True
    while changed:
        changed = False
        for key in candidates_map:
            f, dt_key, mask_kind = key
            rem_cond = remaining_conds[key]
            if rem_cond is None:
                continue
                
            for cand in candidates_map[key]:
                if cand.get("resolved", False):
                    continue
                if cand["level"] > max_level:
                    continue
                    
                cand_if = ""
                if cand["type"] in ["native_or_emu", "generic_emu", "auto_scalar"]:
                    cand_if = cand["ff"].get("if", "")
                    if cand["type"] == "native_or_emu" and not cand_if and "define" in isa and isa["define"]:
                        cand_if = isa["define"]
                    
                target_cond = intersect_conds(cand_if, rem_cond)
                if target_cond is None:
                    continue
                    
                reqs = _get_candidate_reqs(cand, isa, funcs)
                deps_satisfied = True
                restricted_target_cond = target_cond
                for req_f in reqs:
                    for req_dt_key in reqs[req_f]:
                        req_key = (req_f, req_dt_key, None)
                        # For auto_scalar candidates, toreg/tomsk/store deps on
                        # conditional types (those with an "if" guard in the ISA)
                        # are optional: the emitted code wraps the call in
                        # #if <type_guard> ... #else memcpy(...) #endif,
                        # so the function body is always valid regardless of
                        # whether the type's native path is reachable.
                        if cand["type"] == "auto_scalar" and req_f in ("toreg", "tomsk", "store"):
                            req_dt_par = req_dt_key.split(",")[0]
                            req_type_guard = isa.get("datatypes", {}).get(req_dt_par, {}).get("if", None)
                            if req_type_guard and req_type_guard != "0":
                                # Dep is conditional in the ISA; the fallback
                                # memcpy branch handles the case where the native
                                # type doesn't exist, so skip this check.
                                continue
                        if req_key not in working_impls:
                            deps_satisfied = False
                            break
                        compat_conds = []
                        for w_cond in working_impls[req_key]:
                            if not are_conds_mutually_exclusive(restricted_target_cond, w_cond):
                                compat_conds.append(w_cond)
                        if not compat_conds:
                            deps_satisfied = False
                            break
                        if "" in compat_conds:
                            union_cond = ""
                        else:
                            union_cond = " || ".join(f"({w})" for w in compat_conds)
                        restricted_target_cond = intersect_conds(restricted_target_cond, union_cond)
                        if restricted_target_cond is None:
                            deps_satisfied = False
                            break
                    if not deps_satisfied:
                        break
                        
                if deps_satisfied:
                    restricted_target_cond = normalize_cond(restricted_target_cond)
                    resolved[key].append((cand, restricted_target_cond))
                    cand["resolved"] = True
                    
                    if cand["level"] < 4:
                        working_impls[key].append(restricted_target_cond)
                        if restricted_target_cond == "":
                            working_impls[key] = [""]
                            
                    neg_resolved = negate_cond(restricted_target_cond)
                    new_rem = intersect_conds(rem_cond, neg_resolved)
                    remaining_conds[key] = new_rem
                    
                    changed = True
                    break
                    
        if not changed and max_level < 4:
            max_level += 1
            changed = True
                    
    # 1. Register resolved statuses upfront so parse_placeholders knows what is implemented
    for key in resolved:
        f, dt_key, mask_kind = key
        for cand, cond in resolved[key]:
            if cond == "0":
                continue
            reqs = _get_candidate_reqs(cand, isa, funcs)
            # For auto_scalar candidates, toreg/tomsk/store requirements on
            # conditional types are handled inline with a #if guard + memcpy
            # fallback in the generated code, and are NOT structural deps that
            # build_ifdef_rec should follow. Strip them out before registering
            # to avoid infinite recursion.
            if cand["type"] == "auto_scalar":
                filtered_reqs = {}
                for req_f, req_dt_keys in reqs.items():
                    if req_f in ("toreg", "tomsk", "store"):
                        kept = []
                        for req_dt_key in req_dt_keys:
                            req_dt_par = req_dt_key.split(",")[0]
                            req_type_guard = isa.get("datatypes", {}).get(req_dt_par, {}).get("if", None)
                            if not (req_type_guard and req_type_guard != "0"):
                                kept.append(req_dt_key)
                        if kept:
                            filtered_reqs[req_f] = kept
                    else:
                        filtered_reqs[req_f] = req_dt_keys
                reqs = filtered_reqs
            _append_resolved_status(funcs, f, dt_key, mask_kind, cond, reqs)

    # 2. Write code to files
    for f in funcs:
        file_w = file.get_fd(isa["name"], f) if is_inc_mgr else file
        if emit_separators and is_inc_mgr:
            if lmul in [2, 4, 8]:
                _maybe_emit_lmul_separator(isa["name"], f, file_w)
            elif lmul < 0:
                _maybe_emit_ldiv_separator(isa["name"], f, file_w)
        
        # Emit forward declarations first to prevent order-of-declaration issues (e.g. set_k float64 calling set_k int64)
        for dt in funcs[f]["datatypes"]:
            dt_par, dt_ret = compute_dt_par_dt_ret(None, None, dt, check_support=False)
            dt_key = dt_par + "," + dt_ret
            
            mask_kinds = [None]
            if "mask_support" in funcs[f]:
                support = funcs[f]["mask_support"]
                if support.is_maskable():
                    mask_kinds.append("mask")
                if support.is_maskzable():
                    mask_kinds.append("maskz")
                if support.is_masksable():
                    mask_kinds.append("masks")
                    
            for mask_kind in mask_kinds:
                key = (f, dt_key, mask_kind)
                if resolved[key]:
                    has_active = any(cond != "0" for cand, cond in resolved[key])
                    if has_active:
                        func_name = _build_func_name(isa, dt, dt_par, dt_ret, f, masked_version=mask_kind, lmul=lmul)
                        proto_str = build_proto(funcs[f]["proto"], dt_par, dt_ret, isa, func_name, lmul=lmul, isa_name=True, masked_version=mask_kind)
                        print("static " + proto_str + ";", file=file_w)
                        
        for dt in funcs[f]["datatypes"]:
            dt_par, dt_ret = compute_dt_par_dt_ret(None, None, dt, check_support=False)
            dt_key = dt_par + "," + dt_ret
            
            mask_kinds = [None]
            if "mask_support" in funcs[f]:
                support = funcs[f]["mask_support"]
                if support.is_maskable():
                    mask_kinds.append("mask")
                if support.is_maskzable():
                    mask_kinds.append("maskz")
                if support.is_masksable():
                    mask_kinds.append("masks")
                    
            for mask_kind in mask_kinds:
                key = (f, dt_key, mask_kind)
                for cand, cond in resolved[key]:
                    if cond == "0":
                        continue
                    
                    if cand["type"] in ["native_or_emu", "generic_emu"]:
                        pre_rendering = _render_template(isa, cand["ff"], dt_par, dt_ret, func_name=f, lmul=lmul)
                        ph_ret = parse_placeholders(pre_rendering, isa, funcs, f, dt_par, dt_ret, lmul=lmul)
                        post_rendering = ph_ret["converted_ir"]
                        
                        if not cand.get("emitted", False):
                            print("", file=file_w)
                            if cond != "":
                                print(f"#if {cond}", file=file_w)
                            _emit_function_body(funcs, f, isa, dt, dt_par, dt_ret, cand["ff"], post_rendering, file_w, masked_version=mask_kind, level=cand["level"], lmul=lmul)
                            if cond != "":
                                print("#endif", file=file_w)
                            
                    elif cand["type"] == "auto_scalar":
                        _gen_c_auto_scalar_fallback_one(isa, file_w, funcs, f, dt, mask_kind, cond, lmul=lmul)
                        
                    elif cand["type"] == "stub":
                        if cond != "":
                            print(f"#if {cond}", file=file_w)
                        func_name = _build_func_name(isa, dt, dt_par, dt_ret, f, masked_version=mask_kind, lmul=lmul)
                        _missing_emit_stub(file_w, funcs, f, dt_par, dt_ret, isa, func_name, masked_version=mask_kind, lmul=lmul)
                        if cond != "":
                            print("#endif", file=file_w)

def gen_c_missing_functions(isa, file, funcs):
    _resolve_and_emit_missing_functions(isa, file, funcs, lmul=0, emit_separators=False)

def gen_c_missing_functions_lmul(isa, file, funcs, lmul):
    """
    Generate missing variants for a given LMUL, including masked+LMUL missing stubs.
    Intended for RVV.
    """
    _resolve_and_emit_missing_functions(isa, file, funcs, lmul=lmul, emit_separators=True)

def _gen_c_horiz_lmul_one(isa, file, funcs, f, ff, dt, lmul, mkind=None, dummy=False):
    """
    Emit one horizontal LMUL variant body (LMUL>1) for one function+datatype,
    using custom generic emulation templates (implems_horiz_lmul_generic_emu).

    Option-B workaround: pre-mark certain dependencies as "implemented" in funcs
    so parse_placeholders() does not skip.
    """
    dt_par, dt_ret = compute_dt_par_dt_ret(funcs, f, dt)
    dt_key = dt_par + "," + dt_ret

    if _rvv_seen_lmul(funcs, f, dt_key, lmul) and mkind is None:
        return

    # Current horiz templates (tpl_set) reference %set<...>% recursively (tp/2).
    # parse_placeholders requires funcs["set"].implem_status[dep_dt_key] to exist.
    #
    # We mark base set<dt,dt> as implemented; this is enough to avoid the exception.
    # (If you later add more horiz templates that reference other functions, extend this.)

    # the generic emu entries have a "dependencies" key. That list the functions that need 2 be included for them to work. We should append 
    # those dependencies to ensure their inclusion.
    
    
    def _ensure_fake_implemented(func_name, dep_dt_key):
        if func_name not in funcs:
            return
        if "implem_status" not in funcs[func_name]:
            funcs[func_name]["implem_status"] = {}
        if dep_dt_key not in funcs[func_name]["implem_status"]:
            funcs[func_name]["implem_status"][dep_dt_key] = [{"if": "", "requirements": {}}]

   
    #_ensure_fake_implemented(f, dt_key)
    # -------------------------------------------------------------------------------

    ff_local = dict(ff)
    ff_local["type"] = "emulated"

    pre_rendering = _render_template(isa, ff_local, dt_par, dt_ret, func_name=f, lmul=lmul)
    requirements = get_requirements(
        ir=pre_rendering,
        isa=isa,
        funcs=funcs,
        func_name=f,
        dt_par=dt_par,
        dt_ret=dt_ret,
        lmul=lmul,
        isa_name=False,
    )
    
    for req in requirements: # we still need to include the 
    # requirements != to f. This is done in ci_generator for simplicity's sake.
        for req_dt_key in requirements[req]:
            _ensure_fake_implemented(req, req_dt_key)
    

    isa_name = dummy
    ph_ret = _parse_placeholders_or_skip(
        pre_rendering=pre_rendering,
        isa=isa,
        funcs=funcs,
        f=f,
        dt_par=dt_par,
        dt_ret=dt_ret,
        dt_key=dt_key,
        file=file,
        lmul=lmul,
        isa_name = isa_name,
    )
    if ph_ret is None:
        return

    # Hack : change the function call name in the generated ir. For instance 
    # hadd_float32_m2 -> hadd_float32_maskz_m2 for the maskz version of the template.

    # We also need to add the extra argument / arguments after start of the function 
    # i.e : 
    # if mask / maskz : 
    # -> hadd_float32_m2(r0.r1); 
    #    hadd_float32_m2(r0.r2);
    #   becomes:
    # hadd_float32_maskz_m2(m0.m1, r0.r1)
    # hadd_float32_maskz_m2(m0.m2, r0.r2)

    # masks : 
    # -> set_float32_m2(vals);
    #    set_float32_m2(vals+n);
    #    becomes:
    # set_float32_masks_m2(m0.m1, rsrc.r1, vals);
    # set_float32_masks_m2(m0.m2, rsrc.r2, vals+n);

    # if mkind is not None and lmul >= 2:
    #     l2 = int(lmul) // 2
    #     ph_ret["converted_ir"] = ph_ret["converted_ir"].replace(f"{f}_{dt_par}_m{int(l2)}", f"{f}_{dt_par}_{mkind}_m{int(l2)}")


    # if dummy is true, then add prototype of the function 
    if dummy:
        dt_par, dt_ret = compute_dt_par_dt_ret(funcs, f, dt)
        func_name = _build_func_name(isa, dt, dt_par, dt_ret, f, masked_version=mkind, lmul=lmul)
        proto = build_proto(funcs[f]["proto"], dt_par, dt_ret, isa, func_name, lmul=lmul, isa_name=True, masked_version=mkind)
        print("", file=file)
        print("static " + proto + " {", file=file)
        print("\t// Level 2 (Generic Emulated)", file=file)

    if (mkind == "maskz" or mkind == "mask") and lmul >= 2:
        l2 = int(lmul) // 2
        # This is a bit hacky but we want to add the mask argument at the right place in the generated IR. 
        # We look for the first occurrence of the function call in the generated IR and we add the mask argument after the opening parenthesis. 
        # This relies on the fact that in our templates, the first occurrence of the function call is the one we want to modify, which is true for our current horiz_lmul templates.
        ph_ret["converted_ir"] = ph_ret["converted_ir"].replace(f"{f}_{dt_par}_m{int(l2)}(", f"{f}_{dt_par}_{mkind}_m{int(l2)}(m0.m1, ", 1)
        ph_ret["converted_ir"] = ph_ret["converted_ir"].replace(f"{f}_{dt_par}_m{int(l2)}(", f"{f}_{dt_par}_{mkind}_m{int(l2)}(m0.m2, ", 1)
        # if dummy mkind already in
    if (mkind == "masks") and lmul >= 2:
        l2 = int(lmul) // 2
        ph_ret["converted_ir"] = ph_ret["converted_ir"].replace(f"{f}_{dt_par}_m{int(l2)}(", f"{f}_{dt_par}_{mkind}_m{int(l2)}(m0.m1, rsrc.r1, ", 1)
        ph_ret["converted_ir"] = ph_ret["converted_ir"].replace(f"{f}_{dt_par}_m{int(l2)}(", f"{f}_{dt_par}_{mkind}_m{int(l2)}(m0.m2, rsrc.r2, ", 1)

    print("\t", end="", file=file)
    print(ph_ret["converted_ir"], file=file)

    if dummy:
        print("}", file=file)

    _rvv_mark_lmul_seen(funcs, f, dt_key, lmul)    

    # add include deps
    # print(ph_ret["requirements"]) 
    # print("Debug: adding requirements for '" + f + "<" + dt_key + ">' function: " + str(ph_ret["requirements"]))
    _append_implem_status(funcs, f, dt_key, ff, ph_ret["requirements"])

def gen_c_horiz_lmul(isa, file, funcs, f, dt, lmul, implems_horiz_lmul_generic_emu, func_name_for_panic=None, mask_type=None, dummy=False):
    """
    Generate LMUL variants for *horizontal* functions by leveraging custom generic emulation
    templates defined in implems_horiz_lmul_generic_emu.

    Intended to be called from ci_generator.py inside the non-RVV path for LMUL>1.

    If there is no template available, we emit a runtime stub (printf + exit),
    instead of hard-panicking during codegen.

    Notes:
      - For now: unmasked only. (mask_type is accepted for future extension but ignored unless you add templates)
    """
    if lmul <= 1:
        return

    if f not in funcs:
        # If ci_generator calls us with a bad key, keep existing behavior.
        print("Panic: '" + f + "' function does not exist.")
        exit(-1)

    if not funcs[f].get("horizontal", False):
        return

    if mask_type is not None: # I think only hadd, hmul hmin and hmax are masked + horizontal. 
        mask_support = funcs[f]["mask_support"]
        if not mask_support.is_supported(mask_type):
            print(f"Panic: unsupported mask type '{mask_type}' for '{f}' function.")
            exit(-1)
        

    # No template available => emit stub (runtime panic), not a codegen panic.
    if f not in implems_horiz_lmul_generic_emu:
        name = func_name_for_panic or f
        print(f"\tprintf(\"MIPP panic: '%s' is unimplemented.\\n\", \"{name}_m{int(lmul)}\");", file=file)
        print("\texit(-1);", file=file)
        return

    emitted_any = False
    for ff in implems_horiz_lmul_generic_emu[f]:
        # Accept only the dedicated horiz_lmul templates (defensive)
        if "version" in ff and ff["version"] not in (None, "", "horiz_lmul"):
            continue

        # if "version" == "maskz": 
        #     print("Debug: found maskz version for '" + f)

        # Respect datatype list when present
        if "datatypes" in ff and dt not in ff["datatypes"]:
            continue

        _gen_c_horiz_lmul_one(isa=isa, file=file, funcs=funcs, f=f, ff=ff, dt=dt, lmul=lmul, mkind=mask_type, dummy=dummy)
        emitted_any = True

    if not emitted_any:
        # Template exists but doesn't cover this dt => stub.
        name = func_name_for_panic or f
        print(f"\tprintf(\"MIPP panic: '%s' is unimplemented.\\n\", \"{name}_m{int(lmul)}\");", file=file)
        print("\texit(-1);", file=file)

def gen_c_lmul(isa, include_manager, funcs):
    """
    Generate LMUL variants for all functions and datatypes by leveraging the _c_lmul_writer helper.

    Intended to be called from ci_generator.py inside the non-RVV path for LMUL>1.

    For horizontal functions, this will generate direct LMUL variants (e.g., hadd_float32_m4)
    that call the corresponding horiz_lmul generic emulation templates (e.g., hadd_float32_horiz_lmul_m4).
    The horiz_lmul templates are responsible for the actual emulation logic, and can be shared across multiple functions.
    This avoids codegen-time combinatorial explosion while still providing LMUL support for horizontal functions.
    For non-horizontal functions, it generates direct LMUL variants that call the corresponding non-LMUL version (e.g., add_float32_m4 calls add_float32).

    Notes:
      - For now: unmasked only. (mask_type is accepted for future extension but ignored unless you add templates)
      - This is separate from gen_c_horiz_lmul() because we want to generate direct LMUL variants for all functions, not just horizontal ones, and we want to keep the horiz_lmul template logic separate.
    """
    for f in funcs:
        file_w = include_manager.get_fd(isa["name"], f)

        for dt in funcs[f]["datatypes"]:
            dt_par, dt_ret = compute_dt_par_dt_ret(funcs, f, dt)


            for lmul in all_lmul:
                _c_lmul_writer(f=f, dt=dt, dt_par=dt_par, dt_ret=dt_ret, isa=isa, funcs=funcs, file=file_w, lmul=lmul)
        
            for lmul in all_lmul:
                mask_status = ""
                if "mask_support" in funcs[f] :
                    mask_status = funcs[f]["mask_support"]
                else :
                    mask_status = MaskSupport()

                if not mask_status.is_any_mask() :
                    continue
                if mask_status.is_maskable() :
                    _c_lmul_writer(f, dt, dt_par, dt_ret, isa, funcs, file_w, mask_type="mask", lmul=lmul)
                
                if mask_status.is_maskzable() :
                    _c_lmul_writer(f, dt, dt_par, dt_ret, isa, funcs, file_w, mask_type="maskz", lmul=lmul)
                if mask_status.is_masksable() :			
                    _c_lmul_writer(f, dt, dt_par, dt_ret, isa, funcs, file_w, mask_type="masks", lmul=lmul)

def gen_c_ldiv(isa_base, isa_div, include_manager, funcs):
    """
    """
    if isa_base["name"] != "avx512" and isa_base["name"] != "avx": 
        print(f"in c_generator.gen_c_ldiv : error : ldiv not yet supported in {isa_div['name']}")
        exit(-1)
    for f in funcs : 
        file_w = include_manager.get_fd(isa_base["name"], f)
        for dt in funcs[f]["datatypes"]:
            dt_par, dt_ret = compute_dt_par_dt_ret(funcs, f, dt)
            _gen_c_function_one_ldiv_avx(isa_base=isa_base, isa_div=isa_div, file=file_w, funcs=funcs, f=f, ff=None, dt=dt, mask_kind=None, ldiv=2)
            # _gen_c_function_one_ldiv_avx(isa_base=isa_base, isa_div=isa_div, file=file_w, funcs=funcs, f=f, ff=None, dt=dt, mask_kind=None, ldiv=4)
        mask_support = funcs[f]["mask_support"] if "mask_support" in funcs[f] else None
        if mask_support and mask_support.is_maskable():
            for dt in funcs[f]["datatypes"]:
                dt_par, dt_ret = compute_dt_par_dt_ret(funcs, f, dt)
                _gen_c_function_one_ldiv_avx(isa_base=isa_base, isa_div=isa_div, file=file_w, funcs=funcs, f=f, ff=None, dt=dt, mask_kind="mask", ldiv=2)
                # _gen_c_function_one_ldiv_avx(isa_base=isa_base, isa_div=isa_div, file=file_w, funcs=funcs, f=f, ff=None, dt=dt, mask_kind="mask", ldiv=4)
        if mask_support and mask_support.is_maskzable():
            for dt in funcs[f]["datatypes"]:
                dt_par, dt_ret = compute_dt_par_dt_ret(funcs, f, dt)
                _gen_c_function_one_ldiv_avx(isa_base=isa_base, isa_div=isa_div, file=file_w, funcs=funcs, f=f, ff=None, dt=dt, mask_kind="maskz", ldiv=2)
                # _gen_c_function_one_ldiv_avx(isa_base=isa_base, isa_div=isa_div, file=file_w, funcs=funcs, f=f, ff=None, dt=dt, mask_kind="maskz", ldiv=4)
        if mask_support and mask_support.is_masksable():
            for dt in funcs[f]["datatypes"]:
                dt_par, dt_ret = compute_dt_par_dt_ret(funcs, f, dt)
                _gen_c_function_one_ldiv_avx(isa_base=isa_base, isa_div=isa_div, file=file_w, funcs=funcs, f=f, ff=None, dt=dt, mask_kind="masks", ldiv=2)
                # _gen_c_function_one_ldiv_avx(isa_base=isa_base, isa_div=isa_div, file=file_w, funcs=funcs, f=f, ff=None, dt=dt, mask_kind="masks", ldiv=4)

# ----------------------------------------------------------------------------------------------------------------------
# RVV lmul bookkeeping helpers (moved from gen_mipp_rvv.py)
# ----------------------------------------------------------------------------------------------------------------------
def _rvv_seen_lmul(funcs, f, dt_key, lmul):
    if "implem_status" in funcs[f]:
        if "lmul" in funcs[f]["implem_status"]:
            if (lmul, dt_key) in funcs[f]["implem_status"]["lmul"]:
                return True
    return False


def _rvv_mark_lmul_seen(funcs, f, dt_key, lmul):

    if "implem_status" not in funcs[f]:
        funcs[f]["implem_status"] = {}

    if "lmul" in funcs[f]["implem_status"]:
        funcs[f]["implem_status"]["lmul"].add((lmul, dt_key))
    else:
        funcs[f]["implem_status"]["lmul"] = {(lmul, dt_key)}
  
# def _rvv_seen_lmul_masked(funcs, f, dt_key, mask_kind, lmul):
#     bucket = get_masked_bucket(funcs, f, dt_key, mask_kind)
#     if bucket is not None and "lmul" in bucket:
#         if (lmul, dt_key) in bucket["lmul"]:
#             return True
#     return False

# def _rvv_mark_lmul_seen_masked(funcs, f, dt_key, mask_kind, lmul):
#     bucket = get_masked_bucket(funcs, f, dt_key, mask_kind)
#     if bucket is not None:
#         #print(bucket)
#         if "lmul" in bucket:
#             bucket[-1]["lmul"].add((lmul, dt_key))
#         else:
#             bucket[-1]["lmul"] = {(lmul, dt_key)}

def _rvv_seen_lmul_masked(funcs, f, dt_key, mask_kind, lmul):
    bucket = get_masked_bucket(funcs, f, dt_key, mask_kind)
    if not bucket:
        return False

    last = bucket[-1]
    return "lmul" in last and (lmul, dt_key) in last["lmul"]

def _rvv_mark_lmul_seen_masked(funcs, f, dt_key, mask_kind, lmul):
    bucket = get_masked_bucket(funcs, f, dt_key, mask_kind)
    if not bucket:
        return

    last = bucket[-1]
    if "lmul" in last:
        last["lmul"].add((lmul, dt_key))
    else:
        last["lmul"] = {(lmul, dt_key)}

# ----------------------------------------------------------------------------------------------------------------------
# RVV function generator (refactored)
# ----------------------------------------------------------------------------------------------------------------------
def gen_c_functions_rvv(isa, include_manager, funcs, implems, lmul=0, reductions_fix=None, cand_type="native_or_emu"):
    """
    Refactored version of gen_c_functions_rvv originally in gen_mipp_rvv.py.
    """
    for f in implems:
        if f not in funcs:
            print("Panic: '" + f + "' function does not exist.")
            exit(-1)

        file = include_manager.get_fd(isa["name"], f)
        if lmul in [2, 4, 8]:
            _maybe_emit_lmul_separator(isa["name"], f, file)
        elif lmul < 0:
            _maybe_emit_ldiv_separator(isa["name"], f, file)

        if "candidates" not in isa:
            isa["candidates"] = []
        
        for ff in implems[f]:
            if _is_masked_implem(f, ff):
                for dt in ff["datatypes"]:
                    
                    dt_par, dt_ret = compute_dt_par_dt_ret(funcs, f, dt)
                    dt_key = dt_par + "," + dt_ret
                    mask_kind = ff["version"]
                    ff_local = ff.copy()
                    guards = []
                    if cand_type == "native_or_emu":
                        g_par = None
                        g_ret = None
                        if lmul < 0:
                            ldiv = str(-lmul)
                            if "if_ldiv" in isa.get("datatypes", {}).get(dt_par, {}) and ldiv in isa["datatypes"][dt_par]["if_ldiv"]:
                                g_par = isa["datatypes"][dt_par]["if_ldiv"][ldiv]
                            if "if_ldiv" in isa.get("datatypes", {}).get(dt_ret, {}) and ldiv in isa["datatypes"][dt_ret]["if_ldiv"]:
                                g_ret = isa["datatypes"][dt_ret]["if_ldiv"][ldiv]
                        if not g_par:
                            g_par = isa.get("datatypes", {}).get(dt_par, {}).get("if", None)
                        if not g_ret:
                            g_ret = isa.get("datatypes", {}).get(dt_ret, {}).get("if", None)
                        if g_par: guards.append(g_par)
                        if g_ret and g_ret not in guards: guards.append(g_ret)
                    elif cand_type == "generic_emu":
                        pass
                    guard = " && ".join(guards) if guards else None
                    if guard:
                        if "if" in ff_local and ff_local["if"]:
                            ff_local["if"] = ff_local["if"] + " && " + guard
                        else:
                            ff_local["if"] = guard

                    # Add to candidates so dependencies can be resolved later
                    c_dict = {
                        "type": cand_type,
                        "f": f,
                        "ff": ff_local,
                        "dt": dt,
                        "emitted": False,
                        "level": ff.get("level", 1 if ("type" in ff and ff["type"] == "emulated") else 0)
                    }
                    if c_dict not in isa["candidates"]:
                        isa["candidates"].append(c_dict)

                    if (not is_missing_masked_func(funcs, f, dt_key, mask_kind)) and _rvv_seen_lmul_masked(funcs, f, dt_key, mask_kind, lmul):
                        continue

                    # Render & parse placeholders with lmul
                    pre_rendering = _render_template(isa, ff_local, dt_par, dt_ret, func_name=f)
                    ph_ret = _parse_placeholders_or_skip(
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
                            continue

                    ifd_prev = _build_prev_exclusion_ifdef(funcs, f, dt_key, ff_local, mask_kind=mask_kind)

                    # Append implem status *before* building current ifdef
                    _append_implem_status(funcs, f, dt_key, ff_local, ph_ret["requirements"], mask_kind=mask_kind)
                    #print("requirements for '" + f + "<" + mask_kind + "><" + dt_key + ">' implementation: " + str(ph_ret["requirements"]))

                    # Combine ifdefs and emit #if if needed (and update emulated status)
                    ifd = _combine_current_ifdefs(funcs, f, dt_key, ifd_prev, mask_kind=mask_kind)
                    
                    if ifd == "0":
                        continue

                    print("", file=file)
                    _emit_ifdef_begin_and_update_emulated(funcs, f, dt_key, ff_local, ifd, file, mask_kind=mask_kind)
                    # Pick body: reductions_fix override for RVV reductions with lmul>1
                    post_rendering = ph_ret["converted_ir"]
                    if lmul > 1 and reductions_fix and (f in reductions_fix) and (dt in reductions_fix[f]):
                        post_rendering_to_emit = reductions_fix[f][dt]
                    else:
                        post_rendering_to_emit = post_rendering
         
                    # Emit the function body using shared helper (includes lmul in name/proto/calls)
                    _emit_function_body(
                        funcs=funcs,
                        f=f,
                        isa=isa,
                        dt=dt,
                        dt_par=dt_par,
                        dt_ret=dt_ret,
                        ff=ff_local,
                        post_rendering=post_rendering_to_emit,
                        file=file,
                        masked_version=mask_kind,
                        lmul=lmul,
                    )
                    c_dict["emitted"] = True
     
                    _emit_ifdef_end(ifd, file)
     
                    # Preserve original tracking of LMUL implementations for masked functions
                    _rvv_mark_lmul_seen_masked(funcs, f, dt_key, mask_kind, lmul)

            else : # unmasked version
                for dt in ff["datatypes"]:
                    
                    dt_par, dt_ret = compute_dt_par_dt_ret(funcs, f, dt)
                    dt_key = dt_par + "," + dt_ret
                    ff_local = ff.copy()
                    guards = []
                    if cand_type == "native_or_emu":
                        g_par = None
                        g_ret = None
                        if lmul < 0:
                            ldiv = str(-lmul)
                            if "if_ldiv" in isa.get("datatypes", {}).get(dt_par, {}) and ldiv in isa["datatypes"][dt_par]["if_ldiv"]:
                                g_par = isa["datatypes"][dt_par]["if_ldiv"][ldiv]
                            if "if_ldiv" in isa.get("datatypes", {}).get(dt_ret, {}) and ldiv in isa["datatypes"][dt_ret]["if_ldiv"]:
                                g_ret = isa["datatypes"][dt_ret]["if_ldiv"][ldiv]
                        if not g_par:
                            g_par = isa.get("datatypes", {}).get(dt_par, {}).get("if", None)
                        if not g_ret:
                            g_ret = isa.get("datatypes", {}).get(dt_ret, {}).get("if", None)
                        if g_par: guards.append(g_par)
                        if g_ret and g_ret not in guards: guards.append(g_ret)
                    elif cand_type == "generic_emu":
                        # For generic emulation (Level 2), also propagate the ISA datatype guard
                        # so that _build_previous_emulated_exclusion_ifdef can exclude Level 2
                        # when a Level 0 is already emitted for the same function+datatype.
                        g_par = None
                        g_ret = None
                        if lmul < 0:
                            ldiv = str(-lmul)
                            if "if_ldiv" in isa.get("datatypes", {}).get(dt_par, {}) and ldiv in isa["datatypes"][dt_par]["if_ldiv"]:
                                g_par = isa["datatypes"][dt_par]["if_ldiv"][ldiv]
                            if "if_ldiv" in isa.get("datatypes", {}).get(dt_ret, {}) and ldiv in isa["datatypes"][dt_ret]["if_ldiv"]:
                                g_ret = isa["datatypes"][dt_ret]["if_ldiv"][ldiv]
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

                    # Add to candidates so dependencies can be resolved later
                    c_dict = {
                        "type": cand_type,
                        "f": f,
                        "ff": ff_local,
                        "dt": dt,
                        "emitted": False,
                        "level": ff.get("level", 1 if ("type" in ff and ff["type"] == "emulated") else 0)
                    }
                    if c_dict not in isa["candidates"]:
                        isa["candidates"].append(c_dict)


                    if (not is_missing_func(funcs, f, dt_key)) and _rvv_seen_lmul(funcs, f, dt_key, lmul):
                        continue

                    # Render & parse placeholders with lmul
                    pre_rendering = _render_template(isa, ff_local, dt_par, dt_ret)
                    ph_ret = _parse_placeholders_or_skip(
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
                        continue

                    ifd_prev = _build_prev_exclusion_ifdef(funcs, f, dt_key, ff_local)

                    # Append implem status *before* building current ifdef
                    _append_implem_status(funcs, f, dt_key, ff_local, ph_ret["requirements"])

                    # Combine ifdefs and emit #if if needed (and update emulated status)
                    ifd = _combine_current_ifdefs(funcs, f, dt_key, ifd_prev)
                    if ifd == "0":
                        continue

                    print("", file=file)
                    _emit_ifdef_begin_and_update_emulated(funcs, f, dt_key, ff_local, ifd, file)

                    # Pick body: reductions_fix override for RVV reductions with lmul>1
                    post_rendering = ph_ret["converted_ir"]
                    if lmul > 1 and reductions_fix and (f in reductions_fix) and (dt in reductions_fix[f]):
                        post_rendering_to_emit = reductions_fix[f][dt]
                    else:
                        post_rendering_to_emit = post_rendering

                    # Emit the function body using shared helper (includes lmul in name/proto/calls)
                    _emit_function_body(
                        funcs=funcs,
                        f=f,
                        isa=isa,
                        dt=dt,
                        dt_par=dt_par,
                        dt_ret=dt_ret,
                        ff=ff_local,
                        post_rendering=post_rendering_to_emit,
                        file=file,
                        masked_version=None,
                        lmul=lmul,
                    )
                    c_dict["emitted"] = True

                    _emit_ifdef_end(ifd, file)

                    # Preserve original tracking of LMUL implementations
                    _rvv_mark_lmul_seen(funcs, f, dt_key, lmul)
