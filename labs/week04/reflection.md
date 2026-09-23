# Week 4 Reflection

Answer concisely after your implementation passes the public tests and sanitizer run.

1. Why can logical adjacency differ from physical address order in a linked list?
2. Why is numeric indexed access Θ(n) in a simple singly linked list?
3. Under what precise precondition is insertion by pointer rewiring Θ(1)?
4. Why is `insert_after_first(target, value)` still Θ(n) in the worst case?
5. What invariant responsibility is added by caching `tail_`?
6. Why must a removed node's successor be obtained before deleting the node?
7. Give one structural bug that a memory sanitizer may not directly identify as a linked-list invariant violation.
8. Why can dynamic-array traversal outperform linked-list traversal even though both are Θ(n)?
9. Give one workload favoring the Week 4 representation and one favoring Week 3's dynamic array.
10. How do these representation choices prepare you to implement stacks and queues next week?
