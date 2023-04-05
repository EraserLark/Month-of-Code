#include <iostream>

using namespace std;

struct Node{
    int data;
    Node* link;
};

Node* head = NULL;
void Insert(int, int);
void Remove(int);
void Reverse();
void Print();

int main()
{
    Insert(4,1);
    Insert(5,2);
    Insert(2,1);
    Insert(3,2);
    Print();
    Reverse();
    //Remove(3);
    Print();
}

void Insert(int number, int pos)
{
    Node* temp = new Node();
    temp->data = number;
    temp->link = NULL;

    if(pos == 1)
    {
        temp->link = head;
        head = temp;
        return;
    }

    Node* temp2 = head;
    for(int i = 0; i < pos-2; i++)
    {
        temp2 = temp2->link;
    }

    //Now, temp2 points to the Node before this new Node we want to insert
    //temp points to the new node we want to insert

    temp->link = temp2->link;
    temp2->link = temp;

    //Need to add a temp pointer for each of the node pointers you will be changing in this function (Insertion = 2)
}

void Remove(int pos)
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

void Reverse()
{
    Node* current = head;
    Node* prev = NULL;
    Node* next = NULL;

    //Traverse list
    while(current != NULL)
    {
        next = current->link;
        current->link = prev;

        prev = current;
        current = next;
    }

    head = prev;
}