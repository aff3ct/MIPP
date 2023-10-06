#!/bin/bash
set -x

function compile {
	build=$1
	mkdir $build
	cd $build
	cmake .. -G"Unix Makefiles" -DCMAKE_CXX_COMPILER=g++-11 -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_FLAGS="-Wall -funroll-loops -finline-functions $2"
	rc=$?; if [[ $rc != 0 ]]; then exit $rc; fi
	make -j $THREADS
	rc=$?; if [[ $rc != 0 ]]; then exit $rc; fi
	cd ..
}

cd tests

build_root=build_linux_armv8_gcc
compile "${build_root}_sve_ls256" "-march=armv8-a+sve -msve-vector-bits=256"
compile "${build_root}_sve_ls512" "-march=armv8-a+sve -msve-vector-bits=512"
