#include <iostream>
// the Queue:
//  - stdio
//  - Schedualing in processors
//
// * Array Based [linear & circular]
// * Linked Based

struct Node {
    int data {};
    Node *next {};
    Node(int data) : data(data) {}
    ~Node() {
        std::cout << "deleting Node of value " << data
            << " at address " << this << "\n";
    }
};

class QueueLinked {
private:
    Node *front {};
    Node *rear {};

public:
    bool is_empty() {
        return (!front && !rear); // rear & front are NULL
    }

    void enque(int value) {
        Node *item { new Node(value) };
        if (is_empty()) {
            front = rear = item;
        } else {
            rear->next = item;
            rear = item;
        }
    }

    int deque() {
        if (is_empty()) {
            std::cout << "[Error] queue is empty\n";
            return -1; // suppose -1 is an error code
        }
        int to_delete { front->data };
        Node *tmp { front };
        if (rear == front) { // a single item remaining
            rear = front = nullptr;
        } else {
            front = front->next;
        }
        delete tmp;
        return to_delete;
    }
    
    void print() {
        if (is_empty()) {
            std::cout << "[Error] queue is empty\n";
            return;
        }
        for (Node *cur = front; cur; cur = cur->next)
            std::cout << cur->data << "\n";
        std::cout << "\n";
    }

    ~QueueLinked() {
        for (Node *cur = front; cur; ) {
            Node *next { cur->next };
            delete cur;
            cur = next;
        }
    }
};

int main() {
    QueueLinked ql;
    ql.enque(1);
    ql.enque(2);
    ql.enque(3);
    ql.enque(4);
    ql.enque(5);
    ql.print(); // 1 2 3 4 5
    std::cout << ql.deque() << "\n"; // 1
    std::cout << ql.deque() << "\n"; // 2
    std::cout << ql.deque() << "\n"; // 3
    std::cout << ql.deque() << "\n"; // 4
    ql.print(); // 5
    std::cout << ql.deque() << "\n"; // 5
    ql.print(); // error
    ql.deque(); // error
    return 0;
}
