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

// Функция для вычисления новой точки
vector<double> explore(const vector<double>& x, const vector<double>& direction, double stepSize) {
    vector<double> newX = x;
    for (size_t i = 0; i < x.size(); ++i) {
        newX[i] += stepSize * direction[i];
    }
    return newX;
}

// Алгоритм Хука-Дживса
vector<double> hookeJeeves(const vector<double>& initialPoint, double stepSize, double epsilon) {
    vector<double> currentPoint = initialPoint;
    vector<double> basePoint = initialPoint;

    do {
        vector<double> trialPoint = explore(currentPoint, currentPoint, stepSize);

        if (objectiveFunction(trialPoint) < objectiveFunction(currentPoint)) {
            currentPoint = trialPoint;
        } else {
            stepSize /= 2.0;
        }

        if (objectiveFunction(currentPoint) < objectiveFunction(basePoint)) {
            basePoint = currentPoint;
        }
    } while (stepSize > epsilon);

    return basePoint;
}

int main() {
    // Начальная точка
    vector<double> initialPoint = {0.0, 0.0}; // Замените значениями своей функции

    // Размер шага и критерий останова
    double stepSize = 1.0;
    double epsilon = 1e-6;

    // Вызов метода Хука-Дживса
    vector<double> result = hookeJeeves(initialPoint, stepSize, epsilon);

    // Вывод результата
    cout << "Minimum point: ";
    for (const auto& value : result) {
        cout << value << " ";
    }
    cout << "\nMinimum value: " << objectiveFunction(result) << endl;

    return 0;
}
