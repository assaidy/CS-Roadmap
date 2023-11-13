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

    bool bst(int key) {
        if (key == data)
            return true;
        if (key < data && left)
            return left->bst(key);
        if (key > data && right)
            return right->bst(key);
        return false;
    }
};

int main() {
    BinaryTree bst(13);
    bst.add({10, 2}, {'L', 'L'});
    bst.add({10, 12}, {'L', 'R'});
    bst.add({25, 20}, {'R', 'L'});
    bst.add({25, 31, 29}, {'R', 'R', 'L'});

    std::cout << bst.bst(3) << "\n";

    return 0;
}
