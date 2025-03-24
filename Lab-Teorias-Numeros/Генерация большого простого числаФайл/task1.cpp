#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <chrono> // Для измерения времени

using namespace std;

// Функция для проверки простоты числа с помощью теста Миллера-Рабина
bool is_prime(uint64_t n, int k = 5) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0) return false;

    uint64_t d = n - 1;
    int r = 0;
    while (d % 2 == 0) {
        d /= 2;
        r++;
    }

    for (int i = 0; i < k; i++) {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<uint64_t> dis(2, n - 2);
        uint64_t a = dis(gen);

        uint64_t x = pow(a, d) - 1; // a^d % n
        if (x == 0 || x == n - 1) continue;

        bool composite = true;
        for (int j = 0; j < r - 1; j++) {
            x = (x * x) % n;
            if (x == n - 1) {
                composite = false;
                break;
            }
        }
        if (composite) return false;
    }
    return true;
}

// Функция для генерации простого числа заданной длины в битах
uint64_t generate_large_prime(int bits, int &iterations) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<uint64_t> dis(1ULL << (bits - 2), (1ULL << (bits - 1)) - 1);

    while (true) {
        uint64_t candidate = dis(gen);
        candidate |= 1; // Устанавливаем младший бит
        candidate |= (1ULL << (bits - 1)); // Устанавливаем старший бит

        iterations++; // Увеличиваем счетчик итераций

        if (is_prime(candidate)) {
            return candidate;
        }
    }
}

int main() {
    int bits;
    cout << "Введите количество бит для генерации простого числа: ";
    cin >> bits;

    int iterations = 0; // Счетчик итераций
    auto start = chrono::high_resolution_clock::now(); // Начало отсчета времени

    uint64_t prime = generate_large_prime(bits, iterations);

    auto end = chrono::high_resolution_clock::now(); // Конец отсчета времени
    chrono::duration<double> duration = end - start; // Вычисление времени

    cout << "Сгенерированное простое число: " << prime << endl;
    cout << "Количество итераций: " << iterations << endl;
    cout << "Время генерации: " << duration.count() << " секунд" << endl;

    return 0;
}
