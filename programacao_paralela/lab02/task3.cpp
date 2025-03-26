#include <iostream>
#include <vector>
#include <thread>
#include <atomic>
#include <future>

using namespace std;

// Функция для вычисления скалярного произведения двух векторов
int dot_product(const vector<int>& a, const vector<int>& b) {
    int sum = 0;
    for (size_t i = 0; i < a.size(); ++i) {
        sum += a[i] * b[i];
    }
    return sum;
}

// Функция для умножения матриц в параллельном режиме
void multiply_matrices(const vector<vector<int>>& A, const vector<vector<int>>& B, vector<vector<int>>& C, int start_row, int end_row) {
    int n = A.size();
    for (int i = start_row; i < end_row; ++i) {
        for (int j = 0; j < n; ++j) {
            C[i][j] = dot_product(A[i], B[j]);
        }
    }
}

// Функция для многозадачного умножения матриц с использованием std::async
vector<vector<int>> parallel_matrix_multiplication(const vector<vector<int>>& A, const vector<vector<int>>& B, int num_threads) {
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n, 0));

    vector<future<void>> futures;
    int rows_per_thread = n / num_threads;
    
    for (int t = 0; t < num_threads; ++t) {
        int start_row = t * rows_per_thread;
        int end_row = (t == num_threads - 1) ? n : start_row + rows_per_thread;
        
        futures.push_back(async(launch::async, multiply_matrices, ref(A), ref(B), ref(C), start_row, end_row));
    }

    for (auto& f : futures) {
        f.get(); // Ожидание завершения всех потоков
    }

    return C;
}

int main() {
    // Пример матриц для умножения
    int sizes[] = {512, 1024, 2048}; // Размеры матриц для тестирования

    for (int size : sizes) {
        // Создание случайных матриц A и B
        vector<vector<int>> A(size, vector<int>(size, 1)); // Матрица A (заполнена единицами)
        vector<vector<int>> B(size, vector<int>(size, 1)); // Матрица B (заполнена единицами)

        // Запуск параллельного умножения матриц
        cout << "Testing matrix multiplication for size " << size << "x" << size << " with 4 threads..." << endl;

        auto start_time = chrono::high_resolution_clock::now();
        vector<vector<int>> C = parallel_matrix_multiplication(A, B, 4);
        auto end_time = chrono::high_resolution_clock::now();
        
        chrono::duration<double> duration = end_time - start_time;
        cout << "Time taken for multiplication: " << duration.count() << " seconds." << endl;
    }

    return 0;
}
