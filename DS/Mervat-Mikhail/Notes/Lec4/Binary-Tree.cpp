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
        std::cout << "destroing node of value " << bt->data 
            << " at address " << bt << "\n";
        delete bt;
    }

    ~BinaryTree() {
        if (left)
            delete_bt(left);
        if (right)
            delete_bt(right);
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
    return 0;
}
