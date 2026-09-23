#include "int_vector.hpp"

#include <stdexcept>

IntVector::~IntVector() {
    // TODO: release the owned array exactly once.
    delete[] data_;
    data_ = nullptr;
    size_ = 0;
    capacity_ = 0;
}

IntVector::IntVector(const IntVector& other) {
    (void)other;
    // TODO: allocate independent storage and copy the logical elements.
    data_ = new int[other.capacity_];
    size_ = other.size_;
    capacity_ = other.capacity_;
    for (size_t i = 0; i < size_; ++i) {
        data_[i] = other.data_[i];
    }
}

void IntVector::check_invariant() const {
    // TODO: assert the Week 3 representation invariants.
    assert(size_ <= capacity_);
    assert(size_ <= capacity_);
}

void IntVector::grow() {
    // TODO: geometric growth policy: 0 -> 1, otherwise double capacity.
    // Preserve size_ and all existing logical elements.
    if (capacity_ == 0) {
        capacity_ = 1;
    } else {
        capacity_ *= 2;
    }
    int* new_data = new int[capacity_];
    for (size_t i = 0; i < size_; ++i) {
        new_data[i] = data_[i];
    }
    delete[] data_;
    data_ = new_data;
}

void IntVector::push_back(int value) {
    (void)value;
    // TODO: grow only when size_ == capacity_, append, update size_,
    // and finish in a valid representation state.
    if (size_ == capacity_) {
        grow();
    }
    data_[size_++] = value;
}
