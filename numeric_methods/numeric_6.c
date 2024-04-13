#include <stdio.h>
#include <stdlib.h>

// Структура, представляющая точку (x, y)
struct Point {
    double x, y;
};

// Функция для вычисления значения многочлена Ньютона в точке x
double interpolateNewton(struct Point* data, int n, double x) {
    double result = 0.0;
    double* coeffs = malloc(n * sizeof(double));

    // Построение коэффициентов многочлена Ньютона
    for (int i = 0; i < n; ++i) {
        coeffs[i] = data[i].y;
    }
    for (int i = 1; i < n; ++i) {
        for (int j = n - 1; j >= i; --j) {
            coeffs[j] = (coeffs[j] - coeffs[j - 1]) / (data[j].x - data[j - i].x);
        }
    }

    // Вычисление значения многочлена в точке x
    for (int i = n - 1; i >= 0; --i) {
        double term = coeffs[i];
        for (int j = i - 1; j >= 0; --j) {
            term *= (x - data[j].x);
        }
        result += term;
    }

    free(coeffs);
    return result;
}

int main() {
    // Пример данных (x, y)
    struct Point data[] = {{5.430, 21.779}, 
                           {5.816, 25.505}, 
                           {6.211, 29.577}, 
                           {6.620, 34.017},
                           {7.051, 38.852},
                           {7.509, 44.109},
                           {8.001, 49.822},
                           {8.535, 56.027},
                           {9.119, 62.768},
                           {9.762, 70.091},
                           {10.475, 78.052}};
    int n = sizeof(data) / sizeof(data[0]);

    // Значения x для левой и правой границ
    double leftX = 1.46;
    double rightX = 1.67;

    // Вычисление значений функции в точках левой и правой границ
    double leftY = interpolateNewton(data, n, leftX);
    double rightY = interpolateNewton(data, n, rightX);

    // Вывод результатов
    printf("Значение функции в точке %.2f: %.2f\n", leftX, leftY);
    printf("Значение функции в точке %.2f: %.2f\n", rightX, rightY);

    return 0;
}
