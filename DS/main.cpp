#include <iostream>
#include <assert.h>

class Vector
{
private:
    int* arr;
    int size{ 0 };

public:
    Vector(int _size) : size(_size) {
        if (size < 0)
            size = 1;
        arr = new int[size] {};
    }

    int get(int idx) {
        assert(idx >= 0 && idx < size);
        return arr[idx];
    }

    void set(int idx, int val) {
        assert(idx >= 0 && idx < size);
        arr[idx] = val;
    }

    void print() {
        for (int i = 0; i < size; i++) {
            std::cout << arr[i] << ' ';
        }
        std::cout << '\n';
    }

    int find(int val) {
        for (int i = 0; i < size; i++) {
            if (arr[i] == val)
                return i;
        }
        return -1;
    }

    ~Vector() {
        delete[] arr;
        arr = nullptr;
    }
};


int main() {
    Vector v(10);
    for (int i = 0; i < 10; i++) {
        v.set(i, i);
    }
    v.print();
    std::cout << v.find(5) << " " << v.find(50) << '\n';

    return 0;
}
