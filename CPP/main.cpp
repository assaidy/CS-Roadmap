#include <algorithm>
#include <iostream>
#include <string>

double maxim = 0;

template <typename T>
double find_max(T t) {
    if (maxim < t)
        maxim = t;
    return maxim;
}

template <typename T, typename... Args>
double find_max(T t, Args... args) {
    if (maxim < t)
        maxim = t;
    return find_max(args...);
}

int main() {
    double max = find_max(1, 20, 15.5, 30.5, 30);
    std::cout << max << '\n';
    return 0;
}

