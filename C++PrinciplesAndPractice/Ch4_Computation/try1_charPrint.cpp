#include<iostream>

int main()
{
    for(int i = 65; i < 123; i++)
    {
        std::cout << char(i) << '\t' << i << '\n';
    }

    return 0;
}