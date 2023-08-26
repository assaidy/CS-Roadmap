#include <iostream>
#include <wee.h>

int main() {
    int size{};
    std::cin >> size;

    // array of frequency
    int arr_freq[151]{ 0 };

    // fill the array
    int nums[size];
    for (int i = 0; i < size; i++) {
        std::cin >> nums[i]; // fill nums[]
        arr_freq[nums[i]]++; // count frequency
    }

    // find the maximum in arr_freq
    int most_freq_times{ arr_freq[0] };
    int most_freq_num{};
    for (int i = 1; i < std::size(arr_freq); i++) {
        if (most_freq_times <= arr_freq[i])
            most_freq_times = arr_freq[i], most_freq_num = i;
    }

    std::cout << most_freq_num << ' ' << most_freq_times << '\n';

    return 0;
}
