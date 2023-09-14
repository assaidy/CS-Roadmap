#include <iostream>
#include "./projects/input/input.h"


int main() {
    bool test {
        input<std::string>("test: ").has_prefix("hel")
    };
    std::cout << test << '\n';

    // std::string prefix = "--foo=";
    // std::cout << std::string("--").compare(0, prefix.size(), prefix) << '\n';

    return 0;
}
