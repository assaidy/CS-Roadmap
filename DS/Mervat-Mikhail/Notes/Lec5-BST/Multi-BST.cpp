#include <iostream>

// INFO: Unique Binary Search Tree
class MBST {
private:
    int data {};
    int counter {1};
    MBST *left {};
    MBST *right {};

    void clear(MBST *bt) {
        std::cout << "destroing node of value " << bt->data 
            << " at address " << bt << "\n";
        delete bt;
    }

public:
    // initialize the  BST with a root
    MBST(int data) : data(data) {}

    int get_data() {
        return data;
    }

    // INFO: return a pointer to the new node & nullptr if found
    MBST *insert(int key) { // O(h) time
        if (key < data) {
            if (left)
                return left->insert(key);
            else 
                left = new MBST(key);
            return left;
        }
        if (key > data) {
            if (right)
                return right->insert(key);
            else 
                right = new MBST(key);
            return right;
        }
        // equal
        counter++;
        return this;
    }

    // INFO: return a pointer to the node & nullptr if not found
    MBST *search(int key) { // O(h) time : h = height
        if (key == data)
            return this;
        if (left && key < data)
            return left->search(key);
        if (right && key > data)
            return right->search(key);
        return nullptr;
    }

    // INFO: delete a node with a given key & return the new BST
    MBST *delete_node(int key) {
        if (!this) return this;

        if (key < data)
            left = left->delete_node(key);
        else if (key > data)
            right = right->delete_node(key);
        else {
            if (!left) {
                MBST *tmp {right};
                delete this;
                return tmp;
            } else if (!right) {
                MBST *tmp {left};
                delete this;
                return tmp;
            } else {
                MBST *tmp {right->min()};
                this->data = tmp->data;
                right = right->delete_node(tmp->data);
            }
        }
        return this;
    } 

    void print() {
        if (left)
            left->print();
        std::cout << data << " [" << counter << "]" << "\n";
        if (right)
            right->print();
    }

    MBST *min() { // O(h) time
        if (!left)
            return this;
        return left->min();
    }

    MBST *max() { // O(h) time
        if (!right)
            return this;
        return right->max();
    }

    int height() { // O(h) time
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

    ~MBST() {
        if (left)
            clear(left);
        if (right)
            clear(right);
    }
};

int main() {
    MBST bst(13);
    std::cout << bst.insert(13) << "\n"; // 2
    std::cout << bst.insert(10) << "\n";
    std::cout << bst.insert(25) << "\n";
    std::cout << bst.insert(2)  << "\n";
    std::cout << bst.insert(12) << "\n";
    std::cout << bst.insert(20) << "\n";
    std::cout << bst.insert(20) << "\n";
    std::cout << bst.insert(20) << "\n"; // 3
    std::cout << bst.insert(31) << "\n";
    std::cout << bst.insert(29) << "\n";
    std::cout << bst.insert(29) << "\n"; // 2

    std::cout << "\n";
    bst.print();

    std::cout << "\n";
    std::cout << bst.search(13) << "\n";
    std::cout << bst.search(10) << "\n";
    std::cout << bst.search(31) << "\n";
    std::cout << bst.search(29) << "\n";
    std::cout << bst.search(1)  << "\n"; // 0

    std::cout << "\n";
    std::cout << bst.min()->get_data() << "\n"; // 2
    std::cout << bst.max()->get_data() << "\n"; // 29

    std::cout << "\n";
    std::cout << bst.height() << "\n"; // 3

    std::cout << "\n";
    MBST *bst_after_deletion {bst.delete_node(13)};
    std::cout << bst_after_deletion->search(13) << "\n"; // 0
    std::cout << bst_after_deletion->search(31) << "\n";
    bst_after_deletion = bst_after_deletion->delete_node(29);
    std::cout << bst_after_deletion->search(29) << "\n"; // 0
    std::cout << bst_after_deletion->search(31) << "\n";

    std::cout << "\n";
    return 0;
}
