int main() {
    int* p = new int{42};
    int* q = p;

    delete p;

    // Intentionally invalid for the AddressSanitizer exercise.
    delete q;

    // TODO: In a comment, explain why two pointer variables do not imply two allocations.
}
