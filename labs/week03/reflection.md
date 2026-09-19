# Week 3 Reflection — Dynamic Arrays

Complete this file briefly but precisely.

## 1. Size, capacity, and storage

1. Can `size()` be smaller than `capacity()`? Explain.
2. Why must `size()` never exceed `capacity()`?
3. Does every `push_back` allocate? What did `vector_growth` show?
4. What does `data()` identify?

## 2. Reallocation and pointer validity

Why can a pointer to an element become invalid after a capacity-changing `push_back`? Explain using **storage lifetime**, not only address changes.

## 3. Invariants

State the two representation invariants used by `IntVector`. Why is checking an invariant after every mutating operation useful?

## 4. Complexity

Fill in the table.

| Operation | Complexity | Why? |
|---|---|---|
| `at(i)` | | |
| `push_back` without growth | | |
| `push_back` that reallocates | | |
| `push_back` amortized over many appends | | |
| copy construction | | |

Why does doubling capacity give amortized constant-time append even though some individual appends are linear?

## 5. Deep copy

What would go wrong if copying `IntVector` only copied `data_`, `size_`, and `capacity_` member-by-member? Name at least two correctness/ownership problems.

## 6. STL comparison

Give one reason to use `std::vector<int>` in production code instead of this teaching implementation, and one reason implementing `IntVector` is still useful in a data-structures course.
