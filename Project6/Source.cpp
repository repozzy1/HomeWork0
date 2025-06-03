#include <iostream>
#include <string>

// Базовый класс Animal
class Animal {
private:
    std::string name;
    int weight;

protected:
    int protectedVariable; // Произвольная переменная с типом protected

public:
    // Конструктор
    Animal(const std::string& name, int weight, int protectedVar) : name(name), weight(weight), protectedVariable(protectedVar) {}

    // Функция для вывода информации
    void print() const {
        std::cout << "Имя: " << name << ", Вес: " << weight << std::endl;
    }

    // Геттер для protected переменной
    int getProtectedVariable() const {
        return protectedVariable;
    }

    // Сеттер для protected переменной
    void setProtectedVariable(int value) {
        protectedVariable = value;
    }
};

// Производный класс Cat
class Cat : public Animal {
public:
    // Конструктор
    Cat(const std::string& name, int weight, int protectedVar) : Animal(name, weight, protectedVar) {}

    // Дополнительная функция, специфичная для Cat (необязательно)
    void meow() {
        std::cout << "Мяу!" << std::endl;
    }
};

// Производный класс Dog
class Dog : public Animal {
public:
    // Конструктор
    Dog(const std::string& name, int weight, int protectedVar) : Animal(name, weight, protectedVar) {}

    // Дополнительная функция, специфичная для Dog (необязательно)
    void bark() {
        std::cout << "Гав!" << std::endl;
    }
};

int main() {
    // Создание объектов Cat
    Cat cat1("Васька", 5, 10);
    Cat cat2("Мурка", 3, 20);

    // Создание объектов Dog
    Dog dog1("Шарик", 10, 30);
    Dog dog2("Тузик", 15, 40);

    // Вывод информации об объектах
    std::cout << "Информация о кошках:" << std::endl;
    cat1.print();
    cat2.print();

    std::cout << "\nИнформация о собаках:" << std::endl;
    dog1.print();
    dog2.print();

    // Доступ к protected переменной (через геттер/сеттер, т.к. прямой доступ невозможен)
    std::cout << "\nProtected variable для cat1: " << cat1.getProtectedVariable() << std::endl;
    cat1.setProtectedVariable(100);
    std::cout << "Updated protected variable для cat1: " << cat1.getProtectedVariable() << std::endl;


    return 0;
}