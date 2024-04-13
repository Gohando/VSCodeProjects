#include <stdio.h>
#include <math.h>

#define M_E 2.71828 // Manually defining Euler's number

double function1(double x) {
    return x * pow(M_E, x) / (1 + x) * (1 + x);
}

double function2(double x) {
    return x / (1 + x);
}

double function3(double x) {
    return 2 * x / (1 + x * x);
}

double rectangleMethod(double a, double b, double (*func)(double), int n) {
    double h = (b - a) / n;
    double integral = 0.0;

    for (int i = 0; i < n; ++i) {
        integral += func(a + i * h) * h;
    }

    return integral;
}

double trapezoidalMethod(double a, double b, double (*func)(double), int n) {
    double h = (b - a) / n;
    double integral = 0.0;

    integral += (func(a) + func(b)) / 2.0;
    for (int i = 1; i < n; ++i) {
        integral += func(a + i * h);
    }
    integral *= h;

    return integral;
}

double simpsonsMethod(double a, double b, double (*func)(double), int n) {
    if (n % 2 != 0) {
        printf("Error: Number of partitions should be even for Simpson's method.\n");
        return NAN;
    }
    double h = (b - a) / n;
    double integral = 0.0;

    integral += func(a) + func(b);
    for (int i = 1; i < n; ++i) {
        integral += (i % 2 == 0) ? 2 * func(a + i * h) : 4 * func(a + i * h);
    }
    integral *= h / 3.0;

    return integral;
}

int main() {
    double a = 0.0;
    double b = 1.0;
    int n = 100; // Number of partitions

    double resultRectangle1 = rectangleMethod(a, b, &function1, n);
    printf("Result Rectangle for function1: %.6f\n", resultRectangle1);

    double resultTrapezoidal2 = trapezoidalMethod(a, b, &function2, n);
    printf("Result Trapezoidal for function2: %.6f\n", resultTrapezoidal2);

    double resultSimpsons3 = simpsonsMethod(a, b, &function3, n);
    printf("Result Simpsons for function3: %.6f\n", resultSimpsons3);

    return 0;
}
