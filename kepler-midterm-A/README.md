# Kepler Station cargo registry — assessment workspace

This is the programming workspace for the BS0013 Week 7 midterm. Read the examination paper assigned by the instructor before editing code.

## Files you are expected to edit

- `src/cargo_registry.cpp`
- `tests/student_tests.cpp`
- `answers.md`

Do not change the public interface in `include/cargo_registry.hpp`, the supplied public tests, or `CMakeLists.txt` unless the invigilator explicitly instructs you to do so.

## Build and test

Recommended one-command check:

```bash
bash scripts/check.sh
```

Equivalent manual commands:

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build --parallel 2
ctest --test-dir build --output-on-failure
```

The starter project is expected to **compile**, but `public_tests` will fail until required TODOs are implemented. An initially passing `student_tests` executable is not evidence of completion: you must add two meaningful regression tests.

Optional sanitizer build:

```bash
cmake -S . -B build-sanitize -DCMAKE_BUILD_TYPE=Debug -DENABLE_SANITIZERS=ON
cmake --build build-sanitize --parallel 2
ctest --test-dir build-sanitize --output-on-failure
```

Direct compiler fallback for the supplied public test:

```bash
g++ -std=c++20 -Wall -Wextra -Wpedantic -g \
    -Iinclude src/cargo_registry.cpp tests/public_tests.cpp \
    -o registry_tests
./registry_tests
```

## Implementation constraints

The registry is intentionally implemented using the supplied `std::vector<Slot>` and linear probing. Do not replace it with `std::map` or `std::unordered_map`.

There is no automatic growth requirement. `rehash(new_capacity)` is called explicitly.

The diagnostic `check_invariant()` function is supplied and is not itself a TODO. Public tests are examples rather than the full grading specification.

## Written evidence

Complete `answers.md` as you work. It contains prompts for:

- warm-up reasoning;
- invariant/bug explanations;
- expected and worst-case time complexity;
- auxiliary-space complexity;
- rehash/pointer-validity reasoning;
- regression-test rationale;
- final data-structure comparisons.

If you cannot finish a method, keep your best compilable work and describe the intended algorithm in the **Incomplete work** section.

## Submission hygiene

Do not submit generated `build/` directories, executables, editor caches, credentials, or a public repository. Use only the private submission route announced by the instructor.
