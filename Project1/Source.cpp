#include <iostream>
#include <vector>

int main() {
    int numPointers;
    std::cout << "¬ведите количество указателей: ";
    std::cin >> numPointers;

    int object = 42;

    std::vector<int*> pointers;
    pointers.reserve(numPointers);

    for (int i = 0; i < numPointers; ++i) {
        pointers.push_back(&object);
        std::cout << "”казатель " << i + 1 << ": " << pointers[i] << std::endl;
    }
}