#include "int_hash_map.hpp"
#include <cassert>
#include <stdexcept>
namespace {
[[noreturn]] void todo(const char* operation) { throw std::logic_error(operation); }
}
IntHashMap::IntHashMap(std::size_t capacity) : slots_(capacity) { assert(capacity > 0); }
double IntHashMap::load_factor() const noexcept { return static_cast<double>(size_) / static_cast<double>(capacity()); }
std::size_t IntHashMap::bucket(int key) const { assert(key >= 0); todo("TODO: implement bucket()"); }
std::size_t IntHashMap::find_index(int key) const { assert(key >= 0); todo("TODO: implement find_index()"); }
bool IntHashMap::contains(int key) const { return find(key) != nullptr; }
int* IntHashMap::find(int key) { (void)key; todo("TODO: implement find()"); }
const int* IntHashMap::find(int key) const { (void)key; todo("TODO: implement find() const"); }
bool IntHashMap::insert_or_assign(int key, int value) { (void)key; (void)value; todo("TODO: implement insert_or_assign()"); }
bool IntHashMap::erase(int key) { (void)key; todo("TODO: implement erase()"); }
std::size_t IntHashMap::probe_count(int key) const { (void)key; todo("TODO: implement probe_count()"); }
bool IntHashMap::check_invariant() const { todo("TODO: implement check_invariant()"); }
