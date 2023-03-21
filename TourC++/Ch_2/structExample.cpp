#include <iostream>

using namespace std;

struct Vector{
    int size;
    double* elem;
};

void vector_init(Vector& v, int s);
double read_and_sum(int s);

int main()
{
    cout << "Enter a size: ";
    int number;
    cin >> number;

    int sum = read_and_sum(number);
    cout << "The sum is: " << sum << '\n';
}

void vector_init(Vector& v, int s)
{
    v.elem = new double[s];
    v.size = s;
}

double read_and_sum(int s)
{
    Vector v;
    vector_init(v,s);

    for(int i = 0; i < s; i++)
    {
        cin >> v.elem[i];
    }

    double sum = 0;
    for(int i = 0; i < s; i++)
    {
        sum += v.elem[i];
    }

    return sum;
}