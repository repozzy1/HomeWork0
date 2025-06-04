using System;

public class Address
{
    public string Street { get; set; }
    public string City { get; set; }
    public string ZipCode { get; set; }

    public override string ToString()
    {
        return $"Street: {Street ?? "N/A"}, City: {City ?? "N/A"}, ZipCode: {ZipCode ?? "N/A"}";
    }
}

public class Company
{
    public string Name { get; set; }
    public Address Address { get; set; }

    public override string ToString()
    {
        return $"Name: {Name ?? "N/A"}, Address: {Address?.ToString() ?? "N/A"}";
    }
}

public class User
{
    public string FirstName { get; set; }
    public string LastName { get; set; }
    public Company Company { get; set; }

    public override string ToString()
    {
        return $"FirstName: {FirstName ?? "N/A"}, LastName: {LastName ?? "N/A"}, Company: {Company?.ToString() ?? "N/A"}";
    }
}

public class Program
{
    public static void Main(string[] args)
    {
        // Пример 1: Пользователь с компанией, у которой есть название и адрес
        User user1 = new User
        {
            FirstName = "John",
            LastName = "Doe",
            Company = new Company
            {
                Name = "Acme Corp",
                Address = new Address
                {
                    Street = "123 Main St",
                    City = "Anytown",
                    ZipCode = "12345"
                }
            }
        };
        Console.WriteLine($"User 1: {user1}");

        // Пример 2: Пользователь с компанией, у которой нет адреса
        User user2 = new User
        {
            FirstName = "Jane",
            LastName = "Smith",
            Company = new Company
            {
                Name = "Beta Industries"
            }
        };
        Console.WriteLine($"User 2: {user2}");

        // Пример 3: Пользователь без компании
        User user3 = new User
        {
            FirstName = "Peter",
            LastName = "Jones"
        };
        Console.WriteLine($"User 3: {user3}");

        // Пример 4: Пользователь с компанией, у которой нет имени
        User user4 = new User
        {
            FirstName = "Alice",
            LastName = "Brown",
            Company = new Company
            {
                Address = new Address
                {
                    Street = "456 Oak Ave",
                    City = "Springfield",
                    ZipCode = "67890"
                }
            }
        };
        Console.WriteLine($"User 4: {user4}");

        // Пример 5: Все поля null
        User user5 = new User();
        Console.WriteLine($"User 5: {user5}");
    }
}