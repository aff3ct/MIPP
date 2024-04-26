#!/usr/bin/env python3

from jinja2 import Environment, FileSystemLoader
from pathlib import Path
import sys

if sys.version_info[0] != 3 or sys.version_info[1] < 5:
    print("This script requires Python version 3.5")
    sys.exit(1)

env = Environment(loader = FileSystemLoader("codegen"))
template_lut = env.get_template("vcompress-LUT.cpp.j2")
template_file = env.get_template("mipp_LUT.cpp.j2")

def generate_lut(entries, simdwidth, words_per_simd):
    lut = [[0 for j in range(0, simdwidth)] for i in range(0, entries)]

    elem_bytes = simdwidth // words_per_simd

    for i in range(0, entries):
        mask = i
        j = 0

        for k in range(0, words_per_simd):
            for b in range(0, elem_bytes):
                lut[i][j + b] = k * elem_bytes + b

            if mask & 1 == 1:
                j += elem_bytes
            mask >>= 1

        for k in range(j, simdwidth):
            lut[i][k] = -1

    return lut

def write_all_luts(filename, all_luts):
    all_content = template_file.render(
        luts = all_luts,
    )

    with open(filename, "w+") as file:
        file.write(all_content)

def generate_luts(filename, simdname, simdwidth, entrydef, lut_params_list):
    (entrytype, entrybytes) = entrydef

    all_luts = []
    for entries, simd_words in lut_params_list:

        elem_bits = (simdwidth // simd_words) * entrybytes * 8

        lut = template_lut.render(
            lutname = f"vcompress_LUT{elem_bits}x{simd_words}_{simdname}",
            entries = entries,
            simdwidth = simdwidth,
            entrytype = entrytype,
            lut = generate_lut(entries, simdwidth, simd_words)
        )

        all_luts += [lut]

    write_all_luts(filename, all_luts)

def generate_AVX_luts(filename):
    lut_AVX_32x8 = template_lut.render(
        lutname = f"vcompress_LUT32x8_AVX",
        entries = 256,
        simdwidth = 8,
        entrytype = "int32_t",
        lut = generate_lut(256, 8, 8)
    )

    lut_AVX_64x4 = template_lut.render(
        lutname = "vcompress_LUT64x4_AVX",
        entries = 16,
        simdwidth = 8,
        entrytype = "int32_t",
        lut = generate_lut(16, 8, 4)
    )

    all_luts = [lut_AVX_32x8, lut_AVX_64x4]

    write_all_luts(filename, all_luts)
    pass

Path("src/gen").mkdir(parents=True, exist_ok=True)

generate_luts("src/gen/compress_LUT_SSE.cpp",  "SSE",  16, ("int8_t", 1),  [(4, 2), (16, 4), (256, 8), (65536, 16)])
generate_luts("src/gen/compress_LUT_NEON.cpp", "NEON", 16, ("int8_t", 1),  [(4, 2), (16, 4), (256, 8), (65536, 16)])

#generate_luts("src/gen/mipp_compress_LUT_AVX.cpp",  "AVX",  8, ("int32_t", 4), [(256, 8)])
generate_AVX_luts("src/gen/compress_LUT_AVX.cpp")
