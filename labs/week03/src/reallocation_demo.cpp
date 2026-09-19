#include <iostream>
#include <vector>

int main() {
    std::vector<int> values;
    values.reserve(2);
    values.push_back(10);
    values.push_back(20);

    const int* old_data = values.data();

    std::cout << "before: " << static_cast<const void*>(old_data) << '\n';

    values.push_back(30);

    std::cout << "after:  "
              << static_cast<const void*>(values.data()) << '\n';

    std::cout << "old pointer is retained only as an address value for comparison; "
                 "it must not be dereferenced after reallocation.\n";
}
