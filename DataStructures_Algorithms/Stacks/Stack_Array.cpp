#include <iostream>
#define MAX_SIZE 101

using namespace std;

class Stack{
public:
    void Push(int);
    void Pop();
    int Top();
    void Print();
private:
    int A[MAX_SIZE];
    int top = -1;
};

int main()
{
    Stack s;

    s.Push(2);
    s.Push(5);
    s.Push(10);
    s.Pop();
    s.Push(12);
    s.Print();
}

void Stack::Push(int x)
{
    if(top == MAX_SIZE - 1)     //Handling overflow
    {
        cout << "What are we? Some kind of Stack Overflow?";
        return;
    }

    top++;
    A[top] = x;
}

void Stack::Pop()
{
    if(top == -1)
    {
        cout << "List is empty. No element to pop.";
        return;
    }

    top--;
}

int Stack::Top()
{
    return A[top];
}

void Stack::Print()
{
    int i;
    cout << "Stack" << endl;
    for(int i = 0; i <= top; i++)
    {
        cout << A[i] << endl;
    }
}