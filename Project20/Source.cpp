#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <cmath>

// Интерфейс для вычисления характеристик чисел
class NumberCounter {
public:
    virtual ~NumberCounter() {}
    virtual int count(int number) = 0;
};

// Класс для вычисления количества символов в десятичной записи
class DigitCounter : public NumberCounter {
public:
    int count(int number) override {
        if (number == 0) return 1;  // Обработка случая number = 0
        int count = 0;
        int num = abs(number);  // Обработка отрицательных чисел
        while (num > 0) {
            num /= 10;
            count++;
        }
        return count;
    }
};

// Класс для вычисления количества различных простых чисел, являющихся множителями данного числа
class PrimeFactorCounter : public NumberCounter {
private:
    bool isPrime(int n) {
        if (n <= 1) return false;
        for (int i = 2; i <= sqrt(n); ++i) {
            if (n % i == 0) return false;
        }
        return true;
    }

public:
    int count(int number) override {
        if (number <= 1) return 0; // Числа <= 1 не имеют простых множителей

        int num = abs(number);
        std::vector<int> primeFactors;
        for (int i = 2; i <= num; ++i) {
            if (isPrime(i) && num % i == 0) {
                primeFactors.push_back(i);
                while (num % i == 0) {
                    num /= i;
                }
            }
        }
        return primeFactors.size();
    }
};

int main() {
    int number;
    std::cout << "Введите целое число: ";
    std::cin >> number;

    DigitCounter digitCounter;
    PrimeFactorCounter primeFactorCounter;

    int digitCount = digitCounter.count(number);
    int primeFactorCount = primeFactorCounter.count(number);

    std::cout << "Количество цифр в числе " << number << ": " << digitCount << std::endl;
    std::cout << "Количество различных простых множителей числа " << number << ": " << primeFactorCount << std::endl;

    return 0;
}