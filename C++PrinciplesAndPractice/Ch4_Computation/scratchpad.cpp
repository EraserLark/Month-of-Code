#include <iostream>
#include <vector>

int main()
{
    std::vector<int> v = {1,2,3,4};

    for(int x : v)      //for each int 'x' in vector 'v'...
    {
        std::cout << x << '\n';
    }
}