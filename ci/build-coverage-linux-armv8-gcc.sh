#!/bin/bash
set -x

WD=$(pwd)

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
		# use Arm Instruction Emulator (ArmIE) to execute the tests
		source /usr/share/modules/init/profile.sh
		module load armie22/22.0
		nbits=$(echo $build | grep -Eo '[0-9]+(\.[0-9]+)?' | tail -n 1)
		if [ -z "$nbits" ]
		then
			echo "The build name is incompatible with SVE build, it should contain the SIMD size (current wrong build name is '$build', an example of expected build name is: 'build_coverage_linux_armv8_gcc_sve_ls256')."
			exit 1
		fi
		armie -msve-vector-bits=$nbits -- ./bin/run-tests
		#qemu-aarch64 -cpu max,sve-default-vector-length=$nbits ./bin/run-tests
	fi
	cd ..
	# rc=$?; if [[ $rc != 0 ]]; then exit $rc; fi
	lcov --capture --directory $build/CMakeFiles/run_tests.dir/tests/src/ --output-file code_coverage_files/$build.info
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

build_root=build_coverage_linux_armv8_gcc
gen_coverage_info "${build_root}_nointr"     "-DMIPP_NO_INTRINSICS"                      "native"
gen_coverage_info "${build_root}_neon"       "-march=armv8.1-a+simd"                     "native"
gen_coverage_info "${build_root}_sve_ls128"  "-march=armv8-a+sve -msve-vector-bits=128"  "armie"
gen_coverage_info "${build_root}_sve_ls256"  "-march=armv8-a+sve -msve-vector-bits=256"  "armie"
gen_coverage_info "${build_root}_sve_ls512"  "-march=armv8-a+sve -msve-vector-bits=512"  "armie"
gen_coverage_info "${build_root}_sve_ls1024" "-march=armv8-a+sve -msve-vector-bits=1024" "armie"
