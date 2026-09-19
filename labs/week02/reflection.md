# Week 2 Reflection

Answer briefly but precisely.

## 1. Pointer copying

Why does copying a pointer value not copy the pointed-to object?

Since pointer is a memory adress - number when it is copied, you copy the adress and not the object itself

## 2. Reachability versus lifetime

Explain how an object can still be alive but no longer reachable by traversing from a particular head pointer.

If the pointers to the object are deleted/changed the object only exists in memory but is not accessible anymore

## 3. Dangling pointers

When a pointer becomes dangling, what changed: the pointer's stored numeric value, the target object's lifetime, or necessarily both?

Only the lifetime changed as the pointers adress stays the same, but there is not an object there at that adress anymore

## 4. Ownership responsibility

Why can two pointers to one dynamically allocated object not both independently `delete` it?

After the first "delete" the object is ghone and memory freed so the second delete tries to delete something that does not exist and the system crashes

## 5. `nullptr`

Why does assigning `nullptr` to a raw pointer not release dynamically allocated storage?

Setting the pointer to nullptr just makes it point to nothing, does not free up the memmory that is taken. To free the memory you must "delete" first

## 6. Linked traversal complexity

Why is traversal of `n` linked nodes Θ(n) even though following one `next` pointer is Θ(1)?

Because traversing a list requires following however many pointers are in that list so it is n * 0(1) = 0(n) in total

## 7. Invariants

State two invariants that should hold for the final chain `10 -> 20 -> 25 -> 30 -> null`.

No broken links - every nodes next pointer is another node or nullptr
No cycles - starting from the first eventually reach nullptr
