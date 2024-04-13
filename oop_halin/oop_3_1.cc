/*Необходимо разработать пользовательский класс Matrix, который
должен содержать конструктор с параметрами для создания массивов с
динамическим выделением памяти и установки начальных параметров (значений
элементов). При этом размеры массива должны передаваться в конструктор
через параметры. Помимо конструктора в классе должен быть деструктор,
метод просмотра результата, метод изменения состояния массива, а также
дружественная функция (функции) для решения требуемой задачи.

Коды методов и дружественной функции (функций) должны быть вне
пространства определения класса.
Дружественная функция (функции) должны решать задачу, представленную ниже.

(Общая часть). Требуется преобразовать квадратную матрицу
А размерности m по правилу, написанному в задании. Под преобразованием 
понимается замена всех элементов исходной матрицы. В задании определено
правило преобразования элемента матрицы, расположенного в i-й строке и j-м
столбце. Преобразовать требуется все элементы матрицы! Вспомогательными
массивами и рекурсиями не пользоваться. Разработанный алгоритм 
закодировать как дружественную функцию.

Главная сложность преобразования заключается в определении такого
порядка (очередности) обновления, при котором ранее измененные элементы
матрицы не учитывались бы при обновлении следующих элементов.
*/
#include <iostream>
#include <string>
#include <cmath>
using namespace std;

class My_vector;

class Matrix {
public:
    int** matrix;
    int size;
    Matrix(int size);
    ~Matrix();
    void Look();
    void Set();
    int X_sum(int i, int j);
    friend void Transform(Matrix &a);
    friend void Find_max(Matrix a, My_vector my_vector);
    void Set_10() {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                matrix[i][j] = 1;
            }
    }  
    }
};

Matrix::Matrix(int size) {
    this->size = size;
    matrix = new int* [size];
    for (int i = 0; i < size; i++) {
        matrix[i] = new int [size];
    }
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            matrix[i][j] = fabs(i - 2 * j);
        }
    }  
}
Matrix::~Matrix() {
    for (int i = 0; i < size; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}
void Matrix::Look() {
    cout << "Matrix:\n";
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << matrix[i][j] << "  ";
        }
        cout << "\n";
    }
}
void Matrix::Set() {
    cout << "Enter a matrix\n";
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cin >> matrix[i][j];
        }
    }   
}
int Matrix::X_sum(int i, int j) {
    int x_sum = matrix[i][j];
    int i1;
    int j1;
    for (i1 = i - 1, j1 = j - 1; i1 >= 0 && j1 >= 0; i1--, j1--) {
        x_sum += matrix[i1][j1];
    }
    for (i1 = i + 1, j1 = j - 1; i1 < size && j1 >= 0; i1++, j1--) {
        x_sum += matrix[i1][j1];
    }
    for (i1 = i + 1, j1 = j + 1; i1 < size && j1 < size; i1++, j1++) {
        x_sum += matrix[i1][j1];
    }
    return x_sum;    
}
void Transform(Matrix &a) {
    Matrix temp(a.size);
    for (int i = 0; i < a.size; i++) {
        for (int j = 0; j < a.size; j++) {
            temp.matrix[i][j] = a.matrix[i][j];
        }
    }
    for (int i = 0; i < a.size; i++) {
        for (int j = 0; j < a.size; j++) {
            a.matrix[i][j] = temp.X_sum(i, j);
        }
    }
}

class My_vector {
public:
    int* my_vector;
    int size = 0;
    My_vector(int size) {
        this->size = size;
        my_vector = new int[size];
    }
    My_vector() {
        size = 1;
        My_vector(size);
    }
    ~My_vector() {
        delete[] my_vector;
    }
    void Set() {
        cout << "Enter a vector\n";
        for (int i = 0; i < size; i++) {
            cin >> my_vector[i];
        }
    }
    void Look() {
        for (int i = 0; i < size; i++) {
            cout << my_vector[i];
        }
    }
    friend void Find_max(Matrix a, My_vector my_vector);
};

void Find_max(Matrix a, My_vector my_vector) {
    int max = a.matrix[0][0];
    for (int i = 0; i < a.size; i++) {
        for (int j = 0; j < a.size; j++) {
            if (a.matrix[i][j] > max) max = a.matrix[i][j];
        }
    }
    for (int i = 0; i < my_vector.size; i++) {
        if (my_vector.my_vector[i] > max) {
            max = my_vector.my_vector[i];
        }
    }
    cout << "Max is " << max << "\n";
}

int main() {
    Matrix a(10);
    a.Set_10();
    a.Look();
    Transform(a);
    a.Look();
    My_vector b_vec(3);
    b_vec.Set();
    Find_max(a, b_vec);
    return 0;
}