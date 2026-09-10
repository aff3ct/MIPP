#!/usr/bin/env python3
import sys
import os
import shutil
import struct
import argparse
import copy
import time


path = os.getcwd()

sys.path.insert(1, path + "/helpers_headers/")

from tools import all_lmul, all_ldiv, clear_memo_caches, load_isa_config
from registry import scalar_isa
from registry import scalar_implems
from registry import interfaces

from include_gen import generate_mipp_h
from ci_generator import generate_c_interface
from cpp_generator import generate_cpp
from cpp_object_generator import generate_cpp_object

from include_gen import IncludeManager

include_gen_path = "../include/"

# folder paths
simd_ext_path = os.path.join(include_gen_path, "simd_ext")
interfaces_path = os.path.join(include_gen_path, "interfaces")
templates_path = os.path.join(include_gen_path, "templates")

def create_folder(folder_path):
    if not os.path.exists(folder_path):
        os.makedirs(folder_path)

def clean_folder(folder_path):
    try:
        shutil.rmtree(folder_path)
    except Exception as e:
        print(f"Failed to delete folder: {folder_path}. Reason: {e}")

def check_mipp_funcs_scalar_implems():
    should_exit_at_the_end = False
    for f in interfaces:
        mipp_funcs_datatypes = interfaces[f]["datatypes"]
        mipp_funcs_mask_variants = ["no_mask"]
        if ("mask_support" in interfaces[f]):
            if interfaces[f]["mask_support"].is_maskable():
                mipp_funcs_mask_variants = mipp_funcs_mask_variants + ["mask"]
            if interfaces[f]["mask_support"].is_maskzable():
                mipp_funcs_mask_variants = mipp_funcs_mask_variants + ["maskz"]
            if interfaces[f]["mask_support"].is_masksable():
                mipp_funcs_mask_variants = mipp_funcs_mask_variants + ["masks"]

        if f not in scalar_implems:
            print("Panic: '" + f + "' function does not exist in 'scalar_implems'.")
            should_exit_at_the_end = True
            continue

        for mv in mipp_funcs_mask_variants:
            for dt in mipp_funcs_datatypes:
                found = False
                for ff in scalar_implems[f]:
                    if "datatypes" not in ff:
                        print("Panic: '" + f + "<" + dt + "," + mv + ">': \"datatypes\" field is missing in 'scalar_implems'.")
                        should_exit_at_the_end = True
                        continue
                    if "mask_variants" not in ff:
                        print("Panic: '" + f + "<" + dt + "," + mv + ">': \"mask_variants\" field is missing in 'scalar_implems'.")
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
                    print("Panic: '" + f + "<" + dt + "," + mv + ">' function is not defined in 'scalar_implems'.")
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

def discover_and_sort_isas(path, limit_to_isas=None):
    """
    Scans the simd_ext directory, validates the existence of mandatory configuration files
    for each extension, and returns:
      - isas_dict: dict of isa_name -> isa_config
      - implems_dict: dict of isa_name -> (native_implems, emu_implems)
      - sorted_names: list of isa_names in topological order based on sub_isa dependencies
    """
    import os
    from tools import load_isa_config
    from registry import scalar_isa, scalar_implems

    simd_ext_dir = os.path.join(path, "simd_ext")
    subdirs = [d for d in os.listdir(simd_ext_dir) if os.path.isdir(os.path.join(simd_ext_dir, d)) and d != "__pycache__"]

    # Resolve active ISAs (including dependencies)
    if limit_to_isas is not None:
        invalid_isas = [ext for ext in limit_to_isas if ext not in subdirs]
        if invalid_isas:
            raise ValueError(f"Requested invalid SIMD extension(s) that do not exist: {', '.join(invalid_isas)}")

        active_isas = set(limit_to_isas)
        active_isas.add("scalar")  # Always include fallback

        changed = True
        while changed:
            changed = False
            for ext in list(active_isas):
                if ext == "scalar":
                    continue
                ext_dir = os.path.join(simd_ext_dir, ext)
                isa_json_path = os.path.join(ext_dir, f"{ext}_isa.json")
                if os.path.exists(isa_json_path):
                    with open(isa_json_path, "r") as f:
                        import json
                        isa = json.load(f)
                    sub = isa.get("sub_isa", None)
                    if sub and sub not in active_isas:
                        active_isas.add(sub)
                        changed = True
        subdirs = [d for d in subdirs if d in active_isas]

    isas_dict = {}
    implems_dict = {}

    for ext in subdirs:
        if ext == "scalar":
            isas_dict["scalar"] = scalar_isa
            implems_dict["scalar"] = (None, scalar_implems)
            continue

        # Validation checks
        ext_dir = os.path.join(simd_ext_dir, ext)
        mandatory_files = [
            f"{ext}_isa.json",
            f"{ext}_native_implems.json",
            f"{ext}_native_templates.json"
        ]
        missing = [f for f in mandatory_files if not os.path.exists(os.path.join(ext_dir, f))]
        if missing:
            raise FileNotFoundError(f"Missing mandatory configuration files for SIMD extension '{ext}': {', '.join(missing)}")

        # Load config
        isa, native, emu = load_isa_config(ext)
        isas_dict[ext] = isa
        implems_dict[ext] = (native, emu)

    # Topological sort based on sub_isa dependencies
    sorted_names = []
    visited = set()

    def visit(name):
        if name in visited:
            return
        visited.add(name)
        # scalar is the fallback, it doesn't have dependencies
        if name != "scalar":
            sub = isas_dict[name].get("sub_isa", None)
            if sub and sub in isas_dict:
                visit(sub)
        sorted_names.append(name)

    for name in isas_dict:
        visit(name)

    for name, isa in isas_dict.items():
        sub_name = isa.get("sub_isa")
        if sub_name and sub_name in isas_dict:
            isas_dict[sub_name]["super_isa"] = isa

    return isas_dict, implems_dict, sorted_names


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
        "--simd-ext",
        nargs="+",
        help="List of SIMD extensions to generate (e.g. sse avx scalar). If not specified, all discovered extensions are generated.",
        default=None,
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
    
    parser.add_argument(
        "--audit",
        nargs="+",
        choices=["levels", "dead-code", "duplicates", "json-structure", "all", "none"],
        help="Run audits on the MIPP code database: 'levels' checks implementation level placement discrepancies, 'dead-code' checks for unreferenced templates, 'duplicates' checks for datatype implementation level overlaps, 'json-structure' checks for unsorted keys and empty lists in JSON files, 'all' (default) runs all audits, 'none' disables audits.",
        default=["all"],
    )
    
    args = parser.parse_args(argv)

    import input_validation
    input_validation.ACTIVE_AUDITS = set()
    if args.audit:
        has_none = False
        for a in args.audit:
            for item in a.split(","):
                if item.strip().lower() == "none":
                    has_none = True
        
        if not has_none:
            for a in args.audit:
                for item in a.split(","):
                    item = item.strip().lower()
                    if item == "all":
                        input_validation.ACTIVE_AUDITS.update(["levels", "dead-code", "duplicates", "json-structure"])
                    elif item in ("levels", "dead-code", "duplicates", "json-structure"):
                        input_validation.ACTIVE_AUDITS.add(item)

    input_validation.audit_json_files_structure(path)

    # Audit generic templates now that ACTIVE_AUDITS is populated
    import registry
    if registry.generic_flat_implems is not None and registry.generic_data_templates is not None:
        input_validation.audit_generic_templates_dead_code(
            registry.generic_flat_implems, registry.generic_data_templates
        )
    
    if registry.scalar_implems is not None and registry.interfaces is not None:
        input_validation.audit_scalar_implems_dead_code(
            registry.scalar_implems, registry.interfaces
        )

    if registry.categories is not None and registry.interfaces is not None:
        input_validation.validate_categories_logical_integrity(
            registry.categories, registry.interfaces
        )


    # check that all mipp funcs have a scalar implem before to start
    check_mipp_funcs_scalar_implems()

    # Clear tracking sets for separators to handle multiple runs/interactive environments cleanly
    from codegen.lmul_orchestrator import seen_lmul_separators, seen_ldiv_separators
    seen_lmul_separators.clear()
    seen_ldiv_separators.clear()

    selected = _parse_layers(args.layers)
    isa_layers, run_wrappers = _expand_layer_keywords(selected)

    # Parse limit_to_isas from --simd-ext
    limit_to_isas = None
    if args.simd_ext:
        parsed_isas = set()
        for item in args.simd_ext:
            for tok in item.split(","):
                tok = tok.strip().lower()
                if tok:
                    parsed_isas.add(tok)
        if "all" not in parsed_isas:
            limit_to_isas = parsed_isas

    # Auto-discovery, validation and sorting of SIMD extensions
    isas_dict, implems_dict, sorted_names = discover_and_sort_isas(path, limit_to_isas=limit_to_isas)

    if registry.implems_generic_emu is not None:
        emu_dicts = {
            "implems_generic_emu": registry.implems_generic_emu,
            "implems_mask_generic_emu": registry.implems_mask_generic_emu,
            "implems_horiz_lmul_generic_emu": registry.implems_horiz_lmul_generic_emu,
        }
        input_validation.audit_generic_emu_dead_code(emu_dicts, isas_dict, implems_dict)

    print("=" * 85)
    print(" MIPP Header Generator")
    print("=" * 85)
    print(f"  LMUL options: {all_lmul} | LDIV options: {all_ldiv}")
    print("-" * 85)

    # clean all (optional)
    if not args.no_clean:
        print("  ➔ Cleaning old generated files...", end="", flush=True)
        t0 = time.perf_counter()
        clean_folder(include_gen_path)
        print(f" Done (elapsed time: {time.perf_counter() - t0:.3f} sec)!")

    # create folders (always ensure these exist)
    for folder in [simd_ext_path, interfaces_path, templates_path]:
        create_folder(folder)


    # CREATE INCLUDE MANAGER
    include_manager = IncludeManager(sorted_names, mode=args.header_type)

    # ISA generators
    from c_generator import generate_c_layer
    for name in sorted_names:
        if name in isa_layers:
            clear_memo_caches()
            display_name = name.upper() if name != 'avx512' else 'AVX-512'
            display_name = display_name if name != 'scalar' else 'Scalar'
            display_name = display_name if name != 'rvv' else 'RVV1.0'
            print(f"  ➔ Generating {display_name}...", end="", flush=True)
            t0 = time.perf_counter()
            if name == "scalar":
                # import scalar_gen dynamically
                import importlib
                scalar_path = os.path.join(path, "simd_ext", "scalar")
                if scalar_path not in sys.path:
                    sys.path.insert(1, scalar_path)
                scalar_gen_module = importlib.import_module("scalar_gen")
                scalar_gen = getattr(scalar_gen_module, "scalar_gen")
                scalar_gen(include_manager)
            else:
                native, emu = implems_dict[name]
                generate_c_layer(isas_dict[name], include_manager, native, emu)
            print(f" Done (elapsed time: {time.perf_counter() - t0:.3f} sec)!")

    # Wrappers / top-level headers
    if run_wrappers:
        print("  ➔ Generating wrappers & C/C++ interface...", end="", flush=True)
        t0 = time.perf_counter()
        generate_mipp_h(include_manager)
        isa_list = [isas_dict[name] for name in sorted_names]
        generate_c_interface(isa_list, include_manager)
        generate_cpp(include_manager, isa_list)
        generate_cpp_object(include_manager)
        print(f" Done (elapsed time: {time.perf_counter() - t0:.3f} sec)!")

    # Print summary table at the end
    print_summary_table(include_gen_path, sorted_names)

def print_summary_table(include_dir, sorted_names=None):
    import os
    import glob
    import re

    def classify_func_name(func_name):
        m = re.search(r'_(m|d)(\d+)', func_name)
        if m and int(m.group(2)) != 1:
            return "LM/D"
        if func_name.endswith(("_mask", "_maskz", "_masks")):
            return "Msk"
        return "Std"

    # Dynamic ISA detection: use sorted_names if provided, otherwise scan the filesystem
    if sorted_names is not None:
        candidate_isas = sorted_names
    else:
        simd_ext_dir = os.path.join(include_dir, "simd_ext")
        if not os.path.isdir(simd_ext_dir):
            return
        candidate_isas = sorted(os.listdir(simd_ext_dir))

    # Keep only ISAs that actually have generated C function headers
    existing_isas = []
    for isa in candidate_isas:
        isa_dir = os.path.join(include_dir, "simd_ext", isa, "c", "functions")
        if os.path.isdir(isa_dir):
            existing_isas.append(isa)

    if not existing_isas:
        return

    # Print Table Header
    print("\n" + "="*167)
    print(" MIPP IMPLEMENTATION LEVEL SUMMARY")
    print("="*167)
    
    # Header row 1: Levels
    h1 = f"{'Extension':<12} | {'Level 0 (Nat)':^33} | {'Level 1 (SpE)':^33} | {'Level 2 (GeE)':^33} | {'Level 3 (Sca)':^33} | {'Stubs':>8}"
    print(h1)
    
    # Header row 2: Sub-columns
    sub_cols = f"{'Std':^5} {'Msk':^5} {'LM/D':^6} | {'Total':^12}"
    h2 = f"{'':<12} | {sub_cols} | {sub_cols} | {sub_cols} | {sub_cols} | {'':>8}"
    print(h2)
    print("-" * 167)

    for isa in existing_isas:
        stats = {
            0: {"Std": 0, "Msk": 0, "LM/D": 0},
            1: {"Std": 0, "Msk": 0, "LM/D": 0},
            2: {"Std": 0, "Msk": 0, "LM/D": 0},
            3: {"Std": 0, "Msk": 0, "LM/D": 0},
            "stub": 0
        }
        
        isa_dir = os.path.join(include_dir, "simd_ext", isa, "c", "functions")
        files = glob.glob(os.path.join(isa_dir, "**", "*.h"), recursive=True)
            
        # Read all files and extract function levels and categories
        for filepath in files:
            try:
                with open(filepath, "r", encoding="utf-8", errors="ignore") as f:
                    current_func = None
                    for line in f:
                        if line.startswith("static ") or line.startswith("inline ") or (" static " in line) or (" inline " in line):
                            m = re.search(r'(mipp_\w+)\s*\(', line)
                            if m:
                                current_func = m.group(1)
                        
                        if "Level 0" in line:
                            if current_func:
                                stats[0][classify_func_name(current_func)] += 1
                        elif "Level 1" in line:
                            if current_func:
                                stats[1][classify_func_name(current_func)] += 1
                        elif "Level 2" in line:
                            if current_func:
                                stats[2][classify_func_name(current_func)] += 1
                        elif "Level 3" in line:
                            if current_func:
                                stats[3][classify_func_name(current_func)] += 1
                        elif "MIPP panic" in line:
                            stats["stub"] += 1
            except Exception:
                pass
                
        # Calculate totals for each category to compute percentages
        totals = {
            "Std": sum(stats[lvl]["Std"] for lvl in [0, 1, 2, 3]),
            "Msk": sum(stats[lvl]["Msk"] for lvl in [0, 1, 2, 3]),
            "LM/D": sum(stats[lvl]["LM/D"] for lvl in [0, 1, 2, 3])
        }
        
        def fmt_tot_cell(val, total):
            if total == 0:
                pct_str = "(0%)"
            else:
                pct = (val / total) * 100
                pct_str = f"({pct:.0f}%)"
            return f"{val:>5} {pct_str:>6}"

        def fmt_level(level, isa_name):
            if isa_name == "scalar" and level > 0:
                return f"{'N/A':>5} {'N/A':>5} {'N/A':>6} | {'N/A':>12}"

            std_val = stats[level]["Std"]
            msk_val = stats[level]["Msk"]
            lmd_val = stats[level]["LM/D"]
            tot_val = std_val + msk_val + lmd_val
            
            total_all = totals["Std"] + totals["Msk"] + totals["LM/D"]
            
            return f"{std_val:>5} {msk_val:>5} {lmd_val:>6} | {fmt_tot_cell(tot_val, total_all)}"

        stub_print = "N/A" if isa == "scalar" else str(stats["stub"])
        print(f"{isa:<12} | {fmt_level(0, isa)} | {fmt_level(1, isa)} | {fmt_level(2, isa)} | {fmt_level(3, isa)} | {stub_print:>8}")
    print("="*167 + "\n")

if __name__ == "__main__":
    main()
