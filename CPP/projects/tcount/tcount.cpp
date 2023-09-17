#include <cstdlib>
#include <curses.h>
#include <iostream>
#include <thread>
#include <chrono>


int main(int argc, char *argv[]) {

    if (1 == argc) {
        int seconds = 0;
        int minutes = 0;
        int hours = 0;

        while (true) {
            if (seconds == 60) {
                minutes++;
                seconds = 0;
            }
            if (minutes == 60) {
                hours++;
                minutes = 0;
            }
            // std::cout << hours << ":" << minutes << ":" << seconds++ << "\n";
            std::cout << hours << ":" << minutes << ":" << seconds++ << "\r" << std::flush;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }

    else if (2 == argc) {
        // TODO: TIMER

    }

    else {
        std::cout << 
            "Usage: tcount [DURATION]\tDURATION: '$h $m $s'\n"
            "Usage: tcount\n";
        return 1;
    }

    return 0;
}
