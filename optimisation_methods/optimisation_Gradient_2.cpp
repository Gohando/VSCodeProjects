#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

// Определение целевой функции
double objectiveFunction(const vector<double>& x) {
    double term1 = pow(x[0] * x[0] + x[1] - 11, 2);
    double term2 = pow(x[0] + x[1] * x[1] - 7, 2);
    return term1 + term2;
}

// Определение градиента целевой функции
vector<double> gradient(const vector<double>& x) {
    double df_dx1 = 2 * (x[0] * x[0] + x[1] - 11) * (2 * x[0]) + 2 * (x[0] + x[1] * x[1] - 7);
    double df_dx2 = 2 * (x[0] * x[0] + x[1] - 11) + 2 * (x[0] + x[1] * x[1] - 7) * (2 * x[1]);

    return {df_dx1, df_dx2};
}

// Метод градиентного спуска
vector<double> gradientDescent(const vector<double>& initialPoint, double learningRate, double epsilon, int maxIterations) {
    vector<double> currentPoint = initialPoint;

    for (int i = 0; i < maxIterations; ++i) {
        vector<double> grad = gradient(currentPoint);

        // Обновление текущей точки
        for (size_t j = 0; j < currentPoint.size(); ++j) {
            currentPoint[j] -= learningRate * grad[j];
        }

        // Проверка на критерий останова
        if (sqrt(grad[0] * grad[0] + grad[1] * grad[1]) < epsilon) {
            break;
        }
    }

    return currentPoint;
}

int main() {
    // Начальная точка
    vector<double> initialPoint = {0.0, 0.0}; // Замените значениями своей функции

    // Скорость обучения, критерий останова и максимальное количество итераций
    double learningRate = 0.01;
    double epsilon = 1e-6;
    int maxIterations = 1000;

    // Вызов метода градиентного спуска
    vector<double> result = gradientDescent(initialPoint, learningRate, epsilon, maxIterations);

    // Вывод результата
    cout << "Minimum point: ";
    for (const auto& value : result) {
        cout << value << " ";
    }
    cout << "\nMinimum value: " << objectiveFunction(result) << endl;

    return 0;
}
