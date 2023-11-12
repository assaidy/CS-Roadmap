#include <cwchar>
#include <iostream>
#include <assert.h>
#include <queue>
#include <vector>

class BinaryTree {
private:
    int data {};
    BinaryTree *left {};
    BinaryTree *right {};

public:
    // initialize the  BT with a root
    BinaryTree(int data) : data(data) {}

    // bft = breadth first search
    // dft = depth first search
    void bft() {
        std::queue<BinaryTree *> BinaryTreeQueue;
        BinaryTreeQueue.push(this);
        while (!BinaryTreeQueue.empty()) {
            BinaryTree *cur { BinaryTreeQueue.front() };
            BinaryTreeQueue.pop();
            std::cout << cur->data << " ";
            if (cur->left)
                BinaryTreeQueue.push(cur->left);
            if (cur->right)
                BinaryTreeQueue.push(cur->right);
        }
    }

    void dft_preorder() {
        std::cout << data << " ";
        if (left)
            left->dft_preorder();
        if (right)
            right->dft_preorder();
    }

    void dft_inorder() {
        if (left)
            left->dft_inorder();
        std::cout << data << " ";
        if (right)
            right->dft_inorder();
    }

    void dft_postorder() {
        if (left)
            left->dft_postorder();
        if (right)
            right->dft_postorder();
        std::cout << data << " ";
    }

    void add(std::vector<int> values, std::vector<char> direction) {
        assert(values.size() == direction.size());
        BinaryTree *current = this;
        for (size_t i = 0; i < values.size(); i++) {
            if (direction[i] == 'L') {
                if (!current->left) current->left = new BinaryTree(values[i]);
                else assert(current->left->data == values[i]);
                current = current->left;
            } else {
                if (!current->right) current->right = new BinaryTree(values[i]);
                else assert(current->right->data == values[i]);
                current = current->right;
            }
        }
    }

    void delete_bt(BinaryTree *bt) {
        std::cout << "destroing bt of value " << bt->data 
            << " at address " << bt << "\n";
        delete bt;
    }

    ~BinaryTree() {
        if (left)
            delete_bt(left);
        if (right)
            delete_bt(right);
    }

    ////////////////////// Problems /////////////////////////
    void print_leaf_nodes() {
        if (!left && !right) {
            std::cout << data << " ";
            return;
        }
        if (left)
            left->print_leaf_nodes();
        if (right)
            right->print_leaf_nodes();
    }

    bool exist(int value) {
        bool res {data == value};
        if (!res && left)
            res = left->exist(value);
        if (!res && right)
            res = right->exist(value);
        return res;
    }

    int count_leaves() {
        int res {!right && !left};
        if (left)
            res += left->count_leaves();
        if (right)
            res += right->count_leaves();
        return res;
    }

    // invert & return the new root [like a mirror]
    BinaryTree *invert() {
        BinaryTree *new_bt {new BinaryTree(data)};
        if (!left && !right)
            return new_bt;
        if (left)
            new_bt->right = left->invert();
        if (right)
            new_bt->left = right->invert();
        return new_bt;
    }

    int height() {
        if (!left && !right)
            return 0;
        int left_height {};
        int right_height {};
        if (left)
            left_height = left->height();
        if (right)
            right_height = right->height();
        return std::max(left_height, right_height) + 1;
    }

    int diameter() {
        if (!left && !right)
            return 0;
        int left_height {1};
        int right_height {1};
        if (left)
            left_height += left->height();
        if (right)
            right_height += right->height();
        return right_height + left_height;
    }
};

int main() {
    BinaryTree bt(1);
    bt.add({2, 6}, {'L', 'L'});
    bt.add({2, 7, 8}, {'L', 'R', 'R'});
    bt.add({3, 4, 5}, {'R', 'L', 'R'});

    bt.bft();
    std::cout << "\n";
    bt.dft_preorder();
    std::cout << "\n";
    bt.dft_inorder();
    std::cout << "\n";
    bt.dft_postorder();
    std::cout << "\n";

    //////////////////////////// problems /////////////
    std::cout << "\n==> problems: \n";
    bt.print_leaf_nodes(); // 6 8 5
    std::cout << "\n";
    std::cout 
        << bt.exist(1) 
        << bt.exist(11) 
        << bt.exist(6) << "\n"; // 1 0 1
    std::cout << bt.count_leaves() << "\n"; // 3
    BinaryTree *inverted_bt {bt.invert()};
    inverted_bt->bft(); // 1 3 2 4 7 6 5 8
    std::cout << "\n";
    std::cout << bt.height() << "\n"; // 3
    std::cout << bt.diameter() << "\n"; // 6
    return 0;
}
