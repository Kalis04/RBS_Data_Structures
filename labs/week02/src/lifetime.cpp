#include <iostream>

int main() {
    int value = 42;
    int* p = nullptr;

    std::cout << "initially null: " << std::boolalpha << (p == nullptr) << '\n';

    p = &value;
    if (p != nullptr) {
        std::cout << "live value: " << *p << '\n';
    }

    int* dangling = nullptr;
    {
        int temporary = 99;
        dangling = &temporary;
        std::cout << "inside scope: " << *dangling << '\n';
    }

    // TODO: Explain why dangling must not be dereferenced here.
    // Do not add: std::cout << *dangling;
    //temporary was destroyed when it went out of scope. dangling points to a dead object, so we can't dereference it.

    dangling = nullptr;
    std::cout << "dangling reset to null: " << (dangling == nullptr) << '\n';

    return 0;
}
