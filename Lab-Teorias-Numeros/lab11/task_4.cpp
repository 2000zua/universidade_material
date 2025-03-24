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

// Функция для вычисления наибольшего общего делителя (НОД) с использованием алгоритма Евклида
ll gcd(ll a, ll b) {
    while (b != 0) {
        ll temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Функция для возведения числа в степень по модулю
ll mod_exp(ll base, ll exp, ll mod) {
    ll result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp = exp / 2;
    }
    return result;
}

// Метод Полларда p-1 для нахождения простых множителей
ll pollard_p1(ll N, ll B) {
    ll a = 2;  // Начальное значение a
    ll x = 1;

    // Вычисляем a^B mod N
    for (ll i = 1; i <= B; ++i) {
        x = (x * a) % N;
    }

    // Вычисляем НОД(a^B - 1, N)
    ll d = gcd(abs(x - 1), N);
    
    // Если НОД не равен 1 и не равно N, то это множитель
    if (d != 1 && d != N) {
        return d;
    }
    
    return -1;  // Если множитель не найден
}

// Функция для разложения числа на простые множители с использованием метода p-Полларда
vector<ll> factorize(ll n, ll B) {
    vector<ll> factors;

    // Пробуем разложить число на простые множители
    while (n % 2 == 0) {
        factors.push_back(2);
        n /= 2;
    }

    // Для других множителей
    while (n > 1) {
        ll factor = pollard_p1(n, B);
        if (factor == -1) {
            factors.push_back(n); // Если число простое, добавляем его
            break;
        }

        // Если нашли множитель, продолжаем делить
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

    // Проверка на значение n
    if (n <= 1) {
        cout << "Число должно быть больше 1." << endl;
        return 1;
    }

    ll B = 10;  // Параметр B для метода p-Полларда (можно изменить для настройки)

    vector<ll> factors = factorize(n, B);

    cout << "Множители числа " << n << ": ";
    for (ll factor : factors) {
        cout << factor << " ";
    }
    cout << endl;

    return 0;
}
