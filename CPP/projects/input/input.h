#pragma once
#include <iostream>
#include <istream>
#include <vector>
#include <regex>
#include <stdexcept>
#include <string>

#ifndef INPUT_
#define INPUT_

template <class T>
struct input {
    T content;

    input(std::string msg = "", char range = 'w') {
        std::cout << msg;
        if ('w' == range)
            std::cin >> content;
        else if ('l' == range) {
            std::cin.ignore();
            std::getline(std::cin, content, '\n');
        }
    }

    std::vector<std::string> split() {
        std::vector<std::string> result;
        std::string token;
        if (typeid(content) == typeid(std::string)) {
            for (int i = 0; i < std::size(content); i++) {
                if (' ' == content.at(i)) {
                    result.push_back(token);
                    token.clear();
                    continue;
                }
                token += content.at(i);
            }
            result.push_back(token);
        } else {
            throw std::runtime_error("[ERROR] input must be of type 'std::string'\n");
        }
        return result;
    }

    bool has_prefix(std::string prefix) {
        if (typeid(content) == typeid(std::string)) {
            // return (std::string(content).rfind(prefix, 0) == 0);
            return (std::string(content).compare(0, (int)prefix.size(), prefix) == 0);
        }
        return false;
    }

    input strip() {
        content = std::regex_replace(content, std::regex("^\\s+|\\s+$"), "");
        return *this; // to allow method chaninig
    }

    T get() {
        return content;
    }
};

#endif // INPUT_
