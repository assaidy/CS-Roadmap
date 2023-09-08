#include <iostream>
#include <algorithm>
#include <assert.h>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
#include <regex.h>
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
    password_data.push_back(str);
    assert(password_data.size() == 2);
    return password_data;
}

std::vector<std::string> ReadFileLines(std::string path) {
    std::vector<std::string> lines;

    const auto status{ std::ios::in };
    std::fstream file_handler(path, status);

    if (file_handler.fail()) {
        std::cout << "\n\nERROR: can't open file " << path << "\n\n";
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
        status = std::ios::in | std::ios::out | std::ios::app;
    }
    std::fstream file_handler(path, status);

    if (file_handler.fail()) {
        std::cout << "\n\nERROR: can't open file " << path << "\n\n";
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

    Password(std::string key_, std::string passwrod_) {
        key = key_;
        password = passwrod_;
    }

    std::string GenerateRandomPassword() {
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
        return password_;
    }

    std::string GenerateCompletePassword() {
        std::ostringstream oss;
        oss << key << "," << password << '\n';

        return oss.str();
    }

    void Print() {
        std::cout << "\n\t" << key << "\n\t" << password << '\n';
    }

    void Clear() {
        key = "";
        password = "";
    }
};

struct PassMan {
    Password new_password;
    std::vector<std::string> lines;
    std::pair<std::string, std::string> key_password_pairs;
    std::vector<Password> SystemPasswrods;


    PassMan() {
    }

    // for (const auto& line : lines) { // lines(vector of lines)
    //     // std::vector<std::string> key_password = SplitString(line);
    //     key_password_pairs.push_back(std::pair(SplitString(line).at(0), SplitString(line).at(1)));
    // }

    void LoadDatabase() {
        lines = ReadFileLines("passwords.txt");
        std::vector<std::string> key_password_vec;

        for (const auto& line : lines) {
            std::vector<std::string> key_password_vec = SplitString(line);
            key_password_pairs = std::pair(key_password_vec.at(0), key_password_vec.at(1));
            SystemPasswrods.push_back(Password(key_password_pairs.first, key_password_pairs.second));
        }
    }

    int Menu() {
        int choice = -1;
        while (-1 == choice) {
            std::cout << '\n'
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
        int choice{};

        while (true) {
            choice = Menu();

            switch (choice) {
            case 1: NewAutoPassword(); break;
            case 2: NewManualPassword(); break;
            case 3: SearchByKeyPrefix(); break;
            case 4: PrintAllKeys(); break;
            case 5: RemoveKeyByName(); break;
            default: return;
            }
        }
    }

    void NewAutoPassword() {
        LoadDatabase();

        // TODO: check if key is taken before

        std::cout << "\tkey: ";
        std::cin >> new_password.key;
        new_password.password = new_password.GenerateRandomPassword();

        WritFileLines(new_password.GenerateCompletePassword(), "passwords.txt");
        new_password.Clear();
    }

    void NewManualPassword() {
        LoadDatabase();

        // TODO: check if key is taken before

        std::cout << "\tkey: ";
        std::cin >> new_password.key;
        std::cout << "\tpassword: ";
        std::cin >> new_password.password;

        WritFileLines(new_password.GenerateCompletePassword(), "passwords.txt");
        new_password.Clear();
    }

    void SearchByKeyPrefix() {
        std::string keyword = get_string("\t\nenter a search keyword: ");
        // TODO:

    }

    void PrintAllKeys() {
        LoadDatabase();

        for (auto& pw : SystemPasswrods) {
            pw.Print();
        }
    }

    void RemoveKeyByName() {
    }

};

int main() {
    PassMan system;
    system.Run();

    return 0;
}