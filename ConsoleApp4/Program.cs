using System;
using System.Collections.Generic;
using System.Linq; // Для вычисления среднего

class Program
{
    static void Main(string[] args)
    {
        ProcessProducts(
            "Яблоко:1.00",
            "Банан:0.75",
            "Апельсин:1.25",
            "Груша:0.90"
        );
    }

    static void ProcessProducts(params string[] productData)
    {
        if (productData == null || productData.Length == 0)
        {
            Console.WriteLine("Нет данных о товарах.");
            return;
        }

        var productNames = new List<string>();
        var productPrices = new List<double>();

        foreach (var item in productData)
        {
            // Разделяем строку на название и цену
            var parts = item.Split(':');

            if (parts.Length == 2)
            {
                string name = parts[0].Trim();
                if (double.TryParse(parts[1].Trim(), out double price))
                {
                    productNames.Add(name);
                    productPrices.Add(price);
                }
                else
                {
                    Console.WriteLine($"Ошибка: Некорректный формат цены для товара '{name}'.");
                    return;
                }
            }
            else
            {
                Console.WriteLine($"Ошибка: Некорректный формат данных о товаре '{item}'.");
                return;
            }
        }

        if (productNames.Count == 0)
        {
            Console.WriteLine("Нет корректных данных о товарах.");
            return;
        }

        // Вычисление средней цены товаров
        var averagePrice = productPrices.Average();

        // Вывод средней цены на экран
        Console.WriteLine($"Средняя цена товаров: {averagePrice:F2}");

        // Вывод списка товаров и цен
        for (var i = 0; i < productNames.Count; i++)
        {
            Console.WriteLine($"{productNames[i]}: {productPrices[i]:F2}");
        }
    }
    static double CalculateAverage(double[] prices)
    {
        if (prices == null || prices.Length == 0)
        {
            return 0.0;
        }
        return prices.Average();
    }
}