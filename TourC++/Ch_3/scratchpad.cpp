#include <iostream>

class Vector{
    public:
        Vector(int s);
        double& operator[](int i);
        int size();
    private:
        double* elem;
        int sz;
};

Vector::Vector(int s)
{
    elem = new double[s];
    sz = s;
}

double& Vector::operator[](int i)
{
    return elem[i];
}

int Vector::size()
{
    return sz;
}

int main()
{

}