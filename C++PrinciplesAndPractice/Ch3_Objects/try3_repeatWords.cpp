#include <iostream>

int main()
{
    std::string prev = " ";
    std::string current;

    while(std::cin >> current)
    {
        if(prev == current)
        {
            std::cout << "repeated word: " << current << std::endl;
        }
        prev = current;
    }
}