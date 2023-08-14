#include <iostream>

int main() {
    int val{}, curVal{};

    if (std::cin >> curVal){
        int cnt{1};
        while (std::cin >> val){
            if (val == curVal)
                cnt++;
            else{
                std::cout << curVal << " appears " << cnt << " times\n";
                cnt = 1;
                curVal = val;
            }
        }
        std::cout << curVal << " appears " << cnt << " times\n";
    }

    return 0;
}
