#!/bin/bash
set -x

WD=$(pwd)

function gen_coverage_info {
	build=$1
	mkdir $build
	cd $build
	cmake .. -G"Unix Makefiles" -DCMAKE_CXX_COMPILER=g++ -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_FLAGS_DEBUG="-g -O0" -DCMAKE_CXX_FLAGS="-Wall -funroll-loops -finline-functions --coverage $2" -DCMAKE_EXE_LINKER_FLAGS="--coverage" -DMIPP_STATIC_LIB=ON
	rc=$?; if [[ $rc != 0 ]]; then exit $rc; fi
	make -j $THREADS
	rc=$?; if [[ $rc != 0 ]]; then exit $rc; fi
	./tests/bin/run_tests
	cd ..
	# rc=$?; if [[ $rc != 0 ]]; then exit $rc; fi
	lcov --capture --directory $build/tests/CMakeFiles/run_tests.dir/src/ --output-file code_coverage_files/$build.info
	# rc=$?; if [[ $rc != 0 ]]; then exit $rc; fi
	lcov --remove code_coverage_files/$build.info "*/usr*" "*lib/*" "*/tests/src*" --output-file code_coverage_files/$build.info
	# rc=$?; if [[ $rc != 0 ]]; then exit $rc; fi
	if [[ -s code_coverage_files/$build.info ]]
	then
		sed -i -e "s#${WD}#\.\.#g" code_coverage_files/$build.info
	else
		rm code_coverage_files/$build.info
	fi
}

pip3 install --user -r requirements.txt
python3 gencode.py

mkdir code_coverage_files || true

build_root=build_coverage_linux_x86_gcc
gen_coverage_info "${build_root}_nointr"        "-DMIPP_NO_INTRINSICS"
gen_coverage_info "${build_root}_sse2"          "-msse2"
gen_coverage_info "${build_root}_sse3"          "-msse3"
gen_coverage_info "${build_root}_ssse3"         "-mssse3"
gen_coverage_info "${build_root}_sse4_1"        "-msse4.1"
gen_coverage_info "${build_root}_sse4_2"        "-msse4.2"
gen_coverage_info "${build_root}_avx"           "-mavx"
gen_coverage_info "${build_root}_avx2"          "-mavx2"
gen_coverage_info "${build_root}_avx2_bmi2"     "-mavx2 -mbmi2"
gen_coverage_info "${build_root}_avx2_bmi2_fma" "-mavx2 -mbmi2 -mfma"
#gen_coverage_info "${build_root}_avx512f"  "-mavx512f"
#gen_coverage_info "${build_root}_avx512bw" "-mavx512f -mavx512bw"
