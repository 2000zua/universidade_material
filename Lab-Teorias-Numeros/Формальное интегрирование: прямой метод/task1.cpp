#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <map>

using namespace std;

// Функция для разложения на простейшие дроби
map<string, double> partialFractionDecomposition(double numerator, double denominator) {
    map<string, double> result;

    // Пример разложения: ax + b / (x^2 + px + q)
    // Здесь мы просто делаем упрощенное разложение для примера
    // В реальной задаче нужно будет реализовать алгоритм разложения

    // Предположим, что у нас есть простейшие дроби
    result["1/(x+1)"] = numerator / denominator; // Пример
    return result;
}

// Функция для интегрирования простейших дробей
double integratePartialFraction(const string& fraction) {
    // Пример интегрирования: ∫(1/(x+a)) dx = ln|x+a| + C
    if (fraction == "1/(x+1)") {
        return 1; // Возвращаем 1, так как это просто ln|x+1| + C
    }
    return 0;
}

// Основная функция
int main() {
    double numerator, denominator;

    cout << "Введите числитель: ";
    cin >> numerator;
    cout << "Введите знаменатель: ";
    cin >> denominator;

    // Разложение на простейшие дроби
    map<string, double> fractions = partialFractionDecomposition(numerator, denominator);

    // Интегрирование каждой дроби
    for (const auto& fraction : fractions) {
        double integral = integratePartialFraction(fraction.first);
        cout << "Интеграл от " << fraction.first << " = " << integral << endl;
    }

    return 0;
}
