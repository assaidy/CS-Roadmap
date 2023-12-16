#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <assert.h>

/////////////////////// Helper Functions /////////////////////////////
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

int ReadMenu(std::vector<std::string> choices) {
    for (int i = 0; i < int(choices.size()); i++) {
        std::cout << '\t' << i + 1 << ": " << choices.at(i) << '\n';
    }
    return ReadInt(1, choices.size());
}
//////////////////////////////////////////////////////////////////////

struct Question {
    int question_id;
    int parent_question_id; // -1 => the first question in the thread
    int from_user_id;
    int to_user_id;
    int is_anonymous_question; // 0 or 1
    std::string question_txt;
    std::string question_answer;

    Question() {
        question_id = parent_question_id = from_user_id = to_user_id = -1;
        is_anonymous_question = 1;
    }

    Question(std::string line) {
        std::vector<std::string> substrs{ SplitString(line) };
        assert(int(substrs.size()) == 7);

        question_id = ToInt(substrs.at(0));
        parent_question_id = ToInt(substrs.at(1));
        from_user_id = ToInt(substrs.at(2));
        to_user_id = ToInt(substrs.at(3));
        is_anonymous_question = ToInt(substrs.at(4));
        question_txt = substrs.at(5);
        question_answer = substrs.at(6);
    }

    std::string ToString() {
        std::ostringstream oss;
        oss << question_id << "," << parent_question_id << "," << from_user_id << "," << to_user_id << "," << is_anonymous_question << "," << question_txt << "," << question_answer;
        return oss.str();
    }

    void PrintToQuestions() {
        std::string prefix{ "" };

        if (prefix != "") {
            prefix = "\tThread: ";
        }

        std::cout << prefix << "Question id (" << question_id << ")";
        if (!is_anonymous_question) {
            std::cout << " from user id (" << from_user_id << ")";
        }
        std::cout << "\tQuestion: " << question_txt << '\n';

        if (question_answer != "") {
            std::cout << prefix << "\tAnswer: " << question_answer << '\n';
        }
        std::cout << '\n';
    }

    void PrintFromQuestions() {
        std::cout << "Question id (" << question_id << ")";

        if (!is_anonymous_question)
            std::cout << " !AQ";

        std::cout << " to user id (" << to_user_id << ")";
        std::cout << "\tQuestion: " << question_txt;

        if (question_answer != "")
            std::cout << "\tAnswer: " << question_answer << '\n';
        else
            std::cout << "\tNot Answered Yet\n";
    }

    void PrintFeedQuestions() {
        if (parent_question_id != -1) {
            std::cout << "Thread Parent Question ID (" << parent_question_id << ")";
        }
        std::cout << " Question ID (" << question_id << ")";

        if (!is_anonymous_question) {
            std::cout << " from user id (" << from_user_id << ")";
        }
        std::cout << " to user id (" << to_user_id << ")";

        std::cout << "\tQuestion: " << question_txt << '\n';
        if (question_answer != "") {
            std::cout << "\tAnswer: " << question_answer << '\n';
        }
    }

};

struct User {
    int user_id;
    std::string user_name;
    std::string password;
    std::string name;
    std::string email;
    int allow_anonymous_questions; // 0 or 1

    std::vector<int> questions_id_from_me;
    // From question id to list of questions IDS on this question (thread questions) - For this user
    std::map<int, std::vector<int>> questionid_questionidsThead_to_map;

    User() {
        user_id = allow_anonymous_questions = -1;
    }

    User(std::string line) {
        std::vector<std::string> substrs{ SplitString(line) };
        assert(int(substrs.size()) == 6);

        user_id = ToInt(substrs.at(0));
        user_name = substrs.at(1);
        password = substrs.at(2);
        name = substrs.at(3);
        email = substrs.at(4);
        allow_anonymous_questions = ToInt(substrs.at(5));
    }

    std::string ToString() {
        std::ostringstream oss;
        oss << user_id << "," << user_name << "," << password << "," << name << "," << email << "," << allow_anonymous_questions;

        return oss.str();
    }

    void Print() {
        std::cout << "User " << user_id << ", " << user_name << " " << password << ", " << name << ", " << email << "\n";
    }
};

struct QuestionsManager {
    
};




int main() {
    /*     std::string path{ "users.txt" };
        std::vector<std::string> lines{ ReadFileLines(path) };
        WriteFileLines("users.txt", lines);

        for (const auto& str1 : lines) {
            for (const auto& str2 : SplitString(str1)) {
                std::cout << str2 << ' ';
            }
            std::cout << '\n';
        } */


    return 0;
}