#include "book_reader.h"
#include <assert.h>
#include <sstream>

std::string User::tostring(Book _current_book) { // book name + curPage/totalPages + date + time
    std::ostringstream oss;
    oss << _current_book.get_name() << " "
        << _current_book.get_current_page() << "/" << _current_book.get_total_pages() << "\n";

    return oss.str();
}

void User::save_session() {
    User::sessions.push_back(User::tostring(User::get_current_book()));
}

void User::list_sessions() {
    if ((int)User::sessions.size() == 0) {
        std::cout << "==> No Sesions Yet.\n";
    }
    for (const auto& session : User::sessions) {
        std::cout << session;
    }
}

void User::set_name(std::string _name) {
    User::name = _name;
}

void User::set_username(std::string _username) {
    User::username = _username;
}

void User::set_email(std::string _email) {
    User::email = _email;
}

void User::set_password(int _password) {
    User::password = _password;
}

void User::set_current_book(Book _current_book) {
    User::current_book = _current_book;
}

std::string User::get_name() {
    return User::name;
}

std::string User::get_username() {
    return User::username;
}

std::string User::get_email() {
    return User::email;
}

int User::get_password() {
    return User::password;
}

Book& User::get_current_book() {
    return this->current_book;
}