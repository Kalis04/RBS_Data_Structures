# Week 4 Lab Instructions — Linked Structures

**BS0013 Data Structures**  
Riga Business School, Riga Technical University

This is the practical handout for Week 4. It explains how to update your fork, build the lab, complete the required tasks, verify the implementation, commit your work, and submit the result in Moodle.

For the deeper conceptual and implementation specification, also read `assignment.md`.

## 1. Save your existing work

Continue using the same fork and Codespace as in previous weeks.

From the repository root:

```bash
git status
```

If you have changes you want to keep, commit them before updating:

```bash
git add .
git commit -m "Save work before Week 4 update"
```

If Git reports that the working tree is clean, continue normally.

## 2. Check the official repository remote

Run:

```bash
git remote -v
```

Your `origin` should point to your own fork.

If `upstream` is not present, add it once:

```bash
git remote add upstream https://github.com/ValRCS/RBS_BS0013_Data_Structures.git
```

Do not add a second `upstream` remote if it already exists.

## 3. Pull the Week 4 release into your fork

From the repository root:

```bash
git switch main
git fetch upstream
git merge upstream/main
git push origin main
```

This preserves your previous commits while bringing in the Week 4 material.

If Git reports a merge conflict:

1. run `git status`;
2. inspect the conflicted files;
3. resolve the conflict carefully;
4. `git add` the resolved files;
5. commit the merge;
6. push to your fork.

Do not delete earlier lab work merely to obtain the new files.

## 4. Open and build Week 4

Move to:

```bash
cd labs/week04
```

Configure and build:

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
```

The starter code is intentionally incomplete, but it should compile before you fill the TODOs.

## 5. Required implementation work

Your main implementation file is:

```text
src/int_linked_list.cpp
```

Implement the required operations in this order:

1. `check_invariant()`;
2. `front()` and `back()`;
3. `push_front()` and `push_back()`;
4. `contains()`;
5. `pop_front()`;
6. `clear()`;
7. `insert_after_first()`;
8. `erase_after_first()`.

Preserve the representation invariants described in `assignment.md`.

Important boundary transitions include:

```text
empty -> one node
one node -> empty
one node -> two nodes
many nodes -> many nodes
insert after tail
erase the current tail
clear an already-empty list
```

The required empty-operation policy is also fixed:

- `front()` on an empty list throws `std::out_of_range`;
- `back()` on an empty list throws `std::out_of_range`;
- `pop_front()` on an empty list throws `std::out_of_range`.

Do not modify the interface or the tests merely to avoid these requirements.

## 6. Complete the reflection

Complete `reflection.md` after the implementation works.

The questions focus on:

- logical versus physical adjacency;
- Θ(n) indexed access;
- navigation versus rewiring cost;
- `tail_` as cached structural information;
- lifetime ordering during deletion;
- structural versus sanitizer-detectable bugs;
- locality and pointer chasing;
- representation choice;
- the bridge to stacks and queues.

Keep answers concise but precise.

## 7. Run the public tests

Rebuild and run:

```bash
cmake --build build
ctest --test-dir build --output-on-failure
```

You can also run the small demonstration executable:

```bash
./build/week04_demo
```

Add your own short operation traces to `src/main.cpp` if they help you debug. The public tests remain the required functional check.

## 8. Run the complete Week 4 verification

Run:

```bash
bash scripts/check-week04.sh
```

The script:

1. configures and builds a normal Debug build;
2. runs the public tests;
3. configures a second build with AddressSanitizer and UndefinedBehaviorSanitizer;
4. rebuilds and reruns the tests under sanitizers.

Before submission, the expected result is:

```text
public tests: passed
sanitizer tests: passed
no memory diagnostics
```

If a sanitizer reports an error, treat it as a defect even when visible output appears correct.

## 9. Core completion checklist

Before submitting, confirm:

- [ ] your fork contains the Week 4 release;
- [ ] `check_invariant()` is implemented;
- [ ] front/back operations are correct;
- [ ] front/back insertion is correct;
- [ ] traversal with `contains()` is correct;
- [ ] `pop_front()` handles one-node and many-node cases;
- [ ] `clear()` releases the complete chain;
- [ ] insertion after the first matching node works;
- [ ] erasure after the first matching node works;
- [ ] tail updates are correct;
- [ ] `reflection.md` is complete;
- [ ] `ctest --test-dir build --output-on-failure` passes;
- [ ] `bash scripts/check-week04.sh` passes without sanitizer errors;
- [ ] your Week 4 changes are committed and pushed.

Optional extensions in `assignment.md` are not required unless the instructor states otherwise.

## 10. Commit and push your completed lab

From the repository root:

```bash
git status
git diff
```

Commit your Week 4 work, for example:

```bash
git add labs/week04
git commit -m "Complete Week 4 linked list lab"
git push origin main
```

Make sure the final commit is visible in your GitHub fork before submitting in Moodle.

Do not commit build directories, binaries, sanitizer logs, credentials, or unrelated files.

## 11. Moodle submission requirements

Submit through the **Week 4 / Lab 4 submission activity in Moodle**. Moodle is the official submission location; GitHub stores your code.

Your Moodle text submission should contain the following.

### 1. Repository URL

Provide the URL of your fork of the course repository.

Make sure the repository is accessible to the instructor and your Week 4 commit has been pushed.

### 2. Work completed

Briefly describe what you implemented, organized by relevant files or tasks. For example:

```text
src/int_linked_list.cpp — implemented invariants, traversal, insertion/removal, clear(), and boundary handling.
reflection.md — completed the Week 4 complexity and representation questions.
src/main.cpp — added a short local trace used while debugging.
```

### 3. Verification

State whether the required checks pass:

```text
ctest: passed
scripts/check-week04.sh: passed
```

If something does not pass, state that explicitly.

### 4. Blockers and challenges

Mention important technical or conceptual problems and how you addressed them.

If there were no significant blockers, write:

```text
No major blockers.
```

### 5. Incomplete work

Clearly identify anything that remains incomplete or incorrect. If all required work is complete, write:

```text
Required work complete.
```

## 12. Example Moodle submission

```text
Repository: https://github.com/<your-username>/RBS_BS0013_Data_Structures

Completed:
- src/int_linked_list.cpp — implemented the required singly linked-list operations and invariant checking.
- reflection.md — completed all required questions.
- Tested empty, one-node, middle, and tail transitions.

Verification:
- ctest: passed
- scripts/check-week04.sh: passed

Blockers/challenges:
- Initially forgot to update tail_ when removing the final successor; fixed after an invariant failure.

Incomplete work:
- Required work complete.
```

Keep the submission concise. It should document what you actually implemented, tested, and understood; it is not a formal report.
