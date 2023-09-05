#pragma once

#include <cstddef>
#include <iostream>
#include <limits>
#include <regex>
#include <string>


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// basic input() function like python
std::string input(std::string msg = "") {
	std::cout << msg;
	std::string userInput{};
	std::getline(std::cin, userInput);
	return userInput;
}

int get_int(std::string msg = "") {
	int userInput{};

	while (true) {
		std::cout << msg;
		std::cin >> userInput;

		//Error Handling
		if (std::cin.fail()) {
			std::cerr << "==> Type Error: Please enter a value of type 'int' {1, 2, 3, 200}.\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		else
			break;
	}

	return userInput;
}

float get_float(std::string msg = "") {
	float userInput{};

	while (true) {
		std::cout << msg;
		std::cin >> userInput;

		//Error Handling
		if (std::cin.fail()) {
			std::cerr << "==> Type Error: Please enter a value of type 'flaot' {1, 2, 3.5, 200.9}.\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		else
			break;
	}

	return userInput;
}

double get_double(std::string msg = "") {
	double userInput{};

	while (true) {
		std::cout << msg;
		std::cin >> userInput;

		//Error Handling
		if (std::cin.fail()) {
			std::cerr << "==> Type Error: Please enter a value of type 'double' {1, 2, 3.5, 200.9}.\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		else
			break;
	}

	return userInput;
}

char get_char(std::string msg = "") {
	std::string userInput{};

	while (true) {
		std::cout << msg;
		std::cin >> userInput;

		//Error Handling
		if (std::size(userInput) > 1) {
			std::cerr << "==> Type Error: Please enter a value of type 'char' {'a', 'b', 'D'}.\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		else
			break;
	}

	char result = userInput[0];

	return result;
}

std::string get_string(std::string msg = "") {
	std::cout << msg;
	std::string userInput{};
	std::getline(std::cin >> std::ws, userInput);
	return userInput;
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// print new line
void newline() {
	std::cout << '\n';
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// remove white spaces around a string
std::string strip(std::string str = "") {
	str = std::regex_replace(str, std::regex("^\\s+|\\s+$"), "");
	return str;
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// helper function us in str_replace => check if the substring is exists or not
bool start_with(std::string input, std::string pattern, int position) {
    if (position + pattern.size() > input.size()) return false; // don't go beyond the "input" string
    for (int i = position, j = 0; j < size(pattern); i++, j++) {
        if (input[i] != pattern[j])
            return false;
    }
    return true;
}

// replace substrings
std::string str_replace(std::string input, std::string pattern, std::string to) {
    std::string result{};
    for (int i = 0; i < size(input); i++) {
        if (start_with(input, pattern, i)) {
            result += to;
            i += size(pattern) - 1;
        }
        else {
            result += input[i];
        }
    }
    return result;
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
