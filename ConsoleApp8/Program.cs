using System;

// 1. Базовый интерфейс
interface IWeapon
{
    string Name { get; }
    double Weight { get; }
}

// 2. Интерфейсы, разделяющие функциональность (ISP)

interface IShootable : IWeapon
{
    event EventHandler ShotFired;

    void Shoot();
    int Ammo { get; set; }
}

interface IMeeleWeapon : IWeapon
{
    void Attack(ICharacter target);
}

interface IReloadable : IShootable
{
    void Reload();
    int MaxAmmo { get; set; }
}

interface IAimable : IShootable
{
    void Aim();
}

interface ICharacter
{
    string Name { get; }
    double Health { get; set; }
    void TakeDamage(double damage);
}

// 3. Классы, реализующие интерфейсы

class Pistol : IReloadable, IAimable
{
    public string Name { get; } = "Glock 17";
    public double Weight { get; } = 0.703;
    public int Ammo { get; set; }
    public int MaxAmmo { get; set; } = 17;

    public event EventHandler ShotFired;

    public Pistol()
    {
        Ammo = MaxAmmo;
    }

    public void Shoot()
    {
        if (Ammo > 0)
        {
            Console.WriteLine($"{Name}: Пиу! Пиу!");
            Ammo--;
            ShotFired?.Invoke(this, EventArgs.Empty);
        }
        else
        {
            Console.WriteLine($"{Name}: Нет патронов!");
        }
    }

    public void Reload()
    {
        Ammo = MaxAmmo;
        Console.WriteLine($"{Name}: Перезарядка.");
    }

    public void Aim()
    {
        Console.WriteLine($"{Name}: Прицеливаемся...");
    }
}

class Sword : IMeeleWeapon
{
    public string Name { get; } = "Стальной меч";
    public double Weight { get; } = 1.5;

    public void Attack(ICharacter target)
    {
        Console.WriteLine($"{Name}: Взмах мечом в сторону {target.Name}!");
        target.TakeDamage(25);
    }
}

class SniperRifle : IReloadable, IAimable
{
    public string Name { get; } = "Accuracy International Arctic Warfare";
    public double Weight { get; } = 6.5;
    public int Ammo { get; set; }
    public int MaxAmmo { get; set; } = 5;

    public event EventHandler ShotFired;

    public SniperRifle()
    {
        Ammo = MaxAmmo;
    }

    public void Shoot()
    {
        if (Ammo > 0)
        {
            Console.WriteLine($"{Name}: БАХ! Дальний выстрел!");
            Ammo--;
            ShotFired?.Invoke(this, EventArgs.Empty);
        }
        else
        {
            Console.WriteLine($"{Name}: Нет патронов!");
        }
    }

    public void Reload()
    {
        Ammo = MaxAmmo;
        Console.WriteLine($"{Name}: Перезарядка снайперской винтовки.");
    }

    public void Aim()
    {
        Console.WriteLine($"{Name}: Прицеливаемся через оптический прицел...");
    }
}

// Реализация персонажа
class Character : ICharacter
{
    public string Name { get; }
    public double Health { get; set; }

    public Character(string name, double initialHealth)
    {
        Name = name;
        Health = initialHealth;
    }

    public void TakeDamage(double damage)
    {
        Health -= damage;
        Console.WriteLine($"{Name} получил {damage} урона. Здоровье: {Health}");
        if (Health <= 0)
        {
            Console.WriteLine($"{Name} повержен!");
        }
    }
}

class Example
{
    static void Main(string[] args)
    {
        Pistol pistol = new Pistol();
        SniperRifle sniper = new SniperRifle();
        Sword sword = new Sword();

        Character enemy = new Character("Goblin", 100);

        // Использование оружия
        pistol.Shoot();
        sniper.Aim();
        sniper.Shoot();
        sword.Attack(enemy);
        sword.Attack(enemy);
        sword.Attack(enemy);

        //Подписка на событие
        sniper.ShotFired += (sender, eventArgs) => Console.WriteLine("Событие выстрела из снайперской винтовки!");
        sniper.Shoot();
    }
}