#include <iostream>
#include <vector>
#include <ctime>
#include <cstdint>

const uint32_t MODULUS = (1U << 31) - 1; // 31-е простое число Мерсенна
const uint32_t MULTIPLIER = 16807; // 7^5 (k = 5, 7 - первообразный корень)
const uint32_t INCREMENT = 0; // b = 0

class LCG {
private:
    uint32_t state;
public:
    LCG(uint32_t seed) : state(seed % MODULUS) {}

    uint32_t next() {
        state = (uint64_t(state) * MULTIPLIER) % MODULUS;
        return state;
    }
};

int main() {
    uint32_t seed = static_cast<uint32_t>(time(nullptr)); // Инициализация зерна
    LCG rng(seed);

    std::cout << "Генерируем 10 случайных чисел:" << std::endl;
    for (int i = 0; i < 10; ++i) {
        std::cout << rng.next() << " ";
    }
    std::cout << std::endl;

    return 0;
}
