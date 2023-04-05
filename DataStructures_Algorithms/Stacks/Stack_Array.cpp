#include <iostream>

using namespace std;

#define MAX_SIZE 101




int A[MAX_SIZE];
int top = -1;

void Push(int);
void Pop();
int Top();
void Print();

int main()
{
    Push(2);
    Push(5);
    Push(10);
    Pop();
    Push(12);
    Print();
}

void Push(int x)
{
    if(top == MAX_SIZE - 1)     //Handling overflow
    {
        cout << "What are we? Some kind of Stack Overflow?";
        return;
    }

    top++;
    A[top] = x;
}

void Pop()
{
    if(top == -1)
    {
        cout << "List is empty. No element to pop.";
        return;
    }

    top--;
}

int Top()
{
    return A[top];
}

void Print()
{
    int i;
    cout << "Stack" << endl;
    for(int i = 0; i <= top; i++)
    {
        cout << A[i] << endl;
    }
}