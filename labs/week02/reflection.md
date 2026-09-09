# Week 2 Reflection

Answer briefly but precisely.

## 1. Pointer copying

Why does copying a pointer value not copy the pointed-to object?

## 2. Reachability versus lifetime

Explain how an object can still be alive but no longer reachable by traversing from a particular head pointer.

## 3. Dangling pointers

When a pointer becomes dangling, what changed: the pointer's stored numeric value, the target object's lifetime, or necessarily both?

## 4. Ownership responsibility

Why can two pointers to one dynamically allocated object not both independently `delete` it?

## 5. `nullptr`

Why does assigning `nullptr` to a raw pointer not release dynamically allocated storage?

## 6. Linked traversal complexity

Why is traversal of `n` linked nodes Θ(n) even though following one `next` pointer is Θ(1)?

## 7. Invariants

State two invariants that should hold for the final chain `10 -> 20 -> 25 -> 30 -> null`.
