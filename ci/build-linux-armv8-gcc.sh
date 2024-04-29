#!/bin/bash
set -x

function compile {
	build=$1
	mkdir $build
	cd $build
	cmake .. -G"Unix Makefiles" -DCMAKE_CXX_COMPILER=g++ -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_FLAGS="-Wall -funroll-loops -finline-functions $2" -DMIPP_STATIC_LIB=ON
	rc=$?; if [[ $rc != 0 ]]; then exit $rc; fi
	make -j $THREADS
	rc=$?; if [[ $rc != 0 ]]; then exit $rc; fi
	cd ..
}

apt update
apt install -y python3-pip
pip3 install --user -r codegen/requirements.txt
python3 codegen/gen_compress.py

build_root=build_linux_armv8_gcc
compile "${build_root}_nointr"     "-DMIPP_NO_INTRINSICS"
compile "${build_root}_neon"       "-march=armv8.1-a+simd"
compile "${build_root}_sve_ls128"  "-march=armv8-a+sve -msve-vector-bits=128"
compile "${build_root}_sve_ls256"  "-march=armv8-a+sve -msve-vector-bits=256"
compile "${build_root}_sve_ls512"  "-march=armv8-a+sve -msve-vector-bits=512"
compile "${build_root}_sve_ls1024" "-march=armv8-a+sve -msve-vector-bits=1024"