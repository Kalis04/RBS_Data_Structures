#pragma once

#include <cstddef>

class IntLinkedList {
public:
    IntLinkedList() = default;
    ~IntLinkedList();

    IntLinkedList(const IntLinkedList&) = delete;
    IntLinkedList& operator=(const IntLinkedList&) = delete;

    [[nodiscard]] bool empty() const noexcept { return size_ == 0; }
    [[nodiscard]] std::size_t size() const noexcept { return size_; }

    int& front();
    const int& front() const;
    int& back();
    const int& back() const;

    void push_front(int value);
    void push_back(int value);
    void pop_front();

    [[nodiscard]] bool contains(int value) const noexcept;
    bool insert_after_first(int target, int value);
    bool erase_after_first(int target);

    void clear() noexcept;

    // Development aid: checks representation consistency without exposing nodes.
    [[nodiscard]] bool check_invariant() const noexcept;

private:
    struct Node {
        int value;
        Node* next = nullptr;
    };

    Node* head_ = nullptr;
    Node* tail_ = nullptr;
    std::size_t size_ = 0;
};
