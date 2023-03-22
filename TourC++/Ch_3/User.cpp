#include <iostream>
#include <cmath>
#include "Vector.h"

double sqrt_sum(Vector& v)
{
    double sum = 0;
    for(int i = 0; i < v.size(); i++)
    {
        sum += std::sqrt(v[i]);
    }
    return sum;
}

int main()
{
    Vector vec(4);
    std::cout << sqrt_sum(vec) << '\n';
}