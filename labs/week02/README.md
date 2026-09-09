# BS0013 Week 2 Lab

Continue in the same Codespace used for Week 1.

From this directory:

```bash
cmake -S . -B build
cmake --build build
bash scripts/check-week02.sh
```

The normal build contains only safe programs. The intentionally unsafe AddressSanitizer demonstrations are opt-in targets:

```bash
cmake --build build --target use_after_free_asan
./build/use_after_free_asan

cmake --build build --target double_delete_asan
./build/double_delete_asan
```

Read `assignment.md` in this Week 2 folder for the required sequence and reflection questions.
