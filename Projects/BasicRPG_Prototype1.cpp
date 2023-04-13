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
    string playerAction;

    cout << "Welcome to BASIC RPG!" << endl << endl;
    cout << "Player HP: " << p.HP << '\t' << "Enemy HP: " << e.HP << endl << endl;
    cout << "Available actions: Attack" << endl;
    do
    {
        cout << "Enter next action: ";
        cin >> playerAction;
    } while (playerAction != "Attack");
    
    cout << endl;
    cout << "Player Attacks!" << endl;
    e.HP -= 3;
    cout << "Player HP: " << p.HP << '\t' << "Enemy HP: " << e.HP << endl;
    cout << "Enemy Attacks!" << endl;
    p.HP -= 5;
    cout << "Player HP: " << p.HP << '\t' << "Enemy HP: " << e.HP << endl << endl;
    
    cout << "Available actions: Attack" << endl;
    do
    {
        cout << "Enter next action: ";
        cin >> playerAction;
    } while (playerAction != "Attack");
    
}