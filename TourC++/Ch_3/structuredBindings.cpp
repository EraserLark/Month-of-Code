#include <iostream>
#include <string>
#include <tuple>

std::tuple<std::string, int> CreatePerson()  //Return name and age
{
    return {"Conner", 22};
}

int main()
{
    auto[name, age] = CreatePerson();   //structured bindings

    std::cout << name << std::endl;
    std::cout << age << std::endl;
}