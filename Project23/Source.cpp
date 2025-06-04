?using System;
using System.Linq;

public class Program
{
    public static void Main(string[] args)
    {
        Console.WriteLine("������� ���������� �����:");
        int rows = int.Parse(Console.ReadLine());

        Console.WriteLine("������� ���������� ��������:");
        int cols = int.Parse(Console.ReadLine());

        int[, ] matrix = new int[rows, cols];

        Console.WriteLine("������� �������� �������:");

        // ���������� �������
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                Console.Write($"������� [{i + 1}, {j + 1}]: ");
                matrix[i, j] = int.Parse(Console.ReadLine());
            }
        }

        Console.WriteLine("\n������ � �������� ������� (�� �������):");

        // ����� ������� � �������� �������
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