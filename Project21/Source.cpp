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
        std::cout << "Введите числитель: ";
        std::cin >> numerator;
        if (std::cin.fail()) {
            throw std::invalid_argument("Invalid input for numerator.");
        }

        std::cout << "Введите знаменатель: ";
        std::cin >> denominator;
        if (std::cin.fail()) {
            throw std::invalid_argument("Invalid input for denominator.");
        }

        result = divideNumbers(numerator, denominator);
        std::cout << "Результат: " << result << std::endl;

    }
    catch (const std::runtime_error& error) {
        std::cerr << "Ошибка времени выполнения: " << error.what() << std::endl;
    }
    catch (const std::invalid_argument& error) {
        std::cerr << "Ошибка ввода: " << error.what() << std::endl;
        std::cin.clear();  // Очистка флагов ошибок
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Удаление некорректного ввода из потока
    }
    catch (...) {
        std::cerr << "Неизвестная ошибка!" << std::endl;
    }

    return 0;
}