# BS0013 Week 3 Lab — Dynamic Array

## Start here

Read **`instructions.md` first**. It is the complete Week 3 student handout covering:

- updating your fork from the official course repository;
- opening and building the Week 3 Codespaces workspace;
- the required lab tasks;
- verification and sanitizer checks;
- committing and pushing your work;
- the exact Moodle submission format and required summary.

Use `assignment.md` for the deeper conceptual and implementation specification.

Week 3 uses the **same fork and Codespace** as Weeks 1 and 2. The new material must first be merged from the official course repository into your fork.

## Quick update reminder

From the repository root, save any work you want to keep, then update from the official repository:

```bash
git status
git switch main
git fetch upstream
git merge upstream/main
git push origin main
```

If you have not configured `upstream` yet, see `instructions.md` for the one-time setup command and conflict-resolution guidance.

## Quick build

```bash
cd labs/week03
cmake -S . -B build
cmake --build build
```

The starter code is intentionally incomplete, but the project should compile before you fill the TODOs.

First run the observation programs:

```bash
./build/vector_growth
./build/reallocation_demo
```

Then implement `IntVector` in:

```text
src/int_vector.cpp
```

Follow `instructions.md`, `assignment.md`, and complete `reflection.md`.

## Test your implementation

Once the core implementation is complete:

```bash
cmake --build build
ctest --test-dir build --output-on-failure
bash scripts/check-week03.sh
```

`check-week03.sh` runs the public tests again under AddressSanitizer and UndefinedBehaviorSanitizer.

Do not modify `tests/public_tests.cpp` merely to make an incorrect implementation pass.

## Main Week 3 files

```text
instructions.md               complete workflow and Moodle submission instructions
assignment.md                 detailed practical and conceptual specification
include/int_vector.hpp        IntVector interface and representation
src/int_vector.cpp            TODO implementation
src/main.cpp                  small demonstration program
src/vector_growth.cpp         observe std::vector size/capacity
src/reallocation_demo.cpp     observe storage relocation
tests/public_tests.cpp        student-visible correctness checks
scripts/check-week03.sh       build + tests + sanitizer verification
reflection.md                 short conceptual answers
```
