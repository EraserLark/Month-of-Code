#include <iostream>

using namespace std;

int main()
{
    int x = 2;
    int& r = x;
    r = 7;

    int* p = &r;
    *p = 99;

    int** p2 = &p;
    **p2 = 88;

    int&r3 = **p2;
    r3 = 100;

    cout << x << '\n';
}