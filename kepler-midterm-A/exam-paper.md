# BS0013 Midterm — Variant A

**Week 7 · Scope: Weeks 1–6 · 100 points · nominal working time: 90 minutes**

This is individual supervised work. External AI, messaging, collaboration, and unapproved online resources are not permitted. Use the supplied workspace and the instructor-provided reference sheet. If the environment fails, notify the invigilator immediately rather than spending examination time repairing infrastructure.

Suggested time budget: **Part A 15 min, Part B 60 min, Part C 15 min.** You may work in another order. Preserve compilable work whenever possible. If a method is incomplete, describe the intended algorithm in `answers.md` for possible partial credit.

Submit the modified source, your student tests, and the completed `answers.md` through the announced course submission channel. Do not submit `build/`, executables, credentials, or a public GitHub repository.

---

## Part A — Systems warm-up (20 points)

Answer concisely in `answers.md`.

### A1 — Pointer lifetime after vector growth (5)

A `std::vector<int>` has size 8 and capacity 8. You store a pointer to its first element, then a successful `push_back` increases the size to 9.

1. May the old pointer safely be dereferenced after the operation? Why?
2. What is the time cost of this particular append?
3. How does that differ from the amortized cost of many appends under geometric growth?

### A2 — Circular cargo queue trace (5)

A circular queue has capacity 7, head index 4, and live size 2.

1. At which physical index will the next enqueue write?
2. After one dequeue followed by one enqueue, what are the head index and live size?
3. State the formula mapping logical position `j` to its physical index.

No resizing occurs.

### A3 — Deleted slot versus empty slot (5)

An initially empty linear-probing table has capacity 7. Insert IDs `10`, `17`, `24` in that order, then erase `10`.

1. List the occupied indices before deletion.
2. Explain why replacing the erased slot with `Empty` can make a later lookup of `24` fail.

### A4 — Linked-list deletion (5)

A singly linked list gives you a pointer to the node that must be deleted, but no pointer to its predecessor.

Is deletion always worst-case O(1)? Explain the head case, a general non-head case, and why “copy the successor value and delete the successor” is not a general solution.

---

# Part B — Kepler Station cargo registry (65 points)

## Incident briefing

It is 2187. **Kepler Station** is a transfer hub for cargo moving between Earth orbit, Luna, Mars, and the outer-system routes. Every cargo module has a non-negative integer transponder ID. Station Control stores the docking-bay code currently assigned to that cargo.

The registry was built for lower traffic. A new convoy is approaching, several cargo IDs collide in the registry, one departure routine has started corrupting searches, and Operations wants the table expanded before the next docking wave.

You have inherited a partially implemented C++ component:

```text
cargo ID
   |
   v
home slot = id % capacity
   |
   v
linear probe: home, home+1, home+2, ... with wrap-around
   |
   +--> Empty     : key is not beyond this point in this probe history
   +--> Occupied  : compare cargo ID
   +--> Deleted   : reusable slot, but lookup must continue
```

The supplied `CargoRegistry` uses `std::vector<Slot>`. Each slot is `Empty`, `Occupied`, or `Deleted`.

Registry rules:

- cargo IDs are non-negative integers;
- a cargo ID occurs at most once;
- a repeated ID means **reroute/update its bay**, not insert a duplicate;
- bay values may be any integer;
- `size()` counts only live occupied cargo records;
- a cargo record must remain reachable by its normal probe sequence;
- probing must always terminate after at most `capacity()` inspected slots;
- there is **no automatic resizing**; `rehash(new_capacity)` is an explicit operation.

Do not replace the implementation with `std::map` or `std::unordered_map`. Do not change the supplied public interface, public tests, or build rules.

## B1 — Registry coordinates (8 points)

Implement:

- `bucket(int id)`;
- `load_factor()`.

Requirements:

- negative IDs cause `std::invalid_argument`;
- otherwise the home slot is `id % capacity()`;
- load factor is `live entries / capacity` using floating-point division.

In `answers.md`, state the time and auxiliary-space complexity of both operations.

## B2 — Locate missing cargo (12 points)

Implement:

```cpp
const int* find(int id) const;
```

Return a pointer to the stored bay when the cargo exists, otherwise `nullptr`.

Your search must:

- begin at the cargo's home slot;
- wrap around the vector;
- stop at an `Empty` slot;
- continue through a `Deleted` slot;
- return only on an occupied slot with the matching ID;
- terminate after at most `capacity()` probes even when the table contains no `Empty` slot.

In `answers.md`, explain why `Deleted` cannot terminate search, then give expected and worst-case time plus auxiliary space.

## B3 — Register or reroute cargo (15 points)

Implement:

```cpp
bool insert_or_assign(int id, int bay);
```

Return:

- `true` if a new cargo ID was inserted;
- `false` if an existing cargo ID was found and its bay was updated.

Requirements:

- never create a duplicate ID;
- remember the first `Deleted` slot as a possible insertion position;
- **continue probing after that tombstone** in case the ID already exists later in the cluster;
- increment `size_` only for a genuinely new ID;
- if no `Empty` or reusable `Deleted` slot exists for a new ID, throw `std::overflow_error`;
- probing must remain bounded.

In `answers.md`, explain why inserting immediately into the first tombstone can create a duplicate. Give expected and worst-case time plus auxiliary space.

## B4 — Departure incident (10 points)

The supplied `erase(int id)` contains a deliberate logical bug. Repair it.

Requirements:

- return `true` exactly when a live cargo record is removed;
- return `false` if the ID is absent;
- decrement `size_` exactly once on successful removal;
- do not make later cargo in the same probe cluster unreachable;
- preserve bounded probing.

In `answers.md`:

1. identify the incorrect state transition;
2. give a concrete collision example showing the failure;
3. state the reachability invariant preserved by your repair;
4. give expected and worst-case time plus auxiliary space.

## B5 — Expand the station registry (15 points)

Implement:

```cpp
void rehash(std::size_t new_capacity);
```

Operations has approved a new registry capacity. Existing live cargo must be redistributed according to the new capacity.

Requirements:

- reject `new_capacity == 0`;
- reject capacities smaller than the number of live records;
- copy **only occupied records** into the rebuilt table;
- recompute placement using normal insertion/probing rules;
- preserve every live ID and bay;
- preserve the live count;
- a same-capacity rebuild is valid and should remove tombstones;
- shrinking exactly to the live count is allowed if all records can be placed;
- do not merely copy records to their old indices.

Recommended approach: build a temporary `CargoRegistry`, reinsert each live record through the existing insertion logic, and then replace/swap the representation.

In `answers.md`:

1. explain why old indices cannot simply be copied;
2. explain why a pointer previously returned by `find()` must not be retained across `rehash()`;
3. state the expected rebuild cost, a meaningful worst-case bound under heavy collision, and the auxiliary-space cost in terms of old capacity `m`, new capacity `m'`, and live entries `n`.

## B6 — Safety verification (5 points)

Add **two independent regression tests** in `tests/student_tests.cpp`.

Good tests target a specific failure mode rather than merely repeat the public smoke test. Examples of suitable themes include:

- update of an existing key when a tombstone occurs earlier in its probe sequence;
- unsuccessful lookup in a full table;
- wrap-around probing;
- same-capacity rehash removing tombstones;
- failed shrink leaving the original registry valid.

Do not assume these examples are the private tests.

For each test, write one sentence in `answers.md` identifying the incorrect implementation it is intended to detect.

---

# Part C — Post-incident engineering report (15 points)

Answer concisely in `answers.md`.

### C1 — Operational complexity (5)

The registry contains `n` live cargo records and `m` slots.

Explain when lookup can reasonably be described as expected O(1), what the worst-case probing cost is in this implementation, and why accumulated tombstones can make lookup slow even when the live load factor `n/m` is small.

### C2 — Two additional station workflows (5)

Station Control also needs:

1. cargo arrivals processed strictly in arrival order;
2. the ability to undo the most recent manual control correction first.

Choose an appropriate ADT for each workload, state the policy each ADT provides, and distinguish that ADT policy from a possible concrete representation. Explain why the cargo dictionary alone does not provide either ordering rule.

### C3 — Alternative collision representation (5)

Another engineer proposes replacing linear probing with **separate chaining** using linked nodes per bucket.

Compare the two representations with respect to:

- collision handling and deletion;
- memory allocation/pointer overhead;
- cache locality;
- expected versus worst-case lookup behavior.

A short structured comparison is sufficient.

---

## Final submission check

Before submitting:

1. build the project;
2. run the visible tests;
3. run your two student tests;
4. complete `answers.md`, including complexity and auxiliary-space statements;
5. record any unfinished method and intended algorithm rather than deleting partial work;
6. submit only the required source/text files through the announced private channel.

Visible tests are examples, not the complete grading specification. Correctness is judged against the stated contract and additional instructor tests.
