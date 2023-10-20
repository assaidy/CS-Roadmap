#include <filesystem>
#include <iostream>
#include <cassert>

struct Node {
    int data {};
    Node *left {};
    Node *right {};

    Node(int data) : data(data) {}
};

void print(Node *node) {
    if (!node->right && !node->left) {
        std::cout << node->data << "\n";
        return;
    }

    std::cout << node->data << " ";

    if (node->right)
        print(node->right);

    if (node->left)
        print(node->left);
}

int main() {
    Node *root = new Node(1);
    Node *node2 = new Node(2);
    Node *node3 = new Node(3);
    Node *node4 = new Node(4);
    Node *node5 = new Node(5);
    Node *node6 = new Node(6);
    Node *node7 = new Node(7);
    Node *node8 = new Node(8);

    // linking
    root->left = node2;
    root->right = node3;

    node2->left = node4;
    node2->right = node5;

    node3->right = node6;
    
    node5->right = node7;
    
    node6->left = node8;

    // std::cout << root->left->right->right->data << "\n";
    // std::cout <<      node2->right->right->data << "\n";
    // std::cout <<             node5->right->data << "\n";
    // std::cout <<                    node7->data << "\n";

    print(root);

    return 0;
}
