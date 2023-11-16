#include <iostream>
#include <stdexcept>

class StackArray {
private:
    int top { -1 };
    int size {};
    int *arr;

public:
    StackArray(int size) : size(size) {
        arr = new int[size];
    }

    void push(int value) {
        if (is_full()) {
            throw std::overflow_error("stack is full");
        } else {
            arr[++top] = value;
        }
    }

    int pop() {
        if (is_empty()) {
            throw std::underflow_error("stack is empty");
        } else {
            return arr[top--];
        }
    }

    int get_top() {
        if (is_empty()) {
            throw std::underflow_error("stack is empty");
        } else {
            return arr[top];
        }
    }

    void print() {
        for (int i = top; i >= 0; i--) {
            std::cout << arr[i] << " ";
        } std::cout << "\n";
    }

    bool is_full() {
        return (top == size - 1);
    }

    bool is_empty() {
        return (top == -1);
    }
};

int main() {
    StackArray stka(5);
    stka.push(1);
    stka.push(2);
    stka.push(3);
    stka.print(); // 3 2 1
    std::cout << stka.get_top() << "\n"; // 3
    std::cout << stka.pop() << "\n"; // 3
    stka.print(); // 2 1
    stka.push(3);
    stka.push(4);
    stka.push(5);
    stka.print(); // 5 4 3 2 1
    stka.push(6); // overflow 
    return 0;
}
