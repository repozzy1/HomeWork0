using System;

public class BankAccount
{
    private readonly string _accountNumber;
    private double _balance;
    public string AccountNumber
    {
        get { return _accountNumber; }
        init
        {
            if (string.IsNullOrEmpty(value))
            {
                throw new ArgumentException("Счёт не может быть пустым");
            }
            _accountNumber = value;
        }
    }
    private string _owner;

    public string Owner
    {
        get { return _owner; }
        set
        {
            if (string.IsNullOrEmpty(value))
            {
                throw new ArgumentException("Имя владельца не может быть пустым.");
            }
            _owner = value;
        }
    }
    public double Balance
    {
        get { return _balance; }
        private set { _balance = value; }
    }
    public void Deposit(double amount)
    {
        if (amount <= 0)
        {
            throw new ArgumentException("Минус не не, плюс да да");
        }

        _balance += amount;
        Console.WriteLine($"Внесено {amount:C}. Новый баланс: {Balance:C}");
    }
    public void Withdraw(double amount)
    {
        if (amount <= 0)
        {
            throw new ArgumentException("Снять что то надо без этого никак");
        }

        if (amount > _balance)
        {
            throw new InvalidOperationException("Прикинь ты бомж");
        }

        _balance -= amount;
        Console.WriteLine($"Снято {amount:C}. Новый баланс: {Balance:C}");
    }

    public override string ToString()
    {
        return $"AccountNumber: {AccountNumber}, Owner: {Owner}, Balance: {Balance:C}";
    }
}
public class Program
{
    public static void Main(string[] args)
    {
        try
        {
            BankAccount account = new BankAccount
            {
                AccountNumber = "1234567890", // Установка номера счета через инициализатор
                Owner = "Иван Иванов"
            };

            Console.WriteLine(account);

            // Пополняем счет
            account.Deposit(1000);
            account.Deposit(500);

            // Снимаем со счета
            account.Withdraw(200);

            // Изменяем имя владельца
            account.Owner = "Аля Это я";
            Console.WriteLine($"Новое имя владельца: {account.Owner}");

            // Попытка снять с бомжа больше, чем есть на счете
            try
            {
                account.Withdraw(2000);
            }
            catch (InvalidOperationException ex)
            {
                Console.WriteLine($"Ошибка: {ex.Message}");
            }

        }
        catch (Exception e)
        {
            Console.WriteLine($"General Error: {e.Message}");
        }
    }
}