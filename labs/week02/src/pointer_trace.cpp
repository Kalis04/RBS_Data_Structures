#include <iostream>

int main() {
    int a = 10;
    int b = 20;

    int* p = &a;
    int* q = p;

    // TODO: Before running, complete this trace in comments:
    // step                  a    b    p points to    q points to
    // after declarations    ?    ?    ?              ?

    *q += 5;
    // after *q += 5         ?    ?    ?              ?

    p = &b;
    // after p = &b          ?    ?    ?              ?

    *p += 7;
    // after *p += 7         ?    ?    ?              ?

    // TODO: Explain why reassigning p did not also reassign q.

    std::cout << "a = " << a << '\n';
    std::cout << "b = " << b << '\n';
    std::cout << "*p = " << *p << '\n';
    std::cout << "*q = " << *q << '\n';
}
