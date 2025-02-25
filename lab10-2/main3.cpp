#include <iostream>

// Vamos supor que queremos verificar se o número 17 é primo.
// Inicializamos a sequência de Lucas-Lemmer: s = 4, t = 0.
// Calculamos s e t usando a fórmula: s = (s^2 - 2) mod n, t = (t^2 - 2) mod n.
// Repetimos o passo 2 até que s se torne igual a 0 ou t se torne igual a 0.
// Se s = 0, então o número n é primo. Se t = 0, então o número n é composto.

bool teste_lucas_lehmer(unsigned long long n) {
    unsigned long long s = 4, t = 0;
    for (int i = 0; i < n - 1; i++) {
        s = (s * s - 2) % n;
        t = (t * t - 2) % n;
        if (s == 0) return true;
        if (t == 0) return false;
    }
    return false;
}

// Função para gerar números aleatórios
unsigned long long gerarNumeroAleatorio(int min, int max) {
    return (unsigned long long) (min + (rand() % (max - min + 1)));
}

// Função para gerar números primos aleatórios
unsigned long long gerarNumeroPrimoAleatorio(int min, int max) {
    unsigned long long num;
    do {
        num = gerarNumeroAleatorio(min, max);
    } while (!teste_lucas_lehmer(num));
    return num;
}

// Função para gerar números compostos aleatórios
unsigned long long gerarNumeroCompostoAleatorio(int min, int max) {
    unsigned long long num;
    do {
        num = gerarNumeroAleatorio(min, max);
    } while (teste_lucas_lehmer(num));
    return num;
}



int main() {
    srand(time(0)); // Inicializa o gerador de números aleatórios

    int min = 1;
    int max = 1000;

     / Gera números aleatórios para o input
    unsigned long long numAleatorio = gerarNumeroAleatorio(min, max);
    unsigned long long numPrimoAleatorio = gerarNumeroPrimoAleatorio(min, max);
    unsigned long long numCompostoAleatorio = gerarNumeroCompostoAleatorio(min, max);

    std::cout << "Случайное число: " << numAleatorio << std::endl;
    std::cout << "Случайное простое число: " << numPrimoAleatorio << std::endl;
    std::cout << "Случайное составное число: " << numCompostoAleatorio << std::endl;


    // Testa o número aleatório com o Teste de Lucas-Lemmer
    if (teste_lucas_lehmer(numAleatorio)) {
        std::cout << "Число " << numAleatorio << " является простым." << std::endl;
    } else {
        std::cout << "Число " << numAleatorio << " является составным." << std::endl;
    }


    if (teste_lucas_lehmer(numPrimoAleatorio)) {
        std::cout << "Число " << numPrimoAleatorio << " является простым." << std::endl;
    } else {
        std::cout << "Число " << numPrimoAleatorio << " является составным." << std::endl;
    }

    if (teste_lucas_lehmer(numCompostoAleatorio)) {
        std::cout << "Число " << numCompostoAleatorio << " является простым." << std::endl;
    } else {
        std::cout << "Число " << numCompostoAleatorio << " является составным." << std::endl;
    }
    return 0;
}
