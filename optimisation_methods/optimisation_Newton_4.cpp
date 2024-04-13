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
    vector<double> grad(2);
    grad[0] = 4 * x[0] * (x[0] * x[0] + x[1] - 11) + 2 * (x[0] + x[1] * x[1] - 7);
    grad[1] = 2 * (x[0] * x[0] + x[1] - 11) + 4 * x[1] * (x[0] + x[1] * x[1] - 7);
    return grad;
}

// Определение матрицы Гессе целевой функции
vector<vector<double>> hessian(const vector<double>& x) {
    vector<vector<double>> hess(2, vector<double>(2));
    hess[0][0] = 12 * x[0] * x[0] + 4 * x[1] - 42;
    hess[0][1] = 4 * (x[0] + x[1]);
    hess[1][0] = 4 * (x[0] + x[1]);
    hess[1][1] = 2 * x[0] + 12 * x[1] * x[1] - 26;
    return hess;
}

// Метод Ньютона-Рафсона для оптимизации
vector<double> newtonRaphson(const vector<double>& initialPoint, double epsilon) {
    vector<double> currentPoint = initialPoint;

    do {
        // Решение системы линейных уравнений методом Гаусса
        vector<vector<double>> inverseHessian(2, vector<double>(2, 0.0));
        for (int i = 0; i < 2; ++i) {
            inverseHessian[i][i] = 1.0;
        }

        for (int i = 0; i < 2; ++i) {
            double pivot = hessian(currentPoint)[i][i];
            for (int j = 0; j < 2; ++j) {
                hessian(currentPoint)[i][j] /= pivot;
                inverseHessian[i][j] /= pivot;
            }

            for (int k = 0; k < 2; ++k) {
                if (k != i) {
                    double factor = hessian(currentPoint)[k][i];
                    for (int j = 0; j < 2; ++j) {
                        hessian(currentPoint)[k][j] -= factor * hessian(currentPoint)[i][j];
                        inverseHessian[k][j] -= factor * inverseHessian[i][j];
                    }
                }
            }
        }

        // Новое значение
        vector<double> delta = {0.0, 0.0};
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                delta[i] += inverseHessian[i][j] * gradient(currentPoint)[j];
            }
        }

        // Обновление точки
        currentPoint[0] -= delta[0];
        currentPoint[1] -= delta[1];
    } while (sqrt(gradient(currentPoint)[0] * gradient(currentPoint)[0] +
                  gradient(currentPoint)[1] * gradient(currentPoint)[1]) > epsilon);

    return currentPoint;
}

int main() {
    // Начальная точка
    vector<double> initialPoint = {0.0, 0.0};

    // Критерий останова
    double epsilon = 1e-6;

    // Вызов метода Ньютона-Рафсона
    vector<double> result = newtonRaphson(initialPoint, epsilon);

    // Вывод результата
    cout << "Minimum point: (" << result[0] << ", " << result[1] << ")" << endl;
    cout << "Minimum value: " << objectiveFunction(result) << endl;

    return 0;
}
