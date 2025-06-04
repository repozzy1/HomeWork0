#include <iostream>
#include <string>

// Forward declaration
class ElectricCar;
class ElectricBoat;

// Базовый класс LandTransport
class LandTransport {
protected:
    std::string modelName;

public:
    LandTransport(const std::string& modelName) : modelName(modelName) {}
    virtual ~LandTransport() { std::cout << "LandTransport destructor for: " << modelName << std::endl; }

    virtual void drive() {
        std::cout << "LandTransport " << modelName << " is driving on land." << std::endl;
    }

    virtual void displayInfo() const {
        std::cout << "Land Transport: " << modelName << std::endl;
    }
};

// Базовый класс WaterTransport
class WaterTransport {
protected:
    std::string boatName;

public:
    WaterTransport(const std::string& boatName) : boatName(boatName) {}
    virtual ~WaterTransport() { std::cout << "WaterTransport destructor for: " << boatName << std::endl; }

    virtual void floatOnWater() {
        std::cout << "WaterTransport " << boatName << " is floating on water." << std::endl;
    }

    virtual void displayInfo() const {
        std::cout << "Water Transport: " << boatName << std::endl;
    }
};

// Класс ElectricCar (наследуется от LandTransport)
class ElectricCar : public LandTransport {
private:
    int batteryCapacity;

public:
    ElectricCar(const std::string& modelName, int batteryCapacity) :
        LandTransport(modelName), batteryCapacity(batteryCapacity) {
    }
    ~ElectricCar() override { std::cout << "ElectricCar destructor for: " << modelName << std::endl; }

    void charge() {
        std::cout << "ElectricCar " << modelName << " is charging." << std::endl;
    }

    void electricCarSpecificMethod() {
        std::cout << "ElectricCar specific method called for: " << modelName << std::endl;
    }

    void displayInfo() const override {
        LandTransport::displayInfo();
        std::cout << " (Electric Car), Battery Capacity: " << batteryCapacity << " kWh" << std::endl;
    }

    void drive() override {
        std::cout << "ElectricCar " << modelName << " is silently driving on land." << std::endl;
    }
};

// Класс ElectricBoat (наследуется от WaterTransport)
class ElectricBoat : public WaterTransport {
private:
    int motorPower;

public:
    ElectricBoat(const std::string& boatName, int motorPower) :
        WaterTransport(boatName), motorPower(motorPower) {
    }
    ~ElectricBoat() override { std::cout << "ElectricBoat destructor for: " << boatName << std::endl; }

    void recharge() {
        std::cout << "ElectricBoat " << boatName << " is recharging its motor." << std::endl;
    }

    void electricBoatSpecificMethod() {
        std::cout << "ElectricBoat specific method called for: " << boatName << std::endl;
    }

    void displayInfo() const override {
        WaterTransport::displayInfo();
        std::cout << " (Electric Boat), Motor Power: " << motorPower << " kW" << std::endl;
    }

    void floatOnWater() override {
        std::cout << "ElectricBoat " << boatName << " is silently gliding on water." << std::endl;
    }
};

// Класс AmphibiousVehicle (наследуется от ElectricCar и ElectricBoat)
class AmphibiousVehicle : public ElectricCar, public ElectricBoat {
public:
    AmphibiousVehicle(const std::string& modelName, int batteryCapacity, const std::string& boatName, int motorPower) :
        ElectricCar(modelName, batteryCapacity), ElectricBoat(boatName, motorPower),
        LandTransport(modelName), WaterTransport(boatName) {
    }

    ~AmphibiousVehicle() override {
        std::cout << "AmphibiousVehicle destructor for: " << ElectricCar::modelName << " and " << ElectricBoat::boatName << std::endl;
    }

    void operate() {
        drive(); // Вызываем метод из ElectricCar
        floatOnWater(); // Вызываем метод из ElectricBoat
        ElectricCar::electricCarSpecificMethod();
        ElectricBoat::electricBoatSpecificMethod();

        std::cout << "Amphibious vehicle is operating on both land and water!" << std::endl;
    }

    void displayInfo() const {
        ElectricCar::displayInfo();
        ElectricBoat::displayInfo();
        std::cout << "This is an Amphibious Vehicle" << std::endl;
    }
};

int main() {
    AmphibiousVehicle av("Amphicar", 60, "Amphiboat", 40);
    av.displayInfo();
    av.operate();

    return 0;
}