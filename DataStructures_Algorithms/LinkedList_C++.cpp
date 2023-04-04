#include <iostream>

using namespace std;

struct Node
{
    int data;
    Node* next;  
};

void Insert(int);
void Print();

Node* head = NULL;
int main()
{
    Node currentNode;

    int numTotal;

    cout << "How many numbers: ";
    cin >> numTotal;

    for(int i = 0; i < numTotal; i++)
    {
        int newNum;
        cin >> newNum;
        Insert(newNum);
        Print();
    }
}

void Insert(int num)
{
    Node* temp = new Node();
    temp->data = num;
    temp->next = head;  //Head is set to NULL first time through
    head = temp;
}

void Print()
{
    Node* temp = head;
    cout << "List is: ";
    while(temp != NULL)
    {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}