#include <iostream>
#include <string>
// FIXME: #include "./projects/input/input.h"

int main() {
    int num1{}, num2{}, sum{};
    std::cin >> num1 >> num2;
    sum = num1 + num2;
    std::cout << sum << '\n';

    return 0;
}
