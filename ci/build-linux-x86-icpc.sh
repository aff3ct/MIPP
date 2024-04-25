#!/bin/bash
set -x

function compile {
	build=$1
	mkdir $build
	cd $build
	cmake .. -G"Unix Makefiles" -DCMAKE_CXX_COMPILER=icpc -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_FLAGS="-Wall -funroll-loops -finline-functions -std=c++11 $2" -DCMAKE_EXE_LINKER_FLAGS="-static -static-libgcc -static-libstdc++" -DMIPP_STATIC_LIB=ON
	rc=$?; if [[ $rc != 0 ]]; then exit $rc; fi
	make -j $THREADS
	rc=$?; if [[ $rc != 0 ]]; then exit $rc; fi
	cd ..
}

pip3 install --user -r requirements.txt
python3 gencode.py

source /opt/intel/vars-intel.sh

build_root=build_linux_x86_icpc
compile "${build_root}_nointr"    "-DMIPP_NO_INTRINSICS"
compile "${build_root}_sse2"      "-msse2"
compile "${build_root}_sse3"      "-msse3"
compile "${build_root}_ssse3"     "-mssse3"
compile "${build_root}_sse4_1"    "-msse4.1"
compile "${build_root}_sse4_2"    "-msse4.2"
compile "${build_root}_avx"       "-mavx"
compile "${build_root}_avx2_fma"  "-march=core-avx2 -fma"
# compile "${build_root}_avx512mic" "-xMIC-AVX512"
compile "${build_root}_avx512f"   "-xCOMMON-AVX512"
compile "${build_root}_avx512bw"  "-xCORE-AVX512"