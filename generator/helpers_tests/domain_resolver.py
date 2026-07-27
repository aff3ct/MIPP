"""
Unified Domain and Mask Specification Engine for MIPP Test Generators.
Shared across C, C++ unified, and C++ Object layer test builders.
"""

from typing import Dict, List, Any, Optional

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

            # Check default
            if "default" in domain_node:
                return self._extract_spec_for_var(domain_node["default"], var_idx)

            return domain_node

        return None

    def render_input_filling(self, func_spec: dict, var_name: str = "inputs1", dialect: str = "c", dt_cstd: str = "", lmul_suffix: str = "", lmul: str = "", mkind: str = "") -> List[str]:
        is_cpp = (dialect in ("cpp", "obj"))
        active_lmul = lmul_suffix or lmul

        if not is_cpp:
            spec = self.resolve_domain_spec(func_spec, var_name=var_name, dt=dt_cstd, lmul=active_lmul, mkind=mkind)
            expr = self._spec_to_uniform_call(spec, is_cpp=False, dt_cstd=dt_cstd)
            return [f"\t\t\t{var_name}[i] = {expr};"]
        else:
            # Check if func_spec defines specific mkind sections
            has_mkind_sections = any(
                mk in func_spec and isinstance(func_spec[mk], dict) and ("domain" in func_spec[mk] or "input_domain" in func_spec[mk] or "domain_src" in func_spec[mk])
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
                    inner_lines = self._render_cpp_input_filling_single_mkind(func_spec, var_name, active_lmul, mkind=mk_key)
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
            return self._render_cpp_input_filling_single_mkind(func_spec, var_name, active_lmul, mkind=None)

    def _render_cpp_input_filling_single_mkind(self, func_spec: dict, var_name: str, lmul: str, mkind: Optional[str] = None) -> List[str]:
        domain_node = self._get_domain_node(func_spec, var_name, mkind=mkind)
        var_idx = self._get_var_idx(var_name)

        if isinstance(domain_node, dict):
            by_dt = domain_node.get("by_datatype", {})
            rules = domain_node.get("rules", [])
            by_lmul = domain_node.get("by_lmul", {})

            if isinstance(by_dt, dict) and by_dt:
                res = []
                first = True
                for raw_dt, raw_spec in by_dt.items():
                    spec = self._extract_spec_for_var(raw_spec, var_idx)
                    if spec is not None:
                        kw = "if constexpr" if first else "else if constexpr"
                        first = False
                        expr = self._spec_to_uniform_call(spec, is_cpp=True)
                        res.append(f"\t\t\t{kw} (std::is_same_v<T, {raw_dt}_t>) {var_name}[i] = {expr};")
                if res:
                    default_spec = self._extract_spec_for_var(domain_node.get("default"), var_idx)
                    def_expr = self._spec_to_uniform_call(default_spec, is_cpp=True)
                    res.append(f"\t\t\telse {var_name}[i] = {def_expr};")
                    return res

            elif isinstance(by_lmul, dict) and by_lmul:
                res = []
                first = True
                for raw_lmul, raw_spec in by_lmul.items():
                    lmul_val = self._parse_lmul_val(raw_lmul)
                    spec = self._extract_spec_for_var(raw_spec, var_idx)
                    if spec is not None:
                        kw = "if constexpr" if first else "else if constexpr"
                        first = False
                        expr = self._spec_to_uniform_call(spec, is_cpp=True)
                        res.append(f"\t\t\t{kw} (LMUL == {lmul_val}) {var_name}[i] = {expr};")
                if res:
                    default_spec = self._extract_spec_for_var(domain_node.get("default"), var_idx)
                    def_expr = self._spec_to_uniform_call(default_spec, is_cpp=True)
                    res.append(f"\t\t\telse {var_name}[i] = {def_expr};")
                    return res

            elif isinstance(rules, list) and rules:
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
                    expr = self._spec_to_uniform_call(spec, is_cpp=True)
                    if cond_parts:
                        cond_str = " && ".join(cond_parts)
                        res.append(f"\t\t\t{kw} ({cond_str}) {var_name}[i] = {expr};")
                    else:
                        res.append(f"\t\t\t{var_name}[i] = {expr};")
                if res:
                    default_spec = self._extract_spec_for_var(domain_node.get("default"), var_idx)
                    def_expr = self._spec_to_uniform_call(default_spec, is_cpp=True)
                    res.append(f"\t\t\telse {var_name}[i] = {def_expr};")
                    return res

        spec = self.resolve_domain_spec(func_spec, var_name=var_name, dt="", lmul=lmul, mkind=mkind)
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
