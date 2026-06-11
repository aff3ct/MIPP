from jinja2 import Template, StrictUndefined
import json
import re

from tools import *

from include_gen import *
from generic_emu import *

# All of this hardcoding stuff is not looking good. I don't like it. I don't wanna break the generator just yet either though.
from implem_avx512 import isa_avx512
from implem_avx import isa_avx
from implem_sse import isa_sse

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
        _gen_ldiv_structs_avx(isa_avx512, isa_avx, file)
        _gen_ldiv_defines_avx(isa_avx512, isa_avx, file)
    if isa["name"] == "avx" : 
        _gen_ldiv_structs_avx(isa_avx, isa_sse, file)
        _gen_ldiv_defines_avx(isa_avx, isa_sse, file)

# ----------------------------------------------------------------------------------------------------------------------
# Shared helpers
# ----------------------------------------------------------------------------------------------------------------------
def _emit_separator(f, file):
    """
    Writes a separator comment for a given function name, to improve readability of the generated code.
    """
    n_dashes = 120 - 5 - len(f)
    print("// ", end="", file=file)
    while n_dashes > 0:
        print("-", end="", file=file)
        n_dashes = n_dashes - 1
    print(f" {f}", file=file)


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
        print(" -> " + err_message)
        print("// " + err_message, file=file)
        return None


def _build_previous_emulated_exclusion_ifdef(funcs, f, dt_key, ff):
    """
    ?
    """
    ifd = ""
    if "type" in ff and ff["type"] == "emulated":
        if "implem_status" in funcs[f] and dt_key in funcs[f]["implem_status"]:
            is_first = True
            i = 0
            for _implem in funcs[f]["implem_status"][dt_key]:
                ifd_sub = build_ifdef(funcs, f, dt_key, i)
                if ifd_sub:
                    if not is_first:
                        ifd = ifd + " && "
                    ifd = ifd + "!( "
                    ifd = ifd + ifd_sub
                    ifd = ifd + " )"
                    is_first = False
                i = i + 1
    return ifd


def _append_implem_status(funcs, f, dt_key, ff, requirements):
    """
    updates implem_status in funcs[f][dt_key] with the conditions 
    i.e the guard in "if" key and the 
    function that f depends on in "requirements" key.
    """
    cur_implem_status = {"if": "", "requirements": {}}
    if "if" in ff:
        cur_implem_status["if"] = ff["if"]
    cur_implem_status["requirements"] = requirements

    if "implem_status" not in funcs[f]:
        funcs[f]["implem_status"] = {}
    if dt_key not in funcs[f]["implem_status"]:
        funcs[f]["implem_status"][dt_key] = []
    funcs[f]["implem_status"][dt_key].append(cur_implem_status)
    



def _combine_current_ifdefs(funcs, f, dt_key, ifd_prev):
    """
    straightforward.
    """

    ifd_cur = build_ifdef(funcs, f, dt_key, len(funcs[f]["implem_status"][dt_key]) - 1)

    if ifd_prev and ifd_cur:
        return ifd_prev + " && (" + ifd_cur + ")"
    elif ifd_cur:
        return ifd_cur
    return ifd_prev


def _update_emulated(funcs, f, dt_key, ff, ifd):
    """
    only updates the "if" condition in implem_status for emulated functions. 
    Used in gen_c_generic_functions after printing the #if condition for the generic implementation. 
    Since generic implementations are supposed to be the last ones and have no conditions, 
    it's as if you have if A && !A which is false. 
    So you want to update the "if" condition of the generic implementation with the guard that was printed before it.
    """
    if "type" in ff and ff["type"] == "emulated":
        funcs[f]["implem_status"][dt_key][len(funcs[f]["implem_status"][dt_key]) - 1]["if"] = ifd


def _emit_ifdef_begin_and_update_emulated(funcs, f, dt_key, ff, ifd, file):
    """
    adds ifdef conditions to "if" in implem_status
    also prints the #if condition to file
    """
    if ifd:
        print("#if " + ifd, file=file)
        _update_emulated(funcs, f, dt_key, ff, ifd)



def _build_func_name(isa, dt, dt_par, dt_ret, f, masked_version=False):
    """
    wrapper around build_func_name and build_func_name_short. 
    Which function to call is decided if the type isn't a "double type"
    (i.e the function is not cast or cast_k)
    """
    if len(dt.split(',')) <= 1:
        return build_func_name_short(isa, dt_par, f, True, masked_version=masked_version)
    else:
        return build_func_name(isa, dt_par, dt_ret, f, True, masked_version=masked_version)


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


def _emit_function_body(funcs, f, isa, dt, dt_par, dt_ret, ff, post_rendering, file, masked_version=None, lmul=0):
    func_name = _build_func_name(isa, dt, dt_par, dt_ret, f)

    print("static " + build_proto(funcs[f]["proto"], dt_par, dt_ret, isa, func_name, masked_version = masked_version, lmul=lmul) + " {", file=file)

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


def _maybe_print_emulated_implemented(f, dt_key, ff):
    """print implemented message in cli for emulated functions."""
    if "type" in ff and ff["type"] == "emulated":
        print(" -> '" + f + "<" + dt_key + ">' has been implemented.")


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
    # ret ends with || remove it
    # if ret.endswith(" || "):
    #     ret = ret[:-4]
    
    # # ret may or may not start with a parenthesis for some reason. If it does only add the negation, if it doesn't add the parenthesis and the negation.
    # if ret and not ret.startswith("("):
    #     ret = "(" + ret + ")"
    
        
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
 

def _missing_compute_dt_par_dt_ret(dt):
    """
    similar to _compute_dt_par_dt_ret
    but doesn't check for type support and emit error 
    because gen_c_missing_functions's job is 
    to create prototypes/bodies for unimplemented functions.
    """
    if len(dt.split(',')) <= 1:
        dt_par = dt.split(',')[0]
        dt_ret = dt.split(',')[0]
    else:
        dt_par = dt.split(',')[0]
        dt_ret = dt.split(',')[1]
    return dt_par, dt_ret


def _missing_build_negated_ifdef_for_existing_implems(funcs, f, dt_key):
    """
    adds guard to missing function for when the ifdef conditions 
    are not met. Documenting this makes me realize that gen_c_generic_functions 
    and gen_c_missing functions do the same thing but don't share the 
    same helpers. Oops. I'll change it.
     """
    ifd = ""
    if "implem_status" in funcs[f] and dt_key in funcs[f]["implem_status"]:
        is_first = True
        i = 0
        for _implem in funcs[f]["implem_status"][dt_key]:
            ifd_sub = build_ifdef(funcs, f, dt_key, i)
            if ifd_sub:
                if not is_first:
                    ifd = ifd + " && "
                ifd = ifd + "!( "
                ifd = ifd + ifd_sub
                ifd = ifd + " )"
                is_first = False
            i = i + 1
    return ifd


def _missing_emit_ifdef_begin(ifd, file):
    """
    ifd != is_ifdef so not the same helper....
    """
    if ifd:
        print("#if " + ifd, file=file)


def _missing_emit_stub(file, funcs, f, dt_par, dt_ret, isa, func_name, masked_version = None, lmul=None):
    """
    writes the "body" of the missing function. 
    Which prints a panic messages and terminates the program.
    """
    mask_str = ""
    if masked_version:
        mask_str = "_" + masked_version
    #adds the lmul string to fn name
    #if lmul is not None and lmul > 0:
    #	mask_str = mask_str + "_m" + str(lmul)

    print("static " + build_proto(funcs[f]["proto"], dt_par, dt_ret, isa, func_name, lmul, True, masked_version=masked_version) + " {", file=file)
    print("\tprintf(\"MIPP panic: '%s' is unimplemented.\\n\", \"" + func_name + mask_str + "\");", file=file)
    print("\texit(-1);", file=file)
    print("}", file=file)


def _missing_emit_ifdef_end(ifd, file):
    """
    ifd != is_ifdef so not the same helper....
    """
    if ifd:
        print("#endif", file=file)


def _append_implem_status_masked(funcs, f, dt_key, mask_kind, ff, requirements):
    """
    updates masked implem status in funcs[f][dt_key][mask_kind] with the conditions 
    i.e the guard in "if" key and the 
    function that f depends on in "requirements" key.
    """
    cur_implem_status = {"if": "", "requirements": {}}
    if "if" in ff:
        cur_implem_status["if"] = ff["if"]
    cur_implem_status["requirements"] = requirements

    bucket = get_masked_bucket(funcs, f, dt_key, mask_kind, create_missing_bucket=True)
    bucket.append(cur_implem_status)
    #Updated maprint("Updated masked implem status for '" + f + "<" + mask_kind + "><" + dt_key + ">' with conditions: " + str(cur_implem_status))

def _build_previous_masked_emulated_exclusion_ifdef(funcs, f, dt_key, mask_kind, ff):
    """
    ?
    """
    ifd = ""
    if "type" in ff and ff["type"] == "emulated":
        bucket = get_masked_bucket(funcs, f, dt_key, mask_kind)
        if bucket is not None:
            is_first = True
            i = 0
            for _implem in bucket:
                ifd_sub = build_ifdef_masked(funcs, f, dt_key, mask_kind, i)
                if ifd_sub:
                    if not is_first:
                        ifd = ifd + " && "
                    ifd = ifd + "!( "
                    ifd = ifd + ifd_sub
                    ifd = ifd + " )"
                    is_first = False
                i = i + 1
    return ifd


def _combine_current_ifdefs_masked(funcs, f, dt_key, mask_kind, ifd_prev):
    bucket = get_masked_bucket(funcs, f, dt_key, mask_kind)
    if bucket is None:
        return ifd_prev

    ifd_cur = build_ifdef_masked(funcs, f, dt_key, mask_kind, len(bucket) - 1)

    if ifd_prev and ifd_cur:
        return ifd_prev + " && (" + ifd_cur + ")"
    elif ifd_cur:
        return ifd_cur
    return ifd_prev


def _emit_ifdef_begin_and_update_emulated_masked(funcs, f, dt_key, mask_kind, ff, ifd, file):
    if ifd:
        print("#if " + ifd, file=file)
        if "type" in ff and ff["type"] == "emulated":
            bucket = get_masked_bucket(funcs, f, dt_key, mask_kind)
            # bucket exists because masked append happened before this call
            bucket[len(bucket) - 1]["if"] = ifd
   
def _missing_build_negated_masked_ifdef_for_existing_implems(funcs, f, dt_key, mask_kind):
    """
    same as _missing_build_negated_ifdef_for_existing_implems but for masked functions. 
    Which means it builds the negation of the ifdef conditions for all previous implementations of the same masked function.
    """
    ifd = ""
    bucket = get_masked_bucket(funcs, f, dt_key, mask_kind)
    if bucket is not None:
        is_first = True
        i = 0
        for _implem in bucket:
            ifd_sub = build_ifdef_masked(funcs, f, dt_key, mask_kind, i)
            if ifd_sub:
                if not is_first:
                    ifd = ifd + " && "
                ifd = ifd + "!( "
                ifd = ifd + ifd_sub
                ifd = ifd + " )"
                is_first = False
            i = i + 1
    return ifd

def _missing_emit_ifdef_begin_masked(ifd, file):
    if ifd:
        print("#if " + ifd, file=file)
    return ifd


# ----------------------------------------------------------------------------------------------------------------------
# Generator of one function 
# ----------------------------------------------------------------------------------------------------------------------

def _gen_c_functions_one_unmasked(isa, file, funcs, f, ff, dt):
    """
    the big glue guy that calls all the helpers 
    to generate 1 fn for 1 dt. It's the logic of the big inner loop 
    of gen_c_functions.
    """
    dt_par, dt_ret = _compute_dt_par_dt_ret(funcs, f, dt)
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

    ifd_prev = _build_previous_emulated_exclusion_ifdef(funcs, f, dt_key, ff)

    _append_implem_status(funcs, f, dt_key, ff, ph_ret["requirements"])

    post_rendering = ph_ret["converted_ir"]

    ifd = _combine_current_ifdefs(funcs, f, dt_key, ifd_prev)
    _emit_ifdef_begin_and_update_emulated(funcs, f, dt_key, ff, ifd, file)

    _emit_function_body(funcs, f, isa, dt, dt_par, dt_ret, ff, post_rendering, file)

    _emit_ifdef_end(ifd, file)
    _maybe_print_emulated_implemented(f, dt_key, ff)

def _gen_c_function_one_masked(isa, file, funcs, f, ff, dt):
    
    dt_par, dt_ret = _compute_dt_par_dt_ret(funcs, f, dt)
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

    pre_rendering = _render_template(isa, ff, dt_par, dt_ret, func_name = f)
    
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

    ifd_prev = _build_previous_masked_emulated_exclusion_ifdef(funcs, f, dt_key, mask_kind, ff)

    _append_implem_status_masked(funcs, f, dt_key, mask_kind, ff, ph_ret["requirements"])
 
    ifd = _combine_current_ifdefs_masked(funcs, f, dt_key, mask_kind, ifd_prev)
 
    _emit_ifdef_begin_and_update_emulated_masked(funcs, f, dt_key, mask_kind, ff, ifd, file)
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
    _maybe_print_emulated_implemented(f + "<" + mask_kind + ">", dt_key, ff)


#### WIP 

def _c_lmul_writer(f, dt, dt_par, dt_ret, isa, funcs, file, mask_type=None, lmul=0):

    mask_str = ""
    if mask_type == "mask":
        mask_str = "_mask"
    elif mask_type == "maskz":
        mask_str = "_maskz"
    elif mask_type == "masks":
        mask_str = "_masks"


    if len(dt.split(',')) <= 1:
        func_name = build_func_name_short(isa, dt_par, f, lmul=0);
    else:
        func_name = build_func_name(isa, dt_par, dt_ret, f, lmul=0);
  
    
    if lmul == 1:
        #call non_lmul version
        print("static " + build_proto(funcs[f]["proto"], dt_par, dt_ret, isa, func_name, lmul=lmul, isa_name=True, masked_version=mask_type) + " {", file=file)
        print("\t" + build_call(funcs[f]["proto"], dt_par, dt_ret, isa, func_name+mask_str, lmul=0, isa_name=True, masked_version=mask_type) + ";", file=file)
        print("}", file=file)
        return

    if not funcs[f]["horizontal"]:
        print("static " + build_proto(funcs[f]["proto"], dt_par, dt_ret, isa, func_name, lmul=lmul, isa_name=True, masked_version=mask_type) + " {", file=file)

        lmul_2 = int(lmul / 2)
        print(build_call_lmul(funcs[f]["proto"], dt_par, dt_ret, isa, func_name+mask_str+"_m"+str(lmul_2), lmul=lmul, isa_name=True, masked_version=mask_type), file=file)
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

    dt_par, dt_ret = _compute_dt_par_dt_ret(funcs, f, dt)
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
    dt_par, dt_ret = _missing_compute_dt_par_dt_ret(dt)
    dt_key = dt_par + "," + dt_ret

    if is_missing_func(funcs, f, dt_key):
        ifd = _missing_build_negated_ifdef_for_existing_implems(funcs, f, dt_key)
        _missing_emit_ifdef_begin(ifd, file)

        func_name = _build_func_name(isa, dt, dt_par, dt_ret, f)
        
        _missing_emit_stub(file, funcs, f, dt_par, dt_ret, isa, func_name, lmul=lmul)

        _missing_emit_ifdef_end(ifd, file)

# def _fallback_emit_func(file, funcs, f, dt_par, dt_ret, isa, func_name, masked_version=None, lmul=0):
#     """
#     fallback will rely on the scalar implementation. We force the scalar implementation 
#     to contain everything in the mipp specification. 
#     The logic of the fallback fn is
#     -> if type is always defined at the isa level
    
#         -> if RVD : 
#             -> declare scalar reg(s)
#             -> store args in the scalar reg with STORE 
#             -> call the scalar implementation with the scalar reg(s) as argument(s)
#             -> if result == rvd
#                 -> load the result with LOAD
#                 -> return the result
#             -> elif result == rvm
#                 -> return SET_K of the result
#             -> else :
#                 -> return the value or void
#         -> if RVM
#             -> declare scalar reg(s)
#             -> convert isa rvm to rvd with TOREG
#             -> store converted registers in the scalar rvms with scalar SET_K (works)
#             -> call the scalar implementation with the scalar reg(s) as argument(s)
#             -> if result == rvd
#                 -> load the result with LOAD
#                 -> return the result
#             -> elif result == rvm
#                 -> return SET_K of the result
#             -> else :
#                 -> return the value or void
#     -> else 
#         actually idk...
#     """
    
#     is_def_type = "if" not in isa["datatypes"][dt_par]
    

# def _gen_c_fallback_one_dt(isa, file, funcs, f, dt, lmul=0):
#     dt_par, dt_ret = _missing_compute_dt_par_dt_ret(dt)
#     dt_key = dt_par + "," + dt_ret

#     if is_missing_func(funcs, f, dt_key):
#         ifd = _missing_build_negated_ifdef_for_existing_implems(funcs, f, dt_key)
#         _missing_emit_ifdef_begin(ifd, file)

#         func_name = _build_func_name(isa, dt, dt_par, dt_ret, f)

#         _fallback_emit_func(file, funcs, f, dt_par, dt_ret, isa, func_name, lmul=lmul)

#         _missing_emit_ifdef_end(ifd, file)
  
def _gen_c_missing_one_masked(isa, file, funcs, f, dt, mask_kind, lmul=0):
    dt_par, dt_ret = _missing_compute_dt_par_dt_ret(dt)
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
    func_name = _build_func_name(isa, dt, dt_par, dt_ret, f)

    if fully_missing:
        _missing_emit_stub(file, funcs, f, dt_par, dt_ret, isa, func_name, masked_version=mask_kind, lmul=lmul)

    elif ifdef_guarded:
        ifd = _missing_build_negated_masked_ifdef_for_existing_implems(funcs, f, dt_key, mask_kind)
        # check that ifd isn't a blank line 
    
        # use a regex to check if there are actual characters in a-z A-Z 0-9 or _ in ifd, if not consider it as blankmipp_sse_set_uint16
        if not re.search(r'[a-zA-Z0-9_]', ifd):

            return
       
        _missing_emit_ifdef_begin_masked(ifd, file)
  
        _missing_emit_stub(file, funcs, f, dt_par, dt_ret, isa, func_name, masked_version=mask_kind, lmul=lmul)
  
        _missing_emit_ifdef_end(ifd, file)

def _gen_c_function_one_ldiv_avx(isa_base, isa_div, file, funcs, f, ff, dt, mask_kind, ldiv=-2):
    """
    fairly straightforward the uint32_d2 avx function is JUST the uint32_m1 version of avx so wrapper to it.
    smth like : 

    static inline mipp_avx512_add_float32_d2(rvd_avx512_float32_d2 r0, rvd_avx512_float32_d2 r1){
        return mipp_avx_add_float32_m1(r0, r1);
    }
    a d4 function would be the sse version.
    """
    dt_par, dt_ret = _compute_dt_par_dt_ret(funcs, f, dt)
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
        func_name = build_func_name_short(isa_base, dt_par, f, True)
    else:
        func_name = build_func_name(isa_base, dt_par, dt_ret, f, True)

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
def gen_c_functions(isa, file, funcs, implems):
    """
    Looking leaner now.
    """
    #hack while moving from single file to include manager.  
    if isa["name"].startswith("sve"):
        for f in implems:
            if f in funcs:
                for ff in implems[f]:
                    
                    for dt in ff["datatypes"]:
                        _emit_separator(f, file)
                        if _is_masked_implem(f, ff):
                            _gen_c_function_one_masked(isa, file, funcs, f, ff, dt)
                        else :
                            _gen_c_functions_one_unmasked(isa, file, funcs, f, ff, dt)
            else:
                print("Panic: '" + f + "' function does not exist.")
                exit(-1)
    else:
        #in that case file is actually an include manager, so we need to get the right file for each function
        for f in implems:
            if f in funcs:
                file_w = file.get_fd(isa["name"], f)
                for ff in implems[f]:
                    for dt in ff["datatypes"]:
                        _emit_separator(f, file_w)
                        if _is_masked_implem(f, ff):
                            _gen_c_function_one_masked(isa, file_w, funcs, f, ff, dt)
                        else :
                            _gen_c_functions_one_unmasked(isa, file_w, funcs, f, ff, dt)
            else:
                print("Panic: '" + f + "' function does not exist.")
                exit(-1)

def gen_c_generic_functions(isa, file, funcs, implems):
    #hack while moving from single file to include manager.  
    if isa["name"].startswith("sve"):
        for f in implems:
            if f in funcs:
                for ff in implems[f]:
                    for dt in ff["datatypes"]:
                        _emit_separator(f, file)
                        _gen_c_generic_one(isa, file, funcs, f, ff, dt)
            else:
                print("Panic: '" + f + "' function does not exist.")
                exit(-1)
    else:
        #in that case file is actually an include manager, so we need to get the right file for each function
        for f in implems:
            if f in funcs:
                file_w = file.get_fd(isa["name"], f)
                for ff in implems[f]:
                    for dt in ff["datatypes"]:
                        _emit_separator(f, file_w)
                        _gen_c_generic_one(isa, file_w, funcs, f, ff, dt)
            else:
                print("Panic: '" + f + "' function does not exist.")
                exit(-1)

def gen_c_missing_functions(isa, file, funcs):
    #hack while moving from single file to include manager.
    if isa["name"].startswith("sve"):
        for f in funcs:
            for dt in funcs[f]["datatypes"]:
                _emit_separator(f, file)
                _gen_c_missing_one_dt(isa, file, funcs, f, dt)
                if "mask_support" in funcs[f]:
                    support = funcs[f]["mask_support"]
                    if support.is_maskable(): 
                        _gen_c_missing_one_masked(isa, file, funcs, f, dt, "mask")
                    if support.is_maskzable():
                        _gen_c_missing_one_masked(isa, file, funcs, f, dt, "maskz")
                    if support.is_masksable():
                        _gen_c_missing_one_masked(isa, file, funcs, f, dt, "masks")
    else:
        #in that case file is actually an include manager, so we need to get the right file for each function
        for f in funcs:
            file_w = file.get_fd(isa["name"], f)
            for dt in funcs[f]["datatypes"]:
                _emit_separator(f, file_w)
                _gen_c_missing_one_dt(isa, file_w, funcs, f, dt)
                if "mask_support" in funcs[f]:
                    support = funcs[f]["mask_support"]
                    if support.is_maskable(): 
                        _gen_c_missing_one_masked(isa, file_w, funcs, f, dt, "mask")
                    if support.is_maskzable():
                        _gen_c_missing_one_masked(isa, file_w, funcs, f, dt, "maskz")
                    if support.is_masksable():
                        _gen_c_missing_one_masked(isa, file_w, funcs, f, dt, "masks")

def gen_c_missing_functions_lmul(isa, file, funcs, lmul):
    """
    Generate missing variants for a given LMUL, including masked+LMUL missing stubs.
    Intended for RVV.
    """
    #hack while moving from single file to include manager.
    if isa["name"].startswith("sve"):
        for f in funcs:
            for dt in funcs[f]["datatypes"]:
                _emit_separator(f, file)
                _gen_c_missing_one_dt(isa, file, funcs, f, dt, lmul=lmul)

                if "mask_support" in funcs[f]:
                    support = funcs[f]["mask_support"]
                    if support.is_maskable():
                        _gen_c_missing_one_masked(isa, file, funcs, f, dt, "mask", lmul=lmul)
                    if support.is_maskzable():
                        _gen_c_missing_one_masked(isa, file, funcs, f, dt, "maskz", lmul=lmul)
                    if support.is_masksable():
                        _gen_c_missing_one_masked(isa, file, funcs, f, dt, "masks", lmul=lmul)
    else: 
        #in that case file is actually an include manager, so we need to get the right file for each function
        for f in funcs:
            file_w = file.get_fd(isa["name"], f)
            for dt in funcs[f]["datatypes"]:
                
                # hack skip ldiv 4 rvv rn
                dt_par, dt_ret = _missing_compute_dt_par_dt_ret(dt)
                if isa["name"] == "rvv" and lmul < 0 and isa["datatypes"][dt_par]["width"] == "64":
                    continue

                _emit_separator(f, file_w)
                _gen_c_missing_one_dt(isa, file_w, funcs, f, dt, lmul=lmul)

                if "mask_support" in funcs[f]:
                    support = funcs[f]["mask_support"]
                    if support.is_maskable():
                        _gen_c_missing_one_masked(isa, file_w, funcs, f, dt, "mask", lmul=lmul)
                    if support.is_maskzable():
                        _gen_c_missing_one_masked(isa, file_w, funcs, f, dt, "maskz", lmul=lmul)
                    if support.is_masksable():
                        _gen_c_missing_one_masked(isa, file_w, funcs, f, dt, "masks", lmul=lmul)

 
def _gen_c_horiz_lmul_one(isa, file, funcs, f, ff, dt, lmul, mkind=None, dummy=False):
    """
    Emit one horizontal LMUL variant body (LMUL>1) for one function+datatype,
    using custom generic emulation templates (implems_horiz_lmul_generic_emu).

    Option-B workaround: pre-mark certain dependencies as "implemented" in funcs
    so parse_placeholders() does not skip.
    """
    dt_par, dt_ret = _compute_dt_par_dt_ret(funcs, f, dt)
    dt_key = dt_par + "," + dt_ret

    if _rvv_seen_lmul(funcs, f, dt_key, lmul) and mkind is None:
        return

    # Current horiz templates (tpl_set) reference %set<...>% recursively (tp/2).
    # parse_placeholders requires funcs["set"].implem_status[dep_dt_key] to exist.
    #
    # We mark base set<dt,dt> as implemented; this is enough to avoid the exception.
    # (If you later add more horiz templates that reference other functions, extend this.)
    
    
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
        dt_par, dt_ret = _compute_dt_par_dt_ret(funcs, f, dt)
        func_name = _build_func_name(isa, dt, dt_par, dt_ret, f)
        proto = build_proto(funcs[f]["proto"], dt_par, dt_ret, isa, func_name, lmul=lmul, isa_name=True, masked_version=mkind)
        print("static " + proto + " {", file=file)

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
            dt_par, dt_ret = _compute_dt_par_dt_ret(funcs, f, dt)


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
            dt_par, dt_ret = _compute_dt_par_dt_ret(funcs, f, dt)
            _gen_c_function_one_ldiv_avx(isa_base=isa_base, isa_div=isa_div, file=file_w, funcs=funcs, f=f, ff=None, dt=dt, mask_kind=None, ldiv=2)
            # _gen_c_function_one_ldiv_avx(isa_base=isa_base, isa_div=isa_div, file=file_w, funcs=funcs, f=f, ff=None, dt=dt, mask_kind=None, ldiv=4)
        mask_support = funcs[f]["mask_support"] if "mask_support" in funcs[f] else None
        if mask_support and mask_support.is_maskable():
            for dt in funcs[f]["datatypes"]:
                dt_par, dt_ret = _compute_dt_par_dt_ret(funcs, f, dt)
                _gen_c_function_one_ldiv_avx(isa_base=isa_base, isa_div=isa_div, file=file_w, funcs=funcs, f=f, ff=None, dt=dt, mask_kind="mask", ldiv=2)
                # _gen_c_function_one_ldiv_avx(isa_base=isa_base, isa_div=isa_div, file=file_w, funcs=funcs, f=f, ff=None, dt=dt, mask_kind="mask", ldiv=4)
        if mask_support and mask_support.is_maskzable():
            for dt in funcs[f]["datatypes"]:
                dt_par, dt_ret = _compute_dt_par_dt_ret(funcs, f, dt)
                _gen_c_function_one_ldiv_avx(isa_base=isa_base, isa_div=isa_div, file=file_w, funcs=funcs, f=f, ff=None, dt=dt, mask_kind="maskz", ldiv=2)
                # _gen_c_function_one_ldiv_avx(isa_base=isa_base, isa_div=isa_div, file=file_w, funcs=funcs, f=f, ff=None, dt=dt, mask_kind="maskz", ldiv=4)
        if mask_support and mask_support.is_masksable():
            for dt in funcs[f]["datatypes"]:
                dt_par, dt_ret = _compute_dt_par_dt_ret(funcs, f, dt)
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
def gen_c_functions_rvv(isa, include_manager, funcs, implems, lmul=0, reductions_fix=False):
    """
    Refactored version of gen_c_functions_rvv originally in gen_mipp_rvv.py.
    """
    for f in implems:
        if f not in funcs:
            print("Panic: '" + f + "' function does not exist.")
            exit(-1)

        file = include_manager.get_fd(isa["name"], f)
        # print file name
        # print("Debug: generating for '" + f + "' function in file: " + file.name)
        
        
        for ff in implems[f]:
            if _is_masked_implem(f, ff):
                for dt in ff["datatypes"]:

                    dt_par, dt_ret = _compute_dt_par_dt_ret(funcs, f, dt)
                    dt_key = dt_par + "," + dt_ret
                    mask_kind = ff["version"]

                    if ("64" in dt_key) and int(lmul) < 0: 
                        continue

                    print("// ----------------------------------------------------------------------------------------------------------------------------------------------", f, file=file)


                    if (not is_missing_masked_func(funcs, f, dt_key, mask_kind)) and _rvv_seen_lmul_masked(funcs, f, dt_key, mask_kind, lmul):
                        print(
                            "// '"
                            + f
                            + "<" + mask_kind + "><"
                            + dt_key
                            + ">'"
                            + str(lmul)
                            + 'has been skipped (reason: "Info: It has been implemented before.").',
                            file=file,
                        )
                        continue

                    # Render & parse placeholders with lmul
                    pre_rendering = _render_template(isa, ff, dt_par, dt_ret, func_name=f)
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

                    ifd_prev = _build_previous_masked_emulated_exclusion_ifdef(funcs, f, dt_key, mask_kind, ff)

                    # Append implem status *before* building current ifdef
                    _append_implem_status_masked(funcs, f, dt_key, mask_kind, ff, ph_ret["requirements"])
                    #print("requirements for '" + f + "<" + mask_kind + "><" + dt_key + ">' implementation: " + str(ph_ret["requirements"]))

                    # Combine ifdefs and emit #if if needed (and update emulated status)
                    ifd = _combine_current_ifdefs_masked(funcs, f, dt_key, mask_kind, ifd_prev)
                    _emit_ifdef_begin_and_update_emulated_masked(funcs, f, dt_key, mask_kind, ff, ifd, file)
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
                        ff=ff,
                        post_rendering=post_rendering_to_emit,
                        file=file,
                        masked_version=mask_kind,
                        lmul=lmul,
                    )
     
                    _emit_ifdef_end(ifd, file)
                    _maybe_print_emulated_implemented(f + "<" + mask_kind + ">", dt_key, ff)
     
                    # Preserve original tracking of LMUL implementations for masked functions
                    _rvv_mark_lmul_seen_masked(funcs, f, dt_key, mask_kind, lmul)

                
            else : # unmasked version
                for dt in ff["datatypes"]:
                    
                    dt_par, dt_ret = _compute_dt_par_dt_ret(funcs, f, dt)
                    dt_key = dt_par + "," + dt_ret

                    if ("64" in dt_key) and int(lmul) < 0: 
                        continue

                    print("// ----------------------------------------------------------------------------------------------------------------------------------------------", f, file=file)

                    if (not is_missing_func(funcs, f, dt_key)) and _rvv_seen_lmul(funcs, f, dt_key, lmul):
                        print(
                            "// '"
                            + f
                            + "<"
                            + dt_key
                            + ">'"
                            + str(lmul)
                            + 'has been skipped (reason: "Info: It has been implemented before.").',
                            file=file,
                        )
                        continue

                    # Render & parse placeholders with lmul
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
                        lmul=lmul,
                    )
                    if ph_ret is None:
                        continue

                    ifd_prev = _build_previous_emulated_exclusion_ifdef(funcs, f, dt_key, ff)

                    # Append implem status *before* building current ifdef
                    _append_implem_status(funcs, f, dt_key, ff, ph_ret["requirements"])

                    # Combine ifdefs and emit #if if needed (and update emulated status)
                    ifd = _combine_current_ifdefs(funcs, f, dt_key, ifd_prev)
                    _emit_ifdef_begin_and_update_emulated(funcs, f, dt_key, ff, ifd, file)

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
                        ff=ff,
                        post_rendering=post_rendering_to_emit,
                        file=file,
                        masked_version=None,
                        lmul=lmul,
                    )

                    _emit_ifdef_end(ifd, file)
                    _maybe_print_emulated_implemented(f, dt_key, ff)

                    # Preserve original tracking of LMUL implementations
                    _rvv_mark_lmul_seen(funcs, f, dt_key, lmul)