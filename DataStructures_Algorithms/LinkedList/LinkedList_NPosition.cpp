#include <iostream>

using namespace std;

struct Node
{
    int data;
    Node* link;
};

void Insert(int, int);
void Delete(int);
void Print();

Node* head = NULL;  //empty list

int main()
{
    Insert(2,1);
    Insert(3,2);
    Insert(4,1);
    Insert(5,2);
    Delete(3);
    Print();
}

void Insert(int value, int pos)
{
    Node* temp = new Node();
    temp->data = value;
    temp->link = NULL;

    if(pos == 1)    //Special case
    {
        temp->link = head;
        head = temp;
        return;
    }

    Node* temp2 = head;
    for(int i = 0; i < pos-2; i++)
    {
        temp2 = temp2->link;    //Point to n-1 node
    }
    temp->link = temp2->link;
    temp2->link = temp;
}

void Delete(int pos)    //Implemented myself :)
{
    Node* temp = head;

    if(pos==1)  //Special case
    {
        head = temp->link;
        free(temp);
        return;
    }

    for(int i = 0; i < pos-2; i++)
    {
        temp = temp->link;
    }

    Node* temp2 = temp->link;
    cout << "Deleting: " << temp2->data << endl;
    
    temp->link = temp2->link;
    free(temp2);
}

void Print()
{
    Node* temp = head;
    while(temp != NULL)
    {
        cout << temp->data;
        temp = temp->link;
    }
    cout << endl;
}