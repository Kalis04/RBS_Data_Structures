#include "int_vector.hpp"

#include <iostream>

int main() {
    IntVector values;

    for (int i = 0; i < 10; ++i) {
        values.push_back(i * 10);
        std::cout << "push " << i * 10
                  << " -> size=" << values.size()
                  << ", capacity=" << values.capacity() << '\n';
    }

    std::cout << "values: ";
    for (std::size_t i = 0; i < values.size(); ++i) {
        std::cout << values.at(i) << ' ';
    }
    std::cout << '\n';

    IntVector copy = values;
    copy.at(0) = 999;

    std::cout << "original first = " << values.at(0) << '\n';
    std::cout << "copy first     = " << copy.at(0) << '\n';
}
