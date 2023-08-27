#include <iostream>

int main() {
    int N{};
    std::cin >> N;

    int freq_arr[2001]{ 0 };

    int arr[N + 1];
    arr[0] = 0, arr[1] = 1;
    freq_arr[arr[0]]++, freq_arr[arr[1]]++;
    int answer_1{}, answer_2{};
    for (int i = 2; i <= N; i++) { // fill the sequence until the required index
        answer_1 = arr[i - 1] - (i - 1) - 1; // if no repeatition
        answer_2 = arr[i - 1] + (i - 1) + 1; // if repeatition
        if (!freq_arr[answer_1] && answer_1 > 0) {
            arr[i] = answer_1;
            freq_arr[answer_1]++;
        }
        else {
            arr[i] = answer_2;
            freq_arr[answer_2]++;
        }
        std::cout << arr[i] << '\n';
    }
    std::cout << arr[N] << '\n';

    return 0;
}