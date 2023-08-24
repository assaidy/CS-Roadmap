#include <iostream>
#include <limits.h>

int main() {
    int a{}, max{ INT_MIN };

    std::cin >> a; // 1
    if (a > max) max = a;
    std::cin >> a; // 2
    if (a > max) max = a;
    std::cin >> a; // 3
    if (a > max) max = a;
    std::cin >> a; // 4
    if (a > max) max = a;
    std::cin >> a; // 5
    if (a > max) max = a;
    std::cin >> a; // 6
    if (a > max) max = a;
    std::cin >> a; // 7
    if (a > max) max = a;
    std::cin >> a; // 8
    if (a > max) max = a;
    std::cin >> a; // 9
    if (a > max) max = a;
    std::cin >> a; // 10
    if (a > max) max = a;

    std::cout << max << '\n';

    return 0;
}
