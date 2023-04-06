#include <iostream>
#include <vector>

using namespace std;

struct Person
{
    public:
        Person();
        string Name() const;
        int Age() const;
        void setName(string);
        void setAge(int);
    private:
        string name;
        int age;
};

istream& operator>>(istream&, Person&);
ostream& operator<<(ostream&, const Person&);

int main()
{
    vector<Person> peeps;

    while (cin)
    {
        Person p;
        cin >> p;
        peeps.push_back(p);
    }

    for(Person p : peeps)
    {
        cout << p;
        cout << endl;
    }
}

Person::Person()
{
    name = "No name";
    age = 0;
}

string Person::Name() const
{
    return name;
}

int Person::Age() const
{
    return age;
}

void Person::setName(string str)
{
    name = str;
}

void Person::setAge(int num)
{
    age = num;
}

istream& operator>>(istream& is, Person& p)
{
    string str;
    int age;
    
    is >> str;
    p.setName(str);
    is >> age;
    p.setAge(age);

    return is;
}

ostream& operator<<(ostream& os, const Person& p)
{
    os << p.Name() << '\t' << p.Age();
    return os;
}
