#include <iostream>
#include <algorithm>
#include <wee.h>

const int MAX_BOOKS{ 1000 };
const int MAX_USERS{ 1000 };
int added_books{};
int added_users{};
int borrowed_books{};

struct book {
    std::string name;
    int id;
    int quantity;
    int borrowed;

    book() {
        id = quantity = borrowed = 0;
        name = "";
    }

    book(int id_, std::string name_, int quantity_) {
        id = id;
        name = name_;
        quantity = quantity_;
        borrowed = 0;
    }
};

struct user {
    std::string name;
    int id;
    int borrowed;

    user() {
        id = borrowed = 0;
        name = "";
    }

    user(int id_, std::string name_) {
        id = id;
        name = name_;
        borrowed = 0;
    }
};

struct library_system {
    book books[MAX_BOOKS];
    user users[MAX_USERS];

    library_system() {
        added_books = 0;
        added_users = 0;
    }

    void run() {
        int choice{};
        while (true) {
            choice = menu();

            if (choice == 1)
                add_book();
            else if (choice == 2)
                print_library_by_id();
            else if (choice == 3)
                print_library_by_name();
            else if (choice == 4)
                add_user();
            else if (choice == 5)
                print_users();
            else
                break;
        }
    }

    int menu() {
        int choice{};
        while (true) {
            std::cout << "Main Menu: \n"
                "01) add book\n"
                "02) print library by id\n"
                "03) print library by name\n"
                "04) add user\n"
                "05) print users\n"
                "06) exit\n\n";

            choice = get_int("Enter a number [1 - 6]: ");
            if (0 >= choice || choice > 6) {
                std::cout << "Add valid number.\n\n";
                continue;
            }
            else
                return choice;
        }
    }

    void add_book() {
        int id_{}, quantity_{};
        std::string name_{};

        std::cout << "Enter book data (id, name, quantity): ";
        std::cin >> id_ >> name_ >> quantity_;

        // check if exists
        for (int i = 0; i < added_books; i++) {
            if (books[i].name == name_ || books[i].id == id_) {
                std::cout << "this user exists\n";
                return;
            }
        }

        books[added_books].id = id_, books[added_books].name = name_, books[added_books].quantity = quantity_;
        added_books++;
    }

    void print_books() {
        if (added_books <= 0)
            std::cout << "No books available\n\n";
        for (int i = 0; i < added_books; i++) {
            std::cout << "'id': " << books[i].id << ' '
                << "'name': " << books[i].name << ' '
                << "'quantity': " << books[i].quantity << ' '
                << "'borrowed': " << books[i].borrowed << '\n';
        }
    }

    static bool compare_id_book(book& b1, book& b2) {
        return b1.id < b2.id;
    }

    static bool compare_name_book(book& b1, book& b2) {
        return b1.name < b2.name;
    }

    void print_library_by_id() {
        std::sort(books, books + added_books, compare_id_book);
        print_books();
    }

    void print_library_by_name() {
        std::sort(books, books + added_books, compare_name_book);
        print_books();
    }

    void add_user() {
        int id_{};
        std::string name_{};

        std::cout << "Enter user data (id, name): ";
        std::cin >> id_ >> name_;

        // check if exists
        for (int i = 0; i < added_users; i++) {
            if (users[i].name == name_ || users[i].id == id_) {
                std::cout << "this user exists\n";
                return;
            }
        }

        users[added_users].id = id_, users[added_books].name = name_;
        added_users++;
    }

    static bool compare_id_users(user& u1, user& u2) {
        return u1.id < u2.id;
    }

    void print_users() {
        if (added_users <= 0)
            std::cout << "No users available\n\n";

        std::sort(users, users + added_users, compare_id_users);

        for (int i = 0; i < added_users; i++) {
            std::cout << "'id': " << users[i].id << ' '
                << "'name': " << users[i].name << ' '
                << "'borrowed': " << users[i].borrowed << '\n';
        }
    }

    void user_borrow_book() {
        std::cout << "enter user name, book name: ";
        std::string book_to_borrow{};
        std::string user_who_borrow{};

    }

    void user_return_book() {
        std::cout << "enter user name, book name: ";
        std::string book_to_return{};
        std::string user_who_return{};

    }

};

int main() {
    library_system my_library = library_system();
    my_library.run();

    return 0;
}

// user_borrow_book() => book.borrowed++; book.quantity--; user.borrowed++;
// user_return_book() => book.borrowed--; book.quantity++; user.borrowed--;
