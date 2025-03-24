#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

// Функция для вычисления x = a^(n-1) mod n
int powmod(int, int, int);

// Функция для проверки простоты числа n с помощью теста Рабина-Миллера
bool rabina_miller(int, int);

int main() {
    srand(time(0)); // Инициализация генератора случайных чисел
    int n, k;

    std::cout << "Введите число n: ";
    std::cin >> n;

    double p;
    std::cout << "Введите допустимую величину погрешности p: ";
    std::cin >> p;

    k = ceil(log(1 / p) / log(4));
    std::cout << "Количество испытаний: " << k << std::endl;
    
    if (rabina_miller(n, k)) {
        std::cout << "Число " << n << " возможно простое." << std::endl;
    } else {
        std::cout << "Число " << n << " составное." << std::endl;
    }
    return 0;
}


int powmod(int a, int n, int mod) {
    int x = 1;
    for (int i = 0; i < n; i++) {
        x = (x * a) % mod;
    }
    return x;
}

bool rabina_miller(int n, int k) {
    for (int i = 0; i < k; i++) {
        int a = rand() % (n - 2) + 2; // Выбрать случайное число a в интервале от 2 до n-2
        int x = powmod(a, n - 1, n);
        if (x == 1 || x == n - 1) continue;
        for (int j = 0; j < n - 2; j++) {
            x = (x * x) % n;
            if (x == n - 1) break;
        }
        if (x != n - 1) return false;
    }
    return true;
}
