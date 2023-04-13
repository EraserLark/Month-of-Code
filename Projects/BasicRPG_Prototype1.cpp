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
public:
    string name;
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

int main()
{
    TurnQueue turnQueue;
    Player p;
    Enemy e;
    string playerAction;

    cout << "Welcome to BASIC RPG!" << endl << endl;
    cout << "Player HP: " << p.HP << '\t' << "Enemy HP: " << e.HP << endl;
    
    while(p.HP > 0 && e.HP > 0)
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
        
        cout << endl;
        Node* temp = turnQueue.GetHead();
        cout << "Player Action: " << temp->action.name << endl;
        e.HP -= 3;
        cout << "Player HP: " << p.HP << '\t' << "Enemy HP: " << e.HP << endl;
        cout << "Enemy Attacks!" << endl;
        p.HP -= 5;
        cout << "Player HP: " << p.HP << '\t' << "Enemy HP: " << e.HP << endl << endl;
    }
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