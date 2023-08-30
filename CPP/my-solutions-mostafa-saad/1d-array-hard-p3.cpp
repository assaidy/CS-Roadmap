#include <iostream>

int main() {
    int N{};
    std::cin >> N;

    int arr[N];
    for (int i = 0; i < N; i++) // fill the array
        std::cin >> arr[i];

    int counter{ N };
    bool is_continuos{ true };

    for (int i = 1; i < N; i++) {
        if (arr[i] > arr[i - 1] && is_continuos) {
            counter += i;
            // std::cout << counter << ' ' << is_continuos << '\n'; // just for tracing
        }
        else if (arr[i] > arr[i - 1] && !is_continuos) {
            counter += 1;
            // std::cout << counter << ' ' << is_continuos << '\n'; // just for tracing
        }
        else {
            is_continuos = false;
            // std::cout << counter << ' ' << is_continuos << '\n'; // just for tracing
        }
    }
    std::cout << counter << '\n';

    return 0;
}

