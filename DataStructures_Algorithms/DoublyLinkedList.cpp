#include <iostream>

using namespace std;

struct Node
{
    int data;
    Node* next;
    Node* prev;
};

Node* GetNewNode(int x);
void InsertAtHead(int x);
void InsertAtTail(int x);
void Print();
void ReversePrint();

Node* head;

int main()
{
    
}

Node* GetNewNode(int x)
{
    Node* newNode = new Node();
    newNode->data = x;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

void InsertAtHead(int x)
{
    Node* temp = GetNewNode(x);

    if(head == NULL)
    {
        head = temp;
        return;
    }

    head->prev = temp;
    temp->next = head;
    head = temp;
}