#include <iostream>
#include <cassert>

class Queue {
private:
    int size{};
    int front{};
    int rear{};
    int added_elements{};
    int* arr{};

public:
    Queue(int size) : size(size) {
        arr = new int[size];
    }

    ~Queue() {
        delete[] arr;
    }

    int front_val() {
        assert(!isEmpty());
        return arr[front];
    }

    int next(int pos) {
        // return (pos + 1) % size;
        pos++;
        if (pos == size)
            pos = 0;
        return pos;
    }

    void enqueue(int value) {
        assert(!isFull());
        arr[rear] = value;
        rear = next(rear);
        added_elements++;
    }

    int dequeue() {
        assert(!isEmpty());
        int value = arr[front];
        front = next(front);
        added_elements--;
        return value;
    }

    bool isEmpty() {
        return added_elements == 0;
    }

    bool isFull() {
        return added_elements == size;
    }

    void display() {
        std::cout << "Front " << front << " - rear " << rear << "\n";
        if (isEmpty()) {
            std::cout << "empty\n\n";
            return;
        }
        else if (isFull())
            std::cout << "full\n";

        for (int cur = front, steps = 0; steps < added_elements;
            steps++, cur = next(cur))
            std::cout << arr[cur] << " ";
        std::cout << "\n";
    }
};

class Deque {
private:
    int size{};
    int front{};
    int rear{};
    int added_elements{};
    int* arr{};

public:
    Deque(int size) : size(size) {
        arr = new int[size];
    }

    ~Deque() {
        delete[] arr;
    }

    int next(int pos) {
        // return (pos + 1) % size;
        pos++;
        if (pos == size)
            pos = 0;
        return pos;
    }

    int prev(int pos) {
        pos--;
        if (pos == -1)
            pos = size - 1;
        return pos;
    }

    void enqueue_rear(int value) {
        assert(!isFull());
        arr[rear] = value;
        rear = next(rear);
        added_elements++;
    }

    void enqueue_front(int value) {
        assert(!isFull());
        front = prev(front);
        arr[front] = value;
        added_elements++;
    }

    int dequeue_front() {
        assert(!isEmpty());
        int value = arr[front];
        front = next(front);
        added_elements--;
        return value;
    }

    int dequeue_rear() {
        assert(!isEmpty());
        rear = prev(rear);
        int value = arr[rear];
        added_elements--;
        return value;
    }

    bool isEmpty() {
        return added_elements == 0;
    }

    bool isFull() {
        return added_elements == size;
    }

    void display() {
        std::cout << "Front " << front << " - rear " << rear << "\n";
        if (isEmpty()) {
            std::cout << "empty\n\n";
            return;
        }
        else if (isFull())
            std::cout << "full\n";

        for (int cur = front, steps = 0; steps < added_elements;
            steps++, cur = next(cur))
            std::cout << arr[cur] << " ";
        std::cout << "\n";
    }
};

class Stack {
private:
    Queue q;
    int added_elements{};

    void insert_front(int value) {
        int sz = added_elements;
        q.enqueue(value);
        while (sz--)
            q.enqueue(q.dequeue());
        added_elements++;
    }

public:
    Stack(int size) : q(size) {
    }

    void push(int value) {
        insert_front(value);
    }

    int pop() {
        return q.dequeue();
    }

    int peak() {
        return q.front_val();
    }

    bool isFull() {
        return q.isFull();
    }

    bool isEmpty() {
        return q.isEmpty();
    }
};


int main() {

    return 0;
}
