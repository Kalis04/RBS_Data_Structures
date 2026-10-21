#pragma once
#include <cstddef>
#include <vector>
enum class State { Empty, Occupied, Deleted };
struct Slot { int id=0; int bay=0; State state=State::Empty; };
class CargoRegistry {
public:
    explicit CargoRegistry(std::size_t capacity);
    std::size_t size() const noexcept { return size_; }
    std::size_t capacity() const noexcept { return slots_.size(); }
    double load_factor() const noexcept;
    const int* find(int id) const;
    bool insert_or_assign(int id, int bay);
    bool erase(int id);
    void rehash(std::size_t new_capacity);
    bool check_invariant() const; // supplied diagnostic, not a TODO
private:
    std::size_t bucket(int id) const;
    std::vector<Slot> slots_;
    std::size_t size_=0;
};
