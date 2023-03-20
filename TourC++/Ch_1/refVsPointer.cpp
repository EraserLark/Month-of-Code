#include <iostream>

void pointerPrint(int *arrayPtr);
void referencePrint(const int& arrayRef);

int main()
{
    int v[] {0,1,2,3,4};

    //Copy array
    for(int i : v)
    {
        std::cout << "With Copying:" << i << '\n';
    }

    pointerPrint(v);
    referencePrint(*v);
}

void pointerPrint(int *arrayPtr)
{
    for(int i = 0; i < 5; i++)
    {
        std::cout << "With Pointer:" << arrayPtr[i] << '\n';
    } 
}

void referencePrint(const int& arrayRef)
{
    for(int i = 0; i < 5; i++)
    {
        std::cout << "With Reference:" << arrayRef << '\n';
    }
}