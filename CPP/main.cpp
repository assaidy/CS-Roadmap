#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>


int main() {
    std::vector<int> v;
    v.reserve(50000); // reserve an initial capacity with 50000
    std::cout << v.capacity(); // return the capacity 50000


    return 0;
}
