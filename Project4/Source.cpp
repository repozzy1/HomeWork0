#include <iostream>
#include <vector>
#include <algorithm> // Для std::reverse

int main() {
    int N;

    // 1. Ввод размера вектора
    std::cout << "Введите размер вектора (N): ";
    std::cin >> N;

    // 2. Объявление вектора
    std::vector<int> numbers;

    // 3. Ввод чисел и добавление в вектор
    std::cout << "Введите " << N << " чисел:" << std::endl;
    for (int i = 0; i < N; ++i) {
        int number;
        std::cin >> number;
        numbers.push_back(number); // Добавляем число в конец вектора
    }

    // 4. Вывод чисел в обратном порядке
    std::cout << "Числа в обратном порядке: ";
    std::reverse(numbers.begin(), numbers.end()); // Переворачиваем вектор
    for (int number : numbers) { // Используем range-based for loop
        std::cout << number << " ";
    }
    std::cout << std::endl;

    return 0;
}