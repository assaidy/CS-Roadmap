#include <iostream>
#include <cassert>
#include <climits>

#include <vector>		// for debug
#include <algorithm>
#include <sstream>
using namespace std;

struct Node {
    int data{ };
    Node* next{ };
    Node(int data) : data(data) {}
    ~Node() {
        cout << "Destroy value: " << data << " at address " << this << "\n";
    }
};

class LinkedList {
private:
    Node* head{ };
    Node* tail{ };
    int length = 0;	// let's maintain how many nodes

    vector<Node*> debug_data;	// add/remove nodes you use

    void debug_add_node(Node* node) {
        debug_data.push_back(node);
    }
    void debug_remove_node(Node* node) {
        auto it = std::find(debug_data.begin(), debug_data.end(), node);
        if (it == debug_data.end())
            cout << "Node does not exist\n";
        else
            debug_data.erase(it);
    }

public:

    // Below 2 deletes prevent copy and assign to avoid this mistake
    LinkedList() {
    }
    LinkedList(const LinkedList&) = delete;
    LinkedList& operator=(const LinkedList& another) = delete;

    void debug_print_address() {
        for (Node* cur = head; cur; cur = cur->next)
            cout << cur << "," << cur->data << "\t";
        cout << "\n";
    }

    void debug_print_node(Node* node, bool is_seperate = false) {
        if (is_seperate)
            cout << "Sep: ";
        if (node == nullptr) {
            cout << "nullptr\n";
            return;
        }
        cout << node->data << " ";
        if (node->next == nullptr)
            cout << "X ";
        else
            cout << node->next->data << " ";

        if (node == head)
            cout << "head\n";
        else if (node == tail)
            cout << "tail\n";
        else
            cout << "\n";
    }
    void debug_print_list(string msg = "") {
        if (msg != "")
            cout << msg << "\n";
        for (int i = 0; i < (int)debug_data.size(); ++i)
            debug_print_node(debug_data[i]);
        cout << "************\n" << flush;
    }

    string debug_to_string() {
        if (length == 0)
            return "";
        ostringstream oss;
        for (Node* cur = head; cur; cur = cur->next) {
            oss << cur->data;
            if (cur->next)
                oss << " ";
        }
        return oss.str();
    }

    void debug_verify_data_integrity() {
        if (length == 0) {
            assert(head == nullptr);
            assert(tail == nullptr);
        }
        else {
            assert(head != nullptr);
            assert(tail != nullptr);
            if (length == 1)
                assert(head == tail);
            else
                assert(head != tail);
            assert(!tail->next);
        }
        int len = 0;
        for (Node* cur = head; cur; cur = cur->next, len++)
            assert(len < 10000);	// Consider infinite cycle?
        assert(length == len);
        assert(length == (int)debug_data.size());
    }

    ////////////////////////////////////////////////////////////

    void print() {
        for (Node* cur = head; cur; cur = cur->next)
            cout << cur->data << " ";
        cout << "\n";
    }

    // These 2 simple functions just to not forget changing the vector and length
    void delete_node(Node* node) {
        debug_remove_node(node);
        --length;
        delete node;
    }

    void add_node(Node* node) {
        debug_add_node(node);
        ++length;
    }

    void insert_end(int value) {
        Node* item = new Node(value);
        add_node(item);

        if (!head)
            head = tail = item;
        else
            tail->next = item, tail = item;
    }

    Node* get_nth(int n) {
        int cnt = 0;
        for (Node* cur = head; cur; cur = cur->next)
            if (++cnt == n)
                return cur;

        return nullptr;	// still more steps needed - NOT found
    }

    void delete_first() {
        if (head) {
            Node* cur_head = head;
            head = head->next;
            delete_node(cur_head);
            if (!head) {
                tail = nullptr;
                debug_verify_data_integrity();
            }
        }
    }

    void delete_last() {
        if (length <= 1) {
            delete_first();
            return;
        }
        Node* prev_tail = get_nth(length - 1);
        delete_node(tail);
        tail = prev_tail;
        tail->next = nullptr;

        debug_verify_data_integrity();
    }

    void delete_nth(int nth) {
        if (nth < 1 || nth > length) {
            std::cout << "ERROR: out of range\n";
            return;
        }
        if (nth == 1) {
            delete_first();
            return;
        }
        if (nth == length) {
            delete_last();
            return;
        }
        Node* prev = get_nth(nth - 1);
        Node* to_delete = prev->next;
        prev->next = to_delete->next;
        delete_node(to_delete);

        debug_verify_data_integrity();
    }

    // O(n) time, O(1) memory
    void delete_node_with_key(int key) {
        if (length == 0) return;
        int cnt{ 1 };
        bool found{ false };
        for (Node* cur = head; cur; cur = cur->next) {
            if (cur->data == key) {
                found = true;
                break;
            }
            cnt++;
        }
        if (found) delete_nth(cnt);

        debug_verify_data_integrity();
    }

    // O(n) time, O(1) memory
    void swap_pairs() {
        if (length <= 1) return;

        for (Node* cur = head; cur; cur = cur->next) {
            if (cur->next) {
                swap(cur->data, cur->next->data);
                cur = cur->next;
            }
        }
        debug_verify_data_integrity();
    }

    // O(n) time, O(1) memory
    void reverse() {
        if (length <= 1) return;

        tail = head;
        Node* prev = head;
        Node* cur = head->next;

        while (cur) {
            Node* next = cur->next;
            cur->next = prev;

            prev = cur;
            cur = next;
        }
        head = prev;
        tail->next = nullptr;
        debug_verify_data_integrity();
    }

    void delete_next_node(Node* node) {
        // Delete the next of the current node
        // Handle if next is tail case
        assert(node);

        Node* to_delete = node->next;
        bool is_tail = to_delete == tail;

        // node->next in middle to delete
        node->next = node->next->next;

        delete_node(to_delete);
        if (is_tail)
            tail = node;
    }

    void delete_even_positions() {		// O(n) time - O(1) memory
        if (length <= 1)
            return;
        // maintain previous and delete its next (even order)
        for (Node* cur = head->next, *prv = head;cur;) {
            delete_next_node(prv);	// prev is odd, prev-next is even
            if (!prv->next)	// tail
                break;
            cur = prv->next->next;
            prv = prv->next;
        }
        debug_verify_data_integrity();
    }

    void insert_front(int value) {
        Node* item = new Node(value);
        ++length;
        debug_add_node(item);

        item->next = head;
        head = item;

        if (length == 1)
            tail = head;

        debug_verify_data_integrity();
    }

    void embed_after(Node* node, int value) {
        // Add a node with value between node and its next
        Node* item = new Node(value);
        ++length;
        debug_add_node(item);

        item->next = node->next;
        node->next = item;
    }

    void insert_sorted(int value) {		// O(n) time - O(1) memory
        // 3 special cases for simplicity
        if (!length || value <= head->data)
            insert_front(value);
        else if (tail->data <= value)
            insert_end(value);
        else {
            // Find the node I am less than. Then I am before it
            for (Node* cur = head, *prv = nullptr; cur; prv = cur, cur = cur->next) {
                if (value <= cur->data) {
                    embed_after(prv, value);
                    break;
                }
            }
        }
        debug_verify_data_integrity();

        // This idea is used in Insertion Sort Algorithm
    }

    void swap_head_tail() { // O(n) time, O(1) memory
        if (!head || !head->next)
            return;

        Node* prev = get_nth(length - 1);
        prev->next = head;
        tail->next = head->next;
        head->next = nullptr;
        swap(head, tail);

        debug_verify_data_integrity();
    }

    void left_rotate(int k) { // O(n) timer, O(1) memory
        if (k % length == 0) return;
        if (!head || !head->next) return;
        k %= length;

        Node* last = get_nth(k);
        tail->next = head;
        head = last->next;
        last->next = nullptr;
        tail = last;

        debug_verify_data_integrity();
    }

    void remove_duplicates() { // O(n^2) time, O(1) memory
        if (length <= 1)
            return;

        for (Node* cur1 = head; cur1; cur1 = cur1->next) {
            for (Node* cur2 = cur1->next, *prev = cur1; cur2;) {
                if (cur1->data == cur2->data) {
                    delete_next_node(prev);
                    cur2 = prev->next;
                }
                else prev = cur2, cur2 = cur2->next;
            }
        }

        debug_verify_data_integrity();
    }

    void remove_last_occurance(int key) { // O(n) time, O(1) memory
        if (length <= 1) return;

        int cnt{ 1 }, last_occ{};
        for (Node* cur = head; cur; cur = cur->next) {
            if (cur->data == key)
                last_occ = cnt;
            cnt++;
        }
        if (last_occ)
            delete_nth(last_occ);

        debug_verify_data_integrity();
    }

    Node* move_back(Node* cur, Node* prv) {
        if (tail == cur) return cur; // already at end
        Node* next = cur->next;
        tail->next = cur;

        if (prv)
            prv->next = next;
        else
            head = next;

        tail = cur;
        tail->next = nullptr;
        return next;
    }

    void move_all_occurance(int key) { // O(n) time, O(1) memory
        if (length <= 1) return;

        int len = length;
        for (Node* prv = nullptr, *cur = head; len--;) {
            if (cur->data == key) {
                cur = move_back(cur, prv);
            }
            else prv = cur, cur = cur->next;
        }
        debug_verify_data_integrity();
    }

    int max(Node* head = nullptr, bool is_first_call = true) {
        if (is_first_call)
            return this->max(this->head, false);

        if (head == nullptr)
            return INT_MIN;

        return std::max(head->data, this->max(head->next, false));
        // 1 5 3 8 => 8
        // 1, 8 ______^
        // 5, 8
        // 3, 8
        // 8, int_min
        // int_min
    }

    void arrange_odd_even_nodes() { // O(n) time, O(1) memory
        if (length <= 1) return;

        int len = length;
        int cnt = 1;
        for (Node* prv = nullptr, *cur = head; len--;) {
            if (cnt % 2 == 0) {
                cur = move_back(cur, prv);
                cnt++;
            }
            else prv = cur, cur = cur->next, cnt++;
        }
        debug_verify_data_integrity();
    }

    void insert_after(Node* src, Node* target) {
        assert(src && target);
        target->next = src->next;
        src->next = target;
        debug_add_node(target);
        length++;
    }

    void insert_alternate(LinkedList& another) { // O(n) time, O(1) memory
        if (!another.length) return;

        if (!length) {
            head = another.head;
            tail = another.tail;
            length = another.length;
            debug_data = another.debug_data;
        }
        else {
            Node* cur2 = another.head;
            for (Node* cur1 = head; cur1 && cur2; ) {
                Node* cur2_next_tmp = cur2->next;
                insert_after(cur1, cur2);
                another.length--;
                cur2 = cur2_next_tmp;
                if (cur1 == tail) {
                    tail = another.tail;
                    cur1->next->next = cur2;
                    length += another.length;
                    break;
                }
                cur1 = cur1->next->next;
            }
        }
    }

    void add_number(LinkedList& other) {
        if (!other.length) return;

        Node* myCur = head;
        Node* hisCur = other.head;
        int carry = 0, myVal, hisVal;

        while (myCur || hisCur) {
            myVal = hisVal = 0;

            if (myCur)
                myVal = myCur->data;
            if (hisCur) {
                hisVal = hisCur->data;
                hisCur = hisCur->next;
            }

            myVal += hisVal + carry;
            carry = myVal / 10;
            myVal %= 10;

            if (myCur) {
                myCur->data = myVal;
                myCur = myCur->next;
            }
            else
                insert_end(myVal);
        }
        if (carry)
            insert_end(carry);

        debug_verify_data_integrity();
    }


    ////////////////////////////////////////////////////////////
};



int main() {
    LinkedList list1;
    list1.insert_end(9);
    list1.insert_end(6);
    list1.insert_end(5);

    LinkedList list2;
    list2.insert_end(8);
    list2.insert_end(7);
    list2.insert_end(6);
    list2.insert_end(4);
    list2.insert_end(5);
    list2.insert_end(7);
    list2.insert_end(8);
    list2.insert_end(9);

    list1.print();
    list2.print();
    list1.add_number(list2);
    list1.print();

    return 0;
}

