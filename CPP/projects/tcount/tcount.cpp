#include <algorithm>
#include <iomanip>
#include <cstdlib>
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <vector>
#include <regex>

void error_msg() {
    std::cout <<
        "Usage: to count down\n\ttcount [DURATION]\tDURATION: '$h $m $s'\n"
        "Usage: to count up\n\ttcount\n";
}

std::vector<int> get_timer_data(std::string str) {
    std::vector<int> result;
    result.reserve(3);
    std::string tmp;
    for (const auto c : str) {
        tmp += c;
        if (c == 'h' || c == 'm' || c == 's') {
            result.push_back(std::stoi(tmp));
            tmp.clear();
        }
    }

    return result;
}

void figlet_print(int hours, int minutes, int seconds) {
    std::string cmd{ "clear; echo '\n'; " };
    cmd += "figlet -f ~/.local/share/tcount/ansi_regular.flf -t -c ";
    cmd += "\"" + std::to_string(hours) + ":" + std::to_string(minutes) + ":" + std::to_string(seconds) + "\"";
    std::system(cmd.c_str());
}

void norm_counter(int hours = 0, int minutes = 0, int seconds = 0) {
    while (true) {
        if (seconds == 60) {
            minutes++;
            seconds = 0;
        }
        if (minutes == 60) {
            hours++;
            minutes = 0;
        }
        // std::cout
        //     << std::setw(2) << std::setfill('0') << hours << ":"
        //     << std::setw(2) << std::setfill('0') << minutes << ":"
        //     << std::setw(2) << std::setfill('0') << seconds++
        //     << "\r" << std::flush;

        figlet_print(hours, minutes, seconds);
        seconds++;

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}


void norm_timer(const std::vector<int>& _timer_data) {
    int hours{ _timer_data.at(0) };
    int minutes{ _timer_data.at(1) };
    int seconds{ _timer_data.at(2) };
    int total_seconds{ hours * 60 * 60 + minutes * 60 + seconds };

    while (total_seconds--) {
        if (0 == seconds) {
            seconds = 60;
            minutes--;
        }
        if (minutes <= 0) {
            if (hours > 0) {
                minutes = 60;
                hours--;
            }
            else {
                minutes = 0;
            }
        }
        if (hours <= 0) {
            hours = 0;
        }
        // std::cout << " [" << std::setw(2) << std::setfill('0') << total_seconds * 100 / total_seconds_tmp << "%] "
        //     << std::setw(2) << std::setfill('0') << hours << ":"
        //     << std::setw(2) << std::setfill('0') << minutes << ":"
        //     << std::setw(2) << std::setfill('0') << seconds--
        //     << "\r" << std::flush;

        figlet_print(hours, minutes, seconds);
        seconds--;

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    figlet_print(0, 0, 0);
    std::system("canberra-gtk-play -f ~/.local/share/tcount/mixkit-positive-notification-951.wav");
    // std::this_thread::sleep_for(std::chrono::seconds(1));
    norm_counter(_timer_data.at(0), _timer_data.at(1), _timer_data.at(2));
}

int main(int argc, char* argv[]) {
    // NOTE: COUNTER
    if (1 == argc) {
        norm_counter();
    }
    // NOTE: TIMER
    else if (2 == argc) {
        std::string user_arg_str = argv[1]; // $h $m $s
        if (!(std::regex_match(user_arg_str, std::regex("\\d+h \\d+m \\d+s")))) {
            error_msg();
            return 1;
        }
        std::vector<int> timer_data{ get_timer_data(user_arg_str) };

        norm_timer(timer_data);
        // std::cout << "DONE! GOOD JOB :)\n";
    }
    // NOTE: ERROR
    else {
        error_msg();
        return 1;
    }

    return 0;
}

// TODO: BUILD