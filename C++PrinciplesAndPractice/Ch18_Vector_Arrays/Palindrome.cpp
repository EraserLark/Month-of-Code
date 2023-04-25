#include <iostream>

using namespace std;

bool is_palindrome(const string& s);

int main()
{
    for(string s; cin >> s;)
    {
        cout << s << " is";
        if(!is_palindrome(s) )cout << " not";
        cout << " a palindrome.\n";
    }
}

bool is_palindrome(const string& s)
{
    int first = 0;
    int last = s.length() - 1;
    while(first < last)
    {
        if(s[first] != s[last]) return false;
        first++;
        last--;
    }
    return true;
}