#include <iostream>
// the Queue:
//  - stdio
//  - Schedualing in processors
//
// * Array Based [linear & circular]
// * Linked Based

class QueueArray {
private:
    int size {};
    int front { -1 };
    int rear { -1 };
    int *arr {};

public:
    QueueArray(int size) : size(size) {
        arr = new int[size];
    }

    bool is_empty() {
        return  (front == -1) && (rear == front);
    }

    bool is_full() {
        return rear == size - 1;
    }

    void enque(int value) {
        if (is_full()) {
            std::cout << "[Error] queue is full\n";
            return;
        } if (is_empty()) {
            ++front;
        }        
        arr[++rear] = value;
    }

    int deque() {
        if (is_empty()) {
            std::cout << "[Error] queue is empty\n";
            return -1; // suppose -1 is an error code
        }
        int to_delete { arr[front] };
        if (rear == front) { // a single item remaining
            int to_delete { arr[front] };
            rear = front = -1; // reset the queue
            return to_delete;
        }
        return arr[front++];
    }
    
    void print() {
        if (is_empty()) {
            std::cout << "[Error] queue is empty\n";
            return;
        }
        for (int i = front; i <= rear; i++)
            std::cout << arr[i] << " ";
        std::cout << "\n";
    }
};

int main() {
    QueueArray qa(5);
    qa.enque(1);
    qa.enque(2);
    qa.enque(3);
    qa.enque(4);
    qa.enque(5);
    qa.print(); // 1 2 3 4
    qa.enque(6); // error
    std::cout << qa.deque() << "\n"; // 1
    std::cout << qa.deque() << "\n"; // 2
    std::cout << qa.deque() << "\n"; // 3
    std::cout << qa.deque() << "\n"; // 4
    qa.print(); // 5
    std::cout << qa.deque() << "\n"; // 5
    qa.print(); // error
    qa.deque(); // error
    return 0;
}
