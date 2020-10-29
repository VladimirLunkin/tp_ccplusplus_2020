#!/usr/bin/env bash

set -e
set -o pipefail

function print_header() {
    echo -e "\n***** ${1} *****"
}

print_header "RUN cppcheck"
if [ "${1}" == "--local" ]; then
	CPPCHECK="cppcheck"
else
	CPPCHECK="./linters/cppcheck/cppcheck"
fi
${CPPCHECK} project/src/* project/tests/*.cpp --enable=all --error-exitcode=1 -I project/include --suppress=missingInclude # --check-config

print_header "RUN cpplint.py"
cpplint --filter=-legal/copyright,-readability/casting project/include/consistently/*.h
cpplint --filter=-legal/copyright,-readability/casting project/src/consistently/*.c
cpplint --filter=-legal/copyright,-readability/casting project/tests/*.cpp

print_header "SUCCESS"
