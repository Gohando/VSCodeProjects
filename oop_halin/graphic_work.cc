#include <windows.h>
#include <conio.h>
#include <algorithm>
#include <iostream>

using std::cout;

const int WIDTH = 130;
const int HEIGHT = 30;
char pixels[30][130]; // [строк][столбцов]
const int max_shapes = 500;

// Функция определения знака числа
int sign(int val) {
    return (val > 0) ? 1 : ((val < 0) ? -1 : 0);
}

class Shape {
public:
    virtual void draw() = 0;
    virtual ~Shape() {}
};

class Line : public Shape {
private:
    int x1, y1, x2, y2;
public:
    Line(int _x1, int _y1, int _x2, int _y2) : x1(_x1), y1(_y1), x2(_x2), y2(_y2) {}
    // Функция рисования линии по алгоритму Брезенхема
    void draw() override {
        int draw_x1 = x1;
        int draw_y1 = y1;
        // Обработка рисования единственной точки
        if (x1 == x2 && y1 == y2) {
            pixels[y1][x1] = '*';
            return; 
        }
        int dx = abs(x2 - x1);
        int dy = abs(y2 - y1);
        // Определяем направление
        int sx = sign(x2 - x1);
        int sy = sign(y2 - y1);

        bool swap = false;
        if (dy > dx) {
            swap = true;
            std::swap(dx, dy);
        }
        int err = 2 * dy - dx;

        for (int i = 0; i <= dx; i++) {
            // Вводим точку
            pixels[draw_y1][draw_x1] = '*';

            while (err >= 0) {
                if (swap)
                    draw_x1 += sx;
                else
                    draw_y1 += sy;

                err -= 2 * dx;
            }
            if (swap)
                draw_y1 += sy;
            else
                draw_x1 += sx;

            err += 2 * dy;
        }
    }
};

class Rect : public Shape {
private:
    int x1, y1, x2, y2;
    Line* lines[4];
public:
    Rect(int _x1, int _y1, int _x2, int _y2) : x1(_x1), y1(_y1), x2(_x2), y2(_y2) {
        lines[0] = new Line(x1, y1, x1, y2);
        lines[1] = new Line(x1, y1, x2, y1);
        lines[2] = new Line(x2, y2, x1, y2);
        lines[3] = new Line(x2, y2, x2, y1);
    }
    void draw() override {
        for (int i = 0; i < 4; i++) {
            lines[i]->draw();
        }
    }
    ~Rect() {
        for (int i = 0; i < 4; i++) {
            delete lines[i];
        }
    }
};

class Field : public Shape {
private:
    int x1, y1, x2, y2;
    int field_height;
    Line* lines[30];
public:
    Field(int _x1, int _y1, int _x2, int _y2) : x1(_x1), y1(_y1), x2(_x2), y2(_y2) {
        field_height = abs(y1 - y2);
        if (field_height) {
            for(int i = 0; i <= field_height; i++) {
                if (y1 < y2) lines[i] = new Line(_x1, _y1 + i, _x2, _y1 + i);
                if (y1 > y2) lines[i] = new Line(_x1, _y1 - i, _x2, _y1 - i);
            }
        }
        else lines[0] = new Line(x1, y1, x2, y2);
    }
    void draw() override {
        if (field_height) {
            for (int i = 0; i <= field_height; i++) {
                lines[i]->draw();
            }
        }
        else lines[0]->draw();
    }
    ~Field() {
        for(int i = 0; i <= field_height; i++) {
            delete lines[i];
        }
    }
};

class Emtpyness : public Shape {
private:
    int x1, y1, x2, y2;
public:
    Emtpyness(int _x1, int _y1, int _x2, int _y2) : x1(_x1), y1(_y1), x2(_x2), y2(_y2) {
        if (x1 > x2) {
            std::swap(x1, x2);
        }
        if (y1 > y2) {
            std::swap(y1, y2);
        }
    }
    void draw() override {
        for (int i = y1; i <= y2; i++) {
            for (int j = x1; j <= x2; j++) {
                pixels[i][j] = ' ';
            }
        }
    }
};

class Circle : public Shape {
private:
    int x1, y1;
    int radius;
public:
    Circle(int _x1, int _y1) : x1(_x1), y1(_y1) {
        cout << "Введите радиус ";
        std::cin >> radius;
        radius = abs(radius);
        if (radius > 20) {
            radius = 20;
            cout << "Радиус слишком большой. Изменён на 20\n";
            cout << "Нажмите любую клавишу для продолжения";
            int user_ch = _getch();
        }
    }
    // Функция рисования окружности по алгоритму Брезенхема
    void draw() override {
        for (int y = -radius; y <= radius; ++y) {
            for (int x = -radius; x <= radius; ++x) {
                if (x * x + y * y <= radius * radius) {
                    // Вычисление индексов
                    int i = y1 + y;
                    int j = x1 + x;
                    pixels[i][j] = '*';
                }
            }
        }
    }
};

class Canvas {
public:
    Canvas() {
        // Инициализация холста пробелами
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                pixels[i][j] = ' ';
            }
        }
    }
    ~Canvas() {
        for (int i = 0; i < numShapes; i++) {
            delete shapes[i];
        }
    }
    Shape* shapes[max_shapes];
    int numShapes = 0;
    int cursor_x = WIDTH / 2;
    int cursor_y = HEIGHT / 2;

    void addShape(Shape* shape) {
        if (numShapes < max_shapes) {
            shapes[numShapes++] = shape;
        }
    }
    void drawCanvas() {
        system("cls");
        cout << "Управляйте курсором с помощью стрелочек. Для более быстрого передвижения - используйте WASD\n";
        cout << "L - создать новую линию, R - создать новый прямоугольник, C - создать новый круг\n";
        cout << "Q - удалить выделенное, E - заливка выделенного, X - очистить холст\n";

        // Отрисовка верхней границы
        for (int j = 0; j < WIDTH; j++) {
            pixels[0][j] = '-';
        }
        // Отрисовка боковых границ
        for (int i = 1; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                if (j == 0 || j == WIDTH - 1) pixels[i][j] = '|';
                else pixels[i][j] = ' ';
            }
        }
        // Отрисовка нижней границы
        for (int j = 0; j < WIDTH; j++) {
            pixels[HEIGHT - 1][j] = '-';
        }
        // Отрисовка фигур
        for (int i = 0; i < numShapes; i++) {
            shapes[i]->draw();
        }
        // Отрисовка курсора
        for (int i = 1; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                if ((j == cursor_x && (i == cursor_y - 1 || i == cursor_y + 1)) ||
                    (i == cursor_y && (j == cursor_x - 1 || j == cursor_x + 1))) pixels[i][j] = '.';
            }
        }
        // Вывод на экран
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                cout << pixels[i][j];
            }
            cout << "\n";
        }
    }
    void clearCanvas() {
        numShapes = 0;
    }
};

void MoveUntilKeyPressed(char waited, Canvas &canvas) {
    int input;
    do {
        canvas.drawCanvas();
        cout << "Переместите курсор и нажмите " << waited << " ещё раз";
        input = _getch();
        switch (input) {
        case 72: // Стрелка вниз
            --canvas.cursor_y;
            break;
        case 75: // Стрелка вверх
            --canvas.cursor_x;
            break;
        case 77: // Стрелка вправо
            ++canvas.cursor_x;
            break;
        case 80: // Стрелка влево
            ++canvas.cursor_y;
            break;
        case 'w': 
            canvas.cursor_y -= 5;
            break;
        case 'a': 
            canvas.cursor_x -= 5;
            break;
        case 's': 
            canvas.cursor_y += 5;
            break;
        case 'd':
            canvas.cursor_x += 5;
            break;
        }
    } while (input != waited);
}

int main() {
    Canvas canvas;
    int input_ch;
    int input_ch2;
    int shape_x1, shape_x2, shape_y1, shape_y2;
    do {
        canvas.drawCanvas();
        input_ch = _getch();
        switch (input_ch) {
            case 72: // Стрелка вниз
                --canvas.cursor_y;
                break;
            case 75: // Стрелка вверх
                --canvas.cursor_x;
                break;
            case 77: // Стрелка вправо
                ++canvas.cursor_x;
                break;
            case 80: // Стрелка влево
                ++canvas.cursor_y;
                break;
            case 'w': 
                canvas.cursor_y -= 5;
                break;
            case 'a': 
                canvas.cursor_x -= 5;
                break;
            case 's': 
                canvas.cursor_y += 5;
                break;
            case 'd': 
                canvas.cursor_x += 5;
                break;
            // Очистка холста
            case 'x':
                canvas.clearCanvas();
                canvas.cursor_x = WIDTH / 2;
                canvas.cursor_y = HEIGHT / 2;
                break;
            // Очистка области
            case 'q': {
                shape_x1 = canvas.cursor_x;
                shape_y1 = canvas.cursor_y;
                MoveUntilKeyPressed('q', canvas);
                shape_x2 = canvas.cursor_x;
                shape_y2 = canvas.cursor_y;
                Emtpyness* empty = new Emtpyness(shape_x1, shape_y1, shape_x2, shape_y2);
                canvas.addShape(empty);
                break;
            }
            // Заливка области
            case 'e': {
                shape_x1 = canvas.cursor_x;
                shape_y1 = canvas.cursor_y;
                MoveUntilKeyPressed('e', canvas);
                shape_x2 = canvas.cursor_x;
                shape_y2 = canvas.cursor_y;
                Field* field = new Field(shape_x1, shape_y1, shape_x2, shape_y2);
                canvas.addShape(field);
                break;
            }
            // Создание линии
            case 'l': {
                shape_x1 = canvas.cursor_x;
                shape_y1 = canvas.cursor_y;
                MoveUntilKeyPressed('l', canvas);
                shape_x2 = canvas.cursor_x;
                shape_y2 = canvas.cursor_y;
                Line* line = new Line(shape_x1, shape_y1, shape_x2, shape_y2);
                canvas.addShape(line);
                break;
            }
            // Создание прямоугольника
            case 'r': {
                shape_x1 = canvas.cursor_x;
                shape_y1 = canvas.cursor_y;
                MoveUntilKeyPressed('r', canvas);
                shape_x2 = canvas.cursor_x;
                shape_y2 = canvas.cursor_y;
                Rect* rectangle = new Rect(shape_x1, shape_y1, shape_x2, shape_y2);
                canvas.addShape(rectangle);
                break;
            }  
            // Создание окружности
            case 'c': {
                shape_x1 = canvas.cursor_x;
                shape_y1 = canvas.cursor_y;
                Circle* circle = new Circle(shape_x1, shape_y1);
                canvas.addShape(circle);
                break;
            }          
        }
    } while (input_ch != 27); // Клавиша Esc

    return 0;
}