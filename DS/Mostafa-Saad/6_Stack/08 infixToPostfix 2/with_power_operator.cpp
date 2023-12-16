#include <iostream>
#include <cassert>

class Stack {
    struct Node {
        int data{};
        Node* next{};

        Node(int data) : data(data) {}
    };

    Node* head{};

public:
    void push(int value) {
        Node* item = new Node(value);
        item->next = head;
        head = item;
    }

    int pop() {
        assert(!isEmpty());

        int value = head->data;
        Node* tmp = head;
        head = head->next;
        delete tmp;
        return value;
    }

    int peak() {
        assert(!isEmpty());
        return head->data;
    }

    bool isEmpty() {
        return !head;
    }

    void display() {
        assert(!isEmpty());
        for (Node* cur = head; cur; cur = cur->next)
            std::cout << cur->data << " ";
        std::cout << "\n";
    }
};

int precedence(char op) {
    if (op == '^')
        return 3;
    if (op == '/' || op == '*')
        return 2;
    if (op == '+' || op == '-')
        return 1;
    return 0;
}

std::string infix_to_postfix(std::string infix) {
    std::string postfix;
    Stack operators;

    infix += '-'; // force the stack to get empty
    operators.push('#'); // remove the !isEmpty() check

    for (const auto& token : infix) {
        if (isdigit(token))
            postfix += token;
        else if (token == '(')
            operators.push(token);
        else if (token == ')') {
            while (operators.peak() != '(')
                postfix += operators.pop();
            operators.pop();
        }
        else {
            while (precedence(operators.peak()) >= precedence(token) && token != '^')
                postfix += operators.pop();

            operators.push(token);
        }
    }
    return postfix;
}

int main() {
    // test 1
    std::string test = "1+3*5-8/2";
    std::cout << test << "\n";
    std::cout << infix_to_postfix(test) << "\n\n";

    // test 2
    test = "1+2*3";
    std::cout << test << "\n";
    std::cout << infix_to_postfix(test) << "\n\n";

    // test 3
    test = "2+3*4-5*6+7";
    std::cout << test << "\n";
    std::cout << infix_to_postfix(test) << "\n\n";

    // test 4
    test = "3^2^4+5";
    std::cout << test << "\n";
    std::cout << infix_to_postfix(test) << "\n\n"; // 324^^5+

    // test 5
    test = "3*2^4+5";
    std::cout << test << "\n";
    std::cout << infix_to_postfix(test) << "\n\n"; // 324^*5+

    return 0;
}
