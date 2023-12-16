#include <iostream>

struct Node {
    int data {};
    Node *next {};
    Node(int data) : data(data) {};
    ~Node() {
        std::cout << "deleting node with value " << data 
            << " at address " << this << "\n";
    }
};

class SLL {
private:
    Node *head {};
    Node *tail {};
    int length {};

public:
    void print() { // O(n) time, O(1) memory
        for (Node *cur = head; cur; cur = cur->next)
            std::cout << cur->data << " ";
        std::cout << "\n";
    }

    void insert_end(int value) { // O(1) time[with tail], O(1) memory
        Node *item { new Node(value) };
        if (!head)
            head = tail = item;
        else
            tail->next = item, tail = item;
        length++;
    }

    void insert_front(int value) { // O(1) time, O(1) memory
        Node *item { new Node(value) };
        if (!head)
            head = tail = item;
        else
            item->next = head, head = item;
        length++;
    }

    Node *get_nth(int nth) { // O(n) time, O(1) memory
        if (nth < 1 || nth > length) return nullptr;
        int cnt {};
        for (Node *cur = head; cur; cur = cur->next)
            if (++cnt == nth)
                return cur; 
        return nullptr;
    }

    void delete_first() { // O(1) time, O(1) memory
        if (head) {
            Node *tmp { head };
            head = head->next;
            delete tmp;
            if (!head)
                tail = nullptr;
            length--;
        }
    }

    void delete_last() { // O(n) time, O(1) memory
        if (length <= 1) {
            delete_first();
            return;
        }
        Node *tail_prev { get_nth(length - 1) }; // O(n) time
        tail_prev->next = nullptr;
        delete tail;
        tail = tail_prev;
        length--;
    }

    void delete_nth(int nth) { // O(n) time, O(1) memory
        if (nth < 1 || nth > length) return;
        if (nth == 1) {
            delete_first();
            return;
        }
        if (nth == length) {
            delete_last();
            return;
        }
        Node *target_prev { get_nth(nth - 1) }; // O(n) time
        Node *to_delete { target_prev->next };
        target_prev->next = to_delete->next;
        delete to_delete;
        length--;
    }

    void reverse() { // O(1) time, O(1) memory
        if (length <= 1) return;
        tail = head;
        Node *prev { head };
        Node *cur { head->next };
        while (cur) {
            Node *next { cur->next };
            cur->next = prev;
            prev = cur;
            cur = cur->next;
        }
        head = prev;
        tail->next = nullptr;
    }
};

int main() {
    return 0;
}
