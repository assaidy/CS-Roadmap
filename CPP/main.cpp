#include <algorithm>
#include <iostream>
#include <string>
#include "wee.h"

int sum_between(int a, int b);

int main() {

    std::cout << sum_between(5, 1) << '\n'; // 1 + 2 + 3 + 4 + 5 = 15
    
    return 0;
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

int sum_between(int a, int b) {
    if (a == b)
        return a;
    return std::min(a, b) + sum_between(std::min(a, b)+ 1, std::max(a, b));
    // 1 + sum(2, 5)
    // 2 + sum(3, 5)
    // 3 + sum(4, 5)
    // 4 + sum(5, 5)
    // 5
    // 4 + 5
    // 3 + 9
    // 2 + 12
    // 1 + 14 = 15
}
