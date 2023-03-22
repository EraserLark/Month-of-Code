#include <iostream>
#include <string>
#include <tuple>

struct Person{
    std::string Name;
    int Age;
};

Person CreatePerson()  //Return name and age
{
    return {"Conner", 22};
}

int main()
{
    Person me = CreatePerson();
}