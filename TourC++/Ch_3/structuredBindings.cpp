#include <iostream>
#include <string>
#include <tuple>

std::tuple<std::string, int>CreatePerson()  //Return name and age
{
    return {"Conner", 22};
}

int main()
{
    auto person = CreatePerson();
    std::string& name = std::get<0>(person);
    int age = std::get<1>(person);
}