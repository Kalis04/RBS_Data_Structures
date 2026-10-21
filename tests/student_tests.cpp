#include "cargo_registry.hpp"
#include <cassert>
#include <iostream>
#include <stdexcept>

// Regression 1: updating an existing key that lies beyond a tombstone in its
// probe sequence must update in place (no duplicate, size unchanged).
static void test_update_past_tombstone() {
    CargoRegistry r(7);
    assert(r.insert_or_assign(10, 1));   // home 3 -> slot 3
    assert(r.insert_or_assign(17, 2));   // home 3 -> slot 4
    assert(r.insert_or_assign(24, 3));   // home 3 -> slot 5
    assert(r.erase(17));                 // tombstone at slot 4, before 24
    assert(r.size() == 2);
    assert(!r.insert_or_assign(24, 99)); // must be an update, not an insert
    assert(r.size() == 2);
    assert(r.find(24) && *r.find(24) == 99);
    assert(r.find(17) == nullptr);
    assert(r.check_invariant());         // duplicate 24 would break this
    assert(r.insert_or_assign(17, 5));   // genuinely new: reuses the tombstone
    assert(r.size() == 3 && r.check_invariant());
}

// Regression 2: a table with no Empty slot (all Occupied/Deleted) must still
// terminate on unsuccessful lookup/erase/insert, and wrap-around must work.
static void test_full_table_bounded_and_wraparound() {
    CargoRegistry r(3);
    assert(r.insert_or_assign(2, 20));   // slot 2
    assert(r.insert_or_assign(5, 50));   // home 2 -> wraps to slot 0
    assert(r.insert_or_assign(8, 80));   // home 2 -> wraps to slot 1
    assert(r.size() == 3 && r.load_factor() == 1.0);
    assert(r.find(8) && *r.find(8) == 80);
    assert(r.find(11) == nullptr);       // must not loop forever
    assert(!r.erase(11));
    bool threw = false;
    try { r.insert_or_assign(11, 1); } catch (const std::overflow_error&) { threw = true; }
    assert(threw && r.size() == 3);
    assert(r.erase(5));                  // now a tombstone, still no Empty slot
    assert(r.find(11) == nullptr);       // bounded even with only tombstone/occupied
    assert(r.find(8) && *r.find(8) == 80);
    assert(r.check_invariant());
}

int main() {
    try {
        test_update_past_tombstone();
        test_full_table_bounded_and_wraparound();
        std::cout << "Student tests passed\n";
    } catch (const std::exception& e) { std::cerr << e.what() << '\n'; return 1; }
}
