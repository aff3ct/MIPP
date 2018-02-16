#!/bin/bash
set -x

THREADS=$(grep -c ^processor /proc/cpuinfo)

function compile {
	build=$1
	mkdir $build
	cd $build
	cmake .. -G"Unix Makefiles" -DCMAKE_CXX_COMPILER=g++ -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_FLAGS="-Wall -funroll-loops -finline-functions $2"
	rc=$?; if [[ $rc != 0 ]]; then exit $rc; fi
	make -j $THREADS
	rc=$?; if [[ $rc != 0 ]]; then exit $rc; fi
	cd ..
}

cd tests

build_root=build_linux_gcc_x86
compile "${build_root}_nointr"   "-DMIPP_NO_INTRINSICS"
compile "${build_root}_sse2"     "-msse2"
compile "${build_root}_sse3"     "-msse3"
compile "${build_root}_ssse3"    "-mssse3"
compile "${build_root}_sse4_1"   "-msse4.1"
compile "${build_root}_sse4_2"   "-msse4.2"
compile "${build_root}_avx"      "-mavx"
compile "${build_root}_avx2"     "-mavx2"
compile "${build_root}_avx2_fma" "-mavx2 -mfma"
compile "${build_root}_avx512f"  "-mavx512f"