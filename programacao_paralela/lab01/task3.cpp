#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>

using namespace std;
using namespace std::chrono;

const int NUM_RUNS = 3;

// Функция для инициализации матриц случайными значениями
void initializeMatrix(vector<double>& matrix, int N) {
    for (int i = 0; i < N * N; ++i) {
        matrix[i] = rand() % 100;
    }
}

// Функции для разных порядков циклов
void multiply_ijk(const vector<double>& A, const vector<double>& B, vector<double>& C, int N) {
    fill(C.begin(), C.end(), 0);
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            for (int k = 0; k < N; ++k)
                C[i * N + j] += A[i * N + k] * B[k * N + j];
}

void multiply_ikj(const vector<double>& A, const vector<double>& B, vector<double>& C, int N) {
    fill(C.begin(), C.end(), 0);
    for (int i = 0; i < N; ++i)
        for (int k = 0; k < N; ++k)
            for (int j = 0; j < N; ++j)
                C[i * N + j] += A[i * N + k] * B[k * N + j];
}

void multiply_jik(const vector<double>& A, const vector<double>& B, vector<double>& C, int N) {
    fill(C.begin(), C.end(), 0);
    for (int j = 0; j < N; ++j)
        for (int i = 0; i < N; ++i)
            for (int k = 0; k < N; ++k)
                C[i * N + j] += A[i * N + k] * B[k * N + j];
}

void multiply_jki(const vector<double>& A, const vector<double>& B, vector<double>& C, int N) {
    fill(C.begin(), C.end(), 0);
    for (int j = 0; j < N; ++j)
        for (int k = 0; k < N; ++k)
            for (int i = 0; i < N; ++i)
                C[i * N + j] += A[i * N + k] * B[k * N + j];
}

void multiply_kij(const vector<double>& A, const vector<double>& B, vector<double>& C, int N) {
    fill(C.begin(), C.end(), 0);
    for (int k = 0; k < N; ++k)
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                C[i * N + j] += A[i * N + k] * B[k * N + j];
}

void multiply_kji(const vector<double>& A, const vector<double>& B, vector<double>& C, int N) {
    fill(C.begin(), C.end(), 0);
    for (int k = 0; k < N; ++k)
        for (int j = 0; j < N; ++j)
            for (int i = 0; i < N; ++i)
                C[i * N + j] += A[i * N + k] * B[k * N + j];
}

// Функция для измерения времени выполнения
void benchmark(void (*multiply)(const vector<double>&, const vector<double>&, vector<double>&, int),
               const vector<double>& A, const vector<double>& B, vector<double>& C, int N, const string& label) {
    double total_time = 0;
    for (int i = 0; i < NUM_RUNS; ++i) {
        auto start = high_resolution_clock::now();
        multiply(A, B, C, N);
        auto stop = high_resolution_clock::now();
        total_time += duration<double>(stop - start).count();
    }
    cout << label << " : " << (total_time / NUM_RUNS) << " секунд" << endl;
}

int main() {
    srand(time(nullptr));
    vector<int> sizes = {512, 1024, 2048};

    for (int N : sizes) {
        cout << "Размерность: " << N << endl;
        vector<double> A(N * N), B(N * N), C(N * N);
        initializeMatrix(A, N);
        initializeMatrix(B, N);

        benchmark(multiply_ijk, A, B, C, N, "ijk");
        benchmark(multiply_ikj, A, B, C, N, "ikj");
        benchmark(multiply_jik, A, B, C, N, "jik");
        benchmark(multiply_jki, A, B, C, N, "jki");
        benchmark(multiply_kij, A, B, C, N, "kij");
        benchmark(multiply_kji, A, B, C, N, "kji");

        cout << "----------------------------------" << endl;
    }

    return 0;
}
