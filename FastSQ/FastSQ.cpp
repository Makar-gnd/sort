#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/**
 * Функция для быстрого возведения числа в квадрат.
 *
 * @param x Вектор цифр числа (начиная со старшего разряда).
 * @param base Основание системы счисления.
 * @return Вектор цифр результата (начиная со старшего разряда).
 */
vector<int> fastSquare(const vector<int>& x, int base)
{
    // Переворачиваем число, чтобы работать с младшим разрядом первым
    vector<int> reversedX = x;
    reverse(reversedX.begin(), reversedX.end());

    size_t n = reversedX.size();
    size_t resultSize = 2 * n;
    vector<int> y(resultSize, 0); // Результат (изначально заполнен нулями)

    for (size_t i = 0; i < n; ++i)
    {
        int carry = 0;

        // Шаг 2.1: Вычисление квадрата текущей цифры
        int uv = y[2 * i] + reversedX[i] * reversedX[i];
        y[2 * i] = uv % base; // Записываем младший разряд
        carry = uv / base;    // Запоминаем перенос

        // Шаг 2.2: Вычисление произведений с другими цифрами
        for (size_t j = i + 1; j < n; ++j)
        {
            int cuv = y[i + j] + 2 * reversedX[i] * reversedX[j] + carry;
            y[i + j] = cuv % base; // Записываем младший разряд
            carry = cuv / base;    // Запоминаем перенос
        }

        // Шаг 2.3: Обработка оставшегося переноса
        y[i + n] += carry;
    }

    // Удаляем ведущие нули (если они есть)
    while (y.size() > 1 && y.back() == 0)
    {
        y.pop_back();
    }

    // Переворачиваем результат обратно
    reverse(y.begin(), y.end());

    return y;
}

/**
 * Функция для вывода числа, представленного вектором цифр.
 *
 * @param number Вектор цифр числа (начиная со старшего разряда).
 */
void printNumber(const vector<int>& number)
{
    for (int digit : number)
    {
        cout << digit;
    }
    cout << endl;
}

int main() 
{
    // Пример использования
    vector<int> x = { 1, 2, 3 }; // Число 123 
    int base = 10; //основание системы 

    cout << "Исходное число: ";
    printNumber(x);

    vector<int> result = fastSquare(x, base);

    cout << "Результат возведения в квадрат: ";
    printNumber(result);

    return 0;
}