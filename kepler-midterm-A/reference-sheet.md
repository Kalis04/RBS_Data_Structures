# Midterm reference sheet

`std::vector<T>`: `size()`, indexed access, range-based iteration, and `swap`.

`std::invalid_argument`, `std::overflow_error`, `std::logic_error` are in `<stdexcept>`.

`nullptr` denotes a null pointer. `const int*` permits reading the referenced integer, not modifying it through this pointer.

`static_cast<double>(x)` converts before division. Unsigned integer arithmetic requires care at zero. `std::size_t` represents sizes and indices.

`assert(condition)` is available from `<cassert>` in the supplied Debug build. Include the operation itself outside an assertion if building with `NDEBUG` for another purpose.

Build: `cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug`, `cmake --build build`, `ctest --test-dir build --output-on-failure`.

No algorithm pseudocode or asymptotic answers are included on this sheet.
