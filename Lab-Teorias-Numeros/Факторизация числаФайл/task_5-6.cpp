#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// Функция для нахождения наибольшего общего делителя (НОД)
long long gcd(long long a, long long b) {
    while (b != 0) {
        long long t = b;
        b = a % b;
        a = t;
    }
    return a;
}

// Функция для вычисления следующего значения последовательности
long long f(long long x, long long n) {
    return (x * x + 1) % n; // Простая функция для генерации последовательности
}

// Функция для факторизации числа методом Полларда
long long pollardRho(long long n) {
    if (n % 2 == 0) return 2; // Проверка на четность

    long long x = 2; // Начальное значение
    long long y = 2; // Второе значение
    long long d = 1; // НОД
    long long count = 0; // Счетчик итераций

    while (d == 1) {
        count++;
        x = f(x, n);
        y = f(f(y, n), n); // "Удвоение" для быстрого указателя

        d = gcd(abs(x - y), n); // НОД между разностью и n

        // Если d становится равным n, значит, не удалось найти делитель
        if (d == n) {
            return -1; // Не удалось найти делитель
        }
    }

    return d; // Возвращаем найденный делитель
}

// Функция для факторизации числа
vector<long long> factorize(long long n) {
    vector<long long> factors;

    while (n % 2 == 0) {
        factors.push_back(2);
        n /= 2;
    }

    if (n == 1) return factors;

    while (n > 1) {
        long long factor = pollardRho(n);
        if (factor == -1) {
            factors.push_back(n); // n является простым
            break;
        }
        factors.push_back(factor);
        n /= factor;
    }

    return factors;
}

int main() {
    long long n;
    cout << "Введите число для факторизации: ";
    cin >> n;

    vector<long long> factors = factorize(n);

    cout << "Простые множители числа " << n << ": ";
    for (size_t i = 0; i < factors.size(); ++i) {
        cout << factors[i];
        if (i < factors.size() - 1) {
            cout << " * ";
        }
    }
    cout << endl;

    return 0;
}
