#!/bin/bash
set -x

cd tests
mkdir code_coverage_report || true

genhtml code_coverage_files/* --branch-coverage --output-directory ./code_coverage_report/
