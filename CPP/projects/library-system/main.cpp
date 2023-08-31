#include <iostream>
#include <wee.h>

int main_menu() {
    while (true) {
        std::cout << "Library Menu: \n"
            "1)  Add book\n"
            "2)  Search books by prefix\n"
            "3)  Print who borrowed books by name\n"
            "4)  Print library by id\n"
            "5)  Print library by name\n"
            "6)  Add user\n"
            "7)  User borrow book\n"
            "8)  User return book\n"
            "9)  Print users\n"
            "10) Exit\n\n";

        int choice{ get_int("plz, Enter a number [1 - 10]: ") };

        if (0 >= choice || choice > 10) {
            continue;
        }
        else {
            return choice;
        }
    }
}

int main() {
    int choice{ main_menu() };
    std::cout << "Your choice : " << choice << '\n';

    return 0;
}