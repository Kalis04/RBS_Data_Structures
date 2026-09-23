# BS0013 Week 4 Lab — Linked Structures

## Start here

Read **`instructions.md` first**. It is the complete Week 4 student handout covering:

- updating your fork from the official course repository;
- building the Week 4 Codespaces workspace;
- the required linked-list implementation tasks;
- public tests and sanitizer verification;
- committing and pushing your work;
- the Moodle submission format.

Use `assignment.md` for the deeper conceptual and implementation specification.

Week 4 continues in the **same fork and Codespace** used in earlier weeks.

## Quick update reminder

From the repository root:

```bash
git status
git switch main
git fetch upstream
git merge upstream/main
git push origin main
```

If `upstream` is not configured yet, see `instructions.md` for the one-time setup command.

## Quick build

```bash
cd labs/week04
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
```

The starter compiles but intentionally contains TODO operations.

Implement the required functions in:

```text
src/int_linked_list.cpp
```

Do not change the public interface merely to make tests easier.

## Test your implementation

When the core implementation is complete:

```bash
cmake --build build
ctest --test-dir build --output-on-failure
bash scripts/check-week04.sh
```

The verification script repeats the tests with AddressSanitizer and UndefinedBehaviorSanitizer enabled.

## Main Week 4 files

```text
instructions.md                  complete workflow and Moodle submission instructions
assignment.md                    detailed practical and conceptual specification
include/int_linked_list.hpp      IntLinkedList interface and representation
src/int_linked_list.cpp          TODO implementation
src/main.cpp                     small demonstration / debugging trace
tests/public_tests.cpp           student-visible correctness checks
scripts/check-week04.sh          normal + sanitizer verification
reflection.md                    short conceptual answers
```

Week 4 focuses on singly linked topology, representation invariants, pointer rewiring, node lifetime, navigation versus mutation cost, and comparison with Week 3 contiguous storage.
