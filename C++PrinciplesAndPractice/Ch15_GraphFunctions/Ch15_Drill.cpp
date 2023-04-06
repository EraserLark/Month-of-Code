#include <iostream>

using namespace std;

struct Person
{
    string name;
    int age;
};

istream& operator>>(istream&, Person&);
ostream& operator<<(ostream&, const Person&);

int main()
{
    Person p;
    cin >> p;
    cout << p;
}

istream& operator>>(istream& is, Person& p)
{
    is >> p.name;
    is >> p.age;
    return is;
}

ostream& operator<<(ostream& os, const Person& p)
{
    os << p.name << '\t' << p.age;
    return os;
}