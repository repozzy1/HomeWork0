using System;
using System.Collections.Generic;
using System.Linq;

public class ArrHelper
{
    // Удаление первого элемента
    public static bool RemoveFirst<T>(ref T[] array, out T removedElement)
    {
        if (array == null || array.Length == 0)
        {
            removedElement = default(T);
            return false;
        }

        removedElement = array[0];
        array = array.Skip(1).ToArray();

        return true;
    }

    // Удаление последнего элемента
    public static bool RemoveLast<T>(ref T[] array, out T removedElement)
    {
        if (array == null || array.Length == 0)
        {
            removedElement = default(T);
            return false;
        }

        removedElement = array[array.Length - 1];
        array = array.Take(array.Length - 1).ToArray();

        return true;
    }

    // Удаление элемента по индексу
    public static bool RemoveAt<T>(ref T[] arr, int index, out T removElement)
    {
        if (arr == null || arr.Length == 0 || index < 0 || index >= arr.Length)
        {
            removElement = default(T);
            return false;
        }

        removElement = arr[index];
        arr = arr.Where((e, i) => i != index).ToArray();

        return true;
    }

    public static void Main(string[] args)
    {
        int[] myArr = { 1, 2, 3, 4, 5 };
        int remov;

        // Удаление первого элемента
        if (RemoveFirst(ref myArr, out remov))
        {
            Console.WriteLine("Удален первый элемент: " + remov);
            Console.WriteLine("Новый массив: " + string.Join(", ", myArr));
        }
        else
        {
            Console.WriteLine("Не удалось удалить первый элемент.");
        }

        // Удаление последнего элемента
        string[] stringArr = { "a", "b", "c", "d" };
        string removString;
        if (RemoveLast(ref stringArr, out removString))
        {
            Console.WriteLine("Удален последний элемент: " + removString);
            Console.WriteLine("Новый массив: " + string.Join(", ", stringArr));
        }
        else
        {
            Console.WriteLine("Не удалось удалить последний элемент.");
        }


        // Удаление элемента по индексу
        double[] doubleArr = { 1.1, 2.2, 3.3, 4.4 };
        double removDouble;

        if (RemoveAt(ref doubleArr, 1, out removDouble))
        {
            Console.WriteLine("Удален элемент по индексу 1: " + removDouble);
            Console.WriteLine("Новый массив: " + string.Join(", ", doubleArr));
        }
        else
        {
            Console.WriteLine("Не удалось удалить элемент по индексу 1.");
        }

    }
}

        }
    }
}