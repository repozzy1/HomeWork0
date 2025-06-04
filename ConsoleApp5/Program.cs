using System;
enum EducationForm { Очная, Заочная, Вечерняя }

class Student
{
    public string Name { get; set; }
    public int Course { get; set; }
    public EducationForm Form { get; set; }

    public void Study()
    {
        Console.WriteLine($"{Name} учится на {Course} курсе, форма обучения: {Form}");
    }
}
class Example
{
    public static void Main(string[] args)
    {
        Student student = new Student { Name = "Иван", Course = 3, Form = EducationForm.Очная };
        student.Study();
    }
}