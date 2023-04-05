#include <iostream>
#include <stack>

using namespace std;

struct Node
{
    int data;
    Node* link;
};

void Insert(int);
void Delete();
void Print();
void Print();

Node* head = NULL;

int main()
{
    stack<Node*> s;

    Insert(1);
    Insert(2);
    Insert(3);
    Insert(4);

    
    //Traverse list
    Node* temp = head;
    while(temp != NULL)
    {
        s.push(temp);
        temp = temp->link;
    }

    //Set head to end of list
    Node* temp2 = s.top();
    head = temp2;
    s.pop();

    //Work backwards, establishing new links
    while(!s.empty())
    {
        temp2->link = s.top();
        s.pop();
        temp2 = temp2->link;
    }
    temp2->link = NULL;

    Print();
}

void Insert(int val)
{
    Node* temp = new Node();
    temp->data = val;

    if(head == NULL)
    {
        head = temp;
        return;
    }

    temp->link = head;
    head = temp;
}

void Print()
{
    Node* temp = head;

    while(temp!=NULL)
    {
        cout << temp->data << endl;
        temp = temp->link;
    }
}