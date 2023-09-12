#include <iostream>
#include <stdexcept>

struct BanckAcount {
    int money {1000};
    bool PayBill(int bill_value) {
        if (bill_value < 0) {
            throw std::invalid_argument("Bill value can't be negative!");
        }
        if (money >= bill_value) {
            money -= bill_value;
            return true;
        }
        return false;
    }
};

int main() {
    BanckAcount acct;

    try {
        std::cout << acct.PayBill(100) << '\n';
        std::cout << acct.PayBill(500'000) << '\n';
        std::cout << acct.PayBill(-10) << '\n';
        std::cout << acct.PayBill(20) << '\n';
    } catch (std::invalid_argument &e) {
        std::cout << "Cought an exception: " << e.what() << '\n';
    }

    std::cout << "bye\n";

    return 0;
}
