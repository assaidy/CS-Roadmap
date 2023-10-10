#include <iostream>
#include <cassert>
using namespace std;

// The first linked list represents the row CONTENT: for each column, what is its data
// It is a bit confusing, but recall it eventually represents a row content
struct ColumnNode {
	int data { };
	int column { };
	ColumnNode* next { };
	ColumnNode* prev { };

	ColumnNode(int data, int column) :
			data(data), column(column) {
	}
};

class ColumnLinkedList {
private:
	ColumnNode *head { };
	ColumnNode *tail { };
	int length = 0;
	int cols { };	// Total number of columns

	void link(ColumnNode* first, ColumnNode*second) {
		if (first)
			first->next = second;
		if (second)
			second->prev = first;
	}

	ColumnNode* embed_after(ColumnNode* node_before, int data, int col) {
		ColumnNode* middle = new ColumnNode(data, col);
		++length;

		ColumnNode* node_after = node_before->next;
		link(node_before, middle);

		if (!node_after)
			tail = middle;
		else
			link(middle, node_after);

		return middle;
	}

	// Return the node of this column
	ColumnNode* get_col(int col, bool is_create_if_missing) {
		ColumnNode* prev_col = head;
		// Find the node with col-1
		while (prev_col->next && prev_col->next->column < col)
			prev_col = prev_col->next;

		bool found = prev_col->next && prev_col->next->column == col;

		if (found)
			return prev_col->next;

		if (!is_create_if_missing)
			return nullptr;

		return embed_after(prev_col, 0, col);
	}
public:
	ColumnLinkedList(int cols) :
			cols(cols) {
		// Dummy node of col = -1, to make coding shorter and more robust!
		// Reading: https://en.wikipedia.org/wiki/Sentinel_node
		tail = head = new ColumnNode(0, -1);
		++length;
	}

	void print_row() {
		ColumnNode* cur = head->next;

		for (int c = 0; c < cols; ++c) {
			if (cur && cur->column == c) {
				cout << cur->data << " ";
				cur = cur->next;
			} else
				cout << "0 ";
		}
		cout << "\n";
	}

	void print_row_nonzero() {
		for (ColumnNode* cur = head->next; cur; cur = cur->next)
			cout << cur->data << " ";
		cout << "\n";
	}
	void set_value(int data, int col) {
		get_col(col, true)->data = data;
	}

	int get_value(int col) {
		ColumnNode* node = get_col(col, false);
		if (!node)
			return 0;
		return node->data;
	}
	void add(ColumnLinkedList &other) {
		assert(cols == other.cols);

		// Iterate on the other first, and add it to the current one
		for (ColumnNode* other_cur = other.head->next; other_cur; other_cur = other_cur->next) {
			ColumnNode* this_col = get_col(other_cur->column, true);  // **
			this_col->data += other_cur->data;
		}
		// ** We can make this function more efficient, but let's keep simple
	}
};


// not completed

int main() {

    return 0;
}
