#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

/**
 * Функция для возведения в степень по модулю (a^b mod m).
 *
 * @param a Основание степени.
 * @param b Показатель степени.
 * @param m Модуль.
 * @return Результат вычисления a^b mod m.
 */
unsigned long long modPow(unsigned long long a, unsigned long long b, unsigned long long m)
{
    unsigned long long result = 1;
    a = a % m; // Убедимся, что a < m
    while (b > 0)
    {
        // Если b нечётное, умножаем результат на a по модулю m
        if (b % 2 == 1)
        {
            result = (result * a) % m;
        }
        // Возводим a в квадрат по модулю m
        a = (a * a) % m;
        // Делим b на 2
        b = b / 2;
    }
    return result;
}

/**
 * Функция для проверки простоты числа с использованием теста Миллера-Рабина.
 *
 * @param n Число, которое нужно проверить на простоту.
 * @param k Количество раундов теста (по умолчанию 5).
 * @return true, если число n вероятно простое, иначе false.
 */
bool isPrime(unsigned long long n, int k = 5)
{
    //Проверка
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0) return false;

    // Представляем n - 1 как d * 2^s
    unsigned long long d = n - 1;
    int s = 0;
    while (d % 2 == 0)
    {
        d /= 2;
        s++;
    }

    // Проводим k раундов теста Миллера-Рабина
    for (size_t i = 0; i < k; i++)
    {
        unsigned long long a = 2 + rand() % (n - 3); // Случайное число a в диапазоне [2, n-2]
        unsigned long long x = modPow(a, d, n); // Вычисляем a^d mod n
        if (x == 1 || x == n - 1) continue; // Если x == 1 или x == n-1, переходим к следующему раунду

        for (size_t j = 0; j < s - 1; j++)
        {
            x = modPow(x, 2, n); // Возводим x в квадрат по модулю n
            if (x == n - 1) break; // Если x == n-1, переходим к следующему раунду
        }

        if (x != n - 1) return false; // Если x != n-1, число составное
    }

    return true;
}

/**
 * Функция для генерации простого числа по алгоритму ГОСТ.
 *
 * @param t Требуемая длина числа в битах.
 * @param q Простое число длины [t/2] битов.
 * @return Простое число p длины t битов.
 */
unsigned long long generatePrimeGOST(int t, unsigned long long q)
{
    unsigned long long N, u, p;
    unsigned long long two = 2;

    unsigned long long pow2_t_minus_1 = 1ULL << (t - 1); // 2^(t-1)
    N = pow2_t_minus_1 / q;

    if (N % 2 != 0)
    {
        N += 1;
    }

    // Шаг 2: Инициализация u
    u = 0;

    while (true)
    {
        p = q * (N + u) + 1;

        // Проверка, что p <= 2^t
        unsigned long long pow2_t = 1ULL << t;
        if (p > pow2_t)
        {
            // Если p > 2^t, возвращаемся к шагу 1
            N += 2;
            u = 0;
            continue;
        }
        //Проверка условий
        unsigned long long pow2_p_minus_1 = modPow(2, p - 1, p);
        unsigned long long pow2_N_plus_u = modPow(2, N + u, p);

        if (pow2_p_minus_1 == 1 && pow2_N_plus_u != 1)
        {
            return p;
        }
        else
        {
            u += 2;
        }
    }
}

int main() {
    int t = 32; // Требуемая длина числа в битах
    unsigned long long q = 123456789; // Простое число длины [t/2] битов

    unsigned long long p = generatePrimeGOST(t, q);
    cout << "Сгенерированное простое число: " << p << endl;

    return 0;
}