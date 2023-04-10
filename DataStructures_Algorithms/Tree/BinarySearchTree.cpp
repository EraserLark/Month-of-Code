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
Node* SearchPtr(Node*, int);
int FindMin(Node*);
int FindMax(Node*);
int FindHeight(Node*);
Node* Delete(Node*, int);
int GetSuccessor(Node*, int);

void LevelOrder(Node*);
void PreOrder(Node*);
void InOrder(Node*);
void PostOrder(Node*);

bool IsBinarySearchTree(Node*);
bool IsBstUtil(Node*, int, int);
//bool SubtreeLesser(Node*, int);
//bool SubtreeGreater(Node*, int);

int main()
{
    Node* rootPtr = NULL;   //Empty tree

    Insert(rootPtr, 20);
    Insert(rootPtr, 15);
    Insert(rootPtr, 25);
    Insert(rootPtr, 10);
    Insert(rootPtr, 30);
    Insert(rootPtr, 2);

    cout << "Min: " << FindMin(rootPtr) << endl;
    cout << "Max: " << FindMax(rootPtr) << endl;
    cout << "Height: " << FindHeight(rootPtr) << endl;

    cout << "Level Order traversal: ";
    LevelOrder(rootPtr);
    cout << endl;
    cout << "Preorder traversal: ";
    PreOrder(rootPtr);
    cout << endl;
    cout << "Inorder traversal: ";
    InOrder(rootPtr);
    cout << endl;
    cout << "Postorder traversal: ";
    PostOrder(rootPtr);
    cout << endl;

    Delete(rootPtr, 15);
    cout << "Postorder traversal: ";
    PostOrder(rootPtr);
    cout << endl;

    cout << "Is Binary Search Tree? " << IsBinarySearchTree(rootPtr) << endl;
    cout << "Successor of 20 is: " << GetSuccessor(rootPtr, 20) << endl;

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

Node* SearchPtr (Node* rootPtr, int data)
{
    if(rootPtr == NULL) return nullptr;
    else if(rootPtr->value == data) return rootPtr;
    else if(data <= rootPtr->value) return SearchPtr(rootPtr->left, data);
    else return SearchPtr(rootPtr->right, data);
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

void PreOrder(Node* root)
{
    if(root == NULL) return;
    cout << root->value << " ";

    PreOrder(root->left);
    PreOrder(root->right);
}

void InOrder(Node* root)
{
    if(root == NULL) return;

    PreOrder(root->left);
    cout << root->value << " ";
    PreOrder(root->right);
}

void PostOrder(Node* root)
{
    if(root == NULL) return;

    PreOrder(root->left);
    PreOrder(root->right);
    cout << root->value << " ";
}

bool IsBinarySearchTree(Node* root)
{
    return IsBstUtil(root, INT_MIN, INT_MAX);
}

bool IsBstUtil(Node* root, int min, int max)
{
    if(root == NULL) return true;

    if(root->value > min
        && root->value < max
        && IsBstUtil(root->left, min, root->value)
        && IsBstUtil(root->right, root->value, max))
    {
        return true;
    }
    else
        return false;
}

Node* Delete(Node* root, int data)
{
    if(root == NULL)    return root;
    else if(data < root->value)  root->left = Delete(root->left, data);
    else if(data > root->value)    root->right = Delete(root->right, data);
    else    //Found node to delete
    {
        //Case 1: Leaf node
        if(root->left == NULL && root->right==NULL)
        {
            delete root;
            root = NULL;
        }
        //Case 2: One child
        else if(root->left == NULL)
        {
            Node* temp = root;
            root = root->right;
            delete temp;
        }
        else if(root->right == NULL)
        {
            Node* temp = root;
            root = root->left;
            delete temp;
        }
        //Case 3: 2 children
        else
        {
            Node* temp = root;
            
            //Find max in left branch
            temp = temp->left;
            while(temp->right != NULL && temp->left != NULL)
            {
                if(temp->right != NULL)
                {
                    temp = temp->right;
                }
                else if(temp->left != NULL)
                {
                    temp = temp->left;
                }
            }

            //Copy max value
            root->value = temp->value;

            //Delete now-duplicate node
            root->left = Delete(root->left, temp->value);
        }
    }

    return root;
}

//Time complexity: O(h)
int GetSuccessor(Node* root, int data)
{
    Node* current = SearchPtr(root, data);
    if(current == NULL) return NULL;

    //Case 1: Node has right subtree
    if(current->right != NULL)
    {
        return FindMin(current->right);
    }
    //Case 2: No right subtree
    else
    {
        Node* successor = NULL;
        Node* ancestor = root;

        while(ancestor != current)
        {
            if(current->value < ancestor->value)
            {
                successor = ancestor;
                ancestor = ancestor->left;
            }
            else
            {
                ancestor = ancestor->right;
            }
        }

        return successor->value;
    }
}

/*
bool SubtreeLesser(Node* root, int data)
{
    if(root == NULL) return true;
    if(root->value <= data
        &&SubtreeLesser(root->left, data)
        &&SubtreeLesser(root->right, data))
        return true;
    else
        return false;
}

bool SubtreeGreater(Node* root, int data)
{
    if(root == NULL) return true;
    if(root->value > data
        &&SubtreeGreater(root->left, data)
        &&SubtreeGreater(root->right, data))
        return true;
    else
        return false;
}
*/