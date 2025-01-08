#define _USE_MATH_DEFINES // Определяем макрос для использования M_PI
#include <cmath>          // Включаем заголовочный файл
#include <iostream>
#include <vector>
#include <complex>
#include <algorithm>

using namespace std;

// Тип для комплексных чисел
typedef complex<double> Complex;

/**
 * Функция для бит-реверсивной перестановки массива.
 * Переставляет элементы массива так, чтобы их индексы были в бит-реверсивном порядке.
 *
 * @param data Массив комплексных чисел, который нужно переставить.
 */
void BitReverse(vector<Complex>& data)
{
    size_t size = data.size();
    for (size_t i = 1, j = 0; i < size; i++)
    {
        size_t bit = size >> 1;
        for (; j >= bit; bit >>= 1)
        {
            j -= bit;
        }
        j += bit;
        if (i < j)
        {
            swap(data[i], data[j]);
        }
    }
}

/**
 * Итеративная реализация быстрого преобразования Фурье (FFT).
 * Выполняет прямое или обратное FFT в зависимости от параметра invert.
 *
 * @param data Массив комплексных чисел, который нужно преобразовать.
 * @param invert Если true, выполняется обратное FFT, иначе — прямое.
 */
void IterativeFFT(vector<Complex>& data, bool invert)
{
    size_t size = data.size();
    BitReverse(data); // Применяем бит-реверсивную перестановку

    // Проходим по уровням объединения
    for (size_t length = 2; length <= size; length <<= 1)
    {
        double angle = 2 * M_PI / length * (invert ? -1 : 1);
        Complex root(cos(angle), sin(angle)); // Корень из единицы

        // Обрабатываем каждый блок
        for (size_t i = 0; i < size; i += length)
        {
            Complex w(1);
            for (size_t j = 0; j < length / 2; j++)
            {
                Complex u = data[i + j];
                Complex v = w * data[i + j + length / 2];
                data[i + j] = u + v;
                data[i + j + length / 2] = u - v;
                w *= root;
            }
        }
    }

    // Если это обратное FFT, делим на size
    if (invert)
    {
        for (size_t i = 0; i < size; i++)
        {
            data[i] /= size;
        }
    }
}

/**
 * Функция для выполнения прямого или обратного FFT.
 * Дополняет массив до степени двойки и вызывает IterativeFFT.
 *
 * @param input Входной массив комплексных чисел.
 * @param invert Если true, выполняется обратное FFT, иначе — прямое.
 * @return Массив комплексных чисел после преобразования.
 */
vector<Complex> FFTTransform(const vector<Complex>& input, bool invert = false)
{
    vector<Complex> data = input;
    size_t size = data.size();

    // Дополняем массив до степени двойки (если необходимо)
    size_t newSize = 1;
    while (newSize < size) newSize <<= 1;
    data.resize(newSize, Complex(0, 0));

    // Выполняем FFT
    IterativeFFT(data, invert);

    return data;
}

/**
 * Функция для перемножения двух больших чисел, представленных в виде строк.
 *
 * @param num1 Первое число в виде строки.
 * @param num2 Второе число в виде строки.
 * @return Результат умножения в виде строки.
 */
string MultiplyLargeNumbers(const string& num1, const string& num2)
{
    // Преобразуем цифры чисел в коэффициенты многочленов
    vector<Complex> poly1, poly2;
    for (char ch : num1) poly1.push_back(ch - '0');
    for (char ch : num2) poly2.push_back(ch - '0');

    // Определяем размер результата (степень многочлена + 1)
    size_t size = 1;
    while (size < poly1.size() + poly2.size()) size <<= 1;

    // Дополняем массивы до размера size
    poly1.resize(size, Complex(0, 0));
    poly2.resize(size, Complex(0, 0));

    // Прямое FFT для обоих многочленов
    poly1 = FFTTransform(poly1);
    poly2 = FFTTransform(poly2);

    // Поэлементное умножение
    vector<Complex> result(size);
    for (size_t i = 0; i < size; i++)
    {
        result[i] = poly1[i] * poly2[i];
    }

    // Обратное FFT
    result = FFTTransform(result, true);

    // Преобразуем результат в массив целых чисел
    vector<int> finalResult(size);
    for (size_t i = 0; i < size; i++)
    {
        finalResult[i] = round(result[i].real());
    }

    // Нормализация результата (учёт переносов)
    int carry = 0;
    for (size_t i = 0; i < size; i++)
    {
        finalResult[i] += carry;
        carry = finalResult[i] / 10;
        finalResult[i] %= 10;
    }

    // Убираем ведущие нули
    while (finalResult.size() > 1 && finalResult.back() == 0)
    {
        finalResult.pop_back();
    }

    // Преобразуем результат в строку
    string resultStr;
    for (int coeff : finalResult)
    {
        resultStr += to_string(coeff);
    }

    // Разворачиваем строку, так как коэффициенты хранились в обратном порядке
    reverse(resultStr.begin(), resultStr.end());

    return resultStr;
}

int main() {
    setlocale(LC_ALL, "RU");
    // Пример больших чисел
    string num1 = "1234567892392903892";
    string num2 = "987654321239203909";

    // Перемножение чисел
    string result = MultiplyLargeNumbers(num1, num2);

    // Вывод результата
    cout << "Результат умножения: " << result << endl;

    return 0;
}