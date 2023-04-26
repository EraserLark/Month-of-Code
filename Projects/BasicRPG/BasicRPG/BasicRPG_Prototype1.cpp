#include <Windows.h>
#include <iostream>
#include <vector>
#include "action.h"
#include "entity.h"
#include "queue.h"

using namespace std;

#pragma region //Actions ----------------------------------------------------------------

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

#pragma endregion //----------------------------------------------------------------

#pragma region //Entities ----------------------------------------------------------------

class Player : public Entity{
public:
    Player(string name = "Player", int hp = 15, int atk = 5)
    : Entity(name, hp, atk) {
        SetAction(new PhysicalAttack("Regular Attack", 5, this, nullptr));
        SetAction(new PhysicalAttack("Special Attack", 5, this, nullptr));
        SetAction(new PhysicalAttack("Witty Attack?", 5, this, nullptr));
        SetAction(new PhysicalAttack("Bounce Attack", 5, this, nullptr));
    };
    ~Player() {}
};

class Enemy : public Entity{
public:
    Enemy(string name, int hp, int atk)
    : Entity(name, hp, atk) { };
    virtual ~Enemy() override {}
};

class Goblin : public Enemy{
    public:
    Goblin()
    : Enemy("Goblin", 7, 3){ 
        SetAction(new PhysicalAttack("Goblin Attack", 5, this, nullptr));
        SetAction(new PhysicalAttack("Special Goblin Attack", 5, this, nullptr));
        SetAction(new PhysicalAttack("Goblin Gutpunch", 5, this, nullptr));
        SetAction(new PhysicalAttack("Piroutte", 5, this, nullptr));
    };
    virtual ~Goblin() override {}
};
#pragma endregion //----------------------------------------------------------------

#pragma region //Queue ----------------------------------------------------------------

#pragma endregion //----------------------------------------------------------------

//Create a Battle class?
void InitializeActions(Player*, Enemy*);
void PromptPlayer(Player*);
void PromptEnemy(Enemy*);
void BattleActions(Player*, Enemy*);
void Defeat();
void Victory();
void WrapUp();

Queue<Action> turnQueue;
Queue<Enemy> dungeonQueue;

int main()
//int WINAPI wWinMain(HINSTANCE hInstance,)
{
    dungeonQueue.Enqueue(new Goblin());
    dungeonQueue.Enqueue(new Goblin());

    cout << "Welcome to BASIC RPG!" << endl << endl;
    cout << "What is your name: ";
    string playerName;
    cin >> playerName;
    cout << endl;


    while(!dungeonQueue.IsEmpty())
    {
        Player* p = new Player(playerName);
        Enemy* e = dungeonQueue.GetHead();
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
            dungeonQueue.Dequeue();
            delete e;
            delete p;
        }
    }

    cout << "Thanks for playing!" << endl;
}

void InitializeActions(Player* p, Enemy* e)
{
    p->SetAction(new PhysicalAttack("Regular Attack", 5, p, nullptr));
    p->SetAction(new PhysicalAttack("Special Attack", 6, p, nullptr));
    p->SetAction(new PhysicalAttack("Witty Attack?", 3, p, nullptr));
    p->SetAction(new PhysicalAttack("Bounce Attack", 4, p, nullptr));
    
    e->SetAction(new PhysicalAttack("Angry Attack", 3, e, p));
    e->SetAction(new PhysicalAttack("Strange Attack", 4, e, p));
    e->SetAction(new PhysicalAttack("Slam Attack", 5, e, p));
    e->SetAction(new PhysicalAttack("Wacky Attacky", 1, e, p));
}

//Move within player?
void PromptPlayer(Player* p)
{
    int playerActionChoice;
    Action* playerAction = nullptr;

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

    //Check if playerAction is null
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