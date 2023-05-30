#include <iostream>

using namespace std;

void SelectionSort(int A[], int n);

int main()
{
    int numbers[4] = {3,5,1,9};
    SelectionSort(numbers, 4);
}

void SelectionSort(int A[], int n)
{
    int i;
    int j;
    int smallest;

    for(i = 0; i < n-1; i++)
    {
        smallest = i;
        for(int j = i+1; j < n; j++)
        {
            if(A[j] < A[smallest])
            {
                smallest = j;
            }
        }

        int temp = A[i];
        A[i] = A[smallest];
        A[smallest] = temp;
    }

    //Print
    for(int i = 0; i < n; i++)
    {
        cout << A[i] << ", ";
    }
}