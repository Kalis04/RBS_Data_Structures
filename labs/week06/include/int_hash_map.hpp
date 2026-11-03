#pragma once
#include <cstddef>
#include <vector>
enum class SlotState { Empty, Occupied, Deleted };
struct HashSlot { int key{}; int value{}; SlotState state{SlotState::Empty}; };
class IntHashMap {
public:
 explicit IntHashMap(std::size_t capacity);
 [[nodiscard]] std::size_t size() const noexcept { return size_; }
 [[nodiscard]] std::size_t capacity() const noexcept { return slots_.size(); }
 [[nodiscard]] bool empty() const noexcept { return size_ == 0; }
 [[nodiscard]] double load_factor() const noexcept;
 [[nodiscard]] bool contains(int key) const;
 int* find(int key);
 const int* find(int key) const;
 bool insert_or_assign(int key, int value);
 bool erase(int key);
 [[nodiscard]] std::size_t probe_count(int key) const;
 [[nodiscard]] bool check_invariant() const;
private:
 [[nodiscard]] std::size_t bucket(int key) const;
 [[nodiscard]] std::size_t find_index(int key) const;
 std::vector<HashSlot> slots_;
 std::size_t size_{0};
};
