#!/usr/bin/env python3
import sys
import os
import shutil
import struct
import argparse

path = os.getcwd()

sys.path.insert(1,path +'/avx512_gen')
sys.path.insert(1,path + '/avx_gen')
sys.path.insert(1,path + '/sse_gen')

from implem_SSE import isa_sse
from implem_AVX import isa_avx
from implem_AVX512 import isa_avx512

from sse_gen import gen_mipp_sse
from avx_gen import gen_mipp_avx
from avx512_gen import gen_mipp_avx512

from ci_generator import generate_c_interface
from cpp_generator import generate_cpp
from cpp_object_generator import generate_cpp_object

sse_gen = "../include/"
avx_gen = "../include/"
avx512_gen = "../include/"

# avx and avx512 folder path
sse_path = os.path.join(avx512_gen, "sse")
avx_path = os.path.join(avx_gen, "avx")
avx512_path = os.path.join(avx512_gen, "avx512")


def create_folder(folder_path):
    if not os.path.exists(folder_path):
        os.makedirs(folder_path)
        print(folder_path+"folder successfully created")
    else:
        print("The "+ folder_path+" folder already exists.")


def clean_folder(folder_path):
    try:
        shutil.rmtree(folder_path)
        print(f"Successfully deleted folder: {folder_path}")
    except Exception as e:
        print(f"Failed to delete folder: {folder_path}. Reason: {e}")

#Function that manages the display help menu
def help_menu():
    nb_caract = 12
    
    w = struct.unpack('hhhh', fcntl.ioctl(0, 21523, struct.pack('HHHH', 0, 0, 0, 0)))
    nb_ast = (w[1] - nb_caract) // 2
    
    for i in range(nb_ast):
        print("\033[0;37m#", end='')
    
    print(" MIPP generator ", end='')
    
    for i in range(nb_ast-3):
        print("#", end='')
    
    print(
        "\n\n"
        "List of argument:\n"
        "\t-'--avx2'         : Generate MIPP code for avx2 \n"
        "\t-'--avx512'       : Generate MIPP code for avx512 \n"
        "\t-'--all'          : Generate MIPP code for both of avx2 and avx512\n"
        "\t-'--clean_all'    : Remove all generated files in both of  'include/avx2' and 'include/avx512' folder\n"
        "\t-'--clean_avx2'   : Remove avx2 generated files in 'include/avx2' folder\n"
        "\t-'--clean_avx512' : Remove avx2 generated files in 'include/avx512' folder\n"
        "\t-'--version'    		: Return current version of MIPP \n"
        "\t-'--info' or '--h'  : Print brief documentation for how to invoke the program \n"
        "\t-'--quit'         : Quit the program\n\n"
    )
    
    for i in range(w[1]):
        print("#", end='')
    
    print("\n\n\033[0m")

def main(args):
    if args.avx2:
        create_folder(avx_path)
        print("Generating MIPP code for avx2")
        gen_mipp_avx.gen_mipp_avx()
    if args.avx512:
        create_folder(avx512_path)
        print("Generating MIPP code for avx512")
        gen_mipp_avx512.gen_mipp_avx512()
    if args.all:
        create_folder(sse_path)
        create_folder(avx_path)
        create_folder(avx512_path)
        gen_mipp_sse.gen_mipp_sse()
        gen_mipp_avx.gen_mipp_avx()
        gen_mipp_avx512.gen_mipp_avx512()
        # warning order
        generate_c_interface([isa_avx512,isa_avx,isa_sse])
        generate_cpp()
        generate_cpp_object()
        print("Generating MIPP code for sse, avx2 and avx512")
    if args.clean_all:
        print("Removing all generated files ...")
        clean_folder(avx_path)
        clean_folder(avx512_path)
    if args.clean_avx2:
        print("Removing avx2 generated files")
        clean_folder(avx_path)
    if args.clean_avx512:
        print("Removing avx512 generated files")
        clean_folder(avx512_path)
    if args.version:
        print("MIPP.V2 version 2023")
    if args.info:
        print("Help menu")
        help_menu()

if __name__ == "__main__":
    parser = argparse.ArgumentParser(prog='gen_mipp_v2.py', description='MIPP generator')

    parser.add_argument('--avx2'         , action='store_true' , help='Generate MIPP code for avx2')
    parser.add_argument('--avx512'       , action='store_true' , help='Generate MIPP code for avx512')
    parser.add_argument('--all'          , action='store_true' , help='Generate MIPP code for all avalaible simd')
    parser.add_argument('--clean_all'    , action='store_true' , help='Remove all generated files')
    parser.add_argument('--clean_avx2'   , action='store_true' , help='Remove avx2 generated files')
    parser.add_argument('--clean_avx512' , action='store_true' , help='Remove avx512 generated files')
    parser.add_argument('--version'      , action='store_true' , help='Return current version of MIPP')
    parser.add_argument('--info'         , action='store_true' , help='Print brief documentation on how to invoke the program')

    args = parser.parse_args()
    main(args)
