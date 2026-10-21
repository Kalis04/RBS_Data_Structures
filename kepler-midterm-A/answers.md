# Midterm answers — Kepler Station

Variant: **A / B** (circle or delete the one not assigned)

Keep answers concise but specific. Use `n` for live records, `m` for current capacity, and `m'` for a new capacity where useful.

## Part A — Systems warm-up

### A1 — Vector growth and pointer lifetime


### A2 — Circular queue trace


### A3 — Deleted versus Empty


### A4 — Singly linked-list deletion


---

## Part B — Kepler Station cargo registry

### B1 — Registry coordinates

`bucket` time:

`bucket` auxiliary space:

`load_factor` time:

`load_factor` auxiliary space:

### B2 — Locate missing cargo

Why must lookup continue through `Deleted`?

Expected time and assumptions:

Worst-case time:

Auxiliary space:

### B3 — Register or reroute cargo

Why is it incorrect to insert immediately into the first tombstone without checking farther in the probe sequence?

Expected time and assumptions:

Worst-case time:

Auxiliary space:

### B4 — Departure incident

What was the supplied bug?

Give a concrete collision/probe example showing how the buggy version can hide a live cargo record:

State the reachability invariant your repair preserves:

Expected time and assumptions:

Worst-case time:

Auxiliary space:

### B5 — Station expansion

Why can live records not simply remain at their old slot indices after changing capacity?

Why must a pointer returned by `find()` not be retained across `rehash()`?

Expected rebuild time (state assumptions and terms used):

Meaningful worst-case time under heavy collision:

Auxiliary space:

### B6 — Safety verification

Regression test 1: what scenario does it test, and what incorrect implementation should it catch?

Regression test 2: what scenario does it test, and what incorrect implementation should it catch?

---

## Part C — Post-incident engineering report

### C1 — Operational complexity and tombstones


### C2 — Arrival-order processing and undo


### C3 — Linear probing versus separate chaining


---

## Incomplete work / intended algorithms

List any unfinished method or test. Describe the intended algorithm precisely enough to show what you were trying to implement. Preserve your best compilable code rather than deleting partial work.
