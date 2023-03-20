#include <iostream>

int main()
{
    int v[] {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    int i = 0;
    for(int& x : v)
    {
        ++x;
        std::cout << v[i] << '\n';
        i++;
    }
}