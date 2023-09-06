#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

// Helper Functions
std::vector<std::string> SplitString(std::string line, char delimiter = ',') {
    std::vector<std::string> result;
    std::string str;

    for (const auto& c : line) {
        if (c == delimiter) {
            result.push_back(str);
            str = "";
            continue;
        }
        str += c;
    }
    result.push_back(str);
    return result;
}

std::vector<std::string> ReadFileLines(std::string path) {
    std::vector<std::string> result;
    const auto status{ std::ios::in };
    std::fstream file_handler(path.c_str(), status);

    if (file_handler.fail()) {
        std::cout << "\n\nERROR: Can't open file: " << path << "\n\n";
        return result;
    }
    std::string line;

    while (getline(file_handler, line)) {
        if (line.size() == 0)
            continue;
        result.push_back(line);
    }
    file_handler.close();

    return result;
}

void WriteFileLines(std::string path, std::vector<std::string> lines, bool append = true) {
    auto status{ std::ios::in | std::ios::out | std::ios::app };

    if (!append)
        status = std::ios::in | std::ios::out | std::ios::trunc; // overwrite

    std::fstream file_handler(path.c_str(), status);

    if (file_handler.fail()) {
        std::cout << "\n\nERROR: Can't open file: " << path << "\n\n";
        return;
    }

    for (const auto& line : lines) {
        file_handler << line << '\n';
    }

    file_handler.close();
}

int ToInt(std::string str) {
    int num;
    std::istringstream iss(str);
    iss >> num;

    return num;
}

int ReadInt(int low, int high) {
    std::cout << "\nEnter number in range " << low << " - " << high << ": ";

    int value{};
    std::cin >> value;

    if (low <= value && value <= high) return value;

    std::cout << "\n\nERROR: Invalid number...Try again.\n";
    return ReadInt(low, high);
}



int main() {
    // std::string path{ "users.txt" };
    // std::vector<std::string> lines{ ReadFileLines(path) };
    // WriteFileLines("users.txt", lines);

    // for (const auto& str1 : lines) {
    //     for (const auto& str2 : SplitString(str1)) {
    //         std::cout << str2 << ' ';
    //     }
    //     std::cout << '\n';
    // }
    int num{ ReadInt(10, 20) };
    std::cout << num << '\n';

    return 0;
}