#!/bin/bash
set -x

cd tests
for build in "$@"
do
	cd $build
	if [[ "$build" == *"sve"* ]]; then
		source /usr/share/modules/init/profile.sh
		module load armie22/22.0
		if [[ "$build" == *"256"* ]]; then
			nbits=256
		else
			if [[ "$build" == *"512"* ]]; then
				nbits=512
			else
				echo "This should never happen!"
				exit 1;
			fi
		fi
		armie -msve-vector-bits=$nbits -- ./bin/run_tests 2>&1 | tee sve_$nbits.txt
		RES=$(cat sve_$nbits.txt | tail -3 | head -n 1)
		if [[ "$RES" != *"test cases:   289 |    92 passed | 197 failed"* ]]; then
			exit 1;
		fi
	else
		./bin/run_tests
		rc=$?; if [[ $rc != 0 ]]; then exit $rc; fi
	fi
	cd ..
done