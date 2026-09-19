#include "int_vector.hpp"

#include <stdexcept>

IntVector::~IntVector() {
    // TODO: release the owned array exactly once.
}

IntVector::IntVector(const IntVector& other) {
    (void)other;
    // TODO: allocate independent storage and copy the logical elements.
    throw std::logic_error("TODO: implement IntVector copy construction");
}

void IntVector::check_invariant() const {
    // TODO: assert the Week 3 representation invariants.
}

void IntVector::grow() {
    // TODO: geometric growth policy: 0 -> 1, otherwise double capacity.
    // Preserve size_ and all existing logical elements.
    throw std::logic_error("TODO: implement IntVector::grow");
}

void IntVector::push_back(int value) {
    (void)value;
    // TODO: grow only when size_ == capacity_, append, update size_,
    // and finish in a valid representation state.
    throw std::logic_error("TODO: implement IntVector::push_back");
}
