#include <iostream>

int& bad()
{
    int x = 0;
    return x;
}

int main()
{
    int& y = bad();
}