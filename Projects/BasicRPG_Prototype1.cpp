#include <iostream>

using namespace std;

#pragma region //Entities ----------------------------------------------------------------
class Entity{
public:
    Entity(int hp)   {HP = hp;}
    int GetHP()         {return HP;}
    void SetHP(int n)   {HP += n;}
protected:
    virtual void TakeDamage(int);
private:
    int HP;
};

class Player : public Entity{
    using Entity::Entity;

    void TakeDamage(int);
};

class Enemy : public Entity{
    using Entity::Entity;

    void TakeDamage(int);
};
#pragma endregion //----------------------------------------------------------------

#pragma region //Actions ----------------------------------------------------------------
class Action{
public:
    Action(string, Entity*, Entity*);
    virtual ~Action();
    virtual void runAction() = 0;     //Pure virtual function
    string name;
    Entity* sender;
    Entity* target;
};

class BasicAttack : public Action{
    using Action::Action;
    void runAction() { target->SetHP(-5); }
};

Action::Action(string n, Entity* sen, Entity* tar)
{
    name = n;
    sender = sen;
    target = tar;
}

#pragma endregion //----------------------------------------------------------------

#pragma region //TurnQueue ----------------------------------------------------------------
//Could I move Node inside of the TurnQueue class? Public or Private?
struct Node{
    Action* action;
    Node* link;
};

class TurnQueue{
public:
    TurnQueue();
    void Enqueue(Action*);
    void Dequeue();
    bool IsEmpty();
    Node* GetHead();
private:
    Node* head;
    Node* tail;
};

TurnQueue::TurnQueue()
{
    head = nullptr;
    tail = nullptr;
}

void TurnQueue::Enqueue(Action* action)
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

#pragma endregion //----------------------------------------------------------------

void PromptPlayer(Player*, Enemy*);
void BattleActions(Player*, Enemy*);
void Defeat();
void Victory();

TurnQueue turnQueue;

int main()
{
    Player* p = new Player(10);
    Enemy* e = new Enemy(5);

    cout << "Welcome to BASIC RPG!" << endl << endl;
    cout << "Player HP: " << p->GetHP() << '\t' << "Enemy HP: " << e->GetHP() << endl;
    
    //Battle loop
    while(p->GetHP() > 0 && e->GetHP() > 0)
    {
        PromptPlayer(p, e);
        BattleActions(p, e);
    }

    if(p->GetHP() < 0)
    {
        Defeat();
    }
    else if (e->GetHP() < 0)
    {
        Victory();
    }
}

void PromptPlayer(Player* p, Enemy* e)
{
    string playerAction;

    cout << endl;
    cout << "Available actions: Attack" << endl;
    do
    {
        cout << "Enter next action: ";
        cin >> playerAction;
    } while (playerAction != "Attack");

    if(playerAction == "Attack")
    {
        BasicAttack playerAction("Attack", p, e);
        turnQueue.Enqueue(&playerAction);
    }

    BasicAttack enemyAction("Angry attack", e, p);
    turnQueue.Enqueue(&enemyAction);
}

void BattleActions(Player* p, Enemy* e)
{ 
    for(int i = 0; i < 2; i++)
    {
        cout << endl;
        Node* temp = turnQueue.GetHead();
        cout << "Player Action: " << temp->action->name << endl;
        e->SetHP(-5);
        cout << "Player HP: " << p->GetHP() << '\t' << "Enemy HP: " << e->GetHP() << endl;
        turnQueue.Dequeue();
    }


    Node* temp = turnQueue.GetHead();
    cout << "Enemy Action: " << temp->action->name << endl;
    p->SetHP(-3);
    cout << "Player HP: " << p->GetHP() << '\t' << "Enemy HP: " << e->GetHP() << endl << endl;
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