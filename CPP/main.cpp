#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <system_error>
#include "wee.h"

template<class T>
void myswap(T &a, T &b);

int main() {


    return 0;
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

template<class T>
void myswap(T &a, T &b) {
    T tmp = a;
    a = b;
    b = tmp;
}

