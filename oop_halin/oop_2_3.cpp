/*Написать программу. Пользовательский класс должен содержать:
- необходимые поля;
- конструктор с параметрами (исходные значения по умолчанию) для
создания объектов (new) и установки их начального значения: 
LinearAlgorithm(...);
- деструктор ~ LinearAlgorithm(...);
- метод переустановки текущего состояния: void Set(...);
- метод печати значений исходных параметров и результата вычислений:
void Print(...);
- метод, решающий поставленную задачу: void Run () для вычисления
выражения, приведенного в лабораторной работе No 1;
Коды методов – вне пространства определения класса.
Создать проект для демонстрации работы: сформировать объекты со
значениями, изменить значения объектов. Вывести результаты.
*/
#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>
#include <string>

using namespace std;

class LinearAlgorithm {
public:
    LinearAlgorithm();
    LinearAlgorithm(double x, double y, double z, double t);
    ~LinearAlgorithm() {}  
    void Print();
    void Set(double x, double y, double z, double t);
    void Run();
private:
    double x;
    double y;
    double z;
    double t;
    double result = M_PI_4;
};

LinearAlgorithm::LinearAlgorithm() {
    this->x = 14.26;
    this->y = -1.22;
    this->z = 0.035;
    this->t = 0.564849;
}
LinearAlgorithm::LinearAlgorithm(double x, double y, double z, double t) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->t = t;
}
void LinearAlgorithm::Print() {
    if (result != M_PI_4) {
        string to_print = "x: " + to_string(x) + ", y: " +
            to_string(y) + ", z: " + to_string(z) + ", t: " +
            to_string(t) + "\nresult is: " + to_string(result);
        cout << to_print << endl;
    }
    else cout << "Run the algorithm first!\n";
}
void LinearAlgorithm::Set(double x, double y, double z, double t) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->t = t;
}
void LinearAlgorithm::Run() {
    result = (2 * cos(x - M_PI / 6) / (0.5 + sin(y) * sin(y))) *
        (1 + (z * z / (3 - z * z / 5)));
}

int main() {
    LinearAlgorithm *linear_algorithm_;
    linear_algorithm_ = new LinearAlgorithm;
    linear_algorithm_->Print();
    linear_algorithm_->Run();
    linear_algorithm_->Print();
    linear_algorithm_->Set(1, 1, 1, 1);
    linear_algorithm_->Run();
    linear_algorithm_->Print();
    delete linear_algorithm_;
    return 0;
}