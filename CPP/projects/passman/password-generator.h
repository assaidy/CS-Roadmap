#pragma once
#include <vector>
#include <string>

std::string generator(std::string keyName="") {
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
	std::string key;
	for (int i = 0; i < 20; i++) {
		char token = tokens.at(0 + rand() % size(tokens));
		key += token;
	}
	key = key + "@" + keyName;

	return key;
}
