#include <iostream>

int main()
{
    std::string first;
    int age;

    std::cout << "Please enter your name and age\n";
    std::cin >> first >> age;
    
    std::cout << "Hello " << first <<" (age: "<< age <<")\n";
}