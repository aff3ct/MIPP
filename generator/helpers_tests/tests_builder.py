"""
Declarative Test Generation Engine for MIPP.
Consumes MIPP registries and JSON specs to build complete Catch2 test files.
"""

import json
import copy
import os
import re
import sys
import jsonschema
from typing import Dict, List, Any, Optional, Set

from .dialect_adapters import DialectAdapter, CppDialectAdapter, CDialectAdapter, ObjDialectAdapter
from tools import DATATYPES_MAP


class TestBuilderEngine:

    def __init__(self, base_dir: str = ".", active_audits: Optional[Set[str]] = None):
        self.base_dir = base_dir
        if active_audits is None:
            self.active_audits = {"coverage", "redundancy", "consistency"}
        else:
            self.active_audits = active_audits
        self.helpers_tests_dir = os.path.dirname(os.path.abspath(__file__))
        self.schemas_dir = os.path.join(self.helpers_tests_dir, "schemas")
        self.helpers_headers_dir = os.path.join(base_dir, "generator", "helpers_headers")
        self.simd_ext_dir = os.path.join(base_dir, "generator", "simd_ext")

        print("  ➔ Validating JSON configuration schemas...")
        self.component_templates = self._load_and_validate("tests_component_templates.json", "component_templates_schema.json")
        self.func_templates = self._load_and_validate("tests_func_templates.json", "func_templates_schema.json")
        self.specs = self._load_and_validate("tests_specs.json", "specs_schema.json")
        print("    ✓ All schemas valid!\n")

        self.interfaces = self._load_json(os.path.join(self.helpers_headers_dir, "registry_interfaces.json"))
        self.categories = self._load_json(os.path.join(self.helpers_headers_dir, "registry_categories.json"))

        self._audit_specs()

        self.isa_definitions = self._discover_isa_definitions()

    def _load_json(self, filepath: str) -> Dict[str, Any]:
        with open(filepath, "r", encoding="utf-8") as f:
            return json.load(f)

    def _load_and_validate(self, data_filename: str, schema_filename: str) -> Dict[str, Any]:
        data_path = os.path.join(self.helpers_tests_dir, data_filename)
        schema_path = os.path.join(self.schemas_dir, schema_filename)
        
        try:
            data = self._load_json(data_path)
        except json.JSONDecodeError as e:
            print(f"  ❌ Syntax error in JSON file '{data_filename}' (line {e.lineno}, col {e.colno}): {e.msg}")
            sys.exit(1)
        except Exception as e:
            print(f"  ❌ Failed to load '{data_filename}': {e}")
            sys.exit(1)

        try:
            schema = self._load_json(schema_path)
            jsonschema.validate(instance=data, schema=schema)
            print(f"    ✓ {data_filename:<32} valid against {schema_filename}")
        except jsonschema.exceptions.ValidationError as e:
            path_str = " -> ".join(str(p) for p in e.absolute_path) or "root"
            print(f"  ❌ Schema Validation Error in '{data_filename}':")
            print(f"     Path   : {path_str}")
            print(f"     Details: {e.message}")
            sys.exit(1)
        except Exception as e:
            print(f"  ❌ Schema validation error for '{data_filename}': {e}")
            sys.exit(1)

        return data

    def _discover_isa_definitions(self) -> Dict[str, str]:
        """Auto-discover all ISAs and their mipp_definitions from generator/simd_ext/."""
        definitions = {}
        if not os.path.exists(self.simd_ext_dir):
            return definitions
        for isa_name in sorted(os.listdir(self.simd_ext_dir)):
            isa_dir = os.path.join(self.simd_ext_dir, isa_name)
            if not os.path.isdir(isa_dir):
                continue
            isa_json = os.path.join(isa_dir, f"{isa_name}_isa.json")
            if os.path.exists(isa_json):
                data = self._load_json(isa_json)
                mipp_def = data.get("mipp_definitions")
                if mipp_def and mipp_def != "MIPP_SCALAR":
                    definitions[isa_name] = mipp_def
        return definitions

    def _resolve_datatypes(self, func_name: str) -> List[str]:
        dt_spec = self.interfaces.get(func_name, {}).get("datatypes", "all_datatypes")
        if isinstance(dt_spec, str):
            if dt_spec in DATATYPES_MAP:
                return [str(d) for d in DATATYPES_MAP[dt_spec]]
            return [dt_spec]
        elif isinstance(dt_spec, list):
            res = []
            for item in dt_spec:
                if isinstance(item, str) and item in DATATYPES_MAP:
                    res.extend([str(d) for d in DATATYPES_MAP[item]])
                else:
                    res.append(str(item))
            return res
        return ["float64", "float32", "int32"]

    def get_adapter(self, dialect_name: str) -> DialectAdapter:
        if dialect_name == "cpp":
            return CppDialectAdapter()
        elif dialect_name == "c":
            return CDialectAdapter()
        elif dialect_name == "obj":
            return ObjDialectAdapter()
        else:
            raise ValueError(f"Unknown dialect adapter: {dialect_name}")

    def get_category_for_func(self, func_name: str) -> str:
        for cat_name, funcs in self.categories.items():
            if func_name in funcs:
                return cat_name
        return "miscellaneous"

    def is_func_disabled(self, func_name: str, dialect_name: str = "") -> tuple[bool, Optional[str]]:
        func_spec = self.specs["functions"].get(func_name, {})
        if dialect_name == "obj":
            support_obj = func_spec.get("support_obj", self.specs.get("default", {}).get("support_obj", False))
            if not support_obj:
                return True, f"Function '{func_name}' does not support the Object layer (support_obj: false)"
        if func_spec.get("disabled"):
            return True, func_spec.get("disabled_reason", "Disabled in specs")
        return False, None

    def _get_n_args(self, func_name: str) -> int:
        proto_map = self._get_prototype_mapping(func_name)
        components = proto_map.get("components", {})
        init_key = components.get("init", "init_uniform")
        proto_ref = proto_map.get("proto_ref", "")
        if "3args" in init_key or "3args" in proto_ref:
            return 3
        elif "1arg" in init_key or "1arg" in proto_ref:
            return 1
        return 2

    def _audit_specs(self) -> None:
        if not self.active_audits:
            return

        print("  ➔ Auditing tests_specs.json for logical consistency...")
        funcs = self.specs.get("functions", {})
        errors = []
        warnings = []

        # Coverage audit: verify every MIPP function in registry_interfaces.json is defined in tests_specs.json
        if "coverage" in self.active_audits or "all" in self.active_audits:
            missing_funcs = set(self.interfaces.keys()) - set(funcs.keys())
            if missing_funcs:
                for missing in sorted(missing_funcs):
                    errors.append(f"Function '{missing}' is defined in registry_interfaces.json but missing from tests_specs.json.")

            extra_funcs = set(funcs.keys()) - set(self.interfaces.keys())
            if extra_funcs:
                for extra in sorted(extra_funcs):
                    errors.append(f"Function '{extra}' in tests_specs.json is not defined in registry_interfaces.json.")

        def audit_domain_dict(dom_dict: Dict[str, Any], context: str):
            if not isinstance(dom_dict, dict):
                return
            if "type" in dom_dict:
                errors.append(f"{context}: 'type' key in 'domain' is obsolete and no longer supported.")

            min_v = dom_dict.get("min")
            max_v = dom_dict.get("max")
            has_range = min_v is not None or max_v is not None
            excl_zero = dom_dict.get("exclude_zero", False)

            sign_flags = [f for f in ["strictly_positive", "positive", "strictly_negative", "negative"] if dom_dict.get(f, False)]
            if len(sign_flags) > 1:
                errors.append(f"{context}: multiple domain sign flags set ({', '.join(sign_flags)}).")
            if has_range and sign_flags:
                errors.append(f"{context}: 'min'/'max' bounds cannot cohabitate with domain sign flags ({', '.join(sign_flags)}). Use either explicit bounds ('min'/'max') OR a domain flag.")

            if dom_dict.get("strictly_positive") and min_v is not None and min_v < 0:
                errors.append(f"{context}: 'strictly_positive' is true but 'min' ({min_v}) < 0.")
            if dom_dict.get("positive") and min_v is not None and min_v < 0:
                errors.append(f"{context}: 'positive' is true but 'min' ({min_v}) < 0.")
            if dom_dict.get("strictly_negative") and max_v is not None and max_v >= 0:
                errors.append(f"{context}: 'strictly_negative' is true but 'max' ({max_v}) >= 0.")
            if dom_dict.get("negative") and max_v is not None and max_v > 0:
                errors.append(f"{context}: 'negative' is true but 'max' ({max_v}) > 0.")
            if min_v is not None and max_v is not None and min_v >= max_v:
                errors.append(f"{context}: 'min' ({min_v}) >= 'max' ({max_v}).")
            if has_range and excl_zero and ((min_v is not None and min_v > 0) or (max_v is not None and max_v < 0)):
                errors.append(f"{context}: 'exclude_zero' is redundant when range bounds exclude 0.")
            if excl_zero and min_v == 0 and max_v == 0:
                errors.append(f"{context}: 'exclude_zero' is true but min=0 and max=0 (would cause infinite loop).")

        for func_name, func_spec in funcs.items():
            if isinstance(func_spec, dict):
                if "domain_src" in func_spec:
                    errors.append(f"Function '{func_name}': 'domain_src' can only be specified within a 'masks' variant block in tests_specs.json.")
                for variant_key in ("unmasked", "mask", "maskz"):
                    if isinstance(func_spec.get(variant_key), dict) and "domain_src" in func_spec[variant_key]:
                        errors.append(f"Function '{func_name}' -> '{variant_key}': 'domain_src' can only be specified within a 'masks' variant block in tests_specs.json.")
            if "consistency" in self.active_audits or "all" in self.active_audits:
                n_args = self._get_n_args(func_name)
                domain_entry_or_list = func_spec.get("input_domain", func_spec.get("domain", {}))

                if isinstance(domain_entry_or_list, list):
                    if len(domain_entry_or_list) != n_args:
                        errors.append(
                            f"Function '{func_name}': 'input_domain' array length ({len(domain_entry_or_list)}) "
                            f"does not match expected input arguments count ({n_args})."
                        )
                    for idx, item in enumerate(domain_entry_or_list):
                        if isinstance(item, dict):
                            if any(k in item for k in ["default", "by_datatype", "by_define", "by_lmul", "rules"]):
                                if "default" in item:
                                    audit_domain_dict(item["default"], f"Function '{func_name}' input_domain[{idx}].default")
                                for dt, ddict in item.get("by_datatype", {}).items():
                                    audit_domain_dict(ddict, f"Function '{func_name}' input_domain[{idx}].by_datatype.{dt}")
                                for def_k, ddict in item.get("by_define", {}).items():
                                    audit_domain_dict(ddict, f"Function '{func_name}' input_domain[{idx}].by_define.{def_k}")
                                for lmul_k, ddict in item.get("by_lmul", {}).items():
                                    audit_domain_dict(ddict, f"Function '{func_name}' input_domain[{idx}].by_lmul.{lmul_k}")
                                for r_i, rrule in enumerate(item.get("rules", [])):
                                    audit_domain_dict(rrule, f"Function '{func_name}' input_domain[{idx}].rules[{r_i}]")
                            else:
                                audit_domain_dict(item, f"Function '{func_name}' input_domain[{idx}]")
                elif isinstance(domain_entry_or_list, dict):
                    domain_entry = domain_entry_or_list
                    if any(k in domain_entry for k in ["default", "by_datatype", "by_define", "by_lmul", "rules"]):
                        if "default" in domain_entry:
                            audit_domain_dict(domain_entry["default"], f"Function '{func_name}' input_domain.default")
                        for dt, ddict in domain_entry.get("by_datatype", {}).items():
                            audit_domain_dict(ddict, f"Function '{func_name}' input_domain.by_datatype.{dt}")
                        for def_k, ddict in domain_entry.get("by_define", {}).items():
                            audit_domain_dict(ddict, f"Function '{func_name}' input_domain.by_define.{def_k}")
                        for lmul_k, ddict in domain_entry.get("by_lmul", {}).items():
                            audit_domain_dict(ddict, f"Function '{func_name}' input_domain.by_lmul.{lmul_k}")
                        for r_i, rrule in enumerate(domain_entry.get("rules", [])):
                            audit_domain_dict(rrule, f"Function '{func_name}' input_domain.rules[{r_i}]")
                    else:
                        audit_domain_dict(domain_entry, f"Function '{func_name}' input_domain")

                comp = func_spec.get("comparison")
                tol = func_spec.get("tolerance")
                if comp == "tolerance" and not tol:
                    errors.append(f"Function '{func_name}': comparison is 'tolerance' but no 'tolerance' block is specified.")
                if comp == "exact" and tol:
                    errors.append(f"Function '{func_name}': comparison is 'exact' but a 'tolerance' block is specified.")

            # Check for redundant default property overrides
            if "redundancy" in self.active_audits or "all" in self.active_audits:
                default_spec = self.specs.get("default", {})
                for key, val in func_spec.items():
                    if key in default_spec:
                        def_val = default_spec[key]
                        if val == def_val:
                            warnings.append(f"Function '{func_name}': property '{key}' = {json.dumps(val)} redundantly redefines default setting.")

        if warnings:
            print("  ⚠️  Specs Audit Warnings in 'tests_specs.json':", file=sys.stderr)
            for warn in warnings:
                print(f"     - {warn}", file=sys.stderr)
            print("", file=sys.stderr)

        if errors:
            print("  ❌ Specs Audit Errors in 'tests_specs.json':", file=sys.stderr)
            for err in errors:
                print(f"     - {err}", file=sys.stderr)
            sys.exit(1)
        print("    ✓ tests_specs.json passed logical audit!\n")

    def _extract_domain_entry(self, func_name: str) -> Any:
        func_spec = self.specs["functions"].get(func_name, {})
        domain = func_spec.get("input_domain", func_spec.get("domain"))
        if domain is None:
            domain = self.specs.get("default", {}).get("input_domain", self.specs.get("default", {}).get("domain", {}))
        return domain

    def resolve_domain_spec(self, domain_entry: Any, datatype: Optional[str] = None, lmul_suffix: Optional[str] = None, define: Optional[str] = None) -> Dict[str, Any]:
        if not isinstance(domain_entry, dict):
            return {}

        if not any(k in domain_entry for k in ["default", "by_datatype", "by_define", "by_lmul", "rules"]):
            return domain_entry

        rules = domain_entry.get("rules", [])
        for rule in rules:
            match = True
            if "datatype" in rule and datatype is not None and rule["datatype"] != datatype:
                match = False
            if "lmul" in rule and lmul_suffix is not None and str(rule["lmul"]) != str(lmul_suffix):
                match = False
            if "define" in rule and define is not None and rule["define"] != define:
                match = False
            if match and any(k in rule for k in ["min", "max", "strictly_positive", "positive", "strictly_negative", "negative", "exclude_zero"]):
                return rule

        if define and "by_define" in domain_entry and define in domain_entry["by_define"]:
            return domain_entry["by_define"][define]

        if lmul_suffix and "by_lmul" in domain_entry and lmul_suffix in domain_entry["by_lmul"]:
            return domain_entry["by_lmul"][lmul_suffix]

        if datatype and "by_datatype" in domain_entry and datatype in domain_entry["by_datatype"]:
            return domain_entry["by_datatype"][datatype]

        if "default" in domain_entry:
            return domain_entry["default"]

        return domain_entry

    def get_domain_info_for_arg(
        self,
        func_name: str,
        arg_idx: int = 0,
        datatype: Optional[str] = None,
        lmul_suffix: Optional[str] = None,
        define: Optional[str] = None,
        mkind: str = ""
    ) -> tuple[Optional[tuple[Optional[float], Optional[float]]], bool, Optional[str]]:
        func_spec = self._resolve_func_spec(func_name, mkind=mkind)
        domain_entry_or_list = func_spec.get("domain") if "domain" in func_spec and func_spec["domain"] != {} else self._extract_domain_entry(func_name)
        if isinstance(domain_entry_or_list, list):
            if arg_idx < len(domain_entry_or_list):
                domain_entry = domain_entry_or_list[arg_idx]
            else:
                domain_entry = {}
        else:
            domain_entry = domain_entry_or_list

        dom_dict = self.resolve_domain_spec(domain_entry, datatype=datatype, lmul_suffix=lmul_suffix, define=define)
        if isinstance(dom_dict, list):
            dom_dict = dom_dict[arg_idx] if arg_idx < len(dom_dict) else {}

        min_v, max_v = None, None
        exclude_zero = False
        domain_flag = None

        if "min" in dom_dict or "max" in dom_dict:
            min_v = dom_dict.get("min")
            max_v = dom_dict.get("max")
        exclude_zero = dom_dict.get("exclude_zero", False)
        for flag in ["strictly_positive", "positive", "strictly_negative", "negative"]:
            if dom_dict.get(flag, False):
                domain_flag = flag
                break

        if min_v is not None or max_v is not None:
            return (min_v, max_v), exclude_zero, domain_flag
        return None, exclude_zero, domain_flag

    def resolve_tolerance_expr(self, func_name: str, datatype: str, ref_var: str = "res") -> str:
        func_spec = self.specs["functions"].get(func_name, {})
        tol_entry = func_spec.get("tolerance")
        if not tol_entry:
            tol_entry = self.specs.get("default", {}).get("tolerance", {})
        
        if (datatype in ("", "datatype", "T")) and isinstance(tol_entry, dict) and "by_datatype" in tol_entry:
            f_expr = self.resolve_tolerance_expr(func_name, "float32", ref_var=ref_var)
            d_expr = self.resolve_tolerance_expr(func_name, "float64", ref_var=ref_var)
            f_sub = f_expr.replace("(T)", "(float)")
            d_sub = d_expr.replace("(T)", "(double)")
            return f"(std::is_same_v<T, float> ? (T)({f_sub}) : (T)({d_sub}))"

        dom_dict = tol_entry
        if isinstance(tol_entry, dict) and "by_datatype" in tol_entry:
            dom_dict = tol_entry["by_datatype"].get(datatype, tol_entry.get("default", tol_entry))
        elif isinstance(tol_entry, dict) and "default" in tol_entry:
            dom_dict = tol_entry["default"]

        if not isinstance(dom_dict, dict) or "type" not in dom_dict:
            raise ValueError(f"Function '{func_name}': comparison is 'tolerance' but tolerance spec is missing 'type' for datatype '{datatype}'.")

        tol_type = dom_dict["type"]
        if tol_type == "exact":
            return "(T)0"

        val = dom_dict.get("value")
        if val is None:
            raise ValueError(f"Function '{func_name}': tolerance spec '{tol_type}' is missing required 'value' for datatype '{datatype}'.")

        if tol_type == "relative_percent":
            return f"(T){val} * abs_diff::abs_diff({ref_var})"
        elif tol_type == "max_abs_diff":
            return f"(T){val}"
        else:
            raise ValueError(f"Function '{func_name}': unsupported tolerance type '{tol_type}'. Must be 'relative_percent', 'max_abs_diff', or 'exact'.")

    def _build_scalar_ref_assertion(self, func_name: str, dt1_raw: str, dialect_name: str, get_r3_expr: str, dt_cstd: str) -> List[str]:
        func_spec = self.specs["functions"].get(func_name, {})
        comp = func_spec.get("comparison", self.specs.get("default", {}).get("comparison", "exact"))
        t_type = dt_cstd if dialect_name != "cpp" else "T"
        is_float = dt1_raw in ("float32", "float64")

        if comp == "tolerance":
            tol_expr = self.resolve_tolerance_expr(func_name, dt1_raw, ref_var="res")
            if dialect_name == "cpp":
                return [
                    "\t(void)sres;",
                    "\tif constexpr (std::is_floating_point_v<T>) {",
                    f"\t\tT tol = {tol_expr};",
                    f"\t\tREQUIRE(abs_diff::abs_diff({get_r3_expr}, res) <= tol);",
                    "\t} else {",
                    f"\t\tREQUIRE({get_r3_expr} == res);",
                    "\t}"
                ]
            else:
                if is_float:
                    c_tol_expr = tol_expr.replace("T", t_type)
                    return [
                        "(void)sres;",
                        f"{t_type} tol = {c_tol_expr};",
                        f"REQUIRE(abs_diff::abs_diff({get_r3_expr}, res) <= tol);"
                    ]
                else:
                    return [
                        "(void)sres;",
                        f"REQUIRE({get_r3_expr} == res);"
                    ]
        else:
            return ["(void)sres;", f"REQUIRE({get_r3_expr} == res);"]

    def _build_skip_condition_lines(self, skip_spec: Any, var_name: str = "inputs1[i]") -> List[str]:
        if not skip_spec:
            return []
        if isinstance(skip_spec, dict):
            stype = skip_spec.get("type")
            if stype == "fractional_part":
                if "value" not in skip_spec or "tol" not in skip_spec:
                    raise ValueError("skip_condition of type 'fractional_part' must explicitly specify both 'value' and 'tol'.")
                val = skip_spec["value"]
                tol = skip_spec["tol"]
                return [
                    f"\t\t\tfloat frac = std::abs({var_name} - std::trunc({var_name}));",
                    f"\t\t\tif (std::abs(frac - {val}f) < {tol}f) continue;"
                ]
            else:
                raise ValueError(f"Unsupported skip_condition type '{stype}'.")
        elif isinstance(skip_spec, str):
            return [f"\t\t\tif ({skip_spec}) continue;"]
        return []

    @staticmethod
    def indent_lines(lines: List[str], level: int) -> List[str]:
        prefix = "\t" * level
        return [f"{prefix}{line}" if line.strip() else "" for line in lines]

    def _get_prototype_mapping(self, func_name: str) -> Dict[str, Any]:
        if "product_types" in self.func_templates and func_name in self.func_templates["product_types"]:
            return self.func_templates["product_types"][func_name]
        proto_ref = self.interfaces.get(func_name, {}).get("proto_ref", "ret_reg_2args_reg")
        return self.func_templates["prototypes"].get(proto_ref, self.func_templates["prototypes"]["ret_reg_2args_reg"])

    def _render_headers(self, dialect_name: str, func_name: str, N: int = 10) -> List[str]:
        lines = [
            "#include <exception>",
            "#include <algorithm>",
            "#include <numeric>",
            "#include <random>",
            "#include <cstdio>",
            "#include <cmath>",
            "#include <cstdlib>",
            "#include <cstring>",
            '#include "uniform.hpp"',
            '#include "overflow_helpers.hpp"',
            '#include "abs_diff.hpp"',
            f"#ifndef N_ITER\n#define N_ITER {N}\n#endif",
            ""
        ]

        if dialect_name == "c":
            lines.append("#include <c/common.h>")
            lines.append("#include <simd_ext/scalar/scalar_common.h>")
            lines.append(f"#include <c/functions/{func_name}.h>")
            lines.append(f"#include <simd_ext/scalar/functions/scalar_{func_name}.h>")
            lines.append("#include <c/functions/load.h>")
            lines.append("#include <c/functions/get.h>")
            lines.append("#include <c/functions/tomsk.h>")
            lines.append("#include <c/functions/set_k.h>")
            lines.append("#include <simd_ext/scalar/functions/scalar_load.h>")
            lines.append("#include <simd_ext/scalar/functions/scalar_get.h>")
            lines.append("#include <c/functions/toreg.h>")
            lines.append("#include <simd_ext/scalar/functions/scalar_toreg.h>")
            lines.append("#include <simd_ext/scalar/functions/scalar_tomsk.h>")
            lines.append("#include <simd_ext/scalar/functions/scalar_set_k.h>")
        elif dialect_name in ("cpp", "obj"):
            if dialect_name == "cpp":
                lines.append("#include <mipp.hpp>")
            else:
                lines.append("#include <mipp_obj.hpp>")
            lines.append("#include <simd_ext_cpp/scalar_cpp/scalar_cpp_common.hpp>")
            lines.append(f"#include <simd_ext_cpp/scalar_cpp/functions/scalar_cpp_{func_name}.hpp>")
            lines.append("#include <simd_ext_cpp/scalar_cpp/functions/scalar_cpp_load.hpp>")
            lines.append("#include <simd_ext_cpp/scalar_cpp/functions/scalar_cpp_get.hpp>")
            lines.append("#include <simd_ext_cpp/scalar_cpp/functions/scalar_cpp_get_k.hpp>")
            lines.append("#include <simd_ext_cpp/scalar_cpp/functions/scalar_cpp_toreg.hpp>")
            lines.append("#include <simd_ext_cpp/scalar_cpp/functions/scalar_cpp_tomsk.hpp>")
            lines.append("#include <simd_ext_cpp/scalar_cpp/functions/scalar_cpp_set_k.hpp>")

        extra_inc = self.specs.get("functions", {}).get(func_name, {}).get("extra_includes", [])
        for inc in extra_inc:
            if dialect_name == "c":
                lines.append(f"#include <c/functions/{inc}.h>")
                lines.append(f"#include <simd_ext/scalar/functions/scalar_{inc}.h>")
            elif dialect_name in ("cpp", "obj"):
                lines.append(f"#include <simd_ext_cpp/scalar_cpp/functions/scalar_cpp_{inc}.hpp>")

        lines.append("")
        lines.append("#include <catch2/catch_test_macros.hpp>")
        lines.append("#include <catch2/catch_get_random_seed.hpp>")
        lines.append("")
        return lines

    def _resolve_func_spec(self, func_name: str, mkind: str = "") -> Dict[str, Any]:
        default_spec = self.specs.get("default", {})
        func_spec = self.specs.get("functions", {}).get(func_name, {})
        
        merged = copy.deepcopy(default_spec)
        for k, v in func_spec.items():
            if k not in ("unmasked", "mask", "maskz", "masks"):
                merged[k] = copy.deepcopy(v)
                
        variant_key = mkind if mkind in ("mask", "maskz", "masks") else "unmasked"
        if variant_key in func_spec and isinstance(func_spec[variant_key], dict):
            for k, v in func_spec[variant_key].items():
                merged[k] = copy.deepcopy(v)
                
        return merged

    def _format_mask_init(self, pattern: str) -> str:
        if pattern == "alternating":
            return "(i % 2 == 0) ? -1 : 0;"
        elif pattern == "all_true":
            return "-1;"
        elif pattern == "all_false":
            return "0;"
        elif pattern == "sparse":
            return "rnd::uniform<int>(seed, 0, 9) == 0 ? -1 : 0;"
        elif pattern == "dense":
            return "rnd::uniform<int>(seed, 0, 9) != 0 ? -1 : 0;"
        else:
            return "rnd::uniform_bool(seed) ? -1 : 0;"

    def _render_single_test_func(
        self,
        dialect_name: str,
        func_name: str,
        dt_name: str = "",
        lmul_suffix: str = "m1",
        mkind: str = "",
        lmul: int = 0
    ) -> List[str]:
        adapter = self.get_adapter(dialect_name)
        func_spec = self._resolve_func_spec(func_name, mkind=mkind)
        proto_map = self._get_prototype_mapping(func_name)
        is_loop = proto_map.get("is_loop", True)

        comp_tmpl = self.component_templates
        components = proto_map.get("components", {})
        decl_key = components.get("decl", "decl_2args")
        init_key = components.get("init", "init_uniform")
        load_key = components.get("load", "load_2args_reg")
        op_key = components.get("operation", "op_binop")
        lb_key = components.get("loop_body", "lb_binop")
        as_key = components.get("loop_assert", "as_strict_eq")

        raw_func_spec = self.specs.get("functions", {}).get(func_name, {})
        variant_key = mkind if mkind in ("mask", "maskz", "masks") else "unmasked"
        has_custom_comp = "comparison" in raw_func_spec or (isinstance(raw_func_spec.get(variant_key), dict) and "comparison" in raw_func_spec[variant_key])
        if has_custom_comp:
            comp = func_spec.get("comparison")
            if comp == "tolerance":
                as_key = "as_tolerance"
            elif comp == "bitwise":
                as_key = "as_bitwise_eq"
            elif comp == "exact":
                as_key = "as_strict_eq" if is_loop else "as_scalar_val_eq"
        domain_entry = func_spec.get("domain") if "domain" in func_spec and func_spec["domain"] != {} else self._extract_domain_entry(func_name)
        dom_spec = self.resolve_domain_spec(domain_entry, datatype=dt_name, lmul_suffix=lmul_suffix)
        if isinstance(dom_spec, list):
            dom_spec = dom_spec[0] if dom_spec else {}
        for flag in ["strictly_positive", "positive", "strictly_negative", "negative"]:
            if dom_spec.get(flag) and init_key == "init_uniform_1arg":
                init_key = f"init_uniform_1arg_{flag}"
                break

        decl_raw = comp_tmpl["declarations"].get(decl_key, [])
        init_raw = comp_tmpl["initializations"].get(init_key, [])
        load_raw = comp_tmpl["loads"].get(load_key, [])
        op_raw = comp_tmpl["operations"].get(op_key, [])
        lb_raw = comp_tmpl["loop_bodies"].get(lb_key, [])
        is_product = "," in dt_name
        dt1_raw = dt_name.split(',')[0] if is_product else dt_name
        dt2_raw = dt_name.split(',')[1] if is_product else dt_name
        is_float = dt1_raw in ("float32", "float64")

        as_raw = comp_tmpl["assertions"].get(as_key, [])

        if as_key == "as_reduction_eq" and dialect_name == "c":
            if not is_float:
                as_raw = ["REQUIRE(rres == sres);"]
            else:
                tol_expr = self.resolve_tolerance_expr(func_name, dt1_raw, ref_var="sres")
                c_tol = tol_expr.replace("T", f"{dt1_raw}_t")
                as_raw = [
                    f"{dt1_raw}_t tol = {c_tol};",
                    f"{dt1_raw}_t diff = abs_diff::abs_diff(rres, sres);",
                    "if (!std::isnan(diff) && !std::isinf(diff)) REQUIRE(diff <= tol);"
                ]

        dt_cstd = f"{dt1_raw}_t" if dialect_name == "c" else (self._format_cpp_type(dt1_raw) if is_product else "T")
        tag = f"{mkind}_{lmul_suffix}" if mkind else lmul_suffix
        lmul_mult = f" * {lmul}" if lmul > 0 else (f" / {-lmul}" if lmul < 0 else "")
        dt_clean = dt_name.replace(',', '_')
        if dialect_name == "c":
            func_decl = f"static void test_mipp_c_{func_name}_{dt_clean}_{tag}()"
        elif dialect_name == "cpp":
            if is_product:
                func_decl = f"static void test_mipp_cpp_{func_name}_{dt_clean}_{tag}()"
            else:
                func_decl = f"template <typename T>\nstatic void test_mipp_cpp_{func_name}_{tag}()"
        else:
            if is_product:
                func_decl = f"static void test_mipp_cpp_obj_{func_name}_{dt_clean}_{tag}()"
            else:
                func_decl = f"template <typename T>\nstatic void test_mipp_cpp_obj_{func_name}_{tag}()"

        proto_ref = self.interfaces.get(func_name, {}).get("proto_ref", "")
        is_1arg = "1arg" in proto_ref or "2args_ptr_reg" in proto_ref or "2args_reg_val" in proto_ref
        is_3arg = "3args" in proto_ref
        size_var = f"MIPP_N_{dt1_raw.upper()}{lmul_mult}" if dialect_name == "c" else (f"mipp::N<{self._format_cpp_type(dt1_raw)}>(){lmul_mult}" if is_product else f"mipp::N<T>(){lmul_mult}")
        size_out_var = f"MIPP_N_{dt2_raw.upper()}{lmul_mult}" if dialect_name == "c" else (f"mipp::N<{self._format_cpp_type(dt2_raw)}>(){lmul_mult}" if is_product else f"mipp::N<T>(){lmul_mult}")
        mask_code = self._format_mask_init(func_spec.get("mask_pattern", "uniform_bool"))

        if mkind in ("mask", "maskz"):
            if "2args_ptr_reg" in proto_ref:
                decl_raw = [
                    "T inputs1[{{size}}], res_r[{{size}}] = {0}, res_s[{{size}}] = {0};",
                    "int32_t inputs_m[{{size}}];"
                ]
            else:
                decl_raw = [
                    "T inputs1[{{size}}];" if is_1arg else ("T inputs1[{{size}}], inputs2[{{size}}], inputs3[{{size}}];" if is_3arg else "T inputs1[{{size}}], inputs2[{{size}}];"),
                    "int32_t inputs_m[{{size}}];"
                ]
            init_raw = [
                "for (size_t i = 0; i < {{size}}; i++)",
                "{",
                "\tinputs1[i] = rnd::uniform<T>(seed);",
                "" if is_1arg else "\tinputs2[i] = rnd::uniform<T>(seed);",
                "\tinputs3[i] = rnd::uniform<T>(seed);" if is_3arg else "",
                f"\tinputs_m[i] = {mask_code}",
                "}"
            ]
            init_raw = [line for line in init_raw if line != ""]
            if load_key == "load_empty":
                load_raw = [
                    "{{msk_type}} m1 = {{set_k_call}};",
                    "{{scalar_msk_type}} sm1 = {{scalar_set_k_call}};"
                ]
            else:
                load_raw = [
                    "{{reg_type}} r1 = {{load_call1}};",
                    "" if is_1arg else "{{reg_type}} r2 = {{load_call2}};",
                    "{{reg_type}} r3 = {{load_call3}};" if is_3arg else "",
                    "{{scalar_reg_type}} s1 = {{scalar_load_call1}};",
                    "" if is_1arg else "{{scalar_reg_type}} s2 = {{scalar_load_call2}};",
                    "{{scalar_reg_type}} s3 = {{scalar_load_call3}};" if is_3arg else "",
                    "{{msk_type}} m1 = {{set_k_call}};",
                    "{{scalar_msk_type}} sm1 = {{scalar_set_k_call}};"
                ]
            load_raw = [line for line in load_raw if line != ""]
            if "1arg_ptr" in proto_ref:
                op_args_reg = "m1, inputs1"
                op_args_scal = "sm1, inputs1"
            elif "2args_ptr_reg" in proto_ref:
                op_args_reg = "m1, res_r, r1"
                op_args_scal = "sm1, res_s, s1"
            elif "2args_reg_val" in proto_ref:
                op_args_reg = "m1, r1, 2"
                op_args_scal = "sm1, s1, 2"
            elif is_1arg:
                op_args_reg = "m1, r1"
                op_args_scal = "sm1, s1"
            elif is_3arg:
                op_args_reg = "m1, r1, r2, r3"
                op_args_scal = "sm1, s1, s2, s3"
            else:
                op_args_reg = "m1, r1, r2"
                op_args_scal = "sm1, s1, s2"
        elif mkind == "masks":
            if "2args_ptr_reg" in proto_ref:
                decl_raw = [
                    "T inputs1[{{size}}], res_r[{{size}}] = {0}, res_s[{{size}}] = {0};",
                    "int32_t inputs_m[{{size}}];"
                ]
            else:
                decl_raw = [
                    "T inputs1[{{size}}], inputs_src[{{size}}];" if is_1arg else ("T inputs1[{{size}}], inputs2[{{size}}], inputs3[{{size}}], inputs_src[{{size}}];" if is_3arg else "T inputs1[{{size}}], inputs2[{{size}}], inputs_src[{{size}}];"),
                    "int32_t inputs_m[{{size}}];"
                ]
            init_raw = [
                "for (size_t i = 0; i < {{size}}; i++)",
                "{",
                "\tinputs1[i] = rnd::uniform<T>(seed);",
                "" if is_1arg else "\tinputs2[i] = rnd::uniform<T>(seed);",
                "\tinputs3[i] = rnd::uniform<T>(seed);" if is_3arg else "",
                "\tinputs_src[i] = rnd::uniform<T>(seed);",
                f"\tinputs_m[i] = {mask_code}",
                "}",
            ]
            init_raw = [line for line in init_raw if line != ""]
            if load_key == "load_empty":
                load_raw = [
                    "{{reg_type}} rsrc = {{load_call_src}};",
                    "{{scalar_reg_type}} ssrc = {{scalar_load_call_src}};",
                    "{{msk_type}} m1 = {{set_k_call}};",
                    "{{scalar_msk_type}} sm1 = {{scalar_set_k_call}};"
                ]
            else:
                load_raw = [
                    "{{reg_type}} r1 = {{load_call1}};",
                    "" if is_1arg else "{{reg_type}} r2 = {{load_call2}};",
                    "{{reg_type}} r3 = {{load_call3}};" if is_3arg else "",
                    "{{reg_type}} rsrc = {{load_call_src}};",
                    "{{scalar_reg_type}} s1 = {{scalar_load_call1}};",
                    "" if is_1arg else "{{scalar_reg_type}} s2 = {{scalar_load_call2}};",
                    "{{scalar_reg_type}} s3 = {{scalar_load_call3}};" if is_3arg else "",
                    "{{scalar_reg_type}} ssrc = {{scalar_load_call_src}};",
                    "{{msk_type}} m1 = {{set_k_call}};",
                    "{{scalar_msk_type}} sm1 = {{scalar_set_k_call}};"
                ]
            load_raw = [line for line in load_raw if line != ""]
            if "1arg_ptr" in proto_ref:
                op_args_reg = "m1, rsrc, inputs1"
                op_args_scal = "sm1, ssrc, inputs1"
            elif "2args_ptr_reg" in proto_ref:
                op_args_reg = "m1, res_r, r1"
                op_args_scal = "sm1, res_s, s1"
            elif "2args_reg_val" in proto_ref:
                if mkind == "masks":
                    op_args_reg = "m1, rsrc, r1, 2"
                    op_args_scal = "sm1, ssrc, s1, 2"
                else:
                    op_args_reg = "m1, r1, 2"
                    op_args_scal = "sm1, s1, 2"
            elif is_1arg:
                if mkind == "masks":
                    op_args_reg = "m1, rsrc, r1"
                    op_args_scal = "sm1, ssrc, s1"
                else:
                    op_args_reg = "m1, r1"
                    op_args_scal = "sm1, s1"
            elif is_3arg:
                op_args_reg = "m1, rsrc, r1, r2, r3"
                op_args_scal = "sm1, ssrc, s1, s2, s3"
            else:
                op_args_reg = "m1, rsrc, r1, r2"
                op_args_scal = "sm1, ssrc, s1, s2"
        else:
            if "0arg" in proto_ref:
                op_args_reg = ""
                op_args_scal = ""
            elif "1arg_val" in proto_ref:
                op_args_reg = "inputs1[0]"
                op_args_scal = "inputs1[0]"
            elif "1arg_i32" in proto_ref:
                op_args_reg = "inputs_m[0]"
                op_args_scal = "inputs_m[0]"
            elif "1arg_Nele" in proto_ref:
                op_args_reg = "inputs1" if "ret_reg" in proto_ref else "inputs_m"
                op_args_scal = "inputs1" if "ret_reg" in proto_ref else "inputs_m"
            elif "2reg_1msk" in proto_ref:
                op_args_reg = "r1, r2, m3"
                op_args_scal = "s1, s2, sm3"
            elif "2args_msk" in proto_ref:
                op_args_reg = "m1, m2"
                op_args_scal = "sm1, sm2"
            elif "1arg_msk" in proto_ref:
                op_args_reg = "m1"
                op_args_scal = "sm1"
            elif "1arg_reg" in proto_ref and "ret_msk" in proto_ref:
                op_args_reg = "r1"
                op_args_scal = "s1"
            elif "2args_reg_val" in proto_ref or "2args_msk_val" in proto_ref:
                op_args_reg = "r1, 2" if "2args_reg" in proto_ref else "m1, 2"
                op_args_scal = "s1, 2" if "2args_reg" in proto_ref else "sm1, 2"
            elif "1arg_ptr" in proto_ref:
                op_args_reg = "inputs1"
                op_args_scal = "inputs1"
            elif "2args_ptr_reg" in proto_ref:
                op_args_reg = "res_r, r1"
                op_args_scal = "res_s, s1"
            elif is_1arg:
                op_args_reg = "r1"
                op_args_scal = "s1"
            elif "3args" in proto_ref:
                op_args_reg = "r1, r2, r3"
                op_args_scal = "s1, s2, s3"
            else:
                op_args_reg = "r1, r2"
                op_args_scal = "s1, s2"

        n_args = self._get_n_args(func_name)
        for arg_i in range(1, n_args + 1):
            arg_domain_range, arg_excl_zero, arg_domain_flag = self.get_domain_info_for_arg(
                func_name, arg_idx=arg_i - 1, datatype=dt_name, lmul_suffix=lmul_suffix, mkind=mkind
            )
            target_pattern = f"inputs{arg_i}[i] = rnd::uniform<T>(seed)"
            min_v, max_v = arg_domain_range if arg_domain_range else (None, None)
            has_explicit_bounds = min_v is not None or max_v is not None

            if has_explicit_bounds:
                min_str = f"(T){min_v}" if min_v is not None else "std::numeric_limits<T>::lowest()"
                max_str = f"(T){max_v}" if max_v is not None else "std::numeric_limits<T>::max()"
                if arg_excl_zero:
                    repl = f"inputs{arg_i}[i] = rnd::uniform_exclude_zero<T>(seed, {min_str}, {max_str})"
                else:
                    repl = f"inputs{arg_i}[i] = rnd::uniform<T>(seed, {min_str}, {max_str})"
            else:
                if arg_excl_zero:
                    repl = f"inputs{arg_i}[i] = rnd::uniform_exclude_zero<T>(seed)"
                elif arg_domain_flag:
                    repl = f"inputs{arg_i}[i] = rnd::uniform_{arg_domain_flag}<T>(seed)"
                else:
                    repl = f"inputs{arg_i}[i] = rnd::uniform<T>(seed)"

            init_raw = [line.replace(target_pattern, repl) for line in init_raw]

        if mkind == "masks":
            target_pattern = "inputs_src[i] = rnd::uniform<T>(seed)"
            if "domain_src" in func_spec and func_spec["domain_src"]:
                dom_dict = self.resolve_domain_spec(func_spec["domain_src"], datatype=dt_name, lmul_suffix=lmul_suffix)
                min_v = dom_dict.get("min")
                max_v = dom_dict.get("max")
                arg_excl_zero = dom_dict.get("exclude_zero", False)
                arg_domain_flag = None
                for flag in ["strictly_positive", "positive", "strictly_negative", "negative"]:
                    if dom_dict.get(flag, False):
                        arg_domain_flag = flag
                        break
            else:
                arg_domain_range, arg_excl_zero, arg_domain_flag = self.get_domain_info_for_arg(
                    func_name, arg_idx=0, datatype=dt_name, lmul_suffix=lmul_suffix, mkind=mkind
                )
                min_v, max_v = arg_domain_range if arg_domain_range else (None, None)

            if min_v is not None or max_v is not None:
                min_str = f"(T){min_v}" if min_v is not None else "std::numeric_limits<T>::lowest()"
                max_str = f"(T){max_v}" if max_v is not None else "std::numeric_limits<T>::max()"
                if arg_excl_zero:
                    repl = f"inputs_src[i] = rnd::uniform_exclude_zero<T>(seed, {min_str}, {max_str})"
                else:
                    repl = f"inputs_src[i] = rnd::uniform<T>(seed, {min_str}, {max_str})"
                init_raw = [line.replace(target_pattern, repl) for line in init_raw]
            elif arg_excl_zero:
                repl = f"inputs_src[i] = rnd::uniform_exclude_zero<T>(seed)"
                init_raw = [line.replace(target_pattern, repl) for line in init_raw]
            elif arg_domain_flag:
                repl = f"inputs_src[i] = rnd::uniform_{arg_domain_flag}<T>(seed)"
                init_raw = [line.replace(target_pattern, repl) for line in init_raw]

        nan_inf_skip = func_spec.get("nan_inf_skip", self.specs.get("default", {}).get("nan_inf_skip", False))

        def replace_vars(lines: List[str]) -> List[str]:
            out = []
            if is_product:
                dt1_str = dt_name.split(',')[0]
                dt2_str = dt_name.split(',')[1]
                dt_clean = dt_name.replace(',', '_')
            else:
                dt1_str = dt2_str = dt_clean = dt_name if dt_name else "T"

            for line in lines:
                l = line
                l = l.replace("{{func_decl}}", func_decl)
                l = l.replace("{{size_out}}", size_out_var)
                l = l.replace("{{size}}", size_var)
                l = l.replace("{{func}}", func_name)
                l = l.replace("{{reg_type}}", adapter.format_reg_type(dt1_str, lmul_suffix))
                l = l.replace("{{scalar_reg_type}}", adapter.format_scalar_reg_type(dt1_str, lmul_suffix))
                l = l.replace("{{msk_type}}", adapter.format_msk_type(dt1_str, lmul_suffix))
                l = l.replace("{{scalar_msk_type}}", adapter.format_scalar_msk_type(dt1_str, lmul_suffix))
                l = l.replace("{{reg_type_dst}}", adapter.format_reg_type(dt2_str, lmul_suffix))
                l = l.replace("{{scalar_reg_type_dst}}", adapter.format_scalar_reg_type(dt2_str, lmul_suffix))
                l = l.replace("{{msk_type_dst}}", adapter.format_msk_type(dt2_str, lmul_suffix))
                l = l.replace("{{scalar_msk_type_dst}}", adapter.format_scalar_msk_type(dt2_str, lmul_suffix))
                l = l.replace("{{load_call1}}", adapter.format_load(dt1_str, "inputs1", lmul_suffix))
                l = l.replace("{{load_call2}}", adapter.format_load(dt1_str, "inputs2", lmul_suffix))
                l = l.replace("{{load_call3}}", adapter.format_load(dt1_str, "inputs3", lmul_suffix))
                l = l.replace("{{load_call_src}}", adapter.format_load(dt1_str, "inputs_src", lmul_suffix))
                l = l.replace("{{scalar_load_call1}}", adapter.format_scalar_load(dt1_str, "inputs1", lmul_suffix))
                l = l.replace("{{scalar_load_call2}}", adapter.format_scalar_load(dt1_str, "inputs2", lmul_suffix))
                l = l.replace("{{scalar_load_call3}}", adapter.format_scalar_load(dt1_str, "inputs3", lmul_suffix))
                l = l.replace("{{scalar_load_call_src}}", adapter.format_scalar_load(dt1_str, "inputs_src", lmul_suffix))
                msk_dt = dt1_str
                msk_type_str = adapter.format_msk_type(msk_dt, lmul_suffix)
                scalar_msk_type_str = adapter.format_scalar_msk_type(msk_dt, lmul_suffix)
                l = l.replace("{{msk_type}}", msk_type_str)
                l = l.replace("{{scalar_msk_type}}", scalar_msk_type_str)
                l = l.replace("{{set_k_call1}}", adapter.format_set_k(msk_dt, "inputs_m1", lmul_suffix))
                l = l.replace("{{set_k_call2}}", adapter.format_set_k(msk_dt, "inputs_m2", lmul_suffix))
                l = l.replace("{{set_k_call3}}", adapter.format_set_k(msk_dt, "inputs_m3", lmul_suffix))
                l = l.replace("{{scalar_set_k_call1}}", adapter.format_scalar_set_k(msk_dt, "inputs_m1", lmul_suffix))
                l = l.replace("{{scalar_set_k_call2}}", adapter.format_scalar_set_k(msk_dt, "inputs_m2", lmul_suffix))
                l = l.replace("{{scalar_set_k_call3}}", adapter.format_scalar_set_k(msk_dt, "inputs_m3", lmul_suffix))
                l = l.replace("{{set_k_call}}", adapter.format_set_k(msk_dt, "inputs_m", lmul_suffix))
                l = l.replace("{{scalar_set_k_call}}", adapter.format_scalar_set_k(msk_dt, "inputs_m", lmul_suffix))
                l = l.replace("{{tomsk_call1}}", adapter.format_tomsk(dt1_str, "r1", lmul_suffix))
                l = l.replace("{{tomsk_call2}}", adapter.format_tomsk(dt1_str, "r2", lmul_suffix))
                l = l.replace("{{scalar_tomsk_call1}}", adapter.format_scalar_tomsk(dt1_str, "s1", lmul_suffix))
                l = l.replace("{{scalar_tomsk_call2}}", adapter.format_scalar_tomsk(dt1_str, "s2", lmul_suffix))
                l = l.replace("{{op_call}}", adapter.format_func_call(func_name, dt_clean, op_args_reg, lmul_suffix, mkind=mkind))
                l = l.replace("{{scalar_op_call}}", adapter.format_scalar_func_call(func_name, dt_clean, op_args_scal, lmul_suffix, mkind=mkind))
                l = l.replace("{{get_func}}(r3, i)", adapter.format_get("rres", "i", dt2_str, lmul_suffix))
                l = l.replace("{{get_scalar_func}}(s3, i)", adapter.format_scalar_get("s3", "i", dt2_str, lmul_suffix))
                l = l.replace("{{get_func}}(r4, i)", adapter.format_get("r4", "i", dt2_str, lmul_suffix))
                l = l.replace("{{get_scalar_func}}(s4, i)", adapter.format_scalar_get("s4", "i", dt2_str, lmul_suffix))
                l = l.replace("{{get_k_func}}(r3, i)", adapter.format_get_k("rres", "i", dt2_str, lmul_suffix))
                l = l.replace("{{get_scalar_k_func}}(s3, i)", adapter.format_scalar_get_k("s3", "i", dt2_str, lmul_suffix))
                l = l.replace("{{get_func}}", adapter.format_get_func_name(dt2_str, lmul_suffix))
                l = l.replace("{{get_scalar_func}}", adapter.format_scalar_get_func_name(dt2_str, lmul_suffix))
                l = l.replace("{{get_k_func}}", adapter.format_get_k_func_name(dt2_str, lmul_suffix))
                l = l.replace("{{get_scalar_k_func}}", adapter.format_scalar_get_k_func_name(dt2_str, lmul_suffix))
                l = re.sub(r'\bT\b', dt_cstd, l)
                if "{{tol_decl}}" in l:
                    tol_expr = self.resolve_tolerance_expr(func_name, dt2_str if is_product else dt1_raw, ref_var="res2")
                    tol_expr_typed = tol_expr.replace("T", "decltype(res2)")
                    l = l.replace("{{tol_decl}}", f"auto tol = {tol_expr_typed};")
                if "{{tol_decl_s3}}" in l:
                    tol_expr = self.resolve_tolerance_expr(func_name, dt1_raw, ref_var="sres")
                    l = l.replace("{{tol_decl_s3}}", f"T tol = {tol_expr};")
                if "{{nan_inf_skip_lines}}" in l:
                    if nan_inf_skip:
                        out.extend([
                            "if (std::isinf(tol) || std::isnan(tol)) continue;",
                            "if (std::isnan(diff) || std::isnan(res2) || std::isnan(res1)) continue;",
                            "if (std::isinf(diff) || std::isinf(res2) || std::isinf(res1)) continue;"
                        ])
                    continue
                if dialect_name == "obj":
                    s_stripped = l.strip()
                    if s_stripped.endswith("= ;") or s_stripped == ";" or " s1 =" in l or " s2 =" in l or " s3 =" in l or " sm1 =" in l or " sm2 =" in l:
                        continue
                out.append(l)
            return out

        decl_lines = replace_vars(decl_raw)
        init_lines = replace_vars(init_raw)
        load_lines = replace_vars(load_raw)
        op_lines = replace_vars(op_raw)
        lb_lines = replace_vars(lb_raw)
        as_lines = replace_vars(as_raw)

        if dialect_name == "obj":
            op_syms = getattr(adapter, "op_syms", {})
            cmp_syms = getattr(adapter, "cmp_syms", {})
            get_r3_expr = adapter.format_get("rres", "i", dt1_raw, lmul_suffix)
            get_r3_k_expr = adapter.format_get_k("rres", "i", dt1_raw, lmul_suffix)
            if func_name in cmp_syms:
                sym = cmp_syms[func_name]
                lb_lines = [f"\tbool res = inputs1[i] {sym} inputs2[i];"]
                as_lines = [f"\tREQUIRE((!!{get_r3_k_expr}) == res);"]
            elif func_name in ("add", "sub", "mul", "div"):
                sym = op_syms[func_name]
                lb_lines = [f"\t{dt_cstd} res = inputs1[i] {sym} inputs2[i];"]
                as_lines = [f"\tREQUIRE({get_r3_expr} == res);"]
            elif func_name in ("andb", "orb", "xorb"):
                sym = op_syms[func_name]
                lb_lines = [
                    f"\t{dt_cstd} res;",
                    f"\tif constexpr (std::is_floating_point_v<{dt_cstd}>) {{",
                    f"\t\tif constexpr (sizeof({dt_cstd}) == 8) {{ uint64_t u1, u2; memcpy(&u1, &inputs1[i], 8); memcpy(&u2, &inputs2[i], 8); uint64_t ures = u1 {sym} u2; memcpy(&res, &ures, 8); }}",
                    f"\t\telse {{ uint32_t u1, u2; memcpy(&u1, &inputs1[i], 4); memcpy(&u2, &inputs2[i], 4); uint32_t ures = u1 {sym} u2; memcpy(&res, &ures, 4); }}",
                    "\t} else {",
                    f"\t\tres = inputs1[i] {sym} inputs2[i];",
                    "\t}"
                ]
                as_lines = [f"\tREQUIRE({get_r3_expr} == res);"]
            elif func_name in ("andb_k", "orb_k", "xorb_k"):
                op_syms_k = {"andb_k": "&", "orb_k": "|", "xorb_k": "^"}
                sym = op_syms_k[func_name]
                lb_lines = [f"\tbool res = (!!inputs_m1[i]) {sym} (!!inputs_m2[i]);"]
                as_lines = [f"\tREQUIRE((!!{get_r3_k_expr}) == res);"]
            elif func_name == "andnb_k":
                lb_lines = ["\tbool res = (!inputs_m1[i]) & (!!inputs_m2[i]);"]
                as_lines = [f"\tREQUIRE((!!{get_r3_k_expr}) == res);"]
            elif func_name == "notb_k":
                lb_lines = ["\tbool res = !inputs_m[i];"]
                as_lines = [f"\tREQUIRE((!!{get_r3_k_expr}) == res);"]
            elif func_name == "notb":
                lb_lines = [
                    f"\t{dt_cstd} res;",
                    f"\tif constexpr (std::is_floating_point_v<{dt_cstd}>) {{",
                    f"\t\tif constexpr (sizeof({dt_cstd}) == 8) {{ uint64_t u1; memcpy(&u1, &inputs1[i], 8); uint64_t ures = ~u1; memcpy(&res, &ures, 8); }}",
                    f"\t\telse {{ uint32_t u1; memcpy(&u1, &inputs1[i], 4); uint32_t ures = ~u1; memcpy(&res, &ures, 4); }}",
                    "\t} else {",
                    f"\t\tres = ~inputs1[i];",
                    "\t}"
                ]
                as_lines = [f"\tREQUIRE({get_r3_expr} == res);"]


        body_lines = []
        body_lines.append(func_decl)
        body_lines.append("{")
        body_lines.append("\tstd::mt19937 seed(Catch::getSeed());")
        body_lines.append("\tfor (unsigned n = 0; n < get_n_iter(); n++)")
        body_lines.append("\t{")

        body_lines.extend(self.indent_lines(decl_lines, 2))
        body_lines.append("")
        body_lines.extend(self.indent_lines(init_lines, 2))
        body_lines.append("")
        body_lines.extend(self.indent_lines(load_lines, 2))
        body_lines.append("")
        body_lines.extend(self.indent_lines(op_lines, 2))
        body_lines.append("")

        overflow_check = func_spec.get("overflow_check")

        if is_loop:
            body_lines.append(f"\t\tfor (unsigned i = 0; i < {size_out_var}; i++)")
            body_lines.append("\t\t{")
            if overflow_check in ("add", "sub", "mul"):
                get_fn = adapter.format_get_func_name(dt_name, lmul_suffix)
                if dialect_name == "c":
                    val1_expr = f"{get_fn}(r1, i)"
                    val2_expr = f"{get_fn}(r2, i)"
                elif dialect_name == "obj":
                    val1_expr = "r1[i]"
                    val2_expr = "r2[i]"
                else:
                    val1_expr = "mipp::get(r1, i)"
                    val2_expr = "mipp::get(r2, i)"
                body_lines.append(f"\t\t\tbool ov = ovf::will_{overflow_check}_overflow<{dt_cstd}>({val1_expr}, {val2_expr});")
                body_lines.append("\t\t\tif (ov)")
                body_lines.append("\t\t\t{")
                body_lines.append('\t\t\t\tINFO("Overflow occurred, skipping assert");')
                body_lines.append("\t\t\t}")
                body_lines.append("\t\t\telse")
                body_lines.append("\t\t\t{")
                if lb_lines:
                    body_lines.extend(self.indent_lines(lb_lines, 4))
                if as_lines:
                    body_lines.extend(self.indent_lines(as_lines, 4))
                body_lines.append("\t\t\t}")
            else:
                skip_condition = func_spec.get("skip_condition")
                skip_lines = self._build_skip_condition_lines(skip_condition)
                if skip_lines:
                    body_lines.extend(skip_lines)
                if lb_lines:
                    body_lines.extend(self.indent_lines(lb_lines, 3))
                if as_lines:
                    body_lines.extend(self.indent_lines(as_lines, 3))
            body_lines.append("\t\t}")
        else:
            if overflow_check in ("accumulate_add", "accumulate_mul"):
                if overflow_check == "accumulate_add":
                    mask_ptr = "inputs_m" if mkind in ("mask", "maskz", "masks") else "nullptr"
                    is_maskz_bool = "true" if mkind == "maskz" else "false"
                    inputs_src_ptr = "inputs_src" if mkind == "masks" else "nullptr"
                    body_lines.append(f"\t\tbool ov = ovf::will_reduction_add_overflow<{dt_cstd}>(inputs1, {size_var}, {mask_ptr}, {is_maskz_bool}, {inputs_src_ptr});")
                else:
                    op_symbol = "*"
                    val_0 = "inputs1[0]"
                    val_i = "inputs1[i]"
                    if mkind == "maskz":
                        val_0 = f"(inputs_m[0] ? inputs1[0] : ({dt_cstd})0)"
                        val_i = f"(inputs_m[i] ? inputs1[i] : ({dt_cstd})0)"
                    elif mkind == "masks":
                        val_0 = f"(inputs_m[0] ? inputs1[0] : inputs_src[0])"
                        val_i = f"(inputs_m[i] ? inputs1[i] : inputs_src[i])"
                    body_lines.append("\t\tbool ov = false;")
                    body_lines.append("\t\t{")
                    body_lines.append(f"\t\t\t{dt_cstd} acc = {val_0};")
                    body_lines.append(f"\t\t\tfor (size_t i = 1; i < {size_var}; i++)")
                    body_lines.append("\t\t\t{")
                    body_lines.append(f"\t\t\t\t{dt_cstd} v = {val_i};")
                    body_lines.append(f"\t\t\t\tif (ovf::will_mul_overflow<{dt_cstd}>(acc, v)) {{ ov = true; break; }}")
                    body_lines.append(f"\t\t\t\tacc = acc * v;")
                    body_lines.append("\t\t\t}")
                    body_lines.append("\t\t}")
                body_lines.append("\t\tif (ov)")
                body_lines.append("\t\t{")
                body_lines.append('\t\t\tINFO("Reduction overflow occurred, skipping assert");')
                body_lines.append("\t\t}")
                body_lines.append("\t\telse")
                body_lines.append("\t\t{")
                if lb_lines:
                    body_lines.extend(self.indent_lines(lb_lines, 3))
                if as_lines:
                    body_lines.extend(self.indent_lines(as_lines, 3))
                body_lines.append("\t\t}")
            else:
                if lb_lines:
                    body_lines.extend(self.indent_lines(lb_lines, 2))
                if as_lines:
                    body_lines.extend(self.indent_lines(as_lines, 2))

        body_lines.append("\t}")
        body_lines.append("}")
        body_lines.append("")

        return body_lines

    @staticmethod
    def _format_cpp_type(dt_str: str) -> str:
        parts = dt_str.split(",")
        converted = []
        for p in parts:
            p = p.strip()
            if p == "float64":
                converted.append("double")
            elif p == "float32":
                converted.append("float")
            elif p.endswith("_t"):
                converted.append(p)
            else:
                converted.append(f"{p}_t")
        return ", ".join(converted)

    def _render_test_case_section(self, dialect_name: str, func_name: str, lmul_suffix: str = "m1", mkind: str = "", lmul: int = 0) -> List[str]:
        lines = []
        mkind_str = f" {mkind}" if mkind else ""
        lines.append(f'TEST_CASE("{func_name} - {dialect_name} lmul_opt={lmul} ({lmul_suffix}){mkind_str}", "[{func_name}]")')
        lines.append("{")

        datatypes = self._resolve_datatypes(func_name)
        is_product = any("," in str(dt) for dt in datatypes)

        tag = f"{mkind}_{lmul_suffix}" if mkind else lmul_suffix
        for dt in datatypes:
            dt_clean = str(dt).replace(",", "_")
            if dialect_name == "c":
                call_expr = f"test_mipp_c_{func_name}_{dt_clean}_{tag}();"
            elif dialect_name == "cpp":
                if is_product:
                    call_expr = f"test_mipp_cpp_{func_name}_{dt_clean}_{tag}();"
                else:
                    cpp_type = self._format_cpp_type(dt)
                    call_expr = f"test_mipp_cpp_{func_name}_{tag}<{cpp_type}>();"
            else:
                if is_product:
                    call_expr = f"test_mipp_cpp_obj_{func_name}_{dt_clean}_{tag}();"
                else:
                    cpp_type = self._format_cpp_type(dt)
                    call_expr = f"test_mipp_cpp_obj_{func_name}_{tag}<{cpp_type}>();"

            lines.append(f'\tSECTION("datatype = {dt}")')
            lines.append('\t{')
            lines.append('\t\ttry {')
            lines.append(f'\t\t\t{call_expr}')
            lines.append('\t\t} catch (const mipp::stub_exception& e) {')
            lines.append('\t\t\tWARN(e.what());')
            lines.append('\t\t}')
            lines.append('\t}')

        lines.append("}")
        lines.append("")
        return lines

    def _is_mask_kind_supported(self, ms_val: Any, mkind: str) -> bool:
        if mkind in ("", "unmasked"):
            return True
        if hasattr(ms_val, "is_supported"):
            return ms_val.is_supported(mkind)
        ms_str = str(ms_val)
        if ms_str in ("all_mask", "all"):
            return True
        if ms_str in ("no_mask", "none"):
            return False
        if mkind == "mask" and ("mask_and" in ms_str or ms_str in ("mask_only", "mask")):
            return True
        if mkind == "maskz" and ("maskz" in ms_str):
            return True
        if mkind == "masks" and ("masks" in ms_str):
            return True
        return False

    def _format_rnd_call(self, dom_dict: Dict[str, Any], var_name: str) -> str:
        min_v = dom_dict.get("min")
        max_v = dom_dict.get("max")
        arg_excl_zero = dom_dict.get("exclude_zero", False)
        arg_domain_flag = None
        for flag in ["strictly_positive", "positive", "strictly_negative", "negative"]:
            if dom_dict.get(flag, False):
                arg_domain_flag = flag
                break

        if min_v is not None or max_v is not None:
            min_str = f"(T){min_v}" if min_v is not None else "std::numeric_limits<T>::lowest()"
            max_str = f"(T){max_v}" if max_v is not None else "std::numeric_limits<T>::max()"
            if arg_excl_zero:
                return f"{var_name}[i] = rnd::uniform_exclude_zero<T>(seed, {min_str}, {max_str});"
            else:
                return f"{var_name}[i] = rnd::uniform<T>(seed, {min_str}, {max_str});"
        elif arg_excl_zero:
            return f"{var_name}[i] = rnd::uniform_exclude_zero<T>(seed);"
        elif arg_domain_flag:
            return f"{var_name}[i] = rnd::uniform_{arg_domain_flag}<T>(seed);"
        else:
            return f"{var_name}[i] = rnd::uniform<T>(seed);"


    def render_cpp_validation_block(self, func_name: str, proto_ref: str, is_product: bool = False, r_var: str = "rres", s_var: str = "sres", dialect_name: str = "cpp") -> List[str]:
        func_spec = self.specs["functions"].get(func_name, {})
        default_spec = self.specs.get("default", {})
        comp_type = func_spec.get("comparison", default_spec.get("comparison", "exact"))
        has_tolerance = (comp_type == "tolerance") or ("tolerance" in func_spec)
        is_loop = self.func_templates.get("prototypes", {}).get(proto_ref, {}).get("is_loop", True)

        r_get = f"{r_var}[i]" if dialect_name == "obj" else f"mipp::get({r_var}, i)"
        s_get = f"mipp::get({s_var}, i)"

        overflow_check = func_spec.get("overflow_check")

        lines = []
        if not is_loop and overflow_check in ("accumulate_add", "accumulate_mul"):
            lines.append("bool ov = false;")
            lines.append("{")
            lines.append("\tif constexpr (!std::is_floating_point_v<T>)")
            lines.append("\t{")
            if overflow_check == "accumulate_add":
                lines.append("\t\tconst int32_t* m_ptr = nullptr;")
                lines.append("\t\tbool is_z = (MK == mipp::Z);")
                lines.append("\t\tif constexpr (MK == mipp::Z || MK == mipp::M || MK == mipp::S) m_ptr = inputs_m;")
                lines.append("\t\tov = ovf::will_reduction_add_overflow<T>(inputs1, size, m_ptr, is_z);")
            else:
                lines.append("\t\tauto get_val = [&](size_t idx) -> T {")
                lines.append("\t\t\tif constexpr (MK == mipp::Z) return inputs_m[idx] ? inputs1[idx] : static_cast<T>(0);")
                lines.append("\t\t\telse return inputs1[idx];")
                lines.append("\t\t};")
                lines.append("\t\tT acc = get_val(0);")
                lines.append("\t\tfor (size_t i = 1; i < size; i++)")
                lines.append("\t\t{")
                lines.append("\t\t\tT v = get_val(i);")
                lines.append("\t\t\tif (ovf::will_mul_overflow<T>(acc, v)) { ov = true; break; }")
                lines.append("\t\t\tacc = acc * v;")
                lines.append("\t\t}")
            lines.append("\t}")
            lines.append("}")
            lines.append("if (ov)")
            lines.append("{")
            lines.append('\tINFO("Reduction overflow occurred, skipping assert");')
            lines.append("}")
            lines.append("else")
            lines.append("{")
            if has_tolerance:
                tol_expr = self.resolve_tolerance_expr(func_name, "T", ref_var=s_var)
                lines.append("\tif constexpr (std::is_floating_point_v<T>)")
                lines.append("\t{")
                lines.append(f"\t\tT tol = {tol_expr};")
                lines.append(f"\t\tT diff = abs_diff::abs_diff({r_var}, {s_var});")
                lines.append("\t\tif (!std::isnan(diff) && !std::isinf(diff)) REQUIRE(diff <= tol);")
                lines.append("\t}")
                lines.append("\telse")
                lines.append("\t{")
                lines.append(f"\t\tREQUIRE({r_var} == {s_var});")
                lines.append("\t}")
            else:
                lines.append(f"\tREQUIRE({r_var} == {s_var});")
            lines.append("}")
            return lines

        if has_tolerance and is_loop:
            tol_expr = self.resolve_tolerance_expr(func_name, "T", ref_var=s_get)
            lines.append("for (size_t i = 0; i < size; i++)")
            lines.append("{")
            lines.append("\tif constexpr (std::is_floating_point_v<T>)")
            lines.append("\t{")
            lines.append(f"\t\tT tol = {tol_expr};")
            lines.append(f"\t\tT diff = abs_diff::abs_diff({r_get}, {s_get});")
            lines.append("\t\tif (!std::isnan(diff) && !std::isinf(diff)) REQUIRE(diff <= tol);")
            lines.append("\t}")
            lines.append("\telse")
            lines.append("\t{")
            if overflow_check in ("add", "sub", "mul"):
                lines.append(f"\t\tbool ov = ovf::will_{overflow_check}_overflow<T>(inputs1[i], inputs2[i]);")
                lines.append("\t\tif (ov)")
                lines.append("\t\t{")
                lines.append('\t\t\tINFO("Overflow occurred, skipping assert");')
                lines.append("\t\t}")
                lines.append("\t\telse")
                lines.append("\t\t{")
                lines.append(f"\t\t\tREQUIRE({r_get} == {s_get});")
                lines.append("\t\t}")
            else:
                lines.append(f"\t\tREQUIRE({r_get} == {s_get});")
            lines.append("\t}")
            lines.append("}")
        elif comp_type == "bitwise":
            lines.append("for (size_t i = 0; i < size; i++)")
            lines.append("{")
            lines.append(f"\tauto v1 = {r_get};")
            lines.append(f"\tauto v2 = {s_get};")
            lines.append("\tuint64_t u1 = 0, u2 = 0;")
            lines.append("\tstd::memcpy(&u1, &v1, sizeof(v1));")
            lines.append("\tstd::memcpy(&u2, &v2, sizeof(v2));")
            lines.append("\tREQUIRE(u1 == u2);")
            lines.append("}")
        elif comp_type in ("logical", "mask") or func_name.endswith("_k") or "ret_msk" in proto_ref:
            lines.append("for (size_t i = 0; i < size; i++)")
            lines.append("{")
            lines.append(f"\tREQUIRE((!!{r_get}) == (!!{s_get}));")
            lines.append("}")
        elif not is_loop:
            if has_tolerance:
                tol_expr = self.resolve_tolerance_expr(func_name, "T", ref_var=s_var)
                lines.append("if constexpr (std::is_floating_point_v<T>)")
                lines.append("{")
                lines.append(f"\tT tol = {tol_expr};")
                lines.append(f"\tT diff = abs_diff::abs_diff({r_var}, {s_var});")
                lines.append("\tif (!std::isnan(diff) && !std::isinf(diff)) REQUIRE(diff <= tol);")
                lines.append("}")
                lines.append("else")
                lines.append("{")
                lines.append(f"\tREQUIRE({r_var} == {s_var});")
                lines.append("}")
            else:
                lines.append(f"REQUIRE({r_var} == {s_var});")
        else:
            lines.append("for (size_t i = 0; i < size; i++)")
            lines.append("{")
            lines.append(f"\tREQUIRE({r_get} == {s_get});")
            lines.append("}")
        return lines

    def render_cpp_arg_init_branches(self, func_name: str, var_name: str, arg_idx: int = 0, is_src: bool = False, supported_mkinds: List[str] = None) -> List[str]:
        func_spec = self.specs.get("functions", {}).get(func_name, {})

        type_c_map = {
            "float64": "double", "float32": "float",
            "int64": "int64_t", "int32": "int32_t", "int16": "int16_t", "int8": "int8_t",
            "uint64": "uint64_t", "uint32": "uint32_t", "uint16": "uint16_t", "uint8": "uint8_t"
        }
        lmul_num_map = {"m1": 1, "m2": 2, "m4": 4, "m8": 8, "d2": -2}

        branches = []

        if supported_mkinds is None:
            supported_mkinds = ["unmasked", "mask", "maskz", "masks"]

        for mkind in supported_mkinds:
            mk_spec = func_spec.get(mkind, {})
            dom_spec = mk_spec.get("domain_src" if is_src else "domain", {})
            if not dom_spec and not is_src:
                dom_spec = func_spec.get("domain", {})

            if not dom_spec:
                continue

            mk_enum_map = {"unmasked": "mipp::U", "mask": "mipp::M", "maskz": "mipp::Z", "masks": "mipp::S"}
            mk_cond = f"MK == {mk_enum_map[mkind]}"

            if "by_datatype" in dom_spec:
                by_dt = dom_spec["by_datatype"]
                for dt_key, spec_val in by_dt.items():
                    dt_c = type_c_map.get(dt_key, dt_key)
                    type_cond = f"std::is_same_v<T, {dt_c}>"
                    full_cond = f"{mk_cond} && {type_cond}"
                    if isinstance(spec_val, list):
                        target_idx = min(arg_idx, len(spec_val) - 1)
                        sub_dict = spec_val[target_idx] if isinstance(spec_val[target_idx], dict) else {}
                    elif isinstance(spec_val, dict):
                        sub_dict = spec_val
                    else:
                        sub_dict = {}
                    rnd_code = self._format_rnd_call(sub_dict, var_name)
                    branches.append((full_cond, rnd_code))

            elif "by_lmul" in dom_spec:
                by_lm = dom_spec["by_lmul"]
                for lm_key, spec_val in by_lm.items():
                    lm_num = lmul_num_map.get(lm_key, 1)
                    lm_cond = f"LMUL == {lm_num}"
                    full_cond = f"{mk_cond} && {lm_cond}"
                    if isinstance(spec_val, list):
                        target_idx = min(arg_idx, len(spec_val) - 1)
                        sub_dict = spec_val[target_idx] if isinstance(spec_val[target_idx], dict) else {}
                    elif isinstance(spec_val, dict):
                        sub_dict = spec_val
                    else:
                        sub_dict = {}
                    rnd_code = self._format_rnd_call(sub_dict, var_name)
                    branches.append((full_cond, rnd_code))

            elif "rules" in dom_spec:
                for rule in dom_spec["rules"]:
                    cond_parts = [mk_cond]
                    if "datatype" in rule:
                        dt_c = type_c_map.get(rule["datatype"], rule["datatype"])
                        cond_parts.append(f"std::is_same_v<T, {dt_c}>")
                    if "lmul" in rule:
                        lm_num = lmul_num_map.get(rule["lmul"], 1)
                        cond_parts.append(f"LMUL == {lm_num}")
                    full_cond = " && ".join(cond_parts)
                    rnd_code = self._format_rnd_call(rule, var_name)
                    branches.append((full_cond, rnd_code))

            elif isinstance(dom_spec, dict) and dom_spec:
                rnd_code = self._format_rnd_call(dom_spec, var_name)
                branches.append((mk_cond, rnd_code))

        if not branches:
            return [f"{var_name}[i] = rnd::uniform<T>(seed);"]

        lines = []
        is_first = True
        for cond, code in branches:
            kw = "if constexpr" if is_first else "else if constexpr"
            is_first = False
            lines.append(f"{kw} ({cond})")
            lines.append("{")
            lines.append(f"\t{code}")
            lines.append("}")

        lines.append("else")
        lines.append("{")
        lines.append(f"\t{var_name}[i] = rnd::uniform<T>(seed);")
        lines.append("}")

        return lines

    def render_cpp_test_case(self, dialect_name: str, func_name: str, supported_mkinds: List[str]) -> List[str]:
        lines = []
        func_prefix = "test_mipp_cpp" if dialect_name == "cpp" else "test_mipp_cpp_obj"
        mk_enum_map = {"unmasked": "mipp::U", "mask": "mipp::M", "maskz": "mipp::Z", "masks": "mipp::S"}
        mk_label_map = {"unmasked": "unmasked (U)", "mask": "mask (M)", "maskz": "maskz (Z)", "masks": "masks (S)"}

        datatypes = self._resolve_datatypes(func_name)
        is_product = any("," in str(dt) for dt in datatypes)

        lines.append(f'TEST_CASE("{func_name} - {dialect_name} tests", "[{func_name}]")')
        lines.append("{")

        for mkind in supported_mkinds:
            mk_enum = mk_enum_map[mkind]
            mk_label = mk_label_map[mkind]
            lines.append(f'\tSECTION("{mk_label}")')
            lines.append('\t{')

            for dt in datatypes:
                dt_str = str(dt)
                if is_product and "," in dt_str:
                    dt_src, dt_dst = dt_str.split(",")
                    cpp_type = f"{self._format_cpp_type(dt_src)}, {self._format_cpp_type(dt_dst)}"
                else:
                    cpp_type = self._format_cpp_type(dt)

                lines.append(f'\t\tSECTION("datatype = {dt}")')
                lines.append('\t\t{')

                lmuls_to_test = [(1, "LMUL = 1")] if dialect_name == "obj" else [(1, "LMUL = 1"), (2, "LMUL = 2"), (4, "LMUL = 4"), (8, "LMUL = 8")]
                for lmul_val, lmul_str in lmuls_to_test:
                    lines.append(f'\t\t\tSECTION("{lmul_str}")')
                    lines.append('\t\t\t{')
                    lines.append('\t\t\t\ttry {')
                    lines.append(f'\t\t\t\t\t{func_prefix}_{func_name}<{mk_enum}, {cpp_type}, {lmul_val}>();')
                    lines.append('\t\t\t\t} catch (const mipp::stub_exception& e) {')
                    lines.append('\t\t\t\t\tWARN(e.what());')
                    lines.append('\t\t\t\t}')
                    lines.append('\t\t\t}')

                if dialect_name == "cpp":
                    lines.append('\t\t\t#if defined(MIPP_LDIV_2)')
                    lines.append('\t\t\tSECTION("LDIV = 2")')
                    lines.append('\t\t\t{')
                    lines.append('\t\t\t\ttry {')
                    lines.append(f'\t\t\t\t\t{func_prefix}_{func_name}<{mk_enum}, {cpp_type}, -2>();')
                    lines.append('\t\t\t\t} catch (const mipp::stub_exception& e) {')
                    lines.append('\t\t\t\t\tWARN(e.what());')
                    lines.append('\t\t\t\t}')
                    lines.append('\t\t\t}')
                    lines.append('\t\t\t#endif // MIPP_LDIV_2')

                lines.append('\t\t}')

            lines.append('\t}')

        lines.append("}")
        lines.append("")
        return lines

    def build_unified_cpp_test_file(self, dialect_name: str, func_name: str, N: int = 10) -> str:
        lines = []
        lines.extend(self._render_headers(dialect_name, func_name, N=N))

        mask_support = self.interfaces[func_name].get("mask_support", "all_mask")
        supported_mkinds = []
        if dialect_name == "obj":
            supported_mkinds = ["unmasked"]
        else:
            for m in ["unmasked", "mask", "maskz", "masks"]:
                if m == "unmasked" or self._is_mask_kind_supported(mask_support, m):
                    supported_mkinds.append(m)

        n_args = self._get_n_args(func_name)
        proto_ref = self.interfaces.get(func_name, {}).get("proto_ref", "ret_reg_2args_reg")
        datatypes = self._resolve_datatypes(func_name)
        is_product = any("," in str(dt) for dt in datatypes)
        is_1arg = "1arg" in proto_ref or "2args_reg_val" in proto_ref
        is_3arg = "3args" in proto_ref

        func_prefix = "test_mipp_cpp" if dialect_name == "cpp" else "test_mipp_cpp_obj"
        if is_product:
            lines.append(f"template <mipp::MKIND MK = mipp::U, typename T_src = float, typename T_dst = double, int LMUL = 1>")
        else:
            lines.append(f"template <mipp::MKIND MK = mipp::U, typename T = double, int LMUL = 1>")
        lines.append(f"static void {func_prefix}_{func_name}()")
        lines.append("{")
        lines.append("\tstd::mt19937 seed(Catch::getSeed());")
        lines.append("\tfor (unsigned n = 0; n < get_n_iter(); n++)")
        lines.append("\t{")
        if is_product:
            lines.append("\t\tconstexpr size_t size = (LMUL > 0) ? (mipp::N<T_src>() * static_cast<size_t>(LMUL)) : (mipp::N<T_src>() / static_cast<size_t>(-LMUL));")
            lines.append("\t\tusing T [[maybe_unused]] = T_src;")
        else:
            lines.append("\t\tconstexpr size_t size = (LMUL > 0) ? (mipp::N<T>() * static_cast<size_t>(LMUL)) : (mipp::N<T>() / static_cast<size_t>(-LMUL));")

        proto_spec = self.func_templates.get("prototypes", {}).get(proto_ref, {})
        comp_names = proto_spec.get("components", {})
        decl_comp_key = comp_names.get("decl", "decl_2args")
        load_comp_key = comp_names.get("load", "load_2args_reg")
        op_comp_key = comp_names.get("operation", "op_binop")
        assert_comp_key = comp_names.get("loop_assert", "as_strict_eq")

        decl_raw = self.component_templates.get("declarations", {}).get(decl_comp_key, [])
        load_raw = self.component_templates.get("loads", {}).get(load_comp_key, [])
        op_raw = self.component_templates.get("operations", {}).get(op_comp_key, [])
        as_raw = self.component_templates.get("assertions", {}).get(assert_comp_key, [])
        is_loop = proto_spec.get("is_loop", True)

        if is_product:
            decl_lines = [d.replace("{{size}}", "size").replace("{{dt1_ext}}", "T_src").replace("{{dt2_ext}}", "T_dst") for d in decl_raw]
        else:
            decl_lines = [d.replace("{{size}}", "size").replace("{{dt1_ext}}", "T").replace("{{dt2_ext}}", "T") for d in decl_raw]
        lines.extend(self.indent_lines(decl_lines, 2))

        decl_joined = "\n".join(decl_lines)
        if "masks" in supported_mkinds and not any("inputs_src" in d for d in decl_lines):
            lines.append("\t\t[[maybe_unused]] T inputs_src[size];")
        has_inputs_m = bool(re.search(r"\binputs_m\b", decl_joined))
        if any(m in supported_mkinds for m in ["mask", "maskz", "masks"]) and not has_inputs_m:
            has_inputs_m = True
            lines.append("\t\t[[maybe_unused]] int32_t inputs_m[size];")

        lines.append("")
        lines.append("\t\tfor (size_t i = 0; i < size; i++)")
        lines.append("\t\t{")
        if "inputs1" in decl_joined:
            init_stmt_lines = self.render_cpp_arg_init_branches(func_name, "inputs1", arg_idx=0, supported_mkinds=supported_mkinds)
            lines.extend(self.indent_lines(init_stmt_lines, 3))
        if "inputs2" in decl_joined:
            init_stmt_lines = self.render_cpp_arg_init_branches(func_name, "inputs2", arg_idx=1, supported_mkinds=supported_mkinds)
            lines.extend(self.indent_lines(init_stmt_lines, 3))
        if "inputs3" in decl_joined:
            init_stmt_lines = self.render_cpp_arg_init_branches(func_name, "inputs3", arg_idx=2, supported_mkinds=supported_mkinds)
            lines.extend(self.indent_lines(init_stmt_lines, 3))

        if "inputs_src" in decl_joined or "masks" in supported_mkinds:
            src_init_lines = self.render_cpp_arg_init_branches(func_name, "inputs_src", arg_idx=0, is_src=True, supported_mkinds=supported_mkinds)
            lines.extend(self.indent_lines(src_init_lines, 3))

        if "inputs_m1" in decl_joined:
            lines.append("\t\t\tinputs_m1[i] = rnd::uniform_bool(seed) ? -1 : 0;")
        if "inputs_m2" in decl_joined:
            lines.append("\t\t\tinputs_m2[i] = rnd::uniform_bool(seed) ? -1 : 0;")
        if "inputs_m3" in decl_joined:
            lines.append("\t\t\tinputs_m3[i] = rnd::uniform_bool(seed) ? -1 : 0;")
        if has_inputs_m:
            lines.append("\t\t\tinputs_m[i] = rnd::uniform_bool(seed) ? -1 : 0;")

        lines.append("\t\t}")
        lines.append("")

        def expand_cpp_lines(raw_lines: List[str], mkind: str) -> List[str]:
            out = []
            if "0arg" in proto_ref:
                op_args_r = ""
                op_args_s = ""
            elif "1arg_val" in proto_ref or "1arg_i32" in proto_ref:
                op_args_r = "inputs_m[0]" if func_name in ("set_k", "set1_k", "set0_k") else "inputs1[0]"
                op_args_s = "inputs_m[0]" if func_name in ("set_k", "set1_k", "set0_k") else "inputs1[0]"
            elif "1arg_ptr" in proto_ref or "1arg_Nele" in proto_ref:
                op_args_r = "inputs_m" if func_name in ("set_k", "set1_k", "set0_k") else "inputs1"
                op_args_s = "inputs_m" if func_name in ("set_k", "set1_k", "set0_k") else "inputs1"
            elif "2args_ptr_reg" in proto_ref:
                op_args_r = "res_r, r1"
                op_args_s = "res_s, s1"
            elif "2args_reg_val" in proto_ref:
                op_args_r = "r1, 2"
                op_args_s = "s1, 2"
            elif proto_ref == "ret_reg_3args_1msk_2reg":
                op_args_r = "m1, r2, r3"
                op_args_s = "sm1, s2, s3"
            elif proto_ref == "ret_reg_3args_2reg_1msk":
                op_args_r = "r1, r2, m3"
                op_args_s = "s1, s2, sm3"
            elif proto_ref in ("ret_i32_2args_msk", "ret_msk_2args_msk"):
                op_args_r = "m1, m2"
                op_args_s = "sm1, sm2"
            elif proto_ref in ("ret_i32_1arg_msk", "ret_msk_1arg_msk", "ret_reg_1arg_msk"):
                op_args_r = "m1"
                op_args_s = "sm1"
            elif is_1arg:
                op_args_r = "r1"
                op_args_s = "s1"
            elif is_3arg:
                op_args_r = "r1, r2, r3"
                op_args_s = "s1, s2, s3"
            else:
                op_args_r = "r1, r2"
                op_args_s = "s1, s2"

            fname = func_name
            if fname in ("andb_k", "orb_k", "xorb_k", "notb_k", "andnb_k"):
                fname = fname[:-2]

            load_type = "T_src" if is_product else "T"

            if mkind == "unmasked":
                if fname in ("set", "set_k", "set1", "set1_k", "set0", "set0_k", "load", "loadu"):
                    op_call = f"mipp::{fname}<{load_type}, LMUL>({op_args_r})" if op_args_r else f"mipp::{fname}<{load_type}, LMUL>()"
                    scalar_op_call = f"mipp::{fname}<{load_type}, LMUL, mipp::ISA::SCALAR>({op_args_s})" if op_args_s else f"mipp::{fname}<{load_type}, LMUL, mipp::ISA::SCALAR>()"
                else:
                    op_call = f"mipp::{fname}({op_args_r})"
                    scalar_op_call = f"mipp::{fname}({op_args_s})"
            elif mkind == "mask":
                op_call = f"mipp::{fname}<mipp::M, {load_type}, LMUL>(m1, {op_args_r})"
                scalar_op_call = f"mipp::{fname}<mipp::M, {load_type}, LMUL, mipp::ISA::SCALAR>(sm1, {op_args_s})"
            elif mkind == "maskz":
                op_call = f"mipp::{fname}<mipp::Z, {load_type}, LMUL>(m1, {op_args_r})"
                scalar_op_call = f"mipp::{fname}<mipp::Z, {load_type}, LMUL, mipp::ISA::SCALAR>(sm1, {op_args_s})"
            elif mkind == "masks":
                op_call = f"mipp::{fname}<mipp::S, {load_type}, LMUL>(m1, rsrc, {op_args_r})"
                scalar_op_call = f"mipp::{fname}<mipp::S, {load_type}, LMUL, mipp::ISA::SCALAR>(sm1, ssrc, {op_args_s})"

            if dialect_name == "obj":
                op_syms = {"add": "+", "sub": "-", "mul": "*", "div": "/", "andb": "&", "orb": "|", "xorb": "^"}
                cmp_syms = {"cmpeq": "==", "cmpneq": "!=", "cmplt": "<", "cmple": "<=", "cmpgt": ">", "cmpge": ">="}
                if raw_lines == load_raw:
                    lines_out = [
                        "mipp::Rvd<T> r1(inputs1);",
                        "auto s1 = mipp::load<T, LMUL, mipp::ISA::SCALAR>(inputs1);"
                    ]
                    if not is_1arg:
                        lines_out.extend([
                            "mipp::Rvd<T> r2(inputs2);",
                            "auto s2 = mipp::load<T, LMUL, mipp::ISA::SCALAR>(inputs2);"
                        ])
                    if is_3arg:
                        lines_out.extend([
                            "mipp::Rvd<T> r3(inputs3);",
                            "auto s3 = mipp::load<T, LMUL, mipp::ISA::SCALAR>(inputs3);"
                        ])
                    return lines_out
                elif raw_lines == op_raw:
                    if fname in op_syms:
                        return [
                            f"auto rres = r1 {op_syms[fname]} r2;",
                            f"auto sres = {scalar_op_call};"
                        ]
                    elif fname in cmp_syms:
                        return [
                            f"auto rres = r1 {cmp_syms[fname]} r2;",
                            f"auto sres = {scalar_op_call};"
                        ]
                    else:
                        method_args = "r2" if not is_1arg else ""
                        return [
                            f"auto rres = r1.{fname}({method_args});",
                            f"auto sres = {scalar_op_call};"
                        ]

            elif is_product and raw_lines == op_raw:
                base_fname = "cast" if fname == "cast_k" else fname
                if fname == "wcvt":
                    dst_type_map = [
                        ("double", "float64"),
                        ("int64_t", "int64"), ("int32_t", "int32"), ("int16_t", "int16"),
                        ("uint64_t", "uint64"), ("uint32_t", "uint32"), ("uint16_t", "uint16")
                    ]
                else:
                    dst_type_map = [
                        ("double", "float64"), ("float", "float32"),
                        ("int64_t", "int64"), ("int32_t", "int32"), ("int16_t", "int16"), ("int8_t", "int8"),
                        ("uint64_t", "uint64"), ("uint32_t", "uint32"), ("uint16_t", "uint16"), ("uint8_t", "uint8")
                    ]
                func_spec = self.specs.get("functions", {}).get(func_name, {})
                comp_type = func_spec.get("comparison", self.specs.get("default", {}).get("comparison", "exact"))
                branch_lines = []
                is_first = True
                for dst_type, dst_name in dst_type_map:
                    kw = "if constexpr" if is_first else "else if constexpr"
                    is_first = False
                    branch_lines.append(f"{kw} (std::is_same_v<T_dst, {dst_type}>)")
                    branch_lines.append("{")
                    branch_lines.append(f"\tauto rres = mipp::{base_fname}_{dst_name}({op_args_r});")
                    branch_lines.append(f"\tauto sres = mipp::{base_fname}_{dst_name}({op_args_s});")
                    branch_lines.append(f"\tconstexpr size_t size_dst = (LMUL > 0) ? (mipp::N<{dst_type}>() * static_cast<size_t>(LMUL)) : (mipp::N<{dst_type}>() / static_cast<size_t>(-LMUL));")
                    branch_lines.append(f"\tfor (size_t i = 0; i < size_dst; i++)")
                    branch_lines.append(f"\t{{")
                    if comp_type == "bitwise":
                        branch_lines.append(f"\t\tauto v1 = mipp::get(rres, i);")
                        branch_lines.append(f"\t\tauto v2 = mipp::get(sres, i);")
                        branch_lines.append(f"\t\tuint64_t u1 = 0, u2 = 0;")
                        branch_lines.append(f"\t\tstd::memcpy(&u1, &v1, sizeof(v1));")
                        branch_lines.append(f"\t\tstd::memcpy(&u2, &v2, sizeof(v2));")
                        branch_lines.append(f"\t\tREQUIRE(u1 == u2);")
                    elif comp_type in ("logical", "mask"):
                        branch_lines.append(f"\t\tREQUIRE((!!mipp::get(rres, i)) == (!!mipp::get(sres, i)));")
                    else:
                        branch_lines.append(f"\t\tREQUIRE(mipp::get(rres, i) == mipp::get(sres, i));")
                    branch_lines.append(f"\t}}")
                    branch_lines.append("}")
                return branch_lines
            elif is_product and raw_lines == as_raw:
                return []

            for line in raw_lines:
                l = line
                if dialect_name == "obj":
                    l = l.replace("{{reg_type}}", "mipp::Rvd<T>")
                    l = l.replace("{{scalar_reg_type}}", "auto")
                    l = l.replace("{{msk_type}}", "mipp::Rvm<T>")
                    l = l.replace("{{scalar_msk_type}}", "auto")
                    l = l.replace("{{msk_type_dst}}", "mipp::Rvd<T>")
                    l = l.replace("{{scalar_msk_type_dst}}", "auto")
                    l = l.replace("{{reg_type_dst}}", "mipp::Rvd<T>")
                    l = l.replace("{{scalar_reg_type_dst}}", "auto")
                    l = l.replace("{{load_call1}}", "inputs1")
                    l = l.replace("{{scalar_load_call1}}", "inputs1")
                    l = l.replace("{{load_call2}}", "inputs2")
                    l = l.replace("{{scalar_load_call2}}", "inputs2")
                else:
                    l = l.replace("{{reg_type}}", "auto")
                    l = l.replace("{{scalar_reg_type}}", "auto")
                    l = l.replace("{{msk_type}}", "auto")
                    l = l.replace("{{scalar_msk_type}}", "auto")
                    l = l.replace("{{msk_type_dst}}", "auto")
                    l = l.replace("{{scalar_msk_type_dst}}", "auto")
                    l = l.replace("{{reg_type_dst}}", "auto")
                    l = l.replace("{{scalar_reg_type_dst}}", "auto")
                    l = l.replace("{{load_call1}}", f"mipp::load<{load_type}, LMUL>(inputs1)")
                    l = l.replace("{{scalar_load_call1}}", f"mipp::load<{load_type}, LMUL, mipp::ISA::SCALAR>(inputs1)")
                    l = l.replace("{{load_call2}}", f"mipp::load<{load_type}, LMUL>(inputs2)")
                    l = l.replace("{{scalar_load_call2}}", f"mipp::load<{load_type}, LMUL, mipp::ISA::SCALAR>(inputs2)")
                    l = l.replace("{{load_call3}}", f"mipp::load<{load_type}, LMUL>(inputs3)")
                    l = l.replace("{{scalar_load_call3}}", f"mipp::load<{load_type}, LMUL, mipp::ISA::SCALAR>(inputs3)")
                    l = l.replace("{{set_k_call}}", f"mipp::set_k<{load_type}, LMUL>(inputs_m)")
                    l = l.replace("{{scalar_set_k_call}}", f"mipp::set_k<{load_type}, LMUL, mipp::ISA::SCALAR>(inputs_m)")
                    l = l.replace("{{set_k_call1}}", f"mipp::set_k<{load_type}, LMUL>(inputs_m1)")
                    l = l.replace("{{scalar_set_k_call1}}", f"mipp::set_k<{load_type}, LMUL, mipp::ISA::SCALAR>(inputs_m1)")
                    l = l.replace("{{set_k_call2}}", f"mipp::set_k<{load_type}, LMUL>(inputs_m2)")
                    l = l.replace("{{scalar_set_k_call2}}", f"mipp::set_k<{load_type}, LMUL, mipp::ISA::SCALAR>(inputs_m2)")
                    l = l.replace("{{set_k_call3}}", f"mipp::set_k<{load_type}, LMUL>(inputs_m3)")
                    l = l.replace("{{scalar_set_k_call3}}", f"mipp::set_k<{load_type}, LMUL, mipp::ISA::SCALAR>(inputs_m3)")
                l = l.replace("{{op_call}}", op_call)
                l = l.replace("{{scalar_op_call}}", scalar_op_call)
                l = l.replace("{{get_func}}(rres, i)", "rres[i]" if dialect_name == "obj" else "mipp::get(rres, i)")
                l = l.replace("{{get_scalar_func}}(sres, i)", "sres[i]" if dialect_name == "obj" else "mipp::get(sres, i)")
                l = l.replace("{{get_k_func}}(rres, i)", "rres[i]" if dialect_name == "obj" else "mipp::get(rres, i)")
                l = l.replace("{{get_scalar_k_func}}(sres, i)", "sres[i]" if dialect_name == "obj" else "mipp::get(sres, i)")
                l = l.replace("{{tol_decl}}", "auto tol = (decltype(res2))0.05 * abs_diff::abs_diff(res2);")
                l = l.replace("{{tol_decl_s3}}", "T tol = (T)0.05 * abs_diff::abs_diff(sres);")
                l = l.replace("{{nan_inf_skip_lines}}", "if (std::isinf(tol) || std::isnan(tol)) continue;\nif (std::isnan(diff) || std::isnan(res2) || std::isnan(res1)) continue;\nif (std::isinf(diff) || std::isinf(res2) || std::isinf(res1)) continue;")
                out.append(l)
            return out

        mk_enum_map = {"unmasked": "mipp::U", "mask": "mipp::M", "maskz": "mipp::Z", "masks": "mipp::S"}
        is_first_mk = True

        is_void = proto_ref.startswith("ret_void")

        if is_product or is_void:
            for mkind in supported_mkinds:
                mk_enum = mk_enum_map[mkind]
                keyword = "if constexpr" if is_first_mk else "else if constexpr"
                is_first_mk = False

                lines.append(f"\t\t{keyword} (MK == {mk_enum})")
                lines.append("\t\t{")
                loads_lines = expand_cpp_lines(load_raw, mkind)
                lines.extend(self.indent_lines(loads_lines, 3))
                if dialect_name != "obj" and mkind in ("mask", "maskz", "masks") and not any("m1" in l for l in loads_lines):
                    lines.append("\t\t\tauto m1 = mipp::set_k<T, LMUL>(inputs_m);")
                    lines.append("\t\t\tauto sm1 = mipp::set_k<T, LMUL, mipp::ISA::SCALAR>(inputs_m);")
                if dialect_name != "obj" and mkind == "masks" and not any("rsrc" in l for l in loads_lines):
                    lines.append("\t\t\tauto rsrc = mipp::load<T, LMUL>(inputs_src);")
                    lines.append("\t\t\tauto ssrc = mipp::load<T, LMUL, mipp::ISA::SCALAR>(inputs_src);")
                op_lines = expand_cpp_lines(op_raw, mkind)
                lines.extend(self.indent_lines(op_lines, 3))
                if dialect_name == "obj" and not is_void:
                    as_lines = expand_cpp_lines(as_raw, mkind)
                    lines.extend(self.indent_lines(as_lines, 3))
                lines.append("\t\t}")

            if is_void:
                lines.append("")
                lines.append("\t\tfor (size_t i = 0; i < size; i++)")
                lines.append("\t\t{")
                lines.append("\t\t\tREQUIRE(res_r[i] == res_s[i]);")
                lines.append("\t\t}")
        else:
            loads_lines = expand_cpp_lines(load_raw, "unmasked")
            base_loads = [l for l in loads_lines if any(v in l for v in ("r1 =", "r2 =", "r3 =", "s1 =", "s2 =", "s3 =", "m1 =", "m2 =", "m3 =", "sm1 =", "sm2 =", "sm3 =", "r1(", "r2(", "r3("))]
            lines.extend(self.indent_lines(base_loads, 2))

            r_var = "rres"
            s_var = "sres"

            lines.append(f"\t\tauto {r_var} = [&]() {{")
            is_first_mk = True
            for mkind in supported_mkinds:
                mk_enum = mk_enum_map[mkind]
                keyword = "if constexpr" if is_first_mk else "else if constexpr"
                is_first_mk = False
                lines.append(f"\t\t\t{keyword} (MK == {mk_enum})")
                lines.append("\t\t\t{")
                if mkind in ("mask", "maskz", "masks"):
                    lines.append("\t\t\t\tauto m1 = mipp::set_k<T, LMUL>(inputs_m);")
                if mkind == "masks":
                    lines.append("\t\t\t\tauto rsrc = mipp::load<T, LMUL>(inputs_src);")
                op_lines = expand_cpp_lines(op_raw, mkind)
                op_r_matches = [l for l in op_lines if any(k in l for k in ("rres =", "res_r ="))]
                if op_r_matches:
                    ret_r = re.sub(r"^[\w:<>]+\s+(rres|res_r)\s*=\s*", "return ", op_r_matches[0].strip())
                    lines.append(f"\t\t\t\t{ret_r}")
                lines.append("\t\t\t}")
            lines.append("\t\t}();")
            lines.append("")

            lines.append(f"\t\tauto {s_var} = [&]() {{")
            is_first_mk = True
            for mkind in supported_mkinds:
                mk_enum = mk_enum_map[mkind]
                keyword = "if constexpr" if is_first_mk else "else if constexpr"
                is_first_mk = False
                lines.append(f"\t\t\t{keyword} (MK == {mk_enum})")
                lines.append("\t\t\t{")
                if mkind in ("mask", "maskz", "masks"):
                    lines.append("\t\t\t\tauto sm1 = mipp::set_k<T, LMUL, mipp::ISA::SCALAR>(inputs_m);")
                if mkind == "masks":
                    lines.append("\t\t\t\tauto ssrc = mipp::load<T, LMUL, mipp::ISA::SCALAR>(inputs_src);")
                op_lines = expand_cpp_lines(op_raw, mkind)
                op_s_matches = [l for l in op_lines if any(k in l for k in ("sres =", "res_s ="))]
                if op_s_matches:
                    ret_s = re.sub(r"^[\w:<>]+\s+(sres|res_s)\s*=\s*", "return ", op_s_matches[0].strip())
                    lines.append(f"\t\t\t\t{ret_s}")
                lines.append("\t\t\t}")
            lines.append("\t\t}();")
            lines.append("")

            val_lines = self.render_cpp_validation_block(func_name, proto_ref, is_product, r_var=r_var, s_var=s_var, dialect_name=dialect_name)
            lines.extend(self.indent_lines(val_lines, 2))

        lines.append("\t}")
        lines.append("}")
        lines.append("")

        lines.extend(self.render_cpp_test_case(dialect_name, func_name, supported_mkinds))
        return "\n".join(lines)

    def build_test_file_content(self, dialect_name: str, func_name: str, lmul_suffix: str = "m1", mkind: str = "", lmul: int = 0, N: int = 10) -> str:
        if dialect_name in ("cpp", "obj"):
            return self.build_unified_cpp_test_file(dialect_name, func_name, N=N)
        return self.render_function_test(dialect_name, func_name, lmul_suffix, mkind=mkind, lmul=lmul, N=N)

    def render_function_test(self, dialect_name: str, func_name: str, lmul_suffix: str = "m1", mkind: str = "", lmul: int = 0, N: int = 10) -> str:
        """Render complete Catch2 test file code for specified dialect, function and LMUL suffix."""
        lines = []
        lines.extend(self._render_headers(dialect_name, func_name, N=N))

        datatypes = self._resolve_datatypes(func_name)
        is_product = any("," in str(dt) for dt in datatypes)

        if lmul < 0:
            lines.append("#if defined(MIPP_LDIV_2)")

        if dialect_name == "c" or is_product:
            for dt in datatypes:
                lines.extend(self._render_single_test_func(dialect_name, func_name, str(dt), lmul_suffix, mkind=mkind, lmul=lmul))
        else:
            lines.extend(self._render_single_test_func(dialect_name, func_name, "", lmul_suffix, mkind=mkind, lmul=lmul))

        lines.extend(self._render_test_case_section(dialect_name, func_name, lmul_suffix, mkind=mkind, lmul=lmul))

        if lmul < 0:
            lines.append("#endif // MIPP_LDIV_2")

        return "\n".join(lines)
