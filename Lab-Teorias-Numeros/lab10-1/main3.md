# Gerador de Número Primo Grande em C++

## Descrição
Este programa gera um número primo grande com uma quantidade específica de bits. Ele utiliza a abordagem clássica de geração de números primos, incluindo testes probabilísticos para garantir sua primalidade. Além disso, mede o tempo necessário para encontrar um número primo e conta a quantidade de iterações realizadas.

## Etapas do Algoritmo
1. **Geração de um Número Aleatório**
   - Um número aleatório é gerado com o número especificado de bits.
   - O bit mais significativo (MSB) e o bit menos significativo (LSB) são definidos como `1` para garantir o tamanho e a imparidade do número.

2. **Filtragem Inicial com Pequenos Primos**
   - O número gerado é verificado quanto à divisibilidade pelos primos menores que 256.
   - Se o número for divisível por qualquer um desses primos, ele é descartado e um novo número é gerado.

3. **Teste de Primalidade de Miller-Rabin**
   - Se o número passar pela filtragem inicial, ele é submetido ao teste de Miller-Rabin.
   - Este teste probabilístico verifica se o número é primo com alta confiança.

4. **Repetição até Encontrar um Primo**
   - Se o número falhar no teste de Miller-Rabin, outro número é gerado e o processo é repetido.
   - Caso contrário, o número é retornado como primo válido.

5. **Medição do Tempo e Contagem de Iterações**
   - O tempo decorrido para encontrar um número primo é registrado.
   - O número de iterações necessárias para gerar um número primo é contado.

## Estrutura do Código
```cpp
#include <iostream>
#include <random>
#include <vector>
#include <cmath>
#include <chrono>

using namespace std;
using namespace chrono;

const vector<int> SMALL_PRIMES = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47,
                                  53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107,
                                  109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167,
                                  173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229,
                                  233, 239, 241, 251};

long long mod_exp(long long base, long long exp, long long mod) {
    long long result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

bool is_prime(long long n, int k = 5) {
    if (n < 2) return false;
    for (int p : SMALL_PRIMES) {
        if (n == p) return true;
        if (n % p == 0) return false;
    }
    
    long long d = n - 1;
    int r = 0;
    while (d % 2 == 0) {
        d /= 2;
        r++;
    }

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<long long> dist(2, n - 2);

    for (int i = 0; i < k; i++) {
        long long a = dist(gen);
        long long x = mod_exp(a, d, n);
        if (x == 1 || x == n - 1) continue;
        bool composite = true;
        for (int j = 0; j < r - 1; j++) {
            x = mod_exp(x, 2, n);
            if (x == n - 1) {
                composite = false;
                break;
            }
        }
        if (composite) return false;
    }
    return true;
}

long long generate_random_number(int bit_length) {
    random_device rd;
    mt19937_64 gen(rd());
    uniform_int_distribution<long long> dist(0, (1LL << (bit_length - 2)) - 1);

    long long num = dist(gen);
    num |= (1LL << (bit_length - 1));
    num |= 1;
    return num;
}

long long generate_large_prime(int bit_length, int &iterations, double &time_taken) {
    iterations = 0;
    auto start = high_resolution_clock::now();
    
    while (true) {
        iterations++;
        long long candidate = generate_random_number(bit_length);
        bool divisible = false;
        for (int p : SMALL_PRIMES) {
            if (candidate % p == 0) {
                divisible = true;
                break;
            }
        }
        if (!divisible && is_prime(candidate)) {
            auto stop = high_resolution_clock::now();
            time_taken = duration<double>(stop - start).count();
            return candidate;
        }
    }
}

int main() {
    int bit_length;
    cout << "Digite o número de bits: ";
    cin >> bit_length;

    int iterations;
    double time_taken;
    long long prime = generate_large_prime(bit_length, iterations, time_taken);

    cout << "Número primo gerado: " << prime << endl;
    cout << "Iterações: " << iterations << endl;
    cout << "Tempo decorrido: " << time_taken << " segundos" << endl;

    return 0;
}
```

## Como Usar
1. Compile o código com um compilador C++:
   ```sh
   g++ -o prime_generator prime_generator.cpp
   ```
2. Execute o programa:
   ```sh
   ./prime_generator
   ```
3. Insira o número de bits desejado e obtenha um número primo correspondente, junto com as estatísticas de iterações e tempo decorrido.

## Exemplo de Saída
```
Digite o número de bits: 32
Número primo gerado: 2147483659
Iterações: 23
Tempo decorrido: 0.00123 segundos
```

## Requisitos
- Compilador C++ (GCC, Clang, MSVC, etc.).
- Suporte a C++11 ou superior.

## Observações
Este programa é útil para gerar números primos para criptografia, como em algoritmos RSA, onde primos grandes são necessários para segurança robusta.

