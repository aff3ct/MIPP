#!/usr/bin/env python3
import sys
import os
import shutil
import struct
import argparse
import copy


path = os.getcwd()

sys.path.insert(1, path + "/helpers_headers/")
sys.path.insert(1, path + "/simd_ext/avx512/")
sys.path.insert(1, path + "/simd_ext/avx/")
sys.path.insert(1, path + "/simd_ext/sse/")
sys.path.insert(1, path + "/simd_ext/sve/")
sys.path.insert(1, path + "/simd_ext/rvv/")
sys.path.insert(1, path + "/simd_ext/neon/")
sys.path.insert(1, path + "/simd_ext/scalar/")

from implem_sse import isa_sse
from implem_avx import isa_avx
from implem_avx512 import isa_avx512
from implem_sve import isa_sve
from implem_rvv import isa_rvv
from implem_neon import isa_neon
from headers_def import isa_scalar
from headers_def import implems_scalar
from headers_def import mipp_funcs

from gen_mipp_sse import gen_mipp_sse
from gen_mipp_avx import gen_mipp_avx
from gen_mipp_avx512 import gen_mipp_avx512
from gen_mipp_sve import gen_mipp_sve
from gen_mipp_rvv import gen_mipp_rvv
from gen_mipp_neon import gen_mipp_neon
from gen_mipp_scalar import gen_mipp_scalar

from mipp_h import generate_mipp_h
from ci_generator import generate_c_interface
from cpp_generator import generate_cpp
from cpp_object_generator import generate_cpp_object

from include_gen import IncludeManager


from tools import all_lmul, all_ldiv

include_gen_path = "../include/"

# avx and avx512 folder path
sse_path = os.path.join(include_gen_path, "sse")
avx_path = os.path.join(include_gen_path, "avx")
avx512_path = os.path.join(include_gen_path, "avx512")
sve_path = os.path.join(include_gen_path, "sve")
rvv_path = os.path.join(include_gen_path, "rvv")
neon_path = os.path.join(include_gen_path, "neon")
c_path = os.path.join(include_gen_path, "c")
cpp_path = os.path.join(include_gen_path, "cpp")
obj_path = os.path.join(include_gen_path, "obj")
scalar_path = os.path.join(include_gen_path, "scalar")

def create_folder(folder_path):
    if not os.path.exists(folder_path):
        os.makedirs(folder_path)
        print(folder_path + " folder successfully created")
    else:
        print("The " + folder_path + " folder already exists.")

def clean_folder(folder_path):
    try:
        shutil.rmtree(folder_path)
        print(f"Successfully deleted folder: {folder_path}")
    except Exception as e:
        print(f"Failed to delete folder: {folder_path}. Reason: {e}")

def check_mipp_funcs_scalar_implems():
    should_exit_at_the_end = False
    for f in mipp_funcs:
        mipp_funcs_datatypes = mipp_funcs[f]["datatypes"]
        mipp_funcs_mask_variants = ["no_mask"]
        if ("mask_support" in mipp_funcs[f]):
            if mipp_funcs[f]["mask_support"].is_maskable():
                mipp_funcs_mask_variants = mipp_funcs_mask_variants + ["mask"]
            if mipp_funcs[f]["mask_support"].is_maskzable():
                mipp_funcs_mask_variants = mipp_funcs_mask_variants + ["maskz"]
            if mipp_funcs[f]["mask_support"].is_masksable():
                mipp_funcs_mask_variants = mipp_funcs_mask_variants + ["masks"]

        if f not in implems_scalar:
            print("Panic: '" + f + "' function does not exist in 'implems_scalar'.")
            should_exit_at_the_end = True
            continue

        for mv in mipp_funcs_mask_variants:
            for dt in mipp_funcs_datatypes:
                found = False
                for ff in implems_scalar[f]:
                    if "datatypes" not in ff:
                        print("Panic: '" + f + "<" + dt + "," + mv + ">': \"datatypes\" field is missing in 'implems_scalar'.")
                        should_exit_at_the_end = True
                        continue
                    if "mask_variants" not in ff:
                        print("Panic: '" + f + "<" + dt + "," + mv + ">': \"mask_variants\" field is missing in 'implems_scalar'.")
                        should_exit_at_the_end = True
                        continue
                    if not ff["datatypes"] and not ff["mask_variants"]:
                        found = True
                        break
                    if dt in ff["datatypes"] and not ff["mask_variants"]:
                        found = True
                        break
                    if mv in ff["mask_variants"] and not ff["datatypes"]:
                        found = True
                        break
                    if dt in ff["datatypes"] and mv in ff["mask_variants"]:
                        found = True
                        break
                if not found:
                    print("Panic: '" + f + "<" + dt + "," + mv + ">' function is not defined in 'implems_scalar'.")
                    should_exit_at_the_end = True
                    continue

    if should_exit_at_the_end:
        sys.exit(-1)

def _parse_layers(layers_raw):
    """
    layers_raw: list[str] coming from argparse.
    Returns a set of normalized layer tokens.
    """
    if not layers_raw:
        return {"all"}

    normalized = set()
    for item in layers_raw:
        # allow comma-separated too: --layers sse,avx
        for tok in item.split(","):
            tok = tok.strip().lower()
            if tok:
                normalized.add(tok)
    return normalized

def _expand_layer_keywords(selected):
    """
    Expand convenience keywords into concrete actions.
    Returns: (isa_layers_to_run, run_wrappers: bool)
      - isa_layers_to_run is a set among: sse,avx,avx512,sve,rvv,neon,scalar
      - run_wrappers means run generate_mipp_h + generate_c_interface + generate_cpp + generate_cpp_object
    """
    isa_all = {"sse", "avx", "avx512", "sve", "rvv", "neon", "scalar"}

    # default == all
    if "all" in selected:
        return (set(isa_all), True)

    isa_layers = set()
    run_wrappers = False

    if "all_isas" in selected:
        isa_layers |= isa_all

    if "wrappers" in selected:
        run_wrappers = True

    # direct ISA tokens
    for tok in selected:
        if tok in isa_all:
            isa_layers.add(tok)

    # If user selected only ISA(s) and no explicit wrapper keyword, we keep wrappers off.
    # If you'd rather always regenerate wrappers whenever any ISA is regenerated,
    # uncomment the next line:
    # run_wrappers = run_wrappers or bool(isa_layers)

    unknown = selected - (isa_all | {"all", "all_isas", "wrappers"})
    if unknown:
        raise ValueError(f"Unknown layer keyword(s): {', '.join(sorted(unknown))}")

    return (isa_layers, run_wrappers)

def main(argv=None):
    parser = argparse.ArgumentParser(prog='gen_mipp.py', description='MIPP generator')
    parser.add_argument(
        "-l", "--layers",
        nargs="+",
        help=(
            "Which layer(s) to regenerate. "
            "Values: sse avx avx512 sve rvv neon scalar wrappers all_isas all. "
            "Default: all. You can also pass comma-separated lists (e.g. --layers sse,avx)."
        ),
        default=None,
    )
    parser.add_argument(
        "--no-clean",
        action="store_true",
        help="Do not delete ../include/ before generating (useful when regenerating only one layer).",
    )

    parser.add_argument(
        "--skip-sve",
        action="store_true",
        help="Skip generating SVE implementations. This is a hotfix to pass CI.",
    )

    parser.add_argument(
        "--header-type",
        choices=["function_header", "category_header"],
        default="function_header",
        nargs="?",
        help=(
            "Type of header to generate. Affects how the IncludeManager resolves dependencies and organizes files. "
            "Choices: function_header (default) generates one header per function, organized in folders by ISA. "
            "category_header generates one header per ISA category (e.g. all float64 functions in one header), organized in folders by ISA."
        ),
    )
    
    args = parser.parse_args(argv)

    # check that all mipp funcs have a scalar implem before to start
    check_mipp_funcs_scalar_implems()

    # Clear tracking sets for separators to handle multiple runs/interactive environments cleanly
    from c_generator import seen_lmul_separators, seen_ldiv_separators
    seen_lmul_separators.clear()
    seen_ldiv_separators.clear()

    selected = _parse_layers(args.layers)
    isa_layers, run_wrappers = _expand_layer_keywords(selected)

    # clean all (optional)
    if not args.no_clean:
        clean_folder(include_gen_path)

    # create folders (always ensure these exist)
    create_folder(sse_path)
    create_folder(avx_path)
    create_folder(avx512_path)
    create_folder(sve_path)
    create_folder(rvv_path)
    create_folder(neon_path)
    create_folder(scalar_path)

    # wrappers/layers folders
    create_folder(c_path)
    create_folder(cpp_path)
    create_folder(obj_path)

    all_isas_str = ["avx512", "avx", "sse", "rvv", "neon", "scalar"]
    if not args.skip_sve:
        all_isas_str.append("sve")

    # CREATE INCLUDE MANAGER

    include_manager = IncludeManager(all_isas_str, mode=args.header_type)

    # ISA generators
    if "sse" in isa_layers:
        gen_mipp_sse(include_manager)
    if "avx" in isa_layers:
        gen_mipp_avx(include_manager)
    if "avx512" in isa_layers:
        gen_mipp_avx512(include_manager)
    if "sve" in isa_layers and not args.skip_sve:
        gen_mipp_sve(include_manager)
    if "rvv" in isa_layers:
        gen_mipp_rvv(include_manager)
    if "neon" in isa_layers:
        gen_mipp_neon(include_manager)
    if "scalar" in isa_layers:
        gen_mipp_scalar(include_manager)

    # Wrappers / top-level headers
    if run_wrappers and not args.skip_sve:
        generate_mipp_h(include_manager)
        generate_c_interface([isa_sse, isa_avx, isa_avx512, isa_sve, isa_rvv, isa_neon, isa_scalar], include_manager)
        generate_cpp(include_manager, [isa_sse, isa_avx, isa_avx512, isa_sve, isa_rvv, isa_neon, isa_scalar])
        generate_cpp_object(include_manager)
    elif run_wrappers and args.skip_sve:
        generate_mipp_h(include_manager)
        generate_c_interface([isa_sse, isa_avx, isa_avx512, isa_rvv, isa_neon, isa_scalar], include_manager)
        generate_cpp(include_manager, [isa_sse, isa_avx, isa_avx512, isa_rvv, isa_neon, isa_scalar])
        generate_cpp_object(include_manager)

    print("Generating MIPP code for sse, avx2, avx512, rvv and sve with size in " + str(isa_sve["size"]))
    print("With lmul in " + str(all_lmul) + " and ldiv in " + str(all_ldiv))
    
if __name__ == "__main__":
    #parser = argparse.ArgumentParser(prog='gen_mipp.py', description='MIPP generator')
    main()
