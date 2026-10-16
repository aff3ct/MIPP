"""
Tests of the functions with indexed memory accesses (gather, scatter).

These functions take a pointer and a register of unsigned indices, which the generic test builder
cannot generate. Their tests are written here. As for the other functions, the result is compared with
the scalar reference (mipp_scalar_* in C, mipp::ISA::SCALAR in C++), for every datatype, LMUL,
half-vector (d2) and mask variant, in the three APIs:

  gather : the register is stored and compared lane by lane
  scatter: the memory written by both targets is compared

The indices of a gather are random values of [0, N); the ones of a scatter are a permutation of
[0, N), so that the result does not depend on the order of the writes.
"""
from typing import List, Optional

INDEXED_FUNCS = ("gather", "scatter")

_MK_ENUM = {"": "mipp::U", "mask": "mipp::M", "maskz": "mipp::Z", "masks": "mipp::S"}
_MK_LABEL = {"": "unmasked", "mask": "Merge-Masked", "maskz": "Zero-Masked", "masks": "Source-Masked"}
_C_STD = ("#include <exception>", "#include <algorithm>", "#include <numeric>", "#include <random>",
          "#include <cstdio>", "#include <cmath>", "#include <cstdlib>", "#include <cstring>",
          '#include "utils/random.hpp"', "#ifndef N_ITER", "#define N_ITER {N_ITER}", "#endif")
# scalar reference headers (first, as in the other tests: see TestsBuilderEngineCppBase._render_headers)
_SCALAR_FUNCS = (("load", "load"), ("load", "set_k"), ("load", "gather"), ("store", "store"),
                 ("store", "scatter"), ("store", "get"), ("store", "get_k"),
                 ("reinterpret", "to_rvd"), ("reinterpret", "to_rvm"))


def _bits(dt: str) -> str:
    return "".join(c for c in dt if c.isdigit())


def _idx_dt(dt: str) -> str:
    return "uint" + _bits(dt)


def _scalar_includes(ext: str) -> List[str]:
    return [f"#include <mipp/internal/simd_ext/scalar/{'c' if ext == 'h' else 'cpp'}/functions/{cat}/{fn}.{ext}>"
            for cat, fn in _SCALAR_FUNCS]


def _fill() -> List[str]:
    return [
        "for (size_t i = 0; i < N; i++)",
        "{",
        "\tdata[i] = rnd::uniform<T>(seed);",
        "\tsrc[i] = rnd::uniform<T>(seed);",
        "\tmk[i] = rnd::uniform_bool(seed) ? -1 : 0;",
        "\tidx[i] = %s;" % "FILL_IDX",
        "}",
    ]


def _body_common(func: str) -> List[str]:
    lines = _fill()
    lines[5] = ("\tidx[i] = rnd::uniform<IDX>(seed, static_cast<IDX>(0), static_cast<IDX>(N - 1));"
                if func == "gather" else "\tidx[i] = static_cast<IDX>(i);")
    if func == "scatter":
        lines.append("std::shuffle(idx, idx + N, seed);")
    return lines


def _decls() -> List[str]:
    return [
        "alignas(64) T data[N];",
        "alignas(64) T src[N];",
        "alignas(64) IDX idx[N];",
        "int32_t mk[N];",
        "alignas(64) T res_r[N];",
        "alignas(64) T res_s[N];",
    ]


def _compare() -> List[str]:
    return ["for (size_t i = 0; i < N; i++)", "{", "\tREQUIRE(res_r[i] == res_s[i]);", "}"]


def _indent(lines: List[str], n: int) -> List[str]:
    return [("\t" * n + l) if l else l for l in lines]


# --------------------------------------------------------------------------------------------------
# C API
# --------------------------------------------------------------------------------------------------

def _c_test(func: str, dt: str, sfx: str, mkind: str, lmul: int) -> List[str]:
    sfx_u = f"_{sfx}" if sfx and sfx != "m0" else ""
    mult = f" * {lmul}" if lmul > 0 else (f" / {-lmul}" if lmul < 0 else "")
    idt = _idx_dt(dt)
    mk_sfx = f"_{mkind}" if mkind else ""

    def names(prefix: str):
        return {
            "call": f"mipp_{prefix}{func}_{dt}_{dt}{mk_sfx}{sfx_u}",
            "load_i": f"mipp_{prefix}load_{idt}{sfx_u}(idx)",
            "load_src": f"mipp_{prefix}load_{dt}{sfx_u}(src)",
            "load_data": f"mipp_{prefix}load_{dt}{sfx_u}(data)",
            "set_k": f"mipp_{prefix}set_k_{idt}{sfx_u}(mk)",
            "store": f"mipp_{prefix}store_{dt}{sfx_u}",
            "r_t": f"rvd_{prefix}{dt}{sfx_u}_t",
            "ri_t": f"rvd_{prefix}{idt}{sfx_u}_t",
            "rm_t": f"rvm_{prefix}{idt}{sfx_u}_t",
        }

    tag = f"{mkind}_{sfx}" if mkind else sfx
    b = [f"constexpr size_t N = MIPP_N_{dt.upper()}{mult};"]
    b += _decls() + [""] + _body_common(func) + [""]
    for prefix, res, p in (("", "res_r", "r"), ("scalar_", "res_s", "s")):
        n = names(prefix)
        b += [f"[[maybe_unused]] {n['ri_t']} {p}i = {n['load_i']};",
              f"[[maybe_unused]] {n['rm_t']} {p}m = {n['set_k']};",
              f"[[maybe_unused]] {n['r_t']} {p}src = {n['load_src']};"]
        if func == "gather":
            args = {"masks": f"{p}m, {p}src, data, {p}i", "maskz": f"{p}m, data, {p}i"}.get(mkind, f"data, {p}i")
            b += [f"{n['r_t']} {p}res = {n['call']}({args});", f"{n['store']}({res}, {p}res);", ""]
        else:
            b += [f"std::memcpy({res}, src, sizeof({res}));",
                  f"[[maybe_unused]] {n['r_t']} {p}v = {n['load_data']};"]
            args = f"{p}m, {res}, {p}i, {p}v" if mkind else f"{res}, {p}i, {p}v"
            b += [f"{n['call']}({args});", ""]
    b += _compare()
    return ([f"static void test_mipp_c_{func}_{dt}_{tag}()", "{", f"\tusing T = {dt}_t;", f"\tusing IDX = {idt}_t;",
             "\tstd::mt19937 seed(Catch::getSeed());",
             "\tfor (unsigned n = 0; n < get_n_iter(); n++)", "\t{"] + _indent(b, 2) + ["\t}", "}", ""])


def build_c(func: str, datatypes: List[str], sfx: str, mkind: str, lmul: int, N: int) -> str:
    lines = [l.replace("{N_ITER}", str(N)) for l in _C_STD]
    lines += _scalar_includes("h")
    lines += ["#include <mipp.h>", "", "#include <catch2/catch_test_macros.hpp>",
              "#include <catch2/catch_get_random_seed.hpp>", ""]
    if lmul < 0:
        lines.append("#if defined(MIPP_LDIV_2)")
    for dt in datatypes:
        lines += _c_test(func, dt, sfx, mkind, lmul)
    tag = f"{mkind}_{sfx}" if mkind else sfx
    lines += [f'TEST_CASE("{func} - c tests [{_MK_LABEL[mkind]}, {sfx}]", "[{func}]")', "{"]
    for dt in datatypes:
        lines += [f'\tSECTION("datatype = {dt}")', "\t{", "\t\ttry {",
                  f"\t\t\ttest_mipp_c_{func}_{dt}_{tag}();",
                  "\t\t} catch (const mipp::stub_exception& e) {", "\t\t\tWARN(e.what());", "\t\t}", "\t}"]
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
            return [f"return mipp::gather(data, {p}i);"]
        if mkind == "maskz":
            return [f"return mipp::gather<{var}>({p}m, data, {p}i);"]
        return [f"return mipp::gather<{var}>({p}m, {p}src, data, {p}i);"]
    if mkind == "":
        return [f"mipp::scatter({res}, {p}i, {p}v);"]
    return [f"mipp::scatter<{var}>({p}m, {res}, {p}i, {p}v);"]


def _cpp_test(func: str, dialect: str, variants: List[str]) -> List[str]:
    def regs(scalar: bool):
        p = "s" if scalar else "r"
        if scalar or dialect == "cpp":
            isa = ", mipp::ISA::SCALAR" if scalar else ""
            return [f"[[maybe_unused]] auto {p}i = mipp::load<IDX, LMUL{isa}>(idx);",
                    f"[[maybe_unused]] auto {p}m = mipp::set_k<IDX, LMUL{isa}>(mk);",
                    f"[[maybe_unused]] auto {p}src = mipp::load<T, LMUL{isa}>(src);",
                    f"[[maybe_unused]] auto {p}v = mipp::load<T, LMUL{isa}>(data);"]
        return [f"[[maybe_unused]] auto ri = mipp::Rvd<IDX, LMUL>(idx);",
                f"[[maybe_unused]] auto rm = mipp::Rvm<IDX, LMUL>(mk);",
                f"[[maybe_unused]] auto rsrc = mipp::Rvd<T, LMUL>(src);",
                f"[[maybe_unused]] auto rv = mipp::Rvd<T, LMUL>(data);"]

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
    b += _decls() + [""] + _body_common(func) + [""]
    b += regs(False) + regs(True)
    if func == "gather":
        b += dispatch(False, False, "rres") + dispatch(True, False, "sres")
        b += ["mipp::store(res_r, rres);", "mipp::store(res_s, sres);", ""]
    else:
        b += ["std::memcpy(res_r, src, sizeof(res_r));", "std::memcpy(res_s, src, sizeof(res_s));"]
        b += dispatch(False, True, "") + dispatch(True, True, "") + [""]
    b += _compare()
    head = [f"template <mipp::VARIANT V = mipp::U, typename T = double, int LMUL = 1>",
            f"static void test_mipp_{dialect}_{func}()", "{",
            "\tusing IDX = std::conditional_t<sizeof(T) == 1, uint8_t, std::conditional_t<sizeof(T) == 2, uint16_t, "
            "std::conditional_t<sizeof(T) == 4, uint32_t, uint64_t>>>;",
            "\tstd::mt19937 seed(Catch::getSeed());",
            "\tfor (unsigned n = 0; n < get_n_iter(); n++)", "\t{"]
    return head + _indent(b, 2) + ["\t}", "}", ""]


def build_cpp(dialect: str, func: str, datatypes_cpp: List[str], mkinds: List[str],
              lmul_list: Optional[List[int]], ldiv_list: Optional[List[int]], N: int) -> str:
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
    for mk in mkinds:
        lines += [f'\tSECTION("{_MK_LABEL[mk]}")', "\t{"]
        for dt in datatypes_cpp:
            lines += [f'\t\tSECTION("datatype = {dt}")', "\t\t{"]
            calls = [(f"LMUL = {l}", l) for l in lmuls]
            if ldiv_list is None or 2 in ldiv_list:
                calls.append(("LDIV = 2", -2))
            for lab, l in calls:
                if l < 0:
                    lines.append("#if defined(MIPP_LDIV_2)")
                lines += [f'\t\t\tSECTION("{lab}")', "\t\t\t{", "\t\t\t\ttry {",
                          f"\t\t\t\t\ttest_mipp_{dialect}_{func}<{_MK_ENUM[mk]}, {dt}, {l}>();",
                          "\t\t\t\t} catch (const mipp::stub_exception& e) {", "\t\t\t\t\tWARN(e.what());",
                          "\t\t\t\t}", "\t\t\t}"]
                if l < 0:
                    lines.append("#endif // MIPP_LDIV_2")
            lines.append("\t\t}")
        lines.append("\t}")
    lines.append("}")
    return "\n".join(lines)
