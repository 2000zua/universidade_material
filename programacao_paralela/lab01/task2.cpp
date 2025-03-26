#include <iostream>
#include <chrono>
#include <cstdlib>

using namespace std;
using namespace std::chrono;

// Функция для создания матрицы (динамический массив)
int* createMatrix(int N) {
    return new int[N * N];
}

// Функция для заполнения матрицы случайными значениями
void fillMatrix(int* matrix, int N) {
    for (int i = 0; i < N * N; i++) {
        matrix[i] = rand() % 100;
    }
}

// Классическая функция умножения матриц
void multiplyMatrices(int* A, int* B, int* C, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int sum = 0;
            for (int k = 0; k < N; k++) {
                sum += A[i * N + k] * B[k * N + j];
            }
            C[i * N + j] = sum;
        }
    }
}

// Функция для умножения матриц по алгоритму Страссена
void strassenMultiply(int* A, int* B, int* C, int N) {
    if (N == 1) {
        C[0] = A[0] * B[0];
        return;
    }

    int newN = N / 2;
    
    // Разделяем матрицы A и B на 4 подматрицы
    int* A11 = createMatrix(newN);
    int* A12 = createMatrix(newN);
    int* A21 = createMatrix(newN);
    int* A22 = createMatrix(newN);
    int* B11 = createMatrix(newN);
    int* B12 = createMatrix(newN);
    int* B21 = createMatrix(newN);
    int* B22 = createMatrix(newN);
    
    // Заполняем подматрицы A и B
    for (int i = 0; i < newN; i++) {
        for (int j = 0; j < newN; j++) {
            A11[i * newN + j] = A[i * N + j];
            A12[i * newN + j] = A[i * N + j + newN];
            A21[i * newN + j] = A[(i + newN) * N + j];
            A22[i * newN + j] = A[(i + newN) * N + j + newN];
            B11[i * newN + j] = B[i * N + j];
            B12[i * newN + j] = B[i * N + j + newN];
            B21[i * newN + j] = B[(i + newN) * N + j];
            B22[i * newN + j] = B[(i + newN) * N + j + newN];
        }
    }

    // Рекурсивно вычисляем 7 произведений
    int* M1 = createMatrix(newN);
    int* M2 = createMatrix(newN);
    int* M3 = createMatrix(newN);
    int* M4 = createMatrix(newN);
    int* M5 = createMatrix(newN);
    int* M6 = createMatrix(newN);
    int* M7 = createMatrix(newN);

    // М1 = (A11 + A22) * (B11 + B22)
    int* A11_plus_A22 = createMatrix(newN);
    int* B11_plus_B22 = createMatrix(newN);
    for (int i = 0; i < newN; i++) {
        for (int j = 0; j < newN; j++) {
            A11_plus_A22[i * newN + j] = A11[i * newN + j] + A22[i * newN + j];
            B11_plus_B22[i * newN + j] = B11[i * newN + j] + B22[i * newN + j];
        }
    }
    strassenMultiply(A11_plus_A22, B11_plus_B22, M1, newN);

    // М2 = (A21 + A22) * B11
    int* A21_plus_A22 = createMatrix(newN);
    for (int i = 0; i < newN; i++) {
        for (int j = 0; j < newN; j++) {
            A21_plus_A22[i * newN + j] = A21[i * newN + j] + A22[i * newN + j];
        }
    }
    strassenMultiply(A21_plus_A22, B11, M2, newN);

    // М3 = A11 * (B12 - B22)
    int* B12_minus_B22 = createMatrix(newN);
    for (int i = 0; i < newN; i++) {
        for (int j = 0; j < newN; j++) {
            B12_minus_B22[i * newN + j] = B12[i * newN + j] - B22[i * newN + j];
        }
    }
    strassenMultiply(A11, B12_minus_B22, M3, newN);

    // М4 = A22 * (B21 - B11)
    int* B21_minus_B11 = createMatrix(newN);
    for (int i = 0; i < newN; i++) {
        for (int j = 0; j < newN; j++) {
            B21_minus_B11[i * newN + j] = B21[i * newN + j] - B11[i * newN + j];
        }
    }
    strassenMultiply(A22, B21_minus_B11, M4, newN);

    // М5 = (A11 + A12) * B22
    int* A11_plus_A12 = createMatrix(newN);
    for (int i = 0; i < newN; i++) {
        for (int j = 0; j < newN; j++) {
            A11_plus_A12[i * newN + j] = A11[i * newN + j] + A12[i * newN + j];
        }
    }
    strassenMultiply(A11_plus_A12, B22, M5, newN);

    // М6 = (A21 - A11) * (B11 + B12)
    int* A21_minus_A11 = createMatrix(newN);
    int* B11_plus_B12 = createMatrix(newN);
    for (int i = 0; i < newN; i++) {
        for (int j = 0; j < newN; j++) {
            A21_minus_A11[i * newN + j] = A21[i * newN + j] - A11[i * newN + j];
            B11_plus_B12[i * newN + j] = B11[i * newN + j] + B12[i * newN + j];
        }
    }
    strassenMultiply(A21_minus_A11, B11_plus_B12, M6, newN);

    // М7 = (A12 - A22) * (B21 + B22)
    int* A12_minus_A22 = createMatrix(newN);
    int* B21_plus_B22 = createMatrix(newN);
    for (int i = 0; i < newN; i++) {
        for (int j = 0; j < newN; j++) {
            A12_minus_A22[i * newN + j] = A12[i * newN + j] - A22[i * newN + j];
            B21_plus_B22[i * newN + j] = B21[i * newN + j] + B22[i * newN + j];
        }
    }
    strassenMultiply(A12_minus_A22, B21_plus_B22, M7, newN);

    // Собираем результаты из подматриц
    for (int i = 0; i < newN; i++) {
        for (int j = 0; j < newN; j++) {
            C[i * N + j] = M1[i * newN + j] + M4[i * newN + j] - M5[i * newN + j] + M7[i * newN + j];
            C[i * N + j + newN] = M3[i * newN + j] + M5[i * newN + j];
            C[(i + newN) * N + j] = M2[i * newN + j] + M4[i * newN + j];
            C[(i + newN) * N + j + newN] = M1[i * newN + j] - M2[i * newN + j] + M3[i * newN + j] + M6[i * newN + j];
        }
    }

    // Освобождаем память
    delete[] A11; delete[] A12; delete[] A21; delete[] A22;
    delete[] B11; delete[] B12; delete[] B21; delete[] B22;
    delete[] M1; delete[] M2; delete[] M3; delete[] M4;
    delete[] M5; delete[] M6; delete[] M7;
}

// Функция для замера времени умножения матриц
double benchmark(int N) {
    int* A = createMatrix(N);
    int* B = createMatrix(N);
    int* C = createMatrix(N);

    fillMatrix(A, N);
    fillMatrix(B, N);

    auto start = high_resolution_clock::now();
    strassenMultiply(A, B, C, N);
    auto end = high_resolution_clock::now();

    double duration = duration_cast<std::chrono::duration<double>>(end - start).count();

    delete[] A;
    delete[] B;
    delete[] C;

    return duration;
}

int main() {
    srand(time(0));

    int sizes[] = {512, 1024, 2048};  // Размеры матриц
    int numRuns = 3;  // Количество запусков

    for (int N : sizes) {
        double totalTime = 0.0;
        cout << "Размер матрицы: " << N << " x " << N << endl;

        for (int i = 0; i < numRuns; i++) {
            double timeTaken = benchmark(N);
            totalTime += timeTaken;
            cout << "Запуск " << i + 1 << ": " << timeTaken << " с" << endl;
        }

        cout << "Среднее время: " << (totalTime / numRuns) << " с" << endl;
        cout << "------------------------------------" << endl;
    }

    return 0;
}
