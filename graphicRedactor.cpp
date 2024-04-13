#include <iostream>
#include <string>

using namespace std;

/* class B
{
    public:
    virtual void getHp()
    {
        cout << " I like to ick";
    }
};
class BInherited : public B
{
    public:
    void getHp() override
    {
        cout << "\n Oh, smth new, I see he-he";
    }
};
class Item
{
private:
    int hp = 0;
    int level = 1;
public:
    Item(int hp, int level)
    {
        if (hp >= 0 && level > 0) {
        this->hp = hp;
        this->level = level;
        }
        else Item(0, 1);
    }
    Item operator +(Item i2)
    {
        return Item(this->hp + i2.hp, (this->hp + i2.hp) / 10 + 1);
    }
    explicit operator int()
    {
        return this->hp * this->level;
    }
    int getLevel()
    {
        return this->level;
    }
    int getHp()
    {
        return this->hp;
    }
}; */

class Car {
    private:
    int maxSpeed;
    int places;
    public:
    Car(int maxSpeed, int places) {
        this->maxSpeed = maxSpeed;
        this->places = places;
    }
    virtual void Info() 
    {
        cout << "Max speed is " << this->maxSpeed <<
            "and contains " << this->places << "places \n";
    }
};

class Supercar : public Car {
private:
    int price;
public:
    Supercar(int maxSpeed, int places, int price) 
        :Car(maxSpeed, places) 
    {
        this->price = price;
    }
    void Info() override
    {
        cout << this->price << " This one costs too much\n";
    }
};

class Minivan : public Car {
public:
    Minivan(int maxSpeed, int places) 
        :Car(maxSpeed, places) {}
    void Info() override
    {
        cout << "Give me ur kids!!\n";
    }
};

class Train {
protected:
    string name = "train";
public:
    string getName() const
    {
        return this->name;
    }
    virtual void Info()
    {
        cout << "I am a " << this->name << " ha-ha-ha\n";
    }
};

class SmallTrain : public Train {
    public:
    void Info() override
    {
        cout << "I am a small " << getName() << " ha-ha-ha\n";
    }
};


int main()
{
    /* Item hero1(67, 7);
    Item hero2(8,1);
    cout << hero1.getHp() << " " << hero1.getLevel() << "\n";
    cout << hero2.getHp() << " " << hero2.getLevel() << "\n";
    hero1 = hero1 + hero2;
    cout << hero1.getHp() << " " << hero1.getLevel() << "\n";
    cout << int(hero1);
    B dick;
    dick.getHp();
    BInherited newDick;
    newDick.getHp(); */
    Supercar audiTT(220, 2, 3000000);
    Minivan oboyanCar(120, 8);
    SmallTrain electric_boy;

    audiTT.Info();
    oboyanCar.Info();
    electric_boy.Info();


    return 0;
}