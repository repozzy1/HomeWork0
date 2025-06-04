#include <iostream>
#include <stdexcept>
#include <limits>

double divideNumbers(double numerator, double denominator) {
    if (denominator == 0) {
        throw std::runtime_error("Division by zero is not allowed.");
    }
    return numerator / denominator;
}

int main() {
    double numerator, denominator, result;

    try {
        std::cout << "������� ���������: ";
        std::cin >> numerator;
        if (std::cin.fail()) {
            throw std::invalid_argument("Invalid input for numerator.");
        }

        std::cout << "������� �����������: ";
        std::cin >> denominator;
        if (std::cin.fail()) {
            throw std::invalid_argument("Invalid input for denominator.");
        }

        result = divideNumbers(numerator, denominator);
        std::cout << "���������: " << result << std::endl;

    }
    catch (const std::runtime_error& error) {
        std::cerr << "������ ������� ����������: " << error.what() << std::endl;
    }
    catch (const std::invalid_argument& error) {
        std::cerr << "������ �����: " << error.what() << std::endl;
        std::cin.clear();  // ������� ������ ������
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // �������� ������������� ����� �� ������
    }
    catch (...) {
        std::cerr << "����������� ������!" << std::endl;
    }

    return 0;
}