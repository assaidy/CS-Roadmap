#include <iostream>
#include <stdexcept>

struct Node {
    int data {};
    Node *next {};

    Node(int data) : data(data) {}
    ~Node() {
        std::cout << "deleting node with value " << data << " at " << this << "\n";
    }
};

class SLL {
private:
    Node *head {};

    void add_node(Node *_prev, Node *_new_node) {
        _new_node->next = _prev->next;
        _prev->next = _new_node;
    }

public:
    void insert_front(int _data) { // O(1) time
        Node *new_node { new Node(_data) };
        if (!head) {
            head = new_node;
        } else {
            new_node->next = head;
            head = new_node;
        }
    }

    void insert_end(int _data) { // O(n) time
        Node *new_node { new Node(_data) };
        if (!head) {
            insert_front(_data);
        } else {
            Node *tmp { head };
            while (tmp->next) {
                tmp = tmp->next;
            } // now tmp is the last node
            add_node(tmp, new_node);
        }
    }

    // TODO: insert middle

    void delete_front() {
        if (!head) return;
        Node *tmp { head };
        head = head->next;
        delete tmp;
    }

    void delete_end() {
        if (!head) {
            return;
        } else if (!head->next) {
            delete_front();
        } else {
            Node *tmp { head };
            Node *prev {};
            while (tmp->next) {
                prev = tmp;
                tmp = tmp->next;
            } // now tmp is the last node
            prev->next = nullptr;
            delete tmp;
        }
    }

    // TODO: delete middle

    void print() {
        for (Node *tmp = head; tmp; tmp = tmp->next)
            std::cout << tmp->data << " ";
        std::cout << "\n";
    }

    ~SLL() {
        for (Node *cur = head; cur; ) {
            Node *tmp { cur };
            cur = cur->next;
            delete tmp;
        }
    }
};

int main() {
    SLL sll;
    sll.insert_front(30);
    sll.insert_front(20);
    sll.insert_front(10);
    sll.print(); // 10 20 30
    sll.insert_end(40);
    sll.print(); // 10 20 30 40
    return 0;
}
