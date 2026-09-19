# Week 3 Lab Instructions — Dynamic Arrays

**BS0013 Data Structures**  
Riga Business School, Riga Technical University

This is the practical handout for Week 3. It tells you how to update your fork, start the lab, what must be completed, how to verify your work, and what to submit in Moodle.

For deeper explanations of the data-structure concepts and implementation requirements, also read `assignment.md`.

## 1. Before starting: save your existing work

Continue using the same fork and Codespace as in Weeks 1 and 2.

From the repository root, check your current state:

```bash
git status
```

If you have Week 1 or Week 2 changes that you want to keep, commit them before updating:

```bash
git add .
git commit -m "Save work before Week 3 update"
```

If Git reports that there is nothing to commit, continue normally.

## 2. Add the official course repository as `upstream`

Check your remotes:

```bash
git remote -v
```

Your `origin` should point to your own fork. If `upstream` is not yet present, add it once:

```bash
git remote add upstream https://github.com/ValRCS/RBS_BS0013_Data_Structures.git
```

Do not add it again if `upstream` already exists.

## 3. Pull the Week 3 material into your fork

From the repository root:

```bash
git switch main
git fetch upstream
git merge upstream/main
git push origin main
```

The merge preserves your own Week 1 and Week 2 commits while bringing in the new course material.

If Git reports a merge conflict:

1. run `git status`;
2. inspect the conflicted files;
3. resolve the conflict carefully;
4. `git add` the resolved files;
5. commit the merge;
6. push to your fork.

Do not delete earlier lab work merely to obtain the Week 3 files.

## 4. Open and build Week 3

Move into the lab directory:

```bash
cd labs/week03
```

Configure and build:

```bash
cmake -S . -B build
cmake --build build
```

The provided starter code is intentionally incomplete, but the project should compile before you implement the TODOs.

## 5. Required lab tasks

Complete the following in order.

### A. Observe `std::vector` growth

Run:

```bash
./build/vector_growth
```

Observe when `size()`, `capacity()`, and the address returned by `data()` change. Record the requested observations in `reflection.md`.

### B. Observe reallocation and pointer validity

Run:

```bash
./build/reallocation_demo
```

Explain in `reflection.md` why a pointer to the old vector storage becomes invalid after reallocation. Your explanation must use **storage lifetime**, not only the fact that the address changed.

### C. Implement `IntVector`

Your main implementation file is:

```text
src/int_vector.cpp
```

Implement the required functions:

- `check_invariant()`;
- destructor `~IntVector()`;
- `grow()` using the required capacity policy `0 -> 1`, then doubling;
- `push_back(int value)`;
- deep-copy constructor `IntVector(const IntVector& other)`.

Preserve the representation invariants:

```text
0 <= size_ <= capacity_
capacity_ == 0  <=>  data_ == nullptr
```

`grow()` must preserve all logical elements and must not change `size_`. A copy must own independent storage.

Copy assignment is intentionally deleted for this lab; do not turn Week 3 into a Rule-of-Five exercise unless you are working on an optional extension.

### D. Complete the reflection

Complete `reflection.md`, including:

- size versus capacity;
- pointer invalidation and lifetime;
- representation invariants;
- operation complexity;
- deep-copy ownership;
- comparison with `std::vector`.

### E. Do not weaken the provided tests

`tests/public_tests.cpp` is part of the lab verification. Do not change it merely to make an incorrect implementation pass.

## 6. Verify your work

First rebuild and run the public tests:

```bash
cmake --build build
ctest --test-dir build --output-on-failure
```

Then run the complete Week 3 verification:

```bash
bash scripts/check-week03.sh
```

The script rebuilds the project, runs the public tests, and runs the implementation under AddressSanitizer and UndefinedBehaviorSanitizer.

Before submission, the expected result is that the tests pass and the sanitizer run reports no memory errors.

## 7. Core completion checklist

Before submitting, confirm that you have completed all required work:

- [ ] updated your fork with the Week 3 release;
- [ ] ran `vector_growth` and recorded observations;
- [ ] ran `reallocation_demo` and explained pointer invalidation;
- [ ] implemented the representation invariant checks;
- [ ] implemented the destructor;
- [ ] implemented geometric growth;
- [ ] implemented `push_back`;
- [ ] implemented deep-copy construction;
- [ ] completed `reflection.md`;
- [ ] `ctest --test-dir build --output-on-failure` passes;
- [ ] `bash scripts/check-week03.sh` passes without sanitizer errors;
- [ ] committed and pushed your Week 3 work to your fork.

Optional extensions in `assignment.md` are not required unless stated separately by the instructor.

## 8. Commit and push your completed lab

From the repository root, inspect your changes:

```bash
git status
```

Commit your Week 3 work, for example:

```bash
git add labs/week03
git commit -m "Complete Week 3 dynamic array lab"
git push origin main
```

Make sure the commit containing your final Week 3 work is visible in your GitHub fork before submitting in Moodle.

## 9. Moodle submission requirements

Submit your work through the **Week 3 / Lab 3 submission activity in Moodle**. Moodle is the official submission location; GitHub is where your code is stored.

Your Moodle submission should be a concise text submission containing the following.

### 1. Repository URL

Provide the URL of your fork of the course repository.

Make sure the repository is accessible to the instructor and that your Week 3 commit has been pushed.

### 2. Work completed

Briefly describe what you completed. Organize the summary by the relevant Week 3 files or tasks. For example:

```text
src/int_vector.cpp — implemented invariant checks, destructor, grow(), push_back(), and deep-copy construction.
reflection.md — completed observations and complexity/ownership questions.
vector_growth / reallocation_demo — ran both experiments and recorded the results.
```

### 3. Verification

State whether the required checks pass:

```text
ctest: passed
scripts/check-week03.sh: passed
```

If something does not pass, state that explicitly rather than claiming success.

### 4. Blockers and challenges

Mention any important technical or conceptual problems you encountered and how you addressed them.

If there were no significant blockers, write:

```text
No major blockers.
```

### 5. Incomplete work

Clearly identify anything that remains incomplete or does not work correctly. If everything required is complete, write:

```text
Required work complete.
```

## 10. Example Moodle submission

A concise submission can look like this:

```text
Repository: https://github.com/<your-username>/RBS_BS0013_Data_Structures

Completed:
- src/int_vector.cpp — implemented invariant checks, destructor, doubling growth, push_back, and deep-copy constructor.
- reflection.md — completed all required questions.
- Ran vector growth and reallocation experiments.

Verification:
- ctest: passed
- scripts/check-week03.sh: passed

Blockers/challenges:
- Initially had an element-preservation error during grow(); fixed the copy-before-delete order.

Incomplete work:
- Required work complete.
```

Keep the submission concise. The purpose is to document what you actually implemented, tested, and understood; it is not a formal report.
