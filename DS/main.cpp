#include <iostream>
#include <cassert>
#include <climits>

struct Node {
    int data { };
    Node* next { };
    Node(int data) : data(data) {}
    ~Node() {
        std::cout << "Destroy value: " << data <<" at address "<< this<< "\n";
    }
};


int main() {

    return 0;
}

