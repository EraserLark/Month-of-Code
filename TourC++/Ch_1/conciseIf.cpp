#include <iostream>

using namespace std;

int main()
{
    cout << "Enter a number: ";
    int i;
    cin >> i;

    if(int n = i)   //create local var 'n', n gets i. Enter if n != 0
    {
        cout << "The number is NOT 0 -- n = " << n << '\n';
    }
    else
    {
        cout << "The number is 0 -- n = " << n << '\n';
    }
}