#include <iostream>

using namespace std;

struct Node{
    int data;
    Node* next;
};

void Print(Node* p);
Node* Insert(Node* head, int data);

int main()
{
    Node* head = NULL;
    head = Insert(head, 2);
    head = Insert(head, 4);
    head = Insert(head, 6);
    head = Insert(head, 5);
    Print(head);
}

Node* Insert(Node* head, int data)
{
    Node* temp = new Node();
    temp->data = data;
    temp->next = NULL;

    if(head == NULL) head = temp;
    else
    {
        Node* temp2 = head;
        while(temp2->next != NULL) temp2 = temp2->next;
        temp2->next = temp;
    }

    return head;
}

void Print(Node* p)
{
    if(p == NULL) return;   //exit condition
    Print(p->next);         //recursive call
    printf("%d ", p->data);
}