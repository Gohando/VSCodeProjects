#include <stdio.h>
#include <math.h>

// Функция уравнения для метода наименьших квадратов
double equation(double x) {
    return x - 1.2 * cos(x / 3.0);
}

// Метод наименьших квадратов для вычисления значения функции в указанной точке
double leastSquaresMethod(double x[], double y[], int n, double point) {
    double sumX = 0.0, sumY = 0.0, sumXY = 0.0, sumXX = 0.0;

    for (int i = 0; i < n; i++) {
        sumX += x[i];
        sumY += y[i];
        sumXY += x[i] * y[i];
        sumXX += x[i] * x[i];
    }

    double a = (n * sumXY - sumX * sumY) / (n * sumXX - sumX * sumX);
    double b = (sumY - a * sumX) / n;

    return a * point + b;
}

// Функция для метода наименьших квадратов для линейной функции
void linearRegression(double x[], double y[], int n, double *a, double *b) {
    double sumX = 0.0, sumY = 0.0, sumXY = 0.0, sumXX = 0.0;

    for (int i = 0; i < n; i++) {
        sumX += x[i];
        sumY += y[i];
        sumXY += x[i] * y[i];
        sumXX += x[i] * x[i];
    }

    *a = (n * sumXY - sumX * sumY) / (n * sumXX - sumX * sumX);
    *b = (sumY - (*a) * sumX) / n;
}

// Функция для метода наименьших квадратов для степенной функции
void powerRegression(double x[], double y[], int n, double *a, double *b) {
    double sumLogX = 0.0, sumLogY = 0.0, sumLogXY = 0.0, sumLogXX = 0.0;

    for (int i = 0; i < n; i++) {
        sumLogX += log(x[i]);
        sumLogY += log(y[i]);
        sumLogXY += log(x[i]) * log(y[i]);
        sumLogXX += log(x[i]) * log(x[i]);
    }

    *b = (n * sumLogXY - sumLogX * sumLogY) / (n * sumLogXX - sumLogX * sumLogX);
    *a = exp((sumLogY - (*b) * sumLogX) / n);
}

// Функция для метода наименьших квадратов для показательной функции
void exponentialRegression(double x[], double y[], int n, double *a, double *b) {
    double sumX = 0.0, sumLogY = 0.0, sumXLogY = 0.0, sumXX = 0.0;

    for (int i = 0; i < n; i++) {
        sumX += x[i];
        sumLogY += log(y[i]);
        sumXLogY += x[i] * log(y[i]);
        sumXX += x[i] * x[i];
    }

    *b = (n * sumXLogY - sumX * sumLogY) / (n * sumXX - sumX * sumX);
    *a = exp((sumLogY - (*b) * sumX) / n);
}

int main() {
    double x[] = {60.1, 59.2, 58.6, 55.4, 53.1, 52.0, 49.9}; // Значения x
    double y[] = {49.0, 52.1, 53.2, 56.6, 59.5, 66.6, 67.8}; // Значения y
    int n = sizeof(x) / sizeof(x[0]); // Количество точек

    double point = 0.0; // Точка для вычисления функции

    // Вычисление значения функции в указанной точке методом наименьших квадратов
    double result = leastSquaresMethod(x, y, n, point);
    printf("Значение функции в точке %.2f: %.2f\n", point, result);

    double a, b;

    // Расчет параметров линейной функции
    linearRegression(x, y, n, &a, &b);
    printf("Линейная функция: y = %.4fx + %.4f\n", a, b);

    // Расчет параметров степенной функции
    powerRegression(x, y, n, &a, &b);
    printf("Степенная функция: y = %.4fx^%.4f\n", a, b);

    // Расчет параметров показательной функции
    exponentialRegression(x, y, n, &a, &b);
    printf("Показательная функция: y = %.4fe^(%.4fx)\n", a, b);

    return 0;
}
