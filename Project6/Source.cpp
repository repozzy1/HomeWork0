#include <iostream>
#include <string>

// ������� ����� Animal
class Animal {
private:
    std::string name;
    int weight;

protected:
    int protectedVariable; // ������������ ���������� � ����� protected

public:
    // �����������
    Animal(const std::string& name, int weight, int protectedVar) : name(name), weight(weight), protectedVariable(protectedVar) {}

    // ������� ��� ������ ����������
    void print() const {
        std::cout << "���: " << name << ", ���: " << weight << std::endl;
    }

    // ������ ��� protected ����������
    int getProtectedVariable() const {
        return protectedVariable;
    }

    // ������ ��� protected ����������
    void setProtectedVariable(int value) {
        protectedVariable = value;
    }
};

// ����������� ����� Cat
class Cat : public Animal {
public:
    // �����������
    Cat(const std::string& name, int weight, int protectedVar) : Animal(name, weight, protectedVar) {}

    // �������������� �������, ����������� ��� Cat (�������������)
    void meow() {
        std::cout << "���!" << std::endl;
    }
};

// ����������� ����� Dog
class Dog : public Animal {
public:
    // �����������
    Dog(const std::string& name, int weight, int protectedVar) : Animal(name, weight, protectedVar) {}

    // �������������� �������, ����������� ��� Dog (�������������)
    void bark() {
        std::cout << "���!" << std::endl;
    }
};

int main() {
    // �������� �������� Cat
    Cat cat1("������", 5, 10);
    Cat cat2("�����", 3, 20);

    // �������� �������� Dog
    Dog dog1("�����", 10, 30);
    Dog dog2("�����", 15, 40);

    // ����� ���������� �� ��������
    std::cout << "���������� � ������:" << std::endl;
    cat1.print();
    cat2.print();

    std::cout << "\n���������� � �������:" << std::endl;
    dog1.print();
    dog2.print();

    // ������ � protected ���������� (����� ������/������, �.�. ������ ������ ����������)
    std::cout << "\nProtected variable ��� cat1: " << cat1.getProtectedVariable() << std::endl;
    cat1.setProtectedVariable(100);
    std::cout << "Updated protected variable ��� cat1: " << cat1.getProtectedVariable() << std::endl;


    return 0;
}