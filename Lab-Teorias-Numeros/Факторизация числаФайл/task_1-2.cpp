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

// Функция для факторизации числа методом Ферма
set<long long> fermatFactorization(long long n) {
    set<long long> factors; // Используем множество для исключения дубликатов

    // Проверка на четность
    while (n % 2 == 0) {
        factors.insert(2);
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
                factors.insert(factor1);
            }
            if (factor2 > 1 && factor2 != factor1) {
                factors.insert(factor2);
            }

            // Проверяем, являются ли найденные множители простыми
            if (factor1 > 1) {
                long long gcd1 = gcd(n, factor1);
                if (gcd1 > 1 && gcd1 < n) {
                    factors.insert(gcd1);
                    factors.insert(n / gcd1);
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

    cout << endl;
    // Минимальное количество итераций
    for (int i = 0; i < 3; i++){
        set<long long> factors = fermatFactorization(inputMin[i]);

        cout << "Простые множители числа " << inputMin[i] << " =>> ";
        for (auto it = factors.begin(); it != factors.end(); ++it) {
            cout << *it;
            if (next(it) != factors.end()) {
                cout << "*";
            }
        }
        cout << endl;
    }

    cout << endl;

    // Максимальное количество итераций
    for (int i = 0; i < 4; i++){

        set<long long> factors = fermatFactorization(inputMax[i]);

        cout << "Простые множители числа " << inputMax[i] << " =>> ";
        for (auto it = factors.begin(); it != factors.end(); ++it) {
            cout << *it;
            if (next(it) != factors.end()) {
                cout << "*";
            }
        }
        cout << endl;
    }
    cout << endl;

    return 0;
}

