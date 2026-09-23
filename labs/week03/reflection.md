# Week 3 Reflection — Dynamic Arrays

Complete this file briefly but precisely.

## 1. Size, capacity, and storage

1. Can `size()` be smaller than `capacity()`? Explain.
Yes because capacity can be reserved for future reallocations
2. Why must `size()` never exceed `capacity()`?
Becouse it would be impossible to store the data if size exceeds capacity
3. Does every `push_back` allocate? What did `vector_growth` show?
vecto_growth shows that most of the push_back calls use the existing spare capacity, allocation happens only when size_ == capacity_
4. What does `data()` identify?
nullptr or the adress of the first element

## 2. Reallocation and pointer validity

Why can a pointer to an element become invalid after a capacity-changing `push_back`? Explain using **storage lifetime**, not only address changes.
Because when growth occurs a new larger allocation is obtained and the old allocation ends. Pointers to old elements now are allocated to free memory

## 3. Invariants

State the two representation invariants used by `IntVector`. Why is checking an invariant after every mutating operation useful?
`0 <= size_ <= capacity_` — logical size never exceeds allocated capacity.
`capacity_ == 0 ⟺ data_ == nullptr` — null pointer and zero capacity are consistent.
Checking aftyer every mutation can catch bugs early

## 4. Complexity

Fill in the table.

| Operation | Complexity | Why? |
|---|---|---|
| `at(i)` |Θ(1)|Direct address calculation: `base + i * sizeof(int)`|
| `push_back` without growth |Θ(1) |Store value at index and increment size. |
| `push_back` that reallocates |Θ(n) |Copy all n existing elements to new allocation. |
| `push_back` amortized over many appends |Θ(1) |Doubling means expensive copies happen after increasingly long runs of cheap appends. Total work across n appends is O(n), so average 0(1) |
| copy construction |Θ(n) |Allocate new storage and copy all n logical elements |

Why does doubling capacity give amortized constant-time append even though some individual appends are linear?
With geometric growth, reallocation happens at sizes 1, 2, 4, 8, 16, … With each reallocation, we copy the existing elements once. The total copies across n appends is `1 + 2 + 4 + … < 2n`, so amortized cost per append is O(n) / n = O(1)

## 5. Deep copy

What would go wrong if copying `IntVector` only copied `data_`, `size_`, and `capacity_` member-by-member? Name at least two correctness/ownership problems.
Aliasing / data corruption: Modifications through one object's pointer affect the other's elements, violating the independence property of a copy.
Dangling pointer: If the first object is destroyed before the second, the second's `data_` pointer becomes dangling (freed storage).

## 6. STL comparison

Give one reason to use `std::vector<int>` in production code instead of this teaching implementation, and one reason implementing `IntVector` is still useful in a data-structures course.
Reason to use `std::vector<int>` in production: Robustness, thorough testing, rich API (iterators, algorithms), exception safety guarantees
Reason implementing `IntVector`: Demonstrates why contiguous storage gives fast indexing and locality, how reallocation invalidates pointers 