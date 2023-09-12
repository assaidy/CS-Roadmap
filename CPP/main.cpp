#include <algorithm>
#include <iostream>
#include <string>

template <class... Args>
void print(Args... args) {
    (std::cout << ... << args) << '\n';
}

int main() {
    print(1, " ali ", 1 + 5.5, " a");

    return 0;
}

