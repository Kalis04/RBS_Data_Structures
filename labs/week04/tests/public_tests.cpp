#include "int_linked_list.hpp"

#include <cassert>
#include <iostream>
#include <stdexcept>

int main() {
    IntLinkedList list;
    assert(list.empty());
    assert(list.size() == 0);
    assert(list.check_invariant());

    list.push_back(10);
    assert(list.size() == 1);
    assert(list.front() == 10);
    assert(list.back() == 10);
    assert(list.check_invariant());

    list.push_back(20);
    list.push_back(40);
    list.push_front(5);
    assert(list.size() == 4);
    assert(list.front() == 5);
    assert(list.back() == 40);
    assert(list.contains(20));
    assert(!list.contains(99));
    assert(list.check_invariant());

    assert(list.insert_after_first(20, 30));
    assert(list.contains(30));
    assert(list.size() == 5);
    assert(list.check_invariant());

    assert(list.insert_after_first(40, 50));
    assert(list.back() == 50);
    assert(list.size() == 6);
    assert(list.check_invariant());

    assert(list.erase_after_first(30));  // removes 40
    assert(!list.contains(40));
    assert(list.size() == 5);
    assert(list.check_invariant());

    assert(list.erase_after_first(30));  // removes 50, so 30 becomes tail
    assert(list.back() == 30);
    assert(list.size() == 4);
    assert(list.check_invariant());

    assert(!list.erase_after_first(30));
    assert(!list.insert_after_first(999, 1));

    list.pop_front();
    assert(list.front() == 10);
    assert(list.size() == 3);
    assert(list.check_invariant());

    list.clear();
    assert(list.empty());
    assert(list.check_invariant());

    bool front_threw = false;
    try {
        (void)list.front();
    } catch (const std::out_of_range&) {
        front_threw = true;
    }
    assert(front_threw);

    bool pop_threw = false;
    try {
        list.pop_front();
    } catch (const std::out_of_range&) {
        pop_threw = true;
    }
    assert(pop_threw);

    std::cout << "Week 4 public tests passed.\n";
}
