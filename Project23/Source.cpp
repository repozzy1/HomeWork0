?using System;
using System.Linq;

public class Program
{
    public static void Main(string[] args)
    {
        Console.WriteLine("Введите количество строк:");
        int rows = int.Parse(Console.ReadLine());

        Console.WriteLine("Введите количество столбцов:");
        int cols = int.Parse(Console.ReadLine());

        int[, ] matrix = new int[rows, cols];

        Console.WriteLine("Введите элементы массива:");

        // Заполнение массива
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                Console.Write($"Элемент [{i + 1}, {j + 1}]: ");
                matrix[i, j] = int.Parse(Console.ReadLine());
            }
        }

        Console.WriteLine("\nМассив в обратном порядке (по строкам):");

        // Вывод массива в обратном порядке
        for (int i = 0; i < rows; i++)
        {
            int[] row = Enumerable.Range(0, cols)
                .Select(j = > matrix[i, j])
                .Reverse()
                .ToArray();

            foreach(int element in row)
            {
                Console.Write(element + " ");
            }
            Console.WriteLine();
        }
    }
}