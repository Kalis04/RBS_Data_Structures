#include "int_linked_list.hpp"

#include <iostream>
#include <stdexcept>

namespace {
void report(const char* step, const IntLinkedList& list) {
    std::cout << step << ": size=" << list.size()
              << ", invariant=" << std::boolalpha << list.check_invariant();
    if (!list.empty()) {
        std::cout << ", front=" << list.front() << ", back=" << list.back();
    }
    std::cout << '\n';
}
}  // namespace

int main() {
    IntLinkedList list;

    std::cout << "Week 4 linked-list lab\n";
    report("initial", list);

    list.push_back(20);               report("push_back(20)       [empty->one]", list);
    list.push_front(10);              report("push_front(10)      [10 20]", list);
    list.push_back(30);               report("push_back(30)       [10 20 30]", list);
    list.insert_after_first(10, 15);  report("insert_after(10,15) [10 15 20 30]", list);
    list.insert_after_first(30, 40);  report("insert_after(30,40) [tail moves]", list);
    list.erase_after_first(30);       report("erase_after(30)     [tail back to 30]", list);
    list.erase_after_first(10);       report("erase_after(10)     [10 20 30]", list);

    std::cout << "contains(20)=" << list.contains(20)
              << ", contains(99)=" << list.contains(99) << '\n';
    std::cout << "insert_after(99,1)=" << list.insert_after_first(99, 1)
              << ", erase_after(30)=" << list.erase_after_first(30) << '\n';

    list.pop_front();  report("pop_front()", list);
    list.pop_front();  report("pop_front()", list);
    list.pop_front();  report("pop_front()         [one->empty]", list);

    try {
        list.pop_front();
    } catch (const std::out_of_range& e) {
        std::cout << "pop_front() on empty threw: " << e.what() << '\n';
    }

    for (int i = 0; i < 1000; ++i) list.push_back(i);
    report("after 1000 push_back", list);
    list.clear();
    list.clear();                     // clearing twice must be safe
    report("after clear() x2", list);

    return 0;
}
