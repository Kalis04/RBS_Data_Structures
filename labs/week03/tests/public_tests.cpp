#include "int_vector.hpp"

#include <cstddef>
#include <iostream>

namespace {

int failures = 0;

void check(bool condition, const char* message) {
    if (!condition) {
        std::cerr << "FAIL: " << message << '\n';
        ++failures;
    }
}

void test_empty_state() {
    IntVector values;
    check(values.size() == 0, "empty vector has size 0");
    check(values.capacity() == 0, "empty vector has capacity 0");
}

void test_growth_boundaries() {
    IntVector values;

    const std::size_t expected_capacity[] = {1, 2, 4, 4, 8, 8, 8, 8, 16};

    for (std::size_t i = 0; i < 9; ++i) {
        values.push_back(static_cast<int>((i + 1) * 10));
        check(values.size() == i + 1, "push_back increments size exactly once");
        check(values.capacity() == expected_capacity[i],
              "capacity follows the required doubling policy");

        for (std::size_t j = 0; j <= i; ++j) {
            check(values.at(j) == static_cast<int>((j + 1) * 10),
                  "reallocation preserves existing elements");
        }
    }
}

void test_access_and_const_access() {
    IntVector values;
    values.push_back(3);
    values.push_back(6);
    values.push_back(9);

    values.at(1) = 60;
    check(values.at(1) == 60, "non-const at() returns a mutable reference");

    const IntVector& view = values;
    check(view.at(0) == 3, "const at() can read the first element");
    check(view.at(1) == 60, "const at() observes mutations");
    check(view.at(2) == 9, "const at() can read the last element");
}

void test_deep_copy() {
    IntVector original;
    for (int i = 0; i < 6; ++i) {
        original.push_back(100 + i);
    }

    const std::size_t original_capacity = original.capacity();
    IntVector copy = original;

    check(copy.size() == original.size(), "copy preserves size");
    check(copy.capacity() == original_capacity, "copy preserves capacity");

    for (std::size_t i = 0; i < original.size(); ++i) {
        check(copy.at(i) == original.at(i), "copy preserves logical elements");
    }

    copy.at(0) = 999;
    check(original.at(0) == 100, "copy has independent storage");
    check(copy.at(0) == 999, "copy can be modified independently");
}

}  // namespace

int main() {
    test_empty_state();
    test_growth_boundaries();
    test_access_and_const_access();
    test_deep_copy();

    if (failures != 0) {
        std::cerr << failures << " public check(s) failed.\n";
        return 1;
    }

    std::cout << "Week 3 public checks passed.\n";
    return 0;
}
