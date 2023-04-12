#include <iostream>
#include <vector>

class Vector{
    int size;
    double* elem;
public:
    Vector(int s)
        :size{s},               //initialize 'size'
        elem{new double[s]}     //initialize 'elem'
    {
        for(int i = 0; i < s; i++) elem[i] = 0;
    }

    ~Vector()
    {
        delete[] elem;
    }

    int size() const {return size;}
};


int main()
{
    double* p = new double[5];
    Vector v(5);

    std::cout << p[0] << std::endl;
    std::cout << v.size() << std::endl;

    return 0;
}