#include <iostream>
#include <string>

class Animal {
private:
    std::string name;
    int weight;

protected:
    std::string species;

public:
    Animal(const std::string& name, int weight, const std::string& species) :
        name(name), weight(weight), species(species) {
    }

    void print() const {
        std::cout << "���: " << name << ", ���: " << weight << std::endl;
    }
};

class Cat : public Animal {
public:
    Cat(const std::string& name, int weight) : Animal(name, weight, "Cat") {}
};

class Dog : public Animal {
public:
    Dog(const std::string& name, int weight) : Animal(name, weight, "Dog") {}
};

int main() {
    Cat cat1("������", 5);
    Cat cat2("�����", 3);

    Dog dog1("�����", 10);
    Dog dog2("�����", 15);

    std::cout << "���������� � ������:" << std::endl;
    cat1.print();
    cat2.print();

    std::cout << "\n���������� � �������:" << std::endl;
    dog1.print();
    dog2.print();
}