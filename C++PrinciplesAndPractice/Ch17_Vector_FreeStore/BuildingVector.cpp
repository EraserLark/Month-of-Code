#include <iostream>

template <typename T>
class Vector{
    int sz;
    T* elem;
    int space;
public:
    Vector() : sz{0}, elem{nullptr}, space{0} {}

    explicit Vector(int s)
        :sz{s},                 //initialize 'size'
        elem{new T[s]},    //initialize 'elem'
        space{s}     
    {
        for(int i = 0; i < s; i++) elem[i] = 0;
    }

    Vector(std::initializer_list<T> lst)
    : sz{lst.size()}, elem{new T[sz]}
    {
        std::copy(lst.begin(), lst.end(), elem);
    }

    //copy constructor
    Vector(const Vector& arg)
    : sz{arg.sz}, elem{new T[arg.sz]}
    {
        std::copy(arg.elem, arg.elem + arg.sz, elem);   //Need to test
    }
    
    //Copy assignment
    Vector& operator=(const Vector& a)
    {
        //Self allocation, no work needed
        if(this == &a) return *this;

        //Enough space currently to allocate copy
        if(a.sz <= space)
        {
            for(int i = 0; i < a.sz; i++)
            {
                elem[i] = a.elem[i];
                sz = a.sz;
                return *this;
            }
        }

        //Need more space to allocate copy
        T* p = new T[a.sz];               //allocate new space
        for(int i = 0; i < a.sz; i++) p[i] = a.elem[i];     //std::copy(a.elem, a.elem + a.sz, elem);     //copy elements
        delete[] elem;  //deallocate old space
        space = sz = a.sz;
        elem = p;       //now we can reset 'elem'
        return *this;   //return a self-reference
    }

    Vector(Vector&&);               //move constructor
    Vector& operator=(Vector&&);    //move assignment

    T& operator[](int n) { return elem[n];}        //Access a non-const vector
    const T operator[](int n) const { return elem[n];}   //Access a const vector

    ~Vector()
    {
        delete[] elem;
    }

    int size() const {return sz;}
    int capacity() const {return space;}

    void reserve(int newalloc);
    void resize(int newsize);
    void push_back(T d);

    //T get(int n) const {return elem[n];}   //access: read
    //void set(int n, T v) {elem[n] = v;}    //access: write
};

int main()
{   

    Vector<int> v = {1,2,3};

    std::cout << "v[0] = " << v[0] << std::endl;
    v[0] = 4;
    std::cout << "v[0] = " << v[0] << std::endl;

    return 0;
}

template <typename T>
void Vector<T>::reserve(int newalloc)
{
    if(newalloc <= space) return;  //Prevent decrease allocation

    double* p = new double[newalloc];
    for(int i = 0; i < sz; i++)
    {
        p[i] = elem[i];
    }   
    delete[] elem;
    elem = p;
    space = newalloc;
}

template <typename T>
void Vector<T>::resize(int newsize)
{
    reserve(newsize);
    for(int i = 0; i < newsize; i++)
    {
        elem[i] = 0;
    }
    sz = newsize;
}

template <typename T>
void Vector<T>::push_back(T d)
{
    if(space == 0)
    {
        reserve(8);
    }
    else if(sz == space)
    {
        reserve(sz * 2);
    }

    elem[sz] = d;
    sz++;
}