#include <iostream>

int main() {
    int a = 10;
    int b = 20;

    int* p = &a;
    int* q = p;

    // TODO: Before running, complete this trace in comments:
    // step                  a    b    p points to    q points to
    // after declarations    10   20   a              a

    *q += 5;
    // after *q += 5         15   20   a             a

    p = &b;
    // after p = &b          15   20   b              a

    *p += 7;
    // after *p += 7         15   27   b              a

    // TODO: Explain why reassigning p did not also reassign q.
    //When reasigning p = &b only changes are that p points now to b, but q still is holding the stored adress of a. Q is not a pointer to p but it is a seperate pointer that points to a

    std::cout << "a = " << a << '\n';
    std::cout << "b = " << b << '\n';
    std::cout << "*p = " << *p << '\n';
    std::cout << "*q = " << *q << '\n';

    return 0;
}
