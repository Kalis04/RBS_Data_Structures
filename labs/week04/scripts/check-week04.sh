#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
BUILD_DIR="${ROOT_DIR}/build"
ASAN_BUILD_DIR="${ROOT_DIR}/build-asan"

echo "== Week 4: normal Debug build =="
cmake -S "${ROOT_DIR}" -B "${BUILD_DIR}" -DCMAKE_BUILD_TYPE=Debug
cmake --build "${BUILD_DIR}"
ctest --test-dir "${BUILD_DIR}" --output-on-failure

echo
echo "== Week 4: ASan/UBSan build =="
cmake -S "${ROOT_DIR}" -B "${ASAN_BUILD_DIR}"     -DCMAKE_BUILD_TYPE=Debug     -DENABLE_SANITIZERS=ON
cmake --build "${ASAN_BUILD_DIR}"
ctest --test-dir "${ASAN_BUILD_DIR}" --output-on-failure

echo
echo "Week 4 verification passed."
