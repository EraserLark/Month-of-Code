#include <iostream>

using namespace std;

struct Node
{
    int data;
    Node* next;
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
    temp->next = NULL;

    if(pos == 1)    //Special case
    {
        temp->next = head;
        head = temp;
        return;
    }

    Node* temp2 = head;
    for(int i = 0; i < pos-2; i++)
    {
        temp2 = temp2->next;    //Point to n-1 node
    }
    temp->next = temp2->next;
    temp2->next = temp;
}

void Delete(int pos)    //Implemented myself :)
{
    Node* temp = head;

    if(pos==1)  //Special case
    {
        head = temp->next;
        free(temp);
        return;
    }

    for(int i = 0; i < pos-2; i++)
    {
        temp = temp->next;
    }

    Node* temp2 = temp->next;
    cout << "Deleting: " << temp2->data << endl;
    
    temp->next = temp2->next;
    free(temp2);
}

void Print()
{
    Node* temp = head;
    while(temp != NULL)
    {
        cout << temp->data;
        temp = temp->next;
    }
    cout << endl;
}