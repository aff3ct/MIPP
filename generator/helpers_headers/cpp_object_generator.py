"""
C++ OOP Wrapper & Modular Headers Generator Module
Generates:
1. `include/mipp/internal/interfaces/cpp_obj/common.hpp` (defines `Rvd<T, LMUL>` and `Rvm<T, LMUL>` classes directly)
2. `include/mipp/internal/interfaces/cpp_obj/functions/<cat>/<func>.hpp` (modular free functions & operators in namespace mipp)
3. `include/mipp/{c, cpp, cpp_obj}/fun/<func>.{h, hpp}` (granular per-function headers)
4. `include/mipp/{c, cpp, cpp_obj}/cat/<cat>.{h, hpp}` (granular per-category headers)
5. `include/mipp_obj.hpp` (monolithic C++ OOP wrapper for full backwards compatibility)
"""
import os
import sys

from registry import interfaces, categories, protos
from tools import operators_arithm, operators_binary, operators_order
from include_gen import _match_category


def generate_cpp_obj_common(output_dir="../include"):
    common_path = os.path.join(output_dir, "mipp", "internal", "interfaces", "cpp_obj", "common.hpp")
    os.makedirs(os.path.dirname(common_path), exist_ok=True)

    content = """#pragma once

#include "mipp/internal/interfaces/cpp/common.hpp"
#include "mipp/internal/interfaces/cpp/functions/load/loadu.hpp"
#include "mipp/internal/interfaces/cpp/functions/load/set1.hpp"
#include "mipp/internal/interfaces/cpp/functions/load/set_k.hpp"
#include "mipp/internal/interfaces/cpp/functions/store/get.hpp"
#include "mipp/internal/interfaces/cpp/functions/store/get_k.hpp"

namespace mipp
{

template <typename T, int LMUL = 1>
struct Rvd
{
	using value_type = T;
	static constexpr int lmul = LMUL;
	rvd<T, LMUL> r;

	static constexpr int size() { return mipp::N<T, LMUL>(); }

	inline Rvd() = default;
	inline Rvd(rvd<T, LMUL> r) : r(r) {}
	inline Rvd(const T val) : r(mipp::set1<T, LMUL>(val)) {}
	inline Rvd(const T *data) : r(mipp::loadu<T, LMUL>(data)) {}

	inline T operator[](const size_t index) const { return mipp::get(this->r, index); }
};

template <typename T, int LMUL = 1>
struct Rvm
{
	using value_type = T;
	static constexpr int lmul = LMUL;
	rvm<T, LMUL> m;

	static constexpr int size() { return mipp::N<T, LMUL>(); }

	inline Rvm() = default;
	inline Rvm(rvm<T, LMUL> m) : m(m) {}
	inline Rvm(const int32_t vals[mipp::N<T, LMUL>()]) : m(mipp::set_k<T, LMUL>(vals)) {}

	inline int32_t operator[](const size_t index) const { return mipp::get(this->m, index); }
};

} // namespace mipp
"""
    with open(common_path, "w", encoding="utf-8") as f:
        f.write(content)


def generate_cpp_obj_func_file(fn, output_dir="../include"):
    cat = _match_category(fn)
    func_dir = os.path.join(output_dir, "mipp", "internal", "interfaces", "cpp_obj", "functions", cat)
    os.makedirs(func_dir, exist_ok=True)
    file_path = os.path.join(func_dir, f"{fn}.hpp")

    info = interfaces.get(fn, {})
    p = info.get("proto", {})
    args = [a["type"] for a in p.get("args", [])]
    ms = info.get("mask_support")
    is_maskable = ms.is_maskable() if hasattr(ms, "is_maskable") else False
    is_maskzable = ms.is_maskzable() if hasattr(ms, "is_maskzable") else False
    is_masksable = ms.is_masksable() if hasattr(ms, "is_masksable") else False

    lines = [
        "#pragma once",
        "",
        '#include "mipp/internal/interfaces/cpp_obj/common.hpp"',
        f'#include "mipp/internal/interfaces/cpp/functions/{cat}/{fn}.hpp"',
        "",
        "namespace mipp",
        "{"
    ]

    all_binary_ops = {}
    all_binary_ops.update(operators_arithm)
    all_binary_ops.update(operators_binary)

    # 1. Arithmetic binary ops (+, -, *, /) & logic ops (&, |, ^)
    if fn in all_binary_ops and args == ["reg", "reg"]:
        op_info = all_binary_ops[fn]
        op = op_info["operation"]
        op_assign = op_info["option"]

        lines.append(f"template <typename T, int LMUL = 1>")
        lines.append(f"inline Rvd<T, LMUL> {fn}(const Rvd<T, LMUL>& a, const Rvd<T, LMUL>& b)")
        lines.append(f"{{ return Rvd<T, LMUL>(mipp::{fn}(a.r, b.r)); }}")
        lines.append("")

        if is_maskable:
            lines.append(f"template <MKIND MK = M, typename T, int LMUL = 1>")
            lines.append(f"inline Rvd<T, LMUL> {fn}(const Rvm<T, LMUL>& m, const Rvd<T, LMUL>& a, const Rvd<T, LMUL>& b)")
            lines.append(f"{{ return Rvd<T, LMUL>(mipp::{fn}<MK, T, LMUL>(m.m, a.r, b.r)); }}")
            lines.append("")
        if is_masksable:
            lines.append(f"template <MKIND MK = S, typename T, int LMUL = 1>")
            lines.append(f"inline Rvd<T, LMUL> {fn}(const Rvm<T, LMUL>& m, const Rvd<T, LMUL>& src, const Rvd<T, LMUL>& a, const Rvd<T, LMUL>& b)")
            lines.append(f"{{ return Rvd<T, LMUL>(mipp::{fn}<MK, T, LMUL>(m.m, src.r, a.r, b.r)); }}")
            lines.append("")

        lines.append(f"template <typename T, int LMUL = 1>")
        lines.append(f"inline Rvd<T, LMUL> operator{op}(const Rvd<T, LMUL>& a, const Rvd<T, LMUL>& b)")
        lines.append(f"{{ return mipp::{fn}(a, b); }}")
        lines.append("")

        lines.append(f"template <typename T, int LMUL = 1>")
        lines.append(f"inline Rvd<T, LMUL>& operator{op_assign}(Rvd<T, LMUL>& a, const Rvd<T, LMUL>& b)")
        lines.append(f"{{ a = a {op} b; return a; }}")
        lines.append("")

        lines.append(f"template <typename T, int LMUL = 1>")
        lines.append(f"inline Rvd<T, LMUL> operator{op}(const Rvd<T, LMUL>& a, const T val)")
        lines.append(f"{{ return a {op} Rvd<T, LMUL>(val); }}")
        lines.append("")

        lines.append(f"template <typename T, int LMUL = 1>")
        lines.append(f"inline Rvd<T, LMUL> operator{op}(const T val, const Rvd<T, LMUL>& b)")
        lines.append(f"{{ return Rvd<T, LMUL>(val) {op} b; }}")
        lines.append("")

        lines.append(f"template <typename T, int LMUL = 1>")
        lines.append(f"inline Rvd<T, LMUL>& operator{op_assign}(Rvd<T, LMUL>& a, const T val)")
        lines.append(f"{{ a = a {op} Rvd<T, LMUL>(val); return a; }}")
        lines.append("")

        if fn in operators_binary:
            lines.append(f"template <typename T, int LMUL = 1>")
            lines.append(f"inline Rvm<T, LMUL> {fn}(const Rvm<T, LMUL>& a, const Rvm<T, LMUL>& b)")
            lines.append(f"{{ return Rvm<T, LMUL>(mipp::{fn}(a.m, b.m)); }}")
            lines.append("")

            lines.append(f"template <typename T, int LMUL = 1>")
            lines.append(f"inline Rvm<T, LMUL> operator{op}(const Rvm<T, LMUL>& a, const Rvm<T, LMUL>& b)")
            lines.append(f"{{ return mipp::{fn}(a, b); }}")
            lines.append("")

            lines.append(f"template <typename T, int LMUL = 1>")
            lines.append(f"inline Rvm<T, LMUL>& operator{op_assign}(Rvm<T, LMUL>& a, const Rvm<T, LMUL>& b)")
            lines.append(f"{{ a = a {op} b; return a; }}")
            lines.append("")

    # 2. Comparisons (==, !=, <, <=, >, >=)
    elif fn in operators_order:
        op_info = operators_order[fn]
        op = op_info["operation"]

        lines.append(f"template <typename T, int LMUL = 1>")
        lines.append(f"inline Rvm<T, LMUL> {fn}(const Rvd<T, LMUL>& a, const Rvd<T, LMUL>& b)")
        lines.append(f"{{ return Rvm<T, LMUL>(mipp::{fn}(a.r, b.r)); }}")
        lines.append("")

        if is_maskzable:
            lines.append(f"template <MKIND MK = Z, typename T, int LMUL = 1>")
            lines.append(f"inline Rvm<T, LMUL> {fn}(const Rvm<T, LMUL>& m, const Rvd<T, LMUL>& a, const Rvd<T, LMUL>& b)")
            lines.append(f"{{ return Rvm<T, LMUL>(mipp::{fn}<MK, T, LMUL>(m.m, a.r, b.r)); }}")
            lines.append("")

        lines.append(f"template <typename T, int LMUL = 1>")
        lines.append(f"inline Rvm<T, LMUL> operator{op}(const Rvd<T, LMUL>& a, const Rvd<T, LMUL>& b)")
        lines.append(f"{{ return mipp::{fn}(a, b); }}")
        lines.append("")

        lines.append(f"template <typename T, int LMUL = 1>")
        lines.append(f"inline Rvm<T, LMUL> operator{op}(const Rvd<T, LMUL>& a, const T val)")
        lines.append(f"{{ return a {op} Rvd<T, LMUL>(val); }}")
        lines.append("")

        lines.append(f"template <typename T, int LMUL = 1>")
        lines.append(f"inline Rvm<T, LMUL> operator{op}(const T val, const Rvd<T, LMUL>& b)")
        lines.append(f"{{ return Rvd<T, LMUL>(val) {op} b; }}")
        lines.append("")

        if fn in ("cmpeq", "cmpneq"):
            lines.append(f"template <typename T, int LMUL = 1>")
            lines.append(f"inline Rvm<T, LMUL> operator{op}(const Rvm<T, LMUL>& a, const Rvm<T, LMUL>& b)")
            lines.append(f"{{ return Rvm<T, LMUL>(mipp::{fn}(a.m, b.m)); }}")
            lines.append("")

    # 3. Unary logic: notb
    elif fn == "notb":
        lines.append(f"template <typename T, int LMUL = 1>")
        lines.append(f"inline Rvd<T, LMUL> notb(const Rvd<T, LMUL>& a)")
        lines.append(f"{{ return Rvd<T, LMUL>(mipp::notb(a.r)); }}")
        lines.append("")

        if is_maskable:
            lines.append(f"template <MKIND MK = M, typename T, int LMUL = 1>")
            lines.append(f"inline Rvd<T, LMUL> notb(const Rvm<T, LMUL>& m, const Rvd<T, LMUL>& a)")
            lines.append(f"{{ return Rvd<T, LMUL>(mipp::notb<MK, T, LMUL>(m.m, a.r)); }}")
            lines.append("")
        if is_masksable:
            lines.append(f"template <MKIND MK = S, typename T, int LMUL = 1>")
            lines.append(f"inline Rvd<T, LMUL> notb(const Rvm<T, LMUL>& m, const Rvd<T, LMUL>& src, const Rvd<T, LMUL>& a)")
            lines.append(f"{{ return Rvd<T, LMUL>(mipp::notb<MK, T, LMUL>(m.m, src.r, a.r)); }}")
            lines.append("")

        lines.append(f"template <typename T, int LMUL = 1>")
        lines.append(f"inline Rvd<T, LMUL> operator~(const Rvd<T, LMUL>& a)")
        lines.append(f"{{ return mipp::notb(a); }}")
        lines.append("")

        lines.append(f"template <typename T, int LMUL = 1>")
        lines.append(f"inline Rvm<T, LMUL> notb(const Rvm<T, LMUL>& m)")
        lines.append(f"{{ return Rvm<T, LMUL>(mipp::notb(m.m)); }}")
        lines.append("")

        lines.append(f"template <typename T, int LMUL = 1>")
        lines.append(f"inline Rvm<T, LMUL> operator~(const Rvm<T, LMUL>& m)")
        lines.append(f"{{ return mipp::notb(m); }}")
        lines.append("")

    # 4. Shifts (lshift, rshift)
    elif fn in ("lshift", "rshift"):
        op = "<<" if fn == "lshift" else ">>"
        lines.append(f"template <typename T, int LMUL = 1>")
        lines.append(f"inline Rvd<T, LMUL> {fn}(const Rvd<T, LMUL>& a, const int32_t val)")
        lines.append(f"{{ return Rvd<T, LMUL>(mipp::{fn}(a.r, val)); }}")
        lines.append("")

        if is_maskable:
            lines.append(f"template <MKIND MK = M, typename T, int LMUL = 1>")
            lines.append(f"inline Rvd<T, LMUL> {fn}(const Rvm<T, LMUL>& m, const Rvd<T, LMUL>& a, const int32_t val)")
            lines.append(f"{{ return Rvd<T, LMUL>(mipp::{fn}<MK, T, LMUL>(m.m, a.r, val)); }}")
            lines.append("")
        if is_masksable:
            lines.append(f"template <MKIND MK = S, typename T, int LMUL = 1>")
            lines.append(f"inline Rvd<T, LMUL> {fn}(const Rvm<T, LMUL>& m, const Rvd<T, LMUL>& src, const Rvd<T, LMUL>& a, const int32_t val)")
            lines.append(f"{{ return Rvd<T, LMUL>(mipp::{fn}<MK, T, LMUL>(m.m, src.r, a.r, val)); }}")
            lines.append("")

        lines.append(f"template <typename T, int LMUL = 1>")
        lines.append(f"inline Rvd<T, LMUL> operator{op}(const Rvd<T, LMUL>& a, const int32_t val)")
        lines.append(f"{{ return mipp::{fn}(a, val); }}")
        lines.append("")

        lines.append(f"template <typename T, int LMUL = 1>")
        lines.append(f"inline Rvd<T, LMUL>& operator{op}=(Rvd<T, LMUL>& a, const int32_t val)")
        lines.append(f"{{ a = a {op} val; return a; }}")
        lines.append("")

    # 5. Fused arithmetic: fmadd, fmsub, fnmadd, fnmsub
    elif fn in ("fmadd", "fmsub", "fnmadd", "fnmsub"):
        lines.append(f"template <typename T, int LMUL = 1>")
        lines.append(f"inline Rvd<T, LMUL> {fn}(const Rvd<T, LMUL>& a, const Rvd<T, LMUL>& b, const Rvd<T, LMUL>& c)")
        lines.append(f"{{ return Rvd<T, LMUL>(mipp::{fn}(a.r, b.r, c.r)); }}")
        lines.append("")

        if is_maskable:
            lines.append(f"template <MKIND MK = M, typename T, int LMUL = 1>")
            lines.append(f"inline Rvd<T, LMUL> {fn}(const Rvm<T, LMUL>& m, const Rvd<T, LMUL>& a, const Rvd<T, LMUL>& b, const Rvd<T, LMUL>& c)")
            lines.append(f"{{ return Rvd<T, LMUL>(mipp::{fn}<MK, T, LMUL>(m.m, a.r, b.r, c.r)); }}")
            lines.append("")
        if is_masksable:
            lines.append(f"template <MKIND MK = S, typename T, int LMUL = 1>")
            lines.append(f"inline Rvd<T, LMUL> {fn}(const Rvm<T, LMUL>& m, const Rvd<T, LMUL>& src, const Rvd<T, LMUL>& a, const Rvd<T, LMUL>& b, const Rvd<T, LMUL>& c)")
            lines.append(f"{{ return Rvd<T, LMUL>(mipp::{fn}<MK, T, LMUL>(m.m, src.r, a.r, b.r, c.r)); }}")
            lines.append("")

    # 6. Other arithmetic 2-arg: adds, subs
    elif fn in ("adds", "subs"):
        lines.append(f"template <typename T, int LMUL = 1>")
        lines.append(f"inline Rvd<T, LMUL> {fn}(const Rvd<T, LMUL>& a, const Rvd<T, LMUL>& b)")
        lines.append(f"{{ return Rvd<T, LMUL>(mipp::{fn}(a.r, b.r)); }}")
        lines.append("")

        if is_maskable:
            lines.append(f"template <MKIND MK = M, typename T, int LMUL = 1>")
            lines.append(f"inline Rvd<T, LMUL> {fn}(const Rvm<T, LMUL>& m, const Rvd<T, LMUL>& a, const Rvd<T, LMUL>& b)")
            lines.append(f"{{ return Rvd<T, LMUL>(mipp::{fn}<MK, T, LMUL>(m.m, a.r, b.r)); }}")
            lines.append("")
        if is_masksable:
            lines.append(f"template <MKIND MK = S, typename T, int LMUL = 1>")
            lines.append(f"inline Rvd<T, LMUL> {fn}(const Rvm<T, LMUL>& m, const Rvd<T, LMUL>& src, const Rvd<T, LMUL>& a, const Rvd<T, LMUL>& b)")
            lines.append(f"{{ return Rvd<T, LMUL>(mipp::{fn}<MK, T, LMUL>(m.m, src.r, a.r, b.r)); }}")
            lines.append("")

    # 7. Div2, div4
    elif fn in ("div2", "div4"):
        lines.append(f"template <typename T, int LMUL = 1>")
        lines.append(f"inline Rvd<T, LMUL> {fn}(const Rvd<T, LMUL>& a)")
        lines.append(f"{{ return Rvd<T, LMUL>(mipp::{fn}(a.r)); }}")
        lines.append("")

        if is_maskable:
            lines.append(f"template <MKIND MK = M, typename T, int LMUL = 1>")
            lines.append(f"inline Rvd<T, LMUL> {fn}(const Rvm<T, LMUL>& m, const Rvd<T, LMUL>& a)")
            lines.append(f"{{ return Rvd<T, LMUL>(mipp::{fn}<MK, T, LMUL>(m.m, a.r)); }}")
            lines.append("")
        if is_masksable:
            lines.append(f"template <MKIND MK = S, typename T, int LMUL = 1>")
            lines.append(f"inline Rvd<T, LMUL> {fn}(const Rvm<T, LMUL>& m, const Rvd<T, LMUL>& src, const Rvd<T, LMUL>& a)")
            lines.append(f"{{ return Rvd<T, LMUL>(mipp::{fn}<MK, T, LMUL>(m.m, src.r, a.r)); }}")
            lines.append("")

    # 8. Selection: blend
    elif fn == "blend":
        lines.append(f"template <typename T, int LMUL = 1>")
        lines.append(f"inline Rvd<T, LMUL> blend(const Rvd<T, LMUL>& a, const Rvd<T, LMUL>& b, const Rvm<T, LMUL>& m)")
        lines.append(f"{{ return Rvd<T, LMUL>(mipp::blend(a.r, b.r, m.m)); }}")
        lines.append("")

    # 9. Selection: min, max
    elif fn in ("min", "max"):
        lines.append(f"template <typename T, int LMUL = 1>")
        lines.append(f"inline Rvd<T, LMUL> {fn}(const Rvd<T, LMUL>& a, const Rvd<T, LMUL>& b)")
        lines.append(f"{{ return Rvd<T, LMUL>(mipp::{fn}(a.r, b.r)); }}")
        lines.append("")

        if is_maskable:
            lines.append(f"template <MKIND MK = M, typename T, int LMUL = 1>")
            lines.append(f"inline Rvd<T, LMUL> {fn}(const Rvm<T, LMUL>& m, const Rvd<T, LMUL>& a, const Rvd<T, LMUL>& b)")
            lines.append(f"{{ return Rvd<T, LMUL>(mipp::{fn}<MK, T, LMUL>(m.m, a.r, b.r)); }}")
            lines.append("")
        if is_masksable:
            lines.append(f"template <MKIND MK = S, typename T, int LMUL = 1>")
            lines.append(f"inline Rvd<T, LMUL> {fn}(const Rvm<T, LMUL>& m, const Rvd<T, LMUL>& src, const Rvd<T, LMUL>& a, const Rvd<T, LMUL>& b)")
            lines.append(f"{{ return Rvd<T, LMUL>(mipp::{fn}<MK, T, LMUL>(m.m, src.r, a.r, b.r)); }}")
            lines.append("")

    # 10. andnb
    elif fn == "andnb":
        lines.append(f"template <typename T, int LMUL = 1>")
        lines.append(f"inline Rvd<T, LMUL> andnb(const Rvd<T, LMUL>& a, const Rvd<T, LMUL>& b)")
        lines.append(f"{{ return Rvd<T, LMUL>(mipp::andnb(a.r, b.r)); }}")
        lines.append("")

        if is_maskable:
            lines.append(f"template <MKIND MK = M, typename T, int LMUL = 1>")
            lines.append(f"inline Rvd<T, LMUL> andnb(const Rvm<T, LMUL>& m, const Rvd<T, LMUL>& a, const Rvd<T, LMUL>& b)")
            lines.append(f"{{ return Rvd<T, LMUL>(mipp::andnb<MK, T, LMUL>(m.m, a.r, b.r)); }}")
            lines.append("")
        if is_masksable:
            lines.append(f"template <MKIND MK = S, typename T, int LMUL = 1>")
            lines.append(f"inline Rvd<T, LMUL> andnb(const Rvm<T, LMUL>& m, const Rvd<T, LMUL>& src, const Rvd<T, LMUL>& a, const Rvd<T, LMUL>& b)")
            lines.append(f"{{ return Rvd<T, LMUL>(mipp::andnb<MK, T, LMUL>(m.m, src.r, a.r, b.r)); }}")
            lines.append("")

    # 11. Pure mask logic: andb_k, andnb_k, orb_k, xorb_k
    elif fn in ("andb_k", "andnb_k", "orb_k", "xorb_k"):
        lines.append(f"template <typename T, int LMUL = 1>")
        lines.append(f"inline Rvm<T, LMUL> {fn}(const Rvm<T, LMUL>& a, const Rvm<T, LMUL>& b)")
        lines.append(f"{{ return Rvm<T, LMUL>(mipp::{fn}(a.m, b.m)); }}")
        lines.append("")

    # 12. notb_k
    elif fn == "notb_k":
        lines.append(f"template <typename T, int LMUL = 1>")
        lines.append(f"inline Rvm<T, LMUL> notb_k(const Rvm<T, LMUL>& a)")
        lines.append(f"{{ return Rvm<T, LMUL>(mipp::notb_k(a.m)); }}")
        lines.append("")

    # 13. Math unary (abs, sqrt, sin, cos, neg, etc.)
    elif cat == "math" and args == ["reg"]:
        lines.append(f"template <typename T, int LMUL = 1>")
        lines.append(f"inline Rvd<T, LMUL> {fn}(const Rvd<T, LMUL>& a)")
        lines.append(f"{{ return Rvd<T, LMUL>(mipp::{fn}(a.r)); }}")
        lines.append("")

        if is_maskable:
            lines.append(f"template <MKIND MK = M, typename T, int LMUL = 1>")
            lines.append(f"inline Rvd<T, LMUL> {fn}(const Rvm<T, LMUL>& m, const Rvd<T, LMUL>& a)")
            lines.append(f"{{ return Rvd<T, LMUL>(mipp::{fn}<MK, T, LMUL>(m.m, a.r)); }}")
            lines.append("")
        if is_masksable:
            lines.append(f"template <MKIND MK = S, typename T, int LMUL = 1>")
            lines.append(f"inline Rvd<T, LMUL> {fn}(const Rvm<T, LMUL>& m, const Rvd<T, LMUL>& src, const Rvd<T, LMUL>& a)")
            lines.append(f"{{ return Rvd<T, LMUL>(mipp::{fn}<MK, T, LMUL>(m.m, src.r, a.r)); }}")
            lines.append("")

        if fn == "neg":
            lines.append(f"template <typename T, int LMUL = 1>")
            lines.append(f"inline Rvd<T, LMUL> operator-(const Rvd<T, LMUL>& a)")
            lines.append(f"{{ return mipp::neg(a); }}")
            lines.append("")

    # 14. Math binary: atan2, pow
    elif cat == "math" and args == ["reg", "reg"]:
        lines.append(f"template <typename T, int LMUL = 1>")
        lines.append(f"inline Rvd<T, LMUL> {fn}(const Rvd<T, LMUL>& a, const Rvd<T, LMUL>& b)")
        lines.append(f"{{ return Rvd<T, LMUL>(mipp::{fn}(a.r, b.r)); }}")
        lines.append("")

        if is_maskable:
            lines.append(f"template <MKIND MK = M, typename T, int LMUL = 1>")
            lines.append(f"inline Rvd<T, LMUL> {fn}(const Rvm<T, LMUL>& m, const Rvd<T, LMUL>& a, const Rvd<T, LMUL>& b)")
            lines.append(f"{{ return Rvd<T, LMUL>(mipp::{fn}<MK, T, LMUL>(m.m, a.r, b.r)); }}")
            lines.append("")
        if is_masksable:
            lines.append(f"template <MKIND MK = S, typename T, int LMUL = 1>")
            lines.append(f"inline Rvd<T, LMUL> {fn}(const Rvm<T, LMUL>& m, const Rvd<T, LMUL>& src, const Rvd<T, LMUL>& a, const Rvd<T, LMUL>& b)")
            lines.append(f"{{ return Rvd<T, LMUL>(mipp::{fn}<MK, T, LMUL>(m.m, src.r, a.r, b.r)); }}")
            lines.append("")

    # 15. Math pow2
    elif fn == "pow2":
        lines.append(f"template <typename T, int LMUL = 1>")
        lines.append(f"inline Rvd<T, LMUL> pow2(const Rvd<T, LMUL>& a, const int32_t val)")
        lines.append(f"{{ return Rvd<T, LMUL>(mipp::pow2(a.r, val)); }}")
        lines.append("")

        if is_maskable:
            lines.append(f"template <MKIND MK = M, typename T, int LMUL = 1>")
            lines.append(f"inline Rvd<T, LMUL> pow2(const Rvm<T, LMUL>& m, const Rvd<T, LMUL>& a, const int32_t val)")
            lines.append(f"{{ return Rvd<T, LMUL>(mipp::pow2<MK, T, LMUL>(m.m, a.r, val)); }}")
            lines.append("")
        if is_masksable:
            lines.append(f"template <MKIND MK = S, typename T, int LMUL = 1>")
            lines.append(f"inline Rvd<T, LMUL> pow2(const Rvm<T, LMUL>& m, const Rvd<T, LMUL>& src, const Rvd<T, LMUL>& a, const int32_t val)")
            lines.append(f"{{ return Rvd<T, LMUL>(mipp::pow2<MK, T, LMUL>(m.m, src.r, a.r, val)); }}")
            lines.append("")

    # 16. msb
    elif fn == "msb":
        lines.append(f"template <typename T, int LMUL = 1>")
        lines.append(f"inline Rvd<T, LMUL> msb(const Rvd<T, LMUL>& a)")
        lines.append(f"{{ return Rvd<T, LMUL>(mipp::msb(a.r)); }}")
        lines.append("")

    # 17. Reduction (hadd, hadds, hmul, hmin, hmax)
    elif fn in ("hadd", "hadds", "hmul", "hmin", "hmax"):
        lines.append(f"template <typename T, int LMUL = 1>")
        lines.append(f"inline auto {fn}(const Rvd<T, LMUL>& a) -> decltype(mipp::{fn}(a.r))")
        lines.append(f"{{ return mipp::{fn}(a.r); }}")
        lines.append("")

        if is_maskzable:
            lines.append(f"template <MKIND MK = Z, typename T, int LMUL = 1>")
            lines.append(f"inline auto {fn}(const Rvm<T, LMUL>& m, const Rvd<T, LMUL>& a) -> decltype(mipp::{fn}<MK, T, LMUL>(m.m, a.r))")
            lines.append(f"{{ return mipp::{fn}<MK, T, LMUL>(m.m, a.r); }}")
            lines.append("")

    # 18. Reduction: testz, testz_2
    elif fn == "testz":
        lines.append(f"template <typename T, int LMUL = 1>")
        lines.append(f"inline int32_t testz(const Rvm<T, LMUL>& m1, const Rvm<T, LMUL>& m2)")
        lines.append(f"{{ return mipp::testz(m1.m, m2.m); }}")
        lines.append("")
    elif fn == "testz_2":
        lines.append(f"template <typename T, int LMUL = 1>")
        lines.append(f"inline int32_t testz_2(const Rvm<T, LMUL>& m)")
        lines.append(f"{{ return mipp::testz_2(m.m); }}")
        lines.append("")

    # 19. Load/store operations
    elif fn in ["load", "loadu", "set1", "set_k"]:
        pass
    elif fn == "gather":
        lines.append(f"template <typename T, typename T_IDX, int LMUL = 1>")
        lines.append(f"inline Rvd<T, LMUL> gather(const T* ptr, const Rvd<T_IDX, LMUL>& idx)")
        lines.append(f"{{ return Rvd<T, LMUL>(mipp::gather(ptr, idx.r)); }}")
        lines.append("")
    elif fn == "store":
        lines.append(f"template <typename T, int LMUL = 1>")
        lines.append(f"inline void store(T* ptr, const Rvd<T, LMUL>& a)")
        lines.append(f"{{ mipp::store(ptr, a.r); }}")
        lines.append("")
    elif fn == "storeu":
        lines.append(f"template <typename T, int LMUL = 1>")
        lines.append(f"inline void storeu(T* ptr, const Rvd<T, LMUL>& a)")
        lines.append(f"{{ mipp::storeu(ptr, a.r); }}")
        lines.append("")
    elif fn == "scatter":
        lines.append(f"template <typename T, typename T_IDX, int LMUL = 1>")
        lines.append(f"inline void scatter(T* ptr, const Rvd<T_IDX, LMUL>& idx, const Rvd<T, LMUL>& a)")
        lines.append(f"{{ mipp::scatter(ptr, idx.r, a.r); }}")
        lines.append("")
    elif fn == "get":
        lines.append(f"template <typename T, int LMUL = 1>")
        lines.append(f"inline T get(const Rvd<T, LMUL>& a, const size_t idx)")
        lines.append(f"{{ return mipp::get(a.r, idx); }}")
        lines.append("")
    elif fn == "get_k":
        lines.append(f"template <typename T, int LMUL = 1>")
        lines.append(f"inline int32_t get_k(const Rvm<T, LMUL>& m, const size_t idx)")
        lines.append(f"{{ return mipp::get(m.m, idx); }}")
        lines.append("")
    elif fn == "getfirst":
        lines.append(f"template <typename T, int LMUL = 1>")
        lines.append(f"inline T getfirst(const Rvd<T, LMUL>& a)")
        lines.append(f"{{ return mipp::getfirst(a.r); }}")
        lines.append("")

    # 20. Reinterpret & converts
    elif fn == "toreg":
        lines.append(f"template <typename T, int LMUL = 1>")
        lines.append(f"inline Rvd<T, LMUL> toreg(const Rvm<T, LMUL>& m)")
        lines.append(f"{{ return Rvd<T, LMUL>(mipp::toreg(m.m)); }}")
        lines.append("")
    elif fn == "tomsk":
        lines.append(f"template <typename T, int LMUL = 1>")
        lines.append(f"inline Rvm<T, LMUL> tomsk(const Rvd<T, LMUL>& a)")
        lines.append(f"{{ return Rvm<T, LMUL>(mipp::tomsk(a.r)); }}")
        lines.append("")
    elif fn == "cast":
        lines.append(f"template <typename T_DST, typename T_SRC, int LMUL = 1>")
        lines.append(f"inline Rvd<T_DST, LMUL> cast(const Rvd<T_SRC, LMUL>& a)")
        lines.append(f"{{ return Rvd<T_DST, LMUL>(mipp::cast<T_DST, T_SRC, LMUL>(a.r)); }}")
        lines.append("")
    elif fn == "cast_k":
        lines.append(f"template <typename T_DST, typename T_SRC, int LMUL = 1>")
        lines.append(f"inline Rvm<T_DST, LMUL> cast_k(const Rvm<T_SRC, LMUL>& m)")
        lines.append(f"{{ return Rvm<T_DST, LMUL>(mipp::cast_k<T_DST, T_SRC, LMUL>(m.m)); }}")
        lines.append("")
    elif fn in ("cvt", "wcvt"):
        lines.append(f"template <typename T_DST, typename T_SRC, int LMUL = 1>")
        lines.append(f"inline Rvd<T_DST, LMUL> {fn}(const Rvd<T_SRC, LMUL>& a)")
        lines.append(f"{{ return Rvd<T_DST, LMUL>(mipp::{fn}<T_DST, T_SRC, LMUL>(a.r)); }}")
        lines.append("")

    lines.append("} // namespace mipp")

    with open(file_path, "w", encoding="utf-8") as f:
        f.write("\n".join(lines) + "\n")


def generate_cpp_object(include_manager=None, output_dir="../include"):
    """
    Main generator entry point for C++ Object layer:
    1. Generates interfaces/cpp_obj/common.hpp
    2. Generates all interfaces/cpp_obj/functions/<cat>/<func>.hpp
    3. Generates mipp_obj.hpp including all modular components
    """
    generate_cpp_obj_common(output_dir)

    for fn in interfaces:
        generate_cpp_obj_func_file(fn, output_dir)

    # Generate top-level mipp_obj.hpp
    obj_hpp_path = os.path.join(output_dir, "mipp_obj.hpp")
    with open(obj_hpp_path, "w", encoding="utf-8") as f:
        f.write("#pragma once\n\n")
        f.write('#include "mipp.hpp"\n')
        f.write('#include "mipp/internal/interfaces/cpp_obj/common.hpp"\n\n')
        for cat in sorted(categories.keys()):
            f.write(f'#include "mipp/cpp_obj/cat/{cat}.hpp"\n')

