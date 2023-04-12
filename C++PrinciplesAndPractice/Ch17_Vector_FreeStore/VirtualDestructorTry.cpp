#include <iostream>

using namespace std;

class Base
{
public:
    Base()  {cout << "Base Constructor called!" << endl;}
    virtual ~Base() {cout << "Base Destructor called!" << endl;}
};

class Child : public Base
{
public:
    Child()  {cout << "Child Constructor called!" << endl;}
    ~Child() {cout << "Child Destructor called!" << endl;}
};

int main()
{
    Child* c = new Child;
    Base* b = c;
    delete b;
}