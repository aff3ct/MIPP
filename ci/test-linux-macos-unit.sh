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
			armie -msve-vector-bits=256 -- ./bin/run_tests
		else
			if [[ "$build" == *"512"* ]]; then
				armie -msve-vector-bits=512 -- ./bin/run_tests
			else
				echo "This should never happen!"
				exit 1;
			fi
		fi
	else
		./bin/run_tests
	fi
	rc=$?; if [[ $rc != 0 ]]; then exit $rc; fi
	cd ..
done