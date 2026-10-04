"""
C++ OOP Wrapper & Modular Headers Generator Module
Generates:
1. `include/mipp/internal/interfaces/obj/common.hpp` (defines `Rvd<T, LMUL>` and `Rvm<T, LMUL>` classes directly)
2. `include/mipp/internal/interfaces/obj/functions/<cat>/<func>.hpp` (modular free functions & operators in namespace mipp)
3. `include/mipp/{c, cpp, obj}/fun/<func>.{h, hpp}` (granular per-function headers)
4. `include/mipp/{c, cpp, obj}/cat/<cat>.{h, hpp}` (granular per-category headers)
5. `include/mipp_obj.hpp` (monolithic C++ OOP wrapper for full backwards compatibility)
"""
import os
import sys

from registry import interfaces, categories, protos
from tools import operators_arithm, operators_binary, operators_order
from include_gen import _match_category


def generate_obj_common(output_dir="../include"):
    common_path = os.path.join(output_dir, "mipp", "internal", "interfaces", "obj", "common.hpp")
    os.makedirs(os.path.dirname(common_path), exist_ok=True)

    tpl_path = os.path.join(os.path.dirname(__file__), "templates", "mipp_obj.tpl.hpp")
    with open(tpl_path, "r", encoding="utf-8") as f_tpl:
        content = f_tpl.read()

    with open(common_path, "w", encoding="utf-8") as f:
        f.write(content)


all_binary_ops = {}
all_binary_ops.update(operators_arithm)
all_binary_ops.update(operators_binary)

def generate_obj_func_file(fn, output_dir="../include"):
    cat = _match_category(fn)
    func_dir = os.path.join(output_dir, "mipp", "internal", "interfaces", "obj", "functions", cat)
    os.makedirs(func_dir, exist_ok=True)
    file_path = os.path.join(func_dir, f"{fn}.hpp")

    info = interfaces.get(fn, {})
    p = info.get("proto", {})
    args = [a["type"] for a in p.get("args", [])]
    ms = info.get("mask_support")
    is_maskable = ms.is_maskable() if hasattr(ms, "is_maskable") else False
    is_maskzable = ms.is_maskzable() if hasattr(ms, "is_maskzable") else False
    is_masksable = ms.is_masksable() if hasattr(ms, "is_masksable") else False
    cpp_fn = info.get("cpp_name", fn)

    lines = [
        "#pragma once",
        "",
        '#include "mipp/internal/interfaces/obj/common.hpp"',
        f'#include "mipp/internal/interfaces/cpp/functions/{cat}/{fn}.hpp"',
    ]
    if fn in ("andb", "orb", "xorb", "notb", "andnb"):
        lines.append(f'#include "mipp/internal/interfaces/obj/functions/logic/{fn}_k.hpp"')
    elif fn == "get":
        lines.append('#include "mipp/internal/interfaces/obj/functions/store/get_k.hpp"')
    elif fn == "cast":
        lines.append('#include "mipp/internal/interfaces/obj/functions/reinterpret/cast_k.hpp"')
    lines.extend([
        "",
        "namespace mipp",
        "{"
    ])

    # Category 1: Load / initializers (free functions with _obj suffix)
    if fn in ("load", "loadu"):
        lines.append("template <typename T, int LMUL = 1>")
        lines.append(f"inline Rvd<T, LMUL> {fn}_obj(const T* p0)")
        lines.append(f"{{ return Rvd<T, LMUL>(mipp::{fn}<T, LMUL>(p0)); }}")
        lines.append("")
        if is_maskzable:
            lines.append("template <VARIANT V = Z, typename T, int LMUL = 1>")
            lines.append(f"inline Rvd<T, LMUL> {fn}_obj(const Rvm<T, LMUL>& m0, const T* p0)")
            lines.append(f"{{ return Rvd<T, LMUL>(mipp::{fn}<V, T, LMUL>(m0.m, p0)); }}")
            lines.append("")
        if is_masksable:
            lines.append("template <VARIANT V = S, typename T, int LMUL = 1>")
            lines.append(f"inline Rvd<T, LMUL> {fn}_obj(const Rvm<T, LMUL>& m0, const Rvd<T, LMUL>& rsrc, const T* p0)")
            lines.append(f"{{ return Rvd<T, LMUL>(mipp::{fn}<V, T, LMUL>(m0.m, rsrc.r, p0)); }}")
            lines.append("")

    elif fn == "set":
        lines.append("template <typename T, int LMUL = 1>")
        lines.append("inline Rvd<T, LMUL> set_obj(const T vals[mipp::N<T, LMUL>()])")
        lines.append("{ return Rvd<T, LMUL>(mipp::set<T, LMUL>(vals)); }")
        lines.append("")

    elif fn == "set0":
        lines.append("template <typename T, int LMUL = 1>")
        lines.append("inline Rvd<T, LMUL> set0_obj()")
        lines.append("{ return Rvd<T, LMUL>(mipp::set0<T, LMUL>()); }")
        lines.append("")

    elif fn == "set0_k":
        lines.append("template <typename T, int LMUL = 1>")
        lines.append("inline Rvm<T, LMUL> set0_k_obj()")
        lines.append("{ return Rvm<T, LMUL>(mipp::set0_k<T, LMUL>()); }")
        lines.append("")

    elif fn == "set1":
        lines.append("template <typename T, int LMUL = 1>")
        lines.append("inline Rvd<T, LMUL> set1_obj(const T v0)")
        lines.append("{ return Rvd<T, LMUL>(mipp::set1<T, LMUL>(v0)); }")
        lines.append("")

    elif fn == "set1_k":
        lines.append("template <typename T, int LMUL = 1>")
        lines.append("inline Rvm<T, LMUL> set1_k_obj(const int32_t v0)")
        lines.append("{ return Rvm<T, LMUL>(mipp::set1_k<T, LMUL>(v0)); }")
        lines.append("")

    elif fn == "set_k":
        lines.append("template <typename T, int LMUL = 1>")
        lines.append("inline Rvm<T, LMUL> set_k_obj(const int32_t vals[mipp::N<T, LMUL>()])")
        lines.append("{ return Rvm<T, LMUL>(mipp::set_k<T, LMUL>(vals)); }")
        lines.append("")

    # Category 2: Store / Memory operations
    elif fn in ("store", "storeu"):
        lines.append("template <typename T, int LMUL = 1>")
        lines.append(f"inline void {fn}(T* p0, const Rvd<T, LMUL>& r0)")
        lines.append(f"{{ mipp::{fn}(p0, r0.r); }}")
        lines.append("")
        if is_maskable or is_maskzable:
            mk = "M" if is_maskable else "Z"
            lines.append(f"template <VARIANT V = {mk}, typename T, int LMUL = 1>")
            lines.append(f"inline void {fn}(const Rvm<T, LMUL>& m0, T* p0, const Rvd<T, LMUL>& r0)")
            lines.append(f"{{ mipp::{fn}<V, T, LMUL>(m0.m, p0, r0.r); }}")
            lines.append("")
    elif fn == "gather":
        lines.append("template <typename T, typename T_IDX, int LMUL = 1>")
        lines.append("inline Rvd<T, LMUL> gather(const T* p0, const Rvd<T_IDX, LMUL>& vi)")
        lines.append("{ return Rvd<T, LMUL>(mipp::gather(p0, vi.r)); }")
        lines.append("")
    elif fn == "scatter":
        lines.append("template <typename T, typename T_IDX, int LMUL = 1>")
        lines.append("inline void scatter(T* p0, const Rvd<T_IDX, LMUL>& vi, const Rvd<T, LMUL>& r0)")
        lines.append("{ mipp::scatter(p0, vi.r, r0.r); }")
        lines.append("")
    elif fn == "get":
        lines.append("template <typename T, int LMUL = 1>")
        lines.append("inline T get(const Rvd<T, LMUL>& r0, const size_t idx)")
        lines.append("{ return mipp::get(r0.r, idx); }")
        lines.append("")
    elif fn == "get_k":
        lines.append("template <typename T, int LMUL = 1>")
        lines.append("inline bool get(const Rvm<T, LMUL>& m0, const size_t idx)")
        lines.append("{ return details::mask_get_val<T>(mipp::get(m0.m, idx), typename std::is_floating_point<T>::type()); }")
        lines.append("")
    elif fn == "getfirst":
        lines.append("template <typename T, int LMUL = 1>")
        lines.append("inline T getfirst(const Rvd<T, LMUL>& r0)")
        lines.append("{ return mipp::getfirst(r0.r); }")
        lines.append("")

    # Category 3: Selection (blend)
    elif fn == "blend":
        lines.append("template <typename T, int LMUL = 1>")
        lines.append("inline Rvd<T, LMUL> blend(const Rvm<T, LMUL>& m0, const Rvd<T, LMUL>& r0, const Rvd<T, LMUL>& r1)")
        lines.append("{ return Rvd<T, LMUL>(mipp::blend(m0.m, r0.r, r1.r)); }")
        lines.append("")

    # Category 4: Pure mask operations
    elif args == ["msk", "msk"]:
        lines.append("template <typename T, int LMUL = 1>")
        if fn.startswith("testz"):
            lines.append(f"inline int32_t {fn}(const Rvm<T, LMUL>& m0, const Rvm<T, LMUL>& m1)")
            lines.append(f"{{ return mipp::{cpp_fn}(m0.m, m1.m); }}")
        else:
            lines.append(f"inline Rvm<T, LMUL> {cpp_fn}(const Rvm<T, LMUL>& m0, const Rvm<T, LMUL>& m1)")
            lines.append(f"{{ return Rvm<T, LMUL>(mipp::{cpp_fn}(m0.m, m1.m)); }}")
        lines.append("")

        mask_ops = {
            "andb_k": ("&", "&="),
            "orb_k":  ("|", "|="),
            "xorb_k": ("^", "^="),
        }
        if fn in mask_ops:
            op, op_assign = mask_ops[fn]
            lines.append("template <typename T, int LMUL = 1>")
            lines.append(f"inline Rvm<T, LMUL> operator{op}(const Rvm<T, LMUL>& m0, const Rvm<T, LMUL>& m1)")
            lines.append(f"{{ return mipp::{cpp_fn}(m0, m1); }}")
            lines.append("")
            lines.append("template <typename T, int LMUL = 1>")
            lines.append(f"inline Rvm<T, LMUL>& operator{op_assign}(Rvm<T, LMUL>& m0, const Rvm<T, LMUL>& m1)")
            lines.append(f"{{ m0 = m0 {op} m1; return m0; }}")
            lines.append("")
            lines.append("template <typename T, int LMUL = 1>")
            lines.append(f"inline Rvm<T, LMUL> operator{op}(const Rvm<T, LMUL>& m0, const bool val)")
            lines.append(f"{{ return m0 {op} Rvm<T, LMUL>(val); }}")
            lines.append("")
            lines.append("template <typename T, int LMUL = 1>")
            lines.append(f"inline Rvm<T, LMUL> operator{op}(const bool val, const Rvm<T, LMUL>& m1)")
            lines.append(f"{{ return Rvm<T, LMUL>(val) {op} m1; }}")
            lines.append("")
            lines.append("template <typename T, int LMUL = 1>")
            lines.append(f"inline Rvm<T, LMUL>& operator{op_assign}(Rvm<T, LMUL>& m0, const bool val)")
            lines.append(f"{{ m0 = m0 {op} Rvm<T, LMUL>(val); return m0; }}")
            lines.append("")

    elif args == ["msk"] and fn in ("notb_k", "testz_2"):
        lines.append("template <typename T, int LMUL = 1>")
        ret_t = "int32_t" if fn.startswith("testz") else "Rvm<T, LMUL>"
        lines.append(f"inline {ret_t} {cpp_fn}(const Rvm<T, LMUL>& m0)")
        lines.append(f"{{ return {ret_t if ret_t == 'int32_t' else 'Rvm<T, LMUL>'}(mipp::{cpp_fn}(m0.m)); }}")
        lines.append("")
        if fn == "notb_k":
            lines.append("template <typename T, int LMUL = 1>")
            lines.append("inline Rvm<T, LMUL> operator~(const Rvm<T, LMUL>& m0)")
            lines.append(f"{{ return mipp::{cpp_fn}(m0); }}")
            lines.append("")
            lines.append("template <typename T, int LMUL = 1>")
            lines.append("inline Rvm<T, LMUL> operator!(const Rvm<T, LMUL>& m0)")
            lines.append(f"{{ return mipp::{cpp_fn}(m0); }}")
            lines.append("")

    # Category 5: Reductions (hadd, hadds, hmin, hmax, hmul)
    elif cat == "reduction" and args == ["reg"]:
        lines.append("template <typename T, int LMUL = 1>")
        lines.append(f"inline auto {fn}(const Rvd<T, LMUL>& r0) -> decltype(mipp::{fn}(r0.r))")
        lines.append(f"{{ return mipp::{fn}(r0.r); }}")
        lines.append("")
        if is_maskzable:
            lines.append("template <VARIANT V = Z, typename T, int LMUL = 1>")
            lines.append(f"inline auto {fn}(const Rvm<T, LMUL>& m0, const Rvd<T, LMUL>& r0) -> decltype(mipp::{fn}<V, T, LMUL>(m0.m, r0.r))")
            lines.append(f"{{ return mipp::{fn}<V, T, LMUL>(m0.m, r0.r); }}")
            lines.append("")

    # Category 6: Comparisons (cmpeq, cmplt, ...) -> return Rvm
    elif fn in operators_order:
        op = operators_order[fn]["operation"]
        lines.append("template <typename T, int LMUL = 1>")
        lines.append(f"inline Rvm<T, LMUL> {fn}(const Rvd<T, LMUL>& r0, const Rvd<T, LMUL>& r1)")
        lines.append(f"{{ return Rvm<T, LMUL>(mipp::{fn}(r0.r, r1.r)); }}")
        lines.append("")
        if is_maskzable:
            lines.append("template <VARIANT V = Z, typename T, int LMUL = 1>")
            lines.append(f"inline Rvm<T, LMUL> {fn}(const Rvm<T, LMUL>& m0, const Rvd<T, LMUL>& r0, const Rvd<T, LMUL>& r1)")
            lines.append(f"{{ return Rvm<T, LMUL>(mipp::{fn}<V, T, LMUL>(m0.m, r0.r, r1.r)); }}")
            lines.append("")
        lines.append("template <typename T, int LMUL = 1>")
        lines.append(f"inline Rvm<T, LMUL> operator{op}(const Rvd<T, LMUL>& r0, const Rvd<T, LMUL>& r1)")
        lines.append(f"{{ return mipp::{fn}(r0, r1); }}")
        lines.append("")
        lines.append("template <typename T, int LMUL = 1>")
        lines.append(f"inline Rvm<T, LMUL> operator{op}(const Rvd<T, LMUL>& r0, const T val)")
        lines.append(f"{{ return r0 {op} Rvd<T, LMUL>(val); }}")
        lines.append("")
        lines.append("template <typename T, int LMUL = 1>")
        lines.append(f"inline Rvm<T, LMUL> operator{op}(const T val, const Rvd<T, LMUL>& r1)")
        lines.append(f"{{ return Rvd<T, LMUL>(val) {op} r1; }}")
        lines.append("")

    # Category 7: Conversions & reinterprets
    elif fn == "toreg":
        lines.append("template <typename T, int LMUL = 1>")
        lines.append("inline Rvd<T, LMUL> toreg(const Rvm<T, LMUL>& m0)")
        lines.append("{ return Rvd<T, LMUL>(mipp::toreg(m0.m)); }")
        lines.append("")
    elif fn == "tomsk":
        lines.append("template <typename T, int LMUL = 1>")
        lines.append("inline Rvm<T, LMUL> tomsk(const Rvd<T, LMUL>& r0)")
        lines.append("{ return Rvm<T, LMUL>(mipp::tomsk(r0.r)); }")
        lines.append("")
    elif fn == "cast":
        lines.append("namespace details")
        lines.append("{")
        lines.append("template <typename T_DST>")
        lines.append("struct cast_rvd_helper;")
        lines.append("")
        types_map = [
            ("double", "float64"),
            ("float", "float32"),
            ("int64_t", "int64"),
            ("uint64_t", "uint64"),
            ("int32_t", "int32"),
            ("uint32_t", "uint32"),
            ("int16_t", "int16"),
            ("uint16_t", "uint16"),
            ("int8_t", "int8"),
            ("uint8_t", "uint8"),
        ]
        for c_t, f_suffix in types_map:
            lines.append(f"template <> struct cast_rvd_helper<{c_t}> {{")
            lines.append(f"\ttemplate <typename T_SRC, int LMUL>")
            lines.append(f"\tstatic inline Rvd<{c_t}, LMUL> apply(const Rvd<T_SRC, LMUL>& r0)")
            lines.append(f"\t{{ return Rvd<{c_t}, LMUL>(mipp::cast_{f_suffix}(r0.r)); }}")
            lines.append("};")
        lines.append("} // namespace details")
        lines.append("")
        lines.append("template <typename T_DST, typename T_SRC, int LMUL = 1>")
        lines.append("inline Rvd<T_DST, LMUL> cast(const Rvd<T_SRC, LMUL>& r0)")
        lines.append("{ return details::cast_rvd_helper<T_DST>::apply(r0); }")
        lines.append("")
    elif fn == "cast_k":
        lines.append("namespace details")
        lines.append("{")
        lines.append("template <typename T_DST>")
        lines.append("struct cast_rvm_helper;")
        lines.append("")
        types_map = [
            ("double", "float64"),
            ("float", "float32"),
            ("int64_t", "int64"),
            ("uint64_t", "uint64"),
            ("int32_t", "int32"),
            ("uint32_t", "uint32"),
            ("int16_t", "int16"),
            ("uint16_t", "uint16"),
            ("int8_t", "int8"),
            ("uint8_t", "uint8"),
        ]
        for c_t, f_suffix in types_map:
            lines.append(f"template <> struct cast_rvm_helper<{c_t}> {{")
            lines.append(f"\ttemplate <typename T_SRC, int LMUL>")
            lines.append(f"\tstatic inline Rvm<{c_t}, LMUL> apply(const Rvm<T_SRC, LMUL>& m0)")
            lines.append(f"\t{{ return Rvm<{c_t}, LMUL>(mipp::cast_{f_suffix}(m0.m)); }}")
            lines.append("};")
        lines.append("} // namespace details")
        lines.append("")
        lines.append("template <typename T_DST, typename T_SRC, int LMUL = 1>")
        lines.append("inline Rvm<T_DST, LMUL> cast(const Rvm<T_SRC, LMUL>& m0)")
        lines.append("{ return details::cast_rvm_helper<T_DST>::apply(m0); }")
        lines.append("")
    elif fn == "cvt":
        lines.append("namespace details")
        lines.append("{")
        lines.append("template <typename T_DST>")
        lines.append("struct cvt_rvd_helper;")
        lines.append("")
        types_map = [
            ("double", "float64"),
            ("float", "float32"),
            ("int64_t", "int64"),
            ("uint64_t", "uint64"),
            ("int32_t", "int32"),
            ("uint32_t", "uint32"),
            ("int16_t", "int16"),
            ("uint16_t", "uint16"),
            ("int8_t", "int8"),
            ("uint8_t", "uint8"),
        ]
        for c_t, f_suffix in types_map:
            lines.append(f"template <> struct cvt_rvd_helper<{c_t}> {{")
            lines.append(f"\ttemplate <typename T_SRC, int LMUL>")
            lines.append(f"\tstatic inline Rvd<{c_t}, LMUL> apply(const Rvd<T_SRC, LMUL>& r0)")
            lines.append(f"\t{{ return Rvd<{c_t}, LMUL>(mipp::cvt_{f_suffix}(r0.r)); }}")
            lines.append("};")
        lines.append("} // namespace details")
        lines.append("")
        lines.append("template <typename T_DST, typename T_SRC, int LMUL = 1>")
        lines.append("inline Rvd<T_DST, LMUL> cvt(const Rvd<T_SRC, LMUL>& r0)")
        lines.append("{ return details::cvt_rvd_helper<T_DST>::apply(r0); }")
        lines.append("")
    elif fn == "wcvt":
        lines.append("namespace details")
        lines.append("{")
        lines.append("template <typename T_DST>")
        lines.append("struct wcvt_rvd_helper;")
        lines.append("")
        types_map = [
            ("double", "float64"),
            ("int64_t", "int64"),
            ("uint64_t", "uint64"),
            ("int32_t", "int32"),
            ("uint32_t", "uint32"),
            ("int16_t", "int16"),
            ("uint16_t", "uint16"),
        ]
        for c_t, f_suffix in types_map:
            lines.append(f"template <> struct wcvt_rvd_helper<{c_t}> {{")
            lines.append(f"\ttemplate <typename T_SRC, int LMUL>")
            lines.append(f"\tstatic inline Rvd<{c_t}, LMUL> apply(const Rvd<T_SRC, LMUL>& r0)")
            lines.append(f"\t{{ return Rvd<{c_t}, LMUL>(mipp::wcvt_{f_suffix}(r0.r)); }}")
            lines.append("};")
        lines.append("} // namespace details")
        lines.append("")
        lines.append("template <typename T_DST, typename T_SRC, int LMUL = 1>")
        lines.append("inline Rvd<T_DST, LMUL> wcvt(const Rvd<T_SRC, LMUL>& r0)")
        lines.append("{ return details::wcvt_rvd_helper<T_DST>::apply(r0); }")
        lines.append("")

    # Category 8: General Register Operations (1-arg, 2-arg, 3-arg, shifts)
    else:
        cnt_reg = 0
        cnt_val = 0
        typed_args = []
        raw_args = []
        for a_type in args:
            if a_type == "reg":
                arg_name = f"r{cnt_reg}"
                cnt_reg += 1
                typed_args.append(f"const Rvd<T, LMUL>& {arg_name}")
                raw_args.append(f"{arg_name}.r")
            elif a_type == "val":
                arg_name = f"v{cnt_val}"
                cnt_val += 1
                typed_args.append(f"const int32_t {arg_name}")
                raw_args.append(arg_name)

        typed_str = ", ".join(typed_args)
        raw_str = ", ".join(raw_args)

        # 1. Free function overload
        lines.append("template <typename T, int LMUL = 1>")
        lines.append(f"inline Rvd<T, LMUL> {fn}({typed_str})")
        lines.append(f"{{ return Rvd<T, LMUL>(mipp::{fn}({raw_str})); }}")
        lines.append("")

        # 2. Masked overloads
        if is_maskable:
            lines.append("template <VARIANT V = M, typename T, int LMUL = 1>")
            lines.append(f"inline Rvd<T, LMUL> {fn}(const Rvm<T, LMUL>& m0, {typed_str})")
            lines.append(f"{{ return Rvd<T, LMUL>(mipp::{fn}<V, T, LMUL>(m0.m, {raw_str})); }}")
            lines.append("")
        if is_masksable:
            lines.append("template <VARIANT V = S, typename T, int LMUL = 1>")
            lines.append(f"inline Rvd<T, LMUL> {fn}(const Rvm<T, LMUL>& m0, const Rvd<T, LMUL>& rsrc, {typed_str})")
            lines.append(f"{{ return Rvd<T, LMUL>(mipp::{fn}<V, T, LMUL>(m0.m, rsrc.r, {raw_str})); }}")
            lines.append("")

        # 3. Operators
        if fn in all_binary_ops and args == ["reg", "reg"]:
            op_info = all_binary_ops[fn]
            op = op_info["operation"]
            op_assign = op_info["option"]

            lines.append("template <typename T, int LMUL = 1>")
            lines.append(f"inline Rvd<T, LMUL> operator{op}(const Rvd<T, LMUL>& r0, const Rvd<T, LMUL>& r1)")
            lines.append(f"{{ return mipp::{fn}(r0, r1); }}")
            lines.append("")
            lines.append("template <typename T, int LMUL = 1>")
            lines.append(f"inline Rvd<T, LMUL>& operator{op_assign}(Rvd<T, LMUL>& r0, const Rvd<T, LMUL>& r1)")
            lines.append(f"{{ r0 = r0 {op} r1; return r0; }}")
            lines.append("")
            lines.append("template <typename T, int LMUL = 1>")
            lines.append(f"inline Rvd<T, LMUL> operator{op}(const Rvd<T, LMUL>& r0, const T val)")
            lines.append(f"{{ return r0 {op} Rvd<T, LMUL>(val); }}")
            lines.append("")
            lines.append("template <typename T, int LMUL = 1>")
            lines.append(f"inline Rvd<T, LMUL> operator{op}(const T val, const Rvd<T, LMUL>& r1)")
            lines.append(f"{{ return Rvd<T, LMUL>(val) {op} r1; }}")
            lines.append("")
            lines.append("template <typename T, int LMUL = 1>")
            lines.append(f"inline Rvd<T, LMUL>& operator{op_assign}(Rvd<T, LMUL>& r0, const T val)")
            lines.append(f"{{ r0 = r0 {op} Rvd<T, LMUL>(val); return r0; }}")
            lines.append("")

        elif fn in ("lshift", "rshift"):
            op = "<<" if fn == "lshift" else ">>"
            lines.append("template <typename T, int LMUL = 1>")
            lines.append(f"inline Rvd<T, LMUL> operator{op}(const Rvd<T, LMUL>& r0, const int32_t val)")
            lines.append(f"{{ return mipp::{fn}(r0, val); }}")
            lines.append("")
            lines.append("template <typename T, int LMUL = 1>")
            lines.append(f"inline Rvd<T, LMUL>& operator{op}=(Rvd<T, LMUL>& r0, const int32_t val)")
            lines.append(f"{{ r0 = r0 {op} val; return r0; }}")
            lines.append("")

        elif fn == "neg":
            lines.append("template <typename T, int LMUL = 1>")
            lines.append("inline Rvd<T, LMUL> operator-(const Rvd<T, LMUL>& r0)")
            lines.append("{ return mipp::neg(r0); }")
            lines.append("")

        elif fn == "notb":
            lines.append("template <typename T, int LMUL = 1>")
            lines.append("inline Rvd<T, LMUL> operator~(const Rvd<T, LMUL>& r0)")
            lines.append("{ return mipp::notb(r0); }")
            lines.append("")

    lines.append("} // namespace mipp")

    with open(file_path, "w", encoding="utf-8") as f:
        f.write("\n".join(lines) + "\n")


def generate_obj(include_manager=None, output_dir="../include"):
    """
    Main generator entry point for C++ Object layer:
    1. Generates interfaces/obj/common.hpp
    2. Generates all interfaces/obj/functions/<cat>/<func>.hpp
    3. Generates mipp_obj.hpp including all modular components
    """
    generate_obj_common(output_dir)

    for fn in interfaces:
        generate_obj_func_file(fn, output_dir)

    if include_manager and getattr(include_manager, "granularity", "coarse") == "fine":
        for fn in interfaces:
            cat = _match_category(fn)
            func_variants = ["u"]
            ms = interfaces[fn].get("mask_support")
            if ms:
                if hasattr(ms, "is_maskable") and ms.is_maskable():
                    func_variants.append("m")
                if hasattr(ms, "is_maskzable") and ms.is_maskzable():
                    func_variants.append("z")
                if hasattr(ms, "is_masksable") and ms.is_masksable():
                    func_variants.append("s")
            func_lmuls = ["m1", "m2", "m4", "m8", "d2"]

            # Atomic headers
            for v in func_variants:
                for l in func_lmuls:
                    atom_dir = os.path.join(output_dir, "mipp", "internal", "interfaces", "obj", "functions", cat, v, l)
                    os.makedirs(atom_dir, exist_ok=True)
                    with open(os.path.join(atom_dir, f"{fn}.hpp"), "w", encoding="utf-8") as f:
                        f.write(f"#pragma once\n\n#include \"mipp/internal/interfaces/cpp/functions/{cat}/{v}/{l}/{fn}.hpp\"\n#include \"mipp/internal/interfaces/obj/functions/{cat}/{fn}.hpp\"\n")

            # Variant umbrellas
            for v in func_variants:
                v_dir = os.path.join(output_dir, "mipp", "internal", "interfaces", "obj", "functions", cat, v)
                os.makedirs(v_dir, exist_ok=True)
                with open(os.path.join(v_dir, f"{fn}.hpp"), "w", encoding="utf-8") as f:
                    f.write(f"#pragma once\n\n#include \"mipp/internal/interfaces/cpp/functions/{cat}/{v}/{fn}.hpp\"\n#include \"mipp/internal/interfaces/obj/functions/{cat}/{fn}.hpp\"\n")

            # LMUL umbrellas
            for l in func_lmuls:
                l_dir = os.path.join(output_dir, "mipp", "internal", "interfaces", "obj", "functions", cat, l)
                os.makedirs(l_dir, exist_ok=True)
                with open(os.path.join(l_dir, f"{fn}.hpp"), "w", encoding="utf-8") as f:
                    f.write(f"#pragma once\n\n#include \"mipp/internal/interfaces/cpp/functions/{cat}/{l}/{fn}.hpp\"\n#include \"mipp/internal/interfaces/obj/functions/{cat}/{fn}.hpp\"\n")

    # Generate top-level mipp_obj.hpp
    obj_hpp_path = os.path.join(output_dir, "mipp_obj.hpp")
    with open(obj_hpp_path, "w", encoding="utf-8") as f:
        f.write("#pragma once\n\n")
        f.write('#include "mipp.hpp"\n')
        f.write('#include "mipp/internal/interfaces/obj/common.hpp"\n\n')
        for cat in sorted(categories.keys()):
            f.write(f'#include "mipp/obj/cat/{cat}.hpp"\n')

