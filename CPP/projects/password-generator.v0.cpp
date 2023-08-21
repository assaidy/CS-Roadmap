#pragma once
#include <iostream>

// TODO:
// - [X] make a vector of all the numbers/alphabets I want to include
// - [X] generate a random string

generate() {
	// get the name of the website/key
	std::string keyName {strip(get_string("Key Name: "))};

	// tokens container
	std::vector<char> tokens = {
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 
		'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 
		'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 
		'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 
		'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 
		'@', '#', '$'
	};

	// generate the password
	std::string password;
	for (int i = 0; i < 20; i++) {
		char token = tokens.at(0 + rand() % size(tokens));
		password += token;
	}
	password = password + "@" + keyName;

	std::cout << password << '\n';
}
