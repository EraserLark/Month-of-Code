#include <iostream>

using namespace std;

struct Node{
    int data;
    Node* link;
};

void Print(Node* p);
void ReversePrint(Node* p);
Node* RecursiveReverse(Node*);
Node* Insert(Node* head, int data);

int main()
{
    Node* head = NULL;
    head = Insert(head, 2);
    head = Insert(head, 4);
    head = Insert(head, 6);
    head = Insert(head, 5);
    Print(head);
    //ReversePrint(head);
    head = RecursiveReverse(head);
    Print(head);
}

Node* Insert(Node* head, int data)
{
    Node* temp = new Node();
    temp->data = data;
    temp->link = NULL;

    if(head == NULL) head = temp;
    else
    {
        Node* temp2 = head;
        while(temp2->link != NULL) temp2 = temp2->link;
        temp2->link = temp;
    }

    return head;
}

void Print(Node* p)
{
    if(p == NULL) return;   //exit condition
    printf("%d ", p->data);
    Print(p->link);         //recursive call
}

void ReversePrint(Node* p)
{
    if(p == NULL) return;   //exit condition
    ReversePrint(p->link);  //recursive call
    printf("%d ", p->data);
}

Node* RecursiveReverse(Node* p)
{
    if(p == NULL)
    {
        return p;
    }
    
    RecursiveReverse(p->link);

    Node* q = p->link;
    q->link = p;
    p->link = NULL;
}