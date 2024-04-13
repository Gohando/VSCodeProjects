#include <stdio.h> //ввод-вывод
#include <math.h>  //функции синуса и косинуса

double given_function(double x) // исходная функция
{
    return (x - 1.2 * cos(x / 3));
}

double first_derivative(double x) // первая производная
{
    return (1 + 2 * sin(x / 3) / 5);
}

double second_derivative(double x) // вторая производная
{
    return (2 * cos(x / 3) / 15);
}

int main()
{
    // 1 - Метод хорд

    double eps = 0.0000001; // задаём точность
    double a = 1;           // левый конец отрезка
    double b = 1.2;         // правый конец отрезка
    double x0 = 0;          // точка пересечения хорды с ОХ

    do
    {
        // уравнение хорды
        x0 = a - given_function(a) * (b - a) /
                     (given_function(b) - given_function(a));

        // выбираем отрезок с разными знаками на коцах
        if (given_function(a) * given_function(x0) < 0)
            b = x0;

        // если мы точно попали в нуль функции
        else if (given_function(x0) == 0)
            break;

        else
            a = x0;

    } while (b - a > eps); // пока отрезок больше Эпсилон

    printf("Метод хорд. Ноль функции = %lf\n", x0);

    // 2 - Метод Ньютона

    // восстанавливаем изначальные значения концов отрезка
    a = 1;
    b = 1.2;
    double x00 = 0;
    double x01 = 0;

    // абсцисса пересечения ОХ и касательной
    x00 = (first_derivative(a) * a - given_function(a)) /
          first_derivative(a);

    // начальная точка из условия a < f'(x)*x-f(x))/df(x) < b
    x00 = ((x00 >= a) && (x00 <= b)) ? a : b;
    x01 = x00; // иначе в цикле потеряется первое значение x00
    do
    {
        // формула Ньютона
        x00 = x01;
        x01 = x00 - given_function(x00) / first_derivative(x01);
    } while (fabs(x00 - x01) > eps);

    printf("Метод Ньютона. Ноль функции = %lf\n", x01);

    // 3 - Комбинированный метод

    double x000 = 0;
    double x001 = 0;
    double x002 = 0;

    x000 = (second_derivative(a) * given_function(a) > 0) ? a : b;
    x001 = x000 - given_function(x000) / first_derivative(x000);
    x002 = a - given_function(a) * (b - a) /
                     (given_function(b) - given_function(a));

    do
    {
        a = x001;
        b = x002;
        x001 = a - given_function(a) / first_derivative(a);
        x002 = a - given_function(a) * (b - a) /
                     (given_function(b) - given_function(a));

    }
    while ((fabs(a - b) / 2) >= eps);

    printf("Комбинированный метод. ");
    printf("Ноль функции = %lf\n", (a + b) / 2);

    return 0;
}