#pragma once
#include <iostream>
#include <vector>

class Book
{
private:
    std::string name;
    std::vector<std::string> pages_title;
    int id;
    int total_pages;
    int current_page;

public:
    Book(/* args */) {
        id = total_pages = current_page = 0;
        name = "";
    }
    void add_pages(int _total_pages);
    void print();
    bool next_page();
    bool previous_page();

    int get_id();
    int get_total_pages();
    int get_current_page();
    std::string get_name();
    std::string get_page_title(int _page_num);

    void set_id(int _id);
    void set_name(std::string _name);
    void set_current_page(int _pos);
};

class User
{
private:
    std::string name;
    std::string username;
    std::string email;
    int password;
    std::vector<Book> read_books;
    std::vector<std::string> sessions;
    std::string tostring(Book); // book name + curPage/totalPages + date + time
    Book current_book;

public:
    User(/* args */) {
        name = username = email = "";
        password = 0;
    }
    void save_session(std::string);
    void list_sessions();

    void set_name(std::string _name);
    void set_username(std::string _username);
    void set_email(std::string _email);
    void set_password(int _password);
    void set_current_book(Book _current_book);

    std::string get_name();
    Book get_current_book();
    std::string get_username();
    std::string get_email();
    int get_password();
};

class BookReader
{
private:
    std::vector<Book> added_books;
    std::vector<User> added_users;

public:
    BookReader(/* args */);
    void run();
    void login();
    void signup();
    void logout();
    void admin_view();
    void user_view();
    void add_book(const Book& _new_book);
    void stop_reading();
};