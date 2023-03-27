#include <iostream>
#include <vector>

using namespace std;

int main()
{
    vector<double> temps;

    for(double temp; cin >> temp;)
    {
        temps.push_back(temp);
    }

    double highTemp = 200;
    double lowTemp = -200;
    int tempNum = 0;
    double sum = 0;

    for (double x : temps)
    {
        tempNum++;
        sum += x;
        if (x > highTemp) highTemp = x;
        if (x < lowTemp) lowTemp = x;
    }

    cout << "High temperature: " << highTemp << '\n';
    cout << "Low temeperature: " << lowTemp << '\n';
    cout << "Average temperature: " << sum / tempNum << '\n';
}