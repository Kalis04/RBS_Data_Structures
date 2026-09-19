#!/usr/bin/env bash
set -euo pipefail

cd "$(dirname "$0")/.."

cmake -S . -B build >/dev/null
cmake --build build >/dev/null
ctest --test-dir build --output-on-failure

cxx="${CXX:-g++}"
"$cxx" \
    -std=c++20 -Wall -Wextra -Wpedantic -g \
    -fsanitize=address,undefined -fno-omit-frame-pointer \
    -Iinclude \
    src/int_vector.cpp tests/public_tests.cpp \
    -o build/public_tests_asan

ASAN_OPTIONS=detect_leaks=1 ./build/public_tests_asan

echo "Week 3 build, public tests, and sanitizer checks passed."
