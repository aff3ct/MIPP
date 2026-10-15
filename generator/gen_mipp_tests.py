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
from helpers_tests import TestsBuilderEngine

engine = None

tmp_path = "../tests/src/"
cpath = tmp_path + "c/"
cpppath = tmp_path + "cpp/"
objpath = tmp_path + "obj/"


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
        f"{base_path}c/",
        f"{base_path}cpp/",
        f"{base_path}obj/",
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


def gen_test_files_unified_cpp(
    kind: str = "cpp",
    N: int = 10,
    stats: dict = None,
    lmul_list: list = None,
    ldiv_list: list = None,
    mask_list: list = None,
) -> None:
    if stats is None:
        stats = {"generated": 0, "skipped_mask": [], "skipped_disabled": [], "skipped_obj": []}

    base_dir = cpppath if kind == "cpp" else objpath
    funcs = set(interfaces.keys())

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
        content = engine.build_test_file_content(
            kind, func, N=N, lmul_list=lmul_list, ldiv_list=ldiv_list, mask_list=mask_list
        )

        if disabled:
            content = comment_out_cpp_file(content, reason)

        file_path = f"{base_dir}{cat}/{func}.cpp"
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
            file_path = f"{cpath_root}{cat}/{lmul_tag}/{mask_tag}/{func}.cpp"
            write_file_if_different(file_path, c_file)
            stats["generated"] += 1


def build_arg_parser():
    """Command-line parser of gen_mipp_tests.py (also rendered in the CLI reference by gen_mipp_docs.py)."""
    from helpers_docs.cli import MippHelpFormatter, set_examples
    parser = argparse.ArgumentParser(
        prog="gen_mipp_tests.py",
        formatter_class=MippHelpFormatter,
        description=(
            "Generate the Catch2 unit tests of MIPP in '../tests/src/' from 'registry_interfaces.json', "
            "'helpers_tests/tests_specs.json' and 'helpers_tests/tests_templates.json'.\n\n"
            "Each test fills its inputs with random values, calls the function under test and compares "
            "every lane with the scalar reference (Level 3). The C API gets one file per function, LMUL "
            "and mask variant ('tests/src/c/<category>/<m1|d2|...>/<variant>/<function>.cpp'), the C++ "
            "Functional and Object APIs one file per function ('tests/src/<cpp|obj>/<category>/<function>.cpp') "
            "that covers every datatype, LMUL and mask variant."
        ),
    )
    parser.add_argument(
        "kind",
        nargs="?",
        default=["c", "cpp", "obj"],
        choices=["c", "cpp", "obj"],
        metavar="API",
        help="API to generate the tests for: C, C++ Functional or C++ Object. Without it, the three APIs.",
    )
    parser.add_argument(
        "-N", "--num-iterations",
        type=int,
        default=10,
        help="Number of random iterations of each test (the 'N_ITER' environment variable overrides it at run time).",
    )
    parser.add_argument(
        "--no-clean",
        action="store_true",
        help="Do not delete the test sources of the selected APIs before generating.",
    )
    parser.add_argument(
        "--lmul",
        type=int,
        nargs="*",
        metavar="LMUL",
        choices=[0, 1, 2, 4, 8],
        default=[0, 1, 2, 4, 8],
        help="LMUL values to test. '0' and '1' both stand for the base registers (LMUL 1).",
    )
    parser.add_argument(
        "--ldiv",
        type=int,
        nargs="+",
        metavar="LDIV",
        choices=[2],
        default=[2],
        help="LDIV values to test: '2' tests the half-vectors (d2).",
    )
    parser.add_argument(
        "--no-ldiv",
        action="store_true",
        help="Do not test the half-vectors (same as an empty --ldiv).",
    )
    parser.add_argument(
        "--mask-kind",
        type=str,
        nargs="+",
        metavar="KIND",
        choices=["unmasked", "mask", "maskz", "masks"],
        default=["unmasked", "mask", "maskz", "masks"],
        help=(
            "Variants to test: 'unmasked', 'mask' (Merge-Masked), 'maskz' (Zero-Masked) and 'masks' "
            "(Source-Masked). A function is only tested for the variants of its 'mask_support'."
        ),
    )
    parser.add_argument(
        "--skip-lmul-cpp",
        action="store_true",
        help="Deprecated, no effect. Kept for backward compatibility.",
    )
    parser.add_argument(
        "--skip-mask-cpp",
        action="store_true",
        help="Deprecated, no effect. Kept for backward compatibility.",
    )
    parser.add_argument(
        "--header-type",
        choices=["function", "full"],
        default="function",
        help="Headers included by the tests: the header of the tested function ('function') or the global header ('full').",
    )
    parser.add_argument(
        "--audit",
        nargs="+",
        metavar="AUDIT",
        choices=["consistency", "all", "none"],
        default=["all"],
        help=(
            "Audits of 'tests_specs.json'. They print warnings and never stop the generation. "
            "'consistency': entries of 'tests_specs.json' that are not declared functions."
        ),
    )
    set_examples(parser, [
        ("./gen_mipp_tests.py", "the three APIs, every LMUL and variant"),
        ("./gen_mipp_tests.py obj --lmul 0 8 --ldiv 2", "C++ Object tests, as in the CI"),
        ("./gen_mipp_tests.py c --lmul 1 --no-ldiv --mask-kind unmasked", "smallest C test set"),
    ])
    return parser


def main():
    args = build_arg_parser().parse_args()

    if args.no_ldiv:
        args.ldiv = []

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
                        active_audits.update(["consistency"])
                    elif item == "consistency":
                        active_audits.add(item)

    print("=====================================================================================================")
    print(" MIPP Tests Audits")
    print("=====================================================================================================")

    global engine
    engine = TestsBuilderEngine(base_dir="..", active_audits=active_audits)

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
            valid_masks = [m for m in args.mask_kind]
            mask_strs = [m if m != "" else "unmasked" for m in valid_masks]
            mask_str_formatted = "{" + ", ".join(mask_strs) + "}"

            target_lmuls = []
            for l in args.lmul:
                val = 1 if l in (0, 1) else l
                if val not in target_lmuls:
                    target_lmuls.append(val)
            if args.ldiv and 2 in args.ldiv:
                target_lmuls.append(-2)
            lmul_str = "{" + ", ".join(map(str, target_lmuls)) + "}"

            print(f"  ➔ Generating unified {kind.upper()} tests [LMUL={lmul_str}, mask={mask_str_formatted}]...", end="", flush=True)
            t0_step = time.perf_counter()
            gen_test_files_unified_cpp(
                kind=kind,
                N=args.num_iterations,
                stats=stats,
                lmul_list=args.lmul,
                ldiv_list=args.ldiv,
                mask_list=args.mask_kind,
            )
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