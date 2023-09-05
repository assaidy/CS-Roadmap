#include <iostream>
#include <map>

bool valid_brackets(std::string str) {
    std::map<char, char> p1;
    p1['('] = ')';
    p1['['] = ']';
    p1['{'] = '}';

    if (str == "") return true;
    if (str.size() % 2 != 0) return false;

    int size = int(str.size());
    for (int i = 0; i < size / 2; i++) {
        if (p1[str.at(i)] != str.at(size - i - 1))
            return false;
    }
    return true;

}

int main() {

    std::string exp1{ "([])" };
    std::string exp2{ "(])" };
    std::string exp3{ "([]" };
    std::string exp4{ "{]" };
    std::string exp5{ "" };

    std::cout << std::boolalpha;
    std::cout << valid_brackets(exp1) << '\n'; // true
    std::cout << valid_brackets(exp2) << '\n'; // false
    std::cout << valid_brackets(exp3) << '\n'; // false
    std::cout << valid_brackets(exp4) << '\n'; // false
    std::cout << valid_brackets(exp5) << '\n'; // true

    return 0;
}
