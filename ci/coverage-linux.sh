#!/bin/bash
set -x

cd tests
mkdir code_coverage_report || true

genhtml code_coverage_files/* --output-directory ./code_coverage_report/
