#include <iostream>

int main()
{
    std::string first;
    std::string second;

    std::cout << "Please enter your first and last names\n";
    std::cin >> first >> second;
    
    std::cout << "Hello " << first <<" "<< second << '\n';
}