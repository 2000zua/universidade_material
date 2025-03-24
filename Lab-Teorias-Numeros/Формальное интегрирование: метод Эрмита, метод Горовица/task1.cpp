#include <iostream>
#include <vector>
#include <cmath>
#include <stdexcept>

class Polynomial {
public:
    std::vector<double> coefficients; // Коэффициенты полинома

    Polynomial() {}

    Polynomial(const std::vector<double>& coeffs) : coefficients(coeffs) {}

    // Метод для вычисления значения полинома в точке x
    double evaluate(double x) const {
        double result = 0.0;
        for (int i = 0; i < coefficients.size(); ++i) {
            result += coefficients[i] * std::pow(x, i);
        }
        return result;
    }

    // Метод для интегрирования полинома
    Polynomial integrate() const {
        std::vector<double> newCoeffs(coefficients.size() + 1);
        for (int i = 0; i < coefficients.size(); ++i) {
            newCoeffs[i + 1] = coefficients[i] / (i + 1);
        }
        return Polynomial(newCoeffs);
    }

    // Перегрузка оператора сложения
    Polynomial operator+(const Polynomial& other) const {
        std::vector<double> newCoeffs(std::max(coefficients.size(), other.coefficients.size()), 0.0);
        
        for (size_t i = 0; i < coefficients.size(); ++i) {
            newCoeffs[i] += coefficients[i];
        }
        for (size_t i = 0; i < other.coefficients.size(); ++i) {
            newCoeffs[i] += other.coefficients[i];
        }
        
        return Polynomial(newCoeffs);
    }

    // Метод для вывода полинома
    void print() const {
        for (int i = 0; i < coefficients.size(); ++i) {
            if (i > 0) std::cout << " + ";
            std::cout << coefficients[i] << "x^" << i;
        }
        std::cout << std::endl;
    }
};

// Функция для разложения дробнорациональной функции на простые дроби
std::vector<Polynomial> partialFractionDecomposition(const Polynomial& numerator, const Polynomial& denominator) {
    // Здесь должна быть реализация разложения на простые дроби
    // Для простоты примера, мы просто вернем вектор с одним элементом
    return { numerator }; // Это временное решение
}

// Функция для формального интегрирования дробнорациональной функции
Polynomial hermiteIntegration(const Polynomial& numerator, const Polynomial& denominator) {
    // Разложение на простые дроби
    std::vector<Polynomial> fractions = partialFractionDecomposition(numerator, denominator);
    
    Polynomial result;
    for (const auto& fraction : fractions) {
        result = result + fraction.integrate(); // Интегрируем каждую дробь
    }
    return result;
}

int main() {
    // Пример использования
    Polynomial numerator({1, 0, -1}); // x^2 - 1
    Polynomial denominator({1, 0, 0}); // x^2

    Polynomial result = hermiteIntegration(numerator, denominator);
    std::cout << "Результат интегрирования: ";
    result.print();

    return 0;
}
