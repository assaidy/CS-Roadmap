#include <limits.h>
#include <iostream>
#include <string>
#include "wee.h"

void cipher(std::string str){
    for (char &i : str){
        std::cout << int(i);
        if (i != str.back())
            std::cout << '-';
    }
}

void decipher(std::string str){
    std::string character{};

    for (char &i : str){
        if (i == '-'){
            std::cout << char(std::stoi(character));
            character = "";
            continue;
        }
        else{
            character += i;
        }
    }
    std::cout << char(std::stoi(character));
}

int main() {

    cipher(get_string("Cipher: "));

    newline();

    decipher(get_string("Decipher: "));

    newline();

    return 0;
}
