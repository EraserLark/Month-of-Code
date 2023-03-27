#include <iostream>
#include <vector>

class Token
{
    public:
        char kind;
        double value;
};
Token getToken();

std::vector<Token> tok;

int main()
{
    while(std::cin)
    {
        Token t = getToken();
        tok.push_back(t);
    }

    for(int i = 0; i < tok.size(); i++)
    {
        if(tok[i].kind == '*')
        {
            double lVal = tok[i-1].value;
            double rVal = tok[i+1].value;

            double product = lVal * rVal;
        }
    }
}

Token getToken()
{

}