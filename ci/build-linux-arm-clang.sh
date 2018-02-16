#!/bin/bash
set -x

THREADS=$(grep -c ^processor /proc/cpuinfo)

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

build_root=build_linux_arm_clang
compile "${build_root}_nointr"     "-DMIPP_NO_INTRINSICS"
compile "${build_root}_neon32"     "-mfpu=neon"
compile "${build_root}_neon32_fma" "-mfpu=neon-vfpv4"