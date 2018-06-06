#!/bin/bash
set -x

genhtml code_coverage_files/* --branch-coverage --output-directory ./code_coverage_report/
