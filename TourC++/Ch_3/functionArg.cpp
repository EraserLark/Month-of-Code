#include <iostream>
#include <vector>

using namespace std;

int sum(const vector<int>& v)
{
    int s = 0;
    for (const int i : v)
        s += i;
    return s;
}

int main()
{
    vector fib = {1,2,3,5,8,13,21};
    int x = sum(fib); // x becomes 53

    cout << x << endl;
}