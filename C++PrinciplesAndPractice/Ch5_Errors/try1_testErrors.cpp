#include <iostream>
#include <stdlib.h>
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
            if(i > (v.size() - 1))
            {
                throw runtime_error("i is larger than v.size");
            }
            cout << v[i] << endl;
        }
    }
    catch(out_of_range)
    {
        cerr << "Whoops. Range Error!" << '\n';
        return 1;
    }
    catch(runtime_error)
    {
        cerr << "Runtime error" << '\n';
        return 2;
    }
    

    return 0;
}