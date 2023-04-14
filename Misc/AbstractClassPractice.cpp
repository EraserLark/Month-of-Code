#include <iostream>

using namespace std;

class Base{
public:
    int number;
    virtual void doSomething() = 0;
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

        void doSomething()
        {
            cout << "Class A!" << endl;
        }
};

class B : public Base
{
    public:
        B(int n = 2)
        : Base(n) { };

        void doSomething()
        {
            cout << "Class B rulez" << endl;
        }
};

int main()
{
    A* a = new A(34);
    B* b = new B();
    Base* basePtr = b;

    a->doSomething();
    basePtr->doSomething();

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
Class A!
Class B rulez

34
2
*/