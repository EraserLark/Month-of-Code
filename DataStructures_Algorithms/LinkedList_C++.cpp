#include <iostream>

using namespace std;

struct Node
{
    int data;
    Node* link;  
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
        Print(head);
    }
}

Node* Insert(Node* head, int num)
{
    Node* temp = new Node();
    temp->data = num;
    temp->link = head;  //Head is set to NULL first time through
    head = temp;
    return head;
}

void Print(Node* head)
{
    cout << "List is: ";
    while(head != NULL)
    {
        cout << head->data << " ";
        head = head->link;
    }
    cout << endl;
}