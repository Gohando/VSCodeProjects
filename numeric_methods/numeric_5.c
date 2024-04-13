#include <stdio.h>

// Функция для вычисления значения интерполяционного многочлена Лагранжа в точке x
float lagrangeInterpolation(float x, float xData[], float yData[], int dataSize) {
    float result = 0.0; // Инициализация результата

    for (int i = 0; i < dataSize; i++) {
        float term = yData[i]; // Начальное значение члена многочлена

        for (int j = 0; j < dataSize; j++) {
            if (j != i) {
                term *= (x - xData[j]) / (xData[i] - xData[j]);
            }
        }

        result += term; // Добавление члена многочлена к результату
    }

    return result; // Возвращаем вычисленное значение многочлена Лагранжа в точке x
}

int main() {
    float xData[] = {0.32, 0.73, 0.97, 1.13, 1.52,
        1.57, 2.02, 2.52, 2.96, 3.40, 3.79};
     // Значения x (узлы)
    float yData[] = {1.377, 2.075, 2.637, 3.095, 4.572,
        4.806, 7.538, 12.428, 19.297, 29.964, 44.256};
     // Значения функции в узлах

    int dataSize = sizeof(xData) / sizeof(xData[0]); // Размер массивов

    float x = 1.34; // Точка, для которой нужно вычислить значение функции

    // Вычисление значения интерполяционного многочлена Лагранжа в точке x
    float result = lagrangeInterpolation(x, xData, yData, dataSize);

    // Вывод результатов
    printf("Значение функции в точке %.2f: %.2f\n", x, result);

    return 0;
}
