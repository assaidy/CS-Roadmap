#include <iostream>

int main() {
    int size{};
    std::cin >> size;

    int nums[size];
    int freq_arr[5001]{};

    // fill and count freq
    for (int i = 0; i < size; i++) {
        std::cin >> nums[i];
        freq_arr[nums[i]]++;
    }

    // count frequency sort
    for (int i = 0; i < 5001; i++) {
        while (freq_arr[i]--)
            std::cout << i << ' ';
    }
    std::cout << '\n';

    return 0;
}