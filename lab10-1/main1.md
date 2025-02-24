# Método de Fatoração de Fermat

## Descrição
O método de Fermat é um algoritmo de fatoração de números inteiros baseado na ideia de que qualquer número ímpar pode ser expresso como a diferença de dois quadrados:

\[ n = x^2 - y^2 = (x - y)(x + y) \]

O algoritmo busca encontrar valores adequados para \( x \) e \( y \) tal que a diferença de seus quadrados seja igual ao número a ser fatorado.

## Algoritmo
1. Se o número for par, ele pode ser fatorado diretamente como \( 2 \times (n/2) \).
2. Inicialize \( x \) como \( \lceil \sqrt{n} \rceil \).
3. Calcule \( y^2 = x^2 - n \).
4. Se \( y^2 \) for um quadrado perfeito, então os fatores são \( x - y \) e \( x + y \).
5. Caso contrário, incremente \( x \) e repita o processo até encontrar a solução.

## Implementação em C++

```cpp
#include <iostream>
#include <cmath>
using namespace std;

// Função para encontrar raiz quadrada inteira
long long isqrt(long long n) {
    return static_cast<long long>(sqrt(n));
}

// Método de Fermat para fatoração de números
void fermatFactorization(long long n) {
    if (n % 2 == 0) {
        cout << "Número par, fatores: " << 2 << " e " << n / 2 << endl;
        return;
    }
    
    long long x = isqrt(n) + 1;
    long long y2;
    long long y;
    
    while (true) {
        y2 = x * x - n;
        y = isqrt(y2);
        
        if (y * y == y2) {
            long long factor1 = x - y;
            long long factor2 = x + y;
            
            cout << "Fatoração: " << factor1 << " * " << factor2 << " = " << n << endl;
            return;
        }
        x++;
    }
}

int main() {
    long long n;
    cout << "Digite um número para fatoração: ";
    cin >> n;
    
    fermatFactorization(n);
    
    return 0;
}
```

## Complexidade
A complexidade do método de Fermat depende da diferença entre os fatores de \( n \). No pior caso, pode ser aproximadamente \( O(n^{1/4}) \), tornando-o mais eficiente do que a fatoração ingênua para alguns números específicos, mas não para todos.

## Aplicações
- Fatoração de números semi-primos.
- Aplicações em criptografia e teoria dos números.
- Base para métodos mais avançados de fatoração, como o método da elipse e o crivo quadrático.

