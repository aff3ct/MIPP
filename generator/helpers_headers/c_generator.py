from jinja2 import Template, StrictUndefined
import json
import re

from tools import *

from include_gen import *

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


def gen_c_structures(isa, file, is_scalar=False):
    """
    Writes the C structures corresponding to the supported datatypes for a given ISA, for both vector and mask types.
    """
    
    if is_scalar:
        template = """typedef struct { {{ isa_datatype.reg }} r[MIPP_{{isa_name_upper}}_N_{{type_category_upper}}{{datatype.n_bits}}]; } rvd_{{ isa.name }}_{{ datatype.category }}{{ datatype.n_bits }}_t;"""
    else:
        template = """typedef struct { {{ isa_datatype.reg }} r; } rvd_{{ isa.name }}_{{ datatype.category }}{{ datatype.n_bits }}_t;"""
    j2_template = Template(template, undefined=StrictUndefined)

    template_alt = """typedef struct {
#if {{ isa_datatype.if }}
    {{ isa_datatype.reg }} r;
#else
    int r; // this is a hack to compile when the datatype is not suported by the SIMD extension
#endif // {{ isa_datatype.if }}
} rvd_{{ isa.name }}_{{ datatype.category }}{{ datatype.n_bits }}_t;"""
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
        return ifd_prev + " && " + ifd_cur
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
        return ifd_prev + " && " + ifd_cur
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

    # if f == "set_k" : 
    #     print("Debug: requirements for '" + f + "<" + dt_key + ">' function: " + str(ph_ret["requirements"]))
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
    #print debug infos
 
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
        _missing_emit_ifdef_begin_masked(ifd, file)
  
        _missing_emit_stub(file, funcs, f, dt_par, dt_ret, isa, func_name, masked_version=mask_kind, lmul=lmul)
  
        _missing_emit_ifdef_end(ifd, file)
  

# ----------------------------------------------------------------------------------------------------------------------
# Generators
# ----------------------------------------------------------------------------------------------------------------------
def gen_c_functions(isa, file, funcs, implems):
    """
    Looking leaner now.
    """
    
    if isa["name"] != "avx" and isa["name"] != "sse" and isa["name"] != "avx512" and isa["name"] != "neon":
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
    
    if isa["name"] != "avx" and isa["name"] != "sse" and isa["name"] != "avx512" and isa["name"] != "neon":
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
    if isa["name"] != "avx" and isa["name"] != "sse" and isa["name"] != "avx512" and isa["name"] != "neon":
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
    Intended for RVV (explicit _mX entrypoints).
    """
    #hack while moving from single file to include manager.
    if isa["name"] != "rvv" and isa["name"] != "avx" and isa["name"] != "sse" and isa["name"] != "avx512" and isa["name"] != "neon":
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
     
def _gen_c_horiz_lmul_one(isa, file, funcs, f, ff, dt, lmul):
    """
    Emit one horizontal LMUL variant body (LMUL>1) for one function+datatype,
    using custom generic emulation templates (implems_horiz_lmul_generic_emu).

    Option-B workaround: pre-mark certain dependencies as "implemented" in funcs
    so parse_placeholders() does not skip.
    """
    dt_par, dt_ret = _compute_dt_par_dt_ret(funcs, f, dt)
    dt_key = dt_par + "," + dt_ret

    if _rvv_seen_lmul(funcs, f, dt_key, lmul):
        return

    # --- Option B: pre-mark deps as implemented so parse_placeholders doesn't raise ---
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

    if f == "set":
        _ensure_fake_implemented("set", dt_key)
    # -------------------------------------------------------------------------------

    ff_local = dict(ff)
    ff_local["type"] = "emulated"

    pre_rendering = _render_template(isa, ff_local, dt_par, dt_ret, func_name=f, lmul=lmul)

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
        isa_name = False,
    )
    if ph_ret is None:
        return


    print("\t", end="", file=file)
    print(ph_ret["converted_ir"], file=file)


    _rvv_mark_lmul_seen(funcs, f, dt_key, lmul)


def gen_c_horiz_lmul(isa, file, funcs, f, dt, lmul, implems_horiz_lmul_generic_emu, func_name_for_panic=None, mask_type=None):
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

    # For future: if you pass mask_type, we currently just stub out (unless you add templates).
    if mask_type is not None:
        name = func_name_for_panic or f
        print(f"\tprintf(\"MIPP panic: '%s' is unimplemented.\\n\", \"{name}_m{int(lmul)}\");", file=file)
        print("\texit(-1);", file=file)
        return

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

        # Respect datatype list when present
        if "datatypes" in ff and dt not in ff["datatypes"]:
            continue

        _gen_c_horiz_lmul_one(isa=isa, file=file, funcs=funcs, f=f, ff=ff, dt=dt, lmul=lmul)
        emitted_any = True

    if not emitted_any:
        # Template exists but doesn't cover this dt => stub.
        name = func_name_for_panic or f
        print(f"\tprintf(\"MIPP panic: '%s' is unimplemented.\\n\", \"{name}_m{int(lmul)}\");", file=file)
        print("\texit(-1);", file=file)
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
  
def _rvv_seen_lmul_masked(funcs, f, dt_key, mask_kind, lmul):
    bucket = get_masked_bucket(funcs, f, dt_key, mask_kind)
    if bucket is not None and "lmul" in bucket:
        if (lmul, dt_key) in bucket["lmul"]:
            return True
    return False

def _rvv_mark_lmul_seen_masked(funcs, f, dt_key, mask_kind, lmul):
    bucket = get_masked_bucket(funcs, f, dt_key, mask_kind)
    if bucket is not None:
        #print(bucket)
        if "lmul" in bucket:
            bucket[-1]["lmul"].add((lmul, dt_key))
        else:
            bucket[-1]["lmul"] = {(lmul, dt_key)}


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
        
        
        for ff in implems[f]:
            # skip masked versions entirely.
            if _is_masked_implem(f, ff):
                for dt in ff["datatypes"]:
                    print("// ----------------------------------------------------------------------------------------------------------------------------------------------", f, file=file)

                    dt_par, dt_ret = _compute_dt_par_dt_ret(funcs, f, dt)
                    dt_key = dt_par + "," + dt_ret
                    mask_kind = ff["version"]

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

                
            else : 
                for dt in ff["datatypes"]:
                    print("// ----------------------------------------------------------------------------------------------------------------------------------------------", f, file=file)

                    dt_par, dt_ret = _compute_dt_par_dt_ret(funcs, f, dt)
                    dt_key = dt_par + "," + dt_ret

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
