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
from . import indexed_tests
from tools import DATATYPES_MAP, resolve_ret_lmul, is_defined_for_lmul, changes_lmul, isa_provides_lmul
from include_gen import _match_category

# Auxiliary MIPP functions whose headers must always be included in generated test files.
_AUX_HEADERS = ["load", "get", "get_k", "to_rvd", "to_rvm", "set_k"]

# Functions whose vector call gets a pointer shifted by one element: never aligned on the
# register size (the scalar reference keeps the aligned buffers).
_UNALIGNED_PTR_FUNCS = ("loadu", "storeu")

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
            self.active_audits = {"consistency"}
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
        self.obj_builder = TestsBuilderEngineObj(self)

    def get_builder(self, dialect_name: str):
        if dialect_name == "c":
            return self.c_builder
        elif dialect_name == "obj":
            return self.obj_builder
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
                elif func_name in _UNALIGNED_PTR_FUNCS and not is_scalar:
                    args.append("inputs1_u")
                else:
                    args.append("inputs1")

        if mkind in ("mask", "maskz", "masks"):
            args.insert(0, "sm1" if is_scalar else "m1")
        if mkind == "masks":
            args.insert(1, "ssrc" if is_scalar else "rsrc")

        return args

    # --- LMUL of the result, domain and ISA guards (all derived from ret.lmul of the prototype) ---

    def _proto_of(self, func_name: str) -> Dict[str, Any]:
        return self.protos.get(self.interfaces.get(func_name, {}).get("proto_ref", ""), {})

    @staticmethod
    def test_input_lmul(lmul: int) -> int:
        """LMUL of the arguments of a test. The `m0` tests call the names without suffix, which are
        those of LMUL 1."""
        return 1 if lmul == 0 else lmul

    def is_test_defined(self, func_name: str, lmul: int) -> bool:
        """False when the function does not exist for this LMUL (a result LMUL that does not exist,
        e.g. `wcvt` from m8 or `low` from d2). Always true for the functions that keep the LMUL."""
        proto = self._proto_of(func_name)
        return is_defined_for_lmul(proto, self.test_input_lmul(lmul)) if proto else True

    def result_lmul(self, func_name: str, lmul: int) -> int:
        """LMUL of the returned register for arguments of LMUL `lmul` (same value when the function
        keeps the LMUL; for `lmul` 0 and a function that changes it, the LMUL of the result of m1)."""
        proto = self._proto_of(func_name)
        if not proto or not changes_lmul(proto):
            return lmul
        return resolve_ret_lmul(proto["ret"], self.test_input_lmul(lmul))

    @staticmethod
    def lmul_tag(lmul: int) -> str:
        return f"m{lmul}" if lmul >= 0 else f"d{-lmul}"

    @staticmethod
    def lanes_factor(lmul: int) -> str:
        """C expression suffix scaling the number of lanes of a register of LMUL 1 (`* 2`, `/ 2`)."""
        return f" * {lmul}" if lmul > 1 else (f" / {-lmul}" if lmul < 0 else "")

    def _isa_configs(self) -> Dict[str, Any]:
        if getattr(self, "_isa_cfg_cache", None) is None:
            self._isa_cfg_cache = {}
            for name in sorted(os.listdir(self.simd_ext_dir)):
                isa_json = os.path.join(self.simd_ext_dir, name, f"{name}_isa.json")
                if os.path.exists(isa_json):
                    self._isa_cfg_cache[name] = self._load_json(isa_json)
        return self._isa_cfg_cache

    def _isa_providers(self, func_name: str, lmul: int) -> Optional[List[str]]:
        """`defined(MIPP_<ISA>)` conditions of the ISAs that provide the function for this LMUL, or
        None when every ISA provides it."""
        proto = self._proto_of(func_name)
        if not proto:
            return None
        eff = self.test_input_lmul(lmul)
        # the scalar ISA (no JSON of its own) provides every function
        providers = ["defined(MIPP_SCALAR)"]
        configs = self._isa_configs()
        for name, isa in configs.items():
            if isa_provides_lmul(isa, proto, eff):
                providers.append("defined(MIPP_SCALAR)" if isa.get("is_scalar", False)
                                 else f"defined(MIPP_{name.upper()})")
        if len(providers) == len(configs) + 1:
            return None
        return providers

    def isa_guard(self, func_name: str, lmul: int) -> Optional[str]:
        """Preprocessor condition (one `defined(MIPP_<ISA>)` per ISA that provides the function for
        this LMUL), or None when every ISA provides it. Tests are compiled for a single ISA."""
        providers = self._isa_providers(func_name, lmul)
        return None if providers is None else " || ".join(providers)

    def isa_guard_any(self, func_name: str, lmuls: List[int]) -> Optional[str]:
        """Same as `isa_guard` for a file that tests several LMULs: the ISAs that provide the
        function for at least one of them (None when every ISA provides it for one of them)."""
        union: List[str] = []
        for lmul in lmuls:
            providers = self._isa_providers(func_name, lmul)
            if providers is None:
                return None
            union.extend(p for p in providers if p not in union)
        return " || ".join(union) if union else "0"

    # --- C++ layers: product (src,dst) functions and result LMUL as a compile-time expression ---

    def is_product_func(self, func_name: str) -> bool:
        """True when the function is tested on (source, destination) pairs of datatypes."""
        return any("," in str(dt) for dt in self._resolve_datatypes(func_name))

    def lmul_out_expr(self, func_name: str) -> str:
        """C++ constant expression of the LMUL of the returned register as a function of the template
        parameter `LMUL` (the arguments' one): `LMUL` itself unless the prototype changes it."""
        proto = self._proto_of(func_name)
        if not proto or not changes_lmul(proto):
            return "LMUL"
        mode = proto["ret"].get("lmul", "same")
        if mode == "up":
            return "(LMUL == -2 ? 1 : LMUL * 2)"
        if mode == "down":
            return "(LMUL == 1 ? -2 : LMUL / 2)"
        return str({"d2": -2, "m1": 1, "m2": 2, "m4": 4, "m8": 8}[mode])

    def cpp_lmul_out(self, func_name: str) -> tuple:
        """(declaration lines, name) of the constant holding the LMUL of the returned register: a
        `LMUL_OUT` constant when the prototype changes the LMUL, else the template parameter `LMUL`."""
        expr = self.lmul_out_expr(func_name)
        if expr == "LMUL":
            return [], "LMUL"
        return [f"\t\tconstexpr int LMUL_OUT = {expr};"], "LMUL_OUT"

    def render_cpp_sizes(self, func_name: str, adapter: DialectAdapter, is_product: bool) -> List[str]:
        """Declare `size` (lanes of the arguments) and, for a product function or a function that
        changes the LMUL, `size_out` (lanes of the result, with the LMUL of the returned register)."""
        decl, lmul_out = self.cpp_lmul_out(func_name)
        lines = list(decl)
        if is_product:
            lines.extend(self.render_template(self._tpl("func_templates", "cpp", "size_constexpr_product"),
                                              adapter=adapter, lmul_out=lmul_out))
        else:
            lines.extend(self.render_template(self._tpl("func_templates", "obj", "size_constexpr"), adapter=adapter))
            if decl:
                lines.extend(self.render_template(self._tpl("func_templates", "cpp", "size_out_constexpr"),
                                                  adapter=adapter, lmul_out=lmul_out))
        return lines

    def render_cpp_conv_helper(self, func_name: str) -> List[str]:
        """`test_helpers::<cpp_name><T_dst>(reg)`: forwards to the `mipp::<cpp_name>_<dst>` overload of
        the destination type, which is a template parameter of the test (the C++ names carry it)."""
        fname = self.interfaces.get(func_name, {}).get("cpp_name", func_name)
        proto = self._proto_of(func_name)
        first_arg = (proto.get("args") or [{}])[0].get("type") if proto else "reg"
        raw_dsts: List[str] = []
        for dt in self._resolve_datatypes(func_name):
            if "," in str(dt):
                dst = str(dt).split(",")[1].strip()
                if dst not in raw_dsts:
                    raw_dsts.append(dst)
        dsts = [{"raw": d, "cpp": self._format_cpp_type(d)} for d in raw_dsts]
        return self.render_template(
            self._tpl("assertions", "cpp", "conv_helper"), fname=fname, dsts=dsts,
            arg=("m0" if first_arg == "msk" else "r0"), arg_type=("Msk" if first_arg == "msk" else "Reg"))

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
                             indent: str = "\t\t", func_name: str = "") -> List[str]:
        """Generates the declaration and initialization of res_r/res_s for void-ret functions.
        For the functions of _UNALIGNED_PTR_FUNCS, res_r points one element past an aligned buffer.
        """
        if func_name in _UNALIGNED_PTR_FUNCS:
            res_r_decl = [
                f"{indent}alignas(64) {dt_type} res_r_ubuf[{size_var} + 1];",
                f"{indent}{dt_type}* res_r = res_r_ubuf + 1; // unaligned on purpose",
            ]
        else:
            res_r_decl = [f"{indent}alignas(64) {dt_type} res_r[{size_var}];"]
        return res_r_decl + [
            f"{indent}alignas(64) {dt_type} res_s[{size_var}];",
            f"{indent}for (size_t i = 0; i < {size_var}; i++)",
            f"{indent}{{",
            f"{indent}\tres_r[i] = {init_src}[i];",
            f"{indent}\tres_s[i] = {init_src}[i];",
            f"{indent}}}",
        ]

    def render_unaligned_input(self, func_name: str, dt_type: str, size_var: str,
                               indent: str = "\t\t") -> List[str]:
        """Generates inputs1_u, a copy of inputs1 one element past an aligned buffer, for the
        functions of _UNALIGNED_PTR_FUNCS that read memory (nothing for the other functions).
        """
        args_info = self.get_proto_args_info(func_name)
        reads_ptr = any(a.get("type") == "ptr" and a.get("charac") != "WO" for a in args_info)
        if func_name not in _UNALIGNED_PTR_FUNCS or not reads_ptr:
            return []
        return [
            f"{indent}alignas(64) {dt_type} inputs1_ubuf[{size_var} + 1];",
            f"{indent}{dt_type}* inputs1_u = inputs1_ubuf + 1; // unaligned on purpose",
            f"{indent}for (size_t i = 0; i < {size_var}; i++)",
            f"{indent}\tinputs1_u[i] = inputs1[i];",
            "",
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

    def _is_mask_kind_supported(self, variants: List[str], mkind: str) -> bool:
        """`variants` is the list of registry_interfaces.json (`u`, `m`, `z`, `s`)."""
        if mkind == "unmasked":
            return True
        return {"mask": "m", "maskz": "z", "masks": "s"}.get(mkind) in variants

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
            self._tpl("assertions", "obj", "as_bitwise_eq")
        """
        node: Any = self.templates
        for key in path:
            if not isinstance(node, dict):
                return []
            node = node.get(key, {})
        return node if isinstance(node, list) else []

    def _format_cpp_type(self, dt_str: str) -> str:
        return CppDialectAdapter().cpp_type(dt_str)

    # Maps JSON 'by_*' keys to the C++ runtime variable they compare against.
    # Add a new entry here to support a new 'by_*' axis (e.g. "by_mask": "MASK_KIND").
    _BY_RUNTIME_KEYS: dict[str, str] = {
        "by_lmul": "LMUL",
    }

    # The set of keys that are valid in a leaf tolerance spec.
    # Used to safely extract a fallback spec from a by_datatype parent spec.
    _TOLERANCE_LEAF_KEYS: frozenset = frozenset({"type", "value"})

    def _leaf_tol_expr(self, ttype: str, val: float, dt_cpp: str, ref_var: str) -> str:
        """Generates a single C++ tolerance expression for a scalar spec (no by_* keys)."""
        if ttype == "relative_percent":
            f32 = f"({dt_cpp})(abs_diff::abs_diff({ref_var}) * (float){val})"
            f64 = f"({dt_cpp})(abs_diff::abs_diff({ref_var}) * (double){val})"
        else:  # max_abs_diff
            f32 = f"({dt_cpp})((float){val})"
            f64 = f"({dt_cpp})((double){val})"

        if dt_cpp in ("float32_t", "float"):
            return f32
        elif dt_cpp in ("float64_t", "double"):
            return f64
        else:
            return f"(std::is_same_v<{dt_cpp}, float> ? {f32} : {f64})"

    def _tol_spec_to_expr(self, spec: dict, dt_cpp: str, ref_var: str) -> str:
        """Converts a tolerance spec dict into an inline C++ expression.

        Handles nested by_datatype and by_* runtime keys recursively.
        Does NOT handle by_define (preprocessor blocks are handled by the caller).
        """
        if not spec or spec.get("type") == "exact":
            return "(T)0"

        # If the spec is a pure "default" wrapper (no direct leaf keys or by_datatype/by_*),
        # unwrap it. Example: {"default": {"type": "relative_percent", "value": 0.01}}
        content_keys = self._TOLERANCE_LEAF_KEYS | set(self._BY_RUNTIME_KEYS.keys()) | {"by_datatype"}
        if "default" in spec and not any(k in spec for k in content_keys):
            spec = spec["default"]
            if not spec or spec.get("type") == "exact":
                return "(T)0"

        # --- by_datatype: select the sub-spec for the current datatype ---
        if "by_datatype" in spec:
            by_dt = spec["by_datatype"]
            # Build fallback from only known tolerance keys (by inclusion, not exclusion)
            # to avoid accidentally inheriting unrelated keys (e.g. "comparison").
            valid_keys = self._TOLERANCE_LEAF_KEYS | set(self._BY_RUNTIME_KEYS.keys())
            default_sub = (
                spec.get("default")
                or {k: v for k, v in spec.items() if k in valid_keys}
                or {"type": "exact"}
            )

            if dt_cpp in ("float32_t", "float"):
                sub = by_dt.get("float32", default_sub)
                return self._tol_spec_to_expr(sub, dt_cpp, ref_var)
            elif dt_cpp in ("float64_t", "double"):
                sub = by_dt.get("float64", default_sub)
                return self._tol_spec_to_expr(sub, dt_cpp, ref_var)
            else:
                # Generic type T: emit ternary covering float32 vs float64
                f32_sub = by_dt.get("float32", default_sub)
                f64_sub = by_dt.get("float64", default_sub)
                f32_expr = self._tol_spec_to_expr(f32_sub, "float", ref_var)
                f64_expr = self._tol_spec_to_expr(f64_sub, "double", ref_var)
                return f"(std::is_same_v<{dt_cpp}, float> ? {f32_expr} : {f64_expr})"

        # --- by_* runtime keys: build a nested ternary (LMUL == x ? ... : default) ---
        for by_key, cpp_var in self._BY_RUNTIME_KEYS.items():
            if by_key in spec:
                by_vals = spec[by_key]
                ttype = spec.get("type", "max_abs_diff")
                default_val = spec.get("value", 0.001)
                # Build list of (condition, value) pairs
                cond_parts = [(f"({cpp_var} == {k})", float(v)) for k, v in by_vals.items()]
                # Build nested ternary from right to left: last condition is innermost
                expr_val_str = f"({self._cpp_cast(dt_cpp)}){default_val}"
                for cond_str, cond_val in reversed(cond_parts):
                    expr_val_str = f"({cond_str} ? ({self._cpp_cast(dt_cpp)}){cond_val} : {expr_val_str})"
                if ttype == "relative_percent":
                    return f"({dt_cpp})(abs_diff::abs_diff({ref_var}) * {expr_val_str})"
                else:
                    return f"({dt_cpp})({expr_val_str})"

        # --- Leaf: plain type + value ---
        ttype = spec.get("type", "max_abs_diff")
        val = spec.get("value", 0.001)
        return self._leaf_tol_expr(ttype, val, dt_cpp, ref_var)

    def _cpp_cast(self, dt_cpp: str) -> str:
        """Returns the C cast type to use for a numeric literal given the C++ datatype."""
        if dt_cpp in ("float32_t", "float"):
            return "float"
        elif dt_cpp in ("float64_t", "double"):
            return "double"
        else:
            return "T"


    def render_tolerance_declaration(self, func_name: str, dt_cpp: str, ref_var: str,
                                     tol_var: str = "tol",
                                     indent: str = "\t\t\t") -> List[str]:
        """Generates the lines declaring the tolerance variable.

        Handles the 'by_define' case by emitting #if/#elif/#else/#endif blocks.
        For all other cases, delegates to _tol_spec_to_expr for a single expression.
        """
        func_spec = self.specs["functions"].get(func_name, {})
        default_tol = self.specs.get("default", {}).get("tolerance", {"type": "exact"})
        tol_spec = func_spec.get("tolerance", default_tol)

        # by_define: emit preprocessor #if/#elif/#else/#endif blocks
        if isinstance(tol_spec, dict) and "by_define" in tol_spec:
            by_define = tol_spec["by_define"]
            # The fallback is the rest of the spec (by_datatype, etc.) without by_define
            fallback_spec = {k: v for k, v in tol_spec.items() if k != "by_define"}
            if not fallback_spec:
                fallback_spec = default_tol
            # Outer by_datatype used as inheritance base for define branches
            fallback_by_dt = fallback_spec.get("by_datatype", {})
            lines: List[str] = []
            first = True
            for define_key, define_spec in by_define.items():
                lines.append(f"#if defined({define_key})" if first else f"#elif defined({define_key})")
                first = False
                # Merge: outer by_datatype fills in any datatype not explicitly set in define_spec
                if "by_datatype" in define_spec and fallback_by_dt:
                    merged_by_dt = {**fallback_by_dt, **define_spec["by_datatype"]}
                    merged_spec = {**define_spec, "by_datatype": merged_by_dt}
                else:
                    merged_spec = define_spec
                lines.append(f"{indent}auto {tol_var} = {self._tol_spec_to_expr(merged_spec, dt_cpp, ref_var)};")
            lines.append("#else")
            lines.append(f"{indent}auto {tol_var} = {self._tol_spec_to_expr(fallback_spec, dt_cpp, ref_var)};")
            lines.append("#endif")
            return lines

        # Standard case: single inline expression
        expr = self._tol_spec_to_expr(tol_spec, dt_cpp, ref_var)
        return [f"{indent}auto {tol_var} = {expr};"]


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

        loop_limit = "size_out" if (is_product or changes_lmul(self._proto_of(func_name))) else "size"

        nan_inf_skip = func_spec.get("nan_inf_skip", False)
        nan_inf_skip_lines = "if (std::isnan(diff) || std::isinf(diff)) continue;" if nan_inf_skip else ""
        # skip_condition: lignes de skip conditionnel (ex: fractional_part pour round)
        skip_cond_lines = self.render_skip_condition(func_name, s_get, indent="\t")

        val_lines = []
        if isinstance(comp_type, dict) and any(v == "bitwise" for v in comp_type.get("by_datatype", {}).values()):
            val_lines.append("if constexpr (std::is_floating_point_v<T>)")
            val_lines.append("{")
            tpl = self._tpl("assertions", "obj", "as_bitwise_eq")
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
                tpl = self._tpl("assertions", "obj", "as_logical_scalar_eq")
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
                tpl = self._tpl("assertions", "obj", "as_strict_scalar_eq")
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
            tpl = self._tpl("assertions", "obj", "as_bitwise_eq")
            val_lines.extend(self.render_template(tpl, r_get=r_get, s_get=s_get, loop_limit=loop_limit))
        elif comp_type == "logical" or func_name.endswith("_k") or "ret_msk" in proto_ref:
            tpl = self._tpl("assertions", "obj", "as_logical_eq")
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
            tpl = self._tpl("assertions", "obj", tpl_key)
            for line in tpl:
                if "{{validation_block}}" in line:
                    lines.extend(self.indent_lines(val_lines, 1))
                else:
                    lines.append(line)
            return lines

        return val_lines

    def build_test_file_content(
        self,
        dialect_name: str,
        func_name: str,
        lmul_suffix: str = "m1",
        mkind: str = "",
        lmul: int = 0,
        N: int = 10,
        lmul_list: Optional[List[int]] = None,
        ldiv_list: Optional[List[int]] = None,
        mask_list: Optional[List[str]] = None,
    ) -> str:
        if func_name in indexed_tests.INDEXED_FUNCS:
            return self._build_indexed_test_file(dialect_name, func_name, lmul_suffix, mkind, lmul, N,
                                                 lmul_list, ldiv_list, mask_list)
        builder = self.get_builder(dialect_name)
        return builder.build_test_file_content(
            func_name,
            lmul_suffix=lmul_suffix,
            mkind=mkind,
            lmul=lmul,
            N=N,
            lmul_list=lmul_list,
            ldiv_list=ldiv_list,
            mask_list=mask_list,
        )

    def _build_indexed_test_file(self, dialect_name, func_name, lmul_suffix, mkind, lmul, N,
                                 lmul_list, ldiv_list, mask_list) -> str:
        """gather / scatter: see helpers_tests/indexed_tests.py."""
        dts = []
        for dt in self._resolve_datatypes(func_name):
            first = str(dt).split(",")[0].strip()
            if first not in dts:
                dts.append(first)
        if dialect_name == "c":
            return indexed_tests.build_c(func_name, dts, lmul_suffix, mkind, lmul, N)
        func_variants = self.interfaces[func_name].get("variants", ["u", "m", "z", "s"])
        mkinds = []
        for m in ["unmasked", "mask", "maskz", "masks"]:
            if mask_list is None or m in mask_list or (m == "unmasked" and "" in mask_list):
                if m == "unmasked" or self._is_mask_kind_supported(func_variants, m):
                    mkinds.append("" if m == "unmasked" else m)
        return indexed_tests.build_cpp(dialect_name, func_name, [self._format_cpp_type(d) for d in dts],
                                       mkinds, lmul_list, ldiv_list, N)

    def format_cpp_op_call(self, func_name: str, mkind: str, is_scalar: bool = False) -> str:
        """Build a C++ template call expression with symbolic params (V, T, LMUL).

        Used by TestsBuilderEngineCpp where T and LMUL are compile-time template
        parameters, not resolved Python values. Centralises all mipp:: namespace
        references for this dialect so dialect_adapters remain authoritative.
        """
        args = self._build_op_call_args(func_name, mkind, is_scalar)
        fname = self.interfaces.get(func_name, {}).get("cpp_name", func_name)
        call_args = ", ".join(args)
        isa_str = ", mipp::ISA::SCALAR" if is_scalar else ""

        # Masked variants: explicit V template param
        mk_map = {"mask": "mipp::M", "maskz": "mipp::Z", "masks": "mipp::S"}
        if mkind in mk_map:
            mk_sym = mk_map[mkind]
            return f"mipp::{fname}<{mk_sym}, T, LMUL{isa_str}>({call_args})"

        # Conversion functions: test_helpers wrapper
        if self.is_product_func(func_name):
            return f"mipp::test_helpers::{fname}<T_dst>({call_args})"

        # Functions with no register/mask args (set, set0, set1…): explicit T, LMUL
        args_info = self.get_proto_args_info(func_name)
        has_reg_or_msk = any(arg.get("type") in ("reg", "msk") for arg in args_info)
        if not has_reg_or_msk:
            return f"mipp::{fname}<T, LMUL{isa_str}>({call_args})"

        # Default: plain call (T is deduced from arguments)
        return f"mipp::{fname}({call_args})"

    def format_obj_op_call(self, func_name: str, mkind: str) -> str:
        """Build a C++ Object call expression using operator overloads where available,
        or free functions in namespace mipp::.
        """
        args = self._build_op_call_args(func_name, mkind, is_scalar=False)

        # 1. Operators for unmasked calls
        if mkind in ("", "unmasked"):
            all_binary_ops = {
                "add": "+", "sub": "-", "mul": "*", "div": "/",
                "andb": "&", "orb": "|", "xorb": "^",
                "cmpeq": "==", "cmpneq": "!=", "cmplt": "<",
                "cmple": "<=", "cmpgt": ">", "cmpge": ">=",
            }
            if func_name in all_binary_ops and len(args) == 2:
                return f"{args[0]} {all_binary_ops[func_name]} {args[1]}"
            if func_name == "lshift" and len(args) == 2:
                return f"{args[0]} << {args[1]}"
            if func_name == "rshift" and len(args) == 2:
                return f"{args[0]} >> {args[1]}"
            if func_name == "neg" and len(args) == 1:
                return f"-{args[0]}"
            if func_name == "notb" and len(args) == 1:
                return f"~{args[0]}"

        # 2. Conversion functions: test_helpers wrapper (same as Cpp for scalar compatibility)
        if self.is_product_func(func_name):
            fname = self.interfaces.get(func_name, {}).get("cpp_name", func_name)
            call_args = ", ".join(args)
            return f"mipp::{fname}<T_dst>({call_args})"

        # 3. Memory / Load / Set specific names
        obj_name_map = {
            "load": "load_obj",
            "loadu": "loadu_obj",
            "set": "set_obj",
            "set0": "set0_obj",
            "set1": "set1_obj",
            "set_k": "set_k_obj",
            "set0_k": "set0_k_obj",
            "set1_k": "set1_k_obj",
        }
        fname = obj_name_map.get(func_name, self.interfaces.get(func_name, {}).get("cpp_name", func_name))
        call_args = ", ".join(args)

        # 4. Masked variants
        mk_map = {"mask": "mipp::M", "maskz": "mipp::Z", "masks": "mipp::S"}
        if mkind in mk_map:
            mk_sym = mk_map[mkind]
            return f"mipp::{fname}<{mk_sym}>({call_args})"

        # 5. Functions with no register/mask args (set, set0, set1, load, loadu…): explicit T, LMUL
        args_info = self.get_proto_args_info(func_name)
        has_reg_or_msk = any(arg.get("type") in ("reg", "msk") for arg in args_info)
        if not has_reg_or_msk:
            return f"mipp::{fname}<T, LMUL>({call_args})"

        # Default: plain free function call
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
        ret_lmul_suffix: Optional[str] = None,
    ) -> List[str]:
        """Generate assertion lines for the C dialect validation block.

        `lmul_suffix` is the LMUL of the arguments, `ret_lmul_suffix` the one of the returned register
        (defaults to `lmul_suffix`: they differ for the functions whose prototype has `ret.lmul`).

        Symmetric to render_cpp_validation_block but uses CDialectAdapter
        accessor calls (mipp_get_*, mipp_scalar_get_*) and C-specific
        assertion templates. Called by TestsBuilderEngineC to avoid duplicating
        the bitwise/logical/tolerance/exact dispatch logic inline.
        """
        if ret_lmul_suffix is None:
            ret_lmul_suffix = lmul_suffix
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
                r_expr_fn = lambda reg: adapter.format_get_k(reg, "i", dt2_raw, ret_lmul_suffix)
                s_expr_fn = lambda reg: adapter.format_scalar_get_k(reg, "i", dt2_raw, ret_lmul_suffix)
            else:
                r_expr_fn = lambda reg: adapter.format_get(reg, "i", dt2_raw, ret_lmul_suffix)
                s_expr_fn = lambda reg: adapter.format_scalar_get(reg, "i", dt2_raw, ret_lmul_suffix)

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

    def build_test_file_content(
        self,
        func_name: str,
        lmul_suffix: str = "m1",
        mkind: str = "",
        lmul: int = 0,
        N: int = 10,
        lmul_list: Optional[List[int]] = None,
        ldiv_list: Optional[List[int]] = None,
        mask_list: Optional[List[str]] = None,
    ) -> str:
        lines = []
        lines.extend(self._render_headers(func_name, N=N))

        datatypes = self.engine._resolve_datatypes(func_name)

        # ISAs that provide the function for this LMUL (registry: ret.lmul, ldiv_mask files...)
        isa_guard = self.engine.isa_guard(func_name, lmul)
        if isa_guard:
            lines.append(f"#if {isa_guard}")
        if lmul < 0:
            lines.append("#if defined(MIPP_LDIV_2)")

        for dt in datatypes:
            lines.extend(self._render_single_test_func(func_name, str(dt), lmul_suffix, mkind=mkind, lmul=lmul))

        lines.extend(self._render_test_case_section(func_name, lmul_suffix, mkind=mkind, lmul=lmul))

        if lmul < 0:
            lines.append("#endif // MIPP_LDIV_2")
        if isa_guard:
            lines.append("#endif // ISA guard")

        return "\n".join(lines)

    def _render_headers(self, func_name: str, N: int = 10) -> List[str]:
        func_spec = self.engine.specs["functions"].get(func_name, {})
        default_spec = self.engine.specs.get("default", {})
        extra_includes = func_spec.get("extra_includes", default_spec.get("extra_includes", []))

        tpl_fixed = self.engine.templates.get("headers", {}).get("all", {}).get("headers_fixed", [])
        lines = self.engine.render_template(tpl_fixed, N_ITER=str(N))
        wrapper_fns = [func_name]
        for aux in list(_AUX_HEADERS) + [a for a in extra_includes if a in _AUX_HEADERS]:
            if aux in self.engine.interfaces and aux not in wrapper_fns:
                wrapper_fns.append(aux)

        # extra_includes: split into known aux names (handled above) and raw strings (injected verbatim)
        extra_aux = [inc for inc in extra_includes if inc not in _AUX_HEADERS]

        # Scalar reference headers first (self-contained), then the public per-function C wrappers.
        lines.extend(sorted(f'#include <mipp/internal/simd_ext/scalar/c/functions/{_match_category(fn)}/{fn}.h>' for fn in wrapper_fns))
        lines.extend(sorted(f'#include <mipp/c/fun/{fn}.h>' for fn in wrapper_fns))
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
        # LMUL of the result (ret.lmul of the prototype): same as the arguments' one for most functions
        ret_lmul = self.engine.result_lmul(func_name, lmul)
        ret_lmul_suffix = lmul_suffix if ret_lmul == lmul else self.engine.lmul_tag(ret_lmul)
        ret_lmul_mult = lmul_mult if ret_lmul == lmul else self.engine.lanes_factor(ret_lmul)
        dt_clean = dt_name.replace(',', '_')
        func_decl = f"static void test_mipp_c_{func_name}_{dt_clean}_{tag}()"

        proto_ref = self.engine.interfaces.get(func_name, {}).get("proto_ref", "")
        is_1arg = self.engine.proto_is_1arg(proto_ref)
        is_3arg = self.engine.proto_is_3arg(proto_ref)
        size_var = f"MIPP_N_{dt1_raw.upper()}{lmul_mult}"
        size_out_var = f"MIPP_N_{dt2_raw.upper()}{ret_lmul_mult}"

        body_lines = [func_decl, "{", "\tstd::mt19937 seed(Catch::getSeed());", "\tfor (unsigned n = 0; n < get_n_iter(); n++)", "\t{"]
        
        # alignas(64): load/store require a pointer aligned on the register size (64 bytes covers AVX-512)
        body_lines.append(f"\t\t[[maybe_unused]] alignas(64) {dt_cstd} inputs1[{size_var}];")
        if not is_1arg:
            body_lines.append(f"\t\t[[maybe_unused]] alignas(64) {dt_cstd} inputs2[{size_var}];")
        if is_3arg:
            body_lines.append(f"\t\t[[maybe_unused]] alignas(64) {dt_cstd} inputs3[{size_var}];")

        args_info = self.engine.get_proto_args_info(func_name)
        n_masks = self.engine.get_required_mask_count(func_name)
        has_mask_var = n_masks >= 1 or mkind in ("mask", "maskz", "masks") or any(arg.get("fixeddatatype") in ("int32", "i32") for arg in args_info)

        if has_mask_var:
            body_lines.append(f"\t\t[[maybe_unused]] int32_t inputs_m[{size_var}];")
            if n_masks >= 2:
                body_lines.append(f"\t\t[[maybe_unused]] int32_t inputs_m2[{size_var}];")
        if mkind == "masks":
            body_lines.append(f"\t\t[[maybe_unused]] alignas(64) {dt_cstd} inputs_src[{size_var}];")

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
        body_lines.extend(self.engine.render_unaligned_input(func_name, dt_cstd, size_var))

        # Loads
        reg_type1 = adapter.format_reg_type(dt1_raw, lmul_suffix)
        # scalar types are distinct per LMUL name: the m0 tests of an LMUL-changing function use the m1 ones
        s_lmul_suffix = "m1" if (lmul == 0 and ret_lmul != lmul) else lmul_suffix
        scalar_reg_type1 = adapter.format_scalar_reg_type(dt1_raw, s_lmul_suffix)

        body_lines.append(f"\t\t[[maybe_unused]] {reg_type1} r1 = {adapter.format_load(dt1_raw, 'inputs1', lmul_suffix)};")
        body_lines.append(f"\t\t[[maybe_unused]] {scalar_reg_type1} s1 = {adapter.format_scalar_load(dt1_raw, 'inputs1', s_lmul_suffix)};")
        if not is_1arg:
            body_lines.append(f"\t\t[[maybe_unused]] {reg_type1} r2 = {adapter.format_load(dt1_raw, 'inputs2', lmul_suffix)};")
            body_lines.append(f"\t\t[[maybe_unused]] {scalar_reg_type1} s2 = {adapter.format_scalar_load(dt1_raw, 'inputs2', s_lmul_suffix)};")
        if is_3arg:
            body_lines.append(f"\t\t[[maybe_unused]] {reg_type1} r3 = {adapter.format_load(dt1_raw, 'inputs3', lmul_suffix)};")
            body_lines.append(f"\t\t[[maybe_unused]] {scalar_reg_type1} s3 = {adapter.format_scalar_load(dt1_raw, 'inputs3', s_lmul_suffix)};")

        if has_mask_var:
            msk_type = adapter.format_msk_type(dt1_raw, lmul_suffix)
            scalar_msk_type = adapter.format_scalar_msk_type(dt1_raw, s_lmul_suffix)
            body_lines.append(f"\t\t[[maybe_unused]] {msk_type} m1 = {adapter.format_set_k(dt1_raw, 'inputs_m', lmul_suffix)};")
            body_lines.append(f"\t\t[[maybe_unused]] {scalar_msk_type} sm1 = {adapter.format_scalar_set_k(dt1_raw, 'inputs_m', s_lmul_suffix)};")
            if n_masks >= 2:
                body_lines.append(f"\t\t[[maybe_unused]] {msk_type} m2 = {adapter.format_set_k(dt1_raw, 'inputs_m2', lmul_suffix)};")
                body_lines.append(f"\t\t[[maybe_unused]] {scalar_msk_type} sm2 = {adapter.format_scalar_set_k(dt1_raw, 'inputs_m2', s_lmul_suffix)};")
        if mkind == "masks":
            body_lines.append(f"\t\t[[maybe_unused]] {reg_type1} rsrc = {adapter.format_load(dt1_raw, 'inputs_src', lmul_suffix)};")
            body_lines.append(f"\t\t[[maybe_unused]] {scalar_reg_type1} ssrc = {adapter.format_scalar_load(dt1_raw, 'inputs_src', s_lmul_suffix)};")

        body_lines.append("")

        dt_func_ext = f"{dt1_raw}_{dt2_raw}" if len(dt_parts) == 2 else dt1_raw
        proto_spec = self.engine.protos.get(proto_ref, {})
        ret_type_kind = proto_spec.get("ret", {}).get("type")
        is_msk_ret = ret_type_kind == "msk"

        if is_msk_ret:
            ret_type_r = adapter.format_msk_type(dt2_raw, ret_lmul_suffix)
            ret_type_s = adapter.format_scalar_msk_type(dt2_raw, ret_lmul_suffix)
        else:
            ret_type_r = adapter.format_reg_type(dt2_raw, ret_lmul_suffix)
            ret_type_s = adapter.format_scalar_reg_type(dt2_raw, ret_lmul_suffix)

        op_args_r = self.engine._build_op_call_args(func_name, mkind, is_scalar=False)
        op_args_s = self.engine._build_op_call_args(func_name, mkind, is_scalar=True)

        is_loop = self.engine.proto_is_loop(proto_ref)
        if not is_loop:
            ret_type_r = f"{dt2_raw}_t"
            ret_type_s = f"{dt2_raw}_t"

        is_void_ret = self.engine.proto_is_void_ret(proto_ref)
        if is_void_ret:
            body_lines.extend(self.engine.render_void_ret_init(dt_cstd, size_out_var, "inputs_src" if mkind == "masks" else "inputs1", func_name=func_name))
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
            ret_lmul_suffix=ret_lmul_suffix,
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

    def tested_lmuls(self, func_name: str, lmul_list: Optional[List[int]], ldiv_list: Optional[List[int]]) -> List[int]:
        """LMULs (1, 2, 4, 8, then -2 for d2) instantiated by the test case of the function: those
        requested, for which the function exists (a result LMUL that does not exist is skipped)."""
        available = [1, 2, 4, 8]
        if lmul_list is not None:
            target = set(lmul_list)
            if 0 in target:
                target.add(1)
            available = [l for l in available if l in target]
        if ldiv_list is None or 2 in ldiv_list:
            available.append(-2)
        return [l for l in available if self.engine.is_test_defined(func_name, l)]

    def _guard_body(self, func_name: str, lines: List[str], n_head: int,
                    lmul_list: Optional[List[int]], ldiv_list: Optional[List[int]]) -> List[str]:
        """Compile the test body (everything after the headers) only for the ISAs that provide the
        function for at least one tested LMUL: the names it uses are not declared on the others."""
        guard = self.engine.isa_guard_any(func_name, self.tested_lmuls(func_name, lmul_list, ldiv_list))
        if guard is None:
            return lines
        return lines[:n_head] + [f"#if {guard}"] + lines[n_head:] + ["#endif // ISA guard"]

    def render_cpp_test_case(
        self,
        dialect_name: str,
        func_name: str,
        supported_mkinds: List[str],
        lmul_list: Optional[List[int]] = None,
        ldiv_list: Optional[List[int]] = None,
    ) -> List[str]:
        lines = []
        func_prefix = "test_mipp_cpp" if dialect_name == "cpp" else "test_mipp_obj"
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

                for lmul_val in self.tested_lmuls(func_name, lmul_list, ldiv_list):
                    # an ISA that does not provide the function for this LMUL does not instantiate it
                    guard = self.engine.isa_guard(func_name, lmul_val)
                    if guard:
                        lines.append(f"#if {guard}")
                    call_expr = f"{func_prefix}_{func_name}<{mk_enum}, {cpp_type}, {lmul_val}>();"
                    if lmul_val > 0:
                        tpl_lmul = self.engine._tpl("func_templates", "obj", "test_section_lmul")
                        lines.extend(self.engine.render_template(tpl_lmul, lmul_str=f"LMUL = {lmul_val}", call_expr=call_expr))
                    else:
                        tpl_ldiv2 = self.engine._tpl("func_templates", "cpp", "test_section_ldiv2")
                        lines.extend(self.engine.render_template(tpl_ldiv2, call_expr=call_expr))
                    if guard:
                        lines.append(f"#endif // ISA guard")

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

        # Wrapper-level headers (coarse per function) instead of the global umbrellas
        # mipp.hpp / mipp_obj.hpp: parse only what the test actually needs.
        wrapper_ns = "obj" if dialect_name == "obj" else "cpp"
        wrapper_fns = [func_name]
        for aux in list(_AUX_HEADERS) + [a for a in extra_includes if a in _AUX_HEADERS]:
            if aux in self.engine.interfaces and aux not in wrapper_fns:
                wrapper_fns.append(aux)
        if dialect_name == "obj":
            # Rvd(const T*), Rvd(T), Rvm(bool) are backed by these obj atoms (fine-grained: not pulled by obj/common.hpp)
            for aux in ("loadu", "set1", "set1_k"):
                if aux in self.engine.interfaces and aux not in wrapper_fns:
                    wrapper_fns.append(aux)
        # Scalar reference headers are self-contained (they pull the ISA detection and rvd/rvm types) and
        # come FIRST: their explicit specializations (hmax<Z,float64_t,-2,SCALAR>, ...) are matched against
        # every visible same-name template, so the obj overloads (Rvm<T,LMUL>) must not be declared yet.
        wrapper_lines = sorted(f'#include <mipp/{wrapper_ns}/fun/{wfn}.hpp>' for wfn in wrapper_fns)

        headers_set.add(f'#include <mipp/internal/simd_ext/scalar/cpp/functions/{cat_func}/{func_name}.hpp>')
        for aux in _AUX_HEADERS:
            if aux in self.engine.interfaces:
                cat_aux = _match_category(aux)
                headers_set.add(f'#include <mipp/internal/simd_ext/scalar/cpp/functions/{cat_aux}/{aux}.hpp>')

        extra_aux = [inc for inc in extra_includes if inc not in _AUX_HEADERS]
        for aux in extra_includes:
            if aux in _AUX_HEADERS:
                cat_aux = _match_category(aux)
                headers_set.add(f'#include <mipp/internal/simd_ext/scalar/cpp/functions/{cat_aux}/{aux}.hpp>')

        lines.extend(sorted(list(headers_set)))
        lines.extend(wrapper_lines)
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
        """Append mask and source register declarations inside an variant (V) constexpr branch.

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
        # alignas(64): load/store require a pointer aligned on the register size (64 bytes covers AVX-512)
        out.append("\t\talignas(64) T inputs1[size];")
        if has_inputs2:
            out.append("\t\talignas(64) T inputs2[size];")
        if is_3arg:
            out.append("\t\talignas(64) T inputs3[size];")
        out.append("\t\t[[maybe_unused]] alignas(64) T inputs_src[size];")
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
        dialect: str = "cpp",
    ) -> List[str]:
        """Render a [&]() { if constexpr (V == ...) { ... } }() lambda for one op call.

        Used by TestsBuilderEngineCpp and TestsBuilderEngineCppObj (r_var and s_var).
        """
        out: List[str] = []
        out.append(f"\t\t" + ("[&]() {" if is_void_ret else f"auto {var_name} = [&]() {{"))
        is_first = True
        for mkind in supported_mkinds:
            mk_enum = self.MK_ENUM[mkind]
            keyword = "if constexpr" if is_first else "else if constexpr"
            is_first = False
            out.append(f"\t\t\t{keyword} (V == {mk_enum})")
            out.append("\t\t\t{")
            self._append_cpp_mask_loads(out, adapter, mkind, n_masks, is_scalar=is_scalar)
            if is_scalar:
                call_code = self.engine.format_cpp_op_call(func_name, mkind, is_scalar=True)
            elif dialect == "obj":
                call_code = self.engine.format_obj_op_call(func_name, mkind)
            else:
                call_code = self.engine.format_cpp_op_call(func_name, mkind, is_scalar=False)
            out.append(f"\t\t\t\t{ret_prefix}{call_code};")
            out.append("\t\t\t}")
        out.append("\t\t}();")
        out.append("")
        return out


class TestsBuilderEngineCpp(TestsBuilderEngineCppBase):

    def build_test_file_content(
        self,
        func_name: str,
        lmul_suffix: str = "m1",
        mkind: str = "",
        lmul: int = 0,
        N: int = 10,
        lmul_list: Optional[List[int]] = None,
        ldiv_list: Optional[List[int]] = None,
        mask_list: Optional[List[str]] = None,
    ) -> str:
        lines = []
        adapter = CppDialectAdapter()
        lines.extend(self._render_headers("cpp", func_name, N=N))
        n_head = len(lines)
        if self.engine.is_product_func(func_name):
            lines.extend(self.engine.render_cpp_conv_helper(func_name))
            lines.append("")

        func_variants = self.engine.interfaces[func_name].get("variants", ["u", "m", "z", "s"])
        supported_mkinds = []
        for m in ["unmasked", "mask", "maskz", "masks"]:
            if mask_list is None or m in mask_list or (m == "unmasked" and "" in mask_list):
                if m == "unmasked" or self.engine._is_mask_kind_supported(func_variants, m):
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

        lines.extend(self.engine.render_cpp_sizes(func_name, adapter, is_product))

        lines.extend(self._render_cpp_input_arrays(
            func_spec, "cpp", is_1arg, is_3arg,
            has_inputs2=(not is_1arg or is_reg_val),
            has_m2=True,
        ))
        lines.extend(self.engine.render_unaligned_input(func_name, "T", "size"))

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
            lines.extend(self.engine.render_void_ret_init("T", "size", "inputs1", func_name=func_name))
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

        lines.extend(self.engine._tpl("func_templates", "obj", "func_footer"))

        lines.extend(self.render_cpp_test_case("cpp", func_name, supported_mkinds, lmul_list=lmul_list, ldiv_list=ldiv_list))
        lines = self._guard_body(func_name, lines, n_head, lmul_list, ldiv_list)
        return "\n".join(lines)


class TestsBuilderEngineObj(TestsBuilderEngineCppBase):

    def build_test_file_content(
        self,
        func_name: str,
        lmul_suffix: str = "m1",
        mkind: str = "",
        lmul: int = 0,
        N: int = 10,
        lmul_list: Optional[List[int]] = None,
        ldiv_list: Optional[List[int]] = None,
        mask_list: Optional[List[str]] = None,
    ) -> str:
        lines = []
        adapter = CppObjDialectAdapter()
        lines.extend(self._render_headers("obj", func_name, N=N))
        n_head = len(lines)
        if self.engine.is_product_func(func_name):
            lines.extend(self.engine.render_cpp_conv_helper(func_name))
            lines.append("")

        func_variants = self.engine.interfaces[func_name].get("variants", ["u", "m", "z", "s"])
        supported_mkinds = []
        for m in ["unmasked", "mask", "maskz", "masks"]:
            if mask_list is None or m in mask_list or (m == "unmasked" and "" in mask_list):
                if m == "unmasked" or self.engine._is_mask_kind_supported(func_variants, m):
                    supported_mkinds.append(m)

        proto_ref = self.engine.interfaces.get(func_name, {}).get("proto_ref", "ret_reg_2args_reg")
        func_spec = self.engine.specs["functions"].get(func_name, {})
        datatypes = self.engine._resolve_datatypes(func_name)
        is_product = any("," in str(dt) for dt in datatypes)
        is_1arg = self.engine.proto_is_1arg(proto_ref)
        is_3arg = self.engine.proto_is_3arg(proto_ref)
        is_reg_val = self.engine.proto_is_reg_val(proto_ref)

        tpl_key = "func_header_product" if is_product else "func_header"
        tpl_hdr = self.engine._tpl("func_templates", "obj", tpl_key)
        lines.extend(self.engine.render_template(tpl_hdr, func_name=func_name))

        lines.extend(self.engine.render_cpp_sizes(func_name, adapter, is_product))

        lines.extend(self._render_cpp_input_arrays(
            func_spec, "obj", is_1arg, is_3arg,
            has_inputs2=(not is_1arg or is_reg_val),
            has_m2=True,
        ))
        lines.extend(self.engine.render_unaligned_input(func_name, "T", "size"))

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
            lines.extend(self.engine.render_void_ret_init("T", "size", "inputs1", func_name=func_name))
            r_var = "res_r"
            s_var = "res_s"
        else:
            r_var = "rres"
            s_var = "sres"

        ret_prefix = "" if is_void_ret else "return "
        n_masks = self.engine.get_required_mask_count(func_name)

        lines.extend(self._render_op_lambda(
            func_name, r_var, is_void_ret, ret_prefix, supported_mkinds, adapter, n_masks, is_scalar=False, dialect="obj"
        ))
        lines.extend(self._render_op_lambda(
            func_name, s_var, is_void_ret, ret_prefix, supported_mkinds, adapter, n_masks, is_scalar=True, dialect="obj"
        ))

        val_lines = self.engine.render_cpp_validation_block(func_name, proto_ref, is_product, r_var=r_var, s_var=s_var, adapter=adapter)
        lines.extend(self.engine.indent_lines(val_lines, 2))

        lines.extend(self.engine._tpl("func_templates", "obj", "func_footer"))

        lines.extend(self.render_cpp_test_case("obj", func_name, supported_mkinds, lmul_list=lmul_list, ldiv_list=ldiv_list))
        lines = self._guard_body(func_name, lines, n_head, lmul_list, ldiv_list)
        return "\n".join(lines)
