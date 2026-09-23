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
    //todo("TODO: implement front()");
    if (!head_) throw std::out_of_range("List is empty");
    return head_->value;
}

const int& IntLinkedList::front() const {
    //todo("TODO: implement front() const");
    if (!head_) throw std::out_of_range("List is empty");
    return head_->value;
}

int& IntLinkedList::back() {
    //todo("TODO: implement back()");
    if (!tail_) throw std::out_of_range("List is empty");
    return tail_->value;
}

const int& IntLinkedList::back() const {
    //todo("TODO: implement back() const");
    if (!tail_) throw std::out_of_range("List is empty");
    return tail_->value;  
}

void IntLinkedList::push_front(int value) {
    // todo("TODO: implement push_front()");
    Node* node = new Node{value, head_};
    head_ = node;
    if (size_ == 0) tail_ = head_;
    size_++;

}

void IntLinkedList::push_back(int value) {
    // todo("TODO: implement push_back()");
    Node* node = new Node{value, nullptr};
    if (size_ == 0) {
        head_ = node;
    } else {
        tail_->next = node;
    }
    tail_ = node;
    size_++;
}

void IntLinkedList::pop_front() {
    // todo("TODO: implement pop_front()");
    if (!head_) throw std::out_of_range("List is empty");
    Node* node = head_;
    head_ = head_->next;
    delete node;
    size_--;
    if (size_ == 0) tail_ = nullptr;
}

bool IntLinkedList::contains(int value) const noexcept {
    Node* current = head_;
    while (current) {
        if (current->value == value) {
            return true;
        }
        current = current->next;
    }
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
