#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

typedef long long ll;

// Функция генерации случайного нечётного числа
ll generateDataToText() {
    srand(time(0));
    ll num = rand() % 1000000 + 1; // Генерируем случайное число
    if (num % 2 == 0) num += 1; // Делаем его нечётным
    return num;
}

// Функция метода Ферма
void fermatFactorization(ll n) {
    if (n % 2 == 0) {
        cout << "Число чётное, используйте другой метод." << endl;
        return;
    }
    
    ll x = ceil(sqrt(n));
    ll y2;
    ll y;
    int iterations = 0; // Счётчик итераций
    
    while (true) {
        y2 = x * x - n;
        ll yRoot = (ll) sqrt(y2);
         // Проверяем, является ли y2 полным квадратом
         iterations++;
        if (yRoot * yRoot == y2) {
            y = yRoot;
            break;
        }
        x += 1;
    }
    
    ll factor1 = x + y;
    ll factor2 = x - y;
    
    cout << "Множители числа " << n << " : " << factor1 << " и " << factor2 << endl;
    cout << "Число итераций: " << iterations << endl;
}

int main() {
    ll n = generateDataToText();
    cout << "Сгенерированное число: " << n << endl;
    fermatFactorization(n);
    return 0;
}
