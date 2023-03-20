#include <iostream>

int main()
{
    int v[] {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    for(int& x : v)
    {
        ++x;
        std::cout << x << '\n';
    }
}