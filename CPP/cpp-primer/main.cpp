#include <iostream>
#include <ostream>
#include <string>

int main() {
    int i{10};
    const int c{20};
    int *const cptr = &i;        // const pointer
    const int *const ccptr = &c; // const pointer to a const

    return 0;
}
