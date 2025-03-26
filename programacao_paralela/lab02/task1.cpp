#include <iostream>
#include <vector>
#include <execution>
#include <random>
#include <chrono>

// Функция для подсчета количества делителей числа
int count_divisors(int n) {
    int count = 0;
    for (int i = 1; i * i <= n; ++i) {
        if (n % i == 0) {
            count += (i * i == n) ? 1 : 2; // Если i * i == n, учитываем один делитель, иначе два
        }
    }
    return count;
}

// Функция для измерения времени выполнения
template <typename ExecutionPolicy>
double measure_execution_time(ExecutionPolicy policy, std::vector<int>& data, std::vector<int>& results) {
    auto start = std::chrono::high_resolution_clock::now();
    
    // Безопасное выполнение в параллельном режиме, используя индексы напрямую
    std::transform(policy, data.begin(), data.end(), results.begin(), count_divisors);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    return elapsed.count();
}

int main() {
    std::vector<int> sizes = {500000, 1000000, 2000000}; // Размеры векторов
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(100000, 1000000); // Генерация случайных чисел

    for (int size : sizes) {
        std::vector<int> data(size);
        std::vector<int> results(size);

        // Заполнение вектора случайными числами
        for (int& num : data) {
            num = dist(gen);
        }

        std::cout << "Размер вектора: " << size << std::endl;

        // Последовательное выполнение (seq)
        double avg_time_seq = 0;
        for (int i = 0; i < 3; ++i) {
            avg_time_seq += measure_execution_time(std::execution::seq, data, results);
        }
        avg_time_seq /= 3;
        std::cout << "seq: " << avg_time_seq << " с" << std::endl;

        // Параллельное выполнение (par)
        double avg_time_par = 0;
        for (int i = 0; i < 3; ++i) {
            avg_time_par += measure_execution_time(std::execution::par, data, results);
        }
        avg_time_par /= 3;
        std::cout << "par: " << avg_time_par << " с" << std::endl;

        // Параллельное выполнение с векторизацией (par_unseq)
        double avg_time_par_unseq = 0;
        for (int i = 0; i < 3; ++i) {
            avg_time_par_unseq += measure_execution_time(std::execution::par_unseq, data, results);
        }
        avg_time_par_unseq /= 3;
        std::cout << "par_unseq: " << avg_time_par_unseq << " с" << std::endl;

        std::cout << "-----------------------------" << std::endl;
    }

    return 0;
}
