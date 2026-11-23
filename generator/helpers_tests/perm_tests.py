"""
Tests of the functions that move lanes with a register of indices or a mask (permute, permute2, permute_b128,
compress, expand, compress_store, compress_store_full, expand_load).

The generic test builder cannot generate their arguments: a register of unsigned indices of the width of the data
(whose valid values depend on the number of lanes of the register, so on the ISA and the LMUL), a mask that selects
the lanes, a pointer whose memory is compared. Their tests are written here. As for the other functions, the result
is compared with the scalar reference (mipp_scalar_* in C, mipp::ISA::SCALAR in C++), for every datatype, LMUL,
half-vector (d2, when the function has one) and mask variant, in the three APIs:

  permute, permute_b128, permute2: indices drawn in [0, N), [0, lanes of a block of 128 bits), [0, 2N) (bounded
      by the largest index of the type: a uint8 index cannot reach the lanes from 256), the registers compared;
  compress, expand, expand_load: the registers compared;
  compress_store: the returned count and the whole output buffer (2N elements, initialized with the same random
      values): exactly the active lanes are written;
  compress_store_full: the count and the first `count` elements (the following ones are unspecified).
"""
from typing import List, Optional

PERM_FUNCS = ("permute", "permute2", "permute_b128", "compress", "expand", "compress_store", "compress_store_full",
              "expand_load")

_MK_ENUM = {"": "mipp::U", "mask": "mipp::M", "maskz": "mipp::Z", "masks": "mipp::S"}
_MK_LABEL = {"": "unmasked", "mask": "Merge-Masked", "maskz": "Zero-Masked", "masks": "Source-Masked"}
_C_STD = ("#include <exception>", "#include <algorithm>", "#include <random>", "#include <cstdio>", "#include <cmath>",
          "#include <cstdlib>", "#include <cstring>", "#include <vector>", '#include "utils/random.hpp"',
          "#ifndef N_ITER", "#define N_ITER {N_ITER}", "#endif")
# scalar reference headers (first, as in the other tests)
_SCALAR_FUNCS = (("load", "load"), ("load", "set_k"), ("store", "store"), ("store", "get"), ("reinterpret", "torvd"),
                 ("reinterpret", "torvm"), ("rearrangement", "permute"), ("rearrangement", "permute2"),
                 ("rearrangement", "permute_b128"), ("rearrangement", "compress"), ("rearrangement", "expand"),
                 ("store", "compress_store"), ("store", "compress_store_full"), ("load", "expand_load"))


def _uint(dt: str) -> str:
    """Unsigned type of the width of `dt` (type of the indices)."""
    return "uint" + "".join(c for c in dt if c.isdigit())


def has_d2(func: str) -> bool:
    """The functions with a mask argument have no half-vector version ("ldiv": false of their prototype)."""
    return func.startswith("permute")


def _scalar_includes(ext: str) -> List[str]:
    return [f"#include <mipp/internal/simd_ext/scalar/{'c' if ext == 'h' else 'cpp'}/functions/{cat}/{fn}.{ext}>"
            for cat, fn in _SCALAR_FUNCS]


def _indent(lines: List[str], n: int) -> List[str]:
    return [("\t" * n + l) if l else l for l in lines]


def _inputs(func: str) -> List[str]:
    """Random inputs: a, b (data), idx (indices in the valid range of the function), mk (mask), src, mem (memory)."""
    top = {"permute": "N", "permute2": "2 * N", "permute_b128": "NB"}.get(func)
    lines = ["for (size_t i = 0; i < N; i++)", "{",
             "\ta[i] = rnd::uniform<T>(seed);", "\tb[i] = rnd::uniform<T>(seed);", "\tsrc[i] = rnd::uniform<T>(seed);",
             "\tmk[i] = rnd::uniform_bool(seed) ? -1 : 0;"]
    if top:
        # the largest index of the type bounds the range (uint8: 256 lanes)
        lines += [f"\tconst uint64_t top = (uint64_t)({top}) - 1 < (uint64_t)(IDX)~(IDX)0 ? (uint64_t)({top}) - 1 : (uint64_t)(IDX)~(IDX)0;",
                  "\tidx[i] = static_cast<IDX>(rnd::uniform<uint64_t>(seed, 0, top));"]
    lines += ["}", "for (size_t i = 0; i < 2 * N; i++)", "\tmem[i] = rnd::uniform<T>(seed);"]
    return lines


def _decls() -> List[str]:
    return ["constexpr size_t NB = (16 / sizeof(T)) < N ? 16 / sizeof(T) : N; // lanes of a block of 128 bits",
            "alignas(64) T a[N];", "alignas(64) T b[N];", "alignas(64) T src[N];", "alignas(64) IDX idx[N];",
            "int32_t mk[N];", "alignas(64) T mem[2 * N];", "alignas(64) T res_r[2 * N];", "alignas(64) T res_s[2 * N];",
            "(void)NB; (void)idx; // idx: the indices of permute, unused by compress and expand"]


def _returns_count(func: str) -> bool:
    return func.startswith("compress_store")


def _compare(func: str) -> List[str]:
    if func == "compress_store":
        # exact: the count, and nothing written after the active lanes
        return ["REQUIRE(cnt_r == cnt_s);", "for (size_t i = 0; i < 2 * N; i++)", "\tREQUIRE(res_r[i] == res_s[i]);"]
    if func == "compress_store_full":
        # the lanes after the count are unspecified
        return ["REQUIRE(cnt_r == cnt_s);", "for (size_t i = 0; i < (size_t)cnt_r; i++)", "\tREQUIRE(res_r[i] == res_s[i]);"]
    return ["for (size_t i = 0; i < N; i++)", "\tREQUIRE(res_r[i] == res_s[i]);"]


# --------------------------------------------------------------------------------------------------
# C API
# --------------------------------------------------------------------------------------------------

def _c_test(func: str, dt: str, sfx: str, mkind: str, lmul: int) -> List[str]:
    sfx_u = f"_{sfx}" if sfx and sfx != "m0" else ""
    mult = f" * {lmul}" if lmul > 0 else (f" / {-lmul}" if lmul < 0 else "")
    mk_sfx = f"_{mkind}" if mkind else ""
    idt = _uint(dt)
    b = [f"constexpr size_t N = MIPP_N_{dt.upper()}{mult};"] + _decls() + [""] + _inputs(func) + [""]
    for prefix, res, p in (("", "res_r", "r"), ("scalar_", "res_s", "s")):
        call = f"mipp_{prefix}{func}_{dt}{mk_sfx}{sfx_u}"
        r_t, rm_t = f"rvd_{prefix}{dt}{sfx_u}_t", f"rvm_{prefix}{dt}{sfx_u}_t"
        b += [f"[[maybe_unused]] {r_t} {p}a = mipp_{prefix}load_{dt}{sfx_u}(a);",
              f"[[maybe_unused]] {r_t} {p}b = mipp_{prefix}load_{dt}{sfx_u}(b);",
              f"[[maybe_unused]] {r_t} {p}src = mipp_{prefix}load_{dt}{sfx_u}(src);",
              f"[[maybe_unused]] {rm_t} {p}m = mipp_{prefix}set_k_{dt}{sfx_u}(mk);",
              f"std::memcpy({res}, mem, sizeof(mem));"]
        if func.startswith("permute"):
            b += [f"[[maybe_unused]] rvd_{prefix}{idt}{sfx_u}_t {p}i = mipp_{prefix}load_{idt}{sfx_u}(idx);"]
            args = f"{p}a, {p}b, {p}i" if func == "permute2" else f"{p}a, {p}i"
            if mkind in ("mask", "maskz"):
                args = f"{p}m, {args}"
            elif mkind == "masks":
                args = f"{p}m, {p}src, {args}"
            b += [f"mipp_{prefix}store_{dt}{sfx_u}({res}, {call}({args}));"]
        elif func in ("compress", "expand"):
            b += [f"mipp_{prefix}store_{dt}{sfx_u}({res}, {call}({p}a, {p}m));"]
        elif func == "expand_load":
            b += [f"mipp_{prefix}store_{dt}{sfx_u}({res}, {call}(mem, {p}m));"]
        else:
            b += [f"const int32_t cnt_{p} = {call}({res}, {p}a, {p}m);"]
        b += [""]
    b += _compare(func)
    tag = f"{mkind}_{sfx}" if mkind else sfx
    return ([f"static void test_mipp_c_{func}_{dt}_{tag}()", "{", f"\tusing T = {dt}_t;", f"\tusing IDX = {idt}_t;",
             "\t(void)sizeof(IDX);", "\tstd::mt19937 seed(Catch::getSeed());",
             "\tfor (unsigned n = 0; n < get_n_iter(); n++)", "\t{"] + _indent(b, 2) + ["\t}", "}", ""])


def build_c(func: str, dts: List[str], sfx: str, mkind: str, lmul: int, N: int) -> str:
    lines = [l.replace("{N_ITER}", str(N)) for l in _C_STD]
    lines += _scalar_includes("h")
    lines += ["#include <mipp.h>", "", "#include <catch2/catch_test_macros.hpp>",
              "#include <catch2/catch_get_random_seed.hpp>", ""]
    if lmul < 0 and not has_d2(func):
        return "\n".join(lines + ["// no half-vector version"])
    if lmul < 0:
        lines.append("#if defined(MIPP_LDIV_2)")
    for dt in dts:
        lines += _c_test(func, dt, sfx, mkind, lmul)
    tag = f"{mkind}_{sfx}" if mkind else sfx
    lines += [f'TEST_CASE("{func} - c tests [{_MK_LABEL[mkind]}, {sfx}]", "[{func}]")', "{"]
    for dt in dts:
        lines += [f'\tSECTION("datatype = {dt}")', "\t{", "\t\ttry {", f"\t\t\ttest_mipp_c_{func}_{dt}_{tag}();",
                  "\t\t} catch (const mipp::stub_exception& e) {", "\t\t\tWARN(e.what());", "\t\t}", "\t}"]
    lines.append("}")
    if lmul < 0:
        lines += ["", "#endif // MIPP_LDIV_2"]
    return "\n".join(lines)


# --------------------------------------------------------------------------------------------------
# C++ Functional and Object APIs
# --------------------------------------------------------------------------------------------------

def _cpp_call(func: str, dialect: str, mkind: str, scalar: bool) -> str:
    """Expression calling the function with the registers (s)a, (s)b, (s)i, (s)m, (s)src."""
    p = "s" if scalar else "r"
    obj = dialect == "obj" and not scalar
    var = _MK_ENUM[mkind] if obj else f"{_MK_ENUM[mkind]}, T, LMUL" + (", mipp::ISA::SCALAR" if scalar else "")
    if func.startswith("permute"):
        args = f"{p}a, {p}b, {p}i" if func == "permute2" else f"{p}a, {p}i"
        if mkind == "":
            return f"mipp::{func}({args})"
        if mkind == "masks":
            return f"mipp::{func}<{var}>({p}m, {p}src, {args})"
        return f"mipp::{func}<{var}>({p}m, {args})"
    if func in ("compress", "expand"):
        return f"mipp::{func}({p}a, {p}m)"
    if func == "expand_load":
        return f"mipp::{func}(mem, {p}m)"
    return f"mipp::{func}({'res_s' if scalar else 'res_r'}, {p}a, {p}m)"


def _cpp_test(func: str, dialect: str, variants: List[str]) -> List[str]:
    def regs(scalar: bool):
        p = "s" if scalar else "r"
        if scalar or dialect == "cpp":
            isa = ", mipp::ISA::SCALAR" if scalar else ""
            return [f"[[maybe_unused]] auto {p}a = mipp::load<T, LMUL{isa}>(a);",
                    f"[[maybe_unused]] auto {p}b = mipp::load<T, LMUL{isa}>(b);",
                    f"[[maybe_unused]] auto {p}src = mipp::load<T, LMUL{isa}>(src);",
                    f"[[maybe_unused]] auto {p}i = mipp::load<IDX, LMUL{isa}>(idx);",
                    f"[[maybe_unused]] auto {p}m = mipp::set_k<T, LMUL{isa}>(mk);"]
        return ["[[maybe_unused]] auto ra = mipp::Rvd<T, LMUL>(a);", "[[maybe_unused]] auto rb = mipp::Rvd<T, LMUL>(b);",
                "[[maybe_unused]] auto rsrc = mipp::Rvd<T, LMUL>(src);", "[[maybe_unused]] auto ri = mipp::Rvd<IDX, LMUL>(idx);",
                "[[maybe_unused]] auto rm = mipp::Rvm<T, LMUL>(mk);"]

    def dispatch(scalar: bool) -> List[str]:
        out: List[str] = []
        res = "res_s" if scalar else "res_r"
        for k, v in enumerate(variants):
            out += [f"{'if constexpr' if k == 0 else 'else if constexpr'} (V == {_MK_ENUM[v]})", "{"]
            call = _cpp_call(func, dialect, v, scalar)
            if _returns_count(func):
                out += [f"\tcnt_{'s' if scalar else 'r'} = {call};"]
            elif dialect == "obj" and not scalar:
                out += [f"\tconst auto rr = {call};", f"\tfor (size_t i = 0; i < N; i++)", f"\t\t{res}[i] = rr[i];"]
            else:
                out += [f"\tmipp::store({res}, {call});"]
            out += ["}"]
        return out

    b: List[str] = [
        "constexpr size_t N = (LMUL > 0) ? (mipp::N<T>() * static_cast<size_t>(LMUL)) : (mipp::N<T>() / static_cast<size_t>(-LMUL));",
    ] + _decls() + [""] + _inputs(func) + [""]
    b += regs(False) + regs(True)
    b += ["std::memcpy(res_r, mem, sizeof(mem));", "std::memcpy(res_s, mem, sizeof(mem));",
          "[[maybe_unused]] int32_t cnt_r = 0, cnt_s = 0;"]
    b += dispatch(False) + dispatch(True) + [""]
    b += _compare(func)
    head = [f"template <mipp::VARIANT V = mipp::U, typename T = double, int LMUL = 1>",
            f"static void test_mipp_{dialect}_{func}()", "{",
            "\tusing IDX = typename mipp::details::uint_of<T>::type;",
            "\tstd::mt19937 seed(Catch::getSeed());",
            "\tfor (unsigned n = 0; n < get_n_iter(); n++)", "\t{"]
    return head + _indent(b, 2) + ["\t}", "}", ""]


def build_cpp(dialect: str, func: str, dts: List[str], mkinds: List[str],
              lmul_list: Optional[List[int]], ldiv_list: Optional[List[int]], N: int, cpp_type=None) -> str:
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
    cpp_type = cpp_type or (lambda d: d)
    lines += [f'TEST_CASE("{func} - {dialect} tests", "[{func}]")', "{"]
    for mk in mkinds:
        lines += [f'\tSECTION("{_MK_LABEL[mk]}")', "\t{"]
        for dt in dts:
            lines += [f'\t\tSECTION("datatype = {cpp_type(dt)}")', "\t\t{"]
            calls = [(f"LMUL = {l}", l) for l in lmuls]
            if has_d2(func) and (ldiv_list is None or 2 in ldiv_list):
                calls.append(("LDIV = 2", -2))
            for lab, l in calls:
                if l < 0:
                    lines.append("#if defined(MIPP_LDIV_2)")
                lines += [f'\t\t\tSECTION("{lab}")', "\t\t\t{", "\t\t\t\ttry {",
                          f"\t\t\t\t\ttest_mipp_{dialect}_{func}<{_MK_ENUM[mk]}, {cpp_type(dt)}, {l}>();",
                          "\t\t\t\t} catch (const mipp::stub_exception& e) {", "\t\t\t\t\tWARN(e.what());",
                          "\t\t\t\t}", "\t\t\t}"]
                if l < 0:
                    lines.append("#endif // MIPP_LDIV_2")
            lines.append("\t\t}")
        lines.append("\t}")
    lines.append("}")
    return "\n".join(lines)
