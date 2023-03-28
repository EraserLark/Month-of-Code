//For sake of time, I am moving on while this is unfinished

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
        //TokenStream();
        Token get();
        void putback(Token t);
        void ignore(char c);
    private:
        bool full {false};
        Token buffer;
};

class Variable
{
    public:
        string name;
        double value;
};

vector<Variable> var_table;

const char number = '8';
const char print = ';';
const char quit = 'q';
const string prompt = ">";
const string result = "=";

double expression();
double term();
double primary();
void calculate();
void clean_up_mess();
double getValue(string s);
void setValue(string s, double d);
double statement();

vector<Token> tok;
TokenStream ts;

int main()
{
    try
    {
        calculate();
        keep_window_open();
        return 0;
    }
    catch(std::exception& e)
    {
        std::cerr << e.what() << '\n';
        keep_window_open("~~");
        return 1;
    }
    catch(...)
    {
        std::cerr << "Exception \n";
        keep_window_open("~~");
        return 2;
    }

    return 0;
}

void calculate()
{
    while (cin)
    try {
        cout << prompt;
        Token t = ts.get();

        while (t.kind == print) t=ts.get(); // first discard all “prints”
        if (t.kind == quit) return;

        ts.putback(t);
        cout << result << statement() << '\n';
    }
    catch (exception& e) {
        cerr << e.what() << '\n'; // write error message
        clean_up_mess();
    }  
}

void clean_up_mess()
{
    ts.ignore(print);
}

double getValue(string s)
{
    for(const Variable& v : var_table)
    {
        if(v.name == s) return v.value;
    }
    error("get: undefined var ", s);
}

void setValue(string s, double d)
{
    for (Variable& v : var_table)
        if (v.name == s) {
            v.value = d;
            return;
        }
        error("set: undefined variable ", s);
}

double statement()
{
    Token t = ts.get();
    switch (t.kind) {
    //case "let":
        //return declaration();
    default:
        ts.putback(t);
        return expression();
    }
}

void TokenStream::ignore(char c)
{
    if(full && c==buffer.kind)
    {
        full = false;
        return;
    }
    full = false;

    char ch = 0;
    while(cin >> ch)
    {
        if(ch == c) return;
    }
}

void TokenStream::putback(Token t)
{
    if(full)    throw("putback() into a full buffer");
    buffer = t;
    full = true;
}

Token TokenStream::get()
{
    if (full) { // check if we already have a Token ready
        full = false;
        return buffer;
    }
    char ch;
    cin >> ch; // note that >> skips whitespace (space, newline, tab, etc.)
    switch (ch) {
    case quit:
    case print:
    case '(':
    case ')':
    case '+':
    case '–':
    case '*':
    case '/':
    case '%':
        return Token{ch}; // let each character represent itself
    case '.': // a floating-point-literal can start with a dot
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9': // numeric literal
        { cin.putback(ch); // put digit back into the input stream
        double val;
        cin >> val; // read a floating-point number
        return Token{number,val};
        }
    default:
        error("Bad token");
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
            case '%':
            {
                int i1 = narrow_cast<int>(left);
                int i2 = narrow_cast<int>(primary());
                if (i2 == 0) error("%: divide by zero");
                left = i1%i2;
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
        case number:
            return t.value;
        case '-':
            return -primary();
        case '+':
            return primary();
        default:
            throw("Primary Expected");
    }
}