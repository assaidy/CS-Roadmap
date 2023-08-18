#include <cstddef>
#include <iostream>
#include <limits>


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// basic input() function like python
std::string input(std::string msg=""){
	std::cout << msg;
	std::string userInput{};
	std::getline(std::cin, userInput);
	return userInput;
}

int get_int(std::string msg=""){
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

float get_float(std::string msg=""){
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

double get_double(std::string msg=""){
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

char get_char(std::string msg=""){
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

std::string get_string(std::string msg=""){
	std::cout << msg;
	std::string userInput{};
	std::getline(std::cin, userInput);
	return userInput;
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// print new line
void newline(){
	std::cout << '\n';
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


