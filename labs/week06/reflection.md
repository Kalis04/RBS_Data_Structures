# Week 6 Reflection — Linear-Probing Hash Map

Answer briefly after your implementation works.

1. Under suitable hashing and controlled load, why are lookup, insertion, and deletion described as **expected Θ(1)** rather than worst-case Θ(1)?
2. Give a set of integer keys that all collide when the table capacity is 7. What happens to their probe lengths?
3. Why must lookup continue through a Deleted slot but may stop at an Empty slot?
4. Why must insert_or_assign continue probing after finding a tombstone before deciding to insert there?
5. Why does increasing the load factor usually increase successful and unsuccessful probe lengths?
6. Why can changing the table capacity require reinserting or rehashing every live key?
7. How is **expected Θ(1)** hash-table lookup different from **amortized Θ(1)** dynamic-array append?
8. Give one tradeoff between separate chaining and open addressing.
