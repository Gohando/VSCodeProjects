#define pi 3.1415926

#include <iostream>
#include <cmath>
using namespace std;

class Shape {
public:
    virtual void Print() const = 0;
    virtual void Read() = 0;
    virtual ~Shape() {}
protected:
    virtual double Get_square() const = 0;
    virtual double Get_perimeter() const = 0;
};

class Rhombus : public Shape {
public:
    void Read() override {
        cout << "Enter side length:\n";
        cin >> side_length;
        cout << "Enter one of the angels:\n";
        cin >> one_of_angles;
    }
    void Print() const override {
        cout << "Shape: Rhombus\n";
        cout << "Side length: " << side_length << "\n";
        cout << "One of angels: " << one_of_angles << "\n";
        cout << "Perimeter: " << Get_perimeter() << "\n";
        cout << "Square: " << Get_square() << "\n";
    }
private:
    double side_length;
    double one_of_angles;
    double Get_perimeter() const override {
        return side_length * 4;
    }
    double Get_square() const override {
        return side_length * side_length * sin(one_of_angles);
    }
};
class Parallelepiped : public Shape {
public:
    void Read() override {
        cout << "Enter side 1 length:\n";
        cin >> side_length_1;
        cout << "Enter side 2 length:\n";
        cin >> side_length_2;
        cout << "Enter height:\n";
        cin >> height;
    }
    void Print() const override {
        cout << "Shape: Parallelepiped\n";
        cout << "Side 1 length: " << side_length_1 << "\n";
        cout << "Side 2 length: " << side_length_2 << "\n";
        cout << "height: " << height << "\n";
        cout << "Perimeter: " << Get_perimeter() << "\n";
        cout << "Square: " << Get_square() << "\n";
    }
private:
    double side_length_1;
    double side_length_2;
    double height;
    double Get_perimeter() const override {
        return side_length_1 * 2 + side_length_2 * 2;
    }
    double Get_square() const override {
        return 2 * (side_length_1 * side_length_2 +
            side_length_1 * height + side_length_2 * height);
    }
};
class Elipse : public Shape {
public:
    void Read() override {
        cout << "Enter axis 1 length:\n";
        cin >> axis_1;
        cout << "Enter axis 2 length:\n";
        cin >> axis_2;
    }
    void Print() const override {
        cout << "Shape: Elipse\n";
        cout << "Axis 1 length: " << axis_1 << "\n";
        cout << "Axis 2 length: " << axis_2 << "\n";
        cout << "Perimeter: " << Get_perimeter() << "\n";
        cout << "Square: " << Get_square() << "\n";
    }
private:
    double axis_1;
    double axis_2;
    double Get_perimeter() const override {
        return 2 * pi * sqrt((axis_1 * axis_1 + axis_2 * axis_2) / 8);
    }
    double Get_square() const override {
        return pi * axis_1 * axis_2 / 4;
    }
};

int main() {
    int choice;
    Shape* shape_ptr;
    while (true) {
        cout << " Choose a shape:\n";
        cout << "1 - Rhombus\n";
        cout << "2 - Parallelepiped\n";
        cout << "3 - Elipse\n";
        cout << "To exit a program input any other integer\n";
        cin >> choice;
        switch (choice) {
            case 1:
            shape_ptr = new Rhombus;
                break;
            case 2:
            shape_ptr = new Parallelepiped;
                break;
            case 3:
            shape_ptr = new Elipse;
                break;
            default:
                cout << "Exiting...\n";
                exit(0);
        }
        shape_ptr->Read();
        shape_ptr->Print();
        delete shape_ptr;
    }
    
    return 0;
}