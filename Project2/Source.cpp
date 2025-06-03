#include <iostream>

// ����������� ����� BaseEnemy
class BaseEnemy {
public:
    // ����������� ������ (����� ����������� ������ ����� �����������)
    virtual void DoDamage() = 0;
    virtual void Die() = 0;
    virtual void ChasePlayer() = 0;

    // ����������� ���������� (����� ��� ������������)
    virtual ~BaseEnemy() {}
};

// �����-������� Goblin
class Goblin : public BaseEnemy {
public:
    void DoDamage() override {
        std::cout << "Goblin ������� ����!" << std::endl;
    }

    void Die() override {
        std::cout << "Goblin �������!" << std::endl;
    }

    void ChasePlayer() override {
        std::cout << "Goblin ���������� ������!" << std::endl;
    }
};

// �����-������� Orc
class Orc : public BaseEnemy {
public:
    void DoDamage() override {
        std::cout << "Orc ������� ������ ����!" << std::endl;
    }

    void Die() override {
        std::cout << "Orc ������, ����� ������������ ����!" << std::endl;
    }

    void ChasePlayer() override {
        std::cout << "Orc ������� ���������� ������!" << std::endl;
    }
};

int main() {
    // ������ �������������
    Goblin goblin;
    Orc orc;

    goblin.DoDamage();
    goblin.ChasePlayer();
    goblin.Die();

    orc.DoDamage();
    orc.ChasePlayer();
    orc.Die();

    // ����� ������������ ��������� �� ������� ����� ��� ������ � ������� ������ ������
    BaseEnemy* enemy1 = new Goblin();
    BaseEnemy* enemy2 = new Orc();

    enemy1->DoDamage();
    enemy2->Die();

    delete enemy1; // ����� ���������� ������, ���������� ����� new
    delete enemy2;

    return 0;
}