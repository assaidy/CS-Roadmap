#include <iostream>

int main() {
    int arr_flat[12]{ 0 };

    // fill
    for (int i = 0; i < 12; i++)
        std::cin >> arr_flat[i];
    std::cout << '\n';

    int arr_2d[3][4]{ 0 };

    // fill arr_2d
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 4; col++) {
            arr_2d[row][col] = arr_flat[col + row * 4];
        }
    }

    // print arr_2d
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 4; col++) {
            std::cout << arr_2d[row][col] << ' ';
        }
        std::cout << '\n';
    }


    return 0;
}