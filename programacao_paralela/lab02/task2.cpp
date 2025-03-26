#include <iostream>
#include <vector>
#include <numeric>
#include <execution>
#include <random>
#include <chrono>

// Функция для измерения времени выполнения std::reduce с заданной политикой
template <typename ExecutionPolicy>
double measure_execution_time(ExecutionPolicy policy, const std::vector<int>& data) {
    auto start = std::chrono::high_resolution_clock::now();

    // Используем std::reduce для суммирования элементов
    volatile long long sum = std::reduce(policy, data.begin(), data.end(), 0LL);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    return elapsed.count();
}

int main() {
    std::vector<size_t> sizes = {500000000, 1000000000, 2000000000};
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 100); // Генерация случайных чисел (1-100)

    for (size_t size : sizes) {
        std::vector<int> data(size);

        // Заполняем вектор случайными числами
        for (int& num : data) {
            num = dist(gen);
        }

        std::cout << "Размер вектора: " << size << std::endl;

        // Последовательное выполнение (seq)
        double avg_time_seq = 0;
        for (int i = 0; i < 3; ++i) {
            avg_time_seq += measure_execution_time(std::execution::seq, data);
        }
        avg_time_seq /= 3;
        std::cout << "seq: " << avg_time_seq << " с" << std::endl;

        // Параллельное выполнение (par)
        double avg_time_par = 0;
        for (int i = 0; i < 3; ++i) {
            avg_time_par += measure_execution_time(std::execution::par, data);
        }
        avg_time_par /= 3;
        std::cout << "par: " << avg_time_par << " с" << std::endl;

        // Параллельное выполнение с векторизацией (par_unseq)
        double avg_time_par_unseq = 0;
        for (int i = 0; i < 3; ++i) {
            avg_time_par_unseq += measure_execution_time(std::execution::par_unseq, data);
        }
        avg_time_par_unseq /= 3;
        std::cout << "par_unseq: " << avg_time_par_unseq << " с" << std::endl;

        std::cout << "-----------------------------" << std::endl;
    }

    return 0;
}
