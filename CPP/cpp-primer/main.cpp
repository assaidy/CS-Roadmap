#include <iostream>
#include "Sales_item.h"

int main() {

    Sales_item total;

    if (std::cin >> total) {

        Sales_item item;
        while (std::cin >> item) {
            if (total.isbn() == item.isbn()) {
                total += item;
            }
            else {
                std::cout << total << '\n';
                total = item;
            }
        }
        std::cout << total << '\n';
    }

    return 0;
}
