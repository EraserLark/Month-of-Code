#include <iostream>
#include <queue>

using namespace std;

struct Node{
    int value;
    Node* left;
    Node* right;
};

Node* CreateNode(int);
void Insert(Node*&, int);
bool Search(Node*, int);
int FindMin(Node*);
int FindMax(Node*);
int FindHeight(Node*);
void LevelOrder(Node*);

int main()
{
    Node* rootPtr = NULL;   //Empty tree

    Insert(rootPtr, 15);
    Insert(rootPtr, 10);
    Insert(rootPtr, 20);
    Insert(rootPtr, 25);

    cout << "Min: " << FindMin(rootPtr) << endl;
    cout << "Max: " << FindMax(rootPtr) << endl;

    cout << "Height: " << FindHeight(rootPtr) << endl;

    cout << "Level Order traversal: ";
    LevelOrder(rootPtr);
    cout << endl;

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

int FindMin(Node* root)
{
    if(root == NULL)
    {
        cout << "Tree is empty" << endl;
        return -1;
    }

    while(root->left != NULL)
    {
        root = root->left;
    }

    return root->value;   
} 

int FindMax(Node* root)
{
    if(root == NULL)
    {
        cout << "Tree is empty" << endl;
        return -1;
    }

    while(root->right != NULL)
    {
        root = root->right;
    }

    return root->value;   
} 

int FindHeight(Node* root)
{
    if(root == NULL)
    {
        return -1;
    }
    return max(FindHeight(root->left), FindHeight(root->right)) +1; //Adds +1 for each recursive call
}

void LevelOrder(Node* root)
{
    if(root == NULL) return;

    queue<Node*> Q;
    Q.push(root);

    while(!Q.empty())
    {
        Node* current = Q.front();
        cout << current->value << " ";

        if(current->left != NULL) Q.push(current->left);
        if(current->right != NULL) Q.push(current->right);

        Q.pop();
    }
}