#include <iostream>
#include <cmath>

int main()
{
    std::cout << "Please enter a integer value: ";
    int n;
    double d = n;
    std::cin >> n;
    std::cout << "n == " << n
    << "\nn+1 == " << n+1
    << "\nthree times n == " << 3*n
    << "\ntwice n == " << n+n
    << "\nn squared == " << n*n
    << "\nhalf of n == " << n/2
    << "\nsquare root of n == " << std::sqrt(d)
    << '\n'; // another name for newline (“end of line”) in output
}