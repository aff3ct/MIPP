#!/bin/bash
set -x

function compile {
	build=$1
	mkdir $build
	cd $build
	cmake .. -G"Unix Makefiles" -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_FLAGS="-Wall -funroll-loops $2"
	rc=$?; if [[ $rc != 0 ]]; then exit $rc; fi
	make -j $THREADS
	rc=$?; if [[ $rc != 0 ]]; then exit $rc; fi
	cd ..
}

cd tests

build_root=build_linux_x86_clang
compile "${build_root}_nointr"   "-DMIPP_NO_INTRINSICS"
compile "${build_root}_sse2"     "-msse2"
compile "${build_root}_sse3"     "-msse3"
compile "${build_root}_ssse3"    "-mssse3"
compile "${build_root}_sse4_1"   "-msse4.1"
compile "${build_root}_sse4_2"   "-msse4.2"
compile "${build_root}_avx"      "-mavx"
compile "${build_root}_avx2"     "-mavx2"
compile "${build_root}_avx2_fma" "-mavx2 -mfma"