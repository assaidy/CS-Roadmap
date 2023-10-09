#include <iostream>
#include <cassert>
#include <climits>
#include <string>
#include <vector>		// for debug
#include <algorithm>
#include <sstream>
using namespace std;

struct Node {
	int data { };
	Node* next { };
	Node* prev { };	 // Previous node!

	Node(int data) : data(data) {}

	void set(Node* next, Node* prev) {
		this->next = next;
		this->prev = prev;
	}

	~Node() {
		cout << "Destroy value: " << data << " at address " << this << "\n";
	}
};

class LinkedList {
private:
	Node *head { };
	Node *tail { };
	int length = 0;

	// let's maintain how many nodes

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
	LinkedList &operator=(const LinkedList &another) = delete;

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

		if (node->prev == nullptr)
			cout << "X\t";
		else
			cout << node->prev->data << "\t";

		cout << " <= [" <<node->data << "]\t => \t";

		if (node->next == nullptr)
			cout << "X\t";
		else
			cout << node->next->data << "\t";

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
		for (int i = 0; i < (int) debug_data.size(); ++i)
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
		} else {
			assert(head != nullptr);
			assert(tail != nullptr);
			if (length == 1)
				assert(head == tail);
			else
				assert(head != tail);
			assert(!head->prev);
			assert(!tail->next);
		}
		int len = 0;
		for (Node* cur = head; cur; cur = cur->next, len++) {
			if (len == length-1)	// make sure we end at tail
				assert(cur == tail);
		}

		assert(length == len);
		assert(length == (int )debug_data.size());

		len = 0;
		for (Node* cur = tail; cur; cur = cur->prev, len++) {
			if (len == length-1)	// make sure we end at head
				assert(cur == head);
		}
		cout << "\n";
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

    void link(Node *first, Node *second) {
        if (first)
            first->next = second;
        if (second)
            second->prev = first;
    }

    void insert_end(int val) {
        Node *node = new Node(val);
        add_node(node);

        if (!head)
            head = tail = node;
        else {
            link(tail, node);
            tail = node;
        }
        debug_verify_data_integrity();
    }

    void insert_front(int val) {
        Node *node = new Node(val);
        add_node(node);

        if (!head)
            head = tail = node;
        else {
            link(node, head);
            head = node;
        }
        debug_verify_data_integrity();
    }

	void print_reversed()  {
		for (Node* cur = tail; cur; cur = cur->prev)
			cout << cur->data << " ";
		cout << "\n";
	}

	void embed_after(Node* node_before, int value) {
        Node *middle = new Node(value);
        debug_add_node(middle);
        length++;

        Node *node_after = node_before->next;
        link(node_before, middle);
        link(middle, node_after);
	}

	void insert_sorted(int value) {		// O(n) time - O(1) memory
		// 3 special cases for simplicity
		if (!length || value <= head->data)
			insert_front(value);
		else if (tail->data <= value)
			insert_end(value);
		else {
			// Find the node I am less than. Then I am before it
			for (Node *cur = head; cur; cur = cur->next) {
                if (value <= cur->data) {
                    embed_after(cur->prev, value);
                    break;
                }
			}
		}
		debug_verify_data_integrity();

		// This idea is used in Insertion Sort Algorithm
	}

    void delete_front() {
        if (!head)
            return;
        Node *cur = head->next;
        delete_node(head);
        head = cur;

        if (head)
            head->prev = nullptr;
        if (!length)
            tail = nullptr;

        debug_verify_data_integrity();
    }

    void delete_end() {
        if (!head)
            return;
        Node *cur = tail->prev;
        delete_node(tail);
        tail = cur;

        if (tail) 
            tail->next = nullptr;
        else if (!length)
            head = nullptr;

        debug_verify_data_integrity();
    }

    Node *delete_and_link(Node *cur) {
        Node *ret = cur->prev;
        link(cur->prev, cur->next);
        delete_node(cur);
        return ret;
    }

    void delete_with_key(int value) {
        if (!length)
            return;
        if (value == head->data)
            delete_front();
        else {
            for (Node *cur = head; cur; cur = cur->next) {
                if (cur->data == value) {
                    cur = delete_and_link(cur);
                    if (!cur->next)
                        tail = cur;
                    break;
                }
            }
        }
        debug_verify_data_integrity();
    }

    ///////////////////////////// HW //////////////////////////////////////////
    void delete_all_with_key(int value) {
        if (!length)
            return;

        insert_front(-value);

        for (Node *cur = head; cur; cur = cur->next) {
            if (value == cur->data) {
                cur = delete_and_link(cur);
                if (!cur->next)
                    tail = cur;
            }
        }
        delete_front();
        debug_verify_data_integrity();
    }

    void delete_even_positions() {
        if (length <= 1)
            return;
        for (Node *cur = head; cur && cur->next; cur = cur->next) {
            delete_and_link(cur->next);
            if (!cur->next)
                tail = cur;
        }
        debug_verify_data_integrity();
    }

    void delete_odd_positions() {
        insert_front(-1);
        delete_even_positions();
        delete_front();
        debug_verify_data_integrity();
    }

    bool is_palindrome() {
        if (length <= 1) return true;
        if (length == 2) {
            if (head->data == tail->data) return true;
            else return false;
        }

        int len = length / 2;
        for (Node *cur = head, *opp = tail; len; len--) {
            std::cout << cur->data << " " << opp->data << "\n";
            if (cur->data != opp->data) return false;
            cur = cur->next;
            opp = opp->prev;
        }
        return true;
    }

    int get_middle1() {
        if (!length) return 0;

        Node *h = head, *t = tail;
        while (h != t && h != t->prev)
            h = h->next, t = t->prev;
        return t->data;
    }

    int get_middle2() {
        if (!length) return 0;

        Node *slow = head, *fast = head;
        while (fast && fast->next)
            slow = slow->next, fast = fast->next->next;
        return slow->data;
    }

    Node *get_nth(int n) {
        int cnt = 0;
        for (Node *cur = head; cur; cur = cur->next) {
            if (++cnt == n)
                return cur;
        }
        return nullptr;
     }

    void swap(int k) {
        if (length <= 1) return;
        int k_back = length - k + 1;
        if (k == k_back) return;

        Node *first = get_nth(k);
        Node *last = get_nth(k_back);

        Node *last_next = last->next;
        Node *last_prev = last->prev;

        Node *first_next = first->next;
        Node *first_prev = first->prev;

        last->next = first->next;
        last->prev = first->prev;
        first->next = last_next;
        first->prev = last_prev;

        if (k + 1 == k_back) { // consecutive (neighbours)
            link(first_prev, last);
            link(last, first);
            link(first, last_next);
        } else {
            link(first_prev, last);
            link(last, first_next);

            link(last_prev, first);
            link(first, last_next);
        }
        if (k == 1)
            std::swap(head, tail);
        debug_verify_data_integrity();
    }

    // using dll {1, 2, 3, 4, 5} => {5, 4, 3, 2, 1}
    void reverse() { // O(n) time, O(1) memory
        if (length <= 1) return;

        for (Node *cur = head; cur; ) {
            Node *next = cur->next;
            std::swap(cur->next, cur->prev);
            cur = next;
        }
        std::swap(head, tail);
        debug_verify_data_integrity();
    }

    // TODO: O(n+m) time, O(1) memory
    void merge_2sorted_lists(LinkedList &other) {
        debug_verify_data_integrity();
    }

};

void test1() {
	cout << "\n\ntest1\n";
	LinkedList list;

	list.insert_end(3);
	list.insert_end(5);
	list.insert_end(7);
	list.insert_sorted(2);
	list.insert_sorted(9);
	list.insert_sorted(7);
	list.insert_sorted(4);
	list.insert_sorted(1);

	list.print();
	//list.print_reversed();

	string expected = "1 2 3 4 5 7 7 9";
	string result = list.debug_to_string();
	if (expected != result) {
		cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
		assert(false);
	}
	list.debug_print_list("********");
}

// delete_all_with_key();
void test2() {
	cout << "\n\ntest2\n";
	LinkedList list;

	list.insert_end(4);
	list.insert_end(2);
	list.insert_end(5);
	list.insert_end(4);
	list.insert_end(5);
	list.insert_end(4);
	list.insert_end(4);

    list.delete_all_with_key(4);
	list.print();
	//list.print_reversed();

	string expected = "2 5 5";
	string result = list.debug_to_string();
	if (expected != result) {
		cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
		assert(false);
	}
	list.debug_print_list("********");
}

void test3() {
	cout << "\n\ntest3\n";
	LinkedList list;

	list.insert_end(1);
	list.insert_end(2);
	list.insert_end(3);
	list.insert_end(4);
	list.insert_end(5);
	list.insert_end(6);

    list.delete_even_positions();
	list.print();
	//list.print_reversed();

	string expected = "1 3 5";
	string result = list.debug_to_string();
	if (expected != result) {
		cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
		assert(false);
	}
}

void test4() {
	cout << "\n\ntest4\n";
	LinkedList list;

	list.insert_end(1);
	list.insert_end(2);
	list.insert_end(3);
	list.insert_end(4);
	list.insert_end(5);

    list.delete_odd_positions();
	list.print();
	//list.print_reversed();

	string expected = "2 4";
	string result = list.debug_to_string();
	if (expected != result) {
		cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
		assert(false);
	}
}

void test5() {
	cout << "\n\ntest5\n";
	LinkedList list;

    bool result = list.is_palindrome();
	list.print();

	bool expected = true;
	if (expected != result) {
		cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
		assert(false);
	}
}

void test6() {
	cout << "\n\ntest6\n";
	LinkedList list;

    list.insert_end(1);
    list.insert_end(2);
    list.insert_end(3);
    list.insert_end(4);
    list.insert_end(5);
    list.insert_end(6);

    int result = list.get_middle2();
	list.print();

	int expected = 4;
	if (expected != result) {
		cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
		assert(false);
	}
}

void test7() {
	cout << "\n\ntest7\n";
	LinkedList list;

    list.insert_end(1);
    list.insert_end(2);
    list.insert_end(3);
    list.insert_end(4);
    list.insert_end(5);

    list.swap(2);
	list.print();

	string expected = "1 4 3 2 5";
	string result = list.debug_to_string();
    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
}

void test8() {
	cout << "\n\ntest8\n";
	LinkedList list;

    list.insert_end(1);
    list.insert_end(2);
    list.insert_end(3);
    list.insert_end(4);
    list.insert_end(5);

    list.reverse();
	list.print();

	string expected = "5 4 3 2 1";
	string result = list.debug_to_string();
    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
}

void test9() {
	cout << "\n\ntest9\n";
	LinkedList list;
    list.insert_end(10);
    list.insert_end(20);
    list.insert_end(30);
    list.insert_end(40);
    // list.insert_end(50);

    LinkedList list2;
    list2.insert_end(15);
    list2.insert_end(17);
    list2.insert_end(22);
    list2.insert_end(24);
    list2.insert_end(35);

    list.merge_2sorted_lists(list2);
	list.print();

	string expected = "10 15 17 20 22 24 30 35 40 50";
	string result = list.debug_to_string();
    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
}

int main() {
	test9();

	// must see it, otherwise RTE
	cout << "\n\nNO RTE\n";

	return 0;
}

