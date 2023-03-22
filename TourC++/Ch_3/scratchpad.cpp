#include <iostream>

int& bad()
{
    int x = 0;
    return x;   //Don't return a reference to a local var!
}

int main()
{
    int& y = bad();
}