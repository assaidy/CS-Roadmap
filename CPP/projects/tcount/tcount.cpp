#include <algorithm>
#include <cstdlib>
// #include <curses.h>
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <vector>
#include <regex>

void error_msg() {
    std::cout << 
        "Usage: tcount [DURATION]\tDURATION: '$h $m $s'\n"
        "Usage: tcount\n";
}

std::vector<int> get_timer_data(std::string str) {
    std::vector<int> result;
    result.reserve(3);
    std::string tmp;
    for (const auto c: str) {
        tmp += c;
        if (c == 'h' || c == 'm' || c == 's') {
            result.push_back(std::stoi(tmp));
            tmp.clear();
        }
    }

    return result;
}

int main(int argc, char *argv[]) {
    int seconds = 0;
    int minutes = 0;
    int hours = 0;

    // NOTE: COUNTER
    if (1 == argc) {
        while (true) {
            if (seconds == 60) {
                minutes++;
                seconds = 0;
            }
            if (minutes == 60) {
                hours++;
                minutes = 0;
            }
            std::cout << hours << ":" << minutes << ":" << seconds++ << "\r" << std::flush;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }

    // NOTE: TIMER
    else if (2 == argc) {
        std::string user_arg_str = argv[1]; // $h $m $s
        if (!(std::regex_match(user_arg_str, std::regex("\\d+h \\d+m \\d+s")))) {
            error_msg();
            return 1;
        }
        std::vector<int> timer_data {get_timer_data(user_arg_str)};
        hours = timer_data.at(0);
        minutes = timer_data.at(1);
        seconds = timer_data.at(2);
        int total_seconds {hours * 60 * 60 + minutes * 60 + seconds};

        while (total_seconds--) {
            // TODO: PRINT THE COUNDOWN

            std::cout << hours << ":" << minutes << ":" << seconds-- << "\r" << std::flush;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }

    else {
        error_msg();
        return 1;
    }

    return 0;
}
