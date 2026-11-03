# Week 6 Student Instructions — Linear-Probing Hash Map

## 1. Update your fork

Before starting Week 6, save your existing work and update your fork.

    git status
    git switch main
    git remote -v

If no upstream remote exists yet, add the official public course repository once:

    git remote add upstream https://github.com/ValRCS/RBS_BS0013_Data_Structures.git

Then update your branch:

    git fetch upstream
    git merge upstream/main
    git push origin main

If you have uncommitted local changes, commit or stash them before merging.

## 2. Open the Week 6 lab

    cd labs/week06
    cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
    cmake --build build

The starter implementation compiles, but operations marked TODO throw std::logic_error until you implement them.

## 3. Recommended implementation order

Work in src/int_hash_map.cpp.

1. Inspect SlotState and HashSlot in the header.
2. Implement bucket().
3. Implement find_index().
4. Implement both find() overloads and contains().
5. Implement insert_or_assign().
6. Implement erase() using Deleted, not Empty.
7. Implement probe_count().
8. Implement check_invariant().
9. Run the public tests after each small group of changes.

## 4. Run the public tests

    cmake --build build
    ctest --test-dir build --output-on-failure

For a complete verification pass, including sanitizers:

    bash scripts/check-week06.sh

## 5. Required conceptual checks

Before submitting, be able to explain why 10, 17, and 24 collide at capacity 7; why deleting 10 must not make 17 or 24 unreachable; why insertion continues past a tombstone to search for an existing key; why probing wraps around; and why expected Θ(1) lookup is not a worst-case guarantee.

Complete reflection.md after your implementation works.

## 6. Commit your work

From the repository root:

    git status
    git add labs/week06
    git commit -m "Complete week 06 hash table lab"
    git push origin main

## 7. Moodle submission

Submit your forked repository URL, files changed, what you implemented and tested, the collision/wrap-around case you verified, blockers or unresolved questions, and your answers from reflection.md. Do not submit only screenshots.
