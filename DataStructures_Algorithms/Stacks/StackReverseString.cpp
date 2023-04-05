#include <cstring>
#include <iostream>
#include <stack>        //stack from the Standard Template Library (STL)
using namespace std;

void Reverse(char *C, int n);

int main()
{
    char C[] {'H','e','l','l','o'};
    Reverse(C, 5);
    cout << C;
}

void Reverse(char *C, int n)
{
    stack<char> s;

    for(int i = 0; i < n; i++)
    {
        s.push(C[i]);
    }

    for(int i = 0; i < n; i++)
    {
        C[i] = s.top();
        s.pop();
    }
}