# Week 6 Lab — Hash Table with Linear Probing

## Goal

Implement and test a small fixed-capacity dictionary using **open addressing with linear probing**. Focus on correctness invariants behind collision resolution rather than production-quality generic container design.

## Representation

IntHashMap uses three slot states: Empty, Occupied, and Deleted. Keys are non-negative integers. The preferred bucket is key modulo capacity. Linear probing checks successive slots and wraps at the end.

## Core invariant

> Every live key must remain discoverable by following its probe sequence from its preferred bucket.

Empty means lookup may stop. Occupied means compare the stored key. Deleted contains no live entry, but lookup must continue.

## Task 1 — Basic lookup

Implement bucket(), find_index(), both find() overloads, and contains(). A missing lookup must terminate after at most capacity() inspected slots.

## Task 2 — Insert or update

Implement insert_or_assign(int key, int value). Return true for a new key and false when updating an existing key.

When probing encounters a tombstone, remember it as a possible insertion position but continue until the existing key, an Empty slot, or the end of one full probe cycle. Otherwise an existing key later in the probe sequence could be duplicated.

If no Empty or reusable Deleted slot exists, throw std::overflow_error.

## Task 3 — Delete without breaking reachability

Implement erase(int key). Successful deletion changes the slot to Deleted, decrements size_, and returns true. Do not change it directly to Empty.

For capacity 7, keys 10, 17, and 24 all prefer bucket 3. After erasing 10, both 17 and 24 must remain discoverable.

## Task 4 — Wrap-around

With capacity 7, keys 6, 13, and 20 all prefer bucket 6. Their probe sequence must wrap through indices 6, 0, and 1. Verify lookup and deletion in this state.

## Task 5 — Probe count

Implement probe_count(int key). Count inspected slots until the key is found, Empty proves absence, or the entire table has been inspected.

## Task 6 — Invariant checker

Implement check_invariant(). At minimum verify that the number of Occupied slots equals size_, every occupied key is non-negative, and every occupied key is discoverable at that exact slot through the normal probe rule.

## Required tests

Your implementation should handle empty lookup, non-colliding insertion, collision chains, update without size growth, deletion inside a cluster, lookup across a tombstone, tombstone reuse, update when a tombstone appears before the existing key, wrap-around, and missing-key lookup at high load.

## Compare with std::unordered_map

Perform the same dictionary-level insertion, update, lookup, deletion, and size operations using std::unordered_map<int, int>. Compare observable semantics; do not assume the standard container uses this lab's collision representation.

## Complexity

Be prepared to explain expected Θ(1) operations under suitable hashing and controlled load, a Θ(n) collision pattern, the effect of load factor on probe length, why capacity changes require rehashing, and the distinction between expected complexity here and amortized dynamic-array growth.

Complete reflection.md after your implementation works.

## Optional extensions

Automatic resize and rehash; average probe measurements; tombstone accumulation experiments; separate chaining; or a generic templated version with a supplied hash function.
