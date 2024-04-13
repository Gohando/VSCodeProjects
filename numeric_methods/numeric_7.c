#include <stdio.h>
#include <math.h>

// Функция уравнения
double equation(double x) {
    return x - 1.2 * cos(x / 3.0);
}

// Производная уравнения
double equationDerivative(double x) {
    return 1.0 + (1.2 / 3.0) * sin(x / 3.0);
}

// Метод простой итерации для уравнения
double simpleIterationMethod(double initialGuess, double epsilon, int maxIterations) {
    double x = initialGuess;
    int iteration = 0;
    while (iteration < maxIterations) {
        double nextX = equation(x);
        if (fabs(nextX - x) < epsilon) {
            return nextX;
        }
        x = nextX;
        iteration++;
    }
    return NAN; // Если не достигли нужной точности за максимальное число итераций
}

// Метод простой итерации для системы линейных уравнений
void simpleIterationMethodForSystem(double matrix[4][5], double x[4], double epsilon, int maxIterations) {
    double temp[4];
    int iteration = 0;
    while (iteration < maxIterations) {
        for (int i = 0; i < 4; i++) {
            temp[i] = matrix[i][4];
            for (int j = 0; j < 4; j++) {
                if (j != i) {
                    temp[i] -= matrix[i][j] * x[j];
                }
            }
            temp[i] /= matrix[i][i];
        }
        int isConverged = 1;
        for (int i = 0; i < 4; i++) {
            if (fabs(temp[i] - x[i]) >= epsilon) {
                isConverged = 0;
                break;
            }
        }
        if (isConverged) {
            for (int i = 0; i < 4; i++) {
                x[i] = temp[i];
            }
            break;
        }
        for (int i = 0; i < 4; i++) {
            x[i] = temp[i];
        }
        iteration++;
    }
}

// Метод Зейделя для системы линейных уравнений
void gaussSeidelMethod(double matrix[4][5], double x[4], double epsilon, int maxIterations) {
    int iteration = 0;
    double temp[4];
    while (iteration < maxIterations) {
        for (int i = 0; i < 4; i++) {
            temp[i] = matrix[i][4];
            for (int j = 0; j < 4; j++) {
                if (j != i) {
                    temp[i] -= matrix[i][j] * x[j];
                }
            }
            temp[i] /= matrix[i][i];
            if (fabs(temp[i] - x[i]) >= epsilon) {
                x[i] = temp[i];
            }
        }
        int isConverged = 1;
        for (int i = 0; i < 4; i++) {
            if (fabs(temp[i] - x[i]) >= epsilon) {
                isConverged = 0;
                break;
            }
        }
        if (isConverged) {
            break;
        }
        iteration++;
    }
}

int main() {
    double initialGuess = 2.0; // Начальное предположение для метода простой итерации
    double epsilon = 0.0001; // Точность
    int maxIterations = 100; // Максимальное количество итераций

    // Решение уравнения методом простой итерации
    double solution = simpleIterationMethod(initialGuess, epsilon, maxIterations);
    if (!isnan(solution)) {
        printf("Решение уравнения: %.4f\n", solution);
    } else {
        printf("Не удалось найти решение уравнения\n");
    }

    // Система линейных уравнений
    double matrix[4][5] = {
        {2.979, 0.427, 0.406, 0.348, 0.341},
        {0.273, 3.951, 0.217, 0.327, 0.844},
        {0.318, 0.197, 2.875, 0.166, 0.131},
        {0.219, 0.231, 0.187, 3.276, 0.381}
    };
    double x[4] = {0.0, 0.0, 0.0, 0.0}; // Начальные предположения для методов итераций

    // Решение системы линейных уравнений методом простой итерации
    simpleIterationMethodForSystem(matrix, x, epsilon, maxIterations);
    printf("\nРешение системы линейных уравнений (метод простой итерации):\n");
    for (int i = 0; i < 4; i++) {
        printf("x%d = %.4f\n", i + 1, x[i]);
    }

    // Решение системы линейных уравнений методом Зейделя
    gaussSeidelMethod(matrix, x, epsilon, maxIterations);
    printf("\nРешение системы линейных уравнений (метод Зейделя):\n");
    for (int i = 0; i < 4; i++) {
        printf("x%d = %.4f\n", i + 1, x[i]);
    }

    return 0;
}
