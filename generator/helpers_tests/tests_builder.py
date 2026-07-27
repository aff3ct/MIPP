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
import jinja2
from typing import Dict, List, Any, Optional, Set

from .dialect_adapters import DialectAdapter, CppDialectAdapter, CDialectAdapter, CppObjDialectAdapter
from tools import DATATYPES_MAP

class DomainResolver:
    """
    Unified Domain and Mask Specification Engine for MIPP Test Generators.
    Shared across C, C++ unified, and C++ Object layer test builders.
    """

    def resolve_domain_spec(self, func_spec: dict, var_name: str = "inputs1", dt: str = "", lmul: str = "") -> Optional[dict]:
        domain_entry = None

        if var_name == "inputs_src" and "domain_src" in func_spec:
            domain_entry = func_spec["domain_src"]
        elif "input_domain" in func_spec:
            inp_domain = func_spec["input_domain"]
            if isinstance(inp_domain, list):
                idx_map = {"inputs1": 0, "inputs2": 1, "inputs3": 2}
                idx = idx_map.get(var_name, 0)
                if idx < len(inp_domain):
                    domain_entry = inp_domain[idx]
            elif isinstance(inp_domain, dict):
                domain_entry = inp_domain

        if domain_entry is None:
            domain_entry = func_spec.get("domain", {})

        if not domain_entry:
            return None

        if isinstance(domain_entry, dict):
            if "rules" in domain_entry and isinstance(domain_entry["rules"], list):
                raw_dt = dt.replace("_t", "")
                for rule in domain_entry["rules"]:
                    r_dt = rule.get("datatype")
                    r_lmul = rule.get("lmul")
                    dt_match = (not r_dt) or (r_dt == raw_dt)
                    lmul_match = (not r_lmul) or (str(r_lmul) == str(lmul))
                    if dt_match and lmul_match:
                        return rule

            raw_dt = dt.replace("_t", "")
            if "by_datatype" in domain_entry and raw_dt in domain_entry["by_datatype"]:
                sub = domain_entry["by_datatype"][raw_dt]
                if isinstance(sub, dict):
                    return sub
                elif isinstance(sub, list) and sub:
                    return sub[0]

            if "by_lmul" in domain_entry and str(lmul) in domain_entry["by_lmul"]:
                sub = domain_entry["by_lmul"][str(lmul)]
                if isinstance(sub, dict):
                    return sub

            if "default" in domain_entry:
                sub = domain_entry["default"]
                if isinstance(sub, dict):
                    return sub
                elif isinstance(sub, list) and sub:
                    return sub[0]

            return domain_entry

        elif isinstance(domain_entry, list) and domain_entry:
            return domain_entry[0]

        return None

    def render_input_filling(self, func_spec: dict, var_name: str = "inputs1", dialect: str = "c", dt_cstd: str = "", lmul_suffix: str = "", lmul: str = "") -> List[str]:
        is_cpp = (dialect in ("cpp", "obj"))
        active_lmul = lmul_suffix or lmul

        if not is_cpp:
            spec = self.resolve_domain_spec(func_spec, var_name=var_name, dt=dt_cstd, lmul=active_lmul)
            expr = self._spec_to_uniform_call(spec, is_cpp=False, dt_cstd=dt_cstd)
            return [f"\t\t\t{var_name}[i] = {expr};"]
        else:
            domain_entry = func_spec.get("domain_src" if var_name == "inputs_src" else "domain", {})
            if "input_domain" in func_spec:
                inp_domain = func_spec["input_domain"]
                idx_map = {"inputs1": 0, "inputs2": 1, "inputs3": 2}
                idx = idx_map.get(var_name, 0)
                if isinstance(inp_domain, list) and idx < len(inp_domain):
                    domain_entry = inp_domain[idx]

            by_dt = domain_entry.get("by_datatype", {}) if isinstance(domain_entry, dict) else {}
            rules = domain_entry.get("rules", []) if isinstance(domain_entry, dict) else []

            if by_dt:
                res = []
                first = True
                for raw_dt, spec in by_dt.items():
                    if isinstance(spec, dict):
                        kw = "if constexpr" if first else "else if constexpr"
                        first = False
                        expr = self._spec_to_uniform_call(spec, is_cpp=True)
                        res.append(f"\t\t\t{kw} (std::is_same_v<T, {raw_dt}_t>) {var_name}[i] = {expr};")
                if res:
                    default_spec = domain_entry.get("default") if isinstance(domain_entry, dict) else None
                    def_expr = self._spec_to_uniform_call(default_spec, is_cpp=True)
                    res.append(f"\t\t\telse {var_name}[i] = {def_expr};")
                    return res

            elif rules:
                res = []
                first = True
                for rule in rules:
                    r_dt = rule.get("datatype")
                    if r_dt:
                        kw = "if constexpr" if first else "else if constexpr"
                        first = False
                        expr = self._spec_to_uniform_call(rule, is_cpp=True)
                        res.append(f"\t\t\t{kw} (std::is_same_v<T, {r_dt}_t>) {var_name}[i] = {expr};")
                if res:
                    default_spec = domain_entry.get("default") if isinstance(domain_entry, dict) else None
                    def_expr = self._spec_to_uniform_call(default_spec, is_cpp=True)
                    res.append(f"\t\t\telse {var_name}[i] = {def_expr};")
                    return res

            spec = self.resolve_domain_spec(func_spec, var_name=var_name, dt="", lmul=lmul)
            expr = self._spec_to_uniform_call(spec, is_cpp=True)
            return [f"\t\t\t{var_name}[i] = {expr};"]

    def _spec_to_uniform_call(self, spec: Optional[dict], is_cpp: bool = False, dt_cstd: str = "") -> str:
        T_str = "T" if is_cpp else dt_cstd
        if not spec:
            return f"rnd::uniform<{T_str}>(seed)"

        mn = spec.get("min")
        mx = spec.get("max")
        ex_zero = spec.get("exclude_zero", False)
        s_pos = spec.get("strictly_positive", False)
        pos = spec.get("positive", False)
        s_neg = spec.get("strictly_negative", False)
        neg = spec.get("negative", False)

        if ex_zero and (mn is not None) and (mx is not None):
            return f"rnd::uniform_exclude_zero<{T_str}>(seed, static_cast<{T_str}>({mn}), static_cast<{T_str}>({mx}))"
        elif (mn is not None) and (mx is not None):
            return f"rnd::uniform<{T_str}>(seed, static_cast<{T_str}>({mn}), static_cast<{T_str}>({mx}))"
        elif ex_zero:
            return f"rnd::uniform_exclude_zero<{T_str}>(seed)"
        elif s_pos:
            return f"rnd::uniform_strictly_positive<{T_str}>(seed)"
        elif pos:
            return f"rnd::uniform_positive<{T_str}>(seed)"
        elif s_neg:
            return f"rnd::uniform_strictly_negative<{T_str}>(seed)"
        elif neg:
            return f"rnd::uniform_negative<{T_str}>(seed)"
        else:
            return f"rnd::uniform<{T_str}>(seed)"

    def render_mask_filling(self, func_spec: dict, var_name: str = "inputs_m") -> str:
        pattern = func_spec.get("mask_pattern", "uniform_bool")
        if pattern == "uniform_bool":
            return f"{var_name}[i] = rnd::uniform_bool(seed) ? -1 : 0;"
        elif pattern == "alternating":
            return f"{var_name}[i] = (i % 2 == 0) ? -1 : 0;"
        elif pattern == "all_true":
            return f"{var_name}[i] = -1;"
        elif pattern == "all_false":
            return f"{var_name}[i] = 0;"
        elif pattern == "sparse":
            return f"{var_name}[i] = (i % 4 == 0) ? -1 : 0;"
        elif pattern == "dense":
            return f"{var_name}[i] = (i % 4 != 0) ? -1 : 0;"
        else:
            return f"{var_name}[i] = rnd::uniform_bool(seed) ? -1 : 0;"


class TestsBuilderEngine:

    def render_template(self, template_lines: List[str], **kwargs) -> List[str]:
        if not template_lines:
            return []
        template_str = "\n".join(template_lines)
        rendered = jinja2.Template(template_str).render(**kwargs)
        return rendered.split("\n")

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

        self.domain_resolver = DomainResolver()
        print("  ➔ Validating JSON configuration schemas...")
        self.component_templates = self._load_and_validate("tests_component_templates.json", "component_templates_schema.json")
        self.func_templates = self._load_and_validate("tests_func_templates.json", "func_templates_schema.json")
        self.specs = self._load_and_validate("tests_specs.json", "specs_schema.json")
        print("    ✓ All schemas valid!\n")

        self.interfaces = self._load_json(os.path.join(self.helpers_headers_dir, "registry_interfaces.json"))
        self.categories = self._load_json(os.path.join(self.helpers_headers_dir, "registry_categories.json"))
        self.protos = self._load_json(os.path.join(self.helpers_headers_dir, "registry_protos.json"))

        self._audit_specs()
        self.isa_definitions = self._discover_isa_definitions()
        
        self.c_builder = TestsBuilderEngineC(self)
        self.cpp_builder = TestsBuilderEngineCpp(self)
        self.cpp_obj_builder = TestsBuilderEngineCppObj(self)

    def get_builder(self, dialect_name: str):
        if dialect_name == "c":
            return self.c_builder
        elif dialect_name == "obj":
            return self.cpp_obj_builder
        return self.cpp_builder

    def get_proto_args_info(self, func_name: str) -> List[Dict[str, Any]]:
        proto_ref = self.interfaces.get(func_name, {}).get("proto_ref", "")
        return self.protos.get(proto_ref, {}).get("args", [])

    def get_required_mask_count(self, func_name: str) -> int:
        args_info = self.get_proto_args_info(func_name)
        return sum(1 for arg in args_info if arg.get("type") == "msk")

    def _build_op_call_args(self, func_name: str, mkind: str, is_scalar: bool = False) -> List[str]:
        proto_ref = self.interfaces.get(func_name, {}).get("proto_ref", "")
        proto_spec = self.protos.get(proto_ref, {})
        ret_type = proto_spec.get("ret", {}).get("type")
        args_info = proto_spec.get("args", [])
        args = []
        reg_i = 1
        msk_i = 1
        for arg in args_info:
            atype = arg.get("type")
            if atype == "reg":
                args.append(f"s{reg_i}" if is_scalar else f"r{reg_i}")
                reg_i += 1
            elif atype == "msk":
                args.append(f"sm{msk_i}" if is_scalar else f"m{msk_i}")
                msk_i += 1
            elif atype == "val":
                if arg.get("fixeddatatype") in ("uint32", "uint"):
                    args.append("0")
                elif "2args_reg_val" in proto_ref or "1arg" in proto_ref or reg_i == 1:
                    args.append("inputs1[0]")
                else:
                    args.append("inputs2[0]")
            elif atype == "Nele":
                args.append("inputs_m" if arg.get("fixeddatatype") in ("int32", "i32") else "inputs1")
            elif atype == "ptr":
                if arg.get("charac") == "WO":
                    args.append("res_s" if is_scalar else "res_r")
                else:
                    args.append("inputs1")

        if mkind in ("mask", "maskz", "masks"):
            args.insert(0, "sm1" if is_scalar else "m1")
        if mkind == "masks":
            args.insert(1, "ssrc" if is_scalar else "rsrc")

        return args

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
        spec_dt = self.specs.get("specifications", {}).get(func_name, {}).get("datatypes")
        dt_spec = spec_dt if spec_dt else self.interfaces.get(func_name, {}).get("datatypes", "all_datatypes")
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
        return []

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

    def _get_prototype_mapping(self, func_name: str) -> Dict[str, Any]:
        proto_ref = self.interfaces.get(func_name, {}).get("proto_ref", "ret_reg_2args_reg")
        prototypes = self.func_templates.get("prototypes", {})
        if proto_ref in prototypes:
            res = copy.deepcopy(prototypes[proto_ref])
            res["proto_ref"] = proto_ref
            return res
        return {"components": {"init": "init_uniform", "op": "op_binary", "assertion": "as_strict_eq"}, "proto_ref": proto_ref}

    def is_func_disabled(self, func_name: str, dialect_name: str = "") -> tuple[bool, Optional[str]]:
        func_spec = self.specs["functions"].get(func_name, {})
        if dialect_name == "obj":
            support_obj = func_spec.get("support_obj", self.specs.get("default", {}).get("support_obj", False))
            if not support_obj:
                return True, f"Function '{func_name}' does not support the Object layer (support_obj: false)"
        if func_spec.get("disabled"):
            return True, func_spec.get("disabled_reason", "Disabled in specs")
        return False, None

    def is_func_unsupported_by_obj(self, func_name: str) -> bool:
        disabled, reason = self.is_func_disabled(func_name, "obj")
        if disabled and "does not support the Object layer" in (reason or ""):
            return True
        return False

    def _is_mask_kind_supported(self, mask_support: str, mkind: str) -> bool:
        if mkind == "unmasked":
            return True
        if mask_support == "no_mask":
            return False
        if mask_support == "all_mask":
            return True
        if mask_support == "only_maskz":
            return mkind == "maskz"
        if mask_support == "mask_and_maskz":
            return mkind in ("mask", "maskz")
        if mask_support == "maskz_and_masks":
            return mkind in ("maskz", "masks")
        return False

    def indent_lines(self, lines: List[str], indent_level: int) -> List[str]:
        tabs = "\t" * indent_level
        return [f"{tabs}{line}" if line else "" for line in lines]

    def _format_cpp_type(self, dt_str: str) -> str:
        mapping = {
            "float32": "float", "float64": "double",
            "int8": "int8_t", "int16": "int16_t", "int32": "int32_t", "int64": "int64_t",
            "uint8": "uint8_t", "uint16": "uint16_t", "uint32": "uint32_t", "uint64": "uint64_t"
        }
        return mapping.get(dt_str, dt_str)

    def resolve_tolerance_expr(self, func_name: str, dt_cpp: str, ref_var: str = "res2") -> str:
        func_spec = self.specs["functions"].get(func_name, {})
        tol_spec = func_spec.get("tolerance")
        if not tol_spec:
            tol_spec = self.specs.get("default", {}).get("tolerance", {"type": "relative_percent", "value": 0.001})

        if "by_datatype" in tol_spec:
            by_dt = tol_spec["by_datatype"]
            f32_spec = by_dt.get("float32", tol_spec.get("default", {"type": "relative_percent", "value": 0.001}))
            f64_spec = by_dt.get("float64", tol_spec.get("default", {"type": "relative_percent", "value": 0.0001}))
            
            f32_val = f32_spec.get("value", 0.001)
            f64_val = f64_spec.get("value", 0.0001)
            f32_type = f32_spec.get("type", "relative_percent")
            f64_type = f64_spec.get("type", "relative_percent")

            if f32_type == "relative_percent":
                f32_expr = f"({dt_cpp})(abs_diff::abs_diff({ref_var}) * (float){f32_val})"
            else:
                f32_expr = f"({dt_cpp})((float){f32_val})"

            if f64_type == "relative_percent":
                f64_expr = f"({dt_cpp})(abs_diff::abs_diff({ref_var}) * (double){f64_val})"
            else:
                f64_expr = f"({dt_cpp})((double){f64_val})"

            if dt_cpp in ("float32_t", "float"):
                return f32_expr
            elif dt_cpp in ("float64_t", "double"):
                return f64_expr
            else:
                return f"(std::is_same_v<{dt_cpp}, float> ? {f32_expr} : {f64_expr})"
        else:
            val = tol_spec.get("value", 0.001)
            ttype = tol_spec.get("type", "relative_percent")
            f32_expr = f"({dt_cpp})(abs_diff::abs_diff({ref_var}) * (float){val})" if ttype == "relative_percent" else f"({dt_cpp})((float){val})"
            f64_expr = f"({dt_cpp})(abs_diff::abs_diff({ref_var}) * (double){val})" if ttype == "relative_percent" else f"({dt_cpp})((double){val})"
            if dt_cpp in ("float32_t", "float"):
                return f32_expr
            elif dt_cpp in ("float64_t", "double"):
                return f64_expr
            else:
                return f"(std::is_same_v<{dt_cpp}, float> ? {f32_expr} : {f64_expr})"

    def render_cpp_validation_block(self, func_name: str, proto_ref: str, is_product: bool = False, r_var: str = "rres", s_var: str = "sres", dialect_name: str = "cpp") -> List[str]:
        func_spec = self.specs.get("functions", {}).get(func_name, {})
        default_spec = self.specs.get("default", {})
        comp_type = func_spec.get("comparison", default_spec.get("comparison", "exact"))
        has_tolerance = (comp_type == "tolerance") or ("tolerance" in func_spec)
        is_loop = self.func_templates.get("prototypes", {}).get(proto_ref, {}).get("is_loop", True)
        if func_name in ("get", "get_k", "getfirst") or proto_ref in ("ret_val_2args_reg_val", "ret_val_2args_msk_val"):
            is_loop = False

        if proto_ref.startswith("ret_void"):
            r_get = f"{r_var}[i]"
            s_get = f"{s_var}[i]"
        else:
            r_get = f"{r_var}[i]" if dialect_name == "obj" else f"mipp::get({r_var}, i)"
            s_get = f"mipp::get({s_var}, i)"

        overflow_check = func_spec.get("overflow_check")

        loop_limit = "size_out" if is_product else "size"

        nan_inf_skip = func_spec.get("nan_inf_skip", False)
        nan_inf_skip_lines = "if (std::isnan(diff) || std::isinf(diff)) continue;" if nan_inf_skip else ""

        val_lines = []
        if not is_loop:
            if comp_type in ("logical", "mask"):
                tpl = self.component_templates.get("assertions", {}).get("as_logical_scalar_eq_cpp", [])
                for line in tpl:
                    val_lines.append(line.replace("{{r_var}}", r_var).replace("{{s_var}}", s_var))
            elif has_tolerance:
                tol_expr = self.resolve_tolerance_expr(func_name, "T", ref_var=s_var)
                tpl = self.component_templates.get("assertions", {}).get("as_tolerance_scalar_cpp", [])
                val_lines.extend(self.render_template(tpl, tol_expr=tol_expr, r_var=r_var, s_var=s_var, nan_inf_skip_lines=nan_inf_skip_lines))
            else:
                tpl = self.component_templates.get("assertions", {}).get("as_strict_scalar_eq_cpp", [])
                val_lines.extend(self.render_template(tpl, r_var=r_var, s_var=s_var))
        elif has_tolerance:
            tol_expr = self.resolve_tolerance_expr(func_name, "T", ref_var=s_get)
            tpl = self.component_templates.get("assertions", {}).get("as_tolerance_cpp", [])
            val_lines.extend(self.render_template(tpl, tol_expr=tol_expr, r_get=r_get, s_get=s_get, loop_limit=loop_limit, nan_inf_skip_lines=nan_inf_skip_lines))
        elif comp_type == "bitwise":
            tpl = self.component_templates.get("assertions", {}).get("as_bitwise_eq_cpp", [])
            val_lines.extend(self.render_template(tpl, r_get=r_get, s_get=s_get, loop_limit=loop_limit))
        elif comp_type in ("logical", "mask") or func_name.endswith("_k") or "ret_msk" in proto_ref:
            tpl = self.component_templates.get("assertions", {}).get("as_logical_eq_cpp", [])
            val_lines.extend(self.render_template(tpl, r_get=r_get, s_get=s_get, loop_limit=loop_limit))
        else:
            val_lines.append(f"for (size_t i = 0; i < {loop_limit}; i++)")
            val_lines.append("{")
            val_lines.append(f"\tREQUIRE({r_get} == {s_get});")
            val_lines.append("}")

        if overflow_check and overflow_check.startswith("accumulate_"):
            lines = []
            kind = overflow_check.replace("accumulate_", "")
            tpl_key = "as_reduction_overflow_check" if kind == "add" else f"as_reduction_{kind}_overflow_check"
            tpl = self.component_templates.get("assertions", {}).get(tpl_key, [])
            for line in tpl:
                if "{{validation_block}}" in line:
                    lines.extend(self.indent_lines(val_lines, 1))
                else:
                    lines.append(line)
            return lines

        return val_lines

    def _render_domain_input_filling(self, func_spec: dict, var_name: str = "inputs1", is_cpp: bool = False, dt_cstd: str = "") -> List[str]:
        domain = func_spec.get("domain", {})
        if not domain:
            if is_cpp:
                return [f"\t\t\t{var_name}[i] = rnd::uniform<T>(seed);"]
            else:
                return [f"\t\t\t{var_name}[i] = rnd::uniform<{dt_cstd}>(seed);"]

        if "by_datatype" in domain:
            by_dt = domain["by_datatype"]
            if not is_cpp:
                raw_dt = dt_cstd.replace("_t", "")
                if raw_dt in by_dt and isinstance(by_dt[raw_dt], dict) and "min" in by_dt[raw_dt] and "max" in by_dt[raw_dt]:
                    mn = by_dt[raw_dt]["min"]
                    mx = by_dt[raw_dt]["max"]
                    return [f"\t\t\t{var_name}[i] = rnd::uniform<{dt_cstd}>(seed, static_cast<{dt_cstd}>({mn}), static_cast<{dt_cstd}>({mx}));"]
                return [f"\t\t\t{var_name}[i] = rnd::uniform<{dt_cstd}>(seed);"]
            else:
                res = []
                first = True
                for dt, bounds in by_dt.items():
                    if isinstance(bounds, dict) and "min" in bounds and "max" in bounds:
                        kw = "if constexpr" if first else "else if constexpr"
                        first = False
                        mn = bounds["min"]
                        mx = bounds["max"]
                        res.append(f"\t\t\t{kw} (std::is_same_v<T, {dt}_t>) {var_name}[i] = rnd::uniform<T>(seed, static_cast<T>({mn}), static_cast<T>({mx}));")
                if res:
                    res.append(f"\t\t\telse {var_name}[i] = rnd::uniform<T>(seed);")
                    return res
                return [f"\t\t\t{var_name}[i] = rnd::uniform<T>(seed);"]

        elif "min" in domain and "max" in domain:
            mn = domain["min"]
            mx = domain["max"]
            if is_cpp:
                return [f"\t\t\t{var_name}[i] = rnd::uniform<T>(seed, static_cast<T>({mn}), static_cast<T>({mx}));"]
            else:
                return [f"\t\t\t{var_name}[i] = rnd::uniform<{dt_cstd}>(seed, static_cast<{dt_cstd}>({mn}), static_cast<{dt_cstd}>({mx}));"]

        if is_cpp:
            return [f"\t\t\t{var_name}[i] = rnd::uniform<T>(seed);"]
        else:
            return [f"\t\t\t{var_name}[i] = rnd::uniform<{dt_cstd}>(seed);"]

    def build_test_file_content(self, dialect_name: str, func_name: str, lmul_suffix: str = "m1", mkind: str = "", lmul: int = 0, N: int = 10) -> str:
        builder = self.get_builder(dialect_name)
        return builder.build_test_file_content(func_name, lmul_suffix=lmul_suffix, mkind=mkind, lmul=lmul, N=N)

    def _audit_specs(self) -> None:
        if "consistency" in self.active_audits:
            print("  ➔ Auditing tests_specs.json for logical consistency...")
            funcs_in_specs = self.specs.get("functions", {})
            for fname, fspec in funcs_in_specs.items():
                if fname not in self.interfaces:
                    print(f"    ⚠️ Warning: function '{fname}' in tests_specs.json is not present in registry_interfaces.json")
            print("    ✓ tests_specs.json passed logical audit!\n")


class TestsBuilderEngineC:

    def __init__(self, engine: TestsBuilderEngine):
        self.engine = engine

    def build_test_file_content(self, func_name: str, lmul_suffix: str = "m1", mkind: str = "", lmul: int = 0, N: int = 10) -> str:
        lines = []
        lines.extend(self._render_headers("c", func_name, N=N))

        datatypes = self.engine._resolve_datatypes(func_name)
        is_product = any("," in str(dt) for dt in datatypes)

        if lmul < 0:
            lines.append("#if defined(MIPP_LDIV_2)")

        for dt in datatypes:
            lines.extend(self._render_single_test_func("c", func_name, str(dt), lmul_suffix, mkind=mkind, lmul=lmul))

        lines.extend(self._render_test_case_section("c", func_name, lmul_suffix, mkind=mkind, lmul=lmul))

        if lmul < 0:
            lines.append("#endif // MIPP_LDIV_2")

        return "\n".join(lines)

    def _render_headers(self, dialect_name: str, func_name: str, N: int = 10) -> List[str]:
        lines = [
            "#include <exception>", "#include <algorithm>", "#include <numeric>",
            "#include <random>", "#include <cstdio>", "#include <cmath>",
            "#include <cstdlib>", "#include <cstring>",
            '#include "uniform.hpp"', '#include "overflow_helpers.hpp"', '#include "abs_diff.hpp"',
            "#ifndef N_ITER", f"#define N_ITER {N}", "#endif", ""
        ]
        headers_set = set()
        headers_set.add('#include <c/common.h>')
        headers_set.add('#include <simd_ext/scalar/scalar_common.h>')
        headers_set.add(f'#include <c/functions/{func_name}.h>')
        headers_set.add(f'#include <simd_ext/scalar/functions/scalar_{func_name}.h>')
        for aux in ["load", "get", "get_k", "toreg", "tomsk", "set_k"]:
            if aux in self.engine.interfaces:
                headers_set.add(f'#include <c/functions/{aux}.h>')
                headers_set.add(f'#include <simd_ext/scalar/functions/scalar_{aux}.h>')

        lines.extend(sorted(list(headers_set)))
        lines.append("")
        lines.append('#include <catch2/catch_test_macros.hpp>')
        lines.append('#include <catch2/catch_get_random_seed.hpp>')
        lines.append("")
        return lines

    def _render_single_test_func(self, dialect_name: str, func_name: str, dt_name: str, lmul_suffix: str, mkind: str = "", lmul: int = 0) -> List[str]:
        adapter = CDialectAdapter()

        func_spec = self.engine.specs["functions"].get(func_name, {})
        proto_map = self.engine._get_prototype_mapping(func_name)
        components = proto_map.get("components", {})

        dt_parts = [dt.strip() for dt in dt_name.split(",")]
        dt1_raw = dt_parts[0]
        dt2_raw = dt_parts[1] if len(dt_parts) > 1 else dt1_raw

        dt_cstd = f"{dt1_raw}_t"
        tag = f"{mkind}_{lmul_suffix}" if mkind else lmul_suffix
        lmul_mult = f" * {lmul}" if lmul > 0 else (f" / {-lmul}" if lmul < 0 else "")
        dt_clean = dt_name.replace(',', '_')
        func_decl = f"static void test_mipp_c_{func_name}_{dt_clean}_{tag}()"

        proto_ref = self.engine.interfaces.get(func_name, {}).get("proto_ref", "")
        func_spec = self.engine.specs["functions"].get(func_name, {})
        is_1arg = "1arg" in proto_ref or "2args_ptr_reg" in proto_ref or "2args_reg_val" in proto_ref or "2args_msk_val" in proto_ref
        is_3arg = "3args" in proto_ref
        size_var = f"MIPP_N_{dt1_raw.upper()}{lmul_mult}"
        size_out_var = f"MIPP_N_{dt2_raw.upper()}{lmul_mult}"

        body_lines = [func_decl, "{", "\tstd::mt19937 seed(Catch::getSeed());", "\tfor (unsigned n = 0; n < get_n_iter(); n++)", "\t{"]
        
        body_lines.append(f"\t\t[[maybe_unused]] {dt_cstd} inputs1[{size_var}];")
        if not is_1arg:
            body_lines.append(f"\t\t[[maybe_unused]] {dt_cstd} inputs2[{size_var}];")
        if is_3arg:
            body_lines.append(f"\t\t[[maybe_unused]] {dt_cstd} inputs3[{size_var}];")

        args_info = self.engine.get_proto_args_info(func_name)
        n_masks = self.engine.get_required_mask_count(func_name)
        has_mask_var = n_masks >= 1 or mkind in ("mask", "maskz", "masks") or any(arg.get("fixeddatatype") in ("int32", "i32") for arg in args_info)

        if has_mask_var:
            body_lines.append(f"\t\t[[maybe_unused]] int32_t inputs_m[{size_var}];")
            if n_masks >= 2:
                body_lines.append(f"\t\t[[maybe_unused]] int32_t inputs_m2[{size_var}];")
        if mkind == "masks":
            body_lines.append(f"\t\t[[maybe_unused]] {dt_cstd} inputs_src[{size_var}];")

        body_lines.append("")
        body_lines.append(f"\t\tfor (size_t i = 0; i < {size_var}; i++)")
        body_lines.append("\t\t{")

        # Fill inputs
        body_lines.extend(self.engine.domain_resolver.render_input_filling(func_spec, "inputs1", dialect="c", dt_cstd=dt_cstd, lmul_suffix=lmul_suffix))
        if not is_1arg:
            body_lines.extend(self.engine.domain_resolver.render_input_filling(func_spec, "inputs2", dialect="c", dt_cstd=dt_cstd, lmul_suffix=lmul_suffix))
        if is_3arg:
            body_lines.extend(self.engine.domain_resolver.render_input_filling(func_spec, "inputs3", dialect="c", dt_cstd=dt_cstd, lmul_suffix=lmul_suffix))
        if has_mask_var:
            body_lines.append(f"\t\t\t{self.engine.domain_resolver.render_mask_filling(func_spec, 'inputs_m')}")
            if n_masks >= 2:
                body_lines.append(f"\t\t\t{self.engine.domain_resolver.render_mask_filling(func_spec, 'inputs_m2')}")
        if mkind == "masks":
            body_lines.extend(self.engine.domain_resolver.render_input_filling(func_spec, "inputs_src", dialect="c", dt_cstd=dt_cstd, lmul_suffix=lmul_suffix))

        body_lines.append("\t\t}")
        body_lines.append("")

        # Loads
        load_fn = adapter.format_load_func_name(dt1_raw, lmul_suffix)
        load_fn_scalar = adapter.format_scalar_load_func_name(dt1_raw, lmul_suffix)
        reg_type1 = adapter.format_reg_type(dt1_raw, lmul_suffix)
        scalar_reg_type1 = adapter.format_scalar_reg_type(dt1_raw, lmul_suffix)

        body_lines.append(f"\t\t[[maybe_unused]] {reg_type1} r1 = {load_fn}(inputs1);")
        body_lines.append(f"\t\t[[maybe_unused]] {scalar_reg_type1} s1 = {load_fn_scalar}(inputs1);")
        if not is_1arg:
            body_lines.append(f"\t\t[[maybe_unused]] {reg_type1} r2 = {load_fn}(inputs2);")
            body_lines.append(f"\t\t[[maybe_unused]] {scalar_reg_type1} s2 = {load_fn_scalar}(inputs2);")
        if is_3arg:
            body_lines.append(f"\t\t[[maybe_unused]] {reg_type1} r3 = {load_fn}(inputs3);")
            body_lines.append(f"\t\t[[maybe_unused]] {scalar_reg_type1} s3 = {load_fn_scalar}(inputs3);")

        if has_mask_var:
            set_k_fn = adapter.format_set_k_func_name(dt1_raw, lmul_suffix)
            set_k_fn_scalar = adapter.format_scalar_set_k_func_name(dt1_raw, lmul_suffix)
            msk_type = adapter.format_msk_type(dt1_raw, lmul_suffix)
            scalar_msk_type = adapter.format_scalar_msk_type(dt1_raw, lmul_suffix)
            body_lines.append(f"\t\t[[maybe_unused]] {msk_type} m1 = {set_k_fn}(inputs_m);")
            body_lines.append(f"\t\t[[maybe_unused]] {scalar_msk_type} sm1 = {set_k_fn_scalar}(inputs_m);")
            if n_masks >= 2:
                body_lines.append(f"\t\t[[maybe_unused]] {msk_type} m2 = {set_k_fn}(inputs_m2);")
                body_lines.append(f"\t\t[[maybe_unused]] {scalar_msk_type} sm2 = {set_k_fn_scalar}(inputs_m2);")
        if mkind == "masks":
            body_lines.append(f"\t\t[[maybe_unused]] {reg_type1} rsrc = {load_fn}(inputs_src);")
            body_lines.append(f"\t\t[[maybe_unused]] {scalar_reg_type1} ssrc = {load_fn_scalar}(inputs_src);")

        body_lines.append("")

        dt_func_ext = f"{dt1_raw}_{dt2_raw}" if len(dt_parts) == 2 else dt1_raw
        ret_fn_r = adapter.format_func_name(func_name, dt_func_ext, lmul_suffix, mkind=mkind)
        ret_fn_s = adapter.format_scalar_func_name(func_name, dt_func_ext, lmul_suffix, mkind=mkind)
        proto_spec = self.engine.protos.get(proto_ref, {})
        ret_type_kind = proto_spec.get("ret", {}).get("type")
        is_val_ret = ret_type_kind == "val"
        is_msk_ret = ret_type_kind == "msk"

        if is_msk_ret:
            ret_type_r = adapter.format_msk_type(dt2_raw, lmul_suffix)
            ret_type_s = adapter.format_scalar_msk_type(dt2_raw, lmul_suffix)
        else:
            ret_type_r = adapter.format_reg_type(dt2_raw, lmul_suffix)
            ret_type_s = adapter.format_scalar_reg_type(dt2_raw, lmul_suffix)

        op_args_r = self.engine._build_op_call_args(func_name, mkind, is_scalar=False)
        op_args_s = self.engine._build_op_call_args(func_name, mkind, is_scalar=True)

        is_loop = self.engine.func_templates.get("prototypes", {}).get(proto_ref, {}).get("is_loop", True) and not is_val_ret
        if not is_loop:
            ret_type_r = f"{dt2_raw}_t"
            ret_type_s = f"{dt2_raw}_t"

        is_void_ret = proto_ref.startswith("ret_void")
        if is_void_ret:
            body_lines.append(f"\t\t{dt_cstd} res_r[{size_out_var}];")
            body_lines.append(f"\t\t{dt_cstd} res_s[{size_out_var}];")
            init_src = "inputs_src" if mkind == "masks" else "inputs1"
            body_lines.append(f"\t\tfor (size_t i = 0; i < {size_out_var}; i++)")
            body_lines.append("\t\t{")
            body_lines.append(f"\t\t\tres_r[i] = {init_src}[i];")
            body_lines.append(f"\t\t\tres_s[i] = {init_src}[i];")
            body_lines.append("\t\t}")
            body_lines.append(f"\t\t{ret_fn_r}({', '.join(op_args_r)});")
            body_lines.append(f"\t\t{ret_fn_s}({', '.join(op_args_s)});")
        else:
            body_lines.append(f"\t\t{ret_type_r} rres = {ret_fn_r}({', '.join(op_args_r)});")
            body_lines.append(f"\t\t{ret_type_s} sres = {ret_fn_s}({', '.join(op_args_s)});")
        body_lines.append("")

        overflow_check = func_spec.get("overflow_check")
        comp_type = func_spec.get("comparison", "exact")
        has_tolerance = "tolerance" in func_spec or comp_type == "tolerance"
        nan_inf_skip = func_spec.get("nan_inf_skip", False)

        if is_loop:
            body_lines.append(f"\t\tfor (unsigned i = 0; i < {size_out_var}; i++)")
            body_lines.append("\t\t{")
            if is_msk_ret:
                get_fn_r = adapter.format_get_k_func_name(dt2_raw, lmul_suffix)
                get_fn_s = adapter.format_scalar_get_k_func_name(dt2_raw, lmul_suffix)
            else:
                get_fn_r = adapter.format_get_func_name(dt2_raw, lmul_suffix)
                get_fn_s = adapter.format_scalar_get_func_name(dt2_raw, lmul_suffix)

            def get_assert_statements(r_expr: str, s_expr: str, indent: str = "\t\t\t") -> List[str]:
                res = []
                if nan_inf_skip:
                    res.append(f"{indent}if (std::isnan({r_expr}) || std::isnan({s_expr})) continue;")
                    res.append(f"{indent}if (std::isinf({r_expr}) || std::isinf({s_expr})) continue;")

                if comp_type == "bitwise":
                    tpl = self.engine.component_templates.get("assertions", {}).get("as_bitwise_eq_c", [])
                    raw_lines = self.engine.render_template(tpl, r_get=r_expr, s_get=s_expr)
                    res.extend([f"{indent}{l}" for l in raw_lines])
                elif comp_type in ("logical", "mask") or is_msk_ret or func_name.endswith("_k"):
                    tpl = self.engine.component_templates.get("assertions", {}).get("as_logical_eq_c", [])
                    raw_lines = self.engine.render_template(tpl, r_get=r_expr, s_get=s_expr)
                    res.extend([f"{indent}{l}" for l in raw_lines])
                elif has_tolerance and (dt2_raw in ("float32", "float64") or dt1_raw in ("float32", "float64")):
                    tol_expr = self.engine.resolve_tolerance_expr(func_name, f"{dt2_raw}_t", ref_var=s_expr)
                    tpl = self.engine.component_templates.get("assertions", {}).get("as_tolerance_c", [])
                    raw_lines = self.engine.render_template(tpl, r_get=r_expr, s_get=s_expr, dt=f"{dt2_raw}_t", tol_expr=tol_expr)
                    res.extend([f"{indent}{l}" for l in raw_lines])
                else:
                    tpl = self.engine.component_templates.get("assertions", {}).get("as_strict_eq_c", [])
                    raw_lines = self.engine.render_template(tpl, r_get=r_expr, s_get=s_expr)
                    res.extend([f"{indent}{l}" for l in raw_lines])
                return res

            if overflow_check and not overflow_check.startswith("accumulate_"):
                val1_expr = f"{get_fn_r}(r1, i)"
                val2_expr = f"{get_fn_r}(r2, i)"
                body_lines.append(f"\t\t\tbool ov = ovf::will_{overflow_check}_overflow<{dt_cstd}>({val1_expr}, {val2_expr});")
                body_lines.append("\t\t\tif (ov)")
                body_lines.append("\t\t\t{")
                body_lines.append('\t\t\t\tINFO("Overflow occurred, skipping assert");')
                body_lines.append("\t\t\t}")
                body_lines.append("\t\t\telse")
                body_lines.append("\t\t\t{")
                r_expr = f"{get_fn_r}(rres, i)"
                s_expr = f"{get_fn_s}(sres, i)"
                body_lines.extend(get_assert_statements(r_expr, s_expr, indent="\t\t\t\t"))
                body_lines.append("\t\t\t}")
            else:
                if is_void_ret:
                    body_lines.extend(get_assert_statements("res_r[i]", "res_s[i]", indent="\t\t\t"))
                else:
                    r_expr = f"{get_fn_r}(rres, i)"
                    s_expr = f"{get_fn_s}(sres, i)"
                    body_lines.extend(get_assert_statements(r_expr, s_expr, indent="\t\t\t"))
            body_lines.append("\t\t}")
        else:
            if overflow_check and overflow_check.startswith("accumulate_"):
                kind = overflow_check.replace("accumulate_", "")
                tpl_key = f"as_c_reduction_{kind}_overflow_check"
                tpl = self.engine.component_templates.get("assertions", {}).get(tpl_key, [])
                mask_ptr = "inputs_m" if mkind in ("mask", "maskz", "masks") else "nullptr"
                is_maskz_bool = "true" if mkind == "maskz" else "false"
                inputs_src_ptr = "inputs_src" if mkind == "masks" else "nullptr"

                assert_lines = []
                if nan_inf_skip:
                    assert_lines.append("\t\tif (std::isnan(rres) || std::isnan(sres)) return;")
                    assert_lines.append("\t\tif (std::isinf(rres) || std::isinf(sres)) return;")

                if comp_type in ("logical", "mask") or func_name.endswith("_k") or is_msk_ret:
                    assert_lines.append("\t\tREQUIRE((!!rres) == (!!sres));")
                elif has_tolerance and dt1_raw in ("float32", "float64"):
                    tol_expr = self.engine.resolve_tolerance_expr(func_name, dt_cstd, ref_var="sres")
                    assert_lines.append(f"\t\tauto tol = {tol_expr};")
                    assert_lines.append(f"\t\tREQUIRE(abs_diff::abs_diff(rres - sres) <= tol);")
                else:
                    assert_lines.append("\t\tREQUIRE(rres == sres);")

                assert_str = "\n".join(assert_lines)

                for line in tpl:
                    if "{{assert_lines}}" in line:
                        body_lines.append(assert_str)
                    else:
                        formatted_line = (line.replace("{{dt}}", dt_cstd)
                                              .replace("{{size_var}}", size_var)
                                              .replace("{{mask_ptr}}", mask_ptr)
                                              .replace("{{is_maskz_bool}}", is_maskz_bool)
                                              .replace("{{inputs_src_ptr}}", inputs_src_ptr))
                        body_lines.append(f"\t\t{formatted_line}")
            else:
                if comp_type in ("logical", "mask") or func_name.endswith("_k") or is_msk_ret:
                    body_lines.append("\t\tREQUIRE((!!rres) == (!!sres));")
                elif has_tolerance and dt1_raw in ("float32", "float64"):
                    tol_expr = self.engine.resolve_tolerance_expr(func_name, dt_cstd, ref_var="sres")
                    body_lines.append(f"\t\tauto tol = {tol_expr};")
                    body_lines.append(f"\t\tREQUIRE(abs_diff::abs_diff(rres - sres) <= tol);")
                else:
                    body_lines.append("\t\tREQUIRE(rres == sres);")

        body_lines.append("\t}")
        body_lines.append("}")
        body_lines.append("")
        return body_lines

    def _render_test_case_section(self, dialect_name: str, func_name: str, lmul_suffix: str = "m1", mkind: str = "", lmul: int = 0) -> List[str]:
        lines = []
        mask_tag_str = f"({mkind})" if mkind else ""
        lines.append(f'TEST_CASE("{func_name} - c {lmul_suffix} {mask_tag_str}", "[{func_name}]")')
        lines.append("{")

        datatypes = self.engine._resolve_datatypes(func_name)
        tag = f"{mkind}_{lmul_suffix}" if mkind else lmul_suffix
        for dt in datatypes:
            dt_clean = str(dt).replace(",", "_")
            call_expr = f"test_mipp_c_{func_name}_{dt_clean}_{tag}();"

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


class TestsBuilderEngineCppBase:

    def __init__(self, engine: TestsBuilderEngine):
        self.engine = engine

    def render_cpp_test_case(self, dialect_name: str, func_name: str, supported_mkinds: List[str]) -> List[str]:
        lines = []
        func_prefix = "test_mipp_cpp" if dialect_name == "cpp" else "test_mipp_cpp_obj"
        mk_enum_map = {"unmasked": "mipp::U", "mask": "mipp::M", "maskz": "mipp::Z", "masks": "mipp::S"}
        mk_label_map = {"unmasked": "unmasked (U)", "mask": "mask (M)", "maskz": "maskz (Z)", "masks": "masks (S)"}

        datatypes = self.engine._resolve_datatypes(func_name)
        is_product = any("," in str(dt) for dt in datatypes)

        label_dialect = "cpp" if dialect_name == "cpp" else "obj"
        lines.append(f'TEST_CASE("{func_name} - {label_dialect} tests", "[{func_name}]")')
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
                    cpp_type = f"{self.engine._format_cpp_type(dt_src)}, {self.engine._format_cpp_type(dt_dst)}"
                else:
                    cpp_type = self.engine._format_cpp_type(dt)

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

    def _render_headers(self, dialect_name: str, func_name: str, N: int = 10) -> List[str]:
        lines = [
            "#include <exception>", "#include <algorithm>", "#include <numeric>",
            "#include <random>", "#include <cstdio>", "#include <cmath>",
            "#include <cstdlib>", "#include <cstring>",
            '#include "uniform.hpp"', '#include "overflow_helpers.hpp"', '#include "abs_diff.hpp"',
            "#ifndef N_ITER", f"#define N_ITER {N}", "#endif", ""
        ]
        headers_set = set()
        headers_set.add('#include <mipp_obj.hpp>' if dialect_name == "obj" else '#include <mipp.hpp>')
        headers_set.add('#include <simd_ext_cpp/scalar_cpp/scalar_cpp_common.hpp>')
        headers_set.add(f'#include <simd_ext_cpp/scalar_cpp/functions/scalar_cpp_{func_name}.hpp>')
        for aux in ["load", "get", "get_k", "toreg", "tomsk", "set_k"]:
            if aux in self.engine.interfaces:
                headers_set.add(f'#include <simd_ext_cpp/scalar_cpp/functions/scalar_cpp_{aux}.hpp>')
        dt_spec = self.engine.interfaces.get(func_name, {}).get("datatypes")
        is_conversion = dt_spec in ("all_datatypes_cart_prod", "all_datatypes_same_size", "all_datatypes_widenning")
        if dialect_name == "cpp" and is_conversion:
            headers_set.add('#include <simd_ext_cpp/scalar_cpp/functions/scalar_cpp_cvt.hpp>')
            headers_set.add('#include <simd_ext_cpp/scalar_cpp/functions/scalar_cpp_wcvt.hpp>')
            headers_set.add('#include <simd_ext_cpp/scalar_cpp/functions/scalar_cpp_cast.hpp>')
            headers_set.add('#include <simd_ext_cpp/scalar_cpp/functions/scalar_cpp_cast_k.hpp>')

        lines.extend(sorted(list(headers_set)))
        lines.append("")

        if dialect_name == "cpp" and is_conversion:
            lines.extend(self.engine.component_templates.get("assertions", {}).get("cvt_helpers_cpp", []))
            lines.append("")

        lines.append('#include <catch2/catch_test_macros.hpp>')
        lines.append('#include <catch2/catch_get_random_seed.hpp>')
        lines.append("")
        return lines


class TestsBuilderEngineCpp(TestsBuilderEngineCppBase):

    def build_test_file_content(self, func_name: str, lmul_suffix: str = "m1", mkind: str = "", lmul: int = 0, N: int = 10) -> str:
        lines = []
        lines.extend(self._render_headers("cpp", func_name, N=N))

        mask_support = self.engine.interfaces[func_name].get("mask_support", "all_mask")
        supported_mkinds = []
        for m in ["unmasked", "mask", "maskz", "masks"]:
            if m == "unmasked" or self.engine._is_mask_kind_supported(mask_support, m):
                supported_mkinds.append(m)

        n_args = self.engine._get_n_args(func_name)
        proto_ref = self.engine.interfaces.get(func_name, {}).get("proto_ref", "ret_reg_2args_reg")
        func_spec = self.engine.specs["functions"].get(func_name, {})
        datatypes = self.engine._resolve_datatypes(func_name)
        is_product = any("," in str(dt) for dt in datatypes)
        is_1arg = "1arg" in proto_ref or "2args_reg_val" in proto_ref
        is_3arg = "3args" in proto_ref

        if is_product:
            lines.append(f"template <mipp::MKIND MK = mipp::U, typename T_src = float, typename T_dst = double, int LMUL = 1>")
        else:
            lines.append(f"template <mipp::MKIND MK = mipp::U, typename T = double, int LMUL = 1>")
        lines.append(f"static void test_mipp_cpp_{func_name}()")
        lines.append("{")
        lines.append("\tstd::mt19937 seed(Catch::getSeed());")
        lines.append("\tfor (unsigned n = 0; n < get_n_iter(); n++)")
        lines.append("\t{")

        if is_product:
            lines.append("\t\tconstexpr size_t size = (LMUL > 0) ? (mipp::N<T_src>() * static_cast<size_t>(LMUL)) : (mipp::N<T_src>() / static_cast<size_t>(-LMUL));")
            lines.append("\t\tconstexpr size_t size_out = (LMUL > 0) ? (mipp::N<T_dst>() * static_cast<size_t>(LMUL)) : (mipp::N<T_dst>() / static_cast<size_t>(-LMUL));")
            lines.append("\t\tusing T [[maybe_unused]] = T_src;")
        else:
            lines.append("\t\tconstexpr size_t size = (LMUL > 0) ? (mipp::N<T>() * static_cast<size_t>(LMUL)) : (mipp::N<T>() / static_cast<size_t>(-LMUL));")

        is_reg_val = "2args_reg_val" in proto_ref or "2args_msk_val" in proto_ref

        lines.append("\t\tT inputs1[size];")
        if not is_1arg or is_reg_val:
            lines.append("\t\tT inputs2[size];")
        if is_3arg:
            body_lines_arg3 = "\t\tT inputs3[size];"
            lines.append(body_lines_arg3)

        lines.append("\t\t[[maybe_unused]] T inputs_src[size];")
        lines.append("\t\t[[maybe_unused]] int32_t inputs_m[size];")
        lines.append("\t\t[[maybe_unused]] int32_t inputs_m2[size];")
        lines.append("")

        lines.append("\t\tfor (size_t i = 0; i < size; i++)")
        lines.append("\t\t{")

        # Fill inputs
        lines.extend(self.engine.domain_resolver.render_input_filling(func_spec, "inputs1", dialect="cpp"))
        if not is_1arg or is_reg_val:
            lines.extend(self.engine.domain_resolver.render_input_filling(func_spec, "inputs2", dialect="cpp"))
        if is_3arg:
            lines.extend(self.engine.domain_resolver.render_input_filling(func_spec, "inputs3", dialect="cpp"))

        lines.append(f"\t\t\t{self.engine.domain_resolver.render_mask_filling(func_spec, 'inputs_m')}")
        lines.append(f"\t\t\t{self.engine.domain_resolver.render_mask_filling(func_spec, 'inputs_m2')}")
        lines.extend(self.engine.domain_resolver.render_input_filling(func_spec, "inputs_src", dialect="cpp"))
        lines.append("\t\t}")
        lines.append("")

        lines.append("\t\t[[maybe_unused]] auto r1 = mipp::load<T, LMUL>(inputs1);")
        lines.append("\t\t[[maybe_unused]] auto s1 = mipp::load<T, LMUL, mipp::ISA::SCALAR>(inputs1);")
        if not is_1arg or is_reg_val:
            lines.append("\t\t[[maybe_unused]] auto r2 = mipp::load<T, LMUL>(inputs2);")
            lines.append("\t\t[[maybe_unused]] auto s2 = mipp::load<T, LMUL, mipp::ISA::SCALAR>(inputs2);")
        if is_3arg:
            lines.append("\t\t[[maybe_unused]] auto r3 = mipp::load<T, LMUL>(inputs3);")
            lines.append("\t\t[[maybe_unused]] auto s3 = mipp::load<T, LMUL, mipp::ISA::SCALAR>(inputs3);")

        is_reg_val = "2args_reg_val" in proto_ref or "2args_msk_val" in proto_ref
        mk_enum_map = {"unmasked": "mipp::U", "mask": "mipp::M", "maskz": "mipp::Z", "masks": "mipp::S"}

        def format_op_call(mkind: str, is_scalar: bool = False) -> str:
            args = self.engine._build_op_call_args(func_name, mkind, is_scalar)
            fname = self.engine.interfaces.get(func_name, {}).get("cpp_name", func_name)

            call_args = ", ".join(args)
            isa_str = ", mipp::ISA::SCALAR" if is_scalar else ""

            if mkind == "maskz":
                return f"mipp::{fname}<mipp::Z, T, LMUL{isa_str}>({call_args})"
            elif mkind == "masks":
                return f"mipp::{fname}<mipp::S, T, LMUL{isa_str}>({call_args})"
            elif mkind == "mask":
                return f"mipp::{fname}<mipp::M, T, LMUL{isa_str}>({call_args})"
            
            dt_spec = self.engine.interfaces.get(func_name, {}).get("datatypes")
            is_conversion = dt_spec in ("all_datatypes_cart_prod", "all_datatypes_same_size", "all_datatypes_widenning")
            if is_conversion:
                return f"mipp::test_helpers::{fname}<T_dst>({call_args})"
            
            args_info = self.engine.get_proto_args_info(func_name)
            has_reg_or_msk = any(arg.get("type") in ("reg", "msk") for arg in args_info)
            if not has_reg_or_msk:
                return f"mipp::{fname}<T, LMUL{isa_str}>({call_args})"
            return f"mipp::{fname}({call_args})"

        is_void_ret = proto_ref.startswith("ret_void")
        if is_void_ret:
            lines.append("\t\tT res_r[size];")
            lines.append("\t\tT res_s[size];")
            init_src = "inputs_src" if mkind == "masks" else "inputs1"
            lines.append(f"\t\tfor (size_t i = 0; i < size; i++)")
            lines.append("\t\t{")
            lines.append(f"\t\t\tres_r[i] = {init_src}[i];")
            lines.append(f"\t\t\tres_s[i] = {init_src}[i];")
            lines.append("\t\t}")
            r_var = "res_r"
            s_var = "res_s"
        else:
            r_var = "rres"
            s_var = "sres"

        ret_prefix = "" if is_void_ret else "return "
        n_masks = self.engine.get_required_mask_count(func_name)

        lines.append(f"\t\t" + ("[&]() {" if is_void_ret else f"auto {r_var} = [&]() {{"))
        is_first_mk = True
        for mkind in supported_mkinds:
            mk_enum = mk_enum_map[mkind]
            keyword = "if constexpr" if is_first_mk else "else if constexpr"
            is_first_mk = False
            lines.append(f"\t\t\t{keyword} (MK == {mk_enum})")
            lines.append("\t\t\t{")
            if n_masks >= 2:
                lines.append("\t\t\t\tauto m1 = mipp::set_k<T, LMUL>(inputs_m);")
                lines.append("\t\t\t\tauto m2 = mipp::set_k<T, LMUL>(inputs_m2);")
            elif n_masks == 1 or mkind in ("mask", "maskz", "masks"):
                lines.append("\t\t\t\tauto m1 = mipp::set_k<T, LMUL>(inputs_m);")
            if mkind == "masks":
                lines.append("\t\t\t\tauto rsrc = mipp::load<T, LMUL>(inputs_src);")
            lines.append(f"\t\t\t\t{ret_prefix}{format_op_call(mkind, is_scalar=False)};")
            lines.append("\t\t\t}")
        lines.append("\t\t}();")
        lines.append("")

        lines.append(f"\t\t" + ("[&]() {" if is_void_ret else f"auto {s_var} = [&]() {{"))
        is_first_mk = True
        for mkind in supported_mkinds:
            mk_enum = mk_enum_map[mkind]
            keyword = "if constexpr" if is_first_mk else "else if constexpr"
            is_first_mk = False
            lines.append(f"\t\t\t{keyword} (MK == {mk_enum})")
            lines.append("\t\t\t{")
            if n_masks >= 2:
                lines.append("\t\t\t\tauto sm1 = mipp::set_k<T, LMUL, mipp::ISA::SCALAR>(inputs_m);")
                lines.append("\t\t\t\tauto sm2 = mipp::set_k<T, LMUL, mipp::ISA::SCALAR>(inputs_m2);")
            elif n_masks == 1 or mkind in ("mask", "maskz", "masks"):
                lines.append("\t\t\t\tauto sm1 = mipp::set_k<T, LMUL, mipp::ISA::SCALAR>(inputs_m);")
            if mkind == "masks":
                lines.append("\t\t\t\tauto ssrc = mipp::load<T, LMUL, mipp::ISA::SCALAR>(inputs_src);")
            lines.append(f"\t\t\t\t{ret_prefix}{format_op_call(mkind, is_scalar=True)};")
            lines.append("\t\t\t}")
        lines.append("\t\t}();")
        lines.append("")

        val_lines = self.engine.render_cpp_validation_block(func_name, proto_ref, is_product, r_var=r_var, s_var=s_var, dialect_name="cpp")
        lines.extend(self.engine.indent_lines(val_lines, 2))

        lines.append("\t}")
        lines.append("}")
        lines.append("")

        lines.extend(self.render_cpp_test_case("cpp", func_name, supported_mkinds))
        return "\n".join(lines)


class TestsBuilderEngineCppObj(TestsBuilderEngineCppBase):

    def build_test_file_content(self, func_name: str, lmul_suffix: str = "m1", mkind: str = "", lmul: int = 0, N: int = 10) -> str:
        lines = []
        lines.extend(self._render_headers("obj", func_name, N=N))

        supported_mkinds = ["unmasked"]

        n_args = self.engine._get_n_args(func_name)
        proto_ref = self.engine.interfaces.get(func_name, {}).get("proto_ref", "ret_reg_2args_reg")
        func_spec = self.engine.specs["functions"].get(func_name, {})
        datatypes = self.engine._resolve_datatypes(func_name)
        is_product = any("," in str(dt) for dt in datatypes)
        is_1arg = "1arg" in proto_ref or "2args_reg_val" in proto_ref or "2args_msk_val" in proto_ref
        is_3arg = "3args" in proto_ref
        is_reg_val = "2args_reg_val" in proto_ref or "2args_msk_val" in proto_ref

        lines.append(f"template <mipp::MKIND MK = mipp::U, typename T = double, int LMUL = 1>")
        lines.append(f"static void test_mipp_cpp_obj_{func_name}()")
        lines.append("{")
        lines.append("\tstd::mt19937 seed(Catch::getSeed());")
        lines.append("\tfor (unsigned n = 0; n < get_n_iter(); n++)")
        lines.append("\t{")

        lines.append("\t\tconstexpr size_t size = (LMUL > 0) ? (mipp::N<T>() * static_cast<size_t>(LMUL)) : (mipp::N<T>() / static_cast<size_t>(-LMUL));")
        lines.append("\t\tT inputs1[size];")
        if not is_1arg:
            lines.append("\t\tT inputs2[size];")
        if is_3arg:
            lines.append("\t\tT inputs3[size];")

        lines.append("\t\t[[maybe_unused]] T inputs_src[size];")
        lines.append("\t\t[[maybe_unused]] int32_t inputs_m[size];")
        lines.append("")

        lines.append("\t\tfor (size_t i = 0; i < size; i++)")
        lines.append("\t\t{")

        lines.extend(self.engine.domain_resolver.render_input_filling(func_spec, "inputs1", dialect="obj"))
        if not is_1arg:
            lines.extend(self.engine.domain_resolver.render_input_filling(func_spec, "inputs2", dialect="obj"))
        if is_3arg:
            lines.extend(self.engine.domain_resolver.render_input_filling(func_spec, "inputs3", dialect="obj"))

        lines.append(f"\t\t\t{self.engine.domain_resolver.render_mask_filling(func_spec, 'inputs_m')}")
        lines.extend(self.engine.domain_resolver.render_input_filling(func_spec, "inputs_src", dialect="obj"))
        lines.append("\t\t}")
        lines.append("")

        lines.append("\t\tmipp::Rvd<T, LMUL> r1(&inputs1[0]);")
        lines.append("\t\tauto s1 = mipp::load<T, LMUL, mipp::ISA::SCALAR>(inputs1);")
        if not is_1arg:
            lines.append("\t\tmipp::Rvd<T, LMUL> r2(&inputs2[0]);")
            lines.append("\t\tauto s2 = mipp::load<T, LMUL, mipp::ISA::SCALAR>(inputs2);")
        if is_3arg:
            lines.append("\t\tmipp::Rvd<T, LMUL> r3(&inputs3[0]);")
            lines.append("\t\tauto s3 = mipp::load<T, LMUL, mipp::ISA::SCALAR>(inputs3);")

        adapter = CppObjDialectAdapter()
        if is_reg_val:
            op_args_r = ["r1", "inputs2[0]"]
            op_args_s = ["s1", "inputs2[0]"]
        else:
            op_args_r = ["r1"] if is_1arg else (["r1", "r2", "r3"] if is_3arg else ["r1", "r2"])
            op_args_s = ["s1"] if is_1arg else (["s1", "s2", "s3"] if is_3arg else ["s1", "s2"])

        call_r = adapter.format_func_call(func_name, "T", ", ".join(op_args_r))
        call_s = f"mipp::{func_name}({', '.join(op_args_s)})"

        r_var = "rres"
        s_var = "sres"

        lines.append(f"\t\tauto {r_var} = [&]() {{")
        lines.append("\t\t\tif constexpr (MK == mipp::U)")
        lines.append("\t\t\t{")
        lines.append(f"\t\t\t\treturn {call_r};")
        lines.append("\t\t\t}")
        lines.append("\t\t}();")
        lines.append("")

        lines.append(f"\t\tauto {s_var} = [&]() {{")
        lines.append("\t\t\tif constexpr (MK == mipp::U)")
        lines.append("\t\t\t{")
        lines.append(f"\t\t\t\treturn {call_s};")
        lines.append("\t\t\t}")
        lines.append("\t\t}();")
        lines.append("")

        val_lines = self.engine.render_cpp_validation_block(func_name, proto_ref, is_product, r_var=r_var, s_var=s_var, dialect_name="obj")
        lines.extend(self.engine.indent_lines(val_lines, 2))

        lines.append("\t}")
        lines.append("}")
        lines.append("")

        lines.extend(self.render_cpp_test_case("obj", func_name, supported_mkinds))
        return "\n".join(lines)
