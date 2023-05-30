#include <iostream>

using namespace std;

void BubbleSort(int A[], int n);

int main()
{
    int numArray[4] = {7, 3, 6, 0};
    BubbleSort(numArray, 4);
}

void BubbleSort(int A[], int n)
{
    for(int i = 0; i < n-1; i++)
    {
        for(int j = i+1; j < n; j++)
        {
            if(A[i] > A[j])
            {
                int temp = A[j];
                A[j] = A[i];
                A[i] = temp;
            }
        }
    }

    for(int i = 0; i < n; i++)
    {
        cout << A[i] << ", ";
    }
}