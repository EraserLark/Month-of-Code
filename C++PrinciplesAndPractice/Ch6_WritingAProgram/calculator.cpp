#include <iostream>
#include <vector>
#include "../Libraries/std_lib_facilities.h"

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
        bool full {false};
        Token buffer;
};

double expression();
double term();
double primary();

vector<Token> tok;
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

    return 0;
}

void TokenStream::putback(Token t)
{
    if(full)    throw("putback() into a full buffer");
    buffer = t;
    full = true;
}

Token TokenStream::get()
{
    if(full)
    {
        full = false;
        return buffer;
    }

    char ch;
    std::cin >> ch;
    switch(ch)
    {
        case ';':
            break;
        case 'q':
            break;
        case '(': case ')': case '+': case '-': case '*': case '/':
            return Token{ch};
        case '.':
        case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
            {
                std::cin.putback(ch);
                double val;
                std::cin >> val;
                return Token{'8', val};
            } 
        default:
            throw("Bad token");
    }
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
    Token t = ts.get();
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