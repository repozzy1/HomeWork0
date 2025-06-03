#include <iostream>
#include <string>
#include <vector>
#include <limits>  // ��� std::numeric_limits

// ������� ����� Person
class Person {
private:
    std::string name;        // ��� (������)
    int age;                 // ������� (����� �����)
    int id;                   // ������������� (����� �����)

protected: // ������ ��� ����������� �������
    static int nextId; // ����������� ���� ��� ��������� ID

public:
    // ����������� �� ���������
    Person() : name("Unknown"), age(0), id(nextId++) {
        std::cout << "Person() - ����������� �� ���������" << std::endl;
    }

    // ����������� � �����������
    Person(const std::string& name, int age) : name(name), age(age), id(nextId++) {
        // �������� ��������
        if (age < 0 || age > 150) {
            std::cerr << "������: ������������ ������� (" << age << "). ������� ������ ���� �� 0 �� 150." << std::endl;
            this->age = 0; // ������������� �������� �� ��������� ��� ������������ ������ ������ ��������
        }
        std::cout << "Person(const std::string&, int) - ����������� � �����������" << std::endl;
    }

    // �������
    std::string getName() const { return name; }
    int getAge() const { return age; }
    int getId() const { return id; }

    // ������� (� ���������)
    void setName(const std::string& name) { this->name = name; }

    void setAge(int age) {
        if (age >= 0 && age <= 150) {
            this->age = age;
        }
        else {
            std::cerr << "������: ������������ ������� (" << age << "). ������� ������ ���� �� 0 �� 150." << std::endl;
        }
    }

    // ���������� ��������� ������
    friend std::ostream& operator<<(std::ostream& os, const Person& p) {
        os << "ID: " << p.id << ", ���: " << p.name << ", �������: " << p.age;
        return os;
    }

    // ���������� ��������� ��������� �� ���������
    bool operator==(const Person& other) const {
        return id == other.id; // ���������� �� ID
    }

    // ���������� ��������� �������� (��� ������������)
    Person operator+(const Person& other) const {
        Person result;
        result.setName(name + " & " + other.getName()); //  ���������� �����
        result.setAge(age + other.getAge());  // ��������� �������
        return result;
    }

    // ���������� ��������� ���������� (����������)
    Person& operator++() {
        age++;
        return *this;
    }

    // ����������� ���������� (����� ��� ������������)
    virtual ~Person() {
        std::cout << "~Person() - ����������" << std::endl;
    }
};

// ������������� ������������ �����
int Person::nextId = 1;

// ����� Student (����������� �� Person)
class Student : public Person {
private:
    std::string group;         // �������� ������ (������)
    double gpa;                // ������� ���� (������������ �����)

public:
    // ����������� �� ���������
    Student() : Person(), group(""), gpa(0.0) {
        std::cout << "Student() - ����������� �� ���������" << std::endl;
    }

    // ����������� � �����������
    Student(const std::string& name, int age, const std::string& group, double gpa)
        : Person(name, age), group(group), gpa(gpa) {
        // �������� gpa
        if (gpa < 2.0 || gpa > 5.0) {
            std::cerr << "������: ������������ ������� ���� (" << gpa << "). ������ ���� �� 2.0 �� 5.0." << std::endl;
            this->gpa = 2.0;
        }
        std::cout << "Student(const std::string&, int, const std::string&, double) - ����������� � �����������" << std::endl;
    }

    // �������
    std::string getGroup() const { return group; }
    double getGpa() const { return gpa; }

    // ������� (� ���������)
    void setGroup(const std::string& group) { this->group = group; }

    void setGpa(double gpa) {
        if (gpa >= 2.0 && gpa <= 5.0) {
            this->gpa = gpa;
        }
        else {
            std::cerr << "������: ������������ ������� ���� (" << gpa << "). ������ ���� �� 2.0 �� 5.0." << std::endl;
        }
    }

    // ���������� ��������� ������
    friend std::ostream& operator<<(std::ostream& os, const Student& s) {
        os << " [Student] " << static_cast<const Person&>(s) << ", ������: " << s.group << ", GPA: " << s.gpa; // �������� �������� << ��� Person
        return os;
    }

    // ���������� ��������� ��������� �� ���������
    bool operator==(const Student& other) const {
        return static_cast<const Person&>(*this) == static_cast<const Person&>(other); // ���������� �� ID (�������������� ��������)
    }

    // ���������� ��������� �������� (��� ������������)
    Student operator+(const Student& other) const {
        Student result;
        result.setName(getName() + " & " + other.getName());
        result.setAge((getAge() + other.getAge()) / 2); // ������� �������
        result.setGroup(group + ", " + other.group);
        result.setGpa((gpa + other.gpa) / 2.0); // ������� GPA
        return result;
    }

    // ���������� ��������� ���������� (����������)
    Student& operator++() {
        Person::operator++(); // �������������� ������� (�������������)
        gpa = std::min(gpa + 0.1, 5.0); // �������� GPA (����������� 5.0)
        return *this;
    }

    ~Student() override {
        std::cout << "~Student() - ����������" << std::endl;
    }
};

// ����� Teacher (����������� �� Person)
class Teacher : public Person {
private:
    std::string subject;       // ������������� ������� (������)
    int experience;          // ���� ������ (����� �����)

public:
    // ����������� �� ���������
    Teacher() : Person(), subject(""), experience(0) {
        std::cout << "Teacher() - ����������� �� ���������" << std::endl;
    }

    // ����������� � �����������
    Teacher(const std::string& name, int age, const std::string& subject, int experience)
        : Person(name, age), subject(subject), experience(experience) {
        // �������� �����
        if (experience < 0 || experience > 60) {
            std::cerr << "������: ������������ ���� (" << experience << "). ������ ���� �� 0 �� 60." << std::endl;
            this->experience = 0;
        }
        std::cout << "Teacher(const std::string&, int, const std::string&, int) - ����������� � �����������" << std::endl;
    }

    // �������
    std::string getSubject() const { return subject; }
    int getExperience() const { return experience; }

    // ������� (� ���������)
    void setSubject(const std::string& subject) { this->subject = subject; }

    void setExperience(int experience) {
        if (experience >= 0 && experience <= 60) {
            this->experience = experience;
        }
        else {
            std::cerr << "������: ������������ ���� (" << experience << "). ������ ���� �� 0 �� 60." << std::endl;
        }
    }

    // ���������� ��������� ������
    friend std::ostream& operator<<(std::ostream& os, const Teacher& t) {
        os << " [Teacher] " << static_cast<const Person&>(t) << ", �������: " << t.subject << ", ����: " << t.experience; // �������� �������� << ��� Person
        return os;
    }

    // ���������� ��������� ��������� �� ���������
    bool operator==(const Teacher& other) const {
        return static_cast<const Person&>(*this) == static_cast<const Person&>(other); // ���������� �� ID (�������������� ��������)
    }

    // ���������� ��������� �������� (��� ������������)
    Teacher operator+(const Teacher& other) const {
        Teacher result;
        result.setName(getName() + " & " + other.getName());
        result.setAge((getAge() + other.getAge()) / 2);
        result.setSubject(subject + ", " + other.subject);
        result.setExperience(experience + other.getExperience());
        return result;
    }

    // ���������� ��������� ���������� (����������)
    Teacher& operator++() {
        Person::operator++(); // �������������� ������� (�������������)
        experience++;
        return *this;
    }

    ~Teacher() override {
        std::cout << "~Teacher() - ����������" << std::endl;
    }
};

// ����� Employee (����������� �� Person)
class Employee : public Person {
private:
    std::string department;    // ����� (������)
    int yearsInCompany;      // ���� ������ � �������� (����� �����)

public:
    // ����������� �� ���������
    Employee() : Person(), department(""), yearsInCompany(0) {
        std::cout << "Employee() - ����������� �� ���������" << std::endl;
    }

    // ����������� � �����������
    Employee(const std::string& name, int age, const std::string& department, int yearsInCompany)
        : Person(name, age), department(department), yearsInCompany(yearsInCompany) {
        // �������� ����� � ��������
        if (yearsInCompany < 0 || yearsInCompany > 50) {
            std::cerr << "������: ������������ ���� � �������� (" << yearsInCompany << "). ������ ���� �� 0 �� 50." << std::endl;
            this->yearsInCompany = 0;
        }
        std::cout << "Employee(const std::string&, int, const std::string&, int) - ����������� � �����������" << std::endl;
    }

    // �������
    std::string getDepartment() const { return department; }
    int getYearsInCompany() const { return yearsInCompany; }

    // ������� (� ���������)
    void setDepartment(const std::string& department) { this->department = department; }

    void setYearsInCompany(int yearsInCompany) {
        if (yearsInCompany >= 0 && yearsInCompany <= 50) {
            this->yearsInCompany = yearsInCompany;
        }
        else {
            std::cerr << "������: ������������ ���� � �������� (" << yearsInCompany << "). ������ ���� �� 0 �� 50." << std::endl;
        }
    }

    // ���������� ��������� ������
    friend std::ostream& operator<<(std::ostream& os, const Employee& e) {
        os << " [Employee] " << static_cast<const Person&>(e) << ", �����: " << e.department << ", ���� � ��������: " << e.yearsInCompany;
        return os;
    }

    // ���������� ��������� ��������� �� ���������
    bool operator==(const Employee& other) const {
        return static_cast<const Person&>(*this) == static_cast<const Person&>(other); // ���������� �� ID (�������������� ��������)
    }

    // ���������� ��������� �������� (��� ������������)
    Employee operator+(const Employee& other) const {
        Employee result;
        result.setName(getName() + " & " + other.getName());
        result.setAge((getAge() + other.getAge()) / 2);
        result.setDepartment(department + ", " + other.department);
        result.setYearsInCompany(yearsInCompany + other.yearsInCompany);
        return result;
    }

    // ���������� ��������� ���������� (����������)
    Employee& operator++() {
        Person::operator++(); // �������������� ������� (�������������)
        yearsInCompany++;
        return *this;
    }

    ~Employee() override {
        std::cout << "~Employee() - ����������" << std::endl;
    }
};

// ������� ��� ������� ������ �����
void clearInputBuffer() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// ������� ��� ���������� �������� (�������������)
void addElement(std::vector<Person*>& people) {
    int choice;
    std::cout << "\n�������� ��� ������� ��� ����������:" << std::endl;
    std::cout << "1. Person" << std::endl;
    std::cout << "2. Student" << std::endl;
    std::cout << "3. Teacher" << std::endl;
    std::cout << "4. Employee" << std::endl;
    std::cout << "�������� �����: ";
    std::cin >> choice;
    clearInputBuffer();

    std::string name;
    int age;

    std::cout << "������� ���: ";
    std::getline(std::cin >> std::ws, name);

    std::cout << "������� �������: ";
    std::cin >> age;
    clearInputBuffer();

    switch (choice) {
    case 1:
        people.push_back(new Person(name, age));
        break;
    case 2: {
        std::string group;
        double gpa;
        std::cout << "������� �������� ������: ";
        std::getline(std::cin >> std::ws, group);
        std::cout << "������� GPA: ";
        std::cin >> gpa;
        clearInputBuffer();
        people.push_back(new Student(name, age, group, gpa));
        break;
    }
    case 3: {
        std::string subject;
        int experience;
        std::cout << "������� �������: ";
        std::getline(std::cin >> std::ws, subject);
        std::cout << "������� ���� ������: ";
        std::cin >> experience;
        clearInputBuffer();
        people.push_back(new Teacher(name, age, subject, experience));
        break;
    }
    case 4: {
        std::string department;
        int yearsInCompany;
        std::cout << "������� �����: ";
        std::getline(std::cin >> std::ws, department);
        std::cout << "������� ���� � ��������: ";
        std::cin >> yearsInCompany;
        clearInputBuffer();
        people.push_back(new Employee(name, age, department, yearsInCompany));
        break;
    }
    default:
        std::cout << "�������� �����." << std::endl;
        break;
    }
}

// ������� ��� �������� ��������
void removeElement(std::vector<Person*>& people) {
    if (people.empty()) {
        std::cout << "������ ����." << std::endl;
        return;
    }

    int index;
    std::cout << "������� ������ �������� ��� �������� (�� 0 �� " << people.size() - 1 << "): ";
    std::cin >> index;
    clearInputBuffer();

    if (index >= 0 && index < people.size()) {
        delete people[index]; // ����������� ������
        people.erase(people.begin() + index); // ������� ������� �� �������
        std::cout << "������� ������." << std::endl;
    }
    else {
        std::cout << "�������� ������." << std::endl;
    }
}

// ������� ��� ������ ���� ���������
void displayAllElements(const std::vector<Person*>& people) {
    if (people.empty()) {
        std::cout << "������ ����." << std::endl;
        return;
    }
    for (size_t i = 0; i < people.size(); ++i) {
        std::cout << "������� " << i << ": " << *people[i] << std::endl;
    }
}

// ������� ��� ��������� ���� ���������
void compareElements(const std::vector<Person*>& people) {
    if (people.size() < 2) {
        std::cout << "������������ ��������� ��� ���������." << std::endl;
        return;
    }

    int index1, index2;
    std::cout << "������� ������ ������� ��������: ";
    std::cin >> index1;
    clearInputBuffer();
    std::cout << "������� ������ ������� ��������: ";
    std::cin >> index2;
    clearInputBuffer();

    if (index1 < 0 || index1 >= people.size() || index2 < 0 || index2 >= people.size()) {
        std::cout << "�������� ������." << std::endl;
        return;
    }

    if (*people[index1] == *people[index2]) { // ���������� ������������� �������� ==
        std::cout << "�������� �����." << std::endl;
    }
    else {
        std::cout << "�������� �� �����." << std::endl;
    }
}

// ������� ��� ����������� ����
void showMenu() {
    std::cout << "\n�������� ��������:" << std::endl;
    std::cout << "1. �������� ����� �������" << std::endl;
    std::cout << "2. ������� ������� �� �������" << std::endl;
    std::cout << "3. ������� ��� ��������" << std::endl;
    std::cout << "4. �������� ��� ��������" << std::endl;
    std::cout << "5. ��������� ������" << std::endl;
    std::cout << "������� ����� ��������: ";
}

int main() {
    std::vector<Person*> people; // ���������� ������ ���������� �� ������� �����
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
            std::cout << "���������� ������." << std::endl;
            break;
        default:
            std::cout << "�������� �����. ����������, ���������� ��� ���." << std::endl;
        }
    } while (choice != 5);

    // ����������� ������, ���������� ��� ��������
    for (Person* person : people) {
        delete person;
    }
    people.clear(); // ������� ������

    return 0;
}