#include <iostream>
#include <vector>

// Função para realizar a divisão sintética
std::vector<int> divisaoSintetica(const std::vector<int>& polinomio, int a) {
    std::vector<int> resultado(polinomio.size());
    resultado[0] = polinomio[0];

    for (int i = 1; i < polinomio.size(); i++) {
        resultado[i] = polinomio[i] + a * resultado[i - 1];
    }

    return resultado;
}

// Função para realizar o teste de Wilson
// тест на основе критерия Вильсона.
bool testeDeWilson(int n) {
    if (n <= 1) {
        return false;
    }

    long long fatorial = 1;
    for (int i = 2; i < n; i++) {
        fatorial = (fatorial * i) % n;
    }

    return (fatorial + 1) % n == 0;
}

// Função para imprimir o polinômio
void imprimirPolinomio(const std::vector<int>& polinomio) {
    for (int i = 0; i < polinomio.size(); i++) {
        if (polinomio[i] != 0) {
            if (i > 0) {
                if (polinomio[i] > 0) {
                    std::cout << " + ";
                } else {
                    std::cout << " - ";
                }
            }

            if (abs(polinomio[i]) != 1 || i == 0) {
                std::cout << abs(polinomio[i]);
            }

            if (i > 0) {
                std::cout << "x";
                if (i > 1) {
                    std::cout << "^" << i;
                }
            }
        }
    }
}


int main() {
    // Exemplo de uso da divisão sintética
    std::vector<int> polinomio = {1, 2, -3, 1}; // x^3 + 2x^2 - 3x + 1
    int a = 2;
    std::vector<int> resultado = divisaoSintetica(polinomio, a);

    std::cout << "Divisão sintética de x^3 + 2x^2 - 3x + 1 por (x - 2):" << std::endl;
    // for (int i = 0; i < resultado.size(); i++) {
    //     std::cout << resultado[i] << " ";
    // }
    // std::cout << std::endl;
    imprimirPolinomio(resultado);


    // Exemplo de uso do teste de Wilson
    int n = 7;
    bool ehPrimo = testeDeWilson(n);

    std::cout << "O número " << n << " é primo? " << (ehPrimo ? "Sim" : "Não") << std::endl;

    return 0;
}
