# Gerador de Números Aleatórios - Método de Fibonacci com Atraso e Método Blum-Blum-Shub

## Introdução
### Método de Fibonacci com Atraso
O **Método de Fibonacci com Atraso** ("Lagged Fibonacci Generator" - LFG) é um algoritmo para gerar números pseudoaleatórios baseado na seguinte fórmula recorrente:

\[
X_n = (X_{n - p} \; \text{op} \; X_{n - q}) \mod m
\]

Onde:
- \( p \) e \( q \) são **atrasos (lags)**, onde \( p > q \).
- **op** pode ser soma (+), subtração (-), multiplicação (*) ou XOR (^).
- \( m \) é o módulo (geralmente \( 2^{32} \) ou \( 2^{64} \)).

Este método é amplamente utilizado devido às suas **boas propriedades estatísticas** e ao longo período de repetição, sendo aplicado em **criptografia, simulação estatística e algoritmos de Monte Carlo**.

### Método Blum-Blum-Shub (BBS)
O **Blum-Blum-Shub (BBS)** é um gerador de números pseudoaleatórios baseado na dificuldade do problema da fatoração de grandes números. Ele é definido pela seguinte equação:

\[
X_{n+1} = (X_n^2) \mod M
\]

Onde:
- \( M = p \times q \) é o produto de dois grandes números primos \( p \) e \( q \), ambos congruentes a 3 mod 4.
- \( X_0 \) é a semente, escolhida como um número coprimo de \( M \).

Este método é altamente seguro e é utilizado em **criptografia**, sendo considerado um dos mais fortes geradores pseudoaleatórios disponíveis.

---

## Implementação em C++

### Gerador de Fibonacci com Atraso

```cpp
#include <iostream>
#include <vector>
#include <ctime>

class LaggedFibonacciGenerator {
private:
    std::vector<uint32_t> state;
    size_t p, q, index;
    const uint32_t MODULUS = 1U << 31; // 2^31
    
public:
    // Construtor com p e q definidos
    LaggedFibonacciGenerator(size_t p_lag, size_t q_lag, uint32_t seed) : p(p_lag), q(q_lag), index(0) {
        if (p <= q) {
            throw std::invalid_argument("p deve ser maior que q!");
        }

        state.resize(p);
        state[0] = seed;

        // Inicializa o estado com um LCG simples
        for (size_t i = 1; i < p; ++i) {
            state[i] = (state[i - 1] * 1664525 + 1013904223) % MODULUS;
        }
    }

    // Gera um novo número pseudoaleatório
    uint32_t next() {
        size_t pos_p = (index + p - q) % p;
        state[index] = (state[index] + state[pos_p]) % MODULUS;
        
        uint32_t result = state[index];
        index = (index + 1) % p;
        
        return result;
    }
};
```

### Gerador Blum-Blum-Shub

```cpp
#include <iostream>
#include <cmath>

class BlumBlumShub {
private:
    long long M, state;

public:
    BlumBlumShub(long long p, long long q, long long seed) {
        M = p * q;
        state = (seed * seed) % M;
    }

    int next() {
        state = (state * state) % M;
        return state & 1; // Retorna o último bit gerado
    }
};

int main() {
    long long p = 11, q = 19; // Exemplo de primos pequenos para teste
    long long seed = 3;
    BlumBlumShub bbs(p, q, seed);
    
    std::cout << "Gerando 10 bits pseudoaleatórios:\n";
    for (int i = 0; i < 10; ++i) {
        std::cout << bbs.next() << " ";
    }
    std::cout << std::endl;
    
    return 0;
}
```

---

## Comparação dos Métodos

| Método | Velocidade | Comprimento do Período | Lei de Distribuição |
|--------|-----------|----------------------|--------------------|
| **Fibonacci com Atraso** | Rápido, devido a operações aritméticas simples | Muito longo, depende dos valores de \( p \) e \( q \) | Aproximação de uma distribuição uniforme |
| **Blum-Blum-Shub** | Lento, pois envolve operações modulares de grandes números | Extremamente longo, dependendo da escolha de \( p \) e \( q \) | Distribuição uniforme de bits, adequado para criptografia |

---

## Conclusão
O **Gerador Fibonacci com Atraso** é um método confiável para simulação estatística, enquanto o **Blum-Blum-Shub** é uma opção segura para criptografia. Ambos desempenham papéis importantes em diferentes áreas de aplicação. 🚀

