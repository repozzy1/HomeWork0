#include <iostream>
#include <string>
#include <vector>
#include <limits>  // Для std::numeric_limits

// Базовый класс Person
class Person {
private:
    std::string name;        // Имя (строка)
    int age;                 // Возраст (целое число)
    int id;                   // Идентификатор (целое число)

protected: // Доступ для производных классов
    static int nextId; // Статический член для генерации ID

public:
    // Конструктор по умолчанию
    Person() : name("Unknown"), age(0), id(nextId++) {
        std::cout << "Person() - Конструктор по умолчанию" << std::endl;
    }

    // Конструктор с параметрами
    Person(const std::string& name, int age) : name(name), age(age), id(nextId++) {
        // Проверка возраста
        if (age < 0 || age > 150) {
            std::cerr << "Ошибка: Некорректный возраст (" << age << "). Возраст должен быть от 0 до 150." << std::endl;
            this->age = 0; // Устанавливаем значение по умолчанию или обрабатываем ошибку другим способом
        }
        std::cout << "Person(const std::string&, int) - Конструктор с параметрами" << std::endl;
    }

    // Геттеры
    std::string getName() const { return name; }
    int getAge() const { return age; }
    int getId() const { return id; }

    // Сеттеры (с проверкой)
    void setName(const std::string& name) { this->name = name; }

    void setAge(int age) {
        if (age >= 0 && age <= 150) {
            this->age = age;
        }
        else {
            std::cerr << "Ошибка: Некорректный возраст (" << age << "). Возраст должен быть от 0 до 150." << std::endl;
        }
    }

    // Перегрузка оператора вывода
    friend std::ostream& operator<<(std::ostream& os, const Person& p) {
        os << "ID: " << p.id << ", Имя: " << p.name << ", Возраст: " << p.age;
        return os;
    }

    // Перегрузка оператора сравнения на равенство
    bool operator==(const Person& other) const {
        return id == other.id; // Сравниваем по ID
    }

    // Перегрузка оператора сложения (для демонстрации)
    Person operator+(const Person& other) const {
        Person result;
        result.setName(name + " & " + other.getName()); //  Объединяем имена
        result.setAge(age + other.getAge());  // Суммируем возраст
        return result;
    }

    // Перегрузка оператора инкремента (префиксный)
    Person& operator++() {
        age++;
        return *this;
    }

    // Виртуальный деструктор (важно для полиморфизма)
    virtual ~Person() {
        std::cout << "~Person() - Деструктор" << std::endl;
    }
};

// Инициализация статического члена
int Person::nextId = 1;

// Класс Student (наследуется от Person)
class Student : public Person {
private:
    std::string group;         // Название группы (строка)
    double gpa;                // Средний балл (вещественное число)

public:
    // Конструктор по умолчанию
    Student() : Person(), group(""), gpa(0.0) {
        std::cout << "Student() - Конструктор по умолчанию" << std::endl;
    }

    // Конструктор с параметрами
    Student(const std::string& name, int age, const std::string& group, double gpa)
        : Person(name, age), group(group), gpa(gpa) {
        // Проверка gpa
        if (gpa < 2.0 || gpa > 5.0) {
            std::cerr << "Ошибка: Некорректный средний балл (" << gpa << "). Должен быть от 2.0 до 5.0." << std::endl;
            this->gpa = 2.0;
        }
        std::cout << "Student(const std::string&, int, const std::string&, double) - Конструктор с параметрами" << std::endl;
    }

    // Геттеры
    std::string getGroup() const { return group; }
    double getGpa() const { return gpa; }

    // Сеттеры (с проверкой)
    void setGroup(const std::string& group) { this->group = group; }

    void setGpa(double gpa) {
        if (gpa >= 2.0 && gpa <= 5.0) {
            this->gpa = gpa;
        }
        else {
            std::cerr << "Ошибка: Некорректный средний балл (" << gpa << "). Должен быть от 2.0 до 5.0." << std::endl;
        }
    }

    // Перегрузка оператора вывода
    friend std::ostream& operator<<(std::ostream& os, const Student& s) {
        os << " [Student] " << static_cast<const Person&>(s) << ", Группа: " << s.group << ", GPA: " << s.gpa; // Вызываем оператор << для Person
        return os;
    }

    // Перегрузка оператора сравнения на равенство
    bool operator==(const Student& other) const {
        return static_cast<const Person&>(*this) == static_cast<const Person&>(other); // Сравниваем по ID (унаследованный оператор)
    }

    // Перегрузка оператора сложения (для демонстрации)
    Student operator+(const Student& other) const {
        Student result;
        result.setName(getName() + " & " + other.getName());
        result.setAge((getAge() + other.getAge()) / 2); // Средний возраст
        result.setGroup(group + ", " + other.group);
        result.setGpa((gpa + other.gpa) / 2.0); // Средний GPA
        return result;
    }

    // Перегрузка оператора инкремента (префиксный)
    Student& operator++() {
        Person::operator++(); // Инкрементируем возраст (наследованный)
        gpa = std::min(gpa + 0.1, 5.0); // Улучшаем GPA (ограничение 5.0)
        return *this;
    }

    ~Student() override {
        std::cout << "~Student() - Деструктор" << std::endl;
    }
};

// Класс Teacher (наследуется от Person)
class Teacher : public Person {
private:
    std::string subject;       // Преподаваемый предмет (строка)
    int experience;          // Стаж работы (целое число)

public:
    // Конструктор по умолчанию
    Teacher() : Person(), subject(""), experience(0) {
        std::cout << "Teacher() - Конструктор по умолчанию" << std::endl;
    }

    // Конструктор с параметрами
    Teacher(const std::string& name, int age, const std::string& subject, int experience)
        : Person(name, age), subject(subject), experience(experience) {
        // Проверка стажа
        if (experience < 0 || experience > 60) {
            std::cerr << "Ошибка: Некорректный стаж (" << experience << "). Должен быть от 0 до 60." << std::endl;
            this->experience = 0;
        }
        std::cout << "Teacher(const std::string&, int, const std::string&, int) - Конструктор с параметрами" << std::endl;
    }

    // Геттеры
    std::string getSubject() const { return subject; }
    int getExperience() const { return experience; }

    // Сеттеры (с проверкой)
    void setSubject(const std::string& subject) { this->subject = subject; }

    void setExperience(int experience) {
        if (experience >= 0 && experience <= 60) {
            this->experience = experience;
        }
        else {
            std::cerr << "Ошибка: Некорректный стаж (" << experience << "). Должен быть от 0 до 60." << std::endl;
        }
    }

    // Перегрузка оператора вывода
    friend std::ostream& operator<<(std::ostream& os, const Teacher& t) {
        os << " [Teacher] " << static_cast<const Person&>(t) << ", Предмет: " << t.subject << ", Стаж: " << t.experience; // Вызываем оператор << для Person
        return os;
    }

    // Перегрузка оператора сравнения на равенство
    bool operator==(const Teacher& other) const {
        return static_cast<const Person&>(*this) == static_cast<const Person&>(other); // Сравниваем по ID (унаследованный оператор)
    }

    // Перегрузка оператора сложения (для демонстрации)
    Teacher operator+(const Teacher& other) const {
        Teacher result;
        result.setName(getName() + " & " + other.getName());
        result.setAge((getAge() + other.getAge()) / 2);
        result.setSubject(subject + ", " + other.subject);
        result.setExperience(experience + other.getExperience());
        return result;
    }

    // Перегрузка оператора инкремента (префиксный)
    Teacher& operator++() {
        Person::operator++(); // Инкрементируем возраст (наследованный)
        experience++;
        return *this;
    }

    ~Teacher() override {
        std::cout << "~Teacher() - Деструктор" << std::endl;
    }
};

// Класс Employee (наследуется от Person)
class Employee : public Person {
private:
    std::string department;    // Отдел (строка)
    int yearsInCompany;      // Стаж работы в компании (целое число)

public:
    // Конструктор по умолчанию
    Employee() : Person(), department(""), yearsInCompany(0) {
        std::cout << "Employee() - Конструктор по умолчанию" << std::endl;
    }

    // Конструктор с параметрами
    Employee(const std::string& name, int age, const std::string& department, int yearsInCompany)
        : Person(name, age), department(department), yearsInCompany(yearsInCompany) {
        // Проверка стажа в компании
        if (yearsInCompany < 0 || yearsInCompany > 50) {
            std::cerr << "Ошибка: Некорректный стаж в компании (" << yearsInCompany << "). Должен быть от 0 до 50." << std::endl;
            this->yearsInCompany = 0;
        }
        std::cout << "Employee(const std::string&, int, const std::string&, int) - Конструктор с параметрами" << std::endl;
    }

    // Геттеры
    std::string getDepartment() const { return department; }
    int getYearsInCompany() const { return yearsInCompany; }

    // Сеттеры (с проверкой)
    void setDepartment(const std::string& department) { this->department = department; }

    void setYearsInCompany(int yearsInCompany) {
        if (yearsInCompany >= 0 && yearsInCompany <= 50) {
            this->yearsInCompany = yearsInCompany;
        }
        else {
            std::cerr << "Ошибка: Некорректный стаж в компании (" << yearsInCompany << "). Должен быть от 0 до 50." << std::endl;
        }
    }

    // Перегрузка оператора вывода
    friend std::ostream& operator<<(std::ostream& os, const Employee& e) {
        os << " [Employee] " << static_cast<const Person&>(e) << ", Отдел: " << e.department << ", Стаж в компании: " << e.yearsInCompany;
        return os;
    }

    // Перегрузка оператора сравнения на равенство
    bool operator==(const Employee& other) const {
        return static_cast<const Person&>(*this) == static_cast<const Person&>(other); // Сравниваем по ID (унаследованный оператор)
    }

    // Перегрузка оператора сложения (для демонстрации)
    Employee operator+(const Employee& other) const {
        Employee result;
        result.setName(getName() + " & " + other.getName());
        result.setAge((getAge() + other.getAge()) / 2);
        result.setDepartment(department + ", " + other.department);
        result.setYearsInCompany(yearsInCompany + other.yearsInCompany);
        return result;
    }

    // Перегрузка оператора инкремента (префиксный)
    Employee& operator++() {
        Person::operator++(); // Инкрементируем возраст (наследованный)
        yearsInCompany++;
        return *this;
    }

    ~Employee() override {
        std::cout << "~Employee() - Деструктор" << std::endl;
    }
};

// Функция для очистки буфера ввода
void clearInputBuffer() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Функция для добавления элемента (универсальная)
void addElement(std::vector<Person*>& people) {
    int choice;
    std::cout << "\nВыберите тип объекта для добавления:" << std::endl;
    std::cout << "1. Person" << std::endl;
    std::cout << "2. Student" << std::endl;
    std::cout << "3. Teacher" << std::endl;
    std::cout << "4. Employee" << std::endl;
    std::cout << "Выберите пункт: ";
    std::cin >> choice;
    clearInputBuffer();

    std::string name;
    int age;

    std::cout << "Введите имя: ";
    std::getline(std::cin >> std::ws, name);

    std::cout << "Введите возраст: ";
    std::cin >> age;
    clearInputBuffer();

    switch (choice) {
    case 1:
        people.push_back(new Person(name, age));
        break;
    case 2: {
        std::string group;
        double gpa;
        std::cout << "Введите название группы: ";
        std::getline(std::cin >> std::ws, group);
        std::cout << "Введите GPA: ";
        std::cin >> gpa;
        clearInputBuffer();
        people.push_back(new Student(name, age, group, gpa));
        break;
    }
    case 3: {
        std::string subject;
        int experience;
        std::cout << "Введите предмет: ";
        std::getline(std::cin >> std::ws, subject);
        std::cout << "Введите стаж работы: ";
        std::cin >> experience;
        clearInputBuffer();
        people.push_back(new Teacher(name, age, subject, experience));
        break;
    }
    case 4: {
        std::string department;
        int yearsInCompany;
        std::cout << "Введите отдел: ";
        std::getline(std::cin >> std::ws, department);
        std::cout << "Введите стаж в компании: ";
        std::cin >> yearsInCompany;
        clearInputBuffer();
        people.push_back(new Employee(name, age, department, yearsInCompany));
        break;
    }
    default:
        std::cout << "Неверный выбор." << std::endl;
        break;
    }
}

// Функция для удаления элемента
void removeElement(std::vector<Person*>& people) {
    if (people.empty()) {
        std::cout << "Список пуст." << std::endl;
        return;
    }

    int index;
    std::cout << "Введите индекс элемента для удаления (от 0 до " << people.size() - 1 << "): ";
    std::cin >> index;
    clearInputBuffer();

    if (index >= 0 && index < people.size()) {
        delete people[index]; // Освобождаем память
        people.erase(people.begin() + index); // Удаляем элемент из вектора
        std::cout << "Элемент удален." << std::endl;
    }
    else {
        std::cout << "Неверный индекс." << std::endl;
    }
}

// Функция для вывода всех элементов
void displayAllElements(const std::vector<Person*>& people) {
    if (people.empty()) {
        std::cout << "Список пуст." << std::endl;
        return;
    }
    for (size_t i = 0; i < people.size(); ++i) {
        std::cout << "Элемент " << i << ": " << *people[i] << std::endl;
    }
}

// Функция для сравнения двух элементов
void compareElements(const std::vector<Person*>& people) {
    if (people.size() < 2) {
        std::cout << "Недостаточно элементов для сравнения." << std::endl;
        return;
    }

    int index1, index2;
    std::cout << "Введите индекс первого элемента: ";
    std::cin >> index1;
    clearInputBuffer();
    std::cout << "Введите индекс второго элемента: ";
    std::cin >> index2;
    clearInputBuffer();

    if (index1 < 0 || index1 >= people.size() || index2 < 0 || index2 >= people.size()) {
        std::cout << "Неверный индекс." << std::endl;
        return;
    }

    if (*people[index1] == *people[index2]) { // Используем перегруженный оператор ==
        std::cout << "Элементы равны." << std::endl;
    }
    else {
        std::cout << "Элементы не равны." << std::endl;
    }
}

// Функция для отображения меню
void showMenu() {
    std::cout << "\nВыберите действие:" << std::endl;
    std::cout << "1. Добавить новый элемент" << std::endl;
    std::cout << "2. Удалить элемент по индексу" << std::endl;
    std::cout << "3. Вывести все элементы" << std::endl;
    std::cout << "4. Сравнить два элемента" << std::endl;
    std::cout << "5. Завершить работу" << std::endl;
    std::cout << "Введите номер действия: ";
}

int main() {
    std::vector<Person*> people; // Используем вектор указателей на базовый класс
    int choice;

    do {
        showMenu();
        std::cin >> choice;
        clearInputBuffer();

        switch (choice) {
        case 1:
            addElement(people);
            break;
        case 2:
            removeElement(people);
            break;
        case 3:
            displayAllElements(people);
            break;
        case 4:
            compareElements(people);
            break;
        case 5:
            std::cout << "Завершение работы." << std::endl;
            break;
        default:
            std::cout << "Неверный выбор. Пожалуйста, попробуйте еще раз." << std::endl;
        }
    } while (choice != 5);

    // Освобождаем память, выделенную для объектов
    for (Person* person : people) {
        delete person;
    }
    people.clear(); // Очищаем вектор

    return 0;
}