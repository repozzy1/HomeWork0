#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits> // ��� std::numeric_limits

// ����� �������
class Person {
private:
    // �������� ���� (��������)
    std::string name;          // ��� (���������)
    int age;                   // ������� (����� �����)
    double height;              // ���� (������������ �����)
    std::string profession;   // ��������� (���������)
    int salary;               // �������� (����� �����)
    double weight;             // ��� (������������ �����)

public:
    // ����������� �� ���������
    Person() : name(""), age(0), height(0.0), profession(""), salary(0), weight(0.0) {
        std::cout << "������ ����������� �� ��������� ��� Person" << std::endl;
    }

    // ����������� � �����������
    Person(const std::string& name, int age, double height, const std::string& profession, int salary, double weight)
        : name(name), age(age), height(height), profession(profession), salary(salary), weight(weight) {
        std::cout << "������ ����������� � ����������� ��� Person: " << name << std::endl;
    }

    // ������ ������� (������� � �������)
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

    // ����� ��� ����������� ������� ����� ���� (���)
    double calculateBMI() const {
        if (height <= 0 || weight <= 0) {
            return -1.0; // ������������ ������
        }
        return weight / (height * height);
    }

    // ����� ��� ��������� ������� �������� �� ������ ���
    std::string getHealthStatus() const {
        double bmi = calculateBMI();
        if (bmi == -1.0) {
            return "�� ������� ���������� ��� ��-�� ������������ ������.";
        }
        else if (bmi < 18.5) {
            return "������������� ���";
        }
        else if (bmi < 25) {
            return "���������� ���";
        }
        else if (bmi < 30) {
            return "���������� ���";
        }
        else {
            return "��������";
        }
    }

    // ���������� ��������� ������ ��� �������� ������ ���������� � ��������
    friend std::ostream& operator<<(std::ostream& os, const Person& person) {
        os << "���: " << person.name << ", �������: " << person.age
            << ", ����: " << person.height << ", ���������: " << person.profession
            << ", ��������: " << person.salary << ", ���: " << person.weight
            << ", ������ �������� (�� ���): " << person.getHealthStatus();
        return os;
    }
};

// ������� ��� ������� ������ ����� (����� �������� ������� ��� �����)
void clearInputBuffer() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// ������� ��� ����������� ����
void displayMenu() {
    std::cout << "\n����:" << std::endl;
    std::cout << "1. �������� ������ ������" << std::endl;
    std::cout << "2. �������� ������ � �������" << std::endl;
    std::cout << "3. ������������� ������" << std::endl;
    std::cout << "4. ������� ���������� ��� ���� ��������" << std::endl;
    std::cout << "5. ����������� �� ����� (�����������)" << std::endl;
    std::cout << "6. ����������� �� �������� (�����������)" << std::endl;
    std::cout << "7. ����������� �� �������� (�����������)" << std::endl;
    std::cout << "8. ��������� ������" << std::endl;
    std::cout << "�������� ����� ����: ";
}

// ������� ��� ���������� ������� � �������, ���������� �������������
Person createPersonFromInput() {
    std::string name;
    int age;
    double height;
    std::string profession;
    int salary;
    double weight;

    std::cout << "������� ���: ";
    std::getline(std::cin >> std::ws, name); // ���������� std::getline ��� ����� ������ � ���������

    std::cout << "������� �������: ";
    std::cin >> age;
    clearInputBuffer(); // ������� ����� ����� ����� �����

    std::cout << "������� ���� (� ������): ";
    std::cin >> height;
    clearInputBuffer();

    std::cout << "������� ���������: ";
    std::getline(std::cin >> std::ws, profession);

    std::cout << "������� ��������: ";
    std::cin >> salary;
    clearInputBuffer();

    std::cout << "������� ��� (� ��): ";
    std::cin >> weight;
    clearInputBuffer();

    return Person(name, age, height, profession, salary, weight);
}

// ������� ��� �������������� ����� �������
void editPerson(Person& person) {
    int choice;
    std::cout << "\n��� �� ������ ���������������?" << std::endl;
    std::cout << "1. ���" << std::endl;
    std::cout << "2. �������" << std::endl;
    std::cout << "3. ����" << std::endl;
    std::cout << "4. ���������" << std::endl;
    std::cout << "5. ��������" << std::endl;
    std::cout << "6. ���" << std::endl;
    std::cout << "�������� �����: ";
    std::cin >> choice;
    clearInputBuffer();

    switch (choice) {
    case 1: {
        std::string newName;
        std::cout << "������� ����� ���: ";
        std::getline(std::cin >> std::ws, newName);
        person.setName(newName);
        break;
    }
    case 2: {
        int newAge;
        std::cout << "������� ����� �������: ";
        std::cin >> newAge;
        clearInputBuffer();
        person.setAge(newAge);
        break;
    }
    case 3: {
        double newHeight;
        std::cout << "������� ����� ���� (� ������): ";
        std::cin >> newHeight;
        clearInputBuffer();
        person.setHeight(newHeight);
        break;
    }
    case 4: {
        std::string newProfession;
        std::cout << "������� ����� ���������: ";
        std::getline(std::cin >> std::ws, newProfession);
        person.setProfession(newProfession);
        break;
    }
    case 5: {
        int newSalary;
        std::cout << "������� ����� ��������: ";
        std::cin >> newSalary;
        clearInputBuffer();
        person.setSalary(newSalary);
        break;
    }
    case 6: {
        double newWeight;
        std::cout << "������� ����� ��� (� ��): ";
        std::cin >> newWeight;
        clearInputBuffer();
        person.setWeight(newWeight);
        break;
    }
    default:
        std::cout << "�������� �����." << std::endl;
    }
}

// ������� ��� ���������� (������-���������)
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
            people.emplace_back(); // ��������� ������, ��������� ����������� �� ���������
            break;
        }
        case 2: {
            Person newPerson = createPersonFromInput();
            people.push_back(newPerson); // ��������� ������ � �������
            break;
        }
        case 3: {
            if (people.empty()) {
                std::cout << "������ ����." << std::endl;
                break;
            }
            int index;
            std::cout << "������� ������ ������� ��� �������������� (�� 0 �� " << people.size() - 1 << "): ";
            std::cin >> index;
            clearInputBuffer();

            if (index >= 0 && index < people.size()) {
                editPerson(people[index]);
                std::cout << "������ ��������������." << std::endl;
            }
            else {
                std::cout << "�������� ������." << std::endl;
            }
            break;
        }
        case 4: {
            if (people.empty()) {
                std::cout << "������ ����." << std::endl;
                break;
            }
            for (size_t i = 0; i < people.size(); ++i) {
                std::cout << "������ " << i << ": " << people[i] << std::endl;
            }
            break;
        }
        case 5: {
            if (people.empty()) {
                std::cout << "������ ����." << std::endl;
                break;
            }
            std::sort(people.begin(), people.end(), compareByName);
            std::cout << "������ ������������ �� ����� (�����������)." << std::endl;
            break;
        }
        case 6: {
            if (people.empty()) {
                std::cout << "������ ����." << std::endl;
                break;
            }
            std::sort(people.