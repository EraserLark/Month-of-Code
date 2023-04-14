#include <iostream>

using namespace std;

class Actor{

};

class Player : Actor{
public:
    int HP = 10;
};

class Enemy : Actor{
public:
    int HP = 5;
};

class Action{
public:
    string name;
    Actor sender;
    Actor target;
};

//Could I move Node inside of the TurnQueue class? Public or Private?
struct Node{
    Action action;
    Node* link;
};

class TurnQueue{
public:
    TurnQueue();
    void Enqueue(Action);
    void Dequeue();
    bool IsEmpty();
    Node* GetHead();
private:
    Node* head;
    Node* tail;
};

void PromptPlayer();
void BattleActions();
void Defeat();
void Victory();

TurnQueue turnQueue;
Player p;
Enemy e;
string playerAction;

int main()
{
    cout << "Welcome to BASIC RPG!" << endl << endl;
    cout << "Player HP: " << p.HP << '\t' << "Enemy HP: " << e.HP << endl;
    
    //Battle loop
    while(p.HP > 0 && e.HP > 0)
    {
        PromptPlayer();
        BattleActions();
    }

    if(p.HP < 0)
    {
        Defeat();
    }
    else if (e.HP < 0)
    {
        Victory();
    }
}

void PromptPlayer()
{
    cout << endl;
    cout << "Available actions: Attack" << endl;
    do
    {
        cout << "Enter next action: ";
        cin >> playerAction;
    } while (playerAction != "Attack");

    if(playerAction == "Attack")
    {
        Action playerAction;
        playerAction.name = "Attack";
        turnQueue.Enqueue(playerAction);
    }

    Action enemyAction;
    enemyAction.name = "Angry attack";
    turnQueue.Enqueue(enemyAction);
}

void BattleActions()
{   
    cout << endl;
    Node* temp = turnQueue.GetHead();
    cout << "Player Action: " << temp->action.name << endl;
    e.HP -= 3;
    cout << "Player HP: " << p.HP << '\t' << "Enemy HP: " << e.HP << endl;
    turnQueue.Dequeue();

    temp = turnQueue.GetHead();
    cout << "Enemy Action: " << temp->action.name << endl;
    p.HP -= 5;
    cout << "Player HP: " << p.HP << '\t' << "Enemy HP: " << e.HP << endl << endl;
    turnQueue.Dequeue();
}

void Victory()
{
    cout << "----------" << endl;
    cout << "YOU WIN!" << endl;
}

void Defeat()
{
    cout << "----------" << endl;
    cout << "...you lose." << endl;
}

TurnQueue::TurnQueue()
{
    head = nullptr;
    tail = nullptr;
}

void TurnQueue::Enqueue(Action action)
{
    Node* temp = new Node();
    temp->action = action;
    temp->link = nullptr;

    if(head == nullptr && tail == nullptr)
    {
        head = tail = temp;
        return;
    }

    tail->link = temp;
    tail = temp;
}

void TurnQueue::Dequeue()
{
    Node* temp = head;

    if(head == nullptr)
    {
        return;
    }

    if(head == tail)
    {
        head = tail = nullptr;
    }
    else
    {
        head = head->link;
    }

    delete temp;
}

bool TurnQueue::IsEmpty()
{
    if(head == nullptr || tail == nullptr)
        return true;
    else
        return false;
}

Node* TurnQueue::GetHead()
{
    return head;
}