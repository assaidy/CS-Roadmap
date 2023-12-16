#include "book_reader.h"

void BookReader::run() {
    int choice = BookReader::login_menu();
    if (choice == 1) BookReader::login();
    if (choice == 2) BookReader::signup();
}

int BookReader::login_menu() {
    int choice;
    std::cout
        << "\nMenu:\n"
        << "\t1- login.\n"
        << "\t2- signup.\n";

    while (true) {
        std::cout << "\nEnter number from range 1 - 2: ";
        std::cin >> choice;
        if (choice == 1 || choice == 2) {
            break;
        }
    }
    return choice;
}

bool BookReader::is_admin(std::string _username, int _password) {
    return (_username == BookReader::ADMIN_USERNAME)
        && (_password == BookReader::ADMIN_PASSWORD);
}

// return index of user, if not found => return -1
int BookReader::is_user(std::string _username, int _password) {
    if (!((int)BookReader::added_users.size())) return -1;
    for (int i = 0; i < (int)BookReader::added_users.size(); i++) {
        if (BookReader::added_users.at(i).get_username() == _username
            && BookReader::added_users.at(i).get_password() == _password)
            return i;
    }
    return -1;
}

void BookReader::login() {
    std::string tmp_username;
    int tmp_password{ 0 };

    while (true) {
        std::cout << "Enter username: ";
        std::cin >> tmp_username;
        std::cout << "Enter password: ";
        std::cin >> tmp_password;

        if (BookReader::is_admin(tmp_username, tmp_password)) {
            admin_view();
        }
        else if (int user_idx = BookReader::is_user(tmp_username, tmp_password); user_idx != -1) {
            user_view(user_idx);
        }
        else {
            std::cout << "[ERROR] wrong username or password. Try agin.\n";
        }
    }
}

void BookReader::signup() {
    User new_user;
    std::string tmp_str;
    int tmp_int{};

    std::cout << "Enter username: ";
    std::cin >> tmp_str;
    new_user.set_username(tmp_str);
    std::cout << "Enter password: ";
    std::cin >> tmp_int;
    new_user.set_password(tmp_int);
    std::cout << "Enter name: ";
    std::cin >> tmp_str;
    new_user.set_name(tmp_str);
    std::cout << "Enter email: ";
    std::cin >> tmp_str;
    new_user.set_email(tmp_str);

    added_users.push_back(new_user);
    user_view((int)BookReader::added_users.size() - 1); // last element
}

void BookReader::logout() {
    BookReader::run();
}

void BookReader::admin_view() {
    while (true) {
        std::cout
            << "\nMenu:\n"
            << "\t1- Add Book\n"
            << "\t2- logout\n";
        std::cout << "Enter a number from range 1 - 2: ";
        int choice;
        std::cin >> choice;

        if (choice == 1) BookReader::add_book();
        else BookReader::logout();
    }
}

// FIXME: USER PROBLEM: DOESN'T SAVE SESIONS 
// FIXME: BOOK PROBLEM: DOESN'T SAVE PROGRESS 
void BookReader::user_view(int _user_idx) {
    BookReader::current_user = BookReader::added_users.at(_user_idx);
    std::cout << "\nHello user " << current_user.get_name() << " | User View\n";

    int choice{};
    while (true) {
        std::cout
            << "\nMenu:\n"
            << "\t1- View Profile\n"
            << "\t2- List & Select from my reading history\n"
            << "\t3- List & Select from Available books\n"
            << "\t4- Logout\n";
        while (true) {
            std::cout << "\nEnter number from range 1 - 4: ";
            std::cin >> choice;
            if (1 <= choice && choice <= 4) break;
        }

        if (choice == 1) {
            std::cout << "name: " << current_user.get_name() << '\n';
            std::cout << "Email: " << current_user.get_email() << '\n';
            std::cout << "Username: " << current_user.get_username() << '\n';
        }
        else if (choice == 2) { // FIXME: ADD SELECTION
            current_user.list_sessions();
        }
        else if (choice == 3) {
            if ((int)BookReader::added_books.size() == 0) {
                std::cout << "==> No Books Yet.\n";
                continue;
            }
            for (int i = 0; i < (int)BookReader::added_books.size(); i++) {
                std::cout << "\t" << i + 1 << "- "
                    << BookReader::added_books.at(i).get_name() << '\n';
            }

            int selected_book_num;
            while (true) {
                std::cout << "\nEnter a number from range 1 - "
                    << (int)BookReader::added_books.size() << ": ";
                std::cin >> selected_book_num;
                if (1 <= selected_book_num && selected_book_num <= (int)BookReader::added_books.size()) break;
            }
            current_user.set_current_book(BookReader::added_books.at(selected_book_num - 1));

            // Book& current_book = current_user.get_current_book();
            while (true) {
                std::cout << "Current page: "
                    << current_user.get_current_book().get_current_page() + 1 << "/" << current_user.get_current_book().get_total_pages() << '\n';
                std::cout << current_user.get_current_book().get_page_title(current_user.get_current_book().get_current_page()) << '\n';

                std::cout
                    << "\nMenu:\n"
                    << "\t1- Next page\n"
                    << "\t2- Previous page\n"
                    << "\t3- Stop reading\n";
                std::cout << "\nEnter a number from 1 - 3: ";
                int choice;
                std::cin >> choice;
                if (choice == 1) current_user.get_current_book().next_page();
                else if (choice == 2) current_user.get_current_book().previous_page();
                else {
                    BookReader::stop_reading();
                    break;
                }
            }

        }
        else {
            BookReader::logout();
        }
    }
}

void BookReader::add_book() {
    int tmp_int{};
    std::string tmp_str;
    std::cout << "\nAdding Books:\n";
    Book new_book;
    std::cout << "Book name: ";
    std::cin >> tmp_str;
    new_book.set_name(tmp_str);
    std::cout << "Book id: ";
    std::cin >> tmp_int;
    new_book.set_id(tmp_int);
    std::cout << "Book Total Pages: ";
    std::cin >> tmp_int;
    new_book.set_total_pages(tmp_int);
    new_book.add_pages(new_book.get_total_pages());

    BookReader::added_books.push_back(new_book);
}

void BookReader::stop_reading() {
    BookReader::current_user.save_session();
}