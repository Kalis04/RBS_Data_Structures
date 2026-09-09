# Week 2 Practical — Pointers, Lifetime, and Linked Representation

**BS0013 Data Structures**  
Riga Business School, Riga Technical University

## Purpose

Week 1 established the development workflow and the distinction between values, copies, references, and containers. Week 2 moves closer to the representations we will use for dynamic arrays and linked structures.

The central question is:

> When a program stores an address, what must be true before that address may be used safely?

You will work with object addresses, raw pointers, `nullptr`, object lifetime, dynamic allocation, AddressSanitizer, and a small pointer-linked node chain.

The goal is not to master manual memory management. The goal is to reason explicitly about **reachability, lifetime, ownership, and structural invariants**.

## Learning outcomes

By the end of the lab you should be able to:

- distinguish a pointer from the object it points to;
- predict the effect of pointer copying and pointer reassignment;
- explain `nullptr` and dangling pointers;
- identify use-after-free, leak, and double-deletion errors;
- use AddressSanitizer to diagnose invalid memory use;
- traverse a simple node chain;
- rewire links without copying node values;
- state basic structural and lifetime invariants;
- analyse linear traversal as Θ(n) time and Θ(1) auxiliary space.

## 0. Start from your existing Codespace

Continue using the fork and Codespace you created in Week 1. After synchronizing your fork with the course repository, open:

```text
labs/week02/
```

The Week 2 folder already contains starter code. Do **not** recreate the repository or create a new Codespace unless the existing environment is unavailable.

Configure and build from the Week 2 directory:

```bash
cd labs/week02
cmake -S . -B build
cmake --build build
```

Run the public verification script at any time:

```bash
bash scripts/check-week02.sh
```

For deliberately unsafe programs, use the dedicated sanitizer targets described below.

---

# Task 1 — Pointer state tracing

Open:

```text
src/pointer_trace.cpp
```

Before running the program, complete the state table in the source comments.

Reason about this sequence:

```cpp
int a = 10;
int b = 20;
int* p = &a;
int* q = p;
*q += 5;
p = &b;
*p += 7;
```

Your trace must distinguish:

- the values stored in `a` and `b`;
- the address stored in `p`;
- the address stored in `q`;
- the object modified by `*p` or `*q`.

Then build and run:

```bash
./build/pointer_trace
```

Explain in a source comment why reassigning `p` does not reassign `q`.

---

# Task 2 — `nullptr` and lifetime

Open:

```text
src/lifetime.cpp
```

Complete the TODO comments without adding undefined behavior.

You should demonstrate these states:

```text
valid pointer -> live object
nullptr       -> no object
 dangling     -> old address, but lifetime ended
```

The crucial condition is:

> Before dereferencing `p`, `p` must identify a live object of the expected type.

Do not dereference a pointer after the target object's lifetime has ended.

Build and run:

```bash
./build/lifetime
```

---

# Task 3 — Dynamic allocation and ownership responsibility

Open:

```text
src/dynamic_value.cpp
```

Complete the missing cleanup logic so that:

1. exactly one `int` is dynamically allocated;
2. its value is changed through the pointer;
3. it is released exactly once;
4. the pointer is not dereferenced after deletion;
5. the pointer is set to `nullptr` after the release.

Then answer in `reflection.md`:

- Why does `p = nullptr;` not release an allocation?
- Why is `p = nullptr; delete p;` wrong when `p` is the only pointer to the allocation?

---

# Task 4 — Diagnose unsafe programs with AddressSanitizer

Two intentionally unsafe source files are provided:

```text
src/use_after_free.cpp
src/double_delete.cpp
```

They are excluded from the normal build because failure is part of the exercise.

Build the first sanitizer target:

```bash
cmake --build build --target use_after_free_asan
./build/use_after_free_asan
```

Inspect the AddressSanitizer report. Identify:

- the error category;
- the invalid-access line;
- the allocation site;
- the release site.

Repeat for:

```bash
cmake --build build --target double_delete_asan
./build/double_delete_asan
```

Do not merely remove the interesting line. In comments, describe a correct ownership/lifetime repair for each program.

You are not required to make the unsafe demonstration targets pass the normal verification script.

---

# Task 5 — Traverse a node chain

Open:

```text
src/node_chain.cpp
```

The starter representation is:

```text
10 -> 20 -> 30 -> null
```

The nodes have automatic storage duration. The pointers create links; they do not own the nodes.

Complete `print_chain(const Node* head)` so that traversal follows `next` until `nullptr`.

Use pointer-member syntax:

```cpp
current->value
current->next
```

Do not use indexing, arrays, or `std::vector` for this task.

---

# Task 6 — Rewire links

First modify links so that traversal from `a` becomes:

```text
10 -> 30 -> null
```

Do not change stored values. In a comment, explain why node `b` still exists even though it is no longer reachable from `a`.

Then restore the chain and insert the provided node `d{25}` so that traversal becomes:

```text
10 -> 20 -> 25 -> 30 -> null
```

The final submitted program should print:

```text
10 20 25 30
```

After insertion verify these invariants:

1. traversal from the head reaches every intended node exactly once;
2. the last node has `next == nullptr`;
3. no `next` pointer refers to an object whose lifetime has ended;
4. the operation changed links rather than copying node payload values.

---

# Task 7 — Complexity and reflection

Complete `reflection.md`.

For a chain of `n` nodes, state the complexity of:

```cpp
Node* current = head;
while (current != nullptr) {
    current = current->next;
}
```

Use precise terminology:

```text
time: Θ(n)
auxiliary traversal space: Θ(1)
```

The memory occupied by the nodes themselves is not auxiliary traversal storage.

---

# Verification

Run:

```bash
bash scripts/check-week02.sh
```

The public checks verify that the normal targets compile and that the final safe programs produce expected observable behavior. They are not a complete grading oracle.

Also inspect your Git status:

```bash
git status
```

Commit your Week 2 work to your own fork.

## Completion checklist

- [ ] pointer trace completed and explained;
- [ ] lifetime states explained without deliberately dereferencing a dangling pointer;
- [ ] dynamic allocation released exactly once;
- [ ] AddressSanitizer reports inspected for both unsafe demonstrations;
- [ ] linked traversal implemented;
- [ ] links rewired to insert node `25`;
- [ ] final chain prints `10 20 25 30`;
- [ ] reflection questions completed;
- [ ] public verification script passes;
- [ ] changes committed to your fork.

## Optional extension

Add:

```cpp
std::size_t chain_length(const Node* head);
```

without modifying the chain. State its time and auxiliary-space complexity.

A second extension is to write:

```cpp
const Node* find_value(const Node* head, int target);
```

and explain its best-case and worst-case running time.
