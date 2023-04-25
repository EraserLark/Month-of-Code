#include <iostream>

using namespace std;

bool is_palindrome(const string& s);
istream& read_word(istream& is, char* buffer, int max);

int main()
{
    constexpr int max = 128;
    for(char s[max]; read_word(cin, s, max);)
    {
        cout << s << " is";
        if(!is_palindrome(s, strlen(s)))cout << " not";
        cout << " a palindrome.\n";
    }
}

bool is_palindrome(const string& s, int n)
{
    int first = 0;
    int last = n - 1;
    while(first < last)
    {
        if(s[first] != s[last]) return false;
        first++;
        last--;
    }
    return true;
}

istream& read_word(istream& is, char* buffer, int max)
{
    is.width(max);  //Prevents buffer overflow for following operations
    is >> buffer;
    return is;
}