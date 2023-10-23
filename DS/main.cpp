#include <algorithm>
#include <cmath>
#include <cstddef>
#include <ios>
#include <iostream>
#include <cassert>
#include <iterator>
#include <vector>
#include <queue>
using namespace std;

class BinaryTree {
private:
    int data {};
    BinaryTree *left {};
    BinaryTree *right {};

public:
    BinaryTree(int data) : data(data) {}

    void print_inorder() {
        if (left)
            left->print_inorder();
        std::cout << data << " ";
        if (right)
            right->print_inorder();
    }

    void add(vector<int> values, vector<char> directions) {
        assert(values.size() == directions.size());
        BinaryTree *cur = this;
        for (size_t i = 0; i < values.size(); i++) {
            if (directions[i] == 'L') {
                if (!cur->left)
                    cur->left = new BinaryTree(values[i]);
                else
                    assert(cur->left->data == values[i]);
                cur = cur->left;
            }
            else {
                if (!cur->right)
                    cur->right = new BinaryTree(values[i]);
                else
                    assert(cur->right->data == values[i]);
                cur = cur->right;
            }
        }
    }

    //////////////////////// HW 1 ////////////////////////////////

    int tree_max() { // preorder style [VLR]
        int res = data;
        if (left)
            res = std::max(res, left->tree_max());
        if (right)
            res = std::max(res, right->tree_max());
        return res;
    }

    int height() {
        int cnt_left {0};
        int cnt_right {0};
        if (left)
            cnt_left = 1 + left->height();
        if (right)
            cnt_right = 1 + right->height();
        return std::max(cnt_right, cnt_left);
    }

    int total_nodes() {
        int cnt {1};
        if (left)
            cnt += left->total_nodes();
        if (right)
            cnt += right->total_nodes();
        return cnt;
    }

    int total_leafs() {
        int cnt {};
        if (!left && !right)
            return 1;
        if (left)
            cnt += left->total_leafs();
        if (right)
            cnt += right->total_leafs();
        return cnt;
    }

    bool is_exist(int value) {
        bool status {data == value};
        if (!status && left)
            status = left->is_exist(value);
        if (!status && right)
            status = right->is_exist(value);
        return status;
    }

	bool is_perfect(int h = -1) {
		if (h == -1)	// first call
			h = height();

		// All leaves must be on the same last level
		if (!left && !right)
			return h == 0;

		if ((!left && right) || (left && !right))
			return false;	// one child!

		// perfect on level h is perfect on h-1 for children
		return left->is_perfect(h - 1) && right->is_perfect(h - 1);
	}

    bool is_perfect_formula() {
		int h = height();
		int n = total_nodes();
		return std::pow(2, h + 1) - 1 == n;
    }

    /////////////////// //// Level order traversal ///////////////////////
    void level_order_traversal1() {
        std::queue<BinaryTree *> node_queue;
        node_queue.push(this);

        while (!node_queue.empty()) {
            auto cur = node_queue.front();
            node_queue.pop();

            std::cout << cur->data << " ";
            if (cur->left)
                node_queue.push(cur->left);
            if (cur->right)
                node_queue.push(cur->right);
        }
        std::cout << "\n";
    }

    void level_order_traversal2() {
        queue<BinaryTree *> node_queue;
        node_queue.push(this);

        int level = 0;
        while (!node_queue.empty()) {
            std::cout << "level: " << level << "\n";

            int sz = node_queue.size();
            while (sz--) {
                auto cur = node_queue.front();
                node_queue.pop();

                std::cout << cur->data << " ";
                if (cur->left)
                    node_queue.push(cur->left);
                if (cur->right)
                    node_queue.push(cur->right);
            }
            level++;
            std::cout << "\n";
        }
    }
};


int main() {
	BinaryTree tree1(2);
    tree1.add({3}, {'L'});
    tree1.add({13, 7}, {'R', 'L'});
    tree1.add({13, 8}, {'R', 'R'});

    tree1.level_order_traversal1();
    tree1.level_order_traversal2();

	return 0;
}

