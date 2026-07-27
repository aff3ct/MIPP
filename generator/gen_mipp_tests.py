#!/usr/bin/env python3
"""
MIPP Test Suite Generator.
Delegates test generation to TestBuilderEngine using declarative JSON configurations.
"""

import os
import sys
import argparse
import shutil
from pathlib import Path

path = os.getcwd()
sys.path.insert(1, path + "/helpers_headers/")

simd_ext_dir = os.path.join(path, "simd_ext")
if os.path.exists(simd_ext_dir):
    for entry in sorted(os.listdir(simd_ext_dir)):
        isa_path = os.path.join(simd_ext_dir, entry)
        if os.path.isdir(isa_path):
            sys.path.insert(1, isa_path)

from registry import interfaces, categories
from helpers_tests import TestBuilderEngine

engine = None

tmp_path = "../tests/src/"
cpath = tmp_path + "c_tests/"
cpppath = tmp_path + "cpp_tests/"
objpath = tmp_path + "obj_tests/"


def _match_category(func: str) -> str:
    for category in categories:
        if func in categories[category]:
            if category == "a_trier":
                return "miscellaneous"
            return category
    return "miscellaneous"


def clean_folder(folder_path: str) -> None:
    if os.path.exists(folder_path):
        for root, dirs, files in os.walk(folder_path):
            for file in files:
                os.remove(os.path.join(root, file))
            for dir in dirs:
                shutil.rmtree(os.path.join(root, dir))
        shutil.rmtree(folder_path)


def comment_out_cpp_file(file_content: str, reason: str = "") -> str:
    lines = file_content.splitlines()
    commented_lines = []
    if reason:
        commented_lines.append(f"// SKIPPED: {reason}")
    for line in lines:
        commented_lines.append(f"// {line}" if line.strip() else "//")
    return "\n".join(commented_lines) + "\n"


def get_str_path(base_path: str, lmul: int = 0, mkind: str = "") -> tuple[str, str, str]:
    return (
        f"{base_path}c_tests/",
        f"{base_path}cpp_tests/",
        f"{base_path}obj_tests/",
    )


def write_file_if_different(file_path: str, content: str, encoding: str = "utf-8") -> bool:
    p = Path(file_path)
    new_bytes = content.encode(encoding)
    try:
        if p.read_bytes() == new_bytes:
            return False
    except FileNotFoundError:
        pass

    p.parent.mkdir(parents=True, exist_ok=True)
    p.write_bytes(new_bytes)
    return True


def gen_test_files_unified_layer(kind: str = "cpp", N: int = 10, stats: dict = None) -> None:
    if stats is None:
        stats = {"generated": 0, "skipped_mask": [], "skipped_disabled": [], "skipped_obj": []}

    funcs = set(interfaces.keys())
    base_dir = f"{tmp_path}{kind}_tests/"

    for func in sorted(funcs):
        disabled, reason = engine.is_func_disabled(func, kind)
        if disabled:
            func_spec = engine.specs["functions"].get(func, {})
            if func_spec.get("disabled"):
                stats["skipped_disabled"].append(func)
            elif kind == "obj":
                stats["skipped_obj"].append(func)
            if reason is None:
                reason = f"{func} disabled in tests_specs.json"

        cat = _match_category(func)
        content = engine.build_test_file_content(kind, func, N=N)

        if disabled:
            content = comment_out_cpp_file(content, reason)

        fname_prefix = "test_" if kind == "cpp" else "test_obj_"
        file_path = f"{base_dir}{cat}/{fname_prefix}{func}.cpp"
        write_file_if_different(file_path, content)
        stats["generated"] += 1


def gen_test_files_all_funcs(kind: str = "c", lmul: int = 0, mkind: str = "", N: int = 10, mode: str = "function", stats: dict = None) -> None:
    if stats is None:
        stats = {"generated": 0, "skipped_mask": [], "skipped_disabled": [], "skipped_obj": []}

    regen_c = kind == "c"

    funcs = set(interfaces.keys())
    cpath_root, cpppath_root, objpath_root = get_str_path(tmp_path, lmul=lmul, mkind=mkind)

    lmul_tag = f"m{lmul}" if lmul >= 0 else f"d{-lmul}"
    mask_tag = mkind if mkind != "" else "unmasked"

    for func in sorted(funcs):
        mask_support = interfaces[func]["mask_support"]
        if mkind != "" and not mask_support.is_supported(mkind):
            stats["skipped_mask"].append((mkind, func))
            continue

        disabled, reason = engine.is_func_disabled(func, kind)
        if disabled:
            func_spec = engine.specs["functions"].get(func, {})
            if func_spec.get("disabled"):
                stats["skipped_disabled"].append(func)
            if reason is None:
                reason = f"{func} disabled in tests_specs.json"

        lmul_suffix = f"m{lmul}" if lmul >= 0 else f"d{-lmul}"
        cat = _match_category(func)

        if regen_c:
            c_file = engine.build_test_file_content("c", func, lmul_suffix, mkind=mkind, lmul=lmul)
            if disabled:
                c_file = comment_out_cpp_file(c_file, reason)
            file_path = f"{cpath_root}{cat}/{lmul_tag}/{mask_tag}/test_c{func}.cpp"
            write_file_if_different(file_path, c_file)
            stats["generated"] += 1


def main():
    parser = argparse.ArgumentParser(description="Generate MIPP test files.")
    parser.add_argument(
        "kind",
        nargs="?",
        default=["c", "cpp", "obj"],
        choices=["c", "cpp", "obj"],
        help="Which layer to regenerate (default: all).",
    )
    parser.add_argument(
        "-N", "--num-iterations",
        type=int,
        default=10,
        help="Number of iterations for random tests (default: 10).",
    )
    parser.add_argument(
        "--no-clean",
        action="store_true",
        help="Do not clean the test folders before generating new files.",
    )
    parser.add_argument(
        "--lmul",
        type=int,
        nargs="+",
        choices=[0, 1, 2, 4, 8],
        default=[0, 1, 2, 4, 8],
        help="Generate tests for the specified LMUL values.",
    )
    parser.add_argument(
        "--ldiv",
        type=int,
        nargs="+",
        choices=[2],
        default=[2],
        help="Generate tests for the specified LDIV values.",
    )
    parser.add_argument(
        "--mask-kind",
        type=str,
        nargs="+",
        choices=["unmasked", "mask", "maskz", "masks"],
        default=["unmasked", "mask", "maskz", "masks"],
        help="Generate tests for the specified mask kinds.",
    )
    parser.add_argument(
        "--skip-lmul-cpp",
        action="store_true",
        help="Deprecated option kept for backward compatibility.",
    )
    parser.add_argument(
        "--skip-mask-cpp",
        action="store_true",
        help="Deprecated option kept for backward compatibility.",
    )
    parser.add_argument(
        "--header-type",
        choices=["function", "full"],
        default="function",
        help="Generate test using individual header inclusion or global header inclusion.",
    )
    parser.add_argument(
        "--audit",
        nargs="+",
        choices=["coverage", "redundancy", "consistency", "all", "none"],
        default=["all"],
        help="Run audits on tests_specs.json: 'coverage' checks for missing/extra functions, 'redundancy' checks for redundant default property overrides, 'consistency' checks for domain/tolerance integrity, 'all' (default) runs all audits, 'none' disables audits.",
    )

    args = parser.parse_args()

    active_audits = set()
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
                        active_audits.update(["coverage", "redundancy", "consistency"])
                    elif item in ("coverage", "redundancy", "consistency"):
                        active_audits.add(item)

    print("=====================================================================================================")
    print(" MIPP Tests Audits")
    print("=====================================================================================================")

    global engine
    engine = TestBuilderEngine(base_dir="..", active_audits=active_audits)

    if isinstance(args.kind, str):
        args.kind = [args.kind]
    if "unmasked" in args.mask_kind:
        args.mask_kind = [k if k != "unmasked" else "" for k in args.mask_kind]

    print("=====================================================================================================")
    print(" MIPP Tests Generator")
    print("=====================================================================================================")

    if not args.no_clean:
        print("  ➔ Cleaning old test folders...", end="", flush=True)
        import time
        t0 = time.perf_counter()
        if "c" in args.kind:
            clean_folder(cpath)
        if "cpp" in args.kind:
            clean_folder(cpppath)
        if "obj" in args.kind:
            clean_folder(objpath)
        print(f"\n    Done (elapsed time: {time.perf_counter() - t0:.3f} sec)!")

    stats = {
        "generated": 0,
        "skipped_mask": [],
        "skipped_disabled": [],
        "skipped_obj": []
    }

    import time
    for kind in args.kind:
        if kind == "c":
            valid_lmuls = [l for l in args.lmul]
            valid_ldivs = [l for l in args.ldiv]
            valid_masks = [m for m in args.mask_kind]
            mask_strs = [m if m != "" else "unmasked" for m in valid_masks]
            mask_str_formatted = "{" + ", ".join(mask_strs) + "}"
            if valid_lmuls:
                lmul_str = "{" + ", ".join(map(str, valid_lmuls)) + "}"
                print(f"  ➔ Generating C tests [LMUL={lmul_str}, mask={mask_str_formatted}]...", end="", flush=True)
                t0_step = time.perf_counter()
                for lmul in valid_lmuls:
                    for mkind in valid_masks:
                        gen_test_files_all_funcs(kind="c", lmul=lmul, mkind=mkind, N=args.num_iterations, mode=args.header_type, stats=stats)
                print(f" Done ({time.perf_counter() - t0_step:.3f} s)!")
            if valid_ldivs:
                ldiv_str = "{" + ", ".join(map(str, valid_ldivs)) + "}"
                print(f"  ➔ Generating C tests [LDIV={ldiv_str}, mask={mask_str_formatted}]...", end="", flush=True)
                t0_step = time.perf_counter()
                for ldiv in valid_ldivs:
                    for mkind in valid_masks:
                        gen_test_files_all_funcs(kind="c", lmul=(-int(ldiv)), mkind=mkind, N=args.num_iterations, mode=args.header_type, stats=stats)
                print(f" Done ({time.perf_counter() - t0_step:.3f} s)!")
        else:
            print(f"  ➔ Generating unified {kind.upper()} tests (templates [U, M, Z, S], LMUL, datatypes)...", end="", flush=True)
            t0_step = time.perf_counter()
            gen_test_files_unified_layer(kind=kind, N=args.num_iterations, stats=stats)
            print(f" Done ({time.perf_counter() - t0_step:.3f} s)!")

    print("\n=====================================================================================================")
    print(" MIPP Tests Generation Summary")
    print("=====================================================================================================")
    print(f"  Total tests generated: {stats['generated']}")

    unique_skipped_disabled = sorted(list(set(stats.get("skipped_disabled", []))))
    if unique_skipped_disabled:
        print(f"  Skipped (disabled in tests_specs.json): {len(unique_skipped_disabled)} functions")
        print(f"    [{', '.join(unique_skipped_disabled)}]")

    unique_skipped_obj = sorted(list(set(stats.get("skipped_obj", []))))
    if unique_skipped_obj:
        print(f"  Skipped (unsupported by Object layer): {len(unique_skipped_obj)} functions")
        print(f"    [{', '.join(unique_skipped_obj)}]")

    print("=====================================================================================================")

if __name__ == "__main__":
    main()