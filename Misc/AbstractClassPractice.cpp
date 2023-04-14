#include <iostream>

using namespace std;

class Base{
public:
    int number;
    virtual ~Base() { }
protected:
    Base(int);
private:
};

class A : public Base
{
    public:
        A(int n = 1)
        : Base(n) { };
};

class B : public Base
{
    public:
        B(int n = 2)
        : Base(n) { };
};

int main()
{
    A* a = new A(34);
    B* b = new B();

    Base* basePtr = b;

    cout << a->number << endl;
    cout << basePtr->number;
}

Base::Base(int n)
{
    number = n;
}