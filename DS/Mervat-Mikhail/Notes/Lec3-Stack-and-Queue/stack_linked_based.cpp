#include <iostream>

struct Node {
    int data {};
    Node *next {};

    Node(int data) : data(data) {}
    ~Node() {
        std::cout << "deleting node with value " << data
            << " at address " << this << "\n";
    }
};

class StackLinked {
private:
    Node *top {};

public:
    void push(int value) {
        Node *item { new Node(value) };
        if (is_empty()) {
            top = item;
        } else {
            item->next = top;
            top = item;
        }
    }

    int pop() {
        if (is_empty()) {
            throw std::underflow_error("stack is empty");
        } else {
            Node *tmp { top };
            int tmp_data { tmp->data };
            top = top->next;
            delete tmp;
            return tmp_data;
        }
    }

    int get_top() {
        if (is_empty()) {
            throw std::underflow_error("stack is empty");
        } else {
            return top->data;
        }
    }

    void print() {
        for (Node *cur = top; cur; cur = cur->next) {
            std::cout << cur->data << " ";
        } std::cout << "\n";
    }

    bool is_empty() {
        return !top;
    }
};

int main() {
    StackLinked stkl;
    stkl.push(1);
    stkl.push(2);
    stkl.push(3);
    stkl.print(); // 3 2 1
    std::cout << stkl.get_top() << "\n"; // 3
    std::cout << stkl.pop() << "\n"; // 3
    stkl.print(); // 2 1
    stkl.push(3);
    stkl.push(4);
    stkl.push(5);
    stkl.print(); // 5 4 3 2 1
    std::cout << stkl.pop() << "\n"; // 5
    std::cout << stkl.pop() << "\n"; // 4
    std::cout << stkl.pop() << "\n"; // 3
    std::cout << stkl.pop() << "\n"; // 2
    std::cout << stkl.pop() << "\n"; // 1
    std::cout << stkl.pop() << "\n"; // underflow
    return 0;
}
