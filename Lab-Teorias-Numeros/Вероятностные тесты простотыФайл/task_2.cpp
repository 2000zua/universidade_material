#include <iostream>
#include <cstdlib>
#include <ctime>

// Функция для вычисления НОД(a, n)
int gcd(int, int );

// Функция для вычисления символа Якоби (a/n)
int jacobi(int, int );

// Функция для проверки простоты числа с помощью теста Соловея-Штрассена
bool isPrimeSoloveyStrassen(int, int);

// Функция для вычисления a^b mod n
int powMod(int , int, int);


int main() {
    int n = 100; // число, которое нужно проверить
    int k = 5; // количество испытаний

    // Генерация случайного числа с 100 десятичными цифрами
    srand(time(0));
    n = rand() % 1000000000 + 1000000000;

    clock_t start = clock();
    bool isPrime = isPrimeSoloveyStrassen(n, k);
    clock_t end = clock();

    double time = (double)(end - start) / CLOCKS_PER_SEC;

    std::cout << "Число: " << n << std::endl;
    std::cout << "Простое: " << (isPrime ? "да" : "нет") << std::endl;
    std::cout << "Время проверки: " << time << " секунд" << std::endl;

    return 0;
}


int gcd(int a, int n) {
    if (a == 0) return n;
    return gcd(n % a, a);
}


int jacobi(int a, int n) {
    int res = 1;
    while (a != 0) {
        while (a % 2 == 0) {
            a /= 2;
            if (n % 8 == 3 || n % 8 == 5) res = -res;
        }
        if (a % 4 == 3 && n % 4 == 3) res = -res;
        int temp = a;
        a = n;
        n = temp;
        a %= n;
    }
    return res;
}

bool isPrimeSoloveyStrassen(int n, int k) {
    if (n <= 1) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;

    srand(time(0));
    for (int i = 0; i < k; i++) {
        int a = rand() % (n - 2) + 2;
        if (gcd(a, n) != 1) return false;
        int t = powMod(a, (n - 1) / 2, n);
        int q = jacobi(a, n);
        if (t != q) return false;
    }
    return true;
}

int powMod(int a, int b, int n) {
    int res = 1;
    while (b > 0) {
        if (b % 2 == 1) res = (res * a) % n;
        a = (a * a) % n;
        b /= 2;
    }
    return res;
}
