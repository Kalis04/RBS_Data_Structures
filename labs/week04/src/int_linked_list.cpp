#include "int_linked_list.hpp"
#include <cstddef>
#include <stdexcept>


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
    Node* current = head_;
    while (current) {
        if (current->value == target) {
            Node* new_node = new Node{value, current->next};
            current->next = new_node;
            if (current == tail_) {
                tail_ = new_node;
            }
            size_++;
            return true;
        }
        current = current->next;
    }
    return false;  // TODO

}

bool IntLinkedList::erase_after_first(int target) {
    Node* current = head_;
    while (current) {
        if (current->value == target) {
            Node* node_to_delete = current->next;
            if (node_to_delete) {
                current->next = node_to_delete->next;
                if (node_to_delete == tail_) {
                    tail_ = current;
                }
                delete node_to_delete;
                size_--;
                return true;
            }
            return false;  // No node to erase after target
        }
        current = current->next;
    }
    return false;  // Target not found
}

void IntLinkedList::clear() noexcept {
    // TODO: release every reachable node exactly once, then restore empty state.
    while (head_) {
        Node* node_to_delete = head_;
        head_ = head_->next;
        delete node_to_delete;
    }
    tail_ = nullptr;
    size_ = 0;
}

bool IntLinkedList::check_invariant() const noexcept {
    // TODO: verify empty/non-empty state, reachability, tail, count, and no cycle.
    if (size_ == 0) {
        return head_ == nullptr && tail_ == nullptr;
    }
    if (!head_ || !tail_ || tail_->next != nullptr) return false;

    const Node* current = head_;
    for (std::size_t i = 1; i < size_; ++i) {   
        current = current->next;
        if (!current) return false;            
    }
    return current == tail_ && current->next == nullptr;
}
