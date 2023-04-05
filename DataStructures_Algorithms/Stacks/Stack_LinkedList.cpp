#include <iostream>

using namespace std;

struct Node{
    int data;
    Node* link;
};

class Stack{
public:
    void Push(int x);
    void Pop();
    int Top();
    void Print();
private:
    Node* top = NULL;  //Head
};

int main()
{
    Stack s;

    s.Push(3);
    s.Push(6);
    s.Push(11);
    s.Pop();
    s.Push(13);
    s.Print();
}

void Stack::Push(int x)
{
    Node* temp = new Node();
    temp->data = x;

    temp->link = top;
    top = temp;
}

void Stack::Pop()
{
    Node* temp;
    if(top == NULL) return;

    temp = top;
    top = top->link;
    free(temp);
}

void Stack::Print()
{
    cout << "Stack" << endl;
    while(top != NULL)
    {
        cout << top->data << endl;
        top = top->link;
    }
}