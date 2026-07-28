"""
Unified Domain and Mask Specification Engine for MIPP Test Generators.
Shared across C, C++ unified, and C++ Object layer test builders.
"""

from typing import Dict, List, Any, Optional, Tuple

class DomainResolver:
    """
    Unified Domain and Mask Specification Engine for MIPP Test Generators.
    Shared across C, C++ unified, and C++ Object layer test builders.
    """

    def _get_var_idx(self, var_name: str) -> int:
        idx_map = {"inputs1": 0, "inputs2": 1, "inputs3": 2}
        return idx_map.get(var_name, 0)

    def _parse_lmul_val(self, lmul_entry: Any) -> str:
        s = str(lmul_entry).strip()
        if s.startswith("m"):
            return s[1:]
        elif s.startswith("d"):
            return f"-{s[1:]}"
        return s

    def _extract_spec_for_var(self, entry: Any, var_idx: int) -> Optional[dict]:
        if isinstance(entry, list):
            if var_idx < len(entry):
                elem = entry[var_idx]
                if isinstance(elem, dict):
                    return elem
            elif entry and isinstance(entry[0], dict):
                return entry[0]
        elif isinstance(entry, dict):
            return entry
        return None

    def _get_domain_node(self, func_spec: dict, var_name: str = "inputs1", mkind: Optional[str] = None) -> Optional[Any]:
        def _search_dict(d: dict) -> Optional[Any]:
            if var_name == "inputs_src":
                if "domain_src" in d:
                    return d["domain_src"]
            inp_dom = d.get("input_domain")
            if inp_dom is not None:
                var_idx = self._get_var_idx(var_name)
                if isinstance(inp_dom, list):
                    if var_idx < len(inp_dom):
                        return inp_dom[var_idx]
                    elif inp_dom:
                        return inp_dom[0]
                elif isinstance(inp_dom, dict):
                    return inp_dom
            if "domain" in d:
                return d["domain"]
            return None

        # 1. Search in specific mkind if provided
        if mkind and mkind in func_spec and isinstance(func_spec[mkind], dict):
            res = _search_dict(func_spec[mkind])
            if res is not None:
                return res

        # 2. Search root of func_spec
        res = _search_dict(func_spec)
        if res is not None:
            return res

        # 3. Search unmasked fallback
        if "unmasked" in func_spec and isinstance(func_spec["unmasked"], dict):
            res = _search_dict(func_spec["unmasked"])
            if res is not None:
                return res

        return None

    def _render_by_define_shell(
        self,
        by_define: dict,
        render_branch_fn,
        fallback_lines: List[str],
    ) -> List[str]:
        """Emits a #if/#elif/#else/#endif block for by_define branches.

        Args:
            by_define:       Mapping of {DEFINE_KEY: define_node}.
            render_branch_fn: Callable(define_node) -> List[str] — generates the
                             inner fill lines for each #if/#elif branch.
            fallback_lines:  Lines to emit in the #else branch.
        """
        res: List[str] = []
        first = True
        for define_key, define_node in by_define.items():
            kw = "#if" if first else "#elif"
            first = False
            res.append(f"{kw} defined({define_key})")
            res.extend(render_branch_fn(define_node))
        res.append("#else")
        res.extend(fallback_lines)
        res.append("#endif")
        return res

    def _extract_distribution(self, func_spec: dict, mkind: Optional[str] = None) -> Tuple[str, Optional[float]]:
        """Extracts (distribution_name, sigma) from func_spec.

        Supports both string form ("normal") and object form ({"type": "normal", "sigma": 2.0}).
        Checks mkind section first, then falls back to top-level func_spec.
        """
        dist_raw = None
        if mkind and mkind in func_spec and isinstance(func_spec[mkind], dict):
            dist_raw = func_spec[mkind].get("distribution")
        if dist_raw is None:
            dist_raw = func_spec.get("distribution", "uniform")

        if isinstance(dist_raw, dict):
            return dist_raw.get("type", "uniform"), dist_raw.get("sigma")
        return str(dist_raw) if dist_raw else "uniform", None

    def resolve_domain_spec(self, func_spec: dict, var_name: str = "inputs1", dt: str = "", lmul: str = "", mkind: Optional[str] = None) -> Optional[dict]:
        domain_node = self._get_domain_node(func_spec, var_name, mkind=mkind)
        if domain_node is None:
            return None

        var_idx = self._get_var_idx(var_name)

        if isinstance(domain_node, list):
            return self._extract_spec_for_var(domain_node, var_idx)

        if isinstance(domain_node, dict):
            raw_dt = dt.replace("_t", "")

            # Check rules
            if "rules" in domain_node and isinstance(domain_node["rules"], list):
                for rule in domain_node["rules"]:
                    r_dt = rule.get("datatype")
                    r_lmul = rule.get("lmul")
                    dt_match = (not r_dt) or (r_dt == raw_dt)
                    lmul_match = (not r_lmul) or (str(r_lmul) == str(lmul))
                    if dt_match and lmul_match:
                        return self._extract_spec_for_var(rule, var_idx) or rule

            # Check by_datatype
            if "by_datatype" in domain_node and isinstance(domain_node["by_datatype"], dict):
                by_dt = domain_node["by_datatype"]
                if raw_dt in by_dt:
                    return self._extract_spec_for_var(by_dt[raw_dt], var_idx)

            # Check by_lmul
            if "by_lmul" in domain_node and isinstance(domain_node["by_lmul"], dict):
                by_lmul = domain_node["by_lmul"]
                if str(lmul) in by_lmul:
                    return self._extract_spec_for_var(by_lmul[str(lmul)], var_idx)

            # Check by_define — return the default spec so callers get a concrete value
            if "by_define" in domain_node and "default" in domain_node:
                return self._extract_spec_for_var(domain_node["default"], var_idx)

            # Check default
            if "default" in domain_node:
                return self._extract_spec_for_var(domain_node["default"], var_idx)

            return domain_node

        return None

    def render_input_filling(self, func_spec: dict, var_name: str = "inputs1", dialect: str = "c",
                              dt_cstd: str = "", lmul_suffix: str = "", lmul: str = "", mkind: str = "") -> List[str]:
        is_cpp = (dialect in ("cpp", "obj"))
        active_lmul = lmul_suffix or lmul
        distribution, sigma = self._extract_distribution(func_spec, mkind=mkind)

        if not is_cpp:
            domain_node = self._get_domain_node(func_spec, var_name, mkind=mkind)

            # by_define support for C dialect: emit #if/#elif/#else/#endif
            if isinstance(domain_node, dict) and "by_define" in domain_node:
                by_define = domain_node["by_define"]
                var_idx = self._get_var_idx(var_name)

                def _c_branch(define_node):
                    branch_spec = self._resolve_c_spec_from_node(define_node, dt_cstd, var_idx)
                    expr = self._spec_to_random_call(
                        branch_spec, is_cpp=False, dt_cstd=dt_cstd,
                        distribution=distribution, sigma=sigma,
                    )
                    return [f"\t\t\t{var_name}[i] = {expr};"]

                fallback_spec = self.resolve_domain_spec(
                    func_spec, var_name=var_name, dt=dt_cstd, lmul=active_lmul, mkind=mkind,
                )
                def_expr = self._spec_to_random_call(
                    fallback_spec, is_cpp=False, dt_cstd=dt_cstd,
                    distribution=distribution, sigma=sigma,
                )
                return self._render_by_define_shell(
                    by_define, _c_branch, [f"\t\t\t{var_name}[i] = {def_expr};"]
                )

            spec = self.resolve_domain_spec(func_spec, var_name=var_name, dt=dt_cstd,
                                            lmul=active_lmul, mkind=mkind)
            expr = self._spec_to_random_call(spec, is_cpp=False, dt_cstd=dt_cstd,
                                             distribution=distribution, sigma=sigma)
            return [f"\t\t\t{var_name}[i] = {expr};"]
        else:
            # Check if func_spec defines specific mkind sections
            has_mkind_sections = any(
                mk in func_spec and isinstance(func_spec[mk], dict) and (
                    "domain" in func_spec[mk] or "input_domain" in func_spec[mk] or "domain_src" in func_spec[mk]
                )
                for mk in ("unmasked", "mask", "maskz", "masks")
            )

            if has_mkind_sections:
                cpp_mk_map = [
                    ("unmasked", "MK == mipp::U"),
                    ("mask", "MK == mipp::M"),
                    ("maskz", "MK == mipp::Z"),
                    ("masks", "MK == mipp::S"),
                ]
                res = []
                first_mk = True
                for mk_key, cpp_cond in cpp_mk_map:
                    # Re-extract distribution per mkind section
                    mk_distribution, mk_sigma = self._extract_distribution(func_spec, mkind=mk_key)
                    inner_lines = self._render_cpp_input_filling_single_mkind(
                        func_spec, var_name, active_lmul, mkind=mk_key,
                        distribution=mk_distribution, sigma=mk_sigma
                    )
                    if inner_lines:
                        kw = "if constexpr" if first_mk else "else if constexpr"
                        first_mk = False
                        res.append(f"\t\t\t{kw} ({cpp_cond})")
                        res.append("\t\t\t{")
                        for line in inner_lines:
                            res.append(f"\t{line}")
                        res.append("\t\t\t}")
                if res:
                    return res

            # Fallback if no mkind specific sections
            return self._render_cpp_input_filling_single_mkind(func_spec, var_name, active_lmul,
                                                                mkind=None, distribution=distribution, sigma=sigma)

    def _resolve_c_spec_from_node(self, node: Any, dt_cstd: str, var_idx: int) -> Optional[dict]:
        """Resolves a concrete spec for the C dialect from a domain node.

        Handles simple specs and nodes with by_datatype.
        """
        if not isinstance(node, dict):
            return self._extract_spec_for_var(node, var_idx) if isinstance(node, list) else node

        raw_dt = dt_cstd.replace("_t", "")

        # Simple spec (has min/max/etc. directly)
        if any(k in node for k in ("min", "max", "exclude_zero", "strictly_positive",
                                    "positive", "strictly_negative", "negative")):
            return self._extract_spec_for_var(node, var_idx)

        # by_datatype
        if "by_datatype" in node and raw_dt in node["by_datatype"]:
            return self._extract_spec_for_var(node["by_datatype"][raw_dt], var_idx)

        # default
        if "default" in node:
            return self._extract_spec_for_var(node["default"], var_idx)

        return None

    def _render_cpp_input_filling_single_mkind(self, func_spec: dict, var_name: str, lmul: str,
                                                mkind: Optional[str] = None,
                                                distribution: str = "uniform",
                                                sigma: Optional[float] = None) -> List[str]:
        domain_node = self._get_domain_node(func_spec, var_name, mkind=mkind)
        var_idx = self._get_var_idx(var_name)

        if isinstance(domain_node, dict):
            by_define = domain_node.get("by_define", {})

            # by_define takes priority: emits #if/#elif/#else/#endif
            # Each branch can contain either a simple spec or a full domain_node.
            if isinstance(by_define, dict) and by_define:
                fallback_spec = domain_node.get("default")
                node_without_define = {k: v for k, v in domain_node.items() if k != "by_define"}

                def _cpp_branch(define_node):
                    return self._render_cpp_domain_node_lines(
                        define_node, var_name, var_idx, lmul, fallback_spec,
                        distribution=distribution, sigma=sigma,
                    )

                default_lines = self._render_cpp_domain_node_lines(
                    node_without_define, var_name, var_idx, lmul, fallback_spec,
                    distribution=distribution, sigma=sigma,
                )
                return self._render_by_define_shell(by_define, _cpp_branch, default_lines)

            return self._render_cpp_domain_node_lines(domain_node, var_name, var_idx, lmul, None,
                                                       distribution=distribution, sigma=sigma)

        spec = self.resolve_domain_spec(func_spec, var_name=var_name, dt="", lmul=lmul, mkind=mkind)
        expr = self._spec_to_random_call(spec, is_cpp=True, distribution=distribution, sigma=sigma)
        return [f"\t\t\t{var_name}[i] = {expr};"]

    def _render_cpp_domain_node_lines(self, node: Any, var_name: str, var_idx: int, lmul: str,
                                       fallback_spec: Optional[Any] = None,
                                       distribution: str = "uniform",
                                       sigma: Optional[float] = None) -> List[str]:
        """Generates fill lines for a domain node (without by_define).

        If node is a simple spec dict, generates a single line.
        If node has by_datatype/by_lmul/rules, generates the corresponding if constexpr chain.
        """
        if not isinstance(node, dict):
            spec = self._extract_spec_for_var(node, var_idx) if isinstance(node, list) else node
            expr = self._spec_to_random_call(spec, is_cpp=True, distribution=distribution, sigma=sigma)
            return [f"\t\t\t{var_name}[i] = {expr};"]

        by_dt = node.get("by_datatype", {})
        rules = node.get("rules", [])
        by_lmul = node.get("by_lmul", {})
        node_default = node.get("default", fallback_spec)

        # Simple spec: the node directly is a domain_spec (has min/max/etc.)
        is_simple_spec = any(k in node for k in ("min", "max", "exclude_zero", "strictly_positive",
                                                   "positive", "strictly_negative", "negative"))
        if is_simple_spec:
            spec = self._extract_spec_for_var(node, var_idx)
            expr = self._spec_to_random_call(spec, is_cpp=True, distribution=distribution, sigma=sigma)
            return [f"\t\t\t{var_name}[i] = {expr};"]

        if isinstance(by_dt, dict) and by_dt:
            res = []
            first = True
            for raw_dt, raw_spec in by_dt.items():
                spec = self._extract_spec_for_var(raw_spec, var_idx)
                if spec is not None:
                    kw = "if constexpr" if first else "else if constexpr"
                    first = False
                    expr = self._spec_to_random_call(spec, is_cpp=True, distribution=distribution, sigma=sigma)
                    res.append(f"\t\t\t{kw} (std::is_same_v<T, {raw_dt}_t>) {var_name}[i] = {expr};")
            if res:
                default_spec = self._extract_spec_for_var(node_default, var_idx)
                if default_spec is None and isinstance(node_default, dict):
                    default_spec = node_default
                def_expr = self._spec_to_random_call(default_spec, is_cpp=True, distribution=distribution, sigma=sigma)
                res.append(f"\t\t\telse {var_name}[i] = {def_expr};")
                return res

        if isinstance(by_lmul, dict) and by_lmul:
            res = []
            first = True
            for raw_lmul, raw_spec in by_lmul.items():
                lmul_val = self._parse_lmul_val(raw_lmul)
                spec = self._extract_spec_for_var(raw_spec, var_idx)
                if spec is not None:
                    kw = "if constexpr" if first else "else if constexpr"
                    first = False
                    expr = self._spec_to_random_call(spec, is_cpp=True, distribution=distribution, sigma=sigma)
                    res.append(f"\t\t\t{kw} (LMUL == {lmul_val}) {var_name}[i] = {expr};")
            if res:
                default_spec = self._extract_spec_for_var(node_default, var_idx)
                if default_spec is None and isinstance(node_default, dict):
                    default_spec = node_default
                def_expr = self._spec_to_random_call(default_spec, is_cpp=True, distribution=distribution, sigma=sigma)
                res.append(f"\t\t\telse {var_name}[i] = {def_expr};")
                return res

        if isinstance(rules, list) and rules:
            res = []
            first = True
            for rule in rules:
                r_dt = rule.get("datatype")
                r_lmul = rule.get("lmul")
                cond_parts = []
                if r_dt:
                    cond_parts.append(f"std::is_same_v<T, {r_dt}_t>")
                if r_lmul:
                    lmul_val = self._parse_lmul_val(r_lmul)
                    cond_parts.append(f"LMUL == {lmul_val}")
                spec = self._extract_spec_for_var(rule, var_idx) or rule
                kw = "if constexpr" if first else "else if constexpr"
                first = False
                expr = self._spec_to_random_call(spec, is_cpp=True, distribution=distribution, sigma=sigma)
                if cond_parts:
                    cond_str = " && ".join(cond_parts)
                    res.append(f"\t\t\t{kw} ({cond_str}) {var_name}[i] = {expr};")
                else:
                    res.append(f"\t\t\t{var_name}[i] = {expr};")
            if res:
                default_spec = self._extract_spec_for_var(node_default, var_idx)
                if default_spec is None and isinstance(node_default, dict):
                    default_spec = node_default
                def_expr = self._spec_to_random_call(default_spec, is_cpp=True, distribution=distribution, sigma=sigma)
                res.append(f"\t\t\telse {var_name}[i] = {def_expr};")
                return res

        # Fallback: use default or direct spec from node
        default_spec = self._extract_spec_for_var(node_default, var_idx)
        if default_spec is None and isinstance(node_default, dict):
            default_spec = node_default
        expr = self._spec_to_random_call(default_spec, is_cpp=True, distribution=distribution, sigma=sigma)
        return [f"\t\t\t{var_name}[i] = {expr};"]

    def _spec_to_random_call(self, spec: Optional[dict], is_cpp: bool = False,
                              dt_cstd: str = "", distribution: str = "uniform",
                              sigma: Optional[float] = None) -> str:
        """Generates the appropriate rnd:: call based on domain spec and distribution.

        Supports 'uniform' (default) and 'normal' distributions.
        For 'normal' with min/max: uses truncated normal (rejection sampling).
        For 'normal' with named variants: uses the corresponding normal_* helper.
        """
        T_str = "T" if is_cpp else dt_cstd
        dist = distribution if distribution in ("uniform", "normal") else "uniform"

        if not spec:
            if dist == "normal":
                if sigma is not None:
                    return f"rnd::normal<{T_str}>(seed, static_cast<{T_str}>(0), static_cast<{T_str}>({sigma}))"
                return f"rnd::normal<{T_str}>(seed)"
            return f"rnd::uniform<{T_str}>(seed)"

        mn = spec.get("min")
        mx = spec.get("max")
        ex_zero = spec.get("exclude_zero", False)
        s_pos = spec.get("strictly_positive", False)
        pos = spec.get("positive", False)
        s_neg = spec.get("strictly_negative", False)
        neg = spec.get("negative", False)

        sigma_suffix = f", static_cast<{T_str}>({sigma})" if sigma is not None else ""

        if mn is not None and mx is not None:
            if dist == "normal":
                mu = (mn + mx) / 2
                sig = sigma if sigma is not None else (mx - mn) / 6  # 99.7% of values within [min, max]
                if ex_zero:
                    return (f"rnd::normal_exclude_zero<{T_str}>(seed, "
                            f"static_cast<{T_str}>({mn}), static_cast<{T_str}>({mx}), "
                            f"static_cast<{T_str}>({mu}), static_cast<{T_str}>({sig}))")
                return (f"rnd::normal<{T_str}>(seed, "
                        f"static_cast<{T_str}>({mn}), static_cast<{T_str}>({mx}), "
                        f"static_cast<{T_str}>({mu}), static_cast<{T_str}>({sig}))")
            # uniform
            if ex_zero:
                return f"rnd::uniform_exclude_zero<{T_str}>(seed, static_cast<{T_str}>({mn}), static_cast<{T_str}>({mx}))"
            return f"rnd::uniform<{T_str}>(seed, static_cast<{T_str}>({mn}), static_cast<{T_str}>({mx}))"

        # Named variant cases (strictly_positive, etc.)
        if s_pos:
            return f"rnd::{dist}_strictly_positive<{T_str}>(seed{sigma_suffix})"
        if pos:
            return f"rnd::{dist}_positive<{T_str}>(seed{sigma_suffix})"
        if s_neg:
            return f"rnd::{dist}_strictly_negative<{T_str}>(seed{sigma_suffix})"
        if neg:
            return f"rnd::{dist}_negative<{T_str}>(seed{sigma_suffix})"
        if ex_zero:
            return f"rnd::{dist}_exclude_zero<{T_str}>(seed{sigma_suffix})"

        # Default: unconstrained
        if dist == "normal":
            if sigma is not None:
                return f"rnd::normal<{T_str}>(seed, static_cast<{T_str}>(0), static_cast<{T_str}>({sigma}))"
            return f"rnd::normal<{T_str}>(seed)"
        return f"rnd::uniform<{T_str}>(seed)"

    def _format_mask_call(self, pattern: str, var_name: str = "inputs_m") -> str:
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

    def render_mask_filling(self, func_spec: dict, var_name: str = "inputs_m", dialect: str = "c", mkind: str = "") -> List[str]:
        is_cpp = (dialect in ("cpp", "obj"))

        if not is_cpp:
            pattern = func_spec.get(mkind, {}).get("mask_pattern") if mkind else None
            if not pattern:
                pattern = func_spec.get("mask_pattern", "uniform_bool")
            return [f"\t\t\t{self._format_mask_call(pattern, var_name)}"]
        else:
            patterns = {}
            for mk in ("mask", "maskz", "masks"):
                pat = func_spec.get(mk, {}).get("mask_pattern")
                if pat:
                    patterns[mk] = pat

            if patterns:
                cpp_mk_map = [
                    ("mask", "MK == mipp::M"),
                    ("maskz", "MK == mipp::Z"),
                    ("masks", "MK == mipp::S"),
                ]
                res = []
                first_mk = True
                for mk_key, cpp_cond in cpp_mk_map:
                    pat = patterns.get(mk_key, func_spec.get("mask_pattern", "uniform_bool"))
                    kw = "if constexpr" if first_mk else "else if constexpr"
                    first_mk = False
                    res.append(f"\t\t\t{kw} ({cpp_cond}) {self._format_mask_call(pat, var_name)}")
                def_pat = func_spec.get("mask_pattern", "uniform_bool")
                res.append(f"\t\t\telse {self._format_mask_call(def_pat, var_name)}")
                return res

            pattern = func_spec.get("mask_pattern", "uniform_bool")
            return [f"\t\t\t{self._format_mask_call(pattern, var_name)}"]
