#include <iostream>

using namespace std;

int main()
{
    int x = 2;
    int& r = x;
    r = 7;

    int* r2 = &r;
    *r2 = 99;

    int&r3 = *r2;
    r3 = 100;

    cout << x << '\n';
}