#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>

// Função para verificar se um número é primo (Método de Divisões por Tentativa)
bool is_prime_trial_division(int n) {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    }
    return true;
}

// Teste de Wilson para verificar a primalidade
bool is_prime_wilson(int n) {
    if (n < 2) return false;
    long long factorial = 1;

    for (int i = 2; i < n; i++) {
        factorial = (factorial * i) % n;
    }

    return (factorial == n - 1);
}

// Função para gerar números aleatórios (primos e compostos)
std::vector<int> generateTestInputs(int count, int minVal, int maxVal) {
    std::vector<int> inputs;
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    for (int i = 0; i < count; i++) {
        int num = minVal + std::rand() % (maxVal - minVal + 1);
        inputs.push_back(num);
    }

    return inputs;
}

// Função para gerar números primos para testar os algoritmos
std::vector<int> generatePrimeTestInputs(int count, int minVal, int maxVal) {
    std::vector<int> primes;
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    while (primes.size() < count) {
        int num = minVal + std::rand() % (maxVal - minVal + 1);
        if (is_prime_trial_division(num)) {
            primes.push_back(num);
        }
    }

    return primes;
}

int main() {
    int count = 10;    // Quantidade de números de teste
    int minVal = 1;    // Valor mínimo
    int maxVal = 100;  // Valor máximo

    // Gerar números mistos (primos e compostos)
    std::vector<int> testInputs = generateTestInputs(count, minVal, maxVal);

    // Gerar apenas números primos
    std::vector<int> primeTestInputs = generatePrimeTestInputs(count, minVal, maxVal);

    std::cout << "Тестирование с случайными числами (простыми и составными):\n";
    for (int num : testInputs) {
        std::cout << "Число: " << num << "\n";
        std::cout << "Метод деления на пробу: " << (is_prime_trial_division(num) ? "Простое" : "Составное") << "\n";
        std::cout << "Тест Вильсона: " << (is_prime_wilson(num) ? "Простое" : "Составное") << "\n";
        std::cout << "------------------------\n";
    }
    

    std::cout << "\nТестирование только с простыми числами:\n";
    for (int num : primeTestInputs) {
        std::cout << "Число: " << num << "\n";
        std::cout << "Метод деления на пробу: " << (is_prime_trial_division(num) ? "Простое" : "Ошибка!") << "\n";
        std::cout << "Тест Вильсона: " << (is_prime_wilson(num) ? "Простое" : "Ошибка!") << "\n";
        std::cout << "------------------------\n";
    }

    return 0;
}
