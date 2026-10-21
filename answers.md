# Midterm answers — Kepler Station

Variant: **A**

Notation: `n` = live records, `m` = current capacity, `m'` = new capacity.

## Part A — Systems warm-up

### A1 — Vector growth and pointer lifetime

1. **No.** Size 8 = capacity 8, so the 9th `push_back` must allocate a larger buffer, move/copy the elements across and free the old buffer. The saved pointer now dangles; dereferencing it is undefined behaviour.
2. This append costs **Θ(size) = O(n)** (here 8 element moves plus one allocation and one deallocation), not O(1).
3. With geometric growth (e.g. capacity doubles) such expensive appends are rare: the total copy work over N appends is at most 1+2+4+…+N/2 < N, so the **amortized** cost per append is **O(1)**, even though a single append can be O(n) in the worst case.

### A2 — Circular queue trace

Capacity 7, head 4, size 2.

1. Next enqueue writes at `(head + size) % capacity = (4 + 2) % 7 =` **6**.
2. Dequeue: head → `(4+1)%7 = 5`, size 1. Enqueue: size 2. Result: **head = 5, size = 2**.
3. Logical position `j` (0 = front) maps to physical index **`(head + j) % capacity`**.

### A3 — Deleted versus Empty

Capacity 7: 10 % 7 = 3, 17 % 7 = 3 → collides → slot 4, 24 % 7 = 3 → slots 3, 4 taken → slot 5.

1. Occupied indices before deletion: **3, 4, 5** (10 at 3, 17 at 4, 24 at 5).
2. If erasing 10 sets slot 3 back to `Empty`, a lookup of 24 starts at its home slot 3, sees `Empty`, and concludes "not present" – it never reaches slot 5. `Empty` means "no key ever probed past here", and that is now false. A `Deleted` tombstone says "something used to be here, keep probing", so 24 stays reachable.

### A4 — Singly linked-list deletion

No, not always O(1).
- **Head case:** if the given node is the head, set `head = head->next` and free it: worst-case O(1).
- **General non-head node:** the predecessor's `next` must be redirected, but we have no predecessor pointer; finding it needs a traversal from the head: **O(n)** worst case.
- **"Copy the successor's value into this node and delete the successor"** is O(1) but is not general: it fails for the **tail** node (no successor); it invalidates any outside pointer/iterator to the successor node (that node dies, while the node we meant to delete lives on); and it needs the value to be copyable/assignable (can be expensive or have side effects, and is impossible for non-copyable payloads).

---

## Part B — Kepler Station cargo registry

### B1 — Registry coordinates

`bucket` time: **O(1)** (a sign check and one modulo).

`bucket` auxiliary space: **O(1)**.

`load_factor` time: **O(1)** (`size_` is maintained incrementally; one floating-point division).

`load_factor` auxiliary space: **O(1)**.

### B2 — Locate missing cargo

Why must lookup continue through `Deleted`?
A `Deleted` slot is a tombstone for a record that was removed, but the removed record may have been the reason that later keys were pushed further along the cluster. Those keys were inserted while the slot was occupied, so they can sit beyond it. Stopping at `Deleted` would report live cargo as missing. Only `Empty` proves the key was never probed beyond that point. The loop is capped at `capacity()` probes so that a table with no `Empty` slot (only Occupied/Deleted) still terminates.

Expected time and assumptions: **O(1)** expected, assuming IDs spread roughly uniformly over the slots and the fraction of non-`Empty` slots (live + tombstones) is bounded away from 1 (e.g. ≤ ~0.5–0.7), so expected cluster length is constant.

Worst-case time: **O(m)** – up to `capacity()` probes (all keys collide in one cluster, or no `Empty` slot exists).

Auxiliary space: **O(1)**.

### B3 — Register or reroute cargo

Why is it incorrect to insert immediately into the first tombstone without checking farther in the probe sequence?
The ID might already exist later in the same cluster (it was placed there while the tombstone's slot was still occupied). Inserting into the earlier tombstone would create a **second record with the same ID** – a duplicate – and inflate `size_`; `find` would return the first one and the later record would be stale/shadowed. So the algorithm remembers the first tombstone, keeps probing until it finds the ID (update, return `false`) or an `Empty` slot / the end of the bounded probe (ID is absent), and only then inserts at the remembered tombstone (or the `Empty` slot if there was none). `size_` increases only on a genuine insert; if there is neither a tombstone nor an `Empty` slot, `std::overflow_error` is thrown.

Expected time and assumptions: **O(1)** expected under uniform spread and a load (live + tombstones) bounded away from 1.

Worst-case time: **O(m)** (at most `capacity()` probes).

Auxiliary space: **O(1)** (a few indices and flags).

### B4 — Departure incident

What was the supplied bug?
`erase` set the removed slot to `State::Empty` instead of `State::Deleted`. That is the incorrect state transition: Occupied → Empty destroys the probe history, whereas it must be Occupied → Deleted (tombstone).

Give a concrete collision/probe example showing how the buggy version can hide a live cargo record:
Capacity 7: insert 10 (home 3 → slot 3) and 17 (home 3 → collides → slot 4). `erase(10)` makes slot 3 `Empty`. Now `find(17)` starts at slot 3, sees `Empty`, and returns `nullptr` although 17 is live in slot 4 (`size()` is still 1, and `check_invariant()` fails). The same happens in `erase(17)` and `insert_or_assign(17, …)`, which would create a duplicate.

State the reachability invariant your repair preserves:
For every live (Occupied) record, every slot on its probe path from its home slot up to – but not including – the slot it occupies is non-`Empty` (Occupied or Deleted). Equivalently, `find(id)` reaches each live record, and `size_` equals the number of Occupied slots. Erase only changes Occupied → Deleted, which never turns a non-Empty slot into Empty, so the invariant is preserved.

Expected time and assumptions: **O(1)** expected with uniform spread and load (live + tombstones) bounded away from 1.

Worst-case time: **O(m)**.

Auxiliary space: **O(1)**.

### B5 — Station expansion

Why can live records not simply remain at their old slot indices after changing capacity?
The home slot is `id % capacity`, and probing wraps modulo capacity. With a different capacity, the home slots (and wrap-around points) change, so a record at its old index would no longer lie on its probe path from its new home slot – `find` would start elsewhere, stop at an `Empty` slot, and miss it. (E.g. 17 at slot 4 with m=7 has home 3, but with m'=11 its home is 6.) Every live record must be re-inserted under the new capacity with normal probing. Tombstones are dropped in the process, and rebuilding at the same capacity removes them.

Why must a pointer returned by `find()` not be retained across `rehash()`?
`find()` returns the address of `bay` inside the `std::vector<Slot>` storage. `rehash` builds a new vector and swaps it in; the old buffer is destroyed when the temporary registry goes out of scope, so any retained pointer dangles (undefined behaviour). Even if the storage were reused, the record would now be at a different slot.

Expected rebuild time (state assumptions and terms used):
**O(m + m' + n)**, which is O(m + m') since n ≤ m: allocate/initialise `m'` slots, scan the `m` old slots, and perform `n` insertions each of expected O(1) (uniform spread, new load `n/m'` bounded away from 1).

Meaningful worst-case time under heavy collision:
If all keys collide, the k-th reinsertion probes about k slots, so the `n` insertions cost 1+2+…+n = **O(n²)**, plus O(m + m') for the allocation/scan: **O(m + m' + n²)**.

Auxiliary space:
**O(m')** for the temporary replacement table (the old table of size `m` is still alive during the rebuild, so peak memory is O(m + m'); the old storage is freed after the swap). Only O(1) extra beyond the two tables.

Behaviour notes: `new_capacity == 0` and `new_capacity < size()` throw `std::invalid_argument`. The new table is fully built before it is swapped in, so a failed rehash leaves the original registry unchanged. Same-capacity rehash and shrinking to exactly `n` are valid (a full table is fine because insertion probing is bounded).

### B6 — Safety verification

Regression test 1: what scenario does it test, and what incorrect implementation should it catch?
`test_update_past_tombstone`: capacity 7, insert 10, 17, 24 (all home 3), erase 17 to leave a tombstone before 24, then `insert_or_assign(24, 99)`. It must return `false`, keep `size()==2`, update the bay and pass `check_invariant()`. It catches an implementation that inserts into the first tombstone without continuing to probe (creating a duplicate of 24 and returning `true`/over-counting size), and one that erases with `Empty` instead of `Deleted`. It then checks that a new ID (17) reuses the tombstone.

Regression test 2: what scenario does it test, and what incorrect implementation should it catch?
`test_full_table_bounded_and_wraparound`: capacity 3 filled with 2, 5, 8 (same home slot 2, so they wrap to slots 0 and 1). It checks wrap-around lookup, that `find`/`erase` of an absent ID in a table with no `Empty` slot terminate (return `nullptr`/`false`), that inserting a new ID into the full table throws `std::overflow_error` leaving `size()` unchanged, and that after erasing one record (only Occupied/Deleted slots remain) lookups of absent IDs still terminate. It catches unbounded `while(state != Empty)` probing loops (infinite loop on a table with no `Empty`), missing modulo wrap-around, and missing overflow handling.

---

## Part C — Post-incident engineering report

### C1 — Operational complexity and tombstones

Lookup is **expected O(1)** when the hash spreads IDs roughly uniformly (not adversarial or heavily patterned, e.g. IDs that are all multiples of `m`) and the table is kept well below full – for linear probing the expected probes are about ½(1+1/(1−α)) for hits and ½(1+1/(1−α)²) for misses, so constant for α bounded away from 1 (e.g. α ≤ ~0.7). Here there is no auto-resize, so this depends on Operations choosing/rehashing to a suitable capacity.

The **worst case is O(m)** in this implementation: all keys may fall in one cluster, or no `Empty` slot exists, so a lookup inspects up to `capacity()` slots before the bound stops it.

Tombstones count as non-`Empty` for probing, so lookups of absent keys (and of keys behind them) cannot stop at them. Many insert/erase cycles can leave most slots `Deleted`: the live load `n/m` is small, but the *effective* occupancy (live + tombstones) approaches 1, clusters grow long and unsuccessful lookups degrade towards O(m). A same-capacity `rehash` removes the tombstones and restores short probe sequences.

### C2 — Arrival-order processing and undo

1. **Arrivals in strict arrival order → Queue ADT**: FIFO policy – enqueue at the back, dequeue the oldest from the front.
2. **Undo most recent correction first → Stack ADT**: LIFO policy – push each correction, pop the latest to undo it.

An ADT specifies behaviour (which element comes out next), not storage. A queue can be implemented as a circular array (as in A2), a singly linked list with head and tail pointers, or a deque; a stack as a dynamic array with the top at the end, or a linked list with push/pop at the head. Each gives the same policy, with O(1) (amortized for the resizing array) operations but different memory and locality trade-offs.

The cargo dictionary maps ID → bay with lookup by key. Its iteration/slot order is determined by hash values and probing, not by when records were inserted, and rehash/erase reshuffle or recycle slots, so it keeps no record of arrival time or of the order of corrections. Neither FIFO nor LIFO order can be obtained from it without additional structure.

### C3 — Linear probing versus separate chaining

| Aspect | Linear probing (current) | Separate chaining |
|---|---|---|
| Collision handling | Colliding keys occupy the next free slots in the same array; clusters form and merge. Table can become full (insertion fails without resizing). | Colliding keys go into the bucket's linked list; the table never "fills" (load factor may exceed 1). |
| Deletion | Needs tombstones (or backward-shift) to keep probe paths intact; tombstones accumulate and need a rehash. | Simple: unlink the node (O(1) once found); no tombstones. |
| Memory / pointer overhead | One contiguous array of slots, no per-record allocation or pointers, but extra state field and spare capacity needed. | One heap allocation plus a `next` pointer per record, plus the bucket-head array; allocator overhead and fragmentation. |
| Cache locality | Excellent: probes walk adjacent memory. | Poor: following nodes scattered across the heap causes cache misses. |
| Expected lookup | O(1) expected for α bounded away from 1, but degrades quickly (≈1/(1−α)²) as α → 1 or with clustering. | O(1 + α) expected; degrades gracefully with load. |
| Worst-case lookup | O(m) (bounded by capacity here). | O(n) (one long chain). |

Chaining is more robust to high load and deletes more cleanly; linear probing is leaner and faster in practice at moderate load because of locality. Both have O(n)-type worst cases under adversarial collisions.

---

## Incomplete work / intended algorithms

None – all of B1–B6 are implemented; `bash scripts/check.sh` builds and passes `public_tests` and `student_tests` (also clean under the address/UB sanitizer build).
