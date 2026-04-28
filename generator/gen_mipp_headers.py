#!/usr/bin/env python3
import sys
import os
import shutil
import struct
import argparse

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

from tools import all_lmul, all_ldiv

include_gen_path = "../include/"

# avx and avx512 folder path
sse_path = os.path.join(include_gen_path, "sse")
avx_path = os.path.join(include_gen_path, "avx")
avx512_path = os.path.join(include_gen_path, "avx512")
sve_path = os.path.join(include_gen_path, "sve")
rvv_path = os.path.join(include_gen_path, "rvv")
neon_path = os.path.join(include_gen_path, "neon")
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

def main():
    # check that all mipp funcs have a scalar implem before to start
    check_mipp_funcs_scalar_implems()
    #clean all
    clean_folder(include_gen_path)
    #create folders
    create_folder(sse_path)
    create_folder(avx_path)
    create_folder(avx512_path)
    create_folder(sve_path)
    create_folder(rvv_path)
    create_folder(neon_path)
    create_folder(scalar_path)
    # generate all avalaible simd and wrapp
    gen_mipp_sse()
    gen_mipp_avx()
    gen_mipp_avx512()
    gen_mipp_sve()
    gen_mipp_rvv()
    gen_mipp_neon()
    gen_mipp_scalar()
    # generate mipp_v2.h
    generate_mipp_h()
    # warning order
    # interface all simd  in c
    # generate mipp_v2_interface_gen.h
    generate_c_interface([isa_avx512,isa_avx,isa_sse,isa_sve,isa_rvv,isa_neon,isa_scalar])
    # C++ template wrapper interface with specialization
    # generate mipp.hpp
    generate_cpp()
    # C++ object wrapper using template specialization
    # generate mipp_object_gen.h
    generate_cpp_object()

    print("Generating MIPP code for sse, avx2, avx512, rvv and sve with size in " + str(isa_sve["size"]))
    print("With lmul in "+str(all_lmul)+ " and ldiv in "+str(all_ldiv))
    
if __name__ == "__main__":
    parser = argparse.ArgumentParser(prog='gen_mipp.py', description='MIPP generator')
    main()
