#include <iostream>
#include <vector>

class Token
{
    public:
        char kind;
        double value;
};
Token getToken();
double expression();
double term();
double primary();

std::vector<Token> tok;

int main()
{
    try
    {
        while(std::cin)
        {
            std::cout << '=' << expression() << '\n';
        }  
    }
    catch(std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }
    catch(...)
    {
        std::cerr << "Exception \n";
        return 2;
    }
}

Token getToken()
{

}

double expression()
{
    double left = term();
    Token t = getToken();

    while(true)
    {
        switch (t.kind)
        {
        case '+':
            left += term();
            t = getToken();
            break;
        
        case '-':
            left -= term();
            t = getToken();
            break;

        default:
            return left;
        }
    }

    return left;
}

double term()
{
    double left = primary();
    Token t = getToken();
    while(true)
    {
        switch(t.kind)
        {
            case '*':
                left *= primary();
                t = getToken();
                break;
            case '/':
            {
                double d = primary();   //must put code within {} if defining/initializing vars in a switch statement
                if(d == 0)  throw("divide by zero");
                left /= d;
                t = getToken();
                break;
            }
            default:
                return left;
        }
    }
}

double primary()
{
    Token t = getToken();
    switch(t.kind)
    {
        case '(':
        {
            double d = expression();
            t = getToken();
            if(t.kind != ')')   throw("')' expected");
            return d;
        }
        case '8':
            return t.value;
        default:
            throw("Primary Expected");
    }
}