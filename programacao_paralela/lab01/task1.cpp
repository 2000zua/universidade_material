#include <iostream>
#include <chrono>
#include <cstdlib>

using namespace std;
using namespace std::chrono;

// Функция для выделения памяти под матрицу
int** createMatrix(int N) {
    int** matrix = new int*[N];
    for (int i = 0; i < N; ++i) {
        matrix[i] = new int[N];
    }
    return matrix;
}

// Функция для заполнения матрицы случайными числами
void fillMatrix(int** matrix, int N) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            matrix[i][j] = rand() % 10;  // Числа от 0 до 9
        }
    }
}

// Функция для освобождения памяти
void deleteMatrix(int** matrix, int N) {
    for (int i = 0; i < N; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

// Функция умножения матриц
void multiplyMatrices(int** A, int** B, int** C, int N) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            C[i][j] = 0;
            for (int k = 0; k < N; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// Функция тестирования для -O0 (Debug)
double testMatrixMultiplication_O0(int N, int numRuns = 3) {
    double totalTime = 0.0;
    for (int run = 0; run < numRuns; ++run) {
        int** A = createMatrix(N);
        int** B = createMatrix(N);
        int** C = createMatrix(N);

        fillMatrix(A, N);
        fillMatrix(B, N);

        auto start = high_resolution_clock::now();
        multiplyMatrices(A, B, C, N);
        auto end = high_resolution_clock::now();

        duration<double> diff = end - start;
        totalTime += diff.count();

        deleteMatrix(A, N);
        deleteMatrix(B, N);
        deleteMatrix(C, N);
    }
    return totalTime / numRuns;
}

// Функция тестирования для -O2 (Release)
double testMatrixMultiplication_O2(int N, int numRuns = 3) {
    double totalTime = 0.0;
    for (int run = 0; run < numRuns; ++run) {
        int** A = createMatrix(N);
        int** B = createMatrix(N);
        int** C = createMatrix(N);

        fillMatrix(A, N);
        fillMatrix(B, N);

        auto start = high_resolution_clock::now();
        multiplyMatrices(A, B, C, N);
        auto end = high_resolution_clock::now();

        duration<double> diff = end - start;
        totalTime += diff.count();

        deleteMatrix(A, N);
        deleteMatrix(B, N);
        deleteMatrix(C, N);
    }
    return totalTime / numRuns;
}

int main() {
    srand(time(0)); // Инициализация генератора случайных чисел
    
    cout << "Размер матрицы | -O0 (Debug) | -O2 (Release)\n";
    cout << "-----------------------------------------\n";

    for (int N : {512, 1024, 2048}) {
        double avgTime_O0 = testMatrixMultiplication_O0(N);
        double avgTime_O2 = testMatrixMultiplication_O2(N);
        cout << N << " x " << N << " | " << avgTime_O0 << " s | " << avgTime_O2 << " s\n";
    }

    return 0;
}
