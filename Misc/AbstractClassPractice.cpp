#include <iostream>

using namespace std;

class Base{
public:
    int number;
    virtual void doSomething(string message) = 0;
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

        void doSomething(string message = "Wowzers")
        {
            cout << "Class A! " << message << endl;
        }
};

class B : public Base
{
    public:
        B(int n = 2)
        : Base(n) { };

        void doSomething(string message = "wuh oh")
        {
            cout << "Class B rulez!! " << message << endl;
        }
};

int main()
{
    A* a = new A(34);
    B* b = new B();
    Base* basePtr = b;

    a->doSomething();
    basePtr->doSomething("Test");

    cout << endl;
    cout << a->number << endl;
    cout << basePtr->number;
}
Base::Base(int n)
{
    number = n;
}

/*
Output:
Class A! Wowzers
Class B rulez!! Test

34
2
*/