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

// Вычисление градиента целевой функции
vector<double> gradient(const vector<double>& x) {
    double df_dx1 = 2 * (x[0] * x[0] + x[1] - 11) * (2 * x[0]) + 2 * (x[0] + x[1] * x[1] - 7);
    double df_dx2 = 2 * (x[0] * x[0] + x[1] - 11) + 2 * (x[0] + x[1] * x[1] - 7) * (2 * x[1]);

    return {df_dx1, df_dx2};
}

// Метод наискорейшего спуска
vector<double> steepestDescent(const vector<double>& initialPoint, double alpha, double epsilon) {
    vector<double> currentPoint = initialPoint;

    do {
        vector<double> grad = gradient(currentPoint);

        // Вычисление новой точки
        vector<double> newPoint = {currentPoint[0] - alpha * grad[0], currentPoint[1] - alpha * grad[1]};

        // Проверка условия останова
        double norm = sqrt(pow(grad[0], 2) + pow(grad[1], 2));
        if (norm < epsilon) {
            break;
        }

        currentPoint = newPoint;
    } while (true);

    return currentPoint;
}

int main() {
    // Начальная точка
    vector<double> initialPoint = {0.0, 0.0}; // Замените значениями своей функции

    // Параметры метода
    double alpha = 0.01; // Размер шага
    double epsilon = 1e-6; // Критерий останова

    // Вызов метода наискорейшего спуска
    vector<double> result = steepestDescent(initialPoint, alpha, epsilon);

    // Вывод результата
    cout << "Minimum point: ";
    for (const auto& value : result) {
        cout << value << " ";
    }
    cout << "\nMinimum value: " << objectiveFunction(result) << endl;

    return 0;
}
