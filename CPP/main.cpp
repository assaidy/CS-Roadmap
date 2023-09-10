#include <cctype>
#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> SearchByPrefix(
        std::vector<std::string> input,
        std::string prefix){

    bool valid {true};

    std::vector<std::string> result;
    for (const auto &word: input){
        valid = true;
        for (int i = 0; i < int(prefix.size()); i++){
            if (tolower(word.at(i)) != tolower(prefix.at(i))){
                valid = false;
                continue;
            }
        }
        if (valid) result.push_back(word);
    }

    return result;
}

int main() {
    // search by prefix
    std::vector<std::string> test {"hello", "hI", "hilla", "ahmad", "Ali"};

    auto res = SearchByPrefix(test, "Hi");
    
    for (const auto &word: res)
        std::cout << word << ' ';
    std::cout << '\n';

    return 0;
}
