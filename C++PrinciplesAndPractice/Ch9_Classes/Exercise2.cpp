#include "../Libraries/std_lib_facilities.h"

class Name_pairs
{
    public:
    void read_names();
    void read_ages();

    void print(const Name_pairs& pairs);
    void sort(Name_pairs& pairs);

    private:
    vector<string> name;
    vector<double> age;
};

int main()
{
    Name_pairs n;
    n.read_names();
    n.read_ages();

    return 0;
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

void Name_pairs::print(const Name_pairs& pairs)
{
    //prints out name, age pairs in the order of the name vector (one per line)

}

void Name_pairs::sort(Name_pairs& pairs)
{
    //Sort name vector in alpha order, then reorganizes age vector to match

}