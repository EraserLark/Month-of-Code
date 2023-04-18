#include <iostream>
#include <vector>

using namespace std;

class Action;   //Forward declare
int RandomNum();

#pragma region //Entities ----------------------------------------------------------------
class Entity{
public:
    const string name;
    const int ATK;
    
    int GetHP()          {return HP;}
    void SetHP(int n)    {HP = n;}
    void SetAction(Action* actionPtr)   {actions.push_back(actionPtr);}
    Action* GetAction(int n)            {return actions[n];}

    virtual void TakeDamage(int dmg)    {HP -= dmg; if(HP < 0)  HP = 0;}
protected:
    Entity(string entName, int hp, int atk)
    :ATK{atk}, name{entName}    {SetHP(hp);}
    vector<Action*> actions;
private:
    int HP;
};

class Player : public Entity{
public:
    Player(string name = "Player", int hp = 15, int atk = 5)
    : Entity(name, hp, atk) { };
};

class Enemy : public Entity{
public:
    Enemy(string name = "The great wizard Defaulto", int hp = 10, int atk = 3)
    : Entity(name, hp, atk) { };
};
#pragma endregion //----------------------------------------------------------------

#pragma region //Actions ----------------------------------------------------------------
class Action{
public:
    const string name;

    Entity* GetSender() {return sender;}
    Entity* GetTarget() {return target;}
    
    virtual ~Action() { }
    virtual void runAction() = 0;     //Pure virtual function

protected:
    Action(string, Entity*, Entity*);
    Entity* sender;
    Entity* target;
};

class PhysicalAttack : public Action{
public:
    PhysicalAttack(string str, int baseDmg, Entity* e1, Entity* e2)
    : Action(str, e1, e2), baseDamage{baseDmg} { }

    virtual void runAction() override
    {
        //int damage = sender->ATK + RandomNum();
        int damage = baseDamage;
        if(damage <= 0)
        {
            cout << "MISS!!" << endl;
        }
        else
        {
            target->TakeDamage(damage);
        }
    }
private:
    const int baseDamage;
};

Action::Action(string n, Entity* sen, Entity* tar)
: name{n}
{
    sender = sen;
    target = tar;
}

#pragma endregion //----------------------------------------------------------------

#pragma region //Queue ----------------------------------------------------------------

class Queue{
private:
    struct Node
    {
        Action* action;
        Node* link;
    };

    Node* head;
    Node* tail;
public:
    Queue();
    void Enqueue(Action*);
    void Dequeue();
    bool IsEmpty();
    void EmptyQueue();
    Action* GetHead();
};

Queue::Queue()
{
    head = nullptr;
    tail = nullptr;
}

void Queue::Enqueue(Action* action)
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

void Queue::Dequeue()
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

bool Queue::IsEmpty()
{
    if(head == nullptr || tail == nullptr)
        return true;
    else
        return false;
}

void Queue::EmptyQueue()
{
    if(head == nullptr && tail == nullptr)
    {
        return;
    }

    Node* temp = nullptr;

    while(head != nullptr)
    {
        temp = head;
        head = head->link;
        delete temp;
        temp = nullptr;
    }
}

Action* Queue::GetHead()
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
void PromptPlayer(Player*);
void PromptEnemy(Enemy*);
void BattleActions(Player*, Enemy*);
void Defeat();
void Victory();

Queue turnQueue;
Queue dungeonQueue;

int main()
{
    cout << "Welcome to BASIC RPG!" << endl << endl;
    cout << "What is your name: ";
    string playerName;
    cin >> playerName;
    cout << endl;

    Player* p = new Player(playerName);
    Enemy* e = new Enemy("Yeti");
    InitializeActions(p, e);

    cout << "Player HP: " << p->GetHP() << '\t' << "Enemy HP: " << e->GetHP() << endl;
    
    //Battle loop
    while(p->GetHP() > 0 && e->GetHP() > 0)
    {
        //Prompt phase
        PromptPlayer(p);
        PromptEnemy(e);

        //Action phase
        BattleActions(p, e);
    }

    if(p->GetHP() <= 0)
    {
        Defeat();
    }
    else if (e->GetHP() <= 0)
    {
        Victory();
    }
}

void InitializeActions(Player* p, Enemy* e)
{
    p->SetAction(new PhysicalAttack("Regular Attack", 5, p, e));
    p->SetAction(new PhysicalAttack("Special Attack", 6, p, e));
    p->SetAction(new PhysicalAttack("Witty Attack?", 3, p, e));
    p->SetAction(new PhysicalAttack("Bounce Attack", 4, p, e));
    
    e->SetAction(new PhysicalAttack("Angry Attack", 3, e, p));
    e->SetAction(new PhysicalAttack("Strange Attack", 4, e, p));
    e->SetAction(new PhysicalAttack("Slam Attack", 5, e, p));
    e->SetAction(new PhysicalAttack("Wacky Attacky", 1, e, p));
}

//Move within player?
void PromptPlayer(Player* p)
{
    int playerActionChoice;
    Action* playerAction;

    cout << endl;
    cout << "Available actions: "<< endl
    << "0 - " << p->GetAction(0)->name << endl
    << "1 - " << p->GetAction(1)->name << endl
    << "2 - " << p->GetAction(2)->name << endl
    << "3 - " << p->GetAction(3)->name << endl;
    do
    {
        cout << "Enter next action: ";
        cin >> playerActionChoice;
    } while (playerActionChoice < 0 || playerActionChoice > 3);

    playerAction = p->GetAction(playerActionChoice);
    turnQueue.Enqueue(playerAction);
}

void PromptEnemy(Enemy* e)
{
    Action* enemyAction = e->GetAction(0);
    turnQueue.Enqueue(enemyAction);
}

void BattleActions(Player* p, Enemy* e)
{ 
    Action* action = nullptr;

    while(!turnQueue.IsEmpty())
    {
        cout << endl;
        action = turnQueue.GetHead();
        cout << action->GetSender()->name << " Action: " << action->name << endl;
        action->runAction();
        cout << "Player HP: " << p->GetHP() << '\t' << "Enemy HP: " << e->GetHP() << endl;

        if(p->GetHP() <= 0 || e->GetHP() <= 0)
        {
            turnQueue.EmptyQueue(); //Empty queue to exit loop, check victory conditions
        }
        else
        {
            turnQueue.Dequeue();
        }
    }
}

int RandomNum()
{
    srand(time(nullptr));
    int randNum = (rand() % 7) - 3;    //Number between -3 and 3
    return randNum;
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