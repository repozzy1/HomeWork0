#include <iostream>

// Абстрактный класс BaseEnemy
class BaseEnemy {
public:
    // Виртуальные методы (чисто виртуальные делают класс абстрактным)
    virtual void DoDamage() = 0;
    virtual void Die() = 0;
    virtual void ChasePlayer() = 0;

    // Виртуальный деструктор (важно для полиморфизма)
    virtual ~BaseEnemy() {}
};

// Класс-потомок Goblin
class Goblin : public BaseEnemy {
public:
    void DoDamage() override {
        std::cout << "Goblin наносит урон!" << std::endl;
    }

    void Die() override {
        std::cout << "Goblin умирает!" << std::endl;
    }

    void ChasePlayer() override {
        std::cout << "Goblin преследует игрока!" << std::endl;
    }
};

// Класс-потомок Orc
class Orc : public BaseEnemy {
public:
    void DoDamage() override {
        std::cout << "Orc наносит мощный урон!" << std::endl;
    }

    void Die() override {
        std::cout << "Orc падает, издав предсмертный хрип!" << std::endl;
    }

    void ChasePlayer() override {
        std::cout << "Orc яростно преследует игрока!" << std::endl;
    }
};

int main() {
    // Пример использования
    Goblin goblin;
    Orc orc;

    goblin.DoDamage();
    goblin.ChasePlayer();
    goblin.Die();

    orc.DoDamage();
    orc.ChasePlayer();
    orc.Die();

    // Можно использовать указатели на базовый класс для работы с разными типами врагов
    BaseEnemy* enemy1 = new Goblin();
    BaseEnemy* enemy2 = new Orc();

    enemy1->DoDamage();
    enemy2->Die();

    delete enemy1; // Важно освободить память, выделенную через new
    delete enemy2;

    return 0;
}