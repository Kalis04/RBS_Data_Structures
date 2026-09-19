#pragma once

#include <cassert>
#include <cstddef>

class IntVector {
public:
    IntVector() = default;
    ~IntVector();

    IntVector(const IntVector& other);
    IntVector& operator=(const IntVector& other) = delete;

    void push_back(int value);

    [[nodiscard]] std::size_t size() const noexcept {
        return size_;
    }

    [[nodiscard]] std::size_t capacity() const noexcept {
        return capacity_;
    }

    int& at(std::size_t index) {
        assert(index < size_);
        return data_[index];
    }

    const int& at(std::size_t index) const {
        assert(index < size_);
        return data_[index];
    }

private:
    int* data_ = nullptr;
    std::size_t size_ = 0;
    std::size_t capacity_ = 0;

    void grow();
    void check_invariant() const;
};
