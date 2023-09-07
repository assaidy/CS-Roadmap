#include <iostream>
#include <algorithm>
#include <assert.h>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
#include <wee.h>

///////////////////////////// Helper Functions ////////////////////////////
std::vector<std::string> SplitString(const std::string& line) {
    std::vector<std::string> password_data;
    std::string str;

    for (int i = 0; i < int(line.size()); i++) {
        if (line.at(i) == ',') {
            password_data.push_back(str);
            str = "";
            continue;
        }
        str += line.at(i);
    }
    assert(password_data.size() == 2);
    return password_data;
}

std::vector<std::string> ReadFileLines(std::string path) {
    std::vector<std::string> lines;

    const auto status{ std::ios::in };
    std::fstream file_handler(path, status);

    if (file_handler.fail()) {
        std::cout << "\n\nERROR: can't open file " << path << '\n\n';
    }
    std::string line;

    while (getline(file_handler, line)) {
        if (int(line.size()) != 0) {
            lines.push_back(line);
        }
    }

    file_handler.close();
    return lines;
}

void WritFileLines(std::string str, std::string path, bool append = true) {
    auto status{ std::ios::in | std::ios::out | std::ios::app };
    if (!append) {
        auto status{ std::ios::in | std::ios::out | std::ios::app };
    }
    std::fstream file_handler(path, status);

    if (file_handler.fail()) {
        std::cout << "\n\nERROR: can't open file " << path << '\n\n';
    }
    file_handler << str << '\n';

    file_handler.close();
}

///////////////////////////////////////////////////////////////////////////

struct Password {
    std::string password;
    std::string key;

    Password() {
        password = key = "";
    }

    void generate_random_password() {
        std::vector<char> tokens = {
            'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
            'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
            'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
            'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
            '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
            '@', '#', '$'
        };


        std::string password_;
        for (int i = 0; i < 20; i++) {
            char token = tokens.at(0 + rand() % size(tokens));
            password_ += token;
        }
        password = password_;
    }

    std::string generate_complete_password() {
        std::ostringstream oss;
        oss << password << "," << key << '\n';

        return oss.str();
    }

    void print() {
        std::cout << "\t" << key << "\t" << password << '\n';
    }
};

struct PassMan {
    std::map<std::string, std::string> key_to_password_map;

    PassMan() {
        std::vector<std::string> lines{ ReadFileLines("passwords.txt") };
    }

    void LoadDataBase() {

    }

    int Menu() {
        int choice = -1;
        while (-1 == choice) {
            std::cout
                << "\t1. new auto key\n"
                << "\t2. new manual key\n"
                << "\t3. search key by prefix\n"
                << "\t4. print all keys\n"
                << "\t5. remove key name\n"
                << "\t6. exit\n";

            choice = get_int("\t\nenter number in range 1 - 6: ");
            if (!(1 <= choice && choice <= 6)) {
                choice = -1;
            }
        }
        return choice;
    }

    void Run() {
        int choice = Menu();
        switch (choice) {
        case 1: NewAutoPassword(); break;
        case 2: NewManualPassword(); break;
        case 3: SearchByKeyPrefix(); break;
        case 4: PrintAllKeys(); break;
        case 5: RemoveKeyByName(); break;
        default: return;
        }
    }

    void NewAutoPassword() {

    }

    void NewManualPassword() {

    }

    void SearchByKeyPrefix() {

    }

    void PrintAllKeys() {

    }

    void RemoveKeyByName() {

    }

};

int main() {

    return 0;
}