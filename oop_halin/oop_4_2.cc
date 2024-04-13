#include <iostream>
#include <string>
using namespace std;

class Date {
public:
    Date(int day, int month, int year) {
        this->day = day;
        this->month = month; 
        this->year = year;
    }
protected:
    int day;
    int month;
    int year;
};
class Drug : public Date {
public:
    Drug(string name, string company, int day, int month, int year) 
        : Date(day, month, year) {
        this->name = name;
        this->company = company;
    }
    void Get_info() {
        cout << name << " " << company << " " << day << "/" <<
            month << "/" << year << " days from making: " << Days_from_making();
    }
private:
    string name;
    string company;
    int Days_from_making() {
        return (2024 - year) * 365;
    }
};

int main() {
    Drug a("aspi", "drugmake", 23, 6, 2009);
    a.Get_info();
    return 0;
}