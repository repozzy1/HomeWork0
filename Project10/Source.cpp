#include <iostream>
#include <string>
#include <vector>
#include <random>

class Pudge {
private:
    std::string name;
    int health;
    int armour;
    int meatHookLevel;
    bool rottingFleshActive;
    std::vector<std::string> abilities;

public:
    Pudge(const std::string& name, int initialHealth, int initialArmour) :
        name(name),
        health(initialHealth),
        armour(initialArmour),
        meatHookLevel(1),
        rottingFleshActive(false) {
    }

    ~Pudge() {
        std::cout << "Destructor called for " << name << std::endl;
    }

    void addAbility(const std::string& ability) {
        abilities.push_back(ability);
    }

    void displayRandomAbility() const {
        if (abilities.empty()) {
            std::cout << name << " не имеет способностей!" << std::endl;
            return;
        }

        int randomIndex = generateRandomNumber(0, abilities.size() - 1);
        std::cout << name << " использует способность: " << abilities[randomIndex] << std::endl;
    }

    int calculateDamage(int strength) const {
        if (abilities.empty()) return 0;

        int baseDamage = strength * meatHookLevel;
        int abilityModifier = generateRandomNumber(1, 10);
        return baseDamage * abilityModifier;
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
    int generateRandomNumber(int min, int max) const {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(min, max);
        return distrib(gen);
    }
};

int main() {
    Pudge pudge("Pudge", 500, 5);
    pudge.addAbility("Meat Hook");
    pudge.addAbility("Rot");
    pudge.addAbility("Dismember");

    pudge.displayInfo();
    pudge.displayRandomAbility();

    int strength = 25;
    int damage = pudge.calculateDamage(strength);
    std::cout << pudge.getName() << " наносит " << damage << " урона." << std::endl;

    return 0;
}