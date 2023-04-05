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
    InsertAtHead(4);
    InsertAtHead(3);
    InsertAtHead(7);
    Print();
    ReversePrint();
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

    head->prev = temp;      //First node.prev points to new Node
    temp->next = head;      //new Node.next points to First node
    head = temp;            //Head points to new Node (now the first node in list)
}

void ReversePrint()
{
    Node* temp = head;
    if(temp == NULL) return;    //empty list

    while(temp->next != NULL)
    {
        temp = temp->next;
    }

    while(temp != NULL)
    {
        cout << temp->data;
        temp = temp->prev;
    }

    cout << endl;
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