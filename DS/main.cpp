#include <iostream>
#include <cassert>
#include <climits>

#include <vector>		// for debug
#include <algorithm>
#include <sstream>
using namespace std;

struct Node {
    int data { };
    Node* next { };
    Node(int data) : data(data) {}
    ~Node() {
        cout << "Destroy value: " << data <<" at address "<< this<< "\n";
    }
};


class LinkedList {
private:
    Node *head {};

public:
    // O(n) time, O(1) memroy
    void print() {
        for (Node *cur = head; cur; cur = cur->next) {
            std::cout << cur->data << " ";
        }
        std::cout << "\n";
    }

    // O(1) time, O(1) memory
    void add(int val) { // add() now do push_front()
        Node *item = new Node(val);

        if (!head)
            head = item;
        else
         item->next = head, head = item;
    }

    // O(n) time, O(1) memory
    Node *get_tail() {
        for (Node *cur = head; cur; cur = cur->next)
            if (!cur->next) return cur;
        return nullptr;
    }

    ~LinkedList() {
        Node *tmp = nullptr;
        for (Node *cur = head; cur; cur = tmp) {
            tmp = cur->next;
            delete cur;
        }
    }
};


int main() {
    LinkedList list;
    list.add(10);
    list.add(20);
    list.add(30);

    list.print();

    std::cout << list.get_tail()->data << "\n";

    return 0;
}

