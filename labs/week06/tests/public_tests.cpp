#include "int_hash_map.hpp"
#include <cassert>
#include <iostream>
void test_empty_and_basic_insert(){ IntHashMap map(7); assert(map.empty()); assert(map.find(10)==nullptr); assert(map.insert_or_assign(10,100)); assert(map.size()==1); assert(map.contains(10)); assert(*map.find(10)==100); assert(map.check_invariant()); }
void test_collision_and_update(){ IntHashMap map(7); assert(map.insert_or_assign(10,100)); assert(map.insert_or_assign(17,170)); assert(map.insert_or_assign(24,240)); assert(map.probe_count(10)==1); assert(map.probe_count(17)==2); assert(map.probe_count(24)==3); assert(!map.insert_or_assign(17,171)); assert(map.size()==3); assert(*map.find(17)==171); assert(map.check_invariant()); }
void test_tombstone_preserves_lookup(){ IntHashMap map(7); map.insert_or_assign(10,100); map.insert_or_assign(17,170); map.insert_or_assign(24,240); assert(map.erase(10)); assert(!map.contains(10)); assert(map.contains(17)); assert(map.contains(24)); assert(map.size()==2); assert(map.check_invariant()); }
void test_wrap_around(){ IntHashMap map(7); map.insert_or_assign(6,60); map.insert_or_assign(13,130); map.insert_or_assign(20,200); assert(map.probe_count(6)==1); assert(map.probe_count(13)==2); assert(map.probe_count(20)==3); assert(map.contains(20)); assert(map.check_invariant()); }
int main(){ test_empty_and_basic_insert(); test_collision_and_update(); test_tombstone_preserves_lookup(); test_wrap_around(); std::cout<<"Week 6 public tests passed.\n"; }
