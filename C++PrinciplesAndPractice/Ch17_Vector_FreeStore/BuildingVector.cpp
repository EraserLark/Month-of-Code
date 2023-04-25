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

    Vector(std::initializer_list<double> lst)
    : sz{lst.size()}, elem{new double[sz]}
    {
        std::copy(lst.begin(), lst.end(), elem);
    }

    //copy constructor
    Vector(const Vector& arg)
    : sz{arg.sz}, elem{new double[arg.sz]}
    {
        std::copy(arg.elem, arg.elem + arg.sz, elem);   //Need to test
    }
    
    //Copy assignment
    Vector& operator=(const Vector& a)
    {
        double* p = new double[a.sz];               //allocate new space
        std::copy(a.elem, a.elem + a.sz, elem);     //copy elements
        delete[] elem;  //deallocate old space
        elem = p;       //now we can reset 'elem'
        sz = a.sz;
        return *this;   //return a self-reference
    }

    double& operator[](int n) { return elem[n];}        //Access a non-const vector
    double operator[](int n) const { return elem[n];}   //Access a const vector

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

    Vector v = {1,2,3};
    for(int i = 0; i < v.size(); i++)
    {
        //v.set(i, 1.1*i);
        std::cout << "v[" << i << "]==" << v.get(i) << '\n';
    }

    std::cout << "v[0] = " << v[0] << std::endl;
    v[0] = 4;
    std::cout << "v[0] = " << v[0] << std::endl;

    return 0;
}