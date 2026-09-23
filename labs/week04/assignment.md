# Week 4 Practical — Build and Validate a Singly Linked List

**BS0013 Data Structures**  
Riga Business School, Riga Technical University

## Purpose

Week 3 used one contiguous allocation to represent a sequence. Week 4 changes the representation: each element lives in a separately allocated node, and logical order is encoded by explicit links.

The central question is:

> What do we gain and lose when sequence order is represented by pointers rather than physical adjacency?

You will implement a simplified integer singly linked list, preserve structural invariants, test boundary transitions, use sanitizers to detect lifetime errors, and compare the result with the Week 3 dynamic array.

## Learning outcomes

By the end of the practical you should be able to:

- explain logical adjacency versus physical address order;
- state and check linked-list representation invariants;
- traverse a singly linked structure safely;
- implement front/back insertion and front removal;
- distinguish navigation cost from local pointer-rewiring cost;
- update `head_`, `tail_`, and `size_` correctly across boundary cases;
- release an owned node chain without leaks or use-after-free;
- analyse operation complexity precisely;
- compare linked and contiguous representations beyond Big-O notation.

## Expected duration

Approximately **two academic hours (90 minutes)**. Complete the core checklist before attempting extensions.

---

# 1. Open and build the Week 4 workspace

After updating your fork, work in:

```bash
cd labs/week04
```

Configure and build:

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
```

The starter is intentionally incomplete, but it should compile before you implement the TODOs. The public tests will not pass until the required operations are complete.

Important files:

```text
include/int_linked_list.hpp       public interface and representation
src/int_linked_list.cpp           TODO implementation
src/main.cpp                      small operation-trace program
tests/public_tests.cpp            student-visible correctness checks
scripts/check-week04.sh           normal + sanitizer verification
reflection.md                     short conceptual answers
```

Do not change the public interface merely to make tests easier.

---

# 2. Read the representation before coding

The list stores:

```text
head_   -> first node
tail_   -> final node
size_   -> number of reachable nodes
```

Each node stores:

```cpp
struct Node {
    int value;
    Node* next = nullptr;
};
```

A possible physical layout is:

```text
address 0x5000: [10 | next=0x9000]
address 0x9000: [20 | next=0x3000]
address 0x3000: [30 | next=null]
```

The logical sequence is still:

```text
10 -> 20 -> 30
```

The nodes do **not** need to be adjacent in memory or ordered by address.

Before continuing, be able to explain why `next` represents topology while an address only identifies storage.

---

# 3. Representation invariants

For this implementation, a valid empty list satisfies:

```text
size_ == 0
head_ == nullptr
tail_ == nullptr
```

A valid non-empty list satisfies:

```text
size_ > 0
head_ != nullptr
tail_ != nullptr
tail_->next == nullptr
```

Starting at `head_` and repeatedly following `next` must also satisfy:

- exactly `size_` live nodes are reachable;
- no node is reached twice;
- the final reachable node is `tail_`.

These are not comments about typical behavior. They are representation obligations that every completed mutating operation must preserve.

---

# 4. Implement `check_invariant()`

The provided interface contains:

```cpp
[[nodiscard]] bool check_invariant() const noexcept;
```

Return `true` only when the representation is structurally consistent.

At minimum check:

- empty/non-empty metadata consistency;
- `tail_->next == nullptr` for a non-empty list;
- reachable-node count equals `size_`;
- the final reachable node is `tail_`;
- traversal does not loop forever if an accidental cycle exists.

You may use a cycle-detection technique or another bounded strategy that cannot hang on a malformed cyclic list.

Use this function after mutations while debugging. A list can print plausible values and still have a broken tail, wrong size, or cycle.

---

# 5. Implement `front()` and `back()`

Implement both mutable and const overloads.

Required behavior:

- on a non-empty list, return a reference to the first or last value;
- on an empty list, throw `std::out_of_range`.

Both operations should be Θ(1).

`back()` is Θ(1) specifically because this representation caches `tail_`. A singly linked list storing only `head_` would need traversal to find the final node.

---

# 6. Implement `push_front()`

For a non-empty list:

```text
before:
head
 |
 v
[20 | *] -> [30 | null]
                         ^
                         |
                       tail

after push_front(10):
head
 |
 v
[10 | *] -> [20 | *] -> [30 | null]
                                      ^
                                      |
                                    tail
```

Handle the empty-to-one-node transition as well. In that case `head_` and `tail_` must both refer to the new node.

Expected complexity: Θ(1).

---

# 7. Implement `push_back()`

Because `tail_` is stored, appending must not traverse the entire chain.

For a non-empty list:

```text
before:
head                         tail
 |                            |
 v                            v
[A | *] -> [B | *] -> [C | null]

after push_back(D):
head                                   tail
 |                                      |
 v                                      v
[A | *] -> [B | *] -> [C | *] -> [D | null]
```

Also handle the empty-to-one-node transition.

Expected complexity: Θ(1).

The cached tail is a deliberate time-space trade-off: one extra pointer and extra invariant bookkeeping buy constant-time append.

---

# 8. Implement traversal with `contains()`

Implement:

```cpp
[[nodiscard]] bool contains(int value) const noexcept;
```

Start at `head_`, follow `next`, and stop when either the value is found or the chain ends.

Complexity:

- best case: Θ(1);
- worst case: Θ(n);
- auxiliary memory: Θ(1).

This traversal pattern is fundamental to linked structures.

---

# 9. Implement `pop_front()`

Required behavior:

- on an empty list, throw `std::out_of_range`;
- otherwise remove exactly the first node;
- preserve the successor before deleting the old first node;
- decrement `size_`;
- if the removed node was the only node, restore `tail_ == nullptr`.

The safe lifetime ordering is conceptually:

```text
remember victim
remember/update successor
repair head metadata
delete victim
repair empty-state tail if needed
```

Do not read fields from a node after `delete`.

Expected complexity: Θ(1).

---

# 10. Implement `clear()` and verify destruction

The list owns an entire chain, not one allocation.

Implement:

```cpp
void clear() noexcept;
```

so that every reachable node is released exactly once and the object finishes in the valid empty state.

The destructor already calls `clear()`, so a correct `clear()` also gives correct destruction.

Test repeated clearing and destruction of:

- an empty list;
- a one-node list;
- a long list.

A sanitizer report is a defect even if the printed values look correct.

---

# 11. Implement `insert_after_first()`

Required behavior:

```cpp
bool insert_after_first(int target, int value);
```

1. search from `head_` for the first node whose value equals `target`;
2. if no such node exists, return `false`;
3. otherwise insert one new node immediately after it;
4. update `tail_` if insertion occurs after the current tail;
5. increment `size_`;
6. preserve all invariants;
7. return `true`.

Separate two costs:

- **navigation**: locating the target may require Θ(n);
- **mutation after a known node**: rewiring a constant number of pointers is Θ(1).

Therefore the complete public operation is Θ(n) in the worst case, even though the local insertion step is Θ(1).

---

# 12. Implement `erase_after_first()`

Required behavior:

```cpp
bool erase_after_first(int target);
```

1. find the first node whose value equals `target`;
2. return `false` if the target is absent;
3. return `false` if the target node has no successor;
4. otherwise remove exactly the successor node;
5. update `tail_` if the removed node was the tail;
6. decrement `size_`;
7. release the removed node exactly once;
8. preserve all invariants;
9. return `true`.

The lifetime rule is critical: obtain the successor information needed to repair the chain **before** deleting the node.

Worst-case complexity: Θ(n) because locating the target may require traversal.

---

# 13. Run public tests and sanitizers

After implementing the core operations:

```bash
cmake --build build
ctest --test-dir build --output-on-failure
```

Then run the full Week 4 check:

```bash
bash scripts/check-week04.sh
```

The script performs a normal build/test cycle and then repeats the tests with AddressSanitizer and UndefinedBehaviorSanitizer enabled.

Do not weaken `tests/public_tests.cpp` to make an incorrect implementation pass.

Useful failure classification:

```text
wrong value/order       -> traversal or rewiring logic
wrong size/tail         -> invariant bookkeeping
leak                    -> lost ownership / incomplete clear
use-after-free          -> invalid lifetime ordering
double free             -> duplicated ownership/deletion
cycle                   -> incorrect link assignment
```

---

# 14. Complexity summary

For the required representation:

| Operation | Expected complexity |
|---|---:|
| `empty()`, `size()` | Θ(1) |
| `front()`, `back()` | Θ(1) |
| `push_front()`, `push_back()` | Θ(1) |
| `pop_front()` | Θ(1) |
| `contains()` | Θ(n) worst case |
| rewiring after an already-known node | Θ(1) |
| `insert_after_first()` | Θ(n) worst case |
| `erase_after_first()` | Θ(n) worst case |
| numeric indexed access in a simple singly linked list | Θ(n) |
| full traversal | Θ(n) |
| `clear()` / destruction | Θ(n) |

Do not write “linked-list insertion is O(1)” without stating the precondition that the insertion position is already known.

---

# 15. Compare directly with Week 3

Complete the comparison in `reflection.md`.

| Property | Week 3 dynamic array | Week 4 singly linked list |
|---|---|---|
| physical layout | contiguous | separately allocated nodes |
| indexed access | Θ(1) | Θ(n) |
| append in this teaching representation | amortized Θ(1) | Θ(1) with `tail_` |
| local insertion after known position | may move Θ(n) elements | Θ(1) rewiring |
| traversal | Θ(n), strong locality | Θ(n), pointer chasing |
| per-element overhead | low | extra pointer per node |
| allocation pattern | occasional block allocation | allocation per inserted node |
| address stability | reallocation can invalidate | unrelated nodes generally stay put |

Big-O is necessary but not sufficient: cache locality, allocation overhead, pointer chasing, and constant factors matter.

---

# 16. Core completion checklist

Before attempting extensions, confirm:

- [ ] `check_invariant()` validates empty/non-empty state, reachability, count, tail, and cycles;
- [ ] `front()` and `back()` behave correctly and throw on empty;
- [ ] `push_front()` handles empty and non-empty lists;
- [ ] `push_back()` is Θ(1) and updates `tail_`;
- [ ] `contains()` traverses correctly;
- [ ] `pop_front()` handles many-node, one-node, and empty cases;
- [ ] `clear()` releases every reachable node and is safe on an already-empty list;
- [ ] `insert_after_first()` works in the middle and after the tail;
- [ ] `erase_after_first()` works in the middle and when removing the tail;
- [ ] `size_` agrees with reachable nodes after every operation;
- [ ] public tests pass;
- [ ] sanitizer tests report no errors;
- [ ] `reflection.md` is complete;
- [ ] changes are committed and pushed to your fork.

---

# Optional extensions

Attempt these only after the core checklist passes.

1. **Indexed access** — implement `at(index)` and explain why repeatedly calling it in a loop can accidentally create Θ(n²) work.
2. **Deep copy** — implement copy construction that creates an independent node chain.
3. **Move construction** — transfer `head_`, `tail_`, and `size_` and restore the source to a valid empty state.
4. **Generic list** — replace `int` with `template <typename T>`.
5. **Doubly linked nodes** — add `prev` and state the stronger bidirectional invariants.
6. **Sentinel design** — investigate which boundary cases become simpler and which invariants change.

These extensions connect to lecture material, but they are not required Week 4 work.

---

# Submission

Follow `instructions.md` for the Git workflow, verification commands, and Moodle submission format.

Keep the submission concise and factual: repository URL, work completed, verification status, blockers/challenges, and anything incomplete.
