#!/usr/bin/env bash
set -euo pipefail

cd "$(dirname "$0")/.."

cmake -S . -B build >/dev/null
cmake --build build >/dev/null
ctest --test-dir build --output-on-failure

pointer_output="$(./build/pointer_trace)"
grep -q "a = 15" <<<"$pointer_output"
grep -q "b = 27" <<<"$pointer_output"
grep -q "\*p = 27" <<<"$pointer_output"
grep -q "\*q = 15" <<<"$pointer_output"

dynamic_output="$(./build/dynamic_value)"
grep -q "initial = 42" <<<"$dynamic_output"
grep -q "changed = 100" <<<"$dynamic_output"

chain_output="$(./build/node_chain)"
if [[ "$chain_output" != "10 20 25 30 " ]]; then
    echo "Expected final chain output: '10 20 25 30 '"
    echo "Actual output: '$chain_output'"
    exit 1
fi

echo "Week 2 public checks passed."
