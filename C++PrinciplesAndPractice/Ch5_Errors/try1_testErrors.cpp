#include <iostream>
#include <vector>

using namespace std;

int main()
{
    try
    {        
        vector<int> v;
        for(int x; cin >> x;)
        {
            v.push_back(x);
        }

        for(int i = 0; i <= v.size(); i++)
        {
            cout << v[i] << endl;
        }
    }
    catch(out_of_range)
    {
        cerr << "Whoops. Range Error!" << '\n';
    }
    
}