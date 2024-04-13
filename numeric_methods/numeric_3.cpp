#include <stdio.h>

#define N 4 // количество уравнений

void gaussMethod(double matrix[N][N+1]) {
    int i, j, k;
    double c;

    // Прямой ход метода Гаусса
    for (i = 0; i < N; i++) {
        for (j = i+1; j < N; j++) {
            c = matrix[j][i] / matrix[i][i];
            for (k = 0; k <= N; k++) {
                matrix[j][k] = matrix[j][k] - c * matrix[i][k];
            }
        }
    }

    // Обратный ход метода Гаусса
    for (i = N-1; i >= 0; i--) {
        for (j = i-1; j >= 0; j--) {
            c = matrix[j][i] / matrix[i][i];
            for (k = N; k >= i; k--) {
                matrix[j][k] = matrix[j][k] - c * matrix[i][k];
            }
        }
    }

    // Нормализация решений
    for (i = 0; i < N; i++) {
        c = matrix[i][i];
        for (j = 0; j <= N; j++) {
            matrix[i][j] = matrix[i][j] / c;
        }
    }
}

int main() {
    double matrix[N][N+1] = {
        {2.979, 0.427, 0.406, 0.348, 0.341},
        {0.273, 3.951, 0.217, 0.327, 0.844},
        {0.318, 0.197, 2.875, 0.166, 0.131},
        {0.219, 0.231, 0.187, 3.276, 0.381}
    };

    gaussMethod(matrix);

    // Вывод решения
    for (int i = 0; i < N; i++) {
        printf("x%d = %.2f\n", i+1, matrix[i][N]);
    }

    return 0;
}
