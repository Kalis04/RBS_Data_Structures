#include "int_linked_list.hpp"

#include <stdexcept>

namespace {
[[noreturn]] void todo(const char* operation) {
    throw std::logic_error(operation);
}
}  // namespace

IntLinkedList::~IntLinkedList() {
    clear();
}

int& IntLinkedList::front() {
    todo("TODO: implement front()");
}

const int& IntLinkedList::front() const {
    todo("TODO: implement front() const");
}

int& IntLinkedList::back() {
    todo("TODO: implement back()");
}

const int& IntLinkedList::back() const {
    todo("TODO: implement back() const");
}

void IntLinkedList::push_front(int value) {
    (void)value;
    todo("TODO: implement push_front()");
}

void IntLinkedList::push_back(int value) {
    (void)value;
    todo("TODO: implement push_back()");
}

void IntLinkedList::pop_front() {
    todo("TODO: implement pop_front()");
}

bool IntLinkedList::contains(int value) const noexcept {
    (void)value;
    return false;  // TODO
}

bool IntLinkedList::insert_after_first(int target, int value) {
    (void)target;
    (void)value;
    todo("TODO: implement insert_after_first()");
}

bool IntLinkedList::erase_after_first(int target) {
    (void)target;
    todo("TODO: implement erase_after_first()");
}

void IntLinkedList::clear() noexcept {
    // TODO: release every reachable node exactly once, then restore empty state.
    head_ = nullptr;
    tail_ = nullptr;
    size_ = 0;
}

bool IntLinkedList::check_invariant() const noexcept {
    // TODO: verify empty/non-empty state, reachability, tail, count, and no cycle.
    return size_ == 0 && head_ == nullptr && tail_ == nullptr;
}
