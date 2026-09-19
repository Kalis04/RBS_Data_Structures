# Week 3 Practical — Build a Dynamic Array

**BS0013 Data Structures**  
Riga Business School, Riga Technical University

## Purpose

Weeks 1 and 2 established values and references, pointers, dynamic storage, object lifetime, ownership responsibility, and memory diagnostics. This week combines those ideas into the first substantial data-structure implementation of the course: a simplified **dynamic array**.

The central question is:

> How can a contiguous sequence grow while preserving fast indexed access?

You will observe `std::vector`, implement an integer-specific `IntVector`, test its invariants at resizing boundaries, implement deep-copy construction, use sanitizers, and explain why geometric growth gives amortized constant-time append.

The goal is not to reproduce the complete Standard Library. The goal is to understand the representation and its trade-offs.

## Learning outcomes

By the end of the practical you should be able to:

- distinguish **logical size** from **allocated capacity**;
- state and preserve a dynamic-array representation invariant;
- explain why dynamic arrays use contiguous storage;
- implement geometric growth without losing elements or leaking storage;
- explain when reallocation invalidates pointers/references to elements;
- implement `push_back` and analyse its worst-case and amortized cost;
- implement a deep-copy constructor for a resource-owning class;
- use assertions, public tests, and AddressSanitizer/UBSan to check correctness;
- compare the teaching implementation with `std::vector`.

## Expected duration

Approximately **90 minutes**. Prioritize the core checklist before extensions.

---

# 1. Update your fork and open the Week 3 workspace

Continue using the same fork and Codespace as previous weeks. Before starting, commit any work you want to keep and follow the synchronization instructions in `README.md` in this Week 3 folder.

Then move to:

```bash
cd labs/week03
```

Configure and compile:

```bash
cmake -S . -B build
cmake --build build
```

The starter package is intentionally incomplete, but it should **compile**. Some final tests will fail until you implement the TODOs.

The important files are:

```text
include/int_vector.hpp       IntVector interface and representation
src/int_vector.cpp           functions you must implement
src/main.cpp                 small demonstration program
src/vector_growth.cpp        observe std::vector size/capacity
src/reallocation_demo.cpp    observe storage relocation
tests/public_tests.cpp       student-visible correctness checks
scripts/check-week03.sh      build + tests + sanitizer verification
reflection.md                short conceptual answers
```

---

# 2. Warm-up — observe `std::vector` growth

Run:

```bash
./build/vector_growth
```

The program prints `size()`, `capacity()`, and the address returned by `data()` after successive `push_back` operations.

Record when capacity changes and when the data address changes.

Answer in `reflection.md`:

1. Can `size()` be smaller than `capacity()`?
2. Can `size()` legally be greater than `capacity()`?
3. Does every `push_back` allocate a new block?
4. Why does a vector reserve storage it is not currently using?
5. What does `data()` identify?

Do **not** assume every Standard Library implementation uses exactly the same growth factor. The structural behavior matters more than the exact capacity sequence.

---

# 3. Reallocation and pointer validity

Run:

```bash
./build/reallocation_demo
```

The program reserves two elements, stores a pointer to the current allocation, and then appends another element that should require larger storage.

The demonstration deliberately **does not dereference the old pointer after reallocation**.

Explain in `reflection.md` why the old pointer becomes invalid in terms of **storage lifetime**. “The address changed” is an observation, not the underlying reason.

---

# 4. Understand the representation

Open `include/int_vector.hpp`.

`IntVector` stores three representation fields:

```text
IntVector object

    data_       size_       capacity_
      |           |             |
      |           |             +--> allocated slots
      |           +----------------> logical elements
      +----------------------------> contiguous storage
```

The required invariants are:

```text
0 <= size_ <= capacity_
capacity_ == 0  <=>  data_ == nullptr
```

When `capacity_ > 0`, `data_` points to one allocation containing `capacity_` `int` slots. The logical elements occupy `[0, size_)`. The remaining slots `[size_, capacity_)` are spare capacity, not logical elements.

Indexed access is constant time because the elements are contiguous and the address of element `i` is computed directly from the base address and `i`.

---

# 5. Implement `check_invariant()`

Open `src/int_vector.cpp` and implement:

```cpp
void IntVector::check_invariant() const;
```

Use assertions to encode the representation promises above.

At minimum check:

- `size_ <= capacity_`;
- zero capacity and `nullptr` agree with each other.

Call the invariant checker after mutating operations once those operations are implemented.

An invariant should describe what must be true at every externally observable stable state of the structure.

---

# 6. Implement the destructor

`IntVector` owns the array referred to by `data_`. Implement:

```cpp
IntVector::~IntVector();
```

The allocation must be released exactly once when the owning object is destroyed. Match the deallocation operation to the way the array was allocated.

The empty state must also be safe.

---

# 7. Implement geometric growth

Implement:

```cpp
void IntVector::grow();
```

Use the required teaching policy:

```text
if capacity_ == 0:
    new capacity = 1
otherwise:
    new capacity = 2 * capacity_
```

A correct growth operation performs this conceptual sequence:

```text
1. choose larger capacity
2. allocate a new contiguous array
3. copy the existing logical elements
4. release the old allocation
5. update data_
6. update capacity_
7. preserve size_
8. verify the invariant
```

For a full structure:

```text
size = 4, capacity = 4

[10][20][30][40]
```

one growth produces:

```text
size = 4, capacity = 8

[10][20][30][40][  ][  ][  ][  ]
```

Important: capacity growth does **not** itself add a logical element, so `size_` must remain unchanged during `grow()`.

---

# 8. Implement `push_back`

Implement:

```cpp
void IntVector::push_back(int value);
```

Required logic:

```text
if size_ == capacity_:
    grow()

store value at index size_
increment size_
check invariant
```

For the required doubling policy, predict the states before running tests:

| State | size | capacity |
|---|---:|---:|
| empty | 0 | 0 |
| after push 10 | ? | ? |
| after push 20 | ? | ? |
| after push 30 | ? | ? |
| after push 40 | ? | ? |
| after push 50 | ? | ? |

Pay particular attention to the transitions from capacities `1`, `2`, `4`, and `8`.

---

# 9. Run the public tests

After `grow()` and `push_back()` are implemented, run:

```bash
cmake --build build
ctest --test-dir build --output-on-failure
```

The public tests check basic behavior such as:

- empty state;
- size/capacity growth boundaries;
- element preservation after reallocation;
- mutable and const indexed access;
- deep-copy independence once the copy constructor is implemented.

Do not change tests merely to make an incorrect implementation pass.

---

# 10. Implement deep-copy construction

A raw owning pointer makes default member-wise copying unsafe. If two objects merely copied the same pointer value, both objects would believe they owned the same allocation.

Implement:

```cpp
IntVector::IntVector(const IntVector& other);
```

The copy must have **independent storage**.

After:

```cpp
IntVector a;
a.push_back(10);
a.push_back(20);

IntVector b = a;
b.at(0) = 999;
```

`a.at(0)` must still be `10`.

For this lab, preserve the source object's capacity as well as its size. Copy only the logical elements.

Copy assignment remains deliberately deleted; implementing the complete Rule of Five is beyond the required Week 3 scope.

Complexity of copy construction is `Theta(n)` in the number of logical elements, with `Theta(capacity)` newly allocated storage under this representation policy.

---

# 11. Run the complete verification script

When the core work is complete:

```bash
bash scripts/check-week03.sh
```

The script:

1. configures and builds the project;
2. runs the public tests;
3. recompiles the implementation and tests with AddressSanitizer and UndefinedBehaviorSanitizer;
4. runs the sanitized test binary.

Your completed core implementation should finish without sanitizer diagnostics.

If a sanitizer reports an error, classify the failure before patching code: out-of-bounds access, use-after-free, mismatched allocation/deallocation, double deletion, leak, or another lifetime violation.

---

# 12. Complexity analysis

Complete the complexity table in `reflection.md`.

For this implementation:

- `at(i)` is `Theta(1)`;
- `push_back` without growth is `Theta(1)`;
- one `push_back` that triggers reallocation is `Theta(n)` because existing elements are copied;
- a sequence of appends using geometric growth has **amortized `Theta(1)` per append**;
- copying an `IntVector` is `Theta(n)`.

Why amortized constant time? With doubling, expensive copies happen only after increasingly long runs of cheap appends. Across `n` appends from an empty vector, the number of copied elements is bounded by a geometric series:

```text
1 + 2 + 4 + ... < 2n
```

So the total work of `n` appends is `Theta(n)`, even though individual growth operations are `Theta(n)`.

Do not describe a reallocation-triggering append itself as constant time. **Worst-case** and **amortized** complexity are different claims.

---

# 13. Core completion checklist

Before finishing, verify all of the following:

- [ ] `vector_growth` and `reallocation_demo` were run and explained;
- [ ] representation invariants are encoded with assertions;
- [ ] destructor releases owned array storage correctly;
- [ ] `grow()` doubles capacity and preserves all logical elements;
- [ ] `push_back()` works across multiple capacity boundaries;
- [ ] `size_ <= capacity_` always holds;
- [ ] deep-copy construction creates independent storage;
- [ ] `ctest --test-dir build --output-on-failure` passes;
- [ ] `bash scripts/check-week03.sh` passes without sanitizer errors;
- [ ] `reflection.md` is completed;
- [ ] changes are committed to your fork.

---

# Optional extensions

Attempt these only after the core checklist passes.

1. **`pop_back()`** — reduce logical size without shrinking capacity. State preconditions and complexity.
2. **`reserve(new_capacity)`** — grow only when requested capacity exceeds current capacity. Explain pointer invalidation.
3. **Growth experiment** — compare doubling with a smaller growth factor and count total copied elements over many appends.
4. **Move semantics investigation** — without implementing it yet, explain why moving a resource-owning dynamic array can be much cheaper than deep copying it.

---

# Submission

Follow the Week 3 Moodle submission instructions when published. Keep your work in your fork and commit meaningful changes. The repository should compile from a clean Codespace checkout using the documented commands.
