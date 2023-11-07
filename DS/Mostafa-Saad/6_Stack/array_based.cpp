#include <iostream>
#include <algorithm>
#include <cassert>
#include <vector>

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

    // HW 2
    void insert_bottom(int x) {
        if (isEmpty())
            push(x);
        else {
            int cur = pop();
            insert_bottom(x);
            push(cur);
        }
    }

    // HW 2
    void reverse() {
        if (isEmpty())
            return;
        int cur = pop();
        reverse();
        insert_bottom(cur);
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

bool are_opposite(int num1, int num2) {
    if (num1 > 0 && num2 < 0)
        return true;
    return false;
}

std::vector<int> astroid_collision(std::vector<int> vec) {
    Stack stk(vec.size());

    for (int i = 0; i < int(vec.size()); i++) {
        if (!stk.isEmpty() && are_opposite(stk.peak(), vec[i])) {
            while (true && !stk.isEmpty()) {
                if (std::abs(vec[i]) >= stk.peak())
                    stk.pop();
                else
                    break;
            }
            if (!stk.isEmpty() && abs(vec[i]) < stk.peak())
                continue;
        }
        else
            stk.push(vec[i]);
    }
    vec.clear();
    while (!stk.isEmpty())
        vec.push_back(stk.pop());
    std::reverse(vec.begin(), vec.end());

    return vec;
}

void next_greater_nested_loops(int len, int arr[]) { // O(n^2) time
    for (int i = 0; i < len; i++) {
        auto nextGreater{ -1 };
        for (int j = i + 1; j < len; j++) {
            if (arr[j] > arr[i]) {
                nextGreater = arr[j];
                break;
            }
        }
        std::cout << nextGreater << " ";
    }
    std::cout << "\n";
}

void next_greater_stack(int len, int arr[]) { // O(n) time
    Stack stk(len);
    auto nextGreater{ -1 };
    Stack result(len);

    for (int i = len - 1; i >= 0; i--) {
        if (stk.isEmpty())
            stk.push(arr[i]);
        else if (stk.peak() <= arr[i]) {
            stk.push(arr[i]);
        }
        else {
            if (arr[i + 1] < stk.peak() && arr[i + 1] > arr[i])
                nextGreater = arr[i + 1];
            else if (arr[i + 1] > nextGreater || arr[i] > nextGreater)
                nextGreater = stk.peak();
        }
        result.push(nextGreater);
        // std::cout << nextGreater << " "; // this will print reversedly
    }
    // std::cout << "\n";
    result.display();
}

int main() {
    int arr[8]{ 73, 74, 75, 71, 69, 72, 76, 73 };
    next_greater_stack(8, arr);

    return 0;
}
