#include <iostream>
#include <cstring>

using namespace std;

istream& read_word(istream& is, char* buffer, int max);
bool is_palindrome(const char* first, const char* last);

int main()
{
    constexpr int max = 128;
    for(char s[max]; read_word(cin, s, max);)
    {
        cout << s << " is";
        if(!is_palindrome(&s[0], &s[strlen(s)-1]))cout << " not";
        cout << " a palindrome.\n";
    }
}

bool is_palindrome(const char* first, const char* last)
{
    while(first < last)
    {
        if(*first != *last) return false;
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