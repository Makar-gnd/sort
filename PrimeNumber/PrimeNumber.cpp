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
long long modPow(long long a, long long b, long long m)
{
    long long result = 1;
    a = a % m;
    while (b > 0)
    {
        if (b % 2 == 1)
        {
            result = (result * a) % m;
        }
        a = (a * a) % m;
        b = b / 2;
    }
    return result;
}

/**
 * Функция для факторизации числа (разложения на простые множители).
 *
 * @param n Число, которое нужно факторизовать.
 * @return Вектор простых делителей числа n.
 */
vector<long long> factorize(long long n)
{
    vector<long long> factors;
    while (n % 2 == 0)
    {
        factors.push_back(2);
        n = n / 2;
    }
    // Обрабатываем нечётные делители от 3 до sqrt(n)
    for (long long i = 3; i <= sqrt(n); i += 2)
    {
        while (n % i == 0) 
        {
            factors.push_back(i);
            n = n / i;
        }
    }
    // Если остался простой делитель больше 2
    if (n > 2) 
    {
        factors.push_back(n);
    }
    return factors;
}

/**
 * Функция для проверки простоты числа методом Люка.
 *
 * @param n Число, которое нужно проверить на простоту.
 * @return true, если число n простое, иначе false.
 */
bool isPrimeLucas(long long n) 
{
    // Обработка тривиальных случаев
    if (n < 2) return false;
    if (n == 2) return true;

    // Факторизация n - 1
    long long n_minus_1 = n - 1;
    vector<long long> factors = factorize(n_minus_1);

    // Удаляем дубликаты делителей
    sort(factors.begin(), factors.end());
    factors.erase(unique(factors.begin(), factors.end()), factors.end());

    cout << "Простые делители " << n_minus_1 << ": ";
    for (long long factor : factors) 
    {
        cout << factor << " ";
    }
    cout << endl;

    for (long long a = 2; a <= 10; ++a) 
    {
        // Проверяем условие a^(n-1) ≡ 1 mod n
        if (modPow(a, n_minus_1, n) != 1) {
            continue;
        }
        // Проверяем условия для каждого простого делителя q из factors
        bool isWitness = true;
        for (long long q : factors)
        {
            // Проверяем, что a^((n-1)/q) ≢ 1 mod n
            if (modPow(a, n_minus_1 / q, n) == 1) 
            {
                isWitness = false;
                break;
            }
        }
        // Если все условия выполнены, число n простое
        if (isWitness)
        {
            return true;
        }
    }
    return false;
}

int main() {
    setlocale(LC_ALL, "RU");
    long long n;
    cout << "Введите число для проверки на простоту: ";
    cin >> n;

    if (isPrimeLucas(n)) {
        cout << n << " — простое число." << endl;
    }
    else {
        cout << n << " — составное число." << endl;
    }

    return 0;
}