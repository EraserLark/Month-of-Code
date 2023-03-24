#include <iostream>

int main()
{
    int a;
    int b;

    while(std::cin >> a, std::cin >> b)
    {
        int small;
        int large;

        if(a > b)
        {
            large = a;
            small = b;
        }
        else if(a < b)
        {
            large = b;
            small = a;
        }
        else if (a == b)
        {
            std::cout << "The numbers are equal!";
            return 0;
        }

        std::cout << "The smaller value is: " << small << '\n';
        std::cout << "The larger value is: " << large << '\n';
        std::cout << std::endl;
    }
}