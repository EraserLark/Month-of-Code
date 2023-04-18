#include <iostream>
#include <vector>

//Part 1
int* array = new int[11] {100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110};
std::vector<int>* vector = new std::vector<int> {100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119};

void print_array10(std::ostream& os, int* a);
void print_array(std::ostream& os, int* a, int n);
void print_vector(std::ostream& os, std::vector<int>* v, int n);

//Part 2
int a = 7;
int* p1 = &a;

int* p2 = new int[7] {1,2,3,4,5,6,7};
int* p3 = p2;

int main()
{   
    p1 = p2;
    p3 = p2;

    p1 = new int[10] {1,2,3,4,5,6,7,8,9,10};
    p2 = new int[10] {0,0,0,0,0,0,0,0,0,0};

    for(int i = 0; i < 10; i++)
    {
        p2[i] = p1[i];
        std::cout << p2[i] << std::endl;
    }

    //std::cout << "Pointer: " << p1 << ", Value: " << *p1 << std::endl;
    //print_array(std::cout, p2, 7);


    delete p1;
    delete[] p2;
    delete[] p3;    //Just 'delete'?
    delete[] array;
    delete[] vector;
}

void print_array(std::ostream& os, int* a, int n)
{
    for(int i = 0; i < n; i++)
    {
        os << a[i] << std::endl;    
    }
}

void print_vector(std::ostream& os, std::vector<int>* v, int n)
{
    for(int i : *v)
    {
        os << i << std::endl;
    }
}

void print_array10(std::ostream& os, int* a)
{
    for(int i = 0; i < 10; i++)
    {
        os << a[i] << std::endl;    
    }
}