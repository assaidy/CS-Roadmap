#include <iostream>

int main() {
    int arr[3][3]{ 0 };

    // fill 
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            std::cin >> arr[i][j];
        }
    }

    // north, west, east, south
    int di[]{-1, 0, 0, 1}; // y => difference in rows
    int dj[]{0, -1, 1, 0}; // x => difference in cols

    std::cout << "neighboars of indx 1x1: " << arr[1][1] << "\n";
    std::cout << "\tnorth = " << arr[1+ di[0]][1 + dj[0]] << '\n';
    std::cout << "\twest = " << arr[1+ di[1]][1 + dj[1]] << '\n';
    std::cout << "\teast = " << arr[1+ di[2]][1 + dj[2]] << '\n';
    std::cout << "\tsouth = " << arr[1+ di[3]][1 + dj[3]] << '\n';

    return 0;
}