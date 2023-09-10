#include <cctype>
#include <iostream>
#include <string>
#include <vector>

struct SpecialName {
    std::string name = "Ahmad";
    std::string &get_name() {return name;}
    void print() {std::cout << name << '\n';}
};

int main() {
    SpecialName name;
    name.print();

    std::string &str {name.get_name()};
    str = "Ziad";
    name.print();

    name.get_name() = "Ali";
    name.print();


    return 0;
}
