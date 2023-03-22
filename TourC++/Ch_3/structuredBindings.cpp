#include <iostream>
#include <string>
#include <tuple>

std::tuple<std::string, int>CreatePerson()  //Return name and age
{
    return {"Conner", 22};
}

int main()
{
    std::string name;
    int age;
    std::tie(name, age) = CreatePerson();
}