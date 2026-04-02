#!/usr/bin/env python3
import sys
import os
import shutil
import struct
import argparse

path = os.getcwd()

sys.path.insert(1,path +'/simd_ext/avx512/')
sys.path.insert(1,path + '/simd_ext/avx/')
sys.path.insert(1,path + '/simd_ext/sse/')
sys.path.insert(1,path + '/simd_ext/sve/')
sys.path.insert(1,path + '/simd_ext/rvv/')

from implem_sse import isa_sse
from implem_avx import isa_avx
from implem_avx512 import isa_avx512
from implem_sve import isa_sve
from implem_rvv import isa_rvv

from gen_mipp_sse import gen_mipp_sse
from gen_mipp_avx import gen_mipp_avx
from gen_mipp_avx512 import gen_mipp_avx512
from gen_mipp_sve import gen_mipp_sve
from gen_mipp_rvv import gen_mipp_rvv



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

def main():
    #clean all
    clean_folder(include_gen_path)
    #create folders
    create_folder(sse_path)
    create_folder(avx_path)
    create_folder(avx512_path)
    create_folder(sve_path)
    create_folder(rvv_path)
    # generate all avalaible simd and wrapp
    gen_mipp_sse()
    gen_mipp_avx()
    gen_mipp_avx512()
    gen_mipp_sve()
    gen_mipp_rvv()
    # generate mipp_v2.h
    generate_mipp_h()
    # warning order
    # interface all simd  in c
    # generate mipp_v2_interface_gen.h
    generate_c_interface([isa_avx512,isa_avx,isa_sse,isa_sve,isa_rvv])
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
