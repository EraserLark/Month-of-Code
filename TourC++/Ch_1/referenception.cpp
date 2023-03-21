#include <iostream>

using namespace std;

struct testStruct
{
    int* numPtr;
    int*& numRef;      //Reference to a Pointer

    testStruct(int& number)
        : numRef(numPtr)
    {
        numPtr = &number;
        numRef = numPtr;
    }
};

int main()
{
    int x = 2;
    int& r = x;
    r = 7;

    int* p = &r;
    *p = 99;

    int** p2 = &p;
    **p2 = 88;

    testStruct* struct1 = new testStruct(**p2);
    *(struct1->numRef) = 69;

    int&r3 = *(struct1->numRef);
    r3 = 100;

    cout << x << '\n';
}