# BS0013 Data Structures

Public student materials for **BS0013 Data Structures** at Riga Business School, Riga Technical University.

## Course materials

- `syllabus/` — overall course syllabus;
- `lectures/` — weekly lecture materials as released;
- `quizzes/` — student self-check materials where published;
- `labs/week01/` — Week 1 practical;
- `labs/week02/` — Week 2 practical;
- `labs/week03/` — Week 3 dynamic-array practical.

## Use GitHub Codespaces

1. Fork this repository to your GitHub account.
2. Select **Code → Codespaces → Create codespace on main** in your fork.
3. Wait for the terminal to report `BS0013 environment ready.`
4. Weekly practicals are self-contained under `labs/weekNN/`.

The root development container provides Ubuntu, GCC, GDB, CMake, Git, and C++20 tooling for the course.

## Keep your fork up to date

Before starting a new week, commit any work you want to keep:

```bash
git status
git add .
git commit -m "Save work before course update"
```

If there is nothing to commit, Git will simply report that the working tree is clean.

Your fork normally has `origin` pointing to your own GitHub repository. Add the official course repository as `upstream` **once**:

```bash
git remote -v
git remote add upstream https://github.com/ValRCS/RBS_BS0013_Data_Structures.git
```

If `upstream` is already listed by `git remote -v`, do not add it again.

To bring newly released course material into your fork while preserving your commits:

```bash
git switch main
git fetch upstream
git merge upstream/main
git push origin main
```

A normal weekly update should merge cleanly because new material is usually added in new week folders. If Git reports a merge conflict, inspect `git status` and resolve the conflict before continuing; do not discard your previous lab work merely to obtain the update.

## Week 3

After synchronizing your fork:

```bash
cd labs/week03
cmake -S . -B build
cmake --build build
```

Then follow `labs/week03/README.md` and `labs/week03/assignment.md`.

Instructor notes, solutions, answer keys, private tests, and assessment rationale are maintained separately and are not part of this public repository.
