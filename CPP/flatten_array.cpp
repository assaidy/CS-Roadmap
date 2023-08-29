#include <iostream>

int main() {
    int arr[3][4]{ 0 };

    // fill
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 4; col++) {
            std::cin >> arr[row][col];
        }
    }
    std::cout << '\n';

    // print 2d
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 4; col++) {
            std::cout << arr[row][col] << ' ';
        }
        std::cout << '\n';
    }
    std::cout << '\n';

    // flatten
    // the flat array is an array of (12 idx => 3 * 4)
    // idx_flat = cur_col + cur_row * max_cols
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 4; col++) {
            std::cout << "#" << arr[row][col]
                << "\t2d_idx: " << row << "x" << col
                << "\t1d_idx: " << col + row * 4 << '\n';
        }
    }


    return 0;
}