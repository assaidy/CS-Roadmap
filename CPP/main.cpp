#include <iostream>
#include <wee.h>

int max(int a, int b, int c) {
    int maximum = a;
    if (maximum < b) maximum = b;
    if (maximum < c) maximum = c;
    return maximum;
}
int max(int a, int b, int c, int d) {
    if (max(a, b, c) >= d)
        return max(a, b, c);
    else
        return d;
}
int max(int a, int b, int c, int d, int e) {
    if (max(a, b, c, d) >= e)
        return max(a, b, c, d);
    else
        return e;
}
int max(int a, int b, int c, int d, int e, int f) {
    if (max(a, b, c, d, e) >= f)
        return max(a, b, c, d, e);
    else
        return f;
}

int main() {
    std::cout << max(10, 2, 9, 4, 5, 6) << '\n';

    return 0;
}
