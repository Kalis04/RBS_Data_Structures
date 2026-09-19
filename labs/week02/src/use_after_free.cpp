#include <iostream>

int main() {
    int* p = new int{42};
    delete p;

    // Intentionally invalid for the AddressSanitizer exercise.
    std::cout << *p << '\n';

    // TODO: In a comment, describe a correct lifetime/ownership repair.
    // Print the value BEFORE deleting, then delete and set p = nullptr.

    return 0;
}
