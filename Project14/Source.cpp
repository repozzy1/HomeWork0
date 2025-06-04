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
        std::cout << "Имя: " << name << ", Вес: " << weight << std::endl;
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
    Cat cat1("Васька", 5);
    Cat cat2("Мурка", 3);

    Dog dog1("Шарик", 10);
    Dog dog2("Тузик", 15);

    std::cout << "Информация о кошках:" << std::endl;
    cat1.print();
    cat2.print();

    std::cout << "\nИнформация о собаках:" << std::endl;
    dog1.print();
    dog2.print();
}