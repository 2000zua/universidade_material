# Gerador de Números Aleatórios - Método de Fibonacci com Atraso

## Introdução
O **Método de Fibonacci com Atraso** (“Lagged Fibonacci Generator” - LFG) é um algoritmo para gerar números pseudoaleatórios baseado na seguinte fórmula recorrente:

\[
X_n = (X_{n - p} \; \text{op} \; X_{n - q}) \mod m
\]

Onde:
- \( p \) e \( q \) são **atrasos (lags)**, onde \( p > q \).
- **op** pode ser soma (+), subtração (-), multiplicação (*) ou XOR (\^).
- \( m \) é o módulo (geralmente \( 2^{32} \) ou \( 2^{64} \)).

Este método é amplamente utilizado devido às suas **boas propriedades estatísticas** e ao longo período de repetição, sendo aplicado em **criptografia, simulação estatística e algoritmos de Monte Carlo**.

---

## Implementação em C++
O código abaixo implementa um **Gerador de Fibonacci com Atraso** utilizando soma modular:

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

int main() {
    uint32_t seed = static_cast<uint32_t>(time(nullptr));
    LaggedFibonacciGenerator lfg(55, 24, seed);

    std::cout << "Gerando 10 números pseudoaleatórios:\n";
    for (int i = 0; i < 10; ++i) {
        std::cout << lfg.next() << " ";
    }
    std::cout << std::endl;
    
    return 0;
}
```

---

## Explicação do Código
1. **Inicialização**:
   - Criamos um vetor `state` de tamanho \( p \) para armazenar os valores anteriores.
   - Preenchemos `state` com uma sequência gerada por um **LCG** (Linear Congruential Generator).

2. **Geração de Números**:
   - Utilizamos a fórmula \( X_n = (X_{n-p} + X_{n-q}) \mod 2^{31} \).
   - Atualizamos o índice `index` ciclicamente, simulando um **buffer circular**.

3. **Execução**:
   - O programa inicializa o gerador com um seed baseado no tempo.
   - Gera e imprime **10 números pseudoaleatórios**.

---

## Vantagens do Método Fibonacci com Atraso
✅ **Melhores propriedades estatísticas** que o gerador congruencial linear (LCG).  
✅ **Grande período de repetição** (≈ \( 2^p \)), dificultando padrões.  
✅ **Bom desempenho em simulação e criptografia**.  

## Desvantagens
❌ **Mais lento que o LCG** devido ao uso de um buffer grande.  
❌ **Requer armazenamento de \( p \) valores anteriores**.  

---

## Aplicações
🔹 Geração de números aleatórios para **criptografia**.  
🔹 **Simulação estatística e física**, como Monte Carlo.  
🔹 Modelagem de processos aleatórios.  

---

## Conclusão
O **Gerador Fibonacci com Atraso** é um algoritmo confiável para gerar números pseudoaleatórios, sendo amplamente usado em aplicações que exigem um **alto grau de aleatoriedade e um grande período de geração**. 🚀

