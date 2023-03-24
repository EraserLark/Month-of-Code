#include<iostream>

int main()
{
    int charCount = 97;

    while(charCount < 123)
    {
        std::cout << char(charCount) << '\t' << charCount << '\n';
        charCount++;
    }

    return 0;
}