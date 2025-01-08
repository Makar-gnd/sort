#include <iostream>
using namespace std;

/**
 * Функция для подсчёта количества цифр в числе.
 *
 * @param num Число, для которого нужно определить длину.
 * @return Количество цифр в числе. Если число равно 0, возвращает 1.
 */
size_t getNumberLength(size_t num)
{
    size_t length = 0;
    while (num > 0)
    {
        length++;
        num /= 10;
    }
    return length > 0 ? length : 1; // Если число равно 0, длина должна быть 1
}

/**
 * Функция для целочисленного возведения в степень.
 *
 * @param base Основание степени.
 * @param exp Показатель степени.
 * @return Результат возведения base в степень exp.
 */
size_t intPow(size_t base, size_t exp)
{
    size_t result = 1;

    for (size_t i = 0; i < exp; i++) {
        result *= base;
    }
    return result;
}

/**
 * Функция для умножения двух чисел с использованием алгоритма Карацубы.
 *
 * @param FirstNumber Первое число для умножения.
 * @param SecondNumber Второе число для умножения.
 * @return Результат умножения FirstNumber на SecondNumber.
 */
size_t karatsuba(size_t FirstNumber, size_t SecondNumber) {
    // Базовый случай для прекращения рекурсии
    if (FirstNumber < 10 || SecondNumber < 10)
        return FirstNumber * SecondNumber;

    // Определяем длину большего числа
    const size_t maxLength = max(getNumberLength(FirstNumber), getNumberLength(SecondNumber));
    const size_t halfLength = maxLength / 2;

    // Вычисляем основание разбиения (10^halfLength)
    const size_t base = intPow(10, halfLength);

    // Разделяем числа на старшие и младшие разряды
    const size_t highPart1 = FirstNumber / base; // Старшая часть первого числа
    const size_t lowPart1 = FirstNumber % base;  // Младшая часть первого числа
    const size_t highPart2 = SecondNumber / base; // Старшая часть второго числа
    const size_t lowPart2 = SecondNumber % base;  // Младшая часть второго числа

    // Рекурсивные вычисления
    const size_t productLow = karatsuba(lowPart1, lowPart2);                           // Произведение младших частей
    const size_t productCross = karatsuba(lowPart1 + highPart1, lowPart2 + highPart2); // Произведение сумм частей
    const size_t productHigh = karatsuba(highPart1, highPart2);                        // Произведение старших частей

    // Сборка результата
    return productHigh * intPow(10, 2 * halfLength) +
        (productCross - productHigh - productLow) * intPow(10, halfLength) +
        productLow;
}

int main() {
    setlocale(LC_ALL, "RU");
    size_t FirstNumber, SecondNumber;

    // Ввод чисел с клавиатуры
    cout << "Введите первое число: ";
    cin >> FirstNumber;
    cout << "Введите второе число: ";
    cin >> SecondNumber;

    // Вывод результата умножения
    cout << "Результат умножения: " << karatsuba(FirstNumber, SecondNumber) << endl;

    return 0;
}