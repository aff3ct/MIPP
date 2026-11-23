"""
Tests of the functions with indexed memory accesses (gather, scatter).

These functions take a pointer and a register of unsigned indices, which the generic test builder
cannot generate. Their tests are written here. As for the other functions, the result is compared with
the scalar reference (mipp_scalar_* in C, mipp::ISA::SCALAR in C++), for every datatype, LMUL,
half-vector (d2) and mask variant, in the three APIs:

  gather : the register is stored and compared lane by lane
  scatter: the memory written by both targets is compared

The memory accessed through the indices is a table of M elements, larger than a register: M is
2^8 for 8-bit indices, 2^16 for 16-bit indices and 2^17 for wider ones (and at least N). The indices
then cover the whole range of the 8 and 16-bit index types, which catches the byte offsets computed
in the index width that overflow (e.g. idx * 2 on 16 bits from idx = 2^15).

The functions are generated for pairs "data,index" (index: an unsigned type, of the width of the data or
another one): the index has one lane per lane of the data, so its LMUL is the LMUL of the data times
size(index) / size(data) (see name_builder.resolve_arg_lmul), and a pair is only tested for the LMULs
where this LMUL exists. The mask has the type and the LMUL of the data.

  gather : the indices are random values of [0, M)
  scatter: the indices are N distinct values of [0, M) (offset + i * stride mod M, with a stride
           coprime with M, then shuffled), so that the result does not depend on the order of the
           writes; the whole table is compared
"""
from typing import List, Optional

INDEXED_FUNCS = ("gather", "scatter")

_MK_ENUM = {"": "mipp::U", "mask": "mipp::M", "maskz": "mipp::Z", "masks": "mipp::S"}
_MK_LABEL = {"": "unmasked", "mask": "Merge-Masked", "maskz": "Zero-Masked", "masks": "Source-Masked"}
_C_STD = ("#include <exception>", "#include <algorithm>", "#include <numeric>", "#include <random>",
          "#include <cstdio>", "#include <cmath>", "#include <cstdlib>", "#include <cstring>", "#include <vector>",
          '#include "utils/random.hpp"', "#ifndef N_ITER", "#define N_ITER {N_ITER}", "#endif")
# scalar reference headers (first, as in the other tests: see TestsBuilderEngineCppBase._render_headers)
_SCALAR_FUNCS = (("load", "load"), ("load", "set_k"), ("load", "gather"), ("store", "store"),
                 ("store", "scatter"), ("store", "get"), ("store", "get_k"),
                 ("reinterpret", "tovd"), ("reinterpret", "tovm"))


def _bits(dt: str) -> int:
    return int("".join(c for c in dt if c.isdigit()))


def _pair(p: str):
    """"float64,uint32" -> ("float64", "uint32")."""
    a, b = p.split(",")
    return a.strip(), b.strip()


def idx_lmul(dt: str, idt: str, lmul: int) -> Optional[int]:
    """
    LMUL of the index for the data LMUL `lmul` (0 and 1: m1, -2: d2), None when it does not exist, or when the
    function is not generated: the mixed pairs have no d2 version (name_builder.is_defined_for_dt_lmul).
    """
    if lmul == -2 and _bits(idt) != _bits(dt):
        return None
    num, den = (1, 2) if lmul == -2 else (max(lmul, 1), 1)
    num, den = num * _bits(idt), den * _bits(dt)
    if num >= den:
        r = num // den if num % den == 0 else None
        return r if r in (1, 2, 4, 8) else None
    return -2 if den == 2 * num else None


def _c_sfx(lmul: int) -> str:
    """Suffix of the public C names (m1: none)."""
    return "" if lmul in (0, 1) else (f"_m{lmul}" if lmul > 0 else "_d2")


def _scalar_includes(ext: str) -> List[str]:
    return [f"#include <mipp/internal/simd_ext/scalar/{'c' if ext == 'h' else 'cpp'}/functions/{cat}/{fn}.{ext}>"
            for cat, fn in _SCALAR_FUNCS]


def _table_size() -> List[str]:
    """Size M of the memory accessed through the indices (see the module docstring)."""
    return ["constexpr size_t K = sizeof(IDX) == 1 ? 256 : (sizeof(IDX) == 2 ? 65536 : 131072);",
            "constexpr size_t M = N > K ? N : K;"]


def _body_common(func: str) -> List[str]:
    """Random inputs: the table (data for gather, initial memory for scatter), the register inputs and the indices."""
    lines = ["for (size_t i = 0; i < M; i++)", "\ttable[i] = rnd::uniform<T>(seed);",
             "for (size_t i = 0; i < N; i++)", "{",
             "\tsrc[i] = rnd::uniform<T>(seed);",
             "\tmk[i] = rnd::uniform_bool(seed) ? -1 : 0;"]
    if func == "gather":
        lines += ["\tidx[i] = rnd::uniform<IDX>(seed, static_cast<IDX>(0), static_cast<IDX>(M - 1));", "}"]
    else:
        # N distinct indices of [0, M): i -> offset + i * stride mod M is injective when gcd(stride, M) = 1
        lines += ["}",
                  "uint64_t stride = 2 * rnd::uniform<uint64_t>(seed, 0, M / 2 - 1) + 1;",
                  "while (std::gcd(stride, static_cast<uint64_t>(M)) != 1)",
                  "\tstride += 2;",
                  "const uint64_t offset = rnd::uniform<uint64_t>(seed, 0, M - 1);",
                  "for (size_t i = 0; i < N; i++)",
                  "\tidx[i] = static_cast<IDX>((offset + i * stride) % M);",
                  "std::shuffle(idx, idx + N, seed);"]
    return lines


def _decls(func: str) -> List[str]:
    """The table of M elements is a vector (up to 1 MiB); the register-sized arrays stay on the stack."""
    d = _table_size() + ["std::vector<T> table(M);",
                         "alignas(64) T src[N];",
                         "alignas(64) IDX idx[N];",
                         "int32_t mk[N];"]
    if func == "gather":
        d += ["alignas(64) T res_r[N];", "alignas(64) T res_s[N];"]
    else:
        d += ["std::vector<T> res_r(M);", "std::vector<T> res_s(M);"]
    return d


def _compare(func: str) -> List[str]:
    if func == "gather":
        return ["for (size_t i = 0; i < N; i++)", "{", "\tREQUIRE(res_r[i] == res_s[i]);", "}"]
    # scatter: the whole table (M elements) is compared at once; the elements are only checked one by
    # one (for the report) when the tables differ, to keep the number of assertions small
    return ["if (res_r != res_s)", "{", "\tfor (size_t i = 0; i < M; i++)", "\t\tREQUIRE(res_r[i] == res_s[i]);", "}",
            "REQUIRE(res_r == res_s);"]


def _indent(lines: List[str], n: int) -> List[str]:
    return [("\t" * n + l) if l else l for l in lines]


# --------------------------------------------------------------------------------------------------
# C API
# --------------------------------------------------------------------------------------------------

def _c_test(func: str, pair: str, sfx: str, mkind: str, lmul: int) -> List[str]:
    dt, idt = _pair(pair)
    sfx_u = f"_{sfx}" if sfx and sfx != "m0" else ""
    mult = f" * {lmul}" if lmul > 0 else (f" / {-lmul}" if lmul < 0 else "")
    isfx = _c_sfx(idx_lmul(dt, idt, lmul))
    mk_sfx = f"_{mkind}" if mkind else ""

    def names(prefix: str):
        return {
            "call": f"mipp_{prefix}{func}_{dt}_{idt}{mk_sfx}{sfx_u}",
            "load_i": f"mipp_{prefix}load_{idt}{isfx}(idx)",
            "load_src": f"mipp_{prefix}load_{dt}{sfx_u}(src)",
            "load_data": f"mipp_{prefix}load_{dt}{sfx_u}(src)",
            "set_k": f"mipp_{prefix}set_k_{dt}{sfx_u}(mk)",
            "store": f"mipp_{prefix}store_{dt}{sfx_u}",
            "r_t": f"vd_{prefix}{dt}{sfx_u}_t",
            "ri_t": f"vd_{prefix}{idt}{isfx}_t",
            "rm_t": f"vm_{prefix}{dt}{sfx_u}_t",
        }

    tag = f"{mkind}_{sfx}" if mkind else sfx
    b = [f"constexpr size_t N = MIPP_N_{dt.upper()}{mult};"]
    b += _decls(func) + [""] + _body_common(func) + [""]
    for prefix, res, p in (("", "res_r", "r"), ("scalar_", "res_s", "s")):
        n = names(prefix)
        b += [f"[[maybe_unused]] {n['ri_t']} {p}i = {n['load_i']};",
              f"[[maybe_unused]] {n['rm_t']} {p}m = {n['set_k']};",
              f"[[maybe_unused]] {n['r_t']} {p}src = {n['load_src']};"]
        if func == "gather":
            args = {"masks": f"{p}m, {p}src, table.data(), {p}i",
                    "maskz": f"{p}m, table.data(), {p}i"}.get(mkind, f"table.data(), {p}i")
            b += [f"{n['r_t']} {p}res = {n['call']}({args});", f"{n['store']}({res}, {p}res);", ""]
        else:
            b += [f"{res} = table;",
                  f"[[maybe_unused]] {n['r_t']} {p}v = {n['load_data']};"]
            args = f"{p}m, {res}.data(), {p}i, {p}v" if mkind else f"{res}.data(), {p}i, {p}v"
            b += [f"{n['call']}({args});", ""]
    b += _compare(func)
    return ([f"static void test_mipp_c_{func}_{dt}_{idt}_{tag}()", "{", f"\tusing T = {dt}_t;", f"\tusing IDX = {idt}_t;",
             "\tstd::mt19937 seed(Catch::getSeed());",
             "\tfor (unsigned n = 0; n < get_n_iter(); n++)", "\t{"] + _indent(b, 2) + ["\t}", "}", ""])


def build_c(func: str, pairs: List[str], sfx: str, mkind: str, lmul: int, N: int) -> str:
    """One test per pair "data,index" whose index LMUL exists for this LMUL (a d2 index needs MIPP_LDIV_2)."""
    pairs = [p for p in pairs if idx_lmul(*_pair(p), lmul) is not None]
    lines = [l.replace("{N_ITER}", str(N)) for l in _C_STD]
    lines += _scalar_includes("h")
    lines += ["#include <mipp.h>", "", "#include <catch2/catch_test_macros.hpp>",
              "#include <catch2/catch_get_random_seed.hpp>", ""]
    if lmul < 0:
        lines.append("#if defined(MIPP_LDIV_2)")
    d2_idx = lambda p: lmul >= 0 and idx_lmul(*_pair(p), lmul) == -2
    for p in pairs:
        if d2_idx(p):
            lines.append("#if defined(MIPP_LDIV_2)")
        lines += _c_test(func, p, sfx, mkind, lmul)
        if d2_idx(p):
            lines += ["#endif // MIPP_LDIV_2", ""]
    tag = f"{mkind}_{sfx}" if mkind else sfx
    lines += [f'TEST_CASE("{func} - c tests [{_MK_LABEL[mkind]}, {sfx}]", "[{func}]")', "{"]
    for p in pairs:
        dt, idt = _pair(p)
        if d2_idx(p):
            lines.append("#if defined(MIPP_LDIV_2)")
        lines += [f'\tSECTION("datatype = {dt}, index = {idt}")', "\t{", "\t\ttry {",
                  f"\t\t\ttest_mipp_c_{func}_{dt}_{idt}_{tag}();",
                  "\t\t} catch (const mipp::stub_exception& e) {", "\t\t\tWARN(e.what());", "\t\t}", "\t}"]
        if d2_idx(p):
            lines.append("#endif // MIPP_LDIV_2")
    lines.append("}")
    if lmul < 0:
        lines += ["", "#endif // MIPP_LDIV_2"]
    return "\n".join(lines)


# --------------------------------------------------------------------------------------------------
# C++ Functional and Object APIs
# --------------------------------------------------------------------------------------------------

def _cpp_calls(func: str, dialect: str, mkind: str, scalar: bool) -> List[str]:
    """Statement calling the function with the registers (s)i / (s)m / (s)src / (s)v."""
    p = "s" if scalar else "r"
    e = _MK_ENUM[mkind]
    isa = ", mipp::ISA::SCALAR" if scalar else ""
    # Object API: T, T_IDX and LMUL are deduced from the arguments
    obj = dialect == "obj" and not scalar
    t = "" if obj else f"T, IDX, LMUL{isa}"
    res = "res_s" if scalar else "res_r"
    var = e if obj else f"{e}, {t}"
    if func == "gather":
        if mkind == "":
            # unmasked: not a template (the types are deduced from the arguments)
            return [f"return mipp::gather(table.data(), {p}i);"]
        if mkind == "maskz":
            return [f"return mipp::gather<{var}>({p}m, table.data(), {p}i);"]
        return [f"return mipp::gather<{var}>({p}m, {p}src, table.data(), {p}i);"]
    if mkind == "":
        return [f"mipp::scatter({res}.data(), {p}i, {p}v);"]
    return [f"mipp::scatter<{var}>({p}m, {res}.data(), {p}i, {p}v);"]


def _cpp_test(func: str, dialect: str, variants: List[str]) -> List[str]:
    def regs(scalar: bool):
        p = "s" if scalar else "r"
        if scalar or dialect == "cpp":
            isa = ", mipp::ISA::SCALAR" if scalar else ""
            return [f"[[maybe_unused]] auto {p}i = mipp::load<IDX, LMUL_IDX{isa}>(idx);",
                    f"[[maybe_unused]] auto {p}m = mipp::set_k<T, LMUL{isa}>(mk);",
                    f"[[maybe_unused]] auto {p}src = mipp::load<T, LMUL{isa}>(src);",
                    f"[[maybe_unused]] auto {p}v = mipp::load<T, LMUL{isa}>(src);"]
        return [f"[[maybe_unused]] auto ri = mipp::Vd<IDX, LMUL_IDX>(idx);",
                f"[[maybe_unused]] auto rm = mipp::Vm<T, LMUL>(mk);",
                f"[[maybe_unused]] auto rsrc = mipp::Vd<T, LMUL>(src);",
                f"[[maybe_unused]] auto rv = mipp::Vd<T, LMUL>(src);"]

    def dispatch(scalar: bool, void: bool, var: str) -> List[str]:
        out: List[str] = []
        first = True
        for v in variants:
            kw = "if constexpr" if first else "else if constexpr"
            first = False
            out += [f"{kw} (V == {_MK_ENUM[v]})", "{"] + _indent(_cpp_calls(func, dialect, v, scalar), 1) + ["}"]
        if void:
            return out
        return [f"auto {var} = [&]() {{"] + _indent(out, 1) + ["}();"]

    b: List[str] = [
        "constexpr size_t N = (LMUL > 0) ? (mipp::N<T>() * static_cast<size_t>(LMUL)) : (mipp::N<T>() / static_cast<size_t>(-LMUL));",
    ]
    b += _decls(func) + [""] + _body_common(func) + [""]
    b += regs(False) + regs(True)
    if func == "gather":
        b += dispatch(False, False, "rres") + dispatch(True, False, "sres")
        b += ["mipp::store(res_r, rres);", "mipp::store(res_s, sres);", ""]
    else:
        b += ["res_r = table;", "res_s = table;"]
        b += dispatch(False, True, "") + dispatch(True, True, "") + [""]
    b += _compare(func)
    head = [f"template <mipp::VARIANT V = mipp::U, typename T = double, typename IDX = uint64_t, int LMUL = 1>",
            f"static void test_mipp_{dialect}_{func}()", "{",
            "\t// one index lane per data lane: the index has its own LMUL when its width differs",
            "\tconstexpr int LMUL_IDX = mipp::details::idx_lmul<T, IDX>(LMUL);",
            "\tstd::mt19937 seed(Catch::getSeed());",
            "\tfor (unsigned n = 0; n < get_n_iter(); n++)", "\t{"]
    return head + _indent(b, 2) + ["\t}", "}", ""]


def build_cpp(dialect: str, func: str, pairs: List[str], mkinds: List[str],
              lmul_list: Optional[List[int]], ldiv_list: Optional[List[int]], N: int, cpp_type=None) -> str:
    """One section per pair "data,index" and per LMUL where the index LMUL exists; `cpp_type` gives the C++
    name of a datatype (float64 -> double)."""
    lines = [l.replace("{N_ITER}", str(N)) for l in _C_STD]
    lines += _scalar_includes("hpp")
    lines += ["#include <mipp.hpp>"]
    if dialect == "obj":
        lines += ["#include <mipp_obj.hpp>"]
    lines += ["#include <type_traits>", "", "#include <catch2/catch_test_macros.hpp>",
              "#include <catch2/catch_get_random_seed.hpp>", ""]
    lines += _cpp_test(func, dialect, mkinds)
    lmuls = [1, 2, 4, 8]
    if lmul_list is not None:
        want = set(lmul_list)
        if 0 in want:
            want.add(1)
        lmuls = [l for l in lmuls if l in want]
    label = "cpp" if dialect == "cpp" else "obj"
    lines += [f'TEST_CASE("{func} - {label} tests", "[{func}]")', "{"]
    cpp_type = cpp_type or (lambda d: d)
    for mk in mkinds:
        lines += [f'\tSECTION("{_MK_LABEL[mk]}")', "\t{"]
        for p in pairs:
            dt, idt = _pair(p)
            lines += [f'\t\tSECTION("datatype = {cpp_type(dt)}, index = {cpp_type(idt)}")', "\t\t{"]
            calls = [(f"LMUL = {l}", l) for l in lmuls]
            if ldiv_list is None or 2 in ldiv_list:
                calls.append(("LDIV = 2", -2))
            for lab, l in calls:
                il = idx_lmul(dt, idt, l)
                if il is None:
                    continue
                if l < 0 or il < 0:
                    lines.append("#if defined(MIPP_LDIV_2)")
                lines += [f'\t\t\tSECTION("{lab}")', "\t\t\t{", "\t\t\t\ttry {",
                          f"\t\t\t\t\ttest_mipp_{dialect}_{func}<{_MK_ENUM[mk]}, {cpp_type(dt)}, {cpp_type(idt)}, {l}>();",
                          "\t\t\t\t} catch (const mipp::stub_exception& e) {", "\t\t\t\t\tWARN(e.what());",
                          "\t\t\t\t}", "\t\t\t}"]
                if l < 0 or il < 0:
                    lines.append("#endif // MIPP_LDIV_2")
            lines.append("\t\t}")
        lines.append("\t}")
    lines.append("}")
    return "\n".join(lines)
