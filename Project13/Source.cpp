#include <iostream>
#include <string>

class CombatUnit {
private:
    int health;
    int damage;
    std::string unitType;
    static int totalHealth;
    static int totalDamage;

public:
    CombatUnit(const std::string& unitType, int health, int damage) :
        unitType(unitType), health(health), damage(damage) {
        totalHealth += health;
        totalDamage += damage;
        std::cout << "Создана боевая единица: " << unitType
            << ", Здоровье: " << health
            << ", Урон: " << damage << std::endl;
    }

    ~CombatUnit() {
        totalHealth -= health;
        totalDamage -= damage;
        std::cout << "Уничтожена боевая единица: " << unitType << std::endl;
    }

    std::string getUnitType() const { return unitType; }
    int getHealth() const { return health; }
    int getDamage() const { return damage; }

    void setHealth(int newHealth) {
        totalHealth -= health;
        health = newHealth;
        totalHealth += health;
        std::cout << "Здоровье " << unitType << " изменено на: " << health << std::endl;
    }

    void setDamage(int newDamage) {
        totalDamage -= damage;
        damage = newDamage;
        totalDamage += damage;
        std::cout << "Урон " << unitType << " изменен на: " << damage << std::endl;
    }

    static int getTotalHealth() { return totalHealth; }
    static int getTotalDamage() { return totalDamage; }

    void displayInfo() const {
        std::cout << "Тип: " << unitType << ", Здоровье: " << health << ", Урон: " << damage << std::endl;
    }
};

int CombatUnit::totalHealth = 0;
int CombatUnit::totalDamage = 0;

int main() {
    CombatUnit unit1("Мечник", 100, 20);
    CombatUnit unit2("Лучник", 70, 30);

    std::cout << "\nОбщее здоровье: " << CombatUnit::getTotalHealth() << std::endl;
    std::cout << "Общий урон: " << CombatUnit::getTotalDamage() << std::endl;

    unit1.setHealth(120);
    unit2.setDamage(35);

    std::cout << "\nОбщее здоровье: " << CombatUnit::getTotalHealth() << std::endl;
    std::cout << "Общий урон: " << CombatUnit::getTotalDamage() << std::endl;

    {
        CombatUnit unit3("Копейщик", 80, 25);
        unit3.displayInfo();
    }

    std::cout << "\nОбщее здоровье: " << CombatUnit::getTotalHealth() << std::endl;
    std::cout << "Общий урон: " << CombatUnit::getTotalDamage() << std::endl;

    return 0;
}