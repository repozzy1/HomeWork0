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
        std::cout << "������� ������ �������: " << unitType
            << ", ��������: " << health
            << ", ����: " << damage << std::endl;
    }

    ~CombatUnit() {
        totalHealth -= health;
        totalDamage -= damage;
        std::cout << "���������� ������ �������: " << unitType << std::endl;
    }

    std::string getUnitType() const { return unitType; }
    int getHealth() const { return health; }
    int getDamage() const { return damage; }

    void setHealth(int newHealth) {
        totalHealth -= health;
        health = newHealth;
        totalHealth += health;
        std::cout << "�������� " << unitType << " �������� ��: " << health << std::endl;
    }

    void setDamage(int newDamage) {
        totalDamage -= damage;
        damage = newDamage;
        totalDamage += damage;
        std::cout << "���� " << unitType << " ������� ��: " << damage << std::endl;
    }

    static int getTotalHealth() { return totalHealth; }
    static int getTotalDamage() { return totalDamage; }

    void displayInfo() const {
        std::cout << "���: " << unitType << ", ��������: " << health << ", ����: " << damage << std::endl;
    }
};

int CombatUnit::totalHealth = 0;
int CombatUnit::totalDamage = 0;

int main() {
    CombatUnit unit1("������", 100, 20);
    CombatUnit unit2("������", 70, 30);

    std::cout << "\n����� ��������: " << CombatUnit::getTotalHealth() << std::endl;
    std::cout << "����� ����: " << CombatUnit::getTotalDamage() << std::endl;

    unit1.setHealth(120);
    unit2.setDamage(35);

    std::cout << "\n����� ��������: " << CombatUnit::getTotalHealth() << std::endl;
    std::cout << "����� ����: " << CombatUnit::getTotalDamage() << std::endl;

    {
        CombatUnit unit3("��������", 80, 25);
        unit3.displayInfo();
    }

    std::cout << "\n����� ��������: " << CombatUnit::getTotalHealth() << std::endl;
    std::cout << "����� ����: " << CombatUnit::getTotalDamage() << std::endl;

    return 0;
}