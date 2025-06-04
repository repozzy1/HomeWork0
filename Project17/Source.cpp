#include <iostream>
#include <string>
#include <vector>

// Функция для логгирования (можно улучшить, добавив уровни важности)
void logMessage(const std::string& message) {
    std::cout << "[LOG] " << message << std::endl;
}

// Базовый класс Vehicle
class Vehicle {
protected:
    std::string make;
    std::string model;

public:
    Vehicle(const std::string& make, const std::string& model) : make(make), model(model) {
        logMessage("Vehicle constructor called. Make: " + make + ", Model: " + model);
    }

    virtual ~Vehicle() {
        logMessage("Vehicle destructor called. Make: " + make + ", Model: " + model);
    }

    virtual void displayInfo() const {
        std::cout << "Make: " << make << ", Model: " << model << std::endl;
    }
};

// Производный класс Car
class Car : public Vehicle {
private:
    int numberOfDoors;

public:
    Car(const std::string& make, const std::string& model, int numberOfDoors) :
        Vehicle(make, model), numberOfDoors(numberOfDoors) {
        logMessage("Car constructor called. Make: " + make + ", Model: " + model + ", Doors: " + std::to_string(numberOfDoors));
    }

    ~Car() override {
        logMessage("Car destructor called. Make: " + make + ", Model: " + model);
    }

    void displayInfo() const override {
        Vehicle::displayInfo();
        std::cout << "Number of doors: " << numberOfDoors << std::endl;
    }
};

// Производный класс Bike
class Bike : public Vehicle {
private:
    bool hasBasket;

public:
    Bike(const std::string& make, const std::string& model, bool hasBasket) :
        Vehicle(make, model), hasBasket(hasBasket) {
        logMessage("Bike constructor called. Make: " + make + ", Model: " + model + ", Has Basket: " + (hasBasket ? "true" : "false"));
    }

    ~Bike() override {
        logMessage("Bike destructor called. Make: " + make + ", Model: " + model);
    }

    void displayInfo() const override {
        Vehicle::displayInfo();
        std::cout << "Has basket: " << (hasBasket ? "Yes" : "No") << std::endl;
    }
};

int main() {
    std::vector<Vehicle*> vehicles;

    logMessage("Creating Car object");
    Vehicle* car1 = new Car("Toyota", "Camry", 4);
    vehicles.push_back(car1);

    logMessage("Creating Bike object");
    Vehicle* bike1 = new Bike("Giant", "Defy", true);
    vehicles.push_back(bike1);

    logMessage("Displaying vehicle information");
    for (Vehicle* vehicle : vehicles) {
        vehicle->displayInfo();
        std::cout << std::endl;
    }

    logMessage("Deleting vehicle objects");
    for (Vehicle* vehicle : vehicles) {
        delete vehicle;
    }
    vehicles.clear();

    logMessage("Program finished");

    return 0;
}