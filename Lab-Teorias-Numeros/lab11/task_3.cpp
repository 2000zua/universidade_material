#include <iostream>
#include <cmath>
#include <vector>
#include <cassert>

using namespace std;

typedef long long ll;

ll generateDataToText() {
    srand(time(0));
    ll num = rand() % 1000000 + 1; // Генерируем случайное число
    if (num % 2 == 0) num += 1; // Делаем его нечётным
    return num;
}

// Функция для вычисления наибольшего 
// общего делителя (НОД) с использованием алгоритма Евклида
ll gcd(ll a, ll b) {
    while (b != 0) {
        ll temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Функция для нахождения простого множителя 
// с использованием метода Шермана-Лемана
ll sherman_factor(ll n) {
    if (n % 2 == 0) return 2; // Проверяем, делится ли на 2

    ll x = 2;
    ll y = 2;
    ll d = 1;

    while (d == 1) {
        x = (x * x + 1) % n;  // Рекуррентное выражение для x
        y = (y * y + 1) % n;  // Рекуррентное выражение для y
        y = (y * y + 1) % n;  // y идет в два раза быстрее

        d = gcd(abs(x - y), n); // Находим НОД разницы x и y с числом n

        if (d == n) return -1; // Если НОД = n, то фактор не найден
    }

    return d; // Возвращаем найденный делитель
}

// Функция для разложения числа на простые множители
vector<ll> factorize(ll n) {
    vector<ll> factors;
    while (n % 2 == 0) {
        factors.push_back(2);
        n /= 2;
    }

    while (n > 1) {
        ll factor = sherman_factor(n);
        if (factor == -1) {
            factors.push_back(n); // Если число простое, добавляем его
            break;
        }
        while (n % factor == 0) {
            factors.push_back(factor);
            n /= factor;
        }
    }
    return factors;
}

int main() {
    ll n = generateDataToText();
    cout << "Сгенерированное число: " << n << endl;

    vector<ll> factors = factorize(n);

    cout << "Множители числа " << n << ": ";
    for (ll factor : factors) {
        cout << factor << " ";
    }
    cout << endl;

    return 0;
}
