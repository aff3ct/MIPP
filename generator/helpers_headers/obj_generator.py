"""
C++ OOP Wrapper & Modular Headers Generator Module
Generates:
1. `include/mipp/internal/interfaces/obj/common.hpp` (defines `Vd<T, LMUL>` and `Vm<T, LMUL>` classes directly)
2. `include/mipp/internal/interfaces/obj/functions/<cat>/<func>.hpp` (modular free functions & operators in namespace mipp)
3. `include/mipp/{c, cpp, obj}/fun/<func>.{h, hpp}` (granular per-function headers)
4. `include/mipp/{c, cpp, obj}/cat/<cat>.{h, hpp}` (granular per-category headers)
5. `include/mipp_obj.hpp` (monolithic C++ OOP wrapper for full backwards compatibility)
"""
import os
import sys

from registry import interfaces, categories, protos
from tools import operators_arithm, operators_binary, operators_order, changes_lmul, is_defined_for_lmul, resolve_ret_lmul
from include_gen import _match_category


def generate_obj_common(output_dir="../include", fine=False):
    common_path = os.path.join(output_dir, "mipp", "internal", "interfaces", "obj", "common.hpp")
    os.makedirs(os.path.dirname(common_path), exist_ok=True)

    # Fine mode: Vd/Vm go through traits specialised by the obj atoms (no cpp function header pulled here).
    tpl_name = "mipp_obj_fine.tpl.hpp" if fine else "mipp_obj.tpl.hpp"
    tpl_path = os.path.join(os.path.dirname(__file__), "templates", tpl_name)
    with open(tpl_path, "r", encoding="utf-8") as f_tpl:
        content = f_tpl.read()

    with open(common_path, "w", encoding="utf-8") as f:
        f.write(content)


all_binary_ops = {}
all_binary_ops.update(operators_arithm)
all_binary_ops.update(operators_binary)

# Obj functions whose body historically pulls the obj body of their mask partner (`_k`)
# so that a single name (e.g. `cast`) works for both registers and masks.
_OBJ_PARTNERS = {
    "andb": "andb_k", "orb": "orb_k", "xorb": "xorb_k", "notb": "notb_k", "andnb": "andnb_k",
    "get": "get_k",
    "cast": "cast_k",
}

# Fine mode: the obj atom (variant u) of these functions also specialises, per LMUL, the trait that backs the
# matching Vd/Vm member (see templates/mipp_obj_fine.tpl.hpp).
# value: (trait, return type, parameters, call). `{L}` is replaced by the LMUL value of the granule.
_OBJ_MEMBER_OPS = {
    "loadu": ("vd_loadu_op", "vd<T, {L}>", "const T* p0", "mipp::loadu<T, {L}>(p0)"),
    "set1": ("vd_set1_op", "vd<T, {L}>", "const T s0", "mipp::set1<T, {L}>(s0)"),
    "get": ("vd_get_op", "T", "const vd<T, {L}>& r0, const size_t idx", "mipp::get(r0, idx)"),
    "set1_k": ("vm_set1_k_op", "vm<T, {L}>", "const int32_t s0", "mipp::set1_k<T, {L}>(s0)"),
    "set_k": ("vm_set_k_op", "vm<T, {L}>", "const int32_t* vals", "mipp::set_k<T, {L}>(vals)"),
    "get_k": ("vm_get_k_op", "bool", "const vm<T, {L}>& m0, const size_t idx",
              "mask_get_val<T>(mipp::get(m0, idx), typename std::is_floating_point<T>::type())"),
    # lo / hi / combine: `{D}` / `{U}` are the LMULs below / above `{L}`. The functions are called by their
    # (unqualified) name: the cpp granule of the LMUL is included before, and the register types of the ISAs are
    # not always in namespace mipp (so argument-dependent lookup cannot be relied on).
    "lo": ("vd_lo_op", "Vd<T, {D}>", "const vd<T, {L}>& r0", "lo(r0)"),
    "hi": ("vd_hi_op", "Vd<T, {D}>", "const vd<T, {L}>& r0", "hi(r0)"),
    "combine": ("vd_combine_op", "Vd<T, {U}>", "const vd<T, {L}>& r0, const vd<T, {L}>& r1", "combine(r0, r1)"),
    "lo_k": ("vm_lo_op", "Vm<T, {D}>", "const vm<T, {L}>& m0", "lo(m0)"),
    "hi_k": ("vm_hi_op", "Vm<T, {D}>", "const vm<T, {L}>& m0", "hi(m0)"),
    "combine_k": ("vm_combine_op", "Vm<T, {U}>", "const vm<T, {L}>& m0, const vm<T, {L}>& m1", "combine(m0, m1)"),
}


def _variants_of(fn):
    variants = ["u"]
    ms = interfaces[fn].get("variants")
    if ms:
        if hasattr(ms, "is_maskable") and ms.is_maskable():
            variants.append("m")
        if hasattr(ms, "is_maskzable") and ms.is_maskzable():
            variants.append("z")
        if hasattr(ms, "is_masksable") and ms.is_masksable():
            variants.append("s")
    return variants


def generate_obj_func_file(fn, output_dir="../include", fine=False):
    cat = _match_category(fn)
    func_dir = os.path.join(output_dir, "mipp", "internal", "interfaces", "obj", "functions", cat)
    os.makedirs(func_dir, exist_ok=True)
    file_path = os.path.join(func_dir, f"{fn}.hpp")

    info = interfaces.get(fn, {})
    p = info.get("proto", {})
    args = [a["type"] for a in p.get("args", [])]
    ms = info.get("variants")
    is_maskable = ms.is_maskable() if hasattr(ms, "is_maskable") else False
    is_maskzable = ms.is_maskzable() if hasattr(ms, "is_maskzable") else False
    is_masksable = ms.is_masksable() if hasattr(ms, "is_masksable") else False
    cpp_fn = info.get("cpp_name", fn)

    lines = [
        "#pragma once",
        "",
        '#include "mipp/internal/interfaces/obj/common.hpp"',
    ]
    # In fine-grained mode the cpp dependency is NOT pulled here (it would include every
    # cpp variant/LMUL of `fn`): the obj atoms/umbrellas include exactly the cpp granule needed
    # before including this file.
    if not fine:
        lines.append(f'#include "mipp/internal/interfaces/cpp/functions/{cat}/{fn}.hpp"')
    # Partner (`_k`) include: in fine mode it is handled by the atoms/umbrellas (they include the
    # partner's own cpp granule first); here it would be parsed before its cpp declarations.
    if not fine:
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
    body_start = len(lines)

    # Category 1: Load / initializers (free functions with _obj suffix)
    if fn in ("load", "loadu", "loadu_unzip"):
        lines.append("template <typename T, int LMUL = 1>")
        lines.append(f"inline Vd<T, LMUL> {fn}_obj(const T* p0)")
        lines.append(f"{{ return Vd<T, LMUL>(mipp::{fn}<T, LMUL>(p0)); }}")
        lines.append("")
        if is_maskzable:
            lines.append("template <VARIANT V = Z, typename T, int LMUL = 1>")
            lines.append(f"inline Vd<T, LMUL> {fn}_obj(const Vm<T, LMUL>& m0, const T* p0)")
            lines.append(f"{{ return Vd<T, LMUL>(mipp::{fn}<V, T, LMUL>(m0.m, p0)); }}")
            lines.append("")
        if is_masksable:
            lines.append("template <VARIANT V = S, typename T, int LMUL = 1>")
            lines.append(f"inline Vd<T, LMUL> {fn}_obj(const Vm<T, LMUL>& m0, const Vd<T, LMUL>& rsrc, const T* p0)")
            lines.append(f"{{ return Vd<T, LMUL>(mipp::{fn}<V, T, LMUL>(m0.m, rsrc.r, p0)); }}")
            lines.append("")

    # Category 1c: lanes moved by a register of indices (unsigned, of the width of T) and by a mask (compress...)
    elif fn in ("permute", "permute_b128", "permute2"):
        idx_t = "Vd<typename details::uint_of<T>::type, LMUL>"
        regs = ["r0"] if fn != "permute2" else ["r0", "r1"]
        idx = "r1" if fn != "permute2" else "r2"
        typed = ", ".join([f"const Vd<T, LMUL>& {r}" for r in regs] + [f"const {idx_t}& {idx}"])
        raw = ", ".join([f"{r}.r" for r in regs] + [f"{idx}.r"])
        lines.append("template <typename T, int LMUL = 1>")
        lines.append(f"inline Vd<T, LMUL> {fn}({typed})")
        lines.append(f"{{ return Vd<T, LMUL>(mipp::{fn}({raw})); }}")
        lines.append("")
        lines.append("template <VARIANT V = M, typename T, int LMUL = 1>")
        lines.append(f"inline Vd<T, LMUL> {fn}(const Vm<T, LMUL>& m0, {typed})")
        lines.append(f"{{ return Vd<T, LMUL>(mipp::{fn}<V, T, LMUL>(m0.m, {raw})); }}")
        lines.append("")
        lines.append("template <VARIANT V = S, typename T, int LMUL = 1>")
        lines.append(f"inline Vd<T, LMUL> {fn}(const Vm<T, LMUL>& m0, const Vd<T, LMUL>& rsrc, {typed})")
        lines.append(f"{{ return Vd<T, LMUL>(mipp::{fn}<V, T, LMUL>(m0.m, rsrc.r, {raw})); }}")
        lines.append("")
    elif fn in ("compress", "expand"):
        lines.append("template <typename T, int LMUL = 1>")
        lines.append(f"inline Vd<T, LMUL> {fn}(const Vd<T, LMUL>& r0, const Vm<T, LMUL>& m0)")
        lines.append(f"{{ return Vd<T, LMUL>(mipp::{fn}(r0.r, m0.m)); }}")
        lines.append("")
    elif fn in ("storeu_compress", "storeuf_compress"):
        lines.append("template <typename T, int LMUL = 1>")
        lines.append(f"inline int32_t {fn}(T* p0, const Vd<T, LMUL>& r0, const Vm<T, LMUL>& m0)")
        lines.append(f"{{ return mipp::{fn}(p0, r0.r, m0.m); }}")
        lines.append("")
    elif fn == "loadu_expand":
        lines.append("template <typename T, int LMUL = 1>")
        lines.append(f"inline Vd<T, LMUL> {fn}(const T* p0, const Vm<T, LMUL>& m0)")
        lines.append(f"{{ return Vd<T, LMUL>(mipp::{fn}(p0, m0.m)); }}")
        lines.append("")

    # Category 1a: scalar forms (`sub_vs`, `sub_sv`, `fmadd_vsv`, `cmplt_vs`, `select_vs`... see forms.py): overloads
    # of the base function (`mipp::sub(r, s)`), the scalars of type T exactly (no promotion: `Vd<int8_t> - 300`
    # does not compile, as T is deduced from both the register and the scalar).
    elif info.get("form_of"):
        ret = "Vm<T, LMUL>" if p["ret"]["type"] == "msk" else "Vd<T, LMUL>"
        typed_args, raw_args = [], []
        cnt = {"reg": 0, "msk": 0, "val": 0}
        for a_type in args:
            i = cnt[a_type]
            cnt[a_type] += 1
            if a_type == "reg":
                typed_args.append(f"const Vd<T, LMUL>& r{i}")
                raw_args.append(f"r{i}.r")
            elif a_type == "msk":
                typed_args.append(f"const Vm<T, LMUL>& m{i}")
                raw_args.append(f"m{i}.m")
            else:
                typed_args.append(f"const T s{i}")
                raw_args.append(f"s{i}")
        typed_str, raw_str = ", ".join(typed_args), ", ".join(raw_args)
        lines.append("template <typename T, int LMUL = 1>")
        lines.append(f"inline {ret} {cpp_fn}({typed_str})")
        lines.append(f"{{ return {ret}(mipp::{cpp_fn}({raw_str})); }}")
        lines.append("")
        if is_maskable or is_maskzable:
            # one overload for the merge and zero masking (V = M or Z), the default is the first variant
            mk = "M" if is_maskable else "Z"
            lines.append(f"template <VARIANT V = {mk}, typename T, int LMUL = 1>")
            lines.append(f"inline {ret} {cpp_fn}(const Vm<T, LMUL>& m0, {typed_str})")
            lines.append(f"{{ return {ret}(mipp::{cpp_fn}<V, T, LMUL>(m0.m, {raw_str})); }}")
            lines.append("")
        if is_masksable:
            lines.append("template <VARIANT V = S, typename T, int LMUL = 1>")
            lines.append(f"inline {ret} {cpp_fn}(const Vm<T, LMUL>& m0, const Vd<T, LMUL>& rsrc, {typed_str})")
            lines.append(f"{{ return {ret}(mipp::{cpp_fn}<V, T, LMUL>(m0.m, rsrc.r, {raw_str})); }}")
            lines.append("")

    # Category 1b: lo / hi / combine (the LMUL of the result differs from the one of the arguments)
    elif fn in ("lo", "hi", "lo_k", "hi_k"):
        cls = "Vm" if fn.endswith("_k") else "Vd"
        mem = "m" if cls == "Vm" else "r"
        call = "lo" if fn.startswith("lo") else "hi"
        ret = f"{cls}<T, details::lmul_down(LMUL)>"
        lines.append("template <typename T, int LMUL = 1>")
        lines.append(f"inline {ret} {cpp_fn}(const {cls}<T, LMUL>& {mem}0)")
        lines.append(f"{{ return {ret}({call}({mem}0.{mem})); }}")
        lines.append("")
    elif fn in ("combine", "combine_k"):
        cls = "Vm" if fn.endswith("_k") else "Vd"
        mem = "m" if cls == "Vm" else "r"
        ret = f"{cls}<T, details::lmul_up(LMUL)>"
        lines.append("template <typename T, int LMUL = 1>")
        lines.append(f"inline {ret} {cpp_fn}(const {cls}<T, LMUL>& {mem}0, const {cls}<T, LMUL>& {mem}1)")
        lines.append(f"{{ return {ret}(combine({mem}0.{mem}, {mem}1.{mem})); }}")
        lines.append("")

    elif fn == "set":
        lines.append("template <typename T, int LMUL = 1>")
        lines.append("inline Vd<T, LMUL> set_obj(const T vals[mipp::N<T, LMUL>()])")
        lines.append("{ return Vd<T, LMUL>(mipp::set<T, LMUL>(vals)); }")
        lines.append("")

    elif fn == "set0":
        lines.append("template <typename T, int LMUL = 1>")
        lines.append("inline Vd<T, LMUL> set0_obj()")
        lines.append("{ return Vd<T, LMUL>(mipp::set0<T, LMUL>()); }")
        lines.append("")

    elif fn == "set0_k":
        lines.append("template <typename T, int LMUL = 1>")
        lines.append("inline Vm<T, LMUL> set0_k_obj()")
        lines.append("{ return Vm<T, LMUL>(mipp::set0_k<T, LMUL>()); }")
        lines.append("")

    elif fn == "set1":
        lines.append("template <typename T, int LMUL = 1>")
        lines.append("inline Vd<T, LMUL> set1_obj(const T s0)")
        lines.append("{ return Vd<T, LMUL>(mipp::set1<T, LMUL>(s0)); }")
        lines.append("")

    elif fn == "set1_k":
        lines.append("template <typename T, int LMUL = 1>")
        lines.append("inline Vm<T, LMUL> set1_k_obj(const int32_t s0)")
        lines.append("{ return Vm<T, LMUL>(mipp::set1_k<T, LMUL>(s0)); }")
        lines.append("")

    elif fn == "set_k":
        lines.append("template <typename T, int LMUL = 1>")
        lines.append("inline Vm<T, LMUL> set_k_obj(const int32_t vals[mipp::N<T, LMUL>()])")
        lines.append("{ return Vm<T, LMUL>(mipp::set_k<T, LMUL>(vals)); }")
        lines.append("")

    # Category 2: Store / Memory operations
    elif fn in ("store", "storeu", "storeu_zip"):
        lines.append("template <typename T, int LMUL = 1>")
        lines.append(f"inline void {fn}(T* p0, const Vd<T, LMUL>& r0)")
        lines.append(f"{{ mipp::{fn}(p0, r0.r); }}")
        lines.append("")
        if is_maskable or is_maskzable:
            mk = "M" if is_maskable else "Z"
            lines.append(f"template <VARIANT V = {mk}, typename T, int LMUL = 1>")
            lines.append(f"inline void {fn}(const Vm<T, LMUL>& m0, T* p0, const Vd<T, LMUL>& r0)")
            lines.append(f"{{ mipp::{fn}<V, T, LMUL>(m0.m, p0, r0.r); }}")
            lines.append("")
    # gather / scatter: the index (T_IDX, unsigned) has one lane per lane of the data, so its own LMUL when its
    # width differs from the one of the data (32-bit indices of 64-bit data at LMUL 1: LMUL_IDX = -2). The mask has
    # the type and the LMUL of the data.
    elif fn == "gather":
        lines.append("template <typename T, typename T_IDX, int LMUL_IDX = 1>")
        lines.append("inline Vd<T, details::data_lmul<T, T_IDX>(LMUL_IDX)> gather(const T* p0, const Vd<T_IDX, LMUL_IDX>& vi)")
        lines.append("{ return Vd<T, details::data_lmul<T, T_IDX>(LMUL_IDX)>(mipp::gather(p0, vi.r)); }")
        lines.append("")
        if is_maskzable:
            lines.append("template <VARIANT V = Z, typename T, typename T_IDX, int LMUL = 1>")
            lines.append("inline Vd<T, LMUL> gather(const Vm<T, LMUL>& m0, const T* p0, const Vd<T_IDX, details::idx_lmul<T, T_IDX>(LMUL)>& vi)")
            lines.append("{ return Vd<T, LMUL>(mipp::gather<V, T, T_IDX, LMUL>(m0.m, p0, vi.r)); }")
            lines.append("")
        if is_masksable:
            lines.append("template <VARIANT V = S, typename T, typename T_IDX, int LMUL = 1>")
            lines.append("inline Vd<T, LMUL> gather(const Vm<T, LMUL>& m0, const Vd<T, LMUL>& rsrc, const T* p0, const Vd<T_IDX, details::idx_lmul<T, T_IDX>(LMUL)>& vi)")
            lines.append("{ return Vd<T, LMUL>(mipp::gather<V, T, T_IDX, LMUL>(m0.m, rsrc.r, p0, vi.r)); }")
            lines.append("")
    elif fn == "scatter":
        lines.append("template <typename T, typename T_IDX, int LMUL = 1>")
        lines.append("inline void scatter(T* p0, const Vd<T_IDX, details::idx_lmul<T, T_IDX>(LMUL)>& vi, const Vd<T, LMUL>& r0)")
        lines.append("{ mipp::scatter(p0, vi.r, r0.r); }")
        lines.append("")
        if is_maskable or is_maskzable:
            mk = "M" if is_maskable else "Z"
            lines.append(f"template <VARIANT V = {mk}, typename T, typename T_IDX, int LMUL = 1>")
            lines.append("inline void scatter(const Vm<T, LMUL>& m0, T* p0, const Vd<T_IDX, details::idx_lmul<T, T_IDX>(LMUL)>& vi, const Vd<T, LMUL>& r0)")
            lines.append("{ mipp::scatter<V, T, T_IDX, LMUL>(m0.m, p0, vi.r, r0.r); }")
            lines.append("")
    elif fn == "get":
        lines.append("template <typename T, int LMUL = 1>")
        lines.append("inline T get(const Vd<T, LMUL>& r0, const size_t idx)")
        lines.append("{ return mipp::get(r0.r, idx); }")
        lines.append("")
    elif fn == "get_k":
        lines.append("template <typename T, int LMUL = 1>")
        lines.append("inline bool get(const Vm<T, LMUL>& m0, const size_t idx)")
        lines.append("{ return details::mask_get_val<T>(mipp::get(m0.m, idx), typename std::is_floating_point<T>::type()); }")
        lines.append("")
    elif fn == "getfirst":
        lines.append("template <typename T, int LMUL = 1>")
        lines.append("inline T getfirst(const Vd<T, LMUL>& r0)")
        lines.append("{ return mipp::getfirst(r0.r); }")
        lines.append("")

    # Category 3: Selection (select)
    elif fn == "select":
        lines.append("template <typename T, int LMUL = 1>")
        lines.append("inline Vd<T, LMUL> select(const Vm<T, LMUL>& m0, const Vd<T, LMUL>& r0, const Vd<T, LMUL>& r1)")
        lines.append("{ return Vd<T, LMUL>(mipp::select(m0.m, r0.r, r1.r)); }")
        lines.append("")

    # Category 4: Pure mask operations
    elif args == ["msk", "msk"]:
        lines.append("template <typename T, int LMUL = 1>")
        if fn.startswith("testz"):
            lines.append(f"inline int32_t {fn}(const Vm<T, LMUL>& m0, const Vm<T, LMUL>& m1)")
            lines.append(f"{{ return mipp::{cpp_fn}(m0.m, m1.m); }}")
        else:
            lines.append(f"inline Vm<T, LMUL> {cpp_fn}(const Vm<T, LMUL>& m0, const Vm<T, LMUL>& m1)")
            lines.append(f"{{ return Vm<T, LMUL>(mipp::{cpp_fn}(m0.m, m1.m)); }}")
        lines.append("")

        mask_ops = {
            "andb_k": ("&", "&="),
            "orb_k":  ("|", "|="),
            "xorb_k": ("^", "^="),
        }
        if fn in mask_ops:
            op, op_assign = mask_ops[fn]
            lines.append("template <typename T, int LMUL = 1>")
            lines.append(f"inline Vm<T, LMUL> operator{op}(const Vm<T, LMUL>& m0, const Vm<T, LMUL>& m1)")
            lines.append(f"{{ return mipp::{cpp_fn}(m0, m1); }}")
            lines.append("")
            lines.append("template <typename T, int LMUL = 1>")
            lines.append(f"inline Vm<T, LMUL>& operator{op_assign}(Vm<T, LMUL>& m0, const Vm<T, LMUL>& m1)")
            lines.append(f"{{ m0 = m0 {op} m1; return m0; }}")
            lines.append("")
            lines.append("template <typename T, int LMUL = 1>")
            lines.append(f"inline Vm<T, LMUL> operator{op}(const Vm<T, LMUL>& m0, const bool val)")
            lines.append(f"{{ return m0 {op} Vm<T, LMUL>(val); }}")
            lines.append("")
            lines.append("template <typename T, int LMUL = 1>")
            lines.append(f"inline Vm<T, LMUL> operator{op}(const bool val, const Vm<T, LMUL>& m1)")
            lines.append(f"{{ return Vm<T, LMUL>(val) {op} m1; }}")
            lines.append("")
            lines.append("template <typename T, int LMUL = 1>")
            lines.append(f"inline Vm<T, LMUL>& operator{op_assign}(Vm<T, LMUL>& m0, const bool val)")
            lines.append(f"{{ m0 = m0 {op} Vm<T, LMUL>(val); return m0; }}")
            lines.append("")

    elif args == ["msk"] and fn in ("notb_k", "none", "any", "all", "count"):
        lines.append("template <typename T, int LMUL = 1>")
        ret_t = "int32_t" if fn in ("none", "any", "all", "count") else "Vm<T, LMUL>"
        lines.append(f"inline {ret_t} {cpp_fn}(const Vm<T, LMUL>& m0)")
        lines.append(f"{{ return {ret_t if ret_t == 'int32_t' else 'Vm<T, LMUL>'}(mipp::{cpp_fn}(m0.m)); }}")
        lines.append("")
        if fn == "notb_k":
            lines.append("template <typename T, int LMUL = 1>")
            lines.append("inline Vm<T, LMUL> operator~(const Vm<T, LMUL>& m0)")
            lines.append(f"{{ return mipp::{cpp_fn}(m0); }}")
            lines.append("")
            lines.append("template <typename T, int LMUL = 1>")
            lines.append("inline Vm<T, LMUL> operator!(const Vm<T, LMUL>& m0)")
            lines.append(f"{{ return mipp::{cpp_fn}(m0); }}")
            lines.append("")

    # Category 5: Reductions (hadd, hadds, hmin, hmax, hmul)
    elif cat == "reduction" and args == ["reg"]:
        lines.append("template <typename T, int LMUL = 1>")
        lines.append(f"inline auto {fn}(const Vd<T, LMUL>& r0) -> decltype(mipp::{fn}(r0.r))")
        lines.append(f"{{ return mipp::{fn}(r0.r); }}")
        lines.append("")
        if is_maskzable:
            lines.append("template <VARIANT V = Z, typename T, int LMUL = 1>")
            lines.append(f"inline auto {fn}(const Vm<T, LMUL>& m0, const Vd<T, LMUL>& r0) -> decltype(mipp::{fn}<V, T, LMUL>(m0.m, r0.r))")
            lines.append(f"{{ return mipp::{fn}<V, T, LMUL>(m0.m, r0.r); }}")
            lines.append("")

    # Category 6: Comparisons (cmpeq, cmplt, ...) -> return Vm
    elif fn in operators_order:
        op = operators_order[fn]["operation"]
        lines.append("template <typename T, int LMUL = 1>")
        lines.append(f"inline Vm<T, LMUL> {fn}(const Vd<T, LMUL>& r0, const Vd<T, LMUL>& r1)")
        lines.append(f"{{ return Vm<T, LMUL>(mipp::{fn}(r0.r, r1.r)); }}")
        lines.append("")
        if is_maskzable:
            lines.append("template <VARIANT V = Z, typename T, int LMUL = 1>")
            lines.append(f"inline Vm<T, LMUL> {fn}(const Vm<T, LMUL>& m0, const Vd<T, LMUL>& r0, const Vd<T, LMUL>& r1)")
            lines.append(f"{{ return Vm<T, LMUL>(mipp::{fn}<V, T, LMUL>(m0.m, r0.r, r1.r)); }}")
            lines.append("")
        lines.append("template <typename T, int LMUL = 1>")
        lines.append(f"inline Vm<T, LMUL> operator{op}(const Vd<T, LMUL>& r0, const Vd<T, LMUL>& r1)")
        lines.append(f"{{ return mipp::{fn}(r0, r1); }}")
        lines.append("")
        lines.append("template <typename T, int LMUL = 1>")
        lines.append(f"inline Vm<T, LMUL> operator{op}(const Vd<T, LMUL>& r0, const T val)")
        lines.append(f"{{ return r0 {op} Vd<T, LMUL>(val); }}")
        lines.append("")
        lines.append("template <typename T, int LMUL = 1>")
        lines.append(f"inline Vm<T, LMUL> operator{op}(const T val, const Vd<T, LMUL>& r1)")
        lines.append(f"{{ return Vd<T, LMUL>(val) {op} r1; }}")
        lines.append("")

    # Category 7: Conversions & reinterprets
    elif fn == "tovd":
        lines.append("template <typename T, int LMUL = 1>")
        lines.append("inline Vd<T, LMUL> tovd(const Vm<T, LMUL>& m0)")
        lines.append("{ return Vd<T, LMUL>(mipp::tovd(m0.m)); }")
        lines.append("")
    elif fn in ("tovm", "signbit"):
        lines.append("template <typename T, int LMUL = 1>")
        lines.append(f"inline Vm<T, LMUL> {fn}(const Vd<T, LMUL>& r0)")
        lines.append(f"{{ return Vm<T, LMUL>(mipp::{fn}(r0.r)); }}")
        lines.append("")
    elif fn == "cast":
        lines.append("namespace details")
        lines.append("{")
        lines.append("template <typename T_DST>")
        lines.append("struct cast_vd_helper;")
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
            lines.append(f"template <> struct cast_vd_helper<{c_t}> {{")
            lines.append(f"\ttemplate <typename T_SRC, int LMUL>")
            lines.append(f"\tstatic inline Vd<{c_t}, LMUL> apply(const Vd<T_SRC, LMUL>& r0)")
            lines.append(f"\t{{ return Vd<{c_t}, LMUL>(mipp::cast_{f_suffix}(r0.r)); }}")
            lines.append("};")
        lines.append("} // namespace details")
        lines.append("")
        lines.append("template <typename T_DST, typename T_SRC, int LMUL = 1>")
        lines.append("inline Vd<T_DST, LMUL> cast(const Vd<T_SRC, LMUL>& r0)")
        lines.append("{ return details::cast_vd_helper<T_DST>::apply(r0); }")
        lines.append("")
    elif fn == "cast_k":
        lines.append("namespace details")
        lines.append("{")
        lines.append("template <typename T_DST>")
        lines.append("struct cast_vm_helper;")
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
            lines.append(f"template <> struct cast_vm_helper<{c_t}> {{")
            lines.append(f"\ttemplate <typename T_SRC, int LMUL>")
            lines.append(f"\tstatic inline Vm<{c_t}, LMUL> apply(const Vm<T_SRC, LMUL>& m0)")
            lines.append(f"\t{{ return Vm<{c_t}, LMUL>(mipp::cast_{f_suffix}(m0.m)); }}")
            lines.append("};")
        lines.append("} // namespace details")
        lines.append("")
        lines.append("template <typename T_DST, typename T_SRC, int LMUL = 1>")
        lines.append("inline Vm<T_DST, LMUL> cast(const Vm<T_SRC, LMUL>& m0)")
        lines.append("{ return details::cast_vm_helper<T_DST>::apply(m0); }")
        lines.append("")
    elif fn == "cvt":
        lines.append("namespace details")
        lines.append("{")
        lines.append("template <typename T_DST>")
        lines.append("struct cvt_vd_helper;")
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
            lines.append(f"template <> struct cvt_vd_helper<{c_t}> {{")
            lines.append(f"\ttemplate <typename T_SRC, int LMUL>")
            lines.append(f"\tstatic inline Vd<{c_t}, LMUL> apply(const Vd<T_SRC, LMUL>& r0)")
            lines.append(f"\t{{ return Vd<{c_t}, LMUL>(mipp::cvt_{f_suffix}(r0.r)); }}")
            lines.append("};")
        lines.append("} // namespace details")
        lines.append("")
        lines.append("template <typename T_DST, typename T_SRC, int LMUL = 1>")
        lines.append("inline Vd<T_DST, LMUL> cvt(const Vd<T_SRC, LMUL>& r0)")
        lines.append("{ return details::cvt_vd_helper<T_DST>::apply(r0); }")
        lines.append("")
    elif fn == "wcvt":
        lines.append("namespace details")
        lines.append("{")
        lines.append("template <typename T_DST>")
        lines.append("struct wcvt_vd_helper;")
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
            lines.append(f"template <> struct wcvt_vd_helper<{c_t}> {{")
            lines.append(f"\ttemplate <typename T_SRC, int LMUL>")
            lines.append(f"\tstatic inline Vd<{c_t}, details::lmul_up(LMUL)> apply(const Vd<T_SRC, LMUL>& r0)")
            lines.append(f"\t{{ return Vd<{c_t}, details::lmul_up(LMUL)>(mipp::wcvt_{f_suffix}(r0.r)); }}")
            lines.append("};")
        lines.append("} // namespace details")
        lines.append("")
        lines.append("template <typename T_DST, typename T_SRC, int LMUL = 1>")
        lines.append("inline Vd<T_DST, details::lmul_up(LMUL)> wcvt(const Vd<T_SRC, LMUL>& r0)")
        lines.append("{ return details::wcvt_vd_helper<T_DST>::apply(r0); }")
        lines.append("")

    elif fn in ("ncvt", "ncvts"):
        # ncvt (truncating) and ncvts (saturating, integers only): the destination type is a template
        # parameter, dispatched to mipp::<fn>_<dst> by a helper structure
        lines.append("namespace details")
        lines.append("{")
        lines.append("template <typename T_DST>")
        lines.append(f"struct {fn}_vd_helper;")
        lines.append("")
        types_map = [
            ("float", "float32"),
            ("int32_t", "int32"),
            ("uint32_t", "uint32"),
            ("int16_t", "int16"),
            ("uint16_t", "uint16"),
            ("int8_t", "int8"),
            ("uint8_t", "uint8"),
        ]
        if fn == "ncvts":
            types_map = types_map[1:]
        for c_t, f_suffix in types_map:
            lines.append(f"template <> struct {fn}_vd_helper<{c_t}> {{")
            lines.append(f"\ttemplate <typename T_SRC, int LMUL>")
            lines.append(f"\tstatic inline Vd<{c_t}, details::lmul_down(LMUL)> apply(const Vd<T_SRC, LMUL>& r0)")
            lines.append(f"\t{{ return Vd<{c_t}, details::lmul_down(LMUL)>(mipp::{fn}_{f_suffix}(r0.r)); }}")
            lines.append("};")
        lines.append("} // namespace details")
        lines.append("")
        lines.append("template <typename T_DST, typename T_SRC, int LMUL = 1>")
        lines.append(f"inline Vd<T_DST, details::lmul_down(LMUL)> {fn}(const Vd<T_SRC, LMUL>& r0)")
        lines.append(f"{{ return details::{fn}_vd_helper<T_DST>::apply(r0); }}")
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
                typed_args.append(f"const Vd<T, LMUL>& {arg_name}")
                raw_args.append(f"{arg_name}.r")
            elif a_type == "val":
                arg_name = f"s{cnt_val}"
                cnt_val += 1
                typed_args.append(f"const int32_t {arg_name}")
                raw_args.append(arg_name)

        typed_str = ", ".join(typed_args)
        raw_str = ", ".join(raw_args)

        # 1. Free function overload (`cpp_fn`: name in the C++ APIs, `lshift` for `lshift_vs`)
        lines.append("template <typename T, int LMUL = 1>")
        lines.append(f"inline Vd<T, LMUL> {cpp_fn}({typed_str})")
        lines.append(f"{{ return Vd<T, LMUL>(mipp::{cpp_fn}({raw_str})); }}")
        lines.append("")

        # 2. Masked overloads
        if is_maskable:
            lines.append("template <VARIANT V = M, typename T, int LMUL = 1>")
            lines.append(f"inline Vd<T, LMUL> {cpp_fn}(const Vm<T, LMUL>& m0, {typed_str})")
            lines.append(f"{{ return Vd<T, LMUL>(mipp::{cpp_fn}<V, T, LMUL>(m0.m, {raw_str})); }}")
            lines.append("")
        if is_masksable:
            lines.append("template <VARIANT V = S, typename T, int LMUL = 1>")
            lines.append(f"inline Vd<T, LMUL> {cpp_fn}(const Vm<T, LMUL>& m0, const Vd<T, LMUL>& rsrc, {typed_str})")
            lines.append(f"{{ return Vd<T, LMUL>(mipp::{cpp_fn}<V, T, LMUL>(m0.m, rsrc.r, {raw_str})); }}")
            lines.append("")

        # 3. Operators
        if fn in all_binary_ops and args == ["reg", "reg"]:
            op_info = all_binary_ops[fn]
            op = op_info["operation"]
            op_assign = op_info["option"]

            lines.append("template <typename T, int LMUL = 1>")
            lines.append(f"inline Vd<T, LMUL> operator{op}(const Vd<T, LMUL>& r0, const Vd<T, LMUL>& r1)")
            lines.append(f"{{ return mipp::{fn}(r0, r1); }}")
            lines.append("")
            lines.append("template <typename T, int LMUL = 1>")
            lines.append(f"inline Vd<T, LMUL>& operator{op_assign}(Vd<T, LMUL>& r0, const Vd<T, LMUL>& r1)")
            lines.append(f"{{ r0 = r0 {op} r1; return r0; }}")
            lines.append("")
            lines.append("template <typename T, int LMUL = 1>")
            lines.append(f"inline Vd<T, LMUL> operator{op}(const Vd<T, LMUL>& r0, const T val)")
            lines.append(f"{{ return r0 {op} Vd<T, LMUL>(val); }}")
            lines.append("")
            lines.append("template <typename T, int LMUL = 1>")
            lines.append(f"inline Vd<T, LMUL> operator{op}(const T val, const Vd<T, LMUL>& r1)")
            lines.append(f"{{ return Vd<T, LMUL>(val) {op} r1; }}")
            lines.append("")
            lines.append("template <typename T, int LMUL = 1>")
            lines.append(f"inline Vd<T, LMUL>& operator{op_assign}(Vd<T, LMUL>& r0, const T val)")
            lines.append(f"{{ r0 = r0 {op} Vd<T, LMUL>(val); return r0; }}")
            lines.append("")

        elif fn in ("lshift_vs", "rshift_vs"):
            # same count for every lane: `r << 3`
            op = "<<" if fn == "lshift_vs" else ">>"
            lines.append("template <typename T, int LMUL = 1>")
            lines.append(f"inline Vd<T, LMUL> operator{op}(const Vd<T, LMUL>& r0, const int32_t val)")
            lines.append(f"{{ return mipp::{cpp_fn}(r0, val); }}")
            lines.append("")
            lines.append("template <typename T, int LMUL = 1>")
            lines.append(f"inline Vd<T, LMUL>& operator{op}=(Vd<T, LMUL>& r0, const int32_t val)")
            lines.append(f"{{ r0 = r0 {op} val; return r0; }}")
            lines.append("")

        elif fn in ("lshift", "rshift"):
            # count of each lane in a register: `r << n`
            op = "<<" if fn == "lshift" else ">>"
            lines.append("template <typename T, int LMUL = 1>")
            lines.append(f"inline Vd<T, LMUL> operator{op}(const Vd<T, LMUL>& r0, const Vd<T, LMUL>& r1)")
            lines.append(f"{{ return mipp::{fn}(r0, r1); }}")
            lines.append("")
            lines.append("template <typename T, int LMUL = 1>")
            lines.append(f"inline Vd<T, LMUL>& operator{op}=(Vd<T, LMUL>& r0, const Vd<T, LMUL>& r1)")
            lines.append(f"{{ r0 = r0 {op} r1; return r0; }}")
            lines.append("")

        elif fn == "neg":
            lines.append("template <typename T, int LMUL = 1>")
            lines.append("inline Vd<T, LMUL> operator-(const Vd<T, LMUL>& r0)")
            lines.append("{ return mipp::neg(r0); }")
            lines.append("")

        elif fn == "notb":
            lines.append("template <typename T, int LMUL = 1>")
            lines.append("inline Vd<T, LMUL> operator~(const Vd<T, LMUL>& r0)")
            lines.append("{ return mipp::notb(r0); }")
            lines.append("")

    # Immediate version (`"imm"` of the registry, see codegen/imm.py): `mipp::slide<3>(a, b)`, the C++ Functional
    # template of the same name on the registers
    if info.get("imm"):
        ret_t = "T" if p["ret"]["type"] == "val" else "Vd<T, LMUL>"
        typed, raw, cnt = [], [], {"reg": 0, "msk": 0}
        for a in args:  # the registers and masks; the integer argument is the template parameter
            if a in cnt:
                name = ("r" if a == "reg" else "m") + str(cnt[a])
                cnt[a] += 1
                typed.append(f"const {'Vd' if a == 'reg' else 'Vm'}<T, LMUL>& {name}")
                raw.append(f"{name}.{'r' if a == 'reg' else 'm'}")
        typed, raw = ", ".join(typed), ", ".join(raw)
        call = f"mipp::{cpp_fn}<S>({raw})"
        lines.append("template <int S, typename T, int LMUL = 1>")
        lines.append(f"inline {ret_t} {cpp_fn}({typed})")
        lines.append(f"{{ return {call if ret_t == 'T' else ret_t + '(' + call + ')'}; }}")
        lines.append("")

    body = lines[body_start:]
    lines.append("} // namespace mipp")

    if fine:
        _write_fine_granules(fn, cat, body, output_dir)
        return

    with open(file_path, "w", encoding="utf-8") as f:
        f.write("\n".join(lines) + "\n")


_FINE_LMULS = {"m1": 1, "m2": 2, "m4": 4, "m8": 8, "d2": -2}


def _split_units(body):
    """Split a generic obj body into declaration units (blank-line separated; a `namespace details`
    block is a single unit)."""
    units, cur, in_details = [], [], False
    for line in body:
        if line == "namespace details":
            in_details = True
        cur.append(line)
        if line.startswith("} // namespace details"):
            in_details = False
        if line == "" and not in_details:
            if any(l.strip() for l in cur):
                units.append(cur)
            cur = []
    if any(l.strip() for l in cur):
        units.append(cur)
    return units


def _unit_variant(unit):
    """Granule variant (u/m/z/s) an overload unit belongs to, from the default of its VARIANT parameter."""
    for line in unit:
        if line.startswith("template <VARIANT V = "):
            return {"M": "m", "Z": "z", "S": "s"}[line[len("template <VARIANT V = ")]]
        if line.startswith("template <"):
            return "u"
    return "u"


def _write_fine_granules(fn, cat, body, output_dir):
    """
    Fine-grained obj layer for one function. For each (variant, LMUL) granule, writes a self-contained header:

      - it includes ONLY the cpp granule it calls, FIRST, so that the qualified calls `mipp::fn(r.r)` of the
        overloads (resolved at definition time) see the right cpp declaration;
      - it defines only the overloads of that variant. The overloads keep the generic signature
        (`int LMUL = 1`) and are selected with `enable_if<LMUL == X>`, so every call form stays valid
        (deduced or explicit LMUL) and several LMUL granules can be included in the same translation unit.

    Masked overloads have a `VARIANT V` template parameter (default M or Z depending on the function). The
    m and z granules both receive them, constrained with `V == M` / `V == Z` respectively: the default V
    keeps selecting its own granule, and `f<mipp::Z>(...)` only compiles if the z atom was included (it does
    not silently rely on another granule). The s granule gets the 4-argument source overloads (`V == S`).
    """
    import re

    base = os.path.join(output_dir, "mipp", "internal", "interfaces", "obj", "functions", cat)
    variants = _variants_of(fn)
    units = _split_units(body)
    vname = {"m": "M", "z": "Z", "s": "S"}

    def units_for(v):
        res = []
        for u in units:
            d = _unit_variant(u)  # u / m / z / s (default of the VARIANT parameter)
            if v == "u":
                if d == "u":
                    res.append(u)
            elif v in ("m", "z"):
                if d in ("m", "z"):
                    res.append(u)
            elif v == "s":
                if d == "s":
                    res.append(u)
        return res

    partner = _OBJ_PARTNERS.get(fn)
    if partner and partner in interfaces:
        pcat = _match_category(partner)
        pvariants = _variants_of(partner)
    else:
        partner = None

    inc = "mipp/internal/interfaces"
    # lo / hi / combine / wcvt: no function (so no header) for an LMUL whose resulting LMUL does not exist
    fine_lmuls = {l: val for l, val in _FINE_LMULS.items()
                  if is_defined_for_lmul(interfaces[fn]["proto"], val)}
    for v in variants:
        v_units = units_for(v)
        for l, val in fine_lmuls.items():
            v_units_l = v_units
            out = ["#pragma once", "", f'#include "{inc}/obj/common.hpp"']
            out.append(f'#include "{inc}/cpp/functions/{cat}/{v}/{l}/{fn}.hpp"')
            if partner:
                pv = v if v in pvariants else "u"
                out.append(f'#include "{inc}/obj/functions/{pcat}/{pv}/{l}/{partner}.hpp"')
            # Operators building Vd/Vm from a scalar go through Vd(T)/Vm(bool): include the set1/set1_k obj
            # atom of this LMUL (it backs those constructors), unless this atom IS that one.
            body_txt = "\n".join(line for unit in v_units_l for line in unit)
            if "Vd<T, LMUL>(val)" in body_txt and fn != "set1":
                out.append(f'#include "{inc}/obj/functions/load/u/{l}/set1.hpp"')
            if "Vm<T, LMUL>(val)" in body_txt and fn != "set1_k":
                out.append(f'#include "{inc}/obj/functions/load/u/{l}/set1_k.hpp"')
            out += ["", "namespace mipp", "{"]
            for unit in v_units_l:
                for line in unit:
                    if line.startswith("template <") and "int LMUL = 1>" in line:
                        cond = f"LMUL == {val}"
                        if line.startswith("template <VARIANT V = "):
                            # U (mask ignored) is hosted by the same granule as its cpp specialization:
                            # m (or z if the function is not maskable) for the m0 form, s for the rsrc form
                            hosts_u = v == "s" or v == "m" or (v == "z" and "m" not in variants)
                            if hosts_u:
                                cond += f" && (V == {vname[v]} || V == U)"
                            else:
                                cond += f" && V == {vname[v]}"
                        line = line.replace(
                            "int LMUL = 1>",
                            f"int LMUL = 1, typename std::enable_if<{cond}, int>::type = 0>")
                    if line.startswith("template <") and "int LMUL_IDX = 1>" in line:
                        # unmasked gather: deduced from the index, whose LMUL differs from the one of the data
                        line = line.replace(
                            "int LMUL_IDX = 1>",
                            f"int LMUL_IDX = 1, typename std::enable_if<details::data_lmul<T, T_IDX>(LMUL_IDX) == {val}, int>::type = 0>")
                    # helper structs are shared names: make them unique per granule
                    line = re.sub(r"\b(\w+_helper)\b", rf"\1_{v}_{l}", line)
                    out.append(line)
            # Backing trait of the matching Vd/Vm member for this LMUL
            if v == "u" and fn in _OBJ_MEMBER_OPS and v_units_l is v_units:
                trait, ret_t, params, call = _OBJ_MEMBER_OPS[fn]
                L = str(val)
                fmt = dict(L=L, D=resolve_ret_lmul({"lmul": "down"}, val), U=resolve_ret_lmul({"lmul": "up"}, val))
                out += [
                    "namespace details",
                    "{",
                    "template <typename T>",
                    f"struct {trait}<T, {L}>",
                    "{",
                    f"\tstatic inline {ret_t.format(**fmt)} apply({params.format(**fmt)})",
                    f"\t{{ return {call.format(**fmt)}; }}",
                    "};",
                    "} // namespace details",
                    "",
                ]
            out.append("} // namespace mipp")
            atom_dir = os.path.join(base, v, l)
            os.makedirs(atom_dir, exist_ok=True)
            with open(os.path.join(atom_dir, f"{fn}.hpp"), "w", encoding="utf-8") as f:
                f.write("\n".join(out) + "\n")

    # Variant umbrellas: all LMULs of a variant
    for v in variants:
        os.makedirs(os.path.join(base, v), exist_ok=True)
        with open(os.path.join(base, v, f"{fn}.hpp"), "w", encoding="utf-8") as f:
            f.write("#pragma once\n\n")
            for l in fine_lmuls:
                f.write(f'#include "{inc}/obj/functions/{cat}/{v}/{l}/{fn}.hpp"\n')

    # LMUL umbrellas: all variants of an LMUL
    for l in fine_lmuls:
        os.makedirs(os.path.join(base, l), exist_ok=True)
        with open(os.path.join(base, l, f"{fn}.hpp"), "w", encoding="utf-8") as f:
            f.write("#pragma once\n\n")
            for v in variants:
                f.write(f'#include "{inc}/obj/functions/{cat}/{v}/{l}/{fn}.hpp"\n')

    # Function umbrella (used by the coarse per-function public header): everything
    with open(os.path.join(base, f"{fn}.hpp"), "w", encoding="utf-8") as f:
        f.write("#pragma once\n\n")
        for v in variants:
            f.write(f'#include "{inc}/obj/functions/{cat}/{v}/{fn}.hpp"\n')


def generate_obj(include_manager=None, output_dir="../include"):
    """
    Main generator entry point for C++ Object layer:
    1. Generates interfaces/obj/common.hpp
    2. Generates all interfaces/obj/functions/<cat>/<func>.hpp
    3. Generates mipp_obj.hpp including all modular components
    """
    fine = bool(include_manager and getattr(include_manager, "granularity", "coarse") == "fine")
    generate_obj_common(output_dir, fine=fine)

    for fn in interfaces:
        generate_obj_func_file(fn, output_dir, fine=fine)

    # Generate top-level mipp_obj.hpp
    obj_hpp_path = os.path.join(output_dir, "mipp_obj.hpp")
    with open(obj_hpp_path, "w", encoding="utf-8") as f:
        f.write("#pragma once\n\n")
        f.write('#include "mipp.hpp"\n')
        f.write('#include "mipp/internal/interfaces/obj/common.hpp"\n\n')
        for cat in sorted(categories.keys()):
            f.write(f'#include "mipp/obj/cat/{cat}.hpp"\n')
        # hand-written utilities (operator<<, pack, reduce): utils_generator.py
        f.write('#include "mipp/obj/utils.hpp"\n')
        # compile-time permutations of the Vd registers (C++17): utils_generator.py
        f.write('#include "mipp/obj/patterns.hpp"\n')

