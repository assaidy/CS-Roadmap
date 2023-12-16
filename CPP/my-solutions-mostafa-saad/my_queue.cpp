#include <iostream>
#include <algorithm>

struct queue {
    int arr[100];
    int len;

    queue() {
        len = 0;
    }
    void add_end(int num_) {
        arr[len++] = num_;
    }
    void add_front(int num_) {
        // shift right => push front
        for (int i = len - 1; i >= 0; i--) {
            arr[i + 1] = arr[i];
        }
        arr[0] = num_;
        len++;
    }
    int remove_front() {
        // shift left
        int tmp = arr[0];
        for (int i = 0; i < len - 1; i++) {
            arr[i] = arr[i + 1];
        }
        len--;
        return tmp;
    }
    void print() {
        for (int i = 0; i < len; i++) {
            std::cout << arr[i] << ' ';
        }
        std::cout << '\n';
    }
};

int main() {
    queue my_q;

    my_q.add_end(1);
    my_q.add_end(2);
    my_q.add_end(3);
    my_q.print();
    std::cout << my_q.remove_front() << '\n'; // 1
    my_q.add_front(5);
    my_q.add_front(8);
    my_q.print();

    return 0;
}