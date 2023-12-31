#include <iostream>
#include <cassert>
#include <vector>
#include <queue>
#include <stack>
#include <cmath>
using namespace std;

class BinaryTree {
private:
	int data { };
	BinaryTree* left { };
	BinaryTree* right { };

public:

	BinaryTree(int data) :
			data(data) {
	}

	void add(vector<int> values, vector<char> direction) {
		assert(values.size() == direction.size());
		BinaryTree* current = this;
		// iterate on the path, create all necessary nodes
		for (int i = 0; i < (int) values.size(); ++i) {
			if (direction[i] == 'L') {
				if (!current->left)
					current->left = new BinaryTree(values[i]);
				else
					assert(current->left->data == values[i]);
				current = current->left;
			} else {
				if (!current->right)
					current->right = new BinaryTree(values[i]);
				else
					assert(current->right->data == values[i]);
				current = current->right;
			}
		}
	}

	void print_inorder() {
		if (left)
			left->print_inorder();
		cout << data << " ";
		if (right)
			right->print_inorder();
	}
	////////////////////////////////////////////

	int tree_max() {
		int res = data;
		if (left)
			res = max(res, left->tree_max());
		if (right)
			res = max(res, right->tree_max());
		return res;
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	

	int tree_height() {
		int res = 0;
		if (left)
			res = 1 + left->tree_height();
		if (right)
			res = max(res, 1 + right->tree_height());
		return res;
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	

	int total_nodes() {
		int res = 1;
		if (left)
			res += left->total_nodes();
		if (right)
			res += right->total_nodes();
		return res;
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	

	int leafs_count() {
		int res = !left && !right;
		if (left)
			res += left->leafs_count();
		if (right)
			res += right->leafs_count();
		return res;
	}
















	bool is_exists(int value) {
		bool res = value == data;
		if (!res && left)
			res = left->is_exists(value);
		if (!res && right)
			res = right->is_exists(value);
		return res;
	}















	bool is_perfect(int h = -1) {
		if (h == -1)	// first call
			h = tree_height();

		// All leaves must be on the same last level
		if (!left && !right)
			return h == 0;

		if (!left && right || left && !right)
			return false;	// one child!

		// perfect on level h is perfect on h-1 for children
		return left->is_perfect(h - 1) && right->is_perfect(h - 1);
	}

	bool is_perfect_fomula() {
		int h = tree_height();
		int n = total_nodes();
		return pow(2, h + 1) - 1 == n;
	}
};

void test1_numbers() {
	BinaryTree tree(1);
	tree.add( { 2, 4, 7 }, { 'L', 'L', 'L' });
	tree.add( { 2, 4, 8 }, { 'L', 'L', 'R' });
	tree.add( { 2, 5, 9 }, { 'L', 'R', 'R' });
	tree.add( { 3, 6, 15 }, { 'R', 'R', 'L' });

	assert(tree.tree_max() == 15);
	assert(tree.tree_height() == 3);
	assert(tree.total_nodes() == 10);
	assert(tree.leafs_count() == 4);

	assert(tree.is_exists(1));
	assert(tree.is_exists(15));
	assert(tree.is_exists(4));
	assert(!tree.is_exists(61));
}

void test2_is_perfect() {
	BinaryTree tree(1);

	assert(tree.is_perfect() == 1);

	tree.add( { 2 }, { 'L' });
	tree.add( { 3 }, { 'R' });

	assert(tree.is_perfect() == 1);

	tree.add( { 2, 4, 7 }, { 'L', 'L', 'L' });
	tree.add( { 2, 4, 8 }, { 'L', 'L', 'R' });
	tree.add( { 2, 5, 9 }, { 'L', 'R', 'R' });
	tree.add( { 3, 6, 15 }, { 'R', 'R', 'L' });

	assert(tree.is_perfect() == 0);

	tree.add( { 2, 5, 13 }, { 'L', 'R', 'L' });
	tree.add( { 3, 6, 12 }, { 'R', 'R', 'R' });
	tree.add( { 3, 14, 15 }, { 'R', 'L', 'L' });
	tree.add( { 3, 14, 16 }, { 'R', 'L', 'R' });

	assert(tree.is_perfect() == 1);	// now 8 leaf nodes
}

int main() {
	test1_numbers();
	test2_is_perfect();

	cout << "bye\n";

	return 0;
}

