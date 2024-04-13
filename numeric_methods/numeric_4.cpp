#include <stdio.h>
#include <math.h>

#define N 3 // размерность матрицы

void choleskyDecomposition(double A[N][N], double L[N][N])
{
    for (int i = 0; i < N; i++) {
        for (int j = 0; j <= i; j++) {
            double sum = 0;

            if (j == i) {
                for (int k = 0; k < j; k++) {
                    sum += pow(L[j][k], 2);
                }
                L[j][j] = sqrt(A[j][j] - sum);
            } else {
                for (int k = 0; k < j; k++) {
                    sum += L[i][k] * L[j][k];
                }
                L[i][j] = (A[i][j] - sum) / L[j][j];
            }
        }
    }
}

void choleskySolver(double L[N][N], double b[N], double x[N])
{
    double y[N];

    // Решение системы Ly = b методом прямого хода
    for (int i = 0; i < N; i++) {
        double sum = 0;
        for (int j = 0; j < i; j++) {
            sum += L[i][j] * y[j];
        }
        y[i] = (b[i] - sum) / L[i][i];
    }

    // Решение системы LTx = y методом обратного хода
    for (int i = N - 1; i >= 0; i--) {
        double sum = 0;
        for (int j = N - 1; j > i; j--) {
            sum += L[j][i] * x[j];
        }
        x[i] = (y[i] - sum) / L[i][i];
    }
}

int main()
{
    double A[N][N] = {
    {81, -45, 45}, 
    {-45, 50, -15},
    {45, -15, 38},
    }; 
    // симметричная положительно определенная матрица
    double b[N] = {531, -460, 193}; // вектор правой части

    double L[N][N] = {0}; // инициализация нижнетреугольной матрицы
    double x[N] = {0}; // вектор решения

    choleskyDecomposition(A, L); // разложение матрицы A на L
    choleskySolver(L, b, x); // решение системы методом Халецкого

    // Вывод решения
    for (int i = 0; i < N; i++) {
        printf("x%d = %.2lf\n", i+1, x[i]);
    }

    return 0;
}
