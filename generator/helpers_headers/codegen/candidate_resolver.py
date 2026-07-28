"""
Candidate Resolver Module
Implements the core resolution/solver loop to solve missing/emulated instructions dependencies,
and generates auto-scalar fallbacks and panic stubs.
"""
import sys
import os

# Add parent directory to sys.path to find tools.py
sys.path.insert(1, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

from tools import *
from tools import negate_cond as tool_negate_cond
from tools import are_conds_mutually_exclusive as tool_are_conds_mutually_exclusive
from tools import intersect_conds as tool_intersect_conds
from tools import build_func_name_internal, get_dt_par_size, is_guard_dead_under_cond
from registry import scalar_isa
from codegen.implem_tracker import get_implem_bucket, missing_build_negated_ifdef_for_existing_implems
from codegen.emit_helpers import emit_function_body, emit_panic_stub


_template_cache = {}

def _get_template(code):
    cached = _template_cache.get(code)
    if cached is None:
        cached = Template(code, undefined=StrictUndefined)
        _template_cache[code] = cached
    return cached


def _missing_emit_ifdef_begin(ifd, file):
    if ifd:
        print("#if " + ifd, file=file)

def _missing_emit_stub(file, funcs, f, dt_par, dt_ret, isa, func_name, masked_version = None, lmul=0):
    full_func_name = build_func_name_internal(isa, dt_par, dt_par, dt_ret, f, masked_version=masked_version, lmul=lmul)
    proto = build_proto(funcs[f]["proto"], dt_par, dt_ret, isa, func_name, lmul, True, masked_version=masked_version)
    print(f"static {proto} {{", file=file)
    emit_panic_stub(full_func_name, file=file)
    print("}", file=file)

def _missing_emit_ifdef_end(ifd, file):
    if ifd:
        print("#endif", file=file)

def render_template(isa, ff, dt_par, dt_ret, func_name="", lmul=0):
    tpl_code = ff["template"]["code"]
    if isinstance(tpl_code, list):
        tpl_code = "\n".join(tpl_code)
    j2_template = _get_template(tpl_code)
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

def parse_placeholders_or_skip(pre_rendering, isa, funcs, f, dt_par, dt_ret, dt_key, file, lmul=0, isa_name=True):
    try:
        return parse_placeholders(pre_rendering, isa, funcs, f, dt_par, dt_ret, lmul=lmul, isa_name=isa_name)
    except Exception as err:
        err_message = "'" + f + "<" + dt_key + ">' has been skipped (reason: \"{0}\").".format(err)
        print("// " + err_message, file=file)
        return None

_FALLBACK_TEMPLATE = """{% if cond %}#if {{ cond }}
{% endif %}static {{ proto }} {
\t// Level 3 (Auto Scalar Fallback)
{% if pre_statements %}{{ pre_statements }}
{% endif %}\t{{ call_statement }}
{% if post_statements %}{{ post_statements }}
{% endif %}{% if return_statement %}\t{{ return_statement }}
{% endif %}}
{%- if cond %}
#endif
{%- endif %}"""

def _prepare_mask_variable(pre_statements, isa, msk_dt, arg_name, cond, lmul, f, is_initial_mask=False):
    msk_dt_name = msk_dt["name"]
    m0_scalar_type = build_type("msk", msk_dt, scalar_isa, lmul, True, False)
    pre_statements.append(f"\t{m0_scalar_type} s_{arg_name} = {{0}};")
    if isa.get("hw_mask", False):
        reg_vector_type = build_reg(msk_dt, isa, lmul, True, False)
        reg_scalar_type = build_reg(msk_dt, scalar_isa, lmul, True, False)
        scalar_tomsk_func = build_func_name_internal(scalar_isa, msk_dt_name, msk_dt_name, msk_dt_name, "tomsk", lmul=lmul)
        
        is_special_bitfield = False
        if isa.get("hw_mask_is_bitfield", False):
            if is_initial_mask or f in ["toreg", "tomsk", "cast_k"]:
                is_special_bitfield = True
                n_elements = isa["size"] // get_dt_par_size(msk_dt_name)
                
        if is_special_bitfield:
            pre_statements.append(f"\tfor (int i = 0; i < {n_elements}; ++i) {{")
            pre_statements.append(f"\t\ts_{arg_name}.m[i] = ({arg_name}.m & (1ULL << i)) ? ~0 : 0;")
            pre_statements.append(f"\t}}")
        else:
            toreg_func = build_func_name_internal(isa, msk_dt_name, msk_dt_name, msk_dt_name, "toreg", lmul=lmul)
            if "if_lmul" in isa["datatypes"].get(msk_dt_name, {}):
                guard = isa["datatypes"][msk_dt_name]["if_lmul"].get(str(lmul), None)
            else:
                guard = isa["datatypes"].get(msk_dt_name, {}).get("if", None)
                
            if guard == "0" or is_guard_dead_under_cond(guard, cond):
                pre_statements.append(f"\tmemcpy(&s_{arg_name}, &{arg_name}, sizeof({arg_name}));")
            else:
                if guard:
                    pre_statements.append(f"#if {guard}")
                pre_statements.append(f"\t{reg_vector_type} r_{arg_name} = {toreg_func}({arg_name});")
                pre_statements.append(f"\t{reg_scalar_type} s_r_{arg_name} = {{0}};")
                pre_statements.append(f"\tmemcpy(&s_r_{arg_name}, &r_{arg_name}, sizeof(r_{arg_name}));")
                pre_statements.append(f"\ts_{arg_name} = {scalar_tomsk_func}(s_r_{arg_name});")
                if guard:
                    pre_statements.append(f"#else")
                    pre_statements.append(f"\tmemcpy(&s_{arg_name}, &{arg_name}, sizeof({arg_name}));")
                    pre_statements.append(f"#endif")
    else:
        pre_statements.append(f"\tmemcpy(&s_{arg_name}, &{arg_name}, sizeof({arg_name}));")

def _resolve_arg_datatype(arg, dt_par, dt_ret):
    arg_type_name = arg["type"]
    realdatatype = datatypes[dt_par]
    if arg.get("fixeddatatype"):
        if arg["fixeddatatype"] not in datatypes and arg["fixeddatatype"] in all_categories:
            dt_str = arg["fixeddatatype"] + str(get_dt_par_size(dt_par))
            realdatatype = datatypes[dt_str]
        elif arg["fixeddatatype"] in datatypes:
            realdatatype = datatypes[arg["fixeddatatype"]]
    elif arg_type_name == "ret":
        realdatatype = datatypes[dt_ret]
    return realdatatype

def _prepare_return_variable(post_statements, isa, dt_ret, cond, lmul, f, vector_ret_type, ret_type_name):
    dt_ret_name = dt_ret["name"]
    if ret_type_name == "msk" and isa.get("hw_mask", False):
        tomsk_func = build_func_name_internal(isa, dt_ret_name, dt_ret_name, dt_ret_name, "tomsk", lmul=lmul)
        toreg_scalar_func = build_func_name_internal(scalar_isa, dt_ret_name, dt_ret_name, dt_ret_name, "toreg", lmul=lmul)
        if isa.get("hw_mask_is_bitfield", False) and f in ["toreg", "tomsk", "cast_k"]:
            post_statements.append(f"\t{vector_ret_type} res;")
            post_statements.append(f"\tres.m = 0;")
            n_elements = isa["size"] // get_dt_par_size(dt_ret_name)
            post_statements.append(f"\tfor (int i = 0; i < {n_elements}; ++i) {{")
            post_statements.append(f"\t\tif (sres.m[i]) res.m |= (1ULL << i);")
            post_statements.append(f"\t}}")
        else:
            if "if_lmul" in isa["datatypes"].get(dt_ret_name, {}):
                ret_guard = isa["datatypes"][dt_ret_name]["if_lmul"].get(str(lmul), None)
            else:
                ret_guard = isa["datatypes"].get(dt_ret_name, {}).get("if", None)

            if ret_guard == "0" or is_guard_dead_under_cond(ret_guard, cond):
                post_statements.append(f"\t{vector_ret_type} res;")
                post_statements.append(f"\tmemcpy(&res, &sres, sizeof(res));")
            else:
                if ret_guard:
                    post_statements.append(f"\t#if {ret_guard}")
                reg_scalar_type = build_reg(dt_ret, scalar_isa, lmul, True, False)
                reg_vector_type = build_reg(dt_ret, isa, lmul, True, False)
                post_statements.append(f"\t{reg_scalar_type} s_r_res = {toreg_scalar_func}(sres);")
                post_statements.append(f"\t{reg_vector_type} r_res;")
                post_statements.append(f"\tmemcpy(&r_res, &s_r_res, sizeof(r_res));")
                post_statements.append(f"\t{vector_ret_type} res = {tomsk_func}(r_res);")
                if ret_guard:
                    post_statements.append(f"\t#else")
                    post_statements.append(f"\t{vector_ret_type} res;")
                    post_statements.append(f"\tmemcpy(&res, &sres, sizeof(res));")
                    post_statements.append(f"\t#endif")
    else:
        post_statements.append(f"\t{vector_ret_type} res;")
        post_statements.append(f"\tmemcpy(&res, &sres, sizeof(res));")

def _build_fallback_statements(isa, funcs, f, dt, mask_kind, cond, lmul, target_scalar_lmul):
    dt_par, dt_ret = compute_dt_par_dt_ret(None, None, dt, check_support=False)
    proto = funcs[f]["proto"]
    call_args = []
    cnt_reg = 0
    cnt_msk = 0
    cnt_val = 0
    cnt_ptr = 0

    pre_statements = []
    post_statements = []
    return_statement = None

    if mask_kind is not None:
        msk_dt = datatypes[dt_par]
        if "gather" in f or "scatter" in f:
            msk_dt = datatypes["uint" + str(get_dt_par_size(dt_par))]
        elif funcs[f]["proto"]["ret"].get("fixeddatatype"):
            msk_dt = datatypes[funcs[f]["proto"]["ret"]["fixeddatatype"]]
        _prepare_mask_variable(pre_statements, isa, msk_dt, "m0", cond, target_scalar_lmul, f, is_initial_mask=True)
        call_args.append("s_m0")
        cnt_msk += 1

        if mask_kind == "masks":
            rsrc_scalar_type = build_reg(datatypes[dt_par], scalar_isa, target_scalar_lmul, True, False)
            pre_statements.append(f"\t{rsrc_scalar_type} s_rsrc = {{0}};")
            pre_statements.append(f"\tmemcpy(&s_rsrc, &rsrc, sizeof(rsrc));")
            call_args.append("s_rsrc")

    for arg in proto["args"]:
        arg_type_name = arg["type"]
        realdatatype = _resolve_arg_datatype(arg, dt_par, dt_ret)

        if arg_type_name == "reg" or arg_type_name == "ret":
            arg_name = f"r{cnt_reg}"
            cnt_reg += 1
            scalar_type = build_type("reg", realdatatype, scalar_isa, target_scalar_lmul, True, False)
            pre_statements.append(f"\t{scalar_type} s_{arg_name} = {{0}};")
            pre_statements.append(f"\tmemcpy(&s_{arg_name}, &{arg_name}, sizeof({arg_name}));")
            call_args.append(f"s_{arg_name}")
        elif arg_type_name == "msk":
            arg_name = f"m{cnt_msk}"
            cnt_msk += 1
            _prepare_mask_variable(pre_statements, isa, realdatatype, arg_name, cond, target_scalar_lmul, f, is_initial_mask=False)
            call_args.append(f"s_{arg_name}")
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

    call_args_str = ", ".join(call_args)
    scalar_func_name = build_func_name_internal(scalar_isa, dt, dt_par, dt_ret, f, masked_version=mask_kind, lmul=target_scalar_lmul)

    ret_type_name = proto["ret"]["type"]
    if ret_type_name == "reg" or ret_type_name == "msk":
        vector_ret_type = build_type(ret_type_name, datatypes[dt_ret], isa, lmul, True, False)
        scalar_ret_type = build_type(ret_type_name, datatypes[dt_ret], scalar_isa, target_scalar_lmul, True, False)
        call_statement = f"{scalar_ret_type} sres = {scalar_func_name}({call_args_str});"

        _prepare_return_variable(post_statements, isa, datatypes[dt_ret], cond, target_scalar_lmul, f, vector_ret_type, ret_type_name)
        return_statement = "return res;"
    elif ret_type_name == "val":
        call_statement = f"return {scalar_func_name}({call_args_str});"
    else:
        call_statement = f"{scalar_func_name}({call_args_str});"

    pre_statements_str = "\n".join(pre_statements)
    post_statements_str = "\n".join(post_statements)
    return pre_statements_str, call_statement, post_statements_str, return_statement

def _format_fallback_body(pre, call, post, ret):
    lines = [pre] if pre else []
    lines.append(f"\t{call}")
    if post: lines.append(post)
    if ret:  lines.append(f"\t{ret}")
    return "\n".join(lines)

def _gen_c_auto_scalar_fallback_one(isa, file, funcs, f, dt, mask_kind, cond, lmul=0):
    dt_par, dt_ret = compute_dt_par_dt_ret(None, None, dt, check_support=False)
    func_name = build_func_name_internal(isa, dt, dt_par, dt_ret, f, masked_version=mask_kind, lmul=lmul)
    proto_str = build_proto(funcs[f]["proto"], dt_par, dt_ret, isa, func_name, lmul=lmul, isa_name=True, masked_version=mask_kind)

    super_isa = isa.get("super_isa", None)
    if super_isa and -2 in super_isa.get("sw_lmul", []):
        super_macro = f"defined(MIPP_{super_isa['name'].upper()})"
        body_super = _format_fallback_body(*_build_fallback_statements(isa, funcs, f, dt, mask_kind, cond, lmul, -2))
        body_std   = _format_fallback_body(*_build_fallback_statements(isa, funcs, f, dt, mask_kind, cond, lmul, lmul))
        full_body  = f"#if {super_macro}\n{body_super}\n#else\n{body_std}\n#endif"
    else:
        full_body  = _format_fallback_body(*_build_fallback_statements(isa, funcs, f, dt, mask_kind, cond, lmul, lmul))


    single_template = """{% if cond %}#if {{ cond }}
{% endif %}static {{ proto }} {
\t// Level 3 (Auto Scalar Fallback)
{{ body }}
}
{%- if cond %}
#endif
{%- endif %}"""
    j2 = Template(single_template, undefined=StrictUndefined)
    print(j2.render(cond=cond, proto=proto_str, body=full_body), file=file)



def _get_candidate_reqs(cand, isa, funcs, lmul=0):
    if "reqs" in cand:
        return cand["reqs"]
    f = cand["f"]
    ff = cand["ff"]
    dt = cand["dt"]
    dt_par, dt_ret = compute_dt_par_dt_ret(funcs, f, dt)
    pre_rendering = render_template(isa, ff, dt_par, dt_ret, func_name=f, lmul=lmul)
    try:
        reqs = get_requirements(pre_rendering, isa, funcs, f, dt_par, dt_ret, lmul=lmul)
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

def resolve_and_emit_missing_functions(isa, file, funcs, lmul=0, emit_separators=False):
    is_inc_mgr = hasattr(file, "get_fd")
    
    candidates_map = {}
    collected_candidates = isa.get("candidates", [])
    
    # 1. Initialize map keys
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

    # 2. Populate with collected candidates in a single pass O(M)
    for c in collected_candidates:
        c_f = c["f"]
        c_dt = c["dt"]
        c_dt_par, c_dt_ret = compute_dt_par_dt_ret(funcs, c_f, c_dt)
        c_dt_key = c_dt_par + "," + c_dt_ret
        c_mask_kind = c["ff"].get("version", None)
        key = (c_f, c_dt_key, c_mask_kind)
        if key in candidates_map:
            candidates_map[key].append(c)

    # 3. Add auto_scalar and stub candidates, then sort
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
                
                if isa["name"] != "scalar":
                    auto_scalar_reqs = {}
                    
                    if isa.get("hw_mask_requires_toreg", False):
                        if not (isa.get("hw_mask_is_bitfield", False) and f in ["toreg", "tomsk", "cast_k"]):
                            has_msk_arg = any(arg["type"] == "msk" for arg in funcs[f]["proto"]["args"]) or mask_kind is not None
                            if has_msk_arg:
                                single_dt_par = dt_par.split(",")[0]
                                req_dt_par = single_dt_par + "," + single_dt_par
                                auto_scalar_reqs.setdefault("toreg", []).append(req_dt_par)
                                auto_scalar_reqs.setdefault("tomsk", []).append(req_dt_par)
                                if isa.get("hw_mask_extract_via_store", False):
                                    auto_scalar_reqs.setdefault("store", []).append(req_dt_par)
                            
                            if funcs[f]["proto"]["ret"]["type"] == "msk":
                                single_dt_ret = dt_ret.split(",")[0]
                                req_dt_ret = single_dt_ret + "," + single_dt_ret
                                if req_dt_ret not in auto_scalar_reqs.get("toreg", []):
                                    auto_scalar_reqs.setdefault("toreg", []).append(req_dt_ret)
                                    auto_scalar_reqs.setdefault("tomsk", []).append(req_dt_ret)
                                    if isa.get("hw_mask_extract_via_store", False):
                                        if req_dt_ret not in auto_scalar_reqs.get("store", []):
                                            auto_scalar_reqs.setdefault("store", []).append(req_dt_ret)

                    # Check for vindex argument type generics
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
                    layout = isa.get("layout", {})
                    vlen_guard_tpl = layout.get("vlen_guard_template", None)
                    if vlen_guard_tpl and lmul < 0:
                        single_dt = dt_par.split(",")[0]
                        if "width" in isa.get("datatypes", {}).get(single_dt, {}):
                            width = isa["datatypes"][single_dt]["width"]
                            req_vlen = int(width) * abs(lmul)
                            vlen_guard = Template(vlen_guard_tpl, undefined=StrictUndefined).render(width=int(width), abs_lmul=abs(lmul))
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
                
                def get_cand_key(c):
                    lvl = c.get("level", 2)
                    pref = []
                    if "ff" in c:
                        pref = c["ff"].get("preferred_simd_ext", [])
                    if isinstance(pref, str):
                        pref = [pref]
                    if pref:
                        pref_score = 0 if isa["name"] in pref else 2
                    else:
                        pref_score = 1
                    return (lvl, pref_score)
                candidates_map[key].sort(key=get_cand_key)
                
    isa_known_true = [isa["define"]] if "define" in isa and isa["define"] else []

    def normalize_cond(c):
        return simplify_cond_str(c, known_true_conds=isa_known_true)

    def negate_cond(c):
        return tool_negate_cond(c)

    def are_conds_mutually_exclusive(c1, c2):
        return tool_are_conds_mutually_exclusive(c1, c2, known_true_conds=isa_known_true)

    def intersect_conds(c1, c2):
        return tool_intersect_conds(c1, c2, known_true_conds=isa_known_true)

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
                if cand.get("emitted", False):
                    continue
                if cand["level"] > max_level:
                    continue
                    
                # Filter by SIMD size if specified
                cand_simd_size = None
                if "ff" in cand:
                    cand_simd_size = cand["ff"].get("simd_size", None)
                if cand_simd_size is not None:
                    isa_size = isa.get("size", None)
                    if isa_size is None or isinstance(isa_size, list):
                        active_size = None
                    else:
                        try:
                            active_size = int(isa_size)
                            if lmul is not None and lmul != 0:
                                if lmul > 0:
                                    active_size *= lmul
                                else:
                                    active_size //= abs(lmul)
                        except (ValueError, TypeError):
                            active_size = None
                    
                    if active_size is None:
                        continue
                    
                    if isinstance(cand_simd_size, list):
                        if active_size not in cand_simd_size:
                            continue
                    else:
                        if active_size != int(cand_simd_size):
                            continue
                    
                cand_if = ""
                if cand["type"] in ["native_or_emu", "generic_emu", "auto_scalar"]:
                    cand_if = cand["ff"].get("if", "")
                    if cand["type"] == "native_or_emu" and not cand_if and "define" in isa and isa["define"]:
                        cand_if = isa["define"]
                    
                target_cond = intersect_conds(cand_if, rem_cond)
                if target_cond is None:
                    continue
                    
                reqs = _get_candidate_reqs(cand, isa, funcs, lmul=lmul)
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
                    if restricted_target_cond == "0":
                        continue
                    resolved[key].append((cand, restricted_target_cond))
                    
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
            reqs = _get_candidate_reqs(cand, isa, funcs, lmul=lmul)
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
                from codegen.lmul_orchestrator import maybe_emit_lmul_separator
                maybe_emit_lmul_separator(isa["name"], f, file_w)
            elif lmul < 0:
                from codegen.lmul_orchestrator import maybe_emit_ldiv_separator
                maybe_emit_ldiv_separator(isa["name"], f, file_w)
        
        # Emit forward declarations first to prevent order-of-declaration issues
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
                        func_name = build_func_name_internal(isa, dt, dt_par, dt_ret, f, masked_version=mask_kind, lmul=lmul)
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
                        pre_rendering = render_template(isa, cand["ff"], dt_par, dt_ret, func_name=f, lmul=lmul)
                        ph_ret = parse_placeholders(pre_rendering, isa, funcs, f, dt_par, dt_ret, lmul=lmul)
                        post_rendering = ph_ret["converted_ir"]
                        
                        if not cand.get("emitted", False):
                            print("", file=file_w)
                            if cond != "":
                                print(f"#if {cond}", file=file_w)
                            emit_function_body(funcs, f, isa, dt, dt_par, dt_ret, cand["ff"], post_rendering, file_w, masked_version=mask_kind, level=cand["level"], lmul=lmul)
                            if cond != "":
                                print("#endif", file=file_w)
                            
                    elif cand["type"] == "auto_scalar":
                        _gen_c_auto_scalar_fallback_one(isa, file_w, funcs, f, dt, mask_kind, cond, lmul=lmul)
                        
                    elif cand["type"] == "stub":
                        if cond != "":
                            print(f"#if {cond}", file=file_w)
                        func_name = build_func_name_internal(isa, dt, dt_par, dt_ret, f, masked_version=mask_kind, lmul=lmul)
                        _missing_emit_stub(file_w, funcs, f, dt_par, dt_ret, isa, func_name, masked_version=mask_kind, lmul=lmul)
                        if cond != "":
                            print("#endif", file=file_w)
