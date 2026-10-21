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

namespace { [[noreturn]] void todo(const char* task) { throw std::logic_error(task); } }
std::size_t CargoRegistry::bucket(int id) const {
    (void)id; todo("B1: validate ID and calculate home slot");
}
double CargoRegistry::load_factor() const noexcept {
    return 0.0; // B1 TODO: live entries / capacity, using floating-point division
}
const int* CargoRegistry::find(int id) const {
    (void)id; todo("B2: bounded probing with three slot states");
}
bool CargoRegistry::insert_or_assign(int id,int bay) {
    (void)id; (void)bay; todo("B3: distinguish insertion from update");
}
bool CargoRegistry::erase(int id) {
    std::size_t i=bucket(id);
    for(std::size_t steps=0;steps<capacity();++steps) {
        auto& s=slots_[i];
        if(s.state==State::Empty) return false;
        if(s.state==State::Occupied && s.id==id) {
            s.state=State::Empty; // B4: deliberate logical bug; explain and repair
            --size_; return true;
        }
        i=(i+1)%capacity();
    }
    return false;
}
void CargoRegistry::rehash(std::size_t new_capacity) {
    (void)new_capacity;
    // B5: validate capacity, build a replacement table, reinsert live records,
    // then swap representation and count. Reuse insert_or_assign.
    todo("B5: relocate records according to the new capacity");
}
