#include <iostream>
#include <cmath>

double f(double x, double y) {
    return std::fabs(x); // Функция y' = |x|
}

double rungeKutta(double x0, double y0, double h) {
    double x = x0;
    double y = y0;
    
    while (x < 1.0) { // Пока x меньше заданного значения
        double k1 = h * f(x, y);
        double k2 = h * f(x + h / 2, y + k1 / 2);
        double k3 = h * f(x + h / 2, y + k2 / 2);
        double k4 = h * f(x + h, y + k3);
        
        y += (k1 + 2 * k2 + 2 * k3 + k4) / 6;
        x += h;
    }
    
    return y; // Возвращаем значение y в конечной точке
}

int main() {
    double x0 = 0.0; // Начальное значение x
    double y0 = 0.0; // Начальное значение y
    double h = 0.1; // Начальный размер шага
    
    double y_old = rungeKutta(x0, y0, h); // Результат с начальным шагом
    
    while (true) {
        h /= 2; // Уменьшаем шаг интегрирования
        double y_new = rungeKutta(x0, y0, h); // Результат с новым шагом
        
        if (std::fabs(y_new - y_old) < 1e-6) { // Проверяем точность
            std::cout << "Шаг интегрирования: " << h << std::endl;
            break;
        }
        
        y_old = y_new; // Обновляем результат
    }
    
    return 0;
}
