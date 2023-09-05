#include <iostream>
#include <fstream>

int main() {
    std::string path{ "names.txt" };
    std::fstream file_handler(path.c_str());

    if (file_handler.fail()) {
        std::cout << "Can't open the file\n";
        return 0;
    }
    std::string line;

    while (getline(file_handler, line)) {
        std::cout << line << '\n';
    }

    file_handler.close();

    return 0;
}
