#include <iostream>
#include <string>
#include <random>

class Pudge {
private:
    std::string name;    
    int health;           
    int armour;          
    int meatHookLevel;     
    bool rottingFleshActive; 

public:
    Pudge(const std::string& name, int initialHealth, int initialArmour) :
        name(name),
        health(initialHealth),
        armour(initialArmour),
        meatHookLevel(1),       
        rottingFleshActive(false) {
    } 


    std::string getName() const { return name; }
    int getHealth() const { return health; }
    int getArmour() const { return armour; }
    int getMeatHookLevel() const { return meatHookLevel; }
    bool isRottingFleshActive() const { return rottingFleshActive; }

    void displayInfo() const {
        std::cout << "Имя: " << name << std::endl;
        std::cout << "Здоровье: " << health << std::endl;
        std::cout << "Броня: " << armour << std::endl;
        std::cout << "Уровень крюка: " << meatHookLevel << std::endl;
        std::cout << "Гнилая плоть активна: " << (rottingFleshActive ? "Да" : "Нет") << std::endl;
    }
    void FreshMeat() {
        int healthGain = generateRandomNumber(50, 100);  
        int armourGain = generateRandomNumber(10, 20);   

        std::cout << name << " пожирает свежее мясо! +" << healthGain << " здоровья, +" << armourGain << " брони!" << std::endl;

        health += healthGain;
        armour += armourGain;

        if (!rottingFleshActive) {  
            std::cout << name << " чувствует вкус гнили... 'Гнилая плоть' активирована!" << std::endl;
            rottingFleshActive = true;
        }
        else {
            std::cout << name << " становится все более гнилым..." << std::endl;
        }
    }


    void UpgradeMeatHook() {
        if (meatHookLevel < 5) {
            meatHookLevel++;
            std::cout << name << " улучшил свой крюк до " << meatHookLevel << " уровня!" << std::endl;
        }
        else {
            std::cout << name << " уже имеет максимальный уровень крюка!" << std::endl;
        }
    }

private:

    int generateRandomNumber(int min, int max) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(min, max);
        return distrib(gen);
    }
};

int main() {
    Pudge pudge("Pudge", 500, 5);
    pudge.displayInfo();
    pudge.FreshMeat();
    pudge.displayInfo();
    pudge.UpgradeMeatHook();
    pudge.displayInfo();
    pudge.UpgradeMeatHook();
    pudge.displayInfo();
    pudge.UpgradeMeatHook();
    pudge.displayInfo();
    pudge.UpgradeMeatHook();
    pudge.displayInfo();
    pudge.UpgradeMeatHook();
    pudge.displayInfo();
    pudge.UpgradeMeatHook();
    pudge.displayInfo();
}