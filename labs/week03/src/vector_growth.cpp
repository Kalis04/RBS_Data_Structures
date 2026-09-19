#include <iostream>
#include <vector>

int main() {
    std::vector<int> values;

    std::cout << "size\tcapacity\tdata\n";

    for (int i = 0; i < 20; ++i) {
        values.push_back(i * 10);

        std::cout << values.size() << '\t'
                  << values.capacity() << '\t'
                  << static_cast<const void*>(values.data()) << '\n';
    }
}
