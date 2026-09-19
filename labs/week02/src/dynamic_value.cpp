#include <iostream>

int main() {
    int* p = new int{42};

    std::cout << "initial = " << *p << '\n';
    *p = 100;
    std::cout << "changed = " << *p << '\n';

    // TODO: release the allocation exactly once.
    delete p;
    // TODO: after release, make p explicitly represent no object.
    p = nullptr;

    return 0;
}
