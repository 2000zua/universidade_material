#include <iostream>
#include <cmath>
#include <vector>
#include <set>

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

// Функция для проверки, является ли число простым
bool isPrime(long long n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (long long i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

// Функция для факторизации числа методом Шермана-Лемана
vector<long long> shermanLemanFactorization(long long n) {
    vector<long long> factors;

    // Проверка на четность
    while (n % 2 == 0) {
        factors.push_back(2);
        n /= 2;
    }

    // Если n стало 1, возвращаем найденные множители
    if (n == 1) {
        return factors;
    }

    long long a = ceil(sqrt(n));
    long long b2 = a * a - n;

    while (true) {
        long long b = sqrt(b2);
        if (b * b == b2) {
            long long factor1 = a - b;
            long long factor2 = a + b;

            // Добавляем найденные множители
            if (factor1 > 1) {
                factors.push_back(factor1);
            }
            if (factor2 > 1 && factor2 != factor1) {
                factors.push_back(factor2);
            }

            // Проверяем, являются ли найденные множители простыми
            if (factor1 > 1) {
                long long gcd1 = gcd(n, factor1);
                if (gcd1 > 1 && gcd1 < n) {
                    factors.push_back(gcd1);
                    factors.push_back(n / gcd1);
                }
            }
            break;
        }
        a++;
        b2 = a * a - n;
    }

    return factors;
}

int main() {
    int inputMin[] = {15, 21, 10, 16};
    int inputMax[] = {20, 77, 221, 5959};

    long long n;
    cout << "Введите число для факторизации: ";
    cin >> n;

    vector<long long> factors = shermanLemanFactorization(n);

    cout << "Простые множители числа " << n << ": ";
    for (size_t i = 0; i < factors.size(); ++i) {
        cout << factors[i];
        if (i < factors.size() - 1) {
            cout << "*";
        }
    }
    cout << endl;

    return 0;
}
