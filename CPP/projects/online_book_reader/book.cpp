#include "book_reader.h"
#include <assert.h>

void Book::add_pages(int _total_pages) {
    std::string page;
    for (int i = 1; i <= Book::get_total_pages(); i++) {
        std::cout << "Page # " << i << ": ";
        std::cin >> page;
        pages_title.push_back(page);
    }
}

void Book::print() {
    std::cout << "Current Page: " << Book::get_current_page() << "/" << Book::get_total_pages() << '\n';
    for (int i = 1; i <= Book::get_total_pages(); i++) {
        std::cout << Book::get_page_title(i) << '\n';
    }
}

bool Book::next_page() {
    if (Book::current_page == Book::get_total_pages()) return false;

    Book::current_page++;
    return true;
}

bool Book::previous_page() {
    if (Book::current_page == 0) return false;

    Book::current_page--;
    return true;
}

int Book::get_id() {
    return Book::id;
}

int Book::get_total_pages() {
    return Book::total_pages;
}

int Book::get_current_page() {
    return Book::current_page;
}

std::string Book::get_name() {
    return Book::name;
}

// pages starts form 1 => the vector starts from 0
std::string Book::get_page_title(int _page_num) {

    return pages_title.at(_page_num);
}

void Book::set_total_pages(int _total_pages) {
    Book::total_pages = _total_pages;
}

void Book::set_id(int _id) {
    Book::id = _id;
}

void Book::set_name(std::string _name) {
    Book::name = _name;
}

// current page starts from 1
void Book::set_current_page(int _pos) {
    assert(_pos > 0);
    assert(_pos <= Book::get_total_pages());

    Book::current_page = _pos;
}
