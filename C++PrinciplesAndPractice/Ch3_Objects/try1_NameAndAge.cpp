#include <iostream>

int main()
{
    std::string first;
    double age;

    std::cout << "Please enter your name and age\n";
    std::cin >> first >> age;

    double months = age * 12;

    std::cout << "Hello " << first <<" (age: "<< months <<" months)\n";
}