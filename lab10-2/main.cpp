#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

// Função para gerar uma lista de valores aleatórios
std::vector<int> gerarListaAleatoria(int tamanho) {
    std::vector<int> lista;
    for (int i = 0; i <= tamanho; i++) {
        lista.push_back(rand() % 1000 + 1); // Gera números aleatórios entre 1 e 1000
    }
    return lista;
}

std::vector<int> gerarListaSequencial(int tamanho, int inicio) {
    std::vector<int> lista;
    for (int i = 0; i <= tamanho; i++) {
        lista.push_back(inicio + i);
    }
    return lista;
}


// Função para imprimir a lista
void imprimirLista(const std::vector<int>& lista) {
    for (int i = 0; i < lista.size(); i++) {
        std::cout << lista[i] << " ";
    }
    std::cout << std::endl;
}

// Função para encontrar os números primos utilizando o algoritmo de Eratóstenes
std::vector<int> encontrarPrimos(const std::vector<int>& lista) {
    int maximo = *std::max_element(lista.begin(), lista.end());
    std::vector<bool> sieve(maximo + 1, true);
    sieve[0] = sieve[1] = false; // 0 e 1 não são primos

    for (int i = 2; i * i <= maximo; i++) {
        if (sieve[i]) {
            for (int j = i * i; j <= maximo; j += i) {
                sieve[j] = false;
            }
        }
    }

    std::vector<int> primos;
    for (int i = 0; i < lista.size(); i++) {
        if (sieve[lista[i]]) {
            primos.push_back(lista[i]);
        }
    }
    return primos;
}

int main() {
    // Inicializa o gerador de números aleatórios
    srand(time(0)); 

    int tamanho;
    std::cout << "Введите размер списка: ";
    std::cin >> tamanho;

    std::vector<int> lista = gerarListaAleatoria(tamanho);
    //std::vector<int> lista = gerarListaSequencial(tamanho, 0);
    std::cout << "Сгенерированный список: ";
    imprimirLista(lista);

    std::vector<int> primos = encontrarPrimos(lista);
    std::cout << "Простые числа: ";
    imprimirLista(primos);

    return 0;
}
