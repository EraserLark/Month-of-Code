#include <iostream>
#include <vector>

class Vector{
    int sz;
    double* elem;
public:
    Vector(int s)
        :sz{s},               //initialize 'size'
        elem{new double[s]}     //initialize 'elem'
    {
        for(int i = 0; i < s; i++) elem[i] = 0;
    }

    ~Vector()
    {
        delete[] elem;
    }

    int size() const {return sz;}

    double get(int n) const {return elem[n];}   //access: read
    void set(int n, double v) {elem[n] = v;}    //access: write
};

int main()
{
    Vector v(5);
    for(int i = 0; i < v.size(); i++)
    {
        v.set(i, 1.1*i);
        std::cout << "v[" << i << "]==" << v.get(i) << '\n';
    }

    return 0;
}