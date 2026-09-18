#!/usr/bin/env python3
"""
MIPP API Data Generator (gen_mipp_api_data.py)
Extracts and normalizes metadata from registry_interfaces, funcs_docs, tests_specs,
and per-ISA hardware implementations using candidate_resolver to compute effective
acceleration levels and build a comprehensive vendor intrinsics reverse index.
Exports: docs/assets/data/mipp_api_index.json
"""
import sys
import os
import json
import re
import copy
import io
import textwrap

# Ensure paths work whether executed from repo root or generator/
base_generator_dir = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, base_generator_dir)
sys.path.insert(1, os.path.join(base_generator_dir, "helpers_headers"))
sys.path.insert(1, os.path.join(base_generator_dir, "simd_ext", "scalar"))

from tools import (
    load_isa_config, all_datatypes, all_datatypes_cart_prod,
    all_datatypes_same_size, all_datatypes_widenning,
    build_func_name, build_func_name_short, build_proto,
    operators_arithm, operators_binary, operators_order
)
from registry import interfaces, categories, scalar_isa, scalar_implems
from gen_mipp_headers import discover_and_sort_isas
from c_generator import resolve_lmul_in_isa, register_all_candidates
from codegen.candidate_resolver import resolve_candidates, render_template
from scalar_gen import gen_c_functions_scalar_one


def clean_latex(latex_str):
    if not latex_str:
        return ""
    # Remove surrounding \text{}, convert common LaTeX patterns to readable pseudo-math
    s = latex_str
    s = re.sub(r'\\text\{([^}]+)\}', r'\1', s)
    s = re.sub(r'\\operatorname\{([^}]+)\}', r'\1', s)
    s = s.replace(r'\_', '_').replace(r'\ ', ' ')
    s = s.replace(r'\sim', '~').replace(r'\&', '&').replace(r'\le', '<=').replace(r'\ge', '>=')
    return s


def clean_code_indentation(s):
    if not s:
        return ""
    s = s.replace('\t', '    ')
    lines = s.splitlines()
    non_empty = [l for l in lines[1:] if l.strip()]
    if len(lines) > 1 and len(lines[0]) - len(lines[0].lstrip()) == 0 and non_empty:
        common_prefix = os.path.commonprefix([l[:len(l) - len(l.lstrip())] for l in non_empty])
        if common_prefix:
            lines = [lines[0]] + [(l[len(common_prefix):] if l.strip() else '') for l in lines[1:]]
            s = '\n'.join(lines)
    return textwrap.dedent(s).strip()


def build_cpp_obj_prototype(func, interfaces_dict):
    """
    Generates a representative C++ Object API prototype (e.g. `r0 + r1` or `r0.blend(r1, m0)`).
    """
    args = interfaces_dict[func]["proto"]["args"]
    ret = interfaces_dict[func]["proto"]["ret"]
    ret_type = "Rvm<T,LMUL>" if func.endswith("_k") or ret.get("type") == "msk" else "Rvd<T,LMUL>"
    
    # Check operator overloads
    all_binary_ops = {}
    all_binary_ops.update(operators_arithm)
    all_binary_ops.update(operators_binary)
    all_binary_ops.update(operators_order)
    
    if func in all_binary_ops and len(args) == 2:
        sym = all_binary_ops[func]["operation"]
        return f"inline {ret_type} operator {sym} (const Rvd<T,LMUL>& r1) const;"
    elif func == "notb" and len(args) == 1:
        return f"inline {ret_type} operator~ () const;"
    
    # Method invocation on object (first argument is 'this', rest are passed as args)
    method_name = func[:-2] if func.endswith("_k") else func
    if len(args) <= 1:
        return f"inline {ret_type} r0.{method_name}() const;"
    
    arg_strs = []
    reg_idx = 1
    mask_idx = 0
    for arg in args[1:]:
        atype = arg.get("type", "reg")
        if atype == "reg":
            arg_strs.append(f"const Rvd<T,LMUL>& r{reg_idx}")
            reg_idx += 1
        elif atype == "msk":
            arg_strs.append(f"const Rvm<T,LMUL>& m{mask_idx}")
            mask_idx += 1
        elif atype == "scl":
            arg_strs.append("const T val")
        elif atype == "cst":
            arg_strs.append("const T val")
        elif atype == "ptr":
            arg_strs.append("const T* ptr")
        else:
            arg_strs.append("arg")
            
    return f"inline {ret_type} r0.{method_name}({', '.join(arg_strs)}) const;"


def format_scalar_proto(code):
    """
    Formats scalar function prototypes with 'static' on the first line,
    return type and function name on the second line, and parameters aligned
    one per line matching MIPP C styling.
    """
    code = code.strip()
    match = re.match(r"^(?:static\s+)?(?:inline\s+)?([a-zA-Z0-9_]+)\s+([a-zA-Z0-9_]+)\s*\((.*?)\)\s*\{", code, re.DOTALL)
    if not match:
        return code
    ret_type, func_name, args_str = match.groups()
    body = code[match.end():]
    body = re.sub(r"^[ \t]*//[ \t]*Level[ \t]+\d[^\n]*\r?\n?", "", body, flags=re.MULTILINE)
    args = [a.strip() for a in args_str.split(",") if a.strip()]
    if not args:
        header = f"static\n{ret_type} {func_name}()\n{{"
        return header + body

    parsed_args = []
    for a in args:
        parts = a.rsplit(None, 1)
        if len(parts) == 2:
            parsed_args.append((parts[0], parts[1]))
        else:
            parsed_args.append(("", a))

    max_type_len = max(len(t) for t, n in parsed_args)
    line2_prefix = f"{ret_type} {func_name}("
    indent_spaces = " " * len(line2_prefix)

    formatted_lines = []
    if len(parsed_args) == 1:
        t, n = parsed_args[0]
        formatted_lines.append(f"{line2_prefix}{t} {n})")
    else:
        for i, (t, n) in enumerate(parsed_args):
            aligned_t = t.ljust(max_type_len)
            suffix = ")" if i == len(parsed_args) - 1 else ","
            if i == 0:
                formatted_lines.append(f"{line2_prefix}{aligned_t} {n}{suffix}")
            else:
                formatted_lines.append(f"{indent_spaces}{aligned_t} {n}{suffix}")

    header = "static\n" + "\n".join(formatted_lines) + "\n{"
    return header + body


def extract_scalar_macros(scalar_gen_path):
    """
    Extracts all custom macro definitions from tpl_header_scalar in scalar_gen.py.
    """
    macros = {}
    if not os.path.exists(scalar_gen_path):
        return macros

    with open(scalar_gen_path, "r", encoding="utf-8") as f:
        lines = f.readlines()

    i = 0
    while i < len(lines):
        line = lines[i].strip()
        if line.startswith("#define"):
            macro_line = line
            while macro_line.endswith("\\") and i + 1 < len(lines):
                i += 1
                macro_line = macro_line[:-1].strip() + " " + lines[i].strip()

            m = re.match(r"^#define\s+([A-Za-z0-9_]+)(?:\(([^)]*)\))?\s*(.*)$", macro_line)
            if m:
                name = m.group(1)
                args = m.group(2)
                body = m.group(3).strip()
                body = re.sub(r'^[\\ ]+', '', body).strip()
                if not (name.startswith("MIPP_") or name.startswith("MY_")):
                    sig = name + "(" + args + ")" if args is not None else name
                    macros[name] = {
                        "name": name,
                        "signature": sig,
                        "definition": "#define " + sig + " " + body,
                        "body": body
                    }
        i += 1
    return macros


def extract_scalar_reference_algos(func, dtypes, mask_flags):
    """
    Extracts C scalar reference implementations for all supported LMULs, datatypes, and mask variants.
    Returns a nested dict: { lmul_str: { dt: { "unmasked": code, "mask": code, "maskz": code, "masks": code } } }
    """
    algos_by_lmul = {}
    if func not in scalar_implems:
        return algos_by_lmul

    mask_variants_to_extract = ["no_mask"]
    if mask_flags.get("mask"):
        mask_variants_to_extract.append("mask")
    if mask_flags.get("maskz"):
        mask_variants_to_extract.append("maskz")
    if mask_flags.get("masks"):
        mask_variants_to_extract.append("masks")

    # MIPP LMUL options to generate: 1 (lmul=0 in gen_c), 2, 4, 8, -2
    lmul_map = {
        "1": 0,
        "2": 2,
        "4": 4,
        "8": 8,
        "-2": -2
    }

    for lmul_key, lmul_val in lmul_map.items():
        algos_by_lmul[lmul_key] = {}
        for dt in dtypes:
            dt_par = dt.split(",")[0]
            matching_ff = None
            for ff in scalar_implems[func]:
                ff_dts = ff.get("datatypes", [])
                if not ff_dts or dt in ff_dts or dt_par in ff_dts:
                    matching_ff = ff
                    break
            if not matching_ff:
                matching_ff = scalar_implems[func][0]

            algos_by_lmul[lmul_key][dt] = {}
            for mvariant in mask_variants_to_extract:
                variant_key = "unmasked" if mvariant == "no_mask" else mvariant
                try:
                    ff_copy = copy.copy(matching_ff)
                    ff_copy["mask_variants"] = [mvariant]
                    buf = io.StringIO()
                    gen_c_functions_scalar_one(scalar_isa, buf, interfaces, func, ff_copy, dt, lmul=lmul_val)
                    code = buf.getvalue().strip()
                    code = re.sub(r'\binline\s+', '', code)
                    code = format_scalar_proto(code)
                    algos_by_lmul[lmul_key][dt][variant_key] = code
                except Exception:
                    pass
    return algos_by_lmul


def format_domain_obj(d_val):
    """
    Formats a domain range or constraint object into a clean mathematical string.
    """
    if isinstance(d_val, list):
        parts = [format_domain_obj(x) for x in d_val]
        return " ∪ ".join(parts)
    if not isinstance(d_val, dict):
        return str(d_val)
    if "min" in d_val and "max" in d_val:
        return "[" + str(d_val.get("min")) + ", " + str(d_val.get("max")) + "]"
    if d_val.get("strictly_negative"):
        return "< 0 (strictly negative)"
    if d_val.get("strictly_positive"):
        return "> 0 (strictly positive)"
    if d_val.get("negative"):
        return "≤ 0 (negative)"
    if d_val.get("positive"):
        return "≥ 0 (positive)"
    if "values" in d_val:
        return "{" + ", ".join(map(str, d_val["values"])) + "}"
    return "Custom"


def parse_function_test_specs(func, dtypes, mask_flags, funcs_specs, default_spec):
    """
    Parses comprehensive test and verification specifications from tests_specs.json
    across all mask variants (unmasked, mask, maskz, masks) and datatypes.
    """
    func_data = funcs_specs.get(func, {})
    variants = {}

    has_variants = any(k in func_data for k in ("unmasked", "mask", "maskz", "masks"))

    for v_key in ["unmasked", "mask", "maskz", "masks"]:
        if v_key != "unmasked" and not mask_flags.get(v_key):
            continue

        v_spec = func_data.get(v_key, {}) if has_variants else func_data
        comp = v_spec.get("comparison", func_data.get("comparison", default_spec.get("comparison", "exact")))
        tol = v_spec.get("tolerance", func_data.get("tolerance", default_spec.get("tolerance", {"type": "exact"})))
        domain = v_spec.get("domain", func_data.get("domain", default_spec.get("domain", {})))
        domain_src = v_spec.get("domain_src", func_data.get("domain_src", {}))
        mask_pat = v_spec.get("mask_pattern", func_data.get("mask_pattern", default_spec.get("mask_pattern", "uniform_bool")))
        overflow = v_spec.get("overflow_check", func_data.get("overflow_check", None))

        by_dt_table = []
        for dt in dtypes:
            dt_single = dt.split(",")[0]

            dom_str = None
            if "by_datatype" in domain and dt_single in domain["by_datatype"]:
                dom_str = format_domain_obj(domain["by_datatype"][dt_single])
            elif "rules" in domain:
                matching_rules = [r for r in domain["rules"] if r.get("datatype") == dt_single]
                if matching_rules:
                    rule_strs = []
                    for r in matching_rules:
                        r_prefix = "LMUL " + str(r.get("lmul")) + ": " if "lmul" in r else ""
                        rule_strs.append(r_prefix + format_domain_obj(r))
                    dom_str = "; ".join(rule_strs)
            elif "min" in domain and "max" in domain:
                dom_str = "[" + str(domain.get("min")) + ", " + str(domain.get("max")) + "]"
            elif "default" in domain and isinstance(domain["default"], dict) and "min" in domain["default"]:
                dom_str = format_domain_obj(domain["default"])

            if not dom_str:
                dom_str = "Full representable range"

            notes = []
            if "by_define" in domain:
                for def_name, def_obj in domain["by_define"].items():
                    if "by_datatype" in def_obj and dt_single in def_obj["by_datatype"]:
                        notes.append(def_name + ": " + format_domain_obj(def_obj["by_datatype"][dt_single]))
            if "by_lmul" in domain:
                for lmul_tag, lmul_obj in domain["by_lmul"].items():
                    notes.append(lmul_tag + ": " + format_domain_obj(lmul_obj))
            if notes:
                dom_str += " (" + ", ".join(notes) + ")"

            if domain_src:
                src_dom = None
                if "by_datatype" in domain_src and dt_single in domain_src["by_datatype"]:
                    src_dom = format_domain_obj(domain_src["by_datatype"][dt_single])
                elif "default" in domain_src:
                    src_dom = format_domain_obj(domain_src["default"])
                if src_dom:
                    dom_str += " | src: " + src_dom

            if "by_datatype" in tol and dt_single in tol["by_datatype"]:
                t_val = tol["by_datatype"][dt_single]
                t_type = t_val.get("type", "max_abs_diff")
                t_num = t_val.get("value", 0)
                tol_str = "≤ " + str(t_num) + " (" + str(t_type) + ")"
            elif tol.get("type") == "ulp":
                ulp_v = tol.get("value", 1)
                tol_str = "≤ " + str(ulp_v) + " ULP" if dt_single.startswith("float") else "Bit-exact (0 error)"
            elif tol.get("type") == "exact":
                tol_str = "Bit-exact (0 error)"
            else:
                tol_str = str(tol.get("type", "Exact"))

            by_dt_table.append({
                "datatype": dt,
                "domain": dom_str,
                "tolerance": tol_str,
                "comparison": comp
            })

        variants[v_key] = {
            "comparison": comp,
            "mask_pattern": mask_pat,
            "overflow_check": overflow,
            "table": by_dt_table
        }

    return {
        "variants": variants,
        "comparison": func_data.get("comparison", default_spec.get("comparison", "exact")),
        "overflow_check": func_data.get("overflow_check", default_spec.get("overflow_check", None)),
        "table": variants.get("unmasked", {}).get("table", [])
    }


def build_code_snippets(func, category, spec_info, native_avx_instr=None):
    """
    Generates minimal, self-contained reproducible code snippets for C99, C++, and C++ Object,
    as well as a standalone native intrinsic example that compiles directly on Godbolt.
    """
    args = interfaces[func]["proto"]["args"]
    n_args = len(args)
    
    # C++ functional snippet
    cpp_lines = [
        "#include <iostream>",
        "#include <mipp.h>",
        "",
        "int main() {",
        "    // 1. Initialize vector registers",
        "    mipp::reg r0 = mipp::set1<float>(1.5f);"
    ]
    call_args = ["r0"]
    if n_args >= 2:
        if args[1].get("type") == "msk":
            cpp_lines.append("    mipp::msk m0 = mipp::set0<float>();")
            call_args.append("m0")
        else:
            cpp_lines.append("    mipp::reg r1 = mipp::set1<float>(2.5f);")
            call_args.append("r1")
    if n_args >= 3:
        if args[2].get("type") == "msk":
            cpp_lines.append("    mipp::msk m0 = mipp::set0<float>();")
            call_args.append("m0")
        else:
            cpp_lines.append("    mipp::reg r2 = mipp::set1<float>(0.5f);")
            call_args.append("r2")
            
    cpp_name = func[:-2] if func.endswith("_k") else func
    cpp_lines.append("")
    cpp_lines.append("    // 2. Execute MIPP operation")
    cpp_lines.append(f"    auto res = mipp::{cpp_name}({', '.join(call_args)});")
    cpp_lines.append("")
    cpp_lines.append("    // 3. Inspect results")
    cpp_lines.append("    std::cout << \"Vector elements count: \" << mipp::N<float>() << std::endl;")
    cpp_lines.append("    return 0;")
    cpp_lines.append("}")
    
    # C99 snippet
    c99_lines = [
        "#include <stdio.h>",
        "#include <mipp.h>",
        "",
        "int main(void) {",
        "    // 1. Initialize C99 vector registers",
        "    rvd_float32_m1_t r0 = mipp_set1_float32_m1(1.5f);"
    ]
    c_args = ["r0"]
    if n_args >= 2:
        if args[1].get("type") == "msk":
            c99_lines.append("    rvm_float32_m1_t m0 = mipp_set0_float32_m1();")
            c_args.append("m0")
        else:
            c99_lines.append("    rvd_float32_m1_t r1 = mipp_set1_float32_m1(2.5f);")
            c_args.append("r1")
    if n_args >= 3:
        if args[2].get("type") == "msk":
            c99_lines.append("    rvm_float32_m1_t m0 = mipp_set0_float32_m1();")
            c_args.append("m0")
        else:
            c99_lines.append("    rvd_float32_m1_t r2 = mipp_set1_float32_m1(0.5f);")
            c_args.append("r2")
            
    c99_lines.append("")
    c99_lines.append("    // 2. Execute C99 MIPP function")
    c99_lines.append(f"    rvd_float32_m1_t res = mipp_{func}_float32_m1({', '.join(c_args)});")
    c99_lines.append("")
    c99_lines.append("    // 3. Inspect first element")
    c99_lines.append("    printf(\"First vector element: %f\\n\", mipp_get_float32_m1(res, 0));")
    c99_lines.append("    return 0;")
    c99_lines.append("}")

    # Standalone Native Intrinsic demo that compiles immediately on Godbolt without external libs
    godbolt_lines = [
        "#include <stdio.h>",
        "#include <immintrin.h>",
        "",
        "// Standalone demonstration of the underlying native instruction",
        "// Compiles out of the box on Compiler Explorer (x86-64 GCC -O3 -mavx2)",
        "int main() {",
        "    __m256 v0 = _mm256_set1_ps(1.5f);",
        "    __m256 v1 = _mm256_set1_ps(2.5f);"
    ]
    if native_avx_instr and "blend" in native_avx_instr:
        godbolt_lines.append("    __m256 m0 = _mm256_setzero_ps();")
        godbolt_lines.append(f"    __m256 res = {native_avx_instr}(v1, v0, m0);")
    elif native_avx_instr and n_args == 1:
        godbolt_lines.append(f"    __m256 res = {native_avx_instr}(v0);")
    elif native_avx_instr and n_args >= 2:
        godbolt_lines.append(f"    __m256 res = {native_avx_instr}(v0, v1);")
    else:
        godbolt_lines.append(f"    __m256 res = _mm256_add_ps(v0, v1); // MIPP native mapping for {func}")
        
    godbolt_lines.extend([
        "    float out[8];",
        "    _mm256_storeu_ps(out, res);",
        "    printf(\"Native AVX execution result: %f\\n\", out[0]);",
        "    return 0;",
        "}"
    ])
    
    return {
        "cpp": "\n".join(cpp_lines),
        "c99": "\n".join(c99_lines),
        "godbolt_native": "\n".join(godbolt_lines)
    }


def generate_mipp_api_data(project_root=None):
    """
    Main extraction pipeline: merges metadata from registry, candidate solver,
    docs, and tests to produce the complete MIPP API Index dataset.
    """
    if project_root is None:
        project_root = os.path.dirname(base_generator_dir)

    from gen_mipp_docs import SpecFuncInfo, match_args_type_cpp

    # 1. Discover all target ISAs
    isas_dict, implems_dict_raw, sorted_names = discover_and_sort_isas(base_generator_dir)
    target_isas = [name for name in sorted_names if name != "scalar"]

    # 2. Load Docs and Test Metadata
    funcs_docs_path = os.path.join(base_generator_dir, "helpers_headers", "funcs_docs.json")
    funcs_docs = {}
    if os.path.exists(funcs_docs_path):
        with open(funcs_docs_path, "r", encoding="utf-8") as f:
            funcs_docs = json.load(f)

    tests_specs_path = os.path.join(base_generator_dir, "helpers_tests", "tests_specs.json")
    tests_specs_data = {}
    if os.path.exists(tests_specs_path):
        with open(tests_specs_path, "r", encoding="utf-8") as f:
            tests_specs_data = json.load(f)
    default_test_spec = tests_specs_data.get("default", {})

    # 3. Solve Candidates & Resolve Effective Levels per ISA
    print(f"[gen_mipp_api_data] Resolving candidates for ISAs: {', '.join(target_isas)}...")
    isa_solved_map = {}
    for isa_name in target_isas:
        native_impl, emu_impl = implems_dict_raw[isa_name]
        isa_conf = isas_dict[isa_name]
        resolved_isa = resolve_lmul_in_isa(isa_conf, "0")
        resolved_isa["candidates"] = []
        copy_interfaces = copy.deepcopy(interfaces)
        register_all_candidates(resolved_isa, copy_interfaces, native_impl, emu_impl, lmul=0)
        resolved_map = resolve_candidates(resolved_isa, copy_interfaces, lmul=0)
        isa_solved_map[isa_name] = (resolved_isa, resolved_map)

    # Regex to identify intrinsic calls in rendered code
    intrinsic_call_regex = re.compile(
        r'\b(_mm(?:256|512)?_[a-zA-Z0-9_]+|v[a-z0-9_]+|sv[a-z0-9_]+|__riscv_[a-zA-Z0-9_]+)\s*\('
    )
    ignored_intrinsics = {
        'svptrue_b8', 'svptrue_b16', 'svptrue_b32', 'svptrue_b64', 'svptrue_b'
    }

    # Extract scalar macros from scalar_gen.py
    scalar_gen_path = os.path.join(base_generator_dir, "simd_ext", "scalar", "scalar_gen.py")
    scalar_macros = extract_scalar_macros(scalar_gen_path)

    # Collect ISA hardware LMUL metadata
    isa_metadata = {}
    for isa_name in target_isas:
        try:
            isa_conf = isas_dict[isa_name]
            hw_l = [int(x) for x in isa_conf.get("hw_lmul", [1])]
            if 1 not in hw_l and len(hw_l) == 0:
                hw_l = [1]
            sw_l = [int(x) for x in isa_conf.get("sw_lmul", [])]
        except Exception:
            hw_l = [1]
            sw_l = []
        isa_metadata[isa_name] = {
            "hw_lmul": hw_l,
            "sw_lmul": sw_l
        }

    # 4. Process each of the 85 functions
    api_entries = []

    for func, func_def in interfaces.items():
        # Identify category
        cat_name = "arithmetic"
        for cat, flist in categories.items():
            if func in flist:
                cat_name = cat
                break

        doc_meta = funcs_docs.get(func, {})
        description = doc_meta.get("description", f"MIPP vector primitive {func}.")
        latex = doc_meta.get("latex", "")
        math_semantics = clean_latex(latex) if latex else description

        # Spec helper for prototype rendering
        spec_info = SpecFuncInfo()
        spec_info.gen_spec_func_info(func, interfaces, categories)

        # Masking support flags
        mask_support_obj = func_def.get("mask_support", None)
        mask_flags = {
            "unmasked": True,
            "mask": mask_support_obj.is_maskable() if mask_support_obj else False,
            "maskz": mask_support_obj.is_maskzable() if mask_support_obj else False,
            "masks": mask_support_obj.is_masksable() if mask_support_obj else False
        }

        # Collect ISA support, levels, and native instructions
        isa_support = {}
        vendor_intrinsics_reverse_index = set()

        for isa_name in target_isas:
            resolved_isa, resolved_map = isa_solved_map[isa_name]
            by_datatype = {}
            native_instructions = {}
            rendered_code_snippets = {}
            emulation_algorithms = {}
            masked_by_datatype = {"mask": {}, "maskz": {}, "masks": {}}

            for dt in func_def["datatypes"]:
                dt_par, dt_ret = dt.split(",") if "," in dt else (dt, dt)
                dt_key = f"{dt_par},{dt_ret}"

                # Unmasked level
                cands = resolved_map.get((func, dt_key, None), [])
                active_cands = [cand for cand, cond in cands if cond != "0"]
                lvl = min([cand["level"] for cand in active_cands], default=3)
                by_datatype[dt] = lvl

                # Check candidates for native instruction or emulation algorithm
                for cand in active_cands:
                    if cand["level"] == 0 and cand.get("ff") and "template" in cand["ff"]:
                        try:
                            rend = render_template(resolved_isa, cand["ff"], dt_par, dt_ret, func, lmul=0)
                            rend_no_comments = re.sub(r'/\*.*?\*/', '', rend, flags=re.DOTALL)
                            rend_no_comments = re.sub(r'//.*', '', rend_no_comments)

                            rend_clean = rend.strip().replace("\n", " ").replace("\t", " ")
                            rend_clean = re.sub(r'\s+', ' ', rend_clean)
                            rendered_code_snippets[dt] = rend_clean
                            
                            matches = intrinsic_call_regex.findall(rend_no_comments)
                            for m in matches:
                                if m not in ignored_intrinsics:
                                    native_instructions[dt] = m
                                    vendor_intrinsics_reverse_index.add(m)
                                    break
                        except Exception:
                            pass
                    elif cand["level"] in [1, 2] and cand.get("ff") and "template" in cand["ff"]:
                        try:
                            rend = render_template(resolved_isa, cand["ff"], dt_par, dt_ret, func, lmul=0)
                            s = rend
                            s = re.sub(r'%r<[^>]*>%', 'mipp::reg', s)
                            s = re.sub(r'%m<[^>]*>%', 'mipp::msk', s)
                            s = re.sub(r'%([a-zA-Z0-9_]+)<[^>]*>%', r'mipp::\1', s)
                            s = re.sub(r'%', '', s)
                            s = clean_code_indentation(s)
                            if s and dt not in emulation_algorithms:
                                emulation_algorithms[dt] = s
                        except Exception:
                            pass

                # Masked levels
                for mkind in ["mask", "maskz", "masks"]:
                    if mask_flags.get(mkind, False):
                        m_cands = resolved_map.get((func, dt_key, mkind), [])
                        m_active = [cand for cand, cond in m_cands if cond != "0"]
                        m_lvl = min([cand["level"] for cand in m_active], default=3)
                        masked_by_datatype[mkind][dt] = m_lvl

            # Overall level for this ISA (best level across all supported types)
            overall_level = min(by_datatype.values()) if by_datatype else 3

            isa_support[isa_name] = {
                "overall_level": overall_level,
                "by_datatype": by_datatype,
                "native_instructions": native_instructions,
                "code_snippets": rendered_code_snippets,
                "emulation_algorithms": emulation_algorithms,
                "masked_by_datatype": masked_by_datatype,
                "hw_lmul": isa_metadata.get(isa_name, {}).get("hw_lmul", [1]),
                "sw_lmul": isa_metadata.get(isa_name, {}).get("sw_lmul", [])
            }

        # Prototypes across flavors and LMUL ratios
        cpp_obj_proto = build_cpp_obj_prototype(func, interfaces)

        c99_samples = {}
        cpp_samples = {}
        cpp_obj_samples = {}

        mask_variants_list = ["unmasked"]
        if mask_flags.get("mask"):
            mask_variants_list.append("mask")
        if mask_flags.get("maskz"):
            mask_variants_list.append("maskz")
        if mask_flags.get("masks"):
            mask_variants_list.append("masks")

        for lmul in [1, 2, 4, 8, -2]:
            lmul_key = str(lmul)
            c99_samples[lmul_key] = {}
            cpp_samples[lmul_key] = {}

            for mvariant in mask_variants_list:
                m_param = None if mvariant == "unmasked" else mvariant
                try:
                    c99_text = spec_info.func_to_str_c(lmul, mask_kind=m_param).strip()
                    c99_lines = [re.sub(r'\binline\s+', '', line) for line in c99_text.splitlines()]
                    c99_samples[lmul_key][mvariant] = c99_lines
                except Exception:
                    c99_samples[lmul_key][mvariant] = []

                try:
                    cpp_text = spec_info.func_to_str_cpp(lmul, mask_kind=m_param).strip()
                    cpp_samples[lmul_key][mvariant] = re.sub(r'\binline\s+', '', cpp_text)
                except Exception:
                    cpp_samples[lmul_key][mvariant] = ""

            cpp_obj_samples[lmul_key] = re.sub(r'\binline\s+', '', cpp_obj_proto)

        # Test verification specifications
        merged_test_spec = parse_function_test_specs(
            func, func_def["datatypes"], mask_flags, tests_specs_data.get("functions", {}), default_test_spec
        )

        # Reference algorithms across supported datatypes and mask variants
        ref_algos = extract_scalar_reference_algos(func, func_def["datatypes"], mask_flags)
        first_dt = func_def["datatypes"][0] if func_def["datatypes"] else "float32"
        ref_algo_default = ref_algos.get("1", {}).get(first_dt, {}).get("unmasked", "") if ref_algos else ""

        # Reproducible code snippet generator + Godbolt native sample
        native_avx = isa_support.get("avx", {}).get("native_instructions", {}).get("float32", None)
        snippets = build_code_snippets(func, cat_name, spec_info, native_avx)

        # Standardized API object
        entry = {
            "name": func,
            "category": cat_name,
            "description": description,
            "latex": latex,
            "math_semantics": math_semantics,
            "datatypes": func_def["datatypes"],
            "mask_support": mask_flags,
            "isa_support": isa_support,
            "vendor_intrinsics_reverse_index": sorted(list(vendor_intrinsics_reverse_index)),
            "prototypes": {
                "c99": (c99_samples.get("1", {}).get("unmasked", [""])[0]
                        if c99_samples.get("1", {}).get("unmasked") else ""),
                "cpp": cpp_samples.get("1", {}).get("unmasked", ""),
                "cpp_obj": cpp_obj_proto,
                "c99_samples": c99_samples,
                "cpp_samples": cpp_samples,
                "cpp_obj_samples": cpp_obj_samples
            },
            "reference_algo": ref_algo_default,
            "reference_algos": ref_algos,
            "scalar_macros": scalar_macros,
            "test_specs": merged_test_spec,
            "snippets": snippets,
            "doc_url": f"../funcs_support/{cat_name}/{func}.md"
        }

        api_entries.append(entry)

    # Sort entries alphabetically by function name
    api_entries.sort(key=lambda x: x["name"])

    # 5. Export JSON to docs/assets/data/mipp_api_index.json
    output_dir = os.path.join(project_root, "docs", "assets", "data")
    os.makedirs(output_dir, exist_ok=True)
    output_file = os.path.join(output_dir, "mipp_api_index.json")

    with open(output_file, "w", encoding="utf-8") as f:
        json.dump(api_entries, f, indent=2, ensure_ascii=False)

    # Live sync to site/ and active MkDocs livereload temporary cache directories
    import glob, shutil
    site_output = os.path.join(project_root, "site", "assets", "data", "mipp_api_index.json")
    if os.path.exists(os.path.dirname(site_output)):
        try:
            shutil.copyfile(output_file, site_output)
        except Exception:
            pass
    for temp_dir in glob.glob("/var/folders/*/*/*/mkdocs_*/assets/data"):
        try:
            shutil.copyfile(output_file, os.path.join(temp_dir, "mipp_api_index.json"))
        except Exception:
            pass
    for temp_dir in glob.glob("/tmp/mkdocs_*/assets/data"):
        try:
            shutil.copyfile(output_file, os.path.join(temp_dir, "mipp_api_index.json"))
        except Exception:
            pass

    file_size_kb = os.path.getsize(output_file) / 1024
    print(f"[gen_mipp_api_data] Successfully generated {len(api_entries)} functions in {output_file} ({file_size_kb:.1f} KB)")
    return output_file


def export_api_data(project_root=None):
    """
    Public entrypoint called by gen_mipp_docs.py.
    """
    return generate_mipp_api_data(project_root)


if __name__ == "__main__":
    generate_mipp_api_data()
