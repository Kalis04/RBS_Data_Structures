# Week 4 Reflection

Answer concisely after your implementation passes the public tests and sanitizer run.

1. Why can logical adjacency differ from physical address order in a linked list?
Each node is allocated seperately so it can be anywhere in the memmory. Order is defined by next pointers not by adresses
2. Why is numeric indexed access Θ(n) in a simple singly linked list?
Becouse nodes are not continuos so reching index "x" means following "next" "x" times
3. Under what precise precondition is insertion by pointer rewiring Θ(1)?
When a pointer to the node before the insertion point is already known
4. Why is `insert_after_first(target, value)` still Θ(n) in the worst case?
Becouse to find the target it may require going through the whole list 
5. What invariant responsibility is added by caching `tail_`?
tail_ must point to the last node and set it to nullptr when list becomes empty
6. Why must a removed node's successor be obtained before deleting the node?
Without saving the successor first the rest of the chain is lost
7. Give one structural bug that a memory sanitizer may not directly identify as a linked-list invariant violation.
A wrong size or a cycle among live nodes
8. Why can dynamic-array traversal outperform linked-list traversal even though both are Θ(n)?
Contiguous arrays are cache-friendly and easy to prefetch. Linked lists chase pointers to scattered nodes,which might result in missed cahes
9. Give one workload favoring the Week 4 representation and one favoring Week 3's dynamic array.
Linked list: frequent insert/remove at the front, like a job queue. Dynamic array: frequent indexed reads or full scans, like a lookup table.
10. How do these representation choices prepare you to implement stacks and queues next week?
`push_front` + `pop_front` gives a Θ(1) stack. `push_back` + `pop_front` with the cached `tail_` gives a Θ(1) queue.
