#include "password-generator.v0.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <wee.h>

struct data {
    std::string key{};
    std::string keyName{};
};

std::vector<data> record;

// function declarations
int main_menu();
void add_key();
void search_key();
void generate_key();

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

int main() {
    while (true) {
        switch (main_menu()) {
            case 1:
                add_key();
                break;
            case 2:
                search_key();
                break;
            case 3:
                generate_key();
                break;
            case 4:
                return 0;
            default:
                std::cout << "\nPlz enter a number from 1-4...";
                std::cin.ignore();
                getchar();
        } 
    }
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// function definitions
int main_menu() {
    system("clear");
    std::cout << "1) Add Password.\n";
    std::cout << "2) Search Password.\n";
    std::cout << "3) generate Password.\n";
    std::cout << "4) Exit.\n";

    int choice = get_int("\n-> Enter a number from 1-4: ");

    return choice;
}

void add_key() {
    data userInput{};
    std::cin.ignore();
    userInput.keyName  = get_string("\nkey Name: ");
    userInput.key = get_string("Key: ");

    record.push_back(userInput);

    std::cout << "\nEnter a key in the keyboard to Continue...";
    getchar();
}

void generate_key() {
    data userInput{};
    std::cin.ignore();
    userInput.keyName  = strip(get_string("\nkey Name: "));
    userInput.key = generator(userInput.keyName);

    record.push_back(userInput);

    std::cout << "\nEnter a key in the keyboard to Continue...";
    getchar();
}

void search_key() {
    std::cin.ignore();
    std::string keyword = strip(get_string("\nEnter a search Keyword: "));

    // TODO:
    // - [ ] sort the vector befor searching
    // - [ ] improve the search => binary search

    for (const auto& word : record) {
        if (std::regex_match(word.keyName, std::regex(keyword))) {
            std::cout << word.keyName << '\t' << word.key << '\n';
        }
    }

    std::cout << "\nEnter a key in the keyboard to Continue...";
    getchar();
}
