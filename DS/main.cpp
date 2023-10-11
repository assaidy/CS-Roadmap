#include <iostream>
#include <algorithm>
#include <cassert>

// Stack Data Structure
class Stack {
private:
    int size{}; // the max size of the stack
    int top{}; // the index of the last added item
    int* arr{};

public:
    Stack(size_t size) : size(size) {
        arr = new int[size] {};
        top = -1;
    }
    ~Stack() {
        delete[] arr;
    }

    void push(int value) {
        assert(!isFull());
        arr[++top] = value;
    }

    int pop() {
        assert(!isEmpty());
        return arr[top--];
    }

    int peak() {
        assert(!isEmpty());
        return arr[top];
    }

    bool isEmpty() {
        return (top == -1);
    }

    bool isFull() {
        return (top == size - 1);
    }

    void display() {
        for (int i = top; i >= 0; i--)
            std::cout << arr[i] << " ";
        std::cout << "\n";
    }

};

///////////////////////////// HW 1 ///////////////////////////////////

std::string reverse_subwords(std::string line) {
    std::string result;

    line += ' ';
    Stack stk(line.size());

    for (int i = 0; i < (int)line.size(); i++) {
        if (line[i] == ' ') {
            while (!stk.isEmpty())
                result += stk.pop();
            result += ' ';
        }
        else
            stk.push(line[i]);
    }

    return result;
}

int reverse_num(int num) {
    if (num == 0)
        return 0;

    Stack stk(25);

    while (num) {
        stk.push(num % 10);
        num /= 10;
    }

    int tens = 1;
    while (!stk.isEmpty()) {
        num = stk.pop() * tens + num;
        tens *= 10;
    }

    return num;
}

char get_openinig_parantheses(char ch) {
    if (ch == ']') return '[';
    else if (ch == '}') return '{';
    return '(';
}

bool isValid(std::string str) {
    Stack parantheses(str.size());

    for (int i = 0; i < int(str.size()); i++) {
        char ch = str.at(i);

        if (ch == '{' || ch == '(' || ch == '[')
            parantheses.push(ch);
        else if (parantheses.isEmpty() || parantheses.pop() != get_openinig_parantheses(ch))
            return false;
    }
    return parantheses.isEmpty();
}

std::string remove_dublicates(std::string str) {
    Stack raw(str.size());

    for (int i = 0; i < int(str.size()); i++) {
        if (!raw.isEmpty() && str.at(i) == raw.peak()) {
            raw.pop();
            continue;
        }
        else
            raw.push(str.at(i));
    }

    str.clear();
    while (!raw.isEmpty()) {
        str = static_cast<char>(raw.pop()) + str;
    }
    return str;
}

class TwoStacks {
private:
    int size{};
    int top1{};
    int top2{};
    int* arr{};
public:
    TwoStacks(int size) :
        size(size), top1(-1), top2(size) {
        arr = new int[size] {};
    }
    ~TwoStacks() {
        delete[] arr;
    }

    void push(int id, int x) {
        assert(!isFull());
        if (id == 1)
            arr[++top1] = x;
        else
            arr[--top2] = x;
    }

    int pop(int id) {
        assert(!isEmpty(id));
        if (id == 1)
            return arr[top1--];
        return arr[top2++];
    }

    int peak(int id) {
        assert(!isEmpty(id));
        if (id == 1)
            return arr[top1];
        return arr[top2];
    }

    bool isEmpty(int id) {
        if (id == 1)
            return top1 == -1;
        return top2 == size;
    }

    bool isFull() {
        return top1 + 1 >= top2;
    }

    void display() {
        for (int i = top1; i >= 0; i--)
            std::cout << arr[i] << " ";
        std::cout << "\n";
        for (int i = top2; i < size; i++)
            std::cout << arr[i] << " ";
        std::cout << "\n";
    }
};

///////////////////////////// HW 2 ///////////////////////////////////

int main() {
	TwoStacks stk(10);
	stk.push(2, 5);
	stk.push(2, 6);
	stk.pop(2);
	stk.push(2, 7);
	stk.push(2, 9);

	stk.push(1, 4);
	stk.push(1, 6);
	stk.push(1, 8);
	stk.push(2, 3);
	stk.display();

    return 0;
}
