"""
Declarative Test Generation Engine for MIPP.
Consumes MIPP registries and JSON specs to build complete Catch2 test files.
"""

import json

import os
import re
import sys
import jsonschema
import jinja2
from typing import Dict, List, Any, Optional, Set

from .dialect_adapters import DialectAdapter, CppDialectAdapter, CDialectAdapter, CppObjDialectAdapter
from .domain_resolver import DomainResolver
from tools import DATATYPES_MAP
from include_gen import _match_category

# Auxiliary MIPP functions whose headers must always be included in generated test files.
_AUX_HEADERS = ["load", "get", "get_k", "toreg", "tomsk", "set_k"]

_RE_TEST_PLACEHOLDER = re.compile(r'%([\w]+)(?:<([^>]*)>)?(?:\(([^)]*)\))?%')

def resolve_test_placeholders(line: str, adapter: DialectAdapter) -> str:
    """Resolve %token<params>(args)% markers in a template line using the dialect adapter."""
    def _resolve(m: re.Match) -> str:
        token = m.group(1)
        params = [p.strip() for p in (m.group(2) or "").split(",") if p.strip()]
        arg = (m.group(3) or "").strip()
        dt   = params[0] if len(params) >= 1 else ""
        lmul = params[1] if len(params) >= 2 else ""
        dispatch = {
            "reg_type":      lambda: adapter.format_reg_type(dt, lmul),
            "msk_type":      lambda: adapter.format_msk_type(dt, lmul),
            "load":          lambda: adapter.format_load(dt, arg, lmul),
            "scalar_load":   lambda: adapter.format_scalar_load(dt, arg, lmul),
            "set_k":         lambda: adapter.format_set_k(dt, arg, lmul),
            "scalar_set_k":  lambda: adapter.format_scalar_set_k(dt, arg, lmul),
            "N":             lambda: adapter.format_N(dt),
        }
        fn = dispatch.get(token)
        return fn() if fn is not None else m.group(0)  # unknown token → unchanged
    return _RE_TEST_PLACEHOLDER.sub(_resolve, line)


class TestsBuilderEngine:

    def render_template(self, template_lines: List[str], adapter: DialectAdapter = None, **kwargs) -> List[str]:
        if not template_lines:
            return []
        template_str = "\n".join(template_lines)
        rendered = jinja2.Template(template_str).render(**kwargs)
        lines = rendered.split("\n")
        if adapter is not None:
            lines = [resolve_test_placeholders(line, adapter) for line in lines]
        return lines

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
        self.templates = self._load_and_validate("tests_templates.json", "templates_schema.json")
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
        spec_dt = self.specs.get("functions", {}).get(func_name, {}).get("datatypes")
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


    # --- Prototype classification helpers (from registry_protos.json) ---

    def proto_is_1arg(self, proto_ref: str) -> bool:
        """Detects whether the prototype is unary (1 input register).
        Also handles void-return store-style functions that take only one input register.
        """
        return (
            "1arg" in proto_ref
            or "2args_ptr_reg" in proto_ref
            or "2args_reg_val" in proto_ref
            or "2args_msk_val" in proto_ref
        )

    def proto_is_3arg(self, proto_ref: str) -> bool:
        """Detects whether the prototype is ternary (3 input registers)."""
        return "3args" in proto_ref

    def proto_is_reg_val(self, proto_ref: str) -> bool:
        """Detects whether the prototype takes a register + a scalar value."""
        return "2args_reg_val" in proto_ref or "2args_msk_val" in proto_ref

    def proto_is_void_ret(self, proto_ref: str) -> bool:
        """Detects whether the prototype has a void return type (store)."""
        return proto_ref.startswith("ret_void")

    def proto_is_msk_ret(self, proto_ref: str) -> bool:
        """Detects whether the prototype returns a mask."""
        return self.protos.get(proto_ref, {}).get("ret", {}).get("type") == "msk"

    def proto_is_val_ret(self, proto_ref: str) -> bool:
        """Detects whether the prototype returns a scalar value (val or i32 fixedtype).
        Returns False for vector register returns.
        """
        return self.protos.get(proto_ref, {}).get("ret", {}).get("type") == "val"

    def proto_is_loop(self, proto_ref: str) -> bool:
        """Infers is_loop from registry_protos.json.
        Returns False for scalar-returning prototypes (hadd, hmul, etc.).
        """
        return not self.proto_is_val_ret(proto_ref)

    # --- Shared rendering helpers ---

    def render_void_ret_init(self, dt_type: str, size_var: str, init_src: str,
                             indent: str = "\t\t") -> List[str]:
        """Generates the declaration and initialization of res_r/res_s for void-ret functions."""
        return [
            f"{indent}{dt_type} res_r[{size_var}];",
            f"{indent}{dt_type} res_s[{size_var}];",
            f"{indent}for (size_t i = 0; i < {size_var}; i++)",
            f"{indent}{{",
            f"{indent}\tres_r[i] = {init_src}[i];",
            f"{indent}\tres_s[i] = {init_src}[i];",
            f"{indent}}}",
        ]

    def render_skip_condition(self, func_name: str, ref_var: str,
                              indent: str = "\t\t\t",
                              dt_cstd: Optional[str] = None) -> List[str]:
        """Generates a conditional skip block for problematic values.
        All default values are read from tests_specs.json["default"]["skip_condition"].

        If dt_cstd is provided -> C dialect (concrete type, no T or if constexpr).
        Otherwise -> C++ dialect (generic T, if constexpr).
        """
        default_spec = self.specs.get("default", {})
        func_spec = self.specs["functions"].get(func_name, {})
        skip = func_spec.get("skip_condition", default_spec.get("skip_condition"))
        if not skip or not isinstance(skip, dict):
            return []
        skip_type = skip.get("type")
        if skip_type == "fractional_part":
            value = skip["value"]
            tol = skip["tol"]
            if dt_cstd is not None:
                # C dialect: only generate for float32/float64
                if dt_cstd not in ("float32_t", "float64_t"):
                    return []
                return [
                    f"{indent}{{",
                    f"{indent}\t{dt_cstd} frac = (fabs)(({dt_cstd})({ref_var}) - (round)(({dt_cstd})({ref_var})));",
                    f"{indent}\tif ((fabs)(frac - ({dt_cstd})({value})) < ({dt_cstd})({tol})) continue;",
                    f"{indent}}}",
                ]
            else:
                # C++ dialect: generic via if constexpr
                return [
                    f"{indent}if constexpr (std::is_floating_point_v<T>)",
                    f"{indent}{{",
                    f"{indent}\tauto frac = std::abs({ref_var} - std::round({ref_var}));",
                    f"{indent}\tif (std::abs(frac - static_cast<T>({value})) < static_cast<T>({tol})) continue;",
                    f"{indent}}}",
                ]
        return []

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
        """Indent each line by indent_level tabs.

        Preprocessor directives (#if, #elif, #else, #endif, …) are never
        indented — they must always start at column 0 in C/C++ output.
        """
        tabs = "\t" * indent_level
        res = []
        for line in lines:
            if not line:
                res.append("")
            elif line.lstrip().startswith("#"):
                res.append(line.lstrip())
            else:
                res.append(f"{tabs}{line}")
        return res

    def _tpl(self, *path: str) -> List[str]:
        """Look up a template list by path keys.

        Replaces the verbose .get(key, {}).get(key, {}).get(key, []) chain.
        Returns [] if any key is missing or the leaf value is not a list.

        Example:
            self._tpl("assertions", "cpp_obj", "as_bitwise_eq")
        """
        node: Any = self.templates
        for key in path:
            if not isinstance(node, dict):
                return []
            node = node.get(key, {})
        return node if isinstance(node, list) else []

    def _format_cpp_type(self, dt_str: str) -> str:
        return CppDialectAdapter().cpp_type(dt_str)

    def resolve_tolerance_expr(self, func_name: str, dt_cpp: str, ref_var: str = "res2") -> str:
        """Returns an inline C++ expression for tolerance computation.
        Used internally by render_tolerance_declaration(). Does not handle by_define.
        """
        func_spec = self.specs["functions"].get(func_name, {})
        tol_spec = func_spec.get("tolerance")
        if not tol_spec:
            tol_spec = self.specs.get("default", {}).get("tolerance", {"type": "exact"})

        # If exact type, no tolerance needed (should not be called in this case)
        if isinstance(tol_spec, dict) and tol_spec.get("type") == "exact":
            return "(T)0"

        if isinstance(tol_spec, dict) and "by_datatype" in tol_spec:
            by_dt = tol_spec["by_datatype"]
            default_spec = tol_spec.get("default", {"type": "relative_percent", "value": 0.001})
            f32_spec = by_dt.get("float32", default_spec)
            f64_spec = by_dt.get("float64", default_spec)

            def _make_expr(spec: dict, cast_type: str, c_cast: str) -> str:
                ttype = spec.get("type", "relative_percent")
                if ttype == "relative_percent":
                    val = spec.get("value", 0.001)
                    return f"({cast_type})(abs_diff::abs_diff({ref_var}) * ({c_cast}){val})"
                elif ttype == "hybrid":
                    abs_val = spec.get("abs_value", 1e-6 if c_cast == "float" else 1e-12)
                    rel_val = spec.get("rel_value", 1e-6 if c_cast == "float" else 1e-12)
                    return f"({cast_type})(({c_cast}){abs_val} + abs_diff::abs_diff({ref_var}) * ({c_cast}){rel_val})"
                else:
                    val = spec.get("value", 0.001)
                    return f"({cast_type})(({c_cast}){val})"

            f32_expr = _make_expr(f32_spec, dt_cpp, "float")
            f64_expr = _make_expr(f64_spec, dt_cpp, "double")

            if dt_cpp in ("float32_t", "float"):
                return f32_expr
            elif dt_cpp in ("float64_t", "double"):
                return f64_expr
            else:
                return f"(std::is_same_v<{dt_cpp}, float> ? {f32_expr} : {f64_expr})"
        else:
            ttype = tol_spec.get("type", "relative_percent")
            if ttype == "hybrid":
                abs_val = tol_spec.get("abs_value", 1e-6)
                rel_val = tol_spec.get("rel_value", 1e-6)
                f32_expr = f"({dt_cpp})((float){abs_val} + abs_diff::abs_diff({ref_var}) * (float){rel_val})"
                f64_expr = f"({dt_cpp})((double){abs_val} + abs_diff::abs_diff({ref_var}) * (double){rel_val})"
            else:
                val = tol_spec.get("value", 0.001)
                f32_expr = (f"({dt_cpp})(abs_diff::abs_diff({ref_var}) * (float){val})"
                            if ttype == "relative_percent" else f"({dt_cpp})((float){val})")
                f64_expr = (f"({dt_cpp})(abs_diff::abs_diff({ref_var}) * (double){val})"
                            if ttype == "relative_percent" else f"({dt_cpp})((double){val})")
            if dt_cpp in ("float32_t", "float"):
                return f32_expr
            elif dt_cpp in ("float64_t", "double"):
                return f64_expr
            else:
                return f"(std::is_same_v<{dt_cpp}, float> ? {f32_expr} : {f64_expr})"

    def render_tolerance_declaration(self, func_name: str, dt_cpp: str, ref_var: str,
                                     tol_var: str = "tol",
                                     indent: str = "\t\t\t") -> List[str]:
        """Generates the lines declaring the tolerance variable.

        Handles the 'by_define' case by emitting #if/#elif/#else/#endif blocks.
        For simple cases, emits a single inline expression.
        """
        func_spec = self.specs["functions"].get(func_name, {})
        default_tol = self.specs.get("default", {}).get("tolerance", {"type": "exact"})
        tol_spec = func_spec.get("tolerance", default_tol)

        # by_define case: emit #if defined(...) blocks
        if isinstance(tol_spec, dict) and "by_define" in tol_spec:
            by_define = tol_spec["by_define"]
            fallback_spec = tol_spec.get("default", default_tol)
            lines: List[str] = []
            first = True
            for define_key, define_spec in by_define.items():
                if first:
                    lines.append(f"#if defined({define_key})")
                    first = False
                else:
                    lines.append(f"#elif defined({define_key})")
                expr = self._tol_spec_to_expr(define_spec, dt_cpp, ref_var)
                lines.append(f"{indent}auto {tol_var} = {expr};")
            lines.append("#else")
            fallback_expr = self._tol_spec_to_expr(fallback_spec, dt_cpp, ref_var)
            lines.append(f"{indent}auto {tol_var} = {fallback_expr};")
            lines.append("#endif")
            return lines

        # Cas standard : expression simple
        expr = self.resolve_tolerance_expr(func_name, dt_cpp, ref_var)
        return [f"{indent}auto {tol_var} = {expr};"]

    def _tol_spec_to_expr(self, spec: dict, dt_cpp: str, ref_var: str) -> str:
        """Converts a tolerance spec dict into an inline C++ expression."""
        if not spec or spec.get("type") == "exact":
            return "(T)0"
        ttype = spec.get("type", "relative_percent")
        if ttype == "hybrid":
            abs_val_f32 = spec.get("abs_value", 1e-6)
            rel_val_f32 = spec.get("rel_value", 1e-6)
            abs_val_f64 = spec.get("abs_value", 1e-12)
            rel_val_f64 = spec.get("rel_value", 1e-12)
            if dt_cpp in ("float32_t", "float"):
                return f"({dt_cpp})((float){abs_val_f32} + abs_diff::abs_diff({ref_var}) * (float){rel_val_f32})"
            elif dt_cpp in ("float64_t", "double"):
                return f"({dt_cpp})((double){abs_val_f64} + abs_diff::abs_diff({ref_var}) * (double){rel_val_f64})"
            else:
                return (f"(std::is_same_v<{dt_cpp}, float> "
                        f"? ({dt_cpp})((float){abs_val_f32} + abs_diff::abs_diff({ref_var}) * (float){rel_val_f32}) "
                        f": ({dt_cpp})((double){abs_val_f64} + abs_diff::abs_diff({ref_var}) * (double){rel_val_f64}))")
        elif ttype == "relative_percent":
            val = spec.get("value", 0.001)
            if dt_cpp in ("float32_t", "float"):
                return f"({dt_cpp})(abs_diff::abs_diff({ref_var}) * (float){val})"
            elif dt_cpp in ("float64_t", "double"):
                return f"({dt_cpp})(abs_diff::abs_diff({ref_var}) * (double){val})"
            else:
                return (f"(std::is_same_v<{dt_cpp}, float> "
                        f"? ({dt_cpp})(abs_diff::abs_diff({ref_var}) * (float){val}) "
                        f": ({dt_cpp})(abs_diff::abs_diff({ref_var}) * (double){val}))")
        else:
            val = spec.get("value", 0.001)
            if dt_cpp in ("float32_t", "float"):
                return f"({dt_cpp})((float){val})"
            elif dt_cpp in ("float64_t", "double"):
                return f"({dt_cpp})((double){val})"
            else:
                return f"(std::is_same_v<{dt_cpp}, float> ? ({dt_cpp})((float){val}) : ({dt_cpp})((double){val}))"

    def render_cpp_validation_block(self, func_name: str, proto_ref: str, is_product: bool = False, r_var: str = "rres", s_var: str = "sres", adapter: DialectAdapter = None) -> List[str]:
        func_spec = self.specs.get("functions", {}).get(func_name, {})
        default_spec = self.specs.get("default", {})
        comp_type = func_spec.get("comparison", default_spec.get("comparison", "exact"))
        has_tolerance = (comp_type == "tolerance") or ("tolerance" in func_spec)
        is_loop = self.proto_is_loop(proto_ref)
        # Special cases: some val-ret protos iterate but are treated as scalar access
        if func_name in ("get", "get_k", "getfirst") or proto_ref in ("ret_val_2args_reg_val", "ret_val_2args_msk_val"):
            is_loop = False

        if proto_ref.startswith("ret_void"):
            r_get = f"{r_var}[i]"
            s_get = f"{s_var}[i]"
        else:
            r_get = adapter.format_get(r_var, "i", "", "")
            s_get = adapter.format_scalar_get(s_var, "i", "", "")

        overflow_check = func_spec.get("overflow_check")

        loop_limit = "size_out" if is_product else "size"

        nan_inf_skip = func_spec.get("nan_inf_skip", False)
        nan_inf_skip_lines = "if (std::isnan(diff) || std::isinf(diff)) continue;" if nan_inf_skip else ""
        # skip_condition: lignes de skip conditionnel (ex: fractional_part pour round)
        skip_cond_lines = self.render_skip_condition(func_name, s_get, indent="\t")

        val_lines = []
        if isinstance(comp_type, dict) and any(v == "bitwise" for v in comp_type.get("by_datatype", {}).values()):
            val_lines.append("if constexpr (std::is_floating_point_v<T>)")
            val_lines.append("{")
            tpl = self._tpl("assertions", "cpp_obj", "as_bitwise_eq")
            bw_lines = self.render_template(tpl, r_get=r_get, s_get=s_get, loop_limit=loop_limit)
            val_lines.extend([f"\t{l}" if l else "" for l in bw_lines])
            val_lines.append("}")
            val_lines.append("else")
            val_lines.append("{")
            val_lines.append(f"\tfor (size_t i = 0; i < {loop_limit}; i++)")
            val_lines.append("\t{")
            val_lines.append(f"\t\tREQUIRE({r_get} == {s_get});")
            val_lines.append("\t}")
            val_lines.append("}")
        elif not is_loop:
            if comp_type == "logical":
                tpl = self._tpl("assertions", "cpp_obj", "as_logical_scalar_eq")
                for line in tpl:
                    val_lines.append(line.replace("{{r_var}}", r_var).replace("{{s_var}}", s_var))
            elif has_tolerance:
                # Inject tolerance declaration (may be multi-line with #if/#endif)
                tol_lines = self.render_tolerance_declaration(func_name, "T", ref_var=s_var, indent="\t")
                val_lines.extend(tol_lines)
                val_lines.append("if constexpr (std::is_floating_point_v<T>)")
                val_lines.append("{")
                val_lines.append(f"\tT diff = abs_diff::abs_diff({r_var}, {s_var});")
                if nan_inf_skip_lines:
                    val_lines.append(f"\t{nan_inf_skip_lines}")
                val_lines.append("\tREQUIRE(diff <= tol);")
                val_lines.append("}")
                val_lines.append("else")
                val_lines.append("{")
                val_lines.append(f"\tREQUIRE({r_var} == {s_var});")
                val_lines.append("}") 
            else:
                tpl = self._tpl("assertions", "cpp_obj", "as_strict_scalar_eq")
                val_lines.extend(self.render_template(tpl, r_var=r_var, s_var=s_var))
        elif has_tolerance:
            # For the by_define case, inject #if/#endif before the loop using s_var (full register).
            # For the standard case, the declaration is inline inside the loop with s_get.
            func_tol_spec = self.specs.get("functions", {}).get(func_name, {}).get("tolerance", {})
            has_by_define = isinstance(func_tol_spec, dict) and "by_define" in func_tol_spec
            if has_by_define:
                # #if/#endif must be before the loop; use s_var as global ref
                tol_lines = self.render_tolerance_declaration(func_name, "T", ref_var=s_var, indent="\t")
                val_lines.extend(tol_lines)
            val_lines.append(f"for (size_t i = 0; i < {loop_limit}; i++)")
            val_lines.append("{")
            if skip_cond_lines:
                val_lines.extend(skip_cond_lines)
            val_lines.append("\tif constexpr (std::is_floating_point_v<T>)")
            val_lines.append("\t{")
            if not has_by_define:
                # Inline declaration inside the loop (standard case)
                tol_lines = self.render_tolerance_declaration(func_name, "T", ref_var=s_get, indent="\t\t")
                val_lines.extend(tol_lines)
            val_lines.append(f"\t\tT diff = abs_diff::abs_diff({r_get}, {s_get});")
            if nan_inf_skip_lines:
                val_lines.append(f"\t\t{nan_inf_skip_lines}")
            val_lines.append("\t\tREQUIRE(diff <= tol);")
            val_lines.append("\t}")
            val_lines.append("\telse")
            val_lines.append("\t{")
            val_lines.append(f"\t\tREQUIRE({r_get} == {s_get});")
            val_lines.append("\t}")
            val_lines.append("}") 
        elif comp_type == "bitwise":
            tpl = self._tpl("assertions", "cpp_obj", "as_bitwise_eq")
            val_lines.extend(self.render_template(tpl, r_get=r_get, s_get=s_get, loop_limit=loop_limit))
        elif comp_type == "logical" or func_name.endswith("_k") or "ret_msk" in proto_ref:
            tpl = self._tpl("assertions", "cpp_obj", "as_logical_eq")
            val_lines.extend(self.render_template(tpl, r_get=r_get, s_get=s_get, loop_limit=loop_limit))
        else:
            val_lines.append(f"for (size_t i = 0; i < {loop_limit}; i++)")
            val_lines.append("{")
            if skip_cond_lines:
                val_lines.extend(skip_cond_lines)
            val_lines.append(f"\tREQUIRE({r_get} == {s_get});")
            val_lines.append("}")

        if overflow_check and overflow_check.startswith("accumulate_"):
            lines = []
            kind = overflow_check.replace("accumulate_", "")
            tpl_key = "as_reduction_hadd_overflow" if kind == "add" else f"as_reduction_{kind}_overflow"
            tpl = self._tpl("assertions", "cpp_obj", tpl_key)
            for line in tpl:
                if "{{validation_block}}" in line:
                    lines.extend(self.indent_lines(val_lines, 1))
                else:
                    lines.append(line)
            return lines

        return val_lines

    def build_test_file_content(self, dialect_name: str, func_name: str, lmul_suffix: str = "m1", mkind: str = "", lmul: int = 0, N: int = 10) -> str:
        builder = self.get_builder(dialect_name)
        return builder.build_test_file_content(func_name, lmul_suffix=lmul_suffix, mkind=mkind, lmul=lmul, N=N)

    def format_cpp_op_call(self, func_name: str, mkind: str, is_scalar: bool = False) -> str:
        """Build a C++ template call expression with symbolic params (MK, T, LMUL).

        Used by TestsBuilderEngineCpp where T and LMUL are compile-time template
        parameters, not resolved Python values. Centralises all mipp:: namespace
        references for this dialect so dialect_adapters remain authoritative.
        """
        args = self._build_op_call_args(func_name, mkind, is_scalar)
        fname = self.interfaces.get(func_name, {}).get("cpp_name", func_name)
        call_args = ", ".join(args)
        isa_str = ", mipp::ISA::SCALAR" if is_scalar else ""

        # Masked variants: explicit MK template param
        mk_map = {"mask": "mipp::M", "maskz": "mipp::Z", "masks": "mipp::S"}
        if mkind in mk_map:
            mk_sym = mk_map[mkind]
            return f"mipp::{fname}<{mk_sym}, T, LMUL{isa_str}>({call_args})"

        # Conversion functions: test_helpers wrapper
        dt_spec = self.interfaces.get(func_name, {}).get("datatypes")
        is_conversion = dt_spec in ("all_datatypes_cart_prod", "all_datatypes_same_size", "all_datatypes_widenning")
        if is_conversion:
            return f"mipp::test_helpers::{fname}<T_dst>({call_args})"

        # Functions with no register/mask args (set, set0, set1…): explicit T, LMUL
        args_info = self.get_proto_args_info(func_name)
        has_reg_or_msk = any(arg.get("type") in ("reg", "msk") for arg in args_info)
        if not has_reg_or_msk:
            return f"mipp::{fname}<T, LMUL{isa_str}>({call_args})"

        # Default: plain call (T is deduced from arguments)
        return f"mipp::{fname}({call_args})"

    def render_c_validation_block(
        self,
        func_name: str,
        adapter: "CDialectAdapter",
        mkind: str,
        dt1_raw: str,
        dt2_raw: str,
        dt_cstd: str,
        lmul_suffix: str,
        is_loop: bool,
        is_void_ret: bool,
        is_msk_ret: bool,
        size_out_var: str,
        size_var: str,
        r_var: str = "rres",
        s_var: str = "sres",
    ) -> List[str]:
        """Generate assertion lines for the C dialect validation block.

        Symmetric to render_cpp_validation_block but uses CDialectAdapter
        accessor calls (mipp_get_*, mipp_scalar_get_*) and C-specific
        assertion templates. Called by TestsBuilderEngineC to avoid duplicating
        the bitwise/logical/tolerance/exact dispatch logic inline.
        """
        func_spec = self.specs.get("functions", {}).get(func_name, {})
        overflow_check = func_spec.get("overflow_check")
        comp_entry = func_spec.get("comparison", "exact")
        if isinstance(comp_entry, dict):
            dt_key = dt2_raw.split("_")[-1]
            comp_type = comp_entry.get("by_datatype", {}).get(dt_key, comp_entry.get("default", "exact"))
        else:
            comp_type = comp_entry
        has_tolerance = "tolerance" in func_spec or comp_type == "tolerance"
        nan_inf_skip = func_spec.get("nan_inf_skip", False)

        lines: List[str] = []

        if is_loop:
            lines.append(f"\t\tfor (unsigned i = 0; i < {size_out_var}; i++)")
            lines.append("\t\t{")

            if is_msk_ret:
                r_expr_fn = lambda reg: adapter.format_get_k(reg, "i", dt2_raw, lmul_suffix)
                s_expr_fn = lambda reg: adapter.format_scalar_get_k(reg, "i", dt2_raw, lmul_suffix)
            else:
                r_expr_fn = lambda reg: adapter.format_get(reg, "i", dt2_raw, lmul_suffix)
                s_expr_fn = lambda reg: adapter.format_scalar_get(reg, "i", dt2_raw, lmul_suffix)

            def _assert_stmts(r_expr: str, s_expr: str, indent: str = "\t\t\t") -> List[str]:
                res: List[str] = []
                if nan_inf_skip:
                    res.append(f"{indent}if (std::isnan({r_expr}) || std::isnan({s_expr})) continue;")
                    res.append(f"{indent}if (std::isinf({r_expr}) || std::isinf({s_expr})) continue;")
                res.extend(self.render_skip_condition(func_name, s_expr, indent, dt_cstd=f"{dt2_raw}_t"))

                if comp_type == "bitwise":
                    tpl = self._tpl("assertions", "c", "as_bitwise_eq")
                    res.extend([f"{indent}{l}" for l in self.render_template(tpl, r_get=r_expr, s_get=s_expr)])
                elif comp_type == "logical" or is_msk_ret or func_name.endswith("_k"):
                    tpl = self._tpl("assertions", "c", "as_logical_eq")
                    res.extend([f"{indent}{l}" for l in self.render_template(tpl, r_get=r_expr, s_get=s_expr)])
                elif has_tolerance and (dt2_raw in ("float32", "float64") or dt1_raw in ("float32", "float64")):
                    for tl in self.render_tolerance_declaration(func_name, f"{dt2_raw}_t", ref_var=s_expr, indent=indent):
                        res.append(tl)
                    res.append(f"{indent}REQUIRE(abs_diff::abs_diff(({dt2_raw}_t)({r_expr}) - ({dt2_raw}_t)({s_expr})) <= tol);")
                else:
                    tpl = self._tpl("assertions", "c", "as_strict_eq")
                    res.extend([f"{indent}{l}" for l in self.render_template(tpl, r_get=r_expr, s_get=s_expr)])
                return res

            if overflow_check and not overflow_check.startswith("accumulate_"):
                val1_expr = adapter.format_get("r1", "i", dt2_raw, lmul_suffix)
                val2_expr = adapter.format_get("r2", "i", dt2_raw, lmul_suffix)
                inner_lines = "\n".join(_assert_stmts(r_expr_fn(r_var), s_expr_fn(s_var), indent="\t\t\t\t"))
                tpl_shell = self._tpl("func_templates", "c", "overflow_check_shell")
                lines.extend(self.render_template(
                    tpl_shell,
                    overflow_check=overflow_check, dt=dt_cstd,
                    val1=val1_expr, val2=val2_expr, inner_lines=inner_lines,
                ))
            else:
                if is_void_ret:
                    lines.extend(_assert_stmts("res_r[i]", "res_s[i]", indent="\t\t\t"))
                else:
                    lines.extend(_assert_stmts(r_expr_fn(r_var), s_expr_fn(s_var), indent="\t\t\t"))
            lines.append("\t\t}")

        else:
            # Scalar / reduction path
            if overflow_check and overflow_check.startswith("accumulate_"):
                kind = overflow_check.replace("accumulate_", "")
                tpl_key = f"as_reduction_{kind}_overflow"
                tpl = self._tpl("assertions", "c", tpl_key)
                mask_ptr = "inputs_m" if mkind in ("mask", "maskz", "masks") else "nullptr"
                is_maskz_bool = "true" if mkind == "maskz" else "false"
                inputs_src_ptr = "inputs_src" if mkind == "masks" else "nullptr"

                assert_lines = self._c_scalar_assert_stmts(
                    func_name, r_var, s_var, comp_type, has_tolerance, is_msk_ret,
                    dt1_raw, dt_cstd, nan_inf_skip, indent="\t\t",
                )

                assert_str = "\n".join(assert_lines)
                for line in tpl:
                    if "{{assert_lines}}" in line:
                        lines.append(assert_str)
                    else:
                        formatted = (line.replace("{{dt}}", dt_cstd)
                                         .replace("{{size_var}}", size_var)
                                         .replace("{{mask_ptr}}", mask_ptr)
                                         .replace("{{is_maskz_bool}}", is_maskz_bool)
                                         .replace("{{inputs_src_ptr}}", inputs_src_ptr))
                        lines.append(f"\t\t{formatted}")
            else:
                lines.extend(self._c_scalar_assert_stmts(
                    func_name, r_var, s_var, comp_type, has_tolerance, is_msk_ret,
                    dt1_raw, dt_cstd, nan_inf_skip, indent="\t\t",
                ))

        return lines

    def _c_scalar_assert_stmts(
        self, func_name: str, r_var: str, s_var: str,
        comp_type: str, has_tolerance: bool, is_msk_ret: bool,
        dt1_raw: str, dt_cstd: str, nan_inf_skip: bool,
        indent: str = "\t\t",
    ) -> List[str]:
        """Generate scalar (non-loop) assertion lines for the C dialect.

        Shared between the simple scalar path and the accumulate-overflow path
        in render_c_validation_block.
        """
        lines: List[str] = []
        if nan_inf_skip:
            lines.append(f"{indent}if (std::isnan({r_var}) || std::isnan({s_var})) return;")
            lines.append(f"{indent}if (std::isinf({r_var}) || std::isinf({s_var})) return;")
        if comp_type == "logical" or func_name.endswith("_k") or is_msk_ret:
            lines.append(f"{indent}REQUIRE((!!"+r_var+f") == (!!" + s_var + "));")
        elif has_tolerance and dt1_raw in ("float32", "float64"):
            lines.extend(self.render_tolerance_declaration(func_name, dt_cstd, ref_var=s_var, indent=indent))
            lines.append(f"{indent}REQUIRE(abs_diff::abs_diff({r_var} - {s_var}) <= tol);")
        else:
            lines.append(f"{indent}REQUIRE({r_var} == {s_var});")
        return lines

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
        lines.extend(self._render_headers(func_name, N=N))

        datatypes = self.engine._resolve_datatypes(func_name)

        if lmul < 0:
            lines.append("#if defined(MIPP_LDIV_2)")

        for dt in datatypes:
            lines.extend(self._render_single_test_func(func_name, str(dt), lmul_suffix, mkind=mkind, lmul=lmul))

        lines.extend(self._render_test_case_section(func_name, lmul_suffix, mkind=mkind, lmul=lmul))

        if lmul < 0:
            lines.append("#endif // MIPP_LDIV_2")

        return "\n".join(lines)

    def _render_headers(self, func_name: str, N: int = 10) -> List[str]:
        func_spec = self.engine.specs["functions"].get(func_name, {})
        default_spec = self.engine.specs.get("default", {})
        extra_includes = func_spec.get("extra_includes", default_spec.get("extra_includes", []))

        tpl_fixed = self.engine.templates.get("headers", {}).get("all", {}).get("headers_fixed", [])
        lines = self.engine.render_template(tpl_fixed, N_ITER=str(N))
        headers_set = set()
        cat_func = _match_category(func_name)
        headers_set.add('#include <interfaces/c/common.h>')
        headers_set.add('#include <simd_ext/scalar/c/common.h>')
        headers_set.add(f'#include <interfaces/c/functions/{cat_func}/{func_name}.h>')
        headers_set.add(f'#include <simd_ext/scalar/c/functions/{cat_func}/{func_name}.h>')
        for aux in _AUX_HEADERS:
            if aux in self.engine.interfaces:
                cat_aux = _match_category(aux)
                headers_set.add(f'#include <interfaces/c/functions/{cat_aux}/{aux}.h>')
                headers_set.add(f'#include <simd_ext/scalar/c/functions/{cat_aux}/{aux}.h>')

        # extra_includes: split into known aux names (handled above) and raw strings (injected verbatim)
        extra_aux = [inc for inc in extra_includes if inc not in _AUX_HEADERS]
        for aux in extra_includes:
            if aux in _AUX_HEADERS:
                cat_aux = _match_category(aux)
                headers_set.add(f'#include <interfaces/c/functions/{cat_aux}/{aux}.h>')
                headers_set.add(f'#include <simd_ext/scalar/c/functions/{cat_aux}/{aux}.h>')

        lines.extend(sorted(list(headers_set)))
        lines.append("")
        # Inject any raw include strings (not auxiliary names)
        for inc in extra_aux:
            lines.append(inc)
        if extra_aux:
            lines.append("")
        lines.append('#include <catch2/catch_test_macros.hpp>')
        lines.append('#include <catch2/catch_get_random_seed.hpp>')
        lines.append("")
        return lines

    def _render_single_test_func(self, func_name: str, dt_name: str, lmul_suffix: str, mkind: str = "", lmul: int = 0) -> List[str]:
        adapter = CDialectAdapter()

        func_spec = self.engine.specs["functions"].get(func_name, {})

        dt_parts = [dt.strip() for dt in dt_name.split(",")]
        dt1_raw = dt_parts[0]
        dt2_raw = dt_parts[1] if len(dt_parts) > 1 else dt1_raw

        dt_cstd = f"{dt1_raw}_t"
        tag = f"{mkind}_{lmul_suffix}" if mkind else lmul_suffix
        lmul_mult = f" * {lmul}" if lmul > 0 else (f" / {-lmul}" if lmul < 0 else "")
        dt_clean = dt_name.replace(',', '_')
        func_decl = f"static void test_mipp_c_{func_name}_{dt_clean}_{tag}()"

        proto_ref = self.engine.interfaces.get(func_name, {}).get("proto_ref", "")
        is_1arg = self.engine.proto_is_1arg(proto_ref)
        is_3arg = self.engine.proto_is_3arg(proto_ref)
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
        body_lines.extend(self.engine.domain_resolver.render_input_filling(func_spec, "inputs1", dialect="c", dt_cstd=dt_cstd, lmul_suffix=lmul_suffix, mkind=mkind))
        if not is_1arg:
            body_lines.extend(self.engine.domain_resolver.render_input_filling(func_spec, "inputs2", dialect="c", dt_cstd=dt_cstd, lmul_suffix=lmul_suffix, mkind=mkind))
        if is_3arg:
            body_lines.extend(self.engine.domain_resolver.render_input_filling(func_spec, "inputs3", dialect="c", dt_cstd=dt_cstd, lmul_suffix=lmul_suffix, mkind=mkind))
        if has_mask_var:
            body_lines.extend(self.engine.domain_resolver.render_mask_filling(func_spec, "inputs_m", dialect="c", mkind=mkind))
            if n_masks >= 2:
                body_lines.extend(self.engine.domain_resolver.render_mask_filling(func_spec, "inputs_m2", dialect="c", mkind=mkind))
        if mkind == "masks":
            body_lines.extend(self.engine.domain_resolver.render_input_filling(func_spec, "inputs_src", dialect="c", dt_cstd=dt_cstd, lmul_suffix=lmul_suffix, mkind=mkind))

        body_lines.append("\t\t}")
        body_lines.append("")

        # Loads
        reg_type1 = adapter.format_reg_type(dt1_raw, lmul_suffix)
        scalar_reg_type1 = adapter.format_scalar_reg_type(dt1_raw, lmul_suffix)

        body_lines.append(f"\t\t[[maybe_unused]] {reg_type1} r1 = {adapter.format_load(dt1_raw, 'inputs1', lmul_suffix)};")
        body_lines.append(f"\t\t[[maybe_unused]] {scalar_reg_type1} s1 = {adapter.format_scalar_load(dt1_raw, 'inputs1', lmul_suffix)};")
        if not is_1arg:
            body_lines.append(f"\t\t[[maybe_unused]] {reg_type1} r2 = {adapter.format_load(dt1_raw, 'inputs2', lmul_suffix)};")
            body_lines.append(f"\t\t[[maybe_unused]] {scalar_reg_type1} s2 = {adapter.format_scalar_load(dt1_raw, 'inputs2', lmul_suffix)};")
        if is_3arg:
            body_lines.append(f"\t\t[[maybe_unused]] {reg_type1} r3 = {adapter.format_load(dt1_raw, 'inputs3', lmul_suffix)};")
            body_lines.append(f"\t\t[[maybe_unused]] {scalar_reg_type1} s3 = {adapter.format_scalar_load(dt1_raw, 'inputs3', lmul_suffix)};")

        if has_mask_var:
            msk_type = adapter.format_msk_type(dt1_raw, lmul_suffix)
            scalar_msk_type = adapter.format_scalar_msk_type(dt1_raw, lmul_suffix)
            body_lines.append(f"\t\t[[maybe_unused]] {msk_type} m1 = {adapter.format_set_k(dt1_raw, 'inputs_m', lmul_suffix)};")
            body_lines.append(f"\t\t[[maybe_unused]] {scalar_msk_type} sm1 = {adapter.format_scalar_set_k(dt1_raw, 'inputs_m', lmul_suffix)};")
            if n_masks >= 2:
                body_lines.append(f"\t\t[[maybe_unused]] {msk_type} m2 = {adapter.format_set_k(dt1_raw, 'inputs_m2', lmul_suffix)};")
                body_lines.append(f"\t\t[[maybe_unused]] {scalar_msk_type} sm2 = {adapter.format_scalar_set_k(dt1_raw, 'inputs_m2', lmul_suffix)};")
        if mkind == "masks":
            body_lines.append(f"\t\t[[maybe_unused]] {reg_type1} rsrc = {adapter.format_load(dt1_raw, 'inputs_src', lmul_suffix)};")
            body_lines.append(f"\t\t[[maybe_unused]] {scalar_reg_type1} ssrc = {adapter.format_scalar_load(dt1_raw, 'inputs_src', lmul_suffix)};")

        body_lines.append("")

        dt_func_ext = f"{dt1_raw}_{dt2_raw}" if len(dt_parts) == 2 else dt1_raw
        proto_spec = self.engine.protos.get(proto_ref, {})
        ret_type_kind = proto_spec.get("ret", {}).get("type")
        is_msk_ret = ret_type_kind == "msk"

        if is_msk_ret:
            ret_type_r = adapter.format_msk_type(dt2_raw, lmul_suffix)
            ret_type_s = adapter.format_scalar_msk_type(dt2_raw, lmul_suffix)
        else:
            ret_type_r = adapter.format_reg_type(dt2_raw, lmul_suffix)
            ret_type_s = adapter.format_scalar_reg_type(dt2_raw, lmul_suffix)

        op_args_r = self.engine._build_op_call_args(func_name, mkind, is_scalar=False)
        op_args_s = self.engine._build_op_call_args(func_name, mkind, is_scalar=True)

        is_loop = self.engine.proto_is_loop(proto_ref)
        if not is_loop:
            ret_type_r = f"{dt2_raw}_t"
            ret_type_s = f"{dt2_raw}_t"

        is_void_ret = self.engine.proto_is_void_ret(proto_ref)
        if is_void_ret:
            body_lines.extend(self.engine.render_void_ret_init(dt_cstd, size_out_var, "inputs_src" if mkind == "masks" else "inputs1"))
            body_lines.append(f"\t\t{adapter.format_func_call(func_name, dt_func_ext, ', '.join(op_args_r), lmul_suffix, mkind=mkind)};")
            body_lines.append(f"\t\t{adapter.format_scalar_func_call(func_name, dt_func_ext, ', '.join(op_args_s), lmul_suffix, mkind=mkind)};")
        else:
            body_lines.append(f"\t\t{ret_type_r} rres = {adapter.format_func_call(func_name, dt_func_ext, ', '.join(op_args_r), lmul_suffix, mkind=mkind)};")
            body_lines.append(f"\t\t{ret_type_s} sres = {adapter.format_scalar_func_call(func_name, dt_func_ext, ', '.join(op_args_s), lmul_suffix, mkind=mkind)};")
        body_lines.append("")

        body_lines.extend(self.engine.render_c_validation_block(
            func_name=func_name,
            adapter=adapter,
            mkind=mkind,
            dt1_raw=dt1_raw,
            dt2_raw=dt2_raw,
            dt_cstd=dt_cstd,
            lmul_suffix=lmul_suffix,
            is_loop=is_loop,
            is_void_ret=is_void_ret,
            is_msk_ret=is_msk_ret,
            size_out_var=size_out_var,
            size_var=size_var,
        ))

        body_lines.append("\t}")
        body_lines.append("}")
        body_lines.append("")
        return body_lines

    def _render_test_case_section(self, func_name: str, lmul_suffix: str = "m1", mkind: str = "", lmul: int = 0) -> List[str]:
        lines = []
        mask_tag_str = f"({mkind})" if mkind else ""
        lines.append(f'TEST_CASE("{func_name} - c {lmul_suffix} {mask_tag_str}", "[{func_name}]")')
        lines.append("{")

        datatypes = self.engine._resolve_datatypes(func_name)
        tag = f"{mkind}_{lmul_suffix}" if mkind else lmul_suffix
        for dt in datatypes:
            dt_clean = str(dt).replace(",", "_")
            call_expr = f"test_mipp_c_{func_name}_{dt_clean}_{tag}();"

            tpl_sec = self.engine._tpl("func_templates", "c", "test_section")
            lines.extend(self.engine.render_template(tpl_sec, dt=str(dt), call_expr=call_expr))

        lines.append("}")
        lines.append("")
        return lines


class TestsBuilderEngineCppBase:

    MK_ENUM  = {"unmasked": "mipp::U", "mask": "mipp::M", "maskz": "mipp::Z", "masks": "mipp::S"}
    MK_LABEL = {"unmasked": "unmasked (U)", "mask": "mask (M)", "maskz": "maskz (Z)", "masks": "masks (S)"}

    def __init__(self, engine: TestsBuilderEngine):
        self.engine = engine

    def render_cpp_test_case(self, dialect_name: str, func_name: str, supported_mkinds: List[str]) -> List[str]:
        lines = []
        func_prefix = "test_mipp_cpp" if dialect_name == "cpp" else "test_mipp_cpp_obj"
        datatypes = self.engine._resolve_datatypes(func_name)
        is_product = any("," in str(dt) for dt in datatypes)

        label_dialect = "cpp" if dialect_name == "cpp" else "obj"
        lines.append(f'TEST_CASE("{func_name} - {label_dialect} tests", "[{func_name}]")')
        lines.append("{")

        for mkind in supported_mkinds:
            mk_enum = self.MK_ENUM[mkind]
            mk_label = self.MK_LABEL[mkind]
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
                    call_expr = f"{func_prefix}_{func_name}<{mk_enum}, {cpp_type}, {lmul_val}>();"
                    tpl_lmul = self.engine._tpl("func_templates", "cpp_obj", "test_section_lmul")
                    lines.extend(self.engine.render_template(tpl_lmul, lmul_str=lmul_str, call_expr=call_expr))

                if dialect_name == "cpp":
                    call_ldiv2 = f"{func_prefix}_{func_name}<{mk_enum}, {cpp_type}, -2>();"
                    tpl_ldiv2 = self.engine._tpl("func_templates", "cpp", "test_section_ldiv2")
                    lines.extend(self.engine.render_template(tpl_ldiv2, call_expr=call_ldiv2))

                lines.append('\t\t}')

            lines.append('\t}')

        lines.append("}")
        lines.append("")
        return lines

    def _render_headers(self, dialect_name: str, func_name: str, N: int = 10) -> List[str]:
        func_spec = self.engine.specs["functions"].get(func_name, {})
        default_spec = self.engine.specs.get("default", {})
        extra_includes = func_spec.get("extra_includes", default_spec.get("extra_includes", []))

        tpl_fixed = self.engine._tpl("headers", "all", "headers_fixed")
        lines = self.engine.render_template(tpl_fixed, N_ITER=str(N))
        headers_set = set()
        cat_func = _match_category(func_name)
        headers_set.add('#include <mipp_obj.hpp>' if dialect_name == "obj" else '#include <mipp.hpp>')
        headers_set.add('#include <simd_ext/scalar/cpp/common.hpp>')
        headers_set.add(f'#include <simd_ext/scalar/cpp/functions/{cat_func}/{func_name}.hpp>')
        for aux in _AUX_HEADERS:
            if aux in self.engine.interfaces:
                cat_aux = _match_category(aux)
                headers_set.add(f'#include <simd_ext/scalar/cpp/functions/{cat_aux}/{aux}.hpp>')

        extra_aux = [inc for inc in extra_includes if inc not in _AUX_HEADERS]
        for aux in extra_includes:
            if aux in _AUX_HEADERS:
                cat_aux = _match_category(aux)
                headers_set.add(f'#include <simd_ext/scalar/cpp/functions/{cat_aux}/{aux}.hpp>')

        dt_spec = self.engine.interfaces.get(func_name, {}).get("datatypes")
        is_conversion = dt_spec in ("all_datatypes_cart_prod", "all_datatypes_same_size", "all_datatypes_widenning")
        if dialect_name == "cpp" and is_conversion:
            cat_cvt = _match_category("cvt")
            cat_wcvt = _match_category("wcvt")
            cat_cast = _match_category("cast")
            cat_cast_k = _match_category("cast_k")
            headers_set.add(f'#include <simd_ext/scalar/cpp/functions/{cat_cvt}/cvt.hpp>')
            headers_set.add(f'#include <simd_ext/scalar/cpp/functions/{cat_wcvt}/wcvt.hpp>')
            headers_set.add(f'#include <simd_ext/scalar/cpp/functions/{cat_cast}/cast.hpp>')
            headers_set.add(f'#include <simd_ext/scalar/cpp/functions/{cat_cast_k}/cast_k.hpp>')

        lines.extend(sorted(list(headers_set)))
        lines.append("")

        if dialect_name == "cpp" and is_conversion:
            lines.extend(self.engine._tpl("assertions", "cpp", "cvt_helpers"))
            lines.append("")

        for inc in extra_aux:
            lines.append(inc)
        if extra_aux:
            lines.append("")
        lines.append('#include <catch2/catch_test_macros.hpp>')
        lines.append('#include <catch2/catch_get_random_seed.hpp>')
        lines.append("")
        return lines

    def _append_cpp_mask_loads(self, lines: List[str], adapter, mkind: str, n_masks: int, is_scalar: bool) -> None:
        """Append mask and source register declarations inside an MK constexpr branch.

        Centralises the symmetric r/s load pattern in the Cpp template builder,
        eliminating the two near-identical blocks that differed only by scalar prefix.
        """
        prefix = "s" if is_scalar else ""
        set_k = adapter.format_scalar_set_k if is_scalar else adapter.format_set_k
        load  = adapter.format_scalar_load   if is_scalar else adapter.format_load
        if n_masks >= 2:
            lines.append(f"\t\t\t\tauto {prefix}m1 = {set_k('T', 'inputs_m', 'LMUL')};")
            lines.append(f"\t\t\t\tauto {prefix}m2 = {set_k('T', 'inputs_m2', 'LMUL')};")
        elif n_masks == 1 or mkind in ("mask", "maskz", "masks"):
            lines.append(f"\t\t\t\tauto {prefix}m1 = {set_k('T', 'inputs_m', 'LMUL')};")
        if mkind == "masks":
            src_name = "ssrc" if is_scalar else "rsrc"
            lines.append(f"\t\t\t\tauto {src_name} = {load('T', 'inputs_src', 'LMUL')};")


    def _render_cpp_input_arrays(
        self,
        func_spec: dict,
        dialect: str,
        is_1arg: bool,
        is_3arg: bool,
        has_inputs2: bool,
        has_m2: bool = False,
    ) -> List[str]:
        """Declare and fill the input arrays for a Cpp/CppObj test function.

        Generates the T inputs1/2/3[size] declarations, inputs_src and inputs_m
        declarations, and the initialisation loop with domain values.
        Shared between TestsBuilderEngineCpp (has_m2=True) and
        TestsBuilderEngineCppObj (has_m2=False).
        """
        dr = self.engine.domain_resolver
        out: List[str] = []
        out.append("\t\tT inputs1[size];")
        if has_inputs2:
            out.append("\t\tT inputs2[size];")
        if is_3arg:
            out.append("\t\tT inputs3[size];")
        out.append("\t\t[[maybe_unused]] T inputs_src[size];")
        out.append("\t\t[[maybe_unused]] int32_t inputs_m[size];")
        if has_m2:
            out.append("\t\t[[maybe_unused]] int32_t inputs_m2[size];")
        out.append("")
        out.append("\t\tfor (size_t i = 0; i < size; i++)")
        out.append("\t\t{")
        out.extend(dr.render_input_filling(func_spec, "inputs1", dialect=dialect))
        if has_inputs2:
            out.extend(dr.render_input_filling(func_spec, "inputs2", dialect=dialect))
        if is_3arg:
            out.extend(dr.render_input_filling(func_spec, "inputs3", dialect=dialect))
        out.extend(dr.render_mask_filling(func_spec, "inputs_m", dialect=dialect))
        if has_m2:
            out.extend(dr.render_mask_filling(func_spec, "inputs_m2", dialect=dialect))
        out.extend(dr.render_input_filling(func_spec, "inputs_src", dialect=dialect, mkind="masks"))
        out.append("\t\t}")
        out.append("")
        return out

    def _render_op_lambda(
        self,
        func_name: str,
        var_name: str,
        is_void_ret: bool,
        ret_prefix: str,
        supported_mkinds: List[str],
        adapter,
        n_masks: int,
        is_scalar: bool,
    ) -> List[str]:
        """Render a [&]() { if constexpr (MK == ...) { ... } }() lambda for one op call.

        Used twice in TestsBuilderEngineCpp (r_var and s_var), differing only in
        is_scalar and var_name. Centralises the duplicated for-mkind loop.
        """
        out: List[str] = []
        out.append(f"\t\t" + ("[&]() {" if is_void_ret else f"auto {var_name} = [&]() {{"))
        is_first = True
        for mkind in supported_mkinds:
            mk_enum = self.MK_ENUM[mkind]
            keyword = "if constexpr" if is_first else "else if constexpr"
            is_first = False
            out.append(f"\t\t\t{keyword} (MK == {mk_enum})")
            out.append("\t\t\t{")
            self._append_cpp_mask_loads(out, adapter, mkind, n_masks, is_scalar=is_scalar)
            out.append(f"\t\t\t\t{ret_prefix}{self.engine.format_cpp_op_call(func_name, mkind, is_scalar=is_scalar)};")
            out.append("\t\t\t}")
        out.append("\t\t}();")
        out.append("")
        return out


class TestsBuilderEngineCpp(TestsBuilderEngineCppBase):

    def build_test_file_content(self, func_name: str, lmul_suffix: str = "m1", mkind: str = "", lmul: int = 0, N: int = 10) -> str:
        lines = []
        adapter = CppDialectAdapter()
        lines.extend(self._render_headers("cpp", func_name, N=N))

        mask_support = self.engine.interfaces[func_name].get("mask_support", "all_mask")
        supported_mkinds = []
        for m in ["unmasked", "mask", "maskz", "masks"]:
            if m == "unmasked" or self.engine._is_mask_kind_supported(mask_support, m):
                supported_mkinds.append(m)

        proto_ref = self.engine.interfaces.get(func_name, {}).get("proto_ref", "ret_reg_2args_reg")
        func_spec = self.engine.specs["functions"].get(func_name, {})
        datatypes = self.engine._resolve_datatypes(func_name)
        is_product = any("," in str(dt) for dt in datatypes)
        is_1arg = self.engine.proto_is_1arg(proto_ref)
        is_3arg = self.engine.proto_is_3arg(proto_ref)
        is_reg_val = self.engine.proto_is_reg_val(proto_ref)

        tpl_key = "func_header_product" if is_product else "func_header"
        tpl_hdr = self.engine._tpl("func_templates", "cpp", tpl_key)
        lines.extend(self.engine.render_template(tpl_hdr, func_name=func_name))

        if is_product:
            lines.extend(self.engine.render_template(
                self.engine._tpl("func_templates", "cpp", "size_constexpr_product"),
                adapter=adapter
            ))
        else:
            lines.extend(self.engine.render_template(
                self.engine._tpl("func_templates", "cpp_obj", "size_constexpr"),
                adapter=adapter
            ))

        lines.extend(self._render_cpp_input_arrays(
            func_spec, "cpp", is_1arg, is_3arg,
            has_inputs2=(not is_1arg or is_reg_val),
            has_m2=True,
        ))

        lines.append(f"\t\t[[maybe_unused]] auto r1 = {adapter.format_load('T', 'inputs1', 'LMUL')};")
        lines.append(f"\t\t[[maybe_unused]] auto s1 = {adapter.format_scalar_load('T', 'inputs1', 'LMUL')};")
        if not is_1arg or is_reg_val:
            lines.append(f"\t\t[[maybe_unused]] auto r2 = {adapter.format_load('T', 'inputs2', 'LMUL')};")
            lines.append(f"\t\t[[maybe_unused]] auto s2 = {adapter.format_scalar_load('T', 'inputs2', 'LMUL')};")
        if is_3arg:
            lines.append(f"\t\t[[maybe_unused]] auto r3 = {adapter.format_load('T', 'inputs3', 'LMUL')};")
            lines.append(f"\t\t[[maybe_unused]] auto s3 = {adapter.format_scalar_load('T', 'inputs3', 'LMUL')};")

        is_void_ret = self.engine.proto_is_void_ret(proto_ref)
        if is_void_ret:
            lines.extend(self.engine.render_void_ret_init("T", "size", "inputs1"))
            r_var = "res_r"
            s_var = "res_s"
        else:
            r_var = "rres"
            s_var = "sres"

        ret_prefix = "" if is_void_ret else "return "
        n_masks = self.engine.get_required_mask_count(func_name)

        lines.extend(self._render_op_lambda(
            func_name, r_var, is_void_ret, ret_prefix, supported_mkinds, adapter, n_masks, is_scalar=False,
        ))
        lines.extend(self._render_op_lambda(
            func_name, s_var, is_void_ret, ret_prefix, supported_mkinds, adapter, n_masks, is_scalar=True,
        ))

        val_lines = self.engine.render_cpp_validation_block(func_name, proto_ref, is_product, r_var=r_var, s_var=s_var, adapter=adapter)
        lines.extend(self.engine.indent_lines(val_lines, 2))

        lines.extend(self.engine._tpl("func_templates", "cpp_obj", "func_footer"))

        lines.extend(self.render_cpp_test_case("cpp", func_name, supported_mkinds))
        return "\n".join(lines)


class TestsBuilderEngineCppObj(TestsBuilderEngineCppBase):

    def build_test_file_content(self, func_name: str, lmul_suffix: str = "m1", mkind: str = "", lmul: int = 0, N: int = 10) -> str:
        lines = []
        lines.extend(self._render_headers("obj", func_name, N=N))

        supported_mkinds = ["unmasked"]

        proto_ref = self.engine.interfaces.get(func_name, {}).get("proto_ref", "ret_reg_2args_reg")
        func_spec = self.engine.specs["functions"].get(func_name, {})
        datatypes = self.engine._resolve_datatypes(func_name)
        is_product = any("," in str(dt) for dt in datatypes)
        is_1arg = self.engine.proto_is_1arg(proto_ref)
        is_3arg = self.engine.proto_is_3arg(proto_ref)
        is_reg_val = self.engine.proto_is_reg_val(proto_ref)

        tpl_hdr_obj = self.engine._tpl("func_templates", "obj", "func_header")
        lines.extend(self.engine.render_template(tpl_hdr_obj, func_name=func_name))

        adapter = CppObjDialectAdapter()
        lines.extend(self.engine.render_template(
            self.engine._tpl("func_templates", "cpp_obj", "size_constexpr"),
            adapter=adapter
        ))
        lines.extend(self._render_cpp_input_arrays(
            func_spec, "obj", is_1arg, is_3arg,
            has_inputs2=(not is_1arg),
            has_m2=False,
        ))

        load_key = "load_3args" if is_3arg else ("load_1arg" if is_1arg else "load_2args")
        lines.extend(self.engine.render_template(
            self.engine._tpl("func_templates", "obj", load_key),
            adapter=adapter
        ))

        if is_reg_val:
            op_args_r = ["r1", "inputs2[0]"]
            op_args_s = ["s1", "inputs2[0]"]
        else:
            op_args_r = ["r1"] if is_1arg else (["r1", "r2", "r3"] if is_3arg else ["r1", "r2"])
            op_args_s = ["s1"] if is_1arg else (["s1", "s2", "s3"] if is_3arg else ["s1", "s2"])

        call_r = adapter.format_func_call(func_name, "T", ", ".join(op_args_r))
        call_s = adapter.format_scalar_func_call(func_name, "T", ", ".join(op_args_s))

        r_var = "rres"
        s_var = "sres"

        tpl_lambda = self.engine._tpl("func_templates", "obj", "op_call_lambda")
        lines.extend(self.engine.render_template(tpl_lambda, var_name=r_var, call_expr=call_r))
        lines.extend(self.engine.render_template(tpl_lambda, var_name=s_var, call_expr=call_s))

        val_lines = self.engine.render_cpp_validation_block(func_name, proto_ref, is_product, r_var=r_var, s_var=s_var, adapter=adapter)
        lines.extend(self.engine.indent_lines(val_lines, 2))

        lines.extend(self.engine._tpl("func_templates", "cpp_obj", "func_footer"))

        lines.extend(self.render_cpp_test_case("obj", func_name, supported_mkinds))
        return "\n".join(lines)
