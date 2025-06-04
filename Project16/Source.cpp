#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <sstream>

// Базовый класс Person
class Person {
private:
    std::string name;
    int age;
    int id;
    static int nextId;

protected:
    Person(const std::string& name, int age, int id) : name(name), age(age), id(id) {}

public:
    Person() : name(""), age(0), id(nextId++) {
        std::cout << "Person default constructor" << std::endl;
    }

    Person(const std::string& name, int age) : name(name), age(age), id(nextId++) {
        if (age < 0 || age > 120) {
            std::cerr << "Invalid age, setting to 0" << std::endl;
            this->age = 0;
        }
        std::cout << "Person parameterized constructor" << std::endl;
    }

    virtual ~Person() {
        std::cout << "Person destructor" << std::endl;
    }

    std::string getName() const { return name; }
    int getAge() const { return age; }
    int getId() const { return id; }

    void setName(const std::string& name) { this->name = name; }
    void setAge(int age) {
        if (age >= 0 && age <= 120) {
            this->age = age;
        }
    }

    virtual std::string toString() const {
        std::stringstream ss;
        ss << "ID: " << id << ", Name: " << name << ", Age: " << age;
        return ss.str();
    }

    friend std::ostream& operator<<(std::ostream& os, const Person& obj) {
        os << obj.toString();
        return os;
    }

    bool operator==(const Person& other) const {
        return id == other.id;
    }

    Person operator+(const Person& other) const {
        Person newPerson(name + " & " + other.name, (age + other.age) / 2);
        return newPerson;
    }

    Person& operator++() {
        age++;
        return *this;
    }
};

int Person::nextId = 1;

// Класс Student
class Student : public Person {
private:
    std::string major;
    double gpa;

public:
    Student() : Person(), major(""), gpa(0.0) {
        std::cout << "Student default constructor" << std::endl;
    }

    Student(const std::string& name, int age, const std::string& major, double gpa)
        : Person(name, age), major(major), gpa(gpa) {
        if (gpa < 0.0 || gpa > 4.0) {
            std::cerr << "Invalid GPA, setting to 0.0" << std::endl;
            this->gpa = 0.0;
        }
        std::cout << "Student parameterized constructor" << std::endl;
    }

    ~Student() override {
        std::cout << "Student destructor" << std::endl;
    }

    std::string getMajor() const { return major; }
    double getGpa() const { return gpa; }

    void setMajor(const std::string& major) { this->major = major; }
    void setGpa(double gpa) {
        if (gpa >= 0.0 && gpa <= 4.0) {
            this->gpa = gpa;
        }
    }

    std::string toString() const override {
        std::stringstream ss;
        ss << Person::toString() << ", Major: " << major << ", GPA: " << gpa;
        return ss.str();
    }

    Student operator+(const Student& other) const {
        Student newStudent(getName() + " & " + other.getName(), (getAge() + other.getAge()) / 2,
            major + " & " + other.major, (gpa + other.gpa) / 2);
        return newStudent;
    }

    Student& operator++() {
        Person::operator++();
        gpa += 0.1;
        if (gpa > 4.0) gpa = 4.0;
        return *this;
    }
};

// Класс Teacher
class Teacher : public Person {
private:
    std::string subject;
    int yearsOfExperience;

public:
    Teacher() : Person(), subject(""), yearsOfExperience(0) {
        std::cout << "Teacher default constructor" << std::endl;
    }

    Teacher(const std::string& name, int age, const std::string& subject, int yearsOfExperience)
        : Person(name, age), subject(subject), yearsOfExperience(yearsOfExperience) {
        if (yearsOfExperience < 0 || yearsOfExperience > 60) {
            std::cerr << "Invalid years of experience, setting to 0" << std::endl;
            this->yearsOfExperience = 0;
        }
        std::cout << "Teacher parameterized constructor" << std::endl;
    }

    ~Teacher() override {
        std::cout << "Teacher destructor" << std::endl;
    }

    std::string getSubject() const { return subject; }
    int getYearsOfExperience() const { return yearsOfExperience; }

    void setSubject(const std::string& subject) { this->subject = subject; }
    void setYearsOfExperience(int yearsOfExperience) {
        if (yearsOfExperience >= 0 && yearsOfExperience <= 60) {
            this->yearsOfExperience = yearsOfExperience;
        }
    }

    std::string toString() const override {
        std::stringstream ss;
        ss << Person::toString() << ", Subject: " << subject << ", Years of Experience: " << yearsOfExperience;
        return ss.str();
    }

    Teacher operator+(const Teacher& other) const {
        Teacher newTeacher(getName() + " & " + other.getName(), (getAge() + other.getAge()) / 2,
            subject + " & " + other.subject, yearsOfExperience + other.yearsOfExperience);
        return newTeacher;
    }

    Teacher& operator++() {
        Person::operator++();
        yearsOfExperience++;
        return *this;
    }
};

// Класс Employee
class Employee : public Person {
private:
    std::string department;
    int salary;

public:
    Employee() : Person(), department(""), salary(0) {
        std::cout << "Employee default constructor" << std::endl;
    }

    Employee(const std::string& name, int age, const std::string& department, int salary)
        : Person(name, age), department(department), salary(salary) {
        if (salary < 0) {
            std::cerr << "Invalid salary, setting to 0" << std::endl;
            this->salary = 0;
        }
        std::cout << "Employee parameterized constructor" << std::endl;
    }

    ~Employee() override {
        std::cout << "Employee destructor" << std::endl;
    }

    std::string getDepartment() const { return department; }
    int getSalary() const { return salary; }

    void setDepartment(const std::string& department) { this->department = department; }
    void setSalary(int salary) {
        if (salary >= 0) {
            this->salary = salary;
        }
    }

    std::string toString() const override {
        std::stringstream ss;
        ss << Person::toString() << ", Department: " << department << ", Salary: " << salary;
        return ss.str();
    }

    Employee operator+(const Employee& other) const {
        Employee newEmployee(getName() + " & " + other.getName(), (getAge() + other.getAge()) / 2,
            department + " & " + other.department, salary + other.salary);
        return newEmployee;
    }

    Employee& operator++() {
        Person::operator++();
        salary += 1000;
        return *this;
    }
};

// Function to clear input buffer
void clearInputBuffer() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Function to get integer input with validation
int getIntInput(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;

        if (std::cin.fail()) {
            std::cout << "Invalid input. Please enter a number." << std::endl;
            std::cin.clear();
            clearInputBuffer();
        }
        else {
            clearInputBuffer();
            return value;
        }
    }
}

// Function to display the menu
void displayMenu() {
    std::cout << "\nMenu:" << std::endl;
    std::cout << "1. Add new element" << std::endl;
    std::cout << "2. Delete element by index" << std::endl;
    std::cout << "3. Output all elements" << std::endl;
    std::cout << "4. Compare two elements (by index)" << std::endl;
    std::cout << "5. Exit" << std::endl;
    std::cout << "Enter your choice: ";
}

// Function to add a new element
void addElement(std::vector<Person*>& people) {
    int choice;
    std::cout << "Choose type of person to add:" << std::endl;
    std::cout << "1. Person" << std::endl;
    std::cout << "2. Student" << std::endl;
    std::cout << "3. Teacher" << std::endl;
    std::cout << "4. Employee" << std::endl;
    std::cout << "Enter your choice: ";
    std::cin >> choice;
    clearInputBuffer();

    std::string name;
    int age;

    std::cout << "Enter name: ";
    std::getline(std::cin, name);

    age = getIntInput("Enter age: ");

    switch (choice) {
    case 1: {
        people.push_back(new Person(name, age));
        break;
    }
    case 2: {
        std::string major;
        double gpa;
        std::cout << "Enter major: ";
        std::getline(std::cin, major);
        std::cout << "Enter GPA: ";
        std::cin >> gpa;
        clearInputBuffer();
        people.push_back(new Student(name, age, major, gpa));
        break;
    }
    case 3: {
        std::string subject;
        int yearsOfExperience;
        std::cout << "Enter subject: ";
        std::getline(std::cin, subject);
        yearsOfExperience = getIntInput("Enter years of experience: ");
        people.push_back(new Teacher(name, age, subject, yearsOfExperience));
        break;
    }
    case 4: {
        std::string department;
        int salary;
        std::cout << "Enter department: ";
        std::getline(std::cin, department);
        salary = getIntInput("Enter salary: ");
        people.push_back(new Employee(name, age, department, salary));
        break;
    }
    default:
        std::cout << "Invalid choice" << std::endl;
    }
}

// Function to delete an element by index
void deleteElement(std::vector<Person*>& people) {
    int index = getIntInput("Enter index to delete: ");
    if (index >= 0 && index < people.size()) {
        delete people[index];
        people.erase(people.begin() + index);
        std::cout << "Element deleted" << std::endl;
    }
    else {
        std::cout << "Invalid index" << std::endl;
    }
}

// Function to output all elements
void outputElements(const std::vector<Person*>& people) {
    if (people.empty()) {
        std::cout << "No elements to display." << std::endl;
        return;
    }

    for (size_t i = 0; i < people.size(); ++i) {
        std::cout << "Element " << i << ": " << *people[i] << std::endl;
    }
}

// Function to compare two elements
void compareElements(const std::vector<Person*>& people) {
    if (people.size() < 2) {
        std::cout << "Not enough elements to compare." << std::endl;
        return;
    }

    int index1 = getIntInput("Enter first index to compare: ");
    int index2 = getIntInput("Enter second index to compare: ");

    if (index1 >= 0 && index1 < people.size() && index2 >= 0 && index2 < people.size()) {
        if (*people[index1] == *people[index2]) {
            std::cout << "Elements are equal" << std::endl;
        }
        else {
            std::cout << "Elements are not equal" << std::endl;
        }
    }
    else {
        std::cout << "Invalid index" << std::endl;
    }
}

int main() {
    std::vector<Person*> people;
    int choice;

    do {
        displayMenu();
        choice = getIntInput("");

        switch (choice) {
        case 1:
            addElement(people);
            break;
        case 2:
            deleteElement(people);
            break;
        case 3:
            outputElements(people);
            break;
        case 4:
            compareElements(people);
            break;
        case 5:
            std::cout << "Exiting program" << std::endl;
            break;
        default:
            std::cout << "Invalid choice" << std::endl;
        }
    } while (choice != 5);

    for (Person* person : people) {
        delete person;
    }
    people.clear();

    return 0;
}