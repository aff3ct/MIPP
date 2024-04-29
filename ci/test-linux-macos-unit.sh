#!/bin/bash
set -x

for build in "$@"
do
	cd $build
	if [[ "$build" == *"sve"* ]]; then
		source /usr/share/modules/init/profile.sh
		module load armie22/22.0
		nbits=$(echo $build | grep -Eo '[0-9]+(\.[0-9]+)?' | tail -n 1)
		if [ -z "$nbits" ]
		then
			echo "The build name is incompatible with SVE build, it should contain the SIMD size (current wrong build name is '$build', an example of expected build name is: 'build_coverage_linux_armv8_gcc_sve_ls256')."
			exit 1
		fi
		# armie -msve-vector-bits=$nbits -- ./bin/run_tests 2>&1 | tee sve_$nbits.txt
		# RES=$(cat sve_$nbits.txt | tail -3 | head -n 1)
		# if [[ "$RES" != *"test cases:   289 |    92 passed | 197 failed"* ]]; then
		# 	exit 1;
		# fi
		armie -msve-vector-bits=$nbits -- ./bin/run-tests
		rc=$?; if [[ $rc != 0 ]]; then exit $rc; fi
	else
		./bin/run-tests
		rc=$?; if [[ $rc != 0 ]]; then exit $rc; fi
	fi
	cd ..
done
