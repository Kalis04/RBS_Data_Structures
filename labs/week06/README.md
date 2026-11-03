# BS0013 Week 6 Lab — Linear-Probing Hash Map

## Start here

Read **instructions.md first**. It covers updating your fork, building the Week 6 workspace, implementing the hash map, running public tests, sanitizer verification, and Moodle submission.

Use assignment.md for the detailed conceptual and implementation specification. Week 6 continues in the **same fork and Codespace** used in previous weeks.

## Quick build

From the repository root:

    cd labs/week06
    cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
    cmake --build build

The starter compiles but intentionally contains TODO operations that throw std::logic_error until implemented.

Implement the required functions in src/int_hash_map.cpp.

## Test your implementation

    ctest --test-dir build --output-on-failure
    bash scripts/check-week06.sh

The verification script repeats the public tests with AddressSanitizer and UndefinedBehaviorSanitizer enabled.

## Main Week 6 files

    instructions.md             complete workflow and submission instructions
    assignment.md               detailed practical specification
    include/int_hash_map.hpp    public interface and representation
    src/int_hash_map.cpp        TODO implementation
    tests/public_tests.cpp      student-visible correctness checks
    scripts/check-week06.sh     normal + sanitizer verification
    reflection.md               short conceptual reflection

Week 6 focuses on the dictionary ADT, hashing, collision resolution, linear probing, tombstones, representation invariants, load factor, and expected versus worst-case complexity.
