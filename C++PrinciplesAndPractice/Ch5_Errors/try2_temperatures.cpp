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

    double sum = 0;
    double highTemp = 0;
    double lowTemp = 0;

    for (int x : temps)
    {
        if (x > highTemp) highTemp = x;
        if (x < lowTemp) lowTemp = x;
        sum += x;
    }

    cout << "High temperature: " << highTemp << '\n';
    cout << "Low temeperature: " << lowTemp << '\n';
    cout << "Average temperature: " << sum / temps.size() << '\n';
}