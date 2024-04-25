#!/bin/bash
set -x

function compile {
	build=$1
	mkdir $build
	cd $build
	cmake .. -G"Unix Makefiles" -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_FLAGS="-Wall -funroll-loops -finline-functions $2" -DMIPP_STATIC_LIB=ON
	rc=$?; if [[ $rc != 0 ]]; then exit $rc; fi
	make
	rc=$?; if [[ $rc != 0 ]]; then exit $rc; fi
	cd ..
}

apt update
apt install -y python3-pip
pip3 install --user -r requirements.txt
python3 gencode.py

build_root=build_macos_x86_clang
compile "${build_root}_nointr"   "-DMIPP_NO_INTRINSICS"
compile "${build_root}_sse2"     "-msse2"
compile "${build_root}_sse3"     "-msse3"
compile "${build_root}_ssse3"    "-mssse3"
compile "${build_root}_sse4_1"   "-msse4.1"
compile "${build_root}_sse4_2"   "-msse4.2"
compile "${build_root}_avx"      "-mavx"
compile "${build_root}_avx2"     "-mavx2"
compile "${build_root}_avx2_fma" "-mavx2 -mfma"