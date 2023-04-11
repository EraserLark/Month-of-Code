#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    void reverseString(vector<char>& s) {
        char front = s.front();
        char back = s.back();
        int size = s.size();
        
        for(int i = 0; i < size; i++)
        {
            if(front == back)
            {
                return;
            }
            
            char temp;
            front = s[i];
            back = s[size - i];
            
            temp = front;
            s[i] = back;
            s[size - i] = temp;
        }
    }
};

int main()
{
    Solution s;
    vector<char> message = {'h', 'i'};
    s.reverseString(message);
}