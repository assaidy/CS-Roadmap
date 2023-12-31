#include <bits/types/time_t.h>
#include <iostream>
#include <regex>
#include <string>
#include <wee.h>

/*
 * TODO:
 * - [x] set number of tries.
 * - [ ] help the user by: 'the number is between $ and $'
 * */

int main() {
    unsigned int inputNum{};
    unsigned int randomNum{};
    unsigned int tries{5};

    while (tries > 0) {
        system("clear");

        inputNum = get_int("Guess A Number: ");
        if (inputNum > 1000 || inputNum < 1) {
            std::cout << "\nPlz, Enter a number between [1 - 1000] inclusive...";
            getchar();
            getchar();
        } else {
            srand((unsigned)time(NULL));
            randomNum = 1 + (rand() % 1000);

            if (randomNum == inputNum) {
                std::cout << "\nWE HAVE A WINNER:). You guessed the number.\n";
            } else {
                tries--;
                std::cout << "\nWrong Answer:(.\n";
                std::cout << "The number was " << randomNum << '\n';
                std::cout << "\nYou have " << tries << " tries left\n";

                if (tries == 0) {
                    std::cout << "End of the game.\n";
                    return 0;
                }

                std::string answer = strip(get_string("Would you like to continue? [yes/no] ")); // this uses getline()

                if (answer == "yes") {
                    continue;
                } else {
                    std::cout << "\nEnd of the game.\n";
                    return 0;
                }
            }
        }
    }
}
