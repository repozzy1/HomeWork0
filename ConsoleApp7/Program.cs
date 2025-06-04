using System;

class Student
{
    public string FirstName { get; set; }
    public string LastName { get; set; }
    public double GPA { get; set; } //Успеваемость
}

static class StudentExtensions
{
    public static void PrintInfo(this Student student)
    {
        Console.WriteLine($"Полное имя: {student.FirstName} {student.LastName}, Успеваемость: {student.GPA}");
    }
}

class Example
{
    public static void Main(string[] args)
    {
        Student student = new Student { FirstName = "Иван", LastName = "Иванов", GPA = 4.5 };
        student.PrintInfo(); // Вызов extension-метода
    }
}