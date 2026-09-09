#include <iostream>

struct Node {
    int value;
    Node* next = nullptr;
};

void print_chain(const Node* head) {
    // TODO: Traverse from head until nullptr and print each value followed by a space.
    (void)head;
}

int main() {
    Node a{10};
    Node b{20};
    Node c{30};
    Node d{25};

    a.next = &b;
    b.next = &c;

    // Task 6A: temporarily rewire so traversal from a is 10 -> 30 -> null.
    // Explain in a comment why b still exists even when unreachable from a.

    // Task 6B: restore and then insert d so the final chain is:
    // 10 -> 20 -> 25 -> 30 -> null
    // TODO: write the required link assignments here.

    print_chain(&a);
    std::cout << '\n';
}
