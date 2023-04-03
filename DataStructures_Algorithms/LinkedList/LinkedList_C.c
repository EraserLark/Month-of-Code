#include<stdlib.h>
#include<stdio.h>

struct Node{
    int data;
    struct Node* link;
};

struct Node* head;

void Insert(int x);
void Print();

int main(void)
{
    head = NULL;

    printf("How many numbers?\n");
    int n, x;
    scanf("%d", &n);
    for(int i = 0; i < n; i++)
    {
        printf("Enter the number: \n");
        scanf("%d", &x);
        Insert(x);
        Print();
    }
}

void Insert(int x)
{
    struct Node* temp = malloc(sizeof(struct Node));
    temp->data = x;
    temp->link = head;
    head = temp;
}

//Traversing the List
void Print()
{
    struct Node* temp = head;
    printf("The list is: ");

    while(temp != NULL)
    {
        printf(" %d", temp->data);
        temp = temp->link;
    }
    printf('\n');
}