#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <wee.h>

struct data {
    std::string password{};
    std::string website{};
};

std::vector<data> record;

// function declarations
int main_menu();
void add_password();
void search_password();

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

int main() {
    while (true) {
        switch (main_menu()) {
            case 1:
                add_password();
                break;
            case 2:
                search_password();
                break;
            case 3:
                return 0;
            default:
                std::cout << "\nPlz enter a number from 1-2\n";
        } 
    }
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// function definitions
int main_menu() {
    system("clear");
    std::cout << "1) Add Password.\n";
    std::cout << "2) Search Password.\n";
    std::cout << "3) Exit.\n";

    int choice = get_int("\n-> Enter a number from 1-3: ");

    return choice;
}

void add_password() {
    data userInput{};
    std::cin.ignore();
    userInput.website  = get_string("\nWebsite: ");
    userInput.password = get_string("Password: ");

    record.push_back(userInput);

    std::cout << "\nEnter a key in the keyboard to Continue...";
    getchar();
}

void search_password() {
    std::cin.ignore();
    std::string keyword = get_string("\nEnter a search Keyword: ");

    // seraching for a string (keyword)
    /* auto it{std::find_if(record.begin(), record.end(), 
            [&keyword] (const data& recordData) {
            return recordData.website == keyword;}
            )};
    
    if (it != record.end()) {
        std::cout << "\nFound Website: " << it->website 
            << "\nFound Password: " << it->password << "\n";
    }
    else {
        std::cout << "\nWebsite Not Found\n";
    } */

    // search for a string (keyword) or substring.
    for (const auto &entry : record) {
        if (entry.website.compare(0, keyword.size(), keyword) == 0) {
            std::cout << "\nFound Website: " << entry.website 
                << "\nFound Password: " << entry.password << "\n";
            break;
        }
    }

    std::cout << "\nEnter a key in the keyboard to Continue...";
    getchar();
}
