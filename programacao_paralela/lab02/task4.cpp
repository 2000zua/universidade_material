#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <execution>
#include <thread>

using namespace std;

// Функция для генерации случайного массива
vector<double> generate_random_array(int size) {
    vector<double> array(size);
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0.0, 1000000.0);
    
    for (int i = 0; i < size; ++i) {
        array[i] = dis(gen);
    }
    
    return array;
}

// Функция для замера времени выполнения сортировки
template<typename SortFunc>
double measure_sort_time(SortFunc sort_func, vector<double>& arr) {
    auto start = chrono::high_resolution_clock::now();
    sort_func(arr.begin(), arr.end());
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    return duration.count();
}

// Функция для вывода результатов в табличном виде
void print_results(const vector<pair<string, double>>& results) {
    cout << "-----------------------------------\n";
    cout << "Execution Policy / Time (seconds)\n";
    cout << "-----------------------------------\n";
    for (const auto& result : results) {
        cout << result.first << " : " << result.second << " seconds\n";
    }
    cout << "-----------------------------------\n";
}

int main() {
    vector<int> sizes = {1000000, 5000000, 10000000, 20000000}; // Размеры массивов для тестирования
    vector<pair<string, double>> results;

    for (int size : sizes) {
        cout << "Testing for array size " << size << ":\n";
        vector<double> arr = generate_random_array(size);

        // Тестирование с различными политиками выполнения
        vector<double> arr_copy = arr; // Создаем копию массива для каждого теста

        // Сортировка с использованием параллельных потоков (std::execution::par)
        double time = measure_sort_time([](auto& arr) { sort(execution::par, arr.begin(), arr.end()); }, arr_copy);
        results.push_back({"std::execution::par", time});

        // Сортировка с использованием векторного параллельного исполнения (std::execution::par_unseq)
        arr_copy = arr;
        time = measure_sort_time([](auto& arr) { sort(execution::par_unseq, arr.begin(), arr.end()); }, arr_copy);
        results.push_back({"std::execution::par_unseq", time});

        // Сортировка без параллельных потоков (стандартный std::sort)
        arr_copy = arr;
        time = measure_sort_time([](auto& arr) { sort(arr.begin(), arr.end()); }, arr_copy);
        results.push_back({"std::sort", time});

        // Выводим результаты для текущего размера массива
        print_results(results);
        results.clear(); // Очищаем результаты для следующего размера массива
    }

    return 0;
}
