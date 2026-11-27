"""
C++ Header Generator Module
Generates the C++ namespace wrapper (`mipp::`) and function overloads
for the MIPP library.
"""
from jinja2 import Template, StrictUndefined
import json
import re

from tools import *
from registry import *
from include_gen import IncludeManager, _match_category
from ci_generator import prepare_isa_defines


# -------------------------------------------------------------------------------------------------
# Exported functions
# -------------------------------------------------------------------------------------------------

def _generate_mipp_hpp(include_manager=None):
    file = open("../include/mipp.hpp", "w")

    content = "#pragma once\n"
    content += '#include "mipp/internal/interfaces/cpp/common.hpp"\n'
    for func in interfaces:
        category = _match_category(func)
        content += f'#include "mipp/internal/interfaces/cpp/functions/{category}/{func}.hpp"\n'
    # hand-written utilities (allocator, printing): utils_generator.py
    content += '#include "mipp/cpp/utils.hpp"\n'
    # compile-time permutations (C++17), not included by utils.hpp: they pull 20 rearrangement functions
    content += '#include "mipp/cpp/patterns.hpp"\n'
    # transpositions of an array of registers (ziplo/ziphi steps), not included by utils.hpp either
    content += '#include "mipp/cpp/transpose.hpp"\n'
    print(content, file=file)

def generate_cpp(include_manager=None, isa_list=None, all_isa_names=None):
    file_common = include_manager.get_fd("cpp", "common")

    tpl_header_cpp = """#pragma once

#include "mipp/internal/interfaces/c/common.h"
#include "mipp/internal/simd_ext/scalar/c/common.h"
#include <iostream>

namespace mipp
{
	typedef double float64_t;
	typedef float float32_t;
}"""
    print(tpl_header_cpp, file=file_common)

    for isa in isa_list:
        file_isa_common = include_manager.get_fd(isa["name"] + "_cpp", "common")
        _gen_cpp_structures_isa(file_isa_common, isa)
        _gen_cpp_constexpr_functions_isa(file_isa_common, isa)
        _gen_cpp_functions_isa(include_manager, isa, interfaces)

    # definition of the enum used by everyone in cpp layer
    common_enum_dir = "../include/mipp/internal/templates/cpp"
    os.makedirs(common_enum_dir, exist_ok=True)
    file_common_enum = open(f"{common_enum_dir}/common.hpp", "w")
    print("#pragma once\n", file=file_common_enum)
    print("#include <cstdint>", file=file_common_enum)
    print("#include <type_traits>", file=file_common_enum)
    print("#include \"mipp/internal/interfaces/c/common.h\" // ISA detection (MIPP_NEON, MIPP_RVV, ...): makes this header self-contained\n", file=file_common_enum)
    print("namespace mipp {\n", file=file_common_enum)
    # The enum lists every ISA discovered in simd_ext/ (not only the generated
    # ones) so that user code referring to ISA::<NAME> does not depend on the
    # --simd-ext selection. SCALAR comes first, the others follow alphabetically.
    if all_isa_names is None:
        all_isa_names = list_simd_ext_names()
    enum_names = ["scalar"] + sorted(n for n in set(all_isa_names) | {i["name"] for i in isa_list} if n != "scalar")
    print("enum ISA { " + ", ".join(n.upper() for n in enum_names) + " };", file=file_common_enum)
    print("enum VARIANT { U, M, Z, S }; //variant enum for function templates", file=file_common_enum)
    # LMUL of the index of gather / scatter: one lane per lane of the data, so lmul * sizeof(U) / sizeof(T)
    # (-2 for d2; e.g. 32-bit indices of 64-bit data at LMUL 1: -2)
    print("namespace details {", file=file_common_enum)
    print("constexpr int idx_lmul_frac(int num, int den) { return num >= den ? num / den : -(den / num); }", file=file_common_enum)
    print("template <typename T, typename U> constexpr int idx_lmul(int lmul)", file=file_common_enum)
    print("{ return lmul > 0 ? idx_lmul_frac(lmul * (int)sizeof(U), (int)sizeof(T)) : idx_lmul_frac((int)sizeof(U), -lmul * (int)sizeof(T)); }", file=file_common_enum)
    print("template <typename T, typename U> constexpr int data_lmul(int lmul_idx)", file=file_common_enum)
    print("{ return lmul_idx > 0 ? idx_lmul_frac(lmul_idx * (int)sizeof(T), (int)sizeof(U)) : idx_lmul_frac((int)sizeof(T), -lmul_idx * (int)sizeof(U)); }", file=file_common_enum)
    # unsigned type of the width of T: indices of permute (`"fixeddatatype": "uint"`)
    print("template <typename T> struct uint_of { typedef typename std::conditional<sizeof(T) == 1, uint8_t, typename std::conditional<sizeof(T) == 2, uint16_t, typename std::conditional<sizeof(T) == 4, uint32_t, uint64_t>::type>::type>::type type; };", file=file_common_enum)
    print("} // namespace details", file=file_common_enum)

    isa_list_copy = prepare_isa_defines(isa_list) # this is the function that sets the gen_define key for every ISAs for some reason

    for index, isa in enumerate(isa_list_copy):
        if index == 0:
            print("#if " + isa["gen_define"], file=file_common_enum)
        else:
            print("#elif " + isa["gen_define"], file=file_common_enum)
        print(f"constexpr ISA DEFAULT_ISA = ISA::{isa['name'].upper()};", file=file_common_enum)
    print("#else\n#error \"No ISA defined for cpp wrapper\"\n#endif", file=file_common_enum)

    print("template<typename T, int LMUL=1, ISA ISA_TYPE=DEFAULT_ISA> struct vd_type{};", file=file_common_enum)
    print("template<typename T, int LMUL=1, ISA ISA_TYPE=DEFAULT_ISA> struct vm_type{};", file=file_common_enum)
    print("template<typename T, int LMUL=1, ISA ISA_TYPE=DEFAULT_ISA> using vd = typename vd_type<T,LMUL,ISA_TYPE>::type;", file=file_common_enum)
    print("template<typename T, int LMUL=1, ISA ISA_TYPE=DEFAULT_ISA> using vm = typename vm_type<T,LMUL,ISA_TYPE>::type;", file=file_common_enum)
    print("template<typename T, int LMUL=1, ISA ISA_TYPE=DEFAULT_ISA> constexpr uint32_t N(){ return 0; }", file=file_common_enum)
    print("template<ISA ISA_TYPE=DEFAULT_ISA> constexpr uint32_t vd_sz_bits(){ return 0; }", file=file_common_enum)
    print("template<ISA ISA_TYPE=DEFAULT_ISA> constexpr uint32_t vd_sz_bytes(){ return 0; }", file=file_common_enum)
    print("template<ISA ISA_TYPE=DEFAULT_ISA> constexpr uint32_t req_alignment(){ return 0; }", file=file_common_enum)

    print("}\n", file=file_common_enum)
    file_common_enum.close()

    _gen_cpp_generic_templates(include_manager, isa_list_copy, interfaces)
    
    file_common_glue = include_manager.get_fd("cpp", "common")
    _gen_cpp_common(isa_list_copy, file_common_glue)
    _gen_cpp_functions(isa_list_copy, include_manager, copy_interfaces)    
    _generate_mipp_hpp(include_manager)

def _gen_cpp_common(isa_list, file):
    print("", file=file)
    for index, isa in enumerate(isa_list):
        if index == 0:
            print("#if " + isa["gen_define"], file=file)
        else:
            print("#elif " + isa["gen_define"], file=file)
        
        print(f'#include "mipp/internal/simd_ext/{isa["name"].lower()}/cpp/common.hpp"', file=file)
    print("#else\n#error \"No ISA defined for cpp wrapper\"\n#endif", file=file)

def _gen_cpp_functions(isa_list, include_manager, funcs):
    if include_manager.granularity == "coarse":
        for f in funcs.keys():
            category = _match_category(f)
            file = include_manager.get_fd("cpp", f)
            print("#pragma once\n", file=file)
            print('#include "mipp/internal/interfaces/cpp/common.hpp"\n', file=file)
            for index, isa in enumerate(isa_list):
                if index == 0:
                    print("#if " + isa["gen_define"], file=file)
                else:
                    print("#elif " + isa["gen_define"], file=file)
                print(f'#include "mipp/internal/simd_ext/{isa["name"].lower()}/cpp/functions/{category}/{f}.hpp"', file=file)
            print("#else\n#error \"No ISA defined for cpp wrapper\"\n#endif", file=file)
    else:
        for f in funcs.keys():
            category = _match_category(f)
            func_variants = ["u"]
            ms = funcs[f].get("variants")
            if ms:
                if ms.is_maskable():
                    func_variants.append("m")
                if ms.is_maskzable():
                    func_variants.append("z")
                if ms.is_masksable():
                    func_variants.append("s")
            func_lmuls = ["m1", "m2", "m4", "m8", "d2"]

            for v in func_variants:
                for l in func_lmuls:
                    if l == "d2" and not is_defined_for_lmul(funcs[f]["proto"], -2):
                        # no half-vector version ("ldiv": false in the prototype): no wrapper, which would include
                        # ISA headers that are not generated
                        continue
                    valid_isas = [
                        isa for isa in isa_list
                        if l != "d2" or (isa.get("is_scalar", False) or any(x < 0 for x in isa.get("hw_lmul", []) + isa.get("sw_lmul", [])))
                    ]
                    if changes_lmul(funcs[f]["proto"]):
                        lmul_n = -2 if l == "d2" else int(l[1:])
                        valid_isas = [isa for isa in valid_isas if isa_provides_lmul(isa, funcs[f]["proto"], lmul_n)]
                    file = include_manager.get_fd("cpp", f, variant=v, lmul=l)
                    print(f"#pragma once\n// CPP wrapper: {f} [{v}/{l}]\n", file=file)
                    print('#include "mipp/internal/interfaces/cpp/common.hpp"\n', file=file)
                    for index, isa in enumerate(valid_isas):
                        if index == 0:
                            print("#if " + isa["gen_define"], file=file)
                        else:
                            print("#elif " + isa["gen_define"], file=file)
                        print(f'#include "mipp/internal/simd_ext/{isa["name"].lower()}/cpp/functions/{category}/{v}/{l}/{f}.hpp"', file=file)
                    if len(valid_isas) == len(isa_list):
                        print("#else\n#error \"No ISA defined for cpp wrapper\"\n#endif", file=file)
                    elif valid_isas:
                        print("#endif", file=file)

        include_manager.generate_umbrella_headers("cpp")
        include_manager.close_layer_fds("cpp")

# -------------------------------------------------------------------------------------------------
# Helpers
# -------------------------------------------------------------------------------------------------


# Immediate versions of the C++ API (`"imm"` of the registry, see codegen/imm.py): `mipp::slide<3>(a, b)` for
# `mipp::slide(a, b, 3)`. One template per concrete overload, whose only template parameter is the constant: the
# overload is chosen by the types of the registers, as for the dynamic function, and the range is checked at compile
# time. The call passes a constant to the C function, whose dispatch then uses the immediate instruction.
_IMM_CPP_RANGES = {
    "lt_n": ("0", "<", "N"), "le_n": ("0", "<=", "N"), "lt_nb": ("0", "<", "NB"), "le_nb": ("0", "<=", "NB"),
    "lt_bits": ("0", "<", "BITS"),
}


def _emit_imm_template(funcs, f, dt_par, dt_ret, isa, cpp_func_name, c_func_name, lmul, file):
    rng = funcs[f].get("imm")
    if not rng:
        return
    proto = build_proto(funcs[f]["proto"], dt_par, dt_ret, isa, cpp_func_name, lmul, isa_name=True, cpp=True)
    m = re.search(r", const (u?int32_t) (s\d+)\)$", proto)
    if not m:
        raise ValueError(f"'{f}': immediate version without a final integer argument ({proto})")
    int_t, arg = m.group(1), m.group(2)
    proto = proto[:m.start()] + ")"
    call = build_call(funcs[f]["proto"], dt_par, dt_ret, "", c_func_name, lmul, False)
    call = re.sub(r"\b" + arg + r"\b", f"({int_t})S", call)
    lo, op, hi = _IMM_CPP_RANGES[rng]
    n = f"N<{dt_par}_t, {lmul}, ISA::{isa['name'].upper()}>()"
    hi = {"N": f"(int){n}", "NB": f"(int)(16 / sizeof({dt_par}_t) < {n} ? 16 / sizeof({dt_par}_t) : {n})",
          "BITS": f"(int)(8 * sizeof({dt_par}_t))"}[hi]
    print(f"template <int S>", file=file)
    print(proto + " {", file=file)
    print(f'\tstatic_assert(S >= {lo} && S {op} {hi}, "mipp::{cpp_func_name}<S>: S out of range");', file=file)
    print("\t" + call + ";", file=file)
    print("}", file=file)

def _cpp_base_name(funcs, f):
    """
    Name of `f` in the C++ APIs: `cpp_name` of the registry when given, `f` otherwise. The scalar forms of a function
    (`sub_vs`, `sub_sv`, see forms.py) are overloads of the base function (`mipp::sub(r, s)`, `mipp::sub(s, r)`).
    """
    return funcs[f].get("cpp_name", f)


set_functions = ["set0", "set0_k", "set", "set_k", "set1", "set1_k"] + list(LOAD_FUNCS)


# duplicate of c_generator ...
def _compute_dt_par_dt_ret(funcs, f, dt):
    """
    returns dt_par and dt_ret based on dt.  len(dt.split(',')) > 1 for cast and cast_k 
    """
    # Returns (dt_par, dt_ret) or exits on unsupported type (same behavior as original).
    if len(dt.split(',')) <= 1:
        dt_par = dt.split(',')[0]
        dt_ret = dt.split(',')[0]
        if dt_par not in funcs[f]["datatypes"]:
            print("Panic: unsupported type for '" + f + "<" + dt_par + "," + dt_par + ">' function.")
            exit(-1)
    else:
        dt_par = dt.split(',')[0]
        dt_ret = dt.split(',')[1]

        dtk = dt_par + "," + dt_ret
        if dtk not in funcs[f]["datatypes"]:
            print("Panic: unsupported type for '" + f + "<" + dt_par + "," + dt_ret + ">' function.")
            exit(-1)

    return dt_par, dt_ret

def _cpp_custom_prefix_generator(f, isa_name="", funcs=None):
    """
    include c_mipp version of the function + set namespace to mipp for the cpp wrapper.
    """
    s = "#pragma once\n"

    if isa_name:
        category = _match_category(f) if f else ""
        if f is None: # common file
            s += '#include "mipp/internal/templates/cpp/common.hpp"\n'
            s += '#include "mipp/internal/interfaces/cpp/common.hpp"\n'
            s += f'#include "mipp/internal/simd_ext/{isa_name}/c/common.h"\n'
        
        if f is not None: # function file
            s += f'#include "mipp/internal/simd_ext/{isa_name}/cpp/common.hpp"\n'
            s += f'#include "mipp/internal/simd_ext/{isa_name}/c/functions/{category}/{f}.h"\n'

            variant_set = None
            if funcs is not None and f in funcs:
                variant_set = funcs[f]["variants"]
            
            if f in set_functions or (variant_set and variant_set.is_any_mask()):
                s += f'#include "mipp/internal/templates/cpp/functions/{category}/{f}.hpp"\n'

    else: 
        category = _match_category(f)
        s += '#include "mipp/internal/interfaces/cpp/common.hpp"\n'
        s += f'#include "mipp/internal/interfaces/c/functions/{category}/{f}.h"\n'
        s += f'#include "mipp/internal/simd_ext/scalar/c/functions/{category}/{f}.h"\n'
    s += "namespace mipp {\n"
    return s

# maybe there is such thing as too much helpers tbh
def _cpp_close_namespace():
    return "}\n"



# -------------------------------------------------------------------------------------------------
# Masked C++ wrappers (proto-driven: correct names vm0/vdsrc/vd0..., correct arity)
# -------------------------------------------------------------------------------------------------
def _masked_c_symbol(dt_par, dt_ret, f, is_cast, isa=None, isa_name=False):
    # Base C symbol without lmul suffix.
    if not is_cast:
        return build_func_name_short(isa, dt_par, f, isa_name=isa_name, alias=True)
    return build_func_name(isa, dt_par, dt_ret, f, isa_name=isa_name, alias=True)

def get_dt_par_size(dt_par):
    if dt_par in datatypes:
        return datatypes[dt_par]["n_bits"]
    else:
        print(f"error: data type {dt_par} not found in datatypes")
        exit(-1)

def _tpl_scalar_for_arg(arg):
    # Returns a string type name usable in C++ template decls: "T" or "int32_t" etc.
    if arg.get("fixeddatatype"):
        if arg["fixeddatatype"] == "ret":
            # index of gather / scatter: the second type of the pair
            return "U"
        if arg["fixeddatatype"] == "uint":
            # unsigned integers of the width of T (indices of permute)
            return "typename details::uint_of<T>::type"
        if arg["fixeddatatype"] not in datatypes and arg["fixeddatatype"] in all_categories:
                return "U"
        elif arg["fixeddatatype"] in datatypes:
                realdatatype = datatypes[arg["fixeddatatype"]]
                return realdatatype["cstd"]
       # return datatypes[arg["fixeddatatype"]]["cstd"]
    return "T"

def _generic_mask_decl_gather_scatter(file, cpp_func_name, proto, mask_kind):

    if mask_kind == "mask":
        ret = "template <VARIANT V=M, typename T, typename U, int LMUL=1, ISA ISA_TYPE=DEFAULT_ISA>"
    elif mask_kind == "maskz":
        ret = "template <VARIANT V=Z, typename T, typename U, int LMUL=1, ISA ISA_TYPE=DEFAULT_ISA>"
    else:
        ret = "template <VARIANT V=S, typename T, typename U, int LMUL=1, ISA ISA_TYPE=DEFAULT_ISA>"

    ret += "inline " + ("vd<T,LMUL,ISA_TYPE>" if proto["ret"]["type"] == "reg" else
                      "vm<T,LMUL,ISA_TYPE>" if proto["ret"]["type"] == "msk" else
                      "T" if proto["ret"]["type"] == "val" else
                      "void")
    s = "{{ret}} {{cpp_func_name}}("

    is_first = True
    cnt_reg = 0
    cnt_msk = 0
    cnt_val = 0
    cnt_ptr = 0

    # the mask has the type of the data (T); the index (U) has its own LMUL (one lane per lane of the data)
    if mask_kind in ("mask", "maskz"):
        s += "vm<T,LMUL,ISA_TYPE> vm0"
        is_first = False
    elif mask_kind == "masks":
        s += "const vm<T,LMUL,ISA_TYPE> vm0, vd<T,LMUL,ISA_TYPE> vdsrc"
        is_first = False
    for args in proto["args"]:

        tmp_str = ""
        if not is_first:
            tmp_str += ", "
        if args["charac"] == "RO":
            tmp_str += "const "

        A = _tpl_scalar_for_arg(args)

        if args["type"] == "reg" and args.get("lmul", "same") == "ratio":
            tmp_str += "vd<{{A}},details::idx_lmul<T,{{A}}>(LMUL),ISA_TYPE> vd" + str(cnt_reg)
            cnt_reg += 1
        elif args["type"] == "reg":
            tmp_str += "vd<{{A}},LMUL,ISA_TYPE> vd" + str(cnt_reg)
            cnt_reg += 1
        elif args["type"] == "msk":
            tmp_str += "vm<{{A}},LMUL,ISA_TYPE> vm" + str(cnt_msk)
            cnt_msk += 1
        elif args["type"] == "val":
            tmp_str += "{{A}} s" + str(cnt_val)
            cnt_val += 1
        elif args["type"] == "ptr":
            tmp_str += "T* p" + str(cnt_ptr)
            cnt_ptr += 1
        elif args["type"] == "Nele":
            tmp_str += "{{A}} vals[N<{{A}},LMUL,ISA_TYPE>()]"
        elif args["type"] == "vindex":
            tmp_str += "vd<int32_t,LMUL,ISA_TYPE> vi"
        else:
            tmp_str += "void* _"

        tmp_template = Template(tmp_str, undefined=StrictUndefined)
        s += tmp_template.render(A=A) # render the current arg to update s for the next iteration (for correct comma placement and const keywords)

        is_first = False
    s += ");" + "\n"
    template = Template(s, undefined=StrictUndefined)
    # for dt in all_datatypes:
        # cpp_fname_dt = cpp_func_name
    tpl = template.render(cpp_func_name=cpp_func_name, ret=ret)
    print(tpl, file=file)

    #print(s, file=file)
    
def _generic_mask_decl(file, cpp_func_name, proto, mask_kind):
    """
    Emit a generic template declaration with correct *names* (vm0/vdsrc/vd0/s0/p0...),
    but *types* expressed in terms of T and LMUL.

    mask_kind:
      - "mask": prepend 'vm<T,LMUL> vm0', default variant M (merge-maskable function)
      - "maskz": same signature, default variant Z (zero-mask only, e.g. load / loadu)
      - "masks": prepend 'const vm<T,LMUL> vm0, vd<T,LMUL> vdsrc'
    """

    if "gather" in cpp_func_name or "scatter" in cpp_func_name:
        return _generic_mask_decl_gather_scatter(file, cpp_func_name, proto, mask_kind)
    # Template header differs per kind because the default V differs.
    if mask_kind == "mask":
        print("template <VARIANT V=M, typename T, int LMUL=1, ISA ISA_TYPE=DEFAULT_ISA>", file=file)
    elif mask_kind == "maskz":
        print("template <VARIANT V=Z, typename T, int LMUL=1, ISA ISA_TYPE=DEFAULT_ISA>", file=file)
    else:
        print("template <VARIANT V=S, typename T, int LMUL=1, ISA ISA_TYPE=DEFAULT_ISA>", file=file)

    # Return type: generic on T,LMUL (only valid for non-cast funcs; you already skip casts)
    ret = "inline " + ("vd<T,LMUL,ISA_TYPE>" if proto["ret"]["type"] == "reg" else
                      "vm<T,LMUL,ISA_TYPE>" if proto["ret"]["type"] == "msk" else
                      "T" if proto["ret"]["type"] == "val" else
                      "void")

    s = f"{ret} {cpp_func_name}("

    is_first = True
    cnt_reg = 0
    cnt_msk = 0
    cnt_val = 0
    cnt_ptr = 0

    # masked prefix args (names must match build_call expectations)
    if mask_kind in ("mask", "maskz"):
        s += "vm<T,LMUL,ISA_TYPE> vm0"
        is_first = False
    elif mask_kind == "masks":
        s += "const vm<T,LMUL,ISA_TYPE> vm0, vd<T,LMUL,ISA_TYPE> vdsrc"
        is_first = False

    for arg in proto["args"]:
        if not is_first:
            s += ", "
        if arg["charac"] == "RO":
            s += "const "

        # decide the scalar type for this argument
        A = _tpl_scalar_for_arg(arg)

        if arg["type"] == "reg":
            s += f"vd<{A},LMUL,ISA_TYPE> vd{cnt_reg}"
            cnt_reg += 1
        elif arg["type"] == "msk":
            s += f"vm<{A},LMUL,ISA_TYPE> vm{cnt_msk}"
            cnt_msk += 1
        elif arg["type"] == "val":
            s += f"{A} s{cnt_val}"
            cnt_val += 1
        elif arg["type"] == "ptr":
            s += f"{A}* p{cnt_ptr}"
            cnt_ptr += 1
        elif arg["type"] == "Nele":
            s += f"{A} vals[N<{A},LMUL,ISA_TYPE>()]"
        elif arg["type"] == "vindex":
            s += "vd<int32_t,LMUL,ISA_TYPE> vi"
        else:
            s += "void* _"

        is_first = False
    s += ");" + "\n"

    print(s, file=file)


def _mask_tpl_spec(file, proto, dt_par, dt_ret, cpp_func_name, c_base, mk_letter, mask_kind, lmul=1, isa=None, isa_name=False, ignore_mask=False):
    """
    Emit explicit specialization for masked template for a given LMUL.

    Example (storeu, uint32_t, LMUL=2):
      template <>
      inline void storeu<M, uint32_t, 2>(vm<uint32_t,2> vm0, uint32_t* p0, const vd<uint32_t,2> vd0) {
          mipp_storeu_uint32_mask_m2(vm0, p0, vd0);
      }

    With ignore_mask=True (used for the U variant), the signature is the one of
    `mask_kind` but the mask (and vdsrc) are ignored and the unmasked C kernel is
    called, so that `f<U>(m, ...)` behaves exactly like `f(...)`.
    """
    Tret = datatypes[dt_ret]["cstd"]

    print("template <>", file=file)

    full_cpp_func_name = cpp_func_name
    if mask_kind:
        full_cpp_func_name += "_" + mask_kind
    sig = build_proto(proto, dt_par, dt_ret, isa, full_cpp_func_name, lmul, isa_name=isa_name, cpp=True, masked_version=mask_kind)


    if isa is not None:
        sig = sig.replace(
            f"{cpp_func_name}_{mask_kind}(",
            f"{cpp_func_name}<{mk_letter}, {Tret}, {lmul}, {isa['name'].upper()}>("
        )
    else :
        sig = sig.replace(
            f"{cpp_func_name}_{mask_kind}(",
            f"{cpp_func_name}<{mk_letter}, {Tret}, {lmul}>("
        )

    if ignore_mask:
        # load/loadu/gather/scatter protos hardcode the variant letter in the template args
        for letter in ("M", "Z", "S"):
            sig = sig.replace(f"{cpp_func_name}<{letter}, ", f"{cpp_func_name}<{mk_letter}, ", 1)

    print(sig + " {", file=file)

    # # C masked symbol naming:
    # # - if your C layer has no _m1 for masked: use base for LMUL=1, and add _mX for LMUL>1
    # # - if it DOES have _m1 too, change this to always suffix.
    # if int(lmul) == 1:
    #     c_symbol = f"{c_base}_{mask_kind}"
    # else:
    lmul_str = "m" + str(lmul)
    if lmul < 0: 
        lmul_str = "d" + str(-lmul)
    if ignore_mask:
        print("\t(void)vm0;", file=file)
        if mask_kind == "masks":
            print("\t(void)vdsrc;", file=file)
        c_symbol = f"{c_base}_{lmul_str}"
        call = build_call(proto, dt_par, dt_ret, isa, c_symbol, lmul, isa_name=isa_name, masked_version=False)
    else:
        c_symbol = f"{c_base}_{mask_kind}_{lmul_str}"
        call = build_call(proto, dt_par, dt_ret, isa, c_symbol, lmul, isa_name=isa_name, masked_version=mask_kind)
    print("\t" + call + ";", file=file)
    print("}", file=file)


def _emit_mask_specs(get_file, proto, dt_par, dt_ret, cpp_func_name, c_base, mask_status, lmul, isa):
    """
    Emit every masked specialization (M, Z, S and U) of one function for one
    datatype and one LMUL. `get_file(variant)` returns the output file for the
    variant directory ("m", "z" or "s").

    U ignores the mask: it is emitted for each generic masked template that
    exists (the `vm0` form when the function is maskable or maskzable, the
    `vm0, vdsrc` form when it is masksable).
    """
    if mask_status.is_maskable():
        _mask_tpl_spec(get_file("m"), proto, dt_par, dt_ret, cpp_func_name, c_base, "M", "mask", lmul=lmul, isa=isa, isa_name=True)
    if mask_status.is_maskzable():
        _mask_tpl_spec(get_file("z"), proto, dt_par, dt_ret, cpp_func_name, c_base, "Z", "maskz", lmul=lmul, isa=isa, isa_name=True)
    if mask_status.is_masksable():
        _mask_tpl_spec(get_file("s"), proto, dt_par, dt_ret, cpp_func_name, c_base, "S", "masks", lmul=lmul, isa=isa, isa_name=True)

    # U variant: same signature as the masked template, mask ignored
    if mask_status.is_maskable():
        _mask_tpl_spec(get_file("m"), proto, dt_par, dt_ret, cpp_func_name, c_base, "U", "mask", lmul=lmul, isa=isa, isa_name=True, ignore_mask=True)
    elif mask_status.is_maskzable():
        _mask_tpl_spec(get_file("z"), proto, dt_par, dt_ret, cpp_func_name, c_base, "U", "maskz", lmul=lmul, isa=isa, isa_name=True, ignore_mask=True)
    if mask_status.is_masksable():
        _mask_tpl_spec(get_file("s"), proto, dt_par, dt_ret, cpp_func_name, c_base, "U", "masks", lmul=lmul, isa=isa, isa_name=True, ignore_mask=True)


# -------------------------------------------------------------------------------------------------
# CPP REWORK WIP :)
# -------------------------------------------------------------------------------------------------

# regular cpp functions r overloads HOWEVER masked functions r template specialization 
# n.b : functions in set_functions r also template specializations bc they don't have any register arguments 
#       so they can't really be overloaded ...
# so we want to define the generic template in a single place n then specialize them in every header 
# the idea is to have a directory called simd_ext_cpp/templates n put the generic templates in there
# n then include them to every isa header and specialize them there with the correct types and names
def _gen_cpp_generic_templates(include_manager, isa, funcs):
    # this function will generate the generic template of every masked function in separate headers 4 each func
    for f in funcs:

        if ( f not in set_functions ) and ( "variants" not in funcs[f] or funcs[f]["variants"] is None ):
            continue
        file = include_manager.get_fd("templates", f)

        print("#pragma once\n", file=file)
        print('#include "mipp/internal/templates/cpp/common.hpp"\n', file=file)
        print("namespace mipp {\n", file=file)

        if f in set_functions:
            gen_set_func_error(f, file)

        ms = funcs[f]["variants"]
        proto = funcs[f]["proto"]

        dt_par, dr_ret = _compute_dt_par_dt_ret(funcs, f, funcs[f]["datatypes"][0]) # we just need one dt to build the template since it's generic on T
        cpp_func_name = build_cpp_func_name_short(funcs[f]["proto"], dt_par, _cpp_base_name(funcs, f)) # THIS IS A HACK BC build_cpp_func_name_short explodes w/o concrete type ...

        if ms.is_maskable():
            _generic_mask_decl(file, cpp_func_name, proto, "mask")
        elif ms.is_maskzable():
            _generic_mask_decl(file, cpp_func_name, proto, "maskz")

        if ms.is_masksable():
            _generic_mask_decl(file, cpp_func_name, proto, "masks")

        print("}\n", file=file)
def _gen_cpp_structures_isa(file, isa):

    isa_cpp_type = isa["name"].upper()
    isa_c_name = isa["name"].lower()

    print(_cpp_custom_prefix_generator(None, isa["name"]), file=file)

    template = """template<> struct vd_type<{{ datatype.cstd }}, {{ lmul }}, ISA::{{isa_cpp_type}}>{ using type = vd_{{isa_c_name}}_{{ datatype.category }}{{ datatype.n_bits }}_m{{ lmul }}_t; };"""
    j2_template = Template(template, undefined=StrictUndefined)
    for lmul in all_lmul:
        for dt in datatypes:
            print(j2_template.render(datatype=datatypes[dt], lmul=str(lmul), isa_cpp_type=isa_cpp_type, isa_c_name=isa_c_name), file=file)

    template = """template<> struct vm_type<{{ datatype.cstd }}, {{ lmul }}, ISA::{{isa_cpp_type}}>{ using type = vm_{{isa_c_name}}_{{ datatype.category }}{{ datatype.n_bits }}_m{{ lmul }}_t; };"""
    j2_template = Template(template, undefined=StrictUndefined)
    for lmul in all_lmul:
        for dt in datatypes:
            print(j2_template.render(datatype=datatypes[dt], lmul=str(lmul), isa_cpp_type=isa_cpp_type, isa_c_name=isa_c_name), file=file)
    # maybe enum shouldn't be defined here idk

    # ldiv
    has_ldiv = isa.get("is_scalar", False) or any(x < 0 for x in isa.get("hw_lmul", []) + isa.get("sw_lmul", []))
    if has_ldiv:
        ldiv = 2
        ldiv_m = -2
        template = """template<> struct vd_type<{{ datatype.cstd }}, {{ ldiv_m }}, ISA::{{isa_cpp_type}}>{ using type = vd_{{isa_c_name}}_{{ datatype.category }}{{ datatype.n_bits }}_d{{ ldiv }}_t; };"""
        template_msk = """template<> struct vm_type<{{ datatype.cstd }}, {{ ldiv_m }}, ISA::{{isa_cpp_type}}>{ using type = vm_{{isa_c_name}}_{{ datatype.category }}{{ datatype.n_bits }}_d{{ ldiv }}_t; };"""
        j2_template = Template(template, undefined=StrictUndefined)
        j2_template_msk = Template(template_msk, undefined=StrictUndefined)
        for dt in datatypes:
            print(j2_template.render(datatype=datatypes[dt], ldiv_m=str(ldiv_m), isa_cpp_type=isa_cpp_type, isa_c_name=isa_c_name, ldiv=str(ldiv)), file=file)
        for dt in datatypes:
            print(j2_template_msk.render(datatype=datatypes[dt], ldiv_m=str(ldiv_m), isa_cpp_type=isa_cpp_type, isa_c_name=isa_c_name, ldiv=str(ldiv)), file=file)

def _gen_cpp_constexpr_functions_isa(file, isa):
    isa_cpp_type = isa["name"].upper()

    template = """template<> constexpr uint32_t vd_sz_bits<ISA::{{isa_cpp_type}}>(){ return MIPP_{{isa_cpp_type}}_RVD_SIZE_BIT; }"""
    j2_template = Template(template, undefined=StrictUndefined)
    print(j2_template.render(isa_cpp_type=isa_cpp_type), file=file)
    template = """template<> constexpr uint32_t vd_sz_bytes<ISA::{{isa_cpp_type}}>(){ return MIPP_{{isa_cpp_type}}_RVD_SIZE_BYTE; }"""
    j2_template = Template(template, undefined=StrictUndefined)
    print(j2_template.render(isa_cpp_type=isa_cpp_type), file=file)
    template = """template<> constexpr uint32_t req_alignment<ISA::{{isa_cpp_type}}>(){ return MIPP_{{isa_cpp_type}}_RVD_SIZE_BYTE; } // placeholder """
    j2_template = Template(template, undefined=StrictUndefined)
    print(j2_template.render(isa_cpp_type=isa_cpp_type), file=file)

    template = """template<> constexpr uint32_t N<{{ datatype.cstd }}, {{ lmul }}, ISA::{{isa_cpp_type}} >(){ return MIPP_{{isa_cpp_type}}_N_{{type_category_upper}}{{ datatype.n_bits }}{{ lmul_suffix }}; }"""
    j2_template = Template(template, undefined=StrictUndefined)
    for lmul in all_lmul:
        if lmul == 1:
            lmul_suffix = ""
        else:
            lmul_suffix = "_M" + str(lmul)
        for dt in datatypes:
            print(j2_template.render(datatype=datatypes[dt], lmul=str(lmul), type_category_upper=datatypes[dt]["category"].upper(), lmul_suffix=lmul_suffix, isa_cpp_type=isa_cpp_type), file=file)

    # once every isa supports ldiv. This can be moved to the loop above.
    has_ldiv = isa.get("is_scalar", False) or any(x < 0 for x in isa.get("hw_lmul", []) + isa.get("sw_lmul", []))
    if has_ldiv:
        ldiv = -2
        ldiv_suffix = "_D" + str(-ldiv)
        template = """template<> constexpr uint32_t N<{{ datatype.cstd }}, {{ ldiv }}, ISA::{{isa_cpp_type}} >(){ return MIPP_{{isa_cpp_type}}_N_{{type_category_upper}}{{ datatype.n_bits }}{{ ldiv_suffix }}; }"""
        j2_template = Template(template, undefined=StrictUndefined)
        for dt in datatypes:
            print(j2_template.render(datatype=datatypes[dt], ldiv=str(ldiv), type_category_upper=datatypes[dt]["category"].upper(), ldiv_suffix=ldiv_suffix, isa_cpp_type=isa_cpp_type), file=file)


    print(_cpp_close_namespace(), file=file) # hacky -> implies it HAS to be called after _gen_cpp_structures_isa ...

def _gen_cpp_functions_isa(include_manager, isa, funcs):
    layer_name = isa["name"] + "_cpp"
    if include_manager.granularity == "coarse":
        for f in funcs:
            file = include_manager.get_fd(layer_name, f)
            prefix = _cpp_custom_prefix_generator(f, isa["name"], funcs)
            print(prefix, file=file)

            for dt in funcs[f]["datatypes"]:
                is_cast = len(dt.split(',')) > 1
                is_gthr_scttr =  ("gather" in f) or ("scatter" in f)
                is_cast = is_cast

                if not is_cast:
                    dt_par = dt.split(',')[0]
                    dt_ret = dt.split(',')[0]
                elif is_gthr_scttr:
                    dt_par = dt.split(',')[0]
                    dt_ret = dt.split(',')[1]
                else:
                    dt_par = dt.split(',')[0]
                    dt_ret = dt.split(',')[1]

                if not is_cast and not is_gthr_scttr:
                    c_func_name = build_func_name_short(isa, dt_par, f, isa_name=True, alias=True)
                    cpp_func_name = build_cpp_func_name_short(funcs[f]["proto"], dt_ret, _cpp_base_name(funcs, f))
                elif is_gthr_scttr:
                    c_func_name = build_func_name(isa, dt_par, dt_ret, f, isa_name=True, alias=True)                
                    cpp_func_name = build_cpp_func_name_short(funcs[f]["proto"], dt_ret, _cpp_base_name(funcs, f))
                else:
                    c_func_name = build_func_name(isa, dt_par, dt_ret, f, isa_name=True, alias=True)
                    cpp_func_name = build_cpp_func_name(dt_ret, f)

                for lmul in [l for l in all_lmul if isa_provides_lmul(isa, funcs[f]["proto"], l) and is_defined_for_dt_lmul(funcs[f]["proto"], dt, l)]:
                    print(build_proto(funcs[f]["proto"], dt_par, dt_ret, isa, cpp_func_name, lmul, isa_name=True, cpp=True) + " {", file=file)
                    print("\t" + build_call(funcs[f]["proto"], dt_par, dt_ret, "", c_func_name + "_m" + str(lmul), lmul, False) + ";", file=file)
                    print("}", file=file)
                    _emit_imm_template(funcs, f, dt_par, dt_ret, isa, cpp_func_name, c_func_name + "_m" + str(lmul), lmul, file)
                mask_status = funcs[f]["variants"]

                has_ldiv = (isa.get("is_scalar", False) or any(x < 0 for x in isa.get("hw_lmul", []) + isa.get("sw_lmul", []))) and isa_provides_lmul(isa, funcs[f]["proto"], -2) and is_defined_for_dt_lmul(funcs[f]["proto"], dt, -2)
                if has_ldiv:
                    ldiv = -2
                    print(build_proto(funcs[f]["proto"], dt_par, dt_ret, isa, cpp_func_name, ldiv, isa_name=True, cpp=True) + " {", file=file)
                    print("\t" + build_call(funcs[f]["proto"], dt_par, dt_ret, "", c_func_name + "_d" + str(-ldiv), ldiv, False) + ";", file=file)
                    print("}", file=file)
                    _emit_imm_template(funcs, f, dt_par, dt_ret, isa, cpp_func_name, c_func_name + "_d" + str(-ldiv), ldiv, file)
                
                if mask_status and mask_status.is_any_mask():
                    proto = funcs[f]["proto"]
                    c_base = _masked_c_symbol(dt_par, dt_ret, f, is_cast, isa=isa, isa_name=True)

                    for lmul in [l for l in all_lmul if isa_provides_lmul(isa, funcs[f]["proto"], l) and is_defined_for_dt_lmul(funcs[f]["proto"], dt, l)]:
                        _emit_mask_specs(lambda _v: file, proto, dt_par, dt_ret, cpp_func_name, c_base, mask_status, lmul, isa)

                    has_ldiv = (isa.get("is_scalar", False) or any(x < 0 for x in isa.get("hw_lmul", []) + isa.get("sw_lmul", []))) and isa_provides_lmul(isa, funcs[f]["proto"], -2) and is_defined_for_dt_lmul(funcs[f]["proto"], dt, -2)
                    if has_ldiv:
                        ldiv = -2
                        _emit_mask_specs(lambda _v: file, proto, dt_par, dt_ret, cpp_func_name, c_base, mask_status, ldiv, isa)
            print(_cpp_close_namespace(), file=file)
    else:
        for f in funcs:
            for dt in funcs[f]["datatypes"]:
                is_cast = len(dt.split(',')) > 1
                is_gthr_scttr =  ("gather" in f) or ("scatter" in f)

                if not is_cast:
                    dt_par = dt.split(',')[0]
                    dt_ret = dt.split(',')[0]
                elif is_gthr_scttr:
                    dt_par = dt.split(',')[0]
                    dt_ret = dt.split(',')[1]
                else:
                    dt_par = dt.split(',')[0]
                    dt_ret = dt.split(',')[1]

                if not is_cast and not is_gthr_scttr:
                    c_func_name = build_func_name_short(isa, dt_par, f, isa_name=True, alias=True)
                    cpp_func_name = build_cpp_func_name_short(funcs[f]["proto"], dt_ret, _cpp_base_name(funcs, f))
                elif is_gthr_scttr:
                    c_func_name = build_func_name(isa, dt_par, dt_ret, f, isa_name=True, alias=True)                
                    cpp_func_name = build_cpp_func_name_short(funcs[f]["proto"], dt_ret, _cpp_base_name(funcs, f))
                else:
                    c_func_name = build_func_name(isa, dt_par, dt_ret, f, isa_name=True, alias=True)
                    cpp_func_name = build_cpp_func_name(dt_ret, f)

                for lmul in [l for l in all_lmul if isa_provides_lmul(isa, funcs[f]["proto"], l) and is_defined_for_dt_lmul(funcs[f]["proto"], dt, l)]:
                    file_u = include_manager.get_fd(layer_name, f, variant="u", lmul=lmul)
                    print(build_proto(funcs[f]["proto"], dt_par, dt_ret, isa, cpp_func_name, lmul, isa_name=True, cpp=True) + " {", file=file_u)
                    print("\t" + build_call(funcs[f]["proto"], dt_par, dt_ret, "", c_func_name + "_m" + str(lmul), lmul, False) + ";", file=file_u)
                    print("}", file=file_u)
                    _emit_imm_template(funcs, f, dt_par, dt_ret, isa, cpp_func_name, c_func_name + "_m" + str(lmul), lmul, file_u)

                has_ldiv = (isa.get("is_scalar", False) or any(x < 0 for x in isa.get("hw_lmul", []) + isa.get("sw_lmul", []))) and isa_provides_lmul(isa, funcs[f]["proto"], -2) and is_defined_for_dt_lmul(funcs[f]["proto"], dt, -2)
                if has_ldiv:
                    ldiv = -2
                    file_u = include_manager.get_fd(layer_name, f, variant="u", lmul=ldiv)
                    print(build_proto(funcs[f]["proto"], dt_par, dt_ret, isa, cpp_func_name, ldiv, isa_name=True, cpp=True) + " {", file=file_u)
                    print("\t" + build_call(funcs[f]["proto"], dt_par, dt_ret, "", c_func_name + "_d" + str(-ldiv), ldiv, False) + ";", file=file_u)
                    print("}", file=file_u)
                    _emit_imm_template(funcs, f, dt_par, dt_ret, isa, cpp_func_name, c_func_name + "_d" + str(-ldiv), ldiv, file_u)
                
                mask_status = funcs[f]["variants"]
                if mask_status and mask_status.is_any_mask():
                    proto = funcs[f]["proto"]
                    c_base = _masked_c_symbol(dt_par, dt_ret, f, is_cast, isa=isa, isa_name=True)

                    lmuls = [l for l in all_lmul if isa_provides_lmul(isa, funcs[f]["proto"], l) and is_defined_for_dt_lmul(funcs[f]["proto"], dt, l)] + ([-2] if has_ldiv else [])
                    for lmul in lmuls:
                        get_file = lambda v, _l=lmul: include_manager.get_fd(layer_name, f, variant=v, lmul=_l)
                        _emit_mask_specs(get_file, proto, dt_par, dt_ret, cpp_func_name, c_base, mask_status, lmul, isa)

        include_manager.resolve_all_dependencies(layer_name, funcs)
        include_manager.close_layer_fds(layer_name)