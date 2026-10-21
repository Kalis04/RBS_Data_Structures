#include "cargo_registry.hpp"
#include <cassert>
#include <iostream>
int main() {
    try {
        CargoRegistry r(7);
        assert(r.size()==0);
        assert(r.insert_or_assign(10,2));
        assert(r.insert_or_assign(17,4));
        assert(!r.insert_or_assign(17,9));
        assert(r.find(17) && *r.find(17)==9);
        assert(r.size()==2);
        assert(r.erase(10));
        assert(r.find(17) && *r.find(17)==9);
        r.rehash(11);
        assert(r.capacity()==11 && r.size()==1 && r.check_invariant());
        std::cout << "Basic checks passed\n";
    } catch(const std::exception& e) { std::cerr<<e.what()<<'\n'; return 1; }
}
