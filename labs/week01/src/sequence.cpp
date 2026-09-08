#include <iostream>
#include <vector>

void print_values(const std::vector<int>& values) {
    for (int value : values) {
        std::cout << value << ' ';
    }
    std::cout << '\n';
    // TODO: print every value followed by a space, then print a newline.
}

int sum(const std::vector<int>& values) {
    int total = 0;
    for (int value : values) {
        total += value;
    }
    // TODO: calculate and return the sum of the values.
    return total;
}

void add_to_all(std::vector<int>& values, int amount) {
    for (int& value : values) {
        value += amount;
    }
    // TODO: add amount to every element.
}

int main() {
    std::vector<int> values{12, 7, 18, 4, 21, 9};

    std::cout << "Original: ";
    print_values(values);
    std::cout << "Sum: " << sum(values) << '\n';

    add_to_all(values, 5);

    std::cout << "Modified: ";
    print_values(values);
    std::cout << "New sum: " << sum(values) << '\n';
}
