#!/bin/bash
set -x

WD=$(pwd)

# install Intel SDE emulator --------------------------------------------------
apt update
apt install -y wget xz-utils
echo 0 > /proc/sys/kernel/yama/ptrace_scope
mkdir softwares
cd softwares
wget https://largo.lip6.fr/monolithe/downloads/sde-external-9.33.0-2024-01-07-lin.tar.xz
tar -xvvf sde-external-9.33.0-2024-01-07-lin.tar.xz
ln -s $WD/softwares/sde-external-9.33.0-2024-01-07-lin $WD/softwares/sde
export PATH=$WD/softwares/sde:$PATH
cd ..
# -----------------------------------------------------------------------------

function gen_coverage_info {
	build=$1
	mkdir $build
	cd $build
	cmake ../.. -G"Unix Makefiles" -DCMAKE_CXX_COMPILER=g++ -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_FLAGS_DEBUG="-g -O0" -DCMAKE_CXX_FLAGS="-Wall -funroll-loops -finline-functions --coverage $2" -DCMAKE_EXE_LINKER_FLAGS="--coverage" -DMIPP_STATIC_LIB=ON
	rc=$?; if [[ $rc != 0 ]]; then exit $rc; fi
	make -j $THREADS
	rc=$?; if [[ $rc != 0 ]]; then exit $rc; fi
	if [[ $3 == native ]]; then
		# execute the tests natively
		./bin/run-tests
	else
		# use the Intel SDE emulator to execute the tests
		sde64 $3 -- ./bin/run-tests
	fi
	cd ..
	# rc=$?; if [[ $rc != 0 ]]; then exit $rc; fi
	lcov --capture --directory $build/CMakeFiles/tests_exe.dir/tests/src/ --output-file code_coverage_files/$build.info
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

python3 codegen/gen_compress.py

cd tests
mkdir code_coverage_files || true

build_root=build_coverage_linux_x86_gcc
gen_coverage_info "${build_root}_nointr"        "-DMIPP_NO_INTRINSICS"                            "native"
gen_coverage_info "${build_root}_sse2"          "-msse2"                                          "native"
gen_coverage_info "${build_root}_sse3"          "-msse3"                                          "native"
gen_coverage_info "${build_root}_ssse3"         "-mssse3"                                         "native"
gen_coverage_info "${build_root}_sse4_1"        "-msse4.1"                                        "native"
gen_coverage_info "${build_root}_sse4_2"        "-msse4.2"                                        "native"
gen_coverage_info "${build_root}_avx"           "-mavx"                                           "native"
gen_coverage_info "${build_root}_avx2"          "-mavx2"                                          "native"
gen_coverage_info "${build_root}_avx2_bmi2"     "-mavx2 -mbmi2"                                   "native"
gen_coverage_info "${build_root}_avx2_bmi2_fma" "-mavx2 -mbmi2 -mfma"                             "native"
gen_coverage_info "${build_root}_avx512f"       "-mavx512f"                                       "-skx" # skylake server architecture emulation
gen_coverage_info "${build_root}_avx512bw"      "-mavx512f -mavx512bw"                            "-skx" # skylake server architecture emulation
gen_coverage_info "${build_root}_avx512vbmi2"   "-mavx512f -mavx512bw -mavx512vbmi -mavx512vbmi2" "-spr" # sapphire rapid architecture emulation
