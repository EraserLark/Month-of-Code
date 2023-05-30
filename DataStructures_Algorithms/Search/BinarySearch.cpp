#include <iostream>

using namespace std;

int BinarySearch(int A[], int n, int v);

int main()
{
    int numArray[6] = {1,2,3,4,5,6};
    int checkNum = 4;
    cout << "Does this array contain: " << checkNum << "?" << endl;
    cout << BinarySearch(numArray, 6, checkNum);
}

int BinarySearch(int A[], int n, int v)
{
    int start = 0;
    int end = n-1;

    while(start <= end)
    {
        int mid = (start + end) / 2;

        if(A[mid] == v)
        {
            return mid;
        }
        else if(A[mid] < v)
        {
            start = mid + 1;
        }
        else if(A[mid] > v)
        {
            end = mid - 1;
        }
    }

    return -1;
}