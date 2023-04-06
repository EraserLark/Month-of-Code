#include <iostream>

using namespace std;

void Enqueue(int);
void Dequeue();
bool isEmpty();
void Print();

int A[10];
int front = -1;
int rear = -1;

int main()
{
    Enqueue(2);
    Enqueue(5);
    Enqueue(7);
    Dequeue();
    Enqueue(3);
    Enqueue(1);
    Enqueue(9);
    Enqueue(10);
    Enqueue(4);
    Enqueue(6);
    Dequeue();
    Enqueue(2);
    Print();
}

void Enqueue(int x)
{
    if(rear == size(A)-1)   //If full
    {
        cout << "Queue is full";
        return;
    }
    else if(isEmpty())      //If empty
    {
        front = 0;
        rear = 0;
    }
    else
    {
        rear++;
    }
    A[rear] = x;
}

void Dequeue()
{
    if(isEmpty())
        return;
    else if(front == rear)
    {
        front = -1;
        rear = -1;
    }
    else
    {
        front++;
    }   
}

bool isEmpty()
{
    if(front == -1 || rear == -1)
        return true;
    else
        return false;
}

void Print()
{
    cout << "Queue: ";
    for(int i : A)
    {
        cout << i << " ";
    }
    cout << endl;
}