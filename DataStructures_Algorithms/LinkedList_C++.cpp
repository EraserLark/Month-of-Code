#include <iostream>

using namespace std;

struct Node
{
    int value;
    Node* next;  
};

Node* Insert(Node*, int);
void Print(Node*);

int main()
{
    Node* head = NULL;
    Node currentNode;

    int numTotal;

    cout << "How many numbers: ";
    cin >> numTotal;

    for(int i = 0; i < numTotal; i++)
    {
        int newNum;
        cin >> newNum;
        head = Insert(head, newNum);
    }

    Print(head);
}

Node* Insert(Node* temp, int num)
{
    temp = new Node();
    temp->value = num;
    temp->next = NULL;
    return temp;
}

void Print(Node* temp)
{
    while(temp != NULL)
    {
        cout << temp->value << endl;
        temp = temp->next;
    }
}