#include <iostream>
#include <string>

class DynamicArray {
private:
    int* data;        
    int size;        
    int capacity;      

public:
    // 1. Конструктор
    DynamicArray(int capacity) : size(0), capacity(capacity) {
        std::cout << "DynamicArray() - Constructor called. Capacity: " << capacity << std::endl;
        if (capacity > 0) {
            data = new int[capacity];
        }
        else {
            data = nullptr;
            std::cerr << "Warning: Invalid capacity. Array initialized with capacity 0." << std::endl;
        }
    }

    // 2. Деструктор
    ~DynamicArray() {
        std::cout << "~DynamicArray() - Destructor called. Size: " << size << ", Capacity: " << capacity << std::endl;
        delete[] data;
    }

    // 3. Конструктор копирования
    DynamicArray(const DynamicArray& other) : size(other.size), capacity(other.capacity + 1) {
        std::cout << "DynamicArray(const DynamicArray&) - Copy constructor called." << std::endl;
        std::cout << "  - Copying size: " << other.size << " to new size: " << size << std::endl;
        std::cout << "  - Copying capacity: " << other.capacity << " to new capacity: " << capacity << std::endl;

        if (other.data != nullptr) {
            data = new int[capacity];
            std::cout << "  - Allocating new memory with capacity: " << capacity << std::endl;
            for (int i = 0; i < size; ++i) {
                data[i] = other.data[i] + 1; 
                std::cout << "  - Copying element at index " << i << ": " << other.data[i] << " to " << data[i] << std::endl;
            }
        }
        else {
            data = nullptr;
            std::cout << "  - Other array is empty, assigning nullptr to data." << std::endl;
        }
    }

    // Оператор присваивания (чтобы избежать проблем при присваивании объектов)
    DynamicArray& operator=(const DynamicArray& other) {
        std::cout << "operator=(const DynamicArray&) - Assignment operator called." << std::endl;
        if (this != &other) { 

            delete[] data; 

            size = other.size;
            capacity = other.capacity + 1;
            std::cout << "  - Assigning size: " << other.size << " and capacity: " << capacity << std::endl;

            if (other.data != nullptr) {
                data = new int[capacity];
                std::cout << "  - Allocating new memory with capacity: " << capacity << std::endl;

                for (int i = 0; i < size; ++i) {
                    data[i] = other.data[i] + 1;
                    std::cout << "  - Copying element at index " << i << ": " << other.data[i] << " to " << data[i] << std::endl;

                }
            }
            else {
                data = nullptr;
            }
        }
        else {
            std::cout << "  - Self-assignment detected, skipping assignment." << std::endl;
        }
        return *this;
    }

    // 4. Сеттеры и геттеры
    int getSize() const {
        return size;
    }

    int getCapacity() const {
        return capacity;
    }

    int getElement(int index) const {
        if (index >= 0 && index < size) {
            return data[index];
        }
        else {
            std::cerr << "Error: Index out of bounds." << std::endl;
            return -1; 
        }
    }

    void setElement(int index, int value) {
        if (index >= 0 && index < size) {
            data[index] = value;
        }
        else {
            std::cerr << "Error: Index out of bounds." << std::endl;
        }
    }

    void push_back(int value) {
        if (size < capacity) {
            data[size] = value;
            size++;
        }
        else {
            std::cerr << "Error: Array is full." << std::endl;
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const DynamicArray& arr) {
        os << "DynamicArray(size=" << arr.size << ", capacity=" << arr.capacity << "): [";
        for (int i = 0; i < arr.size; ++i) {
            os << arr.data[i];
            if (i < arr.size - 1) {
                os << ", ";
            }
        }
        os << "]";
        return os;
    }
};

int main() {

    DynamicArray arr1(5);
    arr1.push_back(10);
    arr1.push_back(20);
    arr1.push_back(30);

    std::cout << "Original array: " << arr1 << std::endl;

    DynamicArray arr2 = arr1; 
    std::cout << "Copied array: " << arr2 << std::endl;

    DynamicArray arr3(3);
    arr3 = arr1; 
    std::cout << "Assigned array: " << arr3 << std::endl;

    std::cout << "Element at index 1 in arr1: " << arr1.getElement(1) << std::endl;
    arr1.setElement(1, 25);
    std::cout << "Element at index 1 in arr1 after setting: " << arr1.getElement(1) << std::endl;
    std::cout << "Original array after changes: " << arr1 << std::endl;
    std::cout << "Copied array after changes: " << arr2 << std::endl; 
    std::cout << "Assigned array after changes: " << arr3 << std::endl; 
}