#include <iostream>
#include <vector>
#include <algorithm> // ��� std::reverse

int main() {
    int N;

    // 1. ���� ������� �������
    std::cout << "������� ������ ������� (N): ";
    std::cin >> N;

    // 2. ���������� �������
    std::vector<int> numbers;

    // 3. ���� ����� � ���������� � ������
    std::cout << "������� " << N << " �����:" << std::endl;
    for (int i = 0; i < N; ++i) {
        int number;
        std::cin >> number;
        numbers.push_back(number); // ��������� ����� � ����� �������
    }

    // 4. ����� ����� � �������� �������
    std::cout << "����� � �������� �������: ";
    std::reverse(numbers.begin(), numbers.end()); // �������������� ������
    for (int number : numbers) { // ���������� range-based for loop
        std::cout << number << " ";
    }
    std::cout << std::endl;

    return 0;
}