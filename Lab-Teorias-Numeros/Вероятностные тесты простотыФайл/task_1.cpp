#include <iostream>
#include <cstdlib>
#include <ctime>

// Функция возведения в степень по модулю
int powMod(int, int, int);

// Функция проверки простоты числа с помощью теста П. Ферма
bool isPrimeFermat(int , int);


int main() {
    int n = 100; // число, состоящее из 100 десятичных цифр
    int k = 5; // количество испытаний

    // Генерация случайного числа из 100 десятичных цифр
    srand(time(0));
    n = rand() % 1000000000 + 1000000000;

    clock_t start = clock();
    bool isPrime = isPrimeFermat(n, k);
    clock_t end = clock();

    double time = (double)(end - start) / CLOCKS_PER_SEC;

    std::cout << "Число: " << n << std::endl;
    std::cout << "Простое: " << (isPrime ? "да" : "нет") << std::endl;
    std::cout << "Время проверки: " << time << " секунд" << std::endl;

    return 0;
}


int powMod(int a, int b, int n){
    int res = 1;
    while (b > 0) {
        if (b % 2 == 1) res = (res * a) % n;
        a = (a * a) % n;
        b /= 2;
    }
    return res;
}

bool isPrimeFermat(int n, int k) {
    if (n <= 1) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;

    srand(time(0));
    for (int i = 0; i < k; i++) {
        int a = rand() % (n - 2) + 2;
        if (powMod(a, n - 1, n) != 1) return false;
    }
    return true;
}
