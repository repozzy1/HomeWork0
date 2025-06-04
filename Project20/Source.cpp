#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <cmath>

// ��������� ��� ���������� ������������� �����
class NumberCounter {
public:
    virtual ~NumberCounter() {}
    virtual int count(int number) = 0;
};

// ����� ��� ���������� ���������� �������� � ���������� ������
class DigitCounter : public NumberCounter {
public:
    int count(int number) override {
        if (number == 0) return 1;  // ��������� ������ number = 0
        int count = 0;
        int num = abs(number);  // ��������� ������������� �����
        while (num > 0) {
            num /= 10;
            count++;
        }
        return count;
    }
};

// ����� ��� ���������� ���������� ��������� ������� �����, ���������� ����������� ������� �����
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
        if (number <= 1) return 0; // ����� <= 1 �� ����� ������� ����������

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
    std::cout << "������� ����� �����: ";
    std::cin >> number;

    DigitCounter digitCounter;
    PrimeFactorCounter primeFactorCounter;

    int digitCount = digitCounter.count(number);
    int primeFactorCount = primeFactorCounter.count(number);

    std::cout << "���������� ���� � ����� " << number << ": " << digitCount << std::endl;
    std::cout << "���������� ��������� ������� ���������� ����� " << number << ": " << primeFactorCount << std::endl;

    return 0;
}