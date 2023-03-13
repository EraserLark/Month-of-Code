#include <stdio.h>

void BitwiseLogicalCompare();
void LeftShift();
void ExclusiveOr();

//https://youtu.be/jlQmeyce65Q?t=312
//Difference between Bitwise/Logical Operators
int main(void)
{
    ExclusiveOr();
    
    return 0;
}

void BitwiseLogicalCompare()
{
    char x = 1;     //0000 0001
    char y = 2;     //0000 0010

    if(x & y)   //Bitwise   //1&2 = 0(0000 0000) = FALSE
        printf("Result of x&y is 1");
    if(x && y)  //Logical   //1 && 2 = TRUE && TRUE
        printf("Result of x&&y is 1");
}

void LeftShift()
{
    char var = 3;   //3 in binary = 0000 0011
    printf("%d", var<<1);
    //Bits get shifted left once to 0000 0110
}

void ExclusiveOr()
{
    int a = 4;  //0000 0100
    int b = 3;  //0000 0011

    a = a^b;    //0000 0111
    b = a^b;    //Do math to see...

    printf("After XOR, a = %i and b = %i", a, b);
}