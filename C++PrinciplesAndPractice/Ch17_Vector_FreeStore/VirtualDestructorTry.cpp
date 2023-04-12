#include <iostream>

using namespace std;

class Base
{
public:
    Base()  {cout << "Base Constructor called!" << endl;}
    virtual ~Base() {cout << "Base Destructor called!" << endl << endl;}
};

class FirstChild : public Base
{
public:
    FirstChild()  {cout << "First Child Constructor called!" << endl;}
    ~FirstChild() {cout << "First Child Destructor called!" << endl;}
};

class SecondChild : public Base
{
public:
    SecondChild() {cout << "Second Child Constructor called" << endl;}
    ~SecondChild() {cout << "Second Child Destructor called" << endl;}
};

int main()
{
    Base* b = new Base;
    delete b;

    FirstChild* c = new FirstChild;
    delete c;

    SecondChild* c2 = new SecondChild;
    Base* b2 = c2;
    delete b2;
}