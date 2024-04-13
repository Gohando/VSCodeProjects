#include <iostream>
#include <cmath>

using namespace std;


class CLinearAlgorithm {
        double x, y, z, result;
    public:
        void Set(double, double, double);
        void Run();
        void Print();
};

// Метод для установки начальных значений
void CLinearAlgorithm::Set(double a, double b, double c) 
{
    x = a;
    y = b;
    z = c;
}

// Метод для вывода переменных и результата на экран
void CLinearAlgorithm::Print()
{
    cout << "x = " << x << endl;
    cout << "y = " << y << endl;
    cout << "z = " << z << endl;
    cout << "result = " << result << endl;
}

// Метод для решения задачи
void CLinearAlgorithm::Run() { 
    double dop, a, b;
    
    cout << "Результат работы алгоритма:" << endl;
    dop = fabs(x - ((2 * y) / (1 + pow(x, 2) * pow(y, 2))));
    a = (1 + pow(sin(x + y), 2)) * pow(x, fabs(y));
    b = pow(cos(atan(1/z)), 2);
    result = (a / dop) + b;
}

int main()
{
    CLinearAlgorithm Result;
    Result.Set(374, -0.825, 16);
    Result.Run();
    Result.Print();
    return 0;
}