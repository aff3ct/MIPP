#!/bin/bash
set -x

cd tests
for build in "$@"
do
	cd $build
	./bin/run_tests
	rc=$?; if [[ $rc != 0 ]]; then exit $rc; fi
	cd ..
done