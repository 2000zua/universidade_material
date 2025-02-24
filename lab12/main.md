# README - Implementação de Aritmética Polinomial em C++

## Descrição
Este projeto implementa operações básicas de aritmética polinomial em C++.
Ele inclui:
- Representação de polinômios usando um vetor de coeficientes.
- Avaliação do valor do polinômio em um ponto específico.
- Utilização do esquema de Horner para cálculo eficiente de polinômios.
- Três métodos diferentes de exponenciação:
  1. **Método Binário**: Utiliza exponenciação rápida baseada em divisões sucessivas do expoente.
  2. **Método dos Multiplicadores**: Realiza multiplicações sucessivas.
  3. **Árvore de Potências**: Utiliza recursão para reduzir o número de multiplicações.

## Estrutura do Código

### Classe `Polynomial`
A classe `Polynomial` representa um polinômio de uma variável e possui os seguintes métodos:

- **Construtor:**
  ```cpp
  Polynomial(const std::vector<double>& coeffs);
  ```
  Inicializa um polinômio com os coeficientes fornecidos.

- **Impressão do polinômio:**
  ```cpp
  void print() const;
  ```
  Exibe o polinômio na forma matemática legível.

- **Avaliação direta do polinômio:**
  ```cpp
  double evaluate(double x) const;
  ```
  Calcula o valor do polinômio para um dado `x` usando multiplicação direta.

- **Avaliação usando o esquema de Horner:**
  ```cpp
  double horner(double x) const;
  ```
  Implementa o esquema de Horner, reduzindo a quantidade de multiplicações.

- **Métodos de Exponenciação:**
  - **Método Binário:**
    ```cpp
    static double powerBinary(double x, int n);
    ```
    Utiliza divisão sucessiva para otimizar o cálculo da potência.
  
  - **Método dos Multiplicadores:**
    ```cpp
    static double powerMultipliers(double x, int n);
    ```
    Realiza multiplicações repetidas (menos eficiente).
  
  - **Árvore de Potências:**
    ```cpp
    static double powerTree(double x, int n);
    ```
    Usa uma abordagem recursiva para reduzir operações desnecessárias.

## Código Completo
```cpp
#include <iostream>
#include <vector>
#include <cmath>

class Polynomial {
private:
    std::vector<double> coefficients;

public:
    Polynomial(const std::vector<double>& coeffs) : coefficients(coeffs) {}

    void print() const {
        for (size_t i = 0; i < coefficients.size(); ++i) {
            if (coefficients[i] != 0) {
                std::cout << coefficients[i] << "x^" << i;
                if (i != coefficients.size() - 1) std::cout << " + ";
            }
        }
        std::cout << std::endl;
    }

    double evaluate(double x) const {
        double result = 0;
        double power = 1;
        for (double coef : coefficients) {
            result += coef * power;
            power *= x;
        }
        return result;
    }

    double horner(double x) const {
        double result = 0;
        for (int i = coefficients.size() - 1; i >= 0; --i) {
            result = result * x + coefficients[i];
        }
        return result;
    }

    static double powerBinary(double x, int n) {
        double result = 1;
        while (n > 0) {
            if (n % 2 == 1) result *= x;
            x *= x;
            n /= 2;
        }
        return result;
    }

    static double powerMultipliers(double x, int n) {
        double result = 1;
        for (int i = 1; i <= n; ++i) {
            result *= x;
        }
        return result;
    }

    static double powerTree(double x, int n) {
        if (n == 0) return 1;
        if (n == 1) return x;
        double sqrtPower = powerTree(x, n / 2);
        return sqrtPower * sqrtPower * (n % 2 == 1 ? x : 1);
    }
};

int main() {
    Polynomial p({1, -3, 2}); // 1 - 3x + 2x^2
    std::cout << "Polynomial: ";
    p.print();

    double x = 3;
    std::cout << "Value at " << x << " using evaluation: " << p.evaluate(x) << std::endl;
    std::cout << "Value at " << x << " using Horner's method: " << p.horner(x) << std::endl;

    int exponent = 5;
    std::cout << x << "^" << exponent << " using binary method: " << Polynomial::powerBinary(x, exponent) << std::endl;
    std::cout << x << "^" << exponent << " using multipliers method: " << Polynomial::powerMultipliers(x, exponent) << std::endl;
    std::cout << x << "^" << exponent << " using power tree method: " << Polynomial::powerTree(x, exponent) << std::endl;

    return 0;
}
```

## Conclusão
Este projeto fornece uma implementação eficiente de aritmética polinomial em C++, permitindo cálculos rápidos e precisos com diferentes abordagens para avaliação e exponenciação.

