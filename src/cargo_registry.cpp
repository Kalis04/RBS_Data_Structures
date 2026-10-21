#include "cargo_registry.hpp"
#include <stdexcept>
#include <utility>
CargoRegistry::CargoRegistry(std::size_t capacity) : slots_(capacity) {
    if (capacity==0) throw std::invalid_argument("capacity must be positive");
}
bool CargoRegistry::check_invariant() const {
    std::size_t live=0;
    for (const auto& s:slots_) if (s.state==State::Occupied) {
        ++live;
        if(s.id<0) return false;
        const int* p=find(s.id);
        if(p!=&s.bay) return false; // detects duplicate IDs as well as unreachable entries
    }
    return live==size_;
}

std::size_t CargoRegistry::bucket(int id) const {
    if (id < 0) throw std::invalid_argument("cargo ID must be non-negative");
    return static_cast<std::size_t>(id) % capacity();
}
double CargoRegistry::load_factor() const noexcept {
    // capacity() >= 1 is guaranteed by the constructor, so no division by zero.
    return static_cast<double>(size_) / static_cast<double>(capacity());
}
const int* CargoRegistry::find(int id) const {
    std::size_t i = bucket(id);
    for (std::size_t steps = 0; steps < capacity(); ++steps) {
        const Slot& s = slots_[i];
        if (s.state == State::Empty) return nullptr;            // end of probe history
        if (s.state == State::Occupied && s.id == id) return &s.bay;
        // Deleted (tombstone) or a different live ID: keep probing
        i = (i + 1) % capacity();
    }
    return nullptr; // every slot inspected (no Empty slot): not present
}
bool CargoRegistry::insert_or_assign(int id, int bay) {
    std::size_t i = bucket(id);
    bool have_tomb = false;
    std::size_t first_tomb = 0;
    bool have_empty = false;
    std::size_t empty_idx = 0;
    for (std::size_t steps = 0; steps < capacity(); ++steps) {
        Slot& s = slots_[i];
        if (s.state == State::Empty) { have_empty = true; empty_idx = i; break; }
        if (s.state == State::Deleted) {
            if (!have_tomb) { have_tomb = true; first_tomb = i; } // remember, but keep probing
        } else if (s.id == id) {
            s.bay = bay;       // existing cargo: reroute, no new record
            return false;
        }
        i = (i + 1) % capacity();
    }
    // ID is absent. Prefer the first tombstone, otherwise the Empty slot.
    std::size_t target;
    if (have_tomb) target = first_tomb;
    else if (have_empty) target = empty_idx;
    else throw std::overflow_error("cargo registry is full");
    Slot& t = slots_[target];
    t.id = id; t.bay = bay; t.state = State::Occupied;
    ++size_;
    return true;
}
bool CargoRegistry::erase(int id) {
    std::size_t i=bucket(id);
    for(std::size_t steps=0;steps<capacity();++steps) {
        auto& s=slots_[i];
        if(s.state==State::Empty) return false;
        if(s.state==State::Occupied && s.id==id) {
            // B4 fix: leave a tombstone (Deleted), not Empty, so that cargo
            // placed later in this probe cluster stays reachable.
            s.state=State::Deleted;
            --size_; return true;
        }
        i=(i+1)%capacity();
    }
    return false;
}
void CargoRegistry::rehash(std::size_t new_capacity) {
    if (new_capacity == 0) throw std::invalid_argument("capacity must be positive");
    if (new_capacity < size_) throw std::invalid_argument("capacity smaller than live record count");
    CargoRegistry fresh(new_capacity);              // may throw; *this untouched until then
    for (const Slot& s : slots_)
        if (s.state == State::Occupied) fresh.insert_or_assign(s.id, s.bay); // only live records
    slots_.swap(fresh.slots_);
    size_ = fresh.size_;
}
