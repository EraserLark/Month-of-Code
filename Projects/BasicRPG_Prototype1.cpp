#include <iostream>

using namespace std;

class Player{
public:
    int HP = 10;
};

class Enemy{
public:
    int HP = 5;
};

class Action{
    string name;
};

class TurnQueue{
    Action queue[2];
};

int main()
{
    Player p;
    Enemy e;

    cout << "Welcome to BASIC RPG!" << endl << endl;

    cout << "Player HP: " << p.HP << '\t' << "Enemy HP: " << e.HP << endl;
}