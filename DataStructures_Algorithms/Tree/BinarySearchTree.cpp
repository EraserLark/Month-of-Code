#include <iostream>

using namespace std;

struct Node{
    int value;
    Node* left;
    Node* right;
};

Node* CreateNode(int);
void Insert(Node*&, int);
bool Search(Node*, int);

int main()
{
    Node* rootPtr = NULL;   //Empty tree

    Insert(rootPtr, 15);
    Insert(rootPtr, 10);
    Insert(rootPtr, 20);
    Insert(rootPtr, 25);

    int num;
    cout << "Enter number you want to search: ";
    cin >> num;
    if(Search(rootPtr, num) == true) cout << "Found it!\n";
    else cout << "Not found.\n";
}

Node* CreateNode(int data)
{
    Node* newNode = new Node();
    newNode->value = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

//Implemented using Recursion
void Insert(Node*& rootPtr, int data)
{
    if(rootPtr == NULL)
    {
        rootPtr = CreateNode(data);
    }
    else if(data <= rootPtr->value)
    {
        Insert(rootPtr->left, data);
    }
    else if(data > rootPtr->value)
    {
        Insert(rootPtr->right, data);
    }
}

bool Search (Node* rootPtr, int data)
{
    if(rootPtr == NULL) return false;
    else if(rootPtr->value == data) return true;
    else if(data <= rootPtr->value) return Search(rootPtr->left, data);
    else return Search(rootPtr->right, data);
}