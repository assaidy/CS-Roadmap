#include <cassert>
#include <iostream>
using namespace std;

struct ArrayNode {
    int data {};
    int index {};
    ArrayNode *next {};
    ArrayNode *prev {};

    ArrayNode(int data, int index) : 
        data(data), index(index) {}
};

class ArrayLinkedList {
    private:
        ArrayNode *head {};
        ArrayNode *tail {};
        int lenght {};
        int array_length {};

        void link(ArrayNode *first, ArrayNode *second) {
            if (first)
                first->next = second;
            if (second)
                second->prev = first;
        }

        ArrayNode *embed_after(ArrayNode *node_before, int value, int index) {
            ArrayNode *node_middle = new ArrayNode(value, index);
            lenght++;

            ArrayNode *node_after = node_before->next;
            link(node_before, node_middle);

            if (!node_after)
                tail = node_middle;
            else
                link(node_middle, node_after);

            return node_middle;
        }

        ArrayNode *get_in_index(int index, bool create_if_missing) {
            ArrayNode *prev_index = head;

            while (prev_index->next && prev_index->next->index < index)
                prev_index = prev_index->next;

            bool found = prev_index->next && prev_index->next->index == index;

            if (found)
                return prev_index->next;

            if (!create_if_missing)
                return nullptr;

            return embed_after(prev_index, 0, index);
        }

    public:
        ArrayLinkedList(int array_length) : array_length(array_length) {
            head = tail = new ArrayNode(0 , -1);
            lenght++;
        }
        ArrayLinkedList(const ArrayLinkedList&) = delete;
        ArrayLinkedList &operator=(const ArrayLinkedList &another) = delete;

        void print() {
            ArrayNode *cur = head->next;

            for (int i = 0; i < array_length; i++) {
                if (cur && cur->index == i) {
                    std::cout << cur->data << " ";
                    cur = cur->next;
                } else
                    std::cout << "0 ";
            }
            std::cout << "\n";
        }

        void print_nz() {
            for (ArrayNode *cur = head->next; cur; cur = cur->next)
                std::cout << cur->data << " ";
            std::cout << "\n";
        }

        void set_value(int val, int idx) {
            get_in_index(idx, true)->data = val;
        }

        int get_value(int idx) {
            ArrayNode *node = get_in_index(idx, false);
            if (!node)
                return 0;
            return node->data;
        }

        void add(ArrayLinkedList &other) {
            assert(array_length == other.array_length);

            for (ArrayNode *other_cur = other.head->next; other_cur; other_cur = other_cur->next) {
                ArrayNode *this_index = get_in_index(other_cur->index, true);
                this_index->data += other_cur->data;
            }
        }
};

void test_index() {
	ArrayLinkedList array(10);	// length 10
	array.set_value(50, 5);
	array.set_value(20, 2);
	array.set_value(70, 7);
	array.set_value(40, 4);
	array.print();
	// 0 0 20 0 40 50 0 70 0 0
	array.print_nz();
	// 20 40 50 70
	cout << array.get_value(7) << "\n";	// 70

	ArrayLinkedList array2(10);
	array2.set_value(1, 4);
	array2.set_value(3, 7);
	array2.set_value(4, 6);

	array.add(array2);
	array.print();
	// 0 0 20 0 41 50 4 73 0 0
}

int main() {
    test_index();

	cout << "\n\n\nNO RTE\n";
    return 0;
}
