int main() {
    int* p = new int{42};
    int* q = p;

    delete p;

    // Intentionally invalid for the AddressSanitizer exercise.
    delete q;

    // TODO: In a comment, explain why two pointer variables do not imply two allocations.
    //p and q both point to the same memory location. They are just two different variables that hold the same address. delete p frees that one allocation. delete q tries to free it again, causing an error.

    return 0;
}
