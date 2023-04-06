#include <stack>
#include <iostream>

using namespace std;

class Solution {
public:
    bool isValid(string s) {
        stack<char> st;

        for(char c : s)
        {
            if(c == '(' || c == '[' || c == '{')
            {
                st.push(c);
            }
            else if(c == ')' || c == ']' || c == '}')
            {
                if(st.empty()) return false;

                char d = st.top();
                
                switch(d)
                {
                    case '(':
                        d = ')';
                        break;
                    case '[':
                        d = ']';
                        break;
                    case '{':
                        d = '}';
                        break;
                    default:
                        break;
                }

                if(st.size() == 0 || d != c)
                {
                    return false;
                }
                else
                {
                    st.pop();
                }
            }
        }

        return st.empty()? true : false;
    }
};

int main()
{
    Solution s;
    cout << s.isValid("]");
}