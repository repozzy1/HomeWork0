#include <iostream>

class ClassA {
private:
    int num1;
    int num2;

public:
    ClassA(int num1, int num2) : num1(num1), num2(num2) {}

    int getNum1() const { return num1; }
    int getNum2() const { return num2; }

    friend int addFields(const ClassA& a, const ClassB& b);
};

class ClassB {
private:
    int num3;
    int num4;

public:
    ClassB(int num3, int num4) : num3(num3), num4(num4) {}

    int getNum3() const { return num3; }
    int getNum4() const { return num4; }

    friend int addFields(const ClassA& a, const ClassB& b);
};

int addFields(const ClassA& a, const ClassB& b) {
    return a.getNum1() + a.getNum2() + b.getNum3() + b.getNum4();
}

int main() {
    ClassA objA(10, 20);
    ClassB objB(30, 40);

    int sum = addFields(objA, objB);
    std::cout << "Сумма всех полей: " << sum << std::endl;

    return 0;
}