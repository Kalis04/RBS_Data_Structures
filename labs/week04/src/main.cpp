#include "int_linked_list.hpp"

#include <iostream>

int main() {
    IntLinkedList list;

    std::cout << "Week 4 linked-list lab\n";
    std::cout << "Initial state: size=" << list.size()
              << ", invariant=" << std::boolalpha << list.check_invariant() << '\n';

    // Add your own operation traces here while implementing the lab.
    return 0;
}
