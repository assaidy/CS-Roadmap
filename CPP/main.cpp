#include <iostream>
#include <sstream>
#include <fstream>

int main() {
    std::ostringstream oss;
    oss << "Ahmad ";
    oss << 50;
    oss << " years\n";

    std::cout << oss.str();

    return 0;
}
