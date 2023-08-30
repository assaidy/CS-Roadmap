#include <iostream>

int main() {
    int sum{}, N{}, K{};
    std::cin >> K >> N;

    int arr[N];
    for (int i = 0; i < N; i++) // fill the array
        std::cin >> arr[i];

    for (int i = 0; i < K; i++) // initial sum
        sum += arr[i];

    int max_sum{ sum }, max_idx{ 0 };

    for (int i = 1; i < (N - K + 1); i++) {
        // std::cout << i << '\n'; // just for tracing
        sum -= arr[i - 1]; // remove element before
        sum += arr[i + K - 1]; // add element after
        if (max_sum < sum) {
            max_sum = sum;
            max_idx = i;
        }
    }
    std::cout << max_idx << ' ' << max_idx + K - 1 << ' ' << max_sum << '\n';

    return 0;
}
