#include <iostream>
#include <vector>

using namespace std;

class Action;   //Forward declare

#pragma region //Entities ----------------------------------------------------------------
class Entity{
public:
    string GetName()        {return name;}
    int GetHP()             {return HP;}
    void SetHP(int n)       {HP = n;}
    void SetAction(Action* actionPtr) {actions.push_back(actionPtr);}
    Action* GetAction(int n)  {return actions[n];}

    virtual void TakeDamage(int dmg)    {HP -= dmg;}
protected:
    Entity(string entName, int hp)   {name = entName, SetHP(hp);}
    vector<Action*> actions;
private:
    int HP;
    string name;
};

class Player : public Entity{
public:
    Player()
    : Entity("Player", 10) { };
};

class Enemy : public Entity{
public:
    Enemy(string name)
    : Entity(name, 6) { };
};
#pragma endregion //----------------------------------------------------------------

#pragma region //Actions ----------------------------------------------------------------
class Action{
public:
    virtual ~Action() { }
    virtual void runAction() = 0;     //Pure virtual function

    string GetName()    {return  name;}
    Entity* GetSender() {return sender;}
    Entity* GetTarget() {return target;}

protected:
    Action(string, Entity*, Entity*);
    Entity* sender;
    Entity* target;
private:
    string name;
};

class BasicAttack : public Action{
public:
    BasicAttack(string str, Entity* e1, Entity* e2)
    : Action(str, e1, e2) { }

    virtual void runAction() override { target->TakeDamage(5); }
};

Action::Action(string n, Entity* sen, Entity* tar)
{
    name = n;
    sender = sen;
    target = tar;
}

#pragma endregion //----------------------------------------------------------------

#pragma region //TurnQueue ----------------------------------------------------------------

class TurnQueue{
private:
    struct Node
    {
        Action* action;
        Node* link;
    };

    Node* head;
    Node* tail;
public:
    TurnQueue();
    void Enqueue(Action*);
    void Dequeue();
    bool IsEmpty();
    Action* GetHead();
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

Action* TurnQueue::GetHead()
{
    if(head != nullptr)
    {
        return head->action;
    }
    return nullptr;
}

#pragma endregion //----------------------------------------------------------------

//Create a Battle class?
void InitializeActions(Player*, Enemy*);
void PromptPlayer(Player*, Enemy*);
void PromptEnemy(Player*, Enemy*);
void BattleActions(Player*, Enemy*);
void Defeat();
void Victory();

TurnQueue turnQueue;

int main()
{
    Player* p = new Player();
    Enemy* e = new Enemy("Yeti");
    InitializeActions(p, e);

    cout << "Welcome to BASIC RPG!" << endl << endl;
    cout << "Player HP: " << p->GetHP() << '\t' << "Enemy HP: " << e->GetHP() << endl;
    
    //Battle loop
    while(p->GetHP() > 0 && e->GetHP() > 0)
    {
        //Prompt phase
        PromptPlayer(p, e);
        PromptEnemy(p, e);

        //Action phase
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

void InitializeActions(Player* p, Enemy* e)
{
    p->SetAction(new BasicAttack("Attack 1", p, e));
    p->SetAction(new BasicAttack("Attack 2", p, e));
    p->SetAction(new BasicAttack("Attack 3", p, e));
    p->SetAction(new BasicAttack("Attack 4", p, e));
    
    e->SetAction(new BasicAttack("Angry Attack", e, p));
    e->SetAction(new BasicAttack("Strange Attack", e, p));
    e->SetAction(new BasicAttack("Slam Attack", e, p));
    e->SetAction(new BasicAttack("Wacky Attacky", e, p));
}

void PromptPlayer(Player* p, Enemy* e)
{
    string playerActionChoice;
    Action* playerAction;

    cout << endl;
    cout << "Available actions: Attack" << endl;
    do
    {
        cout << "Enter next action: ";
        cin >> playerActionChoice;
    } while (playerActionChoice != "Attack");

    if(playerActionChoice == "Attack")
    {
        playerAction = p->GetAction(0);
        turnQueue.Enqueue(playerAction);    //Move this into constructor?
    }
}

void PromptEnemy(Player* p, Enemy* e)
{
    Action* enemyAction = e->GetAction(0);
    turnQueue.Enqueue(enemyAction);
}

void BattleActions(Player* p, Enemy* e)
{ 
    while(!turnQueue.IsEmpty())
    {
        cout << endl;
        Action* action = turnQueue.GetHead();
        cout << action->GetSender()->GetName() << " Action: " << action->GetName() << endl;
        action->runAction();
        cout << "Player HP: " << p->GetHP() << '\t' << "Enemy HP: " << e->GetHP() << endl;
        turnQueue.Dequeue();
    }
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