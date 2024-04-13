/*Создать класс с указанными двумя полями (Поле 1, Поле 2) и тремя
методами:
- конструктор для инициализации объекта;
- метод формирования строки с информацией об объекте;
- метод обработки значений полей по индивидуальному варианту.

Поле 1: Цена товара, Поле 2: Количество единиц товара,
Функция обработки полей: Вычислить общую стоимость товара  
*/

#include <iostream>
#include <string>

class Item {
public:
    Item(int price, int quantity) {
        this->price = price;
        this->quantity = quantity;
    }
    std::string info() {
        int total = total_price();
        return "Price: " + std::to_string(price) +
            ", quantity: " + std::to_string(quantity) +
            ", total price is " + std::to_string(total);
    }    
private:
    int price;
    int quantity;
    int total_price() {
        return price * quantity;
    }
};

int main() {
    Item tables(1500, 3);
    Item chairs(500, 17);
    std::cout << tables.info() << std::endl;
    std::cout << chairs.info() << std::endl;
    return 0;
}