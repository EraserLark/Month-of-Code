#include <iostream>

using namespace std;

struct Node
{
    int value;
    Node* link;
};

void Enqueue(int);
void Dequeue();
bool IsEmpty();
void Print();

Node* front = NULL;
Node* rear = NULL;

int main()
{
    Enqueue(3);
    Enqueue(2);
    Enqueue(1);
    Dequeue();
    Enqueue(4);
    Print();
}

void Enqueue(int x)
{
    Node* temp = new Node();
    temp->value = x;
    temp->link = NULL;

    if(front == NULL && rear == NULL)
    {
        front = rear = temp;
        return;
    }

    rear->link = temp;
    rear = temp;
}

void Dequeue()
{
    Node* temp = front;

    if(front == NULL) return;

    if(front == rear)
    {
        front = rear = NULL;
    }
    else
    {
        front = front->link;
    }

    free(temp);
}

bool IsEmpty()
{
    if(front == NULL || rear == NULL)
        return true;
    else
        return false;
}

void Print()
{
    Node* temp = front;

    while(temp != NULL)
    {
        cout << temp->value;
        temp = temp->link;
    }

    cout << endl;
}