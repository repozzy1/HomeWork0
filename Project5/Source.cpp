#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits> // Для std::numeric_limits

// Класс Человек
class Person {
private:
    // Закрытые поля (атрибуты)
    std::string name;          // Имя (текстовое)
    int age;                   // Возраст (целое число)
    double height;              // Рост (вещественное число)
    std::string profession;   // Профессия (текстовое)
    int salary;               // Зарплата (целое число)
    double weight;             // Вес (вещественное число)

public:
    // Конструктор по умолчанию
    Person() : name(""), age(0), height(0.0), profession(""), salary(0), weight(0.0) {
        std::cout << "Вызван конструктор по умолчанию для Person" << std::endl;
    }

    // Конструктор с параметрами
    Person(const std::string& name, int age, double height, const std::string& profession, int salary, double weight)
        : name(name), age(age), height(height), profession(profession), salary(salary), weight(weight) {
        std::cout << "Вызван конструктор с параметрами для Person: " << name << std::endl;
    }

    // Методы доступа (геттеры и сеттеры)
    std::string getName() const { return name; }
    void setName(const std::string& name) { this->name = name; }

    int getAge() const { return age; }
    void setAge(int age) { this->age = age; }

    double getHeight() const { return height; }
    void setHeight(double height) { this->height = height; }

    std::string getProfession() const { return profession; }
    void setProfession(const std::string& profession) { this->profession = profession; }

    int getSalary() const { return salary; }
    void setSalary(int salary) { this->salary = salary; }

    double getWeight() const { return weight; }
    void setWeight(double weight) { this->weight = weight; }

    // Метод для определения индекса массы тела (ИМТ)
    double calculateBMI() const {
        if (height <= 0 || weight <= 0) {
            return -1.0; // Некорректные данные
        }
        return weight / (height * height);
    }

    // Метод для получения статуса здоровья на основе ИМТ
    std::string getHealthStatus() const {
        double bmi = calculateBMI();
        if (bmi == -1.0) {
            return "Не удалось рассчитать ИМТ из-за некорректных данных.";
        }
        else if (bmi < 18.5) {
            return "Недостаточный вес";
        }
        else if (bmi < 25) {
            return "Нормальный вес";
        }
        else if (bmi < 30) {
            return "Избыточный вес";
        }
        else {
            return "Ожирение";
        }
    }

    // Перегрузка оператора вывода для удобного вывода информации о человеке
    friend std::ostream& operator<<(std::ostream& os, const Person& person) {
        os << "Имя: " << person.name << ", Возраст: " << person.age
            << ", Рост: " << person.height << ", Профессия: " << person.profession
            << ", Зарплата: " << person.salary << ", Вес: " << person.weight
            << ", Статус здоровья (по ИМТ): " << person.getHealthStatus();
        return os;
    }
};

// Функция для очистки буфера ввода (чтобы избежать проблем при вводе)
void clearInputBuffer() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Функция для отображения меню
void displayMenu() {
    std::cout << "\nМеню:" << std::endl;
    std::cout << "1. Добавить пустой объект" << std::endl;
    std::cout << "2. Добавить объект с данными" << std::endl;
    std::cout << "3. Редактировать объект" << std::endl;
    std::cout << "4. Вывести информацию обо всех объектах" << std::endl;
    std::cout << "5. Сортировать по имени (возрастание)" << std::endl;
    std::cout << "6. Сортировать по возрасту (возрастание)" << std::endl;
    std::cout << "7. Сортировать по зарплате (возрастание)" << std::endl;
    std::cout << "8. Завершить работу" << std::endl;
    std::cout << "Выберите пункт меню: ";
}

// Функция для добавления объекта с данными, введенными пользователем
Person createPersonFromInput() {
    std::string name;
    int age;
    double height;
    std::string profession;
    int salary;
    double weight;

    std::cout << "Введите имя: ";
    std::getline(std::cin >> std::ws, name); // Используем std::getline для ввода строки с пробелами

    std::cout << "Введите возраст: ";
    std::cin >> age;
    clearInputBuffer(); // Очищаем буфер после ввода числа

    std::cout << "Введите рост (в метрах): ";
    std::cin >> height;
    clearInputBuffer();

    std::cout << "Введите профессию: ";
    std::getline(std::cin >> std::ws, profession);

    std::cout << "Введите зарплату: ";
    std::cin >> salary;
    clearInputBuffer();

    std::cout << "Введите вес (в кг): ";
    std::cin >> weight;
    clearInputBuffer();

    return Person(name, age, height, profession, salary, weight);
}

// Функция для редактирования полей объекта
void editPerson(Person& person) {
    int choice;
    std::cout << "\nЧто вы хотите отредактировать?" << std::endl;
    std::cout << "1. Имя" << std::endl;
    std::cout << "2. Возраст" << std::endl;
    std::cout << "3. Рост" << std::endl;
    std::cout << "4. Профессия" << std::endl;
    std::cout << "5. Зарплата" << std::endl;
    std::cout << "6. Вес" << std::endl;
    std::cout << "Выберите пункт: ";
    std::cin >> choice;
    clearInputBuffer();

    switch (choice) {
    case 1: {
        std::string newName;
        std::cout << "Введите новое имя: ";
        std::getline(std::cin >> std::ws, newName);
        person.setName(newName);
        break;
    }
    case 2: {
        int newAge;
        std::cout << "Введите новый возраст: ";
        std::cin >> newAge;
        clearInputBuffer();
        person.setAge(newAge);
        break;
    }
    case 3: {
        double newHeight;
        std::cout << "Введите новый рост (в метрах): ";
        std::cin >> newHeight;
        clearInputBuffer();
        person.setHeight(newHeight);
        break;
    }
    case 4: {
        std::string newProfession;
        std::cout << "Введите новую профессию: ";
        std::getline(std::cin >> std::ws, newProfession);
        person.setProfession(newProfession);
        break;
    }
    case 5: {
        int newSalary;
        std::cout << "Введите новую зарплату: ";
        std::cin >> newSalary;
        clearInputBuffer();
        person.setSalary(newSalary);
        break;
    }
    case 6: {
        double newWeight;
        std::cout << "Введите новый вес (в кг): ";
        std::cin >> newWeight;
        clearInputBuffer();
        person.setWeight(newWeight);
        break;
    }
    default:
        std::cout << "Неверный выбор." << std::endl;
    }
}

// Функции для сортировки (лямбда-выражения)
bool compareByName(const Person& a, const Person& b) {
    return a.getName() < b.getName();
}

bool compareByAge(const Person& a, const Person& b) {
    return a.getAge() < b.getAge();
}

bool compareBySalary(const Person& a, const Person& b) {
    return a.getSalary() < b.getSalary();
}

int main() {
    std::vector<Person> people;
    int choice;

    do {
        displayMenu();
        std::cin >> choice;
        clearInputBuffer();

        switch (choice) {
        case 1: {
            people.emplace_back(); // Добавляем объект, используя конструктор по умолчанию
            break;
        }
        case 2: {
            Person newPerson = createPersonFromInput();
            people.push_back(newPerson); // Добавляем объект с данными
            break;
        }
        case 3: {
            if (people.empty()) {
                std::cout << "Список пуст." << std::endl;
                break;
            }
            int index;
            std::cout << "Введите индекс объекта для редактирования (от 0 до " << people.size() - 1 << "): ";
            std::cin >> index;
            clearInputBuffer();

            if (index >= 0 && index < people.size()) {
                editPerson(people[index]);
                std::cout << "Объект отредактирован." << std::endl;
            }
            else {
                std::cout << "Неверный индекс." << std::endl;
            }
            break;
        }
        case 4: {
            if (people.empty()) {
                std::cout << "Список пуст." << std::endl;
                break;
            }
            for (size_t i = 0; i < people.size(); ++i) {
                std::cout << "Объект " << i << ": " << people[i] << std::endl;
            }
            break;
        }
        case 5: {
            if (people.empty()) {
                std::cout << "Список пуст." << std::endl;
                break;
            }
            std::sort(people.begin(), people.end(), compareByName);
            std::cout << "Список отсортирован по имени (возрастание)." << std::endl;
            break;
        }
        case 6: {
            if (people.empty()) {
                std::cout << "Список пуст." << std::endl;
                break;
            }
            std::sort(people.