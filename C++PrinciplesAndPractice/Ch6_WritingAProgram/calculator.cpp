#include <iostream>
#include <vector>

class Token
{
    public:
        char kind;
        double value;
};

class TokenStream
{
    public:
        TokenStream();
        Token get();
        void putback(Token t);
    private:
};

Token getToken();
double expression();
double term();
double primary();

std::vector<Token> tok;
TokenStream ts;

int main()
{
    try
    {
        double val = 0;
        while(std::cin)
        {
            Token t = ts.get();

            if(t.kind == 'q') break;
            if(t.kind == ';')
            {
                std::cout << '=' << val << '\n';
            }
            else
            {
                ts.putback(t);
            }

            val = expression();
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
    Token t = ts.get();

    while(true)
    {
        switch (t.kind)
        {
        case '+':
            left += term();
            t = ts.get();
            break;
        
        case '-':
            left -= term();
            t = ts.get();
            break;

        default:
            ts.putback(t);
            return left;
        }
    }

    return left;
}

double term()
{
    double left = primary();
    Token t = ts.get();
    while(true)
    {
        switch(t.kind)
        {
            case '*':
                left *= primary();
                t = ts.get();
                break;
            case '/':
            {
                double d = primary();   //must put code within {} if defining/initializing vars in a switch statement
                if(d == 0)  throw("divide by zero");
                left /= d;
                t = ts.get();
                break;
            }
            default:
                ts.putback(t);
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
            t = ts.get();
            if(t.kind != ')')   throw("')' expected");
            return d;
        }
        case '8':
            return t.value;
        default:
            throw("Primary Expected");
    }
}