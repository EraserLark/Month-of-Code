#include "../Libraries/std_lib_facilities.h"

class Name_pairs
{
    public:
    void read_names();
    void read_ages();

    void print();
    void sort();

    vector<string> getNames();
    vector<double> getAges();

    private:
    vector<string> name;
    vector<double> age;
};

ostream& operator<<(ostream& os, Name_pairs namePair)
{
    for(int i = 0; i < namePair.getNames().size(); i++)
    {
        os << "Name: " << namePair.getNames()[i] << ", Age: " << namePair.getAges()[i] << endl;
    }

    return os;
}

int main()
{
    Name_pairs np;
    np.read_names();
    np.read_ages();
    np.sort();

    cout << np;

    return 0;
}

vector<string> Name_pairs::getNames()
{
    return name;
}

vector<double> Name_pairs::getAges()
{
    return age;
}

void Name_pairs::read_names()
{
    //Reads a series of names
    cout << "Enter a series of names: " << endl;
    
    string tempName;
    while(cin >> tempName && tempName != ";")
    {
        name.push_back(tempName);
    }
}

void Name_pairs::read_ages()
{
    //Prompts user for an age for each name
    for(int i = 0; i < name.size(); i++)
    {
        cout << "Enter a corresponding age: ";

        int tempAge;
        cin >> tempAge;
        age.push_back(tempAge);
    }
}

void Name_pairs::print()
{
    //prints out name, age pairs in the order of the name vector (one per line)
    for(int i = 0; i < name.size(); i++)
    {
        cout << "Name: " << name[i] << ", Age: " << age[i] << endl;
    }
}

void Name_pairs::sort()
{
    //Sort name vector in alpha order, then reorganizes age vector to match
    int nameSize = name.size();

    for(int i = 0; i < nameSize; i++)
    {
        string tempName = name[i];
        int tempAge = age[i];
        int arrayNum = i;

        for(int j = i; j < nameSize; j++)
        {
            if(name[j] < tempName)
            {
                tempName = name[j];
                tempAge = age[j];
                arrayNum = j;
            }
        }

        name[arrayNum] = name[i];
        name[i] = tempName;

        age[arrayNum] = age[i];
        age[i] = tempAge;
    }
}