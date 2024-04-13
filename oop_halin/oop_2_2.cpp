/*Создать класс с полями, указанными в индивидуальном задании
Реализовать в классе методы:
- конструктор по умолчанию;
- конструктор с параметрами;
- деструктор для освобождения памяти (с сообщением об уничтожении
объекта);
- функцию формирования строки информации об объекте
- функции обработки данных, указанные в индивидуальном задании
Класс и его поля: дата(три числа), функция 1: определить, совпадают
ли номер месяца и число дня, функция 2: увеличить дату на 1 месяц.
*/
#include <iostream>
#include <string>
using namespace std;

class Date {
public:
    Date() {
        this->day = 0;
        this->month = 0;
        this->year = 0;
    }
    Date(int day, int month, int year) {
        this->day = day;
        this->month = month;
        this->year = year;
    }
    ~Date() {
        cout << "\nObject deleted.";
    }
    string Info() {
        return "Day: " + to_string(day) + ", month: " +
            to_string(month) + ", year: " + to_string(year);
    }
    void CheckMonthAndDayEquality() {
        if (month==day) {
            cout << "Month and day are equal\n";
        }
        else {
            cout << "Month and day are not equal\n";
        }
    }
    void IncrementMonth() {
        if (month < 12) {
            month++;
        }
        else {
            year++;
            month = 1;
        }
    }
private:
    int day;
    int month;
    int year;
};

int main() {
    Date date1;
    Date date2(12, 06, 2006);
    Date *date3 = new Date(07, 12, 2022);
    cout << date1.Info() << endl;
    cout << date2.Info() << endl;
    cout << date3->Info() << endl;
    date3->IncrementMonth();
    date3->CheckMonthAndDayEquality();
    cout << date3->Info();
    delete date3;
    return 0;
}