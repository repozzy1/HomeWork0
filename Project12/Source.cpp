#include <iostream>

class DynamicArray {
private:
    int* data;
    int size;
    int capacity;

public:
    DynamicArray(int capacity) : size(0), capacity(capacity), data(nullptr) {
        std::cout << "Constructor called. Capacity: " << capacity << std::endl;
        if (capacity > 0) {
            data = new int[capacity];
        }
    }

    ~DynamicArray() {
        std::cout << "Destructor called. Size: " << size << ", Capacity: " << capacity << std::endl;
        delete[] data;
    }

    DynamicArray(const DynamicArray& other) : size(other.size), capacity(other.capacity) {
        std::cout << "Copy constructor called." << std::endl;
        std::cout << "  - Copying size: " << other.size << std::endl;
        std::cout << "  - Copying capacity: " << other.capacity << std::endl;

        if (other.data != nullptr) {
            data = new int[capacity];
            std::cout << "  - Allocating new memory." << std::endl;

            for (int i = 0; i < size; ++i) {
                data[i] = other.data[i] + 1;
                std::cout << "  - Copying element at index " << i << ": " << other.data[i] << " + 1 = " << data[i] << std::endl;
            }
        }
        else {
            data = nullptr;
            std::cout << "  - Original array is empty, assigning nullptr to data." << std::endl;
        }
    }

    int getSize() const { return size; }
    int getCapacity() const { return capacity; }
    int getElement(int index) const { return data[index]; }

    void setElement(int index, int value) { data[index] = value; }

    void push_back(int value) {
        if (size < capacity) {
            data[size] = value;
            size++;
        }
        else {
            std::cout << "Array is full!" << std::endl;
        }
    }
};

int main() {
    DynamicArray arr1(5);
    arr1.push_back(10);
    arr1.push_back(20);
    arr1.push_back(30);

    std::cout << "Original array:" << std::endl;
    std::cout << "Size: " << arr1.getSize() << std::endl;
    std::cout << "Capacity: " << arr1.getCapacity() << std::endl;
    for (int i = 0; i < arr1.getSize(); ++i) {
        std::cout << "Element at " << i << ": " << arr1.getElement(i) << std::endl;
    }

    DynamicArray arr2 = arr1; // Copy constructor called here
    std::cout << "\nCopied array:" << std::endl;
    std::cout << "Size: " << arr2.getSize() << std::endl;
    std::cout << "Capacity: " << arr2.getCapacity() << std::endl;
    for (int i = 0; i < arr2.getSize(); ++i) {
        std::cout << "Element at " << i << ": " << arr2.getElement(i) << std::endl;
    }

    return 0;
}